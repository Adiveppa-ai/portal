#ifndef COLLECTION_HPP
#define COLLECTION_HPP
//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   ErrorStatus class implementation.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: aro
//
// $RCSfile: Collection.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:43:30 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Collection.h,v $
// Revision 1.26  2000/09/22 06:40:45  aro
// selfTest() method removed for AIX - see comment.
//
// Revision 1.25  1999/12/07 08:02:34  sd
// Implementation changed to support the HP aCC compiler.
//
// Revision 1.24  1999/11/10 09:04:33  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.23  1999/04/21 11:09:24  arockel
// Collectio::clear() added.
//
// Revision 1.17  1999/03/26 09:46:17  arockel
// Template definitions included in header.
//
// Revision 1.11  1999/03/23 08:44:23  arockel
// Collection operators enhanced; self test methods enhanced.
//
//==============================================================================

#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef ONLYPOINTER_HPP
  #include "BAS/OnlyPointer.hpp"
#endif
#ifndef BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif

// CodeReview - 10.1999 - clohmann - IP - The collection provides only the
// CodeReview - 10.1999 - []-operator of the RogueWave collection. For
// CodeReview - 10.1999 - performance it should also provides the ()-operator


/** <tt><b>Collection</b></tt> is the basic collection class.

     <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
     <tr>
     <td><font size=-1>$RCSfile: Collection.hpp $</font></td>
     <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
     <td><font size=-1>$Date: 2015/11/27 04:43:30 $</font></td>
     <td><font size=-1>$Author: nishahan $</font></td>
     </tr>
     </table>
                                                       
    <p>It maintains an ordered list of items of type <tt>T</tt>, where
    T has to be a subclass of <tt>RegisteredObject</tt>.

    The contained items can be accessed by the following two methods
    <ul>
      <li>by their registered name (found by linear search),
      <li>by index (direct access).
    </ul>

    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>none</dd>
        <dt><b>Messages send</b></dt>
        <dd>none</dd>
      <dt><b>Messages received</b></dt>
        <dd>none</dd>
      <dt><b>Errors</b></dt>
        <dd>none</dd>
    </dl> 
*/
namespace BAS {
template <class T> class Collection : public RegisteredObject
{
  public:
    typedef RWTValOrderedVector<OnlyPointer<T> > CollectionImpl;
    typedef typename RWTValOrderedVector<OnlyPointer<T> >::iterator Iterator;
    typedef typename CollectionImpl::const_iterator  ConstIterator;

    /** Collection default constructor.
    */
    Collection();

    /**  Collection standard constructor.
    */
    Collection(const String& name);

    /** Destructor.
    */
    virtual ~Collection();

    /** Appends an item to the collection.<br>
        Ownership is transferred to the collection.
        @param val Pointer to the item to be inserted.
        @return <tt>True</tt> apppend successful,<br>
                <tt>false</tt> try to insert 0 pointer.
    */
    bool append(T* val);

    /**
    */
    bool addBefore(const String& following, const T& val);

    /** Remove the item with the given id from the collection.
        @param id The identifier of the item to be removed.
        @return <tt>True</tt> remove successful,<br>
                <tt>false</tt> object to be removed not found.
    */
    bool remove(const String& id);

    /** Remove the item with the given index from the collection.
        @param id The index of the item to be removed.
        @return <tt>True</tt> remove successful,<br>
                <tt>false</tt> index out of range.
    */
    bool remove(size_t index);

    /** Check if an object is contained in the collection.
        @param id The identifier of the object to be found.
        @return <tt>True</tt> object contained,<br>
                <tt>false</tt> object not contained in the collection
    */
    bool contains(const String& id) const;

    /** Find the index of the object with the given id.
        @param id The identifier of the object to be found.
        @return The index of the desired object or <br>
                (<tt>RW_NOPOS</tt>) if not found.
    */
    size_t index(const String& id) const;

    /** Access by index.
        @param index Index of the desired item.
        @return Pointer to the item.
    */
    const T* operator[](size_t index) const;

    /** Access by index.
        @param index Index of the desired item.
        @return Pointer to the item.
    */
    T* operator[](size_t index);

   /** Access by name.
        @param id Name of the desired item.
        @return Pointer to the item,<br> 
        or 0 if not found.
    */
    const T* operator[](const String& id) const;

    /** Access by name.
        @param id Name of the desired item.
        @return Pointer to the item,<br> 
        or 0 if not found.
    */
    T* operator[](const String& id);              

    /** Number of contained entries.
        @return Number of entries.
    */
    size_t entries() const;

    /** Non-const iterator.
        @return An iterator for the embedded list.
    */
    Iterator iterator();

    /** Const iterator.
        @return An iterator for the embedded list.
    */
    ConstIterator iterator() const;

    /** Comparison iterator.
        @return An iterator for the embedded list which is 
        positioned at the end.
    */
    ConstIterator end() const;

    /** Clear method.
        Destroys all elements by calling their destructors. 
    */
    void clear();

    // This method lead to problems with the AIX compiler.
    // Because this compiler instatiates all the templates
    // the method instatiation will not work if the
    // template is used with abstract classes.
    /** Self test method.
        @return <tt>True</tt> self test passed,<br>
                <tt>false</tt> otherwise.
    */
    static bool selfTest();

  private:
    CollectionImpl vectorM;
};

//------------------------------------------------------------------------------
// Inlines 
//------------------------------------------------------------------------------

template <class T> inline const T*
Collection<T>::operator[](size_t index) const
{
  return vectorM[index].get();
}

//------------------------------------------------------------------------------

template <class T> inline T*
Collection<T>::operator[](size_t index) 
{
  return vectorM[index].get();
}

//------------------------------------------------------------------------------

template <class T> inline size_t
Collection<T>::entries() const
{
  return vectorM.length();
}

//------------------------------------------------------------------------------

template <class T> inline typename Collection<T>::Iterator
Collection<T>::iterator()
{
  return vectorM.begin();
}

//------------------------------------------------------------------------------

template <class T> inline typename Collection<T>::ConstIterator
Collection<T>::iterator() const   
{
  return vectorM.begin();
}

//------------------------------------------------------------------------------

template <class T> inline typename Collection<T>::ConstIterator
Collection<T>::end() const   
{
  return vectorM.end();
}

//------------------------------------------------------------------------------

template <class T> inline void
Collection<T>::clear() 
{
  vectorM.clear();
}
          
//------------------------------------------------------------------------------
}

#ifdef INC_TEMPL_DEFS
#include "BAS/Collection.cpp"
#endif

#endif // COLLECTION_HPP

