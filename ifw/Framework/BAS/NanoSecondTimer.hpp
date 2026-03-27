#ifndef BAS_NANO_SECOND_TIMER_HPP
#define BAS_NANO_SECOND_TIMER_HPP

//=============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
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
//	Timer with nanosecond granularity. 
//
//=============================================================================

#ifndef BAS_TIMERIF_HPP
  #include "BAS/TimerIf.hpp"
#endif

namespace BAS
{
   /** Timer with nanosecond granularity. 
    */
   class NanoSecondTimer : public TimerIf
   D_THREADINFO
   {
      D_NONTHREADSAFE

      public:
	 /** @name Public Member Functions */
	 //@{

	 /** Start time measurement in nanosecond.
	  */
	 void start();

	 /** Stop time measurement in nanosecond.
	  */
	 void stop();
	 
	 //@}
   };
}

inline void
BAS::NanoSecondTimer::stop()
{
   D_ENTER("BAS::NanoSecondTimer::stop()");
   tpEndM = gethrtime();
}

inline void
BAS::NanoSecondTimer::start()
{
   D_ENTER("BAS::NanoSecondTimer::start()");
   tpStartM = gethrtime();
}


#endif // BAS_NANO_SECOND_TIMER_HPP
