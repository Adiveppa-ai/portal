#ifndef rw_xmlstreams_RWXmlObjectStreamCommon_h_
#define rw_xmlstreams_RWXmlObjectStreamCommon_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWXmlObjectStreamCommon.h#1 $
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
#include <rw/serial/StreamTraits.h>

//--Base class shared by XML object input and output streams.  This
//--class defines the tags and attribute names used in the XML.
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Base class shared by XML object input and output streams.
 *
 * Base class shared by XML object input and output streams. This class
 * defines the tags and attribute names used in the XML.
 */
class RW_XMLSTREAMS_GLOBAL RWXmlObjectStreamCommon
{
public:
    /**
     * Represent the element and attribute names used in the generated XML
     * object stream.
     */
    static const char* objectTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* objectRefTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* objectRefTagLocal;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* nestedObjectTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* memberTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* primitiveTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* sequenceTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* sequenceElementTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* mapTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* associationTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* assocKeyTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* assocValueTag;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* IdAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* IdRefAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* memberNameAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* memberTypeAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* objectNameAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* objectTypeAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* seqCountAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* seqTypeAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* elementPosAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* mapCountAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* mapKeyTypeAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* mapValueTypeAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* xsdNamespace;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* xsdNamespaceAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* xsdNamespaceValue;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* xsiNamespace;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* xsiNamespaceAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* xsiNamespaceValue;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* rwNamespace;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* rwNamespaceAttr;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* rwNamespaceValue;

    /**
     * \copydoc RWXmlObjectStreamCommon::objectTag
     */
    static const char* rwEncodingNamespaceValue;

    /**
     * Converts an RWStreamType enum value into a string representing an XML
     * qualified element name. For example, passing the enum value
     * #RW_NESTED_OBJECT results in a return value of \c rw:nested_object.
     */
    static const char* rwStreamToStringType(RWStreamType stype);

    /**
     * Converts an RWStreamType enum value into a string representing an XML
     * non-qualified (local) element name. For example, passing the enum
     * value #RW_NESTED_OBJECT results in a return value of
     * \c nested_object.
     */
    static const char* rwStreamToLocalStringType(RWStreamType stype);
};


//--Class used to convert a string identifier into an 'RWStreamType'.
class RWXmlStringToStreamType : public RWTValHashDictionary<RWCString, RWStreamType>
{
    friend class RWTSingleton<RWXmlStringToStreamType>;
public:
    static RWStreamType convert(const RWCString& name)
    {
        RWStreamType result = (RWStreamType) - 1;
        (*RWTSingleton<RWXmlStringToStreamType>::instance()).findValue(name, result);
        return result;
    }
private:
    RWXmlStringToStreamType()
    {
        insertKeyAndValue("rw:map", RW_ASSOC);
        insertKeyAndValue("rw:sequence", RW_SEQ);
        insertKeyAndValue("rw:unsupported", RW_UNSUPPORTED);
        insertKeyAndValue("rw:char", RW_CHAR);
        insertKeyAndValue("rw:wchar_t", RW_WCHAR_T);
        insertKeyAndValue("rw:unsignedChar", RW_UNSIGNED_CHAR);
        insertKeyAndValue("xsd:double", RW_DOUBLE);
        insertKeyAndValue("xsd:float", RW_FLOAT);
        insertKeyAndValue("xsd:int", RW_INT);
        insertKeyAndValue("xsd:unsignedInt", RW_UNSIGNED_INT);
        insertKeyAndValue("xsd:long", RW_LONG);
        insertKeyAndValue("xsd:unsignedLong", RW_UNSIGNED_LONG);
        insertKeyAndValue("xsd:short", RW_SHORT);
        insertKeyAndValue("xsd:unsignedShort", RW_UNSIGNED_SHORT);
        insertKeyAndValue("xsd:string", RW_STRING);
        insertKeyAndValue("xsd:date", RW_DATE);
        insertKeyAndValue("xsd:dateTime", RW_DATETIME);
        insertKeyAndValue("rw:decimal_portable", RW_DECIMAL_PORTABLE);
        insertKeyAndValue("rw:object", RW_OBJECT);
        insertKeyAndValue("rw:nested_object", RW_NESTED_OBJECT);
        insertKeyAndValue("xsd:boolean", RW_BOOL);
#ifndef RW_NO_LONG_DOUBLE
        insertKeyAndValue("rw:longDouble", RW_LONG_DOUBLE);
#endif // RW_NO_LONG_DOUBLE
#if !defined(RW_NO_LONG_LONG)
        insertKeyAndValue("rw:longLong", RW_LONG_LONG);
        insertKeyAndValue("rw:unsignedLongLong", RW_UNSIGNED_LONG_LONG);
#endif // !RW_NO_LONG_LONG
        insertKeyAndValue("xsd:ID", RW_ID);
        insertKeyAndValue("xsd:IDREF", RW_IDREF);
        insertKeyAndValue("rw:Namespace", RW_NAMESPACE);
        insertKeyAndValue("rw:UnKnown_Type", RW_TYPE);
    }
};

#endif // rw_xmlstreams_RWXmlObjectStreamCommon_h_
