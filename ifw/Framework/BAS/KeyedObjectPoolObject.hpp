#ifndef BAS_KEYEDOBJECTPOOLOBJECT_HPP
#define BAS_KEYEDOBJECTPOOLOBJECT_HPP

//=============================================================================
//
// Copyright (c) 2003, 2017, Oracle and/or its affiliates. All rights reserved.
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	This is the class whose instances are pooled by a keyed object pool. 
//	Templatized on object type and contains an instance of the type. 
//	It also contains a reference count that is used by a keyed pool to
//  determine when an object is no longer active and can be returned to the
//	free pool. This class is not thread-safe.
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
// 23-May-2003  Keith Brefczynski	Created
// 09-Jun-2003	kbref				Remove key, let container deal with it.
//
//=============================================================================

#ifndef __rw_sync_RWSemaphore_h__
  #include <rw/sync/RWSemaphore.h>
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif


namespace BAS
{
	/** \class KeyedObjectPoolObject<T> KeyedObjectPoolObject.hpp "BAS/KeyedObjectPoolObject.hpp"
 	 *	This is the class whose instances are pooled by a keyed object pool. 
 	 *	Templatized on object type and contains an instance of the type. 
 	 *	It also contains a reference count that is used by a keyed pool to
 	 *  determine when an object is no longer active and can be returned to the
 	 *	free pool. This class is not thread-safe.
 	*/
	template <class T>
	class KeyedObjectPoolObject D_THREADINFO
	{
	D_NONTHREADSAFE

	public:
		/** @name Public Constructors */
		//@{
		/*  Standard constructor.  
	 	 *	Creates an instance with no oustanding references.
	 	 */
		KeyedObjectPoolObject();
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~KeyedObjectPoolObject();
		//@}

		/** @name Public Member Functions */
		//@{
		/** Object accessor. 
	 	 *	@return Reference to the object.
	 	 */
		T& getObject();

		/** Add a reference to the object. 
	 	 *  (This ensures it will not be returned to the free pool until this 
	 	 *  reference is removed (at the earliest)).
	 	 */
		void addReference();

		/** Remove a reference to the object. 
	 	 *  (This allows its return to the free pool when there are no 
	 	 *  outstanding references.) 
	 	 *  @return True if the object now has no outstanding references; 
	 	 *          otherwise False.
	 	 */
		bool removeReference();

		/** Determines if the object has any outstanding references.
	 	 *  @return True if object has outstanding references; False otherwise.
	 	 */
		bool hasReferences() const;
		//@}

	private:
		// Object itself.
		T objectM;

		// Number of oustanding references.
		size_t referencesM;

		//
		// Disallow use.
		//
		KeyedObjectPoolObject(const KeyedObjectPoolObject& p);
		const KeyedObjectPoolObject& operator=(const KeyedObjectPoolObject& p);
	};

//
// Semaphore specialization for timos lock pool. This is needed since we
// cannot use the default RWSemaphore ctor, as the count must be set to 1,
// i.e. RWSemaphore(1).
//
	template <>
	inline
	KeyedObjectPoolObject<RWSemaphore>::KeyedObjectPoolObject() :
		referencesM(0),
		objectM(1)
	{
		D_ENTER("BAS::KeyedObjectPoolObject::KeyedObjectPoolObject()");

		// Nothing else to do.
	}
}

#ifdef INC_TEMPL_DEFS
#include "BAS/KeyedObjectPoolObject.cpp"
#endif

#endif
