#ifndef __rw_internet_RWReply_h__
#define __rw_internet_RWReply_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWReply.h#1 $
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
#include <rw/network/fwd.h>

/**
 * \ingroup internet_basics_package
 *
 * \brief
 * Abstract base class for all protocol replies.
 *
 * RWReply is the abstract base class for all protocol replies. It provides
 * some common methods that all replies share.
 */
class RW_INTERNET_GLOBAL RWReply
{

public:

    /**
     * Constructs a default RWReply as part of a specific and concrete reply
     * object.
     */
    RWReply(void);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWReply(void);

    /**
     * Resets the object to the same state as after the default
     * construction.
     */
    virtual void
    clearAndDestroy(void);

    /**
     * Returns \c true if self represents a complete protocol reply.
     */
    virtual bool
    isComplete(void) const;

    /**
     * Returns \c true if self is a valid reply.
     */
    virtual bool
    isValid(void) const;

protected:

    /**
     * Reads data from \a portal to construct self. It must be overridden by
     * derived classes.
     */
    virtual void readFromPortal(const RWPortal& portal) = 0;

    /**
     * Contains \c true if self is a valid protocol reply.
     */
    bool valid_;

    /**
     * Contains \c true if self is a complete protocol reply.
     */
    bool complete_;

private:

    /**
     * Outputs RWReply to an \c std::ostream as part of a specific and
     * concrete reply object.
     */
    friend RW_INTERNET_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWReply& r);
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWReply instead") RWReply RWIReply;
#endif

#endif // __rw_internet_RWReply_h__
