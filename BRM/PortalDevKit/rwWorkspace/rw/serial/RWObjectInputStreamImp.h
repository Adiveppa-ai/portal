#ifndef rw_serial_RWObjectInputStreamImp_h_
#define rw_serial_RWObjectInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWObjectInputStreamImp.h#1 $
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

#include <rw/serial/StreamTraits.h>
#include <rw/serial/pkgdefs.h>
#include <rw/stream/RWFilteredDataInputStreamImp.h>
#include <rw/types/RWSymbol.h>
#include <rw/tools/bustring.h>
#include <typeinfo>


/**
 * \ingroup serialization_package
 *
 * \brief
 * Base class for all object input stream implementations.
 *
 * Base class for all object input stream implementations. The derivation
 * from filtered data input stream provides default implementations for
 * output of all primitive types and allows the low level stream formatting
 * to be controlled by delegation to a separate data input stream object.
 *
 * See the corresponding handle class, RWObjectInputStream, for the
 * description of the object input stream interface.
 *
 * \sa
 * RWObjectInputStream
 */
class RW_SERIAL_GLOBAL RWObjectInputStreamImp : public RWFilteredDataInputStreamImp
{
protected:

    /**
     * Really opens a new context, called by openContext() when a context is
     * not already open.
     */
    virtual void          openOuterContext(bool readContext) = 0;

    /**
     * Really closes an open context, called when closeContext() calls match
     * the number of openContext() calls.
     */
    virtual void          closeOuterContext(bool readContext) = 0;

    /**
     * Used by derived classes to initialize the attached source stream.
     * Throws no exceptions.
     *
     * \param sourceStream
     * Handle to the attached source stream.
     */
    RWObjectInputStreamImp(const RWDataInputStream& sourceStream)
        : RWFilteredDataInputStreamImp(sourceStream),
          contextNestingLevel_(0),
          lookAheadCharValid_(false),
          lookAheadCharacterValid_(false)
    {
        ;
    }

public:
    /**
     * Called by RWWithObjectInputContext \c ctor to open a context in which
     * multiple references to a single object are resolved.
     */
    virtual void          openContext(bool readContext = true)
    {
        if (contextNestingLevel_++ == 0) {
            openOuterContext(readContext);
        }
    }

    /**
     * Called by RWWithObjectInputContext \c dtor to close an open context.
     */
    virtual void          closeContext(bool readContext = true)
    {
        if (--contextNestingLevel_ == 0) {
            closeOuterContext(readContext);
        }
    }

    /**
     * Inputs tokens that identify the start of a new object. Returns an
     * RWSymbol representing the new object. Depending on the implementation
     * class associated with this handle, the RWSymbol may be empty.
     */
    virtual RWSymbol      startBlock() = 0;

    /**
     * Inputs tokens that identify the end of an object.
     */
    virtual void          endBlock() = 0;

    /**
     * Inputs tokens that identify the start of a parent class.
     */
    virtual void          startParent(const RWSymbol&) {}

    /**
     * Inputs tokens that identify the end of an parent class.
     */
    virtual void          endParent() {}
    virtual bool     needToRead(const void*& obj) = 0;

    /**
     * Reads the dynamic type information (derived class) from the input
     * stream, and factories an instance of this type.
     *
     * \param base
     * Represents the static type (base class) of the field being read.
     */
    virtual void*         getNewObject(const std::type_info* base) = 0;

    /**
     * Reads the type information for an class instance from the stream and
     * returns it as a symbol.
     */
    virtual RWSymbol      readTypeInfo() = 0;

    /**
     * Called by streaming operators to record each instance streamed in, in
     * case it is referenced again in the same context.
     */
    virtual void          rememberObject(const void* obj) = 0;

    /**
     * Called for before each data member by the streamContents() function,
     * metadata about the field may or may not be read from the stream
     * depending on the implementation. If data is read (returning \c true),
     * then parameter \a memberName will contain the name of the member.
     * Otherwise returns \c false.
     */
    virtual bool     startMember(RWSymbol& memberName,
                                 RWStreamType& memberType) = 0;

