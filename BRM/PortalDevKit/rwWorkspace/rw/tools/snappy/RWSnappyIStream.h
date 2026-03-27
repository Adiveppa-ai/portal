#ifndef rw_tools_snappy_RWSnappyIStream_h__
#define rw_tools_snappy_RWSnappyIStream_h__


/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/tools/snappy/RWSnappyIStream.h#1 $
 *
 * Copyright (c) 1989-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 *************************************************************************/

/**************************************************************************
 *
 * Description:
 *
 * Typedef for a compressed input stream using the snappy compression
 * library.
 *
 *************************************************************************/

#include <rw/tools/snappy/RWSnappyCompressor.h>
#include <rw/tools/snappy/pkgdefs.h>
#include <rw/tools/cmpstream.h>

/**
 * \ingroup snappy_module
 *
 * \brief
 * Convenience typedef for RWCompressedIStream instantiated on
 * RWSnappyCompressor.
 *
 * RWSnappyIStream is a typedef for RWCompressedIStream instantiated on
 * RWSnappyCompressor.
 *
 * \sa
 * RWCompressedIStream, RWSnappyCompressor
 */
typedef RWCompressedIStream<RWSnappyCompressor> RWSnappyIStream;

#endif // rw_tools_snappy_RWSnappyIStream_h__
