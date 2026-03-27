#ifndef PBC_VALTREE_HPP
#define PBC_VALTREE_HPP

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
//   This class represents a template tree for the internal trees.
//   The tree values are stored in TreeNode objects.
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
// $RCSfile: ValTree.hpp,v $
// $Revision: 1.9 $
// $Author: bt $
// $Date: 2001/07/04 13:37:23 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ValTree.hpp,v $
// Revision 1.9  2001/07/04 13:37:23  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.8  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.7  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.6  2000/02/11 09:15:21  pengelbr
// Make search-methods const.
// Replace RWCString with BAS::String and RWBoolean with bool.
//
// Revision 1.5  1999/06/09 12:16:26  pengelbr
// Create doc++ documentation.
//
// Revision 1.4  1999/06/08 09:20:04  pengelbr
// Rename PIM to PBC.
//
// Revision 1.3  1999/06/07 12:08:13  aro
// Module PIM_Base renamed to PBC (Plugin Base Classes).
//
// Revision 1.1  1999/05/07 12:53:36  pengelbr
// Renamed Tree/PIM_TreeNode to PIM_ValTree/PIM_ValTreeNode.
// Added PtrTree/PIM_PtrTreeNode as pointer based tree collection.
//
// Revision 1.1  1999/04/15 08:21:22  pengelbr
// initial import
//
//==============================================================================

#ifndef   BAS_DEFS_HPP
  #include "BAS/Defs.hpp"
#endif

#include <ctype.h>
#ifndef   PBC_VALTREENODE_HPP
  #include "PBC/ValTreeNode.hpp"
#endif
namespace PBC
{
//------------------------------------------------------------------------------

/** <tt><b>ValTree</b></tt> implements a digit tree template which is
    value reference based.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: ValTree.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.9 $</font></td>
    <td><font size=-1>$Date: 2001/07/04 13:37:23 $</font></td>
    <td><font size=-1>$Author: bt $</font></td>
    </tr>
    </table>

    <p>This class represents a template tree for the internal trees.
    The tree values are stored in ValTreeNode objects.
    <p>This tree is designed to store and retreive information associated
    to digit strings or digits string pairs eg. zoning information for
    a-/b-number pairs of telephone calls. It also be used for b-number
    descriptions.

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
template<class T> class ValTree D_THREADINFO
{
  protected:
    static int DIGIT_INDEX[ 256 ];

  public:

    /**@name Constructors and Destructors */
    //@{
      /** Default constructor.<br>
          Creates an empty template pointer tree.
      */
        ValTree();

        ValTree(int baseM);

      /** Destructor. */
        virtual ~ValTree();
    //@}

    /**@name Insert and Search operations. */
    //@{
      /** Insert new value in the tree. The value is defined by CLI (A-Number)
        * and B-Number.
        * @param orig CLI or a-number.
        * @param dest b-number.
        * @param val The value to store.
        * @return 0 if OK, < 0 if Error.
        */
        int insert(const BAS::String& orig,
                   const BAS::String& dest,
                         T          val);

      /** Search for CLI and B-Number pair in the tree.
        * Return the corresponding value.
        * @param orig a-number.
        * @param dest b-number.
        * @param val Value Reference.
        * @param fullSearch false: Searches only one subtree,
                            true : Searches all subtrees
        * @return true:  a/b-combination found
                  false: a/b-combination not found.
        */
        bool search(const BAS::String& orig,
                    const BAS::String& dest,
                          T&         val,
                          bool  fullSearch = FALSE);

      /** Insert new cli/value pair in the tree.
        * The value is defined by A-Number.
        * @param cli Call Line Identity Number.
        * @param val New value.
        * @return 0 = OK; < 0 = Error
        */
        int insert(const BAS::String& msisdn,
                         T          val);

      /** Search for cli in the PtrTree and return the corresponding value.
        * @param cli Call Line Identity Number.
        * @param val Value Reference.
        * @param fullSearch false: Searches only one subtree,
                            true : Searches all subtrees
        * @return true:  a-number found
                  false: a-number not found.
        */
        bool search(const BAS::String& msisdn,
                          T&         val,
                          bool  fullSearch);
    //@}

    /**@name Insert and Search operations. */
    //@{
      /** Destroy the tree. Free all allocated memory. */
        void destroy(void);

      /** Initialise (refresh) the tree. <br>
          Destroy the old tree and free all memory.
          Setup a new root node. */
        void init(void);

      /** Return the number of tree nodes allocated to the tree. */
        int64 treeNodeCount(void);

      /** Return the number of nodes allocated to the root node. */
        int64 nodeCount(void);

      /** Set the base number of the tree. */
        bool setBase(int base);
    //@}

  private:

    ValTreeNode<T> *rootM;

    int baseM;
    int64 treeNodeCountM;

    bool searchSubTree(ValTreeNode<T> *sub,
                            const BAS::String&    dest,
                                  T&            val);

    void operator=(const ValTree<T> &parm);
    ValTree(ValTree<T> &copy);
};

//-----------------------------------------------------------------------------
//
// Return the number of tree nodes allocated to the tree.
//
//-----------------------------------------------------------------------------
template<class T>
inline
int64
ValTree<T>::treeNodeCount(void)
{
  return treeNodeCountM;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
template<class T>
inline
int64
ValTree<T>::nodeCount()
{
  return rootM->nodeCount();
}

}
#ifdef INC_TEMPL_DEFS
#include "PBC/ValTree.cpp"
#endif

#endif
