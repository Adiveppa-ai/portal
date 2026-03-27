#ifndef EDR_VALUEDESCR_HPP
#define EDR_VALUEDESCR_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class ValueDescr.
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
// $RCSfile: ValueDescr.hpp,v $
// $Revision: 1.4 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ValueDescr.hpp,v $
// Revision 1.4  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.3  2001/08/07 12:58:46  mwriedt
// - PETS #37618: Code Review.
//
// Revision 1.2  2001/04/12 12:38:14  sd
// - Update for the new module structure
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.2  2000/12/06 09:33:28  sd
// - Backup version.
//
// Revision 1.1  2000/10/17 08:41:54  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
#ifndef   _PCM_H
  #include "pcm.h"
#endif
#ifndef   _PIN_FLDS_H
  #include "pin_flds.h"
#endif

namespace EDR
{
/** <b><tt>ValueDescr</tt></b> is used to save the information about single
 *  EDR values inside the Factory. A value description consists of the
 *  name, the type, and the index inside a datablock.
 */
class ValueDescr D_THREADINFO
{
  D_SINGLETHREADED

  // CodeReview - 08.2001 - mwriedt - C - missing in doc (UML)
  // Checked by CodeReview - 08.2001 - sd - C - is is not necessary to add
  //                                            all helper classes to UML doc

  public:
	/** The infranet data dictionary flags. 
	 * EDR_OPTIONAL means that the field is optional in the container at the
	 * time of creation.
	 * EDR_REQUIRED means that the field is required in the container at the
	 * time of creation.
	 * EDR_PROHIBITED means that the field is prohibited in the container at
	 * the time of creation.
	 * EDR_NOTCACHED means that the field is not stored in the container and
	 * should be skipped over.
	 */
	enum FlagtypeT 
	{
		EDR_OPTIONAL,
		EDR_REQUIRED,
		EDR_PROHIBITED,
		EDR_NOTCACHED
	};

    /**@name ValueDescr constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the value
     *  @param type The type of the value
	 *  @param flag the flag associated with this field
     */
    ValueDescr(const BAS::String& name,
			   const BAS::String& type,
			   const BAS::String& flag);

    /** Destructor
     */
    ~ValueDescr();

    //@}

    /**@name ValueDescr public methods */
    //@{

    /** Get the typename
     *  @return Reference to the typename string
     */
    const BAS::String& type() const;

    /** Get the datatype 
     *  @return Value as specified in FieldDescr
     */
    int64 datatype() const;

    /** Get the value name
     *  @return Reference to the value name
     */
    const BAS::String& name() const;

    /** Set the index for a value
     *  @param The index for that value
     */
    void index( size_t idx );
    
    /** Get the index for the value
     *  @return The index of this value
     */
    size_t index() const;

    /** Get the used flag 
     *  @return The used flag
     */
    int used() const;

    /** Set the used flag
     */ 
    void used( int flag );

    /** Get the pin_fld_num
     *  @return The pin_fld_num
     */
    pin_fld_num_t getPinFldNum() const;

    /** Set the pin_fld_num
     *  @param The pin_fld_num
     */
    void setPinFldNum(pin_fld_num_t fldNum);

	/** Get the flag type
	 * @return type of the flag
	 */
	const FlagtypeT getFlagtype() const;

    /** Get Container Description (like in containerDesc.dsc)
     * @return Container Description Text
     */
    BAS::String getContainerDescrStr() const;

    //@}

  private:
    // Hide the default constructor etc
    ValueDescr();

    // instance members
    BAS::String           nameM;
    BAS::String           typeM;
	FlagtypeT           flagM;
    size_t               indexM;
    int                  usedM;
    pin_fld_num_t        fldNumM;

};

typedef RWTPtrOrderedVector<ValueDescr> ValueDescrVector;

//==============================================================================
// Get the used flag
//==============================================================================
inline int
ValueDescr::used() const
{
  return usedM;
}

//==============================================================================
// Set the used flag
//==============================================================================
inline void
ValueDescr::used( int flag )
{
  usedM = flag;
}
//==============================================================================
// Get the field number
//==============================================================================
inline pin_fld_num_t
ValueDescr::getPinFldNum() const
{
  return fldNumM;
}

//==============================================================================
// Set the fldNum
//==============================================================================
inline void
ValueDescr::setPinFldNum( pin_fld_num_t fldNum )
{
  fldNumM = fldNum;
}

}
#endif // VALUEDESCR::HPP
