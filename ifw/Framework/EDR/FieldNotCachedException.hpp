#ifndef EDR_FieldNotCachedException
#define EDR_FieldNotCachedException
// -*-C++-*-

//=============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: EDR
//-----------------------------------------------------------------------------
// Module Description:
//   Exception thrown if a field is not found
//
// Current Issues:
//   Need to use some kind of abstract factory/clone pattern to avoid circular
//   dependency
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Giles Dougas
// Backup-Responsible:
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// DD-Jun-2002  Giles Douglas       Added new header template.
//
//=============================================================================

#ifndef   EDR_FieldException
  #include "EDR/FieldException.hpp"
#endif

namespace EDR 
{
	class FieldNotCachedException : public FieldException
	{
	public:
		FieldNotCachedException(pin_fld_num_t fld) : FieldException(fld) {};
	};
}

#endif
