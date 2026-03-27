#ifndef rw_xmlabstractions_RWXmlWriter_h_
#define rw_xmlabstractions_RWXmlWriter_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlWriter.h#1 $
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

#include <rw/xmlabstractions/RWXmlDuration.h>
#include <rw/xmlabstractions/RWXmlName.h>
#include <rw/xmlabstractions/RWXmlNamespace.h>
#include <rw/xmlabstractions/RWXmlNamespaceStack.h>
#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>
#include <rw/tools/decport.h>

/*
 * RWXmlWriter is a undocumented utility class used to provide a single interface
 * for writing XML messages to different data sources.

 * Class RWXmlWriter is an abstract class and provides limited functionality. A derived class
 * is expected to implement the abstract functions.  A known implementor is the
 * RWXmlStringWriter class.
 */
class RW_XMLABSTRACTIONS_GLOBAL RWXmlWriter
{

public:

    // Used For Writing In Chunks. Indicates Status of Writing.
    enum WriteState { Start, InProgress };

    // Constructor & Destructor
    RWXmlWriter();
    virtual ~RWXmlWriter() {}

    // Constants
    static const RWCString        XmlNamespaceTag;
    static const RWCString        Blank;
    static const RWCString        Colon;
    static const RWCString        Newline;
    static const RWCString        WhiteSpace;      // Obsolete.  Use Blank instead.
    static const RWCString        EqualToAndQuotes;
    static const RWCString        Quotes;
    static const RWCString        TrueValue;
    static const RWCString        FalseValue;

    static const RWCString        StartTag;
    static const RWCString        EndTag;
    static const RWCString        StartEndTag;
    static const RWCString        UnpairedTag;

    static const RWCString        MarkupGt;
    static const RWCString        MarkupLt;
    static const RWCString        MarkupAmpersand;
    static const RWCString        MarkupQuotes;
    static const RWCString        MarkupApos;
    static const RWCString        MarkupCR;

    // add a namespace to the namespace scope
    void                                    addNamespace(const RWXmlNamespace& ns);

    //Sets the number of spaces for each increment/decrement
    inline int                              setSizeOfIndent(int indentSize_);
    inline int                              getSizeOfIndent() const;

    //Sets the beginning indent
    inline void                             setCurrentIndent(int indent);
    inline int                              getCurrentIndent() const;

    void                                    writeIndentChars();

    // These methods are used by the handlers.

    // Controls the indent size
    inline void                             incrementIndent();
    void                                    decrementIndent();

    //Write Methods that write to the sink
    void                                    writeSimpleElement(const RWCString& name,
            const RWCString& value,
            const RWCString& schemaType,
            bool  includeTypeAttribute = false);

    void                                    writeAttribute(const RWCString& name,
            const RWCString& value,
            bool mustEscapeText = true);

    void                                    writeAttribute(const RWXmlName& name,
            const RWCString& value,
            bool mustEscapeText = true);

    void                                    writeSimpleElement(const RWXmlName& name,
            const RWCString& value,
            const RWCString& schemaType,
            bool  includeTypeAttribute = false);

    void                                    write(const RWCString& text,
            bool mustEscapeText = false);

    void                                    writeElementStart(const RWXmlName& name, const RWXmlAttributeSet& attributes = RWXmlAttributeSet(), bool emptyElement = false);
    void                                    writeElementEnd(const RWXmlName& name);

    void                                    writeNewLine();

protected:

    // Writes to the underlying sink. Implemented by derived classes
    virtual void                            writeToSink(const RWCString& text) = 0;

    virtual void                            writeToSink(const char*, size_t len);

    virtual void                            writeToSink(char c) = 0;

    virtual void                            flush() = 0;

private:

    RWXmlAttributeSet                       getCompleteAttributeSet(const RWXmlAttributeSet& attributes);
    void                                    addNamespaceToScopeIfNecessary(const RWXmlNamespace& aNamespace);

    size_t                                  currentIndent_;
    size_t                                  indentSize_;
    bool                                    newLine_;
    RWXmlNamespaceStack                     namespaceStack_;

}; //RWXmlWriter


//////////////////////////////////////////////////////////////////////////////////////////////
//
// Inline Functions Definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////
inline int
RWXmlWriter::setSizeOfIndent(int indentSize)
{
    int old = int (indentSize_);
    indentSize_ = size_t (indentSize);
    return old;
}

inline int
RWXmlWriter::getSizeOfIndent() const
{
    return int (indentSize_);
}

inline void
RWXmlWriter::setCurrentIndent(int indent)
{
    currentIndent_ = size_t (indent);
}

inline int
RWXmlWriter::getCurrentIndent() const
{
    return int (currentIndent_);
}

inline void
RWXmlWriter::incrementIndent()
{
    currentIndent_ += indentSize_;
}

inline void
RWXmlWriter::writeToSink(const char* str, size_t len)
{
    writeToSink(RWCString(str, len));
}

#endif // rw_xmlabstractions_RWXmlWriter_h_
