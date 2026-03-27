#ifndef __rw_internet_RWAgent_h__
#define __rw_internet_RWAgent_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWAgent.h#1 $
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

#include <rw/internet/RWAgentImp.h>
#include <rw/internet/pkgdefs.h>
#include <rw/network/RWTNetHandle.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/*
 * RWAgent
 *
 * RWAgent is a class that all protocol agents are built from.
 * It is the interface part of the interface-implementation tandem,
 * with the implementation class as the RWAgentImp class.
 *
 * RWAgent itself cannot be instantiated, since no public
 * constructor is provided. It is intended to be constructed
 * as the super-class portion of a specific protocol-agent
 * object.
 *
 */

/**
 * \internal
 * \ingroup internet_basics_package
 *
 * \brief
 * Base class for all protocol-specific agents.
 *
 * RWAgent is the base class from which all specific protocol agents are
 * built. Both of the constructors included in the RWAgent class are
 * protected, so an RWAgent object can be constructed only by its specific
 * protocol agents.
 *
 * RWAgent and its derived protocol-agent classes are lightweight handles.
 * They are implemented using the interface-implementation idiom.
 */
class RW_INTERNET_SYMBOLIC RWAgent
{

protected:

    /**
     * Constructs a default invalid RWAgent.
     */
    RWAgent(void);

    /**
     * Constructs an RWAgent with a specific implementation.
     */
    RWAgent(RWAgentImp* i);

protected:

    /**
     * Contains the underlying implementation pointer that performs protocol
     * actions.
     */
    RWTNetHandle<RWAgentImp> impl_;
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWAgent instead") RWAgent RWIAgent;
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif


#endif // __rw_internet_RWAgent_h__
