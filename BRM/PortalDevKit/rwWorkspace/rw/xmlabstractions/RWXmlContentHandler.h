#ifndef rw_xmlabstractions_RWXmlContentHandler_h_
#define rw_xmlabstractions_RWXmlContentHandler_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlContentHandler.h#1 $
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

#include <rw/xmlabstractions/fwd.h>
#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>

class RW_XMLABSTRACTIONS_GLOBAL RWXmlContentHandler
{
public:

    // Called when a start or empty tag is encountered.  Name contains
    // all name/namespace information.  attrs contains all element
    // attributes, including namespace declarations.
    virtual void startElement(const RWXmlName& name,
                              const RWXmlAttributeSet& attrs) = 0;

    // Called when an end or empty tag is encountered.
    virtual void endElement(const RWXmlName& name) = 0;

    // Called for all character content, including CDATA.
    // Character data is in UTF-8, regardless of document encoding.
    virtual void characters(const RWCString& utf8Chars) = 0;

    // Called when the XML prolog is processed.
    // Don't want to force this to be used in all of RWXmlContentHandler's
    // derived classes as it is only used by RWSoapMessage.
    virtual void prolog(const RWXmlProlog&) {}

    // destructor.
    virtual ~RWXmlContentHandler();
};

#endif // rw_xmlabstractions_RWXmlContentHandler_h_
