#ifndef PBC_VALTREE_CPP
#define PBC_VALTREE_CPP

//==============================================================================
//
//                       Copyright(c) 1998,2023  by Oracle
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description
//   This class represents a template tree for the PlugIn internal trees.
//   The tree values are stored in PBC::TreeNode objects.
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
// $RCSfile: PBC::ValTree.cpp,v $
// $Revision: 1.8 $
// $Author: pengelbr $
// $Date: 2000/12/06 09:38:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PBC::ValTree.cpp,v $
// Revision 1.8  2000/12/06 09:38:14  pengelbr
// Add forgotten variable declaration.
//
// Revision 1.7  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.6  2000/02/11 09:15:21  pengelbr
// Make search-methods const.
// Replace RWCString with BAS::String and RWBoolean with bool.
//
// Revision 1.5  1999/12/07 11:51:36  sd
// Implementation changed to support the HP aCC compiler.
//
// Revision 1.4  1999/06/08 09:20:04  pengelbr
// Rename PIM to PBC.
//
// Revision 1.3  1999/06/07 12:08:13  aro
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

#ifndef   PBC_VALTREE_HPP
  #include "PBC/ValTree.hpp"
#endif
#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif

//------------------------------------------------------------------------------

// Initialiserer
template<class T> int PBC::ValTree<T>::DIGIT_INDEX[] = {

    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //   0- 15
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //  16- 31
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //  32- 47

//  '0' '1' '2' '3' '4' '5' '6' '7' '8' '9'
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1, //  48- 63

//      'A' 'B' 'C' 'D' 'E' 'F'
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, //  64- 79
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //  80- 95

//      'a' 'b' 'c' 'd' 'e' 'f'
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, //  96-111
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 112-127
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 128-143
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 144-159
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 160-175
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 176-191
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 192-207
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 208-223
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 224-239
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1  // 240-255
};

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
template<class T>
PBC::ValTree<T>::ValTree()
{
  D_ENTER("PBC::ValTree<T>::ValTree()");

  baseM          = 10;
  rootM          = new PBC::ValTreeNode<T>(baseM);
  treeNodeCountM = 1;
}

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
template<class T>
PBC::ValTree<T>::ValTree(int base)
{
  D_ENTER("PBC::ValTree<T>::ValTree()");

  if ( base != 10 && base != 16 ) {
    baseM = 10;
  } else {
    baseM = base;
  }

  rootM          = new PBC::ValTreeNode<T>(baseM);
  treeNodeCountM = 1;
}

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
template<class T>
PBC::ValTree<T>::~ValTree()
{
  D_ENTER("PBC::ValTree<T>::~ValTree()");

  if (rootM != 0) destroy();
}

//-----------------------------------------------------------------------------
// Reset base if tree is empty.
//-----------------------------------------------------------------------------
template<class T>
bool
PBC::ValTree<T>::setBase(int base)
{
  D_ENTER("PBC::ValTree<T>::setBase(int)");

  if ( base != 10 && base != 16 ) {
    return false;
  }

  baseM = base;

  if ( treeNodeCount() == 1 ) {
    init();
  } else {
    return false;
  }

  return true;
};

