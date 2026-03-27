#ifndef RW_CURRENCY_FIXEDDEC_H
#define RW_CURRENCY_FIXEDDEC_H

/**************************************************************************
 *
 * Definition of RWFixedDecimal and related classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/fixeddec.h#1 $
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
 **************************************************************************
 *
 * Declarations for the RWFixedDecimal<M> class.  The RWFixedDecimal class
 * is derived from the RWDecimal class using private inheritance.  Although
 * the public interface for the fixed decimal classes is a subset of the
 * public interface for the decimal classes, private inheritance is used
 * for backward compatibility reasons.  In  previous releases of Money.h++
 * the decimal and fixed decimal classes were unrelated to each other.  Thus
 * we do not want pointers and references to fixed decimal instances being
 * implicitly converted to pointers or references to decimal classes.
 *
 * Although friend functions may implicitly convert pointers to a private base
 * class, a few compilers had trouble with this.  Most notably MSVC 5 had a
 * major bug that prevented this.  So, instead of a bunch of ifdefs global
 * operators and functions for the fixed decimal class are reimplemented here.
 * Their implementation involves explicitly casting their fixed decimal
 * arguments to the decimals (the base class) and invoking the corresponding
 * operator for decimals.
 *
 *************************************************************************/

#include <rw/currency/decimal.h>
#include <rw/dcmldefs.h>

/**
 * \ingroup currency_decimal_numbers_group
 *
 * \brief
 * Exact representation of a decimal fraction with a fixed number of digits
 * after the decimal point, with automatic rounding to ensure correct number
 * of decimal places.
 *
 * RWFixedDecimal classes are exact representations of decimal fractions
 * with a fixed number of digits after the decimal point. In most ways, they
 * behave exactly like the corresponding RWDecimal classes. The exception is
 * that rounding automatically occurs to ensure the correct number of
 * decimal places.
 *
 * RWFixedDecimal is templatized. Three short type names are provided:
 * \ref RWFixedDecimal "RWFixedDecimal<RWMP1Int>",
 * \ref RWFixedDecimal "RWFixedDecimal<RWMP2Int>", and
 * \ref RWFixedDecimal "RWFixedDecimal<RWMP3Int>". Each type provides a
 * different amount of precision, as described below in the Limits section.
 * The trade-off is simple: the more precision, the slower the class.
 *
 * You may also write your own RWFixedDecimal class. Throughout this
 * section, when we refer to the RWFixedDecimal class, you can assume that
 * it applies to any of the three provided classes, or to one you have
 * defined.
 *
 * \synopsis
 * #include <rw/currency/fixeddec.h>  // for RWFixedDecimal<T>
 * #include <rw/currency/mp2int.h>   // For RWMP2Int
 *
 * RWFixedDecimal<RWMP2Int> dollarAccount(0,2) = "0.01";
 *     // initialize to zero then set to 2 decimal places
 * \endsynopsis
 *
 * The following header files are available for backward compatibility:
 * \code
 * #include <rw/fixdec52.h> // RWFixedDecimal52
 * #include <rw/fixdec64.h> // RWFixedDecimal64
 * #include <rw/fixdec96.h> // RWFixedDecimal96
 * \endcode
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/currency/fixeddec.h>
 * #include <rw/currency/mp2int.h>
 *
 * int main()
 * {
 *  RWFixedDecimal<RWMP2Int> penny = "0.01";
 *  RWFixedDecimal<RWMP2Int> bank = 0;
 *  for(int i=100; i--;) bank+=penny;      // deposit 100 pennies
 *  bank -= 1;                             // withdraw a buck
 *  std::cout << (bank==0 ? "broke!" : "whew! still solvent") << std::endl;
 *  return 0;
 * }
 * \endcode
 * \endexample
 *
 * <h4>Limits</h4>
 * Class RWFixedDecimal provides three static member functions that can be
 * used to define the limits on an RWFixedDecimal object. These functions
 * return the precision, maximum value, and minimum value:
 *
 * \code
 * int RWFixedDecimal<T>::maxDigits();              // precision
 * RWFixedDecimal<T> RWFixedDecimal<T>::maxValue(); // maximum value
 * RWFixedDecimal<T> RWFixedDecimal<T>::minValue(); // minimum value
 * \endcode
 *
 * Note that the precision returned by maxDigits() does not usually
 * represent the number of digits in the largest possible RWFixedDecimal
 * object. Rather, it indicates the maximum number of digits supported by
 * that object without returning an overflow error. For example the number
 * shown in Table 6 as the maximum value for
 * \ref RWFixedDecimal "RWFixedDecimal<RWMP2Int>" has 19 digits. Notice,
 * however, that any number larger than the 19-digit number shown will cause
 * an overflow error because it exceeds the maximum value. Therefore,
 * RWFixedDecimal<RWMP2Int>::maxDigits() returns 18, because that is the
 * number of digits that will always be supported without an overflow error.
 *
 * The following code snippets demonstrate when an overflow condition caused
 * by exceeding a maximum value will occur:
 *
 * \code
 * // Set max to maximum value:
 * RWFixedDecimal<RWMP1Int>max = RWFixedDecimal<RWMP1Int>::maxValue();
 *
 * // Add 1 to max to generate an overflow error:
 * RWFixedDecimal<RWMP1Int>tooBig = max + RWFixedDecimal<RWMP1Int>(1);
 *
 * // Set min to minimum value:
 * RWFixedDecimal<RWMP1Int>min = RWFixedDecimal<RWMP1Int>::minValue();
 *
 * // Subtract 1 from min to generate an overflow error:
 * RWFixedDecimal<RWMP1Int>tooSmall = min-RWFixedDecimal<RWMP1Int>(1) ;
 * \endcode
 *
 * Table 6 indicates the minimum and maximum values for RWFixedDecimal when
 * \c T is replaced by one of the provided multiprecision integer types:
 *
 * <table>
 * <caption align="top">Table 6: Minimum and maximum values for
 * RWFixedDecimal<T></caption>
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
 * As well as representing a decimal fraction, an RWFixedDecimal can also
 * represent one of several non-numeric values. This concept has several
 * uses, including, for example, representing a null entry from a database
 * or indicating a missing value in data that is to be subjected to a
 * statistical analysis. Currency Module supports three sorts of non-numeric
 * values: #null, #missing, and #NaN (Not a Number).
 *
 * The result of performing arithmetic with a #missing or an #NaN is itself
 * a #missing or an #NaN. An arithmetic operation in which one operand is a
 * #null returns either a valid number or an #NaN (details are given below).
 * Thus, #missing values and #NaN values propagate while #null values do
 * not.
 *
 * The special static variables RWFixedDecimal::missing,
 * RWFixedDecimal::null, and RWFixedDecimal::NaN are the prototype #missing
 * and #null values; to set up a non-numeric RWFixedDecimal use these static
 * variables along with either the copy constructor or the assignment
 * operator. To test for a non-numeric value, use these values along with an
 * equality operator. You can use the member function
 * \ref RWDecimal::isNumber() "isNumber()" to test if an RWFixedDecimal has
 * a numeric value.
 *
 * <h4>Arithmetic</h4>
 * For the most part, arithmetic between RWFixedDecimal objects is defined
 * very simply: you get back an exact representation of the result of the
 * operation. There are several special cases, however:
 *
 * - <b>Loss of precision</b> . If the result cannot be exactly represented
 * as an RWFixedDecimal object because it has more than 18 significant
 * digits, then the result is set to an approximation of the true result,
 * and the inexact error handler is called.
 *
 * - <b>Overflow/underflow</b> . If the magnitude of the result exceeds the
 * range of RWFixedDecimal, then the overflow error handler is called.
 *
 * - <b>Operand of</b> #missing. If one of the operands is the value
 * #missing, then the result of the arithmetic operation is also a #missing.
 *
 * - <b>Operand of</b> #null. If both operands are #null, the result is also
 * #null. In addition and subtraction, a #null value behaves as if it were
 * zero. In multiplication, a #null behaves like a one. Dividing by a #null
 * value returns the numerator, i.e., a #null in the denominator behaves
 * like one. Using a #null as the numerator in a division returns an #NaN.
 */
