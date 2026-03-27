#ifndef LRP_INPUTGRAMMAR_HPP
#define LRP_INPUTGRAMMAR_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class InputGrammar. This class is used to create
//   the input parser.
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
// $RCSfile: InputGrammar.hpp,v $
// $Revision: 1.6 $
// $Author: sd $
// $Date: 2001/04/12 11:15:46 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: InputGrammar.hpp,v $
// Revision 1.6  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.5  2001/04/05 09:28:24  sd
// - Backup version
//
// Revision 1.4  2001/04/04 09:22:30  sd
// - Backup version
//
// Revision 1.3  2001/04/03 08:15:30  sd
// - Full iScript support
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
class InputDevice;
}
namespace LRP
{
class InputParser;

/** <b><tt>InputGrammar</tt></b> is the class for parsing the input grammar
 *  and creating the input parser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: InputGrammar.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.6 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/12 11:15:46 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class InputGrammar : public Grammar
{
  public:
    /**@name InputGrammar constructors and destructor */
    //@{

    /** Constructor
     *  @param dataDescr Pointer to the description of file formats
     *  @param grammarDescrFileName File name for the grammar description file
     *  @param debugFile Name of the file for grammar debug information
     */
    InputGrammar( FRM::DataDescr*    dataDescr,
                      const BAS::String& grammarDescrFileName,
                      const BAS::String& debugFile );

    /** Constructor
     *  @param dataDescr Pointer to the description of file formats
     *  @param grammarDescrFileName File name for the grammar description file
     *  @param grammarDescrText Contents of the grammar description
     *  @param debugFile Name of the file for grammar debug information
     */
    InputGrammar( FRM::DataDescr*    dataDescr,
                      const BAS::String& grammarDescrFileName,
                      const BAS::String& grammarDescrText,
                      const BAS::String& debugFile );

    /** Destructor
     */
    virtual ~InputGrammar();

    //@}


    /**@name InputGrammar public methods */
    //@{

    /** Create an input parser for the grammar.
     *  @param interpreterName Registry name for the iScript interpreter
     *  @param inputDevice The input device with the pushEdr() function
     *  @return Pointer to parser on success, 0 otherwise
     */
    InputParser* createParser( const BAS::String& interpreterName,
                                   PLG::InputDevice*  inputDevice );

    //@}

  private:
    // instance members
    FRM::DataDescr* dataDescrM;
};
}
#endif // INPUTGRAMMAR_HPP
