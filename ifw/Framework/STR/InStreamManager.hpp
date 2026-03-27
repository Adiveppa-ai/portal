#ifndef STR_InStreamManager_HPP
#define STR_InStreamManager_HPP
//==============================================================================
//
//   Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//   
//   This material is the confidential property of Oracle Corporation or its
//   licensors and may be used, reproduced, stored or transmitted only in
//   accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: STR
//------------------------------------------------------------------------------
// Module Description:
//   Standard output stream interface class
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: InStreamManager.hpp,v $
// $Revision: 1.18 $
// $Author: mliebmann $
// $Date: 2001/09/03 11:24:20 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: InStreamManager.hpp,v $
// Revision 1.18  2001/09/03 11:24:20  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.17  2001/08/28 07:33:31  jkeckst
// PETS 37618 code review 08.2001
//
// Revision 1.16  2001/06/26 12:09:52  mliebmann
// IO_REJECTED delete
//
// Revision 1.15  2001/06/25 15:24:54  mliebmann
// error handling corrected
//
// Revision 1.14  2001/06/25 14:49:36  mliebmann
// IOResultT::IO_REJECTED added
//
// Revision 1.13  2001/05/14 15:02:52  mliebmann
// IOResult fixed
//
// Revision 1.12  2001/05/08 14:52:15  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.11  2001/05/03 11:39:55  mliebmann
// GenericIO: Sequencer bug fixed and little changes
//
// Revision 1.10  2001/04/26 11:47:53  mliebmann
// GenericIO: little changes
//
// Revision 1.9  2001/04/26 09:25:45  mliebmann
// GenericIO: TAM added
//
// Revision 1.8  2001/04/11 10:15:44  mliebmann
// Generic IO: little changes and documentation added
//
// Revision 1.7  2001/04/10 10:00:58  mliebmann
// Generic IO: enumeration FILE_IO added
//
// Revision 1.6  2001/04/09 14:23:52  mliebmann
// Generic IO: changes
//
// Revision 1.4  2001/04/04 08:35:23  mliebmann
// Generic IO: updated
//
// Revision 1.2  2001/03/23 15:09:11  mliebmann
// GenericIO - only backup
//
// Revision 1.1  2001/03/21 09:43:05  mliebmann
// only for backup
//
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   PLG_TRANSACTIONPLUGIN_HPP
  #include "PLG/TransactionPlugIn.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif

namespace STR
{
enum IOResultT
{
  IO_CRITICALFALSE = -2, // Demand stop of the format!!!
  IO_TIMEOUT = -1,
  IO_FALSE = 0,
  IO_TRUE = 1
};

/** <tt><b>abstract class InStreamManager</b></tt> provides an input 
    stream interface.
    Currently EXT_InFileManager is supported.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: InStreamManager.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.18 $</font></td>
    <td><font size=-1>$Date: 2001/09/03 11:24:20 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>

    <dl>
      <dt><b>Registry entries</b></dt>
      <dd>none</dd>
      <dt><b>Messages send</b></dt>
      <dd>none</dd>
      <dt><b>Messages receive</b></dt>
      <dd>none</dd>
      <dt><b>Request send</b></dt>
      <dd>none</dd>
      <dt><b>Request receive</b></dt>
      <dd>none</dd>
      <dt><b>Event send</b></dt>
      <dd>none</dd>
      <dt><b>Errors</b></dt>
      <dd>none</dd>
    </dl> 

*/
class InStreamManager : public PLG::TransactionPlugIn
{
public:

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    InStreamManager();
	
    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    InStreamManager(const BAS::String& name,
					const BAS::String& version);
	
    /** Destructor. */
    virtual ~InStreamManager();
    //@}
	
    /** Transaction-functions */
    //@{
	/** Send a begin transaction for the given transaction id.
	 * @param id The transaction id.
	 * @return <tt>true</tt> operation was successful,<br>
	 *         <tt>false</tt> otherwise. */
	virtual bool beginTransactionIO(const TAM::TransId* id) = 0;
	