template< class M >
class RWFixedDecimal : private RWDecimal<M>
{
public:
    typedef RWDecimalInexactErr<M> RWDecimalInexactErrType;
    typedef RWDecimalOverflowErr<M> RWDecimalOverflowErrType;

    // Rounding method enum values from RWDecimalBase.
    // Must change access to public since we use
    // private inheritance.
    using RWDecimal<M>::UP;
    using RWDecimal<M>::PLAIN;
    using RWDecimal<M>::DOWN;
    using RWDecimal<M>::BANKERS;
    using RWDecimal<M>::TRUNCATE;

    /**
     * Specifies the non-numeric value \c null. Use this static instance to
     * test or to set its value on an RWFixedDecimal.
     */
    static const RWFixedDecimal<M> null;

    /**
     * Specifies the non-numeric value \c missing. Use this static instance
     * to test or to set its value on an RWFixedDecimal.
     */
    static const RWFixedDecimal<M> missing;

    /**
     * Specifies the non-numeric value \c NaN. Use this static instance to
     * test or to set its value on an RWFixedDecimal.
     */
    static const RWFixedDecimal<M> NaN;

    /**
     * Specifies the non-numeric value \c SNaN. Use this static instance to
     * test or to set its value on an RWFixedDecimal.
     */
    static const RWFixedDecimal<M> SNaN;

    /**
     * Specifies the non-numeric value \c infinity. Use this static instance
     * to test or to set its value on an RWFixedDecimal.
     */
    static const RWFixedDecimal<M> infinity;

#if !defined(RW_DISABLE_DEPRECATED)

