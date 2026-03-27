#ifndef LRP_EDRNEWXML_HPP
#define LRP_EDRNEWXML_HPP

//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
//
// Revision 1.0  2003/11/19  ammon
// PRSF00068378  Created.
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

/** <b><tt>EdrNewXml</tt></b> is the function node for creating
 *  new edr containers from XML in the input plugin.
 */
class EdrNewXml : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name EdrNewXml constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrNewXml();

    //@}


    /**@name EdrNewXml public methods */
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
    EdrNewXml( IXT::Integrate* integrateExtension,
               IScriptInExt*   lrpExtension );
    
  private:
    // Hide copy constructor and assignment operator
    EdrNewXml( const EdrNewXml& );
    const EdrNewXml operator=( const EdrNewXml& );

    // Instance members
    IXT::Integrate* integrateExtensionM;
    IScriptInExt*   lrpExtensionM;
    EDR::Factory*   factoryM;
};
}
#endif // EDRNEWXML_HPP
