#ifndef rw_xmlstreams_RWXmlObjectInputStreamImp_h_
#define rw_xmlstreams_RWXmlObjectInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWXmlObjectInputStreamImp.h#1 $
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

#include <rw/xmlstreams/RWXmlObjectStreamCommon.h>
#include <rw/xmlstreams/pkgdefs.h>
#include <rw/serial/RWDataFromVirtualInputStreamImp.h>
#include <rw/serial/RWObjectInputStream.h>
#include <rw/serial/RWObjectInputStreamImp.h>
#include <rw/stream/stream.h>
#include <rw/factory/RWTSingleFactory1.h>
#include <rw/pstream.h>
#include <rw/rstream.h>
#include <rw/rwstore.h>
#include <rw/tools/bustring.h>
#include <list>
#include <map>
#include <queue>
#include <ctype.h>
#include <stdlib.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif


//--The class 'RWXmlObjectInputStreamImp' reads objects encoded in XML
//--from the supplied 'RWDataInputStream'.
//--
//--The format of this stream is detailed in the file 'xmlstreams.xsd'.
//--Implements the body idiom from the handle/body pattern.
//--
//--Example:
//--
//--// Open an fstream to serve as our source
//--ifstream s("foo.xml");
//--
//--// Create an XML data stream using the fstream
//--RWObjectInputStream in = RWXmlObjectInputStreamImp::make(s);
//--
//--// Read integer from XML data stream
//--int i;
//--s >> i;
//--
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Reads and restores objects encoded in XML from the supplied
 * RWDataInputStream.
 *
 * The class RWXmlObjectInputStreamImp reads and restores objects encoded in
 * XML from the supplied RWDataInputStream. Typically, the XML stream was
 * originally created by the class RWXmlObjectOutputStreamImp, thereby
 * ensuring symmetry of the output and subsequent input.
 *
 * The XML Streams Module integrates with the general Rogue Wave streams
 * architecture defined by the streams and serialization packages of the
 * Advanced Tools Module of SourcePro Core. This architecture allows an XML
 * stream to be written out and read in using a wide variety of streaming
 * configurations. For more information specific to the XML Streams Module,
 * see the XML Streams Module User's Guide. For information on the general
 * architecture, see the <em>Advanced Tools Module User's Guide</em>.
 *
 * RWXmlObjectInputStreamImp is the body class of a handle-body pattern. The
 * corresponding handle class is RWObjectInputStream.
 *
 * The syntax of the XML formatting parsed by this class is defined by the
 * XML schema \c xmlstreams.xsd. This schema is located in
 * <tt>buildspace\\rw\\xmlstreams</tt>.
 *
 * \example
 * \code
 * // Open an fstream to serve as our source.
 * ifstream s("foo.xml");
 *
 * // Create an XML data stream using the fstream.
 * RWObjectInputStream in = RWXmlObjectInputStreamImp::make(s);
 *
 * // Read an integer from the XML data stream.
 * int i;
 * s >> i;
 * \endcode
 * \endexample
 */
