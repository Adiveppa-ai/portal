#ifndef EDR_DATABLOCK_HPP
#define EDR_DATABLOCK_HPP

/* @(#)%Portal Version: Datablock.hpp:NewPipelineVelocityInt:4:2006-Sep-18 22:53:38 % */
//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Datablock.
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
//------------------------------------------------------------------------------
// Revision 1.11 2012/05/11 Santanu 
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
//
// Revision       1.10  2006/08/10 bertm
// PRSF00224380   Changed ostream to BAS::String to improve performance
//
// Revision 1.9  2005/04/1 rtang
// PRSF00161772  Platform support for improving pre-suspense performance 
//
// Revision 1.8  2004/03/11 ammon
// PRSF00098531  XML de-serialize performance
//
// Revision 1.7  2004/02/06 ammon
// PRSF00090995  More XML performance
//
// Revision 1.6  2004/02/02 ammon
// PRSF00090216  XML performance
//
// Revision 1.5  2002/01/15 09:28:23  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.4  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.3  2001/08/07 12:58:46  mwriedt
// - PETS #37618: Code Review.
//
// Revision 1.2  2001/03/30 12:49:44  sd
// - Changes to support duplication of EDR containers
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.11  2001/03/14 11:42:27  sd
// - Output operator added to Container
//
// Revision 1.10  2001/03/09 14:08:12  sd
// - Performance test
//
// Revision 1.8  2001/03/08 12:32:51  sd
// - Output mapping changed
//
// Revision 1.6  2000/10/20 10:02:01  sd
// - Initial revision.
//
//==============================================================================

#if !defined EDR_EXPORT
  #if defined(WINDOWS)
    #if !defined(EDR_INTERNAL)
      #define EDR_EXPORT __declspec(dllimport)
    #else
      #define EDR_EXPORT __declspec(dllexport)
    #endif
  #else
    #define EDR_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TPVECTOR_H
  #include <rw/tpvector.h>
#endif
#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   EDR_METADATA_H
  #include "EDR/MetaData.hpp"
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

#ifndef   EDR_DATABLOCKDESCR_HPP
  #include "EDR/DatablockDescr.hpp"
#endif
namespace EDR
{
class Value;
class DatablockValue;
class Factory;
class ValueDescr;
class DatablockDescr;

/** <tt><b>Datablock</b></tt> is the class for building up the tree
 *  data structures of the edr container.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Datablock.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:41 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>                
 */
class Datablock D_THREADINFO
{
  D_SINGLETHREADED

  public:

    /**@name Datablock public methods */
    //@{

    /** Get an Value by it's local index value
     *  @param idx The local index value (offset)
     *  @return Pointer to the Value on success, 0 otherwise
     */
    Value* value( size_t idx ) const;

    /** Get an Value by it's pin_fld_num value
     *  @param fld The fld number of the field
     *  @return Pointer to the Value on success, 0 otherwise
     */
    Value* getValue( pin_fld_num_t  fld ) ;

    /** Get an DatablockValue by it's local index value
     *  @param idx The local index value (offset)
     *  @return Pointer to the DatablockValue on success, 0 otherwise
     */
    DatablockValue* datablockValue( size_t idx ) const;

    /** Initialize an Value in the datablock
     *  @param idx The index of the value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setValue( size_t     idx,
                   Value* value );

    /** Initialize an DatablockValue in the datablock
     *  @param idx The index of the value
     *  @param value The DatablockValue to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setDatablockValue( size_t              idx,
                            DatablockValue* blockValue );

    /** Serialize the datablock
     *  @param out Output stream for serialization
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool serialize( std::ostream& out ) const;

    /** Restore the datablock from an input stream
     *  @param in Input stream for operation
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool restore( std::istream& in );

   /** Get the number of elements in this data block and all below it
    * @return size_t containing number of elements contained
    */
   const size_t numElements() const;

   /** Get the number of values in this data block
    * @return size_t containing number of elements in this block
    */
   const size_t numValues() const;

   /** Get the number of block values
     *  @return The number of block values
     */
    size_t numBlockValues() const;

    /** Get the meta data associated with the class. This performs
     * transactions as neccessary for byte swapping (ie it makes it do
     * useful stuff on windowz).
     */
    EDR::MetaData& getMetaData();

	/** Get the value description of the indicated value
	 * @param valueIdx index of the value
	 * @return ValueDescr* pointer to the value description
	 */
	const ValueDescr* getValueDescr(size_t valueIdx) const;

   /** Get the array Index Id of this data block
    * @return size_t the array Index Id of this datablock
    */
   const int32 getArrayIndexId() const;

    /** Set the arrayIndexId
     *  @param arrayIndexId the Id to set
     */
   void setArrayIndexId(int32 arrayIndexId);

    /* Set the level of the datablock
     * @param level The new level
     */
    void level( size_t level );

	/** Return the level for the datablock
	 * @return size_t the level
	 */
	size_t getLevel() const;

    /** Global output operator
     *  @param os The output stream to use
     *  @param datablock Datablock to print
     */

	/** Get the factory pointer
	 */
	Factory* getFactory() const;

    /* Get the blocktype id of the block
     * @return The blocktype id
     */
    size_t blockTypeId() const;

    friend std::ostream& operator<<( std::ostream&             os,
									 const Datablock& datablock);


    /** Serialize the datablock to XML
     *  @param path   Partial xmlId
     *  @param xmlOut Output string for serialization
     *  @param markedOnly only dump the marked block when true
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addXmlEdrBlock( const char* path,
                         BAS::String& xmlOut,
                         bool markedOnly = false) const;
    /** Walk through a EDR container and set the marked flag in all un-cleared fields and datablocks
     */
    void markSetFields();


