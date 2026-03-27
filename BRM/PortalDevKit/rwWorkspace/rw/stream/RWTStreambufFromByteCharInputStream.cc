/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTStreambufFromByteCharInputStream.cc#1 $
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


template <class InputStream>
RWTStreambufFromByteCharInputStream<InputStream>::RWTStreambufFromByteCharInputStream(const InputStream& sourceStream)
    : sourceStream_(sourceStream)
{
    // always work in unbuffered mode if possible
    this->setg(buf_, buf_, buf_);
}

template <class InputStream>
typename RWTStreambufFromByteCharInputStream<InputStream>::int_type
RWTStreambufFromByteCharInputStream<InputStream>::overflow(int_type)
{
    return traits_type::eof();
}

template <class InputStream>
typename RWTStreambufFromByteCharInputStream<InputStream>::int_type
RWTStreambufFromByteCharInputStream<InputStream>::underflow()
{
    if (this->in_avail()) {
        return traits_type::to_int_type(*(this->gptr()));
    }
    RWSize count = this->getSourceStream().read(reinterpret_cast<element_type*>(buf_),
                   RW_STREAM_STREAMBUF_BUFFER_SIZE);
    // we need to unset the source stream failbit if we cannot
    // read RW_STREAM_STREAMBUF_BUFFER_SIZE bytes/narrow characters
    // this is a little tricky, but it works fine
    if (count != RW_STREAM_STREAMBUF_BUFFER_SIZE) {
        this->getSourceStream().skip(0);
    }
    this->setg(buf_, buf_, buf_ + count);
    if (count) {
        return traits_type::to_int_type(*(this->gptr()));
    }
    else {
        return traits_type::eof();
    }
}

template <class InputStream>
typename RWTStreambufFromByteCharInputStream<InputStream>::int_type
RWTStreambufFromByteCharInputStream<InputStream>::pbackfail(int_type)
{
    return traits_type::eof();
}

template <class InputStream>
int
RWTStreambufFromByteCharInputStream<InputStream>::sync()
{
    return 0;
}

template <class InputStream>
std::streamsize
RWTStreambufFromByteCharInputStream<InputStream>::showmanyc()
{
    return static_cast<int>(this->egptr() - this->gptr());
}

template <class InputStream>
typename RWTStreambufFromByteCharInputStream<InputStream>::pos_type
RWTStreambufFromByteCharInputStream<InputStream>::seekoff(off_type, std::ios_base::seekdir,
        std::ios_base::openmode)
{
    return traits_type::eof();
}

template <class InputStream>
typename RWTStreambufFromByteCharInputStream<InputStream>::pos_type
RWTStreambufFromByteCharInputStream<InputStream>::seekpos(pos_type,
        std::ios_base::openmode)
{
    return traits_type::eof();
}

template <class InputStream>
std::streamsize
RWTStreambufFromByteCharInputStream<InputStream>::xsputn(const char_type*,
        std::streamsize)
{
    return 0;
}
