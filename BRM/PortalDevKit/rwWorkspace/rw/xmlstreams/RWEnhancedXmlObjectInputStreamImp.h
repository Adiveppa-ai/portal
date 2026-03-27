#ifndef rw_xmlstreams_RWEnhancedXmlObjectInputStreamImp_h_
#define rw_xmlstreams_RWEnhancedXmlObjectInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWEnhancedXmlObjectInputStreamImp.h#1 $
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

#include <rw/xmlstreams/RWTXmlTraits.h>
#include <rw/xmlstreams/RWXmlObjectStreamCommon.h>
#include <rw/xmlstreams/RWXmlStreamElement.h>
#include <rw/xmlstreams/pkgdefs.h>
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

// Disabling warning #1744:
// field of class type without a DLL interface used in a class with a DLL
// interface.  The data member data_ (std::vector) is not exported and thusly
// The compiler is concerned it may have to create multiple instances of it.
// This is private data that is never returned so in this scenario the warning
// can be silenced.
#if (_MSC_VER)
#  if defined(__INTEL_COMPILER)
#    pragma warning(disable : 1744)
#  else
#    pragma warning(push)
#    pragma warning(disable : 4251)
#  endif
#endif

//--The class 'RWEnhancedXmlObjectInputStreamImp' reads objects encoded in XML
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
//--RWObjectInputStream in = RWEnhancedXmlObjectInputStreamImp::make(s);
//--
//--// Read integer from XML data stream
//--int i;
//--s >> i;
//--
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Reads objects encoded in XML from the supplied RWDataInputStream.
 *
 * The class RWEnhancedXmlObjectInputStreamImp reads objects encoded in XML
 * from the supplied RWDataInputStream.
 *
 * Implements the body idiom from the handle/body pattern.
 *
 * \example
 * \code
 * // Open an fstream to serve as our source
 * ifstream s("foo.xml");
 *
 * // Create an XML data stream using the fstream
 * RWObjectInputStream in =
 *               RWEnhancedXmlObjectInputStreamImp::make(s);
 *
 * // Read integer from XML data stream
 * int i;
 * s >> i;
 * \endcode
 * \endexample
 */
class RW_XMLSTREAMS_GLOBAL RWEnhancedXmlObjectInputStreamImp : public RWObjectInputStreamImp,
    public RWXmlObjectStreamCommon
{

protected:
    typedef RWTXmlTraits<char> Traits;
    RWReadTable* table_;
    bool escapeText_;
    RWXmlStreamElement* rootElem_;
    RWXmlStreamElement* curElem_;
    RWXmlStreamElement dummyElem_;

    virtual void          openOuterContext(bool readContext);
    virtual void          closeOuterContext(bool readContext);

    //--Used by derived classes to initialize the previous processing stream.
    //--Parameter 'sourceStream' is a handle to the previous processing stream.
    //--Throws no exceptions.
    /**
     * Used by derived classes to initialize the previous processing stream.
     * Throws no exceptions.
     *
     * The parameter \a sourceStream is a handle to the previous processing
     * stream.
     */
    RWEnhancedXmlObjectInputStreamImp(std::istream& sourceStream, bool escape)
        :
        RWObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWCharFromStreambufInputStreamImp::make(*(sourceStream.rdbuf())))),
        table_(rwnil),
        escapeText_(escape),
        rootElem_(&dummyElem_),
        curElem_(&dummyElem_),
        putBack_(false)

    {
        ;
    }

    //--Used by derived classes to initialize the previous processing stream.
    //--Parameter 'sourceStream' is a handle to the previous processing stream.
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Throws no exceptions.
    /**
     * Used by derived classes to initialize the previous processing stream.
     * Throws no exceptions.
     *
     * The parameter \a sourceStream is a handle to the previous processing
     * stream
     *
     * The parameter \a formatter will be returned with a reference to the
     * formatting object
     */
    RWEnhancedXmlObjectInputStreamImp(std::istream& sourceStream, std::ios*& formatter, bool escape)
        :
        RWObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWCharFromStreambufInputStreamImp::make(*(sourceStream.rdbuf())), formatter)),
        table_(rwnil),
        escapeText_(escape),
        rootElem_(&dummyElem_),
        curElem_(&dummyElem_),
        putBack_(false)
    {
        ;
    }

    //--Used by derived classes to initialize the previous processing stream.
    //--Parameter 'sourceStream' is a handle to the previous processing stream.
    //--Throws no exceptions.
    /**
     * Used by derived classes to initialize the previous processing stream.
     * Throws no exceptions.
     *
     * The parameter \a sourceStream is a handle to the previous processing
     * stream.
     */
    RWEnhancedXmlObjectInputStreamImp(const RWDataInputStream& sourceStream, bool escape)
        :
        RWObjectInputStreamImp(sourceStream),
        table_(rwnil),
        escapeText_(escape),
        rootElem_(&dummyElem_),
        curElem_(&dummyElem_),
        putBack_(false)
    {
        ;
    }

    /**
     * Destructor. Make sure the \c storeTable is deleted even if an
     * exception is thrown.
     */
    ~RWEnhancedXmlObjectInputStreamImp()
    {
        if (getContextNestingLevel() > 0) {
            RWEnhancedXmlObjectInputStreamImp::closeOuterContext(false);
        }
        if (rootElem_ != &dummyElem_) {
            delete rootElem_;
        }
    }

