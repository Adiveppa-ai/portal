#ifndef BAS_LOCKABLEMAP_HPP
#define BAS_LOCKABLEMAP_HPP

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
//	This class wraps a map container, extending it with the ability to do
//	key-based locking. This is for the case when the map is shared and 
//	manipulation of a key must be guarded from the container's perspective. 
//	The locking is explicitly done so that the user has the ability to 
//	control lock lifetime.
//
// Current Issues:
/** 
 *	@todo Currently the locking semantics are very simple - the entire
 *	      container is locked. This *may* be good enough since for the
 *	      cases when finer-granularity locking is required, a lockable 
 *	      hashmap be the better choice.
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

#ifndef _RWSTD_MAP_INCLUDED
  #include <map>
#endif
#ifndef BAS_LOCKABLEMAPBASE_HPP
  #include "BAS/LockableMapBase.hpp"
#endif


namespace BAS
{
	/** \class LockableMap<K, T, C> LockableMap.hpp "BAS/LockableMap.hpp"
 	 *	This class wraps an STL map container, extending it with the ability to
 	 *	do key-based locking. This is for the case when the map is shared and 
 	 *	manipulation of a key must be guarded from the container's perspective. 
 	 *	Locking is explicitly done so that the user has the ability to 
 	 *	control lock lifetime.
 	 */
	template <class K, class T, class C> 
	class LockableMap : 
		public BAS::LockableMapBase<K, T, std::map<K, T, C> > D_THREADINFO_M
	{
	D_NONTHREADSAFE

	public:
		/** @name Typedefs */
		//@{
		/** Underlying container type.
	 	 */
		typedef std::map<K, T, C> BaseContainer; 
		//@}

		/** @name Public Constructors */
		//@{
		/** Standard constructor.  
	 	 */
		LockableMap();
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		~LockableMap();
		//@}

	private:
		//
		// Disallow use.
		//
		LockableMap(const LockableMap& h);
		const LockableMap& operator=(const LockableMap& h);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockableMap.cpp"
#endif

#endif