    /**
     * \deprecated
     * As of SourcePro 13, use RWFixedDecimal<M>::null.
     *
     * Specifies the non-numeric value \c null. Use this function to test or
     * to set its value on an RWFixedDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWFixedDecimal<M>::null instead") static RWFixedDecimal<M> nullValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWFixedDecimal<M>::missing.
     *
     * Specifies the non-numeric value \c missing. Use this function to test
     * or to set its value on an RWFixedDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWFixedDecimal<M>::missing instead") static RWFixedDecimal<M> missingValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWFixedDecimal<M>::NaN.
     *
     * Specifies the non-numeric value \c NaN. Use this function to test or
     * to set its value on an RWFixedDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWFixedDecimal<M>::NaN instead") static RWFixedDecimal<M> NaNValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWFixedDecimal<M>::SNaN.
     *
     * Specifies the non-numeric value \c SNaN. Use this function to test or
     * to set its value on an RWFixedDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWFixedDecimal<M>::SNaN instead") static RWFixedDecimal<M> SNaNValue();

    /**
     * \deprecated
     * As of SourcePro 13, use RWFixedDecimal<M>::infinity.
     *
     * Specifies the non-numeric value \c infinity. Use this function to
     * test or to set its value on an RWFixedDecimal.
     */
    RW_DEPRECATE_FUNC("Use RWFixedDecimal<M>::infinity instead") static RWFixedDecimal<M> infinityValue();

#endif

    //  Public constructors----------------------------------------------------

    /**
     * Constructs an RWFixedDecimal with a value of #null.
     */
    RWFixedDecimal()
        : RWDecimal<M>()
    {
    }

    /**
     * Copy constructor. Constructs an RWFixedDecimal that is a copy of the
     * argument.
     */
    RWFixedDecimal(const RWFixedDecimal<M>& d)
        : RWDecimal<M>(d)
    {
    }

    // Conversion from/to portable representation
    // This lets you convert to and from decimal classes of different precisions
    // Documented in base class
    RWFixedDecimal(const RWDecimalPortable& p)
        : RWDecimal<M>(p)
    {
    }

    operator RWDecimalPortable() const
    {
        const RWDecimal<M>& tmp = *this;
        return (RWDecimalPortable)tmp;
    }

    // Conversion from an RWDecimal

    /**
     * Constructs an RWFixedDecimal that represents the same value as the
     * parameter. The number of decimal places is fixed to be the same as
     * the parameter.
     */
    RWFixedDecimal(const RWDecimal<M>& d)
        : RWDecimal<M>(d)
    {
    }

    /**
     * Constructs an RWFixedDecimal with value \a i. The explicit integer
     * constructors prevent initializations from 0 from being ambiguous.
     * Without the \c int constructor, the compiler would not know whether
     * to convert 0 to a \c const \c char* or a \c long \c int.
     */
    RWFixedDecimal(int i)
        : RWDecimal<M>(i)
    {
    }

    /**
     * Constructs an RWFixedDecimal with value \a i.
     */
    RWFixedDecimal(long int i)
        : RWDecimal<M>(i)
    {
    }

    // specify an integer mantissa and exponent, this makes
    // declarations like RWFixedDecimal<M>(0,2) unambiguous

    /**
     * Constructs an RWFixedDecimal with value <tt>x*10-e</tt> where \c e
     * represents the number of digits after the decimal point.
     */
    RWFixedDecimal(int x, int e)
        : RWDecimal<M>(x, e)
    {
    }

    /**
     * \copydoc RWFixedDecimal(int m, int e)
     */
    RWFixedDecimal(long int x, int e)
        : RWDecimal<M>(x, e)
    {
    }

    /**
     * Constructs an RWDecimal from the null terminated character string
     * \a s. Since we write numbers using base 10 and the RWDecimal class
     * stores numbers using base 10, the number constructed is an exact
     * representation of the string. If the string cannot be successfully
     * parsed as a number, the RWDecimal is initialized to null. If the
     * number in the string cannot be exactly represented (for example, it
     * has too many significant digits) then the appropriate error handler
     * (either the inexact or overflow handler) is called. The string may
     * contain embedded commas to separate groups of digits and may have a
     * leading dollar sign. Negatives can be indicated with a negative sign
     * or by using parentheses. For more information on exact input grammar
     * allowed, see the discussion of Input Format Grammar in the
     * <em>Currency Module User's Guide</em>.
     */
    RWFixedDecimal(const char* s)
        : RWDecimal<M>(s)
    {
    }


    // Error handlers----------------------------------------------------------
    // These allow you to specify resumptive exceptions.

    // Documented in base class
    static void setInexactHandler(void (*eh)(const RWDecimalInexactErr<M>&))
    {
        RWDecimal<M>::setInexactHandler(eh);
    }

