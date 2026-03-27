#ifndef rw_serial_RWCompactObjectInputStreamImp_h_
#define rw_serial_RWCompactObjectInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWCompactObjectInputStreamImp.h#1 $
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

#include <rw/serial/RWObjectInputStream.h>
#include <rw/serial/RWObjectInputStreamImp.h>
#include <rw/serial/pkgdefs.h>
#include <rw/factory/RWTSingleFactory1.h>
#include <rw/rwstore.h>
#include <rw/tools/bustring.h>


/**
 * \ingroup serialization_package
 *
 * \brief
 * Reads objects encoded in a compact format from the supplied
 * RWDataInputStream.
 *
 * The class RWCompactObjectInputStreamImp reads objects encoded in a
 * compact format from the supplied RWDataInputStream. The format of this
 * stream resembles that produced when RWCollectable instances are persisted
 * using RW virtual streams. Implements the body idiom from the handle/body
 * pattern. The stream can optionally be annotated with member (attribute)
 * name and type information to support generic parsing.
 *
 * \example
 * \code
 * // Open an fstream to serve as our source.
 * ifstream s("foo.dat");
 *
 * // Create a portable stream using the fstream.
 * RWpistream pstrm(s);
 *
 * // Create a compact data stream using the portable stream.
 * RWObjectInputStream in = RWCompactObjectInputStreamImp::make(
 *          RWDataFromVirtualInputStreamImp::make(pstrm));
 *
 * // Read integer from compact data stream
 * int i;
 * in >> i;
 * \endcode
 * \endexample
 */
class RW_SERIAL_GLOBAL RWCompactObjectInputStreamImp : public RWObjectInputStreamImp
{

protected:
    RWReadTable* table_;
    bool annotateStream_;
    virtual void          openOuterContext(bool readContext);
    virtual void          closeOuterContext(bool readContext);

    /**
     * Used by derived classes to initialize the next processing stream.
     * Throws no exceptions.
     *
     * \param sourceStream
     * Serves as a handle to the previous processing stream.
     *
     * \param annotateStream
     * Indicates whether the stream is annotated.
     */
    RWCompactObjectInputStreamImp(const RWDataInputStream& sourceStream,
                                  bool annotateStream)
        : RWObjectInputStreamImp(sourceStream),
          table_(rwnil),
          annotateStream_(annotateStream)
    {
        ;
    }

public:

    /**
     * Constructs an RWCompactObjectInputStreamImp instance that uses
     * \a source as its source of bytes, and returns a handle to it. Throws
     * no exceptions.
     *
     * \param source
     * The data stream used as the source of bytes.
     *
     * \param annotateStream
     * Indicates whether the stream is annotated.
     */
    static RWObjectInputStream make(const RWDataInputStream& source,
                                    bool annotateStream = false);
    virtual RWSymbol      startBlock();
    virtual void          endBlock();
    virtual bool     needToRead(const void*& obj);
    virtual void*         getNewObject(const std::type_info* base);
    virtual RWSymbol      readTypeInfo();
    virtual void          rememberObject(const void* obj);
    virtual bool     startMember(RWSymbol& memberName,
                                 RWStreamType& memberType);
    virtual RWSymbol      startSequence(int& count, RWStreamType& elementType);
    virtual RWSymbol      startMap(int& count, RWStreamType& keyType, RWStreamType& valueType);
    virtual void          getString(RWCString& str);
    virtual void          getWString(RWWString& str);
    virtual void          getUString(RWBasicUString& str);


protected:
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
};

#endif // rw_serial_RWCompactObjectInputStreamImp_h_
