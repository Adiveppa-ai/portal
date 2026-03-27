#ifndef EDR_ASCRAWSTRINGTYPE_HPP
#define EDR_ASCRAWSTRINGTYPE_HPP

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
//   Declaration of the class AscRawStringType.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Mike Ammon
//
//------------------------------------------------------------------------------
//
// Revision 1.0  2003/04/15 ammon
// - Created.
//
//==============================================================================

#ifndef   EDR_ASCSTRINGTYPE_HPP
  #include "EDR/AscStringType.hpp"
#endif

namespace EDR
{
/** <b><tt>AscRawStringType</tt></b> is the string datatype used in input 
 *  files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AscRawStringType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.0 $</font></td>
 *  <td><font size=-1>$Date: 2003/04/15 $</font></td>
 *  <td><font size=-1>$Author: ammon $</font></td>
 *  </tr>
 *  </table>
 */
class AscRawStringType : public AscStringType
{
  D_SINGLETHREADED

  public:
    /**@name AscRawStringType constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AscRawStringType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AscRawStringType();

    //@}

    /**@name AscRawStringType public methods */
    //@{

    /** Get the name of the datatype
     *  @return Reference to the name
     */
    virtual const BAS::String& typeName() const;

    /** Create a new string instance
     *  @param name The name of the input field inside the input record
     *  @return Pointer to the created instance
     */
    virtual FieldDescr* create( const BAS::String& name ) const;

    /** Get a string value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getString( const BAS::String& value,
                            size_t            pos,
                            size_t            len,
                            BAS::String&       buffer ) const;

    //@}

  private:
    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}

#endif // EDR_ASCRAWSTRINGTYPE_HPP
