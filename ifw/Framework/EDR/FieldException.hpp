#ifndef EDR_FieldException
#define EDR_FieldException

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
// 31-Aug-2004  Giles Douglas       Added new header template.
//
//=============================================================================

#ifndef   _PIN_TYPE_H_
  #include "pin_type.h"
#endif

namespace EDR
{
	class FieldException D_THREADINFO
	{
		D_SINGLETHREADED
	public:
		FieldException(pin_fld_num_t fld);
		pin_fld_num_t getField() const;
		virtual ~FieldException();
	private:
		pin_fld_num_t fldM;
	};

	inline FieldException::~FieldException() {}

	inline pin_fld_num_t FieldException::getField() const
	{
		return fldM;
	}

	inline FieldException::FieldException(pin_fld_num_t fld) : 
			fldM(fld)
	{
	}
}
#endif
