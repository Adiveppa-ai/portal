#ifndef SCR_STRTOHEXSTR_HPP
#define SCR_STRTOHEXSTR_HPP

//==============================================================================
//
// Copyright (c) 2003, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of an iScript function node to convert each character
//   in a string into its hexadecimal equivalent in a new string.  The
//   input string may contain embedded nulls, but multibyte characters
//   will not be handled correctly.
//
//   E.g: "ABC + 123!" -> "414243202B2031323321"
//                          A B C   +   1 2 3 !
//
//------------------------------------------------------------------------------
// Log: PRSF00035033 17-Mar-2003 keshav
// Initial revision
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;

/** <b><tt>StrToHexStr</tt></b> is the iScript function node
 *  for the conversion of each char in a string into its hexadecimal
 *  equivalent in a new string.<p>The input string may contain
 *  embedded nulls, but multibyte characters will.
 */
class StrToHexStr : public StringNode
{
  public:
    /**@name StrToHexStr constructors and destructor */
    //@{

    /** Destructor.
     */
    virtual ~StrToHexStr();

    //@}


    /**@name StrToHexStr public methods */
    //@{

    /** Convert each char in a string into its hexadecimal equivalent
     *  in a new string.  The input string may contain embedded nulls,
     *  but it must not contain multibyte characters.
     *  @return The result string
     */
    virtual const BAS::String& result();

    /** Create a strToHexStr() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> to function node on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:
    
    /* Constructor.
     * @param strNode Pointer to the parameter function node
     */
    StrToHexStr( StringNode* strNode );

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    StrToHexStr( const StrToHexStr& other );
    const StrToHexStr& operator=( const StrToHexStr& other );

    // instance members
    StringNode* strNodeM;
    BAS::String      resultM;
};
}
#endif // STRTOHEXSTR_HPP
