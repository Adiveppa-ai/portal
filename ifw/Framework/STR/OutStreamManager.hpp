#ifndef STR_OutStreamManager_HPP
#define STR_OutStreamManager_HPP
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
// Responsible: Karl Braemer
//
// $RCSfile: OutStreamManager.hpp,v $
// $Revision: 1.23 $
// $Author: sd $
// $Date: 2001/09/25 13:50:28 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OutStreamManager.hpp,v $
// Revision 1.23  2001/09/25 13:50:28  sd
// PETS #38714 EXT_OutFileManager: empty outputfile not deleted
//
// Revision 1.22  2001/09/03 11:24:20  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.21  2001/08/28 07:33:31  jkeckst
// PETS 37618 code review 08.2001
//
// Revision 1.20  2001/06/06 13:07:04  mliebmann
// online-doc fixed
//
// Revision 1.19  2001/05/30 13:51:28  mliebmann
// method to delete empty streams added (streams without detail-container)
//
// Revision 1.18  2001/05/28 08:19:43  mliebmann
// setStreamLog for writeToStreamLog(...) added
//
// Revision 1.17  2001/05/15 15:22:05  mliebmann
// registry switch SequenceGeneration changed perFile/perTransaction to Unit/Transaction
//
// Revision 1.16  2001/05/15 10:14:26  mliebmann
// new procedure implementated for sequencegeneration perFile or perTransaction on base of the outputstreams
//
// Revision 1.15  2001/05/14 15:02:52  mliebmann
// IOResult fixed
//
// Revision 1.14  2001/05/08 14:52:15  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.13  2001/05/03 11:39:55  mliebmann
// GenericIO: Sequencer bug fixed and little changes
//
// Revision 1.12  2001/04/26 11:47:53  mliebmann
// GenericIO: little changes
//
// Revision 1.11  2001/04/26 09:25:45  mliebmann
// GenericIO: TAM added
//
// Revision 1.10  2001/04/11 10:15:44  mliebmann
// Generic IO: little changes and documentation added
//
// Revision 1.9  2001/04/10 13:23:54  mliebmann
// Generic IO: changes
//
// Revision 1.8  2001/04/10 10:01:04  mliebmann
// Generic IO: enumeration FILE_IO added
//
// Revision 1.7  2001/04/09 14:23:59  mliebmann
// Generic IO: changes
//
// Revision 1.6  2001/04/05 15:13:20  mliebmann
// Generic IO: updated
//
// Revision 1.5  2001/04/03 14:23:02  mliebmann
// Generic IO: changes
//
// Revision 1.4  2001/03/27 14:00:48  mliebmann
// Generic IO - Interface Changed - only backup
//
// Revision 1.3  2001/03/27 13:24:32  mliebmann
// Generic IO - only Backup
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
#ifndef   LOG_STREAMDATE_HPP
  #include "LOG/StreamDate.hpp"
#endif

// Include used for the IOResultT enumeration
#ifndef   STR_InStreamManager_HPP
  #include "STR/InStreamManager.hpp"
#endif

// #include "PLG/SequenceControl.hpp"

namespace EDR
{
class Container;
}
namespace PLG
{
	class OutputStreamDevice;
}
namespace STR
{

/** <tt><b>abstract class OutStreamManager</b></tt> provides an output 
    stream interface.
    Currently EXT_OutFileManager is supported.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: OutStreamManager.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.23 $</font></td>
    <td><font size=-1>$Date: 2001/09/25 13:50:28 $</font></td>
    <td><font size=-1>$Author: sd $</font></td>
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
class OutStreamManager : public PLG::TransactionPlugIn
{
  friend class PLG::OutputStreamDevice;
  public:

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    OutStreamManager();

    /** Standard constructor.<br>
        Creates an registered InputDevice. 
        @param name    The name for the created object.
        @param version The version for the created object.
        @param queue Input queue for the edr's.
                     This is the output queue of the function
                     plug in.  (comes from FRM_Format)
    */
    OutStreamManager(const BAS::String& name,
                         const BAS::String& version);

    /** Destructor. */
    virtual ~OutStreamManager();
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
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool prepareCommitIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit) = 0;

      /** Commit transaction for the given transaction id.
        * @param id The transaction id.
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool commitIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit) = 0;
   
      /** Cancel transaction for the given transaction id.
        * @param id The transaction id.
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancelIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit) = 0;

      /** Rollback transaction for the given transaction id.
        * @param id The transaction id.
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollbackIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit) = 0;
    //@}

    /** Stream-access-functions */
    //@{
      /** Open stream. 
        * @return <tt>IOResultT</tt> IO result. */
      virtual IOResultT open(const BAS::String& name) = 0;
   
      /** Write line to stream. 
        * @return <tt>>=0</tt> operation was successful and count of written bytes,<br>
        *         <tt>-1</tt> otherwise. */
      virtual int64 write(BAS::String& str);
   
      /** Write block to stream.
        * @return <tt>>=0</tt> operation was successful and count of written bytes,<br>
        *         <tt>-1</tt> otherwise. */
      virtual int64 write(const void* p, size_t size);

      /** Close stream.
        * @return <tt>IOResultT</tt> IO result. */
      virtual IOResultT close(BAS::String& seqNumber) = 0;
      
      /** Delete the last opened stream.
        * @return <tt>IOResultT</tt> IO result */
      virtual IOResultT deleteStream() = 0;
    //@}

    /** Module control. */
    //@{
      /** IsActive. Show if the module is active or not.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool isActive();

      /// write message into the streamLog
      void writeToStreamLog(const BAS::Status& s);
    //@}

  protected:
  
    void IOStatus(IOResultT result);
   
  private:
  
    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    OutStreamManager(OutStreamManager& right);
    const OutStreamManager& operator=(OutStreamManager& right);

    bool setStreamLog(LOG::StreamDate * streamLog);

    LOG::StreamDate * streamLogM;

    IOResultT IOStatus();
    
    IOResultT curIOStatusM;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
inline bool 
OutStreamManager::isActive()
{
  return true;
}

inline IOResultT 
OutStreamManager::IOStatus()
{
  return curIOStatusM;
}

inline void 
OutStreamManager::IOStatus(IOResultT result)
{
  curIOStatusM = result;
}
}
#endif // OutStreamManager_HPP
