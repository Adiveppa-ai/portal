#ifndef __rw_ftp_RWFtpPwdReply_h__
#define __rw_ftp_RWFtpPwdReply_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/RWFtpPwdReply.h#1 $
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
#include <rw/cstring.h>

class RWFtpFSM;

/**
 * \ingroup ftp_package
 *
 * \brief
 * A specialization class of RWFtpReply that attempts to parse the FTP
 * protocol reply for the current directory information.
 *
 * RWFtpPwdReply is a specialization class of RWFtpReply. RWFtpPwdReply
 * attempts to parse the FTP protocol reply for the current directory
 * information. For instance, the following is a common type of server reply
 * from the \c PWD command:
 *
 * \code
 * 257 "/pub" is the current directory
 * \endcode
 *
 * In this reply, \c 257 is a standardized reply, as defined by the FTP RFC 959.
 * However, the RFC does not include a standard syntax for returning the
 * directory information in the text part of the message. RWFtpPwdReply
 * examines RWNumReplyLine objects contained within self in a last-to-first
 * order, searching for a quoted string. As soon as a match is found, a data
 * member is set to the path. The path can be obtained with the
 * getDirectory() member function.
 *
 * Although most FTP servers follow this technique, it is not guaranteed
 * because the directory information is returned in the reply text part of
 * the protocol reply. For this reason, failure to parse the directory from
 * the reply does \e not constitute an error. If the directory name cannot
 * be parsed, the getDirectory() method simply returns an empty string.
 */
class RW_FTP_GLOBAL RWFtpPwdReply : public RWFtpReply
{

    friend class RWFtpFSM;

public:

    /**
     * Default constructor.
     */
    RWFtpPwdReply(void);

    /**
     * Copy constructor.
     */
    RWFtpPwdReply(const RWFtpPwdReply& reply);

    /**
     * Assignment operator. Makes self a copy of \a reply. The previous
     * contents of self are lost.
     */
    RWFtpPwdReply&
    operator=(const RWFtpPwdReply& reply);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWFtpPwdReply::getDirectory() instead")
    RWCString directory(void) const;
#endif
    /**
     * Returns the present working directory that is obtained by examining
     * the reply text. See the Detailed Description section for this class.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getDirectory(void) const;

protected:

    /**
     * Provides an extended parse mechanism that can extract the directory
     * path out of the reply text.
     */
    virtual void parse(void);

private:

    /**
     * \relates RWFtpPwdReply
     *
     * Outputs an RWFtpPwdReply object to an \b std::ostream.
     *
     * \note
     * Class RWFtpPwdReply does not have an extraction (>>) operator.
     */
    friend RW_FTP_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWFtpPwdReply& r);

private:

    RWCString path_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWFtpPwdReply::directory(void) const
{
    return getDirectory();
}

typedef RW_DEPRECATE_TYPE("Use RWFtpPwdReply instead") RWFtpPwdReply RWIFtpPwdReply;
#endif

#endif // __rw_ftp_RWFtpPwdReply_h__
