#ifndef RW_CURRENCY_DECIMAL_H
#define RW_CURRENCY_DECIMAL_H

/*-------------------------------------------------------------------------
 *
 * Definition of RWDecimal and related classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/decimal.h#1 $
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
 *-------------------------------------------------------------------------
 */

/*
 * The RWDecimalPortable class is declared via #define in decport.h rather than
 * using a forward declaration so that you can convert from one decimal type
 * to another simply by including the two types of interest.  Otherwise, you'd
 * have to include decport.h explicitly in user programs in order to do the
 * conversion, and this didn't seem like a good idea.  (conversion from type X
 * to Y happens by first converting X to RWDecimalPortable using operator
 * RWDecimalPortable and then constructing a Y from that).
 *
 * Copy constructors and assignment operators aren't explicitly provided; we
 * count on the compiler to synthesize them for us.  (except for op= for the
 * fixed classes, since this has special semantics).
 *
 */

/* for backward compatibility */
#ifndef RW_MONEY_DECIMAL_H
#  define RW_MONEY_DECIMAL_H
#endif

#include <rw/currency/decdefs.h>     /* See note in top of file comments */
#include <rw/currency/mp1int.h>
#include <rw/currency/mp2int.h>
#include <rw/currency/mp3int.h>
#include <rw/currency/mpint.h>
#include <rw/dcmldefs.h>
#include <rw/dcmlerr.h>
#include <rw/cstring.h>
#include <rw/decbase.h>
#include <rw/decport.h>
#include <rw/rwfile.h>
#include <rw/vstream.h>
#include <iosfwd>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <math.h>
#else
#  include <cmath>
#endif

template< class M >
class RWDecimalInexactErr;

template< class M >
class RWDecimalOverflowErr;


/**
 * \ingroup currency_decimal_numbers_group
 *
 * \brief
 * Exactly represents a decimal fraction.
 *
 * RWDecimal instances are exact representations of decimal fractions. They
 * behave very similarly to the built-in floating point types, \c float and
 * \c double. However, because the built-in types use base 2, they cannot
 * store decimal fractions exactly, resulting in rounding errors and a loss
 * of precision. Since the RWDecimal classes use base 10, they can do
 * decimal math exactly.
 *
 * RWDecimal is templatized. Three short type names are provided:
 * \ref RWDecimal "RWDecimal<RWMP1Int>",
 * \ref RWDecimal "RWDecimal<RWMP2Int>", and
 * \ref RWDecimal "RWDecimal<RWMP3Int>". Each type provides a different
 * amount of precision, as described below in the Limits section. The
 * trade-off is simple: the more precision, the slower the class.
 *
 * You may also write your own RWDecimal class. Throughout this section,
 * when we refer to the RWDecimal class, you can assume that it applies to
 * any of the three provided classes, or to one you have defined.
 *
 * \synopsis
 * #include <rw/currency/decimal.h>    // For RWDecimal<T>
 * #include <rw/currency/mp2int.h>     // For RWMP2Int
 *
 * RWDecimal<RWMP2Int> x = "0.01";
 * cout << "one dollar: " << 100*x << endl;
 * \endsynopsis
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/currency/decimal.h>
 * #include <rw/currency/mp2int.h>
 *
 * int main()
 * {
 *  RWDecimal<RWMP2Int> penny = "0.01";
 *  RWDecimal<RWMP2Int> bank = 0;
 *  for(int i=100; i--;) bank+=penny;  // deposit 100 pennies
 *  bank -= 1;        // withdraw a buck
 *  std::cout << (bank==0 ? "broke!" : "whew! still solvent") << std::endl;
 *  return 0;
 * }
 * \endcode
 * \endexample
 *
 * <h4>Limits</h4>
 * Class RWDecimal provides three static member functions that can be used
 * to define the limits on an RWDecimal object. These functions return the
 * precision, maximum value, and minimum value of a number:
 *
 * \code
 * int RWDecimal<T>::maxDigits(); // indicates precision
 * RWDecimal<T> RWDecimal<T>::maxValue(); // indicates maximum value
 * RWDecimal<T> RWDecimal<T>::minValue(); // indicates minimum value
 * \endcode
 *
 * \note
 * The precision returned by maxDigits() does not usually represent the
 * number of digits in the maximum value of an RWDecimal object. Rather, it
 * indicates the largest number of digits that will always be supported by
 * that object without returning an overflow error. For example, Table 1
 * indicates that the maximum value for \ref RWDecimal "RWDecimal<RWMP2Int>"
 * has 19 digits. Notice, however, that larger 19-digit numbers will cause
 * an overflow error because they exceed the maximum value. Therefore,
 * RWDecimal<RWMP2Int>::maxDigits() returns 18, because that is the number
 * of digits that will always be supported without an overflow error.
 *
 * The following code snippets demonstrate when an overflow condition caused
 * by exceeding a maximum value will occur:
 *
 * \code
 * // Set max to maximum value:
 * RWDecimal<RWMP1Int>max = RWDecimal<RWMP1Int>::maxValue();
 *
 * // Add 1 to max to generate an overflow error:
 * RWDecimal<RWMP1Int>tooBig = max + RWDecimal<RWMP1Int>(1);
 *
 * // Set min to minimum value:
 * RWDecimal<RWMP1Int>min = RWDecimal<RWMP1Int>::minValue();
 *
 * // Subtract 1 from min to generate an overflow error:
 * RWDecimal<RWMP1Int>tooSmall = min - RWDecimal<RWMP1Int>(1);
 * \endcode
 *
 * Table 1 indicates the minimum and maximum values for RWDecimal when \c T
 * is replaced by one of the provided multi-precision integer types:
 * <table>
 * <caption align="top">Table 1: Max/Min Value and Digits for RWDecimal
 * </caption>
 * <tr>
 * <th rowspan="2">Class</th>
 * <th>Minimum value</th>
 * <th rowspan="2">Max Digits</th>
 * </tr>
 * <tr>
 * <th>Maximum value</th>
 * </tr>
 * <tr>
 * <td rowspan="2" valign="top">\ref RWDecimal "RWDecimal<RWMP3Int>"</td>
 * <td>-39614081257132168796771975167</td>
 * <td rowspan="2" valign="top">28</td>
 * </tr>
 * <tr>
 * <td>39614081257132168796771975167</td>
 * </tr>
 * <tr>
 * <td rowspan="2" valign="top">\ref RWDecimal "RWDecimal<RWMP2Int>"</td>
 * <td>-9223372036854775807</td>
 * <td rowspan="2" valign="top">18</td>
 * </tr>
 * <tr>
 * <td>9223372036854775807</td>
 * </tr>
 * <tr>
 * <td rowspan="2" valign="top">\ref RWDecimal "RWDecimal<RWMP1Int>"</td>
 * <td>-9007199254740991</td>
 * <td rowspan="2" valign="top">15</td>
 * </tr>
 * <tr>
 * <td>9007199254740991</td>
 * </tr>
 * </table>
 *
 * <h4>Non-Numeric Values</h4>
 * As well as representing a decimal fraction, an RWDecimal can also
 * represent one of several non-numeric values. This concept has several
 * uses, including, for example, representing a null entry from a database
 * or indicating a missing value in data, which is to be subjected to a
 * statistical analysis. Currency Module supports five types of non-numeric
 * values: #null, #missing, #NaN (not a number), #SNaN (signaling NaN), and
 * #infinity. The #SNaN value behaves as a #NaN value for all operations
 * except toDouble(). The #missing, and #NaN values propagate while #null
 * values do not. This means that arithmetic operations performed using a
 * #missing or an #NaN result in a #missing or an #NaN value, whereas
 * arithmetic operations performed with a #null operand return either a
 * valid number or an #NaN. Operations performed on #infinity follow
 * specific rules detailed in RWDecimalBase::State, and may return
 * #infinity, #NaN, or zero. Details are given below.
 *
 * The special static constants RWDecimal::missing, RWDecimal::null,
 * RWDecimal::NaN, RWDecimal::SNaN, and RWDecimal::infinity are the
 * prototype #missing, #null, #NaN, #SNaN and #infinity values. To set up a
 * non-numeric RWDecimal, use these static variables along with either the
 * copy constructor or assignment operator. To test for a non-numeric value,
 * use these values along with an equality operator. You can use the member
 * function isNumber() to test if an RWDecimal has a numeric value.
 *
 * <h4>Arithmetic</h4>
 * For the most part, arithmetic between RWDecimal objects is defined very
 * simply: you get back an exact representation of the result of the
 * operation. However, there are several special cases:
 * - <b>Loss of precision.</b> If the result cannot be exactly represented
 * as an RWDecimal object because it has too many significant digits, the
 * result is set to an approximation of the true result, and the
 * precisionLoss error handler is called with an RWDecimalInexactErr object.
 *
 * - <b>Overflow/underflow:</b> If the magnitude of the result exceeds the
 * range of RWDecimal, then the overflow error handler is called with an
 * RWDecimalOverflowErr object.
 *
 * - <b>Operand of #missing:</b> If one of the operands is a #missing value,
 * then the result of the arithmetic operation is also a #missing value.
 *
 * - <b>Operand of #null:</b> If both operands are #null, the result is also
 * #null. In addition and subtraction, a #null value behaves as if it were
 * zero. In multiplication, a #null behaves like a one. Dividing by a #null
 * value returns the numerator, thus here a #null behaves like one. Using a
 * #null as the numerator in a division returns an #NaN.
 *
 * - <b>Operand of #NaN or #SNaN:</b> If one or both of the operands is a
 * #NaN or #SNaN, the result of the arithmetic operation will be #NaN.
 *
 * - <b>Operand of #infinity:</b> Refer to the table defined in
 * RWDecimalBase::State.
 */
