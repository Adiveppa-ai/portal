#ifndef __rw_pop3_RWPop3Reply_h__
#define __rw_pop3_RWPop3Reply_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3Reply.h#1 $
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

#include <rw/pop3/pkgdefs.h>
#include <rw/internet/RWReply.h>
#include <rw/network/fwd.h>
#include <rw/cstring.h>


class RWPop3FSM;

/**
 * \ingroup pop3_package
 * \class RWPop3Reply
 *
 * \brief
 * Encapsulates a general POP3 protocol reply and is the base class for
 * specific POP3 replies.
 *
 * RWPop3Reply encapsulates a general POP3 protocol reply. It is the base
 * class for more specific POP3 replies. Specific subclasses of RWPop3Reply
 * -- RWPop3ConnReply, RWPop3DataReply, and RWPop3StatReply -- return
 * additional information specific to those types of POP3 protocol replies.
 *
 * The following are examples of POP3 server command replies:
 *
 * \code
 * +OK scan listing follows
 * -ERR no such message
 * \endcode
 */
class RW_POP3_GLOBAL RWPop3Reply : public RWReply
{
    friend class RWPop3FSM;

public:

    /**
     * Constructs a default invalid RWPop3Reply. You need to use the
     * assignment operator to initialize the default RWPop3Reply object.
     */
    RWPop3Reply(void);

    /**
     * Returns \c true if the reply is positive (\c +OK).
     */
    bool isOk(void) const;

    /**
     * Returns \c true if the reply is negative (\c -ERR).
     */
    bool isErr(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3Reply::getData() instead")
    RWCString data(void) const;
#endif

    /**
     * Returns the raw text used to construct the reply object. This can be
     * useful when communicating with non-standard servers. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWCString getData(void) const;

protected:

    /**
     * Enumerates possible reply categories.
     */
    enum resultCode {

        /**
         * An unexpected reply line was received.
         */
        CODE_UNKNOWN,

        /**
         * The reply status indicator \c +OK was received.
         */
        CODE_OK,

        /**
         * The reply status indicator \c -ERR was received.
         */
        CODE_ERR
    };

    /**
     * Reads data from the \a portal to construct the RWPop3Reply object.
     */
    void readFromPortal(const RWPortal& portal);

    /**
     * Provides an empty parsing mechanism. Derived classes can override the
     * virtual function to get extra meaning in a specific reply.
     */
    virtual void parse(void);

    /**
     * Contains the raw data line. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString data_;

private:

    /**
     * \relates RWPop3Reply
     *
     * Outputs an RWPop3Reply object to an \b std::ostream.
     *
     * \note
     * RWPop3Reply does not have an extraction (>>) operator.
     */
    friend RW_POP3_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWPop3Reply& r);

private:

    int       code_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWPop3Reply::data(void) const
{
    return getData();
}

typedef RW_DEPRECATE_TYPE("Use RWPop3Reply instead") RWPop3Reply RWIPop3Reply;
#endif

#endif // __rw_pop3_RWPop3Reply_h__
