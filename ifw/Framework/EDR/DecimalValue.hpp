#ifndef EDR_DECIMALVALUE_HPP
#define EDR_DECIMALVALUE_HPP

//==============================================================================
//
// Copyright (c) 1996, 2024, Oracle and/or its affiliates. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class DecimalValue.
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
// $RCSfile: DecimalValue.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:43 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.9  2012/05/11 Santanu 
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
//
// Revision 1.8  2004/03/10 ammon
// PRSF00098531 Add setString()
//
// Revision 1.7  2002/01/15 09:28:23  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.6  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.5  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.4  2001/07/02 10:51:48  sd
// - - PETS #36553/2 Input of AscDate("%H%M%S") failed without error
//
// Revision 1.3  2001/04/12 12:38:14  sd
// - Update for the new module structure
//
// Revision 1.2  2001/03/30 12:49:44  sd
// - Changes to support duplication of EDR containers
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.11  2001/03/20 15:01:32  sd
// - ByteBuffer introduced
//
// Revision 1.9  2001/03/14 09:29:33  sd
// - Constants introduced in input mapping
//
// Revision 1.7  2001/03/12 09:59:31  sd
// - Backup version
//
// Revision 1.5  2001/03/08 15:07:51  sd
// - Backup version
//
// Revision 1.3  2000/12/06 09:33:28  sd
// - Backup version.
//
// Revision 1.2  2000/10/20 10:02:01  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif
#ifndef   EDR_VALUE_HPP
  #include "EDR/Value.hpp"
#endif
namespace EDR
{
/** <b><tt>DecimalValue</tt></b> is the decimal datatype inside the edr
 *  container.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DecimalValue.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:43 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>                
 */
class DecimalValue : public Value D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name DecimalTimeValue constructors and destructor */
    //@{

    /** Default constructor
     */
    DecimalValue();

    /** Destructor
     */
    virtual ~DecimalValue();

    //@}


    /**@name DecimalTimeValue public methods */
    //@{

    /** Get the datatype of the value
     *  @return Bitvalue specifing the datatype as defined in FieldDescr
     */
    virtual int64 datatype() const;

    /** Clone the string value
     *  @return Pointer to the cloned string value
     */
    virtual Value* clone() const;

    /** Get a decimal value
     *  @return The decimal value
     */
    virtual const BAS::Decimal& getDecimal() const noexcept(false);

    /** Set the a decimal value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDecimal( const BAS::Decimal& value );

    /** Get the decimal value as string
     *  @return The decimal value as string
     */
    virtual const BAS::String& getString() const noexcept(false);

    /* Copy the data from another DecimalValue. This function is only used
     * when Datablocks will by duplicated. 
     * @param value The source Value 
     */
    virtual void copyData( Value* value );

    /* Copy the data from another DecimalValue. This function is only used
     * in Linux and Solaris when Datablocks will by duplicated.
     * @param value The source Value
     */
    virtual void memberWiseCopyData( Value* value ) noexcept(false);

    /** Serialize the EDR value
     *  @param out Output stream for serialization
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool serialize( std::ostream& out ) const;

    /** Restore the decimal value
     *  @param in Input stream 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool restore( std::istream& in );

    /** Get the serialized Buffer
     *  @return the serialized buffer
     */
    virtual EDR::ByteBuffer&  getSerializedBuffer();

    /** Set the a string value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setString( const BAS::String& value );

    //@}

  protected:

    /* Flush the data to the output byte buffer
     * @param buffer Output buffer
     * @param outField The output field description
     * @param len The length for the output data
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool flushNormal( ByteBuffer& buffer,
                              FieldDescr* outField,
                              size_t          len );

  private:

    // instance members
    BAS::Decimal dataM;
    BAS::String  stringDataM;
    BAS::Decimal restoredDataM;
};
}
#endif // DECIMALVALUE_HPP
