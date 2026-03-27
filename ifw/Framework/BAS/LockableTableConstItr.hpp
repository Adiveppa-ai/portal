#ifndef BAS_LOCKABLETABLECONSTITR_HPP
#define BAS_LOCKABLETABLECONSTITR_HPP

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
//	Thread-safe const iterator for lockable tables.
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
// 26-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LOCKABLETABLE_HPP
  #include "BAS/LockableTable.hpp"
#endif


namespace BAS
{
	/** \class LockableTableConstItr<K, T, C> LockableTableConstItr.hpp "BAS/LockableTableConstItr.hpp"
	 *	Thread-safe const iterator for lockable hashmaps.
	 */
	template <class K, class T, class C>
	class LockableTableConstItr D_THREADINFO
	{
	D_THREADSAFE

	public:
		typedef LockableTable<K, T, typename C::BaseContainer> 
			BaseLockableTable;

		/** @name Public Constructors */
		//@{
		/** Initializing constructor.
	 	 *	@param lockableTable The lockable hashmap to iterate on.
	 	 */
		LockableTableConstItr(const BaseLockableTable& lockableTable);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor.
	 	 */
		~LockableTableConstItr();
		//@}

		/** @name Public Methods */
		//@{
		/** Advance self to next element.
	 	 *  This will be the first element if the iterator has just been
	 	 *  instantiated.
	 	 *  @return True if have not advanced past last element; 
		 *	        otherwise, false.
	 	 */
		bool operator()();

		/** Fetch value of element referenced by self.
	 	 *  @return Value referenced by self.
	 	 */
		T value() const;
		//@}

	private:
		const BaseLockableTable& lockableTableM;
	
		typename BaseLockableTable::ConstItr itrM;
		typename BaseLockableTable::ConstItr itrEndM;

		bool isAcquiredM;
		bool atHeadM;
		bool atTailM;

		// Disallow use.
		LockableTableConstItr();
		LockableTableConstItr(const LockableTableConstItr& itr);
		const LockableTableConstItr& operator=(
			const LockableTableConstItr& itr);
		bool operator++();
		bool operator++(int);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockableTableConstItr.cpp"
#endif

#endif
