#ifndef LRP_EDRNEW_HPP
#define LRP_EDRNEW_HPP

//==============================================================================
//
//   Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//   
//   This material is the confidential property of Oracle Corporation or its
//   licensors and may be used, reproduced, stored or transmitted only in
//   accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the function node for the iScript function edrNew().
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
// $RCSfile: EdrNew.hpp,v $
// $Revision: 1.3 $
// $Author: sd $
// $Date: 2001/04/26 15:23:25 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrNew.hpp,v $
// Revision 1.3  2001/04/26 15:23:25  sd
// - EDR::ContainerIndex introduced
//
// Revision 1.2  2001/04/23 15:21:42  sd
// - Adjusted to use new class EDR::BlockIndex.
//
// Revision 1.1  2001/04/12 12:21:47  sd
// - Update for splitting LRP/FRM::Base
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   LRP_LEXICALANALYSER_HPP
  #include "LRP/LexicalAnalyser.hpp"
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
class IScriptInExt;

/** <b><tt>EdrNew</tt></b> is the function node for creating
 *  new edr containers in the input plugin.
 */
class EdrNew : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name EdrNew constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrNew();

    //@}


    /**@name EdrNew public methods */
    //@{

    /** Execute the edrNew() function
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

    /** Check whether the function node is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

    //@}

  protected:

    /* Constructor
     * @param extension Pointer to the iScript extension
     * @param containerName Name of the container to create
     */
    EdrNew( IXT::Integrate*              integrateExtension,
                IScriptInExt*           lrpExtension,
                const BAS::String&           containerName,
                EDR::Container::contentTypeT contentType );
    
  private:
    // Hide copy constructor and assignment operator
    EdrNew( const EdrNew& );
    const EdrNew operator=( const EdrNew& );

    // Instance members
    IXT::Integrate*              integrateExtensionM;
    IScriptInExt*           lrpExtensionM;
    EDR::Factory*                factoryM;
    EDR::ContainerIndex          edrIndexM;
    EDR::Container::contentTypeT contentTypeM;
    bool                        isValidDetailM;
};
}
#endif // EDRNEW_HPP
