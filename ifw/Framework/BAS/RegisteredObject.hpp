#ifndef BAS_REGISTEREDOBJECT_HPP
#define BAS_REGISTEREDOBJECT_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   RegisteredObject class implementation.
//
//------------------------------------------------------------------------------
// Revision: 10005  07-Feb-2006  msung
// PRSF00191793: Rename getInstrumentationData() to getInstrumentationProbe()
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.68  2001/07/05 13:33:28  mwriedt
// PETS #36700: Account Synchronisation - added observers(), update(const
// BAS_Status&) and notify(const BAS_Status&).
//
// Revision 1.67  2001/05/02 12:50:00  bt
// Method pipelineLog() added.
//
// Revision 1.66  2000/02/11 10:44:57  aro
// Code fromatting fixed, preconditions added.
//
// Revision 1.65  2000/02/11 07:20:17  clohmann
// Observer pattern changed.
//
// Revision 1.64  2000/01/18 07:50:30  jkeckst
// this is the new version for v4.0. include the methode
// setEDRContainerIndices
//
// Revision 1.63  1999/08/27 13:06:54  clohmann
// isUsable() Method added.
//
// Revision 1.62  1999/06/11 13:14:06  jkeckst
// add the methods setBoolFlag and updateBoolFlag to set and update bool vars in the registry
//
// Revision 1.61  1999/06/01 11:59:24  aro
// BAS_Message::set() now clears the instance.
//
// Revision 1.60  1999/05/26 08:50:33  aro
// sendRequest() now returns false if a request can not be served.
//
// Revision 1.59  1999/05/25 14:28:09  aro
// BAS_RegisteredObject::evalEnviroment() added.
//
// Revision 1.58  1999/05/21 12:21:52  aro
// sendRequest/receiveRequest added to BAS_RegsiteredObject.
//
// Revision 1.57  1999/05/07 13:26:25  aro
// setStatus() now always clears the old error.
//
// Revision 1.55  1999/04/29 15:00:53  arockel
// String conversions extended, framework version information method added.
//
// Revision 1.54  1999/04/27 12:50:52  bt
// friend class BAS_Thread added.
//
// Revision 1.53  1999/04/27 07:51:16  arockel
// BAS_ErrorStatus renamed to BAS_Status.
//
// Revision 1.52  1999/04/22 08:11:47  arockel
// Receive message for BAS_Status removed.
//
// Revision 1.51  1999/04/16 08:03:11  arockel
// BAS_RegisteredObject::registryRoot() added.
//
// Revision 1.50  1999/04/16 07:18:33  arockel
// Forward to log in BAS_RegisteredObject::setStatus() made optional.
//
// Revision 1.48  1999/04/15 12:51:49  arockel
// errno now initialised.
//
// Revision 1.47  1999/04/15 09:19:24  arockel
// BAS_RegisteredObject::registryUpdate now returns true.
//
// Revision 1.46  1999/04/14 12:24:19  jkeckst
// add send and receive methods for BAS_Status
//
// Revision 1.45  1999/04/13 12:25:42  arockel
// BAS_RegisteredObject::superName() added.
//
// Revision 1.43  1999/03/31 12:48:13  arockel
// Method BAS_RegsiteredObject::readRegsitry() added.
//
// Revision 1.42  1999/03/30 14:52:02  arockel
// STR_InputFile and BAS_Directory improved.
//
// Revision 1.40  1999/03/26 15:09:27  arockel
// Registry syntax extended to support verbose output.
//
// Revision 1.34  1999/03/25 11:54:08  arockel
// BAS_RegistryEntry: verbose output added; registry made modifyable for BAS_RegisteredObject.
//
// Revision 1.32  1999/03/24 14:54:16  arockel
// Registry update methods added to BAS_RegisteredObject.
//
// Revision 1.31  1999/03/24 12:58:11  arockel
// BAS_RegsiteredObejct::baseName() added.
//
// Revision 1.30  1999/03/24 08:40:21  arockel
// BAS_RegisteredObject: status(err) renamed to setStatus(); minor improvements in others.
//
// Revision 1.28  1999/03/23 16:01:26  arockel
// Error logging implemented.
//
// Revision 1.27  1999/03/23 12:27:37  arockel
// BAS_RegistryEntry::isRootNode(bool) removed; online doc improved.
//
// Revision 1.26  1999/03/23 10:44:37  arockel
// BAS_RegisteredObject::rootName() added.
//
// Revision 1.25  1999/03/23 10:16:28  arockel
// BAS_RegisteredObject::registy() fixed to work for complete names.
//
// Revision 1.23  1999/03/22 13:01:28  arockel
// Registry syntax fixed.
//
// Revision 1.22  1999/03/22 11:29:39  arockel
// protected status() removed.
//
// Revision 1.17  1999/03/18 13:02:43  arockel
// Error status access simplified.
//
// Revision 1.13  1999/03/17 10:02:08  arockel
// notify() renamed to receivedMessage(); error status accessors implemented.
//
// Revision 1.9  1999/03/16 13:57:24  arockel
// Message notification mechanism added.
//
// Revision 1.4  1999/03/15 11:53:45  arockel
// First usable version.
//
//==============================================================================

