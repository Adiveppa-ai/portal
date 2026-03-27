#ifndef LOG_MESSAGETABLE_HPP
#define LOG_MESSAGETABLE_HPP 1
//==============================================================================
//
// Copyright (c) 1996, 2023, Oracle and/or its affiliates. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
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
//   <in-work, finished, accepted>
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: MessageTable.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2009/07/02 21:40:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: MessageTable.hpp,v $
// Revision 1.12  2009/06/26 13:16:32 cprabhak 
// bug8605621 - Introduced new member variable numPtrVectorM to solve mem leak
//
// Revision 1.11  1999/10/27 13:16:32  jkeckst
// check code review and correct all errors
//
// Revision 1.10  1999/10/27 09:18:11  clohmann
// // CodeReview - 10.1999 - clohmann
//
// Revision 1.9  1999/10/06 12:08:33  jkeckst
// implement isUsable function
//
// Revision 1.8  1999/09/10 09:37:07  jkeckst
// check now for double or invalid items in the message file and
// for existing file.
//
// Revision 1.7  1999/08/31 12:56:02  jkeckst
// PR : 573 now the log file can handle more than one input file
//
// Revision 1.6  1999/06/10 08:47:53  jkeckst
// *** empty log message ***
//
// Revision 1.5  1999/06/10 07:50:00  jkeckst
// *** empty log message ***
//
// Revision 1.4  1999/06/09 07:33:11  jkeckst
// *** empty log message ***
//
// Revision 1.3  1999/05/05 14:32:05  aro
// Online doc updated.
//
// Revision 1.5  1999/04/15 11:18:49  jkeckst
// add some comments for doc++
//
// Revision 1.1  1999/03/25 12:36:03  jkeckst
// first try
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

#ifndef   RW_TOOLS_TPHMAP_H
  #include <rw/tphdict.h>
#endif
#ifndef   RW_TOOLS_STRING_H
  #include <rw/rwstring.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   STR_FILEIO_HPP
  #include "STR/FileIo.hpp"
#endif
#ifndef   BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   LOG_MESSAGEENTRY_HPP
  #include "LOG/MessageEntry.hpp"
#endif
namespace LOG
{
/** <tt><b>MessageTable</b></tt> The class to hold all messages.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: MessageTable.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2009/07/02 21:40:38 $</font></td>
    <td><font size=-1>$Author: cprabhak $</font></td>
    </tr>
    </table>                

    This class represents the message files.<br>
    A message file must have the following format:<br>
    [message name] | [message text] | [message number]<br>
    message name : it is the key to search in the DB for the message text and Number.<br>
    message number : (optional) if presents, can be used to search the message DB.<br>

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>MessageFilePath</dd>
    <dd>MessageFilePrefix</dd>
    <dd>MessageFileSuffix</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_MISSING_MESSAGE_FILE_NAME</dd>
    <dd>ERR_OPEN_MESSAGE_FILE</dd>
    <dd>ERR_NO_MESSAGE_FILE</dd>
    <dd>ERR_WRONG_TOKEN_COUNT</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_LINE_NOT_INSERTED_INVALID</dd>
    <dd>ERR_LINE_NOT_INSERTED_DOUBLE</dd>
</dl> 
*/

// Hashing function for int64 key
class LongHashingFunc {
public:
  int64 operator()(const int64& x) const
    {
     return x;
    }
};

class MessageTable : public BAS::RegisteredObject
{
  D_THREADSAFE
  public:
      /** @name Static public methods */
      //@{
      /**     Instantiates the singleton instance of the log message table. 
       *      Should be called exactly once.
       *      @param Registered name of the log message table.
       *      @return Pointer to log message table instance on success;
       *              otherwise, False.
       */
      static MessageTable* MakeInstance(const BAS::String& name);

      /** Accessor for the singleton log message table instance. The instance
       *      must be instantiated before using this method.
       *      @return Pointer to the log message table instance.
       */
      static MessageTable* GetInstance();

