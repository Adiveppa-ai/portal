#ifndef EDR_DATABLOCKCACHE_HPP
#define EDR_DATABLOCKCACHE_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class DatablockCache.
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
// $RCSfile: DatablockCache.hpp,v $
// $Revision: 1.3 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DatablockCache.hpp,v $
// Revision 1.3  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.2  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.2  2000/10/20 10:02:01  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPSLIST_H
  #include <rw/tpslist.h>
#endif
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
namespace EDR
{
class Datablock;

/** <b><tt>DatablockCache</tt></b> is used to cache Datablocks inside
 *  the Factory
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DatablockCache.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>                
 */
class DatablockCache D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name DatablockCache constructors and destructor */
    //@{

    /** Constructor 
     *  @param prototypeBlock The prototype block for this cache list
     */
    DatablockCache( Datablock* prototypeBlock );

    /** Destructor 
     */
    ~DatablockCache();

    //@}

    /**@name DatablockCache public methods */
    //@{

    /** Retrieve a datablock from the cache and remove it from the internal 
     *  list
     *  @return Pointer to the datablock on success
     */
    Datablock* removeDatablock();
    
    /** Insert a new datablock to the cache
     *  @param datablock The datablock to add to the cache
     */
    void insertDatablock( Datablock* datablock );

    /** Clone the prototype datablock
     *  @return Pointer to the cloned prototype block
     */
    Datablock* clonePrototype();

    //@}

  private:
    // Disallow use of copy constructor/operator
    DatablockCache( const DatablockCache& other );
    const DatablockCache& operator=( const DatablockCache& other );

    // instance members
    Datablock* inCacheM;
    Datablock* outCacheM;
    RWMutexLock    inMutexM;
    RWMutexLock    outMutexM;
    Datablock* prototypeBlockM;
};
}
#endif // DATABLOCKCACHE_HPP
