#ifndef __rw_network_RWTPortalStreambuf_h__
#define __rw_network_RWTPortalStreambuf_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTPortalStreambuf.h#1 $
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

#include <rw/network/RWPortal.h>
#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>
#include <streambuf>

/**
 * \ingroup networking_module
 *
 * \brief
 * Streambuf that uses an RWPortal as its source and sink of bytes.
 *
 * RWTPortalStreambuf is a streambuf that uses an RWPortal as its source and
 * sink of bytes.
 */
template <class charT, class traits>
class RWTPortalStreambuf : public std::basic_streambuf<charT, traits>
{
public:

    /**
     * A typedef for the character type used by this stream buffer. This is
     * an alias for the \c charT template parameter.
     */
    typedef              charT                   char_type;

    /**
     * A typedef for the character traits used by this stream buffer. This
     * is an alias for the \c traits template parameter.
     */
    typedef              traits                  traits_type;

    /**
     * A typedef for an integer type that is able to store all possible
     * values of type char_type, including end-of-file.
     */
    typedef  typename  traits_type::int_type   int_type;

    /**
     * Constructs a streambuf without a source or sink of bytes. You need to
     * set the source and sink using setPortal() before using self.
     */
    RWTPortalStreambuf(void);

    /**
     * Constructs a streambuf connected to the portal \a portal.
     */
    RWTPortalStreambuf(const RWPortal& portal);

    ~RWTPortalStreambuf(void) RW_STREAMBUF_DTOR_THROWSPEC;

    /**
     * Sets the communications channel into which you are writing. If
     * \a force is \c true, the underlying portal is reassigned, and any
     * exceptions thrown by the assignment are caught and ignored.
     */
    void
    setPortal(const RWPortal& portal, bool force = false);

protected:

    /**
     * Writes to the portal when the buffer overflows.
     */
    virtual int_type
    overflow(int_type = traits_type::eof());

    /**
     * Reads from the portal when the buffer underflows.
     */
    virtual int_type
    underflow(void);

    virtual int
    sync(void);

    // Work around a bug in SunPro C++ Standard Library (PR #29750)
#if defined(__SUNPRO_CC) && \
    defined(RW_STDLIB_VER) && RW_STDLIB_VER == 0x02010100
    virtual std::streamsize showmanyc()
    {
        return 0;
    }
#endif // __SUNPRO_CC && RW_STDLIB_VER && RW_STDLIB_VER == 0x02010100

private:

    void
    resetbuf(charT* start, int length);

    RWTPortalStreambuf(const RWTPortalStreambuf&);

    RWTPortalStreambuf&
    operator=(const RWTPortalStreambuf&);

private:

    RWPortal portal_;

};


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/network/RWTPortalStreambuf.cc>
#endif

#endif // __rw_network_RWTPortalStreambuf_h__
