#ifndef RW_CURRENCY_DECIMAL_CC
#define RW_CURRENCY_DECIMAL_CC

/*--------------------------------------------------------------
 *
 * Implementation of RWDecimal and related classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/decimal.cc#1 $
 *
 * Copyright (c) 1993-2016 Rogue Wave Software, Inc.  All Rights Reserved.
 * 
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software, Inc.
 * pursuant to a written license agreement and may be used, copied, transmitted,
 * and stored only in accordance with the terms of such license agreement and
 * with the inclusion of the above copyright notice.  This computer software or
 * any other copies thereof may not be provided or otherwise made available to
 * any other person.
 * 
 * U.S. Government Restricted Rights.  This computer software: (a) was
 * developed at private expense and is in all respects the proprietary
 * information of Rogue Wave Software, Inc.; (b) was not developed with
 * government funds; (c) is a trade secret of Rogue Wave Software, Inc. for all
 * purposes of the Freedom of Information Act; and (d) is a commercial item and
 * thus, pursuant to Section 12.212 of the Federal Acquisition Regulations (FAR)
 * and DFAR Supplement Section 227.7202, Government's use, duplication or
 * disclosure of the computer software is subject to the restrictions set forth
 * by Rogue Wave Software, Inc.
 *
 *--------------------------------------------------------------*/

/* for backward compatibility */
#ifndef RW_MONEY_DECIMAL_CC
#  define RW_MONEY_DECIMAL_CC
#endif

#include <rw/dcmldefs.h>
#include <rw/decio.h>
#include <rw/decin.h>
#include <rw/message.h>
#include <rw/rwfile.h>
#include <rw/vstream.h>
#include <limits>
#include <sstream>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <ctype.h>
#  include <stdlib.h>
#else
#  include <cctype>
#  include <cstdlib>
#endif

#if defined(_WIN32)
#  include <float.h>
#  define isnan(x) _isnan(x)
#endif


static const double MaxDouble = 9007199254740991.0;

// Initialization of static class data -----------------------------------
template< class M >
const RWDecimal<M> RWDecimal<M>::null = RWDecimal<M>(RWDecimalBase::nullstate);

template< class M >
const RWDecimal<M> RWDecimal<M>::missing = RWDecimal<M>(RWDecimalBase::missingstate);

template< class M >
const RWDecimal<M> RWDecimal<M>::NaN = RWDecimal<M>(RWDecimalBase::NaNstate);

template< class M >
const RWDecimal<M> RWDecimal<M>::SNaN = RWDecimal<M>(RWDecimalBase::SNaNstate);

template< class M >
const RWDecimal<M> RWDecimal<M>::infinity = RWDecimal<M>(RWDecimalBase::infinitystate);

#if !defined(RW_DISABLE_DEPRECATED)

template< class M >
RWDecimal<M> RWDecimal<M>::nullValue()
{
    static const RWDecimal<M> n = RWDecimal<M>(RWDecimalBase::nullstate);
    return n;
}

template< class M >
RWDecimal<M> RWDecimal<M>::missingValue()
{
    static const RWDecimal<M> n = RWDecimal<M>(RWDecimalBase::missingstate);
    return n;
}

template< class M >
RWDecimal<M> RWDecimal<M>::NaNValue()
{
    static const RWDecimal<M> n = RWDecimal<M>(RWDecimalBase::NaNstate);
    return n;
}

template< class M >
RWDecimal<M> RWDecimal<M>::SNaNValue()
{
    static const RWDecimal<M> n = RWDecimal<M>(RWDecimalBase::SNaNstate);
    return n;
}

template< class M >
RWDecimal<M> RWDecimal<M>::infinityValue()
{
    static const RWDecimal<M> n = RWDecimal<M>(RWDecimalBase::infinitystate);
    return n;
}

#endif

template< class M >
const char* RWDecimal<M>::classname = "RWDecimal";

// Beginning with version 1.15 HP's aCC compiler cannot parse the following
// initializers of static data.  The somewhat ugly workaround is to initialize
// them for each of the template types M supported by the Currency Module. The
// initializations are done in source/currency/decimal.cpp.
#if !defined(RW_NO_STATIC_TEMPLATE_FUNCTION_PTR_INITIALIZER)
template< class M >
void (*RWDecimal<M>::inexactHandler_)(const RWDecimalInexactErr<M>&)
#  ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
;
#  else
    = RWDecimal<M>::defaultInexactHandler;
#  endif

template< class M >
void (*RWDecimal<M>::overflowHandler_)(const RWDecimalOverflowErr<M>&)
#  ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
;
#  else
    = RWDecimal<M>::defaultOverflowHandler;
#  endif
#endif


//------------------------------------------------------------------------
//
// Error handling functions
//------------------------------------------------------------------------