	/** Prepare to commit for the given transaction id.
	 * @param id The transaction id.
	 * @return <tt>true</tt> operation was successful,<br>
	 *         <tt>false</tt> otherwise. */
	virtual bool prepareCommitIO(const TAM::TransId& id) = 0;
	
	/** Commit transaction for the given transaction id.
	 * @param id The transaction id.
	 * @return <tt>true</tt> operation was successful,<br>
	 *         <tt>false</tt> otherwise. */
	virtual bool commitIO(const TAM::TransId& id) = 0;
	
	/** Cancel transaction for the given transaction id.
	 * @param id The transaction id.
	 * @return <tt>true</tt> operation was successful,<br>
	 *         <tt>false</tt> otherwise. */
	virtual bool cancelIO(const TAM::TransId& id) = 0;
	
	/** Rollback transaction for the given transaction id.
	 * @param id The transaction id.
	 * @return <tt>true</tt> operation was successful,<br>
	 *         <tt>false</tt> otherwise. */
	virtual bool rollbackIO(const TAM::TransId& id) = 0;
    //@}
	
    /** Stream-access-functions */
    //@{
	/** Wait for a new input stream. 
	 * @return <tt>IOResultT</tt> IO result. */
	virtual IOResultT waitForData() = 0;
	
	/** Open stream. 
	 * @return <tt>IOResultT</tt> IO result. */
	virtual IOResultT open(BAS::String & streamName) = 0;
	
	/** Read line from stream.
	 * @return <tt> >=0 </tt> successfull and count of read bytes.
	 *         <tt> -1  </tt> otherwise. */
	virtual int64 read(BAS::String& str);
	
	/** Read block from stream.
	 * @return <tt> >=0 </tt> successfull and count of read bytes.
	 *         <tt> -1  </tt> otherwise. */
	virtual int64 read(void* p, size_t size);
	
	/** Close stream.
	 * @return <tt>IOResultT</tt> IO result. */
	virtual IOResultT close() = 0;

	/** Get the context.
	 * @return the context. */
	virtual void* getContext();
    //@}
	
    /** Module control. */
    //@{
	/** IsActive. Show if the module is active or not.
	 * @return <tt>true</tt> operation was successful,<br>
	 *         <tt>false</tt> otherwise. */
	virtual bool isActive();
	
	/** RequestAbort. Immediate exit of the process. */
	void requestAbort();
	
	/** Shutdown. Show the stream that the system shutdown. */
	bool shutdown();
	
	/** Stop. Process indication that we're about to stop
	 * @todo Investigate whether we can get rid of this and just use shutdown
	 */
	virtual bool stop();
    //@}   
    
protected:
	
    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    InStreamManager(InStreamManager& right);
    const InStreamManager& operator=(InStreamManager& right);

    bool requestAbortM;
    bool shutdownM;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
// CodeReview - 08.2001 - jkeckstein - V - In normal way, we use a parameter
//                                to set a value. This can be difficult
//                                to interpret, what happens in this method.
//                                Default: void member_name(...) to set a value
//                                        type member_name() to get a value
// Checked by CodeReview - 08.2001 - MLi - is OK
inline void InStreamManager::requestAbort()
{
	requestAbortM = true;
}

// CodeReview - 08.2001 - jkeckstein - V - In normal way, we use a parameter
//                                to set a value. This can be difficult
//                                to interpret, what happens in this method.
//                                Default: void member_name(...) to set a value
//                                        type member_name() to get a value
// Checked by CodeReview - 08.2001 - MLi - is OK
inline bool InStreamManager::shutdown()
{
	shutdownM = true;
	return true;
}

inline bool InStreamManager::isActive()
{
	return true;
}

inline void* InStreamManager::getContext()
{
	return 0; // this method needs to be overriden if 
	          // there is a context to return.
}
}
#endif // InStreamManager_HPP
