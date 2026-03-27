#ifndef rw_serial_RWObjectInputStream_h_
#define rw_serial_RWObjectInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWObjectInputStream.h#1 $
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

#include <rw/serial/RWObjectInputStreamImp.h>
#include <rw/serial/RWObjectOutputStream.h>
#include <rw/serial/RWTPseudoMethod1.h>
#include <rw/serial/StreamTraits.h>
#include <rw/serial/pkgdefs.h>
#include <rw/stream/RWDataInputStream.h>
#include <rw/factory/RWTFactory1.h>
#include <rw/types/RWSymbol.h>
#include <rw/tools/bustring.h>
#include <typeinfo>

#define RW_DECLARE_PSEUDO_METHOD_INTERNAL(T)                    \
extern RW_SERIAL_GLOBAL                                       \
RWTPseudoMethod1<const T*, RWObjectOutputStream&> saveGuts##T;  \
extern RW_SERIAL_GLOBAL                                       \
RWTPseudoMethod1<T*, RWObjectInputStream&> restoreGuts##T;

#define RW_DECLARE_PSEUDO_METHOD(T)                             \
extern RW_SERIAL_GLOBAL                                         \
RWTPseudoMethod1<const T*, RWObjectOutputStream&> saveGuts##T;  \
extern RW_SERIAL_GLOBAL                                         \
RWTPseudoMethod1<T*, RWObjectInputStream&> restoreGuts##T;

#define RW_DEFINE_PSEUDO_METHOD(T)                      \
RWTPseudoMethod1<const T*, RWObjectOutputStream&>       \
saveGuts##T (RWTExtSaveGuts<T, T>::mkFunctor());        \
RWTPseudoMethod1<T*,RWObjectInputStream&>               \
restoreGuts##T (RWTExtRestoreGuts<T, T>::mkFunctor());


/**
 * \ingroup serialization_package
 *
 * \brief
 * Handle class for object input stream implementation classes.
 *
 * RWObjectInputStream is the handle class for object input stream
 * implementation classes. Implements the handle idiom from the handle/body
 * pattern. With the exception of constructors, assignment operators, and
 * getFactory(), all member functions forward directly to the implementation
 * associated with this handle during construction.
 */
class RW_SERIAL_SYMBOLIC RWObjectInputStream : public RWDataInputStream
{
public:

    /**
     * Constructor.
     *
     * \param body
     * Stream Implementation to associate with this handle.
     */
    explicit RWObjectInputStream(RWObjectInputStreamImp* body)
        : RWDataInputStream(body)
    { }

    /**
     * Copy constructor. Throws no exceptions.
     *
     * \param handle
     * Data stream handle used to initialize this handle.
     */
    RWObjectInputStream(const RWObjectInputStream& handle)
        : RWDataInputStream(handle)
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * Data stream handle used to initialize this handle.
     */
    RWObjectInputStream& operator=(const RWObjectInputStream& handle)
    {
        this->RWHandleBase::operator=(handle);
        return *this;
    }

    /**
     * Obtains the singleton factory used to create objects dynamically from
     * streams.
     */
    static
    RWTFactory1<void*, RWCString, RWSymbol>* getFactory();

    /**
     * Called by RWWithObjectInputContext \c ctor to open a context in which
     * multiple references to a single object are resolved.
     */
    void  openContext(bool readContext = true)
    {
        static_cast<RWObjectInputStreamImp&>(
            this->body()).openContext(readContext);
    }

    /**
     * Called by RWWithObjectInputContext \c dtor to close an open context.
     */
    void closeContext(bool readContext = true)
    {
        static_cast<RWObjectInputStreamImp&>(
            this->body()).closeContext(readContext);
    }

    /**
     * Inputs tokens that identify the start of a new object. Returns an
     * RWSymbol representing the new object. Depending on the implementation
     * class associated with this handle, the RWSymbol may be empty.
     */
    RWSymbol startBlock()
    {
        return static_cast<RWObjectInputStreamImp&>(
                   this->body()).startBlock();
    }

