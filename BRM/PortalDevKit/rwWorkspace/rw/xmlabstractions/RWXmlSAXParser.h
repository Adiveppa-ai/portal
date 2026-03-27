#ifndef rw_xmlabstractions_RWXmlSAXParser_h_
#define rw_xmlabstractions_RWXmlSAXParser_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlSAXParser.h#1 $
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

class RW_XMLABSTRACTIONS_SYMBOLIC RWXmlSAXParser
{
public:
    RWXmlSAXParser();

    // Content handler for parsed documents.  h receives events
    // as the document is parsed.
    void         setContentHandler(RWXmlContentHandler* h);

    // Returns the handler associated with self
    RWXmlContentHandler* getContentHandler() const;

    // Parses the given document.  xmlDocument contains the raw data of the
    // XML document, in any supported encoding (UTF-8, UTF-16 always, other
    // encodings if the i18n module is built in.)  If the document is not
    // in UTF-8 or UTF-16, and the document contains or may not contain
    // a TextDecl (<?xml ... ?>) with an encoding specifier, then pass the
    // name of the encoding in encodingName.
    void         parse(const RWCString& xmlDocument,
                       const RWCString& encodingName = RWCString());

    // get/set expandAttributeReference_
    // if expandAttributeReference_ references in attributes will be expanded
    // ex: "&lt;" expands to "<"
    // expandAttributeReference_ defaults to true
    bool getExpandAttributeReference() const
    {
        return expandAttributeReference_;
    }
    void setExpandAttributeReference(bool expandReference)
    {
        expandAttributeReference_ = expandReference;
    }

private:
    RWXmlContentHandler* handler_;
    bool expandAttributeReference_;
};

#endif // rw_xmlabstractions_RWXmlSAXParser_h_