template< class M >
class RWDecimal : public RWDecimalBase
{
public:
    typedef RWDecimalInexactErr<M> RWDecimalInexactErrType;
    typedef RWDecimalOverflowErr<M> RWDecimalOverflowErrType;

    /**
     * Specifies the non-numeric value \c null. Use this static instance to
     * test or to set its value on an RWDecimal.
     */
    static const RWDecimal<M> null;
    /**
     * Specifies the non-numeric value \c missing. Use this static instance
     * to test or to set its value on an RWDecimal.
     */
    static const RWDecimal<M> missing;
    /**
     * Specifies the non-numeric value \c NaN. Use this static instance to
     * test or to set its value on an RWDecimal.
     */
    static const RWDecimal<M> NaN;
    /**
     * Specifies the non-numeric value \c SNaN. Use this static instance to
     * test or to set its value on an RWDecimal.
     */
    static const RWDecimal<M> SNaN;
    /**
     * Specifies the non-numeric value \c infinity. Use this static instance
     * to test or to set its value on an RWDecimal.
     */
    static const RWDecimal<M> infinity;

#if !defined(RW_DISABLE_DEPRECATED)

    /**
     * \deprecated
     * As of SourcePro 13, use RWDecimal<M>::null.
     *
     * Specifies the non-numeric value \c null. Use this function to test or
     * to set its value on an RWDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWDecimal<M>::null instead") static RWDecimal<M> nullValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWDecimal<M>::missing.
     *
     * Specifies the non-numeric value \c missing. Use this function to test
     * or to set its value on an RWDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWDecimal<M>::missing instead") static RWDecimal<M> missingValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWDecimal<M>::NaN.
     *
     * Specifies the non-numeric value \c NaN. Use this function to test or
     * to set its value on an RWDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWDecimal<M>::NaN instead") static RWDecimal<M> NaNValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWDecimal<M>::SNaN.
     *
     * Specifies the non-numeric value \c SNaN. Use this function to test or
     * to set its value on an RWDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWDecimal<M>::SNaN instead") static RWDecimal<M> SNaNValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWDecimal<M>::infinity.
     *
     * Specifies the non-numeric value \c infinity. Use this function to
     * test or to set its value on an RWDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWDecimal<M>::infinity instead") static RWDecimal<M> infinityValue();

#endif

    //  Public constructors----------------------------------------------------

    /**
     * Constructs an RWDecimal with a value of #null.
     */
    RWDecimal(): RWDecimalBase(), exponent_(0)
    {
        state_ = nullstate;
    }

    /**
     * Copy constructor. Constructs an RWDecimal that is a copy of the
     * argument.
     */
    RWDecimal(const RWDecimal<M>& d): RWDecimalBase()
    {
        mantissa_ = d.mantissa_;
        exponent_ = d.exponent_;
        state_ = d.state_;
    }


    /**
     * Constructs an RWDecimal representation of the argument. This
     * constructor is most often used implicitly to provide type conversion
     * from one RWDecimal type to another using an RWDecimalPortable object
     * as an intermediate representation.
     */
    RWDecimal(const RWDecimalPortable&);

    /**
     * Conversion to a portable decimal object. This is most often used
     * implicitly to interface with a facility such as I/O or type
     * conversion.
     */
    operator RWDecimalPortable() const;

    /**
     * Constructs an RWDecimal with value \a i. The explicit integer
     * constructors prevent initializations from 0 from being ambiguous.
     * Without the \c int constructor, the compiler would not know whether
     * to convert 0 to a \c const \c char* or a \c long \c int.
     */
    RWDecimal(int i): exponent_(0), mantissa_(M(i))
    {
        state_ = normal;
    }

    /**
     * Constructs an RWDecimal with value \a i. The explicit integer
     * constructors prevent initializations from 0 from being ambiguous.
     * Without the \c int constructor, the compiler would not know whether
     * to convert 0 to a \c const \c char* or a \c long \c int.
     */
    RWDecimal(long int i): exponent_(0), mantissa_(M(i))
    {
        state_ = normal;
    }

    /**
     * Constructs an RWDecimal with value <tt>\a m * 10-\a e</tt>, so that
     * \a e represents the number of digits after the decimal point.
     */
    RWDecimal(int m, int e): exponent_(e), mantissa_(M(m))
    {
        RW_PRECONDITION(exponent_ >= 0);
        state_ = normal;
    }

    /**
     * Constructs an RWDecimal with value <tt>\a m * 10-\a e</tt>, so that
     * \a e represents the number of digits after the decimal point.
     */
    RWDecimal(long int m, int e): exponent_(e), mantissa_(M(m))
    {
        RW_PRECONDITION(exponent_ >= 0);
        state_ = normal;
    }


