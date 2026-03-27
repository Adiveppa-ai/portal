#ifndef BAS_THREAD_HPP
#define BAS_THREAD_HPP
//=============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or
//      its subsidiaries or licensors and may be used, reproduced, stored or 
//      transmitted only in accordance with a valid Oracle license or 
//      sublicense agreement.
//
//-----------------------------------------------------------------------------
// Block: BAS
//
//-----------------------------------------------------------------------------
// Module Description:
//   Threaded runnable class implementation.
//
// Open Points:
//   The class is not thread safe. Concurrent access of a reference from 
//   getThread() and ~Thread() will cause a segv on the caller thread
//
// Review Status:
//   in-work
//
//-----------------------------------------------------------------------------
// Responsible: Giles Douglas
//-----------------------------------------------------------------------------
// $Log: Thread.h,v $
// Revision 1.13 05/02/06 echeng
// PRSF00208610 Add lock on access to the threadMapCM
//
// Revision 1.12 03/14/06 echeng
// PRSF00196336 Remove thread from threadMap in the destructor
//
// Revision 1.11 02/03/06 echeng
// PRSF00192305 Add member variable for RWThreadId and provide the getExecutionState
//              and getCompletionState methods
//
// Revision 1.10 11/11/05 ammon
// PRSF00186846 Use proper method for converting RWThreadId to u_int64
//
// Revision 1.9 07/16/03 jlan
// PRSF00144581 Add proc time per thread
//
// Revision 1.8 07/16/03 gdouglas
// Consolidated exception handling, and doxygen'd
//
// Revision 1.7  2001/10/26 14:17:54  bt
// PETS #40026 Contention scope default changed to SYSTEM.
//
// Revision 1.6  2000/09/29 09:28:46  aro
// Tried to fix doc++ comment.
//
// Revision 1.5  2000/01/28 14:15:51  bt
// Following optional registry entries added.
// - ThreadContentionScope   (value: 'Process' or 'System')
// - ThreadConcurrencyPolicy (value: 'NoChange' or 'Increase')
// - ThreadSchedulingPolicy  (value: 'TimeSlicedFixed',
//                                   'TimeSlicedDynamic' or 'Preemptive')
// - ThreadTimeSliceQuantum  (value: number of milliseconds)
// - ThreadPriority          (value: numerical priority)
//
// Revision 1.4  1999/11/10 09:04:33  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.3  1999/11/09 11:57:24  bt
// Method cancelAndJoinThread() changed.
// - check if an exception was produced added.
//
// Revision 1.2  1999/05/12 08:05:25  aro
// Assigemnt operators fixed.
//
// Revision 1.1  1999/04/27 12:53:06  bt
// Initial version.
//
//=============================================================================

#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef RW_TOOLS_TPHMAP_H
  #include <rw/tphdict.h>
#endif
#ifndef __rw_sync_RWThreadId_h__
  #include <rw/sync/RWThreadId.h> 
#endif

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef BAS_PROC_TIME_HPP
  #include "BAS/ProcTime.hpp"
#endif
#ifndef BAS_LATCH_HPP
  #include "BAS/Latch.hpp"
#endif

#define INSTRUMENTATION_INITIALIZE \
    BAS::ProcTime *__inst_procTime = NULL; \
    if (BAS::ProcTime::procTimeEnabledCM) \
    { \
        RWThreadId __inst_rw_thread_id = ::rwThreadId(); \
        BAS::Thread *__inst_bas_thread = BAS::Thread::getThread(__inst_rw_thread_id); \
        if (__inst_bas_thread)\
        { \
            __inst_procTime = &(__inst_bas_thread->getProcTime()); \
        } \
    } \
    else 

#define INSTRUMENTATION_START(arg) \
    if (__inst_procTime) \
    { \
	__inst_procTime->startTime(arg); \
    } \
    else 


#define INSTRUMENTATION_STOP(arg)\
    if (__inst_procTime) \
    { \
	__inst_procTime->stopTime(arg); \
    } \
    else 