//************************************************************************
//
// Default error handling routines
//
//************************************************************************
template< class M >
void RWDecimal<M>::defaultInexactHandler(const RWDecimalInexactErr<M>& err)
{
    if (err.operation() != RWDecimalBase::div) { // ignore division inexact errs
        std::cerr << err.msg() << std::endl;
    }
    //    RWTHROW(err);  exceptions are for fatal errors
}

template< class M >
void RWDecimal<M>::defaultOverflowHandler(const RWDecimalOverflowErr<M>& err)
{
    rwthrow(err); //RWTHROW(err);
}


//************************************************************************
//
// Short hand for calling error handling routines
//
//************************************************************************
template< class M >
void RWDecimal<M>::overflow(RWDecimalBase::Op op, const RWDecimal<M>& lhs,
                            const RWDecimal<M>& rhs, const RWMessage& msg)
{
    (*overflowHandler_)(RWDecimalOverflowErr<M>(op, lhs, rhs, msg));
}

template< class M >
void RWDecimal<M>::inexact(RWDecimalBase::Op op, const RWDecimal<M>& lhs, const RWDecimal<M>& rhs,
                           const RWMessage& msg)
{
    (*inexactHandler_)(RWDecimalInexactErr<M>(op, lhs, rhs, msg));
}


// Constructors ---------------------------------------------------------

//***********************************************************************
//
// Construct from an RWDecimalPortable.
//
//***********************************************************************
template< class M >
RWDecimal<M>::RWDecimal(const RWDecimalPortable& decport) :
    exponent_(0)
{
    static M ten = M(10);
    switch (decport.state()) {
        case RWDecimalBase::nullstate:
            state_ = nullstate;
            return;
        case RWDecimalBase::NaNstate:
            state_ = NaNstate;
            return;
        case RWDecimalBase::SNaNstate:
            state_ = SNaNstate;
            return;
        case RWDecimalBase::missingstate:
            state_ = missingstate;
            return;
        case RWDecimalBase::infinitystate:
            state_ = infinitystate;
            if (decport < 0) {
                mantissa_ = -1;
            }
            else {
                mantissa_ = 1;
            }
            return;
        case RWDecimalBase::normal:
            break;
        case RWDecimalBase::ctorError:
            break;
    }

    // Get the parts of the number before and after the decimal points
    RWCString before, after;
    before = decport;
    bool negative = (before.firstOf('-') == 0);
    if (negative) {
        before = before(1, before.length() - 1);
    }
    size_t decimalPointIndex = before.index(RWDecimalPortable::decimalSeparator((RWLocaleSnapshot&)RWLocale::global()));
    if (RW_NPOS != decimalPointIndex) {
        after = before(decimalPointIndex + 1, before.length() - decimalPointIndex - 1);
        before = before(0U, decimalPointIndex);
    }

    //Instead of not allowing mantissas that are too big, try creating it
    //and stop when overflow is detected.
    state_ = normal;
    mantissa_ = 0;
    size_t place = 0;
    unsigned int i;
    M tmp;
    // Process digits before the decimal point; too many implies overflow.
    for (i = 0; i < before.length(); ++i) {
        mantissa_ *= ten;
        mantissa_ += (int)(before(i) - '0');
        ++place;
    }

    if (!mantissa_.isGood()) {
        // Signal an overflow condition.
        RWDecimal<M>::overflow(RWDecimalBase::conversion, RWDecimal<M>(RWDecimalBase::nullstate), RWDecimal<M>(RWDecimalBase::nullstate),
                               RWMessage(RWDCML_FROMPORTOVER, classname, before.data(), after.data()));
        state_ = NaNstate;
        return;
    }

    // Process digits after the decimal point; too many implies inexact mantissa.
    for (i = 0; i < after.length(); ++i) {
        tmp  = mantissa_ * ten;
        tmp += (int)(after(i) - '0');
        if (!tmp.isGood()) {
            // Signal an inexact condition.
            inexact(RWDecimalBase::conversion, RWDecimal<M>(RWDecimalBase::nullstate), RWDecimal<M>(RWDecimalBase::nullstate),
                    RWMessage(RWDCML_FROMPORTINEXACT, classname, before.data(), after.data()));
            break;
        }
        mantissa_ = tmp;
        ++place;
    }
    // 'place' is the number of processed digits; some acceptable mantissas
    // can exceed the #digits indicated by decimalPrecision() by 1, plus
    // we may have processed one extra digit to cause an inexact condition.
    RW_POSTCONDITION(place <= M::decimalPrecision() + 2UL);
    if (negative) {
        mantissa_ = -mantissa_;
    }
    // Check this value under several conditions.
    exponent_ = static_cast<int>(place - before.length());
}

