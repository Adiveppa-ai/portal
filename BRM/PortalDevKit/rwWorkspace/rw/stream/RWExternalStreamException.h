#ifndef rw_stream_RWExternalStreamException_h_
#define rw_stream_RWExternalStreamException_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWExternalStreamException.h#1 $
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

#include <rw/stream/pkgdefs.h>
#include <rw/rwerr.h>


class RWCString;

//--Base class for all the stream exceptions that might occur due to
//--an external error.
/**
 * \ingroup streams_package
 * \class RWExternalStreamException
 *
 * \brief
 * Base class for the stream exceptions.
 *
 * Base class for all the stream exceptions.
 */
class RW_STREAM_GLOBAL RWExternalStreamException : public RWExternalErr
{

public:
    /**
     * ErrorCode is an enumeration that represents the error type for a
     * stream exception.
     */
    enum ErrorCode {
        /**
         * ok = 0. Everything is fine.
         */
        ok = 0,

        /**
         * Error while flushing the stream.
         */
        flush,

        /**
         * Error while writing to the stream.
         */
        write,

        /**
         * Error while reading an #RWByte, \c char, \c wchar_t, or #RWUChar.
         */
        read,

        /**
         * Error while reading a data type.
         */
        get,

        /**
         * Internal <b>std::ostream</b> object is in fail or bad
         */
        internalOstream,

        /**
         * Internal <b>std::istream</b> object is in fail or bad
         */
        internalIstream,

        /**
         * Reports a feature not currently supported due to compiler
         * limitation.
         */
        featureNotSupported,

        /**
         * The last memory allocation request failed.
         */
        outOfMemory,

        /**
         * One of the parameters has been assigned an invalid value.
         */
        invalidParameter,


        /**
         * A sequence of #RWUChar does not represent a valid sequence of
         * UTF-16 characters.
         */
        invalidUnicodeEncoding,

        /**
         * A sequence of bytes is not formatted according to UTF-8.
         */
        invalidUTF8Encoding
    };

    //--Constructs an empty stream exception.
    //--Throws no exceptions.

    /**
     * Constructs an empty stream exception.
     */
    RWExternalStreamException();

    //--Constructs a stream exception, and initializes it with the error message
    //--'msg' and the error code 'err'.
    //--The parameter 'msg' is a message describing the error. The parameter 'err'
    //--is the error code associated with the error.
    //--Throws no exceptions.

    /**
     * Constructs a stream exception, and initializes it with the error
     * message \a msg and the error code \a err.
     *
     * \param msg
     * A message describing the error.
     *
     * \param err
     * The error code associated with the error.
     */
    RWExternalStreamException(const char* msg, ErrorCode err);


    //--Constructs a stream exception, and initializes it with the error message
    //--'msg' and the error code 'err'.
    //--The parameter 'msg' A message describing the error. The parameter 'err' is
    //--the error code associated with the error.
    //--Throws no exceptions.

    /**
     * Constructs a stream exception, and initializes it with the error
     * message \a msg and the error code \a err.
     *
     * \param msg
     * A message describing the error.
     *
     * \param err
     * The error code associated with the error.
     */
    RWExternalStreamException(const RWCString& msg, ErrorCode err);


    //--Copy constructor.
    //--The parameter 'x' is a stream exception used to initialize the
    //--newly created stream exception.
    //--Throws no exceptions.

    /**
     * Copy constructor.
     *
     * \param x
     * A stream exception used to initialize the newly created stream
     * exception.
     */
    RWExternalStreamException(const RWExternalStreamException& x);

    //--Returns the error code associated with a particular stream exception instance.
    //--Throws no exceptions.

    /**
     * Returns the error code associated with a particular stream exception
     * instance.
     */
    ErrorCode errorCode() const;

private:

    ErrorCode errorCode_;

};

#endif // rw_stream_RWExternalStreamException_h_
