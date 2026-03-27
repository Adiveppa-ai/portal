#ifndef SCR_PARSERFUNCTIONS_HPP
#define SCR_PARSERFUNCTIONS_HPP 

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
//   Functions used by the yacc parser. These functions have been moved from
//   file SCR_Yacc.y because of some problems with the templates database under
//   Solaris.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: ParserFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:03:29 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: SCR_ParserFunctions.hpp,v $
// Revision 1.14  2001/08/29 16:46:14  sd
// - PETS #38712 - iScript functions without parenthesis stop integRate
//
// Revision 1.13  2001/04/10 13:48:22  sd
// - return statement improved
//
// Revision 1.12  2001/04/10 10:50:35  sd
// - Full function support (inclusive return values)
//
// Revision 1.11  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.10  2000/11/02 11:37:12  sd
// - New regExprSwitch(), a switch/case for regular expressions.
//
// Revision 1.9  2000/10/12 15:24:33  sd
// - Implicit break removed again.
//
// Revision 1.7  2000/10/12 07:24:44  sd
// - Switch-case statement introduced.
//
// Revision 1.6  2000/09/27 07:08:01  sd
// - New interface for compilation of compare patters introduced.
//
// Revision 1.5  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.4  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.3  2000/04/27 11:52:01  sd
// - for loop added to iScript.
//
// Revision 1.2  2000/03/24 09:56:44  sd
// - Constants added.
// - Direct assignment in variable declarations added.
//
// Revision 1.1  2000/03/15 08:26:30  sd
// - Functions moved from SCR_Yacc.y to this file due to some problems with
//   the templates database under Solaris.
//
//==============================================================================

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
#ifndef SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif

namespace SCR
{
		class CustomLexer;
void YaccError(const BAS::String& msg, SCR::CustomLexer* lexer = 0);
}

// misc functions
extern bool SCR_useExtension( const BAS::String& name );
extern bool SCR_splitModuleIdentifier( const BAS::String& in,
                                       BAS::String&       module,
                                       BAS::String&       identifier );


// constants and variables
extern bool SCR_decimalConstant( const BAS::String& number );
extern bool SCR_boolConstant( const BAS::String& number );
extern bool SCR_longConstant( const BAS::String& number );
extern bool SCR_stringConstant( const BAS::String& string );
extern bool SCR_functionCall();
extern bool SCR_hashAccess();
extern bool SCR_arrayAccess();
extern bool SCR_identifier( const BAS::String& module,
                            const BAS::String& identifier );

// expressions
extern bool SCR_expression( const BAS::String& op );
extern bool SCR_negation();
extern bool SCR_ruleCondition();
extern bool SCR_comparePattern();

// declarations
extern bool SCR_variableDeclaration(      const BAS::String& type, 
                                          const BAS::String& identifier,
                                          const BAS::String& modifier );
extern bool SCR_constDeclaration(         const BAS::String& constKeyWord,
                                          const BAS::String& type,
                                          const BAS::String& identifier );
extern bool SCR_startFunctionDeclaration( const BAS::String& retType, 
                                          const BAS::String& identifier,
										  void *myLexer);
extern bool SCR_functionAddParameters();
extern bool SCR_endFunctionDeclaration();

extern SCR::Node* SCR_functionCallFactory( SCR::Interpreter&    interpreter,
                                          SCR::ParserStack&    stack,
                                          const SCR::FctDescr& descr );

// statements
extern bool SCR_ifStatement();
extern bool SCR_whileStatement();
extern bool SCR_doStatement();
extern bool SCR_doCondition();
extern bool SCR_createVoidCallStatement();
extern bool SCR_forLoop();
extern bool SCR_switchStatement();
extern bool SCR_regExprSwitchStatement();
extern bool SCR_caseStatement();
extern bool SCR_switchBreak();
extern bool SCR_returnStatement(bool withExpression);
extern bool SCR_switchDefault();
extern bool SCR_regExprFinalSetup();

//==============================================================================
// Extern variables
//==============================================================================
extern SCR::Interpreter*          actInterpreterG;
extern SCR::ParserStack           stackG;

#endif // SCR_PARSERFUNCTIONS_HPP
