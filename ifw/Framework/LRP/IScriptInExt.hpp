#ifndef LRP_ISCRIPTINEXT_HPP
#define LRP_ISCRIPTINEXT_HPP

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
//   Declaration of the iScript extension used in the LRP input plugin.
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
// $RCSfile: IScriptInExt.hpp,v $
// $Revision: 1.9 $
// $Author: cdiab $
// $Date: 2001/11/21 11:56:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: IScriptInExt.hpp,v $
// Revision 2.0  2006/03/22 16:50:35  knijhawa
// Added new function currentTokenIndex()
// 
// Revision 1.9  2001/11/21 11:56:48  cdiab
// PETS #41920 : add a callback to the grammar for error processing
// Added a callback from the input parser to the input grammar through a
// function named onParseError(), providing the following variables:
// ERROR_TOKEN_ASC, ERROR_TOKEN_HEX, ERROR_TOKEN_HEXARRAY, ERROR_TOKEN_BYTEPOS
//
// Revision 1.8  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.7  2001/06/21 10:17:38  sd
// - FRM::FileDescr renamed to FRM::StreamDescr
//
// Revision 1.6  2001/04/26 09:30:30  sd
// - Integrate extension is now initialized correctly by the input parser
//
// Revision 1.5  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.4  2001/04/10 13:48:08  sd
// - New interface to the iScript input extension (pushEDR())
//
// Revision 1.3  2001/04/04 09:22:30  sd
// - Backup version
//
// Revision 1.2  2001/04/03 08:15:30  sd
// - Full iScript support
//
// Revision 1.1  2001/03/20 09:03:35  sd
// - iScript extension renamed
//
//==============================================================================

#if !defined LRP_EXPORT
  #if defined(WINDOWS)
    #if !defined(LRP_INTERNAL)
      #define LRP_EXPORT __declspec(dllimport)
    #else
      #define LRP_EXPORT __declspec(dllexport)
    #endif
  #else
    #define LRP_EXPORT 
  #endif
#endif

#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
#ifndef   SCR_ARRAY_HPP
  #include "SCR/Array.hpp"
#endif
#ifndef   SCR_EXTENSION_HPP
  #include "SCR/Extension.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   EDR_TOKEN_HPP
  #include "EDR/Token.hpp"
#endif

namespace PLG
{
class InputDevice;
}
namespace LRP
{
class LexicalAnalyser; 

/** <b><tt>IScriptInExt</tt></b> is the iScript extension used inside the
 *  generic input plugin.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: IScriptInExt.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.9 $</font></td>
 *  <td><font size=-1>$Date: 2001/11/21 11:56:48 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class IScriptInExt : public SCR::Extension
{
  public:
    /**@name IScriptInExt constructors and destructor */
    //@{

    /** Constructor
     *  @param analyser The lexical analyser 
     *  @param inputDevice Pointer to the input device with pushEdr() function
     */
    IScriptInExt( LexicalAnalyser* analyser,
                      PLG::InputDevice*     inputDevice );

    /** Destructor
     */
    virtual ~IScriptInExt();

    //@}


    /**@name IScriptInExt public methods */
    //@{

    /** Get the name of the extension
     *  @return Reference to the string with the name of the extension
     */
    virtual const BAS::String& extensionName() const;

    /** Get a variable by it's name
     *  @param name The name of the variable
     *  @return Pointer to the variable on success, 0 otherwise
     */
    virtual SCR::Variable* variable( const BAS::String& name );

    /** Get the pointer to the lexical analyser
     *  @return Pointer to lexical analyser
     */
    LexicalAnalyser* lexicalAnalyser() const;

    /** Add a new token to the extension
     *  @param token Pointer to the new token
     */
    void nextToken( EDR::Token* token );

    /** Get the current token from the extension
     *  @return Pointer to the current token
     */
    EDR::Token* currentToken() const;

    /** Get the current token index from the extension
     *  @return Index of the current token, else -1
     */
    int64 currentTokenIndex() const;

	/** Remove the current token from the stack
	 */
	void removeCurrentToken();

    /** Push the new EDR container(s) to the output queue
     *  @param edrVector Vector with EDR container(s) to push
     */
    void pushEDR( RWTPtrOrderedVector<EDR::Container>& edrVector );

    /** Reset the extension
     */
    void reset();

    /** Get the pointer to the input device
     *  @return Pointer to the input device if existent, 0 otherwise
     */
    PLG::InputDevice* inputDevice() const;

    /** Update iScript Global variables accessible in the input Grammar
     *  @param token The last token which was red (and which caused problems)
     */
    void updateForErrorProcessing(EDR::Token* token);

    /** Add a new identifier to the actual statement list 
     *  @param identifier Identifier of this value
     *  @param value Variable to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addIdentifier( const BAS::String& identifier,
                        SCR::Variable*     value );

    //@}

  private:
    // Hide the copy constructor etc.
    IScriptInExt( const IScriptInExt& rhs );
    const IScriptInExt& operator=( const IScriptInExt& rhs );

    // Instance members
    LexicalAnalyser*           lexicalAnalyserM;
    RWTPtrOrderedVector<EDR::Token> tokenStackM;
    PLG::InputDevice*               inputDeviceM;
    size_t                         numLookAheadSymbolsM;
    
    SCR::VariableMap		   variablesM;
    SCR::StringVariable*		   errorTokenAscM;
    BAS::String			   errorTokenAscBufM; // for performance
    SCR::StringVariable*		   errorTokenHexM;
    BAS::String			   errorTokenHexBufM; // for performance
    SCR::Array*			   errorTokenArrayM;
    SCR::LongVariable*		   errorTokenBytePosM;

    // Class members
    LRP_EXPORT static SCR::VariableMap  constantsCM;
    LRP_EXPORT static RWMutexLock      mutexCM;
    LRP_EXPORT static int              instancesCM;

  public:
    // Public lass members
    LRP_EXPORT static const BAS::String extensionNameCM;
};

//==============================================================================
// Get the pointer to the current token
//==============================================================================
inline EDR::Token*
IScriptInExt::currentToken() const
{
  size_t numTokens = tokenStackM.entries();
  if ( numTokens > numLookAheadSymbolsM )
  {
    return tokenStackM( numTokens-numLookAheadSymbolsM-1 );
  }
  else
  {
    return 0;
  }
}

//==============================================================================
// Get the index of the current token
//==============================================================================
inline int64
IScriptInExt::currentTokenIndex() const
{
  size_t numTokens = tokenStackM.entries();
  if ( numTokens > numLookAheadSymbolsM )
  {
    return (numTokens-numLookAheadSymbolsM-1);
  }
  else
  {
    return -1;
  }
}

//==============================================================================
// Get the pointer to the lexical analyser
//==============================================================================
inline LexicalAnalyser*
IScriptInExt::lexicalAnalyser() const
{
  return lexicalAnalyserM;
}

//==============================================================================
// Get the pointer to the input device
//==============================================================================
inline PLG::InputDevice*
IScriptInExt::inputDevice() const
{
  return inputDeviceM;
}
}
#endif // ISCRIPTINEXT_HPP
