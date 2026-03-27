#ifndef EDR_SDSSTRINGTYPE_HPP
#define EDR_SDSSTRINGTYPE_HPP

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
	class SDSStringType: public FieldDescr D_THREADINFO_M
	{
		D_SINGLETHREADED

	public:
		SDSStringType(const BAS::String& name = BAS::NULL_STRING);

		virtual ~SDSStringType();

		virtual const BAS::String& typeName() const;

		virtual bool hasFixedLength() const;

		virtual int64 supportedDatatypes() const;
		
		virtual FieldDescr* create(const BAS::String& name) const;

		virtual bool addParameter(const ParameterList& parameter,
								  BAS::String& failure);

		virtual bool isValid() const;

		virtual bool getString(const BAS::String& value,
								size_t pos,
								size_t len,
								BAS::String& buffer) const;

		virtual bool setString(ByteBuffer& buffer,
								size_t len,
								const BAS::String& value) const;

		virtual void fieldInfo(BAS::String& value) const;

	private:
		EDR_EXPORT static const BAS::String typeNameCM;
	};
}

#endif
