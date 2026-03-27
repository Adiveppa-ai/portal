#ifndef BAS_LOCKABLEHASHMAP_HPP
#define BAS_LOCKABLEHASHMAP_HPP

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
//	This class wraps a hashmap container, extending it with the ability to do
//	key-based locking. This is for the case when the hash is shared and 
//	manipulation of a key must be guarded from the container's perspective. 
//	The locking is explicitly done so that the user has the ability to 
//	control lock lifetime.
//
// Current Issues:
/** 
 *	@todo Currently the locking semantics are very simple - the entire
 *	      container is locked. Bucket locking will need to be supported
 *	      for Timos for better concurrency. This can become the hard-coded
 *	      implementation, or can be made selectable. Revisit this based
 *	      on the RW implementation.
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

#ifndef RW_TOOLS_STDEX_HASHMAP_H_
  #include <rw/stdex/hashmap.h>
#endif
#ifndef BAS_LOCKABLEHASHMAPBASE_HPP
  #include "BAS/LockableHashMapBase.hpp"
#endif


namespace BAS
{
	/** \class LockableHashMap<K, T, H, EQ> LockableHashMap.hpp "BAS/LockableHashMap.hpp"
 	 *	This class wraps a hashmap container, extending it with the ability to
 	 *	do key-based locking. This is for the case when the hash is shared and 
 	 *	manipulation of a key must be guarded from the container's perspective. 
 	 *	The locking is explicitly done so that the user has the ability to 
 	 *	control lock lifetime.
 	 */
	template <
		class K, class T, class H, class EQ, 
		class A = std::allocator<std::pair<const K,T> > >
	class LockableHashMap : public
		BAS::LockableHashMapBase<K, T, rw_hashmap<K, T, H, EQ, A> >
		D_THREADINFO_M
	{
	D_NONTHREADSAFE

	public:
		/** @name Typedefs */
		//@{
		/** Underlying container type.
 	 	 */
		typedef rw_hashmap<K, T, H, EQ, A> BaseContainer;
		//@}

		/** @name Public Constructors */
		//@{
		/** Standard constructor.  
	 	 *	Uses a default rw_hashmap.
	 	 */
		LockableHashMap();

		/** Initializing constructor.  
	 	 *	@param hashFunctor Hash function to use.
	 	 *	@param numberOfBuckets Initial size of the hashmap.
	 	 */
		LockableHashMap(const H& hashFunctor, size_t numberOfBuckets);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		~LockableHashMap();
		//@}

	private:
		//
		// Disallow use.
		//
		LockableHashMap(const LockableHashMap& h);
		const LockableHashMap& operator=(const LockableHashMap& h);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockableHashMap.cpp"
#endif

#endif
