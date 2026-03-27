#ifndef __rw_http_RWIHttpVersion_h__
#define __rw_http_RWIHttpVersion_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpVersion.h#1 $
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


#if !defined(RW_DISABLE_DEPRECATED)

#  include <rw/http/pkgdefs.h>

// forward declarations
class RWCString;
class RWIHttpMethod;

/*
 * RWIHttpVersion
 *
 * RWIHttpVersion is an abstract class that defines the interface
 * for HTTP versions. The version classes are used by RWIHttpClient,
 * as helper classes, to filter request information based on
 * version.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpRequest instead")
    RW_HTTP_GLOBAL RWIHttpVersion
{

public:
    RWIHttpVersion(void);
    // default constructor

    virtual ~RWIHttpVersion() { }

    virtual bool canPersist(void) const = 0;
    // returns whether this version can persist connections

    virtual bool methodIsValid(const RWCString& methodName) const = 0;
    // returns whether the passed in method name is valid for
    // this version

    virtual RWCString makeMethodAsString(RWIHttpMethod& pMethod) = 0;
    // Uses method to create a valid HTTP method
    // string suitable for this version

    virtual int majorVersionNumber(void) const = 0;
    // returns major HTTP version number

    virtual int minorVersionNumber(void) const = 0;
    // returns minor HTTP version number

    virtual RWIHttpVersion* clone(void) const = 0;
    // returns a pointer to a copy of a specific RWIHttpVersion object
};

#endif  // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpVersion_h__
