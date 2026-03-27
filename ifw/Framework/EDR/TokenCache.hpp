#ifndef EDR_TOKENCACHE_HPP
#define EDR_TOKENCACHE_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class TokenCache.
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
// $RCSfile: TokenCache.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/11/09 15:35:54 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TokenCache.hpp,v $
// Revision 1.1  2001/11/09 15:35:54  sd
// - Token cache introduced
//
//==============================================================================

#ifndef   RW_TOOLS_TPSLIST_H
  #include <rw/tpslist.h>
#endif
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

namespace EDR
{
class Token;

/** <b><tt>TokenCache</tt></b> is used to cache Tokens inside
 *  the Factory
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TokenCache.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/11/09 15:35:54 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>                
 */
class TokenCache D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name TokenCache constructors and destructor */
    //@{

    /** Constructor 
     */
    TokenCache();

    /** Destructor 
     */
    ~TokenCache();

    //@}

    /**@name TokenCache public methods */
    //@{

    /** Retrieve a token from the cache and remove it from the internal 
     *  list
     *  @return Pointer to the token on success
     */
    Token* removeToken();
    
    /** Insert a new token to the cache
     *  @param token The token to add to the cache
     */
    void insertToken( Token* token );

    //@}

  private:
    // Disallow use of copy constructor/operator
    TokenCache( const TokenCache& other );
    const TokenCache& operator=( const TokenCache& other );

    // instance members
    Token*     inCacheM;
    Token*     outCacheM;
    RWMutexLock    inMutexM;
    RWMutexLock    outMutexM;
};
}
#endif // TOKENCACHE_HPP