//************************************************************************
//
// Construct from a string
//
//************************************************************************
template< class M >
RWDecimal<M>::RWDecimal(const char* numAsString)
    : exponent_(0)
{
    if (numAsString == 0 || *numAsString == '\0') {
        state_ = nullstate;
    }
    else {
        // use the operator<< machinery to extract the number from the string
        // representation.  To ensure that the string contained only the number,
        // and nothing more, ensure that the string state is ok, and that either
        // 1) we are at eof already, or 2) attempting to read another character
        // from the string leaves us at eof.
        std::istringstream stream(numAsString);
        RWDecimal<M> dec;
        stream >> dec;
        char c = ' ';
        while ((RWMNY_STD::isspace)(c) && !stream.bad() && !stream.eof()) {
            // make real sure not at eof by getting a character
            stream.get(c);

            // this better leave us at the end of file
        }
        if (stream.bad() || !stream.eof()) {
            state_ = RWDecimalBase::NaNstate;
        }
        else {
            mantissa_ = dec.mantissa_;
            exponent_ = dec.exponent_;
            state_ = dec.state_;
        }
    }
}


//************************************************************************
//
// Function: decplus
//
// Note: this function was originally named 'plus', but a bug in the MSVC 4.2
// compiler caused this static member function to be placed in the global
// scope, where it conflicted with the C++ Standard Library struct 'plus' defined
// in the include file <functional>.
//
// Why have a "plus" function? why not just put this code in the overloaded
// "+" operator for RWDecimal<M>'s?  As you can see addition with all the
// error checking is rather tedious and all the same stuff has to be done for
// subtraction.  so for subtraction you'd like to be able to use addition: a -
// b -> a + (-b).  But, the error handlers that might be called need to know
// what operation is being performed.  Hence the plus function with the third
// parameter indicating whether addition or subtraction is actually being
// performed.
//
//************************************************************************
template< class M >
RWDecimal<M> RWDecimal<M>::decplus(const RWDecimal<M>& lhs, const RWDecimal<M>& rhs, RWDecimalBase::Op op)
{
    RWDecimalBase::State state = getStatePlus(lhs, rhs);
    if (state != RWDecimalBase::normal && state != RWDecimalBase::infinitystate) {
        return RWDecimal<M>(state);
    }

    // Check for quick return
    if (lhs.state_ == RWDecimalBase::infinitystate) {
        return (lhs);
    }
    if (rhs.state_ == RWDecimalBase::infinitystate) {
        return (rhs);
    }
    if ((rhs.mantissa_ == M::zero() && lhs.mantissa_ != M::zero()) || rhs.state_ == RWDecimalBase::nullstate) {
        return lhs;
    }
    if ((lhs.mantissa_ == M::zero() && rhs.mantissa_ != M::zero()) || lhs.state_ == RWDecimalBase::nullstate) {
        return rhs;
    }

    int diff = lhs.exponent_ - rhs.exponent_;
    if (diff == 0) {
        return addEqualExponents(lhs.mantissa_, rhs.mantissa_, lhs.exponent_, op);
    }
    // use pointers to avoid making copies of the mantissa
    const M* m1, *m2;
    const int* e1, *e2;
    if (diff > 0) {
        m1 = &lhs.mantissa_;
        e1 = &lhs.exponent_;
        m2 = &rhs.mantissa_;
        e2 = &rhs.exponent_;
    }
    else { // diff < 0
        m1 = &rhs.mantissa_;
        e1 = &rhs.exponent_;
        m2 = &lhs.mantissa_;
        e2 = &lhs.exponent_;
        diff = -diff;
    }

    M m2AdjustedMantissa = m2->decimalShiftLeft(static_cast<unsigned>(diff));
    if (m2AdjustedMantissa.isGood()) {
        return addEqualExponents(*m1, m2AdjustedMantissa, *e1, op);
    }

    int overflowFromLeftShift = diff - rwMaxDecimalLeftShift(*m2);
    M m1AdjustedMantissa = m1->decimalShiftRight(static_cast<unsigned>(overflowFromLeftShift));
    m2AdjustedMantissa = m2->decimalShiftLeft(static_cast<unsigned>(*e1 - overflowFromLeftShift - *e2));
    M sumMantissa;

    unsigned numTruncated  = M::preciseAdd(m1AdjustedMantissa, m2AdjustedMantissa, sumMantissa);
    int sumExponent = *e1 - overflowFromLeftShift;

    if (numTruncated != 0) {
        sumExponent -= numTruncated;
        if (sumExponent < 0) {
            RWMsgId msgid = (op == RWDecimalBase::add) ? RWDCML_ADDOVER : RWDCML_SUBOVER;
            RWDecimal<M>::overflow(op, lhs, rhs, RWMessage(msgid, classname));
            return RWDecimal<M>(RWDecimalBase::NaNstate);
        }
    }

    RWMsgId msgid = (op == RWDecimalBase::add) ? RWDCML_ADDINEXACT : RWDCML_SUBINEXACT;
    inexact(op, lhs, rhs, RWMessage(msgid, classname));

    return RWDecimal<M>(sumMantissa, sumExponent);
}


