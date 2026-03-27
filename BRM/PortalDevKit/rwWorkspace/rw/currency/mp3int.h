#ifndef RW_CURRENCY_MP3INT_H
#define RW_CURRENCY_MP3INT_H

/*--------------------------------------------------------------
 *
 * Type definition for RWMP3Int.
 *
 * $Id: //spro/rel2016.1/rw/currency/mp3int.h#1 $
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
#ifndef RW_MONEY_MP3INT_H
#  define RW_MONEY_MP3INT_H
#endif

#include <rw/currency/mpint.h>

/**
 * \ingroup currency_decimal_numbers_group
 *
 * Convenience typedef for integer with 28 digit precision.
 */
typedef RWMultiPrecisionInt<3> RWMP3Int;

RWDCML_INSTANTIATE_1(class RW_DCML_GLOBAL RWMultiPrecisionInt<3>);

#endif // RW_CURRENCY_MP3INT_H
