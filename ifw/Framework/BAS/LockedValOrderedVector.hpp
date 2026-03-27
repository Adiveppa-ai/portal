#ifndef BAS_LOCKEDVALORDEREDVECTOR_HPP
#define BAS_LOCKEDVALORDEREDVECTOR_HPP

//=============================================================================
//
// Copyright (c) 2003, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//   This template class is a thread-safe encapsulation of RWTValOrderedVector.
//
// Current Issues:
//   None
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
// 06-Mar-2003  kbref               Created
// 13-Mar-2003  kbref               Made generic and moved from TAM_Base to BAS
//
//=============================================================================

#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef __rw_sync_RWTMonitor_h__
  #include <rw/sync/RWTMonitor.h>
#endif
#ifndef __rw_sync_RWMutexLock_h__
  #include <rw/sync/RWMutexLock.h>
#endif

#ifndef BAS_LOCKEDITERATOR_HPP
  #include "BAS/LockedIterator.hpp"
#endif
#ifndef BAS_VALORDEREDVECTORITR_HPP
  #include "BAS/ValOrderedVectorItr.hpp"
#endif
#ifndef BAS_VALORDEREDVECTORCONSTITR_HPP
  #include "BAS/ValOrderedVectorConstItr.hpp"
#endif

/** Class BAS_LockedValOrderedVector<T>.
 *  This template class is a thread-safe encapsulation of 
 *  RWTValOrderedVector<T>.
 */
/** @todo Would be nice to templatize the lock type, too. Could then choose
 *  appropriately based on the access patterns of a particular instance. For
 *  example, if many concurrent readers, use RWReadersWritersLock. To add
 *  this, also need to similarly templatize the friend classes below (I think).
 */
namespace BAS
{
template <class T>
class LockedValOrderedVector : 
	public RWTMonitor<RWMutexLock> D_THREADINFO_M
{

D_THREADSAFE

//
// Locked iterators are friends since they need to access to
// the acquire()/release() methods, which should be private.
//
friend class LockedIterator<
	ValOrderedVectorItr<T>, LockedValOrderedVector<T> >;
friend class LockedIterator<
	ValOrderedVectorConstItr<T>, LockedValOrderedVector<T> >;

public:
	typedef typename RWTValOrderedVector<T>::size_type size_type;

	/** Public constructor.
	 */
	LockedValOrderedVector();

	/** Destructor.
	 */
	~LockedValOrderedVector();

	/** Remove all elements from self. Each element's destructor is called.
	 */
	void clear();

	/** Check if self is empty.
	 *  @return True if self is empty; otherwise, false.
	 */
	bool isEmpty() const;

	/** Get the number of elements in self.
	 *  @return Number of elements in self.
	 */
	size_type entries() const;

	/** Add an element to the end of the self.
	 *  @param key Reference to element to add.
	 */
	void append(const T& key);

	/** Fetch index'th element of self. Bounds checking is performed.
	 *  @param index Index of element to fetch.
	 *  @return Reference to index'th element.
	 */
	T& operator[](size_type index);
	const T& operator[](size_type index) const;

	/** Fetch index'th element of self. Bounds checking is not performed.
	 *  @param index Index of element to fetch.
	 *  @return Reference to index'th element.
	 */
	T& operator()(size_type index);
	const T& operator()(size_type index) const;

private:
	// Underlying container wrapped by instance.
	RWTValOrderedVector<T> vectorM;

	// Acquire mutually exclusive access to container.
	RWTValOrderedVector<T>& acquire();

	// Release access to container.
	void release();

	// Disable use.
	const LockedValOrderedVector& operator=(
		const LockedValOrderedVector& vector);
};

template<class T>
inline LockedValOrderedVector<T>::LockedValOrderedVector()
{
	D_ENTER("LockedValOrderedVector<T>::LockedValOrderedVector()");

	// Nothing else to do.
}

template<class T>
inline LockedValOrderedVector<T>::~LockedValOrderedVector()
{
	D_ENTER("LockedValOrderedVector<T>::~LockedValOrderedVector()");

	// Nothing to do.
}

template<class T>
inline RWTValOrderedVector<T>&
LockedValOrderedVector<T>::acquire()
{
	D_ENTER("LockedValOrderedVector<T>::acquire()");

	mutex().acquire();
	return vectorM;
}

template<class T>
inline void
LockedValOrderedVector<T>::release()
{
	D_ENTER("LockedValOrderedVector<T>::release()");

	mutex().release();
}

template<class T>
inline void 
LockedValOrderedVector<T>::clear()
{
	D_ENTER("LockedValOrderedVector<T>::clear()");

	LockGuard lock(monitor());
	vectorM.clear();
}

template<class T>
inline bool
LockedValOrderedVector<T>::isEmpty() const
{
	D_ENTER("LockedValOrderedVector<T>::isEmpty()");

	LockGuard lock(monitor());
	return vectorM.isEmpty();
}

template<class T>
inline typename LockedValOrderedVector<T>::size_type
LockedValOrderedVector<T>::entries() const
{
	D_ENTER("LockedValOrderedVector<T>::entries()");

	LockGuard lock(monitor());
	return vectorM.entries();
}

template<class T>
inline void 
LockedValOrderedVector<T>::append(const T& key)
{
	D_ENTER("LockedValOrderedVector<T>::append(const T&)");
	D_ARG(key);

	LockGuard lock(monitor());
	vectorM.append(key);
}

template<class T>
inline T&
LockedValOrderedVector<T>::operator[](size_type index)
{
	D_ENTER("LockedValOrderedVector<T>::operator[](size_type)");
	D_ARG(index);

	LockGuard lock(monitor());
	return vectorM[index];
}

template<class T>
inline const T&
LockedValOrderedVector<T>::operator[](size_type index) const
{
	D_ENTER("LockedValOrderedVector<T>::operator[](size_type)");
	D_ARG(index);

	LockGuard lock(monitor());
	return vectorM[index];
}

template<class T>
inline T&
LockedValOrderedVector<T>::operator()(size_type index)
{
	D_ENTER("LockedValOrderedVector<T>::operator()(size_type)");
	D_ARG(index);

	LockGuard lock(monitor());
	return vectorM(index);
}

template<class T>
inline const T&
LockedValOrderedVector<T>::operator()(size_type index) const
{
	D_ENTER("LockedValOrderedVector<T>::operator()(size_type)");
	D_ARG(index);

	LockGuard lock(monitor());
	return vectorM(index);
}
}
#ifdef WHEN_CPP_EXISTS
#ifdef INC_TEMPL_DEFS
#include "BAS/LockedValOrderedVector.cpp"
#endif
#endif

#endif // LOCKEDVALORDEREDVECTOR_HPP
