#ifndef TAM_TRANSACTION_HPP
#define TAM_TRANSACTION_HPP
//
// @(#)%Portal Version: Transaction.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:46:29 %
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
//   Transaction class implementation.
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
// Revision 1.7  2005/03/21 10:54:37  mliu
// PRSF00156818  Added new getter and setter functions to support rollback reason.
//
// Revision 1.6  2001/08/10 08:15:20  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.5  2001/07/04 13:37:24  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.4  2001/05/11 16:21:32  bt
// Method cancelDemanded() added.
//
// Revision 1.3  2001/05/08 09:17:54  bt
// Classes TAM_TransStatus and TAM_TransType removed. Class TAM_TransItem added.
//
// Revision 1.2  2001/04/12 11:06:13  bt
// Stream name extensions added.
//
// Revision 1.1  2001/04/05 13:08:51  bt
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

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   TAM_TRANSITEM_HPP
  #include "TAM/TransItem.hpp"
#endif
namespace TAM
{
/** This class represents a transaction.

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
class Transaction D_THREADINFO
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs an invalid transaction object.
      Transaction();

      /** Constructor with initialization.
        * @param id The transaction id. */
      Transaction(const TransId& id);

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~Transaction();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Returns the transaction id.
      const TransId& transactionId() const;

      /// Set the transaction id.
      void transactionId(const TransId& value);

      /// Returns true if a rollback was demanded.
      const bool rollbackDemanded() const;

      /// Set rollback demanded.
      void rollbackDemanded(bool value);

      /// Returns true if a cancel was demanded.
      const bool cancelDemanded() const;

      /// Set cancel demanded.
      void cancelDemanded(bool value);

      /// Returns true if a redo cancel was demanded.
      const bool redoCancelDemanded() const;

      /// Set redo cancel demanded.
      void redoCancelDemanded(bool value);

      /// Returns true if a commit was successfully prepared.
      const bool commitPrepared() const;

      /// Set commit prepared.
      void commitPrepared(bool value);

      /// Returns the start timestamp.
      const BAS::DateTime& startTimestamp() const;

      /// Set the rollback reason.
      void setRollbackReason(const BAS::String& reason);

      /// Get the rollback reason.
      const BAS::String& getRollbackReason() const;

      /// Returns the list of transaction items.
      TransItemList& transItemList();

      /// Returns the list of transaction items.
      const TransItemList& transItemList() const;

      /// Add a stream name.
      void addStreamName(const BAS::String& streamName);

      /** Set the stream name extension for the given stream name.
        * @param name The stream name.
        * @param extension The stream name extension.
        * @return <tt>true</tt> extension was successfully set,<br>
        *         <tt>false</tt> otherwise. */
      bool streamExtension(const BAS::String& name,
                           const BAS::String& extension);

      /** Set the transaction item type for the given stream name.
        * @param name The stream name.
        * @param type The transaction item type.
        * @return <tt>true</tt> type was successfully set,<br>
        *         <tt>false</tt> otherwise. */
      bool itemType(const BAS::String& name,
                    TransItem::ItemTypeT type);

      /** Restore the internal representation of self from memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      bool binaryRestore(char*& ptr);

      /** Save the internal representation of self to memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      void binarySave(char*& ptr) const;

      /// Returns the number of bytes necessary to store self.
      u_int64 binaryStoreSize() const;

    //@}

    /**@name Related Global Operators */
    //@{

      /** Operator equal-to (==).
        * @param t1 The first transaction to be compared.
        * @param t2 The second transaction to be compared.
        * @return <tt>true</tt> if <B>t1</B> is equal to <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator==(const Transaction& t1, const Transaction& t2);

      /** Operator not-equal-to (!=).
        * @param t1 The first transaction to be compared.
        * @param t2 The second transaction to be compared.
        * @return <tt>true</tt> if <B>t1</B> is not equal to <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator!=(const Transaction& t1, const Transaction& t2);

      /** Operator less-than (<).
        * @param t1 The first transaction to be compared.
        * @param t2 The second transaction to be compared.
        * @return <tt>true</tt> if <B>t1</B> is less than <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<(const Transaction& t1, const Transaction& t2);

      /** Operator less-than-or-equal (<=).
        * @param t1 The first transaction to be compared.
        * @param t2 The second transaction to be compared.
        * @return <tt>true</tt> if <B>t1</B> is less than or equal <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<=(const Transaction& t1, const Transaction& t2);

      /** Operator greater-than (>).
        * @param t1 The first transaction to be compared.
        * @param t2 The second transaction to be compared.
        * @return <tt>true</tt> if <B>t1</B> is greater than <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>(const Transaction& t1, const Transaction& t2);

      /** Operator greater-than-or-equal (>=).
        * @param t1 The first transaction to be compared.
        * @param t2 The second transaction to be compared.
        * @return <tt>true</tt> if <B>t1</B> is greater than or equal <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>=(const Transaction& t1, const Transaction& t2);

      /** Output operator.
        * @param os The output stream.
        * @param t The transaction to be written to the stream. */
      friend std::ostream& operator<<(std::ostream& os, const Transaction& t);

    //@}

  private:

    // The following private attributes and functions are used internally.

      TransId transactionIdM;

      bool rollbackDemandedM;

      bool cancelDemandedM;

      bool redoCancelDemandedM;

      bool commitPreparedM;

