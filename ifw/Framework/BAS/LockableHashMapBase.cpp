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
//	Base class for lockable hashmaps.
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

#ifndef BAS_LOCKABLEHASHMAPBASE_HPP
  #include "BAS/LockableHashMapBase.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif


template <class K, class T, class C>
BAS::LockableHashMapBase<K, T, C>::LockableHashMapBase() :
	BAS::LockableTable<K, T, C>()
{
	D_ENTER("BAS::LockableHashMapBase::LockableHashMapBase()");

	// Nothing else to do.
}

template <class K, class T, class C>
BAS::LockableHashMapBase<K, T, C>::~LockableHashMapBase()
{
	D_ENTER("BAS::LockableHashMapBase::~LockableHashMapBase()");

	// Nothing to do.
}
