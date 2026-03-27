#ifndef LOG_STREAM_HPP
#define LOG_STREAM_HPP 1
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LOG
//------------------------------------------------------------------------------
// Module Description:
//   The implementation of the log stream class.
//
//------------------------------------------------------------------------------
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.29  2001/10/16 10:28:34  jkeckst
// PETS 39582 - add new registry param WriteMessageKey
//
// Revision 1.28  2001/08/23 11:23:27  jkeckst
// update the message entries for the documentation
//
// Revision 1.27  2001/06/29 09:40:19  jkeckst
// solve PT0000000036554 - add new method to get the log file name
//
// Revision 1.26  2000/08/31 12:18:47  clohmann
// Misspelling corrected.
//
// Revision 1.25  2000/07/24 08:25:21  clohmann
// Code Review 07.2000.
//
// Revision 1.24  2000/07/11 12:09:08  jkeckst
// fix problem while writing the log level.
// fix PR.2086
//
// Revision 1.23  2000/06/15 13:02:28  jkeckst
// add new registry item SupressErrors.
//
// Revision 1.21  1999/11/24 09:23:22  jkeckst
// add new funtionality for logLevels
//
// Revision 1.20  1999/10/27 09:18:11  clohmann
// // CodeReview - 10.1999 - clohmann
//
//==============================================================================

#include <unistd.h>
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>   // RWTValHashMap
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   PBC_USABEL_HPP
  #include "PBC/Usable.hpp"
#endif
#ifndef   STR_FILEIO_HPP
  #include "STR/FileIo.hpp"
#endif
#ifndef   LOG_MESSAGETABLE_HPP
  #include "LOG/MessageTable.hpp"
#endif
namespace LOG 
{
/** <tt><b>Stream</b></tt>. 
    This class represents an output stream for messages (BAS::Strings only).

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Stream.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.29 $</font></td>
    <td><font size=-1>$Date: 2001/10/16 10:28:34 $</font></td>
    <td><font size=-1>$Author: jkeckst $</font></td>
    </tr>
    </table>                

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>FilePath</dd>
    <dd>FileName</dd>
    <dd>FileSuffix</dd>
    <dd>FilePrefix</dd>
    <dd>ShowOriginator</dd>
    <dd>LogLevel</dd>
    <dd>SuppressErrors</dd>
    <dd>WriteMessageKey</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_RENAME_LOG_FILE</dd>
    <dd>ERR_OPEN_LOG_FILE</dd>
</dl> 
*/
class Stream : public BAS::RegisteredObject
{
  public:
    /**@name constructors and destructor */
    //@{ 
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    Stream();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    Stream(const BAS::String & name);

    /// destructor
    virtual ~Stream();
    //@}

    /**@name get-set functions */
    //@{
    ///
    const BAS::Status::Severity logLevel() const;
    ///
    const BAS::String & logLevelStr() const;
    //@}
  
    /**@name special functions */
    //@{
    ///
    virtual bool registryUpdate(const BAS::RegistryEntry* myEntry,
                                BAS::ProtectedBool&       workedOn);
    /** Change the filename to the newLogFileName.
        The new file name can be null. Then the programm generates
        a new file name by date.
    */
    bool commit(const BAS::String& newLogFileName = "");

    /// Write the string to the output.
    virtual void write(const BAS::String& msg);

    /** To redefined in derevied classes,
        no implementation here.
    */ 
    virtual void write(const BAS::Status& msg);

    /** If an log is open, it will be closed.
    */
    void close();

    /** Open the log file for writing.
        If the file exists, the new text will be appended.
    */
    //bool open(const BAS::String& fileName = "");
    bool open(const BAS::String& fileName = "", bool writeLogLevel = true);

    /// Returns the actual Date/Time in the given format.
    BAS::String getFormatTime(BAS::String format) const;

    /** Replace all placeholders '%s' with the arguments in arg.
        If more placeholder then arguments the placeholders where removed.
        If more arguments then placeholders, they will be ignored.
    */
    static BAS::String ExpandMessageText(const BAS::String&     msgText,
                                 const BAS::StringList& arg) ;

    /**  Calls static method ExpandMessageText
    */
    BAS::String expandMessageText(const BAS::String&     msgText,
                                 const BAS::StringList& arg) const;

