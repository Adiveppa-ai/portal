#ifndef __rw_ftp_RWFtpEpsvReply_h__
#define __rw_ftp_RWFtpEpsvReply_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/RWFtpEpsvReply.h#1 $
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

#include <rw/ftp/RWFtpReply.h>
#include <rw/ftp/pkgdefs.h>
#include <rw/network/RWSockAddr.h>

class RWFtpFSM;

/*
 * RWFtpEpsvReply
 *
 * RWFtpEpsvReply is a specialization class of RWFtpReply.
 * It contains the server's internet address which is used
 * by the FTP client to establish an TCP connection to
 * the FTP server.
 *
 */

class RW_FTP_GLOBAL RWFtpEpsvReply : public RWFtpReply
{

    friend class RWFtpFSM;

public:

    RWFtpEpsvReply(const RWSockAddrBase& parent);
    // Default constructor

    RWSockAddr getAddress(void) const;
    // Returns the address of the data port on the server.

protected:

    virtual void parse(void);
    // provides an extended parse method that knows how to
    // pull the server data address out of the text part of
    // the reply.

private:

    friend RW_FTP_SYMBOLIC std::ostream&
    operator<< (std::ostream& str, const RWFtpEpsvReply& r);
    // outputs an RWFtpEpsvReply to an ostream

private:

    RWSockAddr addr_;
    RWSockAddr parentAddr_;
};

#endif // __rw_ftp_RWFtpEpsvReply_h__
