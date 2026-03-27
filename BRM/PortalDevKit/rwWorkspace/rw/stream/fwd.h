#ifndef rw_stream_fwd_h_
#define rw_stream_fwd_h_
/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/fwd.h#1 $
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


// Handles

class RW_STREAM_SYMBOLIC RWCharOutputStream;
class RW_STREAM_SYMBOLIC RWByteOutputStream;
class RW_STREAM_GLOBAL RWDataOutputStream;
class RW_STREAM_SYMBOLIC RWUCharOutputStream;
class RW_STREAM_SYMBOLIC RWWCharOutputStream;
class RW_STREAM_SYMBOLIC RWByteInputStream;
class RW_STREAM_SYMBOLIC RWCharInputStream;
class RW_STREAM_SYMBOLIC RWDataInputStream;
class RW_STREAM_SYMBOLIC RWUCharInputStream;
class RW_STREAM_SYMBOLIC RWWCharInputStream;

class RW_STREAM_SYMBOLIC RWByteArrayOutputStream;
class RW_STREAM_SYMBOLIC RWCharArrayOutputStream;
class RW_STREAM_SYMBOLIC RWUCharArrayOutputStream;
class RW_STREAM_SYMBOLIC RWWCharArrayOutputStream;

// Implementations

class RW_STREAM_GLOBAL RWByteToStreambufOutputStreamImp;
class RW_STREAM_GLOBAL RWCharToStreambufOutputStreamImp;
class RW_STREAM_GLOBAL RWByteFromStreambufInputStreamImp;
class RW_STREAM_GLOBAL RWCharFromStreambufInputStreamImp;

class RW_STREAM_GLOBAL RWNativeDataToByteOutputStreamImp;
class RW_STREAM_GLOBAL RWNativeDataFromByteInputStreamImp;

class RW_STREAM_GLOBAL RWOstreamDataToCharOutputStreamImp;
class RW_STREAM_GLOBAL RWIstreamDataFromCharInputStreamImp;

class RW_STREAM_GLOBAL RWUCharToByteOutputStreamImp;
class RW_STREAM_GLOBAL RWUCharFromByteInputStreamImp;
class RW_STREAM_GLOBAL RWUCharToUTF8ByteOutputStreamImp;
class RW_STREAM_GLOBAL RWUCharFromUTF8ByteInputStreamImp;

class RW_STREAM_GLOBAL RWWCharToWStreambufOutputStreamImp;
class RW_STREAM_GLOBAL RWWCharFromWStreambufInputStreamImp;

class RW_STREAM_GLOBAL RWChainedMemoryStreambuf;
class RW_STREAM_GLOBAL RWChainedByteArrayOutputStreamImp;
class RW_STREAM_GLOBAL RWChainedCharArrayOutputStreamImp;
class RW_STREAM_GLOBAL RWChainedUCharArrayOutputStreamImp;
class RW_STREAM_GLOBAL RWChainedWCharArrayOutputStreamImp;

class RW_STREAM_GLOBAL RWFilteredCharOutputStreamImp;
template <class OutputStream, class FilteredOutputStreamImp> class RWTOutputStreamBufferImp;
typedef RWTOutputStreamBufferImp<RWCharOutputStream, RWFilteredCharOutputStreamImp> RWBufferedCharOutputStreamImp;
class RWFilteredByteOutputStreamImp;
typedef RWTOutputStreamBufferImp<RWByteOutputStream, RWFilteredByteOutputStreamImp> RWBufferedByteOutputStreamImp;
class RWFilteredUCharOutputStreamImp;
typedef RWTOutputStreamBufferImp<RWUCharOutputStream, RWFilteredUCharOutputStreamImp> RWBufferedUCharOutputStreamImp;
class RWFilteredWCharOutputStreamImp;
typedef RWTOutputStreamBufferImp<RWWCharOutputStream, RWFilteredWCharOutputStreamImp> RWBufferedWCharOutputStreamImp;

class RW_STREAM_GLOBAL RWFilteredByteInputStreamImp;
template <class InputStream, class FilteredInputStreamImp> class RWTInputStreamBufferImp;
typedef RWTInputStreamBufferImp<RWByteInputStream, RWFilteredByteInputStreamImp> RWBufferedByteInputStreamImp;
class RWBufferedCharInputStreamImp;
class RWFilteredUCharInputStreamImp;
typedef RWTInputStreamBufferImp<RWUCharInputStream, RWFilteredUCharInputStreamImp> RWBufferedUCharInputStreamImp;
class RWFilteredWCharInputStreamImp;
typedef RWTInputStreamBufferImp<RWWCharInputStream, RWFilteredWCharInputStreamImp> RWBufferedWCharInputStreamImp;

