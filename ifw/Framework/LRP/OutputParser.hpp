#ifndef LRP_OUTPUTPARSER_HPP
#define LRP_OUTPUTPARSER_HPP

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
//   Declaration of the class OutputParser. This class is used to convert
//   EDR containers to byte streams.
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
// $RCSfile: OutputParser.hpp,v $
// $Revision: 1.11 $
// $Author: sd $
// $Date: 2001/06/27 06:56:55 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OutputParser.hpp,v $
// Revision 1.11  2001/06/27 06:56:55  sd
// - New interface for the output device.
//
// Revision 1.10  2001/05/21 12:16:29  sd
// - Releasing the EDRs via PLG::OutputDevice::releaseEdr()
//
// Revision 1.9  2001/05/18 12:52:59  sd
// - Error handling added
//
// Revision 1.8  2001/04/12 12:21:47  sd
// - Update for splitting LRP/FRM::Base
//
// Revision 1.7  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.6  2001/04/05 09:28:24  sd
// - Backup version
//
// Revision 1.5  2001/04/04 11:54:14  sd
// - Old stream interfaces replaced by new stream managers.
//
// Revision 1.4  2001/04/03 08:15:30  sd
// - Full iScript support
//
// Revision 1.1  2001/02/22 12:04:03  sd
// - Initial revision.
//
//==============================================================================

#ifndef   LRP_PARSER_HPP
  #include "LRP/Parser.hpp"
#endif

namespace IXT
{
class Integrate;
}
namespace PLG
{
class OutputStreamDevice;
}
namespace EDR
{
class Container;
}
namespace FRM
{
class DataDescr;
}
namespace LRP
{
class EdrAnalyzer;
class IScriptOutExt;

/** <b><tt>OutputParser</tt></b> is used to parse the EDR container stream
 *  arriving at the output plugin and convert this EDRs to output file records.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: OutputParser.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.11 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/27 06:56:55 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class OutputParser : public Parser
{
  public:
    /**@name OutputParser constructors and destructor */
    //@{

    /** Constructor
     *  @param interpreterName Registry name of the iScript interpreter
     *  @param analyzer The EDR analyser to get symbol ids for EDR containers
     *  @param dataDescr The description of the file input data
     *  @param outDevice The output device that uses the parser
     *  @param outStream The output stream for writing the output records
     */
    OutputParser( const BAS::String&       interpreterName,
                      EdrAnalyzer*        analyzer,
                      FRM::DataDescr*          dataDescr,
                      PLG::OutputStreamDevice* outDevice );

    /** Destructor
     */
    virtual ~OutputParser();

    //@}

    /**@name OutputParser public methods */
    //@{

    /** Process the next EDR data container 
     *  @param edr The next EDR container to process
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool process( EDR::Container* edr );
 
    /** Process the EOF symbol
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool eof();

    /** Get the rejected EDR
     *  @return Pointer to the rejected EDR
     */
    EDR::Container* rejectedEdr();

    /** Set the value of the CURRENT_STREAM_NAME iScript global variable
     *  @param currentStreamName the name of the current stream
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setCurrentStreamName(const BAS::String& currentStreamName);
    //@}

  private:

    // instance members
    EdrAnalyzer*      analyzerM;
    IScriptOutExt*    outExtensionM;
    IXT::Integrate*        integrateExtensionM;
    ParserResult          parserResultM;
    EDR::Container*        rejectedEdrM;
    SCR::StringVariable*   currentStreamNameM;
};

//==============================================================================
// Get the rejected EDR
//==============================================================================
inline EDR::Container*
OutputParser::rejectedEdr()
{
  EDR::Container* edr = rejectedEdrM;
  rejectedEdrM = 0;
  return edr;
}

//==============================================================================
// set the current stream name in a global variable on the IScript extension
//==============================================================================
inline bool
OutputParser::setCurrentStreamName(const BAS::String& currentStreamName)
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
#endif // OUTPUTPARSER_HPP

