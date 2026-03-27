#ifndef PLG_STATISTIC_HPP
#define PLG_STATISTIC_HPP
// @(#)%Portal Version: Statistic.hpp:NewPipelineVelocityInt:5:2006-Sep-18 22:47:34 %
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
// $RCSfile: Statistic.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:51 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Statistic.hpp,v $
// ECR for Multithreaded Output
//     bug 9305229 - out_genericstream is consuming 100% cpu because it is duplicating every edr
//
// bug 7648395   Change of the registry parameter name from "EDRCountCrieteria" 
//               to "EDRCountCriteria"
//
// bug 7237250   Enhancement to count only Input number of EDRs
//
// Revision 1.1  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.24  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.23  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.22  2001/05/03 16:09:35  bt
// Format renamed to Pipeline.
//
// Revision 1.21  2001/03/29 14:22:15  mliebmann
// Generic IO added
//
// Revision 1.20  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.1  2001/01/09 09:52:41  sd
// - Backup version.
//
// Revision 1.18  2000/10/25 16:28:24  bt
// Temporary textCountHash maps implemented as members (faster).
//
// Revision 1.17  2000/09/29 10:09:28  aro
// Tried to fix doc++ comments.
//
// Revision 1.16  2000/09/08 12:05:46  bt
// New statistic INF_STATISTIC_RECYCLED for EDR recycling added.
//
// Revision 1.15  2000/09/07 13:46:55  jkeckst
// add new copyright info
//
// Revision 1.14  2000/01/31 10:32:04  jkeckst
// set relCount to 0.01 when it is < 0.01
//
// Revision 1.13  2000/01/18 07:58:04  jkeckst
// this is the new EDR-Container v4.0 (first version)
//
//==============================================================================
#if !defined PLG_EXPORT
  #if defined(WINDOWS)
    #if !defined(PLG_INTERNAL)
      #define PLG_EXPORT __declspec(dllimport)
    #else
      #define PLG_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PLG_EXPORT
  #endif
#endif

#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>   
#endif
#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   PLG_STATINFO_HPP
  #include "PLG/StatInfo.hpp"
#endif
#ifndef   BAS_INSTRUMENTATION_PROBE_GROUP_H
  #include "BAS/InstrumentationProbeGroup.hpp"
#endif
#ifndef   BAS_INSTRUMENTATION_PROBE_TABLE_H
  #include "BAS/InstrumentationProbeTable.hpp"
#endif

namespace PLG
{

class CircularBuffer;

/** <tt><b>Statistic</b></tt>: the statistic object.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Statistic.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/05/23 01:27:51 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    </tr>
    </table>                
    
    The class collect all informations about one pipeline
    over all streams. It holds many informations (count, ..)
    for all incomming containers.

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>none</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>none</dd>
</dl> 
*/
class Statistic : public BAS::RegisteredObject
{
  // CodeReview - 08.2001 - mwriedt - C - missing in doc (UML)
  // Checked by CodeReview - 08.2001 - sd - C - is is not necessary to add
  //                                            all helper classes to UML doc
  private:

    enum streamTableUsageTypeT
    {
      FOR_ROLLBACK = 1,
      FOR_LOGGING
    };

    enum statisticTypeT 
    {
      INPUT ,
      ALL
    };
   

  public:
    typedef RWTValHashMap<BAS::String, int64, BAS::StringHash, 
                          equal_to<BAS::String> >       MaxErrorMap;
    typedef MaxErrorMap::iterator                      Iterator;
    typedef MaxErrorMap::const_iterator                ConstIterator;   

    /**@name constructors and destructor */
    //@{ 
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    Statistic();
    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    Statistic(const BAS::String & name);
    /// destructor
    virtual ~Statistic();
    //@}
    
    /**@name special functions */
    //@{

    // ========================================================================    
    /// Add all necessary statistic infos to the class.
    void addStatistic (const EDR::Container & edr);
    /// Returns the counter for all messages (all streams).
    const u_int64 msgCount() const;
    /// Returns the counter for one message (all streams)
    const u_int64 msgCount(const BAS::String & message, const enum streamTableUsageTypeT usageType=FOR_LOGGING) const; 
    /// Returns the counter for all messages (one stream)
    const u_int64 msgCount(const size_t streamNo) const ;
    /// Returns the counter for one message (one stream)
    const u_int64 msgCount(const BAS::String & message, const size_t streamNo) const;

    // ========================================================================    
    /// Returns the counter for all edr's with errors (all streams)
    const u_int64 edrErrCount () const;
    /// Returns the counter for all edr's with errors (one stream)
    const u_int64 edrErrCount (const size_t streamNo) const;

    // ========================================================================    
    /** Returns the percantage for one message. (all streams)
        The percantage calculate by : msgCount * 100 / edrCount
    */
    const float msgRelCount(const BAS::String & message, const enum streamTableUsageTypeT usageType=FOR_LOGGING) const; 
    /** Returns the percantage for one message. (one streams)
        The percantage calculate by : msgCount * 100 / edrStreamCount */
    const float msgRelCount(const BAS::String & message, const size_t streamNo) const;

