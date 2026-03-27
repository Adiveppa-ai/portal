#ifndef BAS_QUEUE_H
#define BAS_QUEUE_H
//==============================================================================
//
// Copyright (c) 1996, 2024, Oracle and/or its affiliates.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: STR
//------------------------------------------------------------------------------
// Module Description:
//   Queue stream class implementation.
//
//------------------------------------------------------------------------------
// Revision: 10011  7.4 06-Jul-2011  sumeemis
// Bug 11815646 - p-10434779 phase ii changes for pipeline parallel loading ecr
//
// Revision: 10010  7.4 06-Nov-2008  abgeorg
// bug6970010 Fix a bug in the Array Buffer Implementation
//
// Revision: 10009  7.3_Patch  06-Dec-2006  jyadav
// Added CAS support for HP itanium
//
// Revision: 10008  7.3  24-Oct-2006  jlan
// PRSF00234998 Added tryWrite() the non-blocking write
//
// Revision: 10007  7.3  1-Aug-2006  jlan
// PRSF00226859 Fixed uninitialized member objects after the contructor() calls
//
// Revision: 10006  7.3  7-Mar-2006  bertm
// PRSF00194286 Fixed the text in the D_ENTER calls.
//
// Revision: 10005  7.2_EA  6-May-2005  rtang
// PRSF00167007 Added a queue counter for AAA GW Web instrument
//
// Revision: 10004  6.7_FP2  20-Aug-2004  JY
// Added an option for nonblocking read for AAA Gw Server
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// $Log: STR_Queue.cpp,v $
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
// STR splitted into STR_Base and STR
//
// Revision 1.23  2000/08/15 09:32:34  bt
// Call to BAS_String::convert() changed (size_t cast added).
//
// Revision 1.22  2000/06/20 16:03:02  sd
// - The gcc does not support constant class members under AIX. (core dump
//   while loading the shared library).
//
// Revision 1.21  1999/12/07 13:24:21  sd
// Anachronistic (for aCC) constructs removed.
//
// Revision 1.20  1999/12/07 13:14:09  sd
// Anachronistic constructs under HPUX removed.
//
// Revision 1.19  1999/11/09 12:27:11  clohmann
// Checked all CodeReview remarks.
//
// Revision 1.18  1999/11/08 08:19:59  jkeckst
// code review
//
// Revision 1.17  1999/08/13 10:26:46  bt
// Line 269: consvert changed to convert.
//
// Revision 1.16  1999/08/13 09:15:23  clohmann
// Argument with queue capacity to REQ_BUFFER_ENTRIES added.
//
// Revision 1.11  1999/04/27 08:09:07  arockel
// BAS_ErrorStatus renamed to BAS_Status.
//
// Revision 1.9  1999/04/07 15:35:51  bt
// rcsid commented out.
//
// Revision 1.6  1999/03/29 10:52:00  arockel
// Remaining STR classes added, BAS_Directory improved.
//
//==============================================================================

#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   STR_CONSTANTS_HPP
  #include "STR/Constants.hpp"
#endif

#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

#define DEFAULT_SPIN_COUNT  100
#define DEFAULT_YIELD_COUNT 100
#define DEFAULT_SLEEP_TIME_MILLI_SEC 10

//======================================================================
// Default constructor
//======================================================================

template <class T>
STR::Queue<T>::Queue()
  :   ObjectStream<T>()
    , queueM(0)
    , queueBlockTimeM (1000)
    , minReadBlockTimeM (5)
    , maxReadBlockTimeM (250)
    , shutdownIsAbortM (false)
    , readBufferM (0)
    , writeBufferM (0)
    , cannotReadM (commonLockerM)
    , cannotWriteM (commonLockerM)
    , waitingReaderM (0)
    , waitingWriterM (0)
    , maxEntriesM (0)
    , notTransferedM (0)
    , notReadM (0)
    , blockSizeM (0)
    , blockTransferM (false)
    , writeCountM (0)
    , arrayTypeM (false)
    , sizeM (0)
    , headM (0)
    , tailM (0)
    , spinCountM (DEFAULT_SPIN_COUNT)
    , yieldCountM (DEFAULT_YIELD_COUNT)
    , sleepTimeMilliSecM (DEFAULT_SLEEP_TIME_MILLI_SEC)
    , arrayQueueM (0)
{
  D_ENTER("STR::Queue::Queue()");
}

