#ifndef PBC_PTRTREE_HPP
#define PBC_PTRTREE_HPP

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
//   The tree values are stored in PtrTreeNode objects.
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
// $RCSfile: PtrTree.hpp,v $
// $Revision: 1.11 $
// $Author: pengelbr $
// $Date: 2000/10/25 12:22:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PtrTree.hpp,v $
// Revision 1.11  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.10  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.9  2000/06/17 10:23:36  pengelbr
// Added AIX missing operators.
//
// Revision 1.8  2000/02/11 09:15:21  pengelbr
// Make search-methods const.
// Replace RWCString with BAS::String and RWBoolean with bool.
//
// Revision 1.7  1999/12/07 11:51:36  sd
// Implementation changed to support the HP aCC compiler.
//
// Revision 1.6  1999/06/25 11:17:42  pengelbr
// Modified to move back in tree.
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
// Revision 1.1  1999/05/07 12:53:32  pengelbr
// Renamed Tree/TreeNode to ValTree/ValTreeNode.
// Added PtrTree/PtrTreeNode as pointer based tree collection.
//
// Revision 1.1  1999/04/15 08:21:22  pengelbr
// initial import
//
//==============================================================================

#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   PBC_PTRTREENODE_HPP
  #include "PBC/PtrTreeNode.hpp"
#endif
#ifndef   RW_TOOLS_TSTACK_H
  #include <rw/tstack.h>
#endif
namespace PBC
{
//------------------------------------------------------------------------------

/** <tt><b>PtrTree</b></tt> implements a digit tree template which is
    pointer based.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: PtrTree.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.11 $</font></td>
    <td><font size=-1>$Date: 2000/10/25 12:22:21 $</font></td>
    <td><font size=-1>$Author: pengelbr $</font></td>
    </tr>
    </table>

    <p>This class represents a template tree for the internal trees.
    The tree values are stored in PtrTreeNode objects.
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
template<class T>
class PtrTree D_THREADINFO
{
  protected:
    static int DIGIT_INDEX[ 256 ];         // Array to represent ASCII characters in Number format 
    static char CHAR_INDEX[ 16 ];          // Array to represent Numbers in ASCII character format 

  public:

    /**@name Constructors and Destructors */
    //@{
      /** Default constructor.<br>
          Creates an empty template pointer tree.
      */
        PtrTree();

        PtrTree(int baseM);

      /** Destructor. */
        virtual ~PtrTree();
    //@}

#ifdef __aix
  /**@name Comparision. */
  //@{

    /// Equality operator.
      int operator==(const PtrTree<T> &right) const;

    /// Less operator.
      int operator<(const PtrTree<T> &right) const;

  //@}
#endif

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
                         T* val);

      /** Search for CLI and B-Number pair in the PtrTree.
        * Return the corresponding value.
        * @param orig a-number.
        * @param dest b-number.
        * @param fullSearch false: Searches only one subtree,
                            true : Searches all subtrees
        * @return Found value pointer if successful, else nil-pointer.
        */
        T* search(const BAS::String& orig,
                  const BAS::String& dest,
                        bool fullSearch = false) const;

      /** Insert new cli/value pair in the PtrTree.
        * The value is defined by A-Number.
        * @param cli Call Line Identity Number.
        * @param val New value.
        * @return 0 = OK; < 0 = Error
        */
        int insert(const BAS::String& msisdn,
                         T* val);

      /** Search for cli in the PtrTree and return the corresponding value.
        * @param cli Call Line Identity Number.
        * @param fullSearch false: Searches only one subtree,
                            true : Searches all subtrees
        * @return Found value pointer if successful, else nil-pointer.
        */
        T* search(const BAS::String& msisdn,
                        bool fullSearch) const;
      /** Search for cli in the PBC_PtrTree and return the corresponding values.
        * for any of the prefix matches
        * @param cli Call Line Identity Number.
        * @param stack of values that match the any of the prefixes of CLI
        * 
        */

        void search(const BAS::String& cli,
           RWTStack<T*, RWTValSlist<T*> >& stack) const; 

    //@}

    /**@name Insert and Search operations. */
    //@{
      /** Destroy the PtrTree. Free all allocated memory. */
        void destroy(void);

      /** Initialise (refresh) the PtrTree. <br>
          Destroy the old PtrTree and free all memory.
          Setup a new root node. */
        void init(void);

      /** Return the number of tree nodes allocated to the tree. */
        int64 treeNodeCount(void);

      /** Return the number of nodes allocated to the root node. */
        int64 nodeCount(void);

      /** Set the base number of the tree. */
        bool setBase(int base);

      /** Iterate through the tree and for each TreeNode this function
          invokes (*T)->printTree(std::ostream&, cliOfTreeNode) to print the data. 
          This function is currently used to print the NumberPortability data. 
          To make use of this function in other classes, the Class represented by the 
          Template parameter T, should have an implementation for 
          void printTree(std::ostream& out, const BAS::String& cli); **/
        void printTree(std::ostream& out);

    //@}

  protected:

    PtrTreeNode<T>* root() const;

    int baseM;

  private:

    PtrTreeNode<T>* rootM;
    int64 treeNodeCountM;

    T* searchSubTree(PtrTreeNode<T> *sub,
                     const BAS::String& dest) const;

    void operator=(const PtrTree<T> &parm);
    PtrTree(PtrTree<T> &copy);
};

//-----------------------------------------------------------------------------
//
// Return the number of tree nodes allocated to the tree.
//
//-----------------------------------------------------------------------------
template<class T>
inline
int64
PtrTree<T>::treeNodeCount(void)
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
PtrTree<T>::nodeCount()
{
  return rootM->nodeCount();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
template<class T>
inline
PtrTreeNode<T>*
PtrTree<T>::root() const
{
  return rootM;
}

//-----------------------------------------------------------------------------
}
#ifdef INC_TEMPL_DEFS
#include "PBC/PtrTree.cpp"
#endif

#endif

