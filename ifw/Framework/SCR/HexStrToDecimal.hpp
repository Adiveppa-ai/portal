#ifndef SCR_HEXSTRTODECIMAL_HPP
#define SCR_HEXSTRTODECIMAL_HPP

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
//   Declaration of an iScript function node for the conversion from a
//   hexadecimal string to Decimal.
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
// $RCSfile: HexStrToDecimal.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:23 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: HexStrToDecimal.hpp,v $
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

/** <b><tt>HexStrToDecimal</tt></b> is the iScript function node for the 
 *  conversion from hexadecimal strings to Decimal values .
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HexStrToDecimal.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:23 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HexStrToDecimal : public DecimalNode
{
  public:
    /**@name HexStrToDecimal constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~HexStrToDecimal();

    //@}


    /**@name HexStrToDecimal public methods */
    //@{

    /** Convert a hexadecimal string to a Decimal value
     *  @return The result decimal value
     */
    virtual const BAS::Decimal& result();

    /** Create a strHexToDecimal() function node
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
     * @param stringNode node containing the String to convert
     * @param pointChar the character to use as decimal separator
     * @param precision the precision of the decimal value to generate
     */
    HexStrToDecimal(StringNode* stringNode,
    			char		pointChar,
			int64		precision);

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    HexStrToDecimal( const HexStrToDecimal& other );
    const HexStrToDecimal& operator=( const HexStrToDecimal& other );

    // instance members
    StringNode* stringNodeM;
    char	    pointCharM;
    int64	    precisionM;
    BAS::Decimal     resultM;
};
}
#endif // HEXSTRTODECIMAL_HPP
