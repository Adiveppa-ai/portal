#ifndef __rw_thread_RWProductInfo_h__
#define __rw_thread_RWProductInfo_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWProductInfo.h#1 $
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

  RWProductInfo - Base class for product-specific information classes.
                  Used to retrieve information about the current library.

*****************************************************************************/

#include <rw/thread/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tpslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_THREAD_GLOBAL RWProductInfo
{

protected:

    RWTPtrSlist<RWProductInfo> dependencies_;

public:

    virtual
    ~RWProductInfo(void);

    RWCString
    productInfo(void) const;

    virtual
    RWCString
    productVendorName(void) const = 0;

    virtual
    RWCString
    productName(void) const = 0;

    // Library or Executable
    virtual
    RWCString
    productType(void) const = 0;

    RWCString
    productVersion(void) const;

    virtual
    RWCString
    majorVersion(void) const = 0;

    virtual
    RWCString
    minorVersion(void) const = 0;

    virtual
    RWCString
    maintenanceVersion(void) const = 0;

    virtual
    RWCString
    productVersionLabel(void) const = 0;

    virtual
    RWCString
    productCopyright(void) const = 0;

    virtual
    RWCString
    buildTimeStamp(void) const = 0;

    RWCString
    productVariant(void) const;

    RWCString
    targetPlatform(void) const;

    virtual
    RWCString
    targetOSVendorName(void) const = 0;

    virtual
    RWCString
    targetOSName(void) const = 0;

    virtual
    RWCString
    targetOSVersion(void) const = 0;

    RWCString
    targetCompiler(void) const;

    virtual
    RWCString
    targetCompilerVendorName(void) const = 0;

    virtual
    RWCString
    targetCompilerName(void) const = 0;

    virtual
    RWCString
    targetCompilerVersion(void) const = 0;

    RWCString
    configuration(void) const;

    // Debug or Release Version
    virtual
    RWCString
    releaseType(void) const = 0;

    // N/A, Unsafe, Safe(Level 1), MT-Safe(Level 2)
    virtual
    RWCString
    threadSafety(void) const = 0;

    // Compiler options, special releases (test, trace, evaluation) etc.
    virtual
    RWCString
    additionalInfo(void) const = 0;

    // For future use in encoding variant information
    virtual
    RWCString
    variantDescriptor(void) const = 0;

    // Product Info for products used by this product
    RWCString
    dependencies(void) const;

    // Number of products used with product info
    size_t
    numberOfDependencies(void) const;

    // Get Product Info for products used by this product
    const RWProductInfo*
    dependency(size_t index) const;

    // Required for RWTPtrSlist
    inline
    int
    operator==(const RWProductInfo& second) const;

    // Required for RWTPtrSlist (stdlib1 version)
    inline
    int
    operator<(const RWProductInfo& second) const;

    // Required for RWTPtrSlist (stdlib2 version)
    inline
    int
    operator>(const RWProductInfo& second) const;

protected:

    RWProductInfo(void);

    void
    adoptDependency(RWProductInfo* usesInfo);

};

/*****************************************************************************/

inline
RWProductInfo::RWProductInfo(void)
{
}

inline int
RWProductInfo::operator==(const RWProductInfo& second) const
{
    return (this == &second);
}

inline int
RWProductInfo::operator<(const RWProductInfo& second) const
{
    return (productName() < second.productName());
}

inline int
RWProductInfo::operator>(const RWProductInfo& second) const
{
    return (productName() > second.productName());
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWProductInfo_h__