    // Documented in base class.
    static void setOverflowHandler(void (*eh)(const RWDecimalOverflowErr<M>&))
    {
        RWDecimal<M>::setOverflowHandler(eh);
    }

    static void defaultInexactHandler(const RWDecimalInexactErr<M>& err)
    {
        RWDecimal<M>::defaultInexactHandler(err);
    }

    static void defaultOverflowHandler(const RWDecimalOverflowErr<M>& err)
    {
        RWDecimal<M>::defaultOverflowHandler(err);
    }

    static RWCString opAsString(RWDecimalBase::Op op)
    {
        return RWDecimal<M>::opAsString(op);
    }

    // Documented in base class.
    RWFixedDecimal<M> operator-() const
    {
        if (RWDecimal<M>::state_ == RWDecimalBase::SNaNstate) {
            return RWFixedDecimal<M>(RWDecimalBase::NaNstate);
        }
        return (RWFixedDecimal<M>(-this->mantissa_, this->exponent_, this->state_));
    }

    // Documented in base class.
    RWFixedDecimal<M> operator+() const
    {
        if (RWDecimal<M>::state_ == RWDecimalBase::SNaNstate) {
            return RWFixedDecimal<M>(RWDecimalBase::NaNstate);
        }
        return RWFixedDecimal<M>(*this);
    }

    // Assignment operators -------------------------------------------------

    /**
     * Sets value of self equal to the value of the argument.
     */
    RWFixedDecimal<M>& operator=(const RWFixedDecimal<M>& x);

    /**
     * Performs an addition of self and \a a, and stores the result in self.
     */
    RWFixedDecimal<M>& operator+=(const RWFixedDecimal<M>& a)
    {
        *this = *this + a;
        return *this;
    }

    /**
     * Performs a subtraction of \a a from self, and stores the result in
     * self.
     */
    RWFixedDecimal<M>& operator-=(const RWFixedDecimal<M>& a)
    {
        *this = *this - a;
        return *this;
    }

    /**
     * Performs a multiplication of self and \a a, and stores the result in
     * self.
     */
    RWFixedDecimal<M>& operator*=(const RWFixedDecimal<M>& a)
    {
        *this = *this * a;
        return *this;
    }

    /**
     * Performs a division of self by \a a, and stores the result in self.
     */
    RWFixedDecimal<M>& operator/=(const RWFixedDecimal<M>& a)
    {
        *this = *this / a;
        return *this;
    }

    // Documented in base class.
    void saveOn(RWvostream& s) const
    {
        RWDecimal<M>::saveOn(s);
    }

    // Documented in base class.
    void restoreFrom(RWvistream& s)
    {
        RWDecimal<M>::restoreFrom(s);
    }

    // Documented in base class.
    void saveOn(RWFile& f) const
    {
        RWDecimal<M>::saveOn(f);
    }

    // Documented in base class.
    void restoreFrom(RWFile& f)
    {
        RWDecimal<M>::restoreFrom(f);
    }

    // Utility functions ------------------------------------------------------

    // Documented in base class
    static int               maxDigits()
    {
        return M::decimalPrecision();
    }

    // Documented in base class
    static RWFixedDecimal<M> maxValue()
    {
        return RWFixedDecimal<M>(M::maxValue(), 0);
    }

    // Documented in base class
    static RWFixedDecimal<M> minValue()
    {
        return RWFixedDecimal<M>(M::minValue(), 0);
    }

    // Documented in base class
    int             isNumber() const
    {
        return (this->state_ == RWDecimalBase::normal);
    }

    // Documented in base class
    int             decimalPlaces() const
    {
        return (this->state_ == RWDecimalBase::normal ? this->exponent_ : 0);
    }

    // Documented in base class
    static RWFixedDecimal<M>  from(double x)
    {
        return RWDecimal<M>::from(x);
    }

    // Documented in base class
    static RWFixedDecimal<M>  from(long double x)
    {
        return RWDecimal<M>::from(x);
    }

    // GLOBAL FRIEND FUNCTIONS
    // need static class-based ops() methods to call
    static RWFixedDecimal<M> plus(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b,  RWDecimalBase::Op op = RWDecimalBase::assign)
    {
        return RWDecimal<M>::decplus(a, b, op);
    }

    static RWFixedDecimal<M> plus(const RWFixedDecimal<M>& a, const RWDecimal<M>& b,  RWDecimalBase::Op op = RWDecimalBase::assign)
    {
        return RWDecimal<M>::decplus(a, b, op);
    }

