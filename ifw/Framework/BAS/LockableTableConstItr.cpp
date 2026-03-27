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
//	Thread-safe const iterator for lockable tables.
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
// 26-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LOCKABLETABLECONSTITR_HPP
  #include "BAS/LockableTableConstItr.hpp"
#endif


template <class K, class T, class C>
BAS::LockableTableConstItr<K, T, C>::LockableTableConstItr(
	const BaseLockableTable& lockableTable) :
		lockableTableM(lockableTable),
		isAcquiredM(false),
		atHeadM(true),
		atTailM(false)
{
	D_ENTER("BAS::LockableTableConstItr::LockableTableConstItr(const C& lockableTable");

	/** @todo For now, lock the entire container!
	 */
	const_cast<BaseLockableTable&>(lockableTableM).acquire();
	isAcquiredM = true;
}

template <class K, class T, class C>
BAS::LockableTableConstItr<K, T, C>::~LockableTableConstItr()
{
	D_ENTER("BAS::LockableTableConstItr::~LockableTableConstItr()");

	if (isAcquiredM == true)
	{
		const_cast<BaseLockableTable&>(lockableTableM).release();
	}
}

template <class K, class T, class C>
bool 
BAS::LockableTableConstItr<K, T, C>::operator()()
{
	D_ENTER("BAS::LockableTableConstItr::operator()()");

	RWPRECONDITION(!(atHeadM == true && atTailM == true));

	if (atTailM == false)
	{
		if (atHeadM == false)
		{
			++itrM;
		}
		else
		{
			itrM = lockableTableM.begin();
			itrEndM = lockableTableM.end(); 
			atHeadM = false;
		} 

		if (itrM == itrEndM)
		{
			atTailM = true;
			D_PRINT("reached the end");
		}
	}

	RWPOSTCONDITION(!(atHeadM == true && atTailM == true));

	return (atTailM == false);
}

template <class K, class T, class C>
T
BAS::LockableTableConstItr<K, T, C>::value() const
{
	D_ENTER("BAS::LockableTableConstItr::value()");

	return (*itrM).second;
}
