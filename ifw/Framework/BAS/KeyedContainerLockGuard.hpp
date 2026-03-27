#ifndef BAS_KEYEDCONTAINERLOCKGUARD_HPP
#define BAS_KEYEDCONTAINERLOCKGUARD_HPP

//=============================================================================
//
// Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Lock guard for protecting read and write access to keyed containers.
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Keith Brefczynski
// Backup-Responsible: Alan Lu
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 21-Apr-2004  Keith Brefczynski	Created
//
//=============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

namespace BAS 
{
	/** \class KeyedContainerLockGuard<C, L, K> KeyedContainerLockGuard.hpp "BAS/KeyedContainerLockGuard.hpp"
	 *	Acquires key-based access to a keyed container on construction and
	 *	releases it when the final owner of the guard is destructed. 
	 *	Templatized on container, lock, and key type. 
	 *	Transfers ownership on copy construction and assignment.
	 *
	 *	Assumptions:
	 *		- container implements getLock(const K& key)
	 *		- lock type implements acquireRead(), acquireWrite(), and release()
	 */
	template <class C, class L, class K>
	class KeyedContainerLockGuard D_THREADINFO_M
	{
	D_NONTHREADSAFE

    public:
		/** @name Public Constructors */
		//@{
		/** Default constructor.
		 *	Constructs a guard without acquiring the lock. Useful when a
		 *	guard is created first and "filled in" later via acquireXXX(). 
		 */
		KeyedContainerLockGuard();

		/** Initializing constructor.
		 *	Acquired lock for a given keyed container object.
		 *	@param container The keyed container being guarded.
		 *	@param key The key of the container object being accessed.
		 *	@param forUpdate If true, lock for update; otherwise, lock for read.
		 */
		KeyedContainerLockGuard(
			C& container, const K& key, bool forUpdate = false);

		/** ESP constructor.
		 *	Used when the lock to be acquired is already known. Lock is
		 *	acquired.
		 *	@param lock The lock to acquire.
		 *	@param forUpdate If true, lock for update; otherwise, lock for read.
		 */
		KeyedContainerLockGuard(L& lock, bool forUpdate = false);

		/** Copy constructor.
		 *	Ownership is transferred to copyee.
		 */
        KeyedContainerLockGuard(const KeyedContainerLockGuard& sourceGuard);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor.
		 */
		~KeyedContainerLockGuard();
		//@}

		/** @name Public Methods */
		//@{
		/** "Fills in" a guard instantiated via the default ctor.
		 *	Acquires the given lock read. The guard must not have
		 *	already acquired a lock when this method is called.
		 *	@param lock The lock to acquire.
		 */
		void acquireRead(L& lock);

		/** "Fills in" a guard instantiated via the default ctor.
		 *	Acquires the given lock for write. The guard must not have
		 *	already acquired a lock when this method is called.
		 *	@param lock The lock to acquire.
		 */
		void acquireWrite(L& lock);

		/*	Releases the lock currently held and acquires the given lock
		 *	for read.
		 *	Intended for use by full scan container iterators.
		 *	@param lock The lock to acquire.
		 */
		void reacquireRead(L& lock);

		/** Transfer the lock out of self.
		 *	@return Pointer to the acquired lock. Guaranteed to be non-zero.
		 */
		L* transferLock();

		/** Output operator.
		 *	Defined here since hpux blows when it comes to template friends.
 		 */
		friend std::ostream& operator<<(
			std::ostream& os, 
			const KeyedContainerLockGuard<C, L, K>& sourceGuard)
		{
			D_ENTER_F("std::ostream& operator<<(std::ostream& os, const KeyedContainerLockGuard& sourceGuard)");

			return os
				<< "["
			  	<< "is owner: " << sourceGuard.isOwnerM << ", "
			  	<< "lock: " << sourceGuard.lockM
			  	<< "]";
		}
		//@}

	private:
		/** Lock acquired for guarded access.
		 *	The lock is auto-released when the final owner of the guard
		 *	is destroyed.
		 *	Note that we choose to hold the lock instead of a [container, key]
		 *	pair and do lock.acquireXXX()/lock.release() directly instead
		 *	of container.acquire(key)/container.release(key). This is to
		 *	keep the size of the class minimized which makes copy construction
		 *	and assignment as fast as possible. Furthermore, release() is
		 *	faster since key->lock mapping is not needed.
		 */
		L* lockM;

