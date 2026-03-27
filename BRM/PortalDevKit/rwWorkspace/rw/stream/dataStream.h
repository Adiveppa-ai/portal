#ifndef rw_stream_dataStream_h_
#define rw_stream_dataStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/dataStream.h#1 $
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


//-- This header file includes all the public definitions for the data
//-- stream family
#include <rw/stream/RWDataInputStream.h>
#include <rw/stream/RWDataOutputStream.h>
#include <rw/stream/RWExternalStreamException.h>
#include <rw/stream/RWGuardedDataInputStreamImp.h>
#include <rw/stream/RWGuardedDataOutputStreamImp.h>
#include <rw/stream/RWIncompleteStreamOperation.h>
#include <rw/stream/RWIstreamDataFromCharInputStreamImp.h>
#include <rw/stream/RWNativeDataFromByteInputStreamImp.h>
#include <rw/stream/RWNativeDataToByteOutputStreamImp.h>
#include <rw/stream/RWOstreamDataToCharOutputStreamImp.h>
#include <rw/stream/RWSynchronizedDataInputStreamImp.h>
#include <rw/stream/RWSynchronizedDataOutputStreamImp.h>
#include <rw/stream/RWvistreamFromDataInputStream.h>
#include <rw/stream/RWvostreamToDataOutputStream.h>

#endif // rw_stream_dataStream_h_
