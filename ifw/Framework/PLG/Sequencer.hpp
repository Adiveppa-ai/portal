#ifndef PLG_SEQUENCER_HPP
#define PLG_SEQUENCER_HPP
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
//  Sequencer class declaration.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Carsten Lohmann
//
// $RCSfile: Sequencer.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: kkisalay $
// $Date: 2012/01/27 03:19:15 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Sequencer.hpp,v $
// Revision 1.17  2002/03/13 10:53:59  mliebmann
// PETS #39719 sequencer mod for Rap/Tap: backup for ClearCase migration
//
// Revision 1.16  2001/09/26 13:09:35  mliebmann
// PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.15  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.14  2001/09/26 08:24:21  mliebmann
// PETS #39834 IFW_EDRSEQLOG.RECYCLING is now set to the TAM::RECYCLE field of the corresponding streamname
//
// Revision 1.13  2001/06/01 08:24:09  mliebmann
// workaround for the sequencer
//
// Revision 1.12  2001/05/17 07:35:50  mliebmann
// Sequencer.hpp bug fixed for HP-UX
//
// Revision 1.11  2001/05/09 14:46:52  mliebmann
// fixed multiple input-streams to one output-stream / parameter SinlgeProcess in registry elimentated
//
// Revision 1.10  2001/05/08 07:11:20  mliebmann
// variable controller renamed to conrtollerM
//
// Revision 1.9  2001/05/03 16:03:49  bt
// Format renamed to Pipeline.
//
// Revision 1.8  2001/05/03 11:39:55  mliebmann
// GenericIO: Sequencer bug fixed and little changes
//
// Revision 1.7  2001/04/03 14:22:12  mliebmann
// Generic IO: changes
//
// Revision 1.6  2001/01/11 13:03:42  sd
// - First v4-30 check-in.
//
// Revision 1.5  2000/06/16 08:43:29  bt
// Changes for AIX xlC V366.
//
// Revision 1.4  2000/02/25 07:55:54  clohmann
// Class description added.
//
// Revision 1.3  2000/02/23 15:48:03  clohmann
// Sequence sharing added.
//
// Revision 1.2  2000/02/17 09:14:44  clohmann
// Sequence handler redesign.
//
// Revision 1.1  2000/02/16 10:11:02  clohmann
// Initial checkin.
//
//
//==============================================================================

#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   PLG_SEQUENCE_CONTROL_HPP
  #include "PLG/SequenceControl.hpp"
#endif
#ifndef   PLG_TRAILERINFO_HPP
  #include "PLG/TrailerInfo.hpp"
#endif
#ifndef   PLG_STATISTIC_HPP
  #include "PLG/Statistic.hpp"
#endif

namespace EDR
{
class Conatainer;
}

#ifndef INC_TEMPL_DEFS
namespace BAS
{
  template class OnlyPointer<PLG::TrailerInfo>;
  template class RWTValOrderedVector<OnlyPointer<PLG::TrailerInfo> >;
}
#endif
namespace PLG
{
typedef RWTValOrderedVector<BAS::OnlyPointer<TrailerInfo> > TrailerInfoVec;

/** This class is used by the output module as an interface to sequence controller.
    The type of the generated sequence controller depends on the registry SOURCE 
    entry. 

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Sequencer.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/01/27 03:19:15 $</font></td>
    <td><font size=-1>$Author: kkisalay $</font></td>
    </tr>
    </table>                                                                          

<p><dl>
   <dt><b>Registry entries</b></dt>
         <dd>Source</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Messages received</b></dt>
         <dd>none</dd>
    <dt><b>Requests send</b></dt>
         <dd>none</dd>
    <dt><b>Requests received</b></dt>
         <dd>none</dd>
    <dt><b>Errors</b></dt>
         <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
         <dd>ERR_REG_ENTRY_NOT_FOUND</dd>
         <dd>ERR_INVALID_REG_VALUE</dd>
         <dd>ERR_EVAL_ENVIRONMENT</dd>
</dl>

     This module generates the sequence hanlder object. The sequence handler 
     object type depens on the used interface (file or databse). 
*/
class Sequencer : public BAS::RegisteredObject
{
  public:

    enum SourceType
    {
      UNKNOWN  = 0,
      DATABASE = 1,
      FILE     = 2
    };

    /**@name SequenceHandler Constructors and Destructors */
    //@{
      /** Default constructor.<br>
          Creates an unregistered object.
      */
      Sequencer();
                                             
      /** Standard constructor.<br>
          Creates an registered sequence handler..
          @param name The name for the created object.
      */
      Sequencer(const BAS::String& name);

