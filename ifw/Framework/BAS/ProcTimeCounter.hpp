// @(#)%Portal Version: ProcTimeCounter.hpp:PlatformR2Int:4:2006-Jul-16 15:22:48 %
#ifndef BAS_PROC_TIME_COUNTER_HPP
#define BAS_PROC_TIME_COUNTER_HPP

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

// Module Description:
//      Instances of this class are used to intrument a section of code. It accumulates
//      the time it took to execute the code. It also keeps track of the number of times this
//      code has been called.
//
//      Instances of this class are to be used by value.

// Current Issues:
// There was no way of insturmenting a piece of code several times and keeping track of it.
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
// 19-04-2004  Saeed Mokhtarani    New header template created.
//
//=============================================================================
#ifndef _RWSTD_SSTREAM_INCLUDED
  #include <sstream>      // string IO
#endif
#ifndef _RWSTD_IOSTREAM_INCLUDED
  #include <iostream>
#endif

#ifndef RW_TOOLS_CSTRING_COMPAT_H
  #include <rw/cstring.h>
#endif
#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif

#ifndef BAS_NANO_SECOND_TIMER_HPP
  #include "BAS/NanoSecondTimer.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

//------------------------------------------------------------------------------
namespace BAS
{
   /** Collection of processing time statistics.
    */
   class ProcTimeCounter D_THREADINFO
   {
      D_NONTHREADSAFE

      public:
         /**@name Constructors and Destructors */
         //@{

         /** Default constructor.<br>
          */
         ProcTimeCounter();

         /** Destructor.
	  */
         virtual ~ProcTimeCounter();
         //@}

	 /** @name Public Member Functions */
	 //@{

     /**
      * accumulates the total elapsed time.
      * @parameter trackEachCallTime track each call time or not
      */
       void accumulateElapsedTime(bool trackEachCallTime);

     /**
      * returns the total elapsed time.
      * @return the elapsed time in nano second
      */
       hrtime_t getTotalElapsedTime() const;

     /**
      * returns the number times a function is called
      * @return  total number of calls
      */
       u_int64 getTotalCallFreq() const;

     /**
      * increases the call freq counter
      */
       void increaseCallFreq();

     /**
      * returns the timer
      * @return  the time
      */
       NanoSecondTimer& getTimer();

     /**
      * returns the elapsed time for each call
      * @return  the elapsed time container
      */
       RWTValOrderedVector<hrtime_t>& getCallContainer();

     /**
      * sets the label
      * @param label this is used to identify/label an instance of this class.
      * Its main use is when printing the attributes of the instance.
      */
     void setLabel(const String& label);

     /**
      * prints all the call time entries
      * @param val the stream
      * @param label the function call time
      */
     void printCallContainer(std::ostream& val, const BAS::String& label) const;

     /**
      * prints the data fields:msM, totalElapsedTimeM, callFreqM and labelM to the stream.
      * @param val the stream
      */
     void printData(std::ostream& val) const;

     /**
      * prints the data fields:msM, totalElapsedTimeM, callFreqM and labelM to the stream.
      * and resets all the counter values
      * @param val the stream
      */
     void printAndResetData(std::ostream& val); 
     /**
      * gets the default label.
      * @return the default label
      */
     static String getDefaultLabel();

   private:
     /** nsM measures time */
     NanoSecondTimer nsM;
     /** totalElapsedTimeM keeps track of the accumulated time */
     hrtime_t totalElapsedTimeM;
     /** callFreqM keeps track of number of times a section code has been instrumented */
     u_int64 callFreqM;
     /** a convenient way of identifying attributes of the current instance */
     String labelM;
     /** the default value for labelM */
     static String defaultLabelCM;
     /** lock to reset elapsed time etc in printAndResetData() */
     RWMutexLock printAndResetLockerM;

     /** container to keeps track of the spent time for each call */
     RWTValOrderedVector<hrtime_t>  callContainerM;

   };


inline void 
ProcTimeCounter::accumulateElapsedTime(bool trackEachCallTime) {
    RWLockGuard<RWMutexLock> lock(printAndResetLockerM);
    hrtime_t newElapsedTime = nsM.elapsedTime();
    totalElapsedTimeM += newElapsedTime;
    if (trackEachCallTime)
    {
        callContainerM.insert(newElapsedTime);
    }
}

inline hrtime_t ProcTimeCounter::getTotalElapsedTime() const  {return totalElapsedTimeM;}

inline u_int64 ProcTimeCounter::getTotalCallFreq() const { return callFreqM;}

inline void 
ProcTimeCounter::increaseCallFreq() 
{
    RWLockGuard<RWMutexLock> lock(printAndResetLockerM);
    ++callFreqM;
}

inline NanoSecondTimer& ProcTimeCounter::getTimer() {return nsM;}

inline void ProcTimeCounter::setLabel(const String& label) { labelM = label;}

inline RWTValOrderedVector<hrtime_t>&  ProcTimeCounter::getCallContainer() {return callContainerM;}

}
#endif // PROC_TIME_COUNTER_HPP