//************************************************************************
//
// static function for shifting into and out of streams
//
//************************************************************************
template< class M >
std::ostream& RWDecimal<M>::shift(std::ostream& strm, const RWDecimal<M>& d)
{
    strm << convertToString(d);
    return strm;
}

template< class M >
std::istream& RWDecimal<M>::shift(std::istream& strm, RWDecimal<M>& d)
{
    RWDecimalPortable p;
    RWDecimalParser parser(&p);
    bool success = parser(strm);
    if ((success && strm.good()) || strm.eof()) {
        d = RWDecimal<M>(p);
    }
    return strm;
}


//************************************************************************
//
// Conversion to an RWDecimalPortable
//
//************************************************************************

template< class M >
RWDecimal<M>::operator RWDecimalPortable() const
{
    return RWDecimalPortable(convertToString(*this).data());
}


//--------------------------------------------------------------------------
//
// Persistence functions
//
//--------------------------------------------------------------------------
template< class M >
void RWDecimal<M>::saveOn(RWvostream& s) const
{
    int stateAsInt = state_;
    s << stateAsInt;
    mantissa_.saveOn(s);
    s << exponent_;
}

template< class M >
void RWDecimal<M>::restoreFrom(RWvistream& s)
{
    int stateAsInt;
    s >> stateAsInt;
    state_ = State(stateAsInt);
    mantissa_.restoreFrom(s);
    s >> exponent_;
}


template< class M >
void RWDecimal<M>::saveOn(RWFile& f) const
{
    int stateAsInt = state_;
    f.Write(stateAsInt);
    mantissa_.saveOn(f);
    f.Write(exponent_);
}

template< class M >
void RWDecimal<M>::restoreFrom(RWFile& f)
{
    int stateAsInt;
    f.Read(stateAsInt);
    state_ = State(stateAsInt);
    mantissa_.restoreFrom(f);
    f.Read(exponent_);
}

//****************************************************
//
// Conversion from double
//
//****************************************************
template< class M >
RWDecimal<M> RWDecimal<M>::from(double m)
{
    if (isnan(m)) {
        return RWDecimal<M>(RWDecimalBase::NaNstate);
    }
    else if (m == std::numeric_limits<double>::infinity()) {
        return RWDecimal<M>(RWDecimalBase::infinitystate);
    }
    else if (m == -(std::numeric_limits<double>::infinity())) {
        RWDecimal<M> retVal(RWDecimalBase::infinitystate);
        return -retVal;
    }

    static const double biggestDiv10 = MaxDouble / 10.0;

    double mantissa = m;
    int exponent = 0;
#if defined(_AIX71)
    double multiplier = 1;
#endif
    while (mantissa != floor(mantissa) && mantissa <= biggestDiv10 && mantissa >= -biggestDiv10) {
        exponent += 1;
#if defined(_AIX71)
        // AIX 7.1 has an implementation of pow() that returns a different value
        // past DBL_DIG that differs from previous AIX and other UNIXs.
        multiplier *= 10.0;
        mantissa = m * multiplier;
#else
        mantissa = m * pow(10.0, exponent);
#endif
    }
    M tmpMantissa = M(mantissa);
    if (!tmpMantissa.isGood()) { // only happens if m > maximum M
        overflow(RWDecimal<M>::conversion, RWDecimal<M>(RWDecimalBase::nullstate), RWDecimal<M>(RWDecimalBase::nullstate),
                 RWMessage(RWDCML_FROMDBLOVER, classname, m));
        return RWDecimal<M>(RWDecimalBase::NaNstate);
    }
    return RWDecimal<M>(tmpMantissa, exponent);
}

template< class M >
RWDecimal<M> RWDecimal<M>::from(long double m)
{
    if (isnan(m)) {
        return RWDecimal<M>(RWDecimalBase::NaNstate);
    }
    else if (m == std::numeric_limits<long double>::infinity()) {
        return RWDecimal<M>(RWDecimalBase::infinitystate);
    }
    else if (m == -(std::numeric_limits<long double>::infinity())) {
        RWDecimal<M> retVal(RWDecimalBase::infinitystate);
        return -retVal;
    }

    static const long double biggestDiv10 = RW_LARGEST_LDOUBLE / 10.0L;
    long double mantissa = m;
    int exponent = 0;
    long double multiplier = 1;
    while (mantissa != floorl(mantissa) && mantissa <= biggestDiv10 && mantissa >= -biggestDiv10) {
        exponent += 1;
        multiplier *= 10.0;
        mantissa = m * multiplier;
    }
    M tmpMantissa = M(mantissa);
    if (!tmpMantissa.isGood()) { // only happens if m > maximum M
        overflow(RWDecimal<M>::conversion, RWDecimal<M>(RWDecimalBase::nullstate), RWDecimal<M>(RWDecimalBase::nullstate),
                 RWMessage(RWDCML_FROMLDBLOVER, classname, m));
        return RWDecimal<M>(RWDecimalBase::NaNstate);
    }
    return RWDecimal<M>(tmpMantissa, exponent);
}

