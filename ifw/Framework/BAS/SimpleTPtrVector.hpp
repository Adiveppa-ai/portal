
#ifndef BAS_SIMPLETPTRVECTOR_HPP
#define BAS_SIMPLETPTRVECTOR_HPP

//==============================================================================
//
// Copyright (c) 2004, 2023, Oracle and/or its affiliates. 
// This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
// only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------

#ifndef RW_TOOLS_TPVECTOR_H
  #include <rw/tpvector.h>
#endif
#ifndef RW_TOOLS_ERR_H
  #include <rw/rwerr.h>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

namespace BAS
{

/*--------------------------------------------------------------------
 *  SimpleTPtrVector contains a RWTPtrVector which provides extended 
 *  functionality for the addition and deletion of pointer values into 
 *  an exact size vector.
 *--------------------------------------------------------------------*/
template <class T>
class SimpleTPtrVector
{
  public:
    /**
     *  The default contructor created an empty vector of zero size.
     */
    SimpleTPtrVector();

    /**
     * This contructor creates a vector of the specified size and items 
     * are intialized to NULL.
     * @param size size of vector at creation time. 
                   All vector items are initialized to NULL.
     */
    SimpleTPtrVector(size_t size);

    /**
     * Adds a new array item to the end of the vector. Vector
     * nows owns the storage for the item.
     * Increases exact vector size by one.
     * @param item item to be appended.
     */
    void adoptItem( T* item);

    /**
     * Adds a new array item at the specified position. 
     * Trailing items shift one place to the right.
     * Increases exact vector size by one.
     * @param pos position to place new item.
     * @param item item to be adopted.
     */
    void adoptItemAt(size_t pos, T* item);

    /**
     *  Deletes an item at a given position from the vector.  All remaining items
     *  are shifted down one spot. Bounds checking is performed and RWBoundsErr
     *  may be thrown.
     * @param pos pos of item to be deleted.
     */
    void deleteItem(size_t pos);

    /**
     * removes an item from the vector and shifts all remaining item down one spot.
     * Ownership of the returned vector item is now transferred to the caller. 
     * The vector is then resized to the exact size of the remaining elements.
     * Bounds checking is performed and RWBoundsErr may be thrown.
     * @param pos position of the item to be removed.
     * @return pointer to the removed item, the caller now owns storage of this removed item.
     */
    T*   orphanItem(size_t pos);

    /**
     * used to test for equality based containment
     * @return true if there exists an element "t" such that (*t == *item)
     */
    bool contains(const T* item) const;

    /**
     * destructs and removes all vector items and resizes the vector to zero.
     */
    void clearAndDestroy();

    /**
     * resizes the vector according to RogueWave RWTPtrVector::resize().
     * @param size new vector size.
     */
    void resize(size_t size);

    /**
     * gets the current length of the vector.
     * @return vector length
     */
    size_t length() const;

    /**
     * index operator used to get the ith value of the vector. 
     * Bounds checking is performed.
     * @return ith value of the vector
     */
    T*  operator[](size_t i) const;

    /**
     * index operator used to get the ith value of the vector which 
     * can be assigned into. Bounds checking is performed.
     *
     * @return ith value of the vector
     */
    T*&  operator[](size_t i);

    /**
     * index operator used to get the ith value of the vector. 
     * No Bounds checking is performed.
     * @return ith value of the vector
     */
    T*  operator()(size_t i) const;

    /**
     * index operator used to get the ith value of the vector which 
     * can be assigned into. No Bounds checking is performed.
     *
     * @return ith value of the vector
     */
    T*&  operator()(size_t i);

  private:
    // off limits
    SimpleTPtrVector(const SimpleTPtrVector& copy);
    SimpleTPtrVector& operator=(const SimpleTPtrVector& rhs); 

