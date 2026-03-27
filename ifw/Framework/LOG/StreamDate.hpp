#ifndef LOG_STREAMDATE_HPP
#define LOG_STREAMDATE_HPP 
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
//   Declaration of the log stream date class. 
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
// $RCSfile: StreamDate.hpp,v $
// $Revision: 1.12 $
// $Author: jkeckst $
// $Date: 2000/07/11 12:09:08 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StreamDate.hpp,v $
// Revision 1.12  2000/07/11 12:09:08  jkeckst
// fix problem while writing the log level.
// fix PR.2086
//
// Revision 1.11  1999/11/24 09:23:22  jkeckst
// add new funtionality for logLevels
//
// Revision 1.10  1999/10/27 09:18:11  clohmann
// // CodeReview - 10.1999 - clohmann
//
// Revision 1.9  1999/10/06 12:08:33  jkeckst
// implement isUsable function
//
// Revision 1.8  1999/08/06 15:16:55  aro
// Updates to improve coding rule conformance;
// new method Stream::receiveMessage() implemented.
//
//==============================================================================

#ifndef   LOG_STREAM_HPP
  #include "LOG/Stream.hpp"
#endif
#ifndef   BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif
namespace LOG {
/** <tt><b>StreamDate</b></tt> This class represents an output stream for messages (BAS::Status only)..

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: StreamDate.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.12 $</font></td>
    <td><font size=-1>$Date: 2000/07/11 12:09:08 $</font></td>
    <td><font size=-1>$Author: jkeckst $</font></td>
    </tr>
    </table>                

    The BAS::Status were changed into DATE format.

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>LogMessageFileName</dd>
    <dd>LogFilePath</dd>
    <dd>LogFileName</dd>
    <dd>LogFileSuffix</dd>
    <dd>LogFilePrefix</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_MISSING_MESSAGE_FILE_NAME</dd>
    <dd>ERR_OPEN_MESSAGE_FILE</dd>
    <dd>ERR_OPEN_FILE</dd>
    <dd>ERR_RENAME_FILE</dd>
</dl> */
class StreamDate : public Stream
{
  public :
    /**@name constructors and destructor */
    //@{ 
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    StreamDate();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    StreamDate(const BAS::String& name);

    /// destructor
    virtual ~StreamDate();
    //@}
  
    /**@name special functions */
    //@{
    /// Write an string to the log file without any format.
    virtual void write (const BAS::String& msg);

    /// Write the message with prepended date / time stamp to the log file.
    virtual void write (const BAS::Status& msg);
    /// .
    void writeDirect(const BAS::Status & msg);
    /// .
    void writeLogLevelToFile();
    /// .
    virtual bool isUsable();
    
    //@}

  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    StreamDate(StreamDate& right);
    const StreamDate& operator=(StreamDate& right);

};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
// need this function to prevent compiler warnings
inline void StreamDate::write(const BAS::String& msg)
{
  Stream::write(msg);
}

//------------------------------------------------------------------------------
}
#endif // STREAMDATE_HPP
