#ifndef RW_CURRENCY_UTLCONST_H
#define RW_CURRENCY_UTLCONST_H

/*--------------------------------------------------------------
 *
 * Definition of constants used by RWMultiPrecisionInt
 *
 * $Id: //spro/rel2016.1/rw/currency/utlconst.h#1 $
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

#include <rw/currency/decdefs.h>
#include <rw/dcmldefs.h>

// Constants used by template metaprograms and multiple integer class.
template <class T>
class RWIntutilConstants
{
public:
 static const size_t HWDigitSize;
 static const T LowerMask;
 static const T UpperMask;
 static const T HWBorrowBit;
 static const T MaxDigitInt;
 static const T LowDigitBit;
 static const T HighDigitBit;
};


#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/utlconst.cc>
#endif

#endif // RW_CURRENCY_UTLCONST_H
