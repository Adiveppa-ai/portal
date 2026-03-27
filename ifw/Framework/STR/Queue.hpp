#ifndef QUEUE_HPP
#define QUEUE_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: STR
//------------------------------------------------------------------------------
// Module Description:
//   Basic stream class implementation.
//
//------------------------------------------------------------------------------
//
// Revision: 10006  7.3_patch  06-Dec-2006  jyadav
// Added CAS support for HP itanium
//
// Revision: 10005  7.3  24-Oct-2006  jlan
// Added tryWrite() API for nonblocking write (TIMOS HotStandby)
//
// Revision: 10004  6.7_FP2  20-Aug-2004  JY
// Added an option for nonblocking read for AAA Gw Server
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.4  2001/11/14 14:20:30  bt
// PETS #40026 Block transfer mode introduced to improve the performance.
//
// Revision 1.3  2001/09/03 12:35:57  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.2  2001/08/28 07:04:45  jkeckst
// PETS 37618 code review cr-08.2001
//
// Revision 1.1  2000/08/24 11:10:45  rmurawsk
// STR splitted into Base and STR
//
// Revision 1.21  2000/06/20 16:03:02  sd
// - The gcc does not support constant class members under AIX. (core dump
//   while loading the shared library).
//
// Revision 1.20  2000/06/16 09:11:24  bt
// Changes for AIX xlC V366.
//
// Revision 1.19  2000/06/16 08:26:52  bt
// Changes for AIX xlC V366.
//
// Revision 1.18  1999/11/08 08:19:59  jkeckst
// code review
//
// Revision 1.17  1999/06/11 09:25:35  clohmann
// *** empty log message ***
//
// Revision 1.16  1999/05/18 07:52:50  clohmann
// *** empty log message ***
//
// Revision 1.15  1999/05/17 09:04:08  clohmann
// *** empty log message ***
//
// Revision 1.14  1999/04/27 08:09:08  arockel
// BAS::ErrorStatus renamed to BAS::Status.
//
// Revision 1.9  1999/03/30 12:26:26  arockel
// InputFile and BAS::Directory improved.
//
// Revision 1.8  1999/03/29 10:52:01  arockel
// Remaining STR classes added, BAS::Directory improved.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   OBJECT_STREAM_HPP
  #include "STR/ObjectStream.hpp"
#endif
#ifndef   __PORTABLE_DEFNS_H__
  #include "STR/PortableDefns.hpp"
#endif

#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

/** <tt><b>Queue</b></tt>.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Queue.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.4 $</font></td>
    <td><font size=-1>$Date: 2001/11/14 14:20:30 $</font></td>
    <td><font size=-1>$Author: bt $</font></td>
    </tr>
    </table>

    <p> This class represents a first-in-first-out (FIFO) queue
        that provides producer-consumer synchronization semantics
        for exchanging values between cooperating threads.<br>

        If the registry entry 'BlockTransfer' is set to 'True' the values
        are transfered in blocks of the specified block size given by the
        registry entry 'BlockSize'. The block transfer mode improves the
        performance for batch processing with multiple pipelines.<br><br>

    <dl>
    <dt><b>Registry entries</b></dt>
         <dd>Size</dd>
         <dd>BlockSize</dd>
         <dd>BlockTransfer (default = False)</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Requests send</b></dt>
         <dd>none</dd>
    <dt><b>Messages receive</b></dt>
         <dd>none</dd>
    <dt><b>Requests receive</b></dt>
         <dd>REQ_BUFFER_ENTRIES</dd>
    <dt><b>Errors</b></dt>
         <dd>ERR_INVALID_QUEUE_SIZE</dd>
         <dd>ERR_REG_ENTRY_NOT_FOUND</dd>
         <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
         <dd>ERR_REG_VALUE_INVALID</dd>
    </dl>
*/
namespace STR {
template <class T>
class Queue: public ObjectStream<T>
{
  public:

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    Queue();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    Queue(const BAS::String& objectName);

    /** Destructor. */
    virtual ~Queue();
    //@}

    /** Read from the queue */
    virtual bool read(T& val, bool block=true);

    /** Write into the queue */
    virtual bool write(const T& val);

    /** Non-blocking write into the queue 
     *  @param val The value to be enqueued
     *  @return true if succeeded or false
     */
    virtual bool tryWrite(const T& val);

    /** Return the actual queue size */
    size_t queueSize() const;

    /** Return number of entries in queue 
     * @param lockProtected flag indicates to get the value
     * that is protected by a lock or not.  default is 'true'.
     * @return number of entries in queue
     */
    size_t queueEntries(bool lockProtected = true) const;

    /** Return the actual queue read block time */
    size_t queueReadBlockTime() const;

