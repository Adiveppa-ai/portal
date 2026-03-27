#ifndef BAS_LOCKIF_HPP
#define BAS_LOCKIF_HPP

//=============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component:
//-----------------------------------------------------------------------------
// Module Description:
//    Lock interface
//
// Current Issues:
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Alan Lu
// Backup-Responsible: Keith Brefczynski
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 07-Jan-2005	Giles Douglas       Initial revision
//
//=============================================================================

namespace BAS 
{
	/** Interface for locks
	 */
	class LockIf
	{
	public:
		virtual ~LockIf();
		virtual void acquire() = 0;
		virtual void release() = 0;
	};
}

#endif
