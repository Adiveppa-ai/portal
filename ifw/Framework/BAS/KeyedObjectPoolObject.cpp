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
//	This is the class whose instances are pooled by a keyed object pool. 
//	Templatized on object type and contains an instance of the type. 
//	It also contains a reference count that is used by a keyed pool to
//  determine when an object is no longer active and can be returned to the
//	free pool. This class is not thread-safe.
//
// Current Issues:
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Keith Brefczynski
// Backup-Responsible: Alan Lu
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 23-May-2003  Keith Brefczynski	Created
// 08-Jun-2003  kbref				Remove key, let container deal with it.
//
//=============================================================================

#ifndef BAS_KEYEDOBJECTPOOLOBJECT_HPP
  #include "BAS/KeyedObjectPoolObject.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif


template <class T>
BAS::KeyedObjectPoolObject<T>::KeyedObjectPoolObject() :
	referencesM(0)
{
	D_ENTER("BAS::KeyedObjectPoolObject::KeyedObjectPoolObject()");

	// Nothing else to do.
}

template <class T>
BAS::KeyedObjectPoolObject<T>::~KeyedObjectPoolObject()
{
	D_ENTER("BAS::KeyedObjectPoolObject::~KeyedObjectPoolObject()");

	// Nothing to do.
}

template <class T>
T& 
BAS::KeyedObjectPoolObject<T>::getObject()
{
	D_ENTER("BAS::KeyedObjectPoolObject::getObject()");

	return objectM;
}

template <class T>
void 
BAS::KeyedObjectPoolObject<T>::addReference()
{
	D_ENTER("BAS::KeyedObjectPoolObject::addReference()");
	D_ARG(referencesM);

	++referencesM;
}

template <class T>
bool 
BAS::KeyedObjectPoolObject<T>::removeReference()
{
	D_ENTER("BAS::KeyedObjectPoolObject::removeReference()");
	D_ARG(referencesM);
	RWPRECONDITION(referencesM > 0);

	--referencesM;

	return !hasReferences();
}

template <class T>
bool 
BAS::KeyedObjectPoolObject<T>::hasReferences() const
{
	D_ENTER("BAS::KeyedObjectPoolObject::hasReferences()");
	D_ARG(referencesM);

	return referencesM > 0;
}
