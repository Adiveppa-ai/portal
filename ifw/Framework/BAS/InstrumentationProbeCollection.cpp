// @(#)%Portal Version: InstrumentationProbeCollection.cpp:CUPmod7.3PatchInt:1:2006-Nov-17 16:34:02 %
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
//	This is the base class for AttributeInstrumentationProbe, 
// GroupInstrumentationProbe, TableInstrumentationProbe, and 
// InstrumentationProbeList classes.  This template class has a singly-linked
// list as the member variable that contains a list of objects (class T) and 
// provides basic functions to maintain the list (e.g. append, begin, end, 
// isEmpty, clear, contains, and entries).  This template class is inherited
// from InstrumentationProbe abstract class, therefore, it also provides
// getValue() and setValue() interface functions to get and set a value of
// the object from the list that matches with the desired name.
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
//
//=============================================================================

#ifndef BAS_INSTRUMENTATION_PROBE_COLLECTION_H
  #include "BAS/InstrumentationProbeCollection.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

template<class T>
BAS::InstrumentationProbeCollection<T>::InstrumentationProbeCollection(
	const ProbeInfo& probeInfo,
	const int level) :
		InstrumentationProbe(probeInfo, level)
{
	D_ENTER("BAS::InstrumentationProbeCollection::InstrumentationProbeCollection(const ProbeInfo&, const int)");
	D_ARG(probeInfo);
	D_ARG(level);
	// Other preconditions are done in base class

	// Nothing else to do.
}

template<class T>
BAS::InstrumentationProbeCollection<T>::~InstrumentationProbeCollection()
{
	D_ENTER("BAS::InstrumentationProbeCollection::~InstrumentationProbeCollection()");

	clearAndDestroy();
}

template<class T>
bool
BAS::InstrumentationProbeCollection<T>::getValue(
	BAS::String& value,
	bool lockProtected,
	const BAS::String& name)
{
	D_ENTER("BAS::InstrumentationProbeCollection::getValue(BAS::String&, bool, const BAS::String&)");
	D_ARG(name);

	// NOTE: If name is specified (optional), we must traverse through children
	// elements to find the object with matched name and return its value

	if (name != BAS::NULL_STRING)
	{
		BAS::InstrumentationProbe* probeObj = NULL;
		if (getProbe(probeObj, name))
		{
			RWASSERT(probeObj != 0);
			if (probeObj->getValue(value, lockProtected))
			{
				// value retrieved successfully
				D_PRINT("value is " << value);
				D_RETURN(true);
				return true;
				/**********/
			}
		}
	}

	// not supported or not found or failed to retrieve value
	D_RETURN(false);
	return false;
}

template<class T>
bool
BAS::InstrumentationProbeCollection<T>::setValue(
	const BAS::String& value,
	const BAS::String& name)
{
	D_ENTER("BAS::InstrumentationProbeCollection::setValue(const BAS::String&, const BAS::String&)");
	D_ARG(value);
	D_ARG(name);

	// NOTE: If name is specified (optional), we must traverse through children
	// elements to find the object with matched name and set its value

	if (name != BAS::NULL_STRING)
	{
		BAS::InstrumentationProbe* probeObj = NULL;
		if (getProbe(probeObj, name))
		{
			RWASSERT(probeObj != 0);
			if (probeObj->setValue(value))
			{
				// value is set successfully
				D_PRINT("value is set to " << value << " successfully");
				D_RETURN(true);
				return true;
				/**********/
			}
		}
	}

	// not supported or not found or failed to set value
	D_RETURN(false);
	return false;
}

template<class T>
bool
BAS::InstrumentationProbeCollection<T>::getProbe(
	BAS::InstrumentationProbe*& probeObj,
	const BAS::String& name)
{
	D_ENTER("BAS::InstrumentationProbeCollection::getProbe(BAS::InstrumentationProbe*&, const BAS::String&)");
	D_ARG(name);

	if (name != BAS::NULL_STRING && name == getName())
	{
		// if name is specified and matched to the name of this object,
		// return this

		D_PRINT("found " << name << " to be itself");
		probeObj = this;
		D_RETURN(true);
		return true;
		/**********/
	}
	else if (name != BAS::NULL_STRING && name.startsWith(getName()))
	{
		// if name is specified (optional) and not itself, we must 
		// traverse through children elements to find the object 
		// with matched name and return it

		// first remove the name of this object from the name that
		// is passed from the argument.  for example, if name
		// passed is "GroupName.AttributeName" and "GroupName" matches
		// with the name of this object, we want to pass "AttributeName"
		// to children object when looking for matched object
		//
		size_t i = getName().length();
		const BAS::String childName = name(i + 1, name.length() - i - 1);
		D_PRINT("look for " << childName << " from its children objects for match");

		ProbeListConstItr itr = begin();
		ProbeListConstItr itrEnd = end();
		for (; itr != itrEnd; itr++)
		{
			if ((*itr)->getProbe(probeObj, childName))
			{
				// probe object retrieved successfully
				D_PRINT("found " << childName << " from its children objects");
				D_RETURN(true);
				return true;
				/**********/
			}
		}
	}
	else if (name == BAS::NULL_STRING)
	{
		// if name is not specified, return this

		D_PRINT("name is not set, return itself");
		probeObj = this;

		D_RETURN(true);
		return true;
		/**********/
	}

	// not found or failed to get probe object
	D_RETURN(false);
	return false;
}

