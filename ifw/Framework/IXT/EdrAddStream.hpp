#ifndef IXT_EDRADDSTREAM_HPP
#define IXT_EDRADDSTREAM_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrAddStream
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Shivaram Radhakrishna
//
//------------------------------------------------------------------------------
//
// Revision 1.0  2003/08/11 shiva
// PRSF00046362: Support for addStream
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{
class Integrate;

/**<b><tt>EdrAddStream</tt></b> is the function class for adding new
 * datablocks to the edr container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrAddStream.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrAddStream : public SCR::BoolNode
{
  public:
    /**@name EdrAddStream constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrAddStream();

    //@

    /**@name EdrAddStream public methods */
    //@{

    /** Add the supplemental stream number
     *  @return  (>=0) on success, < 0 otherwise
     */
    virtual bool result();

    /** Factory for creation of edr field
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}
    
  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrAddStream( Integrate* extension,
                                    SCR::LongNode* streamNumberNode );

  private:
    // Hide default and copy constructor
    EdrAddStream();
    EdrAddStream( const EdrAddStream& other );
    const EdrAddStream& operator=( const EdrAddStream& other );

    // Instance members
    Integrate* extensionM;
    SCR::LongNode*  streamNumberNodeM;

};
}
#endif // EDRADDSUPPLEMENTALSTREAMNUMBER_HPP
