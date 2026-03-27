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
//	Lock guard class for protecting read and write access to keyed containers.
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
// 22-Apr-2004  Keith Brefczynski	Created
//
//=============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_KEYEDCONTAINERLOCKGUARD_HPP
  #include "BAS/KeyedContainerLockGuard.hpp"
#endif

template <class C, class L, class K>
BAS::KeyedContainerLockGuard<C, L, K>::KeyedContainerLockGuard() :
	isOwnerM(true),
	lockM(0)
{
	D_ENTER("BAS::KeyedContainerLockGuard::KeyedContainerLockGuard()");

	// Nothing else to do.
}

template <class C, class L, class K>
BAS::KeyedContainerLockGuard<C, L, K>::KeyedContainerLockGuard(
	C& container, const K& key, bool forUpdate) :
		isOwnerM(true),
		lockM(0)
{
	D_ENTER("BAS::KeyedContainerLockGuard::KeyedContainerLockGuard(C& container, const K& key, bool forUpdate)");
	D_ARG(key);
	D_BARG(forUpdate);

	//
	// Get the particular lock that needs to be acquired for the given key,
	// then acquire it and mark that it has been acquired.
	//
	acquire(container.getLock(key), forUpdate);
}

template <class C, class L, class K>
BAS::KeyedContainerLockGuard<C, L, K>::KeyedContainerLockGuard(
	L& lock, bool forUpdate) :
		isOwnerM(true),
		lockM(0)
{
	D_ENTER("BAS::KeyedContainerLockGuard::KeyedContainerLockGuard(L& lock, bool forUpdate)");
	D_ARG(&lock);
	D_BARG(forUpdate);

	//
	// Acquire the lock and mark that it has been acquired.
	//
	acquire(lock, forUpdate);
}

template <class C, class L, class K>
BAS::KeyedContainerLockGuard<C, L, K>::KeyedContainerLockGuard(
	const KeyedContainerLockGuard& sourceGuard) : 
		isOwnerM(sourceGuard.isOwnerM),
		lockM(sourceGuard.lockM)
{
	D_ENTER("BAS::KeyedContainerLockGuard::KeyedContainerLockGuard(const KeyedContainerLockGuard& sourceGuard)");
	D_ARG(sourceGuard);
	RWPRECONDITION(sourceGuard.isOwnerM == true);

	//
	// Transfer ownership.
	//
	const_cast<KeyedContainerLockGuard<C, L, K>&>(sourceGuard).isOwnerM = false;

	D_PRINT(*this);
}

template <class C, class L, class K>
BAS::KeyedContainerLockGuard<C, L, K>::~KeyedContainerLockGuard()
{
	D_ENTER("BAS::KeyedContainerLockGuard::~KeyedContainerLockGuard()");
	D_ARG(*this);

	//
	// Release the lock (if neccessary).
	//
	release();
}

// dbx helper function to enable you to print an object if at the dbx prompt
template <class C, class L, class K>
char*
db_pretty_print(
	const BAS::KeyedContainerLockGuard<C, L, K>* obj, 
	int flags, 
	const char *formatString)
{
	std::stringstream str;
	str << *obj;
	return (char *)(str.str().data());
}
