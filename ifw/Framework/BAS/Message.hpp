#ifndef BAS_MESSAGE_HPP
#define BAS_MESSAGE_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   Message class implementation.
//------------------------------------------------------------------------------
// Responsible: Alexander Rockel
//------------------------------------------------------------------------------
// $Log: BAS_Message.hpp,v $
// Revision 1.15  2002/01/15 09:29:07  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.14  2000/05/12 10:06:26  aro
// List constructores added for BAS_Message and BAS_Status.
//
// Revision 1.13  1999/05/12 08:05:17  aro
// Assigemnt operators fixed.
//
// Revision 1.12  1999/04/23 10:49:01  arockel
// BAS_Message::arguments made accessible for changes.
//
// Revision 1.8  1999/03/23 10:16:25  arockel
// BAS_RegisteredObject::registy() fixed to work for complete names.
//
// Revision 1.6  1999/03/18 13:02:41  arockel
// Error status access simplified.
//
// Revision 1.4  1999/03/17 13:25:22  arockel
// Error status enhanced.
//
// Revision 1.3  1999/03/16 15:56:25  arockel
// Message class enhanced.
//
// Revision 1.1  1999/03/16 13:57:22  arockel
// Message notification mechanism added.
//
//==============================================================================

#ifndef RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h> 
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace BAS
{
/** <tt><b>Message</b></tt> is the message class.

    <p>Instances of this class can be used whenever a registered
    objects wants to notify another registered object about
    something an there is no direct connection between the two
    (no instance relations through pointers etc.).

    <p>The  originator and the destination instances are identified by
    their registered name. When the message instance is build, it can 
    be send by the class method <tt>RegisteredObject::sendMessage()</tt>.
    
    <p>Any instance of <tt>RegisteredObject</tt> or its subclasses can 
    <em>send</em> messages. Classes that want to <em>receive</em> messages
    have to redefine the inherited method 
    <tt>RegisteredObject::receiveMessage()</tt>.

    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>n/a
        <dt><b>Messages send</b></dt>
        <dd>n/a
      <dt><b>Messages received</b></dt>
        <dd>n/a
      <dt><b>Errors</b></dt>
        <dd>n/a
    </dl>                     
*/
class Message D_THREADINFO
{
  D_SINGLETHREADED

  public:
    //--------------------------------------------------------------------------
    /** Default constructor.
    */
    Message();

    /** Initialising constructor.
        @param originator Identifier of the originating instance.
        @param destination Identifier of the destination instance.
        @param message Message to be sent.
        @param argument Optional argument for the message.
    */
    Message(const String& originator, 
                const String& destination,
                const String& message,
                const String& argument = "");

    /** Initialising constructor.
        @param originator Identifier of the originating instance.
        @param destination Identifier of the destination instance.
        @param message Message to be sent.
        @param arguments List of arguments.
    */
    Message(const String&     originator,
                const String&     destination,
                const String&     message,
                const StringList& argument);  

    /** Copy constructor.
        @param orig Message to be copied.
    */
    Message(const Message& orig);

    /** Destructor.
    */
    virtual ~Message();

    //--------------------------------------------------------------------------
    /** 
        @return Identifier of the originating instance. 
    */
    const String& originatorName() const;

    /**
        @param val Identifier of the originating instance.
    */
    void originatorName(const String& val);

    /**
        @return Identifier of the destination instance. 
    */
    const String& destinationName() const;

    /**
        @param val Identifier of the destination instance.
    */
    void destinationName(const String& val);

    /**
        @return The message string.
    */
    const String& messageName() const;

    /**
        @param val The message.
    */
    void  messageName(const String& val);

    /**
        @return The argument list.
    */
    const StringList& arguments() const;

    /**
        @return The argument list (changeable).
    */
    StringList& arguments();

    /**
        @param val An argument list.
    */
    void arguments(const StringList& val);

    /**
        @param val An argument (appended to the argument list).
    */
    void argument(const String& val);

    /**
    */
    void set(const String& originator,
             const String& destination,
             const String& message,
             const String& arg = "");

    /**
    */
    void set(const String&     originator,
             const String&     destination,
             const String&     message,
             const StringList& args);

    //--------------------------------------------------------------------------
    /** Assignment operator.
    */
    Message& operator=(const Message& rVal);
   
    /** Clearing of the message.
    */
    virtual void clear();

    /** Serialze the object
    *   @param out Output stream for serialization
    *   @return <b>true</b> on success, <b>false</b> otherwise
    */
    bool serialize(std::ostream& out) const;

    /** Restore the object
    *   @param in Input stream to use
    *   @return <b>true</b> on success, <b>false</b> otherwise
    */
    bool restore(std::istream& in);

  private:
    String     originatorNameM;
    String     destinationNameM;
    String     messageNameM;
    StringList argumentsM;
};

//------------------------------------------------------------------------------
/** Output operator
*/
std::ostream& operator<<(std::ostream& os, const Message& rVal);    

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline const String& 
Message::originatorName() const
{
  return originatorNameM;
}

//------------------------------------------------------------------------------

inline void 
Message::originatorName(const String& val)
{
  originatorNameM = val;
}

//------------------------------------------------------------------------------

inline const String& 
Message::destinationName() const
{
  return destinationNameM;
}

//------------------------------------------------------------------------------

inline void 
Message::destinationName(const String& val)
{
  destinationNameM = val;
}

//------------------------------------------------------------------------------

inline const String& 
Message::messageName() const
{
  return messageNameM;
}

//------------------------------------------------------------------------------

inline void  
Message::messageName(const String& val)
{
  messageNameM = val;
}

//------------------------------------------------------------------------------

inline const StringList& 
Message::arguments() const
{
  return argumentsM;
}

//------------------------------------------------------------------------------

inline StringList&
Message::arguments() 
{
  return argumentsM;
}                        

//------------------------------------------------------------------------------

inline void 
Message::arguments(const StringList& val)
{
  argumentsM = val;
}

//------------------------------------------------------------------------------

inline void 
Message::argument(const String& val)
{
  if (!val.isNull())
  {
    argumentsM.append(val);
  }
}

//------------------------------------------------------------------------------
}
#endif // BAS_MESSAGE_HPP

