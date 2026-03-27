#ifndef IXT_INTEGRATE_HPP
#define IXT_INTEGRATE_HPP
//
// @(#)%Portal Version: Integrate.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:50:22 %
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
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   The iScript extension to access the integRate system.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: Integrate.hpp,v $
// $Revision: 1.14 $
// $Author: sd $
// $Date: 2001/09/15 18:56:43 $
// $Locker:  $
//------------------------------------------------------------------------------
//
// Revision 1.20  2005/03/21 10:54:37  mliu
// PRSF00156818:  Add rollbackReason support. 
//
// Revision 1.19  2004/06/07 ammon
// PRSF00114891:  Add functions for mapping stream names to stream numbers.
//
// Revision 1.18  2003/11/19 ammon
// PRSF00068378:  Add functions for EDR to XML serialization
//
// Revision 1.17  2003/07/15 18:26:43  ammon
// - PRSF00050429: Add demandRollback and demandCancel support.
//
// Revision 1.16  2003/05/05 12:31:14  ammon
// - Change getDuplicateEdrs() to getInternalEdrs() so deletes can be handled
// correctly
//
// 2002/0625
//   iRules iterator does not work for non pattern machting comparisons
//
// Revision 1.14  2001/09/15 18:56:43  sd
// - PETS 37618 Warnings removed
//
// Revision 1.13  2001/08/29 23:47:16  sd
// - PETS #38204 - iScript compile errors have loglevel NORMAL
//
// Revision 1.12  2001/06/28 11:33:00  sd
// - Constants for normalizing numbers added
// - BAS::NormNumber removed
//
// Revision 1.11  2001/06/27 12:31:14  sd
// - New iScript function tamTransId()
//
// Revision 1.10  2001/06/14 09:58:35  sd
// - iScript now supports transactions
//
// Revision 1.9  2001/05/03 16:08:14  bt
// - Format renamed to Pipeline.
//
// Revision 1.8  2001/04/26 09:30:30  sd
// - Integrate extension is now initialized correctly by the input parser
//
// Revision 1.7  2001/04/26 08:44:48  sd
// - initEdrContainer() function changed to support NULL pointer
//
// Revision 1.6  2001/04/23 15:10:49  sd
// - IXT adjusted to EDR::BlockIndex.
//
// Revision 1.5  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.6  2001/04/10 13:47:23  sd
// - New interface to the iScript generic input extension.
//
// Revision 1.5  2001/04/06 08:36:35  sd
// - Statements now return int instead of bool
// - Integrate extension now can remove EDRs
//
// Revision 1.4  2001/04/03 07:30:59  sd
// - Initial revision
//
// Revision 1.3  2001/03/22 15:21:35  sd
// - Adjusted to new EDR container
//
// Revision 1.2  2001/03/13 10:58:28  sd
// - First update for the new EDR container.
//
// Revision 1.1  2000/12/04 08:21:07  sd
// - Module moved from IXT to iScript.
//
// Revision 1.3  2000/10/06 10:20:47  sd
// - Static variable map now will be freed
//
// Revision 1.2  2000/10/04 14:30:28  sd
// - Changes for IBM AIX
//
// Revision 1.1  2000/09/27 11:33:21  sd
// - IXT is a framework module again
//
// Revision 1.1  2000/09/26 13:33:35  sd
// - Initial revision for separate integRate iScript extension.
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

#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   TAM_TRANSITEM_HPP
  #include "TAM/TransItem.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
#ifndef   SCR_EXTENSION_HPP
  #include "SCR/Extension.hpp"
#endif

namespace EDR
{
class Factory;
}
namespace TAM
{
class ManagerRestrictedIf;
}
namespace IXT
{

/** <b><tt>Integrate</tt></b> is the iScript extension to access the 
 *  integRate system.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Integrate.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.14 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 18:56:43 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class Integrate : public SCR::Extension,
                      public BAS::RegisteredObject
{
  public:
    IXT_EXPORT static const BAS::String extensionNameCM;

    /**@name Integrate constructors and destructor */
    //@{

