#ifndef PLG_OutputStreamDevice_HPP
#define PLG_OutputStreamDevice_HPP 
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
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: OutputStreamDevice.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:50 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OutputStreamDevice.hpp,v $
//
// Revision 1.9 2012/05/14 Santanu
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER
//
// Revision 1.8  2004/10/14 15:30:59 kbhagavath 
// PRSF00131806 fix a couple of memory leaks in OutputStreamDevice 
//
// Revision 1.7  2002/03/13 10:53:59  mliebmann
// PETS #39719 sequencer mod for Rap/Tap: backup for ClearCase migration
//
// Revision 1.6  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// Revision 1.5  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.4  2001/09/25 10:41:39  mliebmann
// PETS #38714 DeleteEmptyFile moved from EXT_OutFileManager into the base-class OutputStreamDevice
//
// Revision 1.3  2001/09/25 08:33:18  mliebmann
// PETS #38714 DeleteEmptyFile moved from EXT_OutFileManager into the base-class OutputStreamDevice
//
// Revision 1.2  2001/09/03 11:28:06  mliebmann
// PETS #37618 code review implemention supplmention to STR
//
// Revision 1.1  2001/08/10 12:35:10  mliebmann
// PETS #36559 SourcePro AIX port
//
// Revision 1.8  2001/07/12 10:23:58  mliebmann
// PETS #36926 handling of isUsable()-call fixed on all levels
//
// Revision 1.7  2001/05/30 13:51:28  mliebmann
// method to delete empty streams added (streams without detail-container)
//
// Revision 1.6  2001/05/28 08:19:43  mliebmann
// setStreamLog for writeToStreamLog(...) added
//
// Revision 1.5  2001/05/15 15:22:05  mliebmann
// registry switch SequenceGeneration changed perFile/perTransaction to Unit/Transaction
//
// Revision 1.4  2001/05/15 10:14:26  mliebmann
// new procedure implementated for sequencegeneration perFile or perTransaction on base of the outputstreams
//
// Revision 1.3  2001/05/14 15:02:52  mliebmann
// IOResult fixed
//
// Revision 1.2  2001/05/08 14:52:14  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.1  2001/04/26 09:26:59  mliebmann
// GenericIO: TAM added
//
// Revision 1.10  2001/04/11 10:15:13  mliebmann
// Generic IO: little changes and documentation added
//
// Revision 1.9  2001/04/10 13:24:15  mliebmann
// Generic IO: changes
//
// Revision 1.8  2001/04/10 10:01:32  mliebmann
// Generic IO: enumeration FILE_IO added
//
// Revision 1.7  2001/04/09 14:22:45  mliebmann
// changes commited
//
// Revision 1.6  2001/04/05 15:12:52  mliebmann
// Generic IO: updated
//
// Revision 1.5  2001/04/03 14:22:12  mliebmann
// Generic IO: changes
//
// Revision 1.4  2001/03/28 09:52:32  mliebmann
// Generic IO - only Backup
//
// Revision 1.3  2001/03/27 13:23:37  mliebmann
// Generic IO - only Backup
//
// Revision 1.2  2001/03/23 15:10:09  mliebmann
// GenericIO - only backup
//
// Revision 1.1  2001/03/21 09:41:56  mliebmann
// only for Backup
//
//
//==============================================================================

#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>
#endif
#ifndef   PLG_TRANSACTIONPLUGIN_HPP
  #include "PLG/TransactionPlugIn.hpp"
#endif
#ifndef   STR_OutStreamManager_HPP
  #include "STR/OutStreamManager.hpp"
#endif
#ifndef   LOG_STREAMDATE_HPP
  #include "LOG/StreamDate.hpp"
#endif
#ifndef   PLI_OutputManagerInterface_HPP
  #include "PLI/OutputManagerInterface.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   PLG_OutputDevice_HPP
  #include "PLG/OutputDevice.hpp"
#endif

