#ifndef PLG_SEQUENCE_CONTROL_HPP
#define PLG_SEQUENCE_CONTROL_HPP

// @(#)$Id: SequenceControl.hpp /cgbubrm_7.5.0.pipeline/1 2012/01/27 03:19:14 kkisalay Exp $
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
//  Base class for sequence controller.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//
//==============================================================================

#if !defined PLG_EXPORT
  #if defined(WINDOWS)
    #if !defined(PLG_INTERNAL)
      #define PLG_EXPORT __declspec(dllimport)
    #else
      #define PLG_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PLG_EXPORT 
  #endif
#endif

#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   ONLYPOINTER_HPP
  #include "BAS/OnlyPointer.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   TAM_MANAGERIF_HPP
  #include "TAM/ManagerIf.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif

#ifndef   RW_TOOLS_TVDLIST_H
  #include <rw/tvdlist.h> 
#endif
#ifndef   RW_TOOLS_TVMMAP_H
  #include <rw/tvmmap.h>
#endif
#ifndef   RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif

namespace EDR
{
class Container;
}

namespace PLG
{
class SequenceControl;

/** This is the base class for all sequence controller. 
    The class provides some basic functionalities which 
    are used / needed by all sequence controller. 

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: SequenceControl.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/01/27 03:19:14 $</font></td>
    <td><font size=-1>$Author: kkisalay $</font></td>
    </tr>
    </table>                                                                          

<p><dl>
   <dt><b>Registry entries</b></dt>
         <dd>Check</dd>
         <dd>Generate</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Messages received</b></dt>
         <dd>none</dd>
    <dt><b>Requests send</b></dt>
         <dd>REQ_REJECT_STREAM</dd>
    <dt><b>Requests received</b></dt>
         <dd>none</dd>
    <dt><b>Errors</b></dt>
         <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
         <dd>ERR_REG_ENTRY_NOT_FOUND</dd>
         <dd>ERR_EVAL_ENVIRONMENT</dd>
         <dd>ERR_INVALID_SEQ_VALUE</dd>
         <dd>ERR_OFF_MIN_GREATER_MAX</dd>
         <dd>ERR_SEQ_MIN_GREATER_MAX</dd>
         <dd>ERR_SEQ_GAP</dd>
         <dd>ERR_DOUBLE_SEQ_NUMBER</dd>
         <dd>ERR_GAP_IN_SEQ_NUMBER</dd>
         <dd>ERR_INDEX_NOT_CREATED</dd>
         <dd>INF_NEW_SEQ_NUMBER</dd>
         <dd>INF_SEQUENCE_ROLLBACK</dd>
         <dd>INF_OFF_OUT_OF_RANGE</dd>
         <dd>INF_SEQ_OUT_OF_RANGE</dd>
</dl>
*/
class SequencerInformation
{
  public:

  BAS::String     pipeline;
  BAS::String     streamName;
  BAS::String     streamName_Out;
  BAS::String     genKey;
  BAS::Decimal    totalQuantity;
  BAS::Decimal    totalCharge;
  BAS::Decimal    totalAoC;
  
  size_t  numRecOut;

  size_t originalSequenceNumber;
  size_t sequenceNumber;
  
  size_t itemType;

  SequencerInformation() : totalQuantity(BAS::DECIMAL_NULL)
                             , totalCharge(BAS::DECIMAL_NULL)
                             , totalAoC(BAS::DECIMAL_NULL)
                             , originalSequenceNumber(-1)
                             , sequenceNumber(-1)
                             , numRecOut(0)
  {
    ;
  }
  ~SequencerInformation()
  {
    ;
  }
};

class SequencerInformation_In
{
  public:

  BAS::String     pipeline;
  BAS::String     streamName;
  BAS::String     checkKey;
  size_t numRecIn;
  size_t  numRecOut;
  size_t  numRecWarn;
  size_t  duration;
  
  size_t originalSequenceNumber;
  size_t itemType;
  size_t edrOffsetGeneration;

  SequencerInformation_In() : numRecIn(0)
                                , numRecOut(0)
                                , numRecWarn(0)
                                , duration(0)
                                , edrOffsetGeneration(-1)
                                , originalSequenceNumber(-1)
  {
    ;
  }
  ~SequencerInformation_In()
  {
    ;
  }
};

// The sequence number type
typedef u_int32 SequenceNumberType;

class SequenceControl : public BAS::RegisteredObject
{
  public:

    struct SequenceNumberTypeS
    {
      SequenceNumberType seqNum;
      BAS::String	 seqKey;
    };

