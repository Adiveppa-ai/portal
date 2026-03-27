#ifndef TAM_MANAGERIF_HPP
#define TAM_MANAGERIF_HPP
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: TAM
//
//------------------------------------------------------------------------------
// Module Description:
//   Transaction manager interface.
//------------------------------------------------------------------------------
// Responsible: bt
//------------------------------------------------------------------------------
// $Log: TAM_ManagerIf.hpp,v $
// Revision 1.6  2001/08/10 08:15:20  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.5  2001/05/08 09:17:54  bt
// Classes TAM_TransStatus and TAM_TransType removed. Class TAM_TransItem added.
//
// Revision 1.4  2001/04/19 15:45:57  bt
// Return type of method beginTransaction() changed.
//
// Revision 1.3  2001/04/12 11:06:13  bt
// Stream name extensions added.
//
// Revision 1.2  2001/04/05 13:15:06  bt
// Second beginTransaction() method added.
//
// Revision 1.1  2001/03/23 11:16:06  bt
// Initial version.
//
//==============================================================================

#ifndef   TAM_MANAGERRESTRICTEDIF_HPP
  #include "TAM/ManagerRestrictedIf.hpp"
#endif

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------

namespace BAS
{
	class String;

}

namespace TAM
{
class TransId;

/** Interface to the transaction manager.

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
class ManagerIf : public ManagerRestrictedIf // This is an abstract interface class and will therefore not get the threadinfo macro
{
  public:

    /**@name Public Constructors */
    //@{

      /// Default constructor.
      ManagerIf() { };

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~ManagerIf() { };

    //@}

    /**@name Public Member Functions */
    //@{

      /** Start a transaction.
        * @return The transaction id or a null pointer in case of failure. */
      virtual const TransId* beginTransaction() = 0;

      /** Terminate a transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> transaction was successfully terminated,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool endTransaction(const TransId& id) = 0;

      /** Add a stream name for the given transaction id.
        * @param id The transaction id.
        * @param streamName The stream name.
        * @return <tt>true</tt> stream name was successfully added,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool addStreamName(const TransId& id,
                                 const BAS::String& streamName) = 0;

      /** Set stream name extension for given transaction id and stream name.
        * @param id The transaction id.
        * @param name The stream name.
        * @param extension The stream name extension.
        * @return <tt>true</tt> extension was successfully set,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool streamExtension(const TransId& id,
                                   const BAS::String& name,
                                   const BAS::String& extension) = 0;

    //@}

  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      ManagerIf(ManagerIf& right);

      const ManagerIf& operator=(ManagerIf& right);

};
}
#endif // MANAGERIF_HPP

