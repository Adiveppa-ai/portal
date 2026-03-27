#ifndef rw_serial_RWObjectOutputStream_h_
#define rw_serial_RWObjectOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWObjectOutputStream.h#1 $
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

#include <rw/serial/RWObjectOutputStreamImp.h>
#include <rw/serial/RWTInsertProxy.h>
#include <rw/serial/RWTypeInfo.h>
#include <rw/serial/StreamTraits.h>
#include <rw/serial/pkgdefs.h>
#include <rw/stream/RWDataOutputStream.h>
#include <rw/types/RWSymbol.h>
#include <rw/defs.h>
#include <rw/rwdate.h>
#include <rw/rwint.h>
#include <rw/tools/bustring.h>
#include <rw/tools/datetime.h>
#include <rw/tools/decport.h>
#include <string>


/**
 * \ingroup serialization_package
 *
 * \brief
 * Handle class for all the object output stream implementation classes.
 *
 * Handle class for all the object output stream implementation classes.
 * Implements the handle idiom from the handle/body pattern. With the
 * exception of constructors and assignment operators, all member functions
 * forward directly to the implementation associated with this handle during
 * construction.
 */
class RW_SERIAL_GLOBAL RWObjectOutputStream : public RWDataOutputStream
{
public:

    /**
     * Constructor.
     *
     * \param body
     * The stream implementation to associate with this handle.
     */
    explicit RWObjectOutputStream(RWObjectOutputStreamImp* body)
        : RWDataOutputStream(body) {}