    /**
     * Constructs an RWDecimal from the null-terminated character string
     * \a str. Since we write numbers using base 10, and the RWDecimal class
     * stores numbers using base 10, the number constructed is an exact
     * representation of the string. If the string cannot be successfully
     * parsed as a number, the RWDecimal is initialized to #null. If the
     * number in the string cannot be exactly represented (for example, it
     * has too many significant digits) then the appropriate error handler
     * (either the inexact or overflow handler) is called. The string may
     * contain embedded commas to separate groups of digits and may have a
     * leading dollar sign. Negatives can be indicated with a negative sign
     * or by using parentheses. A technical description of the exact input
     * grammar allowed is given in the section "Technical Notes" of the
     * <em>Currency Module User's Guide</em>.
     */
    RWDecimal(const char* str);


    // Error handlers----------------------------------------------------------
    // These allow you to specify resumptive exceptions.

    /**
     * Sets the function that is called when an "inexact" error occurs. This
     * type of error most often indicates the use of an arithmetic operation
     * that will cause loss of precision in the result.
     * \c defaultInexactHandler, the default error handler, prints an error
     * message, but does not throw an exception.
     */
    static void setInexactHandler(void (*eh)(const RWDecimalInexactErr<M>&))
    {
        inexactHandler_ = eh;
    }

    /**
     * Sets the function that is called when an "overflow" error occurs.
     * This type of error most often indicates the use of an arithmetic
     * operation that will cause a result larger than can be stored. The
     * default error handler, \c defaultOverflowHandler, simply throws the
     * error object as a C++ exception.
     */
    static void setOverflowHandler(void (*eh)(const RWDecimalOverflowErr<M>&))
    {
        overflowHandler_ = eh;
    }
    static void defaultInexactHandler(const RWDecimalInexactErr<M>& err);
    static void defaultOverflowHandler(const RWDecimalOverflowErr<M>& err);

    static RWCString opAsString(RWDecimalBase::Op op);

    /**
     * Returns the result of applying the unary operator.
     */
    RWDecimal<M> operator-() const
    {
        if (state_ == RWDecimalBase::SNaNstate) {
            return RWDecimal<M>(RWDecimalBase::NaNstate);
        }
        return (RWDecimal<M>(-mantissa_, exponent_, state_));
    }

    /**
     * Returns the result of applying the unary operator.
     */
    RWDecimal<M> operator+() const
    {
        if (state_ == RWDecimalBase::SNaNstate) {
            return RWDecimal<M>(RWDecimalBase::NaNstate);
        }
        return (RWDecimal<M>(mantissa_, exponent_, state_));
    }

    // Arithmetic assignment operators
    /**
     * Sets the value of self equal to the value of the argument.
     */
    RWDecimal<M>& operator=(const RWDecimal<M>& a)
    {
        state_ = a.state_;
        mantissa_ = a.mantissa_;
        exponent_ = a.exponent_;

        return *this;
    }

    /**
     * Performs the operation between self and the argument, and then stores
     * the results in self. If the resulting operation causes loss of
     * precision or overflow in the result, the appropriate error handler
     * will be called before the function returns.
     */
    RWDecimal<M>& operator+=(const RWDecimal<M>& a)
    {
        RWDecimal<M> sum = *this + a;
        return (*this = sum);
    }

    /**
     * \copydoc operator+=(const RWDecimal<M>& a)
     */
    RWDecimal<M>& operator-=(const RWDecimal<M>& a)
    {
        RWDecimal<M> diff = *this - a;
        return (*this = diff);
    }

    /**
     * \copydoc operator+=(const RWDecimal<M>& a)
     */
    RWDecimal<M>& operator*=(const RWDecimal<M>& a)
    {
        RWDecimal<M> prod = *this * a;
        return (*this = prod);
    }

    /**
     * \copydoc operator+=(const RWDecimal<M>& a)
     */
    RWDecimal<M>& operator/=(const RWDecimal<M>& a)
    {
        RWDecimal<M> result = *this / a;
        return (*this = result);
    }

    // Persistence ------------------------------------------------------------
    /**
     * Stores value of self to a virtual stream. The virtual stream class is
     * provided with Rogue Wave's Essential Tools Module class library. This
     * function requires that you link in the Essential Tools Module
     * library.
     */
    void saveOn(RWvostream&) const;

    /**
     * Restores value of self from a virtual stream. The virtual stream
     * class is provided with Rogue Wave's Essential Tools Module class
     * library. This function requires that you link in the Essential Tools
     * Module library.
     */
    void restoreFrom(RWvistream&);

    /**
     * Stores value of self to an RWFile in binary format. The RWFile class
     * is provided with Rogue Wave's Essential Tools Module class library.
     * This function requires that you link in the Essential Tools Module
     * library.
     */
    void saveOn(RWFile&) const;

    /**
     * Restores value of self from an RWFile. The RWFile class is provided
     * with Rogue Wave's Essential Tools Module class library. This function
     * requires that you link in the Essential Tools Module library.
     */
    void restoreFrom(RWFile&);

    // Utility functions ------------------------------------------------------

    /**
     * Returns the maximum number of digits that an RWDecimal of the
     * indicated type is <em>guaranteed</em> to represent without overflow.
     * In most cases, an RWDecimal can represent some numbers of length
     * \c actualDigits, where <tt>actualDigits=</tt>maxDigits()
     * <tt>+ 1</tt>. For example, the maxDigits() value for class RWDecimal
     * is 18, even though the number of digits in the maxValue() for the
     * class is 19.
     */
    static int maxDigits()
    {
        return M::decimalPrecision();
    }

    /**
     * Returns the maximum value that can be represented by this class. The
     * maximum value +1 will always generate an overflow error.
     */
    static RWDecimal<M> maxValue()
    {
        return RWDecimal<M>(M::maxValue(), 0);
    }

    /**
     * Returns the minimum value that can be represented by this class. The
     * minimum value -1 will always generate an overflow error.
     */
    static RWDecimal<M> minValue()
    {
        return RWDecimal<M>(M::minValue(), 0);
    }

    /**
     * Returns \c true if self represents a decimal fraction; returns
     * \c false if self is not a representation of a number; for example, if
     * self is a #null or #missing value.
     */
    int isNumber() const
    {
        return (state_ == normal);
    }

    /**
     * Returns the number of digits to the right of the decimal point.
     */
    int decimalPlaces() const
    {
        return (state_ == normal ? exponent_ : 0);
    }


    // Narrowing conversion functions -----------------------------------------

    /**
     * Converts a floating point value to an RWDecimal. Results may be
     * inexact.
     */
    static RWDecimal<M>  from(double);

    /**
     * Converts a floating point value to an RWDecimal. Results may be
     * inexact.
     */
    static RWDecimal<M>  from(long double);

