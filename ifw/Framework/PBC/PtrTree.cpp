#ifndef PBC_PTRTREE_CPP
#define PBC_PTRTREE_CPP

//==============================================================================
//
//      Copyright (c) 1996 - 2023 Oracle.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description
//   This class represents a template tree for the PlugIn internal trees.
//   The tree values are stored in PBC::PtrTreeNode objects.
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
// $RCSfile: PBC::PtrTree.cpp,v $
// $Revision: 1.8 $
// $Author: pengelbr $
// $Date: 2000/10/25 12:22:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PBC::PtrTree.cpp,v $
// Revision 1.8  2000/10/25 12:22:21  pengelbr
// Modified to be able to handle HEX digits. If invoked as before nothing
// has to be changed.
//
// Revision 1.7  2000/06/17 10:23:36  pengelbr
// Added AIX missing operators.
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

#ifndef   RW_TOOLS_TPVECTOR_H
  #include <rw/tpvector.h>
#endif
#ifndef   PBC_PTRTREE_HPP
  #include "PBC/PtrTree.hpp"
#endif

//------------------------------------------------------------------------------

// Initialiserer
template<class T> int PBC::PtrTree<T>::DIGIT_INDEX[] = {

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

// Static Array to hold the ASCII character representation of numbers
template<class T> char PBC::PtrTree<T>::CHAR_INDEX[] = {

    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',               //   0-  9
    'A', 'B', 'C', 'D', 'E', 'F'                                    //  10- 15
};

//----------------------------------------------------------------------------
//
// Constructor
//
//----------------------------------------------------------------------------
template<class T>
PBC::PtrTree<T>::PtrTree()
{
  D_ENTER("PBC::PtrTree<T>::PtrTree()");

  baseM          = 10;
  rootM          = new PBC::PtrTreeNode<T>(10);
  treeNodeCountM = 1;
}

template<class T>
PBC::PtrTree<T>::PtrTree(int base)
{
  D_ENTER("PBC::PtrTree<T>::PtrTree()");

  if ( base != 10 && base != 16 ) {
    baseM = 10;
  } else {
    baseM = base;
  }

  rootM          = new PBC::PtrTreeNode<T>(baseM);
  treeNodeCountM = 1;
}

//----------------------------------------------------------------------------
//
// Destructor
//
//----------------------------------------------------------------------------
template<class T>
PBC::PtrTree<T>::~PtrTree()
{
  D_ENTER("PBC::PtrTree<T>::~PtrTree()");

  if (rootM != 0) destroy();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
template<class T>
bool
PBC::PtrTree<T>::setBase(int base)
{
  D_ENTER("PBC::PtrTree<T>::setBase(int)");

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
//
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
PBC::PtrTree<T>::insert(const BAS::String& orig,
                       const BAS::String& dest,
                             T*         val)
{
  D_ENTER("PBC::PtrTree<T>::insert(const BAS::String&, const BAS::String&, T*)");

  PBC::PtrTreeNode<T> *temp = rootM;
  int                retCode;
  int64               cnt;
  size_t             i;
  size_t             length( orig.length() );
  unsigned char               digit;
  int                digitIndex;
  bool               isDigit;

  retCode = 0;
  cnt     = nodeCount();

//--------------------------------------------------------------------------
// Insert orig number in the tree
//--------------------------------------------------------------------------
  length = orig.length();

  for ( i = 0 ; i < length ; i++ )
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
        if ( temp->treeNode( digitIndex ) == 0)
        {
          temp->grow( digitIndex );
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
//
// Search in the Subtree for the B-Number
//
// Parameter : sub  - Root-node of the subtree
//             dest - B-Number
//             val  - The value found in the tree
//
// Return    : = true  - B-Number found
//               false - B-Number not found
//
//-----------------------------------------------------------------------------
template<class T>
T*
PBC::PtrTree<T>::searchSubTree(PBC::PtrTreeNode<T> *sub,
                              const BAS::String& dest) const
{
  D_ENTER("PBC::PtrTree<T>::searchSubTree(PBC::PtrTreeNode<T> *, const BAS::String&)");

  PBC::PtrTreeNode<T> *next = 0;
  T* retVal( 0 );

  size_t length( dest.length() );
  bool isDigit;
  unsigned char digit;
  int digitIndex;

  for(size_t i = 0; i < length; i++)
  {
    digit = dest(i);

    if ( baseM == 10 ) {
      isDigit = isdigit( digit );
    } else {
      isDigit = isxdigit( digit );
    }

    digitIndex = DIGIT_INDEX[ digit ];

    if ( isDigit ) {
      next = sub->treeNode( digitIndex );

      if(sub->isValid() == true) {
         retVal = sub->value();
      }

      if(next == 0) break;
      sub = next;
    }
  }

  if(next != 0 && next->isValid() == true) {
    retVal = sub->value();
  }

  return retVal;
}

//-----------------------------------------------------------------------------
//
// Search for CLI and B-Number pair in the PBC::PtrTree. Return the corresponding
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
T*
PBC::PtrTree<T>::search(const BAS::String& orig,
                       const BAS::String& dest,
                             bool fullSearch) const
{
  D_ENTER("PBC::PtrTree<T>::search(const BAS::String&,"
                                 "const BAS::String&,"
                                 "bool = false)");

  PBC::PtrTreeNode<T> *temp( rootM );
  PBC::PtrTreeNode<T> *next( 0 );
  PBC::PtrTreeNode<T> *sub( 0 );
  T* tempVal( 0 );
  T* retVal( 0 );

  size_t length( orig.length() );
  bool isDigit;
  unsigned char digit;
  int digitIndex;

  for(size_t i = 0; i < length; i++)
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

      if(fullSearch == true && temp->subTree() != 0) {
        sub = temp->subTree();
        if((tempVal = searchSubTree(sub, dest)) != 0) {
          retVal = tempVal;
        }
      }

      if ( next == 0 || i == length - 1 ) {

        if(next != 0) { temp = next; }

        if(temp != 0) { sub = temp->subTree();}

        if(sub == 0) { return retVal;}

        if ( ( tempVal = searchSubTree( sub, dest ) ) != 0 )
        {
          retVal = tempVal;
        }

        break;
      }
      else temp = next;
    }
  }
  return retVal;
}

//-----------------------------------------------------------------------------
//
// Insert new cli/value pair in the PBC::PtrTree. The value is defined by A-Number.
//
// Parameter : cli - Call Line Identity Number
//             val - New value
//
// Return    :   0 = OK
//             < 0 = Error
//-----------------------------------------------------------------------------
template<class T>
int
PBC::PtrTree<T>::insert(const BAS::String& cli, T*  val)
{
  D_ENTER("PBC::PtrTree<T>::insert(const BAS::String&, T*)");

  PBC::PtrTreeNode<T> *temp = rootM;
  int  retCode = 0;
  int64 cnt     = 0;

  cnt = nodeCount();

  bool isDigit;
  unsigned char digit;
  int digitIndex;
  size_t length( cli.length() );

  for (size_t i = 0; i < length; i++)
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
//
// Search for cli in the PBC::PtrTree and return  a stack of values that 
// match any of the prefixes for the cli
//
// Parameter : cli - Call Line Identity Number
//             stack  - Containing values matching the prefix
//
//-----------------------------------------------------------------------------
template<class T>
void
PBC::PtrTree<T>::search(const BAS::String& cli,
                             RWTStack<T*, RWTValSlist<T*> >& stack) const
{
  D_ENTER("PBC::PtrTree<T>::search(const BAS::String&,RWTStack<T*, RWTValOrderedVector<T*> >& )");

  PBC::PtrTreeNode<T> *temp    = rootM;
  PBC::PtrTreeNode<T> *next    = 0;

  bool isDigit;
  unsigned char digit;
  int digitIndex;
  size_t length( cli.length() );

  for (size_t i = 0; i < length; i++)
  {
    digit = cli(i);

    if ( baseM == 10 )
    {
      isDigit = isdigit( digit );
    }
    else 
    {
      isDigit = isxdigit( digit );
    }

    digitIndex = DIGIT_INDEX[ digit ];

    if ( isDigit )
    {
      next = temp->treeNode( digitIndex );

      if( temp->isValid())
      {
         stack.push( temp->value());
      }

      if (next == 0)
      {
        break;
      }
      temp = next;
    }
  }

  if (next != 0 && next->isValid()) 
  {
    stack.push( next->value());
  }
  return;

}


//-----------------------------------------------------------------------------
//
// Search for cli in the PBC::PtrTree and return the corresponding value.
//
// Parameter : cli - Call Line Identity Number
//             val - found value
//
// Return    :   true  - A-Number found
//               false - A-Number not found
//
//-----------------------------------------------------------------------------
template<class T>
T*
PBC::PtrTree<T>::search(const BAS::String& cli,
                             bool fullSearch) const
{
  D_ENTER("PBC::PtrTree<T>::search(const BAS::String&, bool)");

  PBC::PtrTreeNode<T> *temp    = rootM;
  PBC::PtrTreeNode<T> *next    = 0;

  bool isDigit;
  unsigned char digit;
  int digitIndex;
  size_t length( cli.length() );

  for (size_t i = 0; i < length; i++)
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
      next = temp->treeNode( digitIndex );

      if(!fullSearch && temp->isValid())
      {
         return temp->value();
      }

      if (next == 0) break;
      temp = next;
    }
  }

  if (next != 0 && next->isValid()) {
    return next->value();
  }

  return 0;
}

//-----------------------------------------------------------------------------
//
// Destroy the PBC::PtrTree. Free all allocated memory.
//
//-----------------------------------------------------------------------------
template<class T>
void
PBC::PtrTree<T>::destroy(void)
{
  D_ENTER("PBC::PtrTree<T>::destroy(void)");

  if (rootM != 0)
  {
    delete rootM;

    rootM = 0;
  }

  treeNodeCountM = 0;
}

//-----------------------------------------------------------------------------
//
// Initialise (refresh) the PBC::PtrTree.  Destroy the old PBC::PtrTree and free all memory.
// Setup a new root node.
//
//-----------------------------------------------------------------------------
template<class T>
void
PBC::PtrTree<T>::init(void)
{
  D_ENTER("PBC::PtrTree<T>::init(void)");

  if (rootM != 0)
  {
    delete rootM;

    rootM = 0;
  }

  rootM = new PBC::PtrTreeNode<T>(baseM);

  treeNodeCountM = 1;
}

//-----------------------------------------------------------------------------
//
// Iterate through the Tree, and for each Tree Node with a valid CLI, call the
// function printTree() of TreeNode->Value object.
//
// Parameter : out - reference to std::ostream.
//
// Return    :   void
//
//-----------------------------------------------------------------------------
template<class T>
void
PBC::PtrTree<T>::printTree(std::ostream& out) 
{
  D_ENTER ("PBC::PtrTree<T>::printTree(std::ostream& out)");

  PBC::PtrTreeNode<T> *temp    = rootM;
  PBC::PtrTreeNode<T> *curr    = 0;

  BAS::String numInSearch = "";   // Used as a key to search in the tree. If value found, then this is CLI
  unsigned numLevel = 0;         // Size of the CLI. Holds the seacrh Level
  unsigned idx = 0;

  RWTPtrVector< PBC::PtrTreeNode<T> > nodeStack;  // Not exactly a stack, but a vector holds the pointers
                                                 // of Tree nodes. Needed when continuing the traversal
                                                 // with the previous tree node.

  // Initialize the index and search level.
  idx = 0;
  numLevel = 0;

  // Continue the traversal of the tree nodes, for all the digits in the 
  // range of 0 to (baseM - 1) [baseM can be either 10 or F]

  while (idx < baseM)
  {
    // Increase the size, if needed. 
    // numLevel represents the size of the current CLI in search
    if (numInSearch.length() < (numLevel + 1))
    {
      numInSearch.resize(numInSearch.length() + 10);
      nodeStack.reshape(numInSearch.length() + 10);
    }

    numInSearch[numLevel] = CHAR_INDEX [ idx ];

    curr = temp->treeNode(idx);
    if (curr != 0)         // If there is Tree Node, for the given CLI...
    {
      if(curr->isValid())  // If the Tree Node has a Value, call the function printTree()
      {
        (curr->value())->printTree(out, numInSearch);
      }

      nodeStack[numLevel] = temp;  // For the next interatoin, seacrh level will be increased.
                                   // so, store the current node pointer in the stack.
      numLevel++;
      idx = 0;
      temp = curr;

      continue;
    }
    else if (idx == (baseM - 1))
    {
      // If the digit in search is equal to baseM, reduce the search level
      // and continue from the previous one.
      // eg. If the current CLI in search is 04969999 and there is no value found for this,
      // then the CLI for the next search should be 0497

      while((idx == (baseM - 1)) && (numLevel > 0))
      {
        numInSearch[numLevel] = '\0';
        numLevel--;
        idx = DIGIT_INDEX[(unsigned char)numInSearch[numLevel]];

        temp = nodeStack[numLevel];
      }
    }
    idx++;
  }
}

#ifdef __aix

//=========================================================================
// Equal.
//=========================================================================
template<class T>
int
PBC::PtrTree<T>::operator==(const PBC::PtrTree<T> &right) const
{
  D_ENTER ("PBC::PtrTree<T>::operator==(const PBC::PtrTree<T> &) const");

  return true;
}

//=========================================================================
// Less.
//=========================================================================
template<class T>
int
PBC::PtrTree<T>::operator<(const PBC::PtrTree<T> &right) const
{
  D_ENTER ("PBC::PtrTree::operator<(const PBC::PtrTree<T> &) const");

  return true;
}

#endif

#endif