#define INSTRUMENTATION_PRINT(arg) \
    if (__inst_procTime) \
    { \
	__inst_procTime->printData(arg); \
    } \
    else 

#define INSTRUMENTATION_COUNTER_PRINT(counter, arg) \
    if (__inst_procTime) \
    { \
	__inst_procTime->printCounterData(counter, arg); \
    } \
    else 


namespace BAS 
{
        /**
	  * The Hash Functor for ThreadMap
	  */
        struct HashFunctorThreadMap
        {
	      u_int64 operator()(const RWThreadId id) const;
        };


	/** This class represents a threaded runnable object.
	 *
	 * The following registry entries are optional.
	 * ThreadContentionScope (value: 'Process' or 'System')
	 * ThreadConcurrencyPolicy (value: 'NoChange' or 'Increase').
	 * ThreadSchedulingPolicy (value: 'TimeSlicedFixed',
	 *                              'TimeSlicedDynamic' or 'Preemptive').
	 * ThreadTimeSliceQuantum (value: number of milliseconds).
	 * ThreadPriority (value: numerical priority).
	 * Messages sent: MSG_INVALID_THREAD_STATE.
	 * Messages received: none.
	 * 
	 * Errors
	 * ERR_CREATE_THREAD_FAILED.
	 * ERR_INVALID_THREAD_STATE.
	 * ERR_THREAD_EXCEPTION.
	 */
	class Thread D_THREADINFO
	{
	public:

		/** @name Public Typedefs */
		//@{

		/** \typedef ThreadMap
		 *	Thread hash map container
		 */
	        typedef RWTPtrHashMap<RWThreadId, Thread, HashFunctorThreadMap,
		                      std::equal_to<RWThreadId> > ThreadMap;


		/** \typedef ThreadMapIterator
		 *	Thread hash map iterator
		 */
	        typedef ThreadMap::iterator ThreadMapIterator;

		//@}
		
		/** @name Public Constructors 
		 */
		//@{
		
		/** Constructs a threaded runnable object.<br> 
		 * @param objectPtr Pointer to an registered object. 
		 */
		Thread(RegisteredObject* objectPtr = 0);

		//@}
		
		/** @name Public Destructor 
		 */
		//@{
		
		/** Virtual destructor. 
		 */
		virtual ~Thread();
		
		//@}
		
		/** @name Public Member Functions 
		 */
		//@{

		/** Create a thread instance and execute the specified functor.
		 * @param functor functor to call to start thread
		 * @return true for thread created succesfully, false for error occured
		 */
		virtual bool createAndStartThread(const RWFunctor0& functor);

		/** Request cancellation and wait for the thread to complete execution.
		 * This must be called by the process shutting down the thread or
		 * the thread will enter an invalid state and log an error.
		 * @return true for success
		 */
		virtual bool cancelAndJoinThread();

		/** Print the thread attributes.
		 * Prints attributes of the thread to the specified stream
		 * @param os stream to print to
		 */
		virtual void printThreadAttributes(std::ostream& os);
		
		/** Request join of thread so that we wait for it to complete
		 * @return true
		 */
		virtual bool joinThread();

		/** Request join of a thread with a wait for a number of seconds
		 * @return the status
		 */
		virtual RWWaitStatus joinThread(unsigned long milliseconds);

		/** Get the BAS::ProcTime of the thread
		 * @return the ProcTime
		 */
	        BAS::ProcTime& getProcTime();

		/** @name Static objects/functions
		 */
		//@{

		/** Thread hashmap container
		 */
		BAS_EXPORT static ThreadMap threadMapCM;

		/** Get a Thread given a RW thread Id
		 * @return the thread
		 */
	        static Thread* getThread(const RWThreadId);

		/** Lock for thread hashmap access
		 */
		static BAS::Latch threadMapLockCM;
		//@}

