#ifndef HANDLETEMPLATE_HPP 
#define HANDLETEMPLATE_HPP
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
//  Template class for all handles.
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
// $RCSfile: HandleTemplate.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:44:05 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: HandleTemplate.hpp,v $
// Revision 1.3  2001/08/17 12:16:10  jkeckst
// PETS 37459 need a clear methode
//
// Revision 1.2  2001/07/06 13:49:16  jkeckst
// add clearData function
//
// Revision 1.1  2001/05/14 08:40:28  jkeckst
// add some handle classes
//
// Revision 1.1  2001/03/30 13:20:56  jkeckst
// first save version (with core dump :) )
//
// Revision 1.5  2001/02/26 13:23:20  jkeckst
// *** empty log message ***
//
// Revision 1.4  2001/02/26 09:16:10  jkeckst
// insert some comments and descriptions
//
//==============================================================================

/**  <tt><b>HandleTemplate</b></tt> A Handle class for defined pointer accesses.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: HandleTemplate.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:44:05 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>                

    This class represent a template for handles. A handle is a pointer
    to any data structure with special features.</br>
    One of these is a counter, that counts every reference to the data
    object. The initial status of this counter is 1. For every additional
    reference to the data the counter is increment by 1. If the reference
    object is destroyed or the reference will be changed to an other object, 
    the counter is decrement by 1. If the counter is 0, the data object 
    will be destroyed.</br>
    Another feature is a readers writer lock. This lock can be used to 
    guarenteed that only one handle can write to the data and all other
    obejct must be wait during this time. Multiple reading is possible.
    
*/


#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef BAS_REFCOUNTER_HPP
  #include "BAS/RefCounter.hpp"
#endif
#ifndef BAS_HANDLE_HPP
  #include "BAS/Handle.hpp"
#endif
namespace BAS
{
template<class T>
class HandleTemplate : public Handle
{
public:

  enum LockStatus {
    NoLock = 0,
    Reader,
    Writer
  };

  /* Default Constructor. */
  HandleTemplate();

  /* Constructor. */
  HandleTemplate(T* t);
  
  /* Copy constructor. */
  HandleTemplate(const HandleTemplate& h);

  /* Destructor. */
  virtual ~HandleTemplate();

  /* Assignment operator. */
  HandleTemplate& operator =(T* t);

  /* Assignment operator. */
  HandleTemplate& operator =(const HandleTemplate& h);

  /* Assignment operator. */
  HandleTemplate& operator =(const HandleTemplate* h);

  /* Returns the internal data. */
  T* data();

  /* return the data pointer and clears him from self. */
  T* clearData();
  
  /* Set the data pointer to NULL and set the NoLock flag. */
  void clear();

  /** Returns the internal data.
      For use of data's methods. */
  T* operator ->();

  /** Returns the counter. */
  int counter() const;

  /** Try to read the data. Multiple access is possible. */
  void acquireRead();

  /** Ready with reading data. */
  void releaseRead();

  /** Try to write the data. Only one can write.*/
  void acquireWrite();
  
  /** Ready with writing data. */
  void releaseWrite();

private:
  void checkCounter();
  void setLockStatus(const LockStatus newLockStat);

  T                     * dataM;
  RefCounter            * counterM;
  LockStatus              lockStatM;
  RWReadersWriterLock   * rdwrLockM;

};


//------------------------------------------------------------------------------
// inlines
//------------------------------------------------------------------------------
template <class T> inline T*
HandleTemplate<T>::data()
{
  return dataM;
}

template <class T> inline T*
HandleTemplate<T>::operator ->()
{
  return dataM;
}

template <class T> inline int
HandleTemplate<T>::counter() const
{
  return counterM->counter();
}

template <class T> inline void
HandleTemplate<T>::acquireRead()
{
  setLockStatus(Reader);
}

template <class T> inline void
HandleTemplate<T>::releaseRead()
{
  setLockStatus(NoLock);
}

template <class T> inline void
HandleTemplate<T>::acquireWrite()
{
  setLockStatus(Writer);
}

template <class T> inline void
HandleTemplate<T>::releaseWrite()
{
  setLockStatus(NoLock);
}
}
#ifdef INC_TEMPL_DEFS
#include "BAS/HandleTemplate.cpp"
#endif

#endif
