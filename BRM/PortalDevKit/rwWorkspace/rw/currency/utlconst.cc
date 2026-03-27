#ifndef RW_CURRENCY_UTLCONST_CC
#define RW_CURRENCY_UTLCONST_CC

/*--------------------------------------------------------------
 *
 * Initialization of constants used by RWMultiPrecisionInt
 *
 * $Id: //spro/rel2016.1/rw/currency/utlconst.cc#1 $
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
#ifndef RW_MONEY_UTLCONST_CC
#  define RW_MONEY_UTLCONST_CC
#endif

template <class T>
const size_t RWIntutilConstants<T>::HWDigitSize = sizeof(T) * CHAR_BIT / 2;

template <class T>
const T RWIntutilConstants<T>::LowerMask = T(~(T(~0) << RWIntutilConstants<T>::HWDigitSize));

template <class T>
const T RWIntutilConstants<T>::UpperMask = T(T(~0) << RWIntutilConstants<T>::HWDigitSize);

template <class T>
const T RWIntutilConstants<T>::HWBorrowBit = T(T(1) << RWIntutilConstants<T>::HWDigitSize);

template <class T>
const T RWIntutilConstants<T>::MaxDigitInt = T(~0);

template <class T>
const T RWIntutilConstants<T>::LowDigitBit = T(1);

template <class T>
const T RWIntutilConstants<T>::HighDigitBit = T(RWIntutilConstants<T>::LowDigitBit << (sizeof(T) * CHAR_BIT - 1));

#endif // RW_CURRENCY_UTLCONST_CC
