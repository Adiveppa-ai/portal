#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

//=============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Serialize
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
// $RCSfile: Serialize.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:47:52 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Serialize.hpp,v $
// Revision 1.3.2.1  2002/02/15 13:55:10  sd
// - PETS #36397 - Serialization for EDR Container / merge from main
//                 branch
//
// Revision 1.3  2002/01/16 09:46:43  sd
// - Serialization for Integer values
//
// Revision 1.2  2002/01/15 10:49:43  sd
// - PETS #36397 - Serialization for EDR Container
//
//==============================================================================

#ifndef BAS_DEFS_HPP
  #include "BAS/Defs.hpp"
#endif
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif

/** <b><tt>Serialize</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Serialize.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 04:47:52 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
namespace BAS 
{
class Serialize
{
  public:
    /**@name Serialize constructors and destructor */
    //@{

    //@}


    /**@name Serialize public methods */
    //@{

    /** Serialize an unsigned long value 
     */
    static bool serializeULong( std::ostream& out, u_int64 value );

    /** Restore an unsigned long value
     */
    static bool restoreULong( std::istream& in, u_int64& value );
    
    /** Serialize a long value 
     */
    static bool serializeLong( std::ostream& out, int64 value );

    /** Serialize an integer value 
     */
    static bool serializeInt( std::ostream& out, int value );

    /** Restore a long value
     */
    static bool restoreLong( std::istream& in, int64& value );

    /** Restore a integer value
     */
    static bool restoreInt( std::istream& in, int& value );

    /** Restore a integer value
     */
    static bool restoreUInt( std::istream& in, u_int32& value );

    /** Serialize a boolean value 
     */
    static bool serializeBool( std::ostream& out, bool value );

    /** Restore a boolean value 
     */
    static bool restoreBool( std::istream& in, bool& value );

    /** Execute a self test
     */
    static bool selfTest();

    //@}

  private:
};
}
#endif // SERIALIZE_HPP