      /** Destructor. */
      virtual ~Sequencer();
    //@}                                   

    /**@name Main methods. */
    //@{

      /// Pass through to the sequence handler method
      bool evaluateCheck(const TAM::TransId        & transId, 
                         const BAS::String         & seqCkeckKey,
                         const SequenceNumberType & oldSequenceNumber, 
			       bool               & edrStatus, 
			       BAS::Status         & status);

      /// Pass through to the sequence handler method
      bool evaluateGenerate(const TAM::TransId        & transId, 
                            const BAS::String         & seqGenKey,
                            const SequenceNumberType & oldSequenceNumber, 
			          SequenceNumberType & newSequenceNumber);

      /// Pass through to the sequence handler method
      void rollback(const TAM::TransId & transId);

      /// Pass through to the sequence handler method
      bool commitOnEndTransaction(const TAM::TransId & transId);

      /// Pass through to the sequence handler method
      bool commitOnEndTransaction_In(const TAM::TransId & transId);

      /// Pass through to the sequence handler method 
      bool commitOnEndFile(const TAM::TransId &        transId,
                           const BAS::String&          streamName, 
                           const BAS::String &         streamName_Out, 
			   const BAS::String &         pipeline,
		           const BAS::String &         genKey,
                           const TrailerInfo&     trailerInfo,
			   const int64&                itemType,
			   const SequenceNumberType & actualSeqNum,
			   const SequenceNumberType & actualOrigSeqNum,
			   int64 numRecOut);

      /// Pass through to the sequence handler method 
      bool commitOnEndFile_In(const TAM::TransId &  transId,
                              const BAS::String&    streamName, 
			      const BAS::String &   pipeline,
		              const BAS::String &   checkKey,
                              const Statistic& counter,
			      const int64&          itemType);

      /// Pass though to the EdrSeqCheck of the controller
      bool setEdrSeqCheck(const int64 i);

      /// Pass though to the EdrSeqCheck of the controller
      bool setEdrOffsetGeneration(const int64 i);

      /// Pass though to the current SeqGeneration of the controller
      virtual bool setSeqGen(const int64 i);

      /// Pass though to the current length of the generated sequencenumber of the controller
      virtual unsigned int seqLength();

      /** Routine to process incoming requests.
        * When the request can not be served,
        * all argument list items will be removed.
        * @param msg The request message (in/out parameter). */
      virtual void receiveRequest(BAS::Message& msg);

      /** Release a single sequence number which was generated, because of
        * delete of the empty stream in the output-plugin.
        * @param const transId
	* @param seqNum
	* @param seqKey
	* @return success. */
      virtual bool releaseSequenceNumber(const TAM::TransId & transId, const SequenceNumberType & seqNum, const BAS::String & seqKey = "");
    //@}

  protected:
    /** Initialise an instance from the registry.
        @return <tt>False</tt> if the object could not initialise itself successfully,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool readRegistry();         

    /** Initilialise from environment.
        @return <tt>False</tt> if the object could not read the environment information,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool evalEnvironment();

    /** Evaluate the container indices.
        @return <tt>False</tt> if the object could not evaluate the indeices,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool setEDRContainerIndices();

    EDR::Index streamNameIdx() const;

  private: 

    // source indicator
    SourceType              sourceM; 

    // the sequence controller
    SequenceControl *   controllerM;

    // not implemented
    Sequencer(Sequencer&);
    void operator=(const Sequencer&);

    // Sequencer registry string(s).
    PLG_EXPORT static const BAS::String registrySequenceSourceCM;
    PLG_EXPORT static const BAS::String registryDatabaseControlCM;
    PLG_EXPORT static const BAS::String registryFileControlCM;
    PLG_EXPORT static const BAS::String registryPipelinesCM;
    PLG_EXPORT static const BAS::String registryControllerNameCM;
    
    EDR::Index streamNameIdxM;

    RWMutexLock sequenceLockerM;
    RWMutexLock sequenceCommitLockerM;
    RWMutexLock sequenceCommitInLockerM;
    RWMutexLock sequenceEndTransactionInLockerM;
    RWMutexLock sequenceEndTransactionLockerM;
    RWMutexLock sequenceRollbackLockerM;

};

//------------------------------------------------------------------------------
// get container indizes
//------------------------------------------------------------------------------
inline EDR::Index 
Sequencer::streamNameIdx() const
{
  return streamNameIdxM;
}

inline unsigned int 
Sequencer::seqLength()
{
  return controllerM->seqLength();
}
}
#endif // SEQUENCER_HPP
