#ifndef __rw_network_RWWinSockInfo_h__
#define __rw_network_RWWinSockInfo_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWWinSockInfo.h#1 $
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

/*
 * The RWWinSockInfo class serves two functions.  It provides information
 * on the specifics of the winsock DLL to which the application is attached.
 * More importantly, its constructor initializes the winsock dll for the
 * application and the destructor cleans up.  An RWWinSockInfo must exist
 * while using winsock RWSocket, RWSockAddr, or any other classes that use
 * the winsock dll.  There needs to be an RWWinSockInfo object in each
 * application, not just in each dll.  The easiest way to accomplish this,
 * provided you do not use the SourcePro Net - Essential Networking Module
 * at static initialization time, is to define an RWWinSockInfo object as
 * the first thing in main.
 */

#include <rw/network/pkgdefs.h>
#include <rw/cstring.h>

/**
 * \ingroup networking_module
 *
 * \brief
 * Initializes the Winsock DLL on Windows platforms.
 *
 * Initializes the Winsock DLL on Windows platforms. Initialization is
 * required before your application can make requests of the Winsock API.
 * Deregistration is required for applications that no longer need Winsock
 * services.
 *
 * Rogue Wave encourages all users to include this class in their code.
 * While using this class does not affect the behavior of programs that run
 * on UNIX, it does make them portable to Windows environments.
 *
 * \note
 * If you use Winsock.dll in a DLL, either directly or indirectly, you must
 * initialize it. The fastest way to do this may be to create an instance of
 * RWWinSockInfo in \b DllMain().
 */
class RW_NETWORK_SYMBOLIC RWWinSockInfo
{
public:

    /**
     * Initializes the underlying socket API with the requested version. If
     * the Winsock DLL has already been initialized by this application, the
     * constructor does nothing. An exception of type RWNetWinsockInitError
     * is thrown if the initialization fails. This function is a no-op on
     * non Windows platforms.
     */
    RWWinSockInfo(short ver = 0x0202);

    // Clean up the winsock DLL if this is the outermost [[RWWinSockInfo]]
    // object.  If this is not the outermost [[RWWinSockInfo]] object, then
    // this does nothing.
    //
    // If there is a blocking call in progress, the blocking call is canceled.
    // If the blocking call was done using an [[RWSocket]], the call will throw
    // [[RWNetWinsockInitError]].
    /**
     * Performs the termination tasks.
     */
    ~RWWinSockInfo(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWWinSockInfo::getDescription() instead")
    RWCString description(void) const;
#endif

    /**
     * Returns the vendor-supplied description of the Winsock DLL. The
     * string "not winsock" is returned on platforms that do not support
     * winsock.
     */
    RWCString getDescription(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWWinSockInfo::getMajorVersion() instead")
    int majorVersion(void) const;
#endif

    /**
     * Returns the vendor-supplied major version of the Winsock DLL. Returns
     * \c 0 on platforms that do not support Winsock.
     */
    int getMajorVersion(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWWinSockInfo::getMinorVersion() instead")
    int minorVersion(void) const;
#endif

    /**
     * Returns the vendor-supplied minor version of the Winsock DLL. Returns
     * \c 0 on platforms that do not support Winsock.
     */
    int getMinorVersion(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    enum RW_DEPRECATE_TYPE("") BlockingHook { win16hook };

    RW_DEPRECATE_FUNC("")
    RWWinSockInfo(BlockingHook);

#  if defined(RWNET_WINSOCK) || defined(DOXYGEN)
    /**
     * \deprecated
     * As of SourcePro 4. Blocking hooks are no longer supported by the
     * Windows Socket 2 API.
     *
     * Initializes the Winsock DLL and installs the blocking hook indicated.
     * The previous blocking hook is restored when the RWWinSockInfo is
     * destroyed.
     *
     * \conditional
     * Only available on the Windows platform.
     */
    RW_DEPRECATE_FUNC("")
    RWWinSockInfo(FARPROC blockingHook);

    RW_DEPRECATE_FUNC("")
    static FARPROC lookUpBlockingHook(BlockingHook);
    // Common blocking hooks. You can install these using the
    // constructor.

#  endif // !RWNET_WINSOCK
#endif // !RW_DISABLE_DEPRECATED

#if defined(RWNET_WINSOCK)
private:

    void init(WSADATA*, short);
    // initialize the with version

private:

    WSADATA data_;
    // information about this winsock DLL

#  if !defined(RW_DISABLE_DEPRECATED)
    FARPROC previousBlockingHook_;
    // restore this in dtor
#  endif // !RW_DISABLE_DEPRECATED
#endif // !RWNET_WINSOCK
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWWinSockInfo::description(void) const
{
    return getDescription();
}

inline int
RWWinSockInfo::majorVersion(void) const
{
    return getMajorVersion();
}

inline int
RWWinSockInfo::minorVersion(void) const
{
    return getMinorVersion();
}
#endif

#endif  // __rw_network_RWWinSockInfo_h__ 
