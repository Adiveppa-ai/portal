/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTPortalStreambuf.cc#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

#include <rw/network/RWTPortalStreambuf.h>
#include <rw/network/except.h>
#include <rw/tools/pointer.h>

static const int RWNET_BUFSIZE = 4 + (2 * RWNET_PORTAL_BUFFER_SIZE);

template <class charT, class traits>
RWTPortalStreambuf<charT, traits>::RWTPortalStreambuf(void)
{
    charT* buffer = 0;

    //  if(buffered)
    buffer = new charT[RWNET_BUFSIZE];
    resetbuf(buffer, RWNET_BUFSIZE);
}


template <class charT, class traits>
RWTPortalStreambuf<charT, traits>::RWTPortalStreambuf(const RWPortal& portal)
    : portal_(portal)
{
    charT* buffer = 0;
    //  if(buffered)
    buffer = new charT[RWNET_BUFSIZE];
    resetbuf(buffer, RWNET_BUFSIZE);
}

template <class charT, class traits>
RWTPortalStreambuf<charT, traits>::~RWTPortalStreambuf(void)
{
    typedef std::basic_streambuf<charT, traits> Base;
    // Workaround for optimization issue with Sunpro 5.2 jumbo3
    RWTScopedPointer<charT[]> buffer(Base::eback());
    try {
        sync();
    }
    catch (...) {
    }
}


template <class charT, class traits>
int RWTPortalStreambuf<charT, traits>::sync(void)
{
    typedef std::basic_streambuf<charT, traits> Base;

    if ((Base::pptr() - Base::pbase()) &&
            traits::eq_int_type(overflow(traits::eof()), traits::eof())) {
        return traits::eof();
    }

    return 0;
}


template <class charT, class traits>
void RWTPortalStreambuf<charT, traits>::setPortal(const RWPortal& portal, bool force)
{
    typedef std::basic_streambuf<charT, traits> Base;

    try {
        sync();
    }
    catch (...) {
        if (!force) {
            throw;
        }
    }
    Base::setg(Base::eback(), Base::pbase(), Base::pbase());
    Base::setp(Base::pbase(), Base::epptr());
    portal_ = portal;
}

template <class charT, class traits>
typename RWTPortalStreambuf<charT, traits>::int_type
RWTPortalStreambuf<charT, traits>::overflow(typename RWTPortalStreambuf<charT, traits>::int_type c)
{
    typedef std::basic_streambuf<charT, traits> Base;

    //  if(!Base::pptr())
    //  {
    //    if(eof)
    //      return ~traits::eof();
    //
    //    charT data = c;
    //    portal_.sendAtLeast(&data, 1);
    //    return data;
    //  } else {

    RW_ASSERT(Base::pptr());

    size_t bufLen = size_t (reinterpret_cast< char* >(Base::pptr()) -
                            reinterpret_cast< char* >(Base::pbase()));
    size_t totalBytesSent = 0;

    do {
        int bytesToSend = (bufLen - totalBytesSent < INT_MAX ?
                           (int)(bufLen - totalBytesSent) : INT_MAX);

        portal_.sendAtLeast((char*)Base::pbase() + totalBytesSent, bytesToSend);

        totalBytesSent += bytesToSend;
    }
    while (totalBytesSent < bufLen);

    Base::setp(Base::pbase(), Base::epptr());

    if (!traits::eq_int_type(c, traits::eof())) {
        *Base::pptr() = traits::to_char_type(c);
        Base::pbump(1);
    }

    return traits::not_eof(c);
}


template <class charT, class traits>
typename RWTPortalStreambuf<charT, traits>::int_type RWTPortalStreambuf<charT, traits>::underflow(void)
{
    typedef std::basic_streambuf<charT, traits> Base;

    if (Base::egptr() > Base::gptr()) {
        return traits::to_int_type(*Base::gptr());
    }

    RW_ASSERT(Base::egptr());

    charT* front = Base::eback() + 4;
    charT* back =  Base::pbase();

    size_t bufLen = size_t (back - front);
    int maxBytes = bufLen > INT_MAX ? INT_MAX : (int)bufLen;
    int count = portal_.recv((char*)front, maxBytes);

    if (count > 0) {
        Base::setg(front - 4, front, front + count / sizeof(charT));
        return traits::to_int_type(*Base::gptr());
    }
    return traits::eof();
}


template <class charT, class traits>
void RWTPortalStreambuf<charT, traits>::resetbuf(charT* start, int length)
{
    typedef std::basic_streambuf<charT, traits> Base;

    //  if(start == 0 || length == 0)
    //  {
    //#   if defined(RW_NO_IO_STD)
    //      unbuffered(1);
    //#   endif
    //
    //    Base::setg(0, 0, 0);
    //    Base::setp(0, 0);
    //  }
    //  else
    //  {
    charT* mid = start + (length / 2);
    charT* end = start + length;

    Base::setg(start, mid, mid);
    Base::setp(mid, end);
    //  }
}
