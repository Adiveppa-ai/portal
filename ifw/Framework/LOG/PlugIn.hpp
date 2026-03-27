#ifndef LOG_PLUGIN_HPP
#define LOG_PLUGIN_HPP 
// @(#)%Portal Version: PlugIn.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:45:38 %
//==============================================================================
//
// Copyright (c) 1996, 2016, Oracle and/or its affiliates. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
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
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: PlugIn.hpp $
// $Revision: /cgbubrm_mainbrm.pipeline/2 $
// $Author: skattepu $
// $Date: 2016/12/07 02:14:23 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: LOG_PlugIn.hpp,v $
//
// Revision 1.26  2006/07/11 06:09:58  mliu
// PRSF00222716 create snapshot for CRITICAL log messages
//
// Revision 1.25  2001/06/29 09:39:39  jkeckst
// solve PT0000000036554. Insert new methode to get the log file name.
//
// Revision 1.24  1999/10/27 13:53:19  jkeckst
// check the code reviews and clear all errors.
//
// Revision 1.23  1999/10/27 09:19:54  clohmann
// *** empty log message ***
//
// Revision 1.22  1999/10/06 12:09:00  jkeckst
// implement isUsable function
//
// Revision 1.21  1999/09/08 12:28:22  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
// Class STR_InputFile modified to synchronize start() and inactiveLoop().
// If start() is called prior to inactiveLoop(), inactiveLoop() will hang.
//
// Revision 1.20  1999/09/03 08:41:10  jkeckst
// add testMessageName to plugin
//
// Revision 1.19  1999/08/09 13:19:14  clohmann
// *** empty log message ***
//
// Revision 1.18  1999/08/06 15:16:55  aro
// Updates to improve coding rule conformance;
// new method LOG_Stream::receiveMessage() implemented.
//
// Revision 1.6  1999/04/16 11:27:05  jkeckst
// change all logFilePath to logPathName
//
// Revision 1.5  1999/04/15 14:28:14  jkeckst
// add updateRegistry function
//==============================================================================
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   BAS_THREAD_HPP
  #include "BAS/Thread.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   PLG_THREAD_PLUG_IN_HPP
  #include "PLG/ThreadPlugIn.hpp"
#endif
#ifndef   LOG_STREAM_HPP
  #include "LOG/Stream.hpp"
#endif

namespace BAS 
{
	class Status;
}
namespace OMF
{
  class DiagnosticDataHandler;
}

namespace LOG 
{

/** <tt><b>LOG_PlugIn</b></tt> This class represents the frame for all log plugins.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: PlugIn.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_mainbrm.pipeline/2 $</font></td>
    <td><font size=-1>$Date: 2016/12/07 02:14:23 $</font></td>
    <td><font size=-1>$Author: skattepu $</font></td>
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
</dl> 

    This class represents the frame for all log plugins. The receive
    methode receive all incomming messages, make a copy, put them in 
    the internal queue and returns. The execute function (thread function)
    get this messages an call the log->write(msg) methode. The log
    object is not set automaticly, it must done by another class.
*/
class PlugIn : public PLG::ThreadPlugIn
{
  public:
    /**@name constructors and destructor */
    //@{ 
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    PlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the registered object.
        @param version Version of the registered object.
    */
    PlugIn(const BAS::String & name, const BAS::String & version);

    /// destructor
    virtual ~PlugIn();
    //@}
  
    /**@name special functions */
    //@{
    /// Thread loop, to catch all messages.
    virtual void execute();

    /** Receive all incomming messages.
      * All incomming messages will be stored in the internal queue.
    */
    virtual void receiveMessage(const BAS::Message& msg);
    
    /** Check if the message name is known. 
        return true if known, else false.
    */
    bool testMessageName(const BAS::String & msg) const;
    
    // returns the complete log file name (path prefix name suffix).
    const BAS::String & logFileComplName() const;
    
    ///
    virtual bool isUsable();
    //@}
    
  protected:
    /**
    */
    Stream* log() const; 
    /**
    */
    void        log(Stream* aLog);

  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    PlugIn(PlugIn& right);
    const PlugIn& operator=(PlugIn& right);

    BAS::OnlyPointer<Stream>  logM;
    STR::Queue<BAS::Status*>       queueM;

    /** diagnostic data handler instance
     */
    OMF::DiagnosticDataHandler* diagnosticDataHandlerM;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline Stream* PlugIn::log() const
{
  RWPRECONDITION(logM.get() != rwnil);
  return logM.get();
}

//------------------------------------------------------------------------------

inline void PlugIn::log(Stream* aLog)
{
  logM = aLog;
}

inline const BAS::String & PlugIn::logFileComplName() const
{
  RWPRECONDITION(logM.get() != rwnil);

  return logM->logFileComplName();
}
}

//------------------------------------------------------------------------------

#endif // LOG_PLUGIN_HPP
