#ifndef BAS_TIMERIF_HPP
#define BAS_TIMERIF_HPP

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
//	Timer interface
//
//=============================================================================

#ifndef _pin_os_h_
  #include <pin_os.h> 
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

namespace BAS
{
   /** Timer with nanosecond granularity. 
    */
   class TimerIf D_THREADINFO
   {
      D_NONTHREADSAFE

      public:
	 /** @name Public Member Functions */
	 //@{

	 /** Start time measurement.
	  */
	 virtual void start()=0;

	 /** Stop time measurement.
	  */
	 virtual void stop()=0;
	 
	 /** Provide elapsed time
	     @return elapsed time
	  */
	 hrtime_t elapsedTime();

	 //@}
      protected:
	 hrtime_t tpStartM;
	 hrtime_t tpEndM;
   };
}

inline hrtime_t
BAS::TimerIf::elapsedTime()
{
   D_ENTER("BAS::NanoSecondTimer::elapsedTime()");
   return (tpEndM - tpStartM);
}

#endif // BAS_TIMERIF_HPP
