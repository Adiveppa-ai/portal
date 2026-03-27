#ifndef LRP_EDRCONNECTTOKEN_HPP
#define LRP_EDRCONNECTTOKEN_HPP
//==============================================================================
//
//          Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrConnectToken.
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

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   IXT_EDRVALUEACCESS_HPP
  #include "IXT/EdrValueAccess.hpp"
#endif
#ifndef   LRP_TOKENACCESS_HPP
  #include "LRP/TokenAccess.hpp"
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

/** <b><tt>EdrConnectToken</tt></b> is the iScript function not for 
 *  edrConnectToken().
 */
class EdrConnectToken : public SCR::BoolNode, 
                            public IXT::EdrValueAccess,
                            public TokenAccess
{
  public:
    /**@name EdrConnectToken constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrConnectToken();

    //@}


    /**@name EdrConnectToken public methods */
    //@{

    /** Execute the function.
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Initialize the token access object 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool initTokenAccess( const BAS::String& fieldName );

    /** Factory for creation of the function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
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
     *  @param extension Pointer to the integRate iScript extension
     *  @param inputExtension Pointer to the input iScript extension
     */
    EdrConnectToken( IXT::Integrate*    extension,
                         IScriptInExt* inputExtension,
                         SCR::StringNode* edrFieldNameNode = NULL, 
                         SCR::ArrayNode* indicesArrayNode = NULL,
                         SCR::LongNode* noOfIndicesNode = NULL,
                         SCR::StringNode* tokenFieldNameNode = NULL);

    bool flagM;
    SCR::StringNode* edrFieldNameNodeM;
    SCR::ArrayNode* indicesArrayNodeM;
    SCR::LongNode* noOfIndicesNodeM;
    SCR::StringNode* tokenFieldNameNodeM;
};
};
#endif // EDRCONNECTTOKEN_HPP
