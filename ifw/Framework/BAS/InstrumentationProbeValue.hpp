// @(#)%Portal Version: InstrumentationProbeValue.hpp:CUPmod7.3PatchInt:2:2006-Nov-21 08:53:10 %
#ifndef BAS_INSTRUMENTATION_PROBE_VALUE_H
#define BAS_INSTRUMENTATION_PROBE_VALUE_H

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
//	Instrumentation probe value class to represent a probe value.
//
// Note: Class T must have output operator<< and input operator>> defined
//       in order to use this class
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
// 23-Oct-2006  Ming-Wen Sung       CO236127 - add getValueWithoutLock() API
// 26-Oct-2006  Ming-Wen Sung       CO236475 - add getValue() that can take
//                                  lockProtected flag
// 30-Oct-2006  Ming-Wen Sung       CO236791 - remove getValue(BAS::Strig&) interface
//
//=============================================================================
#ifndef BAS_INSTRUMENTATION_PROBE_VALUE_IF_H
  #include "BAS/InstrumentationProbeValueIf.hpp"
#endif
#ifndef BAS_LOCKIF_HPP
  #include "BAS/LockIf.hpp"
#endif

namespace BAS
{
	/** <b>InstrumentationProbeValue</b> is a template class that represents
	 * a probe value. </br>
	 * Note: Class T must have output operator<< and input operator>> defined
	 * in order to use this class
	 */
	template<class T, class L = BAS::LockIf> 
		class InstrumentationProbeValue : 
		public InstrumentationProbeValueIf  D_THREADINFO
	{
		D_NONTHREADSAFE

	public:

		/** Standard constructor
		 * @param value the reference of instrumentation probe value
		 * @param valueLocker locker to synchrozie read/write to
		 * instrumentation value
		 * @param formatFlags format flags for the stream so that data 
		 * can be interpreted in a desired format
		 */
		InstrumentationProbeValue(
			T& value,
			L* valueLocker = 0,
			std::ios_base::fmtflags formatFlags = formatFlagsNotSpecifiedCM);

		/** Destructor.
		 */
		virtual ~InstrumentationProbeValue();

		/** @name InstrumentationProbeValueIf interface. */
		//@{
		/** Get value in this object
		 * @param value has the value of the object in string representation
		 * @param lockProtected flag indicates to get the value
		 * that is protected by a lock or not
		 * @return true if successful
		 */
		bool getValue(BAS::String& value, bool lockProtected) const;

		/** Set value in this object
		 * @param value new value in string representation
		 * @return true if successful
		 */
		bool setValue(const BAS::String& value); 
		//@}

        private:
		// Hide
		InstrumentationProbeValue();
		InstrumentationProbeValue(const InstrumentationProbeValue& i);
		const InstrumentationProbeValue& operator=(
			const InstrumentationProbeValue& i);

		BAS_EXPORT static const std::ios_base::fmtflags formatFlagsNotSpecifiedCM =
			static_cast<std::ios_base::fmtflags>(0);

		/** The reference of instrumentation probe value */
		T& valueM;
		L* valueLockerM;
		std::ios_base::fmtflags formatFlagsM;
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/InstrumentationProbeValue.cpp"
#endif

#endif