template< class M >
RWCString RWDecimal<M>::opAsString(RWDecimalBase::Op op)
{
    RWCString s;
    switch (op) {
        case RWDecimalBase::assign:
            s = "=";
            break;
        case RWDecimalBase::add:
            s = "+";
            break;
        case RWDecimalBase::sub:
            s = "-";
            break;
        case RWDecimalBase::mult:
            s = "*";
            break;
        case RWDecimalBase::div:
            s = "/";
            break;
        case RWDecimalBase::powop:
            s = "pow";
            break;
        case RWDecimalBase::pow10op:
            s = "pow10";
            break;
        case RWDecimalBase::conversion:
            s = "conversion";
    }
    return s;
}

//######################## Error classes #################################

template< class M >
RWDecimalInexactErr<M>::RWDecimalInexactErr(RWDecimalBase::Op o, const RWDecimal<M>& a, const RWDecimal<M>& b,
        const RWMessage& msg)
    : RWExternalErr(msg),
      op_(o),
      operandA_(a),
      operandB_(b)
{
    ;
}

template< class M >
RWDecimalOverflowErr<M>::RWDecimalOverflowErr(RWDecimalBase::Op o, const RWDecimal<M>& a, const RWDecimal<M>& b,
        const RWMessage& msg)
    : RWExternalErr(msg),
      op_(o),
      operandA_(a),
      operandB_(b)
{
    ;
}


template< class M >
RWCString RWDecimalInexactErr<M>::opString() const
{
    return (RWDecimal<M>::opAsString(operation()));
}


template< class M >
RWCString RWDecimalOverflowErr<M>::opString() const
{
    return (RWDecimal<M>::opAsString(operation()));
}

//------------------------------------------------------------------------
//
//  Static member functions
//
//------------------------------------------------------------------------
template< class M >
RWDecimal<M> RWDecimal<M>::multiply(const RWDecimal<M>& x, const RWDecimal<M>& y)
{
    RWDecimalBase::State state = getStateMultiply(x, y);
    if (state != RWDecimalBase::normal && state != RWDecimalBase::infinitystate) {
        return RWDecimal<M>(state);
    }

    if (x.state_ == RWDecimalBase::nullstate) {
        return RWDecimal<M>(y);
    }

    if (y.state_ == RWDecimalBase::nullstate) {
        return RWDecimal<M>(x);
    }

    if (state == RWDecimalBase::infinitystate) {
        RWDecimal<M> ret(RWDecimalBase::infinitystate);
        if ((x.mantissa_ < M::zero()) != (y.mantissa_ < M::zero())) {
            ret.mantissa_ = -1;
        }
        return ret;
    }

    int e = x.exponent_ + y.exponent_;
    M m;

    unsigned numTruncated = M::preciseMultiply(x.mantissa_, y.mantissa_, m);

    if (numTruncated == 0) {
        return RWDecimal<M>(m, e);
    }

    e -= numTruncated;
    if (e >= 0) {
        inexact(RWDecimalBase::mult, x, y, RWMessage(RWDCML_MULINEXACT, RWDecimal<M>::classname));
        return RWDecimal<M>(m, e);
    }

    RWDecimal<M>::overflow(RWDecimalBase::mult, x, y, RWMessage(RWDCML_MULOVER, RWDecimal<M>::classname));
    return RWDecimal<M>(RWDecimalBase::NaNstate);
}


