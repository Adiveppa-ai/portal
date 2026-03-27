#ifndef BAS_LOCKABLETABLE_HPP
#define BAS_LOCKABLETABLE_HPP

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
//	Base class for lockable conatiners that support the STL access interface
//	for associative containers, particularly map and rw_hashmap. This class
//	provides the access interface for these lockable containers by wrapping
//	the STL interface. 
//	Sub-classes are responsible for implementing the key-based locking 
//	semantics particular for the container it represents, i.e. locking a map 
//	may differ from locking a hashmap. The locking interface is key-based in 
//	order to facilitate fine-grained locking, as opposed to locking the entire 
//	container. This is useful for the case when the container is
//	multi-threaded and manipulation of a key must be guarded from the 
//	container's perspective. Locking is explicitly done so that the user has 
//	the ability to control lock lifetime. This class is not implcitly
//	thread-safe.
//
// Current Issues:
/** 
 *	@todo How to do locking for methods like entries(), isEmpty(), etc? Do
 *	      we need a separate container-level latch to protect operations
 *	      that modify its state? 
 */
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
// 07-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LATCH_HPP
  #include "BAS/Latch.hpp"
#endif
#ifndef __rw_sync_RWCriticalSection_h__
  #include <rw/sync/RWCriticalSection.h>
#endif
#ifndef __rw_sync_RWTLockGuard_h__
  #include <rw/sync/RWTLockGuard.h>
#endif


namespace BAS
{
	/** \class LockableTable<K, T, C> LockableTable.hpp "BAS/LockableTable.hpp"
 	 *	Base class for lockable conatiners that support the STL access interface
 	 *	of associative containers, particularly map and rw_hashmap. This class
 	 *	provides the access interface for these lockable containers by wrapping
 	 *	the STL interface, although all methods can be overriden. 
 	 *	Sub-classes are responsible for implementing the key-based locking 
 	 *	semantics particular for the container it represents, i.e. locking a map
 	 *	may differ from locking a hashmap. The locking interface is key-based 
 	 *	in order to facilitate fine-grained locking, as opposed to locking the 
 	 *	entire container. This is useful for the case when the container is
 	 *	multi-threaded and manipulation of a key must be guarded from the 
 	 *	container's perspective. Locking is explicitly done so that the user has
 	 *	the ability to control lock lifetime. This class is not implcitly
 	 *	thread-safe.
 	 */
	template <class K, class T, class C>
	class LockableTable D_THREADINFO
	{
	D_NONTHREADSAFE

	public:
		/** @name Typedefs */
		//@{
		typedef typename C::iterator Itr;
		typedef typename C::const_iterator ConstItr;
		//&}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~LockableTable();
		//@}

		/** @name Public Member Functions */
		//@{
		/** Lock the container for the specified key. 
	 	 *	@param key The key to do locking with respect to.
	 	 */
		virtual void acquire(const K& key);
	
		/** Unlock the container for the specified key.
	 	 *	@param key The key to do unlocking with respect to.
	 	 */
		virtual void release(const K& key);

		/** Is lock acquired for a given key?
	 	 *	@param key The key!
	 	 *  @return True if lock acquired for key; otherwise, False.
	 	 */
		virtual bool isAcquired(const K& key) const;

		/** Key-based lookup.
	 	 *	@param key The key value to do the lookup on.
	 	 *	@param itr (OUT) Iterator referencing matching entry, if found.
	 	 *  @return True if matching entry found; otherwise, False.
	 	 */
		virtual bool find(const K& key, Itr& itr);

		/** Key-based lookup.
	 	 *	@param key The key value to do the lookup on.
	 	 *	@param value (OUT) Matching value.
	 	 *  @return True if matching entry found; otherwise, False.
	 	 */
		virtual bool findValue(const K& key, T& value) const;

		/** Key-base lookup. Find everything with the same key.
		 * @param key The key value to do the lookup on.
		 * @param lowerBoubd (OUT) Iterator referencing the lower bound 
		 * of the match
		 * @param upperBoubd (OUT) Iterator referencing the higher bound 
		 * of the match
		 */
		virtual bool equalRange(const K& key, 
								Itr& lowerBound, 
								Itr& upperBound) const;

		/** Insert a (key, value) pair.
	 	 *	@param key Key of entry to insert.
	 	 *	@param value Value of entry to insert.
	 	 *	@return True if entry with key does not already exist; 
		 *	        otherwise, False.
	 	 */
		virtual bool insert(const K& key, const T& value);

		/** Removes the entry referenced by the given iterator.
	 	 *	@param itr Iterator referencing the entry to remove. 
	 	 */
		virtual void remove(Itr itr);

		/** Removes the entry for a given key.
	 	 *	@param key Key of entry to remove.
	 	 *	@return True if entry existed and was removed; otherwise, False.
	 	 */
		virtual bool remove(const K& key);

		/** Key-based existence check.
	 	 *	@param key The key value to check existence on.
	 	 *  @return True if an entry with the key exists; otherwise, False.
	 	 */
		virtual bool contains(const K& key) const;

		/** Number of entries in self.
		 *	@return You guess it!
		 */
		virtual size_t entries() const;

		/** Is self empty?
		 *	@return True if self has 0 entries; otherwise False.
		 */
		virtual bool isEmpty() const;

		/** Removes all entries from self.
	 	 *	Does not destroy key/value objects when the table is pointer-based.
	 	 */
		virtual void clear();

		/** @todo Temporary hack-ola to make latching work.
 		 */
		BAS::Latch* getLock() { return &containerLockM; }

		/** @todo Need to revisit the lockable iterators.
		 */
		void acquire();
		void release();
		bool isAcquired() const;
		ConstItr begin() const;
		ConstItr end() const;
		//@}

	protected:
		//
		// Standard constructor.  
		//
		LockableTable();

		//
		// Set handle to underlying container.
		//
		void setBaseContainer(C* baseContainer, bool takeOwnership = true);

		//
		// Get handle to underlying container.
		//
		C& getBaseContainer();

	private:
		// Underlying container.
		C* baseContainerM;
	
		// Does self own the underlying container?
		bool isBaseContainerOwnerM;

		// Container-wide key locking for now.
		BAS::Latch containerLockM;
		typedef RWTLockGuard<BAS::Latch> ContainerLockGuard;

		// Thread-id of current lock owner, and a lock for it.
		long ownerIdM;
		RWCriticalSection ownerIdLockM;
		typedef RWTLockGuard<RWCriticalSection> OwnerIdGuard;

		//
		// Disallow use.
		//
		LockableTable(const LockableTable& h);
		const LockableTable& operator=(const LockableTable& h);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockableTable.cpp"
#endif

#endif