		/** Indicates if self is the owner of the guard. Ownership is
		 *	transferred on copy construction/assignment, with the final
		 *	owner responsible for releasing the lock.
		 */ 
		bool isOwnerM;

		/** Acquire a lock.
		 *	@param lock Lock to acquire.
		 *	@param forUpdate If true, acquire lock for update; otherwise,
		 *		acquire lock for read.
		 */
		void acquire(L& lock, bool forUpdate);

		/** Whether or not the lock has been acquired.
		 *	@return True if lock has been acquired; otherwise, false.
		 */
		bool isAcquired() const;

		/** Lock mutator.
		 *	@param lock Value to set.
		 */
		void setLock(L& lock);

		/** Release lock if it has been acquired.
		 */
		void release();

		// Disallow use.
        const KeyedContainerLockGuard& operator=(
			const KeyedContainerLockGuard& sourceGuard);
	};
}

template <class C, class L, class K>
inline void
BAS::KeyedContainerLockGuard<C, L, K>::acquireRead(L& lock)
{
	D_ENTER("BAS::KeyedContainerLockGuard::acquireRead(L& lock)");
	D_ARG(&lock);

	acquire(lock, false);
}

template <class C, class L, class K>
inline void
BAS::KeyedContainerLockGuard<C, L, K>::reacquireRead(L& lock)
{
	D_ENTER("BAS::KeyedContainerLockGuard::reacquireRead(L& lock)");
	D_ARG(&lock);

	//
	// First, release the currently held lock, then acquire the new one.
	//
	release();
	acquire(lock, false);
}

template <class C, class L, class K>
inline void
BAS::KeyedContainerLockGuard<C, L, K>::acquireWrite(L& lock)
{
	D_ENTER("BAS::KeyedContainerLockGuard::acquireWrite(L& lock)");
	D_ARG(&lock);

	acquire(lock, true);
}

template <class C, class L, class K>
inline void
BAS::KeyedContainerLockGuard<C, L, K>::acquire(L& lock, bool forUpdate)
{
	D_ENTER("BAS::KeyedContainerLockGuard::acquire(L& lock, bool forUpdate)");
	D_ARG(&lock);
	D_BARG(forUpdate);
	RWPRECONDITION(isAcquired() == false);

	if (forUpdate == true)
	{
		D_PRINT("acquiring lock for write: " << &lock);
		lock.acquireWrite();
	}
	else
	{
		D_PRINT("acquiring lock for read: " << &lock);
		lock.acquireRead();
	}

	setLock(lock);
}

template <class C, class L, class K>
inline L*
BAS::KeyedContainerLockGuard<C, L, K>::transferLock()
{
	D_ENTER("BAS::KeyedContainerLockGuard::transferLock()");
	RWPRECONDITION(isAcquired() == true);

	//
	// Mark the lock as no longer owned by self, and give to caller.
	//
	D_PRINT("transferring lock: " << lockM);
	isOwnerM = false;

	return lockM;
}

template <class C, class L, class K>
inline void
BAS::KeyedContainerLockGuard<C, L, K>::release()
{
	D_ENTER("BAS::KeyedContainerLockGuard::release()");

	if (isAcquired() == true)
	{
		D_PRINT("releasing lock: " << lockM);
		lockM->release();
		lockM = 0;
	}
}

template <class C, class L, class K>
inline bool
BAS::KeyedContainerLockGuard<C, L, K>::isAcquired() const
{
	D_ENTER("BAS::KeyedContainerLockGuard::isAcquired() const)");

	D_RETURN(((isOwnerM == true) && (lockM != 0)));
	return ((isOwnerM == true) && (lockM != 0));
}

template <class C, class L, class K>
inline void
BAS::KeyedContainerLockGuard<C, L, K>::setLock(L& lock)
{
	D_ENTER("BAS::KeyedContainerLockGuard::setLock(L& lock)");
	D_ARG(&lock);
	RWPRECONDITION(isAcquired() == false);

	lockM = &lock;
}

#ifdef INC_TEMPL_DEFS
#include "BAS/KeyedContainerLockGuard.cpp"
#endif

#endif
