#ifndef __rw_http_RWHttpPortalImp_h__
#define __rw_http_RWHttpPortalImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpPortalImp.h#1 $
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
 *************************************************************************/

#include <rw/http/pkgdefs.h>
#include <rw/network/RWNetBuf.h>
#include <rw/network/RWPortal.h>
#include <rw/network/RWPortalImp.h>

/**
 * \internal
 *
 * \headerfileloc{#include <rw/http/RWHttpPortalImp.h>}
 *
 * Specifies the type of transfer encoding that the server is sending back.
 * This information is derived from the headers returned in the server's
 * reply.
 */
enum RWHttpTransferEncoding {

    /**
     * No transfer encoding is used. The length of the entire message is
     * known.
     */
    RW_HTTP_NONE = 0,

    /**
     * A chunked transfer encoding is used. Information about the size of
     * each data block is sent with the data.
     */
    RW_HTTP_CHUNKED = 1,

    /**
     * No transfer encoding is used. The length of the message is not known
     * in advance, but the connection will close when all data has been
     * sent.
     */
    RW_HTTP_CLOSE = 2
};

class RW_HTTP_GLOBAL RWHttpPortalImp : public RWPortalImp
{
public:
    RWHttpPortalImp();
    // default constructor

    ~RWHttpPortalImp();
    // destructor

    virtual RWNetBuf
    recv();
    // Receives a buffer of data
    // Note: May make more than one call to communications channel

    virtual int
    recv(char* buf, int len, RWNetBuf::State* state);
    // Receives a buffer of at most len bytes of data
    // Note: May make more than one call to communications channel

    virtual int
    send(const char* buf, int len);
    // throws RWNetCantSendError

    virtual RWNetBuf
    recv(unsigned long timeout);
    // Receives a buffer of data with every call to the underlying
    // recv method being timed
    // Note: May make more than one call to communications channel

    virtual int
    recv(char* buf, int len, RWNetBuf::State* state, unsigned long timeout);
    // Receives a buffer of data of at most len bytes of data with
    // every call to the underlying recv method being timed
    // Note: May makes more than one call to communications channel

    virtual int
    send(const char* buf, int len, unsigned long timeout);
    // throws RWNetCantSendError

    void
    setPortal(const RWPortal& portal, size_t length,
              RWHttpTransferEncoding te = RW_HTTP_NONE);
    // Set the underlying portal

    bool
    isEOF() const;
    // Returns a bool indicating whether or not
    // all data has been read from this portal

private:
    size_t
    getChunkSize(unsigned long timeout);

private:
    bool                eof_;
    RWPortal                 portal_;
    size_t                   length_;
    RWHttpTransferEncoding   te_;
};

inline
RWHttpPortalImp::RWHttpPortalImp()
    : eof_(true),
      length_(0)
{
}

inline bool
RWHttpPortalImp::isEOF() const
{
    return eof_;
}

#endif  // __rw_http_RWHttpPortalImp_h__ 
