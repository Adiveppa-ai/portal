#ifndef __rw_http_defs_h__
#define __rw_http_defs_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/defs.h#1 $
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


//////////////////////////////////////////////////////////////////////////////
// Note: All extern variables are defined in defs.cpp
//////////////////////////////////////////////////////////////////////////////

#include <rw/http/pkgdefs.h>
#include <rw/internet/defs.h>

//////////////////////////////////////////////////////////////////////////////
// HTTP specific definitions
//////////////////////////////////////////////////////////////////////////////

// When sending data to the server in chunked form, we have to limit the
// size of the chunk to a reasonable size.  Network buffers are usually
// about 4K, so our size is slightly less than that so that we can send
// the chunk and chunk size in a single network communication.

const int RW_HTTP_MAX_CHUNK_SIZE = 4080;

// When constructing a client manager instance, we need to know how many
// connections to allow per client and how many threads are going to be
// used to be doing HTTP work.

const size_t RW_HTTP_CLIENT_MANAGER_MAX_CONN = 2;
const size_t RW_HTTP_CLIENT_MANAGER_MAX_THREADS = 20;

#endif // __rw_http_defs_h__
