#ifndef PBC_PTRTREENODE_CPP
#define PBC_PTRTREENODE_CPP

//==============================================================================
//
// 1998,1999,2000                                 (c) Copyright by SOLUTION42 AG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description
//    This class represents the tree node for the PlugIn data trees.
//    The node is implemented as a template class to any kind of value.
//    Because of the storage management, the template type must be a
//    reference type. No pointer allowed.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Peter Engelbrecht
//
// $RCSfile: PBC::PtrTreeNode.cpp,v $
// $Revision: 1.7 $
// $Author: pengelbr $
// $Date: 2002/01/16 09:52:45 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PBC::PtrTreeNode.cpp,v $
// Revision 1.7  2002/01/16 09:52:45  pengelbr
// PETS #42843 Move treeNode function into header as inline.
//
// Revision 1.6  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.5  2000/06/17 07:51:11  clohmann
// Changes for AIX compiler.
//
// Revision 1.4  2000/02/11 09:15:21  pengelbr
// Make search-methods const.
// Replace RWCString with BAS::String and RWBoolean with bool.
//
// Revision 1.3  1999/06/08 09:20:04  pengelbr
// Rename PIM to PBC.
//
// Revision 1.2  1999/06/07 12:08:13  aro
// Module PIM_Base renamed to PBC (Plugin Base Classes).
//
// Revision 1.1  1999/05/07 12:53:32  pengelbr
// Renamed PBC::Tree/PBC::TreeNode to PBC::ValTree/PBC::ValTreeNode.
// Added PBC::PtrTree/PBC::PtrTreeNode as pointer based tree collection.
//
// Revision 1.1  1999/04/15 08:21:22  pengelbr
// initial import
//
//==============================================================================

/* -- rcsid() does not work for this class, because the template is included in headers
*/

//------------------------------------------------------------------------------

#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   PBC_PTRTREENODE_HPP
  #include "PBC/PtrTreeNode.hpp"
#endif

//------------------------------------------------------------------------------

// Initialisierer
template<class T> int64 PBC::PtrTreeNode<T>::nodeCountM = 0;

//----------------------------------------------------------------------------
//
// Constructor
//
//----------------------------------------------------------------------------
template<class T>
PBC::PtrTreeNode<T>::PtrTreeNode(T* val, int base)
{
  D_ENTER("PBC::PtrTreeNode<T>::PtrTreeNode(T*, size_t)");

  baseM = base;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  valueM   = val;
  validM  = true;

  nodeCountM++;
}

template<class T>
PBC::PtrTreeNode<T>::PtrTreeNode(int base)
{
  D_ENTER("PBC::PtrTreeNode<T>::PtrTreeNode(T*, size_t)");

  baseM = base;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  valueM   = 0;
  validM  = false;

  nodeCountM++;
}

template<class T>
PBC::PtrTreeNode<T>::PtrTreeNode(T* val)
{
  D_ENTER("PBC::PtrTreeNode<T>::PtrTreeNode(T*)");

  baseM = 10;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  valueM   = val;
  validM  = true;

  nodeCountM++;
}

template<class T>
PBC::PtrTreeNode<T>::PtrTreeNode()
{
  D_ENTER("PBC::PtrTreeNode<T>::PtrTreeNode()");

  baseM = 10;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  validM  = false;
  valueM = 0;

  nodeCountM++;
}

//----------------------------------------------------------------------------
//
// Destructor
//
//----------------------------------------------------------------------------
template<class T>
PBC::PtrTreeNode<T>::~PtrTreeNode()
{
  D_ENTER("PBC::PtrTreeNode<T>::~PtrTreeNode()");

  nodeCountM--;

  for(int i=0; i<treeNodeM.length(); ++i) 
  {
    delete treeNodeM(i);
  }

  if(subTreeM != 0)
  {
    delete subTreeM;
    subTreeM = 0;
  }

  if(valueM != 0)
  {
    delete valueM;
    valueM = 0;
  }
};

//-----------------------------------------------------------------------------
//
// Funktion: grow
//
//-----------------------------------------------------------------------------
template<class T>
PBC::PtrTreeNode<T>*
PBC::PtrTreeNode<T>::grow(int i)
{
  D_ENTER("PBC::PtrTreeNode<T> *PBC::PtrTreeNode<T>::grow(int)");

  if( i>= 0 && i <= baseM-1)
  {
    if(treeNodeM(i) == 0)
    {
      treeNodeM(i) = new PBC::PtrTreeNode<T>(baseM);
      return treeNodeM(i);
    }
  }

  return 0;
};

#endif
