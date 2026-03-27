#ifndef BAS_COLLECTION_CPP
#define BAS_COLLECTION_CPP
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
// $RCSfile: Collection.cpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:43:28 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Collection.cpp,v $
// Revision 1.21  2000/09/22 06:40:45  aro
// selfTest() method removed for AIX - see comment.
//
// Revision 1.20  2000/06/27 09:18:21  aro
// Syntax error fixed.
//
// Revision 1.19  2000/06/20 15:32:29  sd
// - Constants are definded extern in header files and declared
//   int cpp file.
//
// Revision 1.18  2000/06/15 12:17:52  bt
// Changes for AIX xlC V366.
//
// Revision 1.17  1999/12/07 08:02:34  sd
// Implementation changed to support the HP aCC compiler.
//
// Revision 1.16  1999/07/27 15:13:28  aro
// Small fix.
//
// Revision 1.15  1999/04/21 11:09:23  arockel
// Collectio::clear() added.
//
// Revision 1.8  1999/03/24 08:40:19  arockel
// RegisteredObject: status(err) renamed to setStatus(); minor improvements in others.
//
// Revision 1.7  1999/03/23 08:44:22  arockel
// Collection operators enhanced; self test methods enhanced.
//
// Revision 1.6  1999/03/22 13:01:23  arockel
// Registry syntax fixed.
//
//==============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef COLLECTION_HPP
  #include "BAS/Collection.hpp"
#endif

//------------------------------------------------------------------------------

template <class T>
BAS::Collection<T>::Collection()
{
  D_ENTER("BAS::Collection<T>::Collection()");
}

//------------------------------------------------------------------------------

template <class T>
BAS::Collection<T>::Collection(const String& name)
                  :RegisteredObject(name)
{
  D_ENTER("BAS::Collection<T>::Collection(const String& name)");
}

//------------------------------------------------------------------------------

template <class T>
BAS::Collection<T>::~Collection()
{
  D_ENTER("BAS::Collection<T>::~Collection()");
}

//------------------------------------------------------------------------------

template <class T> bool 
BAS::Collection<T>::append(T* val)
{
  D_ENTER("BAS::Collection<T>::append(T* val)");
  
  if (val)
  {
    D_PRINT("Item appended.");
    vectorM.append(val);
    return true;
  }
  else
  {
    D_PRINT("Try to insert 0 pointer");
    return false;
  }
}

//------------------------------------------------------------------------------

template <class T> bool 
BAS::Collection<T>::remove(const String& id)
{
  D_ENTER("BAS::Collection<T>::remove(const String& id)");

   size_t pos = index(id);

   if (pos != RW_NPOS)
   {
     vectorM.removeAt(pos);
     return true;
   }
   else
   {
     return false;
   }
}

//------------------------------------------------------------------------------

template <class T> bool 
BAS::Collection<T>::remove(size_t index)
{
  D_ENTER("BAS::Collection<T>::remove(size_t index)");

  if (index < entries())
  {
    vectorM.removeAt(index);
    return true;
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------

template <class T> size_t 
BAS::Collection<T>::index(const String& id) const
{
  D_ENTER("BAS::Collection<T>::index(const String& id) const");
  D_ARG(id);

  String completeName;
  String dirName = RegisteredObject::dirName(id);

  // The name to be searched has to start with the name of the 
  // collection. If this is not the case, force it.
  if (dirName == name())
  {
    completeName = id;
    D_PRINT("Id does contain collection name, using it as it is: " << completeName);
  }
  else
  {
    completeName = RegisteredObject::name() + "." + id; 
    D_PRINT("Id does not contain collection name, prepending: " << completeName); 
  }

  size_t ret = RW_NPOS;
 
  for (size_t i = 0; i < entries(); i++)
  {
     if (vectorM[i]->name() == completeName)
     {
        ret = i;
        break;
     }
  }

  return ret;            
}

//------------------------------------------------------------------------------

template <class T> bool 
BAS::Collection<T>::contains(const String& id) const
{
  D_ENTER("BAS::Collection<T>contains(const String& id) const");
  D_ARG(id);

  bool                          ret = false;

  typename Collection<T>::ConstIterator it = iterator();

  while (it != end())
  {
    if ((*it)->name() == id)
    {
      ret = true;
      break;
    }

    it++;
  } 

  return ret;
}

//------------------------------------------------------------------------------

template <class T> bool 
BAS::Collection<T>::selfTest()
{
  D_ENTER_F("BAS::Collection::selfTest()");

  cout << endl << "Collection self test." << endl;

  Collection<T> aCollection("col");
  T*  aT = new T("col.paul");

  if (aCollection.contains("col.paul"))
  {
    cout << "Paul found." << endl;
  }
  else
  {
    cout << "Paul NOT found." << endl;
  }

  aCollection.append(aT);

  if (aCollection.contains("col.paul"))
  {
    cout << "Paul found." << endl;
  }
  else
  {
    cout << "Paul NOT found." << endl;
  }

  size_t pos = aCollection.index("paul");
  size_t num = aCollection.entries();

  if (pos == RW_NPOS)
  {
    cout << "Collection self test FAILED." << endl;
    return false;
  }

  cout << aCollection[pos]->name() << endl;

  T* anotherT = 0;

  if ((anotherT = aCollection["paul"]) == 0)
  {
    cout << "Collection self test FAILED." << endl;
    return false;
  }
  else
  {
    cout << anotherT->name() << endl;
  }

  cout << "Collection self test PASSED." << endl;
  return true;
}

//------------------------------------------------------------------------------

template <class T> const T* 
BAS::Collection<T>::operator[](const String& id) const
{
  D_ENTER("BAS::Collection<T>::operator[](const String& id) const");
  D_ARG(id);

  size_t pos = index(id);

  if (pos != RW_NPOS)
  {
    return vectorM[pos].get();
  }
  else
  {
    return 0;
  }                   
}

//------------------------------------------------------------------------------  

template <class T> T* 
BAS::Collection<T>::operator[](const String& id)
{
  D_ENTER("BAS::Collection<T>::operator[](const String& id) const");
  D_ARG(id);

  size_t pos = index(id);

  if (pos != RW_NPOS)
  {
    return vectorM[pos].get();
  }
  else
  {
    return 0;
  }
}

//------------------------------------------------------------------------------

#endif
