#ifndef RW_CURRENCY_MPPOT_H
#define RW_CURRENCY_MPPOT_H

/******************************************************************************
 *
 * RWMPPowersOfTen< int S >
 *
 * This class stores a static array of RWMultiPrecision int's (mp
 * ints)representing the powers of ten.  If using mp ints in decimal
 * calculations it is frequently necessary to shift an mp int either
 * right or left by a certain number of decimal digits.  One fairly
 * efficient way of doing this is to divide or multiply the number by
 * the appropriate power of ten.
 *
 * $Id: //spro/rel2016.1/rw/currency/mppot.h#1 $
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
 ******************************************************************************/

/* for backward compatibility */
#ifndef RW_MONEY_MPPOT_H
#  define RW_MONEY_MPPOT_H
#endif

#include <rw/currency/mpint.h>
#include <rw/dcmldefs.h>
#include <rw/mutex.h>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <limits.h>
#  include <math.h>
#else
#  include <climits>
#  include <cmath>
#endif


template <int S>
struct RWNumPow10;

#define RW_NUMPOW_10(x, y) \
template <> \
struct RWNumPow10<x> { \
    static const unsigned value = y; \
}

RW_NUMPOW_10(1, 10);
RW_NUMPOW_10(2, 19);
RW_NUMPOW_10(3, 29);
RW_NUMPOW_10(4, 39);
RW_NUMPOW_10(5, 48);
RW_NUMPOW_10(6, 58);
RW_NUMPOW_10(7, 68);
RW_NUMPOW_10(8, 77);
RW_NUMPOW_10(9, 87);
RW_NUMPOW_10(10, 97);
RW_NUMPOW_10(11, 106);
RW_NUMPOW_10(12, 116);
RW_NUMPOW_10(13, 125);
RW_NUMPOW_10(14, 135);
RW_NUMPOW_10(15, 145);
RW_NUMPOW_10(16, 154);
#undef RW_NUMPOW_10

template< int S >
class RWMPPowersOfTen
{
public:
    static RWMultiPrecisionInt<S> power(size_t n)
    {
        if (powerIsInitialized) {
            return powers[n];
        }
        RW_MT_LOCK_GUARD(RWStaticFastMutex, powersOfTenLock);

        if (! powerIsInitialized) {
            const RWMultiPrecisionInt<S> ten = 10;
            const unsigned numP = numPowers();
            powers[0] = RWMultiPrecisionInt<S>(1);
            for (unsigned i = 1; i < numP; ++i) {
                powers[i] = powers[i - 1] * ten;
            }
            powerIsInitialized = true;
        }
        return powers[n];
    }

    static unsigned numPowers()
    {
        return RWNumPow10<S>::value;
    }
private:
    static bool powerIsInitialized;
    static RWStaticFastMutex powersOfTenLock;
    static RWMultiPrecisionInt<S> powers[RWNumPow10<S>::value];
};

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/mppot.cc>
#endif

#endif  // RW_CURRENCY_MPPOT_H