    static RWFixedDecimal<M> multiply(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
    {
        return RWDecimal<M>::multiply(a, b);
    }

    static RWFixedDecimal<M> multiply(const RWFixedDecimal<M>& a, const RWDecimal<M>& b)
    {
        return RWDecimal<M>::multiply(a, b);
    }

    static RWFixedDecimal<M> divide(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
    {
        return RWDecimal<M>::divide(a, b);
    }

    static RWFixedDecimal<M> divide(const RWFixedDecimal<M>& a, const RWDecimal<M>& b)
    {
        return RWDecimal<M>::divide(a, b);
    }

    static RWFixedDecimal<M> divide(const RWDecimal<M>& a, const RWFixedDecimal<M>& b)
    {
        return RWDecimal<M>::divide(a, b);
    }

    // global Comparison operators --------------------------------------------
    // Provide them all via a public (undocumented) compare(other) method
    // returns -1, 0, 1 as this is respectively less, equal, greater the other
    int compare(const RWFixedDecimal<M>& c) const
    {
        return this->compare(static_cast<const RWDecimal<M>&>(c));
    }

    int compare(const RWDecimal<M>& c) const
    {
        return
            *static_cast<const RWDecimal<M>*>(this) < c
            ? -1 :
            *static_cast<const RWDecimal<M>*>(this) == c
            ? 0 : 1;
    }

    // Math functions -------------------------------------------------------
    // now static to avoid problems with templates. Global forwarding inlines too.
    static RWFixedDecimal<M> absoluteValue(const RWFixedDecimal<M>& x)
    {
        return RWDecimal<M>::absoluteValue(x);
    }

    /**
     * Returns \a x raised to the exponent \a e. This computation is likely
     * to cause a loss of precision (and a corresponding call to the
     * precision error handler) if e is at all large and \a x has any
     * decimal places.
     */
    static RWFixedDecimal<M> pow(const RWFixedDecimal<M>& x, int e)
    {
        return RWDecimal<M>::power(x, e);
    }

    /**
     * Returns \a x rounded to \a n decimal places. The method of rounding
     * is controlled by the optional last parameter as follows:
     *
     * <b>Table 7: Methods of rounding</b>
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
     * <td>Rounds away from zero on a tie</td>
     * <td>1.3</td>
     * <td>1.4</td>
     * <td>1.3</td>
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
     *
     * The last three columns indicate the result of rounding three example
     * numbers to one decimal place.
     */
    static RWFixedDecimal<M> round(const RWFixedDecimal<M>& x, int n, RWDecimalBase::RoundingMethod rm)
    {
        return RWDecimal<M>::roundDecimal(x, n, rm, 4U);
    }

    static RWFixedDecimal<M> round(const RWFixedDecimal<M>& x, int digits)
    {
        return RWDecimal<M>::roundDecimal(x, digits, RWDecimalBase::PLAIN, 4U);
    }

    static RWCString convertToString(const RWFixedDecimal<M>& d)
    {
        return RWDecimal<M>::convertToString(d);
    }

    static long double convertToDouble(const RWFixedDecimal<M>& d)
    {
        return RWDecimal<M>::convertToDouble(d);
    }

    static long int convertToInt(const RWFixedDecimal<M>& d, RWDecimalBase::RoundingMethod m = RWDecimalBase::PLAIN)
    {
        return RWDecimal<M>::convertToInt(d, m);
    }

    // I/O friend operators ---------------------------------------------------
    // ... are now replaced by static opShift functions called from globals.
    // handle reading (op >>)
    static std::istream& rshift(std::istream& strm, RWFixedDecimal<M>& x)
    {
        return (strm >> (RWDecimal<M>&)x);
    }

    static RWvistream&            rshift(RWvistream& strm, RWFixedDecimal<M>& x)
    {
        return (strm >> (RWDecimal<M>&)x);
    }

    static RWFile&                rshift(RWFile& strm, RWFixedDecimal<M>& x)
    {
        return (strm >> (RWDecimal<M>&)x);
    }

    // handle writing(op <<)
    static std::ostream& lshift(std::ostream& strm, const RWFixedDecimal<M>& x)
    {
        return (strm << (const RWDecimal<M>&)x);
    }

    static RWvostream&            lshift(RWvostream& strm, const RWFixedDecimal<M>& x)
    {
        return (strm << (const RWDecimal<M>&)x);
    }

    static RWFile&                lshift(RWFile& strm, const RWFixedDecimal<M>& x)
    {
        return (strm << (const RWDecimal<M>&)x);
    }

    // Protected constructors -------------------------------------------------
protected:

    RWFixedDecimal(RWDecimalBase::State s)
        : RWDecimal<M>(s)
    {
    }

    // Specify the pieces explicitly
    RWFixedDecimal(const M& m, int e, RWDecimalBase::State s = RWDecimalBase::normal)
        : RWDecimal<M>(m, e, s)
    {
    }

};


// GLOBAL FUNCTION IMPLEMENTATIONS

// Arithmetic operators ---------------------------------------------------

/**
 * \relates RWFixedDecimal
 * Addition operator
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(a, b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator+(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWFixedDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(a, b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator+(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(b, a);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator+(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWFixedDecimal<M>& a, int b)
{
    return RWFixedDecimal<M>::plus(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator+(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator+(const RWFixedDecimal<M>& a, long b)
{
    return RWFixedDecimal<M>::plus(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator+(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator+(int a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(b, RWDecimal<M>(a));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator+(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator+(long a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(b, RWDecimal<M>(a));
}

/**
 * \relates RWFixedDecimal
 * Subtraction operator.
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(a, -b, RWDecimalBase::sub);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator-(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWFixedDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(a, -b, RWDecimalBase::sub);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator-(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(RWFixedDecimal<M>(a), -b, RWDecimalBase::sub);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator-(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWFixedDecimal<M>& a, int b)
{
    return RWFixedDecimal<M>::plus(a, RWDecimal<M>(-b), RWDecimalBase::sub);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator-(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator-(const RWFixedDecimal<M>& a, long b)
{
    return RWFixedDecimal<M>::plus(a, RWDecimal<M>(-b), RWDecimalBase::sub);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator-(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator-(int a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(RWFixedDecimal<M>(a), -b, RWDecimalBase::sub);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator-(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator-(long a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::plus(RWFixedDecimal<M>(a), -b, RWDecimalBase::sub);
}

/**
 * \relates RWFixedDecimal
 * Multiplication operator.
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::multiply(a, b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWFixedDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWFixedDecimal<M>::multiply(a, b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::multiply(b, a);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWFixedDecimal<M>& a, double b)
{
    return RWFixedDecimal<M>::multiply(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(double a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::multiply(b, RWDecimal<M>(a));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWFixedDecimal<M>& a, int b)
{
    return RWFixedDecimal<M>::multiply(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(const RWFixedDecimal<M>& a, long b)
{
    return RWFixedDecimal<M>::multiply(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(int a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::multiply(b, RWDecimal<M>(a));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator*(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator*(long a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::multiply(b, RWDecimal<M>(a));
}

/**
 * \relates RWFixedDecimal
 * Division Operator
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(a, b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWFixedDecimal<M>& a, const RWDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(a, b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(a, b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWFixedDecimal<M>& a, double b)
{
    return RWFixedDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(double a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWFixedDecimal<M>& a, int b)
{
    return RWFixedDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWFixedDecimal<M>& a, long b)
{
    return RWFixedDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(int a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(long a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWFixedDecimal<M>& a, const char* b)
{
    return RWFixedDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const char* a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(RWDecimal<M>(a), b);
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWFixedDecimal<M>& a, const RWDecimalPortable& b)
{
    return RWFixedDecimal<M>::divide(a, RWDecimal<M>(b));
}

/**
 * \relates RWFixedDecimal
 * \copydoc operator/(const RWFixedDecimal<M>&, const RWFixedDecimal<M>&)
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT operator/(const RWDecimalPortable& a, const RWFixedDecimal<M>& b)
{
    return RWFixedDecimal<M>::divide(RWDecimal<M>(a), b);
}

// Comparison operators ---------------------------------------------------

/**
 * \relates RWFixedDecimal
 * The equality operator returns \c true if the two operands are exactly the
 * same, and \c false otherwise.
 */
template< class M >
inline bool RW_DCML_MEMBER_EXPORT operator==(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return 0 == a.compare(b);
}

/**
 * \relates RWFixedDecimal
 * Less than operator. If one (or both) of the operands is #null or
 * #missing, then the result of the operator is undefined.
 */
template< class M >
inline bool RW_DCML_MEMBER_EXPORT operator<(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    if (rwValidCompare(a, b)) {
        return 0 > a.compare(b);
    }
    return false;
}

// Don't provide relational operators if using a C++ Standard Library and
// namespaces are broken, since the definitions below would be redundant.
#if !defined(RWSTD_NO_NAMESPACE)

/**
 * \relates RWFixedDecimal
 * The inequality operator returns \c false if the two operands are exactly
 * the same, and \c true otherwise.
 */
template< class M >
inline bool RW_DCML_MEMBER_EXPORT operator!=(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    return 0 != a.compare(b);
}

/**
 * \relates RWFixedDecimal
 * Greater than operator. If one (or both) of the operands is #null or
 * #missing, then the result of the operator is undefined.
 */
template< class M >
inline bool RW_DCML_MEMBER_EXPORT operator>(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    if (rwValidCompare(a, b)) {
        return 0 < a.compare(b);
    }
    return false;
}

/**
 * \relates RWFixedDecimal
 * Less than or equal to operator. If one (or both) of the operands is #null
 * or #missing, then the result of the operator is undefined.
 */
template< class M >
inline bool RW_DCML_MEMBER_EXPORT operator<=(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    if (rwValidCompare(a, b)) {
        return 0 >= a.compare(b);
    }
    return false;
}

/**
 * \relates RWFixedDecimal
 * Greater than or equal to operator. If one (or both) of the operands is
 * #null or #missing, then the result of the operator is undefined.
 */
template< class M >
inline bool RW_DCML_MEMBER_EXPORT operator>=(const RWFixedDecimal<M>& a, const RWFixedDecimal<M>& b)
{
    if (rwValidCompare(a, b)) {
        return 0 <= a.compare(b);
    }
    return false;
}
#endif // stdlib and namespaces

// I/O operators ----------------------------------------------------------

/**
 * \relates RWFixedDecimal
 * Reads an RWFixedDecimal from an input stream. The format expected is (
 * \c -xxx.yyy) where the \c xxx and \c yyy are integers (which may begin
 * with zeros) and all the parts -- parentheses, minus sign, \c xxx, decimal
 * point, and \c yyy -- are optional. Since we write numbers using base 10,
 * and the RWFixedDecimal class stores numbers using base 10, the number
 * constructed is an exact representation of the input.
 */
template< class M >
inline std::istream& operator>>(std::istream& strm, RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::rshift(strm, x);
}

/**
 * \relates RWFixedDecimal
 * Writes an RWFixedDecimal to an output stream. Output is written in the
 * form \c -xxx.yyy where the \c xxx and \c yyy are integers and only the
 * necessary parts are written. For more elaborate formatting, use an
 * RWDecimalFormat object.
 */
template< class M >
inline std::ostream& operator<<(std::ostream& strm, const RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::lshift(strm, x);
}

template< class M >
inline RWvostream& operator<<(RWvostream& strm, const RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::lshift(strm, x);
}

template< class M >
inline RWvistream& operator>>(RWvistream& strm, RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::rshift(strm, x);
}

template< class M >
inline RWFile& operator>>(RWFile& strm, RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::rshift(strm, x);
}

template< class M >
inline RWFile& operator<<(RWFile& strm, const RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::lshift(strm, x);
}

//  Math functions --------------------------------------------------------

// xlC of some vintage refuses default args in template functions
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::round(x, 0, RWDecimalBase::PLAIN);
}

// xlC of some vintage refuses default args in template functions
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWFixedDecimal<M>& x, int digits)
{
    return RWFixedDecimal<M>::round(x, digits, RWDecimalBase::PLAIN);
}

