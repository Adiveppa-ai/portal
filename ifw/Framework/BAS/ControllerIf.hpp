// -*-C++-*-
#ifndef BAS_CONTROLLERIF_H
#define BAS_CONTROLLERIF_H

//=============================================================================
//
// Copyright (c) 2002, 2009, Oracle and/or its affiliates. 
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
//  Interface class for the various activities that control the system.
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

namespace BAS
{
	/**
	 *  Interface class for the various activities that control the system.
	 *  These activities include installing, uninstalling, starting up,
	 *  and shutting down the system. All objects who inherit this interface 
	 *  are required to implement it.
	 */
	class ControllerIf
	{
	public:
		/** Destructor
		 */
		virtual ~ControllerIf();

		/**
		 *  This method provides an opportunity for an object to do it's
		 *  necessary work (if any) when the system is installed.
		 *  @return true on success, false otherwise.
		 */
		virtual bool install() = 0;

		/**
		 *  This method provides an opportunity for an object to do it's
		 *  necessary work (if any) when the system is uninstalled.
		 *  @return true on success, false otherwise.
		 */
		virtual bool uninstall() = 0;

		/**
		 *  This method provides an opportunity for an object to do it's
		 *  necessary work (if any) when the system is started up.
		 *  @return true on success, false otherwise.
		 */
		virtual bool startup() = 0;

		/**
		 *  This method provides an opportunity for an object to do it's
		 *  necessary work (if any) when the system is shutdown.
		 *  @return true on success, false otherwise.
		 */
		virtual bool shutdown() = 0;

	protected:
		// Standard constructor.
		ControllerIf();

	private:
		// Disable use.
		ControllerIf(const ControllerIf& c);
		const ControllerIf& operator=(const ControllerIf& c);
	};
}

#endif