    /** Set the PinFldIdxMap pointer
     *  @param pinFldIdxMapPtr the pinFldIdx to set
     */
   void setPinFldIdxMapPtr(const EDR::DatablockDescr::PinFldNumIdxTableT* pinFldIdxMapPtr);

    //@}

  protected:
    
    /* Constructor
     */
    Datablock( Factory* factory,
                   size_t       blockTypeId,
                   size_t       numValues,
                   size_t       numBlocks );

    /* Copy constructor (is only used by the factory to duplicate prototypes)
     * @param other The datablock to copy
     */
    Datablock( const Datablock& other );

    /* Destructor
     */
    ~Datablock();

    /* Clone the datablock. This function is used by the factory to duplicate
     * the prototype datablocks.
     * @return Pointer to the cloned datablock
     */
    Datablock* clone() const;

    /* Copy the data from another datablock. This function is used by
     * the factory when EDR containers and their datablocks are duplicated
     * @param other Pointer to the source datablock
     */
    void copyData( const Datablock* other );

    /* Copy the data from another datablock. This function is used by
     * the factory when EDR containers and their datablocks are duplicated
     * The thread-safe-multi-factory version
     * @param other Pointer to the source datablock
     */
    void variantFactoryCopyData( const Datablock* other );

    /** Clear the entire datablock
     */
    void clearValues();

    /* Get the datablock's cache successor
     * @return Pointer to the cache successor (can be 0)
     */
    Datablock* cacheSucc() const;

    /* Set the datablock's cache successor
     * @param edr The new cache successor
     */
    void cacheSucc( Datablock* edr );

    /* Release all subblocks of this datablock and insert them into the factory
     */
    void releaseSubblocks();	

    /* Return true if the block is marked
     */
    bool isMarked() const;	

    /* Set the marked flag 
     */
    void setMarked(bool marked);	

  private:
    // Hide the default constructor and assignment operator
    Datablock();
    const Datablock& operator=( const Datablock& other );

    // instance members
    Factory*         factoryM;
    size_t               blockTypeIdM;
    size_t               levelM;
    Datablock*       cacheSuccM;
    size_t               numValuesM;
    Value**          valuesM;
    size_t               numBlockValuesM;
    DatablockValue** blockValuesM;
    const char *containerBufferM;
    EDR::MetaData metaDataM;

	/** Flist array index
	 * This is an int32 (defined in pcm), and has to be int, and not unsigned
	 * int, because -1 has a special meaning
	 */
    int32               arrayIndexIdM;  // This is flist array Index
    
    // class members

    //  Pointer to the PinFldNum-ValueIdx Map held in DataBlockDescr
    const EDR::DatablockDescr::PinFldNumIdxTableT*  pinFldNumIdxMapPtrM;

    EDR_EXPORT static size_t        illegalSubBlockStartIdxCM;

    bool markedM;

    friend class DatablockCache;
    friend class Container;
    friend class Factory;
    friend class DatablockValue;
};

std::ostream& operator<<(std::ostream& os, const Datablock& datablock);

//==============================================================================
// Get the cache successor
//==============================================================================
inline Datablock*
Datablock::cacheSucc() const
{
  return cacheSuccM;
}

//==============================================================================
// Set the cache successor
//==============================================================================
inline void 
Datablock::cacheSucc( Datablock* datablock )
{
  cacheSuccM = datablock;
}

//==============================================================================
// Set the level of the datablock
//==============================================================================
inline void
Datablock::level( size_t level )
{
  levelM = level;
}

inline size_t
Datablock::getLevel() const
{
	return levelM;
}

//==============================================================================
// Get the blocktype id
//==============================================================================
inline size_t
Datablock::blockTypeId() const
{
  return blockTypeIdM;
}

//==============================================================================
// Get the number of blockvalues inside the datablock
//==============================================================================
inline size_t
Datablock::numBlockValues() const
{
  return numBlockValuesM;
}

//==============================================================================
// Get the subblock by it's local subindex
//==============================================================================
inline DatablockValue*
Datablock::datablockValue( size_t index ) const
{
  RWPRECONDITION( index < numBlockValuesM );
  return blockValuesM[index];
}

//==============================================================================
// Get an EDR value by it's index
//==============================================================================
inline Value*
Datablock::value( size_t idx ) const
{
  RWPRECONDITION( idx < numValuesM );
  return valuesM[ idx ];
}
//==============================================================================
// Set the arrayIndexId
//==============================================================================
inline void
Datablock::setArrayIndexId(int32 arrayIndexId)
{
  arrayIndexIdM = arrayIndexId;
}

//==============================================================================
// Return the Container's mmlBuffer
//==============================================================================
inline const int32
Datablock::getArrayIndexId() const
{
  return arrayIndexIdM;
}
inline Factory* 
Datablock::getFactory() const
{
	return factoryM;
}
//==============================================================================
// Set the PinFldIdxMap pointer
//==============================================================================
inline void
Datablock::setPinFldIdxMapPtr(const EDR::DatablockDescr::PinFldNumIdxTableT* pinFldNumIdxMapPtr )
{
  pinFldNumIdxMapPtrM = pinFldNumIdxMapPtr;
}

//==============================================================================
// Get/Set the marked flag
//==============================================================================
inline bool 
Datablock::isMarked() const
{
	return markedM;
}
inline void 
Datablock::setMarked(bool marked) 
{
	markedM = marked;
}

}
#endif // DATABLOCK_HPP
