#ifndef SCR_HASH_HPP
#define SCR_HASH_HPP

//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the iScript array class.
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
// $RCSfile: Hash.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:10 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Hash.hpp,v $
// Revision 1.5  2001/09/25 11:30:02  sd
// - PETS #39831 Missing iScript function hashRemove()
//
// Revision 1.4  2001/04/10 15:05:12  sd
// - New function hashKeys() to retrieve the key values of a hash
//
// Revision 1.3  2000/10/09 10:16:43  sd
// - New function hashContains() added
//
// Revision 1.2  2000/10/09 10:01:08  sd
// - Function clear() added.
//
// Revision 1.1  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
//==============================================================================

#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
namespace SCR
{

/**<b><tt>Hash</tt></b> is the variable class for iScript hash tables.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Hash.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:10 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Hash : public Variable
{
  public:

    typedef RWTPtrMapIterator<BAS::String,Variable,less<BAS::String> > 
      HashIterator;

    /**@name Hash constructors and destructor */
    //@{
    
    /** Constructor
     *  @param defaultValue The default array member value
     */
    Hash( Variable* defaultValue );

    /** Copy constructor
     *  @param other The value to copy
     */
    Hash( const Hash& other );

    /** Destructor
     */
    virtual ~Hash();

    //@}

    /**@name Hash public methods */
    //@{

    /** Clone the array
     *  @return Pointer to the cloned array
     */
    virtual Variable* clone() const;

    /** Access an hash value
     *  @parma key The key for the value to access
     *  @return Pointer to the hash value
     */
    Variable* find( const BAS::String& key );

    /** Remove a variable from the hash
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool remove( const BAS::String& key );

    /** Get the container datatype
     *  @return The container datatype
     */
    int containerType() const;

    /** Get the default value
     *  @return Pointer to default value
     */
    const Variable* defaultValue() const;

    /** Clear the hash
     */
    void clear();

    /** Check if the hash contains the key
     *  @param key The key to check
     *  @return <b>true</b> if the hash contains the key, <b>false</b> otherwise
     */
    bool contains( const BAS::String& key ) const;

    /** Get a iterator for the hash
     *  @return Iterator for the hash
     */
    RWTPtrMapIterator<BAS::String,Variable,less<BAS::String> > iterator();

    //@}

  private:
    // Hide the default constructor
    Hash();

    // instance members
    Variable*                                        defaultValueM;
    RWTPtrMap<BAS::String,Variable,less<BAS::String> > hashM;
};


//==============================================================================
// Check if the hash contains a key
//==============================================================================
inline bool
Hash::contains( const BAS::String& key ) const
{
  return hashM.contains( &key );
}

//==============================================================================
// Get an iterator for the hash
//==============================================================================
inline Hash::HashIterator
Hash::iterator()
{
  return HashIterator( hashM );
}
}
#endif // HASH_HPP
