#ifndef BAS_MICRO_SECOND_TIMER_HPP
#define BAS_MICRO_SECOND_TIMER_HPP

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
//	Timer with microsecond granularity. 
//
//=============================================================================

#ifndef BAS_TIMERIF_HPP
  #include "BAS/TimerIf.hpp"
#endif

//------------------------------------------------------------------------------

namespace BAS
{
   /** Timer with microsecond granularity. 
    */
   class MicroSecondTimer : public TimerIf 
   D_THREADINFO 
   {
      D_NONTHREADSAFE

      public:
	 /** @name Public Member Functions */
	 //@{

	 /** Start time measurement in microsecond.
	  */
	 void start();

	 /** Stop time measurement in microsecond.
	  */
	 void stop();
	 
	 //@}
   };
}

inline void
BAS::MicroSecondTimer::stop()
{
   D_ENTER("BAS::MicroSecondTimer::stop()");
   struct timeval tv;
   gettimeofday(&tv, 0);
   tpEndM = tv.tv_sec*1000000 + tv.tv_usec;
}

inline void
BAS::MicroSecondTimer::start()
{
   D_ENTER("BAS::MicroSecondTimer::start()");
   struct timeval tv;
   gettimeofday(&tv, 0);
   tpStartM = tv.tv_sec*1000000 + tv.tv_usec;
}


#endif // BAS_MICRO_SECOND_TIMER_HPP
