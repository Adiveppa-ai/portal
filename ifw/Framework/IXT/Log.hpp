#ifndef IXT_LOG_HPP
#define IXT_LOG_HPP
//==============================================================================
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.

//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Log. This class is used to write compiler
//   errors to the integRate pipeline log.
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
// $RCSfile: Log.hpp,v $
// $Revision: 1.6 $
// $Author: bt $
// $Date: 2001/05/03 16:08:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Log.hpp,v $
// Revision 1.6  2005/08/30  pborah
// PRSF00180911  WARNING logged as MAJOR error.
//
// Revision 1.5  2001/05/03 16:08:14  bt
// Format renamed to Pipeline.
//
// Revision 1.4  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.1  2000/12/04 08:21:07  sd
// - Module moved from IXT to iScript.
//
// Revision 1.2  2000/09/27 12:15:08  sd
// - BugFix in IScript
//
// Revision 1.1  2000/09/27 11:33:21  sd
// - IXT is a framework module again
//
// Revision 1.1  2000/09/26 13:33:35  sd
// - Initial revision for separate integRate iScript extension.
//
//==============================================================================

#ifndef   SCR_LOG_HPP
  #include "SCR/Log.hpp"
#endif

namespace IXT
{
class Integrate;

/** <b><tt>Log</tt></b> is used to write compiler errors to the integRate
 *  pipeline log.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Log.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/05/03 16:08:14 $</font></td>
 *  <td><font size=-1>$Author: bt $</font></td>
 *  </tr>
 *  </table>
 */
class Log : public SCR::Log
{
   public:
    /**@name Log constructors and destructor */
    //@{

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    Log();

    /** Destructor
     */
    virtual ~Log();

    //@}


    /**@name Log public methods */
    //@{

    /** Log a message
     *  @param msg The message to log
     */
    virtual void log( const BAS::String& msg, BAS::Status::Severity severity=BAS::Status::major);

    /** Initialize the log
     *  @param extension The extension to use inside the log
     */
    void extension( Integrate* extension );

    //@}

  private:
    Integrate* extensionM;
};

//==============================================================================
// Set the extension
//==============================================================================
inline void
Log::extension( Integrate* extension )
{
  extensionM  = extension;
}
}
#endif // LOG::HPP