class RW_XMLSTREAMS_GLOBAL RWXmlObjectInputStreamImp : public RWObjectInputStreamImp,
    public RWXmlObjectStreamCommon
{

protected:
    RWReadTable* table_;
    bool escapeText_;

    virtual void          openOuterContext(bool readContext);
    virtual void          closeOuterContext(bool readContext);

    //--Used by derived classes to initialize the previous processing stream.
    //--Parameter 'sourceStream' is a handle to the previous processing stream.
    //--Throws no exceptions.
    /**
     * Used by the make() function and potentially by derived classes to
     * initialize the source data stream if the required input stream is a
     * standard library istream.
     *
     * The parameter \a sourceStream is a handle to the initialized stream.
     *
     * The parameter \a escape sets whether the input stream contains
     * escapes for XML reserved characters that need to be unescaped.
     * Usually this would be because the objects serialized out with
     * RWXmlObjectOutputStreamImp contained embedded XML.
     *
     * The reserved characters are:
     *
     * \code
     * <  >  &  "  '
     * \endcode
     *
     * You get slightly better performance if the \a escape parameter is set
     * to \c false, but before doing so be certain that your data does not
     * contain reserved characters.
     */
    RWXmlObjectInputStreamImp(std::istream& sourceStream, bool escape)
        :
        RWObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWCharFromStreambufInputStreamImp::make(*(sourceStream.rdbuf())))),
        table_(rwnil),
        escapeText_(escape),
        attributesRead_(false)
    {
        ;
    }

    //--Used by derived classes to initialize the previous processing stream.
    //--Parameter 'sourceStream' is a handle to the previous processing stream.
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Throws no exceptions.
    /**
     * \copydoc RWXmlObjectInputStreamImp::RWXmlObjectInputStreamImp(std::istream&, bool)
     *
     * This constructor also takes a pointer reference to an \c std::ios
     * formatting object.
     *
     * Before the XML stream is created, pass an empty formatting object
     * pointer to this constructor through the make() function. This
     * constructor, in defining the underlying character stream for the XML
     * stream, creates a formatting object for the stream and places the
     * address of that object in the pointer reference. The calling
     * application can then use this formatting object to manipulate data
     * formats in the XML stream. See the corresponding
     * \ref RWXmlObjectInputStreamImp::make(std::istream&, std::ios*&, bool) "make()"
     * function description for an example.
     */
    RWXmlObjectInputStreamImp(std::istream& sourceStream, std::ios*& formatter, bool escape)
        :
        RWObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWCharFromStreambufInputStreamImp::make(*(sourceStream.rdbuf())), formatter)),
        table_(rwnil),
        escapeText_(escape),
        attributesRead_(false)
    {
        ;
    }

    //--Used by derived classes to initialize the previous processing stream.
    //--Parameter 'sourceStream' is a handle to the previous processing stream.
    //--Throws no exceptions.
    /**
     * Used by the make() function and potentially by derived classes to
     * initialize the source data stream if the required input stream is a
     * RWDataInputStream istream.
     *
     * The parameter \a sourceStream is a handle to the initialized stream.
     *
     * The parameter \a escape sets whether the input stream contains
     * escapes for XML reserved characters that need to be unescaped.
     * Usually this would be because the objects serialized out with
     * RWXmlObjectOutputStreamImp contained embedded XML.
     *
     * The reserved characters are:
     *
     * \code
     * <  >  &  "  '
     * \endcode
     *
     * You get slightly better performance if the \a escape parameter is set
     * to \c false, but before doing so be certain that your data does not
     * contain reserved characters.
     */
    RWXmlObjectInputStreamImp(const RWDataInputStream& sourceStream, bool escape)
        :
        RWObjectInputStreamImp(sourceStream),
        table_(rwnil),
        escapeText_(escape),
        attributesRead_(false)
    {
        ;
    }
    // Make sure the storeTable is deleted even if an exception is thrown
    ~RWXmlObjectInputStreamImp()
    {
        if (getContextNestingLevel() > 0) {
            RWXmlObjectInputStreamImp::closeOuterContext(false);
        }
    }