template< class M >
RWDecimal<M>  RWDecimal<M>::divide(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    RWDecimalBase::State state = getStateDivide(a, b);
    if (state != RWDecimalBase::normal) {
        RWDecimal<M> ret(state);
        if (state == RWDecimalBase::infinitystate &&
                ((a.mantissa_ < M::zero()) != (b.mantissa_ < M::zero()))) {
            ret.mantissa_ = -1;
        }
        return ret;
    }

    if (b.state_ == RWDecimalBase::nullstate) {
        return RWDecimal<M>(a);
    }

    if (b == RWDecimal<M>(0)) {
        if (a == 0) {
            return RWDecimal<M>(RWDecimalBase::NaNstate);
        }
        RWDecimal<M> retVal = RWDecimalBase::infinitystate;
        if (a < 0) {
            retVal.mantissa_ = M(-1);
        }
        return retVal;
    }

    if ((b.state_ == RWDecimalBase::infinitystate) && (a == RWDecimalBase::normal)) {
        return RWDecimal<M>(0);
    }

    M a_pos(a.mantissa_);
    M b_pos(b.mantissa_);
    bool aNeg = (a.mantissa_ < M::zero());
    bool bNeg = (b.mantissa_ < M::zero());
    if (aNeg) {
        a_pos = -a.mantissa_;
    }
    if (bNeg) {
        b_pos = -b.mantissa_;
    }
    bool resultPositive = (aNeg == bNeg);

    M partialQuotient(0);
    M quotient(0);
    M remainder(0);
    bool success = M::longDividePos(a_pos, b_pos, quotient, remainder);

    if (!success) {
        return RWDecimal<M>(RWDecimalBase::NaNstate);
    }

    M shiftedQuotient, temp, tmp_rem, tmp_mant(b_pos);
    int exp = a.exponent_ - b.exponent_;
    unsigned numTruncated;

    while (remainder != M::zero()) {
        // guard against overflow in remainder
        tmp_rem = remainder.decimalShiftLeft();
        if (tmp_rem.isGood()) {
            remainder = tmp_rem;
        }
        else {
            tmp_mant = tmp_mant.decimalShiftRight();
        }
        success = M::longDividePos(remainder, tmp_mant, partialQuotient, remainder);
        if (!success) {
            return RWDecimal<M>(RWDecimalBase::NaNstate);
        }

        if (quotient == M::zero()) {
            quotient = partialQuotient;
        }
        else {
            shiftedQuotient = quotient.decimalShiftLeft();
            if (!shiftedQuotient.isGood()) {
                break;
            }
            numTruncated = M::preciseAdd(partialQuotient, shiftedQuotient, temp);
            if (numTruncated > 0) {
                break;
            }
            quotient = temp;
        }
        ++exp;
    }
    if (exp < 0) {
        quotient = quotient.decimalShiftLeft(static_cast<unsigned>(RWMNY_STD::abs(exp)));

        if (!quotient.isGood()) {
            RWDecimal<M>::overflow(RWDecimal<M>::div, a, b, RWMessage(RWDCML_DIVOVER, RWDecimal<M>::classname));
            return RWDecimal<M>(RWDecimalBase::NaNstate);
        }
        exp = 0;
    }
    if (remainder != M::zero()) {
        RWDecimal<M>::inexact(RWDecimal<M>::div, a, b, RWMessage(RWDCML_DIVINEXACT, RWDecimal<M>::classname));
    }
    return resultPositive ? RWDecimal<M>(quotient, exp) : -(RWDecimal<M>(quotient, exp));
}

//------------------------------------------------------------------------
//
// Comparison Operators
//
// Note that since RWDecimals are not normalized, numbers do not have a
// unique representation.  e.g. 2 may be represented as mantissa = 2,
// exponent = 0, or, mantissa = 20, exponent = 1, or, mantissa = 200,
// exponent = 2, and so forth.  Thus we must attempt to adjust exponents
// when doing comparisons.
//------------------------------------------------------------------------

//****************************************************
//
//  Equal static member function
//
//****************************************************

template< class M >
bool RWDecimal<M>::equal(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    if (a.state_ || b.state_) {
        if ((a.state_ == RWDecimalBase::infinitystate) && (b.state_ == RWDecimalBase::infinitystate)) {
            return ((a.mantissa_ < M::zero()) == (b.mantissa_ < M::zero()));
        }
        return (a.state_ == b.state_);
    }

    int exponentDiff = a.exponent_ - b.exponent_;
    if (exponentDiff == 0) {
        return (a.mantissa_ == b.mantissa_);
    }


    if (exponentDiff > 0) {
        M tmp = b.mantissa_ == M::zero() ? M::zero() : b.mantissa_.decimalShiftLeft(unsigned(exponentDiff));
        if (!tmp.isGood()) {
            return false;
        }
        return (a.mantissa_ == tmp);
    }

    M tmp = a.mantissa_ == M::zero() ? M::zero() : a.mantissa_.decimalShiftLeft(unsigned(-exponentDiff));
    if (!tmp.isGood()) {
        return false;
    }
    return (tmp == b.mantissa_);
}


