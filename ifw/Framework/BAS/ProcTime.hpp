// @(#)%Portal Version: ProcTime.hpp:PlatformR2Int:7:2006-Jul-16 15:29:43 %
#ifndef BAS_PROC_TIME_HPP
#define BAS_PROC_TIME_HPP

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
//	Collection of processing time statistics.
//
// Current Issues:
//    Need to instrument code
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Saeed Mokhtarani 
// Backup-Responsible: Jens Kaemmer 
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 23-Jun-2005  pborah		    PRSF00173781 - Pipeline instrumentation for Windows
// 19-03-2004   Jens Kaemmer        New header template created.
//
//=============================================================================

#ifndef _RWSTD_SSTREAM_INCLUDED
  #include <sstream>      // string IO
#endif
#ifndef _RWSTD_IOSTREAM_INCLUDED
  #include <iostream>
#endif
#ifndef _RWSTD_FSTREAM_INCLUDED
  #include <fstream>
#endif

#ifndef RW_TOOLS_CSTRING_COMPAT_H
  #include <rw/cstring.h>
#endif
#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif

#ifndef BAS_PROC_TIME_COUNTER_HPP
  #include "BAS/ProcTimeCounter.hpp"
#endif

//------------------------------------------------------------------------------
namespace BAS
{
   /** Collection of processing time statistics.
    */
   class ProcTime D_THREADINFO
   {
      D_NONTHREADSAFE

      public:
         typedef RWTPtrMapIterator<RWCString, ProcTimeCounter, std::less<RWCString> > CounterIterator;
         typedef RWTPtrMap<RWCString, ProcTimeCounter,  std::less<RWCString> > CounterPool;

         /**@name Constructors and Destructors */
         //@{

         /** Default constructor.<br>
          */
         ProcTime();

         /** Destructor.
	  */
         virtual ~ProcTime();
         //@}

	 /** @name Public Member Functions */
	 //@{

	 /** Write statistics to pipeline log file.
	     @param stat string holding processing time statistis name value pairs (comma separated)
	  */
	 void printData(BAS::String& stat);

	 /** Write a counter statistics to pipeline log file.
           * @param counterName name of the counter
	     @param stat string holding processing time statistis name value pair
	  */
	 void printCounterData(const BAS::String& counterName, BAS::String& stat);

	 /** Write statistics to pipeline log file.
	     @param os output stream
	  */
	 void logData(const char *);

	
	 /** Reset all accumulated time values of all counters.
	  */
	 void reset();

	 /** Install statistics signalhandler and enable/disable processing
	     time statistics collection. SIGUSR1 signal in Unix and CTRL+BREAK in Windows allows to enable or disable
             collection of processing time statistics.
	  */
	 static void selectProcTime(void);

	 /** Logs all statistics collected upto the point SIGUSR1 was received
	  */
	 static void logProcTime(void);

	 /** Start microsecond timer. Enabled with SIGUSR1 in Unix and CTRL+BREAK in Windows
           * @param counterName    used as a key in RWTPtrMap
	  */
	 void startTime(const BAS::String& counterName); 

         /** Stop microsecond timer and accumulate elapsed time. Enabled with SIGUSR1 in Unix and CTRL+BREAK in Windows.
           * @param counterName name of the counter
           * @param label   the label
          */
         void stopTime(const BAS::String& counterName, const BAS::String& label = BAS::ProcTimeCounter::getDefaultLabel());


	 /** Determine current state of statistics collection (enabled or disabled).
	  */
	 bool getProcTimeEnabled(void) const;

         /** a boolean variable to enable or disable instrumentation */

	 BAS_EXPORT static bool procTimeEnabledCM;

         /** A boolean variable to enable or disable tracking each
	  *  call time or not. Default is false, means instrumentation
	  *  only keep the accumulated call time.
	  */
         BAS_EXPORT static bool trackEachCallTimeCM;

	 //@}
      private:
         /** used to set procTimeEnabledCM to false for the first time */
	
         static bool firstTimeCM;
         
         /** a container to keep track of number of instances of ProcTimeCounter.
             The instances can be keyed via a RWstring name*/
  
         CounterPool countersM; 


   };
}
#endif // BAS_PROC_TIME_HPP

