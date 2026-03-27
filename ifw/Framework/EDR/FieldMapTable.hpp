#ifndef EDR_FIELDMAPTABLE_HPP
#define EDR_FIELDMAPTABLE_HPP

//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class FieldMapTable. This class is used to map
//   logical alias names to real EDR field names.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: FieldMapTable.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2010/11/15 09:23:11 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FieldMapTable.hpp,v $
// Revision 1.8  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.7  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.6  2001/06/19 14:11:58  sd
// - Working EDR usage statistic
//
// Revision 1.5  2001/06/19 12:26:28  sd
// - Output for edr usage statistic added.
//
// Revision 1.4  2001/05/11 08:31:42  sd
// - Bug in Factory::getIndex() fixed
//
// Revision 1.3  2001/05/02 10:49:18  sd
// - Input stream plugin no longer needed in v4-30
//
// Revision 1.2  2001/05/02 10:17:44  sd
// - Statistic introduced
//
// Revision 1.1  2001/05/02 08:13:07  sd
// - Initial revision
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_FIELDMAPKEY_HPP
  #include "EDR/FieldMapKey.hpp"
#endif
#ifndef   __RWDB_DB_H__
  #include <rw/db/db.h>
#endif
#ifndef   RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef   RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef   RW_TOOLS_TVSRTVEC_H
  #include <rw/tvsrtvec.h>
#endif
#include <rw/thr/mutex.h>

namespace EDR
{
/** <b><tt>FieldMapTable</tt></b> is used to map logical alias names to
 *  real EDR index names. The table is initialized from the database table
 *  IFW_ALIAS_MAP.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FieldMapTable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2010/11/15 09:23:11 $</font></td>
 *  <td><font size=-1>$Author: cprabhak $</font></td>
 *  </tr>
 *  </table>
 */
class FieldMapTable D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name FieldMapTable constructors and destructor */
    //@{

    /** Constructor
     */
    FieldMapTable();

    /** Destructor
     */
    ~FieldMapTable();

    //@}

    /**@name FieldMapTable public methods */
    //@{

    /** Get the description for the last failure
     *  @return Reference to the failure string
     */
    const BAS::String& failure() const;

    /** Initialize the mapping table (read from database)
     *  @param connection The database connection to use
     *  @param pipeline The name of the pipeline the mapping table is used in
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( RWDBConnection    connection, 
               const BAS::String& pipeline,
               bool collectStat = true);

    /** Map a index 
     *  @param libName The name of the library that accesses the edr field
     *  @param defaultName The default index to use
     *  @param key The key for the index to access
     *  @param reference The reference for the mapping operation
     *  @param output Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool map( const BAS::String& libName,
              const BAS::String& defaultName,
              const BAS::String& key,
              const BAS::String& reference,
              BAS::String&       output );

    /** Print the edr usage statistic to an output stream
     *  @param os The output stream
     */
    void printUsageStatistic( std::ostream& os );
    
    //@}

  protected:
    /* Set the failure string
     * @param str The new failure string
     */
    void failure( const BAS::String& str );

    /* Update the statistic of used edr fields for each library
     * @param libName Name of the library that accesses the edr field
     * @param defaultName The default name to use
     * @param key The key for the edr field to access
     * @param reference The reference for the alias mapping
     */
    void updateStatistic( const BAS::String& libName, 
                          const BAS::String& defaultName,
                          const BAS::String& key, 
                          const BAS::String& reference );

    /* Get a padstring of specified length 
     */
    BAS::String padString( size_t len, const BAS::String& str );


    typedef RWTValSortedVector<FieldMapKey, less<FieldMapKey> >
      FieldStatisticEntry;
    typedef RWTPtrMap<BAS::String,FieldStatisticEntry,less<BAS::String> > 
      FieldStatistic;
    typedef RWTPtrMapIterator<BAS::String,FieldStatisticEntry,
                              less<BAS::String> > 
      FieldStatisticIterator;

  private:
    // Instance members
    BAS::String                                                   failureM;
    BAS::String                                                   pipelineM;
    RWTValMap<FieldMapKey,BAS::String,less<FieldMapKey> > mapTableM;
    FieldStatistic                                           statisticM;
    bool  bCollectStatisticsM;
    RWMutexLock      mutexM;

    // find the best matched pipeline name defined in ifw_pipeline table
    bool findBestMatchedPipeline(RWDBConnection  connection, BAS::String& pipeline);
};

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
FieldMapTable::failure() const
{
  return failureM;
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
FieldMapTable::failure( const BAS::String& str )
{
  failureM = str;
}
}
#endif // FIELDMAPTABLE_HPP