    /**
     * Inputs tokens that identify the end of an object.
     */
    void endBlock()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).endBlock();
    }

    /**
     * Inputs tokens that identify the start of a parent class.
     *
     * \param typeInfo
     * Identifies the type of the parent class, if such information is
     * available.
     */
    void startParent(const RWSymbol& typeInfo)
    {
        static_cast<RWObjectInputStreamImp&>(
            this->body()).startParent(typeInfo);
    }

    /**
     * Inputs tokens that identify the end of an parent class.
     */
    void endParent()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).endParent();
    }

    // Returns  'true' when  a new  object  is encountered  in the  input
    // stream  which  must be  factored,  and  have  its contents  read.
    // Otherwise, the  stream contains a reference to  an existing object
    // which  is passed  out via  the  'obj' argument,  and the  function
    // returns 'false'
    bool
    needToRead(const void*& obj)
    {
        return static_cast<RWObjectInputStreamImp&>(
                   this->body()).needToRead(obj);
    }

    /**
     * Reads the dynamic type information (derived class) from the input
     * stream, and factories an instance of this type.
     *
     * \param base
     * The static type (base class) of the field being read.
     */
    void*  getNewObject(const std::type_info* base)
    {
        return static_cast<RWObjectInputStreamImp&>(
                   this->body()).getNewObject(base);
    }

    /**
     * Reads the type information for a class instance from the stream and
     * returns it as a symbol.
     */
    RWSymbol    readTypeInfo()
    {
        return static_cast<RWObjectInputStreamImp&>(
                   this->body()).readTypeInfo();
    }

    /**
     * Called by streaming operators to record each instance streamed in, in
     * case it is referenced again in the same context.
     */
    void rememberObject(const void* obj)
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).rememberObject(obj);
    }

    /**
     * Called for before each data member by the streamContents() function.
     * Metadata about the field may or may not be read from the stream
     * depending on the implementation. If data is read, returns \c true and
     * parameter \a memberName will contain the name of the member;
     * otherwise returns \c false.
     */
    bool startMember(RWSymbol& memberName,
                     RWStreamType& memberType)
    {
        return static_cast<RWObjectInputStreamImp&>(
                   this->body()).startMember(memberName, memberType);
    }

    /**
     * Called by streamContents() after each data member is read.
     */
    void          endMember()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).endMember();
    }

    /**
     * Called by the input operators for collection types at the start of a
     * sequence. Returns an RWSymbol representing the collection.
     *
     * \param count
     * Contains the number of items in the collection.
     *
     * \param elementType
     * Contains the type of element in the collection.
     */
    RWSymbol  startSequence(int& count, RWStreamType& elementType)
    {
        return static_cast<RWObjectInputStreamImp&>(
                   this->body()).startSequence(count, elementType);
    }

    /**
     * Called by the input operators for collection types before each
     * element in a sequence.
     *
     * \param position
     * Contains the position of the element in the collection.
     */
    void  startElement(int& position)
    {
        static_cast<RWObjectInputStreamImp&>(
            this->body()).startElement(position);
    }

    /**
     * Called by the input operators for collection types after each element
     * in a sequence.
     */
    void  endElement()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).endElement();
    }

    /**
     * Called by the input operators for collection types at the end of a
     * sequence.
     */
    void  endSequence()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).endSequence();
    }

    /**
     * Called by the input operators for association types (hash tables,
     * etc.) at the start of a sequence. Returns an RWSymbol representing
     * the collection.
     *
     * \param count
     * Contains the number of items in the association.
     *
     * \param keyType
     * Contains the type of key in the association.
     *
     * \param valueType
     * Contains the type of value in the association.
     */
    RWSymbol startMap(int& count,
                      RWStreamType& keyType,
                      RWStreamType& valueType)
    {
        return static_cast<RWObjectInputStreamImp&>(
                   this->body()).startMap(count, keyType, valueType);
    }

    /**
     * Called by the input operators for association types before each key.
     */
    void startAssocKey()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).startAssocKey();
    }

    /**
     * Called by the input operators for association types after each key
     * and before each value.
     */
    void startAssocValue()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).startAssocValue();
    }

    /**
     * Called by the input operators for association types after each value.
     */
    void  endAssoc()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).endAssoc();
    }

    /**
     * Called by the input operators for association types after all the
     * pairs.
     */
    void endMap()
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).endMap();
    }

    /**
     * Reads an RWSymbol value from the stream.
     *
     * \param value
     * The RWSymbol value to be read from the stream.
     */
    void getSymbol(RWSymbol& value)
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).getSymbol(value);
    }

    /**
     * Reads an RWCString value from the stream.
     *
     * \param value
     * The RWCString value to be read from the stream.
     */
    void  getString(RWCString& value)
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).getString(value);
    }

    /**
     * Reads a \b std::string value from the stream.
     *
     * \param value
     * The \b std::string value to be read from the stream.
     */
    void  getString(std::string& value)
    {
        RWCString st;
        static_cast<RWObjectInputStreamImp&>(this->body()).getString(st);
#if !defined(RW_COPY_ON_WRITE_STRING)
        value.assign(st.std());
#else
        value.assign(st.data(), st.length());
#endif
    }

    /**
     * Reads an RWWString value from the stream.
     *
     * \param value
     * The RWWString value to be read from the stream.
     */
    void  getWString(RWWString& value)
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).getWString(value);
    }

    /**
     * Reads an RWBasicUString value from the stream.
     *
     * \param value
     * The RWBasicUString value to be read from the stream.
     */
    void  getUString(RWBasicUString& value)
    {
        static_cast<RWObjectInputStreamImp&>(this->body()).getUString(value);
    }

    // =======================================================================
    // The following are necessary for disambiguation on some compilers.
    // -----------------------------------------------------------------------

    RWObjectInputStream& operator>>(char& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(unsigned char& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(signed char& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(short& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(unsigned short& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(int& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(unsigned int& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(long& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(unsigned long& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(float& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(double& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(bool& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(wchar_t& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
#if !defined(RW_NO_LONG_LONG)
    RWObjectInputStream& operator>>(long long& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
    RWObjectInputStream& operator>>(unsigned long long& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
#endif
#ifndef RW_NO_LONG_DOUBLE
    RWObjectInputStream& operator>>(long double& value)
    {
        RWDataInputStream::operator>>(value);
        return *this;
    }
#endif

};

/**
 * \ingroup serialization_package
 *
 * \brief
 * Represents a guard object that opens and closes a context within a
 * lexical scope for input streams.
 *
 * This class consists of a guard object that opens and closes a context
 * within a lexical scope. To use RWWithObjectInputContext, simply declare
 * an automatic instance of this class initialized with a object input
 * stream, and all object references within the scope of the automatic
 * variable will be streamed within the same context.
 *
 * \example
 * \code
 * // Read in one or more objects from an object stream that
 * // were output in the same context.
 *
 * #include <rw/serial/RWCompactObjectInputStreamImp.h>
 * #include <rw/serial/RWObjectInputStream.h>
 * #include <fstream.h>
 * #include <iostream.h>
 *
 * int main() {
 *   ifstream fstrm;
 *   fstrm.open("RWWithObjectOutputContext.out",
 *     ios::in | ios::nocreate);
 *
 *   if (!fstrm) {
 *     cout << "The file does not exist."<< endl;
 *   }
 *
 *   else {
 *     RWObjectInputStream in =
 *       RWCompactObjectInputStreamImp::make(fstrm);
 *
 *     RWWithObjectInputContext context(in);
 *
 *     int i,j;
 *
 *     in >> i >> j;
 *     cout << "i = " << i << "  j = " << j << endl;
 *
 *   }
 *   return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWObjectInputStream
 */
class RW_SERIAL_SYMBOLIC RWWithObjectInputContext
{

public:
    /**
     * Constructor taking an object input stream reference argument. If
     * \a readContext is \c true, then read in any document header at the
     * outer context.
     */
    RWWithObjectInputContext(RWObjectInputStream& strm, bool readContext = true)
        : strm_(strm)
    {
        strm_.openContext(readContext);
    }

    /**
     * Constructor taking an object input stream pointer argument. If
     * \a readContext is \c true, then read in any document header at the
     * outer context.
     */
    RWWithObjectInputContext(RWObjectInputStreamImp* strm,
                             bool readContext = true)
        : strm_(strm)
    {
        strm_.openContext(readContext);
    }

    /**
     * Destructor automatically closes context.
     */
    ~RWWithObjectInputContext()
    {
        strm_.closeContext();
    }

private:
    RWObjectInputStream strm_;
};

// Stream in an 'RWCString'.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm, RWCString& target)
{
    strm.getString(target);
    return strm;
}

inline void streamContents(RWCString* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}

RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWCString)

// Stream in a 'std::string'.
inline RWObjectInputStream& operator>>(RWObjectInputStream& strm,
                                       std::string&         target)
{
    strm.getString(target);
    return strm;
}

inline void streamContents(std::string* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}

extern RW_SERIAL_GLOBAL RWTPseudoMethod1 <
const std::string*, RWObjectOutputStream& > saveGutsstd_string;

extern RW_SERIAL_GLOBAL RWTPseudoMethod1 <
std::string*, RWObjectInputStream& > restoreGutsstd_string;

// Stream in an 'RWWString'.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm, RWWString& target)
{
    strm.getWString(target);
    return strm;
}

inline void streamContents(RWWString* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}

RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWWString)

// Stream in an 'RWBasicUString'.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm,
                                RWBasicUString&      target)
{
    strm.getUString(target);
    return strm;
}

inline void streamContents(RWBasicUString* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}

RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWBasicUString)

// Stream in an 'RWSymbol'.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm, RWSymbol& target)
{
    strm.getSymbol(target);
    return strm;
}

inline void streamContents(RWSymbol* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}

RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWSymbol)

#include <rw/rwdate.h>

// Stream in an RWDate.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm, RWDate& target)
{
    RWCString text;
    strm >> text;
    target = text;
    return strm;
}

inline void streamContents(RWDate* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}
RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWDate)

#include <rw/tools/datetime.h>
// Stream in an RWDateTime.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm, RWDateTime& target)
{
    RWCString text;
    strm >> text;
    target = RWDateTime(text, RWDateTime::setBoth, RWLocale::global());
    return strm;
}

inline void streamContents(RWDateTime* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}
RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWDateTime)

#include <rw/tools/decport.h>

// Stream in an RWDecimalPortable.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm,
                                RWDecimalPortable&   target)
{
    RWCString text;
    strm >> text;
    target = RWDecimalPortable(text.data());
    return strm;
}

inline void streamContents(RWDecimalPortable* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}

RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWDecimalPortable)

#include <rw/rwint.h>

// Stream in an RWInteger.
inline
RWObjectInputStream& operator>>(RWObjectInputStream& strm, RWInteger& target)
{
    int tmp;
    strm >> tmp;
    target = RWInteger(tmp);
    return strm;
}

inline void streamContents(RWInteger* local_this,
                           RWObjectInputStream* instream,
                           RWObjectOutputStream* outstream)
{
    if (instream) {
        *instream >> *local_this;
    }
    else if (outstream) {
        *outstream << *local_this;
    }
}

RW_DECLARE_PSEUDO_METHOD_INTERNAL(RWInteger)

#if !defined(_MSC_VER) && !defined(__IBMCPP__)

template <class T>
RWObjectInputStream& operator>>(RWObjectInputStream& vstream, T*& b)
{
    RWWithObjectInputContext inputContext(vstream);
    if (!vstream.isGood()) {
        return vstream;
    }
    const std::type_info* baseType = &(typeid(T));
    const void* vp = rwnil;
    if (vstream.needToRead(vp)) {
        vp = vstream.getNewObject(baseType);
        if (vp != rwnil) {
            b = static_cast<T*>(const_cast<void*>(vp));
            RWWithObjectInputContext tmp(vstream);
            if (rwStreamType(b) != RW_NESTED_OBJECT) {
                vstream.startBlock();
                vstream >> *b;
                vstream.endBlock();
            }
            else {
                vstream >> *b;
            }
        }
    }
    else if (vp != rwnil) {
        b = static_cast<T*>(const_cast<void*>(vp));
    }
    else {
        b = 0;
    }

    return vstream;
}

#endif // !(_MSC_VER) && !(__IBMCPP__)

#endif // rw_serial_RWObjectInputStream_h_
