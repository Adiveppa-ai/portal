#ifndef BAS_RATIOGROWINGSTRATEGY_HPP
#define BAS_RATIOGROWINGSTRATEGY_HPP

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
//	Ratio based grow logic for pools. 
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
	/** \class RatioGrowingStrategy RatioGrowingStrategy.hpp "BAS/RatioGrowingStrategy.hpp"
 	*  Grow logic for pools based on a ratio.
 	*/
	class RatioGrowingStrategy : public GrowingStrategy D_THREADINFO_M
	{
	D_THREADSAFE

	public:
		/** @name Public Constructors */
		//@{
		/** Creates a RatioGrowingStrategy with the given growth factor
		 *  @param size Number by which the pool should grow.
	 	 */
		 RatioGrowingStrategy(size_t factor);

		/** Copy constructor
		 *  @param BAS::RatioGrowingStrategy& GrowingStrategy to be copied.
	 	 */
		 RatioGrowingStrategy(const BAS::RatioGrowingStrategy& iGrowingStrategy);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~RatioGrowingStrategy();
		//@}

		/** @name Public Member Functions */
		//@{
		/** Calculate the amount to grow the pool by.
		 *  @param size Current size of the pool.
	 	 *  @return size amount to grow
	 	 */
		virtual size_t growBy(const size_t);

		/** Clone a RatioGrowingStrategy
	 	 *  @return a pointer to a cloned RatioGrowingStrategy
	 	 */
		virtual BAS::RatioGrowingStrategy* clone() const;

		/** Output operator.
		 *  @param std::ostream& Output stream.
	 	 *  @return std::ostream& Output stream.
		*/
		std::ostream& operator<<(std::ostream& os) const;

		//@}

	protected:
		/** @name Protected Member Functions */
		//@{
		/** Get the grow factor 
	 	 *  @return size the grow factor
	 	 */
		virtual size_t getGrowFactor() const;
		//@}

	private:

		size_t growFactorM;
		//
		// Disallow use.
		//
		RatioGrowingStrategy();
		const RatioGrowingStrategy& operator=(const RatioGrowingStrategy& p);
	};

}

inline size_t
BAS::RatioGrowingStrategy::getGrowFactor() const {
	return growFactorM;
}

inline BAS::RatioGrowingStrategy*
BAS::RatioGrowingStrategy::clone() const{
	
	return (new RatioGrowingStrategy(*this));
}

#endif
