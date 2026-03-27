#ifndef BAS_VALORDEREDVECTORITRBASE_HPP
#define BAS_VALORDEREDVECTORITRBASE_HPP

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
// 07-Mar-2003  kbref               Created
// 14-Mar-2003  kbref               Added base class and dervied iterator
//                                  and (new) const iterator from.
//
//=============================================================================

namespace BAS
{
/** Class ValOrderedVectorItrBase<T>.
 *  Base template class from which an RWTValOrderedVector<T> iterator
 *  and const interator are derived. This class is never instantiated
 *  directly.
 */
template <class T>
class ValOrderedVectorItrBase D_THREADINFO
{

D_NONTHREADSAFE

public:
	/** Advance self to next element.
	 *  This will be the first element if the iterator has just been
	 *  instantiated or reset.
	 *  @return True if have not advanced past last element; otherwise, false.
	 */
	bool operator++();

	/** Advance self to next element.
	 *  This will be the first element if the iterator has just been
	 *  instantiated or reset.
	 *  @return True if have not advanced past last element; otherwise, false.
	 */
	bool operator()();

	/** Reset self so that next advance will reference the first element.
	 */
	void reset();

	/** Check if the container being iterated on is empty.
	 *  This method is provided so that the container does have to be locked
	 *  twice when one wants to check if empty and then iterate.
	 *  @return True if container is empty; otherwise, false.
	 */
	bool isEmpty() const;

protected:
	ValOrderedVectorItrBase(RWTValOrderedVector<T>& vector);

	~ValOrderedVectorItrBase();

	RWTValOrderedVector<T>& getVector() const;

	typename RWTValOrderedVector<T>::size_type getCurrentIndex() const;

private:
	RWTValOrderedVector<T>& vectorM;

	typename RWTValOrderedVector<T>::size_type entriesM;

	typename RWTValOrderedVector<T>::size_type currentIndexM;

	// Disallow use.
	ValOrderedVectorItrBase();
	ValOrderedVectorItrBase(
		const ValOrderedVectorItrBase& itr);
	const ValOrderedVectorItrBase& operator=(
		const ValOrderedVectorItrBase& itr);
	bool operator++(int);
};

template <class T>
inline ValOrderedVectorItrBase<T>::ValOrderedVectorItrBase(
	RWTValOrderedVector<T>& vector) :
		vectorM(vector), 
		entriesM(vector.entries()),
		currentIndexM(-1)
{
	D_ENTER("ValOrderedVectorItrBase<T>::ValOrderedVectorItrBase(RWTValOrderedVector<T>& vector)");
	D_ARG(entriesM);

	// Nothing else to do.
}

template <class T>
inline ValOrderedVectorItrBase<T>::~ValOrderedVectorItrBase()
{
	D_ENTER("ValOrderedVectorItrBase<T>::~ValOrderedVectorItrBase()");

	// Nothing to do.
}

template <class T>
inline bool 
ValOrderedVectorItrBase<T>::operator++()
{
	D_ENTER("ValOrderedVectorItrBase<T>::operator++()");
	D_PRINT("current index: " << currentIndexM + 1);

	return (++currentIndexM != entriesM);
}

template <class T>
inline bool 
ValOrderedVectorItrBase<T>::operator()()
{
	D_ENTER("ValOrderedVectorItrBase<T>::operator()()");

	return ++(*this);
}

template <class T>
inline bool 
ValOrderedVectorItrBase<T>::isEmpty() const
{
	D_ENTER("ValOrderedVectorItrBase<T>::isEmpty()");

	return (entriesM == 0);
}

template <class T>
inline void 
ValOrderedVectorItrBase<T>::reset()
{
	D_ENTER("ValOrderedVectorItrBase<T>::reset()");

	currentIndexM = -1;
}

template <class T>
inline RWTValOrderedVector<T>& 
ValOrderedVectorItrBase<T>::getVector() const
{
	D_ENTER("ValOrderedVectorItrBase<T>::getVector()");

	return vectorM;
}

template <class T>
inline typename RWTValOrderedVector<T>::size_type
ValOrderedVectorItrBase<T>::getCurrentIndex() const
{
	D_ENTER("ValOrderedVectorItrBase<T>::getCurrentIndex()");
	D_ARG(currentIndexM);

	return currentIndexM;
}
}
#ifdef WHEN_CPP_EXISTS
#ifdef INC_TEMPL_DEFS
#include "BAS/ValOrderedVectorItrBase.cpp"
#endif
#endif

#endif