//======================================================================
// "Name" constructor
//======================================================================

template <class T>
STR::Queue<T>::Queue(const BAS::String& objectName)
  :   ObjectStream<T>(objectName)
    , queueM(0)
    , queueBlockTimeM (1000)
    , minReadBlockTimeM (5)
    , maxReadBlockTimeM (250)
    , shutdownIsAbortM (false)
    , readBufferM (0)
    , writeBufferM (0)
    , cannotReadM (commonLockerM)
    , cannotWriteM (commonLockerM)
    , waitingReaderM (0)
    , waitingWriterM (0)
    , maxEntriesM (0)
    , notTransferedM (0)
    , notReadM (0)
    , blockSizeM (0)
    , blockTransferM (false)
    , writeCountM (0)
    , arrayTypeM (false)
    , sizeM (0)
    , headM (0)
    , tailM (0)
    , spinCountM (DEFAULT_SPIN_COUNT)
    , yieldCountM (DEFAULT_YIELD_COUNT)
    , sleepTimeMilliSecM (DEFAULT_SLEEP_TIME_MILLI_SEC)
    , arrayQueueM (0)
{
  D_ENTER("STR::Queue::Queue(const BAS::String&)");

  if ((this->isRegistered() == true) && (this->isValid() == true))
  {
    this->isValid(readRegistry());
  }
}

//======================================================================
// Destructor
//======================================================================

template <class T>
STR::Queue<T>::~Queue()
{
  D_ENTER("STR::Queue::~Queue()");

  if (blockTransferM == true)
  {
    RWLockGuard<RWMutexLock> readGuard(readLockerM);

    RWLockGuard<RWMutexLock> commonGuard(commonLockerM);

    while (emptyBlocksM.entries() > 0)
    {
      delete emptyBlocksM.removeFirst();
    }

    while (filledBlocksM.entries() > 0)
    {
      delete filledBlocksM.removeFirst();
    }
  }
  else if (arrayTypeM == true)
  {
    delete [] arrayQueueM;
  }

  requestAbort();
}

//======================================================================
// Read from queue
//======================================================================

template <class T>
bool STR::Queue<T>::read(T& val, bool block)
{
  D_ENTER("STR::Queue::read()");

  if (blockTransferM == true)
  {
    return readBlocks(val);
  }
  else if (arrayTypeM == true)
  {
    return readArray(val,block);
  }
  else
  {
    RWWaitStatus status;

    while ((status = queueM.read(val, queueBlockTimeM)) == RW_THR_TIMEOUT)
    {
      RWThreadSelf self = ::rwThread();

      if (self.isValid() == true || shutdownIsAbortM == true)
      {
        self.serviceInterrupt();

        self.serviceCancellation();
      }
      if( (!block) && (status == RW_THR_TIMEOUT) )
      { 
        D_PRINT("Returning after timeout for non blocking only");
        return false;
      }
    }

    return status == RW_THR_COMPLETED;
  }
}

//======================================================================
// Write into queue
//======================================================================

template <class T>
bool STR::Queue<T>::write(const T& val)
{
  D_ENTER("STR::Queue::write(const T& val)");

  increaseWriteCount();

  if (blockTransferM == true)
  {
    return writeBlocks(val);
  }
  else if (arrayTypeM == true)
  {
    return writeArray(val);
  }
  else
  {
    RWWaitStatus status;

    while ((status = queueM.write(val, queueBlockTimeM)) == RW_THR_TIMEOUT)
    {
      RWThreadSelf self = ::rwThread();
 
      if ((self.isValid() == true) && (shutdownIsAbortM == true))
      {
        self.serviceInterrupt();

        self.serviceCancellation();
      }
    }

    return status == RW_THR_COMPLETED;
  }
}

//======================================================================
// Non-blocking write into queue
//======================================================================

template <class T>
bool STR::Queue<T>::tryWrite(const T& val)
{
    D_ENTER("STR::Queue::tryWrite(const T& val)");

    return (queueM.tryWrite(val) == TRUE ? true : false);

}