    /** Constructor
     *  @param name The registry name of the extension
     */
    Integrate( const BAS::String& name );

    /** Destructor
     */
    virtual ~Integrate();

    //@}


    /**@name Integrate public methods */
    //@{

    /** Get the name of the extension
     *  @return Reference to the string with the name of the extension
     */
    virtual const BAS::String& extensionName() const;

    /** Get a variable from the "integrate" extension
     *  @param name The name of the variable
     *  @return Pointer to the variable on success, 0 otherwise
     */
    virtual SCR::Variable* variable( const BAS::String& name );

    //@}

    /**@name Integrate special methods */
    //@{

    /** Write a message to the pipeline log. This function is used by the 
     *  logPipeline() function of the script language.
     *  @param string String to write to the pipeline log
     */
    void logPipeline( const BAS::String&    string,
                      BAS::Status::Severity severity ) const;

    /** Get the stream number for a stream name
     *  @param streamName Stream name to resolve
     *  @return Stream number >= 0 on success, < 0 otherwise
     */
    int64 streamNameToNumber( const BAS::String& streamName );

    /** Get the stream name for a stream number
     *  @param streamNumber Stream number to resolve
     *  @return Stream name on success, BAS::NULL_STRING otherwise
     */
    const BAS::String& streamNumberToName( int64 streamNumber );

    /** Get the current edr
     *  @return Pointer to the current edr
     */
    EDR::Container* currentEdr() const;

    /** Remove the current EDR container from the extension
     *  @return Pointer to the removed EDR
     */
    EDR::Container* removeCurrentEdr();

    /** Set the index for the current edr container
     *  @param index The index of the edr container
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool currentEdr( int64 index );

    /** Get the vector with all edr containers
     *  @return Reference to the vector with all EDR containers
     */
    RWTPtrOrderedVector<EDR::Container>& edrVector();

    /** Get the number of EDR containers in the extension
     *  @return The number of EDR containers in the extension's vector
     */
    size_t numEdrs() const;

    /** Get the n-th EDR container from the extension
     *  @param n The index of the EDR container
     *  @return Pointer to the EDR container
     */
    EDR::Container* edr( size_t n );

    /** Do the first initialization of edr container before executing a script
     *  @param edr The edr container to use
     */
    void initEdrContainer( EDR::Container* edr );

    /** Get the internal edr containers
     *  @param edrVector Vector for returning the result
     */
    void getInternalEdrs( RWTPtrOrderedVector<EDR::Container>& edrVector ) 
      const;

    /** Get an index for an edr datablock
     *  @param alias The alias name for the datablock
     *  @return Index >= 0 on success, < 0 otherwise
     */
    EDR::BlockIndex getBlockIndex( const BAS::String& alias );

    /** Get an index for the edr container access
     *  @param alias The alias name for the edr field
     *  @return Index >= 0 on success, < 0 otherwise
     */
    EDR::Index getIndex( const BAS::String& alias );

    /** Duplicate the current edr container
     *  @return The index of the duplicated edr record on success, -1 otherwise
     */
    int64 duplicateEdr();

    /** Get the pipeline name for this interpreter
     *  @return Reference to the pipeline name string
     */
    const BAS::String& pipelineName() const;

    /** Get the current message
     *  @return Pointer to the current message
     */
    const BAS::Message* currentMsg() const;

    /** Set the current message
     *  @param msg The current message to use
     */
    void currentMsg( const BAS::Message* msg );

    /** Send an event to the event handler
     *  @param eventName The name of the event to send
     *  @param eventArgs The arguments for the event
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool sendEvent( const BAS::String&     eventName,
                    const BAS::StringList& eventArgs );

    /** Set the origin name used for events
     *  @param originName The origin name for all events send by the interpreter
     */
    void eventOriginName( const BAS::String& originName );

    /** Get a registry entry
     *  @param name The name of the registry entry
     *  @return Pointer on success, <b>0</b> otherwise
     */
    const BAS::RegistryEntry* registryEntry( const BAS::String& name ) const;

    /** Stop the pipeline
     */
    void stopPipeline() const;

