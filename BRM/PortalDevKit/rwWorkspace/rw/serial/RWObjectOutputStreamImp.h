#ifndef rw_serial_RWObjectOutputStreamImp_h_
#define rw_serial_RWObjectOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWObjectOutputStreamImp.h#1 $
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
#include <rw/stream/RWFilteredDataOutputStreamImp.h>
#include <rw/types/RWSymbol.h>
#include <rw/defs.h>
#include <rw/tools/bustring.h>


/**
 * \ingroup serialization_package
 *
 * \brief
 * Base class for all object output stream implementations.
 *
 * Base class for all object output stream implementations. Inherits default
 * operations for streaming primitives from the data output stream.
 *
 * See the corresponding handle class, RWObjectOutputStream, for the
 * description of the object output stream interface.
 */
class RW_SERIAL_GLOBAL RWObjectOutputStreamImp : public RWFilteredDataOutputStreamImp
{
protected:

    /**
     * Used by derived classes to initialize the next processing stream.
     * Throws no exceptions.
     *
     * \param sinkStream
     * A handle to the next processing stream.
     */
    RWObjectOutputStreamImp(const RWDataOutputStream& sinkStream)
        : RWFilteredDataOutputStreamImp(sinkStream)
        , nameForNextObject_("")
        , contextNestingLevel_(0)
    {
        ;
    }

    // If writeContext is true then write out any document header at the outer
    // context.
    /**
     * Really opens a new context. This function is called by openContext()
     * when a context is not already open.
     */
    virtual void          openOuterContext(bool writeContext) = 0;

    // If writeContext is true then write out any document footer at the outer
    // context.
    /**
     * Really closes an open context. This function is called when the
     * number of closeContext() calls matches the number of openContext()
     * calls.
     */
    virtual void          closeOuterContext(bool writeContext) = 0;

public:
    /**
     * Called by RWWithObjectOutputContext \c ctor to open a context in
     * which multiple references to a single object are resolved.
     */
    virtual void          openContext(bool writeContext = true)
    {
        if (contextNestingLevel_++ == 0) {
            openOuterContext(writeContext);
        }
    }

    /**
     * Called by RWWithObjectOutputContext \c dtor to close an open context.
     */
    virtual void          closeContext(bool writeContext = true)
    {
        if (--contextNestingLevel_ == 0) {
            closeOuterContext(writeContext);
        }
    }

    /**
     * Outputs tokens that identify the start of a new object.
     *
     * \param typeInfo
     * Identifies the type of the new object, if such information is
     * available.
     */
    virtual void          startBlock(const RWSymbol& typeInfo) = 0;

    /**
     * Outputs tokens that identify the end of an object.
     */
    virtual void          endBlock() = 0;

    /**
     * Outputs tokens that identify the start of a parent class.
     */
    virtual void          startParent(const RWSymbol&) {}

    /**
     * Outputs tokens that identify the end of an parent class.
     */
    virtual void          endParent() {}

    /**
     * Returns \c true when the referenced object has not yet been written
     * to the stream in the current context. Otherwise, tokens are output
     * identifying this object as having been previously streamed, and the
     * function returns \c false.
     */
    virtual bool     needToWrite(const void* obj) = 0;

    /**
     * Output is a token representing a null pointer.
     */
    virtual void          writeNullPtr() = 0;

    /**
     * Output is a token indicating that an object will be created by the
     * factory.
     */
    virtual void          newObjectMarker() = 0;

    /**
     * Outputs the type information required to factory an object of the
     * correct dynamic type (derived class) on input.
     *
     * \param typeInfo
     * Identifies the type of the new object, if such information is
     * available.
     */
    virtual void          writeTypeInfo(const RWSymbol& typeInfo) = 0;

    /**
     * Called by streaming operators to record each instance streamed out,
     * in case it is referenced again in the same context.
     *
     * \param obj
     * Holds the address of the instance.
     */
    virtual void          rememberObject(const void* obj) = 0;

    /**
     * Called for before each data member by the streamContents() function.
     * Metadata about the field may or may not be written to the stream,
     * depending on the implementation. This function returns \c true if
     * data is actually written out. Otherwise, it returns \c false.
     *
     * \param memberName
     * Identifies the name of the member.
     *
     * \param memberType
     * Identifies the type of the member.
     */
    virtual void          writeMemberInfo(const RWSymbol& memberName,
                                          RWStreamType memberType) = 0;

    /**
     * Called by streamContents() after each data member is written.
     */
    virtual void          endMember(const RWSymbol&) {}

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
    virtual void          startSequence(int count, RWStreamType elementType, const RWSymbol& typeInfo) = 0;

    /**
     * Called by the output operators for collection types before each
     * element in a sequence.
     */
    virtual void          startElement(int) {}

    /**
     * Called by the output operators for collection types after each
     * element in a sequence.
     */
    virtual void          endElement() {}

    /**
     * Called by the output operators for collection types at the end of a
     * sequence.
     */
    virtual void          endSequence() {}

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
    virtual void          startMap(int count, RWStreamType keyType, RWStreamType valueType, const RWSymbol& typeInfo) = 0;

    /**
     * Called by the output operators for association types before each key.
     */
    virtual void          startAssocKey() {}

    /**
     * Called by the output operators for association types after each key
     * and before each value.
     */
    virtual void          startAssocValue() {}

    /**
     * Called by the output operators for association types after each
     * value.
     */
    virtual void          endAssoc() {}

    /**
     * Called by the output operators for association types after all the
     * pairs.
     */
    virtual void          endMap() {}

    /**
     * Writes an RWSymbol to the stream.
     */
    virtual void          putSymbol(const RWSymbol& sym);

    /**
     * Writes an RWCString to the stream.
     */
    virtual void          putString(const RWCString& str) = 0;

    /**
     * Writes an RWWString to the stream.
     */
    virtual void          putWString(const RWWString& str) = 0;

    /**
     * Writes an RWBasicUString to the stream.
     */
    virtual void          putUString(const RWBasicUString& str) = 0;

    /**
     * Sets up the instance name for the next object to be written out.
     */
    virtual void          setNameForNextObject(const RWCString& str) = 0;

protected:
    //--This here to prevent putString(RWCString&) from hiding the base class'
    //--function.
    // Documented in base class.
    virtual void putString(const char* string, RWSize count)
    {
        RWFilteredDataOutputStreamImp::putString(string, count);
    }

    // Documented in base class.
    virtual void putWString(const wchar_t* wstring, RWSize count)
    {
        RWFilteredDataOutputStreamImp::putWString(wstring, count);
    }

    // Documented in base class.
    virtual void putUString(const RWUChar* ustring, RWSize count)
    {
        RWFilteredDataOutputStreamImp::putUString(ustring, count);
    }

    /**
     * Returns the current context nesting level. 0 indicates no open
     * context.
     */
    int                  getContextNestingLevel()
    {
        return contextNestingLevel_;
    }

    /**
     * The name for the next object inserted or extracted. This name will be
     * cleared as soon as an object has been written or read, and ignored if
     * empty.
     */
    RWCString nameForNextObject_;

private:
    int contextNestingLevel_;

};

#endif // rw_serial_RWObjectOutputStreamImp_h_
