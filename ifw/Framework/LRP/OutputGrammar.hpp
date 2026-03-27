#ifndef LRP_OUTPUTGRAMMAR_HPP
#define LRP_OUTPUTGRAMMAR_HPP

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
//   Declaration of the class OutputGrammar. This class is used to parse
//   the output grammar and create a parser that is used to convert the 
//   EDR containers back to file records.
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
// $RCSfile: OutputGrammar.hpp,v $
// $Revision: 1.11 $
// $Author: sd $
// $Date: 2001/06/28 08:47:55 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OutputGrammar.hpp,v $
// Revision 1.11  2001/06/28 08:47:55  sd
// - Forward declaration corrected
//
// Revision 1.10  2001/06/27 06:56:55  sd
// - New interface for the output device.
//
// Revision 1.9  2001/05/21 12:47:54  sd
// - Forward declaration for PLG::OutputDevice
//
// Revision 1.8  2001/05/21 12:16:29  sd
// - Releasing the EDRs via PLG::OutputDevice::releaseEdr()
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
// Revision 1.3  2001/03/07 10:13:35  sd
// - Backup version
//
// Revision 1.2  2001/02/26 15:07:12  sd
// - Backup version
//
// Revision 1.1  2001/02/22 12:04:03  sd
// - Initial revision.
//
//==============================================================================

#ifndef   LRP_GRAMMAR_HPP
  #include "LRP/Grammar.hpp"
#endif

namespace PLG
{
class OutputStreamDevice;
}
namespace STR
{
class OutStreamManager;
}
namespace FRM
{
class DataDescr;
}
namespace LRP
{
class OutputParser;

/** <b><tt>OutputGrammar</tt></b> is used to parse the output grammar and
 *  create the output parser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: OutputGrammar.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.11 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/28 08:47:55 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class OutputGrammar : public Grammar
{
  public:
    /**@name OutputGrammar constructors and destructor */
    //@{

    /** Constructor
     *  @param dataDescr Pointer to the description of file formats
     *  @param grammarDescrFileName File name for the grammar description file
     *  @param debugFile Name of the file for grammar debug information
     */
    OutputGrammar( const BAS::String& grammarDescrFileName,
                       const BAS::String& debugFile = BAS::NULL_STRING );

    /** Destructor
     */
    ~OutputGrammar();

    //@}


    /**@name OutputGrammar public methods */
    //@{

    /** Create an output parser
     *  @param name The registry name of the iScript interpreter
     *  @param dataDescr Pointer to the file data description
     *  @param outputDevice Output stream device that uses the parser
     *  @return Pointer to parser on success, 0 otherwise
     */
    OutputParser* createParser( const BAS::String&       interpreterName,
                                    FRM::DataDescr*          dataDescr,
                                    PLG::OutputStreamDevice* outputDevice );

    //@}

  private:
};
}
#endif // OUTPUTGRAMMAR_HPP