    /** Check if the interpreter is in iRules mode or not
     *  @return true if interpreter is in iRules mode, false otherwise
     */
    bool iRulesMode() const;

    /** Set the iRules mode flag
     *  @param flag The flag if interpreter is in iRules mode or not
     */
    void iRulesMode( bool flag );

    /** Add an iRules iteration index
     *  @param index Iteration index
     */
    void iRulesAddIterationIndex( const EDR::BlockIndex& index );

    /** Return the iRules iteration indices
     *  @return Reference to the iteration index vector
     */
    const RWTValOrderedVector<EDR::BlockIndex>& iRulesIterationIndices() const;

    /** Get the current vector used by iRules
     *  @return Reference to the current vector
     */
    EDR::CurrentVector& iRulesCurrentVector();

    /** Get the pointer to the transaction manager
     *  @return Pointer to transaction manager if existent, 0 otherwise
     */
    TAM::ManagerRestrictedIf* transactionManager() const;

    /** Initialize members for the current transaction
     *  @param transId The current transaction id
     *  @param transItemList The current trans item list
     */
    void curTransaction( const TAM::TransId*       transId,
                         const TAM::TransItemList* transItemList );

    /** Get the pointer to the current transaction id
     *  @return Poitner to the current transaction id, 0 if not present
     */
    const TAM::TransId* curTransId() const;

    /** Get the pointer to the current trans item list
     *  @return Poitner to the current trans item list, 0 if not present
     */
    const TAM::TransItemList* curTransItemList() const;

    /** Set the current rollback transaction
     *  @param edr The BEGIN_TRANSACTION edr
     */
    void setRollbackTransId( EDR::Container* edr );

    /** Call demandRollback in the Transaction Manager
     */
    bool demandRollback( const BAS::String& reason );

    /** Call demandCancel in the Transaction Manager
     */
    bool demandCancel();

    /** Call rollbackReason in the Transaction Manager
     *  @return The rollback reason string if successful,
     *          BAS::NULL_STRING otherwise.
     */
    const BAS::String& rollbackReason();

    /** Get the XML representation for the current edr
     *  @param multiline  Produce multi-line "pretty" format XML.
     *                    Multiline must be false to use XML with input grammar
     *  @return XML form of the current edr if successful,
     *          BAS::NULL_STRING otherwise.
     */
    BAS::String getEdrXml( bool multiline = false );

    //@}

  private:
    // Get all valid stream names and numbers
    void collectAllStreamNames();

    // instance members
    EDR::Factory*                           edrFactoryM;
    size_t                                 currentEdrIndexM;
    RWTPtrOrderedVector<EDR::Container>     edrVectorM;
    BAS::String                             pipelineNameM;
    const BAS::Message*                     currentMsgM;
    BAS::String                             eventOriginNameM;
    BAS::String                             eventHandlerNameM;
    bool                                   iRulesModeM;
    EDR::CurrentVector                      iRulesCurrentVectorM;
    RWTValOrderedVector<EDR::BlockIndex>    iRulesIterationIndicesM;
    TAM::ManagerRestrictedIf*               transactionManagerM;
    const TAM::TransId*                     curTransIdM;
    const TAM::TransItemList*               curTransItemListM;
    SCR::VariableMap                        localConstantsM;
    TAM::TransId                            rollbackTransIdM;
    RWTValOrderedVector<BAS::String>        streamNameM;

    // class members 
    IXT_EXPORT static SCR::VariableMap  globalConstantsCM;
    IXT_EXPORT static const BAS::String descriptionCM;
    IXT_EXPORT static const BAS::String outputModuleCM;
    IXT_EXPORT static const BAS::String reqStreamNameCM;
    IXT_EXPORT static const BAS::String regPipelinesCM;
    IXT_EXPORT static const BAS::String regManagerCM;
    IXT_EXPORT static RWMutexLock      mutexCM;
    IXT_EXPORT static int              instancesCM;
};

//==============================================================================
// Get the current edr
//==============================================================================
inline EDR::Container*
Integrate::currentEdr() const
{
  if ( edrVectorM.entries() > currentEdrIndexM )
  {
    return edrVectorM( currentEdrIndexM );
  }
  else
  {
    return 0;
  }
}

//==============================================================================
// Init the edr container before executing a script
//==============================================================================
inline void
Integrate::initEdrContainer( EDR::Container* edr )
{
  edrVectorM.clear();
  if ( edr != 0 )
  {
    edrVectorM.append( edr );
  }
  currentEdrIndexM = 0;
}

//==============================================================================
// Get the internal edrs
//==============================================================================
inline void 
Integrate::getInternalEdrs(
  RWTPtrOrderedVector<EDR::Container>& edrVector ) const
{
  //----------------------------------------------------------------------------
  // Get all internal edrs
  //----------------------------------------------------------------------------
  int numEdrs = edrVectorM.entries();
  for ( int i = 0; i < numEdrs; i++ )
  {
    edrVector.append( edrVectorM(i) ); 
  }
}

//==============================================================================
// Get the pipeline name
//==============================================================================
inline const BAS::String&
Integrate::pipelineName() const
{
  return pipelineNameM;
}

//==============================================================================
// Get the current message
//==============================================================================
inline const BAS::Message*
Integrate::currentMsg() const
{
  return currentMsgM;
}

//==============================================================================
// Set the current message
//==============================================================================
inline void
Integrate::currentMsg( const BAS::Message* msg )
{
  currentMsgM = msg;
}

//==============================================================================
// Set the origin name used by send event
//==============================================================================
inline void 
Integrate::eventOriginName( const BAS::String& originName )
{
  eventOriginNameM = originName;
}

//==============================================================================
// Get the number of EDR containers in the extension's array
//==============================================================================
inline size_t 
Integrate::numEdrs() const
{
  return edrVectorM.entries();
}

//==============================================================================
// Get the n-th EDR container for the extension's array
//==============================================================================
inline EDR::Container*
Integrate::edr( size_t n )
{
  RWPRECONDITION( n < edrVectorM.entries() );
  return edrVectorM(n);
}

//==============================================================================
// Get the vector with all EDR containers
//==============================================================================
inline RWTPtrOrderedVector<EDR::Container>&
Integrate::edrVector()
{
  return edrVectorM;
}

//==============================================================================
// Check if the interpreter is in iRules mode or not
//==============================================================================
inline bool
Integrate::iRulesMode() const
{
  return iRulesModeM;
}

//==============================================================================
// Set the iRules mode flag
//==============================================================================
inline void
Integrate::iRulesMode( bool flag )
{
  iRulesModeM = flag;
}

//==============================================================================
// Get the iRules current vector
//==============================================================================
inline EDR::CurrentVector&
Integrate::iRulesCurrentVector()
{
  RWPRECONDITION( iRulesModeM == true );
  return iRulesCurrentVectorM;
}

//==============================================================================
// Get the iRules iteration indices
//==============================================================================
inline const RWTValOrderedVector<EDR::BlockIndex>&
Integrate::iRulesIterationIndices() const
{
  RWPRECONDITION( iRulesModeM == true );
  return iRulesIterationIndicesM;
}

//==============================================================================
// Get the pointer to the transaction manager
//==============================================================================
inline TAM::ManagerRestrictedIf*
Integrate::transactionManager() const
{
  return transactionManagerM;
}

//==============================================================================
// Get the pointer to the current transaction id
//==============================================================================
inline const TAM::TransId*
Integrate::curTransId() const
{
  return curTransIdM;
}

//==============================================================================
// Get the pointer to the current trans item list
//==============================================================================
inline  const TAM::TransItemList*
Integrate::curTransItemList() const
{
  return curTransItemListM;
}

//==============================================================================
// Set the current TAM transaction
//==============================================================================
inline void
Integrate::curTransaction( const TAM::TransId*       transId,
                               const TAM::TransItemList* transItemList )
{
  curTransIdM       = transId;
  curTransItemListM = transItemList;
}

}
#endif // INTEGRATE_HPP

