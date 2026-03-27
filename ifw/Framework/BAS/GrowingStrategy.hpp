#ifndef BAS_GROWINGSTRATEGY_HPP
#define BAS_GROWINGSTRATEGY_HPP

//=============================================================================
//
// Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
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
//	Generic grow logic for pools. 
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
// 10-Feb-2004  Mitch Nelson		Created
//
//=============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

namespace BAS
{
	/** \class GrowingStrategy GrowingStrategy.hpp "BAS/GrowingStrategy.hpp"
 	*  Generic grow logic for pools.
 	*/
	class GrowingStrategy D_THREADINFO_M
	{
	D_THREADSAFE

	public:
		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~GrowingStrategy();
		//@}

		/** @name Public Member Functions */
		//@{
		/** Calculate the amount to grow the pool by. Pure virtual.
		 *  @param size Current size of the pool.
	 	 *  @return amount to grow
	 	 */
		virtual size_t growBy(const size_t) = 0;

		/** Clone myself pure virtual.
	 	 *  @return pointer to a new me
	 	 */
		virtual GrowingStrategy* clone() const = 0;

		/** Output operator pure virtual.
		 *  @param std::ostream& Output stream.
	 	 *  @return std::ostream& Output stream.
	 	 */
		virtual std::ostream& operator<<(std::ostream& os) const = 0;
		//@}

		/** Output operator friend.
		 *  @param std::ostream& Output stream.
	 	 *  @return std::ostream& Output stream.
	 	 */
		friend std::ostream& operator<<(std::ostream& os, const BAS::GrowingStrategy& growingStrategy);

	protected:
		/** @name Protected Constructors */
		//@{
		/** Standard constructor
	 	 */
		GrowingStrategy();
		//@}
	
	private:

		//
		// Disallow use.
		//
		const GrowingStrategy& operator=(const GrowingStrategy& p);
	};
	std::ostream& operator<<(std::ostream& os, const BAS::GrowingStrategy& growStrategy);
}

#endif