namespace EDR
{
class Container;
}
namespace PLG
{

//------------------------------------------------------------------------------
// Forward declarations and typedefs.
//------------------------------------------------------------------------------

/** <tt><b>abstract class OutputStreamDevice</b></tt><br>
    <p>This module represents the last element of <em>integRate</em>
    and it uses a stream-module to access to physical devices.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: OutputStreamDevice.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/05/23 01:27:50 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    </tr>
    </table>                                                                          
  
    <dl>
      <dt><b>Registry entries</b></dt>
      <dd>OutputStream</dd>
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
      <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    </dl> 

*/
class OutputStreamDevice : public OutputDevice
{
  friend class PPL::OutputCollection;
  public:

    /**@name OutputStreamDevice Constructors and Destructors */
    //@{
      /** Default constructor.<br>
          Creates an unregistered OutputStreamPlugIn.
          This Object cannot be used as an output stream. */
      OutputStreamDevice();

      /** Standard constructor.<br>
          Creates an registered OutputStreamPlugIn. 
          @param name    The name for the created object.
          @param version The version for the created object. */
      OutputStreamDevice(const BAS::String& name,
                       const BAS::String& version);

      /// Destructor.
      virtual ~OutputStreamDevice();
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
      /** Open. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT open(const BAS::String& name, const int64 curSeqGen, const int64 curOffGen);
   
      /** Write. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT write(EDR::Container * edr) = 0;
   
      /** Close. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT close();

      /** DeleteEmptyStream.
        * Is called if no detail reachs an outputdevice and delete the stream, 
        * even if a header or trailer passed into the device/stream.
        * @return <tt>STR::IOResultT</tt> IO result */
      virtual STR::IOResultT deleteEmptyStream(const TAM::TransId & transId);
    //@}

    /** Module control. */
    //@{
      /** IsActive. Show if the module is active or not.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool isActive();

      /** Shutdown. Show the stream that the system shutdown. */
      virtual bool shutdown();

      /** Get the stream module. */
      virtual STR::OutStreamManager * outStreamManagerPlugIn();
    
      /** Write version of the module. */
      virtual void writeModuleVersion() const;

      /** Is modul usable.
        * @return <tt>true</tt> is usable,<br>
        *         <tt>false</tt> is not usable. */
      virtual bool isUsable();

      /** Method to ask for the state of the registry-parameter DeleteEmptyFile.
        * @return <tt>true</tt> should delete,<br>
        *         <tt>false</tt> should not delete. */
      virtual bool getDeleteEmptyStream();

      /** Method to ask for the output filename.
        * @return <tt>true</tt> determined,<br>
        *         <tt>false</tt> not determined. */
      virtual bool getOutputStreamName(const BAS::String & streamName, BAS::String & streamName_Out);
    //@}

      /** Check if the multithreaded write is enabled
       *  return <tt>true</tt> is enabled ,<br>
       *         <tt>false</tt> is not enabled. */
      bool isMultiThreadedWrite();

      /** Set the multithreaded write is enabled
       *  @param enabled The flag to set the multithreaded flag
       */
      void multiThreadedWrite(const bool enabled);
    
  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    OutputStreamDevice(OutputStreamDevice& right);
    const OutputStreamDevice& operator=(OutputStreamDevice& right);

    STR::IOResultT IOStatus();

    bool setStreamLog(LOG::StreamDate * streamLog);
 
    PLI::OutputManagerInterface* outStreamManagerInterfaceM;
    
    BAS::OnlyPointer<STR::OutStreamManager> outStreamManagerPlugInM;

    // Registry strings
    PLG_EXPORT static const BAS::String outputStreamManagerCM;
    PLG_EXPORT static const BAS::String registryDeleteEmptyStreamCM;

    bool deleteEmptyStreamM;

    bool multiThreadedWriteEnabledM; 
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
inline bool
OutputStreamDevice::shutdown()
{
  RWPRECONDITION(outStreamManagerPlugInM);

  // tell the stream the request!
  return outStreamManagerPlugInM->shutdown();
}

inline STR::OutStreamManager * 
OutputStreamDevice::outStreamManagerPlugIn()
{
  return outStreamManagerPlugInM.get();
}

inline bool 
OutputStreamDevice::isActive()
{
  RWPRECONDITION(outStreamManagerPlugInM);
  
  return outStreamManagerPlugInM->isActive();
}

inline bool 
OutputStreamDevice::getDeleteEmptyStream()
{
  return deleteEmptyStreamM;
}
}
#endif // OutputStreamDevice_HPP