    /** Returns the text to the message name. 
        If message couldn't find in the DB, then an empty String returns.
    */
    BAS::String getMessageText(const BAS::String& msgName) const;

    /** Returns the number to the message name.
        If message not found in the DB, returns 0.
    */
    int64 getMessageNumber(const BAS::String& msgName) const;
    
    /** Check if the message name is known. 
        return true if known, else false.
    */
    bool testMessageName(const BAS::String& msgName) const;

    /** Returns the value showOriginator.
        This field can used to switch on/off to show the originator in the output.
        This field is optional and set default to false.
    */
    const bool showOriginator() const;

    /** Check if the message name is in the suppress message name collection.
      @Return true - found message, this message should be suppress.
      @Return false - message not in collection, this message should be written.
    */
    bool suppressError(const BAS::String & messageName);
    
    /// .
    virtual void writeLogLevelToFile();
    
    /** Returns the status of the write message key flag.
        It is used to write the message key to the log file.
    */
    const bool writeMsgKey() const;

    ///
    virtual bool isUsable();

    /// Return the log file name inc. path.
    const BAS::String & logFileComplName() const;
    
    /** Return the log file name from the last backup.
        It is set in the commit method.
    */ 
    const BAS::String & lastLogFileBackupName() const;
    //@}
    
  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    Stream(Stream& right);
    const Stream& operator=(Stream& right);

    bool readRegistry ();
    bool evalEnvironment();
    
    BAS::String createRandomName(); 

    bool getLogLevel(const BAS::String & level, BAS::Status::Severity & logLevel);
    bool lookForSuppressErrors(const BAS::RegistryEntry * subEntry);

    BAS::String    logFileNameM;
    BAS::String    logFileNameRegM;
    BAS::String    logFilePathM;
    BAS::String    logFilePrefixM;
    BAS::String    logFileSuffixM;
    BAS::String    logFileComplNameM;
    BAS::String    lastLogFileBackupNameM;
    bool           showOriginatorM;
    
    RWTValHashMap  <BAS::String , 
                    size_t, 
                    BAS::StringHash ,
                    equal_to<BAS::String> >  suppressErrorsM;

    LOG::MessageTable* 	   logMessageTableM;
    STR::FileIo            logFileM;
    PBC::Usable            usableM;
    BAS::Status::Severity  logLevelM;
    BAS::String            logLevelStrM;
    BAS::String            eventHandlerNameM;
    BAS::String		   rootNameM;
    bool                   writeMsgKeyM;
    
    LOG_EXPORT static const BAS::String registryFilePathCM;
    LOG_EXPORT static const BAS::String registryFileNameCM;
    LOG_EXPORT static const BAS::String registryFilePrefixCM;
    LOG_EXPORT static const BAS::String registryFileSuffixCM;
    LOG_EXPORT static const BAS::String registryShowOriginatorCM;
    LOG_EXPORT static const BAS::String registryLogLevelCM;
    LOG_EXPORT static const BAS::String registrySuppressErrorsCM;
    LOG_EXPORT static const BAS::String registryWriteMessageKeyCM;
    
    LOG_EXPORT static const BAS::String debugLevelCM;
    LOG_EXPORT static const BAS::String normalLevelCM;
    LOG_EXPORT static const BAS::String warningLevelCM;
    LOG_EXPORT static const BAS::String minorLevelCM;
    LOG_EXPORT static const BAS::String majorLevelCM;
    LOG_EXPORT static const BAS::String criticalLevelCM;
    
    
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline const bool Stream::showOriginator() const
{
  return showOriginatorM;
}

inline const BAS::Status::Severity Stream::logLevel() const
{
  return logLevelM;
}

inline const BAS::String & Stream::logLevelStr() const
{
  return logLevelStrM;
}

inline const BAS::String & Stream::logFileComplName() const
{
  return logFileComplNameM;
}

inline const BAS::String & Stream::lastLogFileBackupName() const
{
  return lastLogFileBackupNameM;
}

inline const bool Stream::writeMsgKey() const
{
  return writeMsgKeyM;
}

}
//------------------------------------------------------------------------------

#endif // STREAM_HPP
