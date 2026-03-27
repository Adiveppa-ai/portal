// @(#)%Portal Version: InstrumentationProbeValueIf.hpp:CUPmod7.3PatchInt:2:2006-Nov-21 08:53:14 %
#ifndef BAS_INSTRUMENTATION_PROBE_VALUE_IF_H
#define BAS_INSTRUMENTATION_PROBE_VALUE_IF_H

//=============================================================================
//
// Copyright (c) 2005 - 2006 Oracle. All rights reserved.
//
// This material is the confidential property of Oracle Corporation or
// its licensors and may be used, reproduced, stored or transmitted only
// in accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Instrumentation probe value interface class
//
// Current Issues:
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Ming-Wen Sung
// Backup-Responsible: Shivaram
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 24-Jan-2005  Ming-Wen Sung       Created
// 07-Feb-2006  Ming-Wen Sung       Modified based on design in OMF
// 11-Mar-2006  Ming-Wen Sung       CO196231 - make InstrumentationProbeValueIf
//                                  non pure virtual
// 23-Oct-2006  Ming-Wen Sung       CO236127 - add getValueWithoutLock() API
// 26-Oct-2006  Ming-Wen Sung       CO236475 - add getValue() that can take
//                                  lockProtected flag
// 30-Oct-2006  Ming-Wen Sung       CO236791 - remove getValue(BAS::Strig&) interface
//
//=============================================================================

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace BAS
{
	/** <b>InstrumentationProbeValueIf</b> is the interface class that 
	 * defines getValue() and setValue() virtual classes.  For the value
	 * that can not use InstrumentationProbeValue class to represent the 
	 * value, use must define a new class which is inherited from
	 * InstrumentationProbeValueIf class and provide getValue() and
	 * setValue() functions.
	 */
	class InstrumentationProbeValueIf  D_THREADINFO
	{
		D_NONTHREADSAFE

	public:
		/** Standard destructor.
		 */
		virtual ~InstrumentationProbeValueIf();

		/** Get value in this object
		 * @param value has the value of the object in string representation
		 * @param lockProtected flag indicates to get the value that is
		 * protected by a lock
		 * @return true if successful
		 */
		virtual bool getValue(BAS::String& value, bool lockProtected) const;

		/** Set value in this object
		 * @param value new value in string representation
		 * @return true if successful
		 */
		virtual bool setValue(const BAS::String& value); 
	};

inline
InstrumentationProbeValueIf::~InstrumentationProbeValueIf()
{
}

inline bool
InstrumentationProbeValueIf::getValue(BAS::String& value, bool lockProtected) const
{
	return false;
}

inline bool
InstrumentationProbeValueIf::setValue(const BAS::String& value)
{
	return false;
}
}

#endif
