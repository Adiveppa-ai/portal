//=============================================================================
//
//      Copyright (c) 2003 - 2007 Oracle. All rights reserved.
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Refer to BAS_LockableTable.hpp
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
// 28-May-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif


template <class K, class T, class C>
BAS::LockableTable<K, T, C>::LockableTable() :
	baseContainerM(0)
{
	D_ENTER("BAS::LockableTable::BAS_LockableTable()");

	// Nothing else to do.
}

template <class K, class T, class C>
BAS::LockableTable<K, T, C>::~LockableTable()
{
	D_ENTER("BAS::LockableTable::~LockableTable()");

	if (isBaseContainerOwnerM)
	{
		delete baseContainerM;
	}
}

template <class K, class T, class C>
void
BAS::LockableTable<K, T, C>::setBaseContainer(
	C* baseContainer, bool takeOwnership)
{
	D_ENTER("BAS::LockableTable::setBaseContainer(C* baseContainer, bool takeOwnership)");
	D_BARG(takeOwnership);
	RWPRECONDITION(baseContainer != NULL);

	baseContainerM = baseContainer;
	isBaseContainerOwnerM = takeOwnership;
}

template <class K, class T, class C>
C&
BAS::LockableTable<K, T, C>::getBaseContainer()
{
	D_ENTER("BAS::LockableTable::getBaseContainer()");
	RWRECONDITION(baseContainerM != NULL);

	return *baseContainerM;
}

template <class K, class T, class C>
void 
BAS::LockableTable<K, T, C>::acquire()
{
	D_ENTER("BAS::LockableTable::acquire()");

	//
	// Acquire the lock.
	//
	containerLockM.acquire();

	//
	// Set the owner.
	//
	{
		OwnerIdGuard guard(ownerIdLockM);

		ownerIdM = rwThreadHash(rwThreadId());
		D_PRINT("acquired by: " << ownerIdM);
	}
}
	
template <class K, class T, class C>
void 
BAS::LockableTable<K, T, C>::acquire(const K& key)
{
	D_ENTER("BAS::LockableTable::acquire(const K& key)");
	D_ARG(key);

	this->acquire();
}

template <class K, class T, class C>
void 
BAS::LockableTable<K, T, C>::release()
{
	D_ENTER("BAS::LockableTable::release()");

	OwnerIdGuard guard(ownerIdLockM);

	//
	// Release the lock.
	//
	containerLockM.release();
	D_PRINT("released by: " << ownerIdM);

	//
	// Reset the owner.
	//
	ownerIdM = 0;
}

template <class K, class T, class C>
void 
BAS::LockableTable<K, T, C>::release(const K& key)
{
	D_ENTER("BAS::LockableTable::release(const K& key)");
	D_ARG(key);

	this->release();
}

template <class K, class T, class C>
bool 
BAS::LockableTable<K, T, C>::isAcquired() const
{
	D_ENTER("BAS::LockableTable::isAcquired()");

	OwnerIdGuard guard(
		(const_cast<BAS::LockableTable<K, T, C>*>(this))->ownerIdLockM);

	D_PRINT("owner: " << ownerIdM);
	D_PRINT("self: " << rwThreadHash(rwThreadId()));

	return (ownerIdM == rwThreadHash(rwThreadId()));
}

template <class K, class T, class C>
bool 
BAS::LockableTable<K, T, C>::isAcquired(const K& key) const
{
	D_ENTER("BAS::LockableTable::isAcquired(const K& key)");
	D_ARG(key);

	return this->isAcquired();
}

template <class K, class T, class C>
bool
BAS::LockableTable<K, T, C>::find(const K& key, Itr& itr)
{
	D_ENTER("BAS::LockableTable::find(const K& key)");
	D_ARG(key);

	itr = baseContainerM->find(key);
	return (itr != baseContainerM->end());
}

template <class K, class T, class C>
bool
BAS::LockableTable<K, T, C>::findValue(const K& key, T& value) const
{
	D_ENTER("BAS::LockableTable::findValue(const K& key)");
	D_ARG(key);

	ConstItr itr = baseContainerM->find(key);
	if (itr != baseContainerM->end())
	{
		value = (*itr).second;
		return true;
	}

	return false;
}

template <class K, class T, class C>
bool 
BAS::LockableTable<K, T, C>::equalRange(const K& key, 
										Itr& lowerBound, 
										Itr& upperBound) const
{
	D_ENTER("BAS::LockableTable::equalRange(const K&, Itr&, Itr&)");
	D_ARG(key);

	std::pair<Itr, Itr> range = baseContainerM->equal_range(key);
	lowerBound = range.first;
	upperBound = range.second;

	return (lowerBound != upperBound);
}

template <class K, class T, class C>
bool 
BAS::LockableTable<K, T, C>::insert(const K& key, const T& value)
{
	D_ENTER("BAS::LockableTable::insert(const K& key, const T& value)");
	D_ARG(key);

	return (baseContainerM->insert(typename C::value_type(key, value))).second;
}

template <class K, class T, class C>
void 
BAS::LockableTable<K, T, C>::remove(Itr itr)
{
	D_ENTER("BAS::LockableTable::remove(Itr itr)");
	D_ARG((*itr).first);

	baseContainerM->erase(itr);
}

template <class K, class T, class C>
bool 
BAS::LockableTable<K, T, C>::remove(const K& key)
{
	D_ENTER("BAS::LockableTable::remove(const K& key)");
	D_ARG(key);

	return (baseContainerM->erase(key) == 1);
}

template <class K, class T, class C>
bool 
BAS::LockableTable<K, T, C>::contains(const K& key) const
{
	D_ENTER("BAS::LockableTable::contains(const K& key)");
	D_ARG(key);

	ConstItr itr = baseContainerM->find(key);
	if (itr != baseContainerM->end())
	{
		return true;
	}

	return false;
}

template <class K, class T, class C>
size_t 
BAS::LockableTable<K, T, C>::entries() const
{
	D_ENTER("BAS::LockableTable::entries()");

	ContainerLockGuard guard(
		(const_cast<BAS::LockableTable<K, T, C>*>(this))->containerLockM);

	return baseContainerM->size();
}

template <class K, class T, class C>
bool 
BAS::LockableTable<K, T, C>::isEmpty() const
{
	D_ENTER("BAS::LockableTable::isEmpty()");

	ContainerLockGuard guard(
		(const_cast<BAS::LockableTable<K, T, C>*>(this))->containerLockM);

	return baseContainerM->empty();
}

template <class K, class T, class C>
void 
BAS::LockableTable<K, T, C>::clear()
{
	D_ENTER("BAS::LockableTable::clear()");

	baseContainerM->clear();
}

template <class K, class T, class C>
typename BAS::LockableTable<K, T, C>::ConstItr 
BAS::LockableTable<K, T, C>::begin() const
{
	D_ENTER("BAS::LockableTable::begin()");

	return baseContainerM->begin();
}

template <class K, class T, class C>
typename BAS::LockableTable<K, T, C>::ConstItr 
BAS::LockableTable<K, T, C>::end() const
{
	D_ENTER("BAS::LockableTable::end()");

	return baseContainerM->end();
}
