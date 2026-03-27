#ifndef IXT_EDRLONG_HPP
#define IXT_EDRLONG_HPP

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
//   Declaration of the class EdrLong
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

namespace IXT
{
class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{

/**<b><tt>EdrLong</tt></b> is the funtion class to access long values
 * in the edr container.
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
class EdrLong : public SCR::LongDataNode, public EdrValueAccess
{
  public:
    /**@name EdrLong constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrLong();

    //@

    /**@name EdrLong public methods */
    //@{

    /** Get the value from the EDR container
     *  @return The value
     */
    virtual int64 result();

    /** Set the value in the EDR container
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( int64 value );

    /** Factory for creation of edr access function
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

    /* Constructor
     * @param extension Pointer to the integRate iScript extension
     */
    EdrLong( Integrate*  extension,
                         SCR::StringNode* edrFieldNameNode = NULL, 
                         SCR::ArrayNode* indicesArrayNode = NULL,
                         SCR::LongNode* noOfIndicesNode = NULL);

    bool flagM;
    SCR::StringNode* edrFieldNameNodeM;
    SCR::ArrayNode* indicesArrayNodeM;
    SCR::LongNode* noOfIndicesNodeM;


  private:
    // Hide copy and default constructor
    EdrLong();
    EdrLong( const EdrLong& other );
    const EdrLong& operator=( const EdrLong& other );
};
}
#endif // EDRLONG_HPP
