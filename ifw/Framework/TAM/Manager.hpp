#ifndef TAM_MANAGER_HPP
#define TAM_MANAGER_HPP
//
// @(#)%Portal Version: Manager.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:46:45 %
//
//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: TAM
//
//------------------------------------------------------------------------------
// Module Description:
//   Transaction manager class implementation.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
//
// Responsible: bt
//
//------------------------------------------------------------------------------
//
// Revision 1.12 2010/07/09 Santanu
// BugBug 9871778  Added the new function demandCancelAll

// Revision 1.11 2006/01/25 10:54:37  brajan
// PRSF00190901 Fix TAM message logging + MLK in TAM/IRules (propagation of 156575 + 186125)
//
// Revision 1.10 2005/03/21 10:54:37  mliu
// PRSF00156818  Added new TAM method rollbackReason() to allow modules to ask
//               for the rollback reason.
//
// Revision 1.9  2001/09/26 16:54:37  bt
// PETS #39868 New TAM parameter 'SingleTransaction' added.
// If set to 'True' only one transaction can be generated at a time.
//
// Revision 1.8  2001/08/14 07:36:35  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.7  2001/06/25 09:01:32  bt
// Method cancelDemanded() added.
//
// Revision 1.6  2001/05/11 16:28:44  bt
// Write to pipeline log, transaction initialization and cancellation added.
//
// Revision 1.5  2001/05/08 09:19:26  bt
// Classes TransStatus and TransType removed. Class TransItem added.
//
// Revision 1.4  2001/04/25 08:03:18  bt
// rameter type of method attachModule() changed.
//
// Revision 1.3  2001/04/24 13:31:55  bt
// No comment.
//
// Revision 1.2  2001/04/19 17:23:06  bt
// No comment.
//
// Revision 1.1  2001/04/18 16:12:03  bt
// Initial version.
//
//==============================================================================

#if !defined TAM_EXPORT
  #if defined(WINDOWS)
    #if !defined(TAM_INTERNAL)
      #define TAM_EXPORT __declspec(dllimport)
    #else
      #define TAM_EXPORT __declspec(dllexport)
    #endif
  #else
    #define TAM_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   BAS_OBJECT_H
  #include "BAS/Object.hpp"
#endif
#ifndef   TAM_MANAGERIF_HPP
  #include "TAM/ManagerIf.hpp"
#endif
#ifndef   TAM_MODULEIF_HPP
  #include "TAM/ModuleIf.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   TAM_TRANSMAP_HPP
  #include "TAM/TransMap.hpp"
#endif
#ifndef   TAM_TRANSITEM_HPP
  #include "TAM/TransItem.hpp"
#endif
#ifndef   TAM_TRANSIDCONTROLLER_HPP
  #include "TAM/TransIdController.hpp"
#endif

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
namespace TAM
{
typedef RWTValMap< BAS::String,
                   ModuleIf*,
                   less<BAS::String> >   ModuleMap;
typedef ModuleMap::const_iterator   ModuleMapConstIterator;
typedef ModuleMap::iterator         ModuleMapIterator;

/** This class represents the transaction manager object.

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>RedoEnabled</dd>
    <dd>WriteToLogEnabled</dd>
    <dd>BinaryLogFileName</dd>
    <dd>TransactionIdController</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>none</dd>
</dl> 
*/
class Manager : public BAS::Object , public ManagerIf
{
  D_SINGLETHREADED

  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      Manager();

