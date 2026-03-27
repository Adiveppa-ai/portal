#ifndef __rw_pop3_RWPop3ConnReply_h__
#define __rw_pop3_RWPop3ConnReply_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3ConnReply.h#1 $
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

#include <rw/pop3/RWPop3Reply.h>
#include <rw/pop3/pkgdefs.h>
#include <rw/cstring.h>

/**
 * \ingroup pop3_package
 *
 * \brief
 * Used to parse the POP3 protocol reply for the timestamp passed back by a
 * server implementation supporting enhanced security features.
 *
 * RWPop3ConnReply is derived from RWPop3Reply. RWPop3ConnReply attempts to
 * parse the POP3 protocol reply for the timestamp passed back by a server
 * implementation supporting enhanced security features. If the server does
 * not support this option, the timestamp method returns an empty string.
 */
class RW_POP3_GLOBAL RWPop3ConnReply : public RWPop3Reply
{

public:

    /**
     * Constructs a default RWPop3ConnReply.
     */
    RWPop3ConnReply(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3ConnReply::getTimeStamp() instead")
    RWCString timestamp(void) const;
#endif

    /**
     * Returns the timestamp passed to the client upon the connection to the
     * server. The timestamp is a unique ID used for advanced features, such
     * as authentication. The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getTimeStamp(void) const;

protected:

    /**
     * Performs an extended parse that attempts to obtain the server
     * timestamp.
     */
    virtual void parse(void);

private:

    /**
     * \relates RWPop3ConnReply
     *
     * Outputs an RWPop3ConnReply object to an \b std::ostream.
     *
     * \note
     * RWPop3ConnReply does not have an extraction (>>) operator.
     */
    friend RW_POP3_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWPop3ConnReply& r);

private:

    RWCString timestamp_;
};

#if !defined(RW_DISABLE_DEPRECATED)

inline RWCString
RWPop3ConnReply::timestamp(void) const
{
    return getTimeStamp();
}

typedef RW_DEPRECATE_TYPE("Use RWPop3ConnReply instead") RWPop3ConnReply RWIPop3ConnReply;
#endif

#endif // __rw_pop3_RWPop3ConnReply_h__
