// -*-C++-*-
#ifndef BAS_OBJECT_H
#define BAS_OBJECT_H

//=============================================================================
//
// Copyright (c) 2002, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Extended registered object that inherits various interface classes.
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
// 07-Aug-2002  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef BAS_CONTROLLERIF_H
  #include "BAS/ControllerIf.hpp"
#endif


namespace BAS
{
	/** 
	 *  This is an extended form of a BAS registered object. It is extended
	 *  in the sense that it inherits various interface classes whose
	 *  interfaces are applicable to most, if not all, registered objects
	 *  in the system. This class facilitates the exposure of these
	 *  interfaces to the system's registered objects.
	 */
	class Object :
		public BAS::RegisteredObject, 
		public BAS::ControllerIf
	{
	public:
		/** Destructor.
		 */
		virtual ~Object();

	protected:
		/** Standard constructor
         * @param name the name of the registered object to construct
         */
		Object(const BAS::String& name);

        /** Default constructor
         * Does nothing except delegate to the registered object
         * Needed for some of the test programs, that don't actually want
         * to create an allocator. This is especially important for the
         * heap allocator, which sometimes we want to create with no
         * registry information.
         */
		Object();
	private:
        // Hide
		Object(const Object& o);
		const Object& operator=(const Object& o);
	};
}

#endif
