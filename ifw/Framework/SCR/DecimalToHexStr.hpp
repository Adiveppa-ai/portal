#ifndef SCR_DECIMALTOHEXSTR_HPP
#define SCR_DECIMALTOHEXSTR_HPP

//==============================================================================
//
// Copyright (c) 1995, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//
//	This material is the confidential property of Oracle Corporation.
//	or its subsidiaries or licensors and may be used, reproduced,
//	stored or transmitted only in accordance with a valid Oracle
//	license or sublicense agreement
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of an iScript function node for the conversion from Decimal
//   to a hexadecimal string.
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
// $RCSfile: DecimalToHexStr.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:35 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DecimalToHexStr.hpp,v $
// Revision 1.3  2001/10/09 14:17:58  cdiab
// PETS #40224: need 2 iScript methodes for conversion from/to strHex to/from Decimal
// added a 'precison' optional parameter to the conversion functions (default=0)
//
// Revision 1.2  2001/10/08 15:39:34  cdiab
// PETS #40224: need 2 iScript methodes for conversion from/to strHex to/from Decimal
// now the conversion uses conversion methodes built directly in BAS::Decimal.
//
// Revision 1.1  2001/10/08 08:33:17  cdiab
// PETS #40224: need 2 iScript methodes for conversion from/to strHex to/from Decimal.
//
// Revision 1.0  2001/10/05 12:14:03  cdiab
// - Creation
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
namespace SCR
{

class Interpreter;
class ParserStack;
class FctDescr;

/** <b><tt>DecimalToHexStr</tt></b> is the iScript function node for the 
 *  conversion from Decimal values to hexadecimal strings.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DecimalToHexStr.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalToHexStr : public StringNode
{
  public:
    /**@name DecimalToHexStr constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DecimalToHexStr();

    //@}


    /**@name DecimalToHexStr public methods */
    //@{

    /** Convert a Decimal value to a hexadecimal string
     *  @return The result string
     */
    virtual const BAS::String& result();

    /** Create a decimalToHexStr() function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> to function node on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:
    
    /* Constructor
     * @param decimalNode node containing the Decimal value to convert
     * @param pointChar the character to use as decimal separator
     * @param precision the precision of the decimal value to use
     */
    DecimalToHexStr(DecimalNode* decimalNode,
    			char		 pointChar,
			int64		 precision );

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    DecimalToHexStr( const DecimalToHexStr& other );
    const DecimalToHexStr& operator=( const DecimalToHexStr& other );

    // instance members
    DecimalNode* decimalNodeM;
    char	     pointCharM;
    int64	     precisionM;
    BAS::String       resultM;
};
}
#endif // DECIMALTOHEXSTR_HPP