template <class OutputStream, class FilteredOutputStreamImp> class RWTOutputStreamLockImp;
typedef RWTOutputStreamLockImp<RWCharOutputStream, RWFilteredCharOutputStreamImp> RWSynchronizedCharOutputStreamImp;
typedef RWTOutputStreamLockImp<RWByteOutputStream, RWFilteredByteOutputStreamImp> RWSynchronizedByteOutputStreamImp;
typedef RWTOutputStreamLockImp<RWUCharOutputStream, RWFilteredUCharOutputStreamImp> RWSynchronizedUCharOutputStreamImp;
typedef RWTOutputStreamLockImp<RWWCharOutputStream, RWFilteredWCharOutputStreamImp> RWSynchronizedWCharOutputStreamImp;
class RW_STREAM_GLOBAL RWSynchronizedByteInputStreamImp;
class RW_STREAM_GLOBAL RWSynchronizedCharInputStreamImp;
class RW_STREAM_GLOBAL RWSynchronizedUCharInputStreamImp;
class RW_STREAM_GLOBAL RWSynchronizedWCharInputStreamImp;
class RW_STREAM_GLOBAL RWSynchronizedDataInputStreamImp;
class RW_STREAM_GLOBAL RWSynchronizedDataOutputStreamImp;

template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
typedef RWTStreamGuardImp<RWCharOutputStream, RWFilteredCharOutputStreamImp> RWGuardedCharOutputStreamImp;
typedef RWTStreamGuardImp<RWByteOutputStream, RWFilteredByteOutputStreamImp> RWGuardedByteOutputStreamImp;
typedef RWTStreamGuardImp<RWUCharOutputStream, RWFilteredUCharOutputStreamImp> RWGuardedUCharOutputStreamImp;
typedef RWTStreamGuardImp<RWWCharOutputStream, RWFilteredWCharOutputStreamImp> RWGuardedWCharOutputStreamImp;
class RW_STREAM_GLOBAL RWFilteredDataOutputStreamImp;
typedef RWTStreamGuardImp<RWDataOutputStream, RWFilteredDataOutputStreamImp> RWGuardedDataOutputStreamImp;
typedef RWTStreamGuardImp<RWCharInputStream, RWFilteredCharInputStreamImp> RWGuardedCharInputStreamImp;
typedef RWTStreamGuardImp<RWByteInputStream, RWFilteredByteInputStreamImp> RWGuardedByteInputStreamImp;
typedef RWTStreamGuardImp<RWUCharInputStream, RWFilteredUCharInputStreamImp> RWGuardedUCharInputStreamImp;
typedef RWTStreamGuardImp<RWWCharInputStream, RWFilteredWCharInputStreamImp> RWGuardedWCharInputStreamImp;
class RW_STREAM_GLOBAL RWFilteredDataInputStreamImp;
typedef RWTStreamGuardImp<RWDataInputStream, RWFilteredDataInputStreamImp> RWGuardedDataInputStreamImp;

// Adaptors

class RW_STREAM_GLOBAL RWvostreamToDataOutputStream;
class RW_STREAM_GLOBAL RWvistreamFromDataInputStream;

template <class OutputStream> class RWTStreambufToByteCharOutputStream;
typedef RWTStreambufToByteCharOutputStream<RWByteOutputStream> RWStreambufToByteOutputStream;
typedef RWTStreambufToByteCharOutputStream<RWCharOutputStream> RWStreambufToCharOutputStream;

template <class InputStream> class RWTStreambufFromByteCharInputStream;
typedef RWTStreambufFromByteCharInputStream<RWByteInputStream> RWStreambufFromByteInputStream;
typedef RWTStreambufFromByteCharInputStream<RWCharInputStream> RWStreambufFromCharInputStream;

// Exceptions

class RW_STREAM_GLOBAL RWExternalStreamException;
class RW_STREAM_GLOBAL RWIncompleteStreamOperation;

#endif // rw_stream_fwd_h_