    /**
     * Called by streamContents() after each data member is read.
     */
    virtual void          endMember() {}

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
    virtual RWSymbol      startSequence(int& count, RWStreamType& elementType) = 0;

    /**
     * Called by the input operators for collection types before each
     * element in a sequence.
     */
    virtual void          startElement(int&) {}

    /**
     * Called by the input operators for collection types after each element
     * in a sequence.
     */
    virtual void          endElement() {}

    /**
     * Called by the input operators for collection types at the end of a
     * sequence.
     */
    virtual void          endSequence() {}

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
    virtual RWSymbol      startMap(int& count, RWStreamType& keyType, RWStreamType& valueType) = 0;

    /**
     * Called by the input operators for association types before each key.
     */
    virtual void          startAssocKey() {}

    /**
     * Called by the input operators for association types after each key
     * and before each value.
     */
    virtual void          startAssocValue() {}

    /**
     * Called by the input operators for association types after each value.
     */
    virtual void          endAssoc() {}

    /**
     * Called by the input operators for association types after all the
     * pairs.
     */
    virtual void          endMap() {}

    /**
     * Reads an RWSymbol value from the stream.
     *
     * \param value
     * The RWSymbol value to be read from the stream.
     */
    virtual void getSymbol(RWSymbol& value);

    /**
     * Reads an RWCString value from the stream.
     *
     * \param value
     * The RWCString value to be read from the stream.
     */
    virtual void getString(RWCString& value) = 0;

    /**
     * Reads an RWWString value from the stream.
     *
     * \param value
     * The RWWString value to be read from the stream.
     */
    virtual void getWString(RWWString& value) = 0;

    /**
     * Reads an RWBasicUString value from the stream.
     *
     * \param value
     * The RWBasicUString value to be read from the stream.
     */
    virtual void getUString(RWBasicUString& value) = 0;

    /**
     * Forward reads a single \c char value from the attached source stream.
     * Value is stored for subsequent call to getChar().
     *
     * \param value
     * The \c char value to be read from the attached source stream.
     */
    virtual void peekChar(char& value);

    /**
     * Forward reads a single \c char value from the attached source stream.
     * Value stored by peekChar() is used if available.
     *
     * \param value
     * The \c char value to be read from the attached source stream.
     */
    virtual void getChar(char& value);

    /**
     * Forward reads a single \c char value from the attached source stream.
     * Value is stored for subsequent call to getCharacter().
     *
     * \param value
     * The \c char value to be read from the attached source stream.
     */
    virtual void peekCharacter(char& value);

    /**
     * Forward reads a single \c char value from the attached source stream.
     * Value stored by peekCharacter() is used if available.
     *
     * \param value
     * The \c char value to be read from the attached source stream.
     */
    virtual void getCharacter(char& value);

protected:
    //--This here to prevent getString(RWCString&) from hiding the base class'
    //--function.
    virtual RWSize getString(char* string, RWSize count)
    {
        return RWFilteredDataInputStreamImp::getString(string, count);
    }

    virtual RWSize getWString(wchar_t* wstring, RWSize count)
    {
        return RWFilteredDataInputStreamImp::getWString(wstring, count);
    }

    virtual RWSize getUString(RWUChar* ustring, RWSize count)
    {
        return RWFilteredDataInputStreamImp::getUString(ustring, count);
    }

    int  getContextNestingLevel()
    {
        return contextNestingLevel_;
    }

private:
    int contextNestingLevel_;
    // true if the next char has been stored by peekChar()
    // false if getChar() has been called since the last peekChar()
    bool lookAheadCharValid_;
    // A stored value set by calling peekChar
    char      lookAheadChar_;
    // true if the next char has been stored by peekCharacter()
    // false if getCharacter() has been called since the last peekCharacter()
    bool lookAheadCharacterValid_;
    // A stored value set by calling peekCharacter
    char      lookAheadCharacter_;
};

#endif // rw_serial_RWObjectInputStreamImp_h_
