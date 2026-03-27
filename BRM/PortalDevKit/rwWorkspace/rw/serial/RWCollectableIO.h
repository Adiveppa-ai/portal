#ifndef rw_serial_RWCollectableIO_h_
#define rw_serial_RWCollectableIO_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWCollectableIO.h#1 $
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

#include <rw/serial/RWObjectStreamMacros.h>
#include <rw/serial/StreamTraits.h>
#include <rw/serial/pkgdefs.h>
#include <rw/stream/stream.h>
#include <rw/collect.h>

inline
RWStreamType
rwStreamType(const RWCollectable*)
{
    return RW_OBJECT;
}

inline
RWStreamType
rwStreamType(const RWCollectable**)
{
    return RW_OBJECT;
}

inline
RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWCollectable& obj)
{
    RWvostreamToDataOutputStream vostr(strm);
    vostr << obj;
    return strm;
}

inline
RWObjectOutputStream&
operator<<(RWObjectOutputStream& strm, const RWCollectable* obj)
{
    RWvostreamToDataOutputStream vostr(strm);
    vostr << obj;
    return strm;
}

inline
RWObjectInputStream&
operator>>(RWObjectInputStream& strm, RWCollectable& obj)
{
    RWvistreamFromDataInputStream vistr(strm);
    vistr >> obj;
    return strm;
}

inline
RWObjectInputStream&
operator>>(RWObjectInputStream& strm, RWCollectable*& obj)
{
    RWvistreamFromDataInputStream vistr(strm);
    vistr >> obj;
    return strm;
}

// despite the name, this macro is intended to be used in a
// header file. ideally we'd rename it to reflect how it is
// intended to be used, but that would likely break our user code.
#define RW_DEFINE_COLLECTABLE_AS_STREAMABLE(derived)            \
inline RWObjectInputStream&                                     \
operator>>(RWObjectInputStream& strm, derived*& obj)            \
{                                                               \
  RWvistreamFromDataInputStream vistr(strm);                    \
  RWCollectable* baseptr;                                       \
  vistr >> baseptr;                                             \
  obj = (derived*)baseptr;                                      \
  return strm;                                                  \
}                                                               \
inline RWObjectOutputStream&                                    \
operator<<(RWObjectOutputStream& strm, const derived* obj)      \
{                                                               \
  RWvostreamToDataOutputStream vostr(strm);                     \
  const RWCollectable* baseptr = obj;                           \
  vostr << baseptr;                                             \
  return strm;                                                  \
}                                                               \
inline RWObjectOutputStream&                                    \
operator<<(RWObjectOutputStream& strm, derived* obj)            \
{                                                               \
  return operator<<(strm, (const derived*)obj);                 \
}


#endif // rw_serial_RWCollectableIO_h_
