#ifndef PLG_STATINFO_HPP
#define PLG_STATINFO_HPP
//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//  <description>
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: StatInfo.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:51 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StatInfo.hpp,v $
// ECR for Multithreaded Output
//     bug 9305229 - out_genericstream is consuming 100% cpu because it is duplicating every edr
//
// Revision 1.1  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.19  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.18  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.17  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.1  2001/01/09 09:52:41  sd
// - Backup version.
//
// Revision 1.15  2000/10/25 16:28:24  bt
// Temporary textCountHash maps implemented as members (faster).
//
// Revision 1.14  2000/09/29 10:09:28  aro
// Tried to fix doc++ comments.
//
// Revision 1.13  2000/09/08 12:02:58  bt
// New attribute for EDR recycling added.
//
// Revision 1.12  2000/09/07 13:46:55  jkeckst
// add new copyright info
//
// Revision 1.11  2000/01/31 10:31:21  jkeckst
// count only one message type per EDRC
//
// Revision 1.10  1999/09/09 16:02:20  bt
// RWCString replaced by BAS::String.
//
// Revision 1.5  1999/05/20 07:56:11  jkeckst
// add new functionality : duration
//
// Revision 1.1  1999/04/22 11:21:43  jkeckst
// add all necessary methods for statistic informations
//
//==============================================================================

#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>
#endif
#ifndef   RW_TOOLS_TIME_H
  #include <rw/rwtime.h>
#endif

#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
namespace PLG 
{
/** <tt><b>StatInfo</b></tt>.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: StatInfo.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/05/23 01:27:51 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    </tr>
    </table>           
    
    This is a helper class for the EDR::Statistic object. It collect
    all information about one Stream.
*/
class StatInfo D_THREADINFO
{
  // CodeReview - 08.2001 - mwriedt - C - missing in doc (UML)
  // Checked by CodeReview - 08.2001 - sd - C - is is not necessary to add
  //                                            all helper classes to UML doc

  public:
    /**@name constructors and destructor */
    //@{ 
    /// default constructor
    StatInfo();

    /// destructor
    ~StatInfo();
    //@}
  
    /**@name special functions */
    //@{ 
    /// Add all necessary statistic infos to the class.
    void addEDRInfos (const EDR::Container & edr);
    /// Clears all infos in the class (all counters set to 0)  
    void clear();
    /// Returns the counter for all messages.
    const u_int64 msgCount() const;
    /// Returns the counter for one message.
    const u_int64 msgCount(const BAS::String & message) const;
    /** Returns the percentage for the message.
        The percentage calculate by : msgCount * 100 / edrCount
    */
    const float msgRelCount(const BAS::String & message) const;
    /// Returns the counter for all record edr's.
    const u_int64 edrCount() const;
    /// Returns the counter for all recycled edr's.
    const u_int64 edrRecCount() const;
    /// Returns the counter for all record edr's with messages.
    const u_int64 edrErrCount() const;
    /// Stop the actual timer. 
    void stopTimer();
    /** Returned the duration in seconds from the timer. 
        This operation doesn't stop the timer. 
    */    
    const u_int64 duration();

    /** Return the endTime in seconds.
    */
    const u_int64 getStopTime();

    //@}
    
    /** Show the hash contents
     */
    void showHash();

    BAS::String getKey (const bool first = false) const;

  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    StatInfo(StatInfo& right);
    const StatInfo& operator=(StatInfo& right);

    typedef RWTValHashMap <BAS::String, 
                       u_int64, 
                       BAS::StringHash, 
                       equal_to<BAS::String> > TextCountHash;
  
  
    // sum over all incomming messages
    u_int64   msgCountM;
    // sum over all incomming edr
    u_int64   edrCountM;
    // sum over all recycled edr 
    u_int64   edrRecCountM;
    // sum over all incomming edr with messages
    u_int64   edrErrCountM;
	// state of TextCountHash in iterator
	TextCountHash::const_iterator hashCntItrM;
    TextCountHash   txtCntM;
    TextCountHash   tmpTxtCntHashM;
    RWTime          *start, *stop;
};


inline const u_int64
StatInfo::edrCount() const
{
  return edrCountM;
}

inline const u_int64
StatInfo::edrRecCount() const
{
  return edrRecCountM;
}

inline const u_int64
StatInfo::edrErrCount() const
{
  return edrErrCountM;
}

inline const u_int64
StatInfo::msgCount() const
{
  return msgCountM;
}

inline const u_int64
StatInfo::getStopTime()
{
   return stop->seconds();
}

}
#endif

