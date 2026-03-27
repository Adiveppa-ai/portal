#ifndef BAS_VALORDEREDVECTORITR_HPP
#define BAS_VALORDEREDVECTORITR_HPP

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
//  Generic iterator for the RWTValOrderedVector<T> container.
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
/** Class ValOrderedVectorItr<T>
 *  This is a generic iterator for the RWTValOrderedVector<T> container.
 *  It is based on the RogueWave iterators, e.g. RWTValMultiMapIterator.
 *  It is used with LockedValOrderedVector<T>, a thread-safe
 *  RWTValOrderedVector<T>, which requires a locked iterator. This class,
 *  in conjunction with LockedIterator<Base, L> form such an iterator. 
 */
template <class T>
class ValOrderedVectorItr : 
	public ValOrderedVectorItrBase<T> D_THREADINFO_M
{

D_NONTHREADSAFE

public:
	/** Public constructor.
	 */
	ValOrderedVectorItr(RWTValOrderedVector<T>& vector);

	/** Destructor.
	 */
	~ValOrderedVectorItr();

	/** Fetch element referenced by self.
	 *  @return Reference to element referenced by self.
	 */
	T& key() const;

private:
	// Disallow use.
	ValOrderedVectorItr();
	ValOrderedVectorItr(const ValOrderedVectorItr& itr);
	const ValOrderedVectorItr& operator=(
		const ValOrderedVectorItr& itr);
};

template <class T>
inline ValOrderedVectorItr<T>::ValOrderedVectorItr(
	RWTValOrderedVector<T>& vector) : ValOrderedVectorItrBase<T>(vector)
{
	D_ENTER("ValOrderedVectorItr<T>::ValOrderedVectorItr(RWTValOrderedVector<T>& vector)");

	// Nothing else to do.
}

template <class T>
inline ValOrderedVectorItr<T>::~ValOrderedVectorItr()
{
	D_ENTER("ValOrderedVectorItr<T>::~ValOrderedVectorItr()");

	// Nothing to do.
}

template <class T>
inline T& 
ValOrderedVectorItr<T>::key() const
{
	D_ENTER("ValOrderedVectorItr<T>::key()");

	return this->getVector()[this->getCurrentIndex()];
}
}
#ifdef WHEN_CPP_EXISTS
#ifdef INC_TEMPL_DEFS
#include "BAS/ValOrderedVectorItr.cpp"
#endif
#endif

#endif
