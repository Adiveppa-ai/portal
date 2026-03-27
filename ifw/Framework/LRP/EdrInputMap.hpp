#ifndef LRP_EDRINPUTMAP_HPP
#define LRP_EDRINPUTMAP_HPP
//==============================================================================
//
//             1998, 1999, 2000 (c) Copyright by SOLUTION42 AG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the iScript function node for mapping data from input
//   file records to EDR container fields.
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
// $RCSfile: EdrInputMap.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/04/12 12:21:47 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrInputMap.hpp,v $
// Revision 1.1  2001/04/12 12:21:47  sd
// - Update for splitting LRP/FRM::Base
//
// Revision 1.1  2001/04/03 07:30:59  sd
// - Initial revision
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
namespace FRM
{
class InputMapping;
}
namespace LRP
{
class IScriptInExt;

/** <b><tt>EdrInputMap</tt></b> is the function node for mapping
 *  the fields of a file input record to the according edr fields.
 */
class EdrInputMap : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name EdrInputMap constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrInputMap();

    //@}


    /**@name EdrInputMap public methods */
    //@{

    /** Execute the edrInputMap() function
     *  @return The result of the function execution
     */
    virtual bool result();

    /** Factory for creation of the function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    /** Check whether the mapping description is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

    //@}

  protected:

    /* Constructor
     * @param integrateExtension Pointer to the integRate iScript extension
     * @param inputExtension Pointer to the input iScript extension
     * @param mappingDescr Name of the mapping description to use
     */
    EdrInputMap( IXT::Integrate*    integrateExtension,
                     IScriptInExt* inputExtension,
                     const BAS::String& mappingDescr );
    
  private:
    // Hide copy constructor and assignment operator
    EdrInputMap( const EdrInputMap& );
    const EdrInputMap operator=( const EdrInputMap& );

    // Instance members
    IXT::Integrate*    integrateExtensionM;
    IScriptInExt* inputExtensionM;
    FRM::InputMapping* inputMappingM;
};
}
#endif // EDRINPUTMAP_HPP
