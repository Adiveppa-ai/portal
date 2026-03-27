#ifndef PBC_PTRTREENODE_HPP
#define PBC_PTRTREENODE_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
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
// $RCSfile: PtrTreeNode.hpp,v $
// $Revision: 1.9 $
// $Author: pengelbr $
// $Date: 2002/01/16 09:52:45 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PtrTreeNode.hpp,v $
// Revision 1.9  2002/01/16 09:52:45  pengelbr
// PETS #42843 Move treeNode function into header as inline.
//
// Revision 1.8  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.7  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.6  2000/06/17 07:51:11  clohmann
// Changes for AIX compiler.
//
// Revision 1.5  2000/02/11 09:15:21  pengelbr
// Make search-methods const.
// Replace RWCString with BAS::String and RWBoolean with bool.
//
// Revision 1.4  1999/06/09 12:16:26  pengelbr
// Create doc++ documentation.
//
// Revision 1.3  1999/06/08 09:20:04  pengelbr
// Rename PIM to PBC.
//
// Revision 1.2  1999/06/07 12:08:13  aro
// Module PIM_Base renamed to PBC (Plugin Base Classes).
//
// Revision 1.1  1999/05/07 12:53:32  pengelbr
// Renamed Tree/TreeNode to ValTree/ValTreeNode.
// Added PtrTree/PtrTreeNode as pointer based tree collection.
//
//==============================================================================

//------------------------------------------------------------------------------

#if !defined PBC_EXPORT
  #if defined(WINDOWS)
    #if !defined(PBC_INTERNAL)
      #define PBC_EXPORT __declspec(dllimport)
    #else
      #define PBC_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PBC_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TPVECTOR_H
  #include <rw/tpvector.h>
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

//------------------------------------------------------------------------------
namespace PBC
{
/** <tt><b>PtrTreeNode</b></tt>.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: PtrTreeNode.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.9 $</font></td>
    <td><font size=-1>$Date: 2002/01/16 09:52:45 $</font></td>
    <td><font size=-1>$Author: pengelbr $</font></td>
    </tr>
    </table>

    <p>This class represents the tree node for the PlugIn data trees.
    The node is implemented as a template class to any kind of value.

<dl>
   <dt><b>Registry entries</b></dt>
        <dd>none</dd>
   <dt><b>Messages send</b></dt>
        <dd>none</dd>
   <dt><b>Messages receive</b></dt>
        <dd>none</dd>
   <dt><b>Errors</b></dt>
        <dd>none</dd>
</dl>
*/
template <class T> class PtrTreeNode D_THREADINFO
{
  D_NONTHREADSAFE
  public:

    static int64 nodeCountM;

//----------------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------------
    PtrTreeNode(T* val);
    PtrTreeNode(T* val, int base);
    PtrTreeNode(int base);
    PtrTreeNode();
    virtual ~PtrTreeNode();

    PtrTreeNode<T> *treeNode(int i);
    PtrTreeNode<T> *grow(int i);
    PtrTreeNode<T> *subTree(void);
    PtrTreeNode<T> *newSubTree(void);

    void subTree(PtrTreeNode<T> *s);

    T* value(void);
    void value(T* val);

    void valid(bool val);
    bool isValid();

    int64 nodeCount(void);


  private:

    RWTPtrVector< PtrTreeNode<T> > treeNodeM;
    PtrTreeNode<T>                 *subTreeM;
    bool                               validM;
    T*                                 valueM;
    size_t                             baseM;

//----------------------------------------------------------------------------------
// not implemented
//----------------------------------------------------------------------------------
    void operator=(PtrTreeNode<T> &parm);
    PtrTreeNode(PtrTreeNode<T> &copy);

};

//-----------------------------------------------------------------------------
//
// Funktion: getSubTree
//
//-----------------------------------------------------------------------------
template<class T>
inline
PtrTreeNode<T>*
PtrTreeNode<T>::subTree(void)
{
  return subTreeM;
}

//-----------------------------------------------------------------------------
//
// Funktion: newSubTree
//
//-----------------------------------------------------------------------------
template<class T>
inline
PtrTreeNode<T>*
PtrTreeNode<T>::newSubTree(void)
{
  subTreeM = new PtrTreeNode<T>(baseM);

  return subTreeM;
}

//-----------------------------------------------------------------------------
//
// Funktion: setSubTree
//
//-----------------------------------------------------------------------------
template<class T>
inline
void
PtrTreeNode<T>::subTree(PtrTreeNode<T> *s)
{
  subTreeM = s;
}

//-----------------------------------------------------------------------------
//
// Funktion: getValue
//
//-----------------------------------------------------------------------------
template<class T>
inline
T*
PtrTreeNode<T>::value()
{
  return valueM;
}

//-----------------------------------------------------------------------------
//
// Funktion: setValue
//
//-----------------------------------------------------------------------------
template<class T>
inline
void
PtrTreeNode<T>::value(T* val)
{
  valueM  = val;
  validM = true;
}

//-----------------------------------------------------------------------------
//
// Funktion: getNodeCount
//
//-----------------------------------------------------------------------------
template<class T>
inline
int64
PtrTreeNode<T>::nodeCount()
{
  return nodeCountM;
}

//-----------------------------------------------------------------------------
//
// Funktion: setValid
//
//-----------------------------------------------------------------------------
template <class T>
inline
void
PtrTreeNode<T>::valid(bool val)
{
  validM = val;
}

//-----------------------------------------------------------------------------
//
// Funktion: getNodeCount
//
//-----------------------------------------------------------------------------
template <class T>
inline
bool
PtrTreeNode<T>::isValid()
{
  return validM;
}

//-----------------------------------------------------------------------------
//
// Funktion: getTreeNode
//
//-----------------------------------------------------------------------------
template<class T>
inline
PtrTreeNode<T>*
PtrTreeNode<T>::treeNode(int i)
{
  if(i > -1 && i < baseM)
    return treeNodeM(i);
  else
    return 0;
}
} // end namespace PBC
#ifdef INC_TEMPL_DEFS
#include "PBC/PtrTreeNode.cpp"
#endif

#endif
