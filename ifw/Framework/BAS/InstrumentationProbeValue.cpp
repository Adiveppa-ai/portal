// @(#)%Portal Version: InstrumentationProbeValue.cpp:CUPmod7.3PatchInt:2:2006-Nov-21 08:53:12 %
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

#ifndef BAS_INSTRUMENTATION_PROBE_VALUE_H
  #include "BAS/InstrumentationProbeValue.hpp"
#endif
#ifndef BAS_LOCKGUARD_HPP
  #include "BAS/LockGuard.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

template<class T, class L>
BAS::InstrumentationProbeValue<T, L>::InstrumentationProbeValue(
	T& value,
	L* valueLocker,
	std::ios_base::fmtflags formatFlags) :
	valueM(value),
	valueLockerM(valueLocker),
	formatFlagsM(formatFlags)
{
	D_ENTER("BAS::InstrumentationProbeValue::InstrumentationProbeValue(T&, L*, std::ios_base::fmtflags&)");
	D_ARG(value);
	D_ARG(formatFlags);

	// Nothing else to do.
}

template<class T, class L>
BAS::InstrumentationProbeValue<T, L>::~InstrumentationProbeValue()
{
	D_ENTER("BAS::InstrumentationProbeValue::~InstrumentationProbeValue(");
}

template<class T, class L>
bool
BAS::InstrumentationProbeValue<T, L>::getValue(BAS::String& value, bool lockProtected) const
{
	D_ENTER("BAS::InstrumentationProbeValue::getValue(BAS::String&, bool) const");

	std::ostringstream os;
	if (formatFlagsM != formatFlagsNotSpecifiedCM)
	{
		os.setf(formatFlagsM);
	}

	if (valueLockerM != 0 && lockProtected)
	{
		LockGuard<L> lock(*valueLockerM);
		os << valueM;
	}
	else
	{
		os << valueM;
	}

	value = BAS::String(os.str());

	D_RETURN(true);
	return true;
}

template<class T, class L>
bool
BAS::InstrumentationProbeValue<T, L>::setValue(const BAS::String& value)
{
	D_ENTER("BAS::InstrumentationProbeValue::setValue(const BAS::String&)");
	D_ARG(value);

	std::istringstream is(value.data());
	if (formatFlagsM != formatFlagsNotSpecifiedCM)
	{
		is.setf(formatFlagsM);
	}

	if (valueLockerM != 0)
	{
		LockGuard<L> lock(*valueLockerM);
		is >> valueM;
	}
	else
	{
		is >> valueM;
	}

	D_RETURN(true);
	return true;
}