    static RWDecimal<M> multiply(const RWDecimal<M>& a, const RWDecimal<M>& b);
    static RWDecimal<M> divide(const RWDecimal<M>& a, const RWDecimal<M>& b);
    static bool    equal(const RWDecimal<M>& a, const RWDecimal<M>& b);
    static bool    lessThan(const RWDecimal<M>& a, const RWDecimal<M>& b);
    static std::istream&     shift(std::istream&, RWDecimal<M>&);
    static std::ostream&     shift(std::ostream&, const RWDecimal<M>&);
    static RWDecimal<M> power(const RWDecimal<M>&, int);
    static RWDecimal<M> absoluteValue(const RWDecimal<M>&);
    static RWDecimal<M> roundDecimal(const RWDecimal<M>&, int, RWDecimalBase::RoundingMethod, int roundDigit = 5);
    static RWCString    convertToString(const RWDecimal<M>&);
    static long double  convertToDouble(const RWDecimal<M>&);
    static long int     convertToInt(const RWDecimal<M>& d, RWDecimalBase::RoundingMethod);

protected:
    //State state_;    from RWDecimalBase
    int   exponent_;
    M     mantissa_;

    // HP aCC gives ugly warnings if classname is declared to be a char*; when
    // doing the initialization it complains that assigning a literal string constant to
    // a char* is deprecated and may not be supported in the future.
    // Sunpro, OTOH, complains that classname is an undefined symbol at link
    // if you DON'T declare it to be a char*.
#if defined(__hppa)
    static const char  classname[];
#else
    static const char* classname;
#endif

    static void (*overflowHandler_)(const RWDecimalOverflowErr<M>&);
    static void (*inexactHandler_)(const RWDecimalInexactErr<M>&);


    // Protected constructors -------------------------------------------------

    RWDecimal(State s)
        : exponent_(0)
    {
        state_ = s;
        if (s == RWDecimalBase::infinitystate) {
            mantissa_ = M(1);
        }
    }

    // Specify the pieces explicitly
    RWDecimal(const M& m, int e, State s = RWDecimalBase::normal)
        : exponent_(e), mantissa_(m)
    {
        RW_PRECONDITION(exponent_ >= 0);
        RW_PRECONDITION((s != infinitystate || mantissa_ != M::zero()));
        state_ = s;
    }


    // Protected utility functions --------------------------------------------
    static void   overflow(Op oper, const RWDecimal<M>& a, const RWDecimal<M>& b, const RWMessage& msg);
    static void   inexact(Op oper, const RWDecimal<M>& a, const RWDecimal<M>& b, const RWMessage& msg);

    static inline RWDecimalBase::State getStatePlus(const RWDecimal<M>& a, const RWDecimal<M>& b);
    static inline RWDecimalBase::State getStateDivide(const RWDecimal<M>& a, const RWDecimal<M>& b);
    static inline RWDecimalBase::State getStateMultiply(const RWDecimal<M>& a, const RWDecimal<M>& b);
    static inline RWDecimal<M> addEqualExponents(const M& lhs, const M& rhs, int exp, RWDecimalBase::Op op);
public:
    static RWDecimal<M> decplus(const RWDecimal<M>& lhs, const RWDecimal<M>& rhs, RWDecimalBase::Op op);
};

/*
 * Exception classes.  These are used as arguments to the error
 * handlers.  The default error handlers throw them as exceptions,
 * but you are free to change this behavior.
 */


/**
 * \ingroup currency_decimal_numbers_group
 *
 * \brief
 * Signals problems in computations involving the Rogue Wave decimal
 * classes.
 *
 * RWDecimalInexactErr is one of the error objects used to signal problems
 * in computations involving RWDecimal and RWFixedDecimal objects. The other
 * error object is RWDecimalOverflowErr. See RWDecimal and RWFixedDecimal
 * for details about when the error objects are used. Also, see the section
 * on error handling in the <em>Currency Module User's Guide</em> for
 * information about how to set error handlers.
 *
 * \synopsis
 * #include <rw/currency/decimal.h> // for RWDecimalInexactErr<T>
 *                                  // and RWDecimalOverflowErr<T>
 * #include <rw/currency/mp2int.h>  // For RWMP2Int
 *
 * RWDecimal<RWMP2Int> a = "9.9999999999";
 * RWDecimal<RWMP2Int> b = a*a;    // calls the inexact error handler
 * \endsynopsis
 *
 * The following header files are available for backward compatibility:
 * \code
 * #include <rw/dec52.h>   // RWDecimal52InexactErr,
 *                         // RWDecimal52OverflowErr
 * #include <rw/dec64.h>   // RWDecimal64InexactErr,
 *                         // RWDecimal64OverflowErr
 * #include <rw/dec96.h>   // RWDecimal96InexactErr,
 *                         // RWDecimal96OverflowErr
 * \endcode
 */
template< class M >
class RWDecimalInexactErr : public RWExternalErr
{
public:
    RWDecimalInexactErr(RWDecimalBase::Op o, const RWDecimal<M>& a, const RWDecimal<M>& b, const RWMessage& msg);


    /**
     * Returns the left operand of the operation that generated the error
     * object.
     */
    RWDecimal<M>      leftOperand() const
    {
        return operandA_;
    }

    /**
     * Returns the right operand of the operation that generated the error
     * object.
     */
    RWDecimal<M>      rightOperand() const
    {
        return operandB_;
    }

    /**
     * Returns the operation that generated the error object. The returned
     * value RWDecimalBase::Op is an enumerated type scoped in the
     * RWDecimalBase class.
     */
    RWDecimalBase::Op operation() const
    {
        return op_;
    }
    RWCString         opString() const;

    /**
     * Returns a message describing the error.
     */
    const char*       msg() const
    {
        return why();
    }

private:
    RWDecimalBase::Op op_;
    RWDecimal<M>     operandA_, operandB_;
};


/**
 * \ingroup currency_decimal_numbers_group
 *
 * \brief
 * Signals overflow problems in computations involving the Rogue Wave
 * decimal classes.
 *
 * RWDecimalOverflowErr is one of the error objects used to signal problems
 * in computations involving RWDecimal and RWFixedDecimal objects. The other
 * error object is RWDecimalInexactErr. See RWDecimal and RWFixedDecimal for
 * details about when the error objects are used. Also, see the section on
 * error handling in the <em>Currency Module User's Guide</em> for
 * information about how to set error handlers.
 *
 * \synopsis
 * #include <rw/currency/decimal.h> // for RWDecimalOverflowErr<T>
 *                                  // and RWDecimalInexactErr<T>
 * #include <rw/currency/mp2int.h>  // For RWMP2Int
 *
 * RWDecimal<RWMP2Int> x = "9999999999";
 * RWDecimal<RWMP2Int> y = x*x;  // calls the overflow error handler
 * \endsynopsis
 *
 * The following header files are available for backward compatibility:
 * \code
 * #include <rw/dec52.h>   // RWDecimal52InexactErr,
 *                         // RWDecimal52OverflowErr
 * #include <rw/dec64.h>   // RWDecimal64InexactErr,
 *                         // RWDecimal64OverflowErr
 * #include <rw/dec96.h>   // RWDecimal96InexactErr,
 *                         // RWDecimal96OverflowErr
 * \endcode
 */
template< class M >
class  RWDecimalOverflowErr : public RWExternalErr
{
public:
    RWDecimalOverflowErr(RWDecimalBase::Op o, const RWDecimal<M>& a, const RWDecimal<M>& b, const RWMessage&);

    /**
     * Returns the left operand of the operation that generated the error
     * object.
     */
    RWDecimal<M>      leftOperand() const
    {
        return operandA_;
    }