#ifndef RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h> 
#endif
#ifndef RW_TOOLS_TVSET_H
  #include <rw/tvset.h> 
#endif
#ifndef __rw_sync_RWTRecursiveLock_h__
  #include <rw/sync/RWTRecursiveLock.h>
#endif
#ifndef __rw_sync_RWTMonitor_h__
  #include <rw/sync/RWTMonitor.h>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_REGISTRYENTRY_HPP
  #include "BAS/RegistryEntry.hpp"
#endif
#ifndef BAS_MESSAGE_HPP
  #include "BAS/Message.hpp"
#endif
#ifndef BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif
#ifndef BAS_PROTECTEDBOOL_HPP
  #include "BAS/ProtectedBool.hpp"
#endif
#ifndef BAS_INSTRUMENTATION_PROBE_LIST_H
  #include "BAS/InstrumentationProbeList.hpp"
#endif
namespace BAS
{
class RegisteredObject;
typedef RWTValHashMap<String, RegisteredObject*, StringHash, equal_to<String> > ObjectTable;
typedef RWTValSet<RegisteredObject*, less<RegisteredObject*> >                          ObjectList;

/** <tt><b>RegisteredObject</b></tt> is the base class for all registered objects.

    <p>A registered object is defined as a long-living implementation object that
    <ul>
    <li> is able to use the <em>registry</em> to parameterise itself,
    <li> has a system-unique name assigned that can be used as an identifier,
    <li> is registered in the global object table,
    <li> might support the <em>observer pattern</em> as subject and/or as observer,
    <li> might support (be able to receive and interpret) messages.
    </ul>

    <p>Before this class and its derived classes are fully operational, 
    <ul>
    <li>the <em>root name</em> should be set using the class method 
        <tt>RegisteredObject::rootName()</tt>,
    <li>the pointer to the root of the registry should be set using the class method
        <tt>RegisteredObject::registry()</tt>.
    <li>the pointer to the log object should be set using the class method
        <tt>RegisteredObject::log()</tt>.
    </ul>

    <p>Messages to the log are written if
    <ul>
    <li>the internal error status is changed using <tt>setStatus()</tt>,
    <li>or if the internal error status is set using <tt>setStatus</tt> <em>and</em>
        the new error status comes from the same instance.
    </ul>

    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>none</dd>
      <dt><b>Messages send</b></dt>
        <dd>none</dd>
      <dt><b>Messages received</b></dt>
        <dd>none</dd>
      <dt><b>Errors</b></dt>
	<dd>WRN_SEMAPHORE_NOT_PROCESSED
        <dd>ERR_OBJ_NOT_REGISTERABLE
        <dd>ERR_OBJ_ALREADY_REGISTERED
    </dl> 
*/
class RegisteredObject D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name Creation and destruction*/
    //@{
    /** Standard constructor.
      * Creates an unregistered object. */
    RegisteredObject();

    /** Standard registration constructor.
        Creates an object and trys to register it.
        The success of the registration operation has to be checked using 
        the <tt>isRegistered()</tt> method. 
        @param name The system wide instance identifier, e.g. "<tt>integrate.Pipelines.eplus</tt>". 
    */
    RegisteredObject(const String& name);

    /** Destructor. 
      * If the object is registered, the destructor will remove it from the object table. */
    virtual ~RegisteredObject();
    //@}

    /**@name RegisteredObject state accessors*/
    //@{
    /** Object registration status. 
        To be checked after construction. 
        If the status is false, the object can not be used and should be destroyed. 
        @return <tt>False</tt>: object is not registered,<br> 
                <tt>true</tt> otherwise.
    */
    bool isRegistered() const;

