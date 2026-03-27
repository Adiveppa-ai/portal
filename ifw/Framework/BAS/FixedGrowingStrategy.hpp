#ifndef BAS_FIXEDGROWINGSTRATEGY_HPP
#define BAS_FIXEDGROWINGSTRATEGY_HPP

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
//	 Fixed number grow logic for pools. 
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

#ifndef BAS_GROWINGSTRATEGY_HPP
  #include "BAS/GrowingStrategy.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
 

namespace BAS
{
	/** \class FixedGrowingStrategy FixedGrowingStrategy.hpp "BAS/FixedGrowingStrategy.hpp"
 	*  Fixed number grow logic for pools.
 	*/
	class FixedGrowingStrategy : public GrowingStrategy D_THREADINFO_M
	{
	D_THREADSAFE

	public:
		/** @name Public Constructors */
		//@{
		/** Creates a FixedGrowingStrategy with the given growth factor
		 *  @param size Number by which the pool should grow.
	 	 */
		 FixedGrowingStrategy(size_t factor);

		/** Copy constructor
		 *  @param BAS::FixedGrowingStrategy& GrowingStrategy to be copied.
	 	 */
		 FixedGrowingStrategy(const BAS::FixedGrowingStrategy& iGrowingStrategy);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~FixedGrowingStrategy();
		//@}

		/** @name Public Member Functions */
		//@{
		/** Calculate the amount to grow the pool by.
		 *  @param size Current size of the pool.
	 	 *  @return amount to grow
	 	 */
		virtual size_t growBy(const size_t);

		/** Clone a FixedGrowingStrategy
	 	 *  @return a pointer to a cloned FixedGrowingStrategy
	 	 */
		virtual BAS::FixedGrowingStrategy* clone() const;

		/** Output operator.
		 *  @param std::ostream& Output stream.
	 	 *  @return std::ostream& Output stream.
		*/
		virtual std::ostream& operator<<(std::ostream& os) const;

		//@}
	
	protected:
		/** @name Protected Member Functions */
		//@{
		/** Get the grow factor 
	 	 *  @return the grow factor
	 	 */
		virtual size_t getGrowFactor() const;
		//@}

	private:

		size_t growFactorM;
		//
		// Disallow use.
		//
		FixedGrowingStrategy();
		const FixedGrowingStrategy& operator=(const FixedGrowingStrategy& p);
	};

}

inline size_t
BAS::FixedGrowingStrategy::growBy(const size_t currentSize) {
	return growFactorM;
}

inline size_t
BAS::FixedGrowingStrategy::getGrowFactor() const {
	return growFactorM;
}

inline BAS::FixedGrowingStrategy*
BAS::FixedGrowingStrategy::clone() const{
	
	return (new FixedGrowingStrategy(*this));
}

#endif
