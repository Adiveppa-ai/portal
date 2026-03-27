#ifndef __rw_internet_RWStreamCoupler_h__
#define __rw_internet_RWStreamCoupler_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWStreamCoupler.h#1 $
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

#include <rw/internet/pkgdefs.h>
#include <rw/network/fwd.h>
#include <iosfwd>

class RWCString;

/**
 * \ingroup internet_basics_package
 * \class RWStreamCoupler
 *
 * \brief
 * Provides an automated mechanism for connecting an input stream to an
 * output stream.
 *
 * RWStreamCoupler provides an automated mechanism for connecting an input
 * stream to an output stream. You can use it in conjunction with the
 * network portal streams and the Internet classes to couple an FTP \c get
 * to an FTP \c put, an FTP \c get to a file, an FTP \c put from a file, and
 * a POP3 \c get to a file. You can also use it to automate copying one file
 * to another.
 *
 * The coupling mechanism respects canonical line termination in ASCII mode,
 * and always uses \c \<cr\>\<lf\> pairs to terminate lines when streaming
 * out to a portal.
 *
 * An optional end-of-input filter may be added to terminate the processing
 * of the input stream prior to the end of the stream.
 *
 * \example
 * \code
 * #include <rw/rstream.h>
 *
 * #include <rw/network/RWWinSockInfo.h>
 * #include <rw/network/RWSocketPortal.h>
 * #include <rw/network/RWPortalIStream.h>
 * #include <rw/network/RWInetHost.h>
 * #include <rw/network/RWInetAddr.h>
 *
 * #include <rw/internet/RWStreamCoupler.h>
 *
 * int
 * main(void)
 * {
 *     RWWinSockInfo info;
 *
 *     try {
 *         // get an address for daytime port on localhost
 *         RWInetAddr addr("daytime", RWInetHost::me());
 *
 *         // connect to address
 *         RWSocketPortal portal(addr);
 *
 *         // construct an input stream
 *         RWPortalIStream istr(portal);
 *
 *         // construct a coupler object using ASCII mode to couple
 *         RWStreamCoupler couple;
 *
 *         // connect the input stream to the output stream cout
 *         couple(istr, cout);
 *     }
 *     catch(const RWxmsg& msg) {
 *         cerr << "Error: " << msg.why() << endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_INTERNET_SYMBOLIC RWStreamCoupler
{
public:

    /**
     * Defines a \a Filter function that takes \c const \c RWCString& as its
     * argument. The purpose of a possible customized \a Filter function is
     * to allow the termination of the processing of an input stream prior
     * to the end of the stream.
     */
    typedef bool(*Filter)(const RWCString&);

    /**
     * Enumerates whether an RWStreamCoupler object adopts a line mode
     * (#mode_ascii) transfer with possible line termination and filter
     * issues, or a byte mode (#mode_binary) transfer.
     */
    enum TransferMode {

#if !defined(RW_DISABLE_DEPRECATED)

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWStreamCoupler::mode_ascii "mode_ascii" instead.
         *
         * line mode transfer
         */
        RW_DEPRECATE_ENUMERATOR(ASCII, "Use RWStreamCoupler::mode_ascii instead") = 0,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWStreamCoupler::mode_binary "mode_binary" instead.
         *
         * byte mode transfer
         */
        RW_DEPRECATE_ENUMERATOR(BINARY, "Use RWStreamCoupler::mode_binary instead") = 1,

#endif

        /**
         * line mode transfer
         */
        mode_ascii = 0,

        /**
         * byte mode transfer
         */
        mode_binary = 1

    };

    /**
     * Constructs an RWStreamCoupler object. If the \a mode argument is not
     * explicitly set, it is #mode_ascii by default.
     */
    RWStreamCoupler(TransferMode mode = mode_ascii);

    /**
     * Streams the contents of \a in into \a out. If the \a out argument is
     * an RWPortalOStream and the current transfer mode is #mode_ascii,
     * \c \<cr\>\<lf\> line termination is enforced. If a \a filter function
     * is passed in and the transfer mode is #mode_ascii, each line of input
     * from \a in is passed to the filter before streaming out to \a out.
     */
    bool
    operator()(std::istream& in,
               std::ostream& out);

    /**
     * Streams the contents of \a in into \a out. If the \a out argument is
     * an RWPortalOStream and the current transfer mode is #mode_ascii,
     * \c \<cr\>\<lf\> line termination is enforced. If a \a filter function
     * is passed in and the transfer mode is #mode_ascii, each line of input
     * from \a in is passed to the filter before streaming out to \a out.
     */
    bool
    operator()(std::istream& in, RWPortalOStream& out);

    /**
     * Streams the contents of \a in into \a out. If the \a out argument is
     * an RWPortalOStream and the current transfer mode is #mode_ascii,
     * \c \<cr\>\<lf\> line termination is enforced. If a \a filter function
     * is passed in and the transfer mode is #mode_ascii, each line of input
     * from \a in is passed to the filter before streaming out to \a out.
     */
    bool
    operator()(std::istream& in,
               std::ostream& out, Filter filter);

    /**
     * Streams the contents of \a in into \a out. If the \a out argument is
     * an RWPortalOStream and the current transfer mode is #mode_ascii,
     * \c \<cr\>\<lf\> line termination is enforced. If a \a filter function
     * is passed in and the transfer mode is #mode_ascii, each line of input
     * from \a in is passed to the filter before streaming out to \a out.
     */
    bool
    operator()(std::istream& in, RWPortalOStream& out, Filter filter);

    /**
     * Sets the transfer mode.
     */
    void setMode(TransferMode mode);

    /**
     * Gets the current transfer mode.
     */
    TransferMode getMode(void) const;

private:

    bool
    couple(std::istream& istr,
           std::ostream& ostr,
           bool bForceCRLF, Filter Filter);
    // performs the actual data copy.  If a filter is provided and
    // the transfer mode is mode_ascii, then each line is filtered prior
    // to passing it to the output stream. If bForceCRLF is true and
    // the mode is mode_ascii, a CR/LF pair is used to terminate each line.
    // Otherwise, the endl stream-manipulator is used for line termination.

private:

    TransferMode    mode_;
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWStreamCoupler instead") RWStreamCoupler RWIStreamCoupler;
#endif

#endif // __rw_internet_RWStreamCoupler_h__
