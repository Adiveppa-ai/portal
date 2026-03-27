#ifndef LRP_OUTPUTWRITE_HPP
#define LRP_OUTPUTWRITE_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the function node for the iScript function outputWrite().
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: cdiab
//
// $RCSfile: OutputWrite.hpp,v $
// $Revision: 1.0 $
// $Author: cdiab $
// $Date: 2002/05/22 12:10:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OutputWrite.hpp,v $
// Revision 1.0  2002/05/22 12:10:57  cdiab
// - creation
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
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
}
namespace LRP
{
class IScriptOutExt;

/** <b><tt>OutputWrite</tt></b> is the function node for writing directly 
 *  from the output grammar to the output stream.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: OutputWrite.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.0 $</font></td>
 *  <td><font size=-1>$Date: 2002/05/22 12:10:57 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class OutputWrite : public SCR::LongNode
{
  public:
    /**@name OutputWrite constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~OutputWrite();

    //@}


    /**@name OutputWrite public methods */
    //@{

    /** Execute the outputWrite() function
     *  @return The number of bytes written to the output
     */
    virtual int64 result();

    /** Factory for creation of the function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );
    //@}

  protected:

    /* Constructor
     * @param outExtension Pointer to assciated output extension
     * @param value Pointer to the string to write to the output
     */
    OutputWrite( IScriptOutExt* outExtension,
		     SCR::StringNode*    value);
    
  private:
    // Hide copy constructor and assignment operator
    OutputWrite( const OutputWrite& );
    const OutputWrite operator=( const OutputWrite& );

    // Instance members
    IScriptOutExt* outExtensionM;
    SCR::StringNode*    valueM;
};
}
#endif // OUTPUTWRITE_HPP
