#ifndef BAS_REFCOUNTER_HPP
#define BAS_REFCOUNTER_HPP
//==============================================================================
//
// Copyright (c) 2001, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//  Referent counter for handle class.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work, finished, accepted>
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: RefCounter.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:47:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: RefCounter.hpp,v $
// Revision 1.2  2001/10/02 09:54:19  jkeckst
// add some changes for DAT_UniData
//
// Revision 1.1  2001/05/14 08:40:28  jkeckst
// add some handle classes
//
// Revision 1.1  2001/03/30 13:20:56  jkeckst
// first save version (with core dump :) )
//
//
//==============================================================================

/**  <tt><b>Handle</b></tt> A Handle class for counting accesses to a handle.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: RefCounter.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:47:48 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>                
    
*/

#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
namespace BAS 
{
class RefCounter D_THREADINFO
{
public:

  /** Constructor. */
  RefCounter(const int c = 1);

  /** Destructor. */
  virtual ~RefCounter();

  /** Return the actual counter. */
  int counter() const;

  /** Set the counter to a new number. */
  void setCounter(const int c);

  /** Increment the counter by one. */
  int incCounter();

  /** Decrement the counter by one. */
  int decCounter();

  /** Lock the opject. Owner can now inc and dec the object.*/
  void lock();

  /** After working with this object you must release this. */
  void release();

  /** Lock counter, increment by one, unlock counter */
  void safeIncCounter();

  /** Lock counter, decrement by one, unlock counter */
  void safeDecCounter();

private:

  RWMutexLock mutexM;
  int counterM;
};


//------------------------------------------------------------------------------
// inlines
//------------------------------------------------------------------------------
inline void
RefCounter::lock()
{
  mutexM.acquire();
}

inline void
RefCounter::release()
{
  mutexM.release();
}

inline int
RefCounter::counter() const
{
  return counterM;
}

inline void
RefCounter::setCounter(const int c)
{
  counterM = c;
}

inline int
RefCounter::incCounter()
{
  return ++counterM;
}

inline int
RefCounter::decCounter()
{
  return --counterM;
}
}
#endif