    /** Object validity.<br>
        This attribute is initialised to <tt>true</tt>. It should be set in derived classes to reflect
        the status of the registry evaluation or anything else that affects the usability of 
        the instance.
        @return <tt>False</tt> if the instance is invalid (e.g. because of an invalid registry update)
                and shall not be used;<br> 
                <tt>true</tt> the instance can be used.
    */
    bool isValid() const;

    /** Object usability.<br>
        This method is used to determine the usability of an registered object at runtime. 
        The method must test the following conditions
        <dl> 
         <dd>The isValid attribut.</dd>
         <dd>The usability of the base class.</dd>
         <dd>The internal state of the object. (e.g. registry parameter)</dd>
         <dd>The usability of all members, which are registered objects. (e.g. sequencer)</dd>
         <dd>The usability of all connected objects. (e.g. connected plugin's)</dd>
        </dl>
        If one of these tests fails, the method has to return false.

        @return <tt>false</tt> if the object is not usable 
                <tt>true</tt> if the object is usable.
    */ 
    virtual bool isUsable();

    /** Error status.
	 * The status is returned by value instead of by reference to handle
	 * situations where a reader and writer manipulate the status 
	 * concurrently.
	 * @return Error status of the instance. 
	 */
    const Status status() const;
    //@}

    /**@name RegisteredObject access methods*/
    //@{
    /** Instance name.
        This method returns the registered name of the instance.
        @return The registered name of the instance. 
        If the name is empty, the instance can not be registered (this is checked
        by a precondition in the DEBUG version).
    */
    const String& name() const;

    /** Instance base name.
        This method returns the base name of the instance, which is the last 
        part of the registered name.<br> 
        Example: Instance name is <tt>integrate.Pipelines.eplus</tt>,
        base name is <tt>eplus</tt>.
        @return The base name of the instance.
    */
    const String& baseName() const;

    /** Instance dir name.
        This method returns the dir name of the instance, which is the first part of 
        the registered name (the opposite of baseName()).<br>
        Example: Instance name is <tt>integrate.Pipelines.eplus</tt>,
        dir name is <tt>integrate.Pipelines</tt>.
        @return The dir name of the instance.
    */
    const String dirName() const;

    /** Name of a superior object.
        This method returns the complete name of an object to which
        the own instance is connected via a direct or indirect instance
        connection.<br>
        Example: The own instance name is <tt>integrate.Pipelines.eplus.Functions.Thread01.dtag</tt>.
        Parameter is <tt>Pipelines</tt>, result is <tt>integrate.Pipelines.eplus</tt>.
        @param  superGroup Base name of the object superior to the object in question.
        @return Complete name of the superior object.
    */
    const String superName(const String& superGroup) const;
    //@}

    /**@name Registry / registration methods*/
    //@{
    /** Object registration method.
        Returns false if the object could not be registered successfully.
        Side effect: Sets the error status of the instance if the registration fails.
        Note: Thread-safe access to the object table. 
        @param name The system wide instance identifier, e.g. "<tt>integrate.Pipelines.eplus</tt>".
        @return <tt>False</tt> if the object could not be registered,<br> 
                <tt>true</tt> otherwise.
    */
    bool registerAs(const String& name);

    /** Returns a const pointer to corresponding registry subtree. 
        This method can only be called when 
        <ul>
        <li>the object is registered, 
        <li>the root node of the registry has been set in the class.
        </ul>
        Both conditions are checked by a precondition when compiled with
        the option DEBUG.
        Note 1: The returned object can be changed, but it is not allowed to
        delete it.
        Note 2: Method provides thread-safe access to the registry. 
        @return Pointer to the corresponding registry node,<br>
                0 if the object was not found in the registry.
    */
    RegistryEntry* const registry() const;
    //@}

    /**@name Message reception*/ 
    //@{
    /** Notify an instance about a message.
        This method should be redefined in derived classes that want to 
        receive messages. 
        @param msg The message.
    */
    virtual void receiveMessage(const Message& msg);

    /** Forward a request to an instance.
        This method should be redefined in derived classes that want to 
        serve requests.
        By convention, when the request can not be served, the
        argument list of the message has to remain empty 
        (or has to be cleared).
        @param msg The message (in/out parameter).
    */
    virtual void receiveRequest(Message& msg);
    //@}

