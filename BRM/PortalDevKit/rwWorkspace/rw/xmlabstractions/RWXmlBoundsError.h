#ifndef rw_xmlabstractions_RWXmlBoundsError_h_
#define rw_xmlabstractions_RWXmlBoundsError_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlBoundsError.h#1 $
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
 ********************************************************************/


#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable : 4275)
#endif

#include <rw/xmlabstractions/RWXmlError.h>  // Xml error space
#include <rw/xmlabstractions/pkgdefs.h>     // every class needs this
#include <rw/message.h>             // use RWMessage for i18n purposes
#include <stdexcept>                // standard exception hierarchy

/******************************************************************************
 *
 * RWXmlBoundsError will usually be thrown, but might be compiled to do
 * something more old fashioned. It indicates
 *
 * To provide maximum flexibility in its use, it inherits both RWXmlError
 * (which in turn inherits RWxmsg) and the appropriate exception from the
 * standard exception hierarchy: out_of_range
 *
 ******************************************************************************/

class RW_XMLABSTRACTIONS_GLOBAL RWXmlBoundsError :
    public RWXmlError, public std::out_of_range
{
public:
    RWXmlBoundsError(const RWCString& msg);
    RWXmlBoundsError(const RWMessage&);
    virtual ~RWXmlBoundsError() RW_NO_THROW;
};

extern RW_XMLABSTRACTIONS_GLOBAL void RWThrow(const RWXmlBoundsError&);

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

#endif // rw_xmlabstractions_RWXmlBoundsError_h_
