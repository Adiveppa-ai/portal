#ifndef __rw_internet_except_h__
#define __rw_internet_except_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/except.h#1 $
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
#include <rw/cstring.h>
#include <rw/rwerr.h>

// Exceptions

/**
 * \ingroup internet_basics_package
 *
 * \brief
 * An exception thrown when when a protocol-specific error (FTP, POP3, SMTP)
 * occurs while processing a command in an Agent class.
 *
 * An RWProtocolAgentError is thrown when a protocol-specific error (FTP,
 * POP3, SMTP) occurs while processing a command in an Agent class.
 */
class RW_INTERNET_GLOBAL RWProtocolAgentError
    : public RWInternalErr
{
public:
    RWProtocolAgentError(const RWCString& s);
};


/**
 * \ingroup internet_basics_package
 *
 * \brief
 * An exception thrown when when a protocol-specific error (FTP, POP3, SMTP)
 * occurs while processing a command in a Client class.
 *
 * An RWProtocolAgentError is thrown when a protocol-specific error (FTP,
 * POP3, SMTP) occurs while processing a command in a Client class.
 */
class RW_INTERNET_GLOBAL RWProtocolClientError
    : public RWInternalErr
{
public:
    RWProtocolClientError(const RWCString& s);
};


/**
 * \ingroup internet_basics_package
 *
 * \brief
 * An exception thrown when a protocol action (FTP, POP3, HTTP, SMTP) is
 * used out of the sequence dictated by that protocol.
 *
 * An RWProtocolClientCmdSequenceError is thrown when a protocol action
 * (FTP, POP3, HTTP, SMTP) is used out of the sequence dictated by that
 * protocol.
 */
class RW_INTERNET_GLOBAL RWProtocolClientCmdSequenceError
    : public RWProtocolClientError
{
public:
    RWProtocolClientCmdSequenceError(const RWCString& s);
};


/**
 * \ingroup internet_basics_package
 *
 * \brief
 * An exception thrown when an RWReply (or derived class) is used in an
 * invalid manner.
 *
 * An RWReplyError is thrown when an RWReply (or derived class) is used in
 * an invalid manner.
 */
class RW_INTERNET_GLOBAL RWReplyError
    : public RWInternalErr
{
public:
    RWReplyError(const RWCString& s);
};


/**
 * \ingroup internet_basics_package
 *
 * \brief
 * An exception thrown when the text or error number of a reply message does
 * not adhere to the single numerical reply defined by the protocol being
 * used.
 *
 * An RWReplySyntaxError is thrown when the text or error number of a reply
 * message does not adhere to the single numerical reply defined by the
 * protocol being used.
 */
class RW_INTERNET_GLOBAL RWReplySyntaxError
    : public RWInternalErr
{
public:
    RWReplySyntaxError(const RWCString& s);
};


/**
 * \ingroup internet_basics_package
 *
 * \brief
 * An exception not currently used. It remains reserved for potential future
 * use.
 *
 * The exception RWURLError is not currently used. It remains reserved for
 * potential future use.
 */
class RW_INTERNET_GLOBAL RWURLError
    : public RWInternalErr
{
public:
    RWURLError(const RWCString& s);
};


#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWProtocolAgentError instead") RWProtocolAgentError                          RWIProtocolAgentErr;
typedef RW_DEPRECATE_TYPE("Use RWProtocolClientCmdSequenceError instead") RWProtocolClientCmdSequenceError  RWIProtocolClientCmdSequenceErr;
typedef RW_DEPRECATE_TYPE("Use RWProtocolClientError instead") RWProtocolClientError                        RWIProtocolClientErr;
typedef RW_DEPRECATE_TYPE("Use RWReplyError instead") RWReplyError                                          RWIReplyErr;
typedef RW_DEPRECATE_TYPE("Use RWReplySyntaxError instead") RWReplySyntaxError                              RWIReplySyntaxErr;
typedef RW_DEPRECATE_TYPE("Use RWURLError instead") RWURLError                                              RWURLErr;
#endif

#endif // __rw_internet_except_h__
