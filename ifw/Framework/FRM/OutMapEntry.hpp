#ifndef FRM_OUTMAPENTRY_HPP
#define FRM_OUTMAPENTRY_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FRM
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class OutMapEntry.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: OutMapEntry.hpp,v $
// $Revision: 1.2 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:17 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OutMapEntry.hpp,v $
// Revision 1.2  2001/09/27 12:01:17  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.1  2001/05/03 16:29:24  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.1  2001/04/25 06:21:17  sd
// - Initial revision
//
//==============================================================================

#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif

namespace EDR
{
class FieldDescr;
}
namespace FRM
{
class MappingConstant;


/** <b><tt>OutMapEntry</tt></b> is used to store the information about a
 *  single mapping entry in the output mapping descriptions.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: OutMapEntry.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:17 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class OutMapEntry D_THREADINFO
{
  public:
    /**@name OutMapEntry constructors and destructor */
    //@{

    /** Constructor
     *  @param outField Pointer to the output field description
     *  @param posM Position of the output field description
     *  @param lenM Length of the output field
     */
    OutMapEntry( EDR::FieldDescr* outField, size_t posM, size_t lenM );
                       
    /** Destructor
     */
    ~OutMapEntry();

    //@}


    /**@name OutMapEntry public methods */
    //@{

    /** Get the output field
     *  @return Pointer to the output field description
     */
    EDR::FieldDescr* outField() const;

    /** Check whether the entry is initialized or not
     *  @return <b>true</b> if initialized, <b>false</b> otherwise
     */
    bool isInitialized() const;

    /** Initialize the EDR index
     *  @param index The new EDR index
     */
    void edrIndex( const EDR::Index& index );

    /** Get the EDR index of the mapping entry
     *  @return Reference to the EDR index field
     */
    const EDR::Index& edrIndex() const;

    /** Initialize the entry with a constant
     *  @param constant The constant
     */
    void constant( MappingConstant* constant );

    /** Get the mapping constant from the entry
     *  @return Pointer to the mapping constant
     */
    MappingConstant* constant() const;
    

    /** Get the length of the output field
     *  @return The length
     */
    size_t len() const;

    /** Get the position of the output field
     *  @return The position
     */
    size_t pos() const;
    
    //@}

  private:
    // instance members
    EDR::FieldDescr*      outFieldM;
    EDR::Index            edrIndexM;
    MappingConstant* constantM;
    size_t               posM;
    size_t               lenM;
};

//==============================================================================
// Get the output field description
//==============================================================================
inline EDR::FieldDescr*
OutMapEntry::outField() const
{
  return outFieldM;
}

//==============================================================================
// Check whether the mapping entry is initialized or not
//==============================================================================
inline bool
OutMapEntry::isInitialized() const
{
  return (edrIndexM.isValid() == true) || (constantM != 0);
}

//==============================================================================
// Initialize the EDR index
//==============================================================================
inline void
OutMapEntry::edrIndex( const EDR::Index& index )
{
  RWPRECONDITION( isInitialized() == false );
  edrIndexM = index;
}

//==============================================================================
// Get a reference to the EDR index
//==============================================================================
inline const EDR::Index&
OutMapEntry::edrIndex() const
{
  return edrIndexM;
}

//==============================================================================
// Get the length of the output field
//==============================================================================
inline size_t
OutMapEntry::len() const
{
  return lenM;
}

//==============================================================================
// Get the position of the output field
//==============================================================================
inline size_t
OutMapEntry::pos() const
{
  return posM;
}

//==============================================================================
// Set the mapping constant
//==============================================================================
inline void
OutMapEntry::constant( MappingConstant* constant )
{
  RWPRECONDITION( isInitialized() == false );
  constantM = constant;
}

//==============================================================================
// Get the mapping constant
//==============================================================================
inline MappingConstant*
OutMapEntry::constant() const
{
  return constantM;
}
}
#endif // OUTMAPENTRY_HPP