		/** Get the object's thread id
		 * @return the thread id
		 */
		RWThreadId& getThreadId();

		/** Get the thread's execution state by
		 * redirecting to the RWThread's function
                 * @return execution state
                 */
		RWExecutionState getExecutionState();
                                                                                                                                
                /** Get the thread's completion state
		 * redirecting to the RWThread's function
                 * @return completion state
                 */
                RWCompletionState getCompletionState();


	private:

		/** Function to print errors in case of exceptions
		 * @param where what we were doing when the exception was thrown
		 * @param message the message to log
		 */
		void handleException(const BAS::String& where,
							 const BAS::String& message);


		/** Check for error states. Shared between joinThread and 
		 * cancelAndJoinThread 
		 * @param state desired exit state
		 * @return false for failure, true for success
		 */
		bool checkForError(RWCompletionState state);

		/** Remove the callback function
		 */
		void removeCallback();

		/** @name Static constant variables
		 */
		//@{
		/** Error message for alloc failure */
		BAS_EXPORT static const BAS::String allocFailureMessageCM;
		
		/** Error message for unknown exception */
		BAS_EXPORT static const BAS::String unknownExceptionMessageCM;
		
		/** Error message for invalid state change */
		BAS_EXPORT static const BAS::String invalidStateChangeMessageCM;
		
		/** Error message for error during thread creation */
		BAS_EXPORT static const BAS::String createThreadMessageCM;
		
		/** Error message for error during thread cancellation */
		BAS_EXPORT static const BAS::String cancelThreadMessageCM;

		//@}

		/** @name Private data members */
		//@{
		/** Storage for RWThread class */
		RWThread threadM;
		
		/** Thread attributes */
		RWThreadAttribute thrAttrM;
		
		/** Thread id */
		String threadIdStringM;

		/** Thread id */
		RWThreadId threadIdM;

		/** Object name - Set to the name of the registered object passed
		 * to the threads constructor */
		String objectNameStringM;

		/** Pointer to the registered object that the thread was created for */
		RegisteredObject* objectPtrM;

		/** Functor to call if in invalid state */
		RWFunctor2<const RWRunnable&,RWExecutionState> invalidStateFunctorM;

		/** Activity state of the thread */
		bool isThreadActiveM;
		
		/** Is the call back function set? */
		bool isCallbackActiveM;

		/** Is the contention scope set? */
		bool isContScopeSetM;

		/** Is the priority set? */
		bool isPrioritySetM;

		/** Has an exception been handled? */
		bool exceptionHandledM;
		
		/** Priority of thread */
		int64 priorityM;

		/** ProcTime of thread */
		ProcTime procTimeM;

		/** Read the configuration values out of the
		 * registry and set the thread attributes.
		 */
		void readRegistryAndSetAttributes();

		/** Callback function which will get called on invalid state changes.
		 */
		void invalidStateCallback(const RWRunnable& runnable,
								  RWExecutionState state);

		/** Private Copy constructor to prevent unintentional use
		 */
		Thread(const Thread& right);

		/** Private assignment operator to prevent unintentional use
		 */
		Thread& operator=(Thread& right);
	};

        inline Thread* Thread::getThread(const RWThreadId id)
	{
		RWLockGuard<BAS::Latch> actGuard(threadMapLockCM);
	        return threadMapCM.findValue(&id);
	}

	inline RWThreadId& Thread::getThreadId()
	{
		return threadIdM;
	}

        inline ProcTime& Thread::getProcTime()
	{
	        return procTimeM;
	}

        inline u_int64 HashFunctorThreadMap::operator()(const RWThreadId id) const
	{
	         u_int64 key = rwThreadHash(id);
		 u_int64 c1 = 0xd2d84a61;
		 u_int64 c2 = 0x7832c9f4;
		 key *= c1;
		 key ^= (key < 0) ? c2 : (0x7ffffffff ^ c2);
		 return key;
	}
}
#endif // BAS_THREAD_HPP