//======================================================================
// Read registry
//======================================================================

template <class T>
bool STR::Queue<T>::readRegistry()
{
  D_ENTER("STR::Queue::readRegistry()");

  const BAS::RegistryEntry* subEntry = 0;

  const BAS::RegistryEntry* mainEntry = this->registry();

  if (mainEntry != 0)
  {
	//------------------------------------------------------------------
    // Get the registry value of the entry 'QueueBlockTime'
    //------------------------------------------------------------------

    subEntry = mainEntry->find(registryQueueBlockTimeCM);

    if (subEntry != 0)
    {
      BAS::String queueBlockTimeVal = subEntry->value();

      queueBlockTimeVal.toNum(queueBlockTimeM);

      if (queueBlockTimeM <= 0 )
      {
        queueBlockTimeM = 1000;
      }
      D_PRINT("QueueBlockTime is " << queueBlockTimeM);
    }

    //------------------------------------------------------------------
    // Get the registry value of the entry 'LockFree'
    //------------------------------------------------------------------

    arrayTypeM = false;

    subEntry = mainEntry->find(registryArrayTypeCM);

    if (subEntry != 0)
    {
      BAS::String arrayBasedVal = subEntry->value();

      arrayBasedVal.toUpper();

      if (arrayBasedVal == "TRUE")
      {
        arrayTypeM = true;

        D_PRINT("Set arrayType to true");

        subEntry = mainEntry->find(registrySleepTimeMilliSecCM);
        if (subEntry != 0)
        {
          BAS::String sleepTime = subEntry->value();
          sleepTime.toNum(sleepTimeMilliSecM);
	  if (sleepTimeMilliSecM <= 0)
          {
               sleepTimeMilliSecM = DEFAULT_SLEEP_TIME_MILLI_SEC;
          }
        }
        D_PRINT("SleepTimeMilliSec is " << sleepTimeMilliSecM);

        subEntry = mainEntry->find(registrySpinCountCM);
        if (subEntry != 0)
        {
          BAS::String spinCount = subEntry->value();
          spinCount.toNum(spinCountM);
          if (spinCountM <= 0)
          {
               spinCountM = DEFAULT_SPIN_COUNT;
          }
        }
        D_PRINT("SpinCount is " << spinCountM);

        subEntry = mainEntry->find(registryYieldCountCM);
        if (subEntry != 0)
        {
          BAS::String yieldCount = subEntry->value();
          yieldCount.toNum(yieldCountM);
	  if (yieldCountM <= 0)
          {
               yieldCountM = DEFAULT_YIELD_COUNT;
          }
        }
        D_PRINT("YieldCount is " << yieldCountM);

      }
    }

    //------------------------------------------------------------------
    // Get the registry value of the entry 'BlockTransfer'
    //------------------------------------------------------------------

    subEntry = mainEntry->find(registryBlockTransferCM);

    if (subEntry != 0)
    {
      BAS::String blockTransferVal = subEntry->value();

      blockTransferVal.toUpper();

      if (blockTransferVal == "TRUE")
      {
        blockTransferM = true;

        D_PRINT("Set block transfer to true");
      }
    }

    //------------------------------------------------------------------
    // Get the registry value of the entry 'Size'
    //------------------------------------------------------------------

    BAS::String queueSizeVal = "";

    BAS::String regSizeName = this->name() + "." + registryQueueSizeCM;

    subEntry = mainEntry->find(registryQueueSizeCM);

    if (subEntry != 0)
    {
      queueSizeVal = subEntry->value();

      int64 numQueueSize = atoi64(queueSizeVal.data());

      if (numQueueSize < 0)
      {
        this->setStatus("ERR_INVALID_QUEUE_SIZE",
                  BAS::Status::warning,
                  regSizeName);

        numQueueSize = 1000;

        queueSizeVal.convert(numQueueSize);
      }

      D_PRINT("Set queue capacity to " << numQueueSize);

      if (blockTransferM == true)
      {
        maxEntriesM = numQueueSize;
      }
      else if (arrayTypeM == true)
      {
        sizeM = numQueueSize;

        tailM = headM = 0;

        arrayQueueM = new struct arrayNode[sizeM];
        if (arrayQueueM != NULL)
        {
          for (size_t i = 0; i <sizeM; i++)
          {
            arrayQueueM[i].val = NULL;
            arrayQueueM[i].ref = i;
          }
        }
        else
        {
          D_PRINT("Unable to create Array Queue with size " << sizeM );
        }
      }

      else
      {
        queueM.setCapacity(numQueueSize);
      }
    }
    else
    {
      this->setStatus("ERR_REG_ENTRY_NOT_FOUND",
					  BAS::Status::critical,
					  regSizeName);

      return false;
    }

    //------------------------------------------------------------------
    // Get the registry value of the entry 'BlockSize'
    //------------------------------------------------------------------

    if (blockTransferM == true)
    {
      BAS::String regBlockSizeName = this->name() + "." + registryBlockSizeCM;

      subEntry = mainEntry->find(registryBlockSizeCM);
  
      if (subEntry != 0)
      {
        BAS::String blockSizeVal = subEntry->value();
  
        int64 numBlockSize = atoi64(blockSizeVal.data());
  
        if (numBlockSize > 1)
        {
          size_t numberOfBlocks = maxEntriesM / numBlockSize;
  
          if (numberOfBlocks > 1)
          {
            D_PRINT("Set queue block size to " << blockSizeVal);

            blockSizeM = numBlockSize;

            maxEntriesM = blockSizeM * numberOfBlocks;
  
            for (size_t cnt = 0; cnt < numberOfBlocks; cnt++)
            {
              emptyBlocksM.append(new RWTValSlist<T>);
            }
          }
        }

        if (blockSizeM <= 1)
        {
          BAS::StringList argList;

          argList.append(this->name());

          argList.append(registryQueueSizeCM + "=" +
                         queueSizeVal + ", " +
                         registryBlockSizeCM + "=" +
                         blockSizeVal);

          this->setStatus("ERR_REG_VALUE_INVALID",
						  BAS::Status::critical,
						  argList);

          return false;
        }
      }
      else
      {
        this->setStatus("ERR_REG_ENTRY_NOT_FOUND",
						BAS::Status::critical,
						regBlockSizeName);

        return false;
      }
    }
  }
  else
  {
	  this->setStatus("ERR_REG_SUBTREE_NOT_FOUND", 
					  BAS::Status::critical,
					  this->name());

    return false;
  }

  return true;
}

