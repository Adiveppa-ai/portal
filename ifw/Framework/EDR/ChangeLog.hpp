#ifndef EDR_CHANGELOG_HPP
#define EDR_CHANGELOG_HPP
/* @(#)%Portal Version: ChangeLog.hpp:NewPipelineVelocityInt:6:2006-Aug-08 00:10:00 % */

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class ChangeLog.
//------------------------------------------------------------------------------
// Revision    

//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace EDR
{
/** <tt><b>ChangeLog</b></tt> will hold the information of edr fields of the
 *   edr container that is being worked upon by a plugin.
 */
class ChangeLog D_THREADINFO
{
 D_SINGLETHREADED

 public:

    /** Add a LogEntry of the edr container
     *  @param pluginName The  plugin name in which edr content modified
     *  @param edrFieldName The fieldname of the edr
     *  @param edrFieldOldValue FieldName's old value 
     *  @param edrFieldNewValue FieldName's new value 
     *  @param edrFieldAccessType AccessType of edr field 
     */
    virtual void addLogEntry(const BAS::String& pluginName, 
		      const BAS::String& edrFieldName, 
		      const BAS::String& edrFieldOldValue, 
		      const BAS::String& edrFieldNewValue, 
		      const BAS::String& edrFieldAccessType)=0;


   /** Get the number of entries
    *  @return Number of entries
    */
   virtual int getChangeLogEntries() const = 0;

   /** Get the Formatted entries
    *  @param pluginList The list of filtered plugins
    *  @return The Formatted string
    */ 
   virtual const BAS::String& getFormattedLogEntries(RWTValOrderedVector<BAS::String> pluginList ) = 0;

   /** Clear log entries
    */
   virtual void clearData() = 0;
 
   /** Copy the log entries from another ChangeLog
    */ 
   virtual void copyData(EDR::ChangeLog*) = 0;

   /** Constructor
    */
   ChangeLog(){}
   
   /** Destructor
    */
   virtual ~ChangeLog() {}
	
  };
}

#endif


