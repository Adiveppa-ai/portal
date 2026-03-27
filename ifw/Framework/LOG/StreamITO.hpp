#ifndef LOG_STREAMITO_HPP
#define LOG_STREAMITO_HPP 
// @(#)%Portal Version: StreamITO.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:45:41 %
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//==============================================================================
// Block: LOG
//------------------------------------------------------------------------------
// Module Description:
//  <description>
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work, finished, accepted>
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: StreamITO.hpp,v $
// $Revision: 1.13 $
// $Author: jkeckst $
// $Date: 2000/07/11 12:09:08 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StreamITO.hpp,v $
// Revision 1.13  2000/07/11 12:09:08  jkeckst
// fix problem while writing the log level.
// fix PR.2086
//
// Revision 1.12  1999/11/24 09:23:22  jkeckst
// add new funtionality for logLevels
//
// Revision 1.11  1999/10/27 09:18:11  clohmann
// // CodeReview - 10.1999 - clohmann
//
// Revision 1.10  1999/10/06 12:08:33  jkeckst
// implement isUsable function
//
// Revision 1.9  1999/08/06 15:16:55  aro
// Updates to improve coding rule conformance;
// new method Stream::receiveMessage() implemented.
//
// Revision 1.8  1999/06/10 08:47:53  jkeckst
// *** empty log message ***
//
// Revision 1.7  1999/06/10 07:50:00  jkeckst
// *** empty log message ***
//
// Revision 1.6  1999/06/09 07:33:11  jkeckst
// *** empty log message ***
//
// Revision 1.5  1999/05/05 14:32:08  aro
// Online doc updated.
//
//==============================================================================
#if !defined LOG_EXPORT
  #if defined(WINDOWS)
    #if !defined(LOG_INTERNAL)
      #define LOG_EXPORT __declspec(dllimport)
    #else
      #define LOG_EXPORT __declspec(dllexport)
    #endif
  #else
    #define LOG_EXPORT
  #endif
#endif

#ifndef   LOG_STREAM_HPP
  #include "LOG/Stream.hpp"
#endif
#ifndef   BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif
#ifndef   BAS_INSTRUMENTATION_PROBE_TABLE_H
  #include "BAS/InstrumentationProbeTable.hpp"
#endif
#include "LogCircularBuffer.hpp"

namespace LOG
{

static BAS::String DefaultMsgStr = "";

/** <tt><b>StreamITO</b></tt> This class represents an output stream for messages (BAS::Status only). <br>

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: StreamITO.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.13 $</font></td>
    <td><font size=-1>$Date: 2000/07/11 12:09:08 $</font></td>
    <td><font size=-1>$Author: jkeckst $</font></td>
    </tr>
    </table>                

    The BAS::Status were changed into ITO format.<br>

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>LogMessageFileName</dd>
    <dd>LogFilePath</dd>
    <dd>LogFileName</dd>
    <dd>LogFileSuffix</dd>
    <dd>LogFilePrefix</dd>
    <dd>LogProcessName</dd>
    <dd>LogMessageGroup</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_MISSING_MESSAGE_FILE_NAME</dd>
    <dd>ERR_OPEN_MESSAGE_FILE</dd>
    <dd>ERR_OPEN_FILE</dd>
    <dd>ERR_RENAME_FILE</dd>
</dl> 
*/
class StreamITO : public Stream
{

  public :
    /**@name constructors and destructor */
    //@{ 
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    StreamITO();
    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    StreamITO(const BAS::String & name);
    /// destructor
    ~StreamITO();
    //@}
  
    /**@name special functions */
    //@{
    /// Write an string to the log file without any format.
    virtual void write(const BAS::String& msg);
    /// Writes the message in ITO format to the log file.
    virtual void write(const BAS::Status& msg);

    /** Write the formatted log message to log file
     * @param msg Log message
     * @param bufMsg Optional, formatted log message
     * @param forCircularBuf Optional.
     *        true - for circular buffer usage; set the formatted string in bufMsg
     *        false - normal logging to file 
     */    
    void writeDirect(const BAS::Status & msg, BAS::String& bufMsg = DefaultMsgStr, bool forCircularBuf = false);

    /// .
    void writeLogLevelToFile();
    /// .
    virtual bool isUsable();

    /** Get the probes
     */
    void getInstrumentationProbe(BAS::InstrumentationProbeList& probeList) const;

    //@}
    
  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    StreamITO(StreamITO& right);
    const StreamITO& operator=(StreamITO& right);

    void getMessageTextForITO(const BAS::String& msgName, 
                               BAS::String& msgText, 
                               int64& msgNum);
    bool readRegistry();
    
    BAS::String            hostNameM;
    BAS::String            processNameM;
    BAS::String            messageGroupNameM;
    u_int32                circularBufferSizeM;

    LOG_EXPORT static const u_int32 MaxLogEntriesCM;
    LOG_EXPORT static const u_int32 MaxLogEntrySizeCM;

    /** circular buffer to hold log messages of all levels
     */
    LogCircularBuffer* msgBufM;

    /** Table for storing instrumentation probes
     */
    BAS::InstrumentationProbeTable* logCircularBufInfoInstrM;

    /** Initialize the probes.
     * @return True on success; otherwise, False.
     */
    bool initInstrumentationProbe();
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
/// This function is needed to prevent compiler warnings.
inline void StreamITO::write(const BAS::String& msg)
{
  Stream::write(msg);
}
}
//------------------------------------------------------------------------------

#endif // STREAMITO_HPP