      /** Constructs the transaction manager instance.<br> 
        * @param objectName The string is used for the object registration. */
      Manager(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~Manager();

    //@}

    /**@name Public Member Functions */
    //@{

      /** Init function which will be called
        * to initialize the transaction manager. */
      bool init();

      /** Shutdown function which will be called
        * to shutdown the transaction manager. */
      bool shutdown();

	bool startup();

	bool install();

	bool uninstall();

      /// Request an abort to perform the next shut down immediately.
      virtual void requestAbort();

      /// Returns true if self is valid, false otherwise.
      virtual bool isManagerValid() const;

      /// Returns the status of self.
      virtual const BAS::Status managerStatus() const;

      /** Start a transaction.
        * @return The transaction id or a null pointer in case of failure. */
      virtual const TransId* beginTransaction();

      /** Terminate a transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> transaction was successfully terminated,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool endTransaction(const TransId& id);

      /** Attach a module to the transaction manager.
        * @param moduleName The name of the module.
        * @param modulePtr The pointer to the module instance.
        * @return <tt>true</tt> module was successfully attached,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool attachModule(const BAS::String& moduleName,
                                ModuleIf* modulePtr);

      /** Demand a rollback for the given transaction id.
        * @param id The transaction id.
        * @param moduleName The module demanding the rollback.
        * @param reason The rollback reason.
        * @return <tt>true</tt> rollback was successfully demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool demandRollback(const TransId& id,
                                  const BAS::String& moduleName=DEFAULT_VAL,
                                  const BAS::String& reason=DEFAULT_VAL);

      /** Returns the rollback reason for the given transaction id.
        * @param id The transaction id.
        * @return The rollback reason string. */
      virtual const BAS::String& rollbackReason(const TransId& id) const;

      /** Check if a rollback was demanded for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> rollback was demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollbackDemanded(const TransId& id) const;

      /** Demand a cancel for the given transaction id.
        * @param id The transaction id.
        * @param moduleName The module demanding the rollback.
        * @param reason The cancel reason.
        * @return <tt>true</tt> cancel was successfully demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool demandCancel(const TransId& id,
                                const BAS::String& moduleName=DEFAULT_VAL,
                                const BAS::String& reason=DEFAULT_VAL);

      /** Check if a cancel was demanded for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> cancel was demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancelDemanded(const TransId& id) const;

      /** Returns the start timestamp for the given transaction id.
        * @param id The transaction id.
        * @return The start timestamp. */
      virtual const BAS::DateTime& startTimestamp(const TransId& id) const;

      /** Returns a list of transaction items for the given transaction id.
        * @param id The transaction id.
        * @return The list of transaction items. */
      virtual const TransItemList&
        transItemList(const TransId& id) const;

      /** Add a stream name for the given transaction id.
        * @param id The transaction id.
        * @param streamName The stream name.
        * @return <tt>true</tt> stream name was successfully added,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool addStreamName(const TransId& id,
                                 const BAS::String& streamName);

      /** Set stream name extension for given transaction id and stream name.
        * @param id The transaction id.
        * @param name The stream name.
        * @param extension The stream name extension.
        * @return <tt>true</tt> extension was successfully added,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool streamExtension(const TransId& id,
                                   const BAS::String& name,
                                   const BAS::String& extension);

      /** Set transaction item type for given transaction id and stream name.
        * @param id The transaction id.
        * @param name The stream name.
        * @param type The transaction item type.
        * @return <tt>true</tt> type was set,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool transItemType(const TransId& id,
                                 const BAS::String& name,
                                 TransItem::ItemTypeT type);

      /** Demand a cancel for ALL transactions
        * @return <tt>true</tt> cancel was successfully demanded,<br>
        *         <tt>false</tt> otherwise. */
      bool demandCancelAll();

  private:

    // The following private attributes and functions are used internally.

      BAS::RegisteredObject* pipelineLogM;

      TransIdController* transIdCtrlM;

      TransMap transMapM;

      RWMutexLock transMapLockerM;

      ModuleMap moduleMapM;

      RWMutexLock moduleMapLockerM;

      bool redoEnabledM;

      bool singleTransactionM;

      bool beginTransIsActiveM;

      bool transIsActiveM;

      size_t transToCancelM;

      RWMutexLock isActiveLockerM;

      bool writeToLogEnabledM;

    // Class members.

      TAM_EXPORT static const BAS::String regRedoEnabledCM;

      TAM_EXPORT static const BAS::String regSingleTransactionCM;

      TAM_EXPORT static const BAS::String regWriteToLogCM;

      TAM_EXPORT static const BAS::String regBinLogFileNameCM;

      TAM_EXPORT static const BAS::String regTransIdCtrlCM;

      TAM_EXPORT static const TransItemList emptyItemListCM;

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      Manager(Manager& right);

      const Manager& operator=(Manager& right);

    // Read the configuration values out of the registry.

      virtual bool readRegistry();

    // Prepare commit the transaction for the given transaction.

      bool prepareCommitTransaction(const TransId& id,
                                    Transaction* ta,
                                    bool& rollback);

    // Commit the transaction for the given transaction id.

      bool commitTransaction(const TransId& id);

    // Rollback the transaction for the given transaction id,

      bool rollbackTransaction(const TransId& id);

    // Cancel the transaction for the given transaction id.

      bool cancelTransaction(const TransId& id);

    // Find a transaction map entry.

      Transaction* findTransMapEntry(const TransId& id);

    // Remove a transaction map entry.

      bool removeTransMapEntry(const TransId& id);

    // Save the internal representation of the transaction map to a file.

      bool binarySaveTransMap();

    // Write a message to the pipeline log.

      void writeToPipelineLog(const BAS::Status& msg) const;

};

//------------------------------------------------------------------------------
// Returns true if self is valid, false otherwise
//------------------------------------------------------------------------------

// virtual
inline bool
Manager::isManagerValid() const
{
  return isValid();
}

//------------------------------------------------------------------------------
// Returns the status of self
//------------------------------------------------------------------------------

// virtual
inline const BAS::Status 
Manager::managerStatus() const
{
  const BAS::Status& tempStatusRef = status();
  return tempStatusRef;
}
}

#endif // MANAGER_HPP

