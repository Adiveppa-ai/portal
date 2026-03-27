#ifndef LRP_TOKENFUNCTIONS_HPP
#define LRP_TOKENFUNCTIONS_HPP

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
//   Declaration of the iScript function nodes to access fields inside of 
//   tokens.
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
// $RCSfile: TokenFunctions.hpp,v $
// $Revision: 1.4 $
// $Author: sd $
// $Date: 2001/06/21 14:37:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TokenFunctions.hpp,v $
// Revision 1.4  2001/06/21 14:37:14  sd
// - new function writeOnReject()
//
// Revision 1.3  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.2  2001/04/03 08:15:30  sd
// - Full iScript support
//
// Revision 1.1  2001/04/02 11:40:52  sd
// - Initial revision
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   LRP_TOKENACCESS_HPP
  #include "LRP/TokenAccess.hpp"
#endif

namespace LRP
{
/** <b><tt>TokenString</tt></b> is the iScript function node class for 
 *  accessing string values in tokens.
 */
class TokenString : public SCR::StringNode, public TokenAccess
{
  public:
    /**@name TokenString constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~TokenString();

    //@}

    /**@name TokenString public methods */
    //@{

    /** Initialize the token string access object 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool initTokenAccess( const BAS::String& fieldName );

    /** Execute the function.
     *  @return Reference to function result 
     */
    const BAS::String& result();

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
     * @param extension Pointer to the iScript input extension
     * @param recordDescr Pointer to the recorddescription 
     */
    TokenString( IScriptInExt* extension );

  private:
    BAS::String resultM;
};

/** <b><tt>TokenLong</tt></b> is the iScript function node class for 
 *  accessing long values in tokens.
 */
class TokenLong : public SCR::LongNode, public TokenAccess
{
  public:
    /**@name TokenLong constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~TokenLong();

    //@}

    /**@name TokenLong public methods */
    //@{

    /** Initialize the token long access object 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool initTokenAccess( const BAS::String& fieldName );

    /** Execute the function.
     *  @return Reference to function result 
     */
    int64 result();

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
     * @param extension Pointer to the iScript input extension
     * @param recordDescr Pointer to the recorddescription 
     */
    TokenLong( IScriptInExt* extension );

  private:
    BAS::String resultM;
};

/** <b><tt>TokenDate</tt></b> is the iScript function node class for 
 *  accessing date values in tokens.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TokenFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/21 14:37:14 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class TokenDate : public SCR::DateNode, public TokenAccess
{
  public:
    /**@name TokenDate constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~TokenDate();

    //@}

    /**@name TokenDate public methods */
    //@{

    /** Initialize the token string access object 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool initTokenAccess( const BAS::String& fieldName );

    /** Execute the function.
     *  @return Reference to function result 
     */
    const BAS::DateTime& result();

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
     * @param extension Pointer to the iScript input extension
     * @param recordDescr Pointer to the recorddescription 
     */
    TokenDate( IScriptInExt* extension );

  private:
    BAS::DateTime resultM;
};

/** <b><tt>TokenDecimal</tt></b> is the iScript function node class for 
 *  accessing decimal values in tokens.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TokenFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/21 14:37:14 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class TokenDecimal : public SCR::DecimalNode, public TokenAccess
{
  public:
    /**@name TokenDecimal constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~TokenDecimal();

    //@}

    /**@name TokenDecimal public methods */
    //@{

    /** Initialize the token string access object 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool initTokenAccess( const BAS::String& fieldName );

    /** Execute the function.
     *  @return Reference to function result 
     */
    const BAS::Decimal& result();

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
     * @param extension Pointer to the iScript input extension
     * @param recordDescr Pointer to the recorddescription 
     */
    TokenDecimal( IScriptInExt* extension );

  private:
    BAS::Decimal resultM;
};

class EdrTokenPop : public SCR::BoolNode
{
public:
    /**@name TokenDecimal constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrTokenPop();

    //@}

    /**@name EdrTokenPop public methods */
    //@{

    /** Execute the function.
     *  @return Reference to function result 
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

    //@}

  protected:

    /* Constructor
     * @param extension Pointer to the iScript input extension
     * @param recordDescr Pointer to the recorddescription 
     */
    EdrTokenPop( IScriptInExt* extension );

   private:
	IScriptInExt* inputExtensionM;

};	
}

#endif // TOKENFUNCTIONS_HPP

