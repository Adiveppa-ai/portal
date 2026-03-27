#ifndef PPL_OutputCollection_HPP
#define PPL_OutputCollection_HPP
//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLG
//------------------------------------------------------------------------------
// Module Description:
//  OutputStreamPlugIn class implementation.
//
//  This class is the base class for all output stream PlugIn's.
//
//------------------------------------------------------------------------------
//
// Revision: 10004 7.5    14-May-2012 Santanu
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.24  2002/03/13 10:53:59  mliebmann
// PETS #39719 sequencer mod for Rap/Tap: backup for ClearCase migration
//
// Revision 1.23  2001/10/16 12:29:15  mliebmann
// PETS #40541 FCT_DuplicateCheck - no data which ... -> basic functionality for I-Script: Message REQ_STREAM_NAME from output-collection
//
// Revision 1.22  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.21  2001/09/25 08:33:18  mliebmann
// PETS #38714 DeleteEmptyFile moved from EXT_OutFileManager into the base-class PLG::OutputStreamDevice
//
// Revision 1.20  2001/09/17 11:01:53  mliebmann
// PETS #39464 ERR_REJECT_STREAM_NOT_DEFINED renamed to ERR_STREAM_NOT_FOUND for REQ_STREAM_NUMBER in OutputCollection
//
// Revision 1.19  2001/08/31 13:36:50  mliebmann
// PETS #37618 warnings eliminated
//
// Revision 1.18  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.17  2001/07/18 09:32:23  mliebmann
// PETS #36557 double error logs from haeder and trailer into streamlog fixed
//
// Revision 1.16  2001/07/10 09:31:29  mliebmann
// PETS #36808 renamed variable lastHeaderM into lastTrailerM
//
// Revision 1.15  2001/06/28 12:28:46  mliebmann
// statist for header and trailer fixed - inf-message added for the pipelineLog for demanding rollback
//
// Revision 1.12  2001/06/27 06:35:45  mliebmann
// releaseEdr(..) moved and some additional changes based on the first!
//
// Revision 1.11  2001/06/26 11:31:31  mliebmann
// reject-stream handling fixed
//
// Revision 1.10  2001/06/05 14:36:17  mliebmann
// reject stream number return fixed
//
// Revision 1.9  2001/05/30 13:51:28  mliebmann
// method to delete empty streams added (streams without detail-container)
//
// Revision 1.8  2001/05/18 13:04:24  mliebmann
// LogError(EDR::Container *) moved into PLG::OutputDevice
//
// Revision 1.7  2001/05/15 15:22:05  mliebmann
// registry switch SequenceGeneration changed perFile/perTransaction to Unit/Transaction
//
// Revision 1.6  2001/05/15 10:14:26  mliebmann
// new procedure implementated for sequencegeneration perFile or perTransaction on base of the outputstreams
//
// Revision 1.5  2001/05/14 15:02:52  mliebmann
// IOResult fixed
//
// Revision 1.4  2001/05/11 09:09:19  mliebmann
// error messages added/corrected
//
// Revision 1.3  2001/05/08 14:52:14  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.2  2001/05/04 09:17:37  bt
// Method writeToPipelineLog() changed.
//
// Revision 1.1  2001/05/03 16:31:07  bt
// FRM modules moved to PPL (Format renamed to Pipeline).
//
// Revision 1.9  2001/04/26 09:23:26  mliebmann
// GenericIO: TAM added
//
// Revision 1.8  2001/04/11 10:14:35  mliebmann
// Generic IO: little changes and documentation added
//
// Revision 1.6  2001/04/10 10:17:29  mliebmann
// Generic IO: cahnges
//
// Revision 1.5  2001/04/04 12:00:54  sd
// - Old stream interfaces removed
//
// Revision 1.4  2001/04/04 08:34:14  mliebmann
// Generic IO: default outputdevice added
//
// Revision 1.3  2001/04/03 12:30:50  mliebmann
// Generic IO: changes
//
// Revision 1.2  2001/03/23 15:08:10  mliebmann
// GenericIO - only backup
//
// Revision 1.1  2001/03/21 09:39:11  mliebmann
// only for backup
//
//
//==============================================================================

#if !defined PPL_EXPORT
  #if defined(WINDOWS)
    #if !defined(PPL_INTERNAL)
      #define PPL_EXPORT __declspec(dllimport)
    #else
      #define PPL_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PPL_EXPORT
  #endif
#endif

#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>
#endif
#ifndef   RW_TOOLS_TPVECTOR_H
  #include <rw/tpvector.h>