    struct SequenceNumberSearchType
    {
      TAM::TransId        transId;
      SequenceNumberType seqNum;
      BAS::String	 seqKey;
    };

    /**@name SequenceControl Constructors and Destructors */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    SequenceControl();
                                             
    /** Standard constructor.<br>
        Creates an registered sequence controller.
        @param name The name for the created object.
    */
    SequenceControl(const BAS::String& name);

    /** Destructor. */
    virtual ~SequenceControl();
    //@}                                   

    /**@name Main methods. */
    //@{

    /** Check the original number.
    */
    virtual bool evaluateCheck(const TAM::TransId        & transId, 
                               const BAS::String         & seqCkeckKey,
                               const SequenceNumberType & sequenceNumber, 
			             bool               & edrStatus, 
				     BAS::Status         & status);

    /** Generate new sequence number.
    */
    virtual bool evaluateGenerate(const TAM::TransId        & transId, 
                                  const BAS::String         & seqGenKey, 
                                  const SequenceNumberType & oldSequenceNumber, 
				        SequenceNumberType & newSequenceNumber);

    /** Discard the actual sequence data.
    */
    virtual void rollback(const TAM::TransId & transId);

    /** Write the actual sequence data to control and log file:
    */
    virtual bool commitOnEndTransaction(const TAM::TransId & transId);

    /** Write the actual sequence data to control and log file:
    */
    virtual bool commitOnEndTransaction_In(const TAM::TransId & transId);

    /** Save internal the actual input log file:
    */
    virtual bool commitOnEndFile(const TAM::TransId &              transId,
                                 const SequencerInformation & seqInfo);

    /** Save internal the actual sequence check data:
    */
    virtual bool commitOnEndFile_In(const TAM::TransId &              transId,
                                    const SequencerInformation_In& seqInfo_In);

    /** Commit the DB/File operations to the database/file:
    */
    virtual bool commitToStorage();

    /** Rollback DB/File operations:
    */
    virtual bool rollbackFromStorage();
    
    /** Initialise the sequence controller.
    */
    virtual bool init();

    virtual bool currentSequencePresentInGap(const BAS::String & key);

      /** Release a single sequence number which was generated, because of
        * delete of the empty stream in the output-plugin.
        * @param const transId
	* @param seqNum
	* @param seqkey
	* @return success. */
      virtual bool releaseSequenceNumber(const TAM::TransId & transId, 
                                         const SequenceNumberType & seqNum, 
                                         const BAS::String         & seqKey);
    //@}

    /// Set current edrSeqCheck
    virtual bool setEdrSeqCheck(const size_t i);
    /// Set current SeqGeneration
    virtual bool setSeqGen(const size_t i);
    /// Set current OffsetGeneration
    virtual bool setEdrOffsetGeneration(const size_t i);

    /// Get the sequence number length (digits)
    virtual size_t seqLength();
    
  protected:
    /** Initialise an instance from the registry.
        @return <tt>False</tt> if the object could not initialise 
                               itself successfully,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool readRegistry();         

    /** Initilialise from environment.
        @return <tt>False</tt> if the object could not read the 
                               environment information,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool evalEnvironment();

    /** Evaluate the container indices.
        @return <tt>False</tt> if the object could not evaluate the indeices,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool setEDRContainerIndices();

    /** Sequence check is active.
    */
    virtual bool checkIsActive() const;

    /** Sequence geration function is active.
    */
    virtual bool generateIsActive() const;

    /** Generate next sequence number.
    */
    virtual SequenceNumberType nextSequenceNumber(const TAM::TransId & transId);

    /** Generate next offset number.
    */
    virtual SequenceNumberType nextOffset();

    /** Store the original sequence number.
    */
    virtual SequenceNumberType originalSequenceNumber(const BAS::String & key);
    virtual void originalSequenceNumber(const SequenceNumberType& num);
    virtual void conv_originalSequenceNumber(const BAS::String& num);

    /** Check the original sequence number.
    */
    virtual bool checkForDouble(const BAS::String & seqCkeckKey);

    /** Check for gaps in sequence number sequence.
    */
    virtual bool checkForGaps(const BAS::String & seqCkeckKey);

    /** Check the sequence values and convert strings to numbers.
    */
    bool checkAndConvert();

    // get pipeline name
    const BAS::String& sequencerName() const;
    //void sequencerName(const BAS::String& value);

    // write the sequence data into the sequence file
    virtual bool writeSequenceInformation(const BAS::String & key, const TAM::TransId & transId);

    // write the sequence data into the sequence file
    bool writeSequenceInformation(const BAS::String & key);

    // log the actual sequence information.
    virtual bool logSequenceInformation(SequencerInformation& seqInfo);

    // log the actual sequence information.
    virtual bool logSequenceInformation_In(SequencerInformation_In& seqInfo_In);

    SequenceNumberType lastOriginalSequenceNumber() const;
    void lastOriginalSequenceNumber(SequenceNumberType value);
    virtual SequenceNumberType lastOriginalSequenceNumber(const BAS::String & key);

    SequenceNumberType lastOffset() const;
    void lastOffset(SequenceNumberType value);

    // get and set for actual used values
    SequenceNumberType sequenceNumber() const;
    SequenceNumberType sequenceNumber(const BAS::String & key) const;
    void               sequenceNumber(const SequenceNumberType & value);

    SequenceNumberType originalSequenceNumber();

    SequenceNumberType actualSequenceNumber();

    BAS::String gapSequenceNumbers();

    /** Returns a comma separated string with sequence gap list, for the given key 
    */
    BAS::String gapSequenceNumbers(const BAS::String & key);

    /** Returns a comma separated string with sequence gap list, for the given key, 
    * excluding the sequence number associated with the passed transId
    */
    BAS::String excludeGapSequenceNumbers(const BAS::String & key, const TAM::TransId & transId);//gapseqnum excluding the transId
    bool removeAllGapSequenceNumbers(const TAM::TransId & transId);

    SequenceNumberType offset() const;
    SequenceNumberType offset(const BAS::String & key);
    void               offset(const SequenceNumberType & value);

    // get and set for max and min values
    SequenceNumberType maxSequenceNumber() const;
    SequenceNumberType maxSequenceNumber(const BAS::String & key) const;
    void maxSequenceNumber(SequenceNumberType value);

    SequenceNumberType minSequenceNumber() const;
    SequenceNumberType minSequenceNumber(const BAS::String & key) const;
    void minSequenceNumber(SequenceNumberType value);

    SequenceNumberType maxOffset() const;
    SequenceNumberType maxOffset(const BAS::String & key) const;
    void maxOffset(SequenceNumberType value);

    SequenceNumberType minOffset() const;
    SequenceNumberType minOffset(const BAS::String & key) const;
    void minOffset(SequenceNumberType value);

    void seqKeyAsStr(const BAS::String& value);

    // insert new key into the database!
    virtual bool insertIntoDatabase(const BAS::String & key);
    
    // get container indizes
    EDR::Index streamNameIdx() const;
    EDR::Index seqNumOrigIdx() const;
    EDR::Index seqNumBuildIdx() const;

    // get the container generation and check values
    size_t edrSeqGeneration() const;
    size_t edrSeqCheck() const;
    size_t edrOffsetGeneration() const;
    size_t edrSingleProcess() const;

    // set the sequence string information
    void seqNumberAsStr(const BAS::String& value);
    void seqOrigNumberAsStr(const BAS::String& value);
    void seqGapNumberAsStr(const BAS::String& value);
    void seqOffsetAsStr(const BAS::String& value);
    void seqMaxSequenceAsStr(const BAS::String& value);
    void seqMaxOffsetAsStr(const BAS::String& value);
    void seqMinSequenceAsStr(const BAS::String& value);
    void seqMinOffsetAsStr(const BAS::String& value);

    // Actual used values.
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      sequenceNumberM;

    bool reUseGapM;

  private: 

    // not implemented
    SequenceControl(SequenceControl&);
    void operator=(const SequenceControl&);


    // Last used values.
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      lastTransactionOriginalSequenceNumberM;
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      lastOriginalSequenceNumberM;
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      lastOffsetM;

    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      originalSequenceNumberM;

    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      offsetM;

    // Maximum values.
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      maxSequenceNumberM;
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      maxOffsetM;

    // Minimum values.
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      minSequenceNumberM;
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      minOffsetM;

    // actuall sequencenumber
    RWTValMap< BAS::String, SequenceNumberType, less<BAS::String> > 
      actualSequenceNumberM;

    RWTValMultiMap<TAM::TransId, SequenceNumberTypeS, less<TAM::TransId> > 
      gapSequenceNumberListM;

    // Activation flags.
    bool checkIsActiveM;
    bool generateIsActiveM;
    bool useGapAtStartupM;
    bool roamingFlagM;
    
    // sequence name
    BAS::String sequencerNameM;

    // indices for conatiner access
    EDR::Index headerSequenceNumberIdxM;
    EDR::Index streamTransIdIdxM;
    EDR::Index streamNameIdxM;

    // values from the edr container
    size_t edrSeqGenerationM;
    size_t edrSeqCheckM;
    size_t edrOffsetGenerationM;

