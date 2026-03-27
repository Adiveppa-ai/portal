#ifndef EDR_FIELDMAPKEY_HPP
#define EDR_FIELDMAPKEY_HPP

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
//   Declaration of the class FieldMapKey.
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
// $RCSfile: FieldMapKey.hpp,v $
// $Revision: 1.5 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FieldMapKey.hpp,v $
// Revision 1.5  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.4  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.3  2001/06/19 14:11:58  sd
// - Working EDR usage statistic
//
// Revision 1.2  2001/06/19 12:26:28  sd
// - Output for edr usage statistic added.
//
// Revision 1.1  2001/05/02 10:17:25  sd
// - Initial revision
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace EDR
{
/** <b><tt>FieldMapKey</tt></b> is the key class for looking up entries in
 *  the EDR field mapping table.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FieldMapKey.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class FieldMapKey  D_THREADINFO
{
  D_SINGLETHREADED

  // CodeReview - 08.2001 - mwriedt - C - missing in doc (UML)
  // Checked by CodeReview - 08.2001 - sd - C - is is not necessary to add
  //                                            all helper classes to UML doc
  public:
    /**@name FieldMapKey constructors and destructor */
    //@{

    /** Constructor
     *  @param def The default index to use
     *  @param key The logical key for the edr field
     *  @param reference The reference (context) for the mapping
     */
    FieldMapKey( const BAS::String& def,
                     const BAS::String& key,
                     const BAS::String& reference );


    /** Destructor
     */
    ~FieldMapKey();

    //@}


    /**@name FieldMapKey public methods */
    //@{

    /** Get the key
     *  @return Reference to the key
     */
    const BAS::String& key() const;

    /** Get the default value
     *  @return Reference to the default name
     */
    const BAS::String& defaultValue() const;

    /** Get the reference name
     *  @return Reference to the reference name
     */
    const BAS::String& reference() const;

    /** Comparison operator equal
     *  @param other The other element for the comparison
     */
    bool operator==( const FieldMapKey& other ) const;

    /** Comparison operator less
     *  @param other The other element for the comparison
     */
    bool operator<( const FieldMapKey& other ) const;
    
    //@}

  private:
    // Instance members
    BAS::String defaultM;
    BAS::String keyM;
    BAS::String referenceM;
};

//==============================================================================
// Get the default name
//==============================================================================
inline const BAS::String& 
FieldMapKey::defaultValue() const
{
  return defaultM;
}

//==============================================================================
// Get the key
//==============================================================================
inline const BAS::String& 
FieldMapKey::key() const
{
  return keyM;
}

//==============================================================================
// Get the reference
//==============================================================================
inline const BAS::String& 
FieldMapKey::reference() const
{
  return referenceM;
}
}

#endif // FIELDMAPKEY_HPP