      /** Destroys the singleton instance of the log message table. Should be
       *      called exactly once.
       */
      static void DestroyInstance();

      //@}

      /**@name get operations */
      //@{
      /** Get the number of messages in the hash map
	   * @return int64 containing the number of messages mapped
      */
      const int64 msgCount() const;

      /** Get the message text for the given message name.
	   * @param msgName contains the message name to search.
	   * @param msgText The message text returned
	   * @return false: message name not found, true message name found.
      */ 
      bool getMessageTextByName(const BAS::String & msgName,
                                BAS::String & msgText) const;

      /** Get the message text for the given message number.
	   * @param msgNumber contains the message number to search.
	   * @param msgText The message text returned
	   * @return false: message name not found, true message name found.
      */ 
      bool getMessageTextByNumber(const int64& msgNumber,
                                BAS::String & msgText) const;

      /** Get the message number for the given message name.
	   * @param msgName contains the message name to search.
	   * @param msgNumber The message number returned
	   * @return false: message name not found, true message name found.
      */ 
      bool getMessageNumber(const BAS::String & msgName,
                                int64 & msgNumber) const;

      /** Get the message Name for the given message number.
	   * @param msgName contains the message name to search.
	   * @param msgNumber The message number returned
	   * @return false: message name not found, true message name found.
      */ 
      bool getMessageName(const int64& msgNumber,
                                BAS::String & msgName) const;
      //@}

  
  private:
      // Singleton instance of self.
      LOG_EXPORT static MessageTable* instanceM;

      /** @name Private Constructors */
      //@{
      /** Default constructor.
       * Constructs an 'invalid' object
       */
      MessageTable();

      /** Initializing constructor.
       *      @param Registered name of the log message table.
       */
      MessageTable(const BAS::String& name);
      //@}

      /** @name Private Destructors */
      //@{
      /** Standard destructor.
       */
      ~MessageTable();
      //@}

      // Default, copy constructor and assign operator are not implemented. 
      // They are private to prevent unintentionally use.
      MessageTable(const MessageTable& right);
      const MessageTable& operator=(const MessageTable& right);

      bool readRegistry ();

      bool readAllMessageFiles(const BAS::String & msgFilePath,
                          const BAS::String & msgFilePrefix,
                          const BAS::String & msgFileSuffix);

      bool readMessageFile(const BAS::String & fileName);

	/** Clear the hash map
	 * Clears any contained messages. This is called by the destructor
	 */ 
      void clearMessageDB();

  	/** Typedef for message database.
  	 * This is a pointer-based hash from strings to strings.
  	 */
      typedef RWTPtrHashMap<BAS::String , const MessageEntry, BAS::StringHash,
                equal_to<BAS::String> > messageDBNamePtrType;

  	/** Typedef for message database.
  	 * This is a pointer-based hash for 'int64'.
  	 */
      typedef RWTPtrHashMap<int64 , const MessageEntry, LongHashingFunc,
                equal_to<int64> > messageDBNumberPtrType;

	/** enumeration containing characters that are special to the 'parser'
	 * # is used to indicate a comment
	 * | is the seperator between the message name and the string
	 */
      enum SPECIAL_CHARS 
	{
      COMMENT_CHAR = '#',
      TOKEN_CHAR   = '|'
      };

	/** Storage for the hash map */
      messageDBNamePtrType   messageDBNamePtrM;
      messageDBNumberPtrType messageDBNumberPtrM;

      LOG_EXPORT static const BAS::String registryMessageFilePathCM;
      LOG_EXPORT static const BAS::String registryMessageFilePrefixCM;
      LOG_EXPORT static const BAS::String registryMessageFileSuffixCM;

};


inline const int64 MessageTable::msgCount () const
{
  return messageDBNamePtrM.entries();
}

inline void MessageTable::clearMessageDB ()
{
  messageDBNamePtrM.clear();
  messageDBNumberPtrM.clear();
}
}

#endif
