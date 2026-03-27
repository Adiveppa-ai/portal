#ifndef EDR_DATABLOCKDESCR_HPP
#define EDR_DATABLOCKDESCR_HPP
// @(#)%Portal Version: DatablockDescr.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:53:32 % 
//==============================================================================
//
// Copyright (c) 1996 - 2008 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class DatablockDescr. This class is used to store
//   the edr field names and types of the different datablocks.
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
// $RCSfile: DatablockDescr.hpp,v $
// $Revision: 1.4 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DatablockDescr.hpp,v $
// Revision 1.4  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.3  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.2  2001/04/23 14:53:16  sd
// - Index splitted to IndexBase, Index and BlockIndex
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.1  2000/10/17 08:41:54  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_VALUEDESCR_HPP
  #include "EDR/ValueDescr.hpp"
#endif
#ifndef   _RWSTD_MAP_INCLUDED
  #include "map"
#endif
#ifndef   _PCM_H
  #include "pcm.h"
#endif
#ifndef   _PIN_FLDS_H
  #include "pin_flds.h"
#endif

namespace EDR
{
/** <b><tt>DatablockDescr</tt></b> is the description for the contents of
 *  an edr datablock.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DatablockDescr.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>                
 */
class DatablockDescr D_THREADINFO
{
  D_SINGLETHREADED

  public:
    typedef std::map<pin_fld_num_t, int> PinFldNumIdxTableT;

    /**@name DatablockDescr constructors and destructor */
    //@{

    /** Constructor
     *  @param blockName The full qualified name of the block
     */
    DatablockDescr( const BAS::String& blockName );

    /** Destructor
     */
    ~DatablockDescr();

    //@}

    /**@name DatablockDescr public methods */
    //@{
    
    /** Get the blockname
     *  @return Reference to the blockname
     */
    const BAS::String& blockName() const;

    /** Add a new value description to the datablock
     *  @param fieldName Name of the value
     *  @param typeName Type of the value
	 * @param flagName name of the flag specified in the grammar for the field
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addValue( const BAS::String& fieldName, 
                   const BAS::String& typeName, 
				   const BAS::String& flagName);


    /** Add a new subblock description to the datablock
     *  @param fieldName Name of the subblock
     *  @param typeName Type of the subblock
	 * @param flagName name of the flag specified in the grammar for the field
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addBlock( const BAS::String& fieldName, 
                   const BAS::String& typeName,
				   const BAS::String& flagName);

    /** Get a value description by it's index
     *  @param idx The values index
     *  @return Reference to the value
     */
    ValueDescr* value( size_t idx ) const;

    /** Get a value descriptioin by it's name
     *  @param name The name of the searched value description
     *  @return Pointer to the value on success, 0 otherwise
     */
    ValueDescr* value( const BAS::String& name ) const;

    /** Get a subblock description by it's index
     *  @param idx The subblocks index
     *  @return Reference to the value
     */
    ValueDescr* block( size_t idx ) const;

    /** Get a subblock description by it's name
     *  @param name The name of the searched subblock description
     *  @return Pointer to the value on success, 0 otherwise
     */
    ValueDescr* block( const BAS::String& name ) const;

    /** Get the number of values inside this datablock
     *  @return Number of values
     */
    size_t numValues() const;

    /** Get the number of subblocks inside this datablock
     *  @return Number of subblocks
     */
    size_t numBlocks() const;

    /** Get the blockTypeId of the description
     *  @return The block type id
     */
    size_t blockTypeId() const;

    /** Set the blockTypeId of the description
     *  @param blockTypeId The block id
     */
    void blockTypeId( size_t blockTypeId );

    /** Get the pin_fld_num
     *  @return The pin_fld_num
     */
    pin_fld_num_t getPinFldNum() const;

    /** Set the pin_fld_num
     *  @param The pin_fld_num
     */
    void setPinFldNum(pin_fld_num_t fldNum);

    /** Add an entry in the PinFldNum to Index Number Table
     *  @param The pin_fld_num
     *  @param  Index Number
     */
    void addToPinFldIdxMap(pin_fld_num_t fldNum, size_t idx);

    /** Get the PinFldIdxMap
     *  @return  reference to PinFldIdxMapM data
     */
    const PinFldNumIdxTableT* getPinFldIdxMapPtr() const;

    /** Get Container Description Text (like in containerDesc.dsc)
     *  @return String containing Container Description
     */
    BAS::String getContainerDescrStr() const;

    //@}

  private:
    BAS::String           blockNameM;
    size_t               blockTypeIdM;
    ValueDescrVector valuesM;
    ValueDescrVector blocksM;
    int                  fldNumM;
    PinFldNumIdxTableT               pinFldNumIdxMapM;  // This is to map pin_fld_num to idx
};

//==============================================================================
// Get the blockname
//==============================================================================
inline const BAS::String&
DatablockDescr::blockName() const
{
  return blockNameM;
}

//==============================================================================
// Get the block ID
//==============================================================================
inline size_t
DatablockDescr::blockTypeId() const
{
  return blockTypeIdM;
}

//==============================================================================
// Set the block ID
//==============================================================================
inline void
DatablockDescr::blockTypeId( size_t blockTypeId )
{
  blockTypeIdM = blockTypeId;
}

//==============================================================================
// Get the number of values inside the datablock
//==============================================================================
inline size_t
DatablockDescr::numValues() const
{
  return valuesM.entries();
}

//==============================================================================
// Get the number of subblocks inside the datablock
//==============================================================================
inline size_t
DatablockDescr::numBlocks() const
{
  return blocksM.entries();
}
//==============================================================================
// Get the field number
//==============================================================================
inline pin_fld_num_t
DatablockDescr::getPinFldNum() const
{
  return fldNumM;
}

//==============================================================================
// Set the fldNum
//==============================================================================
inline void
DatablockDescr::setPinFldNum( pin_fld_num_t fldNum )
{
  fldNumM = fldNum;
}

}

#endif // DATABLOCKDESCR::HPP
