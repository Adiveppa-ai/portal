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
//	Specific type of key-based object pool for locks. Templatized on key
//	type and lock type.
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
// 29-May-2003  Keith Brefczynski	Created
// 25-Feb-2004  Mitch Neson 		Added constructor with GrowStrategy
//
//=============================================================================

#ifndef BAS_LOCKPOOL_HPP
  #include "BAS/LockPool.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif


template <class K, class L>
BAS::LockPool<K, L>::LockPool(size_t size) :
	BAS::KeyedObjectPool<K, L>(size)
{
	D_ENTER("BAS::LockPool::LockPool(size_t size)");
	D_ARG(size);
	RWPRECONDITION(size > 0);

	// Nothing else to do.
}

template <class K, class L>
BAS::LockPool<K, L>::LockPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy) :
	BAS::KeyedObjectPool<K, L>(size, iGrowingStrategy)
{
	D_ENTER("BAS::LockPool::LockPool(size_t size)");
	D_ARG(size);
	D_ARG(iGrowingStrategy);
	RWPRECONDITION(size > 0);

	// Nothing else to do.
}

template <class K, class L>
BAS::LockPool<K, L>::~LockPool()
{
	D_ENTER("BAS::LockPool::~LockPool()");

	// Nothing to do.
}