//****************************************************
//
//  static Less than function
//
//****************************************************
template< class M >
bool RWDecimal<M>::lessThan(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    if (a.state_ || b.state_) {
        if ((a.state_ == RWDecimalBase::infinitystate) &&
                ((b.state_ == RWDecimalBase::infinitystate) || !b.state_)) {
            if (a.mantissa_ < M::zero() && (b.mantissa_ >= M::zero() || !b.state_)) {
                return true;
            }
        }
        if (!a.state_ && b.state_ == RWDecimalBase::infinitystate &&
                b.mantissa_ >= M::zero()) {
            return true;
        }
        return false;
    }

    int exponentDiff = a.exponent_ - b.exponent_;

    if (exponentDiff == 0) {
        return (a.mantissa_ < b.mantissa_);
    }

    if (exponentDiff > 0) {
        M tmp = b.mantissa_ == M::zero() ? M::zero() : b.mantissa_.decimalShiftLeft(unsigned(exponentDiff));

        // if b != 0 and b overflows with an equal exponent then abs(b) > a
        if (!tmp.isGood()) {
            return (b.mantissa_ > M::zero());
        }
        return (a.mantissa_ < tmp);
    }

    M tmp = a.mantissa_ == M::zero() ? M::zero() : a.mantissa_.decimalShiftLeft(unsigned(-exponentDiff));

    // if a != 0 and a overflows with an equal exponent them abs(a) > b
    if (!tmp.isGood()) {
        return (a.mantissa_ < M::zero());
    }
    return (tmp < b.mantissa_);
}


//****************************************************
//
// static power function
//
// Uses the "binary" method for exponentiation.  See
// "The Art of Computer Programming Vol. 2, Seminumerical
// Algorithms" by Donald Knuth.  Section 4.6.3
//
//***************************************************
template< class M >
RWDecimal<M> RWDecimal<M>::power(const RWDecimal<M>& base, int exponent)
{
    if (exponent == 0) {
        return RWDecimal<M>(1);
    }
    if (exponent < 0) {
        RWDecimal<M> one(1);

        RWDecimal<M> a = one / pow(base, -exponent);
        return (a);
    }

    RWDecimal<M> product(1);
    RWDecimal<M> z = base;
    unsigned exponentBits = static_cast<unsigned>(exponent);
    bool odd;

    for (; ;) {
        // For the purposes of this algorithm zero is odd
        odd = (exponentBits == 0 ? true : (exponentBits & 1));
        exponentBits >>= 1;
        if (odd) {
            product = z * product;
            if (exponentBits == 0) {
                break;
            }
        }
        z = z * z;
    }

    return product;
}


//****************************************************
//
// static absolute value function
//
//***************************************************
template< class M >
RWDecimal<M> RWDecimal<M>::absoluteValue(const RWDecimal<M>& x)
{
    if ((!x.state_ || x.state_ == RWDecimalBase::infinitystate) && x.mantissa_ < M::zero()) {
        return RWDecimal<M>(-x.mantissa_, x.exponent_, x.state_);
    }
    else if (x.state_ == RWDecimalBase::SNaNstate) {
        return RWDecimal<M>(RWDecimalBase::NaNstate);
    }
    return RWDecimal<M>(x);
}


//***************************************************
//
// static round function
//
//***************************************************
template< class M >
RWDecimal<M> RWDecimal<M>::roundDecimal(const RWDecimal<M>& d, int exponent, RWDecimalBase::RoundingMethod method,
                                        int roundDigit)
{
    if (!d.isNumber()) {
        return d;
    }

    int exponentDiff = d.exponent_ - exponent;
    if (exponentDiff <= 0) {
        return d; // We're done.  No need to round.
    }

    M one(1);
    M mantissa = d.mantissa_;

    bool negative = false;
    if (mantissa < M::zero()) { // Convert negatives to positive, change back later
        mantissa = -mantissa;
        negative = true;
    }

    M quotient(0);
    if (exponentDiff - d.maxDigits() > 1) { // Result must be zero...
        if ((method == RWDecimalBase::UP) && (mantissa != M::zero())) {   //...unless...
            quotient = one;    // ...we're rounding UP with a non-zero mantissa.
        }
    }
    else { // Rounding away at most maxDigits() + 1 digits
        M remainder(0);
        if (exponentDiff > d.maxDigits()) { // exponentDiff must be maxDigits() + 1
            quotient = M::zero();
            remainder = mantissa;
        }
        else { // divide mantissa by 10^exponentDiff to get quotient & remainder
            M divisor(10);
            divisor = divisor.decimalShiftLeft(static_cast<unsigned>(exponentDiff - 1));
            M::longDivide(mantissa, divisor, quotient, remainder);
        }

        // discriminator is the decision digit, remainder's most-significant digit
        M discriminator(remainder.decimalShiftRight(static_cast<unsigned>(exponentDiff - 1)));
        M split(roundDigit), tie(5);

        switch (method) {
            case RWDecimalBase::UP: // Round up unless remainder is zero
                if (remainder != M::zero()) {
                    quotient += one;
                }
                break;

            case RWDecimalBase::PLAIN: // Round up if greater than the split
                if (discriminator > split) {
                    quotient += one;
                }
                break;

            case RWDecimalBase::BANKERS: // Round up to an even number on a tie
                if (discriminator >  tie) {
                    quotient += one;
                }
                else if (discriminator == tie) {
                    if (remainder == discriminator.decimalShiftLeft(static_cast<unsigned>(exponentDiff - 1))) {
                        remainder = discriminator;    // Strip trailing zeros from remainder
                    }

                    if (remainder > tie) {
                        quotient += one;
                    }
                    else if ((remainder == tie) && (!quotient.isEven())) {
                        quotient += one;
                    }
                }
                break;

            default: ; // Truncate.
        } // switch
    } // if( exponentDiff - d.maxDigits() > 1 )

    if (exponent < 0) {
        quotient = quotient * one.decimalShiftLeft(static_cast<unsigned>(-exponent));
        exponent = 0;
    }

    if (negative) { // ...restore the sign
        quotient = -quotient;
    }

    return RWDecimal<M>(quotient, exponent);
}