//======================================================================
// Registry update
//======================================================================

template <class T>
bool STR::Queue<T>::registryUpdate(const BAS::RegistryEntry* update,
                                   BAS::ProtectedBool&       workedOn)
{
  D_ENTER("STR::Queue::registryUpdate()");

  RWPRECONDITION(update);

  BAS::RegistryEntry *const mainEntry = this->registry();

  RWPRECONDITION(mainEntry);

  const BAS::RegistryEntry* sizeEntry = update->find(registryQueueSizeCM);

  BAS::RegistryEntry* origSizeEntry = mainEntry->find(registryQueueSizeCM);

  size_t newMaxEntries = maxEntriesM;

  BAS::String queueSizeVal = "";

  if ((sizeEntry != 0) && (origSizeEntry != 0))
  {
    queueSizeVal = sizeEntry->value();

    int64 numQueueSize = atoi64(queueSizeVal.data());

    if (numQueueSize < 0)
    {
      numQueueSize = 1000;

      queueSizeVal.convert(numQueueSize);
    }

    if (blockTransferM == true)
    {
      newMaxEntries = numQueueSize;
    }
    else
    {
      D_PRINT("Set queue capacity to " << queueSizeVal);

      queueM.setCapacity(numQueueSize);

      origSizeEntry->value(queueSizeVal);
    }
	workedOn = true;
  }

  if (blockTransferM == true)
  {
    const BAS::RegistryEntry* blockEntry = update->find(registryBlockSizeCM);

    BAS::RegistryEntry* origBlockEntry = mainEntry->find(registryBlockSizeCM);

    if ((blockEntry != 0) && (origBlockEntry != 0))
    {
      BAS::String blockSizeVal = blockEntry->value();

      int64 numBlockSize = atoi64(blockSizeVal.data());

      if (numBlockSize > 1)
      {
        size_t numberOfBlocks = newMaxEntries / numBlockSize;

        if (numberOfBlocks > 1)
        {
          newMaxEntries = numBlockSize * numberOfBlocks;

          if ((newMaxEntries != maxEntriesM) || ((size_t)numBlockSize != blockSizeM))
          {
            RWLockGuard<RWMutexLock> readGuard(readLockerM);

            RWLockGuard<RWMutexLock> commonGuard(commonLockerM);

            notTransferedM = 0;

            blockSizeM = numBlockSize;

            maxEntriesM = newMaxEntries;

            if (readBufferM == 0)
            {
              readBufferM = new RWTValSlist<T>;
            }

            while (filledBlocksM.entries() > 0)
            {
              RWTValSlist<T>* filledBuffer = filledBlocksM.removeFirst();

              while (filledBuffer->entries() > 0)
              {
                readBufferM->append(filledBuffer->removeFirst());
              }
          
              delete filledBuffer;
            }
          
            if (writeBufferM != 0)
            {
              while (writeBufferM->entries() > 0)
              {
                readBufferM->append(writeBufferM->removeFirst());
              }
          
              delete writeBufferM;
          
              writeBufferM = 0;
            }
          
            while (emptyBlocksM.entries() > 0)
            {
              delete emptyBlocksM.removeFirst();
            }

            notReadM = readBufferM->entries();

            if (notReadM > 0)
            {
              --numberOfBlocks;
            }
            else
            {
              delete readBufferM;

              readBufferM = 0;
            }

            for (size_t cnt = 0; cnt < numberOfBlocks; cnt++)
            {
              emptyBlocksM.append(new RWTValSlist<T>);
            }

            D_PRINT("Set queue capacity to " << queueSizeVal);

            origSizeEntry->value(queueSizeVal);

            D_PRINT("Set queue block size to " << blockSizeVal);

            origBlockEntry->value(blockSizeVal);
          }
        }
      }
	  workedOn = true;
    }
  }

  return true;
}

