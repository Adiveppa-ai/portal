
#ifndef BAS_SIMPLETPTRPAIR_HPP
#define BAS_SIMPLETPTRPAIR_HPP

//==============================================================================
//
// Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
// only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

namespace BAS
{

/*--------------------------------------------------------------------
 *  SimpleTPtrPair which provides destruction of pair pointer objects
 *--------------------------------------------------------------------*/
template <class T1, class T2>
class SimpleTPtrPair
{
  public:
    /**
     * Contructor creates pointer pair.
     * @param first pair pointer item.
     * @param second pair pointer item.
     */
    SimpleTPtrPair(T1* first, T2* second);

    /**
     *  Destructor deletes both first and second pair pointers.
     */
    ~SimpleTPtrPair();

    /**
     * returns pointer to the first pair item
     * @return first pair item pointer
     */
    T1* first() const;

    /**
     * returns pointer to the second pair item
     * @return second pair item pointer
     */
    T2* second() const;

    /**
     * reassigns the pointer to the first pair item
     * @param value new first pair item pointer
     */
    void first(T1* value);

    /**
     * reassigns the pointer to the second pair item
     * @param value new second pair item pointer
     */
    void second(T2* value);


    /**
     * less-than operator compares the first item in the pair.
     * @param rhs the right-hand-side of the compare operation.
     */
    bool operator< (const SimpleTPtrPair<T1, T2>& rhs) const;

  private:
    // off limits
    SimpleTPtrPair();
    SimpleTPtrPair(const SimpleTPtrPair& copy);
    SimpleTPtrPair& operator=(const SimpleTPtrPair& rhs);

  private:
    T1* firstM;
    T2* secondM;

};

//------------------------------------------------------------------------------

template <class T1, class T2>
SimpleTPtrPair<T1, T2>::SimpleTPtrPair(T1* first, T2* second)
  : firstM(first),
    secondM(second)
{
  D_ENTER("SimpleTPtrPair<T1, T2>::SimpleTPtrPair(T1* first, T2* second)");
}

//------------------------------------------------------------------------------

template <class T1, class T2>
SimpleTPtrPair<T1, T2>::~SimpleTPtrPair()
{
  D_ENTER("SimpleTPtrPair<T1, T2>::~SimpleTPtrPair()");

  delete firstM; firstM= 0;
  delete secondM; secondM= 0;
}

//------------------------------------------------------------------------------

template <class T1, class T2>
inline
void
SimpleTPtrPair<T1, T2>::first(T1* value)
{
  D_ENTER("SimpleTPtrPair<T1, T2>::first(T1* value)");

  firstM=value;
}

//------------------------------------------------------------------------------

template <class T1, class T2>
inline
void
SimpleTPtrPair<T1, T2>::second(T2* value)
{
  D_ENTER("SimpleTPtrPair<T1, T2>::first(T2* value)");

  secondM=value;
}

//------------------------------------------------------------------------------

template <class T1, class T2>
inline
T1*
SimpleTPtrPair<T1, T2>::first() const
{
  D_ENTER("SimpleTPtrPair<T1, T2>::first() const");

  return firstM;
}

//------------------------------------------------------------------------------

template <class T1, class T2>
inline
T2*
SimpleTPtrPair<T1, T2>::second() const
{
  D_ENTER("SimpleTPtrPair<T1, T2>::second() const");

  return secondM;
}

//------------------------------------------------------------------------------

template <class T1, class T2>
inline
bool
SimpleTPtrPair<T1, T2>::operator< (const SimpleTPtrPair<T1, T2>& rhs) const
{
  D_ENTER("SimpleTPtrPair<T1, T2>::operator< ("
          "const SimpleTPtrPair<T1, T2>& rhs) const");

  if (firstM && rhs.firstM)
  {
    return (*firstM < *rhs.firstM); 
  }
  return false;
}

//------------------------------------------------------------------------------

}

#endif // BAS_SIMPLETPTRPAIR_HPP