    // length in digits of the generated seqencenumber!
    int32 seqLengthM;

    // sequence information as strings
    BAS::String seqKeyAsStrM;
    BAS::String seqNumberAsStrM;
    BAS::String seqOrigNumberAsStrM;
    BAS::String seqGapNumberAsStrM;
    BAS::String seqOffsetAsStrM;
    BAS::String seqMaxSequenceAsStrM;
    BAS::String seqMaxOffsetAsStrM;
    BAS::String seqMinSequenceAsStrM;
    BAS::String seqMinOffsetAsStrM;

    // Sequencer registry string(s).
    PLG_EXPORT static const BAS::String registryPipelinesCM;
    PLG_EXPORT static const BAS::String sequenceLengthCM;
    PLG_EXPORT static const BAS::String registrySequenceReuseGapCM;
    PLG_EXPORT static const BAS::String registrySequencerTypeCM;    
    PLG_EXPORT static const BAS::String registrySequenceLogTimeoutCM;
    PLG_EXPORT static const BAS::String registryUseGapAtStartupCM;
    PLG_EXPORT static const BAS::String registryRoamingFlagCM;
    
    RWTValMultiMap < TAM::TransId, SequencerInformation_In, less<TAM::TransId> > 
                   seqInfoList_InM;

    RWTValMultiMap < TAM::TransId, SequencerInformation, less<TAM::TransId> > 
                   seqInfoListM;