public:
    //--Constructs an 'RWEnhancedXmlObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream that is used as the source of bytes.
    //--Throws no exceptions.
    /**
     * Used by derived classes to initialize the previous processing stream.
     * Constructs an RWEnhancedXmlObjectInputStreamImp instance that uses
     * the data stream \a source as its source of bytes, and returns a
     * handle to it. Throws no exceptions.
     *
     * Use this method when the data input stream is a standard library
     * \c std::istream.
     *
     * The parameter \a source is the istream that is used as the source of
     * bytes.
     *
     * The parameter \a escape sets whether the input stream contains
     * escapes for XML reserved characters that need to be unescaped. Escape
     * is set to \c true if the objects serialized out with
     * RWXmlObjectOutputStreamImp contained embedded XML. Defaults to
     * \c true.
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

    //--Constructs an 'RWEnhancedXmlObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream that is used as the source of bytes.
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Throws no exceptions.
    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::make(std::istream&, bool)
     *
     * This function also takes a pointer reference to an \c std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed through this make()
     * function to the constructor:
     *
     * \code
     * std::ios* formatter;            // uninitialized pointer
     * RWObjectInputStream xistr =
     * RWEnhancedXmlObjectInputStreamImp::make(infile,formatter);
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
     *
     * The parameter \a source is the istream that is used as the source of
     * bytes.
     *
     * The parameter \a formatter will be returned with a reference to the
     * formatting object.
     */
    static RWObjectInputStream make(std::istream& source, std::ios*& formatter, bool escape = true);

    //--Constructs an 'RWEnhancedXmlObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the data stream that is used as the source of bytes.
    //--Throws no exceptions.
    /**
     * Constructs an RWEnhancedXmlObjectInputStreamImp instance that uses
     * \a source as its source of bytes, and returns a handle to it. Throws
     * no exceptions.
     *
     * The parameter \a source is the data stream that is used as the source
     * of bytes.
     */
    static RWObjectInputStream make(RWDataInputStream& source, bool escape = true);

    inline void           openPrimitive();
    inline void           closePrimitive();
    void                  getSymbol(RWSymbol& value);
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
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getWString(RWWString& str);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUString(RWBasicUString& str);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getBool(bool& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getChar(char& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedChar(unsigned char& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getSignedChar(signed char& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getShort(short& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedShort(unsigned short& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getInt(int& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedInt(unsigned int& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getLong(long& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedLong(unsigned long& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getFloat(float& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getDouble(double& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getWchar_t(wchar_t& value);

#if !defined(RW_NO_LONG_LONG)
    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getLongLong(long long& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUnsignedLongLong(unsigned long long& value);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getLongDouble(long double& value);
#endif

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getCharacter(char& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getWCharacter(wchar_t& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
     */
    virtual void          getUCharacter(RWUChar& value);

    /**
     * \copydoc RWEnhancedXmlObjectInputStreamImp::getString(RWCString&)
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

private:
    // Start Parser

    //-- Read one character from the input
    //--
    //-- Returns the next character
    //--
    char readOne();
    //--
    //-- Put back one character so it will be available for the next read
    //--
    //-- Parameter 'cur' is the character to put back.
    //--
    void putBack(char cur);
    //--
    //-- Read the next XML element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'parent' holds the current element (the parent of the one to read)
    //-- Returns the parsed element
    //--
    RWXmlStreamElement* readNextElement(char& cur, RWXmlStreamElement& parent);
    //--
    //-- Read a token
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will be returned with the token
    //-- Returns the last character read
    //--
    char readToken(char cur, RWCString& token);
    //--
    //-- Read past the closing tag of the current element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain any data read before the closing tag
    //-- Returns the last character read
    //--
    char readToClose(char cur, RWCString& token);
    //--
    //-- Read everything to the next '>' character
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain any data read before the '>' character
    //-- Returns the last character read
    //--
    char readWholeName(char cur, RWCString& token);
    //--
    //-- Read in an entire attribute (name and value)
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain the attribute string or RWCString() if
    //--           no attribute is available.
    //-- Returns the last character read
    //--
    char readAttribute(char cur, RWCString& token);
    //--
    //-- Read in an attribute value
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain the value without quotes or RWCString() if
    //--           no value is available.
    //-- Returns the last character read
    //--
    char readAttributeValue(char cur, RWCString& token);
    //--
    //-- Read all attributes in an element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'element' will have the attributes added to it.
    //-- Returns the last character read
    //--
    char readAttributes(char cur, RWXmlStreamElement& element);
    //--
    //-- Read all attributes in an element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'element' will have the value added to it
    //--           (including nested elements).
    //-- Returns the last character read
    //--
    char readValue(char cur, RWXmlStreamElement& element);

    // End Parser

    RWXmlStreamElement::const_iterator findSequenceElement(int position);
    void readString(RWCString& value);
    char putBackChar_;
    bool putBack_;
    std::queue<char> charQueue_;
};


inline void RWEnhancedXmlObjectInputStreamImp::openPrimitive()
{
    openContext(true);
}

inline void RWEnhancedXmlObjectInputStreamImp::closePrimitive()
{
    closeContext();
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_xmlstreams_RWEnhancedXmlObjectInputStreamImp_h_