    /**
     * Returns the right operand of the operation that generated the error
     * object.
     */
    RWDecimal<M>      rightOperand() const
    {
        return operandB_;
    }

    /**
     * Returns the operation that generated the error object. The returned
     * value RWDecimalBase::Op is an enumerated type scoped in the
     * RWDecimalBase class.
     */
    RWDecimalBase::Op operation() const
    {
        return op_;
    }
    RWCString         opString() const;

    /**
     * Returns a message describing the error.
     */
    const char*       msg() const
    {
        return why();
    }

private:
    RWDecimalBase::Op   op_;
    RWDecimal<M> operandA_, operandB_;
};

template< class M >
inline unsigned rwMaxDecimalLeftShift(const M& x)
{
    double max = x >= M::zero() ? M::maxValue().asDouble() : -(M::minValue().asDouble());
    int n;
    if (x == M::zero()) {
        n = (int)log10(max);
    }
    else {
        n = (int)(log10(max / fabs(x.asDouble())));
    }
    return (n <= 0 ? 0U : (unsigned)n);
}


// ***************************************************************************
//
// getStatePlus
//
// This function determines the state of the result of adding two RWDecimals
// together.
//
// ****************************************************************************

template< class M >
inline RWDecimalBase::State RWDecimal<M>::getStatePlus(const RWDecimal<M>& a, const RWDecimal<M>& b)
{

    if (a.state_ == RWDecimalBase::missingstate || b.state_ == RWDecimalBase::missingstate) {
        return RWDecimalBase::missingstate;
    }

    if (a.state_ == RWDecimalBase::NaNstate || b.state_ == RWDecimalBase::NaNstate) {
        return RWDecimalBase::NaNstate;
    }

    if (a.state_ == RWDecimalBase::SNaNstate || b.state_ == RWDecimalBase::SNaNstate) {
        return RWDecimalBase::NaNstate;
    }

    if (a.state_ == RWDecimalBase::nullstate) {
        return b.state_;
    }

    if (b.state_ == RWDecimalBase::nullstate) {
        return a.state_;
    }

    if (a.state_ == RWDecimalBase::infinitystate) {
        if (b.state_ == RWDecimalBase::infinitystate && ((a.mantissa_ < M::zero()) != (b.mantissa_ < M::zero()))) {
            return RWDecimalBase::NaNstate;
        }
        return RWDecimalBase::infinitystate;
    }

    if (b.state_ == RWDecimalBase::infinitystate) {
        return RWDecimalBase::infinitystate;
    }

    return RWDecimalBase::normal;
}


// ***************************************************************************
//
// getStateMultiply
//
// This function determines the state of the result of multiplying two
// RWDecimals together.
//
// ****************************************************************************

template< class M >
inline RWDecimalBase::State RWDecimal<M>::getStateMultiply(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    if (a.state_ == RWDecimalBase::missingstate || b.state_ == RWDecimalBase::missingstate) {
        return RWDecimalBase::missingstate;
    }

    if (a.state_ == RWDecimalBase::NaNstate || b.state_ == RWDecimalBase::NaNstate) {
        return RWDecimalBase::NaNstate;
    }

    if (a.state_ == RWDecimalBase::SNaNstate || b.state_ == RWDecimalBase::SNaNstate) {
        return RWDecimalBase::NaNstate;
    }

    if (a.state_ == RWDecimalBase::nullstate) {
        return b.state_;
    }

    if (b.state_ == RWDecimalBase::nullstate) {
        return a.state_;
    }

    if (a.state_ == RWDecimalBase::infinitystate || b.state_ == RWDecimalBase::infinitystate) {
        if (a == 0 || b == 0) {
            return RWDecimalBase::NaNstate;
        }
        return RWDecimalBase::infinitystate;
    }

    return RWDecimalBase::normal;
}


// ***************************************************************************
//
// getStateDivide
//
// This function determines the state of the result of dividing two RWDecimals
// together.
//
// ****************************************************************************

template< class M >
inline RWDecimalBase::State RWDecimal<M>::getStateDivide(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    if ((a.state_ == RWDecimalBase::nullstate) && (b.state_ == RWDecimalBase::normal)) {
        return RWDecimalBase::NaNstate;
    }

    if (a.state_ == RWDecimalBase::missingstate || b.state_ == RWDecimalBase::missingstate) {
        return RWDecimalBase::missingstate;
    }

    if (a.state_ == RWDecimalBase::NaNstate || b.state_ == RWDecimalBase::NaNstate) {
        return RWDecimalBase::NaNstate;
    }

    if (a.state_ == RWDecimalBase::SNaNstate || b.state_ == RWDecimalBase::SNaNstate) {
        return RWDecimalBase::NaNstate;
    }

    if (a.state_ == RWDecimalBase::infinitystate) {
        if (b.state_ == RWDecimalBase::infinitystate) {
            return RWDecimalBase::NaNstate;
        }
        if (b.state_ == RWDecimalBase::normal) {
            return RWDecimalBase::infinitystate;
        }
    }

    if (a.state_ == RWDecimalBase::nullstate) {
        return b.state_;
    }

    if (b.state_ == RWDecimalBase::nullstate) {
        return a.state_;
    }

    return RWDecimalBase::normal;
}


template< class M >
inline RWDecimal<M> RWDecimal<M>::addEqualExponents(const M& lhs, const M& rhs, int exp, RWDecimalBase::Op op)
{
    M   sumMantissa;
    int sumExponent = exp;
    unsigned numTruncated = M::preciseAdd(lhs, rhs, sumMantissa);

    if (numTruncated == 0) {
        return RWDecimal<M>(sumMantissa, sumExponent);
    }

    sumExponent -= numTruncated;
    if (sumExponent < 0) {
        RWMsgId msgid = (op == RWDecimalBase::add) ? RWDCML_ADDOVER : RWDCML_SUBOVER;
        overflow(op, RWDecimal<M>(lhs, exp), RWDecimal<M>(rhs, exp), RWMessage(msgid, classname));
        return RWDecimal<M>(RWDecimalBase::NaNstate);
    }
    RWMsgId msgid = (op == RWDecimalBase::add) ? RWDCML_ADDINEXACT : RWDCML_SUBINEXACT;
    inexact(op, RWDecimal<M>(lhs, exp), RWDecimal<M>(rhs, exp), RWMessage(msgid, classname));

    return RWDecimal<M>(sumMantissa, sumExponent);
}




