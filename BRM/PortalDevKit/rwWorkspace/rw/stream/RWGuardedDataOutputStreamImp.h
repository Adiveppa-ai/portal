#ifndef rw_stream_RWGuardedDataOutputStreamImp_h_
#define rw_stream_RWGuardedDataOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWGuardedDataOutputStreamImp.h#1 $
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

#include <rw/stream/RWDataOutputStream.h>
#include <rw/stream/RWFilteredDataOutputStreamImp.h>
#include <rw/stream/RWTStreamGuardImp.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \headerfileloc{#include <rw/stream/RWGuardedDataOutputStreamImp.h>}
 *
 * The typedef #RWGuardedDataOutputStreamImp implements a simple data guard
 * output stream. The output stream guard acquires the synchronization
 * mechanism provided by its sink stream at construction time, and releases
 * it upon destruction. The output guard stream doesn't maintain its own
 * synchronization mechanism, but uses the one provided by the next
 * processing stream. If the next processing stream doesn't implement any
 * synchronization mechanism, the output stream guard class has no effect.
 * The guard class is generally used in combination with class
 * RWSynchronizedDataOutputStreamImp.
 *
 * \sa
 * RWSynchronizedDataOutputStreamImp
 */
typedef RWTStreamGuardImp<RWDataOutputStream, RWFilteredDataOutputStreamImp> RWGuardedDataOutputStreamImp;

/**
 * \relates RWDataOutputStream
 *
 * \headerfileloc{#include <rw/stream/RWGuardedDataOutputStreamImp.h>}
 *
 * Manipulator that is used to guard a series of insertion operations.
 *
 * \param stream
 * A binary output stream.
 *
 * A \ref rwGuard(RWDataOutputStream&) "rwGuard()" manipulator creates a
 * temporary guarded stream that locks the internal mutex of the preceding
 * synchronized stream. In this way, any insertions following the
 * manipulator within the statement will be atomic, that is, uninterrupted
 * by any other threads. Note that if the preceding stream is not a
 * synchronized stream, the \ref rwGuard(RWDataOutputStream&) "rwGuard()"
 * manipulator has no effect.
 *
 * \example
 * \code
 * // Lock the stream for the duration of all three insertions:
 * ostr << rwGuard << data1 << data2 << data3;
 * \endcode
 * \endexample
 */
RWDataOutputStream RW_STREAM_SYMBOLIC rwGuard(RWDataOutputStream& stream);

#endif // rw_stream_RWGuardedDataOutputStreamImp_h_
