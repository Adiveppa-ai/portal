#ifndef PLG_OutputDevice_HPP
#define PLG_OutputDevice_HPP

// @(#)%Portal Version: OutputDevice.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:47:51 %
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
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
// $RCSfile: OutputDevice.hpp,v $
// $Revision: 1.4 $
// $Author: mliebmann $
// $Date: 2002/03/13 10:53:59 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: OutputDevice.hpp,v $
// Revision 1.4  2002/03/13 10:53:59  mliebmann
// PETS #39719 sequencer mod for Rap/Tap: backup for ClearCase migration
//
// Revision 1.3  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// Revision 1.2  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.1  2001/08/10 12:35:10  mliebmann
// PETS #36559 SourcePro AIX port
//
// Revision 1.27  2001/07/12 10:23:58  mliebmann
// PETS #36926 handling of isUsable()-call fixed on all levels
//
// Revision 1.26  2001/06/28 10:28:02  mliebmann
// forwarddefinition for PPL::OutputCollection added
//
// Revision 1.25  2001/06/27 06:35:45  mliebmann
// releaseEdr(..) moved and some additional changes based on the first!
//
// Revision 1.24  2001/06/26 13:42:50  sd
// - ERR_OUTPUT_MAPPING_FAILED added
//
// Revision 1.23  2001/06/26 11:47:44  mliebmann
// method PPL::OutputCollection * outputCollection() added
//
// Revision 1.22  2001/06/26 11:31:31  mliebmann
// reject-stream handling fixed
//
// Revision 1.21  2001/05/30 13:51:28  mliebmann
// method to delete empty streams added (streams without detail-container)
//
// Revision 1.20  2001/05/28 08:19:43  mliebmann
// setStreamLog for writeToStreamLog(...) added
//
// Revision 1.19  2001/05/18 14:51:49  mliebmann
// releaseEdr() is public now
//
// Revision 1.18  2001/05/18 13:04:24  mliebmann
// LogError(EDR::Container *) moved into OutputDevice
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
// Revision 1.14  2001/05/11 09:09:19  mliebmann
// error messages added/corrected
//
// Revision 1.13  2001/05/08 14:52:14  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.12  2001/04/26 11:47:53  mliebmann
// GenericIO: little changes
//
// Revision 1.11  2001/04/26 09:26:59  mliebmann
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
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   PLI_OutputManagerInterface_HPP
  #include "PLI/OutputManagerInterface.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   PLG_SEQUENCER_HPP
  #include "PLG/Sequencer.hpp"
#endif
#ifndef   PLG_TRAILERINFO_HPP
  #include "PLG/TrailerInfo.hpp"
#endif

namespace EDR
{
class Container;
}
namespace PPL
{
class OutputCollection;
}
namespace PLG
{

//------------------------------------------------------------------------------
// Forward declarations and typedefs.
//------------------------------------------------------------------------------

/** <tt><b>abstract class OutputDevice</b></tt><br>
    <p>This module represents the last element of <em>integRate</em>.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: OutputDevice.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.4 $</font></td>
    <td><font size=-1>$Date: 2002/03/13 10:53:59 $</font></td>
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
class OutputDevice : public TransactionPlugIn
{
  friend class PPL::OutputCollection;
  friend class OutputStreamDevice;
  public:

    /**@name OutputDevice Constructors and Destructors */
    //@{
      /** Default constructor.<br>
        * Creates an unregistered OutputStreamPlugIn.
        * This Object cannot be used as an output stream. */
      OutputDevice();

      /** Standard constructor.<br>
        * Creates an registered OutputStreamPlugIn. 
        * @param name    The name for the created object.
        * @param version The version for the created object. */
      OutputDevice(const BAS::String& name,
                       const BAS::String& version);

      /// Destructor.
      virtual ~OutputDevice();
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
      virtual bool commitIO(const TAM::TransId& id, const bool sequenceGenerationPerUnit) = 0;
   
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
      virtual STR::IOResultT write(EDR::Container * edr);

      /** Close. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT close();
      
      /** DeleteEmptyStream.
        * Is called if no detail reachs an outputdevice and delete the stream, 
        * even if a header or trailer passed into the device/stream.
        * @return <tt>STR::IOResultT</tt> IO result */
      virtual STR::IOResultT deleteEmptyStream(const TAM::TransId & transId);

