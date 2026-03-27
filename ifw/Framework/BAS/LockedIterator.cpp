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
//  This is a generic locking iterator
//
// Current Issues:
//  None
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Giles Douglas
// Backup-Responsible: ???
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 23-Jan-2002  Giles Douglas       Initial revision
// 06-Mar-2003  kbref               Moved from DAT_Discount to BAS.
//
//=============================================================================

#ifndef BAS_LOCKEDITERATOR_HPP
  #include "BAS/LockedIterator.hpp"
#endif

template<class Base, class T>
BAS::LockedIterator<Base, T>::LockedIterator(T& lockedClass) :
		lockedClassM(lockedClass),
		Base(lockedClass.acquire())
{
	D_ENTER("BAS::LockedIterator::LockedIterator(T&)");
}

template<class Base, class T>
BAS::LockedIterator<Base, T>::~LockedIterator()
{
	D_ENTER("BAS::LockedIterator<Base, T>::~LockedIterator()");
	lockedClassM.release();
}