    /**@name Observer pattern - observer methods*/
    //@{
    /** Update method - to be redefined in derived classes.
        This method has to be redefined appropriatly in classes
        derived from <tt>RegisteredObject</tt> which act as observers. 
    */
    virtual void update(const String& name);

    /** Update method - to be redefined in derived classes.
        This method has to be redefined appropriatly in classes
        derived from <tt>RegisteredObject</tt> which act as observers. 
    */
    virtual bool update(const Status& status);
    //@}
    
    /**@name Observer pattern - subject methods*/
    //@{
    /** Attach an observer to a subject.
        @param observer The instance that wants to be registered as an observer.
    */
    void attach(RegisteredObject* observer);

    /** Detach an observer from a subject
        @param observer The instance that wants to be unregistered as an observer.
    */
    void detach(RegisteredObject* observer);
    //@}

    /** Get Instrumentation Probe for the object
        @param dataList reference to list of InstrumentationProbe objects 
        @return returns nothing, new InstrProbe is appended to probeList
    */

	virtual void getInstrumentationProbe(BAS::InstrumentationProbeList& probeList) const;

    /**@name RegisteredObject static class methods*/
    //@{
    /** Returns the object table instance. 
        Note: Thread-safe access. 
        @return Reference to the single object table instance.
    */
    static ObjectTable& objectTable();

    /** Searches an instance in the object table.
        Returns a null-pointer if the instance wasn't found. 
        Note: Thread-safe access to the object table. 
        @param name The instance identifier.
        @return <tt>0</tt> if the instance was not found,<br> 
                pointer to instance otherwise.
    */
    static RegisteredObject* find(const String& name);

    /** Sends a message to the designated object.
        Returns false if there is no such object, true otherwise.
        Note: Thread-safe access to the object table. 
        @param msg The message.
        @return <tt>True</tt> if the destination object was found,<br>
                <tt>false</tt> otherwise.
    */
    static bool sendMessage(const Message& msg);

    /** Sends a request to the designated object.
        The parameter is used to identify the request and to 
        enclose the return value(s).
        Returns false if there is no such object, true otherwise.
        The convention for sending / receiving is the follwing:
        The request is encoded in the message name (name starts with <tt>REQ_*</tt>).
        The result is returned in the first slot (and following, if required) 
        of the argument list.
        Note: Thread-safe access to the object table. 
        @param msg The message (in/out parameter).
        @return <tt>True</tt> if the destination object was found <em>and</em> the 
                argument list is not empty,<br>
                <tt>false</tt> otherwise.
    */
    static bool sendRequest(Message& msg);

    /** Assign the registry to the registered object tree.
        Note: Thread-safe access. 
        @param rootEntry Pointer to the root node of the registry (shall not be 0).
    */
    static void registry(RegistryEntry* rootEntry);

    /** Return the root node of the registry tree assigned to the 
        registered object class hierarchy.
        @return The registry root.
    */
    static const RegistryEntry* registryRoot();

    /** Assign the root name of the registry and the object tree.
        @param name The root name, e.g. <em>integrate</em>.
     */
    static void rootName(const String& name);

    /** Get the root name.
        @return Reference to the root name.
     */
    static const String& rootName();

     /** Assign the log object to the class.
         @param logger Pointer to the log object. 
     */
    static void log(RegisteredObject* logger);

     /** Get the log object.
         @return Pointer to the log object. 
     */
    static RegisteredObject* log();

     /** Get the pipeline log object for the given module name.
         @param name The module name.
         @return <tt>0</tt> if the object was not found,<br> 
                 pointer to the pipeline log object otherwise.
     */
    static RegisteredObject* pipelineLog(const String& name);

    /** Registry update method.<br>
        This method visits the registry tree from the bottom up and calls
        the method <tt>registryUpdate()</tt> for all objects whose names are contained
        in the tree. The update method for each object is called with the corresponding
        registry node.
        @return <tt>True</tt> if the update was successful for all found objects,<br>
                <tt>false</tt> otherwise.
    */
    static bool updateObjects(const RegistryEntry* newReg);

    /**
    */
    static const String dirName(const String& id);

    /** Returns the frame work version information.
        Note that this information reflects the CVS tag which was used
        to check out the sources. It is not set when a "normal"
        checkout (without specifiyng a tag) is done.
    */
    static const String& frameWorkVersion();

    /** Returns the system copyright information.
    */
    static const String& copyRightInfo();

