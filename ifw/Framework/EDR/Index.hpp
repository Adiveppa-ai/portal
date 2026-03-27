#ifndef EDR_INDEX_HPP
#define EDR_INDEX_HPP

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
//   Declaration of the class Index.
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
// $RCSfile: Index.hpp,v $
// $Revision: 1.6 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.7  2003/10/31 ammon
// PRSF00075996 Add getXmlId()
//
// Revision 1.6  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.5  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.4  2001/04/26 15:23:25  sd
// - ContainerIndex introduced
//
// Revision 1.3  2001/04/23 14:53:16  sd
// - Index splitted to IndexBase, Index and BlockIndex
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   EDR_PARAMETER_HPP
  #include "EDR/Parameter.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
namespace EDR
{
    class Factory;
/** <b><tt>Index</tt></b> is the index class to access edr container 
 *  values.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Index.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.6 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>                
 */
class Index D_THREADINFO
{
  D_SINGLETHREADED

  public:

    /**@name Index constructors and destructor */
    //@{

    /** Default constructor
     */
    Index();

    /** Destructor
     */
    ~Index();

    //@}

    /**@name Index public methods */
    //@{

    /** Check if the index is a valid index
     *  @return <b>true</b> if the index is valid, <b>false</b> otherwise
     */
    bool isValid() const;

    /** Compare index with another
     *  @param other The other index for comparison
     *  @return <b>true</b> if equal, <b>false</b> otherwise
     */
    bool operator==( const Index& other ) const;

    /** Assignment operator
     *  @param other The Index to assign
     *  @return Reference for self
     */
    const Index& operator=( const Index& other );

    /** Get the datatype for the index
     *  @return Datatype as defined in FieldDescr
     */
    int64 datatype() const;

    /** Get the datatype as string
     *  @return Datatype as string
     */
    BAS::String datatypeAsString() const;
    

    /** Get the block index of the value
     *  @return Reference to the block value
     */
    const BlockIndex& blockIndex() const;

    /** Get the value index inside the block
     *  @return The value index
     */
    size_t valueIndex() const;

    /** Get the name of the value index
     *  @return Name of the index
     */
    BAS::String name() const;

    /** Get the XML ID to use for this Index
     *  @return XML ID string
     */
    BAS::String getXmlId() const;

    //@}

  protected:

    /* Constructor
     * @param blockIndex The block for the value
     * @param valueIndex The value inside this block
     * @param datatype The type of the value
     */
    Index( const BlockIndex& blockIndex,
               size_t                valueIndex,
               int64                  datatype );

    /* Set the datatype
     * @param datatype The new datatype
     */
    void datatype( int64 datatype );

    /* Check wheter the index contains another or not
     * @param other The other index
     * @return <b>true</b> if index contains the other, <b>false</b> otherwise
     */
    bool contains( const Index& other ) const;

  private:
    // Instance members
    BlockIndex blockIndexM;
    size_t         valueIndexM;
    int64           datatypeM;

    // friend classes
    friend class Factory;
    friend class ValueIterator;
};

//==============================================================================
// Get the block index
//==============================================================================
inline const BlockIndex&
Index::blockIndex() const
{
  return blockIndexM;
}

//==============================================================================
// Get the value index
//==============================================================================
inline size_t
Index::valueIndex() const
{
  return valueIndexM;
}

//==============================================================================
// Get the datatype of the value
//==============================================================================
inline int64
Index::datatype() const
{
  return datatypeM;
}

//==============================================================================
// Get the datatype as string
//==============================================================================
inline BAS::String
Index::datatypeAsString() const
{
  return Parameter::datatypeAsString((Parameter::ParamTypeT)datatypeM );
}

//==============================================================================
// Set the datatype of the value
//==============================================================================
inline void
Index::datatype( int64 datatype )
{
  datatypeM = datatype;
}

//==============================================================================
// Check if the index is a valid one
//==============================================================================
inline bool
Index::isValid() const
{
  return blockIndexM.isValid();
}
}
#endif // INDEX_HPP
