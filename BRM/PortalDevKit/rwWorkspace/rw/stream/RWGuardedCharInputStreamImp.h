#ifndef rw_stream_RWGuardedCharInputStreamImp_h_
#define rw_stream_RWGuardedCharInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWGuardedCharInputStreamImp.h#1 $
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
#include <rw/stream/RWTStreamGuardImp.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \headerfileloc{#include <rw/stream/RWGuardedCharInputStreamImp.h>}
 *
 * The typedef #RWGuardedCharInputStreamImp implements a simple narrow
 * character guard input stream. The input stream guard acquires the
 * synchronization mechanism provided by its source stream at construction
 * time, and releases it upon destruction. The input guard stream doesn't
 * maintain its own synchronization mechanism, but uses the one provided by
 * the next processing stream. If the next processing stream doesn't
 * implement any synchronization mechanism, the input stream guard class has
 * no effect. The guard class is generally used in combination with class
 * RWSynchronizedCharInputStreamImp.
 *
 * \sa
 * RWSynchronizedCharInputStreamImp
 */
typedef RWTStreamGuardImp<RWCharInputStream, RWFilteredCharInputStreamImp> RWGuardedCharInputStreamImp;

/**
 * \relates RWCharInputStream
 *
 * \headerfileloc{#include <rw/stream/RWGuardedCharInputStreamImp.h>}
 *
 * Manipulator that is used to guard a series of extraction operations.
 *
 * \param stream
 * A narrow character input stream.
 *
 * A \ref rwGuard(RWCharInputStream&) "rwGuard()" manipulator creates a
 * temporary guarded stream that locks the internal mutex of the preceding
 * synchronized stream. In this way, any extractions following the
 * manipulator within the statement will be atomic, that is, uninterrupted
 * by any other threads. Note that if the preceding stream is not a
 * synchronized stream, the \ref rwGuard(RWCharInputStream&) "rwGuard()"
 * manipulator has no effect.
 *
 * \example
 * \code
 * // Lock the stream for the duration of all three insertions:
 * instr >> rwGuard >> data1 >> data2 >> data3;
 * \endcode
 * \endexample
 */
RWCharInputStream RW_STREAM_SYMBOLIC rwGuard(RWCharInputStream& stream);

#endif // rw_stream_RWGuardedCharInputStreamImp_h_