    /** Self test method (<em>for internal use only</em>).
        @return <tt>True</tt> if the class test was succesful,<br> 
                <tt>false</tt> otherwise.
    */
    static bool selfTest();
    //@}

	/** @name Status setting methods
	 * These became public so as to facilitate the formatting of messages
	 * by helper classes to generalize error logging
	 */
	//@{

    /** Sets the instance's error status.<br>
        The internal error status is set to the given values.
        <p>If the originator name is not set in the error status
        or equals the instance name AND the optional parameter forward to log is 
        not changed, the error is also forwarded to
        the log (if it was initialised before).
        @param error The error identifier.
        @param sev   The severity.
        @param arg   An optional argument. 
        @param forwardToLog Should only be changed by those who know what they are doing.
    */
    void setStatus(const String&          error, 
                   const Status::Severity sev          = Status::normal,
                   const String&          arg          = "",
                   bool                       forwardToLog = true);

    /** Sets the instance's error status.<br>
        The internal error status is set to the given values.
        <p>If the originator name is not set in the error status
        or equals the instance name AND the optional parameter forward to log is 
        not changed, the error is also forwarded to
        the log (if it was initialised before).
        @param error The error identifier.
        @param sev   The severity.
        @param args  The argument list.
        @param forwardToLog Should only be changed by those who know what they are doing.
    */
    void setStatus(const String&          error, 
                   const Status::Severity sev,
                   const StringList&      args,
                   bool                       forwardToLog = true);

    /** Set the instance's error status.<br>
        The internal error status is replaced by the given status.
        <p>If the originator name is not set in the error status
        or equals the instance name AND the optional parameter forward to log is 
        not changed, the error is also forwarded to
        the log (if it was initialised before).
        @param err The new error status.
        @param forwardToLog Should only be changed by those who know what they are doing.
    */
    void setStatus(const Status& err, bool forwardToLog = true); 

	//@}

  protected:
    /** Mark instance as valid or invalid.<br>
        This method has to be used to express the usability of the instance.
        E.g., after a successful registry update, this should be set to true.
        @param val The new validity status.
    */
    void isValid(const bool val);

    /** Reset the instance's error status.
    */
    void clearStatus();

    /** Subject notification method.
        This method has to be called internally when an object acting
        as a subject wants to notify its observers (observer pattern). 
    */
    void notify() const;

    /** Subject notification method.
        This method has to be called internally when an object acting
        as a subject wants to notify its observers (observer pattern). 
    */
    bool notify(const Status& status) const;

    /** Return the list of observers.
    */
    const ObjectList& observers() const;

    /** Initilialise an instance from the registry.
        This method has to be re-implemented in every class to evaluate its registry
        entries. Normally this method should be called internally by the constructor of
        the class.
        @return <tt>False</tt> if the object could not initialise itself successfully,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool readRegistry();

    /** Initilialise an instance from the environment. In this method, initialistation 
        information is collected from other instances in relationship to this one.
        To get information from other instances that are not in direct relation to
        the own instance, the instance can check the registry for the other instance or 
        can use the method <tt>sendRequest()</tt> to get the information directly. 
        In the latter case, the other instance has to have a proper <tt>receiveRequest()</tt> 
        method.<br>
        This method has to be re-implemented in every class that to need to evaluate 
        its environment as described above.
        Normally this method should be called internally by the constructor of
        the class.
        @return <tt>False</tt> if the object could not initialise itself successfully,<br>
                <tt>true</tt> otherwise.
    */             
    virtual bool evalEnvironment();
    
    /** Ascertain all needed indices for the access to the EDR-Container.
        For every field that must read or write you have to know the index
        for the access methods.
        This method has to be re-implemented in every class that to need to
        access to the EDR-Container.
        Normally this method should be called internally by the constructor of
        the class.
        @return <tt>False</tt> if one or more indices couldn't acertain,<br>
                <tt>true</tt> otherwise.
        
    */
    virtual bool setEDRContainerIndices();
    