//----------------------------------------------------------------------------
// Insert new value in the tree. The value is defined by CLI (A-Number) and
// B-Number.
//
// Parameter : orig - A-Number
//             dest - B-Number
//             val  - Value
//
// Return    :    0 - OK
//              < 0 - Error
//----------------------------------------------------------------------------
template<class T>
int
PBC::ValTree<T>::insert(const BAS::String& orig,
                       const BAS::String& dest,
                             T           val)
{
  D_ENTER("PBC::ValTree<T>::insert(const BAS::String&,"
                                 "const BAS::String&, T)");

  PBC::ValTreeNode<T> *temp = rootM;
  int    retCode;
  int64   cnt;
  size_t i, length;
  unsigned char digit;
  size_t digitIndex;
  bool isDigit;

  retCode = 0;
  cnt     = nodeCount();

//--------------------------------------------------------------------------
// Insert orig number in the tree
//--------------------------------------------------------------------------
  length = orig.length();

  for ( i=0 ; i < length ; i++ )
  {
    digit = orig(i);

    if ( baseM == 10 ) {
      isDigit = isdigit( digit );
    } else {
      isDigit = isxdigit( digit );
    }

    digitIndex = DIGIT_INDEX[ digit ];

    if ( isDigit )
    {
      if ( temp->treeNode( digitIndex ) == 0)
      {
        temp->grow( digitIndex );
      }

      temp = temp->treeNode( digitIndex );
    }
  }
//---------------------------------------------------------------------------
// Insert dest number in the subtree
//---------------------------------------------------------------------------
  if (temp->subTree() == 0)
  {
    temp->newSubTree();
  }

  temp = temp->subTree();

  if (temp->subTree() != 0)
  {
    retCode = -2;
  }

  PBC::ValTreeNode<T> *dummy(0);


  if (retCode == 0)
  {
    length = dest.length();

    for (i = 0; i < length; i++)
    {
      digit = dest(i);

      if ( baseM == 10 ) {
        isDigit = isdigit( digit );
      } else {
        isDigit = isxdigit( digit );
      }

      digitIndex = DIGIT_INDEX[ digit ];

      if ( isDigit )
      {
        if (temp->treeNode( digitIndex ) == 0)
        {
          dummy = temp->grow( digitIndex );
        }

        temp = temp->treeNode( digitIndex );
      }
    }

    temp->value(val);
    retCode = 0;
  }

  treeNodeCountM += (nodeCount() - cnt);
  return retCode;
}

//-----------------------------------------------------------------------------
// Search in the Subtree for the B-Number
//
// Parameter : sub  - Root-node of the subtree
//             dest - B-Number
//             val  - The value found in the tree
//
// Return    : = true  - B-Number found
//               false - B-Number not found
//-----------------------------------------------------------------------------
template<class T>
bool
PBC::ValTree<T>::searchSubTree( PBC::ValTreeNode<T> *sub,
                               const BAS::String& dest,
                               T& val)
{
  D_ENTER("PBC::ValTree<T>::searchSubTree(PBC::ValTreeNode<T>*,"
                                        "const BAS::String&, T&)");

  PBC::ValTreeNode<T> *next = 0;
  bool retCode        = false;
  unsigned char digit;
  bool isDigit;
  size_t digitIndex;
  size_t length(dest.length());

  for ( size_t i = 0 ; i < length ; i++ )
  {
    digit = dest(i);

    if ( baseM == 10 ) {
      isDigit = isdigit( digit );
    } else {
      isDigit = isxdigit( digit );
    }

    digitIndex = DIGIT_INDEX[ digit ];

    if ( isDigit )
    {
      next = sub->treeNode( digitIndex );

      if ( sub->isValid() == true )
      {
         val     = sub->value();
         retCode = true;
      }

      if ( next == 0 )
        break;

      sub = next;
    }
  }

  if ( next != 0 && next->isValid() )
  {
    val     = sub->value();
    retCode = true;
  }

  return retCode;
}

//-----------------------------------------------------------------------------
// Search for CLI and B-Number pair in the PBC::ValTree. Return the corresponding
// value.
//
// Parameter : orig         - A-Number
//             dest         - B-Number
//             val          - value
//             fullSearch  - false = Searches only one subtree
//                            true  = Searches all subtrees
//
// Return    : true  - A-B combination found
//           : false - A-B combination not found
//-----------------------------------------------------------------------------
template<class T>
bool
PBC::ValTree<T>::search(const BAS::String& orig,
                       const BAS::String& dest,
                       T& val,
                       bool fullSearch)
{
  D_ENTER("PBC::ValTree<T>::search(const BAS::String&,"
                                 "const BAS::String&,"
                                 "T&,"
                                 "bool = false)");

  PBC::ValTreeNode<T> *temp    = rootM;
  PBC::ValTreeNode<T> *next    = 0;
  PBC::ValTreeNode<T> *sub     = 0;
  bool retCode = false;
  T tempVal;
  unsigned char digit;
  bool isDigit;
  size_t digitIndex;
  size_t length(orig.length());

  for( size_t i = 0 ; i < length ; i++ )
  {
    digit = orig(i);

    if ( baseM == 10 ) {
      isDigit = isdigit( digit );
    } else {
      isDigit = isxdigit( digit );
    }

    digitIndex = DIGIT_INDEX[ digit ];

    if ( isDigit )
    {
      next = temp->treeNode( digitIndex );

      if ( fullSearch == true && temp->subTree() != 0 )
      {
        sub = temp->subTree();

        if ( searchSubTree( sub, dest, tempVal ) )
        {
          val     = tempVal;
          retCode = true;
        }
      }

      if ( next == 0 || i == length-1 )
      {
        if(next != 0) { temp = next; }

        if(temp != 0) { sub = temp->subTree();}

        if(sub == 0) { return retCode;}

        if ( searchSubTree( sub, dest, tempVal ) )
        {
          val     = tempVal;
          retCode = true;
        }

        break;
      }
      else temp = next;
    }
  }
  return retCode;
}

