/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTStreambufToByteCharOutputStream.cc#1 $
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


template <class OutputStream>
RWTStreambufToByteCharOutputStream<OutputStream>::RWTStreambufToByteCharOutputStream(const OutputStream& sinkStream)
    : sinkStream_(sinkStream)
{
    // always work in unbuffered mode
    this->pubsetbuf(0, 0);
}

template <class OutputStream>
typename RWTStreambufToByteCharOutputStream<OutputStream>::int_type
RWTStreambufToByteCharOutputStream<OutputStream>::overflow(int_type c)
{
    // always work in unbuffered mode
    try {
        if (!traits_type::eq_int_type(c, traits_type::eof())) {
            this->getSinkStream().write(static_cast<element_type>(c));
        }
    }
    catch (...) {
        return traits_type::eof();
    }

    return 1;
}

template <class OutputStream>
typename RWTStreambufToByteCharOutputStream<OutputStream>::int_type
RWTStreambufToByteCharOutputStream<OutputStream>::underflow()
{
    return traits_type::eof();
}

template <class OutputStream>
typename RWTStreambufToByteCharOutputStream<OutputStream>::int_type
RWTStreambufToByteCharOutputStream<OutputStream>::pbackfail(int_type)
{
    return traits_type::eof();
}

template <class OutputStream>
int
RWTStreambufToByteCharOutputStream<OutputStream>::sync()
{
    // always work in unbuffered mode
    try {
        this->getSinkStream().flush();
    }
    catch (...) {
        return traits_type::eof();
    }
    if (!this->getSinkStream().isGood()) {
        return traits_type::eof();
    }
    return 0;
}

template <class OutputStream>
typename RWTStreambufToByteCharOutputStream<OutputStream>::pos_type
RWTStreambufToByteCharOutputStream<OutputStream>::seekoff(off_type, std::ios_base::seekdir,
        std::ios_base::openmode)
{
    return traits_type::eof();
}

template <class OutputStream>
typename RWTStreambufToByteCharOutputStream<OutputStream>::pos_type
RWTStreambufToByteCharOutputStream<OutputStream>::seekpos(pos_type,
        std::ios_base::openmode)
{
    return traits_type::eof();
}

template <class OutputStream>
std::streamsize
RWTStreambufToByteCharOutputStream<OutputStream>::xsgetn(char_type*,
        std::streamsize)
{
    return 0;
}

template <class OutputStream>
std::streamsize
RWTStreambufToByteCharOutputStream<OutputStream>::xsputn(const char_type* s,
        std::streamsize n)
{
    // always work in unbuffered mode
    try {
        this->getSinkStream().write(reinterpret_cast<const element_type*>(s),
                                    static_cast<RWSize>(n));
    }
    catch (const RWIncompleteStreamOperation& e) {
        return static_cast<std::streamsize>(e.elementsProcessed());
    }

    return n;
}