//======================================================================
// Receive request
//======================================================================

template <class T>
void STR::Queue<T>::receiveRequest(BAS::Message& msg)
{
  D_ENTER("STR::Queue::receiveRequest(BAS::Message&)");

  //----------------------------------------------------------------------
  // Return the queue size and the number of queue entries
  // if the request 'REQ_BUFFER_ENTRIES' has been received
  //----------------------------------------------------------------------

  if (msg.messageName() == "REQ_BUFFER_ENTRIES")
  {
    D_PRINT("STR::Queue: Receive REQ_BUFFER_ENTRIES");

    msg.arguments().clear();

    BAS::String capacity;

    capacity.convert(queueSize(),(size_t) 7,RWCString::leading,'0');

    msg.arguments().append(capacity);

    BAS::String entries;

    entries.convert(queueEntries(),(size_t) 7,RWCString::leading,'0');

    msg.arguments().append(entries);
  }
}

//======================================================================
// Read block wise
//======================================================================

template <class T>
bool STR::Queue<T>::readBlocks(T& val)
{
  D_ENTER("STR::Queue::readBlocks()");

  readLockerM.acquire();

  while (true)
  {
    if (notReadM == 0)
    {
      commonLockerM.acquire();

      if (filledBlocksM.entries() > 0)
      {
        readBufferM = filledBlocksM.removeFirst();

        notReadM = readBufferM->entries();

        notTransferedM -= notReadM;
      }

      commonLockerM.release();
    }

    if (notReadM > 0)
    {
      val = readBufferM->removeFirst();

      --notReadM;

      if (notReadM == 0)
      {
        commonLockerM.acquire();

        emptyBlocksM.append(readBufferM);

        readBufferM = 0;

        if (waitingWriterM > 0)
        {
          cannotWriteM.signal();
        }

        commonLockerM.release();
      }

      readLockerM.release();

      return true;
    }
    else
    {
      size_t readBlockTime = minReadBlockTimeM;

      do
      {
        commonLockerM.acquire();

        RWWaitStatus waitStatus;

        size_t prevNotTransfered = notTransferedM;

        size_t totalReadBlockTime = 0;

        readLockerM.release();

        do
        {
          ++waitingReaderM;

          waitStatus = cannotReadM.wait(readBlockTime);

          --waitingReaderM;

          totalReadBlockTime += readBlockTime;
        }
        while (readLockerM.tryAcquire() == false);

        if (waitStatus == RW_THR_TIMEOUT)
        {
          if ((notTransferedM > 0) && (notTransferedM < blockSizeM))
          {
            if ((notTransferedM == prevNotTransfered) && (writeBufferM != 0))
            {
              readBufferM = writeBufferM;

              notReadM = readBufferM->entries();

              notTransferedM -= notReadM;

              writeBufferM = 0;

              readBlockTime = 0;

              if (waitingWriterM > 0)
              {
                cannotWriteM.signal();
              }
            }
            else if (notTransferedM > prevNotTransfered)
            {
              prevNotTransfered = notTransferedM - prevNotTransfered;

              readBlockTime = (totalReadBlockTime * blockSizeM /
                                prevNotTransfered) - totalReadBlockTime;

              if (readBlockTime > maxReadBlockTimeM)
              {
                readBlockTime = maxReadBlockTimeM;
              }
            }
            else
            {
              readBlockTime = 0;
            }

            commonLockerM.release();
          }
          else if ((notTransferedM == 0) && (notReadM == 0))
          {
            readBlockTime = maxReadBlockTimeM;

            commonLockerM.release();

            RWThreadSelf self = ::rwThread();

            if (self.isValid() == true)
            {
              readLockerM.release();

              self.serviceInterrupt();

              self.serviceCancellation();

              readLockerM.acquire();
            }
          }
          else
          {
            readBlockTime = 0;

            commonLockerM.release();
          }
        }
        else
        {
          readBlockTime = 0;

          commonLockerM.release();
        }
      }
      while (readBlockTime > 0);
    }
  }
}

