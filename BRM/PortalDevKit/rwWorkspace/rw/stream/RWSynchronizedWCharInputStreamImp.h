#ifndef rw_stream_RWSynchronizedWCharInputStreamImp_h_
#define rw_stream_RWSynchronizedWCharInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWSynchronizedWCharInputStreamImp.h#1 $
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

#include <rw/stream/RWFilteredWCharInputStreamImp.h>
#include <rw/stream/RWTInputStreamLockImp.h>
#include <rw/stream/RWWCharInputStream.h>
#include <rw/stream/pkgdefs.h>

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
#  pragma warning (disable:4231)
#  if !defined(_RWBUILD_streams)
extern template class RW_STREAM_GLOBAL RWTInputStreamLockImp<RWWCharInputStream, RWFilteredWCharInputStreamImp>;
#  else
template class RW_STREAM_GLOBAL RWTInputStreamLockImp<RWWCharInputStream, RWFilteredWCharInputStreamImp>;
#  endif
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Implementation of a simple lock stream that can be used with a wide
 * character input stream.
 *
 * Class RWSynchronizedWCharInputStreamImp implements a simple lock stream
 * that is used with wide character input stream. The stream locks its
 * internal synchronization mechanism before forwarding input requests to
 * its associated source stream, and then unlocks the internal
 * synchronization mechanism upon completion. The stream's internal
 * synchronization mechanism is locked using a guard object, ensuring its
 * proper release in the event that an exception is thrown.
 */
class RW_STREAM_GLOBAL RWSynchronizedWCharInputStreamImp : public RWTInputStreamLockImp<RWWCharInputStream, RWFilteredWCharInputStreamImp>
{

public:

    /**
     * Constructs an RWSynchronizedWCharInputStreamImp instance that uses
     * \a sourceStream as its source of wide characters, and returns a
     * handle to it. Throws no exceptions.
     *
     * \param sourceStream
     * The output stream that will serve as the source of wide characters.
     */
    static RWWCharInputStream make(const RWWCharInputStream& sourceStream)
    {
        return RWWCharInputStream(new RWSynchronizedWCharInputStreamImp(sourceStream));
    }

    // Documented in the base class
    virtual RWSize readUntil(wchar_t* wcharArray, RWSize maxSize, wchar_t delim);

protected:

    //-- Throws no exceptions.
    /**
     * Initializes the reference to the input stream that will be used as
     * the source of wide characters.
     *
     * \param sourceStream
     * The input stream that will serve as the source of wide characters.
     */
    RWSynchronizedWCharInputStreamImp(const RWWCharInputStream& sourceStream);

};

#endif // rw_stream_RWSynchronizedWCharInputStreamImp_h_
