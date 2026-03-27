#ifndef rw_stream_types_h_
#define rw_stream_types_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/types.h#1 $
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


//-- RWSize is used to represent a number of elements [0, +N[
/**
 * \ingroup streams_package
 *
 * Global typedef for unsigned long
 */
typedef unsigned long RWSize;

//-- RWByte represents the unit of information manipulated by the
//-- binary streams.
/**
 * \ingroup streams_package
 *
 * Global typedef for unsigned char
 */
typedef unsigned char RWByte;

//-- RWUChar represents a unicode character.
/**
 * \ingroup streams_package
 *
 * Global typedef for unsigned short
 */
typedef unsigned short RWUChar;

#endif // rw_stream_types_h_
