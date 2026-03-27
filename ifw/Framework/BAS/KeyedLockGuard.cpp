//=============================================================================
//
// Copyright (c) 2003, 2009, Oracle and/or its affiliates. 
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
//	Generic lock guard for key-based locking of a resource.
//
// Current Issues:
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
// 27-May-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_KEYEDLOCKGUARD_HPP
  #include "BAS/KeyedLockGuard.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp" 
#endif

template <class K, class T>
BAS::KeyedLockGuard<K, T>::KeyedLockGuard(const K& key, T& resource) :
	resourceM(resource),
	keyM(key),
	acquiredM(false)
{
	D_ENTER("BAS::KeyedLockGuard::KeyedLockGuard(const K& key, T& resource)");
	D_ARG(key);

	resource.acquire(keyM);
	acquiredM = true;
}

template <class K, class T>
BAS::KeyedLockGuard<K, T>::~KeyedLockGuard()
{
	D_ENTER("BAS::KeyedLockGuard<K, T>::~KeyedLockGuard()");
	D_ARG(keyM);
	D_ARG(acquiredM);

	if (true == acquiredM)
	{
		resourceM.release(keyM);	
	}
}
