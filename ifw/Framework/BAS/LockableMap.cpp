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
//	This class wraps a map container, extending it with the ability to do
//	key-based locking. This is for the case when the map is shared and 
//	manipulation of a key must be guarded from the container's perspective. 
//	The locking is explicitly done so that the user has the ability to 
//	control lock lifetime.
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
// 07-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LOCKABLEMAP_HPP
  #include "BAS/LockableMap.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif


template <class K, class T, class C>
BAS::LockableMap<K, T, C>::LockableMap() :
	BAS::LockableMapBase<K, T, BaseContainer>()
{
	D_ENTER("BAS_LockableMap::LockableMap()");

	this->setBaseContainer(new BaseContainer);
}

template <class K, class T, class C>
BAS::LockableMap<K, T, C>::~LockableMap()
{
	D_ENTER("BAS_LockableMap::~LockableMap()");

	// Nothing to do.
}
