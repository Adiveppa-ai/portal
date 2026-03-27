#ifndef __rw_internet_RWAgentImp_h__
#define __rw_internet_RWAgentImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWAgentImp.h#1 $
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
#include <rw/sync/RWBarrier.h>
#include <rw/cstring.h>
#include <rw/mutex.h>
#include <rw/tphdict.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/*
 * RWAgentImp
 *
 * RWAgentImp is an implementation class for RWAgent. It provides
 * lock mechanisms for its interface to have synchronization control
 * in a multithreaded environment. It also supplies some basic methods
 * to record and retrieve properties associated with an agent for a
 * specific protocol.
 *
 */

class RW_INTERNET_GLOBAL RWAgentImp
{

public:

    RWAgentImp(void);
    // Default Constructor

    virtual ~RWAgentImp(void);
    // Destructor

    void lock(void);
    // Locks the implementation to prevent
    // access from another thread.

    void unlock(void);
    // Unlocks the implementation.

    void wait(void);
    // barrier to synchronize threads, guaranties thread
    // acquisition before allowing main thread to continue.

    virtual void setProperty(const RWCString& p, const RWCString& v);
    // Sets a named property p to the string v

    virtual RWCString getProperty(const RWCString& p);
    // Gets the named property p

    virtual void clearProperties(void);
    // Clears the property hash dictionary

private:

    RWTPtrHashDictionary<RWCString, RWCString> props_;
    // Property dictionary

    RWMutex     apiMutex_;
    // interface mutex

    RWBarrier   tSync_;
    // Barrier object used by wait method.
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWAgentImp instead") RWAgentImp RWIAgentImpl;
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_internet_RWAgentImp_h__