//======================================================================
// Write block wise
//======================================================================

template <class T>
bool STR::Queue<T>::writeBlocks(const T& val)
{
  D_ENTER("STR::Queue::writeBlocks()");

  commonLockerM.acquire();

  while (true)
  {
    if ((writeBufferM == 0) && (emptyBlocksM.entries() > 0))
    {
      writeBufferM = emptyBlocksM.removeFirst();
    }

    if (writeBufferM != 0)
    {
      writeBufferM->append(val);

      ++notTransferedM;

      if (writeBufferM->entries() == blockSizeM)
      {
        filledBlocksM.append(writeBufferM);

        writeBufferM = 0;

        if (waitingReaderM > 0)
        {
          cannotReadM.signal();
        }
      }

      commonLockerM.release();

      return true;
    }
    else
    {
      ++waitingWriterM;

      RWWaitStatus waitStatus = cannotWriteM.wait(queueBlockTimeM);

      --waitingWriterM;

      if (waitStatus == RW_THR_TIMEOUT)
      {
        RWThreadSelf self = ::rwThread();

        if ((self.isValid() == true) && (shutdownIsAbortM == true))
        {
          commonLockerM.release();

          self.serviceInterrupt();

          self.serviceCancellation();

          commonLockerM.acquire();
        } 
      }
    }
  }
}

