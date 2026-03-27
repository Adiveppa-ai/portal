#ifndef EDR_TOKENHANDLE_HPP
#define EDR_TOKENHANDLE_HPP

//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//   TokenHandle is used as reference counted access to Tokens. The 
//   class was introduced because we want to avoid to duplication of all tokens
//   read when an EDR container is duplicated. 
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: TokenHandle.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:46 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TokenHandle.hpp,v $
// Revision 1.1  2001/11/09 15:32:33  sd
// - Token cache introduced
//
// Revision 1.3  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.2  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.1  2001/03/30 12:50:37  sd
// - New class TokenHandle introduced to allow reference counting on
//   tokens.
//
//==============================================================================
namespace EDR
{
class Factory;
class Token;

/** <b><tt>TokenHandle</tt></b> is used to permit reference counted access
 *  to Token values. This feature was especially necessary when EDR 
 *  containers will be duplicated.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TokenHandle.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:46 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>
 */
class TokenHandle D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name TokenHandle constructors and destructor */
    //@{

    /** Constructor
     */
    TokenHandle( Factory* factory,
                     Token*   token );

    /** Copy constructor
     *  @param other The TokenHandle to copy
     */
    TokenHandle( const TokenHandle& other );

    /** Overloading Assignment operator
     *  @param other The TokenHandle to copy
     */
    EDR::TokenHandle & operator=( const EDR::TokenHandle& other );

    /** Destructor
     */
    ~TokenHandle();

    //@}


    /**@name TokenHandle public methods */
    //@{

    /** Get the pointer to the token
     *  @return Pointer to token
     */
    Token* token() const;

    //@}
  private:
    // Instance members
    Factory* factoryM;
    Token*   tokenM;
};

//==============================================================================
// Get the pointer to the token
//==============================================================================
inline Token*
TokenHandle::token() const
{
  return tokenM;
}
}
#endif // TOKENHANDLE_HPP
