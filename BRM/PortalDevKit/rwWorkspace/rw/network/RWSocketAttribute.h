#ifndef __rw_network_RWSocketAttribute_h__
#define __rw_network_RWSocketAttribute_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSocketAttribute.h#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

#include <rw/network/RWSocket.h>
#include <rw/network/RWTSocketAttribute.h>
#include <rw/network/pkgdefs.h>
#include <rw/tvordvec.h>

/**
 * \ingroup networking_module
 *
 * This is a typedef for
 * \ref RWTSocketAttribute "RWTSocketAttribute<RWSocket>".
 *
 * \sa
 * rwSocketSelect()
 */
typedef RWTSocketAttribute<RWSocket> RWSocketAttribute;

/**
 * \ingroup networking_module
 *
 * This function helps to perform asynchronous socket input/output
 * operations. It waits for one of the conditions in the user-defined
 * attributes vector to occur, and returns a vector of the conditions that
 * have occurred. If any of the conditions has already occurred when the
 * function is called, it returns immediately.
 *
 * The \a attributes parameter is a vector of socket attributes. If empty,
 * the program may sleep indefinitely. If one of the attributes refers to an
 * invalid socket, a RWNetInvalidSocketError exception is thrown. If more
 * than \c FD_SETSIZE attributes are in the attributes vector, an exception
 * is thrown.
 *
 * \note
 * On stream sockets that are not connected, this function returns
 * RWSocketAttribute::sock_attr_canwrite. This is a known issue with the
 * underlying \b select() function.
 */
RW_NETWORK_SYMBOLIC RWTValOrderedVector<RWSocketAttribute>
rwSocketSelect(const RWTValOrderedVector<RWSocketAttribute>& attributes);

/**
 * \ingroup networking_module
 *
 * This function helps to perform asynchronous socket input/output
 * operations. It waits for one of the conditions in the user-defined
 * attributes vector to occur, and returns a vector of the conditions that
 * have occurred. If any of the conditions has already occurred when the
 * function is called, it returns immediately.
 *
 * The \a attributes parameter is a vector of socket attributes. If empty,
 * the program may sleep indefinitely. If one of the attributes refers to an
 * invalid socket, a RWNetInvalidSocketError exception is thrown. If more
 * than \c FD_SETSIZE attributes are in the attributes vector, an exception
 * is thrown.
 *
 * The \a timeout parameter is the maximum amount of time, in seconds, to
 * wait for one of the conditions to become true. If the the value is
 * negative, this function may block indefinitely. When using large timeout
 * values, the fractional part may change due to rounding.
 *
 * \note
 * The underlying \b select() call may limit the maximum amount of time it
 * will wait to something less than \a timeout.
 *
 * \note
 * On stream sockets that are not connected, this function returns
 * RWSocketAttribute::sock_attr_canwrite. This is a known issue with the
 * underlying \b select() function.
 */
RW_NETWORK_SYMBOLIC RWTValOrderedVector<RWSocketAttribute>
rwSocketSelect(const RWTValOrderedVector<RWSocketAttribute>&, double timeout);

#if !defined(RW_DISABLE_DEPRECATED)

RW_DEPRECATE_FUNC("Use rwSocketSelect(const RWTValOrderedVector<RWSocketAttribute>&) instead")
RW_NETWORK_SYMBOLIC RWTValOrderedVector<RWSocketAttribute>
select(const RWTValOrderedVector<RWSocketAttribute>& attributes);

RW_DEPRECATE_FUNC("Use rwSocketSelect(const RWTValOrderedVector<RWSocketAttribute>&, double) instead")
RW_NETWORK_SYMBOLIC RWTValOrderedVector<RWSocketAttribute>
select(const RWTValOrderedVector<RWSocketAttribute>& att, double timeout);

#endif

#endif   // __rw_network_RWSocketAttribute_h__ 
