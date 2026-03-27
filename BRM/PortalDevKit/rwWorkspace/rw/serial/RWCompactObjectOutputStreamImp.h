#ifndef rw_serial_RWCompactObjectOutputStreamImp_h_
#define rw_serial_RWCompactObjectOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWCompactObjectOutputStreamImp.h#1 $
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

#include <rw/serial/RWObjectOutputStream.h>
#include <rw/serial/RWObjectOutputStreamImp.h>
#include <rw/serial/pkgdefs.h>
#include <rw/rwstore.h>
#include <rw/tools/bustring.h>


/**
 * \ingroup serialization_package
 *
 * \brief
 * Writes objects in a compact format to the supplied RWDataOutputStream.
 *
 * The class RWCompactObjectOutputStreamImp writes objects in a compact
 * format to the supplied RWDataOutputStream. The format of this stream
 * resembles that produced when RWCollectable instances are persisted using
 * RW virtual streams. Implements the body idiom from the handle/body
 * pattern. The stream can optionally be annotated with member (attribute)
 * name and type information to support generic parsing.
 *
 * \example
 * \code
 * // Create a string stream to serve as our sink
 * ostringstream s;
 *
 * // Create a portable stream from the string stream
 * RWpostream pstrm(s);
 *
 * // Create a compact data stream using the portable stream
 * RWObjectOutputStream out = RWCompactObjectOutputStreamImp::make(
 *                            RWDataToVirtualOutputStreamImp::make(pstrm));
 *
 * // Write integer value 1 to compact data stream
 * out << 1;
 * \endcode
 * \endexample
 */
class RW_SERIAL_GLOBAL RWCompactObjectOutputStreamImp : public RWObjectOutputStreamImp
{
protected:
    RWStoreTable* table_;
    bool annotateStream_;
    virtual void          openOuterContext(bool writeContext);
    virtual void          closeOuterContext(bool writeContext);

    /**
     * Used by derived classes to initialize the next processing stream.
     * Throws no exceptions.
     *
     * \param sinkStream
     * A handle to the next processing stream.
     *
     * \param annotateStream
     * Indicates whether the stream will be annotated.
     */
    RWCompactObjectOutputStreamImp(const RWDataOutputStream& sinkStream,
                                   bool annotateStream)
        : RWObjectOutputStreamImp(sinkStream),
          table_(rwnil),
          annotateStream_(annotateStream)
    {
        ;
    }

public:

    /**
     * Constructs an RWCompactObjectOutputStreamImp instance that uses the
     * parameter \a sink as its sink of bytes, and returns a handle to it.
     * Throws no exceptions.
     *
     * \param sink
     * The data stream used as the sink of bytes.
     *
     * \param annotateStream
     * Indicates whether the stream will be annotated.
     */
    static RWObjectOutputStream make(const RWDataOutputStream& sink,
                                     bool annotateStream = false);
    virtual void          startBlock(const RWSymbol&);
    virtual void          endBlock();
    virtual bool     needToWrite(const void* obj);
    virtual void          writeNullPtr();
    virtual void          newObjectMarker();
    virtual void          writeTypeInfo(const RWSymbol& typeInfo);
    virtual void          rememberObject(const void* obj);
    virtual void          writeMemberInfo(const RWSymbol& memberName,
                                          RWStreamType memberType);
    virtual void          startSequence(int count, RWStreamType elementType, const RWSymbol&);
    virtual void          startMap(int count, RWStreamType keyType, RWStreamType valueType, const RWSymbol&);
    virtual void          putString(const RWCString& str);
    virtual void          putWString(const RWWString& str);
    virtual void          putUString(const RWBasicUString& str);

    virtual void          setNameForNextObject(const RWCString&) {}

protected:
    //--This here to prevent putString(RWCString&) from hiding the base class'
    //--function.
    virtual void putString(const char* string, RWSize count)
    {
        RWObjectOutputStreamImp::putString(string, count);
    }

    virtual void putWString(const wchar_t* wstring, RWSize count)
    {
        RWObjectOutputStreamImp::putWString(wstring, count);
    }

    virtual void putUString(const RWUChar* ustring, RWSize count)
    {
        RWObjectOutputStreamImp::putUString(ustring, count);
    }
};

#endif // rw_serial_RWCompactObjectOutputStreamImp_h_
