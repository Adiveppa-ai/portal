#ifndef IXT_ISCRIPT_HPP
#define IXT_ISCRIPT_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Class declaration for a single executable script.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: IScript.hpp,v $
// $Revision: 1.11 $
// $Author: sd $
// $Date: 2001/06/27 12:31:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: IScript.hpp,v $
// Revision 1.13  2003/06/17 12:31:14  ammon
// - Add onEndTransaction() function.
//
// Revision 1.12  2003/05/05 12:31:14  ammon
// - Change getDuplicateEdrs() to getInternalEdrs() so deletes can be handled
// correctly
//
// Revision 1.11  2001/06/27 12:31:14  sd
// - New iScript function tamTransId()
//
// Revision 1.10  2001/06/25 07:58:43  sd
// - Mutex added for TAM functions
//
// Revision 1.9  2001/06/14 11:05:30  sd
// - Transaction support changed
//
// Revision 1.8  2001/06/14 09:58:35  sd
// - iScript now supports transactions
//
// Revision 1.7  2001/05/17 12:14:56  sd
// - License key check removed
//
// Revision 1.6  2001/04/25 10:51:54  sd
// - Databasetable INT::ISCRIPT renamed to IFW_ISCRIPT
//
// Revision 1.5  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.2  2001/04/06 08:36:35  sd
// - Statements now return int instead of bool
// - Integrate extension now can remove EDRs
//
// Revision 1.1  2000/12/04 08:21:07  sd
// - Module moved from IXT to iScript.
//
// Revision 1.3  2000/09/27 13:22:22  sd
// - Now uses new class Interpreter
//
// Revision 1.2  2000/09/27 12:15:08  sd
// - BugFix in IScript
//
// Revision 1.1  2000/09/27 11:33:21  sd
// - IXT is a framework module again
//
// Revision 1.1  2000/09/26 13:33:35  sd
// - Initial revision for separate integRate iScript extension.
//
// Revision 1.20  2000/09/12 13:56:30  sd
// - The iScript function onDetailEdr() is now only called for valid details
//   There is an additional function onInvalidEdr() for invalid ones.
//
// Revision 1.19  2000/09/08 15:04:32  sd
// - Function scriptUsable() added.
//
// Revision 1.18  2000/06/22 08:58:41  sd
// - Missing inline added.
//
// Revision 1.17  2000/06/17 11:04:29  sd
// - Comparison operators added to support the IBM xlC compiler.
//
// Revision 1.16  2000/05/09 15:08:12  sd
// - go back to v3-99-10
//
// Revision 1.14  2000/04/25 14:30:28  sd
// - Interface for edr duplication changed.
//
// Revision 1.13  2000/04/25 08:15:20  sd
// - Support for EDR container duplication added.
//
// Revision 1.12  2000/04/20 10:37:10  sd
// - new functions edrDuplicate() and edrSetCurrent() added.
// - support for edr duplication added (not yet working)
//
// Revision 1.11  2000/04/19 11:31:58  sd
// - Support for license keys and certification added.
//
// Revision 1.10  2000/04/17 13:15:00  sd
// - Support for message processing added.
//
// Revision 1.9  2000/04/06 10:27:16  sd
// - Changed the interface for adding arguments to an IScript.
//
// Revision 1.8  2000/03/31 11:09:51  sd
// - Global constant now can be passed to the interpreter.
//
// Revision 1.7  2000/03/23 12:49:13  sd
// - new function callEdrSpecificFunctions().
//
// Revision 1.6  2000/03/17 09:29:41  sd
// - Support for sending events added.
// - New function Bool sendEvent(String) added to script language.
//
// Revision 1.5  2000/03/15 08:26:57  sd
// - New files SCR::ParserFunctions.?pp added.
//
// Revision 1.4  2000/03/14 14:36:33  sd
// - Return type added to operator=().
//
// Revision 1.3  2000/03/14 14:35:37  sd
// - Return added to function execute().
//
// Revision 1.2  2000/03/08 08:20:16  sd
// - Default constructor, copy constructor and assignement operator declared
//   private.
//
// Revision 1.1  2000/03/08 07:47:50  sd
// - Initial revision.
//
//==============================================================================

#if !defined IXT_EXPORT
  #if defined(WINDOWS)
    #if !defined(IXT_INTERNAL)
      #define IXT_EXPORT __declspec(dllimport)
    #else
      #define IXT_EXPORT __declspec(dllexport)
    #endif
  #else
    #define IXT_EXPORT 
  #endif
