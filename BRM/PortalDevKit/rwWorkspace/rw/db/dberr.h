#ifndef __RWDB_DBERR_H__
#define __RWDB_DBERR_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dberr.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 * DB Interface message catalog. This file could be named more appropriately
 * msg.h or some such, but dberr.h is retained for historical reasons.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/message.h>

#  define RWDB_OK                   RWDB_OK()
#  define RWDB_NOMEM                RWDB_NOMEM()
#  define RWDB_TYPECONVERSION       RWDB_TYPECONVERSION()
#  define RWDB_DBNOTFOUND           RWDB_DBNOTFOUND()
#  define RWDB_NOTINITIALIZED       RWDB_NOTINITIALIZED()
#  define RWDB_SERVERERROR          RWDB_SERVERERROR()
#  define RWDB_SERVERMESSAGE        RWDB_SERVERMESSAGE()
#  define RWDB_VENDORLIB            RWDB_VENDORLIB()
#  define RWDB_NOTCONNECTED         RWDB_NOTCONNECTED()
#  define RWDB_ENDOFFETCH           RWDB_ENDOFFETCH()
#  define RWDB_INVALIDUSAGE         RWDB_INVALIDUSAGE()
#  define RWDB_COLUMNNOTFOUND       RWDB_COLUMNNOTFOUND()
#  define RWDB_INVALIDPOSITION      RWDB_INVALIDPOSITION()
#  define RWDB_NOTSUPPORTED         RWDB_NOTSUPPORTED()
#  define RWDB_NULLREFERENCE        RWDB_NULLREFERENCE()
#  define RWDB_NOTFOUND             RWDB_NOTFOUND()
#  define RWDB_MISSING              RWDB_MISSING()
#  define RWDB_NOMULTIREADERS       RWDB_NOMULTIREADERS()
#  define RWDB_NODELETER            RWDB_NODELETER()
#  define RWDB_NOINSERTER           RWDB_NOINSERTER()
#  define RWDB_NOUPDATER            RWDB_NOUPDATER()
#  define RWDB_NOREADER             RWDB_NOREADER()
#  define RWDB_NOINDEX              RWDB_NOINDEX()
#  define RWDB_NODROP               RWDB_NODROP()
#  define RWDB_WRONGCONN            RWDB_WRONGCONN()
#  define RWDB_NOPRIVILEGE          RWDB_NOPRIVILEGE()
#  define RWDB_NOCURSOR             RWDB_NOCURSOR()
#  define RWDB_CANTOPEN             RWDB_CANTOPEN()
#  define RWDB_NOTREADY             RWDB_NOTREADY()
#  define RWDB_COLUMNNUMNOTFOUND    RWDB_COLUMNNUMNOTFOUND()
#  define RWDB_COLUMNLISTMISMATCH   RWDB_COLUMNLISTMISMATCH()

extern RWMsgId RWDB_GLOBAL RWDB_OK;
extern RWMsgId RWDB_GLOBAL RWDB_NOMEM;
extern RWMsgId RWDB_GLOBAL RWDB_TYPECONVERSION;
extern RWMsgId RWDB_GLOBAL RWDB_DBNOTFOUND;
extern RWMsgId RWDB_GLOBAL RWDB_NOTINITIALIZED;
extern RWMsgId RWDB_GLOBAL RWDB_SERVERERROR;
extern RWMsgId RWDB_GLOBAL RWDB_SERVERMESSAGE;
extern RWMsgId RWDB_GLOBAL RWDB_VENDORLIB;
extern RWMsgId RWDB_GLOBAL RWDB_NOTCONNECTED;
extern RWMsgId RWDB_GLOBAL RWDB_ENDOFFETCH;
extern RWMsgId RWDB_GLOBAL RWDB_INVALIDUSAGE;
extern RWMsgId RWDB_GLOBAL RWDB_COLUMNNOTFOUND;
extern RWMsgId RWDB_GLOBAL RWDB_INVALIDPOSITION;
extern RWMsgId RWDB_GLOBAL RWDB_NOTSUPPORTED;
extern RWMsgId RWDB_GLOBAL RWDB_NULLREFERENCE;
extern RWMsgId RWDB_GLOBAL RWDB_NOTFOUND;
extern RWMsgId RWDB_GLOBAL RWDB_MISSING;
extern RWMsgId RWDB_GLOBAL RWDB_NOMULTIREADERS;
extern RWMsgId RWDB_GLOBAL RWDB_NODELETER;
extern RWMsgId RWDB_GLOBAL RWDB_NOINSERTER;
extern RWMsgId RWDB_GLOBAL RWDB_NOUPDATER;
extern RWMsgId RWDB_GLOBAL RWDB_NOREADER;
extern RWMsgId RWDB_GLOBAL RWDB_NOINDEX;
extern RWMsgId RWDB_GLOBAL RWDB_NODROP;
extern RWMsgId RWDB_GLOBAL RWDB_WRONGCONN;
extern RWMsgId RWDB_GLOBAL RWDB_NOPRIVILEGE;
extern RWMsgId RWDB_GLOBAL RWDB_NOCURSOR;
extern RWMsgId RWDB_GLOBAL RWDB_CANTOPEN;
extern RWMsgId RWDB_GLOBAL RWDB_NOTREADY;
extern RWMsgId RWDB_GLOBAL RWDB_COLUMNNUMNOTFOUND;
extern RWMsgId RWDB_GLOBAL RWDB_COLUMNLISTMISMATCH;

#endif