    // ========================================================================    
    /// Returns the counter for the edr's. (all streams)
    const u_int64 edrCount(const enum streamTableUsageTypeT usageType=FOR_LOGGING) const; 
    /// Returns the counter for the edr's. (one stream)
    const u_int64 edrCount(const size_t streamNo) const;

    // ========================================================================    
    /// Returns the counter for all detail edr's. (all streams)
    const u_int64 edrDetCount() const;
    /// Returns the counter for all detail edr's. (one stream)
    const u_int64 edrDetCount(const size_t streamNo) const;

    // ========================================================================    
    /// Returns the counter for recycled edr's. (all streams)
    const u_int64 edrRecCount() const;
    /// Returns the counter for recycled edr's. (one stream)
    const u_int64 edrRecCount(const size_t streamNo) const;

    // ========================================================================    
    /** Returns the duration time between the first EDR::Container and the 
        stop command (one stream). If no stop command sended, it returns 
        the duration time between the first EDR::Container and the actual time.
        @return The work duration time for all EDR containers
    */
    const u_int64 duration (const size_t streamNo) const;
    /** Returns the maximum duration time over all streams.
    */    
    const u_int64 duration () const;
    
    /** Send the stop commando for the timer (one stream).   
    */
    void stopTimer (const size_t streamNo) const;

    /** Send the stop commando for the timer (all streams).   
    */
    void stopTimer () const;

    // ========================================================================    
    /// Send all statistics to the log file. (summary over all streams)
    void writeStatistic ();
    /// Send all statistics to the log file. (summary over one streams)
    void writeStatistic (const size_t streamNo);

    // ========================================================================    
    /// clears ALL items 
    void clear();
    /// clear all stream items
    void clearStream(const size_t streamNo);
    //@}

    /// for check programm only (private use)    
    void showHash();

// CodeReview - 08.2001 - mwriedt - C - public, so please comment
    bool streamShallBeRenamed() const;
    bool addErrorRate(const BAS::RegistryEntry* entry);
    void clearErrorMap();

    void writeToPipelineLog(const BAS::Status& msg) const;

    /** Get the probes
     */
    void getInstrumentationProbe(BAS::InstrumentationProbeList& probeList) const;

    /** Set the Transaction start time.
    */
    void setTxnStartTime( RWTime * txnStartTime);

  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    Statistic(Statistic& right);
    const Statistic& operator=(Statistic& right);
 
    /** Initialize the instance from the registry
     */
    virtual bool readRegistry();

    enum StatNum 
    {
      HEADER_STAT = -1,
      TRAILER_STAT = -2
    };
    
    PLG_EXPORT static const u_int64 MaxEdrsPerSecEntriesCM;
    PLG_EXPORT static const BAS::String edrCountCriteriaCM;

    /** Initialize the probes.
     * @return True on success; otherwise, False.
     */
    bool initInstrumentationProbe();
 
    void writeEDRStatistic (const size_t streamNo,
                            const bool oneStream) const;

    struct StatisticHash
    {
      u_int64 operator()(const size_t & x) const 
      { return x; }
    };

    typedef RWTValHashMap <int,
                       StatInfo*,
                       StatisticHash,
                       equal_to<int> > StreamHash;

    /** Update the stream statistics in the StreamHash object
     */
    void updateStreamStatistics(StreamHash & streamTable, const EDR::Container &edr);


    typedef RWTValHashMap <BAS::String, 
                       u_int64, 
                       BAS::StringHash, 
                       equal_to<BAS::String> > TextCountHash;

    StreamHash streamTableM;

    TextCountHash tmpTxtCntHashM;

    // The maximal error map. Contains the errorrs and the maximal
    // rate allowed for each of them.
    MaxErrorMap        maxErrorMapM;

    BAS::RegisteredObject* pipelineLogM;

    // Total # of EDRs since startup (real-time)
    u_int64 totalEdrCountM;

    // Total # of EDRs since startup (after end transaction)
    u_int64 totalTxnEdrCountM;

    // accumulated EDR processing time since startup
    u_int64 totalProcTimeM;

    // # of transactions since startup
    u_int64 totalTxnCountM;

    // Circular buffer to hold last throughtputs.
    PLG::CircularBuffer* edrsPerSecBufM;

    /** Group and table for storing instrumentation probes
     */
    BAS::InstrumentationProbeGroup* statisticInfoInstrM;
    BAS::InstrumentationProbeTable* edrsPerSecBufInfoInstrM;

    /** Variable that holds the registry value of EDRCountCriteria
     */
    statisticTypeT  edrCountTypeM ;

    /** A hash table to hold the EDR statistics for all the streams
     */
    StreamHash allStreamTableM;

    /** The transaction start time Used when Output controller
        is running multithreaded and batch mode.
    */
    RWTime  * txnStartTimeM;

};

//------------------------------------------------------------------------------
inline void
Statistic::clearErrorMap()
{
  maxErrorMapM.clear();
}

//--------------------------------------------------------------------------------
inline void
Statistic::setTxnStartTime( RWTime * txnStartTime)
{
  txnStartTimeM = txnStartTime; 
}

}
#endif