#endif

#ifndef   __RWDB_DB_H__
  #include <rw/db/db.h>
#endif
#ifndef   RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   IXT_ISCRIPTARG_HPP
  #include "IXT/IScriptArg.hpp"
#endif
#ifndef   IXT_INTERPRETER_HPP
  #include "IXT/Interpreter.hpp"
#endif
namespace IXT
{

/**<b><tt>IScript</tt></b> is the class used to load a single script either
 * from database or from file.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: IScript.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.11 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/27 12:31:14 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class IScript D_THREADINFO
{
  public:
    /**@name IScript constructors and destructor */
    //@{

    /** Initialize the script from file. Use the isValid() method to check for
     *  success.
     *  @param parent Name of the parent registered object
     *  @param name Registry name of the object
     *  @param file Name of the script file
     *  @param args Argument list
     */
    IScript( const BAS::String&           parent,
                 const BAS::String&           name,
                 const BAS::String&           file,
                 const IScriptArgVector& args = noArgsCM );

    /** Initialize the script from database. Use the isValid() method to check
     *  for success.
     *  @param parent Name of the parent registered object
     *  @param name Registry name of the object
     *  @param connection Database connectin for initialization
     *  @param args Argument list
     */
    IScript( const BAS::String&           parent,
                 const BAS::String&           name,
                 RWDBConnection              connection,
                 const IScriptArgVector& args = noArgsCM );

    /** Destructor
     */
    virtual ~IScript();

    //@}

    /**@name IScript public methods */
    //@{

    /** Check if the object is valid
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

    /** Get the last failure
     *  @return Reference to internal failure string
     */
    const BAS::String& failure() const;

    /** Get the number of lines in script
     *  @return The number of lines in script
     */
    int64 linesCompiled() const;

    /** Execute the script on the given edr container
     *  @param edr The edr container to process
     *  @param internalEdrs Return buffer for the internal edrs
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool execute( EDR::Container* edr,
                  RWTPtrOrderedVector<EDR::Container>& internalEdrs );

    /** Call the onMessageReceived function with the message specified
     *  @param msg The received message
     */
    void processMessage( const BAS::Message* msg );

    /** Set the origin name for events send by the script
     *  @param originName The origin name for all events send by the interpreter
     */
    void eventOriginName( const BAS::String& originName );

    /** Check if the script is usable
     *  @return <b>true</b> if script is usable, <b>false</b> otherwise
     */
    bool scriptUsable() const;

    /** Prepare to commit for the given transaction id.
     *  @param transId The transaction id.
     *  @param transItemList The list with transaction items
     *  @return <tt>true</tt> operation was successful,<br>
     *          <tt>false</tt> otherwise. 
     */
    bool prepareCommit( const TAM::TransId*       transId,
                        const TAM::TransItemList* transItemList );

    /** Commit transaction for the given transaction id.
     *  @param transId The transaction id.
     *  @param transItemList The list with transaction items
     *  @return <tt>true</tt> operation was successful,<br>
     *          <tt>false</tt> otherwise. */
    bool commit( const TAM::TransId*       transId,
                 const TAM::TransItemList* transItemList );

    /** Cancel transaction for the given transaction id.
     *  @param transId The transaction id.
     *  @param transItemList The list with transaction items
     *  @return <tt>true</tt> operation was successful,<br>
     *          <tt>false</tt> otherwise. 
     */
    bool cancel( const TAM::TransId*       transId,
                 const TAM::TransItemList* transItemList );
    
    /** Rollback transaction for the given transaction id.
     *  @param transId The transaction id.
     *  @param transItemList The list with transaction items
     *  @return <tt>true</tt> operation was successful,<br>
     *          <tt>false</tt> otherwise. 
     */
    bool rollback( const TAM::TransId*       transId,
                   const TAM::TransItemList* transItemList );

    /** Check if the script needs the transaction manager
     *  @return <b>true</b> if TAM is needed, <b>false</b> otherwise
     */
    bool needsTransactionManager() const;

#ifdef __aix
    bool operator<( const IScript& rVal ) const
    {
      return( this < &rVal );
    }
    bool operator==( const IScript& rVal ) const
    {
      return( this == &rVal );
    }
#endif

    //@}

  protected:

    /** Set the objects valid state
     *  @param state New valid state
     */
    void isValid( bool state );

