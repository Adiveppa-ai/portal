#ifndef rw_serial_GlobalStreamingTemplates_h_
#define rw_serial_GlobalStreamingTemplates_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/GlobalStreamingTemplates.h#1 $
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

#include <rw/serial/RWCompactObjectInputStreamImp.h>
#include <rw/serial/RWCompactObjectOutputStreamImp.h>
#include <rw/serial/RWDataFromVirtualInputStreamImp.h>
#include <rw/serial/RWDataToVirtualOutputStreamImp.h>
#include <rw/serial/pkgdefs.h>
#include <rw/stream/stream.h> // for RWByteToStreambufOutputStreamImp,
#include <rw/cstring.h>
#include <rw/pstream.h>       // for RWpistream, and RWpostream
#include <sstream>


//--Global template functions provided as a convenience when objects are serialized
//--as text strings or as blobs.

//--Global template function that produces a serialized form of its
//--argument, in US-ASCII format, and returns it as an RWCString. Requires
//--that the '<<' operator is defined on the argument type, for
//--'RWObjectOutputStream'.
template <class StreamableObject>
RWCString
rwtStreamableToString(const StreamableObject& obj)
{
    std::stringbuf buf;
    RWpostream pstr(&buf);
    RWDataOutputStream dostr = RWDataToVirtualOutputStreamImp::make(pstr);
    RWObjectOutputStream oostr = RWCompactObjectOutputStreamImp::make(dostr);
    oostr << obj;
    buf.sputc(0);
    return RWCString(buf.str());
}

//--Global template function that reconstitutes an object from an
//--RWCString containing the serialized object in US-ASCII format. If the
//--operation succeeds, then the function returns 'true', and the result
//--is passed out through the 'obj' reference parameter. Otherwise, it
//--returns false, and the 'obj' value is not altered.  The operation
//--requires that the '>>' operator is defined on the argument type, for
//--'RWObjectInputStream'.
template <class StreamableObject>
bool
rwtStringToStreamable(const RWCString& source, StreamableObject& obj)
{
#if !defined(RW_COPY_ON_WRITE_STRING)
    std::stringbuf buf(source.std());
#else
    std::string str(source.data(), source.length());
    std::stringbuf buf(str);
#endif
    RWpistream pstr(&buf);
    RWDataInputStream distr = RWDataFromVirtualInputStreamImp::make(pstr);
    RWObjectInputStream oistr = RWCompactObjectInputStreamImp::make(distr);
    oistr >> obj;
    return oistr.isGood();
}


//--Global template function that produces a serialized form of its
//--argument, in native binary format, and returns it as an array of
//--RWByte and a length.  Requires that the '<<' operator is defined
//--on the argument type, for 'RWObjectOutputStream'.
template <class StreamableObject>
void
rwtStreamableToByte(const StreamableObject& obj,
                    RWByte*&         blob,
                    unsigned long&          length)
{
    RWByteArrayOutputStream bostrm = RWChainedByteArrayOutputStreamImp::make();
    RWDataOutputStream dostrm = RWNativeDataToByteOutputStreamImp::make(bostrm);
    RWObjectOutputStream oostrm = RWCompactObjectOutputStreamImp::make(dostrm);
    oostrm << obj;
    length = bostrm.getByteArraySize();
    blob = (RWByte*)(bostrm.getByteArray());
}

//--Global template function that reconstitutes an object from an
//--array of 'RWByte' containing the serialized object in binary native
//--format.  If the operation succeeds, then the function returns
//--'true', and the result is passed out through the 'obj' reference
//--parameter. Otherwise, it returns 'false', and the 'obj' value is not
//--altered.  Requires that the '>>' operator is defined on the
//--argument type, for 'RWObjectInputStream'.
template <class StreamableObject>
bool
rwtByteToStreamable(const unsigned char* blob,
                    unsigned long        length,
                    StreamableObject&    obj)
{
    std::string str((const char*)blob, length);
    std::stringbuf buf(str);
    RWByteInputStream bistrm = RWByteFromStreambufInputStreamImp::make(buf);
    RWDataInputStream distrm = RWNativeDataFromByteInputStreamImp::make(bistrm);
    RWObjectInputStream oistrm = RWCompactObjectInputStreamImp::make(distrm);
    oistrm >> obj;
    return oistrm.isGood();
}

#endif // rw_serial_GlobalStreamingTemplates_h_
