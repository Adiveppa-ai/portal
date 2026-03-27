#ifndef LOG_MESSAGEENTRY_HPP
#define LOG_MESSAGEENTRY_HPP 1

// @(#)%Portal Version: MessageEntry.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:44:37 %
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
// Responsible: Mei-Feng Liu
//
// MessageEntry.hpp
//==============================================================================

#ifndef   RW_TOOLS_STRING_H
  #include <rw/rwstring.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace LOG
{
/** <tt><b>MessageEntry</b></tt> is the log message entry class.
    <p>Instances of this class are used to set up the log message table.

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
*/

class MessageEntry D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name Public Constructors and Destructor */
    //@{

      /** Default constructor.
       */
      MessageEntry();
      /**
       * @param mName  The message name of the entry.
       * @param mText  The message text of the entry.
       * @param mNumber The message number of the entry.
       */
      MessageEntry(const BAS::String& mName, const BAS::String& mText, const int64& mNumber);

      /// Destructor.
      ~MessageEntry();
    //@}

    /** Copy constructor.
        @param rVal log message entry to be copied.
    */
    MessageEntry(const MessageEntry& rVal);

    /** Assignment operator.
    */
    MessageEntry& operator=(const MessageEntry& rVal);
 
    /**
     * @return The log message name
     */
    const BAS::String& messageName() const;

    /**
     * @return The log message text
     */
    const BAS::String& messageText() const;

    /**
     * @return The log message number
     */
    const int64& messageNumber() const;

  private:
    // private attributes
    BAS::String msgNameM;
    BAS::String msgTextM;
    int64        msgNumberM;
};

//------------------------------------------------------------------------------

inline const BAS::String&
MessageEntry::messageName() const
{
  D_ENTER("LOG::MessageEntry::messageName() const");
  return msgNameM;
}

//------------------------------------------------------------------------------

inline const BAS::String&
MessageEntry::messageText() const
{
  D_ENTER("LOG::MessageEntry::messageText() const");
  return msgTextM;
}

//------------------------------------------------------------------------------

inline const int64&
MessageEntry::messageNumber() const
{
  D_ENTER("LOG::MessageEntry::messageNumber() const");
  return msgNumberM;
}
}
#endif // LOG_MESSAGEENTRY_HPP
