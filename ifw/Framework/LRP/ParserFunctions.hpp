#ifndef LRP_PARSERFUNCTIONS_HPP
#define LRP_PARSERFUNCTIONS_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Functions and helper classes used by the parser of the input grammar.
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
// $RCSfile: ParserFunctions.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2001/03/07 11:44:49 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ParserFunctions.hpp,v $
// Revision 1.2  2001/03/07 11:44:49  sd
// - Backup
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace LRP
{
//==============================================================================
// Types
//==============================================================================
typedef struct RuleDescription
{
    BAS::String     leftSideM;
    BAS::StringList rightSideM;
    int            lineNumberM;

#ifdef __aix
    bool operator==( const RuleDescription& other ) const
    {
      return( this == &other );
    }
    bool operator<( const RuleDescription& other ) const
    {
      return( this < &other );
    }
#endif
} RuleDescription;

typedef struct ActionDescription
{
    BAS::String     leftSideM;
    BAS::String     actionM;

#ifdef __aix
    bool operator==( const ActionDescription& other ) const
    {
      return( this == &other );
    }
    bool operator<( const ActionDescription& other ) const
    {
      return( this < &other );
    }
#endif
} ActionDescription;

typedef enum
{
  IN_MAPPING,
  OUT_MAPPING
} MappingModeT;
}

//==============================================================================
// External functions
//==============================================================================
extern char* yytext;
extern int  lex();
extern int  parse();
extern void error();
extern int  initMappingLexer( const BAS::String& fileName, 
                                  const BAS::String& mapping );
extern int  initGrammarLexer( const BAS::String& fileName, 
                                  const BAS::String& grammar );
extern int  initFileDescrLexer( const BAS::String& fileName,
                                    const BAS::String& fileDescr );
extern int  lineNumber();
extern const char* yytext();
extern const BAS::String& fileName();
extern void switchToIScriptMode( bool flag );
extern const BAS::String& iScriptSource();

#endif // PARSERFUNCTIONS_HPP