  private:
    RWTPtrVector<T> vectorM;


};

//------------------------------------------------------------------------------
// Constructor

template <class T>
SimpleTPtrVector<T>::SimpleTPtrVector(size_t size)
  : vectorM(size, 0)
{
  D_ENTER("BAS::SimpleTPtrVector<T>::SimpleTPtrVector(size_t size)");
}

//------------------------------------------------------------------------------

// Constructor
template <class T>
SimpleTPtrVector<T>::SimpleTPtrVector()
  : vectorM()
{
  D_ENTER("BAS::SimpleTPtrVector<T>::SimpleTPtrVector()");
}

//------------------------------------------------------------------------------

// Smart delete function
template <class T>
inline void
SimpleTPtrVector<T>::deleteItem(size_t pos)
{
  D_ENTER("BAS::SimpleTPtrVector<T>::deleteItem(size_t pos)");

  T* item= orphanItem(pos);
  delete item;
}

//------------------------------------------------------------------------------

// Smart remove function
template <class T>
T*
SimpleTPtrVector<T>::orphanItem(size_t pos)
{
  D_ENTER("BAS::SimpleTPtrVector<T>::orphanItem(size_t pos)");

  T* result= 0;

  // original length
  size_t len= vectorM.length();

  // Is position in range
  if ((pos < 0) || (len == 0) || (pos > len-1))
  {
    throw RWBoundsErr("SimpleTPtrVector::orphanItem() index out of bounds!");
  }
  else
  {
    // get the item at the requested position
    result= vectorM(pos);

    // set position to NULL
    vectorM(pos)= 0;

    // shift succeeding elements down one position
    for (size_t i=pos; i<len-1; i++)
    {
      vectorM(i)= vectorM(i+1);
    }

    // resize to new length
    vectorM.resize(len-1);
  }

  return result;

}

//------------------------------------------------------------------------------

// Smart append function
template <class T>
void
SimpleTPtrVector<T>::adoptItem(T* item)
{
  D_ENTER("BAS::SimpleTPtrVector<T>::adoptItem(T* item)");

  // current length
  size_t len= vectorM.length();

  // increase length by 1
  vectorM.resize(len+1);

  // append new item on end
  vectorM(len)= item;
}

//------------------------------------------------------------------------------

// Placement insert function
template <class T>
void
SimpleTPtrVector<T>::adoptItemAt(size_t pos, T* item)
{
  D_ENTER("SimpleTPtrVector<T>::adoptItemAt(T* item)");

  // original length
  size_t len= vectorM.length();

  // Is position in range
  if ( (pos < 0) || (pos > len) )
  {
    throw RWBoundsErr("SimpleTPtrVector<T>::adoptItemAt() index out of bounds!");
  }
  else
  {
    // increase length by 1
    vectorM.resize(len+1);

    // shift succeeding elements down one position
    for (size_t i = vectorM.length() - 1; (i>pos) && (i>0) ; i--)
    {
      vectorM(i)= vectorM(i-1);
    }
    // place item at new position
    vectorM(pos)= item;
  }
}

//------------------------------------------------------------------------------

// clear and destroy function
template <class T>
void
SimpleTPtrVector<T>::clearAndDestroy()
{
  D_ENTER("BAS::SimpleTPtrVector<T>::clearAndDestroy()");

  // current length
  size_t len= vectorM.length();

  // delete all elements
  for (size_t i=0; i<len; i++)
  {
    delete vectorM(i);
    vectorM(i) = 0;
  }

  // resize to empty
  vectorM.resize(0);
}

//------------------------------------------------------------------------------

template <class T>
inline size_t
SimpleTPtrVector<T>::length() const
{
  D_ENTER("BAS::SimpleTPtrVector::length() const");

  return vectorM.length();
}

//------------------------------------------------------------------------------

template <class T>
inline void 
SimpleTPtrVector<T>::resize(size_t size)
{
  D_ENTER("BAS::SimpleTPtrVector::resize(size_t size)");

  vectorM.resize(size);
}

//------------------------------------------------------------------------------

template <class T>
inline bool
SimpleTPtrVector<T>::contains(const T* item) const
{
  D_ENTER("SimpleTPtrVector<T>::contains(const T* item) const");

  // test for NULL input parameter
  if (0==item)
  {
    return false;
  }

  // begin search for item
  size_t len= vectorM.length();
  const T* vectorItem=0;
  for (size_t i=0; i<len; i++)
  {
    vectorItem= vectorM(i);
    if (vectorItem && (*vectorItem == *item) )
    {
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------

template <class T>
inline T*
SimpleTPtrVector<T>::operator[](size_t i) const
{
  D_ENTER("BAS::SimpleTPtrVector::operator[](size_t i) const");

  return vectorM[i];
}

//------------------------------------------------------------------------------

template <class T>
inline T*&
SimpleTPtrVector<T>::operator[](size_t i)
{
  D_ENTER("BAS::SimpleTPtrVector::operator[](size_t i)");

  return vectorM[i];
}

//------------------------------------------------------------------------------

template <class T>
inline T*
SimpleTPtrVector<T>::operator()(size_t i) const
{
  D_ENTER("BAS::SimpleTPtrVector::operator()(size_t i) const");

  return vectorM(i);
}

//------------------------------------------------------------------------------

template <class T>
inline T*&
SimpleTPtrVector<T>::operator()(size_t i)
{
  D_ENTER("BAS::SimpleTPtrVector::operator()(size_t i)");

  return vectorM(i);
}

//------------------------------------------------------------------------------

}

#endif // BAS_SIMPLETPTRVECTOR_HPP
