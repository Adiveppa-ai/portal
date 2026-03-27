#ifndef rw_xmlabstractions_RWXmlSchemaError_h_
#define rw_xmlabstractions_RWXmlSchemaError_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlSchemaError.h#1 $
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
#include <rw/xmlabstractions/RWXmlError.h>
#include <rw/xmlabstractions/pkgdefs.h>     // every class needs this
#include <rw/message.h>             // use RWMessage for i18n purposes
#include <stdexcept>                // standard exception hierarchy
#include <string>

/******************************************************************************
 *
 * RWXmlSchemaError will usually be thrown, but might be compiled to do
 * something more old fashioned. It inherits RWxmsg to join it to the
 * hierarchy expected by users of Tools.h++, and to enable the old fashioned
 * error handler technique to work (albeit with the loss of a small amount
 * of type information.
 *
 ******************************************************************************/

class RW_XMLABSTRACTIONS_GLOBAL RWXmlSchemaError
    : public RWXmlError, public std::logic_error
{
public:

    RWXmlSchemaError()
        : RWXmlError(RWCString()), std::logic_error(0) { }

    RWXmlSchemaError(const RWCString& msg);
    RWXmlSchemaError(const RWMessage&);
    virtual ~RWXmlSchemaError() RW_NO_THROW;
};

extern RW_XMLABSTRACTIONS_GLOBAL void RWThrow(const RWXmlSchemaError&);

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

#endif // rw_xmlabstractions_RWXmlSchemaError_h_
