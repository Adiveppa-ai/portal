/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTRunnableIOUFunctionImp.cc#1 $
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


/*****************************************************************************

  RWTRunnableIOUFunctionImp - RWTFunctor<R()> based runnable class.

******************************************************************************/

#include <rw/thread/RWCancellation.h>
#include <rw/thread/RWTRunnableIOUFunctionImp.h>

template <class Return>
RWTRunnableIOUFunctionImp<Return>::RWTRunnableIOUFunctionImp(const RWTIOUEscrow<Return>& escrow)
    :
    escrow_(escrow)
{
}

template <class Return>
RWTRunnableIOUFunctionImp<Return>::RWTRunnableIOUFunctionImp(const RWTIOUEscrow<Return>& escrow,
        const RWTFunctor<Return()>& functor)
    :
    functor_(functor),
    escrow_(escrow)
{
}

template <class Return>
RWTFunctor<Return()>
RWTRunnableIOUFunctionImp<Return>::getFunctor(void) const
{
    // Lock the thread object
    LockGuard lock(monitor());
    return functor_;
}

template <class Return>
RWTIOUResult<Return>
RWTRunnableIOUFunctionImp<Return>::result(void) const
{
    return escrow_;
}

template <class Return>
void
RWTRunnableIOUFunctionImp<Return>::run(void)
{
    RWTFunctor<Return()> functor;
    RWTIOUEscrow<Return> escrow;
    {
        LockGuard lock(monitor());
        // Use second handle so that we don't have to worry about changes to
        // the functor_ member while executing the statements below.
        // (we don't want to lock the thread object across the functor invocation!)
        functor = functor_;

        // Is this escrow all used up (already closed or aborted)?
        if (!escrow_.closeable()) {
            // Get a new escrow since the current escrow has already been used.
            // (Perhaps because this runnable has been restarted...)
            escrow_ = escrow_.newInstance();
        }

        // Make a local copy of the escrow handle so that the escrow
        // instance can't be changed in mid-stream...
        escrow = escrow_;
    }

    RW_ASSERT(functor.isValid()); // USAGE ERROR - Functor handle is empty!
    RW_ASSERT(escrow.isValid()); // USAGE ERROR - Escrow handle is empty!

    if (functor.isValid()) {

        // Create a temporary for the result
        Return r;

        try {
            r = functor();
            if (escrow.isValid()) {
                escrow.close(r);
            }
        }
        catch (RWCancellation&) {
            // A RWCancellation exception indicates that the thread was canceled.
            // Disable abort reporting from cancellation object so we can destroy it...
            if (escrow.isValid()) {
                escrow.setException(RWTHROperationCanceled());    // ???
            }
            throw; // Rethrow to caller
        }
        catch (RWTHRxmsg& msg) {
            // We got some other kind of thread-safe exception,
            // Store the exception so we can rethrow it when the IOU is evaluated.
            if (escrow.isValid()) {
                escrow.setException(msg);
            }
        }
        catch (RWxmsg& msg) {
            // We got some other kind of exception,
            // Store the exception to throw later
            if (escrow.isValid()) {
                escrow.setException(msg.why());
            }
        }
        catch (...) {
            // We got some other kind of exception that we don't recognize
            // Store the exception to throw later
            if (escrow.isValid()) {
                escrow.setException(RWTHRxmsg(RW_THR_Unexpected_Exception));
            }
        }
    }
    else {
        // Set exception on escrow. Close with an exception so clients can
        // be informed that the runnable was started with an invalid functor.
        if (escrow.isValid()) {
            escrow.setException(RWTHRInvalidPointer(RW_THR_Invalid_Runnable_Functor));
        }
        ;
    }
}

template <class Return>
void
RWTRunnableIOUFunctionImp<Return>::setFunctor(const RWTFunctor<Return()>& functor)
{
    // Lock the thread object
    LockGuard lock(monitor());
    functor_ = functor;
}

template <class Return>
void
RWTRunnableIOUFunctionImp<Return>::setIOUEscrow(const RWTIOUEscrow<Return>& escrow)
{
    // Lock the thread object
    LockGuard lock(monitor());
    escrow_ = escrow;
}
