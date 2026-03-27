#ifndef BAS_STATUS_HPP
#define BAS_STATUS_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
// only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   ErrorStatus class implementation.
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//------------------------------------------------------------------------------
// $Log: BAS_Status.hpp,v $
// Revision 1.23  2002/01/15 09:29:07  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.22  2000/07/27 10:53:46  mwriedt
// Set-method without originator added.
//
// Revision 1.21  2000/07/06 11:18:49  mwriedt
// Constructor without originator added.
//
// Revision 1.20  2000/06/15 12:17:52  bt
// Changes for AIX xlC V366.
//
// Revision 1.19  2000/05/12 10:06:26  aro
// List constructores added for BAS_Message and BAS_Status.
//
// Revision 1.18  1999/11/24 09:22:49  jkeckst
// add new severity state undef
//
// Revision 1.17  1999/06/01 11:59:24  aro
// BAS_Message::set() now clears the instance.
//
// Revision 1.16  1999/05/12 08:05:22  aro
// Assigemnt operators fixed.
//
// Revision 1.15  1999/05/06 17:28:08  aro
// CVS Recovery.
//
// Revision 1.15  1999/05/06 08:05:06  aro
// Content type enum in EDR simplified.
//
// Revision 1.14  1999/04/27 07:51:18  arockel
// BAS_ErrorStatus renamed to BAS_Status.
//
// Revision 1.13  1999/04/12 11:34:30  arockel
// BAS_Status::severityNames() added.
//
// Revision 1.9  1999/03/23 13:10:07  arockel
// Fix in BAS_Status.
//
// Revision 1.8  1999/03/23 10:16:23  arockel
// BAS_RegisteredObject::registy() fixed to work for complete names.
//
// Revision 1.6  1999/03/22 15:35:31  arockel
// Error Status changed, registry parser fixed.
//
// Revision 1.5  1999/03/18 13:02:39  arockel
// Error status access simplified.
//
//==============================================================================

#ifndef RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h> 
#endif
#ifndef __rw_sync_RWThreadId_h__
  #include <rw/sync/RWThreadId.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_MESSAGE_HPP
  #include "BAS/Message.hpp"
#endif

namespace BAS
{
/** <tt>Status</tt> is the global error status class.
    This class has to be used whenever a class needs an error
    status attribute or whenever an error has to be send around.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Status.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:50:10 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>
                                     
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
class Status: public Message
{
  D_SINGLETHREADED

  public:
    //--------------------------------------------------------------------------
    /** Severity.
        <ul>
        <li>undef -  the initial state for some values.
        <li>debug - error status evaluates to <tt>true</tt>
        <li>normal - error status evaluates to <tt>true</tt>
        <li>warning - error status evaluates to <tt>true</tt>
        <li>minor - error status evaluates to <tt>false</tt>
        <li>major - error status evaluates to <tt>false</tt>
        <li>critical - error status evaluates to <tt>false</tt>
        </ul>
    */ 
    enum Severity
    {
      undef     = -1,
      debug	= 0,
      normal    = 1,
      warning   = 2,
      minor     = 3,
      major     = 4,
      critical  = 5
    };                

    //--------------------------------------------------------------------------
    /** Default constructor.
    */
    Status();

    /** Copy constructor.
    */
    Status(const Status& orig);

    /** Specialised constructor.
        @param error The error identifier.
        @param sev The sevrity (optional).
        @param argument An error argument (optional).
    */
    Status(const String& error,
               const Severity    sev = normal,
               const String& argument = "");

    /** Specialised constructor.
        @param originator The identifying name of the originator of this error object.
        @param error The error identifier.
        @param sev The sevrity (optional).
        @param argument An error argument (optional).
    */
    Status(const String& originator, 
               const String& error,
               const Severity    sev      = normal,
               const String& argument = "");