      BAS::DateTime startTimestampM;

      BAS::String rollbackReasonM;

      TransItemList transItemListM;

    // Class members.

      TAM_EXPORT static const u_int64 beginMarkerV1CM;

      TAM_EXPORT static const u_int64 beginMarkerV2CM;

      TAM_EXPORT static const u_int64 endMarkerCM;

};

//------------------------------------------------------------------------------
// Returns the transaction id
//------------------------------------------------------------------------------

inline const TransId&
Transaction::transactionId() const
{
  return transactionIdM;
}

//------------------------------------------------------------------------------
// Set the transaction id
//------------------------------------------------------------------------------

inline void
Transaction::transactionId(const TransId& value)
{
  transactionIdM = value;
}

//------------------------------------------------------------------------------
// Returns true if a rollback was demanded
//------------------------------------------------------------------------------

inline const bool
Transaction::rollbackDemanded() const
{
  return rollbackDemandedM;
}

//------------------------------------------------------------------------------
// Set rollback demanded
//------------------------------------------------------------------------------

inline void
Transaction::rollbackDemanded(bool value)
{
  rollbackDemandedM = value;
}

//------------------------------------------------------------------------------
// Returns true if a cancel was demanded
//------------------------------------------------------------------------------

inline const bool
Transaction::cancelDemanded() const
{
  return cancelDemandedM;
}

//------------------------------------------------------------------------------
// Set cancel demanded
//------------------------------------------------------------------------------

inline void
Transaction::cancelDemanded(bool value)
{
  cancelDemandedM = value;
}

//------------------------------------------------------------------------------
// Returns true if a redo cancel was demanded
//------------------------------------------------------------------------------

inline const bool
Transaction::redoCancelDemanded() const
{
  return redoCancelDemandedM;
}

//------------------------------------------------------------------------------
// Set redo cancel demanded
//------------------------------------------------------------------------------

inline void
Transaction::redoCancelDemanded(bool value)
{
  redoCancelDemandedM = value;
}

//------------------------------------------------------------------------------
// Returns true if a commit was successfully prepared
//------------------------------------------------------------------------------

inline const bool
Transaction::commitPrepared() const
{
  return commitPreparedM;
}

//------------------------------------------------------------------------------
// Set commit prepared
//------------------------------------------------------------------------------

inline void
Transaction::commitPrepared(bool value)
{
  commitPreparedM = value;
}

//------------------------------------------------------------------------------
// Returns the start timestamp
//------------------------------------------------------------------------------

inline const BAS::DateTime&
Transaction::startTimestamp() const
{
  return startTimestampM;
}

//------------------------------------------------------------------------------
// Set the rollback reason
//------------------------------------------------------------------------------

inline void
Transaction::setRollbackReason(const BAS::String& reason)
{
  rollbackReasonM = reason;
}

//------------------------------------------------------------------------------
// Get the rollback reason
//------------------------------------------------------------------------------

inline const BAS::String&
Transaction::getRollbackReason() const
{
  return rollbackReasonM;
}

//------------------------------------------------------------------------------
// Returns the list of transaction items
//------------------------------------------------------------------------------

inline TransItemList&
Transaction::transItemList()
{
  return transItemListM;
}

//------------------------------------------------------------------------------
// Returns the list of transaction items
//------------------------------------------------------------------------------

inline const TransItemList&
Transaction::transItemList() const
{
  return transItemListM;
}

//------------------------------------------------------------------------------
// Add a stream name
//------------------------------------------------------------------------------

inline void
Transaction::addStreamName(const BAS::String& streamName)
{
  D_ENTER("TAM::Transaction::addStreamName(const BAS::String&)");
  D_ARG(streamName);

  transItemListM.append(TransItem(streamName));
}

//------------------------------------------------------------------------------
// Output operator
//------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& os, const Transaction& t);

//------------------------------------------------------------------------------
// Operator equal-to (==)
//------------------------------------------------------------------------------

inline bool
operator==(const Transaction& t1, const Transaction& t2)
{
  return (t1.transactionIdM == t2.transactionIdM);
}

//------------------------------------------------------------------------------
// Operator not-equal-to (!=)
//------------------------------------------------------------------------------

inline bool
operator!=(const Transaction& t1, const Transaction& t2)
{
  return (t1.transactionIdM != t2.transactionIdM);
}

//------------------------------------------------------------------------------
// Operator less-than (<)
//------------------------------------------------------------------------------

inline bool
operator<(const Transaction& t1, const Transaction& t2)
{
  return (t1.transactionIdM < t2.transactionIdM);
}

//------------------------------------------------------------------------------
// Operator less-than-or-equal (<=)
//------------------------------------------------------------------------------

inline bool
operator<=(const Transaction& t1, const Transaction& t2)
{
  return (t1.transactionIdM <= t2.transactionIdM);
}

//------------------------------------------------------------------------------
// Operator greater-than (>)
//------------------------------------------------------------------------------

inline bool
operator>(const Transaction& t1, const Transaction& t2)
{
  return (t1.transactionIdM > t2.transactionIdM);
}

//------------------------------------------------------------------------------
// Operator greater-than-or-equal (>=)
//------------------------------------------------------------------------------

inline bool
operator>=(const Transaction& t1, const Transaction& t2)
{
  return (t1.transactionIdM >= t2.transactionIdM);
}
}
#endif // TRANSACTION_HPP

