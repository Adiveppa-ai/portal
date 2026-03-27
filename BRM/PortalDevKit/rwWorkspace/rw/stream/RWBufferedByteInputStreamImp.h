#ifndef rw_stream_RWBufferedByteInputStreamImp_h_
#define rw_stream_RWBufferedByteInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWBufferedByteInputStreamImp.h#1 $
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

#include <rw/stream/RWByteInputStream.h>
#include <rw/stream/RWFilteredByteInputStreamImp.h>
#include <rw/stream/RWTInputStreamBufferImp.h>
#include <rw/stream/pkgdefs.h>


//--The typedef 'RWBufferedByteInputStreamImp' implements a buffer that can be used with
//--binary input streams. The size of the buffer is specified in its static member 'make()'
//--function that is used to create it.
//--
//--Example:
//--
//--See Also?
/**
 * \ingroup streams_package
 *
 * \headerfileloc{#include <rw/stream/RWBufferedByteInputStreamImp.h>}
 *
 * The typedef #RWBufferedByteInputStreamImp implements a buffer that can be
 * used with binary input streams. The size of the buffer is specified in
 * its static member \ref RWTInputStreamBufferImp::make() "make()" function
 * that is used to create it.
 *
 * \example
 * \code
 * // A buffer for binary input streams
 *
 * #include <rw/stream/RWBufferedByteInputStreamImp.h>
 * #include <rw/stream/RWByteFromStreambufInputStreamImp.h>
 * #include <rw/stream/RWNativeDataFromByteInputStreamImp.h>
 * #include <iostream.h>
 * #include <fstream.h>
 * #include <rw/rwfile.h>
 *
 * int main() {
 *   filebuf fbuf;
 *
 *   if (!RWFile::Exists("RWBufferedByteOutputStreamImp.out")) {
 *     cout << "The input file does not exist." << endl;
 *   }
 *
 *   else {
 *     fbuf.open("RWBufferedByteOutputStreamImp.out",
 *       ios::in | ios::binary);
 *
 *     RWByteInputStream binStream =
 *       RWByteFromStreambufInputStreamImp::make(fbuf);
 *
 *     RWByteInputStream bufferedStream =
 *       RWBufferedByteInputStreamImp::make(binStream, 512);
 *
 *     RWStreambufFromByteInputStream adaptor(bufferedStream);
 *
 *     istream in(&adaptor);
 *
 *     int i;
 *     in >> i;
 *     cout << i << endl;
 *   }
 *   return 0;
 * }
 * \endcode
 * \endexample
 */
typedef RWTInputStreamBufferImp<RWByteInputStream, RWFilteredByteInputStreamImp> RWBufferedByteInputStreamImp;

#endif // rw_stream_RWBufferedByteInputStreamImp_h_
