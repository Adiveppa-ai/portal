#ifndef LRP_FILEBUFFER_HPP
#define LRP_FILEBUFFER_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   The class FileBuffer is the interface of the lexical analyser to the
//   input stream.
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
// $RCSfile: FileBuffer.hpp,v $
// $Revision: 1.15 $
// $Author: sd $
// $Date: 2001/10/18 08:37:10 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FileBuffer.hpp,v $
// Revision 1.15  2001/10/18 08:37:10  sd
// - Interface changed to BAS::StringList
//
// Revision 1.7  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.6  2001/03/29 14:30:32  sd
// - Backup version
//
// Revision 1.5  2001/03/27 09:13:42  sd
// - Backup version
//
// Revision 1.4  2001/03/16 16:03:13  sd
// - ASN blocks added
//
// Revision 1.3  2001/03/14 09:29:33  sd
// - Constants introduced in input mapping
//
// Revision 1.2  2001/01/11 13:03:41  sd
// - First v4-30 check-in.
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_SIMPLESTRING_HPP
  #include "BAS/SimpleString.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace STR
{
class InStreamManager;
}
namespace EDR
{
class Token;
}
namespace LRP
{

/** <b><tt>FileBuffer</tt></b> is used as interface between STR::File and
 *  the lexical analyser used by the LR(1) parser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileBuffer.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.15 $</font></td>
 *  <td><font size=-1>$Date: 2001/10/18 08:37:10 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
 
class FileBuffer D_THREADINFO
{
  public:

    /**@name FileBuffer constructors and destructor */
    //@{

    /** Constructor for reading from input streams
     *  @param inputStream The input stream to read from
     *  @param bufferSize The size of the internal buffer
     */
    FileBuffer( STR::InStreamManager* inputStream,
                    size_t               bufferSize );

    /** Constructor for reading from BAS::SimpleStringLists
     *  @param inputList Input list to read from
     */
    FileBuffer( const BAS::SimpleStringList* inputList );

    /** Constructor for reading from BAS::StringLists
     *  @param inputList Input list to read from
     */
    FileBuffer( const BAS::StringList* inputList );

    /** Destructor
     */
    ~FileBuffer();

    //@}

    /**@name FileBuffer public methods */
    //@{

    /** Flush the entire file buffer
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool flush();

    /** Flush the currently saved part to the token
     */
    void flushSavedToToken();

    /** Initialize the file buffer for a new token
     *  @param token The new token
     */
    void beginToken( EDR::Token* token );

    /** Flush the read data to the token
     */
    void endToken();

    /** Get the next char from the input stream
     *  @return Next character on success, EOF otherwise
     */
    int getChar();
    
    /** Unget the last read character
     */
    void ungetChar();

    /** Skip n bytes
     *  @param n Number of bytes to skip
     */
    bool skipTo( size_t n );

    /** Check if end-of-file is reached
     *  @return <b>true</b> on EOF, <b>false</b> otherwise
     */
    bool eof() const;

    /** Check if there is some more data in the input buffer
     *  @return <b>true</b> if more data, <b>false</b> otherwise
     */
    bool moreData();

    //@}

  protected:
    /* Refill the input buffer
     * @return The number of bytes read from the input stream
     */
    size_t refill();

  private:
    // inputStream specific instance members
    STR::InStreamManager*  inputStreamM;
    size_t                bufferSizeM;
    
    // stringList specific instance members
    const BAS::SimpleStringList* simpleStringInputListM;
    const BAS::StringList*       stringInputListM;
    size_t                inputListEntriesM;
    size_t                currentInputListEntryM;

    // general instance members
    char*                 bufferM;
    size_t                currentM;
    size_t                lastM;
    size_t                tokenSizeM;
    int                   savePointM;
    EDR::Token*            currentTokenM;
    bool                  eofM;
};

//==============================================================================
// Get the next character
//==============================================================================
inline int 
FileBuffer::getChar()
{
  if ( currentM < lastM )
  {
    return (unsigned char) bufferM[currentM++];
  }
  else
  {
    if ( refill() == 0 )
    {
      return EOF;
    }
    else
    {
      return (unsigned char) bufferM[currentM++];
    }
  }
}

//==============================================================================
// Unget the last read character
//==============================================================================
inline void
FileBuffer::ungetChar()
{
  RWPRECONDITION( currentM > 0 );
  currentM--;
}

//==============================================================================
// Get the END-OF-FILE flag
//==============================================================================
inline bool
FileBuffer::eof() const
{
  return eofM;
}

//==============================================================================
// Check if there is some more data in the buffer
//==============================================================================
inline bool
FileBuffer::moreData()
{
  if ( eofM == true )
  {
    return false;
  }
  if ( currentM >= lastM )
  {
    if ( refill() == 0 )
    {
      return false;
    }
  }

  return true;
}
}
#endif // FILEBUFFER_HPP
