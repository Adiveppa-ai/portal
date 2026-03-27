#ifndef __rw_internet_util_h__
#define __rw_internet_util_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/util.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 *************************************************************************/

#include <rw/internet/pkgdefs.h>
#include <rw/network/RWInetAddr.h>
#include <rw/cstring.h>

/*
 * Utility functions for Tools.h++ Professional
 *
 */

/*
 * rwNormalizeLine(RWCString text)
 *
 * rwNormalizeLine function removes CR and LF characters embedded in
 * an RWCString, and returns the normalized RWCString
 *
 */

/**
 * \ingroup internet_basics_package
 *
 * \headerfileloc{#include <rw/internet/util.h>}
 *
 * Returns the \a text argument normalized by removing \c \<cr\>\<lf\>
 * characters embedded in an RWCString.
 */
RW_INTERNET_SYMBOLIC RWCString rwNormalizeLine(const RWCString& text);

/*
 * rwDecodeString(RWCString s)
 *
 * rwDecodeString function returns a decoded RWCString.
 */

RW_INTERNET_SYMBOLIC RWCString rwDecodeString(const RWCString& s);

/*
 * rwAddPeriods(RWCString)
 *
 * SMTP requires that <newline><period> be sent as
 * <newline><period><period>. This function doubles any leading
 *  period in the input string, and any period immediately
 * following a newline (any type).
 */

/**
 * \ingroup internet_basics_package
 *
 * Returns a copy of \a line that replaces all leading periods following any
 * newline character with two periods. This is a convenience function that
 * you can use to reverses the encoding used by SMTP clients to transmit
 * objects over the SMTP protocol. The RWCString should contain 7-bit
 * US-ASCII data.
 *
 * \headerfileloc{#include <rw/internet/util.h>}
 */
RW_INTERNET_SYMBOLIC RWCString rwAddPeriods(const RWCString& line);

/*
 * rwRemovePeriods(RWCString)
 *
 * POP3 ships data with a period doubled if it immediately follows a
 * newline character sequence. This function looks for double periods
 * at the front of the string, or after any newline and removes one
 * period from any such sequence
 *
 */

/**
 * \ingroup internet_basics_package
 *
 * Returns a copy of \a line that replaces all leading double periods and
 * double periods following any newline character with single periods. This
 * is a convenience function that you can use to undo the encoding used by
 * POP3 servers to transmit objects over the SMTP protocol. The RWCString
 * should contain 7-bit US-ASCII data.
 *
 * \headerfileloc{#include <rw/internet/util.h>}
 */
RW_INTERNET_SYMBOLIC RWCString rwRemovePeriods(const RWCString& line);

/**
 * \ingroup internet_basics_package
 *
 * Returns \a addrString converted to RWInetAddr format. The RWCString
 * should contain 7-bit US-ASCII data.
 *
 * \headerfileloc{#include <rw/internet/util.h>}
 */
RW_INTERNET_SYMBOLIC RWInetAddr rwFtpStringToAddr(const RWCString& addrString);

/**
 * \ingroup internet_basics_package
 *
 * Returns \a addr converted to RWCString format. The RWCString should
 * contain 7-bit US-ASCII data.
 *
 * \headerfileloc{#include <rw/internet/util.h>}
 */
RW_INTERNET_SYMBOLIC RWCString rwFtpAddrToString(const RWInetAddr& addr);

#endif // __rw_internet_util_h__