//**************************************************
//
// static convertToString function
//
//**************************************************
template< class M >
RWCString  RWDecimal<M>::convertToString(const RWDecimal<M>& d)
{
    switch (d.state_) {
        case RWDecimalBase::normal:
            break;
        case RWDecimalBase::NaNstate:
            return RWCString("(NaN)", 5);
        case RWDecimalBase::SNaNstate:
            return RWCString("(SNaN)", 6);
        case RWDecimalBase::nullstate:
            return RWCString("(null)", 6);
        case RWDecimalBase::missingstate:
            return RWCString("(missing)", 9);
        case RWDecimalBase::ctorError:
            return RWCString("(ctorError)", 11);
        case RWDecimalBase::infinitystate:
            if (d.mantissa_ < M::zero()) {
                return RWCString("(-infinity)", 11);
            }
            return RWCString("(infinity)", 10);
        default:
            return RWCString("(Impossible value)", 18);
    }

    RWCString decSep = RWDecimalPortable::decimalSeparator(RWLocale::global());
    RWCString locNegSign = RWLocale::global().negative_sign();
    char negSign;
    if (!locNegSign.isNull()) {
        negSign = locNegSign(0);
    }
    else {
        negSign = '-';
    }

    bool negative = false;
    std::ostringstream o;  // Format the mantissa into a string
    o << d.RWDecimal<M>::mantissa_;
    RWCString man(o.str().c_str());

    // If negative, remove the minus sign for now and put it back at the end.
    // Really, it makes life a whole lot easier.
    if (man(0UL) == negSign) {
        negative = true;
        man.remove(0UL, 1UL);
    }

    while ((size_t)d.exponent_ > man.length()) { // Add leading zeros if necessary
        man.prepend("0");
    }

    RWCString string;   // create string representation

    // extract piece after the decimal point
    if (d.exponent_ > 0) {
        string.append(decSep);
        string.append(man(man.length() - d.exponent_, static_cast<unsigned>(d.exponent_)));
    }

    // extract piece before the decimal point
    if ((size_t)d.exponent_ < man.length()) {
        string.prepend(man(0, man.length() - d.exponent_));
    }
    else {
        string.prepend("0");
    }

    if (negative) {
        string.prepend(negSign);
    }

    return string;
}


//**************************************************
//
// convertToDouble function
//
//**************************************************
template< class M >
long double RWDecimal<M>::convertToDouble(const RWDecimal<M>& x)
{
    if (x.state_) {
        long double retVal = 0;
        stateConvert(x.state_, retVal);
        if (x.state_ == RWDecimalBase::infinitystate && x.mantissa_ < M::zero()) {
            retVal = -retVal;
        }
        return retVal;
    }
    double mant = x.mantissa_.asDouble();
#if defined(_AIX71)
    // AIX 7.1 has an implementation of pow() that returns a different value
    // past DBL_DIG that differs from previous AIX and other UNIXs.
    double divisor = 1.0;
    for (unsigned i = 0; i < (unsigned)x.exponent_; ++i) {
        divisor *= 10.0;
    }
#else
    double divisor = pow(10.0, (double)x.exponent_);
#endif
    return (long double)(mant / divisor);
}


//**************************************************
//
// convertToInt function
//
//**************************************************
template< class M >
long int RWDecimal<M>::convertToInt(const RWDecimal<M>& x, RWDecimalBase::RoundingMethod method)
{
    if (x.state_) {
        return 0;
    }
    const RWDecimal<M> rounded = round(x, 0, method);
    return (long int)toDouble(rounded);
}

#if defined(_WIN32)
#  undef isnan
#endif

#endif // RW_CURRENCY_DECIMAL_CC
