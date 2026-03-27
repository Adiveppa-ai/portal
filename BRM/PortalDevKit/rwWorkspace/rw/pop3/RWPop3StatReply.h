#ifndef __rw_pop3_RWPop3StatReply_h__
#define __rw_pop3_RWPop3StatReply_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3StatReply.h#1 $
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

/**
 * \ingroup pop3_package
 *
 * \brief
 * Used to parse additional reply data returned in response to the POP3
 * \c STAT command.
 *
 * RWPop3StatReply is derived from RWPop3Reply. RWPop3StatReply parses out
 * additional reply data returned in response to the POP3 \c STAT command.
 * This data includes the number of messages waiting in the maildrop, and
 * the number of octets consumed by those messages.
 */
class RW_POP3_GLOBAL RWPop3StatReply : public RWPop3Reply
{

public:

    /**
     * Default constructor.
     */
    RWPop3StatReply(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3StatReply::getMessageCount() instead")
    int messages(void) const;
#endif

    /**
     * Returns the number of messages waiting in the mail drop.
     */
    int getMessageCount(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3StatReply::getOctets() instead")
    int octets(void) const;
#endif

    /**
     * Returns the total size (in octets) of the messages waiting in the
     * mail drop.
     */
    int getOctets(void) const;

private:

    /**
     * Performs an extended parse to obtain the number of waiting messages
     * and their total size.
     */
    virtual void parse(void);

private:

    /**
     * \relates RWPop3StatReply
     *
     * Outputs an RWPop3StatReply object to an \b std::ostream.
     *
     * \note
     * RWPop3StatReply does not have an extraction (>>) operator.
     */
    friend RW_POP3_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWPop3StatReply& r);

private:

    int octets_;
    int messages_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline int
RWPop3StatReply::messages(void) const
{
    return getMessageCount();
}

inline int
RWPop3StatReply::octets(void) const
{
    return getOctets();
}

typedef RW_DEPRECATE_TYPE("Use RWPop3StatReply instead") RWPop3StatReply RWIPop3StatReply;
#endif

#endif // __rw_pop3_RWPop3StatReply_h__
