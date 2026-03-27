#ifndef BAS_THREADINFO
#define BAS_THREADINFO
//==============================================================================
//
// Copyright (c) 2003, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Author: Alexander Rockel
//==============================================================================

#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

#ifdef RW_MULTI_THREAD
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#endif

namespace BAS 
{
/** class ThreadInfo.
This class is used by the debug trace class Trace to track thread-related information.
<b>It is not intended for direct use</b> - please refer to the description of the
trace macros for more information.
<p>This class is not used in the optimized version of the system.
*/
class ThreadInfo
{
  public:
    /// Default constructor.
    ThreadInfo(bool isThreadSafe=false);

    /// Copy constructor.
    ThreadInfo(const ThreadInfo& obj);
            
    /// Stores the thread id.
    bool         setThreadId(unsigned id);

    /// Retrieves the thread id.
    unsigned     getThreadId() const;

    /// Assignment operator.
    ThreadInfo& 
                 operator=(const ThreadInfo& rVal);

    /// The return value of this method will be true if the associated 
    /// class was declared as thread-safe. This method has to be overloaded
    /// on a per class basis.
    virtual bool isThreadSafe();

  private:
    unsigned     threadIdM;
    RWMutexLock  threadIdLockM;
};


//---------------------------------------------------
// Inlines
//---------------------------------------------------

inline
ThreadInfo::ThreadInfo(bool isThreadSafe)
#ifdef RW_MULTI_THREAD
               :threadIdM(rwThreadId().hash())
#else
               :threadIdM(1)
#endif
{
  // nothing to do
}

//---------------------------------------------------

inline
ThreadInfo::ThreadInfo(const ThreadInfo& obj)
{
   *this = obj;
}

//---------------------------------------------------

inline bool    
ThreadInfo::setThreadId(unsigned id)
{
  RWLockGuard<RWMutexLock> guard(threadIdLockM);
  if (id == threadIdM)
  {
    return false; // thread did not change
  }
  else
  {
    threadIdM = id;
    return true; // thread did change
  }
}

//---------------------------------------------------

inline unsigned 
ThreadInfo::getThreadId() const
{
  RWMutexLock* threadIdLockPtr = const_cast<RWMutexLock*>(&threadIdLockM);
  RWLockGuard<RWMutexLock> guard(*threadIdLockPtr);
  return threadIdM;
}

//---------------------------------------------------

inline bool     
ThreadInfo::isThreadSafe() 
{
  return false;
}

//---------------------------------------------------

inline ThreadInfo&
ThreadInfo::operator=(const ThreadInfo& rVal)
{
  if (this != &rVal)
  {
     threadIdM     = rVal.threadIdM;
     // threadIdMutexLockM intentionally not copied
  }
  return *this;
}

}
#endif // BAS_THREADINFO