#endif
#ifndef   RW_TOOLS_TVVECTOR_H
  #include <rw/tvvector.h>
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   PLG_SEQUENCER_HPP
  #include "PLG/Sequencer.hpp"
#endif
#ifndef   LOG_STREAMDATE_HPP
  #include "LOG/StreamDate.hpp"
#endif
#ifndef   PLI_OutputInterface_HPP
  #include "PLI/OutputInterface.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   BAS_PROC_TIME_HPP
  #include "BAS/ProcTime.hpp"
#endif

//------------------------------------------------------------------------------
// Forward declarations and typedefs.
//------------------------------------------------------------------------------
namespace PLG
{
class OutputStream;
}
namespace PPL
{
class OutputController;



/** <tt><b>class OutputCollection.</b></tt>

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: OutputCollection.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/05/23 01:27:51 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    <td><font size=-1>$RCSfile: OutputCollection.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/05/23 01:27:51 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    </tr>
    </table>

    <p>This class represents the last element in the <em>integRate</em> process pipeline.
    It acts as the "data sink" of the system.


    <dl>
      <dt><b>Registry entries</b></dt>
      <dd>RejectOutput</dd>
      <dd>DevNull (optional)</dd>
      <dt><b>Messages send</b></dt>
      <dd>none</dd>
      <dt><b>Messages receive</b></dt>
      <dd>none</dd>
      <dt><b>Request send</b></dt>
      <dd>none</dd>
      <dt><b>Request receive</b></dt>
      <dd>REQ_STREAM_NUMBER</dd>
      <dd>REQ_STREAM_NAME</dd>
      <dt><b>Event send</b></dt>
      <dd>none</dd>
      <dt><b>Errors</b></dt>
      <dd>ERR_CANNOT_INIT_OUTPUT_MODULE</dd>
      <dd>ERR_ILLEGAL_DEVICE_NUM</dd>
      <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
      <dd>ERR_STREAM_NOT_FOUND</dd>
    </dl>

*/
class OutputCollection : public BAS::Object
{
  friend class OutputController;

  public:
    STR::IOResultT rejectEdr(EDR::Container * edr);
    bool releaseEdr(EDR::Container * edr);

    /** Return the current output contoller in this collection
      * @return pointer to the current PPL_OutputController
      */
    OutputController *getOutputController();

  private:
    /**@name OutputCollection Constructors and Destructors */
    //@{
    /** Default constructor.<br>
        Creates an unregistered OutputStreamPlugIn.
        This Object cannot be used as an output stream.
    */
    OutputCollection();

    /** Standard constructor.<br>
        Creates an registered OutputStreamPlugIn.
        @param name    The name for the created object.
        @param version The version for the created object.
        @param queue Input queue for the edr's.
                     This is the output queue of the function
                     plug in.  (comes from Pipeline)
    */
    OutputCollection(const BAS::String& name,
                               OutputController * outputCollection,
                               TAM::ManagerIf * managerIf);

    /** Destructor. */
    virtual ~OutputCollection();
    //@}

    /** Transaction-functions */
    //@{
      /** Send a begin transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool beginTransactionIO(const TAM::TransId* id);

      /** Prepare to commit for the given transaction id.
        * @param id The transaction id.
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool prepareCommitIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit);

      /** Commit transaction for the given transaction id.
        * @param id The transaction id.
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool commitIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit);

      /** Cancel transaction for the given transaction id.
        * @param id The transaction id.
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancelIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit);

      /** Rollback transaction for the given transaction id.
        * @param id The transaction id.
        * @param sequenceGenerationPerUnit bool for the streams/devices
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollbackIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit);
    //@}

    /** Stream-access-functions */
    //@{
      /** Open. */
      virtual STR::IOResultT open(const BAS::String& name, const int64 curSeqGen, const int64 curOffGen);

      /** Write. */
      virtual STR::IOResultT write(EDR::Container * edr);

      /** Close. */
      virtual STR::IOResultT close();

      /** GetIOStatus.*/
      STR::IOResultT getIOResult();

      /// Set the streamLog for each outputdevice.
      bool setStreamLogs(LOG::StreamDate * streamLog);
    //@}

    /** Module control. */
    //@{
      /** Return the count of output devices.
        * @return <tt>size_t</tt> count of devices. */
      size_t size();

      /** Return the usability of the module.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      bool isUsable();

      /** Write version of the module. */
      void writeModuleVersion() const;

      /** Shutdown. Show the stream that the system shutdown. */
      bool shutdown();

  bool install();

  bool uninstall();