// Arithmetic operators ---------------------------------------------------
/**
 * \relates RWDecimal
 * These arithmetic operators have their conventional meanings. If the
 * resulting operation causes loss of precision or overflow in the result,
 * the appropriate error handler will be called before the function returns.
 *
 * \note
 * Operations on sentinel values are defined in #RWDecimalBase::State.
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::decplus(a, b, RWDecimalBase::add);
}

/**
 * \relates RWDecimal
 * \copydoc operator+(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWDecimal<M>& a, int b)
{
    return RWDecimal<M>::decplus(a, RWDecimal<M>(b), RWDecimalBase::add);
}

/**
 * \relates RWDecimal
 * \copydoc operator+(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWDecimal<M>& a, long b)
{
    return RWDecimal<M>::decplus(a, RWDecimal<M>(b), RWDecimalBase::add);
}

/**
 * \relates RWDecimal
 * \copydoc operator+(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator+(int a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::decplus(RWDecimal<M>(a), b, RWDecimalBase::add);
}

/**
 * \relates RWDecimal
 * \copydoc operator+(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator+(long a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::decplus(RWDecimal<M>(a), b, RWDecimalBase::add);
}

/**
 * \relates RWDecimal
 * These arithmetic operators have their conventional meanings. If the
 * resulting operation causes loss of precision or overflow in the result,
 * the appropriate error handler will be called before the function returns.
 *
 * \note
 * Operations on sentinel values are defined in #RWDecimalBase::State.
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::decplus(a, -b, RWDecimalBase::sub);
}

/**
 * \relates RWDecimal
 * \copydoc operator-(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWDecimal<M>& a, int b)
{
    return RWDecimal<M>::decplus(a, RWDecimal<M>(-b), RWDecimalBase::sub);
}

/**
 * \relates RWDecimal
 * \copydoc operator-(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWDecimal<M>& a, long b)
{
    return RWDecimal<M>::decplus(a, RWDecimal<M>(-b), RWDecimalBase::sub);
}

/**
 * \relates RWDecimal
 * \copydoc operator-(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator-(int a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::decplus(RWDecimal<M>(a), -b, RWDecimalBase::sub);
}

/**
 * \relates RWDecimal
 * \copydoc operator-(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator-(long a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::decplus(RWDecimal<M>(a), -b, RWDecimalBase::sub);
}

/**
 * \relates RWDecimal
 * These arithmetic operators have their conventional meanings. If the
 * resulting operation causes loss of precision or overflow in the result,
 * the appropriate error handler will be called before the function returns.
 *
 * \note
 * Operations on sentinel values are defined in #RWDecimalBase::State.
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::multiply(a, b);
}

/**
 * \relates RWDecimal
 * \copydoc operator*(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator*(double a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::multiply(RWDecimal<M>::from(a), b);
}

/**
 * \relates RWDecimal
 * \copydoc operator*(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWDecimal<M>& a, double b)
{
    return RWDecimal<M>::multiply(a, RWDecimal<M>::from(b));
}

/**
 * \relates RWDecimal
 * \copydoc operator*(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWDecimal<M>& a, int b)
{
    return RWDecimal<M>::multiply(a, RWDecimal<M>(b));
}

/**
 * \relates RWDecimal
 * \copydoc operator*(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWDecimal<M>& a, long b)
{
    return RWDecimal<M>::multiply(a, RWDecimal<M>(b));
}

/**
 * \relates RWDecimal
 * \copydoc operator*(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator*(int a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::multiply(RWDecimal<M>(a), b);
}

/**
 * \relates RWDecimal
 * \copydoc operator*(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator*(long a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::multiply(RWDecimal<M>(a), b);
}


// // I wish someone would explain it to me.  For all the other binary operators
// // conversions happen as they should.  But not the / operator.  e.g.
// //
// //  RWDecimal<M> x("123"), y;
// //  y = x + 2;  // OK. the int 2 is converted to decimal
// //  y = x - 2;  // OK.
// //  y = x * 2;  // OK
// //  y = x / 2;  // Compile error!! not operator / for lhs RWDecimal<M> and rhs int
// //
// // And this is not for just some screwy compiler.  I get this error on all of them!
// // This is the reason for the all the overloads of the / operator.  Two for each
// // conversion that should happen via a ctor.

/**
 * \relates RWDecimal
 * These arithmetic operators have their conventional meanings. If the
 * resulting operation causes loss of precision or overflow in the result,
 * the appropriate error handler will be called before the function returns.
 *
 * \note
 * Operations on sentinel values are defined in #RWDecimalBase::State.
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::divide(a, b);
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimal<M>& a, int b)
{
    return RWDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimal<M>& a, long b)
{
    return RWDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(int a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(long a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimal<M>& a, const RWDecimalPortable& b)
{
    return RWDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimalPortable& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimal<M>& a, const char* b)
{
    return RWDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const char* a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(double a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::divide(RWDecimal<M>::from(a), b);
}

/**
 * \relates RWDecimal
 * \copydoc operator/(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimal<M>& a, double b)
{
    return RWDecimal<M>::divide(a, RWDecimal<M>::from(b));
}

// Helper function for state comparison.
template< class T >
inline bool rwValidCompare(const T& a, const T& b)
{
    if ((!a.isNumber() && abs(a) != T::infinity) ||
            (!b.isNumber() && abs(b) != T::infinity)) {
        return false;
    }
    return true;
}

/**
 * \relates RWDecimal
 * The equality operator returns \c true if the two operands are exactly the
 * same, and \c false otherwise.
 */
template<class M>
inline  bool RW_DCML_MEMBER_EXPORT operator==(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::equal(a, b);
}

/**
 * \relates RWDecimal
 * The relational operators have their conventional meanings. If one (or
 * both) of the operands is #null, #missing, #NaN, or #SNaN, then the result
 * of the operator is undefined.
 */
template<class M>
inline  bool RW_DCML_MEMBER_EXPORT operator<(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::lessThan(a, b);
}

// Don't provide relational operators if using a C++ Standard Library and
// namespaces are broken, since the definitions below would be redundant.
#if !defined(RWSTD_NO_NAMESPACE) || defined(DOXYGEN)

/**
 * \relates RWDecimal
 * The not equal operator returns \c true if the two operands are not
 * exactly the same, and \c false otherwise.
 */
template<class M> inline  bool RW_DCML_MEMBER_EXPORT operator!=(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return !RWDecimal<M>::equal(a, b);
}

/**
 * \relates RWDecimal
 * \copydoc operator<(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M> inline  bool RW_DCML_MEMBER_EXPORT operator>(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWDecimal<M>::lessThan(b, a);
}

/**
 * \relates RWDecimal
 * \copydoc operator<(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M> inline  bool RW_DCML_MEMBER_EXPORT operator>=(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    if (!rwValidCompare(a, b)) {
        return false;
    }
    return !RWDecimal<M>::lessThan(a, b);
}


/**
 * \relates RWDecimal
 * \copydoc operator<(const RWDecimal<M>& a, const RWDecimal<M>& b)
 */
template<class M> inline  bool RW_DCML_MEMBER_EXPORT operator<=(const RWDecimal<M>& a, const RWDecimal<M>& b)
{
    if (!rwValidCompare(a, b)) {
        return false;
    }
    return !RWDecimal<M>::lessThan(b, a);
}
#endif


/**
 * \relates RWDecimal
 * Returns \a d raised to the exponent \a e. This computation is likely to
 * cause a loss of precision (and a corresponding call to the precision
 * error handler) if \a e is at all large, and \a d has any decimal places.
 */
template<class M> inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT pow(const RWDecimal<M>& d, int e)
{
    return RWDecimal<M>::power(d, e);
}


/**
 * \relates RWDecimal
 * Returns the absolute value of \a d.
 */
template<class M> inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT abs(const RWDecimal<M>& d)
{
    return RWDecimal<M>::absoluteValue(d);
}

