#ifndef ONLYPOINTER_HPP
#define ONLYPOINTER_HPP
//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//
//  Enhanced version of RogueWave's RWOnlyPointer.
//
//   --------------------------------------------------------------------------
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: arockel
//
// $RCSfile: OnlyPointer.hpp $
// $Revision: /cgbubrm_mainbrm.portalbase/1 $
// $Author: anirbisw $
// $Date: 2016/12/18 22:19:04 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OnlyPointer.hpp,v $
// Revision 1.18  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.17  2000/06/29 15:39:09  bt
// Changes for AIX xlC V500.
//
// Revision 1.16  2000/03/30 08:38:26  jkeckst
// add orphan methode
//
// Revision 1.15  1999/09/03 14:41:58  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
//
// Revision 1.14  1999/08/19 12:09:00  aro
// OnlyPointer<T>::operator T*(void) disabled.
//
// Revision 1.13  1999/05/12 08:05:18  aro
// Assigemnt operators fixed.
//
// Revision 1.3  1999/02/26 08:14:44  arockel
// get()-method added in OnlyPointer.
//
// Revision 1.2  1999/02/22 15:45:13  arockel
// OnlyPointer constructors added, trace in String added.
//
// Revision 1.1  1999/02/15 07:52:51  arockel
// OnlyPointer.hpp added.
//
//==============================================================================

#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

#ifndef BAS_DEFS_HPP
  #include "BAS/Defs.hpp"
#endif

/** <tt><b>OnlyPointer</b></tt> is the smart pointer class.
    It is derived from RogueWave's <tt>RWOnlyPointer</tt> and
    enhanced with the operator "<tt>-></tt>" and the method "<tt>get()</tt>".

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: OnlyPointer.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_mainbrm.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2016/12/18 22:19:04 $</font></td>
    <td><font size=-1>$Author: anirbisw $</font></td>
    </tr>
    </table>
                                     
    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>n/a
        <dt><b>Messages send</b></dt>
        <dd>n/a
      <dt><b>Messages received</b></dt>
        <dd>n/a
      <dt><b>Errors</b></dt>
        <dd>none
    </dl>                     
*/
//3rd party has been upgraded only for Linux and Sun.
//Please remove this once it is done for other OS.
   #include "rw_macros.hpp"

namespace BAS {
template <class T>
class OnlyPointer: public RWOnlyPointer<T>
{
  public:
    /** Constructor for static instances.
    */
    OnlyPointer(RWStaticCtor) ;

    /** Assume responsibility for a new body.
        @param bodyP A pointer to an instance of type T.
    */
    OnlyPointer(T* bodyP=rwnil) ;

    /** Assume responsibility for another handle's body.
        Even though we will orphan the body from second, we must
        declare second const to allow assignment from temporaries! 
        @param second The smart pointer to be copied.
    */
    OnlyPointer(const OnlyPointer<T>& second) ;

    /** Delete the current body
    */
#  if defined(RW_THR_INLINE_IN_DECLARATION)
    inline
#  endif
    ~OnlyPointer(void) ;
                                                        
    /** Assignment. Responsibility is transferred.
    */
    OnlyPointer<T>&
      operator=(const OnlyPointer<T>& second)
                          ;
    /** Assignment.
    */
    OnlyPointer<T>&
       operator=(T* ptr)  ;

    /** Convenience operator.
        @return The real instance pointer.
    */
    T* operator->() const ;

    /** Inherited get() made public.
        @return The real instance pointer.
    */
    T* get() const ; 
    
    /// .
    T* orphan() ; 

  private:
    /** Disallow the cast operator.
    */
    operator T*(void);
};

//------------------------------------------------------------------------------
// inlines
//------------------------------------------------------------------------------

template <class T>
inline
OnlyPointer<T>::OnlyPointer(RWStaticCtor) 
                   :RWOnlyPointer<T>(RW_STATIC_CTOR)
{
}

//------------------------------------------------------------------------------

template <class T>
inline
OnlyPointer<T>::OnlyPointer(T* bodyP) 
                   :RWOnlyPointer<T>(bodyP)
{
}

//------------------------------------------------------------------------------

template <class T>
inline
OnlyPointer<T>::OnlyPointer(const OnlyPointer<T>& second) 
                   :RWOnlyPointer<T>(second)
{
}

//------------------------------------------------------------------------------

template <class T>
inline
OnlyPointer<T>::~OnlyPointer(void) 
{
}

//------------------------------------------------------------------------------

template <class T>
inline
OnlyPointer<T>&
OnlyPointer<T>::operator=(const OnlyPointer<T>& second) 
{
   if (&second != this)
      RWOnlyPointer<T>::transfer(RWSTD_CONST_CAST(OnlyPointer<T>&, second).orphan());
   return *this;
}

//------------------------------------------------------------------------------

template <class T>
inline
OnlyPointer<T>&
OnlyPointer<T>::operator=(T* ptr) 
{
   RWOnlyPointer<T>::transfer(ptr);
   return *this;                        
}

//------------------------------------------------------------------------------

template <class T>
inline
T*
OnlyPointer<T>::operator->() const 
{
  return get();
}
			    
//------------------------------------------------------------------------------

template <class T>
inline
T*
OnlyPointer<T>::get() const 
{
  return RWOnlyPointer<T>::get();
}
			    
template <class T>
inline
T*
OnlyPointer<T>::orphan() 
{
  return RWOnlyPointer<T>::orphan();
}


//------------------------------------------------------------------------------
}
#endif  // ONLYPOINTER_HPP