//======================================================================
// Write Array element
//======================================================================
template <class T>
bool STR::Queue<T>::writeArray(const T& val, bool block)
{
  D_ENTER("STR::Queue::writeArray()");
  unsigned int lTail = 0;
  T lVal ;

  // Spin count
  u_int32 sCount = 0;
  // Yield count
  u_int32 yCount = 0;


  while (1)
  {
    if (yieldCountM == yCount)
    {
      // reset yield count
      yCount = 0;
      rwSleep(sleepTimeMilliSecM);
    }

    // Let it spin for spinCountM
    if (spinCountM == sCount )
    {
      // reset spin count
      sCount = 0;
      // increment yield count
      yCount++;

      sched_yield();
    }

    sCount++;

    /* Store local copy of tail */
    lTail = tailM;

    /* Read the value of tail node */
    lVal = arrayQueueM[lTail%sizeM].val;

    /* Check for consistency */
    if (lTail != tailM)
      continue;

    /* Queue is full */
    if (lTail == headM + sizeM)
    {
      /* 
       * Self check for exit 
       * because if we don't check here 
       * we can't ever come out of this loop
       * as a result of that pipeline can't be 
       * stopped gracefully.
       */
      RWThreadSelf self = ::rwThread();

      if (self.isValid() == true)
      {
        self.serviceInterrupt();

        self.serviceCancellation();
      }
      else 
      {
        return false;
      }

      continue;
    }

    /* Check if the node is free */
   if (lVal == NULL)
   {
    /* CAS(location, current_val, new_val)
     * CAS returns the previous value.
     * Check if the return val matches with current_val
     * if it is so, then the swap was successful
     * else there was already a data in the and advance the
     * the tail.
     */
     if (((arrayQueueM[tailM%sizeM].val) == lVal) &&
         ((T)(CAS64((&(arrayQueueM[tailM%sizeM].val)), lVal, val)) == lVal))

     {
       /* increment the tail */
       CAS32(&tailM, lTail, lTail+1);
       //dumpArrayQueue("writer");
       return true;
     } 
   }
   else
   {
       /* increment the tail, help reader thread */
       CAS32(&tailM, lTail, lTail+1);
   }
  }
}

//======================================================================
// Read Array wise
//======================================================================
template <class T>
bool STR::Queue<T>::readArray(T& val, bool block)
{
  D_ENTER("STR::Queue::readArray()");

  unsigned int lHead = 0;
  T lVal ;

  // Spin count
  u_int32 sCount = 0;
  // Yield count
  u_int32 yCount = 0;


  while (1)
  {
    if (yieldCountM == yCount)
    {
      // reset yield count
      yCount = 0;
      rwSleep(sleepTimeMilliSecM);
    }

    // Let it spin for spinCountM
    if (spinCountM == sCount )
    {
      // reset spin count
      sCount = 0;
      // increment yield count
      yCount++;

      sched_yield();
    }

    sCount++;

    /* Store local copy of head */
    lHead = headM;

    /* Read the value of head node */
    lVal = arrayQueueM[lHead%sizeM].val;

    /* Check for consistency */
    if (lHead != headM)
      continue;

    /* Queue is empty */
    if (lHead == tailM )
	{
      /* 
       * Self check for exit 
       * because if we don't check here 
       * we can't ever come out of this loop
       * as a result of that pipeline can't be 
       * stopped gracefully.
       */
      RWThreadSelf self = ::rwThread();

      if (self.isValid() == true)
      {
        self.serviceInterrupt();

        self.serviceCancellation();
      }
      else 
      {
        return false;
      }

      continue;
	}

    /* Check if the node is occupied */
   if (lVal != NULL)
   {
    /* CAS(location, current_val, new_val)
     * CAS returns the previous value.
     * Check if the return val matches with current_val
     * if it is so, then the swap was successful
     * else there was already a data in the and advance the
     * the tail.
     */
     if ( (T)(CAS64(&(arrayQueueM[headM%sizeM].val), lVal, NULL)) == lVal)
     {
       /* increment the head */
       CAS32(&headM, lHead, lHead+1);
       val = lVal;
       //dumpArrayQueue("reader");
       return true;
     } 
   }
   else
   {
       /* increment the head, help writer thread */
       CAS32(&headM, lHead, lHead+1);
   }
  }
}
//======================================================================
// Dump queue contant
//======================================================================

template <class T>
void STR::Queue<T>::dumpArrayQueue(const BAS::String& name)
{
  D_ENTER("STR::Queue::dumpArrayQueue()");
  cerr<< "*** Queue Dump *** "<< name << endl;
  cerr<< "Queue head: "<<headM << ", Queue tail:  "<<tailM  <<endl;
  for (int i= 0; i < sizeM ; i++)
  {
	if (arrayQueueM[i].val != NULL )
	{
		cerr<<"Nodes["<<i<<"].val = "<<*(arrayQueueM[i].val);
		cerr<<", Nodes["<<i<<"].ref = "<<(arrayQueueM[i].ref)<<endl;
	}
  }

}

#endif
