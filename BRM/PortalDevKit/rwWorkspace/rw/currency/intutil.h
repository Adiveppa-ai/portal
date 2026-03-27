#ifndef RW_CURRENCY_INTUTIL_H
#define RW_CURRENCY_INTUTIL_H

/*--------------------------------------------------------------
 *
 * Utility functions used by RWMultiPrecisionInt
 *
 * $Id: //spro/rel2016.1/rw/currency/intutil.h#1 $
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
#ifndef RW_MONEY_INTUTIL_H
#  define RW_MONEY_INTUTIL_H
#endif

#include <rw/currency/decdefs.h>
#include <rw/currency/utlconst.h>    // for RWIntutilConstants<T> constants
#include <rw/dcmldefs.h>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <math.h>
#else
#  include <cmath>
#endif        // for pow()

//
// Global function prototypes found in intutil.cc
//
template <class T>
void printAsBinary(const T* digits, const size_t numDigits);

template <class T>
unsigned int decimalShiftRight(T* hw_array, unsigned int hw_arraysize, unsigned int nshift);

template <class T>
unsigned int decimalShiftRightToHalfSize(T* hw_array, unsigned int hw_arraysize, unsigned int nshift);


//
// RWHalfwordSplit: splits a zero-referenced array of words into
// an array of halfwords.  Works only on nonnegative numbers.
//
// Note: the parameter *S* refers to the size of the *word* array.
// Calling form: RWHalfwordSplit<DigitType,S-1>::split(arr_n,arr_2n);
//
template <class T, int N>
class RWHalfwordSplit
{
public:
    static inline void split(const T* arr_n, T* arr_2n)
    {
        arr_2n[2 * N]   = arr_n[N] >> RWIntutilConstants<T>::HWDigitSize;
        arr_2n[2 * N + 1] = arr_n[N] &  RWIntutilConstants<T>::LowerMask;
        RWHalfwordSplit < T, N - 1 >::split(arr_n, arr_2n);
    };
};

// Base cases for the recursion
template <class T>
class RWHalfwordSplit<T, -1>
{
public:
    static inline void split(const T*, T*)
    { }
};


//
// RWHalfwordSplitReverse: splits a zero-referenced array of words into
// an array of halfwords, but puts the halfwords in reverse order (for
// simplifying a multiplication algorithm).  Works only on nonnegative
// numbers.
//
// Note: this should always be called with the first two parameters only.
//       In the call, *S* refers to the size of the *word* array.
// Calling form: RWHalfwordSplitReverse<DigitType,S-1>::split(arr_n,arr_2n);
//
template <class T, int N>
class RWHalfwordSplitReverse
{
public:
    static inline void split(const T* arr_n, T* arr_2n, size_t size = N + 1)
    {
        arr_2n[2 * N]   = arr_n[size - 1 - N] &  RWIntutilConstants<T>::LowerMask;
        arr_2n[2 * N + 1] = arr_n[size - 1 - N] >> RWIntutilConstants<T>::HWDigitSize;
        RWHalfwordSplitReverse < T, N - 1 >::split(arr_n, arr_2n, size);
    };
};

// Base cases for the recursion
template <class T>
class RWHalfwordSplitReverse<T, -1>
{
public:
    static inline void split(const T*, T*, size_t = 0)
    { }
};


//
// RWHalfwordPropagate: propagates carries in a halfword array, so that
// a subsequent merge from halfwords to words can be performed without
// loss of carry information.  The number represented must be nonnegative.
//
// Note: The parameter *S* refers to the size of a *word* array;
//       if array has length 2*S, call is made with parameter (2*S-2).
// Calling form: RWHalfwordPropagate<DigitType,2*S-2>::propagate(array);
//
template <class T, int N>
class RWHalfwordPropagate
{
public:
    static inline void propagate(T* array)
    {
        array[N]   += array[N + 1] >> RWIntutilConstants<T>::HWDigitSize;
        array[N + 1] &= RWIntutilConstants<T>::LowerMask;
        RWHalfwordPropagate < T, N - 1 >::propagate(array);
    };
};

// Base cases for the recursion
template <class T>
class RWHalfwordPropagate<T, -1>
{
public:
    static inline void propagate(const T*)
    { }
};


//
// RWHalfwordMerge: merges a zero-referenced array of halfwords into
// an array of words.  Works only on nonnegative numbers.
//
// Note: the template parameter *S* refers to the size of the *word* array.
// Calling form: RWHalfwordMerge<DigitType,S-1>::merge(arr_2n,arr_n);
//
template <class T, int N>
class RWHalfwordMerge
{
public:
    static inline void merge(const T* arr_2n, T* arr_n)
    {
        arr_n[N] = (arr_2n[2 * N] << RWIntutilConstants<T>::HWDigitSize) |
                   (arr_2n[2 * N + 1] & RWIntutilConstants<T>::LowerMask);
        RWHalfwordMerge < T, N - 1 >::merge(arr_2n, arr_n);
    };
};

// Base cases for the recursion
template <class T>
class RWHalfwordMerge<T, -1>
{
public:
    static inline void merge(const T*, T*)
    { }
};


//
// RWArrayCopy: copies one array to another.
//
// Note: here, *S* refers to the size of the array.
// Calling form: RWArrayCopy<DigitType,S-1>::copy(source,result);
//
template <class T, int N>
class RWArrayCopy
{
public:
    static inline void copy(const T* source, T* result)
    {
        result[N] = source[N];
        RWArrayCopy < T, N - 1 >::copy(source, result);
    };
};

// Base cases for the recursion
template <class T>
class RWArrayCopy<T, -1>
{
public:
    static inline void copy(const T*, T*)
    { }
};


//
// RWHalfwordInit: initializes each element in a zero-referenced array of
// halfwords with a given value.
//
// Note: here, *S* refers to the size of a *word* array.
// Calling form: RWHalfwordInit<DigitType,2*S-1>::init(array,value);
//
template <class T, int N>
class RWHalfwordInit
{
public:
    static inline void init(T* array, const T value)
    {
        array[N] = value;
        RWHalfwordInit < T, N - 1 >::init(array, value);
    };
};

// Base cases for the recursion
template <class T>
class RWHalfwordInit<T, -1>
{
public:
    static inline void init(T*, const T)
    { }
};


//
// RWDigitAdd: adds two wholeword arrays and puts result into a third array.
// Returns overflow status.
//
// Note: this function should be called with the first three parameters only.
// Calling form: RWDigitAdd<DigitType,S-1>::add(op1,op2,result);
//
template <class T, int N>
class RWDigitAdd
{
public:
    static inline int add(const T* op1, const T* op2, T* result, int carry = 0)
    {
        T res = op1[N] + op2[N] + carry;  // use *res* in case result=(op1 or op2)
        if ((res <= op1[N] && op2[N] != 0) ||
                (res <= op2[N] && op1[N] != 0)) {
            carry = 1;
        }
        else {
            carry = 0;
        }
        result[N] = res;
        return (RWDigitAdd < T, N - 1 >::add(op1, op2, result, carry));
    };
};

// Base cases for the recursion
template <class T>
class RWDigitAdd<T, -1>
{
public:
    static inline int add(const T*, const T*, T*, int carry = 0)
    {
        return (carry);
    }
};


//
// RWHalfwordAdd: adds two zero-referenced halfword arrays and puts
// result into a third array.
//
// Note: this should be called with the first three parameters only; here,
//       *S* is the size of a *word* array.
// Calling form: RWHalfwordAdd<DigitType,2*S-1>::add(op1,op2,result);
//
template <class T, int N>
class RWHalfwordAdd
{
public:
    static inline bool add(const T* op1, const T* op2, T* result, T remainder = 0)
    {
        remainder += op1[N] + op2[N];
        result[N] = remainder & RWIntutilConstants<T>::LowerMask;
        remainder >>= RWIntutilConstants<T>::HWDigitSize;
        return (RWHalfwordAdd < T, N - 1 >::add(op1, op2, result, remainder));
    };
};

// Base cases for the recursion.
template <class T>
class RWHalfwordAdd<T, -1>
{
public:
    static inline bool add(const T*, const T*, T*, T remainder = 0)
    {
        return (remainder != 0);
    }
};


//
// RWHalfwordSubtract: subtracts two zero-referenced halfword
// arrays and puts result into a third array. Works only for two nonnegative
// operands.
//
// Note: this function should always be called with three parameters only.
//       In the calling notation, *S* refers to the size of a *word* array.
// Calling form: RWHalfwordSubtract<DigitType,2*S-1>::subtract(op1,op2,result);
//
template <class T, int N>
class RWHalfwordSubtract
{
public:
    // some compilers don't allow template expressions as default parameters;
    // hence an extra definition.
    static inline bool subtract(const T* op1, const T* op2, T* result)
    {
        return (subtract(op1, op2, result, RWIntutilConstants<T>::HWBorrowBit));
    }
    static inline bool subtract(const T* op1, const T* op2, T* result, T borrow)
    {
        borrow = RWIntutilConstants<T>::LowerMask + op1[N] - op2[N] +
                 (borrow >> RWIntutilConstants<T>::HWDigitSize);
        result[N] = borrow & RWIntutilConstants<T>::LowerMask;
        return (RWHalfwordSubtract < T, N - 1 >::subtract(op1, op2, result, borrow));
    }
};

// Base cases for the recursion; return true if subtraction went negative.
template <class T>
class RWHalfwordSubtract<T, -1>
{
public:
    static inline bool subtract(const T*, const T*, T*, T borrow)
    {
        return borrow < RWIntutilConstants<T>::HWBorrowBit;
    }
};


// RWHalfwordShiftRight: shift right a zero-referenced halfword array, so
// that the padded-zero areas in each digit are ignored.  Used by the
// MPInt division algorithm.  This algorithm works only if
// the amount to shift does not exceed the number of bits in a halfword.
//
// Note: the function should be called with the first two parameters only.
//       In the calling notation, *S* refers to the size of a *word* array.
// Calling form: RWHalfwordShiftLeft<DigitType,2*S-1>::left(shiftBy,array);
//
template <class T, int N>
class RWHalfwordShiftRight
{
public:
    static inline void right(const size_t shiftBy, T* array)
    {
        array[N] >>= shiftBy;
        array[N]  |= (array[N - 1] << (RWIntutilConstants<T>::HWDigitSize - shiftBy)) &
                     RWIntutilConstants<T>::LowerMask;
        RWHalfwordShiftRight < T, N - 1 >::right(shiftBy, array);
    }
};

// Base cases for the recursion.
template <class T>
class RWHalfwordShiftRight<T, 0>
{
public:
    static inline void right(const size_t shiftBy, T* array)
    {
        array[0] >>= shiftBy;
    }
};


// RWHalfwordShiftLeft: shift left a zero-referenced halfword array, so
// that the padded-zero areas in each digit are ignored.  Used by the
// MPInt division algorithm.  This algorithm works only if
// the amount to shift does not exceed the number of bits in a halfword.
//
// Note: the function should be called with the first two parameters only.
//       In the calling notation, *S* refers to the size of a *word* array.
// Calling form: RWHalfwordShiftLeft<DigitType,2*S-1>::left(shiftBy,array);
//
template <class T, int N>
class RWHalfwordShiftLeft
{
public:
    static inline void left(const size_t shiftBy, T* array, size_t maxindex = N)
    {
        array[maxindex - N]  = (array[maxindex - N] << shiftBy) & RWIntutilConstants<T>::LowerMask;
        array[maxindex - N] |= array[maxindex - N + 1] >> (RWIntutilConstants<T>::HWDigitSize - shiftBy);
        RWHalfwordShiftLeft < T, N - 1 >::left(shiftBy, array, maxindex);
    }
};

// Base cases for the recursion.
template <class T>
class RWHalfwordShiftLeft<T, 0>
{
public:
    static inline void left(const size_t shiftBy, T* array, size_t maxindex = 0)
    {
        array[maxindex] = (array[maxindex] << shiftBy) & RWIntutilConstants<T>::LowerMask;
    }
};


// RWHalfwordMultiply: multiplies a zero-indexed halfword array by a halfword
// value.  Used by the MPInt division algorithm; works only on nonnegative
// values.  Returns carry-out from most significant digit.
//
// Note: This function should be called with the first three parameters only;
//       in the calling form, *S* refers to the typical size of a *word* array.
// Calling form: RWHalfwordMultiply<DigitType, 2*S-1>::multiply(array,value,result);
//
template <class T, int N>
class RWHalfwordMultiply
{
public:
    static inline T multiply(const  T* array, T value, T* result, T carry = 0)
    {
        carry += array[N] * value;
        result[N] = carry & RWIntutilConstants<T>::LowerMask;
        carry >>= RWIntutilConstants<T>::HWDigitSize;
        return (RWHalfwordMultiply < T, N - 1 >::multiply(array, value, result, carry));
    }
};

// Base cases for the recursion.
template <class T>
class RWHalfwordMultiply<T, -1>
{
public:
    static inline T multiply(const T*, T, T*, T carry = 0)
    {
        return carry;
    }
};


//
// RWIntToDouble: converts a multiple precision integer to a double
// precision value.  Works only for nonnegative numbers.  Algorithm
// works from least significant to most significant digit; it
// multiplies each digit by its appropriate power of two before adding in
// its contribution.
//
// Note: this function should always be called with the first parameter only.
// Calling form: RWIntToDouble<DigitType,S-1>::todouble(array);
//
template <class T, int N>
class RWIntToDouble
{
public:
    static inline double todouble(const T* array, double value = 0.0, size_t ndigits = N)
    {
        // Convert this value to double by recursively calculating the decimal value
        // of each halfword, starting with the most significant. We multiply by
        // MaxDigitInt + 1 (which represents pow(2,X), where X is the "bitness" of
        // the current platform) each time, which conceptually shifts the calculated
        // halfwords to the left each time. In this way, we never have to multiply by
        // anything other than pow(2,X), (and thus don't have to directly call pow()
        // which is slower [and less accurate on HP-UX 10.20] than multiplication).
        //
        return (RWIntToDouble < T, N - 1 >::todouble(array, value, ndigits) *
                ((double)RWIntutilConstants<T>::MaxDigitInt + 1) + array[N]);
    };
};

// Base cases for the recursion.
template <class T>
class RWIntToDouble<T, -1>
{
public:
    static inline double todouble(const T*, double value, size_t)
    {
        return (value);
    }
};


// RWDigitNegate: negates a wholeword array and puts result into a second array.
// Returns overflow status.
//
// Note: this function should be called with the first two parameters only.
// Calling form: RWDigitNegate<DigitType,S-1>::negate(op1,result);
//
template <class T, int N>
class RWDigitNegate
{
public:
    static inline int negate(const T* op1, T* result, int carry = 1)
    {
        T res = (RWIntutilConstants<T>::MaxDigitInt - op1[N]);
        res += T(carry);
        if (res == T(0) &&  carry == 1) {
            carry = 1;
        }
        else {
            carry = 0;
        }
        result[N] = res;
        return (RWDigitNegate < T, N - 1 >::negate(op1, result, carry));
    };
};

// Base cases for the recursion
template <class T>
class RWDigitNegate<T, -1>
{
public:
    static inline int negate(const T*, T*, int carry)
    {
        return (carry);
    }
};


// RWMPIntEqual: returns true if two arrays of type T represent the same
// integer, i.e., if corresponding elements in the arrays are equal.
//
// Calling form: RWMPIntEqual<DigitType,S-1>::equal(lhs,rhs);
//
template< class T, int N >
class RWMPIntEqual
{
public:
    static inline bool equal(const T* lhs, const T* rhs)
    {
        bool result;
        if (lhs[N] != rhs[N]) {
            result = false;
        }
        else {
            result = RWMPIntEqual < T, N - 1 >::equal(lhs, rhs);
        }
        return result;
    }
};

// Base cases for the recursion.
template <class T>
class RWMPIntEqual<T, -1>
{
public:
    static inline bool equal(const T*, const T*)
    {
        return true;
    }
};


// RWIndexOfLastNonZero: Used by the MPInt multiplication algorithm to
// avoid unnecessary multiplies by zero.  When passed an ordinal array
// of type T, it returns the index of the least significant nonzero value.
//
// Calling form: RWIndexOfLastNonZero<DigitType,2*S-1>::index(array);
//
template< class T, int N >
class RWIndexOfLastNonZero
{
public:
    static inline size_t index(const T* array)
    {
        size_t result;
        if (array[N] != T(0)) {
            result = N;
        }
        else {
            result = RWIndexOfLastNonZero < T, N - 1 >::index(array);
        }
        return result;
    }
};

// Base cases for the recursion.
template <class T>
class RWIndexOfLastNonZero<T, -1>
{
public:
    static inline size_t index(const T*)
    {
        return RW_NPOS;
    }
};


// RWIndexOfFirstDiff: Returns the index of the first place the two
// arrays differ.
//
// Calling form: RWIndexOfFirstDiff<DigitType,2*S-1>::index(array1, array2);
//
template< class T, int N >
class RWIndexOfFirstDiff
{
public:
    static inline size_t index(const T* array1, const T* array2, size_t index = RW_NPOS)
    {
        if (array1[N] != array2[N]) {
            index = N;
        }
        return RWIndexOfFirstDiff < T, N - 1 >::index(array1, array2, index);
    }
};

// Base cases for the recursion.
template <class T>
class RWIndexOfFirstDiff<T, -1>
{
public:
    static inline size_t index(const T*, const T*, size_t index)
    {
        return index;
    }
};


#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/intutil.cc>
#endif

#endif // RW_CURRENCY_INTUTIL_H