    /** Specialised constructor.
        @param originator The identifying name of the originator of this error object.
        @param error The error identifier.
        @param sev The sevrity.
        @param argument A list of error arguments.
    */
    Status(const String& originator,
               const String& error,
               const Severity    sev,
               const StringList& argument);            

    /** Destructor.
    */
    virtual ~Status();

    //--------------------------------------------------------------------------
    /** The error status.
        @return <tt>True</tt>: no error,<br>
                <tt>false</tt> otherwise.
    */
    bool state() const;

    /** The severity of the error.
        If the severity is <tt>debug</tt>, 
	<tt>normal</tt> or <tt>warning</tt>, 
        the state is interpreted as <tt>true</tt> (ok).
        @return The error severity.
    */
    Severity severity() const;

    /** The severity descriptive name of the error.
        @return The error severity mapped to a string.
    */
    const String& severityName() const;

    /** The thread identifier */
    const unsigned int& threadId() const;

    /** The severity of the error (set method).
        @param sev The new error severity.
    */
    void severity(const Severity sev);

    /** Multi set method, single argument.
        @param error The error identifier.
        @param sev The error severity.
        @param arg The optional argument.
    */
    void set(const String& error,
             const Severity    sev = normal,
             const String& argument = "");

    /** Multi set method, single argument.
        @param originator The error initiating instance.
        @param error The error identifier.
        @param sev The error severity.
        @param arg The optional argument.
    */
    void set(const String& originator,
             const String& error,
             const Severity    sev = normal,
             const String& arg = "");

    /** Multi set method, argument list.
        @param originator The error initiating instance.
        @param error The error identifier.
        @param sev The error severity.
        @param args The optional argument list.
    */
    void set(const String&     originator,
             const String&     error,
             const Severity        sev,
             const StringList& args); 

    //--------------------------------------------------------------------------
    /** Assignment operator.
    */
    Status& operator=(const Status& rVal);

    /** Comparison operator (this pointer only).
    */
    bool operator==(const Status& rVal) const;

    /** Comparison operator (this pointer only).
    */
    bool operator<(const Status& rVal) const;

    /** Comparison operator (this pointer only).
    */
    bool operator!=(const Status& rVal) const;

    /** Boolean conversion operator.
        @return <tt>True</tt>: no error, <tt>false</tt> otherwise.
    */
    operator const bool()     const;
   
    /** Clears the error status.
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
    /**
    */
    Severity              severityM;       
    BAS_EXPORT static const String severityNamesCM[];
    unsigned int          threadIdM;
};

/** Output operator.
*/
std::ostream& operator<<(std::ostream& os, const Status& rVal);

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline bool
Status::state() const
{
  if (severity() > warning) 
  {
    return false;
  }
  else
  {
    return true;
  }
}

//------------------------------------------------------------------------------

inline Status::Severity
Status::severity() const
{
  RWPRECONDITION((severityM >= debug) && (severityM <= critical));
  return severityM;
}

//------------------------------------------------------------------------------

inline const String&
Status::severityName() const
{
  RWPRECONDITION((severityM >= debug) && (severityM <= critical));
  return severityNamesCM[severityM];
}

//------------------------------------------------------------------------------

inline const unsigned int&
Status::threadId () const
{
  return threadIdM;
}                              

//------------------------------------------------------------------------------

inline void
Status::severity(const Status::Severity sev)
{
  RWPRECONDITION((sev >= debug) && (sev <= critical));
  severityM = sev;
}                                                         

//------------------------------------------------------------------------------

inline bool
Status::operator==(const Status& rVal) const
{
  return (this == &rVal);
}

//------------------------------------------------------------------------------

inline bool
Status::operator<(const Status& rVal) const
{
  return (this < &rVal);
}

//------------------------------------------------------------------------------

inline bool
Status::operator!=(const Status& rVal) const
{
  return (this != &rVal);
}

//------------------------------------------------------------------------------

inline
Status::operator const bool() const
{
  return state();
}                              

//------------------------------------------------------------------------------
}
#endif // BAS_STATUS_HPP

