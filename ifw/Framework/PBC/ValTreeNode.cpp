#ifndef PBC_VALTREENODE_CPP
#define PBC_VALTREENODE_CPP

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
// $RCSfile: ValTreeNode.cpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: nishanku $
// $Date: 2010/12/01 03:55:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PBC::ValTreeNode.cpp,v $
// Revision 1.6  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.5  2000/06/16 15:00:04  clohmann
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
// Revision 1.1  1999/05/07 12:53:36  pengelbr
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
#ifndef   PBC_VALTREENODE_HPP
  #include "PBC/ValTreeNode.hpp"
#endif

//------------------------------------------------------------------------------

// Initialisierer
template<class T> int64 PBC::ValTreeNode<T>::nodeCountM = 0;

//----------------------------------------------------------------------------
//
// Constructor
//
//----------------------------------------------------------------------------
template<class T> PBC::ValTreeNode<T>::ValTreeNode(T &val)
{
  D_ENTER( "PBC::ValTreeNode<T>::ValTreeNode(T&)" );

  baseM = 10;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  valueM = val;
  validM = true;

  nodeCountM++;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
template<class T> PBC::ValTreeNode<T>::ValTreeNode(T &val, int base)
{
  D_ENTER( "PBC::ValTreeNode<T>::ValTreeNode(T&, int)" );

  baseM = base;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  valueM = val;
  validM = true;

  nodeCountM++;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
template<class T> PBC::ValTreeNode<T>::ValTreeNode()
{
  D_ENTER( "PBC::ValTreeNode<T>::ValTreeNode()" );

  baseM = 10;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  validM  = false;

  nodeCountM++;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
template<class T> PBC::ValTreeNode<T>::ValTreeNode(int base)
{
  D_ENTER( "PBC::ValTreeNode<T>::ValTreeNode(int base)" );

  baseM = base;

  treeNodeM.reshape( baseM );

  for ( int i = 0 ; i < baseM ; i++ )
  {
    treeNodeM(i) = 0;
  }

  subTreeM = 0;
  validM  = false;

  nodeCountM++;
}

//----------------------------------------------------------------------------
//
// Destructor
//
//----------------------------------------------------------------------------
template<class T> PBC::ValTreeNode<T>::~ValTreeNode()
{
  D_ENTER( "PBC::ValTreeNode<T>::~ValTreeNode()" );

  nodeCountM--;

  for( int i=0; i< treeNodeM.length();i++)
  {
    if(treeNodeM(i) != 0)
    {
      delete treeNodeM(i);
    }
  }

  if ( subTreeM )
  {
    delete subTreeM;
    subTreeM = 0;
  }
}

//-----------------------------------------------------------------------------
//
// Funktion: getTreeNode
//
//-----------------------------------------------------------------------------
template<class T> PBC::ValTreeNode<T> *PBC::ValTreeNode<T>::treeNode(int i)
{
  D_ENTER( "PBC::ValTreeNode<T> *PBC::ValTreeNode<T>::treeNode(int i)" );

  if(i >= 0 && i < baseM)
    return treeNodeM(i);
  else
    return 0;
};

//-----------------------------------------------------------------------------
//
// Funktion: grow
//
//-----------------------------------------------------------------------------
template<class T> PBC::ValTreeNode<T> *PBC::ValTreeNode<T>::grow(int i)
{
  D_ENTER( "PBC::ValTreeNode<T> *PBC::ValTreeNode<T>::grow(int)" );

  if ( i >= 0 && i < baseM )
  {
    if ( treeNodeM(i) == 0 )
    {
      treeNodeM(i) = new PBC::ValTreeNode<T>(baseM);
      return treeNodeM(i);
    }
  }

  return 0;
};

#endif
