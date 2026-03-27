#ifndef LOG_PLUGIN_ITO_HPP
#define LOG_PLUGIN_ITO_HPP 
//==============================================================================
//
// 1998,1999 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: LOG
//------------------------------------------------------------------------------
// Module Description:
//  <description>
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: LOG_PlugInITO.hpp,v $
// $Revision: 1.13 $
// $Author: jkeckst $
// $Date: 1999/10/27 13:53:19 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: LOG_PlugInITO.hpp,v $
// Revision 1.13  1999/10/27 13:53:19  jkeckst
// check the code reviews and clear all errors.
//
// Revision 1.12  1999/10/27 09:19:54  clohmann
// *** empty log message ***
//
// Revision 1.11  1999/10/06 12:09:00  jkeckst
// implement isUsable function
//
// Revision 1.10  1999/08/09 13:19:14  clohmann
// *** empty log message ***
//
// Revision 1.9  1999/08/06 15:16:55  aro
// Updates to improve coding rule conformance;
// new method LOG_Stream::receiveMessage() implemented.
//
// Revision 1.1  1999/04/28 07:58:16  jkeckst
// create new class LOG_Stream for logging without thread overhead...
//
//==============================================================================
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   LOG_PLUGIN_HPP
  #include "LOG/PlugIn.hpp"
#endif

namespace LOG {
/** <tt><b>LOG_PlugInITO</b></tt> This class records all log messages in ITO format.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: LOG_PlugInITO.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.13 $</font></td>
    <td><font size=-1>$Date: 1999/10/27 13:53:19 $</font></td>
    <td><font size=-1>$Author: jkeckst $</font></td>
    </tr>
    </table>                

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>none</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>none</dd>
    
    This class generates only a new LOG_StreamITO object and
    set this object to the log pointer. The name of the new
    object is added with ".ITO".
    
</dl> 
*/
class PlugInITO : public PlugIn
{
  public:
    /**@name constructors and destructor */
    //@{ 
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    PlugInITO();
    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    PlugInITO(const BAS::String & name, 
                  const BAS::String & version);
    /// destructor
    virtual ~PlugInITO();
    ///
    virtual bool isUsable();
    //@}

  private:  
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    PlugInITO(PlugInITO& right);
    const PlugInITO& operator=(PlugInITO& right);
};
}
#endif // LOG_PLUGINITO_HPP
