#ifndef TAM_MANAGERRESTRICTEDIF_HPP
#define TAM_MANAGERRESTRICTEDIF_HPP
//
// @(#)%Portal Version: ManagerRestrictedIf.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:46:37 %
//
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
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
//   Restricted transaction manager interface.
//
//------------------------------------------------------------------------------
// Responsible: bt
//------------------------------------------------------------------------------
// $Log: TAM_ManagerRestrictedIf.hpp,v $
//
// Revision 1.8  2005/03/21 10:54:37  mliu
// PRSF00156818  Added new method RollbackReason() to allow modules to ask
//               for the rollback reason.
//
// Revision 1.7  2001/08/10 08:15:20  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.6  2001/06/25 09:02:14  bt
// Method cancelDemanded() added.
//
// Revision 1.5  2001/05/08 09:17:54  bt
// Classes TAM_TransStatus and TAM_TransType removed. Class TAM_TransItem added.
//
// Revision 1.4  2001/04/25 08:00:52  bt
// Parameter type of method attachModule() changed.
//
// Revision 1.3  2001/04/19 15:27:26  bt
// Method status() renamed to transStatus().
//
// Revision 1.2  2001/04/12 11:06:13  bt
// Stream name extensions added.
//
// Revision 1.1  2001/03/22 17:30:07  bt
// Initial version.
//
//==============================================================================

#ifndef   TAM_TRANSITEM_HPP
  #include "TAM/TransItem.hpp"
#endif

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
namespace BAS
{
class String;
class Status;
class DateTime;
}
namespace TAM
{
class TransId;
class ModuleIf;
static const BAS::String DEFAULT_VAL = "UNKNOWN";
/** Restricted interface to the transaction manager.

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
class ManagerRestrictedIf // This is an abstract interface class and will therefore not get the threadinfo macro
{
  public:

    /**@name Public Constructors */
    //@{

      /// Default constructor.
      ManagerRestrictedIf() { };

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~ManagerRestrictedIf() { };

    //@}

    /**@name Public Member Functions */
    //@{

      /// Returns true if self is valid, false otherwise.
      virtual bool isManagerValid() const = 0;

      /// Returns the status of self.
      virtual const BAS::Status managerStatus() const = 0;

      /** Attach a module to the transaction manager.
        * @param moduleName The name of the module.
        * @param modulePtr The pointer to the module instance.
        * @return <tt>true</tt> module was successfully attached,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool attachModule(const BAS::String& moduleName,
                                ModuleIf* modulePtr) = 0;

      /** Demand a rollback for the given transaction id.
        * @param id The transaction id.
        * @param moduleName The module demanding the rollback.
        * @param reason The rollback reason.
        * @return <tt>true</tt> rollback was successfully demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool demandRollback(const TransId& id,
                                  const BAS::String& moduleName=DEFAULT_VAL,
                                  const BAS::String& reason=DEFAULT_VAL) = 0;

      /** Returns the rollback reason for the given transaction id.
        * @param id The transaction id.
        * @return The rollback reason string. */
      virtual const BAS::String& rollbackReason(const TransId& id) const = 0;

      /** Check if a rollback was demanded for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> rollback was demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollbackDemanded(const TransId& id) const = 0;

      /** Demand a cancel for the given transaction id.
        * @param id The transaction id.
        * @param moduleName The module demanding the rollback.
        * @param reason The cancel reason.
        * @return <tt>true</tt> cancel was successfully demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool demandCancel(const TransId& id,
                                const BAS::String& moduleName=DEFAULT_VAL,
                                const BAS::String& reason=DEFAULT_VAL) = 0;

      /** Check if a cancel was demanded for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> cancel was demanded,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancelDemanded(const TransId& id) const = 0;

      /** Returns the start timestamp for the given transaction id.
        * @param id The transaction id.
        * @return The start timestamp. */
      virtual const BAS::DateTime&
        startTimestamp(const TransId& id) const = 0;

      /** Returns a list of transaction items for the given transaction id.
        * @param id The transaction id.
        * @return The list of transaction items. */
      virtual const TransItemList&
        transItemList(const TransId& id) const = 0;

      /** Set transaction item type for given transaction id and stream name.
        * @param id The transaction id.
        * @param name The stream name.
        * @param type The transaction item type.
        * @return <tt>true</tt> type was successfully set,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool transItemType(const TransId& id,
                                 const BAS::String& name,
                                 TransItem::ItemTypeT type) = 0;

    //@}

  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      ManagerRestrictedIf(ManagerRestrictedIf& right);

      const ManagerRestrictedIf& operator=(ManagerRestrictedIf& right);

};
}
#endif // MANAGERRESTRICTEDIF_HPP

