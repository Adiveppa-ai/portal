#ifndef EDR_CONTAINERCACHE_HPP
#define EDR_CONTAINERCACHE_HPP

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
//   Declaration of the class ContainerCache.
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
// $RCSfile: ContainerCache.hpp,v $
// $Revision: 1.3 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ContainerCache.hpp,v $
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
class Container;

/** <b><tt>ContainerCache</tt></b> is used to cache Containers inside
 *  the Factory
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ContainerCache.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>                
 */
class ContainerCache D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name ContainerCache constructors and destructor */
    //@{

    /** Constructor 
     */
    ContainerCache();

    /** Destructor 
     */
    ~ContainerCache();

    //@}

    /**@name ContainerCache public methods */
    //@{

    /** Retrieve a container from the cache and remove it from the internal 
     *  list
     *  @return Pointer to the container on success
     */
    Container* removeContainer();
    
    /** Insert a new container to the cache
     *  @param container The container to add to the cache
     */
    void insertContainer( Container* container );

#ifdef TRACE
    void printCacheStatistic( std::ostream& os ) const;
#endif

    //@}

  private:
    // Disallow use of copy constructor/operator
    ContainerCache( const ContainerCache& other );
    const ContainerCache& operator=( const ContainerCache& other );

    // instance members
    Container* inCacheM;
    Container* outCacheM;
    RWMutexLock    inMutexM;
    RWMutexLock    outMutexM;

#ifdef TRACE
    int            edrsInCacheM;
    int            cacheHitM;
    int            cacheMissM;
    int            inOutSwitchesM;
#endif
};
}
#endif // CONTAINERCACHE_HPP
