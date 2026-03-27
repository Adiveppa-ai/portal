#ifndef __RWDB_STATUSI_H__
#define __RWDB_STATUSI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/statusi.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **************************************************************************
 *
 * Class RWDBStatusImp encapsulates the status of an object or operation.
 * Most database-specific implementation classes derive from RWDBStatus.
 * RWDBStatus supports error-handling through explicit testing (isValid()),
 * through callbacks(setErrorHandler()), and through exceptions (raise()).
 * See the Users Guide for details.
 *
 **************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/status.h>


class RWDB_GLOBAL RWDBStatusImp
    : public RWDBReference
{
    friend class RWDB_GLOBAL RWDBStatus;
public:

    RWDBStatusImp(
        const RWCString& message,
        const RWCString& vendorMessage1,
        const RWCString& vendorMessage2,
        RWDBStatus::ErrorCode  errorCode = RWDBStatus::notInitialized,
        long             vendorError1 = 0,
        long             vendorError2 = 0 ,
        bool        isTerminal = false);

    virtual ~RWDBStatusImp();

    // Mutator functions (see comment above regarding defaults):
    // NB: setError calls error handler; changeError doesn't. Otherwise
    // they are identical.
    virtual void          setError(RWDBStatus::ErrorCode        code,
                                   bool        isTerminal,
                                   const RWCString& message,
                                   const RWCString& vendorMessage1,
                                   const RWCString& vendorMessage2,
                                   long             vendorError1 = 0,
                                   long             vendorError2 = 0);

    virtual void          changeError(RWDBStatus::ErrorCode        code,
                                      bool        isTerminal,
                                      const RWCString& message,
                                      const RWCString& vendorMessage1,
                                      const RWCString& vendorMessage2,
                                      long             vendorError1 = 0,
                                      long             vendorError2 = 0);

    // Raises exception if available, otherwise aborts
    void          raise() const;

    inline void          setErrorHandler(RWDBStatus::ErrorHandler newHandler)
    {
        errorHandler_ = newHandler;
    }

    // Accessor functions:
    inline RWDBStatus::ErrorCode     errorCode() const
    {
        return errorCode_;
    }
    inline long          vendorError1() const
    {
        return vendorError1_;
    }
    inline long          vendorError2() const
    {
        return vendorError2_;
    }
    inline bool     isValid() const
    {
        return errorCode_ == RWDBStatus::ok;
    }
    inline bool     isTerminal() const
    {
        return isTerminal_;
    }
    inline RWCString     message() const
    {
        return message_;
    }
    inline RWCString     vendorMessage1() const
    {
        return vendorMessage1_;
    }
    inline RWCString     vendorMessage2() const
    {
        return vendorMessage2_;
    }
    inline RWDBStatus::ErrorHandler errorHandler() const
    {
        return errorHandler_;
    }

    RWDBStatusImp* pattern() const;

protected:

    RWCString                 message_;           // Message string
    RWCString                 vendorMessage1_;    // Vendor-specific message
    RWCString                 vendorMessage2_;    // Vendor-specific message
    long                      vendorError1_;      // Vendor-specific code
    long                      vendorError2_;      // Vendor-specific code
    RWDBStatus::ErrorHandler  errorHandler_;
    RWDBStatus::ErrorCode     errorCode_;         // Generic error code
    bool                 isTerminal_;        // true if cannot recover

private :

    // Mutex for changing errors
    static RWDBStaticMutex    errChangeMutex_;

    // not implemented
    RWDBStatusImp(const RWDBStatusImp& statusImp);
    RWDBStatusImp& operator=(const RWDBStatusImp& statusImp);
};

#endif
