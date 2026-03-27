#ifndef SCR_CRYPT_HPP
#define SCR_CRYPT_HPP
//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of class Crypt. 
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
// $RCSfile: Crypt.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:10 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Crypt.hpp,v $
// Revision 1.2  2001/07/06 09:34:01  sd
// - User password removed
//
// Revision 1.1  2001/07/05 12:43:07  sd
// - PETS #36608 - Support for encrypted iScripts
//
//==============================================================================

#if !defined SCR_EXPORT
    #define SCR_EXPORT 
#endif

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace SCR
{
/** <b><tt>Crypt</tt></b> is used to encrpyt/decrypt iScripts.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Crypt.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:10 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Crypt
{
  public:
    /**@name Crypt constructors and destructor */
    //@{

    //@}


    /**@name Crypt public methods */
    //@{

    /** Encrypt a string
     */
    static bool encrypt( const BAS::String& source,
                         BAS::String&       destination );

    /** Decrypt a string
     */
    static bool decrypt( const BAS::String& source,
                         BAS::String&       destination );

    //@}

  protected:

    /* Get the hexadecimal string for a character
     * @param character The character to convert
     * @return The hexadecimal string
     */
    static BAS::String hexString( unsigned char character );

    /* Get a hexadecimal encoded character
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    static bool charFromHex( const char*& ptr, unsigned char& value );

  private:
    // Class members
    SCR_EXPORT static const BAS::String magicNumberCM;
    SCR_EXPORT static const int        maxColumnsCM;
};
}
#endif // CRYPT_HPP
