#ifndef rw_xmlstreams_RWTXmlTraits_h_
#define rw_xmlstreams_RWTXmlTraits_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTXmlTraits.h#1 $
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

#include <rw/xmlstreams/pkgdefs.h>
#include <rw/xmlabstractions/RWXmlNamespace.h>

template <class T>
class RWTXmlTraits
{};

/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Provides character and string values required by the \b RWTParsedXXX
 * transformation classes.
 *
 * A traits class used to provide character and string values required by
 * the \b RWTParsedXXX transformation classes.
 */
template <>
class RW_XMLSTREAMS_GLOBAL RWTXmlTraits<char>
{
public:
    /**
     * Character and string values required by the \b RWTParsedXXX
     * transformation classes.
     */
    static const char lt;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char gt;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char question;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char bang;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char space;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char newline;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char tab;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char slash;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char equal;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char apostrophe;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char quote;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char ampersand;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char colon;

    /**
     * \copydoc RWTXmlTraits<char>::lt
     */
    static const char namespacePrefix[];

    /**
     * URI of namespace "rw"
     */
    static const RWXmlNamespace rw;

    /**
     * XML schema instance namespace URI
     */
    static const RWXmlNamespace xsi;

    /**
     * XML schema namespace URIs
     */
    static const RWXmlNamespace xsd;
};

#endif // rw_xmlstreams_RWTXmlTraits_h_
