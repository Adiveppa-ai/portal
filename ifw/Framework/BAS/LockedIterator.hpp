#ifndef BAS_LOCKEDITERATOR_HPP
#define BAS_LOCKEDITERATOR_HPP

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
namespace BAS
{
template<class Base, class T>
class LockedIterator : public Base D_THREADINFO_M
{
public:
	LockedIterator(T& lockedClass);
	~LockedIterator();
	
private:
	T& lockedClassM;
};
}
#ifdef INC_TEMPL_DEFS
#include "BAS/LockedIterator.cpp"
#endif

#endif