public:
    //--Constructs an 'RWXmlObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream that is used as the source of bytes.
    //--Throws no exceptions.
    /**
     * Constructs an RWXmlObjectInputStreamImp instance that uses the data
     * stream \a source as its source of bytes, and returns a handle to it.
     * Use this method when the data input stream is a standard library
     * istream.
     *
     * The parameter \a escape sets whether the input stream contains
     * escapes for XML reserved characters that need to be unescaped.
     * Usually this would be because the objects serialized out with
     * RWXmlObjectOutputStreamImp contained embedded XML. By default, this
     * parameter is set to \c true.
     *
     * The reserved characters are:
     *
     * \code
     * <  >  &  "  '
     * \endcode
     *
     * You get slightly better performance if the \a escape parameter is set
     * to \c false, but before doing so be certain that your data does not
     * contain reserved characters.
     */
    static RWObjectInputStream make(std::istream& source, bool escape = true);

    //--Constructs an 'RWXmlObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream that is used as the source of bytes.
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Throws no exceptions.
    /**
     * \copydoc RWXmlObjectInputStreamImp::make(std::istream&, bool)
     *
     * This function also takes a pointer reference to an \c std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed through this make()
     * function to the constructor:
     *
     * \code
     * std::ios* formatter;            // uninitialized pointer
     * RWObjectInputStream xistr =
     * RWXmlObjectInputStreamImp::make(infile,formatter);
     * \endcode
     *
     * The constructor, in creating the underlying character stream for the
     * XML stream, creates a formatting object for the stream and places the
     * address of that object in the pointer reference. The calling
     * application can then use this formatting object to manipulate data
     * formats in the XML stream.
     *
     * \code
     * formatter->precision(15);       // manipulate data format
     * \endcode
     */
    static RWObjectInputStream make(std::istream& source, std::ios*& formatter, bool escape = true);

    //--Constructs an 'RWXmlObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the data stream that is used as the source of bytes.
    //--Throws no exceptions.
    /**
     * Constructs an RWXmlObjectInputStreamImp instance that uses the data
     * stream \a source as its source of bytes, and returns a handle to it.
     * Use this method when the data input stream is a RWDataInputStream
     * istream.
     *
     * The parameter \a escape sets whether the input stream contains
     * escapes for XML reserved characters that need to be unescaped.
     * Usually this would be because the objects serialized out with
     * RWXmlObjectOutputStreamImp contained embedded XML. By default, this
     * parameter is set to \c true.
     *
     * The reserved characters are:
     *
     * \code
     * <  >  &  "  '
     * \endcode
     *
     * You get slightly better performance if the \a escape parameter is set
     * to \c false, but before doing so be certain that your data does not
     * contain reserved characters.
     */
    static RWObjectInputStream make(RWDataInputStream& source, bool escape = true);

    inline void           eatWhitespace();
    inline void           eatTerminator();
    inline void           openPrimitive();
    inline void           closePrimitive();
    inline void           getTag(RWSymbol& tag);
    void                  getSymbol(RWSymbol& value);
    void                  getQuotedString(RWCString& result);
    bool             parseAttribute(RWSymbol& name, RWCString& value);
    virtual RWSymbol      startBlock();
    virtual void          endBlock();
    virtual bool     needToRead(const void*& obj);
    virtual void*         getNewObject(const std::type_info* base);
    virtual RWSymbol      readTypeInfo();
    virtual void          rememberObject(const void* obj);
    virtual bool     startMember(RWSymbol& memberName,
                                 RWStreamType& memberType);
    virtual void          endMember();
    virtual RWSymbol      startSequence(int& count, RWStreamType& elementType);
    virtual void          startElement(int& position);
    virtual void          endElement();
    virtual void          endSequence();
    virtual RWSymbol      startMap(int& count, RWStreamType& keyType, RWStreamType& valueType);
    virtual void          startAssocKey();
    virtual void          startAssocValue();
    virtual void          endAssoc();
    virtual void          endMap();

    /**
     * Reads a value from the stream, where the type of the value is defined
     * by the first parameter.
     */
    virtual void          getString(RWCString& str);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getWString(RWWString& str);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUString(RWBasicUString& str);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getBool(bool& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getChar(char& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedChar(unsigned char& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getSignedChar(signed char& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getShort(short& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedShort(unsigned short& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getInt(int& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedInt(unsigned int& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getLong(long& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedLong(unsigned long& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getFloat(float& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getDouble(double& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getWchar_t(wchar_t& value);

#if !defined(RW_NO_LONG_LONG)
    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getLongLong(long long& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedLongLong(unsigned long long& value);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getLongDouble(long double& value);
#endif

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getCharacter(char& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getWCharacter(wchar_t& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUCharacter(RWUChar& value);

    /**
     * \copydoc RWXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getSizeT(size_t& value);


protected:
    // Unescape characters in char or string values to allow embedded XML
    virtual char getUnescapedChar();
    virtual char getUnescapedChar(char firstChar);

    //--This here to prevent getString(RWCString&) from hiding the base class'
    //--function.
    virtual RWSize getString(char* string, RWSize count)
    {
        return RWObjectInputStreamImp::getString(string, count);
    }

    virtual RWSize getWString(wchar_t* wstring, RWSize count)
    {
        return RWObjectInputStreamImp::getWString(wstring, count);
    }

    virtual RWSize getUString(RWUChar* ustring, RWSize count)
    {
        return RWObjectInputStreamImp::getUString(ustring, count);
    }

    virtual void          getNextCharacter(char& value);
    virtual void          peekNextCharacter(char& value);
    virtual void          getNextDataCharacter(char& value);
    virtual RWCString     findAttribute(const RWSymbol& name);
    virtual void          readAttributes();

private:
    void readString(RWCString& value);
    std::queue<char> charQueue_;
    std::list<std::pair<RWSymbol, RWCString> > attributes_;
    //   std::map<RWSymbol,RWCString> attributes_;
    bool attributesRead_;
};


inline void RWXmlObjectInputStreamImp::eatWhitespace()
{
    char c;
    peekNextCharacter(c);
    while (isspace(c)) {
        getNextCharacter(c);
        peekNextCharacter(c);
    }
}

inline void RWXmlObjectInputStreamImp::eatTerminator()
{
    char c;
    do {
        getNextCharacter(c);
    }
    while (c != '>');
}

inline void RWXmlObjectInputStreamImp::openPrimitive()
{
    openContext(true);
    if (getContextNestingLevel() <= 2) {
        eatTerminator();
    }
}

inline void RWXmlObjectInputStreamImp::closePrimitive()
{
    if (getContextNestingLevel() <= 2) {
        eatTerminator();
    }
    closeContext();
}

inline void RWXmlObjectInputStreamImp::getTag(RWSymbol& tag)
{
    eatWhitespace();
    char c;
    getNextCharacter(c);
    getSymbol(tag);
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_xmlstreams_RWXmlObjectInputStreamImp_h_