    BAS::String seqKeyM;
};

//------------------------------------------------------------------------------
// Convenience typedef(s).
//------------------------------------------------------------------------------
typedef BAS::OnlyPointer<SequenceControl> SequenceControlPtr;

//------------------------------------------------------------------------------
// get check and deneration flag
//------------------------------------------------------------------------------
inline bool 
SequenceControl::checkIsActive() const
{
  return checkIsActiveM;
}                   

inline bool 
SequenceControl::generateIsActive() const
{
  return generateIsActiveM;
}                   

//------------------------------------------------------------------------------
// get and set for last used values
//------------------------------------------------------------------------------
inline SequenceNumberType 
SequenceControl::lastOffset() const
{
  SequenceNumberType value;
  if (lastOffsetM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline void 
SequenceControl::lastOffset(SequenceNumberType value)
{
  lastOffsetM[seqKeyM] = value;
}

//------------------------------------------------------------------------------
// get and set for actual used values
//------------------------------------------------------------------------------
inline SequenceNumberType 
SequenceControl::sequenceNumber() const
{
  SequenceNumberType value;
  if (sequenceNumberM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline void 
SequenceControl::sequenceNumber(const SequenceNumberType & value) 
{
  sequenceNumberM[seqKeyM] = value;
}

inline SequenceNumberType 
SequenceControl::sequenceNumber(const BAS::String & key) const
{
  SequenceNumberType value;
  if (sequenceNumberM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline SequenceNumberType 
SequenceControl::offset() const
{
  SequenceNumberType value;
  if (offsetM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline SequenceNumberType 
SequenceControl::offset(const BAS::String & key)
{
  SequenceNumberType value;
  if (offsetM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline void 
SequenceControl::offset(const SequenceNumberType & value)
{
  offsetM[seqKeyM] = value;
}

inline void 
SequenceControl::lastOriginalSequenceNumber(SequenceNumberType value)
{
  lastOriginalSequenceNumberM[seqKeyM] = value;
}

//==============================================================================
// Set ogiginal sequence number
//==============================================================================
inline SequenceNumberType 
SequenceControl::lastOriginalSequenceNumber() const
{
  SequenceNumberType value;
  if (lastOriginalSequenceNumberM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

//==============================================================================
// Set original sequence number
//==============================================================================
inline void 
SequenceControl::originalSequenceNumber(const SequenceNumberType& num)
{
  originalSequenceNumberM[seqKeyM] = num;
}
               
//==============================================================================
// Set original sequence number
//==============================================================================
inline SequenceNumberType 
SequenceControl::originalSequenceNumber()
{
  D_ENTER("PLG::SequenceControl::originalSequenceNumber(const TAM::TransId & transIf) const");

  return originalSequenceNumberM[seqKeyM];
}

inline SequenceNumberType
SequenceControl::lastOriginalSequenceNumber(const BAS::String& key)
{
  SequenceNumberType value;
  if (lastOriginalSequenceNumberM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

//==============================================================================
// Set ogiginal sequence number
//==============================================================================
inline void 
SequenceControl::conv_originalSequenceNumber(const BAS::String& num)
{
  SequenceNumberType tmpSeqNumber = 0;
  num.toNum(tmpSeqNumber); // Stays 0 if the conversion fails.
  originalSequenceNumber(tmpSeqNumber);
}

inline SequenceNumberType
SequenceControl::originalSequenceNumber(const BAS::String& key)
{
  SequenceNumberType value;
  if (originalSequenceNumberM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

//------------------------------------------------------------------------------
// get and set for max and min values
//------------------------------------------------------------------------------
inline SequenceNumberType 
SequenceControl::maxSequenceNumber() const
{
  SequenceNumberType value;
  if (maxSequenceNumberM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline SequenceNumberType 
SequenceControl::maxSequenceNumber(const BAS::String& key) const
{
  SequenceNumberType value;
  if (maxSequenceNumberM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline void 
SequenceControl::maxSequenceNumber(SequenceNumberType value)
{
  maxSequenceNumberM[seqKeyM] = value;
}

inline SequenceNumberType 
SequenceControl::minSequenceNumber() const
{
  SequenceNumberType value;
  if (minSequenceNumberM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline SequenceNumberType 
SequenceControl::minSequenceNumber(const BAS::String& key) const
{
  SequenceNumberType value;
  if (minSequenceNumberM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline void 
SequenceControl::minSequenceNumber(SequenceNumberType value)
{
  minSequenceNumberM[seqKeyM] = value;
}

inline SequenceNumberType 
SequenceControl::maxOffset() const
{
  SequenceNumberType value;
  if (maxOffsetM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline SequenceNumberType 
SequenceControl::maxOffset(const BAS::String& key) const
{
  SequenceNumberType value;
  if (maxOffsetM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline void 
SequenceControl::maxOffset(SequenceNumberType value)
{
  maxOffsetM[seqKeyM] = value;
}

inline SequenceNumberType 
SequenceControl::minOffset() const
{
  SequenceNumberType value;
  if (minOffsetM.findValue(seqKeyM, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline SequenceNumberType 
SequenceControl::minOffset(const BAS::String& key) const
{
  SequenceNumberType value;
  if (minOffsetM.findValue(key, value))
  {
    return value;
  }
  else
  {
    return 0;
  }
}

inline void 
SequenceControl::minOffset(SequenceNumberType value)
{
  minOffsetM[seqKeyM] = value;
}

//------------------------------------------------------------------------------
// get pipeline name
//------------------------------------------------------------------------------
inline const 
BAS::String& SequenceControl::sequencerName() const
{
  return sequencerNameM;
}

//------------------------------------------------------------------------------
// get container indizes
//------------------------------------------------------------------------------
inline EDR::Index 
SequenceControl::streamNameIdx() const
{
  return streamNameIdxM;
}

//------------------------------------------------------------------------------
// get the container generation and check values
//------------------------------------------------------------------------------
inline size_t
SequenceControl::edrSeqGeneration() const
{
  return edrSeqGenerationM;
}

inline size_t
SequenceControl::edrSeqCheck() const
{
  return edrSeqCheckM;
}

inline size_t
SequenceControl::edrOffsetGeneration() const
{
  return edrOffsetGenerationM;
}

//------------------------------------------------------------------------------
// set the sequence string information
//------------------------------------------------------------------------------
inline void 
SequenceControl::seqNumberAsStr(const BAS::String& value)
{
  seqNumberAsStrM = value;
}

inline void 
SequenceControl::seqOrigNumberAsStr(const BAS::String& value)
{
  seqOrigNumberAsStrM = value;
}

inline void 
SequenceControl::seqGapNumberAsStr(const BAS::String& value)
{
  seqGapNumberAsStrM = value;
}

inline void 
SequenceControl::seqOffsetAsStr(const BAS::String& value)
{
  seqOffsetAsStrM = value;
}

inline void 
SequenceControl::seqMaxSequenceAsStr(const BAS::String& value)
{
  seqMaxSequenceAsStrM = value;
}

inline void 
SequenceControl::seqMaxOffsetAsStr(const BAS::String& value)
{
  seqMaxOffsetAsStrM = value;
}

inline void 
SequenceControl::seqMinSequenceAsStr(const BAS::String& value)
{
  seqMinSequenceAsStrM = value;
}

inline void 
SequenceControl::seqMinOffsetAsStr(const BAS::String& value)
{
  seqMinOffsetAsStrM = value;
}

inline void 
SequenceControl::seqKeyAsStr(const BAS::String& value)
{
  seqKeyM = value;
}

inline size_t
SequenceControl::seqLength()
{
  return seqLengthM;
}

inline bool 
SequenceControl::insertIntoDatabase(const BAS::String & key)
{
  return true;
}
//------------------------------------------------------------------------------
}
#endif 
