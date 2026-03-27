#ifndef rw_stream_RWCharOutputStreamImp_h_
#define rw_stream_RWCharOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWCharOutputStreamImp.h#1 $
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

// forward declaration
class RWCharOutputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all narrow character output stream implementation
 * classes.
 *
 * Abstract base class for all the narrow character output stream
 * implementation classes. Implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWCharOutputStreamImp : public RWOutputStreamImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWCharOutputStreamImp()
    {
        ;
    }

    /**
     * Writes a single narrow character to the stream.
     *
     * \param charValue
     * The narrow character to be written to the stream.
     */
    virtual void write(char charValue) = 0;

    /**
     * Writes an array of narrow characters to the stream.
     *
     * \param charArray
     * A pointer to the first element of the array.
     *
     * \param numChars
     * The number of narrow characters to be written to the stream.
     */
    virtual void write(const char* charArray, RWSize numChars) = 0;

    /**
     * Acquires the synchronization mechanism provided by a stream concrete
     * implementation. The acquire() member function returns a handle to the
     * narrow character stream that should be used for output operation
     * after acquiring the synchronization mechanism.
     */
    virtual RWCharOutputStream acquire();

    /**
     * Releases the synchronization mechanism provided by a stream concrete
     * implementation.
     */
    virtual void release()
    {
        ;
    }

protected:

    /**
     * Constructor.
     */
    RWCharOutputStreamImp()
        : RWOutputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWCharOutputStreamImp_h_
