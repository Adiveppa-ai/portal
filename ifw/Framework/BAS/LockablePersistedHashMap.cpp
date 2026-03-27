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
//	See BAS/LockablePersistedHashMap.hpp. 
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
// 10-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LOCKABLEPERSISTEDHASHMAP_HPP
  #include "BAS/LockablePersistedHashMap.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif


template <class C>
BAS::LockablePersistedHashMap<C>::LockablePersistedHashMap(C* baseContainer) :
		BAS::LockableHashMapBase<KeyType, ValueType, C>()
{
	D_ENTER("BAS::LockablePersistedHashMap::LockablePersistedHashMap(C* baseContainer)");
	RWPRECONDITION(baseContainer != 0);

	this->setBaseContainer(baseContainer, false);
}

template <class C>
BAS::LockablePersistedHashMap<C>::~LockablePersistedHashMap()
{
	D_ENTER("BAS::LockablePersistedHashMap::~LockablePersistedHashMap()");

	// Nothing to do.
}