// // Begin duplicates: AIX compiler does not allow default initializers here.
template<class M>
inline RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d, int digits, RWDecimalBase::RoundingMethod m, unsigned int roundDigit)
{
    return RWDecimal<M>::roundDecimal(d, digits, m, roundDigit);
}

/**
 * \relates RWDecimal
 * Returns \a d rounded to \a digits decimal places. The method of rounding
 * is controlled by the optional last parameter. These parameters are
 * enumerated in RWDecimalBase, and their effects are shown in the table
 * below. The last three columns indicate the result of rounding three
 * example numbers to one decimal place. Rounding a negative number returns
 * exactly the same result as rounding the corresponding positive number and
 * making the result negative.
 *
 * <table>
 * <tr>
 * <td><b><b>Method</b></b></td>
 * <td><b><b>Description</b></b></td>
 * <td><b><b>1.25</b></b></td>
 * <td><b><b>1.35</b></b></td>
 * <td><b><b>1.251</b></b></td>
 * </tr>
 * <tr>
 * <td>\c PLAIN</td>
 * <td>Rounds towards zero on a tie</td>
 * <td>1.2</td>
 * <td>1.3</td>
 * <td>1.2</td>
 * </tr>
 * <tr>
 * <td>\c UP</td>
 * <td>Always rounds away from zero</td>
 * <td>1.3</td>
 * <td>1.4</td>
 * <td>1.3</td>
 * </tr>
 * <tr>
 * <td>\c DOWN</td>
 * <td>Always rounds toward zero</td>
 * <td>1.2</td>
 * <td>1.3</td>
 * <td>1.2</td>
 * </tr>
 * <tr>
 * <td>\c TRUNCATE</td>
 * <td>Same as \c DOWN</td>
 * <td>1.2</td>
 * <td>1.3</td>
 * <td>1.2</td>
 * </tr>
 * <tr>
 * <td>\c BANKERS</td>
 * <td>On a tie, round so last digit is even</td>
 * <td>1.2</td>
 * <td>1.4</td>
 * <td>1.3</td>
 * </tr>
 * </table>
 */
template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d, int digits, RWDecimalBase::RoundingMethod m)
{
    return RWDecimal<M>::roundDecimal(d, digits, m, 4U);
}

template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d, RWDecimalBase::RoundingMethod m, unsigned int roundDigit)
{
    return RWDecimal<M>::roundDecimal(d, 0, m, roundDigit);
}

template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d, RWDecimalBase::RoundingMethod m)
{
    return RWDecimal<M>::roundDecimal(d, 0, m, 4U);
}

template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d, int digits, unsigned int roundDigit)
{
    return RWDecimal<M>::roundDecimal(d, digits, RWDecimalBase::PLAIN, roundDigit);
}

template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d, int digits)
{
    return RWDecimal<M>::roundDecimal(d, digits, RWDecimalBase::PLAIN, 4U);
}

template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d, unsigned int roundDigit)
{
    return RWDecimal<M>::roundDecimal(d, 0, RWDecimalBase::PLAIN, roundDigit);
}

template<class M>
inline  RWDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWDecimal<M>& d)
{
    return RWDecimal<M>::roundDecimal(d, 0, RWDecimalBase::PLAIN, 4U);
}

/**
 * \relates RWDecimal
 * Converts the argument to an integer. The method of rounding is controlled
 * by the optional last parameter as described in detail above in the
 * description of the global function round(). Arguments with #missing,
 * #null, #NaN, #SNaN, or #infinity are converted to zero.
 */
template<class M>
inline  long int RW_DCML_MEMBER_EXPORT toInt(const RWDecimal<M>& d, RWDecimalBase::RoundingMethod m)
{
    return RWDecimal<M>::convertToInt(d, m);
}

template<class M>
inline  long int RW_DCML_MEMBER_EXPORT toInt(const RWDecimal<M>& d)
{
    return RWDecimal<M>::convertToInt(d, RWDecimalBase::PLAIN);
}

// // End duplicates

/**
 * \relates RWDecimal
 * Converts an RWDecimal to a string. The string produced by this function
 * has the form \c -xxx.yyy where the \c xxx and \c yyy are integers to the
 * left and right of the decimal. Digits only appear if necessary. For more
 * elaborate formatting, use an RWDecimalFormat object.
 */
template<class M>
inline  RWCString RW_DCML_MEMBER_EXPORT toString(const RWDecimal<M>& d)
{
    return RWDecimal<M>::convertToString(d);
}

/**
 * \relates RWDecimal
 * Converts the argument to a double precision value close to its true
 * value. It will correctly convert arguments with the values, #NaN, #SNaN,
 * or #infinity. Arguments with #missing or #null are converted to zero.
 */
template<class M>
inline  long double RW_DCML_MEMBER_EXPORT toDouble(const RWDecimal<M>& d)
{
    return RWDecimal<M>::convertToDouble(d);
}


template<class M>
inline  std::ostream& operator <<(std::ostream& strm, const RWDecimal<M>& d)
{
    return RWDecimal<M>::shift(strm, d);
}

/**
 * \relates RWDecimal
 * Reads an RWDecimal from an input stream. Since we write numbers using
 * base 10 and the RWDecimal class stores numbers using base 10, the number
 * constructed is an exact representation of the input. The number may
 * contain embedded commas to separate groups of digits and may have a
 * leading dollar sign. Negatives can be indicated with a negative sign or
 * by using parentheses. A technical description of the exact input grammar
 * allowed is given in the section "Technical Notes" of the <em>Currency
 * Module User's Guide</em>.
 */
template<class M>
inline  std::istream& operator >>(std::istream& strm, RWDecimal<M>& d)
{
    return RWDecimal<M>::shift(strm, d);
}

/**
 * \relates RWDecimal
 * Writes an RWDecimal to an output stream. Output is written in the form
 * \c -xxx.yyy where the \c xxx and \c yyy are integers and only the
 * necessary parts are written. For more elaborate formatting, use an
 * RWDecimalFormat object.
 */
template<class M>
inline RWvostream& operator <<(RWvostream& strm, const RWDecimal<M>& n)
{
    n.saveOn(strm);
    return strm;
}

template<class M>
inline RWvistream& operator >>(RWvistream& strm, RWDecimal<M>& n)
{
    n.restoreFrom(strm);
    return strm;
}

template<class M>
inline RWFile& operator <<(RWFile& strm, const RWDecimal<M>& n)
{
    n.saveOn(strm);
    return strm;
}

template<class M>
inline RWFile& operator >>(RWFile& strm, RWDecimal<M>& n)
{
    n.restoreFrom(strm);
    return strm;
}



// These exact match operators are provided to prevent
// ambiguities involving the the conversion operator
// to RWCString

// operator ==
template <class M>
inline bool operator==(const RWDecimal<M>& x, const RWCString& y)
{
    return x == RWDecimal<M>(y);
}

template <class M>
inline bool operator==(const RWCString& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWDecimal<M>& x, const RWDecimalPortable& y)
{
    return x == RWDecimal<M>(y);
}

template <class M>
inline bool operator==(const RWDecimalPortable& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWDecimal<M>& x, const char* y)
{
    return x == RWDecimal<M>(y);
}