    /** The next service cancellation is abort */
    virtual void requestAbort();

    /** Check registry for new values */
    virtual bool registryUpdate(const BAS::RegistryEntry*, BAS::ProtectedBool&);

    /** Handle requests from other registered objects */
    void receiveRequest(BAS::Message& msg);

   /** Return write count in queue */
    u_int64 queueCount() const;
  
#ifdef __aix
    bool operator<(const Queue<T>& rVal) const { return true; };
    bool operator==(const Queue<T>& rVal) const { return true; };
#endif

  protected:

  private:

    // Default, copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

    Queue(Queue<T>& right);

    const Queue<T>& operator=(Queue<T>& right);

    // Read the configuration values out of the registry

    bool readRegistry();

   // increase writeCount
   void increaseWriteCount();

    RWPCValQueue<T> queueM;

    // Blocking time for read and write in ms

    int32 queueBlockTimeM; 

    const size_t minReadBlockTimeM; 

    const size_t maxReadBlockTimeM; 

    // "fast" shutdown
    bool shutdownIsAbortM;

    RWTValSlist<RWTValSlist<T>*> emptyBlocksM;

    RWTValSlist<RWTValSlist<T>*> filledBlocksM;

    RWTValSlist<T>* readBufferM;

    RWTValSlist<T>* writeBufferM;

    RWMutexLock readLockerM;

    RWMutexLock commonLockerM;

    RWCondition cannotReadM;

    RWCondition cannotWriteM;

    size_t waitingReaderM;

    size_t waitingWriterM;

    size_t maxEntriesM;

    size_t notTransferedM;

    size_t notReadM;

    size_t blockSizeM;

    // total write count
    u_int64 writeCountM;

    bool blockTransferM;

    // Read block wise
    bool readBlocks(T& val);

    // Write block wise
    bool writeBlocks(const T& val);

    // ARRAY based lock Free Queue

    // Read Array wise
    bool readArray(T& val, bool block=true);

    // Write Array wise
    bool writeArray(const T& val, bool block=true);

	// dump the arrayQueue
	void dumpArrayQueue(const BAS::String& caller);

    bool arrayTypeM;

	// Size of the array 
    unsigned int sizeM;

	// Reader starting point
    unsigned int headM;

	// Writer starting point
    unsigned int tailM;

    // Spin Count number
    unsigned int spinCountM;

    // Yield Count number
    unsigned int yieldCountM;

    // Sleep Time in Milli seconds
    unsigned int sleepTimeMilliSecM;

	// Node that stores the data
    struct arrayNode
    {
		T val;
		unsigned int ref;
	};

	// Actual queue
	struct arrayNode* arrayQueueM;

};

//======================================================================
// Return the actual queue size
//======================================================================

template <class T>
inline size_t Queue<T>::queueSize() const
{
  if (blockTransferM == true)
  {
    RWLockGuard<RWMutexLock>
      commonGuard(RWSTD_CONST_CAST(RWMutexLock&,commonLockerM));

    return maxEntriesM;
  }
  else if (arrayTypeM == true)
  {
    return sizeM;
  }
  else
  {
    return queueM.getCapacity();
  }
}

//======================================================================
// Return number of entries in queue
//======================================================================

template <class T>
inline size_t Queue<T>::queueEntries(bool lockProtected) const
{
  if (blockTransferM == true)
  {
    if (lockProtected)
    {
      RWLockGuard<RWMutexLock>
        readGuard(RWSTD_CONST_CAST(RWMutexLock&,readLockerM));

      RWLockGuard<RWMutexLock>
        commonGuard(RWSTD_CONST_CAST(RWMutexLock&,commonLockerM));

      return (notReadM + notTransferedM);
    }
    else
    {
      return (notReadM + notTransferedM);
    }
  }
  else if (arrayTypeM == true)
  {
    return (tailM - headM);
  }
  else
  {
    return queueM.entries();
  }
}

//======================================================================
// Return total number of write to queue
//======================================================================
template <class T>
inline u_int64 Queue<T>::queueCount() const
{
   return writeCountM;
}

//======================================================================
// Increase writeCountM
//======================================================================
template <class T>
inline void Queue<T>::increaseWriteCount() 
{
  // no locking, as it will be expensive 
  if (writeCountM == UINT64_MAX)
  { 
    //reset counter
    writeCountM = 0;
  }
  else
  {
    writeCountM++;
  }
}

//======================================================================
// Request abort
//======================================================================

template <class T>
inline void Queue<T>::requestAbort() 
{
  shutdownIsAbortM = true;
}
}
#ifdef INC_TEMPL_DEFS
  #include "Queue.cpp"
#endif

#endif // QUEUE_HPP