    /** Initialize the script from file
     *  @param file Name of the script file
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const BAS::String& file );

    /** Initialize the script from database
     *  @param connection Database connection for initialization
     *  @param script Primary key in database table IFW_ISCRIPT
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( RWDBConnection& connection, const BAS::String& script );

    /** Do the final setup after reading from file or database
     *  @param script The script source code
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool finalSetup( BAS::String& script );

    /** Call the edr specific functions
     *  @param edr The container for which to execute the function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    int callEdrSpecificFunction( EDR::Container* edr );

    /** Insert the arguments as global constants in the interpretr
     *  @param args Argument list to insert
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool insertArgsInInterpreter( const IScriptArgVector& args );

    /** Initialize members for the current transaction
     *  @param transId The current transaction id
     *  @param transItemList The current trans item list
     */
    void curTransaction( const TAM::TransId*       transId,
                         const TAM::TransItemList* transItemList );

  private:
    // Hide default, copy constructor and assignment operator
    IScript();
    IScript( const IScript& );
    const IScript& operator=( const IScript& );

    // instance members
    bool                     isValidM;
    BAS::String               failureM;
    Interpreter          interpreterM;
    RWMutexLock              mutexM;

    // special edr container fcts
    SCR::Function* fctEdrHeaderM;
    SCR::Function* fctEdrDetailM;
    SCR::Function* fctEdrInvalidDetailM;
    SCR::Function* fctEdrTrailerM;
    SCR::Function* fctEdrStartM;
    SCR::Function* fctEdrStopM;
    SCR::Function* fctEdrBeginM;
    SCR::Function* fctEdrEndM;
    SCR::Function* fctMsgReceivedM;
    SCR::Function* fctCommitM;
    SCR::Function* fctPrepareCommitM;
    SCR::Function* fctCancelM;
    SCR::Function* fctRollbackM;
    SCR::Function* fctBeginTransactionM;
    SCR::Function* fctEndTransactionM;

    // class members
    IXT_EXPORT static const IScriptArgVector noArgsCM;

    IXT_EXPORT static const BAS::String fctEdrHeaderNameCM;
    IXT_EXPORT static const BAS::String fctEdrDetailNameCM;
    IXT_EXPORT static const BAS::String fctEdrInvalidDetailNameCM;
    IXT_EXPORT static const BAS::String fctEdrTrailerNameCM;
    IXT_EXPORT static const BAS::String fctEdrStartNameCM;
    IXT_EXPORT static const BAS::String fctEdrStopNameCM;
    IXT_EXPORT static const BAS::String fctEdrBeginNameCM;
    IXT_EXPORT static const BAS::String fctEdrEndNameCM;
    IXT_EXPORT static const BAS::String fctMsgReceivedNameCM;
    IXT_EXPORT static const BAS::String fctCommitNameCM;
    IXT_EXPORT static const BAS::String fctPrepareCommitNameCM;
    IXT_EXPORT static const BAS::String fctCancelNameCM;
    IXT_EXPORT static const BAS::String fctRollbackNameCM;
    IXT_EXPORT static const BAS::String fctBeginTransactionNameCM;
    IXT_EXPORT static const BAS::String fctEndTransactionNameCM;
};

//==============================================================================
// Execute the script
//==============================================================================
inline bool
IScript::execute( EDR::Container*                      edr,
                      RWTPtrOrderedVector<EDR::Container>& internalEdrs ) 
{
  RWPRECONDITION( edr != 0 );

  RWLockGuard<RWMutexLock> mutex( mutexM );

  interpreterM.initEdrContainer( edr );
  callEdrSpecificFunction( edr );
  bool ret = interpreterM.execute();
  interpreterM.getInternalEdrs( internalEdrs );
  return ret;
}

//==============================================================================
// Set the origin name for all events send by the script
//==============================================================================
inline void 
IScript::eventOriginName( const BAS::String& originName )
{
  interpreterM.eventOriginName( originName );
}

//==============================================================================
// Check if the script needs the transaction manager
//==============================================================================
inline bool
IScript::needsTransactionManager() const
{
  return( fctCommitM != 0 || 
          fctPrepareCommitM != 0 || 
          fctCancelM != 0 ||
          fctRollbackM != 0 );
}

//==============================================================================
// Set the current TAM transaction
//==============================================================================
inline void
IScript::curTransaction( const TAM::TransId*       transId,
                             const TAM::TransItemList* transItemList )
{
  interpreterM.extension()->curTransaction( transId, transItemList );
}
}
#endif // ISCRIPT_HPP
