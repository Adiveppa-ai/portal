#ifndef SCR_HEXSTRTOSTR_HPP
#define SCR_HEXSTRTOSTR_HPP

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
//   Implementation of an iScript function node to convert each pair
//   of characters in the input string into the equivalent single-byte
//   ascii character in a new string and return the new string.
//   The input string may contain embedded nulls, but multibyte
//   characters will not be handled correctly.
//
//   E.g: "414243202B2031323321" -> "ABC + 123!"
//          A B C   +   1 2 3 !
//
//------------------------------------------------------------------------------
// Log: PRSF00035033 18-Mar-2003 keshav
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

/** <b><tt>HexStrToStr</tt></b> is the iScript function node
 *  to convert each pair of characters in an input string into the
 *  equivalent single-byte ascii character in a new string and
 *  return the new string. The input string may contain "00"
 *  character pairs to represent embedded nulls, but representations
 */
class HexStrToStr : public StringNode
{
  public:
    /**@name HexStrToStr constructors and destructor */
    //@{

    /** Destructor.
     */
    virtual ~HexStrToStr();

    //@}


    /**@name HexStrToStr public methods */
    //@{

    /** Convert each pair of characters in the input string into the
     *  equivalent single-byte ascii character in a new string and
     *  return the new string. The input string may contain "00"
     *  character pairs to represent embedded nulls, but representations
     *  @return The result string
     */
    virtual const BAS::String& result();

    /** Create a HexStrToStr() function node.
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
    HexStrToStr( StringNode* strNode );

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    HexStrToStr( const HexStrToStr& other );
    const HexStrToStr& operator=( const HexStrToStr& other );

    // instance members
    StringNode* strNodeM;
    BAS::String      resultM;
};
}
#endif // HEXSTRTOSTR_HPP
