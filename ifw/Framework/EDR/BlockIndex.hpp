#ifndef EDR_BLOCKINDEX_HPP
#define EDR_BLOCKINDEX_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class BlockIndex.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: BlockIndex.hpp,v $
// $Revision: 1.4 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.5  2003/10/31 ammon
// PRSF00075996 Add getXmlId() and getXmlIndices()
//
// Revision 1.4  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.3  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.2  2001/04/26 15:23:25  sd
// - ContainerIndex introduced
//
// Revision 1.1  2001/04/23 14:53:16  sd
// - Index splitted to BlockIndex, Index and BlockIndex
//
// Revision 1.2  2001/04/12 12:38:14  sd
// - Update for the new module structure
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.10  2001/03/20 15:01:32  sd
// - ByteBuffer introduced
//
// Revision 1.8  2001/03/09 12:30:40  sd
// - ValueIterator added.
//
// Revision 1.7  2000/12/06 09:33:28  sd
// - Backup version.
//
// Revision 1.6  2000/10/20 10:33:40  sd
// - Rogue Wave array replaced
//
// Revision 1.5  2000/10/20 10:02:01  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   EDR_CONTAINERINDEX_HPP
  #include "EDR/ContainerIndex.hpp"
#endif
namespace EDR
{
/** <b><tt>BlockIndex</tt></b> is the index class to access edr container 
 *  values.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: BlockIndex.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>                
 */
class BlockIndex  D_THREADINFO
{
  D_SINGLETHREADED

  public:

    /**@name BlockIndex constructors and destructor */
    //@{

    /** Default constructor
     */
    BlockIndex();

    /**  Copy constructor
     *   @param other The edr index to copy
     */
    BlockIndex( const BlockIndex& other );

    /** Destructor
     */
    ~BlockIndex();

    //@}

    /**@name BlockIndex public methods */
    //@{

    /** Check if the index is a valid index
     *  @return <b>true</b> if the index is valid, <b>false</b> otherwise
     */
    bool isValid() const;

    /**  Assignment operator
     *  @param other The BlockIndex to assign
     *  @return Reference for self
     */
    const BlockIndex& operator=( const BlockIndex& other );

    /** Compare index with another
     *  @param other The other index for comparison
     *  @return <b>true</b> if equal, <b>false</b> otherwise
     */
    bool operator==( const BlockIndex& other ) const;

    /** Check wheter the index contains another or not
     *  @param other The other index
     *  @return <b>true</b> if index contains the other, <b>false</b> otherwise
     */
    bool contains( const BlockIndex& other ) const;

    /** Get the subindex for the block index
     *  @param depth The depth for the subindex 
     *  @return The subindex
     */
    BlockIndex subBlockIndex( size_t depth ) const;

    /** Get the depth of the index
     *  @return The depth of the index
     */
    size_t depth() const;

    /* Get the container index
     * @return Container index for this block index
     */
    const ContainerIndex& containerIndex() const;

    /** Get the name of the block index
     *  @return Name of the index
     */
    BAS::String name() const;

    /** Get the indices used to make an XML ID for this Block type
     *  @return XML ID indexes
     */
    BAS::StringList getXmlIndices() const;

    /** Get the XML ID to use for this Block type
     *  @return XML ID string
     */
    BAS::String getXmlId() const;

    //@}

  protected:

    /* Constructor
     * @param containerIndex The associated container index
     */
    BlockIndex( const ContainerIndex& containerIndex );

    /* Get the value index at specified depth
     * @param depth The depth for the value index
     */
    size_t valueIndex( size_t depth ) const;

    /* Get the start blocktype id
     * @return The blocktype id of the root block
     */
    size_t startBlockTypeId( ) const;

    /* Add a new value index to the index
     * @param valueIndex The new value index
     */
    void addValueIndex( size_t valueIndex );

  protected:
    // instance members
    ContainerIndex containerIndexM;
    size_t             depthM;
    size_t*            indexVectorM;

  public:
    // friend classes
    friend class Container;
    friend class TracedContainer;
    friend class Datablock;
    friend class Factory;
    friend class Iterator;
    friend class ValueIterator;
};

//==============================================================================
// Get the index depth
//==============================================================================
inline size_t
BlockIndex::depth() const
{
  return depthM;
}

//==============================================================================
// Get the value index at specified depth
//==============================================================================
inline size_t
BlockIndex::valueIndex( size_t depth ) const
{
  RWPRECONDITION( depth < depthM );
  return indexVectorM[ depth ];
}

//=========================================-====================================
// Get the start blocktype id at level
//==============================================================================
inline size_t
BlockIndex::startBlockTypeId() const
{
  return containerIndexM.startBlockTypeId();
}

//==============================================================================
// Check if the index is a valid one
//==============================================================================
inline bool
BlockIndex::isValid() const
{
  return containerIndexM.isValid();
}

//==============================================================================
// Get the container index
//==============================================================================
inline const ContainerIndex&
BlockIndex::containerIndex() const
{
  return containerIndexM;
}
}
#endif // BLOCKINDEX_HPP
