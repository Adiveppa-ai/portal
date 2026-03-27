#ifndef EDR_SDSLONGTYPE_HPP
#define EDR_SDSLONGTYPE_HPP

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
//
// Current Issues:
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Shivaram
// Backup-Responsible: Giles Douglas
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 18-Aug-2003  Giles Douglas       Initial Revision
//
//=============================================================================

#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif

namespace EDR
{
	class SDSLongType: public FieldDescr D_THREADINFO_M
	{
		D_SINGLETHREADED

	public:
		SDSLongType(const BAS::String& name = BAS::NULL_STRING);

		virtual ~SDSLongType();

		virtual const BAS::String& typeName() const;

		virtual bool hasFixedLength() const;

		virtual int64 supportedDatatypes() const;
		
		virtual FieldDescr* create(const BAS::String& name) const;

		virtual bool addParameter(const ParameterList& parameter,
								  BAS::String& failure);

		virtual bool isValid() const;

		virtual bool getLong(const BAS::String& value,
								size_t pos,
								size_t len,
								int64& buffer) const;

		virtual bool setLong(ByteBuffer& buffer,
								size_t len,
								int64 value) const;

		virtual void fieldInfo(BAS::String& value) const;

	private:
		EDR_EXPORT static const BAS::String typeNameCM;
	};
}

#endif
