#ifndef BAS_MEMORY_CONTAINER_HPP
#define BAS_MEMORY_CONTAINER_HPP

//==============================================================================
//
// Copyright (c) 2005, 2023, Oracle and/or its affiliates. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::Container
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::Container class
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Annama Ponnusamy
//
//==============================================================================

#ifndef BAS_MEMORY_VARIABLESIZEMEMMGR_HPP
  #include "BAS/VariableSizeMemoryManager.hpp"
#endif

namespace BAS
{

namespace Memory
{

template<class T>
class Container D_THREADINFO
{
  public:
   
    Container(size_t size);
    virtual ~Container();
    /** Set the size of the container
     *  @param capacity Number of element in the container
     *  @param BAS::Memory::VariableSizeMemoryManager*
     */
    void setSize(size_t capacity) ;

    /** Insert the value in the container
     *  @value the value to be inserted
     */
    void add(T value);

    /** Value to be inserted at specified location
     *  @param value The index at which the value has to inserted
     */
     const T& operator [] (size_t index) const;

     /** assignment operator
     *  @param source Container<T>
     */
     Container<T>& operator = (Container<T>& source);

    /** Number of entries in the self
     *  @param void
     *  @return int
     */
     int length() const;

    static BAS::Memory::VariableSizeMemoryManager* memMgrCM;

   private:
    size_t capacityM;
    size_t currIndexM;
    T* startAddressM;
};

template<class T>
Container<T>::Container(size_t size)
  : capacityM(0),
    startAddressM(0),
    currIndexM(0)
{
  D_ENTER("BAS::Memory::Container(size_t size)");
  if (size)
  {
    setSize(size);
  }
}

template<class T>
Container<T>::~Container()
{
  D_ENTER("BAS::Memory::Container<T>::~Container()");
  if (startAddressM)
  {
    size_t correctSize = 0;
    unsigned int expoVal = BAS::Memory::Container<T>::memMgrCM->expVal( (capacityM * sizeof(T)), correctSize);

    RWPRECONDITION(BAS::Memory::VariableSizeMemoryManager::lockPoolObjectM != 0);

    BAS::LockPoolLockGuard<BAS::LockPoolObject> guard(memMgrCM->startAdrs(), *BAS::Memory::VariableSizeMemoryManager::lockPoolObjectM);
    BAS::Memory::Container<T>::memMgrCM->freeBuddyBlock( startAddressM, expoVal ); 
     
    memMgrCM->decrTotalUsedObjectSize(correctSize);
  }
}

template<class T>
void Container<T>::setSize (size_t capacity)  
{
  D_ENTER("BAS::Memory::Container<T>::setSize (size_t capacity)");
  int64 memSize = sizeof(T)*capacity;
  size_t correctSize = 0;

  unsigned int expoVal = memMgrCM->expVal(memSize, correctSize);

  RWPRECONDITION(BAS::Memory::VariableSizeMemoryManager::lockPoolObjectM != 0);
  BAS::LockPoolLockGuard<BAS::LockPoolObject> guard(memMgrCM->startAdrs(), *BAS::Memory::VariableSizeMemoryManager::lockPoolObjectM);

  startAddressM = (T *)(memMgrCM->getBuddyBlock( expoVal ));
  
  if (!startAddressM)
  {    
    memMgrCM->activateThread();
    throw std::bad_alloc();
  }
  memMgrCM->incrTotalUsedObjectSize(correctSize);
  capacityM = correctSize / sizeof(T);
  currIndexM = 0;
}

template<class T>
const inline
T& Container<T>::operator [] (size_t index) const
{
  D_ENTER("BASS::Container<T>::operator [] (size_t index)");
  RWPRECONDITION(index < capacityM);
  RWPRECONDITION(startAddressM != 0);
  if (index >= capacityM)
  {
    throw "Out of bound error";
  }
  return *(startAddressM + index);
}

template<class T>
inline
void Container<T>::add(T value)
{
  D_ENTER("BAS::Memory::Container<T>::add(T value)");
  if (currIndexM  == capacityM)
  {
    T* startAdrs = startAddressM;
    size_t capacity = capacityM;

    setSize(capacity + 1);

    for (size_t i = 0; i < capacity; i++)
    {
      add ( *(startAdrs + i) );
    }

    size_t correctSize = 0;
    RWPRECONDITION(BAS::Memory::VariableSizeMemoryManager::lockPoolObjectM != 0);
    BAS::LockPoolLockGuard<BAS::LockPoolObject> guard(memMgrCM->startAdrs(), *BAS::Memory::VariableSizeMemoryManager::lockPoolObjectM);

    unsigned int expoVal = BAS::Memory::Container<T>::memMgrCM->expVal( capacity * sizeof(T), correctSize);
  
    memMgrCM->freeBuddyBlock( startAdrs, expoVal );
    memMgrCM->decrTotalUsedObjectSize(correctSize);
  }
  startAddressM[currIndexM] = value;
  currIndexM++;
  
}

template<class T>
inline
int Container<T>::length() const
{
  D_ENTER("BAS::Memory::Container<T>::length()");
  return currIndexM ;
}

template<class T>
inline
Container<T>& Container<T>::operator = (Container<T>& source)
{
  if (this == &source)
  {
    return *this;
  }    
  setSize(source.length());
  for (int i = 0; i < source.length(); i++)
  {
    startAddressM[currIndexM++] = source[i];
  }
  return *this;
}

} // end namespace Memory

} // end namespace BAS
#endif // CONTAINER_HPP
