#ifndef LRP_LEXERSTATE_HPP
#define LRP_LEXERSTATE_HPP

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
// Block: 
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class LexerState.
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
// $RCSfile: LexerState.hpp,v $
// $Revision: 1.8 $
// $Author: bt $
// $Date: 2001/08/03 13:15:02 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: LexerState.hpp,v $
// Revision 1.8  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.7  2001/07/03 11:49:58  sd
// - PETS #36641 - ASN.1 enhancements for Swisscom
//
// Revision 1.6  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.5  2001/04/05 09:28:24  sd
// - Backup version
//
// Revision 1.4  2001/04/02 09:13:22  sd
// - BlockDescr renamed to FRM::RecordDescr
//
// Revision 1.3  2001/01/11 14:49:13  sd
// - const in RWVector removed (Solaris problem)
//
// Revision 1.2  2000/11/27 12:21:26  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   FSM_ENGINE_HPP
  #include "FSM/Engine.hpp"
#endif
#ifndef   FRM_RECORDDESCR_HPP
  #include "FRM/RecordDescr.hpp"
#endif

namespace FRM
{
class StateTransition;
}
namespace EDR
{
class Token;
}
namespace LRP
{
class FileBuffer;

/** <b><tt>LexerState</tt></b> represents a single state inside the 
 *  lexical analyser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LexerState.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.8 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/03 13:15:02 $</font></td>
 *  <td><font size=-1>$Author: bt $</font></td>
 *  </tr>
 *  </table>
 */
class LexerState : public FSM::Engine
{
  public:
    /**@name LexerState constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the lexer state
     */
    LexerState( const BAS::String& name );
    
    /** Destructor
     */
    ~LexerState();

    //@}


    /**@name LexerState public methods */
    //@{

    /** Get the name of the lexer state
     *  @return Reference for name string
     */
    const BAS::String& name() const;

    /** Add a record description to the state
     *  @param recordDescr The record description to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addRecordDescr( FRM::RecordDescr* recordDescr );

    /** Process the next token
     *  @param fileBuffer The file buffer to read from
     *  @param token The return buffer for the found token
     *  @param recordDescr The return buffer for the found record's description
     *  @return <b>true</b> if there is more data to read, <b>false</b> on eof
     */
    bool process( FileBuffer&         fileBuffer,
                  EDR::Token&              token,
                  const FRM::RecordDescr*& recordDescr );

    //@}

  private:
    // Hide the copy constructor
    LexerState( const LexerState& );
    const LexerState operator=( const LexerState& );

    // Instance members
    BAS::String                           nameM;
    RWTPtrOrderedVector<FRM::RecordDescr> recordDescrM;
};

//==============================================================================
// Get the name
//==============================================================================
inline const BAS::String&
LexerState::name() const
{
  return nameM;
}
}
#endif // LEXERSTATE_HPP