    /** Update the state of an instance from a new registry.<br>
        This method has to be redefined in derived classes that shall
        have the ability to change their state via a registry update.
        <p>Note 1: The default implementation provided by this class
        always returns true and does nothing. This version is called
        for all classes that do not provide the registry update feature.
        
        <p>Note 2: This method is protected because it shall only be called
        by the static method <tt>updateObjects()</tt>.

        @param update   Pointer to a registry subtree that shall be scanned for
                        change requests.
        @param workedOn Reference to a boolean that should be set to
                        <tt>true</tt> if this registered object changes
                        something because of a change request found in
                        the other (i.e. update) parameter.
	@param workedOn Reference to set to true if anything was changed.
        @return <tt>False</tt> if the object could not update itself successfully,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool registryUpdate(const RegistryEntry* update,
                                ProtectedBool&       workedOn);
    
    /** Convenience method.
      Updates a boolean variable and a registry with the a new value.
      This method tries to find the subEntryStr in the update registry.
      If found, it is used to set the boolean variable to the new value. 
      Then system registry is updated. A status message is sent to the
      the pipeline log.
      @param update The update registry with the new values.
      @param systemRegistry The original registry (systemRegistry = registry())
      @param subEntryStr The item to find in both registrys.
      @param boolFlag The bool variable to set with the determined value.
      @param funcName The calling function name. Used for the status message.
      @param workedOn Reference to set to true if anything was changed.
      @return <tt>true</tt> allways.
    */    
    virtual bool updateBoolFlag(const RegistryEntry* update,
                                RegistryEntry*       systemRegistry,
                                const String&        subEntryStr,
                                bool&                boolFlag,
                                const String&        funcName,
				ProtectedBool&       workedOn);
    /** Convenience method.
      Read a bool value from the registry and set the variable.
      This method tries to find the subEntryStr in the registry (update).
      If the value is "TRUE" the bool variable is set to true. All other
      values are interpreted as false. If no entry is found, the variable is unchanged.
      @param update The registry where to find subEntryStr.
      @param subEntryStr The item to find in the registry.
      @param boolFlag The bool variable to set with the determined value.
      @return  <tt>False</tt> the subEntryStr couldn't be found <br>
                <tt>true</tt> otherwise.
    */
    virtual bool setBoolFlag(const RegistryEntry* myEntry,
                             const String&        subEntryStr,
                             bool&                    boolFlag);

    /** Convenience method.
      This function when called in a thread gets the threadId, name associated
      with thread and logs it in the process log.
     */
     void logThreadId();
  private:
    // Hidden functions and operators
    RegisteredObject(const  RegisteredObject& original);
    const RegisteredObject& operator=(const RegisteredObject& rVal);

    // Log writer method
    void                         writeLog(const Status& err);

    // Recursive registry evalution method.
    static bool bottomUpEvaluation(const RegistryEntry* newReg, 
                                   StringList&          stack,
                                   ProtectedBool&       workedOn);

	//
	// State variables. These are protected with a single guard since
    // they are accessed relatively infrequently, therefore no benefit
	// to incurring the extra space for multiple guards. Note that a 
	// recursive-safe mutex is used to prevent deadlock when one guarded
	// method calls another (e.g. setStatus() calls name()).
	//
    String                   nameM;
    StringList               nameStackM;
    bool                         isRegisteredM;
    bool                         isValidM;
    Status                   statusM;
    ObjectList               observersM;

    // Class members
    BAS_EXPORT static ObjectTable       objectTableCM;
    BAS_EXPORT static RWMutexLock           objectTableLockerCM;

    BAS_EXPORT static RegistryEntry*    registryCM;
    BAS_EXPORT static RWMutexLock           registryLockerCM;

    BAS_EXPORT static String            rootNameCM;
    BAS_EXPORT static RWMutexLock           rootNameLockerCM;

    BAS_EXPORT static RWMutexLock           statusLockerCM;
    BAS_EXPORT static RWMutexLock           nameLockerCM;
    BAS_EXPORT static RWMutexLock           baseNameLockerCM;
    BAS_EXPORT static RWMutexLock           isRegisteredLockerCM;
    BAS_EXPORT static RWMutexLock           isValidLockerCM;
    BAS_EXPORT static RWMutexLock           observersLockerCM;
    BAS_EXPORT static RWMutexLock           dirNameLockerCM;
    BAS_EXPORT static RWMutexLock           nameStackLockerCM;
    BAS_EXPORT static RWMutexLock           isUsableLockerCM;
    BAS_EXPORT static RWMutexLock           registerAsLockerCM;

    BAS_EXPORT static RegisteredObject* logCM;

    BAS_EXPORT static String            frameWorkVersionCM;
    BAS_EXPORT static String            copyRightInfoCM;

    //--------------------------------------------------------------------------
    // friends
    //--------------------------------------------------------------------------
    