// xlC of some vintage refuses default args in template functions
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT round(const RWFixedDecimal<M>& x, int digits, RWDecimalBase::RoundingMethod rm)
{
    return RWFixedDecimal<M>::round(x, digits, rm);
}

template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT pow(const RWFixedDecimal<M>& x, int e)
{
    return RWFixedDecimal<M>::pow(x, e);
}

/**
 * \relates RWFixedDecimal
 * Returns the absolute value of \a x.
 */
template< class M >
inline RWFixedDecimal<M> RW_DCML_MEMBER_EXPORT abs(const RWFixedDecimal<M>& x)
{
    return RWFixedDecimal<M>::absoluteValue(x);
}


// Narrowing global conversion functions ----------------------------------

/**
 * \relates RWFixedDecimal
 * Converts an RWFixedDecimal to a string. The string has the form
 * \c xxx.yyy where the \c xxx and \c yyy are integers and only the parts
 * necessary are written. For more elaborate formatting, use an
 * RWDecimalFormat object.
 */
template< class M >
inline RWCString RW_DCML_MEMBER_EXPORT toString(const RWFixedDecimal<M>& d)
{
    return RWFixedDecimal<M>::convertToString(d);
}

/**
 * \relates RWFixedDecimal
 * Converts the argument to a double precision value close to its true
 * value.
 */
