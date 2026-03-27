#ifndef EDR_TOKEN_HPP
#define EDR_TOKEN_HPP

//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Token. Token is used by the lexical 
//   analyser to return the found tokens. A token contains the information 
//   about the found symbol (e.g. HEADER) and the current value for the token.
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
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:40 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.18  2012/05/23 Santanu 
// - BUG 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
//
// Revision 1.17  2002/01/16 13:28:18  sd
// - Serialization of tokens added
//
// Revision 1.16  2001/11/15 10:09:38  sd
// - PETS #41247 - Parser error messages insufficient
//
// Revision 1.15  2001/11/15 10:06:03  sd
// - PETS #41247 - Core dumping while process GSM CDRs
//
// Revision 1.14  2001/11/11 19:09:23  sd
// - Token cache introduced
//
// Revision 1.13  2001/11/09 15:32:33  sd
// - Token cache introduced
//
// Revision 1.12  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.11  2001/07/18 13:11:00  sd
// - PETS #37117 Stream LOG: Wrong EDR number
//   New function bytePosition() added witch is used to evaluate the
//   starting position of an EDR container inside a stream
//
// Revision 1.10  2001/06/21 14:39:57  sd
// - New function writeOnReject()
//
// Revision 1.9  2001/06/21 14:37:34  sd
// - Write on reject
//
// Revision 1.8  2001/06/14 09:58:35  sd
// - iScript now supports transactions
//
// Revision 1.7  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.6  2001/03/30 12:50:37  sd
// - New class TokenHandle introduced to allow reference counting on
//   tokens.
//
// Revision 1.5  2001/03/08 12:32:51  sd
// - Output mapping changed
//
// Revision 1.4  2001/03/08 08:39:27  sd
// - Performance improvements
//
// Revision 1.3  2001/03/08 07:37:42  sd
// - Performance improvements
//
// Revision 1.2  2001/03/07 10:13:35  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace EDR
{
/** <b><tt>Token</tt></b> is used to transfer the information about the 
 *  read symbol and it's value from the lexical analyser to the parser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
,v $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:40 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>
 */
class Token D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name Token constructors and destructor */
    //@{

    /** Constructor
     *  @param writeOnReject Flag if the token shall be written when edr 
     *                       is rejected
     *  @param bytePosition The byte position of the token
     */
    Token();

    //@}

    /**@name Token public methods */
    //@{

    /** Get the token symbol
     *  @return The symbol value
     */
    size_t symbolId() const;

    /** Set the token symbol
     *  @param symbol The new symbol
     */
    void symbolId( size_t symbol );

    /** Get the token value
     *  @return Reference to value string
     */
    const BAS::String& value() const;

    /** Get the byte position (in stream) of the token
     *  @return The byte position
     */
    size_t bytePosition() const;
    
    /** Set the byte position (in stream) of the token
     *  @param pos The byte position
     */
    void bytePosition( size_t pos );
    
    /** Reset the token value
     */
    void resetValue();

    /** Append some data to the token value
     *  @param len The length of the data to append
     *  @param buffer The buffer with data to append
     */
    void appendValue( size_t len, const char* buffer );

    /** Increase the reference counter
     */
    void incRefCount();

    /** Decrease the reference counter and return the new value
     */
    size_t decRefCount();

    /** Get the present value of the reference counter
     *  @return the value of the reference counter
     */
    size_t getRefCount();

    /** Get the write on reject flag
     *  @return The writeOnReject flag
     */
    bool writeOnReject() const;

    /** Set the write on reject flag
     *  @param flag The new flag
     */
    void writeOnReject( bool flag );
    
    /* Get the token's cache successor
     * @return Pointer to the cache successor (can be 0)
     */
    Token* cacheSucc() const;

    /* Set the token's cache successor
     * @param edr The new cache successor
     */
    void cacheSucc( Token* edr );

    /** Clear the token
     */
    void clear();

    /** Serialize the token
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool serialize( std::ostream& out ) const;

    /** Restore the token
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool restore( std::istream& in );

    /** A public mutex used for thread-safe token operations
     *  in TokenHandle class
    */

    RWMutexLock         refCountMutexM;
    //@}

    friend class TokenCache;

  protected:
    /** Destructor
     */
    ~Token();

  private:

    // instance members
    size_t              symbolIdM;
    size_t              refCountM;
    BAS::String         valueM;
    bool                writeOnRejectM;
    size_t              bytePositionM;
    Token*              cacheSuccM;
};

//==============================================================================
// Get the token symbol
//==============================================================================
inline size_t
Token::symbolId() const
{
  return symbolIdM;
}

//==============================================================================
// Get the token symbol
//==============================================================================
inline void
Token::symbolId( size_t symbol )
{
  symbolIdM = symbol;
}


//==============================================================================
// Get the token value
//==============================================================================
inline const BAS::String&
Token::value() const
{
  return valueM;
}

//==============================================================================
// Reset the token value
//==============================================================================
inline void
Token::resetValue()
{
  valueM = "";
}

//==============================================================================
// Append some data to the value
//==============================================================================
inline void
Token::appendValue( size_t len, const char* buffer )
{
  valueM.replace( valueM.length(), 0, buffer, len );
}

//==============================================================================
// Increase the reference counter
//==============================================================================
inline void
Token::incRefCount()
{
  refCountM++;
}

//==============================================================================
// Decrease the reference counter
//==============================================================================
inline size_t
Token::decRefCount()
{
  RWPRECONDITION( refCountM > 0 );
  return --refCountM;
}

//=============================================================================
// Get the present value of the reference counter
//==============================================================================
inline size_t Token:: getRefCount()
{
   return refCountM;
}


//==============================================================================
// Get the write on reject flag
//==============================================================================
inline bool
Token::writeOnReject() const
{
  return writeOnRejectM;
}

//==============================================================================
// Set the write on reject flag
//==============================================================================
inline void
Token::writeOnReject( bool flag )
{
  writeOnRejectM = flag;
}

//==============================================================================
// Get the byte position
//==============================================================================
inline size_t
Token::bytePosition() const
{
  return bytePositionM;
}

//==============================================================================
// Set the byte position
//==============================================================================
inline void
Token::bytePosition( size_t pos )
{
  bytePositionM = pos;
}

//==============================================================================
// Get the cache successor
//==============================================================================
inline Token*
Token::cacheSucc() const
{
  return cacheSuccM;
}

//==============================================================================
// Set the cache successor
//==============================================================================
inline void 
Token::cacheSucc( Token* token )
{
  cacheSuccM = token;
}
}
#endif // TOKEN_HPP