    friend class Thread;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline const Status
RegisteredObject::status() const 
{
  RWLockGuard<RWMutexLock> lock(statusLockerCM);

  return statusM;
}

//------------------------------------------------------------------------------

inline const String&
RegisteredObject::name() const
{
  RWLockGuard<RWMutexLock> lock(nameLockerCM);

  return nameM;
}

//------------------------------------------------------------------------------

inline const String&
RegisteredObject::baseName() const
{
  RWLockGuard<RWMutexLock> lock(baseNameLockerCM);

  return nameStackM.last();
}

//------------------------------------------------------------------------------

inline bool 
RegisteredObject::isRegistered() const
{
  RWLockGuard<RWMutexLock> lock(isRegisteredLockerCM);

  return isRegisteredM;
}

//------------------------------------------------------------------------------

inline bool 
RegisteredObject::isValid() const
{
  RWLockGuard<RWMutexLock> lock(isValidLockerCM);

  return isValidM;
}

//------------------------------------------------------------------------------

inline void 
RegisteredObject::isValid(const bool val)
{
  RWLockGuard<RWMutexLock> lock(isValidLockerCM);

  isValidM = val;
}

//------------------------------------------------------------------------------
inline ObjectTable&
RegisteredObject::objectTable()
{
  RWLockGuard<RWMutexLock> guard(objectTableLockerCM);
  return objectTableCM;
}

//------------------------------------------------------------------------------

inline void 
RegisteredObject::registry(RegistryEntry* rootEntry)
{
  RWLockGuard<RWMutexLock> guard(registryLockerCM);
  RWPRECONDITION(rootEntry);

  registryCM = rootEntry;
}

//------------------------------------------------------------------------------

inline void
RegisteredObject::setStatus(const String&          error,
                                const Status::Severity sev,
                                const String&          arg,
                                bool                       forwardToLog)
{
  RWLockGuard<RWMutexLock> lock(statusLockerCM);

  statusM.set(name(), error, sev, arg);
  if (forwardToLog) 
  {
     writeLog(statusM);
  }
}

//------------------------------------------------------------------------------

inline void
RegisteredObject::setStatus(const String&          error,
                                const Status::Severity sev,
                                const StringList&      args,
                                bool                       forwardToLog)
{
  RWLockGuard<RWMutexLock> lock(statusLockerCM);

  statusM.set(name(), error, sev, args);
  if (forwardToLog) 
  {
    writeLog(statusM);
  }
}

//------------------------------------------------------------------------------

inline void
RegisteredObject::clearStatus()
{
  RWLockGuard<RWMutexLock> lock(statusLockerCM);

  statusM.clear();
  statusM.originatorName(name());
}

//------------------------------------------------------------------------------

inline const ObjectList&
RegisteredObject::observers() const
{
  RWLockGuard<RWMutexLock> lock(observersLockerCM);

  return observersM;
}

//------------------------------------------------------------------------------

inline void 
RegisteredObject::rootName(const String& name)
{
  RWLockGuard<RWMutexLock> guard(rootNameLockerCM);
  rootNameCM = name;                              
}

//------------------------------------------------------------------------------

inline const String& 
RegisteredObject::rootName()    
{
  RWLockGuard<RWMutexLock> guard(rootNameLockerCM);
  return rootNameCM;                              
}

//------------------------------------------------------------------------------
                                          
inline void 
RegisteredObject::log(RegisteredObject* logger)
{
  RWPRECONDITION(logger);

  logCM = logger;
}

//------------------------------------------------------------------------------

inline RegisteredObject* 
RegisteredObject::log()
{
  return logCM;
}

//------------------------------------------------------------------------------

inline const String
RegisteredObject::dirName() const
{
  RWLockGuard<RWMutexLock> lock(dirNameLockerCM);

  return dirName(nameM);
}                      

//------------------------------------------------------------------------------

inline const RegistryEntry*
RegisteredObject::registryRoot()
{
  return registryCM;
}        

//------------------------------------------------------------------------------

inline const String&
RegisteredObject::frameWorkVersion()
{
  return frameWorkVersionCM;
}
             
//------------------------------------------------------------------------------

inline const String&
RegisteredObject::copyRightInfo()
{
  return copyRightInfoCM;
}
                          
//------------------------------------------------------------------------------
inline bool 
RegisteredObject::isUsable()
{
  RWLockGuard<RWMutexLock> lock(isUsableLockerCM);

  return isValid();
}
}
#endif // BAS_REGISTEREDOBJECT_HPP