template< class M >
inline long double RW_DCML_MEMBER_EXPORT toDouble(const RWFixedDecimal<M>& d)
{
    return RWFixedDecimal<M>::convertToDouble(d);
}

/**
 * \relates RWFixedDecimal
 * Converts the argument to an integer. The method of rounding used is
 * RWDecimalBase::PLAIN, as described in detail in the description of the
 * global function round().
 */
template< class M >
inline long int RW_DCML_MEMBER_EXPORT toInt(const RWFixedDecimal<M>& d)
{
    return RWFixedDecimal<M>::convertToInt(d, RWDecimalBase::PLAIN);
}

/**
 * \relates RWFixedDecimal
 * Converts the argument to an integer. The method of rounding is controlled
 * by the last parameter, as described in detail in the description of the
 * global function round().
 */
template< class M >
inline long int RW_DCML_MEMBER_EXPORT toInt(const RWFixedDecimal<M>& d, RWDecimalBase::RoundingMethod m)
{
    return RWFixedDecimal<M>::convertToInt(d, m);
}

RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWFixedDecimal< RWMultiPrecisionInt<1> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWFixedDecimal< RWMultiPrecisionInt<2> >);
RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWFixedDecimal< RWMultiPrecisionInt<3> >);

// These exact match operators are provided to prevent
// ambiguities involving the the conversion operator
// to decport operators

// operator ==
template <class M>
inline bool operator==(const RWFixedDecimal<M>& x, const RWCString& y)
{
    return x == RWFixedDecimal<M>(y);
}