//-----------------------------------------------------------------------------
// Insert new cli/value pair in the PBC::ValTree. The value is defined by A-Number.
//
// Parameter : cli - Call Line Identity Number
//             val - New value
//
// Return    :   0 = OK
//             < 0 = Error
//-----------------------------------------------------------------------------
template<class T>
int
PBC::ValTree<T>::insert(const BAS::String& cli, T  val)
{
  D_ENTER("PBC::ValTree<T>::insert(const BAS::String&, T)");

  PBC::ValTreeNode<T> *temp = rootM;
  int  retCode = 0;
  int64 cnt     = 0;
  unsigned char digit;
  bool isDigit;
  size_t digitIndex;
  size_t length(cli.length());

  cnt = nodeCount();

  for ( size_t i = 0 ; i < length ; i++ )
  {
    digit = cli(i);

    if ( baseM == 10 ) {
      isDigit = isdigit( digit );
    } else {
      isDigit = isxdigit( digit );
    }

    digitIndex = DIGIT_INDEX[ digit ];

    if ( isDigit )
    {
      if (temp->treeNode( digitIndex ) == 0)
      {
        temp->grow( digitIndex );
      }

      temp = temp->treeNode( digitIndex );
    }
  }

  temp->value(val);

  treeNodeCountM += (nodeCount() - cnt);

  return retCode;
}

//-----------------------------------------------------------------------------
// Search for cli in the PBC::ValTree and return the corresponding value.
//
// Parameter : cli - Call Line Identity Number
//             val - found value
//
// Return    :   true  - A-Number found
//               false - A-Number not found
//-----------------------------------------------------------------------------
template<class T>
bool
PBC::ValTree<T>::search(const BAS::String& cli,
                       T& val,
                       bool fullSearch)
{
  D_ENTER("PBC::ValTree<T>::search(const BAS::String&, T&, bool)");

  PBC::ValTreeNode<T> *temp    = rootM;
  PBC::ValTreeNode<T> *next    = 0;
  bool           retCode = false;

  unsigned char digit;
  bool isDigit;
  size_t digitIndex;
  size_t length(cli.length());

  for (size_t i = 0; i < length; i++)
  {
    digit = cli(i);

    if ( baseM == 10 ) {
      isDigit = isdigit( digit );
    } else {
      isDigit = isxdigit( digit );
    }

    digitIndex = DIGIT_INDEX[ digit ];

    if ( isDigit ) {
      next = temp->treeNode( digitIndex );

      if(!fullSearch && temp->isValid()) {
         val      = temp->value();
         retCode = true;
      }

      if (next == 0) break;
      temp = next;
    }
  }

  if (next != 0 && next->isValid()) {
    val      = next->value();
    retCode = true;
  }

  return retCode;
}

//-----------------------------------------------------------------------------
// Destroy the PBC::ValTree. Free all allocated memory.
//-----------------------------------------------------------------------------
template<class T>
void
PBC::ValTree<T>::destroy(void)
{
  D_ENTER("PBC::ValTree<T>::destroy(void)");

  if (rootM != 0)
  {
    delete rootM;

    rootM = 0;
  }

  treeNodeCountM = 0;
}

//-----------------------------------------------------------------------------
// Initialise (refresh) the PBC::ValTree. Destroy the old PBC::ValTree and free
// all memory. Setup a new root node.
//-----------------------------------------------------------------------------
template<class T>
void
PBC::ValTree<T>::init(void)
{
  D_ENTER("PBC::ValTree<T>::init(void)");

  if (rootM != 0)
  {
    delete rootM;

    rootM = 0;
  }

  rootM = new PBC::ValTreeNode<T>(baseM);

  treeNodeCountM = 1;
}


#endif
