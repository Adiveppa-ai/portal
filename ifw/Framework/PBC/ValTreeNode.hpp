#ifndef PBC_VALTREENODE_HPP
#define PBC_VALTREENODE_HPP

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
// $RCSfile: ValTreeNode.hpp,v $
// $Revision: 1.8 $
// $Author: pengelbr $
// $Date: 2000/10/25 12:22:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ValTreeNode.hpp,v $
// Revision 1.8  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.7  2000/09/29 10:27:48  aro
// Tried to fix doc++ comments.
//
// Revision 1.6  2000/06/16 15:00:04  clohmann
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
// Revision 1.1  1999/05/07 12:53:36  pengelbr
// Renamed Tree/PIM_TreeNode to PIM_ValTree/PIM_ValTreeNode.
// Added PtrTree/PIM_PtrTreeNode as pointer based tree collection.
//
// Revision 1.3  1999/04/23 12:18:03  pengelbr
// PlugIn Definitions.
//
// Revision 1.1  1999/04/15 08:21:22  pengelbr
// initial import
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
/** <tt><b>ValTreeNode</b></tt>

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: ValTreeNode.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.8 $</font></td>
    <td><font size=-1>$Date: 2000/10/25 12:22:21 $</font></td>
    <td><font size=-1>$Author: pengelbr $</font></td>
    </tr>
    </table>

    <p>This class represents the tree node for the PlugIn data trees.
    The node is implemented as a template class to any kind of value.
    Because of the storage management, the template type must be a
    reference type. No pointer allowed.

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
template <class T> class ValTreeNode D_THREADINFO
{
  public:

    static int64 nodeCountM;

//----------------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------------
    ValTreeNode(T& val);
    ValTreeNode(T& val, int base);
    ValTreeNode();
    ValTreeNode(int base);
    virtual ~ValTreeNode();

    ValTreeNode<T> *treeNode(int i);
    ValTreeNode<T> *grow(int i);
    ValTreeNode<T> *subTree(void);
    ValTreeNode<T> *newSubTree(void);

    void subTree(ValTreeNode<T> *s);

    T& value(void);
    void value(T& val);

    void valid(bool val);
    bool isValid();

    int64 nodeCount(void);

  private:

    int                                baseM;
    RWTPtrVector< ValTreeNode<T> > treeNodeM;
    ValTreeNode<T>*                subTreeM;
    bool                               validM;
    T                                  valueM;

//----------------------------------------------------------------------------------
// not implemented
//----------------------------------------------------------------------------------
    void operator=(ValTreeNode<T> &parm);
    ValTreeNode(ValTreeNode<T> &copy);

};

//-----------------------------------------------------------------------------
//
// Funktion: getSubTree
//
//-----------------------------------------------------------------------------
template<class T>
inline
ValTreeNode<T>*
ValTreeNode<T>::subTree(void)
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
ValTreeNode<T>*
ValTreeNode<T>::newSubTree(void)
{
  subTreeM = new ValTreeNode<T>(baseM);

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
ValTreeNode<T>::subTree(ValTreeNode<T> *s)
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
T&
ValTreeNode<T>::value()
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
ValTreeNode<T>::value(T & val)
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
ValTreeNode<T>::nodeCount()
{
  return nodeCountM;
}

//-----------------------------------------------------------------------------
//
// Funktion: setValid
//
//-----------------------------------------------------------------------------
template<class T>
inline
void
ValTreeNode<T>::valid(bool val)
{
  validM = val;
}

//-----------------------------------------------------------------------------
//
// Funktion: getNodeCount
//
//-----------------------------------------------------------------------------
template<class T>
inline
bool
ValTreeNode<T>::isValid()
{
  return validM;
}
}
#ifdef INC_TEMPL_DEFS
#include "PBC/ValTreeNode.cpp"
#endif

#endif
