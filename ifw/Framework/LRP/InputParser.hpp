#ifndef LRP_INPUTPARSER_HPP
#define LRP_INPUTPARSER_HPP
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
//   Declaration of the class InputParser.
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
// $RCSfile: InputParser.hpp,v $
// $Revision: 1.10 $
// $Author: sd $
// $Date: 2001/07/04 08:32:15 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: InputParser.hpp,v $
// Revision 1.10  2001/07/04 08:32:15  sd
// - Interface changed to support FCT_UniData
//
// Revision 1.9  2001/06/22 06:36:37  pengelbr
// Include LexicalAnalyzer instead of forward declaration.
//
// Revision 1.8  2001/06/21 14:37:14  sd
// - new function writeOnReject()
//
// Revision 1.7  2001/04/12 12:21:47  sd
// - Update for splitting LRP/FRM::Base
//
// Revision 1.6  2001/04/05 15:14:58  sd
// - Input parser now has a pointer to the integRate iScript extension
//
// Revision 1.5  2001/04/04 09:22:30  sd
// - Backup version
//
// Revision 1.4  2001/04/03 08:15:30  sd
// - Full iScript support
//
// Revision 1.3  2001/03/20 09:03:35  sd
// - iScript extension renamed
//
//==============================================================================

#ifndef   LRP_PARSER_HPP
  #include "LRP/Parser.hpp"
#endif
#ifndef   LRP_LEXICALANALYSER_HPP
  #include "LRP/LexicalAnalyser.hpp"
#endif

namespace IXT
{
class Integrate;
}
namespace EDR 
{
class Container;
}
namespace PLG
{
class InputDevice;
}
namespace LRP
{
class IScriptInExt;

/** <b><tt>InputParser</tt></b> is used to parse input byte streams and
 *  create EDR::Containers.
 */
class InputParser : public Parser
{
  D_SINGLETHREADED

  public:
    /**@name InputParser constructors and destructor */
    //@{

    /** Constructor
     *  @param interpreterName Registry name of the iScript interpreter
     *  @param inputDevice Input device with pushEdr() function
     *  @param lexicalAnalyser Lexical analyser for parsing the files
     */
    InputParser( const BAS::String&    interpreterName,
                     PLG::InputDevice*     inputDevice,
                     LexicalAnalyser* lexicalAnalyser );

    /** Destructor
     */
    ~InputParser();

    //@}


    /**@name InputParser public methods */
    //@{

    /** Process a file.
     *  @param fileBuffer The file buffer to read from
     *  @param edr The EDR container to process
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool process( FileBuffer& fileBuffer,
                  EDR::Container*  edr = 0 );

    /** Set the writeOnReject flag for the tokens read by the parser
     *  @param flag The new write on reject flag
     */
    void writeOnReject( bool flag );

    /** Set the value of the CURRENT_STREAM_NAME iScript global variable
     *  @param currentStreamName the name of the current stream
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setCurrentStreamName(const BAS::String& currentStreamName);
    //@}

  private:
    // Hide copy constructor and assignment operator
    InputParser( const InputParser& other );
    const InputParser operator=( const InputParser& other );

    // Instance members
    LexicalAnalyser* lexicalAnalyserM;
    IXT::Integrate*       integrateExtensionM;
    IScriptInExt*    inputExtensionM;
    SCR::StringVariable*  currentStreamNameM;
};

//==============================================================================
// Set the write on reject flag for tokens read by the parser
//==============================================================================
inline void
InputParser::writeOnReject( bool flag )
{
  RWPRECONDITION( lexicalAnalyserM != 0 );
  lexicalAnalyserM->writeOnReject( flag );
}

//==============================================================================
// set the current stream name in a global variable on the IScript extension
//==============================================================================
inline bool
InputParser::setCurrentStreamName(const BAS::String& currentStreamName)
{
  if (currentStreamNameM)
  {
    currentStreamNameM->set(currentStreamName);
    return true;
  }
  else
  {
    return false;
  }
}
}
#endif // INPUTPARSER_HPP
