#ifndef rw_stream_RWWCharOutputStreamImp_h_
#define rw_stream_RWWCharOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWWCharOutputStreamImp.h#1 $
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

#include <rw/stream/RWOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>

class RWWCharOutputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the wide character output stream
 * implementation classes.
 *
 * Abstract base class for all the wide character output stream
 * implementation classes. Implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWWCharOutputStreamImp : public RWOutputStreamImp
{

public:

    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWWCharOutputStreamImp()
    {
        ;
    }

    /**
     * Writes a single wide character to the stream.
     *
     * \param wcharValue
     * The wide character to be written to the stream.
     */
    virtual void write(wchar_t wcharValue) = 0;

    /**
     * Writes an array of wide characters to the stream.
     *
     * \param wcharArray
     * A pointer to the first element of the array.
     *
     * \param numWchars
     * The number of wide characters to be written to the stream.
     */
    virtual void write(const wchar_t* wcharArray, RWSize numWchars) = 0;

    /**
     * Acquires the synchronization mechanism provided by a stream concrete
     * implementation. The acquire() member function returns a handle to the
     * wide character stream that should be used for output operation after
     * acquiring the synchronization mechanism.
     */
    virtual RWWCharOutputStream acquire();

    /**
     * Releases the synchronization mechanism provided by a stream concrete
     * implementation.
     */
    virtual void release()
    {
        ;
    }

protected:

    //-- Throws no exceptions.
    /**
     * Constructor.
     */
    RWWCharOutputStreamImp()
        : RWOutputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWWCharOutputStreamImp_h_
