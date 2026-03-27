#ifndef BAS_NOGROWINGSTRATEGY_HPP
#define BAS_NOGROWINGSTRATEGY_HPP

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
//	 No grow logic for fixed size pools. 
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

#ifndef BAS_FIXEDGROWINGSTRATEGY_HPP
  #include "BAS/FixedGrowingStrategy.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
 

namespace BAS
{
	/** \class NoGrowingStrategy NoGrowingStrategy.hpp "BAS/NoGrowingStrategy.hpp"
 	*  No grow logic for pools.
 	*/
	class NoGrowingStrategy : public BAS::FixedGrowingStrategy D_THREADINFO_M
	{
	D_THREADSAFE

	public:
                //@{
                /** Standard constructor
                 */
                 NoGrowingStrategy();

                /** Copy constructor
                 */
                 NoGrowingStrategy(const BAS::NoGrowingStrategy& iGrowingStrategy);
                //@}

		/** @name Public Member Functions */
		//@{
		/** Clone a NoGrowingStrategy
	 	 *  @return a pointer to a cloned NoGrowingStrategy
	 	 */
		virtual BAS::NoGrowingStrategy* clone() const;

		/** Output operator.
		 *  @param std::ostream& Output stream.
	 	 *  @return std::ostream& Output stream.
		*/
		virtual std::ostream& operator<<(std::ostream& os) const;

		//@}

	
	private:
		//
		// Disallow use.
		//
		const NoGrowingStrategy& operator=(const NoGrowingStrategy& p);
	};

}

inline BAS::NoGrowingStrategy*
BAS::NoGrowingStrategy::clone() const{
	
	return (new NoGrowingStrategy(*this));
}

#endif
