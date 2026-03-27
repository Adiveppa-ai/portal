#ifndef __rw_network_RWBufferedPortalImp_h__
#define __rw_network_RWBufferedPortalImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWBufferedPortalImp.h#1 $
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

#include <rw/network/RWBufferedPortal.h>
#include <rw/network/RWNetBuf.h>
#include <rw/network/RWPortal.h>
#include <rw/network/RWPortalImp.h>
#include <rw/network/pkgdefs.h>

class RW_NETWORK_GLOBAL RWBufferedPortalImp
    : public RWPortalImp, protected RWPortal
{
public:

    /*
     * Portal constructor.  Constructs a RWBufferedPortalImp from
     * an existing portal, with bufferSize bytes allocated as a
     * buffer. type indicates whether recv requests, send requests,
     * or both are buffered.
     */
    RWBufferedPortalImp(const RWPortal& portal, size_t bufferSize, RWBufferedPortal::BufferType type);

    /*
     * Destructor
     */
    virtual ~RWBufferedPortalImp();

    virtual RWNetBuf
    recv();

    virtual int
    recv(char* buf, int len, RWNetBuf::State* state);

    virtual int
    send(const char* buf, int len);

    virtual RWNetBuf
    recv(unsigned long timeout);

    virtual int
    recv(char* buf, int len, RWNetBuf::State* state, unsigned long timeout);

    virtual int
    send(const char* buf, int len, unsigned long timeout);

    /*
     * Sends any remaining buffered data.  If no data is buffered,
     * or buffering of send requests is not enabled, this function
     * does nothing.
     */
    void
    flush(void);

    void
    flush(unsigned long timeout);

protected:

    int
    sendbuf(void);

    int
    sendbuf(unsigned long timeout);

private:
    char* buf_;

    char* recv_buf_; // start of the recv buffer
    char* send_buf_; // start of the send buffer

    int recv_pos_;   // index of last character read from recv buffer

    int recv_len_;   // number of bytes in the recv buffer
    int send_len_;   // number of bytes in the send buffer

    int recv_cap_; // length of the recv buffer
    int send_cap_; // length of the send buffer

    // Copy constructor and assignment declared (only) private so they can't
    // be used accidentally
    RWBufferedPortalImp(const RWBufferedPortalImp&);
    RWBufferedPortalImp& operator=(const RWBufferedPortalImp&);
};

#endif  // __rw_network_RWBufferedPortalImp_h__ 