template <class M>
inline bool operator==(const char* x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWDecimal<M>& x, const long& y)
{
    return x == RWDecimal<M>(y);
}

template <class M>
inline bool operator==(const long& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWDecimal<M>& x, const int& y)
{
    return x == RWDecimal<M>(y);
}

template <class M>
inline bool operator==(const int& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) == y;
}


// operator <
template <class M>
inline bool operator<(const RWDecimal<M>& x, const RWCString& y)
{
    return x < RWDecimal<M>(y);
}

template <class M>
inline bool operator<(const RWCString& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWDecimal<M>& x, const RWDecimalPortable& y)
{
    return x < RWDecimal<M>(y);
}

template <class M>
inline bool operator<(const RWDecimalPortable& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWDecimal<M>& x, const char* y)
{
    return x < RWDecimal<M>(y);
}

template <class M>
inline bool operator<(const char* x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWDecimal<M>& x, const long& y)
{
    return x < RWDecimal<M>(y);
}

template <class M>
inline bool operator<(const long& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWDecimal<M>& x, const int& y)
{
    return x < RWDecimal<M>(y);
}

template <class M>
inline bool operator<(const int& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) < y;
}



// operator >
template <class M>
inline bool operator>(const RWDecimal<M>& x, const RWCString& y)
{
    return x > RWDecimal<M>(y);
}

template <class M>
inline bool operator>(const RWCString& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWDecimal<M>& x, const RWDecimalPortable& y)
{
    return x > RWDecimal<M>(y);
}

template <class M>
inline bool operator>(const RWDecimalPortable& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWDecimal<M>& x, const char* y)
{
    return x > RWDecimal<M>(y);
}

template <class M>
inline bool operator>(const char* x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWDecimal<M>& x, const long& y)
{
    return x > RWDecimal<M>(y);
}

template <class M>
inline bool operator>(const long& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWDecimal<M>& x, const int& y)
{
    return x > RWDecimal<M>(y);
}

template <class M>
inline bool operator>(const int& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) > y;
}



// operator >=
template <class M>
inline bool operator>=(const RWDecimal<M>& x, const RWCString& y)
{
    return x >= RWDecimal<M>(y);
}

template <class M>
inline bool operator>=(const RWCString& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWDecimal<M>& x, const RWDecimalPortable& y)
{
    return x >= RWDecimal<M>(y);
}

template <class M>
inline bool operator>=(const RWDecimalPortable& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWDecimal<M>& x, const char* y)
{
    return x >= RWDecimal<M>(y);
}

template <class M>
inline bool operator>=(const char* x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWDecimal<M>& x, const long& y)
{
    return x >= RWDecimal<M>(y);
}

template <class M>
inline bool operator>=(const long& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWDecimal<M>& x, const int& y)
{
    return x >= RWDecimal<M>(y);
}

template <class M>
inline bool operator>=(const int& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) >= y;
}



// operator <=
template <class M>
inline bool operator<=(const RWDecimal<M>& x, const RWCString& y)
{
    return x <= RWDecimal<M>(y);
}

template <class M>
inline bool operator<=(const RWCString& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWDecimal<M>& x, const RWDecimalPortable& y)
{
    return x <= RWDecimal<M>(y);
}

template <class M>
inline bool operator<=(const RWDecimalPortable& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWDecimal<M>& x, const char* y)
{
    return x <= RWDecimal<M>(y);
}

template <class M>
inline bool operator<=(const char* x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWDecimal<M>& x, const long& y)
{
    return x <= RWDecimal<M>(y);
}

template <class M>
inline bool operator<=(const long& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWDecimal<M>& x, const int& y)
{
    return x <= RWDecimal<M>(y);
}

template <class M>
inline bool operator<=(const int& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) <= y;
}



// operator !=
template <class M>
inline bool operator!=(const RWDecimal<M>& x, const RWCString& y)
{
    return x != RWDecimal<M>(y);
}

template <class M>
inline bool operator!=(const RWCString& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWDecimal<M>& x, const RWDecimalPortable& y)
{
    return x != RWDecimal<M>(y);
}

template <class M>
inline bool operator!=(const RWDecimalPortable& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWDecimal<M>& x, const char* y)
{
    return x != RWDecimal<M>(y);
}

template <class M>
inline bool operator!=(const char* x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWDecimal<M>& x, const long& y)
{
    return x != RWDecimal<M>(y);
}

template <class M>
inline bool operator!=(const long& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWDecimal<M>& x, const int& y)
{
    return x != RWDecimal<M>(y);
}

template <class M>
inline bool operator!=(const int& x, const RWDecimal<M>& y)
{
    return RWDecimal<M>(x) != y;
}


RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimal< RWMultiPrecisionInt<1> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimal< RWMultiPrecisionInt<2> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimal< RWMultiPrecisionInt<3> >);

RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimalInexactErr< RWMultiPrecisionInt<1> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimalInexactErr< RWMultiPrecisionInt<2> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimalInexactErr< RWMultiPrecisionInt<3> >);

RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimalOverflowErr< RWMultiPrecisionInt<1> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimalOverflowErr< RWMultiPrecisionInt<2> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWDecimalOverflowErr< RWMultiPrecisionInt<3> >);

#if defined(RW_NO_STATIC_TEMPLATE_FUNCTION_PTR_INITIALIZER)
#  define RWDCML_INITIALIZE_RWDECIMAL_FUNCTION_PTR(a) \
template<>                                                                                                                 \
  void  (*RWDecimal< RWMultiPrecisionInt<a> >::inexactHandler_)( const RWDecimalInexactErr< RWMultiPrecisionInt<a> >& ) =  \
    RWDecimal< RWMultiPrecisionInt<a> >::defaultInexactHandler;                                                            \
                                                                                                                           \
template<>                                                                                                                 \
  void (*RWDecimal< RWMultiPrecisionInt<a> >::overflowHandler_)( const RWDecimalOverflowErr< RWMultiPrecisionInt<a> >& ) = \
    RWDecimal< RWMultiPrecisionInt<a> >::defaultOverflowHandler;
#else
#  define RWDCML_INITIALIZE_RWDECIMAL_FUNCTION_PTR(a)
#endif

//-------------------------------------------------------------------------
//
// RWDCML_RWDECIMAL_STATIC_INIT is necessary when using the Currency module with Windows,
// and when it is compiled as a DLL.  It must be added to code that instantiates an
// instance of RWDecimal not instantiated in the currency library.  The parameter
// 'a' defines the width of RWMultiPrecisionInt
//
//-------------------------------------------------------------------------

#if defined(_MSC_VER)
#  define RWDCML_RWDECIMAL_STATIC_INIT(a) \
static RWDecimalOverflowErr< RWMultiPrecisionInt<a> > rwDecimalOverflowErrInstVar##a( RWDecimalBase::assign, \
                                                           RWDecimal< RWMultiPrecisionInt<a> >(),            \
                                                           RWDecimal< RWMultiPrecisionInt<a> >(),            \
                                                           RWMessage("") );                                  \
RWDCML_INITIALIZE_RWDECIMAL_FUNCTION_PTR(a)
#else
#  define RWDCML_RWDECIMAL_STATIC_INIT(a)
#endif

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/decimal.cc>
#endif

#endif // RW_CURRENCY_DECIMAL_H
