#ifndef __rw_thread_RWThreadsProductInfo_h__
#define __rw_thread_RWThreadsProductInfo_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadsProductInfo.h#1 $
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


/*****************************************************************************

  RWThreadsProductInfo - SourcePro Core - Threads Module product
                         information class.

*****************************************************************************/

#include <rw/thread/RWProductInfo.h>
#include <rw/thread/pkgdefs.h>

class RW_THREAD_GLOBAL RWThreadsProductInfo :
    public RWProductInfo
{

public:

    RWThreadsProductInfo(void);

    virtual
    ~RWThreadsProductInfo(void);

    virtual
    RWCString
    productVendorName(void) const;

    virtual
    RWCString
    productName(void) const;

    virtual
    RWCString
    productType(void) const;

    virtual
    RWCString
    majorVersion(void) const;

    virtual
    RWCString
    minorVersion(void) const;

    virtual
    RWCString
    maintenanceVersion(void) const;

    virtual
    RWCString
    productVersionLabel(void) const;

    virtual
    RWCString
    productCopyright(void) const;

    virtual
    RWCString
    buildTimeStamp(void) const;

    virtual
    RWCString
    targetOSVendorName(void) const;

    virtual
    RWCString
    targetOSName(void) const;

    virtual
    RWCString
    targetOSVersion(void) const;

    virtual
    RWCString
    targetCompilerVendorName(void) const;

    virtual
    RWCString
    targetCompilerName(void) const;

    virtual
    RWCString
    targetCompilerVersion(void) const;

    virtual
    RWCString
    releaseType(void) const;

    virtual
    RWCString
    threadSafety(void) const;

    virtual
    RWCString
    additionalInfo(void) const;

    virtual
    RWCString
    threadAPI(void) const;

    virtual
    RWCString
    variantDescriptor(void) const;

};

#endif // __rw_thread_RWThreadsProductInfo_h__