template <class M>
inline bool operator==(const RWCString& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWFixedDecimal<M>& y, const RWDecimalPortable& x)
{
    return (y == RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator==(const RWDecimalPortable& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWFixedDecimal<M>& y, const char* x)
{
    return (y == RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator==(const char* x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWFixedDecimal<M>& y, const long& x)
{
    return (y == RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator==(const long& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) == y;
}

template <class M>
inline bool operator==(const RWFixedDecimal<M>& y, const int& x)
{
    return (y == RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator==(const int& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) == y;
}


// operator <
template <class M>
inline bool operator<(const RWFixedDecimal<M>& x, const RWCString& y)
{
    return x < RWFixedDecimal<M>(y);
}

template <class M>
inline bool operator<(const RWCString& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWFixedDecimal<M>& y, const RWDecimalPortable& x)
{
    return (y < RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator<(const RWDecimalPortable& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWFixedDecimal<M>& y, const char* x)
{
    return y < RWFixedDecimal<M>(x);
}

template <class M>
inline bool operator<(const char* x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWFixedDecimal<M>& y, const long& x)
{
    return (y < RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator<(const long& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) < y;
}

template <class M>
inline bool operator<(const RWFixedDecimal<M>& y, const int& x)
{
    return (y < RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator<(const int& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) < y;
}



// operator >
template <class M>
inline bool operator>(const RWFixedDecimal<M>& x, const RWCString& y)
{
    return x > RWFixedDecimal<M>(y);
}

template <class M>
inline bool operator>(const RWCString& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWFixedDecimal<M>& y, const RWDecimalPortable& x)
{
    return (y > RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator>(const RWDecimalPortable& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWFixedDecimal<M>& y, const char* x)
{
    return y > RWFixedDecimal<M>(x);
}

template <class M>
inline bool operator>(const char* x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWFixedDecimal<M>& y, const long& x)
{
    return (y > RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator>(const long& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) > y;
}

template <class M>
inline bool operator>(const RWFixedDecimal<M>& y, const int& x)
{
    return (y > RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator>(const int& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) > y;
}

// operator >=
template <class M>
inline bool operator>=(const RWFixedDecimal<M>& x, const RWCString& y)
{
    return x >= RWFixedDecimal<M>(y);
}

template <class M>
inline bool operator>=(const RWCString& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWFixedDecimal<M>& y, const RWDecimalPortable& x)
{
    return (y >= RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator>=(const RWDecimalPortable& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWFixedDecimal<M>& y, const char* x)
{
    return y >= RWFixedDecimal<M>(x);
}

template <class M>
inline bool operator>=(const char* x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWFixedDecimal<M>& y, const long& x)
{
    return (y >= RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator>=(const long& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) >= y;
}

template <class M>
inline bool operator>=(const RWFixedDecimal<M>& y, const int& x)
{
    return (y >= RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator>=(const int& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) >= y;
}

// operator <=
template <class M>
inline bool operator<=(const RWFixedDecimal<M>& x, const RWCString& y)
{
    return x <= RWFixedDecimal<M>(y);
}

template <class M>
inline bool operator<=(const RWCString& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWFixedDecimal<M>& y, const RWDecimalPortable& x)
{
    return (y <= RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator<=(const RWDecimalPortable& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWFixedDecimal<M>& y, const char* x)
{
    return y <= RWFixedDecimal<M>(x);
}

template <class M>
inline bool operator<=(const char* x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWFixedDecimal<M>& y, const long& x)
{
    return (y <= RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator<=(const long& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) <= y;
}

template <class M>
inline bool operator<=(const RWFixedDecimal<M>& y, const int& x)
{
    return (y <= RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator<=(const int& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) <= y;
}

// operator !=
template <class M>
inline bool operator!=(const RWFixedDecimal<M>& x, const RWCString& y)
{
    return x != RWFixedDecimal<M>(y);
}

template <class M>
inline bool operator!=(const RWCString& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWFixedDecimal<M>& y, const RWDecimalPortable& x)
{
    return (y != RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator!=(const RWDecimalPortable& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWFixedDecimal<M>& y, const char* x)
{
    return y != RWFixedDecimal<M>(x);
}

template <class M>
inline bool operator!=(const char* x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWFixedDecimal<M>& y, const long& x)
{
    return (y != RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator!=(const long& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) != y;
}

template <class M>
inline bool operator!=(const RWFixedDecimal<M>& y, const int& x)
{
    return (y != RWFixedDecimal<M>(x)) != 0;
}

template <class M>
inline bool operator!=(const int& x, const RWFixedDecimal<M>& y)
{
    return RWFixedDecimal<M>(x) != y;
}


#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/fixeddec.cc>
#endif

#endif  // RW_CURRENCY_FIXEDDEC_H
