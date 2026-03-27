#ifndef rw_stream_RWBufferedCharInputStreamImp_h_
#define rw_stream_RWBufferedCharInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWBufferedCharInputStreamImp.h#1 $
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

#include <rw/stream/RWCharInputStream.h>
#include <rw/stream/RWFilteredCharInputStreamImp.h>
#include <rw/stream/RWTInputStreamBufferImp.h>
#include <rw/stream/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4231)
#  pragma warning(disable : 4251)
#endif


// forward declaration
class RWCString;

// Visual C++ disallows the exporting of templates into DLL libraries.
// When a regular (non-templatized) exported class uses a class template
// (as an instance variable), the complete specialization must be in the
// library. This is handled by an instantiation directive when the library is
// built, and an "extern" instantiation directive when clients use the
// library.  This causes a warning about the use of a non-standard language
// extension (which it is), which is to be turned off as per instructions
// from Microsoft.
//
// For more info see:
// http://support.microsoft.com/support/kb/articles/Q168/9/58.asp
#if defined(RW_STREAM_DLL) && defined(_WIN32)
#  if !defined(_RWBUILD_streams)
extern template class RW_STREAM_GLOBAL RWTInputStreamBufferImp<RWCharInputStream, RWFilteredCharInputStreamImp>;
#  else
template class RW_STREAM_GLOBAL RWTInputStreamBufferImp<RWCharInputStream, RWFilteredCharInputStreamImp>;
#  endif
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Implements a buffer that can be used with narrow character input streams.
 *
 * Class RWBufferedCharInputStreamImp implements a buffer that can be used
 * with narrow character input streams. The size of the buffer is specified
 * in its static member make() function, which is used to create it.
 *
 * \example
 * \code
 * // This is an input buffer used for narrow character streams.
 *
 * #include <rw/stream/RWBufferedCharInputStreamImp.h>
 * #include <rw/stream/RWCharFromStreambufInputStreamImp.h>
 * #include <rw/stream/RWStreambufFromCharInputStream.h>
 * #include <fstream.h>
 * #include <iostream.h>
 * #include <rw/rwfile.h>
 *
 * int main() {
 *   filebuf fbuf;
 *
 *   if(!RWFile::Exists("RWBufferedCharOutputStreamImp.out")) {
 *     cout << "The input file does not exist."<< endl;
 *   }
 *
 *   else {
 *     fbuf.open("RWBufferedCharOutputStreamImp.out",
 *       ios::in);
 *
 *     RWCharInputStream charStream =
 *       RWCharFromStreambufInputStreamImp::make(fbuf);
 *
 *     RWCharInputStream bufferedStream =
 *       RWBufferedCharInputStreamImp::make(charStream, 128);
 *
 *     RWStreambufFromCharInputStream adaptor(bufferedStream);
 *
 *     istream in(&adaptor);
 *
 *     int i;
 *     in >> i;
 *     cout << i << endl;
 *
 *   }
 *
 *   return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_STREAM_GLOBAL RWBufferedCharInputStreamImp : public RWTInputStreamBufferImp<RWCharInputStream, RWFilteredCharInputStreamImp>
{

public:

    /**
     * Constructs a RWBufferedCharInputStreamImp instance that uses
     * \a sourceStream as its source of narrow characters, and returns a
     * handle to it. The internal buffer is dynamically allocated to be of
     * size #RW_STREAM_BUFFER_SIZE.
     *
     * \exception RWExternalStreamException
     * Thrown if an illegal buffer size was requested or if the memory
     * allocation request for the buffer fails.
     *
     * \param sourceStream
     * Input stream that will serve as the source of narrow characters.
     */
    static RWCharInputStream make(const RWCharInputStream& sourceStream)
    {
        return RWCharInputStream(new RWBufferedCharInputStreamImp(sourceStream));
    }

    /**
     * Constructs a RWBufferedCharInputStreamImp instance that uses
     * \a sourceStream as its source of narrow characters, and returns a
     * handle to it. The internal buffer is dynamically allocated to be of
     * size \a bufSize.
     *
     * \exception RWExternalStreamException
     * Thrown if an illegal buffer size was requested or if the memory
     * allocation request for the buffer fails.
     *
     * \param sourceStream
     * The input stream that will serve as the source of narrow characters.
     *
     * \param bufSize
     * The buffer capacity in number of narrow characters.
     */
    static RWCharInputStream make(const RWCharInputStream& sourceStream, RWSize bufSize)
    {
        return RWCharInputStream(new RWBufferedCharInputStreamImp(sourceStream, bufSize));
    }

    /**
     * Constructs an RWBufferedCharInputStreamImp instance that uses
     * \a sourceStream as its source of narrow characters, and returns a
     * handle to it. The internal buffer is initialized using the
     * pre-allocated narrow character's array of size \a bufSize.
     *
     * \exception RWExternalStreamException
     * Thrown if an illegal buffer size was requested or if the memory
     * allocation request for the buffer fails.
     *
     * \param sourceStream
     * The input stream that will serve as the source of narrow characters.
     *
     * \param buffer
     * A pre-allocated buffer of size \a bufSize to be used internally by
     * the constructed RWBufferedCharInputStreamImp object.
     *
     * \param bufSize
     * The buffer capacity in number of narrow characters.
     */
    static RWCharInputStream make(const RWCharInputStream& sourceStream, char* buffer, RWSize bufSize)
    {
        return RWCharInputStream(new RWBufferedCharInputStreamImp(sourceStream, buffer, bufSize));
    }

    // documented in base class.
    virtual void readStringUntil(RWCString& string, char delim);

protected:

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of narrow characters, as well as the internal buffer
     * capacity, which will be equal to #RW_STREAM_BUFFER_SIZE.
     *
     * \exception RWExternalStreamException
     * Thrown if an illegal buffer size was requested or if the memory
     * allocation request for the buffer fails.
     *
     * \param sourceStream
     * Input stream that will serve as the source of narrow characters.
     */
    RWBufferedCharInputStreamImp(const RWCharInputStream& sourceStream);

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of narrow characters, as well as the buffer capacity.
     *
     * \exception RWExternalStreamException
     * Thrown if an illegal buffer size was requested or if the memory
     * allocation request for the buffer fails.
     *
     * \param sourceStream
     * Input stream that will serve as the source of narrow characters.
     *
     * \param bufSize
     * Buffer capacity in number of narrow characters.
     */
    RWBufferedCharInputStreamImp(const RWCharInputStream& sourceStream, RWSize bufSize);

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of narrow characters, as well as the internal buffer.
     *
     * \exception RWExternalStreamException
     * Thrown if an illegal buffer size was requested or if the memory
     * allocation request for the buffer fails.
     *
     * \param sourceStream
     * Input stream that will serve as the source of narrow characters.
     *
     * \param buffer
     * Pre-allocated buffer of size \a bufSize to be used internally by the
     * constructed RWBufferedCharInputStreamImp object.
     *
     * \param bufSize
     * Buffer capacity in number of narrow characters.
     */
    RWBufferedCharInputStreamImp(const RWCharInputStream& sourceStream, char* buffer, RWSize bufSize);

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWBufferedCharInputStreamImp_h_
