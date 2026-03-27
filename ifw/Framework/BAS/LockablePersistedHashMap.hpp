#ifndef BAS_LOCKABLEPERSISTEDHASHMAP_HPP
#define BAS_LOCKABLEPERSISTEDHASHMAP_HPP

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
//	See below.
//
// Current Issues:
/** 
 *	@todo Currently the locking semantics are very simple - the entire
 *	      container is locked. Bucket locking will need to be supported
 *	      for Timos for better concurrency. This can become the hard-coded
 *	      implementation, or can be made selectable. Revisit this based
 *	      on the RW implementation.
 *
 *	@todo This class can initially be used for both hashmap and hash multimap.
 *	      If later, the requirements differ, will need to add
 *	      BAS_LockablePersistedHashMultiMap.
 *
 *	@todo Will eventually need high-concurrency locked iterators for timos 
 *	      table/index scans. This may prove to be tricky since the RW
 *	      hashmap implementation does not use independent bucket chains.
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
// 10-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LOCKABLEHASHMAPBASE_HPP
  #include "BAS/LockableHashMapBase.hpp"
#endif
#ifndef _MML_HASHMAP_H_
  #include "MML/hashmap.h"
#endif


namespace BAS
{
	/** \class LockablePersistedHashMap<C> LockablePersistedHashMap.hpp "BAS/LockablePersistedHashMap.hpp"
 	 *	This class wraps an relocatable hashmap container, extending it with 
	 *	the ability to do key-based locking. This is for the case when the hash 
	 *	is shared and manipulation of a key must be guarded from the container's
	 *	perspective. The locking is explicitly done so that the user has the 
	 *	ability to control lock lifetime.
 	 */
	template <class C>
	class LockablePersistedHashMap : public 
		LockableHashMapBase<typename C::KeyType, typename C::ValueType, C> 
		D_THREADINFO_M
	{
	D_NONTHREADSAFE

	public:
	    // Base container's key type.
	    typedef typename C::KeyType KeyType;
		
		// Base container's value type.
		typedef typename C::ValueType ValueType;
		
		/** \typedef BaseContainer
		 *	For compatibility with other lockables.
		 */
		typedef C BaseContainer;

		/** @name Public Constructors */
		//@{
		/** Initializing constructor.  
		 *	@param baseContainer Container to bind self to.
	 	 */
		LockablePersistedHashMap(C* baseContainer);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		~LockablePersistedHashMap();
		//@}

	private:
		//
		// Disallow use.
		//
		LockablePersistedHashMap();
		LockablePersistedHashMap(const LockablePersistedHashMap& h);
		const LockablePersistedHashMap& operator=(
			const LockablePersistedHashMap& h);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockablePersistedHashMap.cpp"
#endif

#endif
