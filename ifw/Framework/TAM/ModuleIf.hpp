#ifndef TAM_MODULEIF_HPP
#define TAM_MODULEIF_HPP
//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: TAM
//
//------------------------------------------------------------------------------
// Module Description:
//   Transaction module interface.
//
//------------------------------------------------------------------------------
// Responsible: bt
//------------------------------------------------------------------------------
// $Log: TAM_ModuleIf.hpp,v $
// Revision 1.4  2001/08/10 08:15:20  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.3  2001/06/15 07:42:36  bt
// Method activeState() added.
//
// Revision 1.2  2001/05/08 09:17:54  bt
// Classes TAM_TransStatus and TAM_TransType removed. Class TAM_TransItem added.
//
// Revision 1.1  2001/03/23 13:35:42  bt
// Initial version.
//
//==============================================================================

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
namespace TAM
{
class TransId;

/** Interface to a module that can be attached to the transaction manager.

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
class ModuleIf // This is an abstract interface class and will therefore not get the threadinfo macro
{
  public:

    /**@name Public Constructors */
    //@{

      /// Default constructor.
      ModuleIf() { };

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~ModuleIf() { };

    //@}

    /**@name Public Member Functions */
    //@{

      /** Returns the active state of the module.
        * @return <tt>true</tt> module is active,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool activeState() = 0;

      /** Prepare to commit for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool prepareCommit(const TransId& id) = 0;

      /** Commit transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool commit(const TransId& id) = 0;

      /** Cancel transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancel(const TransId& id) = 0;

      /** Rollback transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollback(const TransId& id) = 0;

  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      ModuleIf(ModuleIf& right);

      const ModuleIf& operator=(ModuleIf& right);

};
}
#endif // MODULEIF_HPP