  bool startup();

      /** Recieve messages. */
      void receiveRequest(BAS::Message& msg);

      STR::IOResultT getIOStatus();

      int64 rejectStream();
    //@}

    /** Log writing method.
        Creates a log command for the pipeline object
        and sends it.
        @param s The status to be logged.
    */
    void writeToPipelineLog(const BAS::Status& s) const;
    void writeToStreamLog(const BAS::Status& s);

  /** Disable stream logging */
  void disableStreamLog();

  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    OutputCollection(OutputCollection& right);
    const OutputCollection& operator=(OutputCollection& right);

  /** Determine if the stream log is disabled or not
   */
  bool isStreamLogDisabled() const;

    bool getEdrFactory();
    EDR::Factory *                      edrFactoryM;

    EDR::Container *                    lastHeaderM;
    EDR::Container *                    lastTrailerM;
    bool                               headerErrorsLoggedM;
    bool                               trailerErrorsLoggedM;

    OutputController *             outputControllerM;

    TAM::ManagerIf *                    tamManagerIfM;
    const TAM::TransId *                curTransIdM;

    LOG::StreamDate *                   streamLogM;

  /** Set to true if we are not using stream logs */
  bool streamLogDisabledM;

    void logErrors(EDR::Container* edr);

    PPL_EXPORT static const BAS::String            registryPipelinesCM;

    bool readRegistry();
    bool evalEnvironment();
    bool registryUpdate(const BAS::RegistryEntry* updateRegistry,
                        BAS::ProtectedBool&       workedOn);

    RWTPtrVector<PLI::OutputInterface>  outputInterfaceListM;

    BAS::RegisteredObject*              pipelineLogM;

    void setIOStatus(PLG::OutputDevice * p);
    STR::IOResultT                          curIOStatusM;

    int64                               rejectStreamM;
    BAS::ProcTime                      pluginStatM;

    RWMutexLock releaseLockM;
    RWMutexLock pluginStatLockM;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
inline void OutputCollection::writeModuleVersion() const
{
  for (size_t i = 0; i<outputInterfaceListM.length(); i++)
  {
    if (outputInterfaceListM[i]->isValid())
    {
      outputInterfaceListM[i]->plugIn()->writeModuleVersion();
    }
  }
}

inline size_t OutputCollection::size()
{
  return outputInterfaceListM.length();
}

inline bool OutputCollection::shutdown()
{
  for (size_t i = 0; i<outputInterfaceListM.length(); i++)
  {
    if (outputInterfaceListM[i]->isValid())
    {
      if (outputInterfaceListM[i]->plugIn()->shutdown() == false)
      {
        setStatus(outputInterfaceListM[i]->plugIn()->status());
        isValid(false);
      }
    }
  }
  return isValid();
}

inline bool OutputCollection::startup()
{
  for (size_t i = 0; i<outputInterfaceListM.length(); i++)
  {
    if (outputInterfaceListM[i]->isValid())
    {
      if (outputInterfaceListM[i]->plugIn()->startup() == false)
      {
        setStatus(outputInterfaceListM[i]->plugIn()->status());
        isValid(false);
      }
    }
  }
  return isValid();
}

inline bool OutputCollection::uninstall()
{
  for (size_t i = 0; i<outputInterfaceListM.length(); i++)
  {
    if (outputInterfaceListM[i]->isValid())
    {
      if (outputInterfaceListM[i]->plugIn()->uninstall() == false)
      {
        setStatus(outputInterfaceListM[i]->plugIn()->status());
        isValid(false);
      }
    }
  }
  return isValid();
}

inline bool OutputCollection::install()
{
  for (size_t i = 0; i<outputInterfaceListM.length(); i++)
  {
    if (outputInterfaceListM[i]->isValid())
    {
      if (outputInterfaceListM[i]->plugIn()->install() == false)
      {
        setStatus(outputInterfaceListM[i]->plugIn()->status());
        isValid(false);
      }
    }
  }
  return isValid();
}

inline bool
OutputCollection::isStreamLogDisabled() const
{
  return streamLogDisabledM;
}

inline void
OutputCollection::writeToStreamLog(const BAS::Status& s)
{
  if (!isStreamLogDisabled())
  {
    if (streamLogM)
    {
      streamLogM->write(s);
    }
    else
    {
      setStatus("WRN_NO_STREAMLOG_DEFINED",BAS::Status::major);
      isValid(false);
    }
  }
}
inline  OutputController *
OutputCollection::getOutputController()
{
   return outputControllerM;
}

}
#endif // OutputCollection_HPP
