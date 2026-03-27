#ifndef IXT_EDRDECIMAL_HPP
#define IXT_EDRDECIMAL_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrDecimal.
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
// $RCSfile: EXT_OutFileManager.cpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/04/03 14:28:08 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_OutFileManager.cpp,v $
//==============================================================================

#ifndef   SCR_DATA_HPP
  #include "SCR/Data.hpp"
#endif
#ifndef   IXT_EDRVALUEACCESS_HPP
  #include "IXT/EdrValueAccess.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{
/**<b><tt>EdrDecimal</tt></b> is the function class to access decimal 
 * values in the edr container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrDecimal : public SCR::DecimalDataNode, public EdrValueAccess
{
  public:
    /**@name EdrDecimal constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrDecimal();

    //@

    /**@name EdrDecimal public methods */
    //@{

    /** Get the value from the edr container
     *  @return The value
     */
    virtual const BAS::Decimal& result();

    /** Set the edr container value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( const BAS::Decimal& value );

    /** Factory for creation of edr field
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    static SCR::Node* otherFactory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}
    
  protected:

    /** Constructor
     *  @param extension Pointer to the integrate iScript extension
     */
    EdrDecimal( Integrate* extension,
                         SCR::StringNode* edrFieldNameNode = NULL, 
                         SCR::ArrayNode* indicesArrayNode = NULL,
                         SCR::LongNode* noOfIndicesNode = NULL);

    bool flagM;
    SCR::StringNode* edrFieldNameNodeM;
    SCR::ArrayNode* indicesArrayNodeM;
    SCR::LongNode* noOfIndicesNodeM;


  private:
    // Hide default and copy constructor
    EdrDecimal();
    EdrDecimal( const EdrDecimal& other );
    const EdrDecimal& operator=( const EdrDecimal& other );
};
}
#endif // EDRDECIMAL_HPP