      /** Method to ask for the output filename.
        * @return <tt>true</tt> determined,<br>
        *         <tt>false</tt> not determined. */
      virtual bool getOutputStreamName(const BAS::String & streamName, BAS::String & streamName_Out);
    //@}

    /** Module control. */
    //@{
      /// Get the outputCollection pointer
      PPL::OutputCollection * outputCollection();

      /** IsActive. Show if the module is active or not.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool isActive();

      /// Shutdown. Show the stream that the system shutdown.
      virtual bool shutdown() = 0;

      /// Write version of the module.
      virtual void writeModuleVersion() const;
    
      /// write message into the streamLog
      void writeToStreamLog(const BAS::Status& s);

      /** Is modul usable.
        * @return <tt>true</tt> is usable,<br>
        *         <tt>false</tt> is not usable. */
      virtual bool isUsable();

      /** Get actual SequnceNumber.
        * @return <tt>SequenceNumberType</tt> sequence number */
      SequenceNumberType actualSequenceNumber();

      /** Get the seqeuncer name
        * @return name of sequence if applicable for this device
        * NULL_STRING otherwise
        */
      BAS::String getSequencerName() const;

    //@}

  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    OutputDevice(OutputDevice& right);
    const OutputDevice& operator=(OutputDevice& right);

    bool setEDRContainerIndices();

    /// Set the outputCollection.
    bool outputCollection(PPL::OutputCollection * outputCollection);
      
    bool setStreamLog(LOG::StreamDate * streamLog);
    void disableStreamLog();
	bool isStreamLogDisabled() const;

	bool streamLogDisabledM;
    LOG::StreamDate * streamLogM;

    PLG_EXPORT static const BAS::String registrySequenceHandlerCM;
    PLG_EXPORT static const BAS::String registrySequencerPoolCM;
    PLG_EXPORT static const BAS::String registryPipelinesCM;
    PLG_EXPORT static const BAS::String registrySequenceGenerationCM;
    PLG_EXPORT static const BAS::String trailerInfoNameCM;

    EDR::Index            headerSequenceKeyIdxM;
    EDR::Index            headerSequenceNumberIdxM;
    EDR::Index            trailerSequenceNumberIdxM;

    // Sequence Handler object.
    Sequencer *      sequencerM;

    // indicates if the sequencer object is needed or not
    bool                 sequencerNeededM;

    // actual sequencenumber for renaming if close is called!
    SequenceNumberType   actualSequenceNumberM;
    SequenceNumberType   actualOriginSequenceNumberM;

    // actual streamname in process if sequencer is needed!    
    BAS::String           curStreamNameM;
    const TAM::TransId *  curTransIdM;

    // Array with trailer infos for every output stream
    TrailerInfo *    trailerInfoM;

    PPL::OutputCollection * outputCollectionM;
    
    BAS::String keyM;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
inline bool OutputDevice::isActive()
{
  if (!isStreamLogDisabled() && !streamLogM)
  {
    return false;
  }
  
  if (!outputCollectionM)
  {
    return false;
  }
  
  return true;
}

inline void 
OutputDevice::writeToStreamLog(const BAS::Status& s)
{
  D_ENTER("PLG::OutputDevice::writeToStreamLog(const BAS::Status& s)");
  if (!isStreamLogDisabled())
  {
	  if (streamLogM)
	  {
		  streamLogM->write(s);
	  } else 
	  {
		  setStatus("WRN_NO_STREAMLOG::DEFINED",BAS::Status::major);
		  isValid(false);
	  }
  }
}

inline bool 
OutputDevice::outputCollection(PPL::OutputCollection * outputCollection)
{
  outputCollectionM = outputCollection;
  return (outputCollectionM != 0);
}

inline PPL::OutputCollection * 
OutputDevice::outputCollection()
{
  return outputCollectionM;
}

inline SequenceNumberType 
OutputDevice::actualSequenceNumber()
{
  return actualSequenceNumberM;
}

inline bool 
OutputDevice::getOutputStreamName(const BAS::String & streamName, BAS::String & streamName_Out)
{
  return false;
}

inline BAS::String
OutputDevice::getSequencerName() const
{
  if ((sequencerNeededM == true) && sequencerM != 0)
  {
    return sequencerM->name();
  }
  else 
  {
    return BAS::NULL_STRING;
  }

}

inline bool
OutputDevice::isStreamLogDisabled() const
{
	return streamLogDisabledM;
}

}
#endif // OutputDevice_HPP
