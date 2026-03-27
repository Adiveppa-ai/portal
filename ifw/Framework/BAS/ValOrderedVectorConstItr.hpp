#ifndef BAS_VALORDEREDVECTORCONSTITR_HPP
#define BAS_VALORDEREDVECTORCONSTITR_HPP

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
//  Generic const iterator for the RWTValOrderedVector<T> container.
//
// Current Issues:
//  None
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Keith Brefczynski
// Backup-Responsible: Giles Douglas
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 14-Mar-2003  kbref               Created
//
//=============================================================================

#ifndef BAS_VALORDEREDVECTORITRBASE_HPP
  #include "BAS/ValOrderedVectorItrBase.hpp"
#endif

namespace BAS
{
/** Class ValOrderedVectorConstItr<T>
 *  This is a generic const iterator for the RWTValOrderedVector<T> container.
 *  It is based on the RogueWave iterators, e.g. RWTValMultiMapConstIterator.
 *  It is used with LockedValOrderedVector<T>, a thread-safe
 *  RWTValOrderedVector<T>, which requires a locked const iterator. This class,
 *  in conjunction with LockedIterator<Base, L> form such an iterator. 
 */
template <class T>
class ValOrderedVectorConstItr : 
	public ValOrderedVectorItrBase<T> D_THREADINFO_M
{

D_NONTHREADSAFE

public:
	/** Public constructor.
	 */
	ValOrderedVectorConstItr(RWTValOrderedVector<T>& vector);

	/** Destructor.
	 */
	~ValOrderedVectorConstItr();

	/** Fetch element referenced by self.
	 *  @return Const reference to element referenced by self.
	 */
	const T& key() const;

private:
	// Disallow use.
	ValOrderedVectorConstItr();
	ValOrderedVectorConstItr(
		const ValOrderedVectorConstItr& itr);
	const ValOrderedVectorConstItr& operator=(
		const ValOrderedVectorConstItr& itr);
};

template <class T>
inline ValOrderedVectorConstItr<T>::ValOrderedVectorConstItr(
	RWTValOrderedVector<T>& vector) : ValOrderedVectorItrBase<T>(vector)
{
	D_ENTER("ValOrderedVectorConstItr<T>::ValOrderedVectorConstItr(RWTValOrderedVector<T>& vector)");

	// Nothing else to do.
}

template <class T>
inline ValOrderedVectorConstItr<T>::~ValOrderedVectorConstItr()
{
	D_ENTER("ValOrderedVectorConstItr<T>::~ValOrderedVectorConstItr()");

	// Nothing to do.
}

template <class T>
inline const T& 
ValOrderedVectorConstItr<T>::key() const
{
	D_ENTER("ValOrderedVectorConstItr<T>::key()");

	return this->getVector()[this->getCurrentIndex()];
}
}
#ifdef WHEN_CPP_EXISTS
#ifdef INC_TEMPL_DEFS
#include "BAS/ValOrderedVectorConstItr.cpp"
#endif
#endif

#endif
