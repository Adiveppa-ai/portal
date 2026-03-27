#ifndef __rw_ftp_RWFtpDataReply_h__
#define __rw_ftp_RWFtpDataReply_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/RWFtpDataReply.h#1 $
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
#include <rw/network/RWSocketPortal.h>
#include <iosfwd>

class RWFtpFSM;

/**
 * \ingroup ftp_package
 *
 * \brief
 * Specialization class of RWFtpReply containing an RWSocketPortal for data
 * that is to be read from or written to the underlying socket.
 *
 * RWFtpDataReply is a specialization class of RWFtpReply. It contains an
 * RWSocketPortal for data that is to be read from or written to the
 * underlying socket.
 */
class RW_FTP_GLOBAL RWFtpDataReply : public RWFtpReply
{

    friend class RWFtpFSM;

public:

    /**
     * Default constructor.
     */
    RWFtpDataReply(void);

    /**
     * Copy constructor.
     */
    RWFtpDataReply(const RWFtpDataReply& reply);

    /**
     * Assignment operator. Makes self a copy of \a reply. The previous
     * contents of self are lost.
     */
    RWFtpDataReply&
    operator=(const RWFtpDataReply& reply);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWFtpDataReply::getPortal() instead")
    RWSocketPortal portal(void) const;
#endif
    /**
     * Returns the RWSocketPortal to use for the data communication session.
     */
    RWSocketPortal getPortal(void) const;

private:

    /**
     * \relates RWFtpDataReply
     *
     * Outputs an RWFtpDataReply object to an \b std::ostream.
     *
     * \note
     * Class RWFtpDataReply does not have an extraction (>>) operator.
     */
    friend RW_FTP_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWFtpDataReply& r);

private:

    void setPortal(const RWSocketPortal& portal);
    // sets the data portal that will be contained within the
    // reply set.

    RWSocketPortal  portal_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWSocketPortal
RWFtpDataReply::portal(void) const
{
    return getPortal();
}

typedef RW_DEPRECATE_TYPE("Use RWFtpDataReply instead") RWFtpDataReply RWIFtpDataReply;
#endif

#endif // __rw_ftp_RWFtpDataReply_h__