    /**
     * Copy constructor. Throws no exceptions.
     *
     * \param handle
     * A data stream handle used to initialize the newly created handle.
     */
    RWObjectOutputStream(const RWObjectOutputStream& handle)
    // this should come from the pointer package
        : RWDataOutputStream(handle) {}

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A data stream handle used to initialize this handle.
     */
    RWObjectOutputStream& operator=(const RWObjectOutputStream& handle)
    {
        this->RWHandleBase::operator=(handle);
        return *this;
    }


public:
    /**
     * Called by RWWithObjectOutputContext \c ctor to open a context in
     * which multiple references to a single object are resolved.
     */
    void openContext(bool writeContext = true)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).openContext(writeContext);
    }

    /**
     * Called by RWWithObjectOutputContext \c dtor to close an open context.
     */
    void closeContext(bool writeContext = true)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).closeContext(writeContext);
    }

    /**
     * Outputs tokens that identify the start of a new object.
     *
     * \param typeInfo
     * Identifies the type of the new object, if such information is
     * available.
     */
    void startBlock(const RWSymbol& typeInfo)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).startBlock(typeInfo);
    }

    /**
     * Outputs tokens that identify the end of an object.
     */
    void endBlock()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).endBlock();
    }

    /**
     * Outputs tokens that identify the start of a parent class.
     *
     * \param typeInfo
     * Identifies the type of the parent class, if such information is
     * available.
     */
    void startParent(const RWSymbol& typeInfo)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).startParent(typeInfo);
    }

    /**
     * Outputs tokens that identify the end of an parent class.
     */
    void endParent()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).endParent();
    }

    /**
     * Returns \c true when the referenced object has not yet been written
     * to the stream in the current context. Otherwise, outputs tokens
     * identifying this object as having been previously streamed, and the
     * function returns \c false.
     */
    bool  needToWrite(const void* obj)
    {
        return static_cast<RWObjectOutputStreamImp&>(this->body()).needToWrite(obj);
    }

    /**
     * Output is a token representing a null pointer.
     */
    void writeNullPtr()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).writeNullPtr();
    }

    /**
     * Output is a token indicating that an object will be created by the
     * factory.
     */
    void newObjectMarker()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).newObjectMarker();
    }

    /**
     * Outputs the type information required to factory an object of the
     * correct dynamic type (derived class) on input.
     *
     * \param typeInfo
     * Identifies the type of the new object, if such information is
     * available.
     */
    void  writeTypeInfo(const RWSymbol& typeInfo)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).writeTypeInfo(typeInfo);
    }

    /**
     * Called by streaming operators to record each instance streamed out,
     * in case it is referenced again in the same context.
     *
     * \param obj
     * Holds the address of the instance.
     */
    void rememberObject(const void* obj)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).rememberObject(obj);
    }

    /**
     * Called for before each data member by the streamContents() function.
     * Metadata about the field may or may not be written to the stream,
     * depending on the implementation. This function returns \c true if
     * data is actually written out; otherwise returns \c false.
     *
     * \param memberName
     * Identifies the name of the member.
     *
     * \param memberType
     * Identifies the type of the member.
     */
    void writeMemberInfo(const RWSymbol& memberName, RWStreamType memberType)
    {
        static_cast<RWObjectOutputStreamImp&>(
            this->body()).writeMemberInfo(memberName, memberType);
    }

    /**
     * Called by streamContents() after each data member is written.
     *
     * \param memberName
     * Identifies the name of the member.
     */
    void endMember(const RWSymbol& memberName)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).endMember(memberName);
    }

    /**
     * Called by the output operators for collection types at the start of a
     * sequence.
     *
     * \param count
     * Contains the number of items in the collection.
     *
     * \param elementType
     * Contains the type of element in the collection.
     *
     * \param typeInfo
     * Contains the type of the collection itself.
     */
    void startSequence(int count, RWStreamType elementType, const RWSymbol& typeInfo)
    {
        static_cast<RWObjectOutputStreamImp&>(
            this->body()).startSequence(count, elementType, typeInfo);
    }

    /**
     * Called by the output operators for collection types before each
     * element in a sequence.
     *
     * \param position
     * Contains the position of the element.
     */
    void startElement(int position)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).startElement(position);
    }

    /**
     * Called by the output operators for collection types after each
     * element in a sequence.
     */
    void endElement()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).endElement();
    }

    /**
     * Called by the output operators for collection types at the end of a
     * sequence.
     */
    void endSequence()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).endSequence();
    }

    /**
     * Called by the output operators for association types (hash tables,
     * etc.) at the start.
     *
     * \param count
     * Contains the number of items in the association.
     *
     * \param keyType
     * Contains the type of key in the association.
     *
     * \param valueType
     * Contains the type of value in the association.
     *
     * \param typeInfo
     * Contains the type of the association (collection) itself.
     */
    void startMap(int count, RWStreamType keyType,
                  RWStreamType valueType, const RWSymbol& typeInfo)
    {
        static_cast<RWObjectOutputStreamImp&>(
            this->body()).startMap(count, keyType, valueType, typeInfo);
    }

    /**
     * Called by the output operators for association types before each key.
     */
    void startAssocKey()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).startAssocKey();
    }

    /**
     * Called by the output operators for association types after each key
     * and before each value.
     */
    void startAssocValue()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).startAssocValue();
    }

    /**
     * Called by the output operators for association types after each
     * value.
     */
    void endAssoc()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).endAssoc();
    }

    /**
     * Called by the output operators for association types after all the
     * pairs.
     */
    void endMap()
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).endMap();
    }

    /**
     * Writes an RWSymbol to the stream.
     */
    void putSymbol(const RWSymbol& sym)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).putSymbol(sym);
    }

    /**
     * Writes an RWCString to the stream.
     */
    void putString(const RWCString& str)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).putString(str);
    }

    /**
     * Writes a \b std::string to the stream.
     */
    void putString(const std::string& str)
    {
        static_cast<RWObjectOutputStreamImp&>(
            this->body()).putString(RWCString(str));
    }

    /**
     * Writes an RWWString to the stream.
     */
    void putWString(const RWWString& str)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).putWString(str);
    }

    /**
     * Writes an RWBasicUString to the stream.
     */
    void putUString(const RWBasicUString& str)
    {
        static_cast<RWObjectOutputStreamImp&>(this->body()).putUString(str);
    }

    /**
     * Sets up the instance name for the next object to be written out.
     */
    void setNameForNextObject(const RWCString& instanceName)
    {
        static_cast<RWObjectOutputStreamImp&>(
            this->body()).setNameForNextObject(instanceName);
    }


    // =======================================================================
    // The following is necessary for disambiguation on some compilers.
    // -----------------------------------------------------------------------

    // Documented in base class.
    RWObjectOutputStream& operator<<(char value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(unsigned char value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(signed char value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(short value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(unsigned short value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(int value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(unsigned int value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(long value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(unsigned long value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(float value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(double value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(bool value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

    // Documented in base class.
    RWObjectOutputStream& operator<<(wchar_t value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }

#if !defined(RW_NO_LONG_LONG)
    RWObjectOutputStream& operator<<(long long value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }
    RWObjectOutputStream& operator<<(unsigned long long value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }
#endif

#ifndef RW_NO_LONG_DOUBLE
    // Documented in base class.
    RWObjectOutputStream& operator<<(long double value)
    {
        RWDataOutputStream::operator<<(value);
        return *this;
    }
#endif


};



/**
 * \ingroup serialization_package
 *
 * \brief
 * Represents a guard object that opens and closes a context within a
 * lexical scope for output streams.
 *
 * This class consists of a guard object that opens and closes a context
 * within a lexical scope. Simply declare an automatic instance of this
 * class initialized with a object output stream, and all object references
 * within the scope of the automatic variable will be streamed within the
 * same context.
 *
 * \example
 * \code
 * // Output one or more objects in the same context.
 *
 * #include <rw/serial/RWCompactObjectOutputStreamImp.h>
 * #include <rw/serial/RWObjectOutputStream.h>
 * #include <fstream.h>
 * #include <iostream.h>
 *
 * int main() {
 *   ofstream fstrm;
 *   fstrm.open("RWWithObjectOutputContext.out", ios::out);
 *
 *   RWObjectOutputStream out =
 *     RWCompactObjectOutputStreamImp::make(fstrm);
 *
 *   RWWithObjectOutputContext context(out);
 *
 *   int i,j;
 *   i = 53;
 *   j = 42;
 *
 *   out << i << j;
 *
 *   return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWObjectOutputStream
 */
class RW_SERIAL_SUN_SYMBOLIC RWWithObjectOutputContext
{
public:
    /**
     * Constructor taking an object output stream reference argument. If
     * \a writeContext is \c true, then write out any document header at the
     * outer context.
     */
    RWWithObjectOutputContext(RWObjectOutputStream& strm, bool writeContext = true)
        : strm_(strm)
    {
        strm_.openContext(writeContext);
    }

    /**
     * Constructor taking an object output stream pointer argument. If
     * \a writeContext is \c true, then write out in any document header at
     * the outer context.
     */
    RWWithObjectOutputContext(RWObjectOutputStreamImp* strm, bool writeContext = true)
        : strm_(strm)
    {
        strm_.openContext(writeContext);
    }

    /**
     * Destructor automatically closes the context.
     */
    ~RWWithObjectOutputContext()
    {
        strm_.closeContext();
    }
private:
    RWObjectOutputStream strm_;
};

//--Stream out an 'RWSymbol'.
inline
RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWSymbol& sym)
{
    strm.putSymbol(sym);
    return strm;
}


//--Stream out an 'RWCString'.
inline
RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWCString& str)
{
    strm.putString(str);
    return strm;
}

//--Stream out a 'string'.
inline
RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const std::string& str)
{
    strm.putString(str);
    return strm;
}

//--Stream out an 'RWWString'.
inline
RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWWString& str)
{
    strm.putWString(str);
    return strm;
}

//--Stream out an 'RWBasicUString'.
inline
RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWBasicUString& str)
{
    strm.putUString(str);
    return strm;
}

//--Stream out an 'RWDate' (use proxy to avoid ambiguous overloads).
inline RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWDate& obj)
{
    strm << obj.asString("%m/%d/%Y");
    return strm;
}

//--Stream out an 'RWDateTime'
inline RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWDateTime& obj)
{
    strm.putString(obj.asString("%x;%X", RWLocale::global()));
    return strm;
}


//--Stream out an 'RWDecimalPortable'
inline RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWDecimalPortable& target)
{
    strm.putString(target.asString(RWLocale::global()));
    return strm;
}

//--Stream out an 'RWInteger'
inline RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWInteger& target)
{
    strm << target.value();
    return strm;
}

//--Stream out an 'RWTInsertProxy' ie write out an object with its instance name
template <class T>
inline RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWTInsertProxy<T>& target)
{
    strm.setNameForNextObject(target.instanceName_);
    strm << target.instance_;
    return strm;
}

#if !defined(_MSC_VER) && !defined(__IBMCPP__)

template <class T>
RWObjectOutputStream& operator<<(RWObjectOutputStream& vstream,  T* b)
{
    if (b) {
        RWWithObjectOutputContext outputContext(vstream);
        if (vstream.needToWrite(b)) {
            vstream.newObjectMarker();
            vstream.writeTypeInfo(RWTypeInfo::symbol(typeid(*((T*)b))));
            vstream.rememberObject(b);
            if (rwStreamType(b) != RW_NESTED_OBJECT  &&
                    rwStreamType(b) != RW_SEQ &&
                    rwStreamType(b) != RW_ASSOC) {
                vstream.startBlock(RWTypeInfo::symbol(typeid(*((T*)b))));
                vstream << *b;
                vstream.endBlock();
            }
            else {
                vstream << *b;
            }
        }
    }
    else {
        vstream.writeNullPtr();
    }
    return vstream;
}

#endif // !(_MSC_VER) && !(__IBMCPP__)

#endif // rw_serial_RWObjectOutputStream_h_
