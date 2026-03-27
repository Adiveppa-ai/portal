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
//  <description>
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
// $RCSfile: HandleTemplate.cpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:44:03 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: HandleTemplate.cpp,v $
// Revision 1.6  2001/10/02 09:54:19  jkeckst
// add some changes for DAT_UniData
//
// Revision 1.5  2001/08/29 14:22:25  jkeckst
// PETS: 38750 set the ref counter to zero if clear() called.
// Make all points sensible to get a zero pointed ref counter.
//
// Revision 1.4  2001/08/17 12:16:10  jkeckst
// PETS 37459 need a clear methode
//
// Revision 1.3  2001/07/25 08:32:56  jkeckst
// PETS #37459 add some debug informations
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
// Revision 1.7  2001/02/26 15:10:32  jkeckst
// *** empty log message ***
//
// Revision 1.6  2001/02/26 13:23:20  jkeckst
// *** empty log message ***
//
// Revision 1.5  2001/02/26 10:14:42  jkeckst
// change copy constructor
//
// Revision 1.4  2001/02/26 09:16:10  jkeckst
// insert some comments and descriptions
//
//==============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef HANDLETEMPLATE_HPP
  #include "BAS/HandleTemplate.hpp"
#endif

namespace BAS
{
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T>
HandleTemplate<T>::HandleTemplate()
  : dataM(0)
  , counterM(new RefCounter(1))
  , lockStatM(NoLock)
  , rdwrLockM(new RWReadersWriterLock())
{
  D_ENTER("HandleTemplate<T>::HandleTemplate()");
  D_PRINT(this);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T>
HandleTemplate<T>::HandleTemplate(T* t)
  : dataM(t)
  , counterM(new RefCounter(1))
  , lockStatM(NoLock)
  , rdwrLockM(new RWReadersWriterLock())
{
  D_ENTER("HandleTemplate<T>::HandleTemplate(T* t)");
  D_PRINT(this);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T>
HandleTemplate<T>::HandleTemplate(const HandleTemplate& h)
  : dataM(h.dataM)
  , counterM(h.counterM)
  , lockStatM(NoLock)
  , rdwrLockM(h.rdwrLockM)
{
  D_ENTER("HandleTemplate<T>::HandleTemplate(const HandleTemplate& h)");
  D_PRINT(this);

  counterM->safeIncCounter();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T>
HandleTemplate<T>::~HandleTemplate()
{
  D_ENTER("HandleTemplate<T>::~HandleTemplate()");
  D_PRINT(this);

  if (lockStatM != NoLock) {
    setLockStatus(NoLock);
    checkCounter();
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T> HandleTemplate<T>&
HandleTemplate<T>::operator =(T* t)
{
  D_ENTER("HandleTemplate<T>::operator =(T* t)");
  D_PRINT(this);

  if (dataM != t)
  {
    setLockStatus(NoLock);
    // if no counter exists, create one
    if (counterM == 0) {
      counterM = new RefCounter(1);
    // if a counter exists, remove accessing
    } else {
      counterM->lock();
      // if we are the last access to the data, remove data
      if (counterM->decCounter() == 0)
      {
        if (dataM) {
          delete dataM;
        }
        counterM->setCounter(1);
        counterM->release();
      // if we are not the last access, create a new instance
      } else {
        counterM->release();
        counterM = new RefCounter(1);
        rdwrLockM = new RWReadersWriterLock();
      }
    }
    dataM = t;
  }

  return *this;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T> HandleTemplate<T>&
HandleTemplate<T>::operator =(const HandleTemplate& h)
{
  D_ENTER("HandleTemplate<T>::operator =(const HandleTemplate& h)");
  D_PRINT(this);

  if (dataM == h.dataM)
  {
    return *this;
  }

  setLockStatus(NoLock);
  checkCounter();

  rdwrLockM = h.rdwrLockM;
  dataM = h.dataM;

  counterM = h.counterM;

  counterM->safeIncCounter();
  
  return *this;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T> HandleTemplate<T>&
HandleTemplate<T>::operator =(const HandleTemplate* h)
{
  D_ENTER("HandleTemplate<T>::operator =(const HandleTemplate* h)");
  D_PRINT(this);

  if (dataM == h->dataM)
  {
    return *this;
  }

  setLockStatus(NoLock);
  checkCounter();

  rdwrLockM = h.rdwrLockM;
  dataM = h->dataM;
  counterM = h->counterM;

  counterM->safeIncCounter();

  return *this;
}

//------------------------------------------------------------------------------
// The counter will be decremented. If the counter is 0, then it is the
// flag that nobody points to this object. In this case the object can
// deleted.
//------------------------------------------------------------------------------
template <class T> void
HandleTemplate<T>::checkCounter()
{
  D_ENTER("HandleTemplate<T>::checkCounter()");

  D_PRINT(this);

  // if no counter exists, than is nothing to do
  if (counterM == 0) {
    return;
  }
  
  counterM->lock();

  if (counterM->decCounter() == 0) {
    if (dataM) {
      delete dataM;
    }
    counterM->release();
    delete counterM;
    counterM = 0;
    delete rdwrLockM;
  } else {
    counterM->release();
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T> void
HandleTemplate<T>::setLockStatus(const LockStatus newLockStat)
{
  D_ENTER("HandleTemplate<T>::setLockStatus(const int )");

  D_PRINT(this);
    
  if (lockStatM != NoLock) {
    D_PRINT("release rdwr lock");
    rdwrLockM->release();
  }

  switch (newLockStat) {
    case Reader: 
      rdwrLockM->acquireRead();
      D_PRINT("aquire read");
      break;
    case Writer: 
      rdwrLockM->acquireWrite();
      D_PRINT("aquire write");
      break;
    case NoLock: 
      break;
    default:
      D_PRINT("ERROR: unknown lock status");
      break;
  }  
  lockStatM = newLockStat;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T> T*
HandleTemplate<T>::clearData()
{
  D_ENTER("HandleTemplate<T>::clearData()");
  
  T * retVal = dataM;
  dataM = 0;
  return retVal;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T> void
HandleTemplate<T>::clear()
{
  D_ENTER("HandleTemplate<T>::clear()");
  
  if (lockStatM != NoLock) {
    setLockStatus(NoLock);
    checkCounter();
    counterM = 0;
    dataM    = 0;
  }
}
}
