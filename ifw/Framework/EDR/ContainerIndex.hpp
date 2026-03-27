#ifndef EDR_CONTAINERINDEX_HPP
#define EDR_CONTAINERINDEX_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class ContainerIndex.
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
// $RCSfile: ContainerIndex.hpp,v $
// $Revision: 1.5 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ContainerIndex.hpp,v $
// Revision 1.5  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.4  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.3  2001/07/04 13:37:23  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.2  2001/06/12 12:00:55  sd
// - Pointer to factory added to container index
// - New method addIndex() added to iterator
//
// Revision 1.1  2001/04/27 06:42:58  sd
// - Initial revision
//
//==============================================================================
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace EDR
{
    class Factory;
/** <b><tt>ContainerIndex</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ContainerIndex.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class ContainerIndex  D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name ContainerIndex constructors and destructor */
    //@{

    /** Default constructor
     */
    ContainerIndex();

    /** Destructor
     */
    ~ContainerIndex();

    //@}

    /**@name ContainerIndex public methods */
    //@{

    /** Check if the index is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;
      
    /** Get the start blocktype id
     *  @return The blocktype id of the root block
     */
    size_t startBlockTypeId( ) const;

    /** Get the pointer to the associated EDR factory
     *  @return Pointer to factory (can be 0 if uninitialized)
     */
    Factory* factory() const;
    
    /** Equal operator
     *  @param other The other index for the comparison
     *  @return <b>true</b> if equal, <b>false</b> otherwise
     */
    bool operator==( const ContainerIndex& other ) const;

    /** Not equal operator
     *  @param other The other index for the comparison
     *  @return <b>true</b> if not equal, <b>false</b> otherwise
     */
    bool operator!=( const ContainerIndex& other ) const;

    /** Get the name of the container index
     *  @return Name of the index
     */
    BAS::String name() const;

    //@}

  protected:

    /* Constructor
     */
    ContainerIndex( Factory* factory,
                        size_t       startBlockTypeId );
    
  private:
    // Instance members
    Factory* factoryM;
    size_t       startBlockTypeIdM;

    // Friends
    friend class Factory;
};

//==============================================================================
// Get the start blocktype id for the Index
//==============================================================================
inline size_t
ContainerIndex::startBlockTypeId() const
{
  return startBlockTypeIdM;
}

//==============================================================================
// Get the pointer to the EDR factory
//==============================================================================
inline Factory*
ContainerIndex::factory() const
{
  return factoryM;
}

//==============================================================================
// Comparison operator equal
//==============================================================================
inline bool
ContainerIndex::operator==( const ContainerIndex& other ) const
{
  return( startBlockTypeIdM == other.startBlockTypeIdM );
}

//==============================================================================
// Comparison operator not equal
//==============================================================================
inline bool
ContainerIndex::operator!=( const ContainerIndex& other ) const
{
  return( startBlockTypeIdM != other.startBlockTypeIdM );
}
}
#endif // CONTAINERINDEX_HPP
