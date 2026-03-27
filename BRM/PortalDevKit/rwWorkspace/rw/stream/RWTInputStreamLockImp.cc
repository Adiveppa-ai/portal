/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTInputStreamLockImp.cc#1 $
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


template <class InputStream, class FilteredInputStreamImp>
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::RWTInputStreamLockImp(const InputStream& sourceStream)
    : FilteredInputStreamImp(sourceStream)
{
    ;
}

template <class InputStream, class FilteredInputStreamImp>
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::~RWTInputStreamLockImp()
{
    ;
}

template <class InputStream, class FilteredInputStreamImp>
void
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::close()
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    this->getSourceStream().close();
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::isEof() const
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().isEof();
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::isFail() const
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().isFail();
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::isBad() const
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().isBad();
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::isGood() const
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().isGood();
}

template <class InputStream, class FilteredInputStreamImp>
#if defined(__hpux)
typename InputStream::element_type
#else
typename RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::element_type
#endif
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::read()
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().read();
}

template <class InputStream, class FilteredInputStreamImp>
RWSize
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::read(element_type* array,
        RWSize num)
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().read(array, num);
}

template <class InputStream, class FilteredInputStreamImp>
RWSize
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::available() const
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().available();
}

template <class InputStream, class FilteredInputStreamImp>
RWSize
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::skip(RWSize numUnits)
{
    RWTLockGuard<RWMutexLock> lock_(this->getStreamMutex());

    return this->getSourceStream().skip(numUnits);
}

template <class InputStream, class FilteredInputStreamImp>
InputStream
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::acquire()
{
    this->getStreamMutex().acquire();
    return this->getSourceStream();
}

template <class InputStream, class FilteredInputStreamImp>
void
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::release()
{
    this->getStreamMutex().release();
}
