//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD/TAP3
//------------------------------------------------------------------------------
// Module Description:
//   Input grammar file for the TAP3_v10 CDR format
//
//______________________________________________________________________________
//______________________________________________________________________________
// Revision       14-Sep-2005   7.2_Patch   knijhawa
// PRSF00181931   Supporting optional field CallReference
//
// Revision       19-May-2004   6.7_FP2   rvemuri
// PRSF00112149   Change TP type to 695 from 690 as DP uses 690.
//
// Revision       22-Jul-2003   6.5_SP1_EBF   njalel, keshav
// PRSF00051843   Add TAP3 changes.
//
// Log 2003/04/11 pgeiger
// - Creation
//
//==============================================================================


//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  use EXT_Converter; //used for number normalization
  include "RAP_v01_FatalReturn.dsc";
//setenv ISCRIPT_INCLUDE "/vobs/integrate_all_vob/integrate_all/integrate/Implementation/FMD/Formats/TAP3;."

  // for statistics and debug printouts
  Date startTime;
  Date stopTime;
  String  msgBuffer;
  Bool    checkForBatchRejectFlag;

  // default values
  Date         defLocalTime     = MIN_DATE;
  String       defLocalTimeStamp= dateToStr(MIN_DATE);
  String       defTelNumber     = "000";
  const String defUtcTimeOffset = "+0000";
  const String defCauseForTerm  = "00";

  // constants
  const Long record_Header =11;
  const Long record_Trailer=12;
  const Long record_MOC    =1;
  const Long record_MTC    =2;
  const Long record_MSS    =3;
  const Long record_SCU    =4;
  const Long record_VAS    =5;
  const Long record_CONT   =6;
  const Long record_GPRS   =7;
  const Long record_LOCN   =8;
  Long       record_Type   =0; // use to know which type of detail we are reading

  // constants
  const Long service_Basic   =1;
  const Long service_Camel   =2;
  const Long service_Gprs    =3;
  const Long service_Suppl   =4;
  const Long service_Vas     =5;
  const Long service_Content =6;
  const Long service_Location=7;
  Long       service_Type    =0; // use to know which type of service we are reading

  // constants
  const String type_HEADER        ="010";
  const String type_TRAILER       ="090";
  const String type_MOC           ="021";
  const String type_MSS           ="029";
  const String type_MTC           ="031";
  const String type_GPRS_SG       ="040";
  const String type_GPRS_GG       ="042";
  const String type_GPRS_assembled="042"; //default for mixed ticket
  const String type_GPRS          ="042"; //default is mixed ticket
  const String type_SCU           ="050";
  const String type_VAS           ="060";
  const String type_CONT          ="070";
  const String type_LOCN          ="080";

  // constants
  const String extension_GSMW     ="520";
  const String extension_GPRS     ="540";
  const String extension_CONT     ="550";
  const String extension_LOCN     ="560";
  const String extension_SS_EVENT ="620";
  const String extension_BS_EVENT ="630";
  const String extension_CP       ="680";
  const String extension_TAP	  ="670";
  const String extension_TP	  ="695";
  const String extension_CAMEL    ="700";
  const String extension_VAS      ="710";
  const String extension_CBD      ="980"; //default CBD is global charge

  //constants
  const Long callOriginatorType    =1;
  const Long callDestinationType   =2;
  const Long nonChargedPartyType   =3;
  const Long thirdPartyType        =4;
  const Long camelCallReferenceType=5;
  const Long camelDestinationType  =6;
  const Long camelServerType       =7;
  Long       callNumberType        =0; // use to know which type of number we are reading

  //file level timestamps
  const Long earliestCallTimeStampType     =10;
  const Long latestCallTimeStampType       =11;
  const Long fileAvailableTimeStampType    =12;
  const Long fileCreationTimeStampType     =13;
  const Long transferCutOffTimeStampType   =14;
  //record level timestamps but not used
  const Long hscsdModificationTimestampType=20;
  const Long pDPContextStartTimestampType  =21;
  const Long orderPlacementTimeStampType   =22;
  const Long requestedDeliveryTimeStampType=23;
  const Long actualDeliveryTimeStampType   =24;
  const Long lCSRequestTimeStampType       =25;

  //record level timestamps
  const Long callEventStartTimeStampType   =1; // at the tap3detail level
  const Long chargingTimeStampType         =2; // at the service level
  const Long chargeDetailTimeStampType     =3; // at the chargeDetail level
  const Long scuDepositTimeStampType       =4;
  const Long scuCompletionTimeStampType    =5;
  Long       timeStampType                 =0; // use to know which type of timestamp we are reading

  // for split details
  Long chainReference;
  Long theLastEdrCopy; // index on copy

  // block counters
  Long records;
  Long related_record;
  Long related_info_id;
  Long tap3Detail;
  Long details;
  Long successiveBasicServiceUsed;
  Long successiveChargeInformation;
  Long successiveChargeInformationPerBS;
  Long successiveChargeDetail;
  Long successiveTaxDetail;
  Long successiveChargePacket;
  Long successiveTaxPacket;
  Long successiveChargePacketCI;

  // block type identifier
  Long    blockType;
  // block type identifier constants
  const Long advisedChargeInfoBlockType     =  1;
  const Long chargedPartyHomeBlockType      =  2;
  const Long chargedPartyLocnBlockType      =  3;
  const Long contentProviderBlockType       =  4;
  const Long lCSSPIdBlockType               =  5;
  const Long trackedCustomerEqptBlockType   =  6;
  const Long trackedCustomerHomeBlockType   =  7;
  const Long trackedCustomerIdBlockType     =  8;
  const Long trackedCustomerLocnBlockType   =  9;
  const Long trackingCustomerEqptBlockType  = 10;
  const Long trackingCustomerHomeBlockType  = 11;
  const Long trackingCustomerIdBlockType    = 12;
  const Long trackingCustomerLocnBlockType  = 13;
  const Long chargedPartyEquipmentBlockType = 14;
  const Long gprsServiceUsageBlockType      = 15;
  const Long lCSSPInfoBlockType             = 16;
  const Long servingPartiesInfoBlockType    = 17;
  const Long gprsServiceUsedBlockType       = 18;

  // for storage of Header/Trailer/Notification values
  String  theSender;
  String  theRecipient;
  Long    theTap3SpecificationVersionNumber;
  Long    theTap3ReleaseVersionNumber;
  Long    theFileSeqNum;
  Long    theOrigFileSeqNum;
  String  theFileCreationTimeStamp;
  String  theFileCreationUtcTimeOffset;
  String  theFileAvailableTimeStamp;
  String  theFileAvailableUtcTimeOffset;
  String  theTransferCutOffTimeStamp;
  String  theTransferCutOffUtcTimeOffset;
  String  theFileTypeIndicator;
  Decimal theTotalChargedValue;
  Decimal theTotalTaxValue;
  Decimal theTotalDiscountValue;
  Decimal theTotalChargedValue_00;
  String  lastTotalChargeValueChargeType;
  Decimal lastTotalChargeValueAbsoluteAmount;
  Long    theSenderNetworkType;
  String  theLocalCurrency;
  Bool    theLocalCurrencyIsMissing;
  String  theTapCurrency;
  Long    theTapDecimalPlaces;
  Decimal theAbsoluteAmountDivider;

  // runtime data storage
  String lastLocalTimeStamp;
  String lastUtcTimeOffset;
  String lastValidLocalTimeStamp;
  String lastValidUtcTimeOffset;
  Long   lastCalledNumAnalysisCode;
  String lastCalledNumberAnalysisCC;
  String lastCalledNumberAnalysisIAC;
  Long   lastCode; // for initialisation lists in TAP3 header
  String lastBasicService;
  String lastBasicDualService;
  String last_ipAddress;

  String lastChannelCoding;

  // for Value Added Services
  String lastVasShortDescrList;
  Long   lastVasCode;
  String lastVasLocalTimeStamp;
  String lastVasUtcTimeOffset;

  // for supplementary services in MOC and MTC, to know wehere to add SS_PACKETS
  String lastSupplServiceEventCode;
  String lastSupplServiceActionCode;
  String SsBasicServicesAffected[];
  Long   SsBasicServicesAffectedNb;
  String lastbasicServiceCodeSS;

  // for GPRS Service usage
  String  lastRemotePdpAddressList;
  String  lastAPN;
  Decimal sumDataVolumeIncoming;
  Decimal sumDataVolumeOutgoing;
  Long    SGSNidx;

  // for CAMEL Service
  String lastCamelModificationList;

  // store value from ChargeInformation Block
  String  lastChargedItem;
  Decimal lastExchangeRateFactor;
  Decimal lastExchangeRateFactorValue;
  String  lastChargeType;
  Decimal lastCharge;
  Long    lastChargeableUnits;
  String  lastChargeableUnitsUoM; // not really a collected value, built out from lastChargedItem
  Long    sumChargedUnitsCI;
  Long    sumChargeableUnitsCI;
  Long    sumChargeableUnitsDuration;
  Long    sumChargeableUnitsVolumeSent;
  Long    sumChargeableUnitsVolumeReceived;
  Long    sumChargeableUnitsEvents;
  Long    sumChargeableUnitsEventsBS;
  Long    lastChargedUnits;
  String  lastChargeDetailTimeStamp;
  Long    lastTaxRate;
  Decimal lastTaxCharge;
  Decimal sumTaxChargeEDR;
  Decimal sumTaxChargeBS;
  Decimal sumTaxChargeFile;
  Decimal sumTaxChargeFileAll;
  Decimal sumTaxChargeCI;
  Decimal sumTaxAmountCI;
  Long    lastDiscountCode;
  Decimal lastDiscountValue;
  Decimal lastDiscountValueCI;       // ChargeInformation block level Discount Value
  Decimal sumDiscountValueFile;      // Tap3 File Level Discount Value sum
  Decimal sumChargedAmountValueEDR;  // EDR level sum
  Decimal sumChargedAmountValueBS;   // BS level sum
  Decimal sumChargedAmountValueFile; // Tap3 File level sum
  Decimal sumChargedAmountValueCI;   // ChargeInformation block level sum

  Long    CPidx;
  Long    TPidx;
  Long    ssPacketIdx;
  Long    gsPacketIdx;
  Long    bsPacketIdx;
  Long    lastCPidx_00;
  Long	  ACBidx;
  Long	  pmidx;
  Long	  vasidx;
  Long	  tcvidx;
  Decimal lastChargedAmountValue_00;
  Long    lastChargeableUnits_00;
  Long    lastChargedUnits_00;

  // block counters
  Long    chargedPartyHomeIdx;
  Long    chargedPartyIdIdx;
  Long    chargedPartyLocnIdx;
  Long    contentProviderIdx;
  Long    contentSvcUsedIdx;
  Long    internetSvcProvIdx;
  Long    lcsspIdx;
  Long    networkIdx;
  Long    trackedCustHomeIdx;
  Long    trackedCustIdx;
  Long    trackedCustLocnIdx;
  Long    trackingCustHomeIdx;
  Long    trackingCustIdx;
  Long    trackingCustLocnIdx;

  // calledNumberAnalysis
  Long   calledNumberAnalysisEntries;
  Long   calledNumberAnalysisCode[];
  String calledNumberAnalysisCC[];
  String calledNumberAnalysisIAC[];
  String calledNumberAnalysisCCarray[][];
  String calledNumberAnalysisIACarray[][];
  Long   lastCcIdx;
  Long   lastIacIdx;

  // taxation
  Long   taxEntries;
  Long   taxCode[];
  String taxType[];
  String taxRate[];

  // discounting
  Long discountEntries;
  Long discountCode[];
  Long discountApplied_Type[]; // discountApplied_discountRate/discountApplied_fixedDiscountValue
  Long discountApplied_discountRate;
  Long discountApplied_fixedDiscountValue;
  Long discountApplied[];

  // currencyConversion
  Long currencyEntries;
  Long exchangeRateCode[];
  Long numberOfDecimalPlaces[];
  Long exchangeRate[];
  Decimal exchangeRateFactor[]; //calculated value

  // utcTimeOffsetInfo
  Long   utcTimeOffsetEntries;
  Long   utcTimeOffsetCode[];
  String utcTimeOffset[];

  // recEntityInfo
  Long   recEntityEntries;
  Long   recEntityCode[];
  Long   recEntityType_MSC;
  Long   recEntityType_SMSC;
  Long   recEntityType_GGSN;
  Long   recEntityType_SGSN;
  Long   recEntityType_GMLC;
  Long   recEntityType_WLAN;

  Long   recEntityType[];
  Long   recEntityId_Type[]; // recEntityId_gmlcAddress/recEntityId_mscId/recEntityId_msisdn/recEntityId_iPTextV4Address/recEntityId_iPTextV6Address
  Long   recEntityId_gmlcAddress;
  Long   recEntityId_mscId;
  Long   recEntityId_msisdn;
  Long   recEntityId_iPTextV4Address;
  Long   recEntityId_iPTextV6Address;
  String recEntityId[];
  Long   last_recEntityId_Type; // used for intermediate storage
  String last_recEntityId;      // used for intermediate storage
  Long   theRecEntityType;      // used at runtime
  String theRecEntityId;       // used at runtime

  // vasInfo
  Long   vasEntries;
  Long   vasCode[];
  String vasShortDesc[];
  String vasDesc[];

  // messageDescriptionInfo
  Long   messageDescriptionEntries;
  Long   messageDescriptionCode[];
  String messageDescription[];

  //registry string where to find user configurable values
  String reg_TapPipeline;
  String reg_TapIOModule;
  String reg_InputStream;
  String reg_RapSequencer;
  String reg_OriginCountryCode;
  String reg_SenderCountryCode;
  String reg_UseLocalCurrency;
  String reg_InternationalAccessCode;

  // storage of registry values
  String strRapSequencer;
  String strOriginCountryCode;
  String strSenderCountryCode;
  String strIAC;
  Bool   bUseLocalCurrency;

  // Validation variables
  Bool recEntityCodeIsMissing;
  Bool recEntityTypeIsMissing;
  Bool recEntityIdIsMissing;
  Bool numberOfChannelsUsedIsMissing;
  Bool qoSDelayIsMissing;
  Bool qoSMeanThroughputIsMissing;
  Bool qoSPeakThroughputIsMissing;
  Bool qoSPrecedenceIsMissing;
  Bool qoSReliabilityIsMissing;
  Bool chargedPartyStatusIsMissing;
  Bool nonChargedPartyIsMissing;
  Bool messageStatusIsMissing;
  Bool priorityCodeIsMissing;
  Bool messageTypeIsMissing;
  Bool messageDescriptionCodeIsMissing;
  Bool depositTimeStampIsMissing;
  Bool completionTimeStampIsMissing;
  Bool taxCodeIsMissing;
  Bool taxTypeIsMissing;
  Bool taxValueIsMissing;
  Bool totalChargeTypeIsMissing;
  Bool absoluteAmountIsMissing;
  Bool homeIdTypeIsMissing;
  Bool homeIdentifierIsMissing;
  Bool utcTimeOffsetCodeIsMissing;
  Bool utcTimeOffsetIsMissing;
  Bool vasCodeIsMissing;
  Bool vasShortDescriptionIsMissing;
  Bool imsiIsMissing;
  Bool taxableAmountIsMissing;
  Bool taxationListIsMissing;
  Bool exchangeRateCodeIsMissing; // For checking the empty condition of ExchangeRateCode of ChargeInformation
  Bool destinationIsMissing;      // Flag to check the missing condition of Destination field.
  Bool chargeType00IsMissing;     // Flag to check the missing condition of Total Charge Value with Charge Type of "00"


  // Error processing for Batch Reject
  String toReturn_StreamName    ="";
  String toReturn_ErrFileName   ="";
  String toReturn_RetFileName   ="";
  String toReturn_RetTmpFileName="";
  String toReturn_Sender        ="";
  String toReturn_Recipient     ="";
  String toReturn_RapSeqNum     ="";
  String toReturn_TapSeqNum     ="";
  Long   toReturn_ObjTag        = 0;
  Long   toReturn_ArrayIdx      =-1;
  Long   toReturn_ObjDepth      = 0;
  Long   toReturn_ObjOffset     = 0;
  Long   toReturn_ErrCode       = 0;

  // Error processing
  const Long beginTap3Header            = 1;
  const Long beginTap3Notification      = 2;
  const Long endTap3Notification        = 3;
  const Long beginTap3BatchControlInfo  = 4;
  const Long endTap3BatchControlInfo    = 5;
  const Long beginTap3AccountingInfo    = 6;
  const Long endTap3AccountingInfo      = 7;
  const Long beginTap3NetworkInfo       = 8;
  const Long endTap3NetworkInfo         = 9;
  const Long beginTap3VasInfo           =10;
  const Long endTap3VasInfo             =11;
  const Long beginTap3MessageDescrInfo  =12;
  const Long endTap3MessageDescrInfo    =13;
  const Long endTap3Header              =14;
  const Long beginTap3DetailList        =15;
  const Long beginTap3Detail            =16;
  const Long endTap3Detail              =17;
  const Long endTap3DetailList          =18;
  const Long beginTap3AuditControlInfo  =19;
  const Long endTap3AuditControlInfo    =20;
  Long       errorStateTap3             = 0;

  //Following are index keys for GeographicalLocation fields
  const String servingNetworkKey        = "1";
  const String servingBIDKey            = "2";
  const String servingLocationDescKey   = "3";
  const String longitudeKey             = "4";
  const String latitudeKey              = "5";

  String geographicalLocation;

  // Following are index keys for UMTSQosRequeseted/Used
  const String QosTrafficClassKey                     = "1";
  const String QosMaxBitRateUpLnKey                   = "2";
  const String QosMaxBitRateDownLnKey                 = "3";
  const String QosGuaranteedBitRateDownLnKey          = "4";
  const String QosGuaranteedBitRateUpLnKey            = "5";
  const String QosAllocRetenPriorityKey               = "6";

  String strUMTSQosReqOrUsed;


  /***************************************************************************
   * function onParseError
   ***************************************************************************/
  function onParseError //this function is only called with integrate v4-40-xx
  {
    // Error processing
    String errorBlockName;
    switch (errorStateTap3)
    {
      case beginTap3Header:             errorBlockName = "one of the TAP3 Header Blocks";break;
      case beginTap3Notification:       errorBlockName = "Notification Block";          break;
      case beginTap3BatchControlInfo:   errorBlockName = "BatchControlInfo Block";      break;
      case beginTap3AccountingInfo:     errorBlockName = "AccountingInfo Block";        break;
      case beginTap3NetworkInfo:        errorBlockName = "NetworkInfo Block";           break;
      case beginTap3VasInfo:            errorBlockName = "VasInfo Block";               break;
      case beginTap3MessageDescrInfo:   errorBlockName = "MessageDescrInfo Block";      break;
      case beginTap3DetailList:         errorBlockName = "CallEventDetails Block";      break;
      case beginTap3AuditControlInfo:   errorBlockName = "AuditControlInfo Block";      break;

      case beginTap3Detail:
        errorBlockName = "Tap3Detail Block #"+longToStr(tap3Detail)+" (ifw EDR #"+longToStr(details)+")";
      break;

      default:
        errorBlockName = "TAP3 Block, errorStateTap3="+longToStr(errorStateTap3);
      break;
    }

    logPipeline("TAP3_ERROR on "+errorBlockName+", at BytePos @"+longToStr(ERROR_TOKEN_BYTEPOS)+
                " (ie. @0x"+longToHexStr(ERROR_TOKEN_BYTEPOS)+
                "), Token hex content=<"+ERROR_TOKEN_ASC+">", 3);
  }

  /***************************************************************************
   * function onParseStart
   ***************************************************************************/
  function onParseStart
  {
    lexState("STATE_TAP3");
  }

  /***************************************************************************
   * function onRollback
   ***************************************************************************/
  function Bool onRollback
  {
    String transID      = decimalToStr( tamTransId() );
    Long   nbTransItems = tamNumTransItems();
    String sendArray[];
    String receiveArray[];

    msgBuffer="ROLLBACK: called in TAP3 input for transID("+transID+
              "), we have the stream("+toReturn_StreamName+
              ") which is waiting for this rollback";
//logStdout(msgBuffer+"\n");

    // set defaults for the fields that we must request from other modules
    toReturn_ErrFileName    = "";
    toReturn_RetFileName    = "";
    toReturn_RetTmpFileName = "";
    toReturn_RapSeqNum      = "";
    toReturn_StreamName     = CURRENT_STREAM_NAME;

    // get the real name of the rollbacked files that need to be post-processed
    //-------------------------------------------------------------------------
    if (toReturn_StreamName != "")
    {
      Long   i;
      // first, make sure it is really part of this transaction!
      for ( i=0; i<nbTransItems; i=i+1 )
      {
        if ( tamStreamName(i) == toReturn_StreamName )
        {
          // get the error filename
          arrayClear( sendArray    );
          arrayClear( receiveArray );
          sendArray[0] = toReturn_StreamName ;
          if ( reqSend( reg_InputStream, "REQ_ERROR_FILENAME",
                        sendArray, receiveArray)==true )
          {
            toReturn_ErrFileName = receiveArray[0];
            if (toReturn_ErrFileName == toReturn_StreamName)
            {
              toReturn_ErrFileName = "";
            }
          }
          //get the return filename
          arrayClear( sendArray    );
          arrayClear( receiveArray );
          sendArray[0] = toReturn_StreamName ;
          if ( reqSend( reg_InputStream, "REQ_RETURN_FILENAME",
                        sendArray, receiveArray)==true )
          {
            toReturn_RetFileName = receiveArray[0];
            if (toReturn_RetFileName == toReturn_StreamName)
            {
              toReturn_RetFileName = "";
            }
          }
          //get the temporary return filename
          arrayClear( sendArray    );
          arrayClear( receiveArray );
          sendArray[0] = toReturn_StreamName ;
          if ( reqSend( reg_InputStream, "REQ_RETURN_TEMP_FILENAME",
                        sendArray, receiveArray)==true )
          {
            toReturn_RetTmpFileName = receiveArray[0];
            if (toReturn_RetTmpFileName == toReturn_StreamName)
            {
              toReturn_RetTmpFileName = "";
            }
          }

          msgBuffer="ROLLBACK: stream(" +toReturn_StreamName+
                  "), ErrorFile(" +toReturn_ErrFileName+
                  "), ReturnFile(" +toReturn_RetFileName+
                  "), ReturnTmpFile(" +toReturn_RetTmpFileName+")";
          logPipeline(msgBuffer, 0);
//logStdout(msgBuffer+"\n");
        }
      }

      // Get a new Rap sequence number
      //------------------------------
      if (toReturn_RetFileName != "")
      {
        arrayClear( sendArray    );
        arrayClear( receiveArray );
        sendArray[0] = transID;
        sendArray[1] = "00000"; //TODO- how to get the last used RAP seq Num?
	sendArray[2] = theSender;
        if (strRapSequencer != "")
        {
          if ( reqSend(strRapSequencer, "REQ_NEWSEQUENCENUMBER",
                       sendArray, receiveArray)==true )
          {
            toReturn_RapSeqNum = receiveArray[0];
            msgBuffer="ROLLBACK: the input TapSequence(" +toReturn_TapSeqNum+
                      ") is sent back in RAP with a RapSequence(" +toReturn_RapSeqNum+")";
//logStdout(msgBuffer+"\n");
          }
          else // reqSend(strRapSequencer ....)
          {
            msgBuffer="ROLLBACK: the input TapSequence("+toReturn_TapSeqNum+
                      ") could NOT get a RapSequence";
            logPipeline(msgBuffer, 1);
//logStdout(msgBuffer+"\n");
          }
        }

        if (toReturn_RapSeqNum != "")
        {
          //build the returned RAP file
          writeRapFile( toReturn_RetTmpFileName,
                        toReturn_Sender,
                        toReturn_Recipient,
                        strToLong(toReturn_RapSeqNum),
                        sysdate(),             //Date    creationTime,
                        defUtcTimeOffset,      //String  headerUtcTimeOffset,  //TODO
                        theTap3SpecificationVersionNumber,
                        theTap3ReleaseVersionNumber,
                        1,     //Long    rapSpecNo,
                        1,     //Long    rapRelNo,
                        " ",   //String  typeInd,
                        strToLong(toReturn_TapSeqNum),
                        0,     //Long    totRetCharge,
                        0,     //Long    rapDetWritten,
                        toReturn_ObjTag,       //Long    pathItemId,
                        toReturn_ArrayIdx,     //Long    arrayIndex,
                        toReturn_ObjDepth,     //Long    objDepth,
                        toReturn_ObjOffset,    //Long    objOffset,
                        toReturn_ErrCode        //Long    errorCode
                        );
          fileRename(toReturn_RetTmpFileName, toReturn_RetFileName);

          msgBuffer="ROLLBACK: Returned stream("+toReturn_StreamName+
                    ") as RAPfile("+toReturn_RetFileName+
                    ") using sequence("+toReturn_RapSeqNum+") -DONE";
//logStdout(msgBuffer+"\n");

          //TODO decide what to do with the errFile (for now, it stays there)
        }
      }
    }

    //reinitialization for next time...
    toReturn_StreamName    ="";
    toReturn_ErrFileName   ="";
    toReturn_RetFileName   ="";
    toReturn_RetTmpFileName="";
    toReturn_Sender        ="";
    toReturn_Recipient     ="";
    toReturn_RapSeqNum     ="";
    toReturn_TapSeqNum     ="";
    toReturn_ObjTag        = 0;
    toReturn_ArrayIdx      =-1;
    toReturn_ObjDepth      = 0;
    toReturn_ObjOffset     = 0;
    toReturn_ErrCode       = 0;
    return true; //must return true if you dont want to stop integrate!
  }

  /***************************************************************************
   * function setAssociatedTapErr
   ***************************************************************************/
  function setAssociatedTapErr (String errorName , Long errorSeverity , 
  				String tapErrorCode , String tapErrorAppTag , String tapErrorDepth)
                                  
  {
    Long blockIndex;
    blockIndex = edrNumDatablocks(DETAIL.ASS_TAP3_ERR);
    if(edrAddDatablock(DETAIL.ASS_TAP3_ERR) == true){
      edrString(DETAIL.ASS_TAP3_ERR.RECORD_TYPE,blockIndex) =  extension_TAP;
      edrLong(DETAIL.ASS_TAP3_ERR.RECORD_NUMBER,blockIndex) = edrLong(DETAIL.RECORD_NUMBER);
      edrString(DETAIL.ASS_TAP3_ERR.ERROR_NAME,blockIndex) = errorName;
      edrLong(DETAIL.ASS_TAP3_ERR.ERROR_SEVERITY,blockIndex) = errorSeverity;
      edrString(DETAIL.ASS_TAP3_ERR.TAP3_ERROR_CODE,blockIndex) = tapErrorCode;
      edrString(DETAIL.ASS_TAP3_ERR.TAP3_ERROR_APPLICATION_TAG,blockIndex) = tapErrorAppTag;
      edrString(DETAIL.ASS_TAP3_ERR.TAP3_ERROR_DEPTH,blockIndex) = tapErrorDepth;
    }
  
    blockIndex = edrNumDatablocks(HEADER.ASS_TAP3_ERR);
    if(edrAddDatablock(HEADER.ASS_TAP3_ERR) == true){
      edrString(HEADER.ASS_TAP3_ERR.RECORD_TYPE,blockIndex) =  extension_TAP;
      edrLong(HEADER.ASS_TAP3_ERR.RECORD_NUMBER,blockIndex) = edrLong(HEADER.RECORD_NUMBER);
      edrString(HEADER.ASS_TAP3_ERR.ERROR_NAME,blockIndex) = errorName;
      edrLong(HEADER.ASS_TAP3_ERR.ERROR_SEVERITY,blockIndex) = errorSeverity;
      edrString(HEADER.ASS_TAP3_ERR.TAP3_ERROR_CODE,blockIndex) = tapErrorCode;
      edrString(HEADER.ASS_TAP3_ERR.TAP3_ERROR_APPLICATION_TAG,blockIndex) = tapErrorAppTag;
      edrString(HEADER.ASS_TAP3_ERR.TAP3_ERROR_DEPTH,blockIndex) = tapErrorDepth;
    }
  
    blockIndex = edrNumDatablocks(TRAILER.ASS_TAP3_ERR);
    if(edrAddDatablock(TRAILER.ASS_TAP3_ERR) == true){
      edrString(TRAILER.ASS_TAP3_ERR.RECORD_TYPE,blockIndex) =  extension_TAP;
      edrLong(TRAILER.ASS_TAP3_ERR.RECORD_NUMBER,blockIndex) = edrLong(TRAILER.RECORD_NUMBER);
      edrString(TRAILER.ASS_TAP3_ERR.ERROR_NAME,blockIndex) = errorName;
      edrLong(TRAILER.ASS_TAP3_ERR.ERROR_SEVERITY,blockIndex) = errorSeverity;
      edrString(TRAILER.ASS_TAP3_ERR.TAP3_ERROR_CODE,blockIndex) = tapErrorCode;
      edrString(TRAILER.ASS_TAP3_ERR.TAP3_ERROR_APPLICATION_TAG,blockIndex) = tapErrorAppTag;
      edrString(TRAILER.ASS_TAP3_ERR.TAP3_ERROR_DEPTH,blockIndex) = tapErrorDepth;
    }
  }

  /***************************************************************************
   * function requestBatchReject
   ***************************************************************************/
  function requestBatchReject(  Long ObjTag,
                                Long ArrayIdx,
                                Long ObjDepth,
                                Long ObjOffset,
                                Long ErrCode,
				String ErrName)
  {
    // get ObjTag, ObjDepth, ErrCode from the TAP3 specs
    // get ObjOffset by calling edrFieldTokenBytePos() [see doc in IXT module]
    // set ArrayIdx to (-1) by default if object is not part of an array [ie. SEQUENCE OF]

    if (checkForBatchRejectFlag == false)
    {
      // if it was not activated, do not allow a RAP return
      return;
    }

    toReturn_StreamName    = CURRENT_STREAM_NAME;
    //toReturn_ErrFileName   = "";                //must be requested in the onRollback() function
    //toReturn_RetFileName   = "";                //must be requested in the onRollback() function
    //toReturn_RetTmpFileName= "";                //must be requested in the onRollback() function
    toReturn_Sender        = theSender;
    toReturn_Recipient     = theRecipient;
    //toReturn_RapSeqNum     = "";                //must be requested in the onRollback() function
    toReturn_TapSeqNum     = longToStr(theFileSeqNum);
    toReturn_ObjTag        = ObjTag;
    toReturn_ArrayIdx      = ArrayIdx;
    toReturn_ObjDepth      = ObjDepth;
    toReturn_ObjOffset     = ObjOffset;
    toReturn_ErrCode       = ErrCode;

    String rejReason=   "TAP3 Batch Reject: stream("+toReturn_StreamName+
                        "), ObjTag("   +longToStr(toReturn_ObjTag)+
                        "), ArrayIdx(" +longToStr(toReturn_ArrayIdx)+
                        "), ObjDepth(" +longToStr(toReturn_ObjDepth)+
                        "), ObjOffset("+longToStr(toReturn_ObjOffset)+
                        "), ErrCode("  +longToStr(toReturn_ErrCode)+")";
    setAssociatedTapErr(ErrName, 4,longToStr(ErrCode) ,longToStr(ObjTag) ,longToStr(ObjDepth));
    edrAddError("ERR_INPUT_REQUEST_ROLLBACK", 4, rejReason);
  }

  /***************************************************************************
   * function BEGIN
   ***************************************************************************/
  function BEGIN
  {
    // activate RAP batch reject checks
    checkForBatchRejectFlag = true;

    // initialisation of some constant values
    //---------------------------------------
    reg_TapPipeline       = "ifw.Pipelines."+pipelineName();
    reg_TapIOModule       = registryNodeName();
    //logStdout("reg_TapIOModule(input) = "+reg_TapIOModule+"\n");

    reg_InputStream       = reg_TapIOModule + ".Module.InputStream.Module";
    reg_RapSequencer      = reg_TapIOModule + ".Sequencer";

    reg_OriginCountryCode = reg_TapPipeline + ".OriginCountryCode";
    reg_SenderCountryCode = reg_TapPipeline + ".SenderCountryCode";
    reg_UseLocalCurrency  = reg_TapPipeline + ".UseLocalCurrency";
    reg_InternationalAccessCode = reg_TapPipeline + ".InternationalAccessCode";

    strRapSequencer = regString(reg_RapSequencer);
    if (strRapSequencer != "")
    {
      strRapSequencer= "ifw.SequencerPool."+strRapSequencer;
    }
    strOriginCountryCode = regString(reg_OriginCountryCode);
    if (strOriginCountryCode == "")
    {
      strOriginCountryCode= "0049";
    }
    strSenderCountryCode = regString(reg_SenderCountryCode);
    if (strSenderCountryCode == "")
    {
      strSenderCountryCode= "0049";
    }
    strIAC = regString(reg_InternationalAccessCode);
    if (strIAC == "")
    {
      // log a warning message
      logPipeline(reg_InternationalAccessCode + "is not specified or is empty.", 1);
      //logStdout("The empty string \"\" will be used as the InternationalAccessCode\n");
    }
    bUseLocalCurrency = false;		//this is default if is not specified
    if ( strToUpper(regString(reg_UseLocalCurrency)) == "TRUE" )
    {
      bUseLocalCurrency = true;
    }

    discountApplied_discountRate       = 1;
    discountApplied_fixedDiscountValue = 2;

    recEntityType_MSC           = 1;
    recEntityType_SMSC          = 2;
    recEntityType_GGSN          = 3;
    recEntityType_SGSN          = 4;
    recEntityType_GMLC          = 5;
    recEntityType_WLAN          = 6;

    recEntityId_gmlcAddress     = 1;
    recEntityId_mscId           = 2;
    recEntityId_msisdn          = 3;
    recEntityId_iPTextV4Address = 4;
    recEntityId_iPTextV6Address = 5;

    // initialisation of some runtime variables
    //-----------------------------------------
    startTime  = defLocalTime;
    stopTime   = defLocalTime;

  }

  /***************************************************************************
   * function initializeForNewHeader
   ***************************************************************************/
  function initializeForNewHeader
  {
    // initialisation of some runtime arrays
    //-----------------------------------------
    // calledNumberAnalysis
    calledNumberAnalysisEntries = 0;
    arrayClear( calledNumberAnalysisCode );
    arrayClear( calledNumberAnalysisCC );
    arrayClear( calledNumberAnalysisIAC );
    arrayClear( calledNumberAnalysisCCarray );
    arrayClear( calledNumberAnalysisIACarray );
    // taxation
    taxEntries = 0;
    arrayClear( taxCode );
    arrayClear( taxType );
    arrayClear( taxRate );
    // recEntityInfo
    recEntityEntries = 0;
    arrayClear( recEntityCode );
    arrayClear( recEntityType );
    arrayClear( recEntityId );
    arrayClear( recEntityId_Type );
    // utcTimeOffsetInfo
    utcTimeOffsetEntries = 0;
    arrayClear( utcTimeOffsetCode );
    arrayClear( utcTimeOffset );
    // vasInfo
    vasEntries = 0;
    arrayClear( vasCode );
    arrayClear( vasShortDesc );
    arrayClear( vasDesc );
    // messageDescriptionInfo
    messageDescriptionEntries = 0;
    arrayClear( messageDescriptionCode );
    arrayClear( messageDescription );
    // discounting
    discountEntries = 0;
    arrayClear( discountCode );
    arrayClear( discountApplied_Type );
    arrayClear( discountApplied );
    // currencyConversion
    currencyEntries = 0;
    arrayClear( exchangeRateCode );
    arrayClear( numberOfDecimalPlaces );
    arrayClear( exchangeRate );
    arrayClear( exchangeRateFactor );

    // initialisation of some runtime variables
    //-----------------------------------------
    chainReference              = 0;
    records                     = 0;
    related_record              = 0;
    related_info_id             = 0;
    tap3Detail                  = 0;
    details                     = 0;
    theSender                   = "";
    theRecipient                = "";
    theTap3SpecificationVersionNumber = 0; //TODO default?
    theTap3ReleaseVersionNumber       = 0; //TODO default?
    theFileSeqNum               = 0;
    theOrigFileSeqNum           = 0;
    theTotalChargedValue        = 0.0;
    theTotalTaxValue            = 0.0;
    theTotalDiscountValue       = 0.0;
    theTotalChargedValue_00     = 0.0;
    lastLocalTimeStamp          = defLocalTimeStamp;
    lastUtcTimeOffset           = defUtcTimeOffset;
    sumChargedAmountValueFile   = 0.0;
    sumTaxChargeFile            = 0.0;
    sumTaxChargeFileAll         = 0.0;
    sumDiscountValueFile        = 0.0;   // Initialize file level, Dis Val sum to 0

    theLocalCurrency            = "SDR"; // default
    theLocalCurrencyIsMissing   = false;

    theTapCurrency              = "SDR"; // default
    theTapDecimalPlaces         = 0;     // manadatory tap3 field, will be overwritten
    theAbsoluteAmountDivider    = 1.0;   // corresponding to theTapDecimalPlaces

    recEntityCodeIsMissing      = false;
    recEntityTypeIsMissing      = false;
    recEntityIdIsMissing        = false;
    numberOfChannelsUsedIsMissing= false;
    qoSDelayIsMissing		= false;
    qoSMeanThroughputIsMissing  = false;
    qoSPeakThroughputIsMissing  = false;
    qoSPrecedenceIsMissing	= false;
    qoSReliabilityIsMissing	= false;
    chargedPartyStatusIsMissing = false;
    nonChargedPartyIsMissing	= false;
    messageStatusIsMissing	= false;
    priorityCodeIsMissing	= false;
    messageTypeIsMissing	= false;
    messageDescriptionCodeIsMissing = false;
    depositTimeStampIsMissing	= false;
    completionTimeStampIsMissing= false;
    taxCodeIsMissing		= false;
    taxTypeIsMissing		= false;
    taxValueIsMissing		= false;
    totalChargeTypeIsMissing	= false;
    absoluteAmountIsMissing	= false;
    homeIdTypeIsMissing		= false;
    homeIdentifierIsMissing	= false;
    utcTimeOffsetCodeIsMissing	= false;
    utcTimeOffsetIsMissing	= false;
    vasCodeIsMissing		= false;
    vasShortDescriptionIsMissing= false;
    imsiIsMissing		= false;
    taxableAmountIsMissing	= false;
    tcvidx			= 0;

    taxationListIsMissing       = false;
  }

  /***************************************************************************
   * function createNewGarbageCollectorDetail
   ***************************************************************************/
  function Bool createNewGarbageCollectorDetail
  {
    // Create the EDR
    if ( edrNew( DETAIL, CONTAINER_UNKNOWN ) == false )
    {
      edrAddError( "ERR_EDR_CREATE", 4 );
      logFormat( "ERROR: Failed to create a DETAIL of type CONTAINER_UNKNOWN\n" );
      //TODO abort processing of the input stream
      return false;
    }
    edrString(DETAIL.ERROR_REJECT_TYPE) = "garbage";
    edrLong(DETAIL.DISCARDING)          = 1;
    return true;
  }

  /***************************************************************************
   * function createNewDetail
   ***************************************************************************/
  function Bool createNewDetail(Long detailTypedId, String detailType)
  {
    // Create the EDR
    if ( edrNew( DETAIL, CONTAINER_DETAIL ) == false )
    {
      edrAddError( "ERR_EDR_CREATE", 4 );
      logFormat( "ERROR: Failed to create DETAIL\n" );
      //TODO abort processing of the input stream
      return false;
    }

    // specific data
    record_Type = detailTypedId;
    details     = details+1;
    records     = records+1;
    edrString(DETAIL.RECORD_TYPE) = detailType;
    edrLong(DETAIL.RECORD_NUMBER) = records;

    edrLong(DETAIL.RECORD_LENGTH) = tap3Detail; //TODOremove workaround for errorProcessing
/*
    // little info printout
    if      ( detailTypedId==record_MOC )
        logStdout( "IN_record_MOC  #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else if ( detailTypedId==record_MTC )
        logStdout( "IN_record_MTC  #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else if ( detailTypedId==record_MSS )
        logStdout( "IN_record_MSS  #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else if ( detailTypedId==record_SCU )
        logStdout( "IN_record_SCU  #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else if ( detailTypedId==record_VAS )
        logStdout( "IN_record_VAS  #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else if ( detailTypedId==record_CONT )
        logStdout( "IN_record_CONT #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else if ( detailTypedId==record_GPRS )
        logStdout( "IN_record_GPRS #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else if ( detailTypedId==record_LOCN )
        logStdout( "IN_record_LOCN #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else
        logStdout( "ERROR: unknown detail type: "+longToStr(detailTypedId)+"\n" );
*/

    // Add the Extension block to store service information
    if      (   ( detailTypedId==record_MOC ) or
                ( detailTypedId==record_MTC ) or
                ( detailTypedId==record_MSS ) or
                ( detailTypedId==record_SCU ) or
                ( detailTypedId==record_VAS )  )
    {
      if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT ) == false )
      {
        String Msg = "failed to add ASS_GSMW_EXT datablock for EDR "+longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        return false; //TODO check for consequences
      }
      records = records+1;
      edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)                 = 1;
      edrString(DETAIL.ASS_GSMW_EXT.RECORD_TYPE, 0)             = extension_GSMW;
      edrLong(DETAIL.ASS_GSMW_EXT.RECORD_NUMBER, 0)             = records;
      edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS, 0)      = 0;
      edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_BS_PACKETS, 0)      = 0;
      related_record = records;
    }
    else if ( detailTypedId==record_GPRS )
    {
      if ( edrAddDatablock( DETAIL.ASS_GPRS_EXT ) == false )
      {
        String Msg = "failed to add ASS_GPRS_EXT datablock for EDR "+longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        return false; //TODO check for consequences
      }
      records = records+1;
      edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)                 = 1;
      edrString(DETAIL.ASS_GPRS_EXT.RECORD_TYPE, 0)             = extension_GPRS;
      edrLong( DETAIL.ASS_GPRS_EXT.RECORD_NUMBER, 0)            = records;
      related_record = records;

      //defaults for QoS
      edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_DELAY, 0)           = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_MEAN_THROUGHPUT, 0) = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PEAK_THROUGHPUT, 0) = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PRECEDENCE, 0)      = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_RELIABILITY, 0)     = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_DELAY, 0)                = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_MEAN_THROUGHPUT, 0)      = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_PEAK_THROUGHPUT, 0)      = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_PRECEDENCE, 0)           = "0";
      edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_RELIABILITY, 0)          = "0";
    }
    else if ( detailTypedId == record_CONT )
    {
      if ( edrAddDatablock( DETAIL.ASS_CONT_EXT ) == false )
      {
        String Msg = "Failed to add ASS_CONT_EXT datablock for EDR " + longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        return false;					//TODO check for consequences
      }
      records = records + 1;
      edrLong( DETAIL.NUMBER_ASSOCIATED_RECORDS )     = 1;
      edrString( DETAIL.ASS_CONT_EXT.RECORD_TYPE, 0 ) = extension_CONT;
      edrLong( DETAIL.ASS_CONT_EXT.RECORD_NUMBER, 0 ) = records;
      related_record = records;
    }
    else if ( detailTypedId == record_LOCN )
    {
      if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT ) == false )
      {
        String Msg = "Failed to add ASS_LOCN_EXT datablock for EDR " + longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg );
        return false;					//TODO check for consequences
      }
      records = records + 1;
      edrLong( DETAIL.NUMBER_ASSOCIATED_RECORDS )     = 1;
      edrString( DETAIL.ASS_LOCN_EXT.RECORD_TYPE, 0 ) = extension_LOCN;
      edrLong( DETAIL.ASS_LOCN_EXT.RECORD_NUMBER, 0 ) = records;
      related_record = records;
    }
    else
    {
      String Msg = "unknown detail type: "+longToStr(detailTypedId)+", for EDR "+longToStr(records);
      edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

//logStdout( "ERROR: unknown detail type: "+longToStr(detailTypedId)+"\n" );
      return false; //TODO check for consequences
    }

    // initialisation to defaults
    edrLong(DETAIL.DISCARDING)                         = 0;
    edrLong(DETAIL.A_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.A_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.A_NUMBER)                         = defTelNumber;
      edrEmptyInput(DETAIL.A_NUMBER);
    edrString(DETAIL.INTERN_A_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.B_TYPE_OF_NUMBER)                   = 0;      // unknown
      edrEmptyInput(DETAIL.B_TYPE_OF_NUMBER);
    edrString(DETAIL.B_NUMBERING_PLAN)                 = "0";
      edrEmptyInput(DETAIL.B_NUMBERING_PLAN);
    edrString(DETAIL.B_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_B_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.C_TYPE_OF_NUMBER)                   = 0;      // unknown
      edrEmptyInput(DETAIL.C_TYPE_OF_NUMBER);
    edrString(DETAIL.C_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.C_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_C_NUMBER_ZONE)             = defTelNumber;
    edrString(DETAIL.USAGE_DIRECTION)                  = "0";
    edrString(DETAIL.BASIC_SERVICE)                    = "011";
    edrString(DETAIL.CALL_COMPLETION_INDICATOR)        = defCauseForTerm;   // normal charging
      edrEmptyInput(DETAIL.CALL_COMPLETION_INDICATOR);
    edrString(DETAIL.LONG_DURATION_INDICATOR)          = "S";    // single record (no chain)
    edrDate(DETAIL.CHARGING_START_TIMESTAMP)           = defLocalTime;
      edrEmptyInput(DETAIL.CHARGING_START_TIMESTAMP);
    edrDate(DETAIL.CHARGING_END_TIMESTAMP)             = defLocalTime;
      edrEmptyInput(DETAIL.CHARGING_END_TIMESTAMP);
    edrString(DETAIL.UTC_TIME_OFFSET)                  = defUtcTimeOffset;
    edrDecimal(DETAIL.DURATION)                        = 0.0;
    edrString(DETAIL.DURATION_UOM)                     = "SEC";
    edrDecimal(DETAIL.VOLUME_SENT)                     = 0.0;
    edrString(DETAIL.VOLUME_SENT_UOM)                  = "BYT";
    edrDecimal(DETAIL.VOLUME_RECEIVED)                 = 0.0;
    edrString(DETAIL.VOLUME_RECEIVED_UOM)              = "BYT";
    edrDecimal(DETAIL.NUMBER_OF_UNITS)                 = 0.0;
    edrString(DETAIL.NUMBER_OF_UNITS_UOM)              = "CLK";
    edrString(DETAIL.RETAIL_CHARGED_TAX_TREATMENT)     = "N";    // tax not included in charge
    edrString(DETAIL.WHOLESALE_CHARGED_TAX_TREATMENT)  = "N";    // tax not included in charge
    edrString(DETAIL.INTERN_SERVICE_CLASS)             = "*";
    edrLong(DETAIL.INTERN_PROCESS_STATUS)              = 0;      // Normal

    // initialize block counters
    successiveBasicServiceUsed  = 0;
    successiveChargeInformation = 0;
    successiveChargeInformationPerBS = 0;
    successiveChargeDetail      = 0;
    successiveTaxDetail         = 0;
    successiveChargePacket      = 0;
    successiveTaxPacket         = 0;
    ACBidx                      = 0; //index of the current associate charge breakdown
    CPidx                       = 0; //index of the current ChargePacket
    TPidx                       = 0; //index of the current TaxPacket
    pmidx                       = 0; //index of the hscsd paramter modification
    vasidx                      = 0; //index of the vas block
    gsPacketIdx			= 0;
    SGSNidx			= 0; //index of SGSN block

    // some detail level runtime values
    lastLocalTimeStamp          = defLocalTimeStamp;
    lastUtcTimeOffset           = defUtcTimeOffset;
    lastValidLocalTimeStamp     = defLocalTimeStamp;
    lastValidUtcTimeOffset      = defUtcTimeOffset;
    lastCode                    = 0;
    related_info_id             = 0;

    recEntityCodeIsMissing      = false;
    recEntityTypeIsMissing      = false;
    recEntityIdIsMissing        = false;
    numberOfChannelsUsedIsMissing= false;
    qoSDelayIsMissing		= false;
    qoSMeanThroughputIsMissing  = false;
    qoSPeakThroughputIsMissing  = false;
    qoSPrecedenceIsMissing	= false;
    qoSReliabilityIsMissing	= false;
    chargedPartyStatusIsMissing = false;
    nonChargedPartyIsMissing	= false;
    messageStatusIsMissing	= false;
    priorityCodeIsMissing	= false;
    messageTypeIsMissing	= false;
    messageDescriptionCodeIsMissing= false;
    depositTimeStampIsMissing	= false;
    completionTimeStampIsMissing= false;
    taxCodeIsMissing		= false;
    taxTypeIsMissing		= false;
    taxValueIsMissing		= false;
    totalChargeTypeIsMissing	= false;
    absoluteAmountIsMissing	= false;
    homeIdTypeIsMissing		= false;
    homeIdentifierIsMissing	= false;
    utcTimeOffsetCodeIsMissing	= false;
    utcTimeOffsetIsMissing	= false;
    vasCodeIsMissing		= false;
    vasShortDescriptionIsMissing= false;
    imsiIsMissing		= false;

    geographicalLocation        = "";
    strUMTSQosReqOrUsed         = "";

    return true;
  }

  /***************************************************************************
   * function initializeChargeDetailTempFields
   ***************************************************************************/
  function initializeChargeDetailTempFields
  {
    // initialise ChargeDetail temporaey fields used to store the provided values
    lastChargeType              = "";
    lastCharge                  = 0.0;
    lastChargeableUnits         = 0;
    lastChargedUnits            = 0;
    lastChargeDetailTimeStamp   = lastValidLocalTimeStamp;
    lastDiscountCode            = 0;
    lastDiscountValue           = 0.0; // initialised here because it is stored on the ChargePacket ! (and we only want to count it once)
  }

  /***************************************************************************
   * function initializeChargeInfoTempFields
   ***************************************************************************/
  function initializeChargeInfoTempFields
  {
    // initialise ChargeInformation temporary fields used to store the provided values
    // for a list of ChargeInformation blocks (CALLED ONLY ONCE PER GENERATED EDR RECORD !!!)
    // (a call to storeChargeInfoTempFields will be used to update the EDR with the data)
    lastChargedItem             = "";

    sumChargeableUnitsDuration          = 0;
    sumChargeableUnitsVolumeSent        = 0;
    sumChargeableUnitsVolumeReceived    = 0;
    sumChargeableUnitsEvents            = 0;
    lastTaxRate                 = 0;
    lastTaxCharge               = 0.0;
    sumTaxChargeEDR             = 0.0;
    sumChargedAmountValueEDR    = 0.0;
    // initialise ChargeDetail temporary fields used to store the provided values
    lastChargeType              = "";
    lastCharge                  = 0.0;
    lastChargeableUnits         = 0;
    lastChargedUnits            = 0;
    lastChargeDetailTimeStamp   = lastValidLocalTimeStamp;
    lastDiscountCode            = 0;
    lastDiscountValue           = 0.0; // initialised here because it is stored on the ChargePacket ! (and we only want to count it once)
  }

  /***************************************************************************
   * function storeChargeInfoTempFields
   ***************************************************************************/
  function storeChargeInfoTempFields
  {
    if (successiveChargeInformation >= 1)
    {
      // default values
      edrString(DETAIL.ASS_CBD.SYSTEM_BRAND_CODE, ACBidx)     = "0";
      // store the collected chargeInformation data in the corresponding EDR
      if (sumChargeableUnitsDuration != 0)
      {
        edrDecimal(DETAIL.DURATION)                     = longToDecimal(sumChargeableUnitsDuration);
      }
      if (record_Type != record_GPRS) //for GPRS, VOLUME_SENT and VOLUME_RECEIVED have already been updated by GprsServiceUsage
      {
        if (sumChargeableUnitsVolumeSent != 0)
        {
          edrDecimal(DETAIL.VOLUME_SENT)                = longToDecimal(sumChargeableUnitsVolumeSent);
        }
        if (sumChargeableUnitsVolumeReceived != 0)
        {
          edrDecimal(DETAIL.VOLUME_RECEIVED)            = longToDecimal(sumChargeableUnitsVolumeReceived);
        }
      }
      if (sumChargeableUnitsEvents != 0)
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)              = longToDecimal(sumChargeableUnitsEvents);
	if ( service_Type == service_Basic)
	{
	  edrDecimal(DETAIL.ASS_GSMW_EXT.BS_PACKET.NUMBER_OF_UNITS, 0, bsPacketIdx) =
					longToDecimal(sumChargeableUnitsEventsBS);
        }
      }
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS, ACBidx)=successiveChargePacket;
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_TAX_PACKETS, ACBidx)=successiveTaxPacket;

      edrString(DETAIL.WHOLESALE_IMPACT_CATEGORY)       = "00";       // as for IFW_TAP3.ChargeType : global charge for ChargeInformation
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) = sumChargedAmountValueEDR;
      if (bUseLocalCurrency)
      {
        edrString(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY) = theLocalCurrency;
        if (theLocalCurrency == "")
        {
          edrEmptyInput(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY);
        }
      }
      else
      {
        edrString(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY) = theTapCurrency;
      }

      if (theLocalCurrencyIsMissing == true)
      {
	edrMissingInput(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY);
      }

      edrString(DETAIL.WHOLESALE_CHARGED_TAX_TREATMENT) = "N";
      edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE)        = lastTaxRate;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)    = sumTaxChargeEDR; //TODO check

      if ( service_Type == service_Basic)
      {
	  edrDecimal(DETAIL.ASS_GSMW_EXT.BS_PACKET.WHOLESALE_CHARGED_AMOUNT_VALUE, 0, bsPacketIdx) = sumChargedAmountValueBS;
	  edrDecimal(DETAIL.ASS_GSMW_EXT.BS_PACKET.WHOLESALE_CHARGED_TAX_VALUE, 0, bsPacketIdx) = sumTaxChargeBS;
//	  edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.WHOLESALE_CHARGED_TAX_RATE, 0, bsPacketIdx) = edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE);
	  edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.WHOLESALE_CHARGED_TAX_RATE, 0, bsPacketIdx) = lastTaxRate;
      }
    }
  }

  /***************************************************************************
   * function updateBasicDetailWithVasCharge
   ***************************************************************************/
  function updateBasicDetailWithVasCharge
  {
    if (successiveChargeInformation >= 1)
    {
      // store the collected chargeInformation data in the corresponding EDR
      if (sumChargeableUnitsDuration != 0)
      {
        edrDecimal(DETAIL.DURATION)                     = longToDecimal(sumChargeableUnitsDuration);
      }
      if (record_Type != record_GPRS) //for GPRS, VOLUME_SENT and VOLUME_RECEIVED have already been updated by GprsServiceUsage
      {
        if (sumChargeableUnitsVolumeSent != 0)
        {
          edrDecimal(DETAIL.VOLUME_SENT)                = longToDecimal(sumChargeableUnitsVolumeSent);
        }
        if (sumChargeableUnitsVolumeReceived != 0)
        {
          edrDecimal(DETAIL.VOLUME_RECEIVED)            = longToDecimal(sumChargeableUnitsVolumeReceived);
        }
      }
      if (sumChargeableUnitsEvents != 0)
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)              = longToDecimal(sumChargeableUnitsEvents);
      }
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS, ACBidx)=successiveChargePacket;
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_TAX_PACKETS, ACBidx)=successiveTaxPacket;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) = sumChargedAmountValueEDR;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)    = sumTaxChargeEDR;  //TODO check
      edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE)        = lastTaxRate;
    }
  }

  /***************************************************************************
   * function updateBasicDetailWithCamelCharge
   ***************************************************************************/
  function updateBasicDetailWithCamelCharge
  {
    if (successiveChargeInformation >= 1)
    {
      // store the collected chargeInformation data in the corresponding EDR
      if (sumChargeableUnitsDuration != 0)
      {
        edrDecimal(DETAIL.DURATION)                     = longToDecimal(sumChargeableUnitsDuration);
      }
      if (record_Type != record_GPRS) //for GPRS, VOLUME_SENT and VOLUME_RECEIVED have already been updated by GprsServiceUsage
      {
        if (sumChargeableUnitsVolumeSent != 0)
        {
          edrDecimal(DETAIL.VOLUME_SENT)                = longToDecimal(sumChargeableUnitsVolumeSent);
        }
        if (sumChargeableUnitsVolumeReceived != 0)
        {
          edrDecimal(DETAIL.VOLUME_RECEIVED)            = longToDecimal(sumChargeableUnitsVolumeReceived);
        }
      }
      if (sumChargeableUnitsEvents != 0)
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)              = longToDecimal(sumChargeableUnitsEvents);
      }
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS, ACBidx)=successiveChargePacket;
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_TAX_PACKETS, ACBidx)=successiveTaxPacket;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) = sumChargedAmountValueEDR;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)    = sumTaxChargeEDR;  //TODO check
    }
  }

  /***************************************************************************
   * function newBasicServiceBlock
   ***************************************************************************/
  function Bool newBasicServiceBlock
  {
    service_Type                = service_Basic;
    successiveBasicServiceUsed  = successiveBasicServiceUsed +1;
//  successiveChargeInformation = 0; // for this Service Block
    successiveChargeInformationPerBS = 0; // for this Service Block
    successiveChargeDetail      = 0; // for this one Charge Information
    successiveTaxDetail         = 0; // for this one Charge Information
    successiveChargePacket      = 0; // for this EDR
    successiveTaxPacket         = 0; // for this EDR
    related_info_id             = 0;
    sumChargedAmountValueBS     = 0.0;
    sumChargeableUnitsEventsBS  = 0;
    sumTaxChargeBS              = 0.0;

    // add a corresponding BS_PACKET
    if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.BS_PACKET ) == false )
    {
         String Msg = "failed to add ASS_GSMW_EXT.BS_PACKET datablock";
         edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

         return false;
    }

    //get an index to the BS_PACKET
    bsPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_BS_PACKETS , 0);
    edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_BS_PACKETS , 0) = bsPacketIdx + 1;

    records = records+1;
    edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
    edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.RECORD_TYPE, 0, bsPacketIdx) = extension_BS_EVENT;
    edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.RECORD_NUMBER, 0, bsPacketIdx) = records;
    related_record = records;

    if (successiveBasicServiceUsed > 1)
    {
      if (successiveBasicServiceUsed == 2)
      {
        // get a new unique ID to chain all records for aggregation (do only once!)
        chainReference = chainReference +1;
        edrString(DETAIL.CHAIN_REFERENCE)         = longToStr(chainReference);
        edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHAIN_REFERENCE, 0, bsPacketIdx)         = longToStr(chainReference);
        edrString(DETAIL.LONG_DURATION_INDICATOR) = "F"; //the first record of the chain
        edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.LONG_DURATION_INDICATOR, 0, bsPacketIdx) = "I"; //the first record of the chain
        edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHAIN_REFERENCE, 0, bsPacketIdx -1)         = longToStr(chainReference);
        edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.LONG_DURATION_INDICATOR, 0, bsPacketIdx -1) = "F"; //the first record of the chain
      }
      edrString(DETAIL.CHAIN_REFERENCE)         = longToStr(chainReference);
      edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHAIN_REFERENCE, 0, bsPacketIdx)         = longToStr(chainReference);
      edrString(DETAIL.LONG_DURATION_INDICATOR) = "I"; //an intermediate record of the chain
      edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.LONG_DURATION_INDICATOR, 0, bsPacketIdx) = "I"; //an intermediate record of the chain
    }
    return true;
  }

  /***************************************************************************
   * function getExchangeRateFactor
   ***************************************************************************/
  function Decimal getExchangeRateFactor(Long ExchangeRateCode)
  {
    if (ExchangeRateCode >= currencyEntries)
    {
      // this should never happen!
      String Msg = "getExchangeRateFactor("+longToStr(ExchangeRateCode)+"), unknown ExchangeRateCode";
      //edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);

      const String severe     = "severe";
      const String tag        = "105";
      const String depth      = "6";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "101", tag, depth, offset, arrayIndex,
		"Can not find the exchange rate associated with the code");
      setAssociatedTapErr("ERR_TAP3_EXCHANGE_RATE_FOR_CODE_NOT_FOUND", 3,"101" ,tag ,depth);	


// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      return(1.0);
    }
    return(exchangeRateFactor[ExchangeRateCode]);
  }

  /***************************************************************************
   * function getRecEntityType
   ***************************************************************************/
  function Long getRecEntityType(Long RecEntityCode)
  {
    if (RecEntityCode >= recEntityEntries)
    {
      // this should never happen!
      String Msg = "getRecEntityType("+longToStr(RecEntityCode)+"), unknown RecEntityCode";
     // edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      const String severe     = "severe";
      const String tag        = "184";
      const String depth      = "6";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "100", tag, depth, offset, arrayIndex,
		"Can not find record entity type associated with this code");
      setAssociatedTapErr("ERR_TAP3_REC_ENTITY_TYPE_NOT_FOUND", 3,"100" ,tag ,depth);	

      return(0);
    }
    return( recEntityType[RecEntityCode] );
  }

  /***************************************************************************
   * function getRecEntityId
   ***************************************************************************/
  function String getRecEntityId(Long RecEntityCode)
  {
    if (RecEntityCode >= recEntityEntries)
    {
      // this should never happen!
      String Msg = "getRecEntityId("+longToStr(RecEntityCode)+"), unknown RecEntityCode";
      // edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      const String severe     = "severe";
      const String tag        = "184";
      const String depth      = "6";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "100", tag, depth, offset, arrayIndex,
	"Can not find record entity id associatd with this code");
      setAssociatedTapErr("ERR_TAP3_REC_ENTITY_ID_NOT_FOUND", 3,"100" ,tag ,depth);	

      return("");
    }
    return( recEntityId[RecEntityCode] );
  }

  /***************************************************************************
   * function getVasShortDesc
   ***************************************************************************/
  function String getVasShortDesc(Long VasCode)
  {
    if (VasCode >= vasEntries)
    {
      // this should never happen!
      String Msg = "getVasShortDesc("+longToStr(VasCode)+"), unknown VasCode";
   //   edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);

      const String severe     = "severe";
      const String tag        = "237";
      const String depth      = "5";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "100", tag, depth, offset, arrayIndex,
		"Can not find Vas Short description associated with this code");
      setAssociatedTapErr("ERR_TAP3_VAS_SHORT_DESC_NOT_FOUND", 3,"100" ,tag ,depth);	

// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      return("");
    }
    return( vasShortDesc[VasCode] );
  }

  /***************************************************************************
   * function getVasDesc
   ***************************************************************************/
  function String getVasDesc(Long VasCode)
  {
    if (VasCode >= vasEntries)
    {
      // this should never happen!
      String Msg = "getVasDesc("+longToStr(VasCode)+"), unknown VasCode";
    //  edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

    //  const String severe     = "severe";
    //  const String tag        = "237";
    //  const String depth      = "5";
    //  const String offset     = "0";
    //  const String arrayIndex ="-1";

    // edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
    // edrAddError("ERR_TAP3_RET", 3, severe, "100", tag, depth, offset, arrayIndex, " ");

      return("");
    }
    return( vasDesc[VasCode] );
  }

  /***************************************************************************
   * function getDiscountAppliedType
   ***************************************************************************/
  function Long getDiscountAppliedType(Long DiscountCode)
  {
    if (DiscountCode >= discountEntries)
    {
      // this should never happen!
      String Msg = "getDiscountAppliedType("+longToStr(DiscountCode)+"), unknown DiscountCode";
      // edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++


      const String severe     = "severe";
      const String tag        = "91";
      const String depth      = "7";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "102", tag, depth, offset, arrayIndex,
		"Can not find discount type associated with this code");
      setAssociatedTapErr("ERR_TAP3_DISCOUNT_TYPE_NOT_FOUND", 3,"102" ,tag ,depth);	

      return(0);
    }
    return( discountApplied_Type[DiscountCode] );
  }

  /***************************************************************************
   * function getDiscountApplied
   ***************************************************************************/
  function Long getDiscountApplied(Long DiscountCode)
  {
    if (DiscountCode >= discountEntries)
    {
      // this should never happen!
      String Msg = "getDiscountApplied("+longToStr(DiscountCode)+"), unknown DiscountCode";
      //edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      const String severe     = "severe";
      const String tag        = "91";
      const String depth      = "7";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "102", tag, depth, offset, arrayIndex,
		"Can not find discount applied associated with this code");
      setAssociatedTapErr("ERR_TAP3_DISCOUNT_APPLIED_NOT_FOUND", 3,"102" ,tag ,depth);	

      return(0);
    }
    return( discountApplied[DiscountCode] );
  }

  /***************************************************************************
   * function getTaxRate
   ***************************************************************************/
  function String getTaxRate(Long TaxCode)
  {
    if (TaxCode >= taxEntries)
    {
      // this should never happen!
      String Msg = "getTaxRate("+longToStr(TaxCode)+"), unknown TaxCode";
      //edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      const String severe     = "severe";
      const String tag        = "212";
      const String depth      = "7";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "100", tag, depth, offset, arrayIndex,
	"Can not find the tax rate associated with this code");
      setAssociatedTapErr("ERR_TAP3_TAX_RATE_NOT_FOUND", 3,"100" ,tag ,depth);	

      return("");
    }
    return( taxRate[TaxCode] );
  }


  /***************************************************************************
   * function getTaxType
   ***************************************************************************/
  function String getTaxType(Long TaxCode)
  {
    if (TaxCode >= taxEntries)
    {
      // this should never happen!
      String Msg = "getTaxRate("+longToStr(TaxCode)+"), unknown TaxCode";
      //edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      const String severe     = "severe";
      const String tag        = "212";
      const String depth      = "7";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "100", tag, depth, offset, arrayIndex,
		"Can not find the tax type associated with this tax code");
      setAssociatedTapErr("ERR_TAP3_TAX_TYPE_NOT_FOUND", 3,"100" ,tag ,depth);	

      return("");
    }
    return( taxType[TaxCode] );
  }

  /***************************************************************************
   * function getUtcTimeOffset
   ***************************************************************************/
  function String getUtcTimeOffset(Long TimeOffsetCode)
  {
    if (TimeOffsetCode >= utcTimeOffsetEntries)
    {
      // this should never happen!
      String Msg = "getUtcTimeOffset("+longToStr(TimeOffsetCode)+"), unknown utcTimeOffsetCode";
      //edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++
      const String severe     = "severe";
      const String tag        = "232";
      const String depth      = "6";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 3, severe, "100", tag, depth, offset, arrayIndex,
		"Can not find the UTC TimeOffset associated with this code");
      setAssociatedTapErr("ERR_TAP3_UTC_TIMEOFFSET_NOT_FOUND", 3,"100" ,tag ,depth);	

      return("");
    }
    return( utcTimeOffset[TimeOffsetCode] );
  }

  /***************************************************************************
   * function getMessageDescription
   ***************************************************************************/
  function String getMessageDescription(Long MessageDescriptionCode)
  {
    if (MessageDescriptionCode >= messageDescriptionEntries)
    {
      // this should never happen!
      String Msg = "getMessageDescription("+longToStr(MessageDescriptionCode)+"), unknown MessageDescriptionCode";
      //edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 3);
// ++++++++++++++++++++

      const String warning     = "warning";
      const String tag        = "141";
      const String depth      = "5";
      const String offset     = "0";
      const String arrayIndex ="-1";

      edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
      edrAddError("ERR_TAP3_RET", 1, warning, "100", tag, depth, offset, arrayIndex,
		"Can not find message description associated with this code");
      setAssociatedTapErr("ERR_TAP3_MESSAGE_DESC_NOT_FOUND", 1,"100" ,tag ,depth);	
      return("");
    }
    return( messageDescription[MessageDescriptionCode] );
  }

  /***************************************************************************
   * function getIAC
   ***************************************************************************/
  function String getIAC(Long CalledNumberAnalysisCode)
  {
    Long i;
    for (i=0 ; i<calledNumberAnalysisEntries; i=i+1)
    {
      if (calledNumberAnalysisCode[i] == CalledNumberAnalysisCode)
      {
        return( calledNumberAnalysisIAC[i] );
      }
    }
    return(NORM_IAC_STRING);
  }

  /***************************************************************************
   * function getCC
   ***************************************************************************/
  function String getCC(Long CalledNumberAnalysisCode)
  {
    Long i;
    for (i=0 ; i<calledNumberAnalysisEntries; i=i+1)
    {
      if (calledNumberAnalysisCode[i] == CalledNumberAnalysisCode)
      {
        return( calledNumberAnalysisCC[i] );
      }
    }
    return(NORM_CC_STRING);
  }

  /***************************************************************************
   * function getCalledNumberAnalysisCodeIdx
   ***************************************************************************/
  function Long getCalledNumberAnalysisCodeIdx(Long CalledNumberAnalysisCode)
  {
    Long i;
    for (i=0 ; i<calledNumberAnalysisEntries; i=i+1)
    {
      if (calledNumberAnalysisCode[i] == CalledNumberAnalysisCode)
      {
        return( i );
      }
    }
    return(0); //default
  }

  /***************************************************************************
   * function getIacList
   ***************************************************************************/
  function String getIacList
  {
    String localString = "";
    Long size1 = arraySize( calledNumberAnalysisIACarray );
    Long size2 = 0;
    Long i;
    Long j;
    for (i=0 ; i<size1 ; i=i+1)
    {
      size2 = arraySize( calledNumberAnalysisIACarray[i] );
      for (j=0 ; j<size2 ; j=j+1)
      {
        localString = localString + calledNumberAnalysisIACarray[i][j] + ", ";
      }
    }
    if (localString == "")
    {
      return NORM_IAC_STRING; // use default from the registry
    }
    else
    {
      //strip the last comma
      localString = strSubstr(localString, 0, strLength(localString)-1);
      return localString;
    }
  }

  /***************************************************************************
   * function getCcList
   ***************************************************************************/
  function String getCcList
  {
    String localString = "";
    Long size1 = arraySize( calledNumberAnalysisCCarray );
    Long size2 = 0;
    Long i;
    Long j;
    for (i=0 ; i<size1 ; i=i+1)
    {
      size2 = arraySize( calledNumberAnalysisCCarray[i] );
      for (j=0 ; j<size2 ; j=j+1)
      {
        localString = localString + calledNumberAnalysisCCarray[i][j] + ", ";
      }
    }
    if (localString == "")
    {
      return NORM_CC_STRING; // use default from the registry
    }
    else
    {
      //strip the last comma
      localString = strSubstr(localString, 0, strLength(localString)-1);
      return localString;
    }
  }

  /***************************************************************************
   * function buildNullFiller
   ***************************************************************************/
  function String buildNullFiller(Long desiredLen, Long effectiveLen)
  {
    // NB: it is still hardcoded for a desiredLen of 5
    String filler = "";
    if (effectiveLen < desiredLen)
    {
      switch (effectiveLen)
      {
        case 0 : filler="00000";break;
        case 1 : filler="0000"; break;
        case 2 : filler="000";  break;
        case 3 : filler="00";   break;
        case 4 : filler="0";    break;
        default:                break;
      }
    }
    return filler;
  }

  /***************************************************************************
   * function storeTheOperatorSpecInformation
   ***************************************************************************/
  function storeTheOperatorSpecInformation
  {
    switch (record_Type)
    {
      case (record_MOC):
      case (record_MTC):
      case (record_MSS):
      case (record_SCU):
      case (record_VAS):
      case (record_CONT):
      case (record_LOCN):
      case (record_GPRS):
      {
        edrConnectToken(DETAIL.OPERATOR_SPECIFIC_INFO,
		"IFW_TAP3.OperatorSpecInformation.OPERATOR_SPEC_INFORMATION");
      }
      break;
      case (record_Header):
      {
        edrConnectToken(HEADER.OPERATOR_SPECIFIC_INFO,
		"IFW_TAP3.OperatorSpecInformation.OPERATOR_SPEC_INFORMATION");
      }
      break;
      case (record_Trailer):
      {
        edrConnectToken(TRAILER.OPERATOR_SPECIFIC_INFO,
		"IFW_TAP3.OperatorSpecInformation.OPERATOR_SPEC_INFORMATION");
      }
      break;
      default:
      {
        //nothing to do
      }
      break;
    }
  }
}

//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{
  inputStream:
      {
//startTime = sysdate(); //TODO remove this line or just comment it
        initializeForNewHeader();
      }
      dataInterchange
      fileFiller
      {
//stopTime = sysdate(); //TODO remove this line or just comment it
//logStdout( "  Start Tap0310 input :  " + dateToStr(startTime)+ "\n");         //TODO remove this line or just comment it
//logStdout( "  End   Tap0310 input :  " + dateToStr(stopTime) + "\n");         //TODO remove this line or just comment it
//logStdout( "  This pass generated :  " + longToStr(details)  + " details\n"); //TODO remove this line or just comment it
      }
    ;

  fileFiller:
      fileFiller
      fileFillerElement
    | /* EMPTY */
    ;

  fileFillerElement:
      IFW_TAP3.Block_END   // "\0\0"
    | IFW_TAP3.FileFiller  // "\0"
    | IFW_TAP3.FileEndFiller  // "\n"
    ;

  dataInterchange:
      transferBatch
    | notification
    ;

  notification:
      IFW_TAP3.Notification
      {
        errorStateTap3 = beginTap3Notification;
        record_Type = record_Header;
//logStdout( "record_Header #"+longToStr(records)+" (TAP3_NOTIFICATION)\n" );
        if ( edrNew( HEADER, CONTAINER_HEADER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 ); //TODO abort processing of the input stream
          logFormat( "ERROR: Failed to create HEADER" );
        }
        edrString(HEADER.RECORD_TYPE)         = type_HEADER;
        edrLong(HEADER.RECORD_NUMBER)         = 1;

        edrString(HEADER.SENDER_COUNTRY_CODE) = "NOTIFICATION"; //TODOremove workaround for errorProcessing
      }
      sender_mandopt
      {
        theSender = tokenString("IFW_TAP3.Sender.PLMN_ID");
        edrString(HEADER.SENDER)= theSender;
      }
      recipient_mandopt
      {
        theRecipient = tokenString("IFW_TAP3.Recipient.PLMN_ID");
        edrString(HEADER.RECIPIENT)= theRecipient;
      }
      fileSequenceNumber_mandopt
      {
        theFileSeqNum     = tokenLong("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER");
        theOrigFileSeqNum = theFileSeqNum;
        edrLong(HEADER.SEQUENCE_NUMBER)       = theFileSeqNum;
        edrLong(HEADER.ORIGIN_SEQUENCE_NUMBER)= theOrigFileSeqNum;
      }
      rapFileSequenceNumberBatch_opt
      fileCreationTimeStamp_mandopt
      fileAvailableTimeStamp_mandopt
      transferCutOffTimeStamp_mandopt
      specificationVersionNumber_mandopt
      {
        edrConnectToken(HEADER.SPECIFICATION_VERSION_NUMBER,
		"IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER");
        theTap3SpecificationVersionNumber = edrLong(HEADER.SPECIFICATION_VERSION_NUMBER);
      }
      releaseVersionNumber_mandopt
      {
        edrConnectToken(HEADER.RELEASE_VERSION, "IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER");
        theTap3ReleaseVersionNumber = edrLong(HEADER.RELEASE_VERSION);
      }
      fileTypeIndicator_opt
      {
        edrString(HEADER.DATA_TYPE_INDICATOR) = theFileTypeIndicator;
      }
      operatorSpecInformation_opt
      {
        errorStateTap3 = endTap3Notification;

        //Generate a default TRAILER to close the stream and identify a Notification to the output
        if ( edrNew( TRAILER, CONTAINER_TRAILER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 ); //TODO abort processing of the input stream
          logFormat( "ERROR: Failed to create TRAILER" );
        }
        edrString(TRAILER.RECORD_TYPE)                     = type_TRAILER;
        edrLong(TRAILER.RECORD_NUMBER)                     = 2;
        edrString(TRAILER.SENDER)                          = theSender;
        edrString(TRAILER.RECIPIENT)                       = theRecipient;
        edrLong(TRAILER.SEQUENCE_NUMBER)                   = theFileSeqNum;
        edrLong(TRAILER.ORIGIN_SEQUENCE_NUMBER)            = theOrigFileSeqNum;
        edrLong(TRAILER.TOTAL_NUMBER_OF_RECORDS)           = 0;
        edrDate(TRAILER.FIRST_START_TIMESTAMP)             = strToDate(theFileCreationTimeStamp);
        edrString(TRAILER.FIRST_CHARGING_UTC_TIME_OFFSET)  = theFileCreationUtcTimeOffset;
        edrDate(TRAILER.LAST_START_TIMESTAMP)              = strToDate(theFileCreationTimeStamp);
        edrString(TRAILER.LAST_CHARGING_UTC_TIME_OFFSET)   = theFileCreationUtcTimeOffset;
      }
      IFW_TAP3.Block_END
    ;

  transferBatch:
      IFW_TAP3.TransferBatch
      {
        createNewGarbageCollectorDetail();
        errorStateTap3 = beginTap3Header;
        record_Type = record_Header;
      }
      batchControlInfo_mandopt
      accountingInfo_opt
      networkInfo_mandopt
      {
        // for every stream, the default TelNnumber is different, built as <iac><cc>
        defTelNumber = convertCli(      "", "00", 0,
                                        NORM_NAC,
                                        calledNumberAnalysisIACarray[0], // NORM_IAC,
                                        calledNumberAnalysisCCarray[0], // NORM_CC,
                                        NORM_IAC_SIGN,
                                        NORM_NDC );
        edrString(HEADER.ORIGIN_COUNTRY_CODE) = defTelNumber; //strOriginCountryCode; //TODO check
        edrEmptyInput(HEADER.ORIGIN_COUNTRY_CODE);
        edrString(HEADER.SENDER_COUNTRY_CODE) = strSenderCountryCode; //TODO check (we take it from registry)
        edrEmptyInput(HEADER.SENDER_COUNTRY_CODE);
        edrString(HEADER.IAC_LIST)            = getIacList();
        edrString(HEADER.CC_LIST)             = getCcList();
      }
      vasInfoList_opt
      messageDescriptionInfoList_opt
      {
        errorStateTap3 = endTap3Header;
      }
      callEventDetails_mandopt
      auditControlInfo_mandopt
      IFW_TAP3.Block_END
      {
        createNewGarbageCollectorDetail();
      }
    ;

  absoluteAmount_mandopt:
      IFW_TAP3.AbsoluteAmount
      {
	edrConnectToken(TRAILER.TOTAL_CHARGE_VALUE_LIST.TOTAL_CHARGE_VALUE, tcvidx,
			"IFW_TAP3.AbsoluteAmount.ABSOLUTE_AMOUNT");
        lastTotalChargeValueAbsoluteAmount = tokenDecimal("IFW_TAP3.AbsoluteAmount.ABSOLUTE_AMOUNT");
      }
    | /* EMPTY */
      {
        absoluteAmountIsMissing = true;
      }
    ;

  accountingInfo_opt:
      IFW_TAP3.AccountingInfo
      {
        errorStateTap3 = beginTap3AccountingInfo;
      }
      taxationList_opt
      discountingList_opt
      localCurrency_mandopt
      tapCurrency_opt
      currencyConversionList_opt
      tapDecimalPlaces_mandopt
      {
        errorStateTap3 = endTap3AccountingInfo;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  advisedCharge_mandopt:
      IFW_TAP3.AdvisedCharge
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0,
                        contentSvcUsedIdx, "IFW_TAP3.AdvisedCharge.ADVISED_CHARGE");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0,
			contentSvcUsedIdx);
      }
    ;

  aiurRequested_opt:
      IFW_TAP3.AiurRequested
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.AIUR_REQUESTED, 0, bsPacketIdx, "IFW_TAP3.AiurRequested.AIUR_REQUESTED");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.AIUR_REQUESTED, 0, bsPacketIdx);
      }
    ;

  aiurRequested_hpm_opt:
      IFW_TAP3.AiurRequested
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.AIUR, 0, bsPacketIdx, 0,  pmidx,  "IFW_TAP3.AiurRequested.AIUR_REQUESTED");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.AIUR, 0, bsPacketIdx, 0, pmidx);
      }
    ;



  earliestCallTimeStamp_opt:
      IFW_TAP3.EarliestCallTimeStamp
      {
        timeStampType = earliestCallTimeStampType;
      }
      dateTimeLong
      IFW_TAP3.Block_END
      {
        edrDate(TRAILER.FIRST_START_TIMESTAMP)             = strToDate(lastLocalTimeStamp);
        edrString(TRAILER.FIRST_CHARGING_UTC_TIME_OFFSET)  = lastUtcTimeOffset;
      }
    | /* EMTPY */
    ;

  latestCallTimeStamp_opt:
      IFW_TAP3.LatestCallTimeStamp
      {
        timeStampType = latestCallTimeStampType;
      }
      dateTimeLong
      IFW_TAP3.Block_END
      {
        edrDate(TRAILER.LAST_START_TIMESTAMP)              = strToDate(lastLocalTimeStamp);
        edrString(TRAILER.LAST_CHARGING_UTC_TIME_OFFSET)   = lastUtcTimeOffset;
      }
    | /* EMTPY */
    ;

  auditControlInfo_mandopt:
      IFW_TAP3.AuditControlInfo
      {
        errorStateTap3 = beginTap3AuditControlInfo;
        record_Type = record_Trailer;
        if ( edrNew( TRAILER, CONTAINER_TRAILER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 );
          logFormat( "ERROR: Failed to create TRAILER\n" );
          //TODO abort processing of the input stream
        }
        records=records+1;
//logStdout( "record_Trailer #"+longToStr(records)+"\n" ); //TODO comment or remove
        edrString(TRAILER.RECORD_TYPE)                     = type_TRAILER;
        edrLong(TRAILER.RECORD_NUMBER)                     = records;
        edrString(TRAILER.SENDER)                          = theSender;
        edrString(TRAILER.RECIPIENT)                       = theRecipient;
        edrLong(TRAILER.SEQUENCE_NUMBER)                   = theFileSeqNum;
        edrLong(TRAILER.ORIGIN_SEQUENCE_NUMBER)            = theOrigFileSeqNum;
        edrLong(TRAILER.TOTAL_NUMBER_OF_RECORDS)           = details;

        // Initialize the Total Charge Value with Charge Type "00" as missing.
        chargeType00IsMissing = true;
      }
      earliestCallTimeStamp_opt
      latestCallTimeStamp_opt
      totalChargeValueList_mandopt
      {
        // Total Charge Value with Charge Type of "00" must be present.
        // If it is missing, raise fatal error.
        if (chargeType00IsMissing == true)
        {
          requestBatchReject(15, -1, 2,  0,  34, "ERR_TAP3_MISSING_TOTAL_CHARGE_VALUE_CHARGE_TYPE_00");
        }

        edrDecimal(TRAILER.TOTAL_RETAIL_CHARGED_VALUE)     = 0.0;
        edrDecimal(TRAILER.TOTAL_WHOLESALE_CHARGED_VALUE)  = sumChargedAmountValueFile;
	if (theTotalChargedValue_00 != 0.0 ) {
         edrDecimal(TRAILER.TAP_TOTAL_CHARGE_VALUE)  = theTotalChargedValue_00 / theAbsoluteAmountDivider;
        }
	else {
	 edrDecimal(TRAILER.TAP_TOTAL_CHARGE_VALUE)  = theTotalChargedValue / theAbsoluteAmountDivider;
        }
      }
      totalTaxRefund_Compatibility
      totalTaxValue_mandopt
      {
        edrDecimal(TRAILER.TOTAL_TAX_VALUE)  = sumTaxChargeFile;
        edrDecimal(TRAILER.TAP_TOTAL_TAX_VALUE)  = (theTotalTaxValue/ theAbsoluteAmountDivider) * lastExchangeRateFactor;
      }
      totalDiscountValue_mandopt
      {
        edrDecimal(TRAILER.TAP_TOTAL_DISCOUNT_VALUE)  = (theTotalDiscountValue/ theAbsoluteAmountDivider) * lastExchangeRateFactor;
        
        // Check if the TAP Total Discount Value and the calculated file level
        // sum of Discount Values are equal.
        if ( sumDiscountValueFile != edrDecimal(TRAILER.TAP_TOTAL_DISCOUNT_VALUE) )
        {
          // If not equal, set Fatal Error
          String offset = "-1";

          // requestBatchReject( Long ObjTag, Long ArrayIdx, Long ObjDepth,  Long ObjOffset,  Long ErrCode)
          requestBatchReject(225, -1, 3,  0,  100, "ERR_TAP3_TOTAL_DISCOUNT_VALUE_MISMATCH");
        }
      }
      totalDiscountRefund_opt
      totalAdvisedChargeValueList_opt
      callEventDetailsCount_mandopt
      operatorSpecInformation_opt
      {
        errorStateTap3 = endTap3AuditControlInfo;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        // Set fatal error
        // requestBatchReject( Long ObjTag, Long ArrayIdx, Long ObjDepth,  Long ObjOffset,  Long ErrCode)
        requestBatchReject(1, -1, 1,  0,  36, "ERR_TAP3_MISSING_AUDIT_CTRL_INFO");
      }
    ;

  totalTaxRefund_Compatibility:
      IFW_TAP3.TotalTaxRefund
    | /* EMPTY */  //for compatibility with before tap0304
    ;

  batchControlInfo_mandopt:
      IFW_TAP3.BatchControlInfo
      {
        if ( edrNew( HEADER, CONTAINER_HEADER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 );
          logFormat( "ERROR: Failed to create HEADER\n" );
          //TODO abort processing of the input stream
        }
        records=records+1;
//logStdout( "record_Header #"+longToStr(records)+"\n" );
        edrString(HEADER.RECORD_TYPE)         = type_HEADER;
        edrLong(HEADER.RECORD_NUMBER)         = records;

        errorStateTap3 = beginTap3BatchControlInfo;
      }
      sender_mandopt
      {
        theSender = tokenString("IFW_TAP3.Sender.PLMN_ID");
        edrString(HEADER.SENDER)= theSender;
      }
      recipient_mandopt
      {
        theRecipient = tokenString("IFW_TAP3.Recipient.PLMN_ID");
        edrString(HEADER.RECIPIENT)= theRecipient;
      }
      fileSequenceNumber_mandopt
      {
        theFileSeqNum     = tokenLong("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER");
        theOrigFileSeqNum = theFileSeqNum;
        edrLong(HEADER.SEQUENCE_NUMBER)       = theFileSeqNum;
        edrLong(HEADER.ORIGIN_SEQUENCE_NUMBER)= theOrigFileSeqNum;
      }
      fileCreationTimeStamp_mandopt
      transferCutOffTimeStamp_mandopt
      fileAvailableTimeStamp_mandopt
      specificationVersionNumber_mandopt
      {
        edrConnectToken(HEADER.SPECIFICATION_VERSION_NUMBER, "IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER");
      }
      releaseVersionNumber_mandopt
      {
        edrConnectToken(HEADER.RELEASE_VERSION, "IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER");
      }
      fileTypeIndicator_opt
      {
        edrString(HEADER.DATA_TYPE_INDICATOR) = theFileTypeIndicator;
      }
      rapFileSequenceNumberBatch_opt
      operatorSpecInformation_opt
      {
        errorStateTap3 = endTap3BatchControlInfo;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
       // Set fatal error
       requestBatchReject(1, -1, 1,  0,  30, "ERR_TAP3_MISSING_BATCH_CTRL_INFO");
      }
    ;

  basicHSCSDParameters:
      IFW_TAP3.BasicHSCSDParameters
      numberOfChannels_basichscd_mandopt
      channelCodingAcceptableList_mandopt
      {
       edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.CHANNEL_CODING_OK_LIST, 0, bsPacketIdx, 0) = lastChannelCoding;
      }
      channelCoding_basicHSCSD_mandopt
      numberOfChannelsUsed_mandopt
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)    = longToDecimal( tokenLong("IFW_TAP3.NumberOfChannelsUsed.NUMBER_OF_CHANNELS_USED") );
        edrString(DETAIL.NUMBER_OF_UNITS_UOM) = "CHL";
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.NUMBER_OF_CHANNELS_USED, 0, bsPacketIdx, 0,
			"IFW_TAP3.NumberOfChannelsUsed.NUMBER_OF_CHANNELS_USED");
        if (numberOfChannelsUsedIsMissing == true)
	{
	 edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.NUMBER_OF_CHANNELS_USED, 0, bsPacketIdx, 0);
	 numberOfChannelsUsedIsMissing = false;
        }
      }
      IFW_TAP3.Block_END
    ;

    basicHSCSDParameters_mandopt:
	basicHSCSDParameters
    | /* EMPTY */
      {
        // Set sever error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT.HSCSD_INFO_PACKET, 0, bsPacketIdx));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "124", "5", offset, "-1", "Missing basic HSCSC Parameter");
        setAssociatedTapErr("ERR_TAP3_MISSING_BASIC_HSCC_PARAM", 3,"30" ,"124" ,"5");	
      }
    ;

  basicService:
      IFW_TAP3.BasicService
      basicServiceCode_mandopt
      radioChannelRequested_opt
      radioChannelUsed_opt
      speechVersionRequested_opt
      speechVersionUsed_opt
      transparencyIndicator_opt
      fnur_opt
      aiurRequested_opt
      userProtocolIndicator_opt
      IFW_TAP3.Block_END
    ;

  basicService_mandopt:
      basicService
    | /* EMPTY */
      {
        // Set sever error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT.BS_PACKET, 0));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "38", "4", offset, "-1", "Missing bassic service");
        setAssociatedTapErr("ERR_TAP3_MISSING_BASIC_SERVICE", 3,"30" ,"38" ,"4");	
      }
    ;

  basicServiceCode:
      IFW_TAP3.TeleServiceCode
      {
        edrConnectToken(DETAIL.BASIC_SERVICE, "IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE");
        edrString(DETAIL.BASIC_SERVICE) = "0" + edrString(DETAIL.BASIC_SERVICE) ;
        edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.BASIC_SERVICE, 0, bsPacketIdx) = edrString(DETAIL.BASIC_SERVICE) ;

        // The TeleServiceCode for Emergency call is 12.
        // Check if the call is not an Emergency Call i.e. TeleServiceCode != 12,
        // and the Destination field is missing.
        // Since the Destination field comes in to picture only for MOC,
        // the check for record type has been added. This is because this part
        // of the code will be executed for MTC also.
        if ( (strToLong(edrString(DETAIL.BASIC_SERVICE)) != 12) and
             (destinationIsMissing == true) and
             (edrString(DETAIL.RECORD_TYPE) == type_MOC) )
        {
          // If Destination field is missing when the call is not an emergency call,
          // then raise the appropriate error.
          String offset = "-1";

          edrAddError("ERR_TAP3_RET", 3, "severe", "35", "147", "5",
                offset, "-1", "Missing Destination when the call is not an emergency call");
          setAssociatedTapErr ("ERR_TAP3_MISSING_DESTINATION", 3, "35", "147", "5");
        }
      }
    | IFW_TAP3.BearerServiceCode
      {
        edrConnectToken(DETAIL.BASIC_SERVICE, "IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE");
        edrString(DETAIL.BASIC_SERVICE) = "1" + edrString(DETAIL.BASIC_SERVICE) ;
	edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.BASIC_SERVICE, 0, bsPacketIdx) = edrString(DETAIL.BASIC_SERVICE);
      }
    ;

  basicServiceCode_mandopt:
      basicServiceCode
    | /* EMPTY */
      {
       // Set an error code
       edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.BASIC_SERVICE, 0, bsPacketIdx);
      }
    ;

  basicServiceCodeSS:
      IFW_TAP3.TeleServiceCode
      {
       // Adding suffix "0" to identify it as TeleServiceCode
       lastbasicServiceCodeSS = lastbasicServiceCodeSS + "0" + tokenString("IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE") + ",";
      }
    | IFW_TAP3.BearerServiceCode
      {
       // Adding suffix "1" to identify it as BearerServiceCode
       lastbasicServiceCodeSS = lastbasicServiceCodeSS + "1" + tokenString("IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE") + ",";
      }
    ;


  basicServiceCodeList:  //only used for supplementary services affected Basic Services
      basicServiceCodeList
      basicServiceCodeSS
      {
        SsBasicServicesAffected[SsBasicServicesAffectedNb] = lastBasicService ;
        SsBasicServicesAffectedNb                          = SsBasicServicesAffectedNb +1;
      }
    | basicServiceCodeSS
      {
        SsBasicServicesAffected[SsBasicServicesAffectedNb] = lastBasicService ;
        SsBasicServicesAffectedNb                          = SsBasicServicesAffectedNb +1;
      }
    ;

  basicServiceCodeList_opt:
      IFW_TAP3.BasicServiceCodeList
      {
        SsBasicServicesAffectedNb                          = 0; // initialisation
	lastbasicServiceCodeSS				   = "";
      }
      basicServiceCodeList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        SsBasicServicesAffectedNb                          = 0; // initialisation
	lastbasicServiceCodeSS				   = "";
      }
    ;

  basicServiceCodeList_opt2:
      basicServiceCodeList
    | /* EMPTY */ //accept empty list
    ;

  basicServiceUsed:
      IFW_TAP3.BasicServiceUsed
      {
        newBasicServiceBlock();
        service_Type                    =service_Basic;
        lastBasicService                ="011"; // default
      }
      basicService_mandopt
      chargingTimeStamp_opt
      chargeInformationList_mandopt
      {
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      dataVolumeReference_opt
      hSCSDInformation_opt
      IFW_TAP3.Block_END
    ;

  basicServiceUsedList:
      basicServiceUsedList
      basicServiceUsed
    | basicServiceUsed
    ;

  basicServiceUsedList_mandopt:
      IFW_TAP3.BasicServiceUsedList
      basicServiceUsedList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
      // Error code will be set within the I Rules
      }
    ;

  basicServiceUsedList_opt2:
      basicServiceUsedList
    | /* EMPTY */
    ;

  calledNumAnalysis:
      IFW_TAP3.CalledNumAnalysis
      calledNumAnalysisCode_opt
      {
        calledNumberAnalysisCode[lastCode]      = lastCalledNumAnalysisCode;
      }
      countryCodeList_mandopt
      {
        calledNumberAnalysisCC[lastCode]        = lastCalledNumberAnalysisCC; //we store only the last element
      }
      iacList_mandopt
      {
        calledNumberAnalysisIAC[lastCode]       = lastCalledNumberAnalysisIAC; //we store only the last element
        lastCode                                = lastCode+1;
        calledNumberAnalysisEntries             = lastCode;
      }
      IFW_TAP3.Block_END
    ;

  calledNumAnalysisCode_opt:
      IFW_TAP3.CalledNumAnalysisCode
      {
        lastCalledNumAnalysisCode       = tokenLong("IFW_TAP3.CalledNumAnalysisCode.CALLED_NUM_ANALYSIS_CODE");
      }
    | /* EMPTY */
      {
        lastCalledNumAnalysisCode       = 0; // when only one entry, it can be omitted
      }
    ;

   calledNumAnalysisList_opt:
      IFW_TAP3.CalledNumAnalysisList
      {
        lastCode = 0;
      }
      calledNumAnalysisList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  calledNumAnalysisList_opt2:
      calledNumAnalysisList
    | /* EMPTY */ //accept empty list
    ;

  calledNumAnalysisList:
      calledNumAnalysisList
      calledNumAnalysis
    |
      calledNumAnalysis // first element of the list
    ;

  calledNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        edrString(DETAIL.B_NUMBER)             = strIAC + tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
        edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0) = edrString(DETAIL.B_NUMBER);
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0);
      }
    ;

  calledPlace_opt:
      IFW_TAP3.CalledPlace
      {
        edrConnectToken(DETAIL.DESCRIPTION, "IFW_TAP3.CalledPlace.CALLED_PLACE");
      }
    | /* EMPTY */
    ;

  calledRegion_opt:
      IFW_TAP3.CalledRegion
      {
          String tmpDescription = edrString(DETAIL.DESCRIPTION);
          tmpDescription = tmpDescription + "," + tokenString("IFW_TAP3.CalledRegion.CALLED_REGION");
          edrString(DETAIL.DESCRIPTION) = tmpDescription;
      }
    | /* EMPTY */
    ;

  callEventDetail:
      mobileOriginatedCall
    | mobileTerminatedCall
    | supplServiceEvent
    | serviceCentreUsage
    | valueAddedService
    | gprsCall
    | contentTransaction
    | locationService
    ;

  callEventDetailList:
      callEventDetailList
      callEventDetailListElem
    | callEventDetailListElem
    ;

  callEventDetailListElem:
      {
        tap3Detail = tap3Detail +1;
        errorStateTap3 = beginTap3Detail;
      }
      callEventDetail
      {
        errorStateTap3 = endTap3Detail;
        // delete of the unused duplicated edr (for MOC and MTC)
        if ( (record_Type == record_MOC) or (record_Type == record_MTC) )
        {
          if (successiveBasicServiceUsed > 1)
          {
            edrString(DETAIL.LONG_DURATION_INDICATOR) = "L"; // the last record of a chain
          }
//          if ( edrSetCurrent( theLastEdrCopy ) == true )
//          {
//            edrDelete();
//            theLastEdrCopy = 0;
//          }
//          else
//          {
//            String Msg = "edrSetCurrent(theLastEdrCopy) FAILED before edrDelete()";
//            edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);
//         }
        }
      }
    ;

  callEventDetailList_opt2:
      callEventDetailList
    | /* EMPTY */
      {
        /* Set Fatal Error */
        requestBatchReject(1, -1, 1,  0,  35, "ERR_TAP3_MISSING_CALL_EVENT_DETAILS");
      }
    ;

  callEventDetails_mandopt:
      IFW_TAP3.CallEventDetailList
      {
        createNewGarbageCollectorDetail();
        errorStateTap3 = beginTap3DetailList;
      }
      callEventDetailList_opt2
      {
        errorStateTap3 = endTap3DetailList;
      }
      IFW_TAP3.Block_END
      {
        createNewGarbageCollectorDetail();
      }
    | /* EMPTY */
      {
        /* Set Fatal Error */
        requestBatchReject(1, -1, 1,  0,  35, "ERR_TAP3_MISSING_CALL_EVENT_DETAILS");
      }
    ;

  callEventDetailsCount_mandopt:
      IFW_TAP3.CallEventDetailsCount
      {
       edrConnectToken(TRAILER.TAP_TOTAL_NUMBER_OF_RECORDS, "IFW_TAP3.CallEventDetailsCount.CALL_EVENT_DETAIL_COUNT");
      }
    | /* EMPTY */
      {
       edrMissingInput(TRAILER.TAP_TOTAL_NUMBER_OF_RECORDS);
      }
    ;

  callEventStartTimeStamp:
      IFW_TAP3.CallEventStartTimeStamp
      {
        timeStampType = callEventStartTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
      {
        //mandatory field for MOC, MTC, GPRS,  will serve as a default timestamp
        lastValidLocalTimeStamp = lastLocalTimeStamp; // to serve as default LocalTimeStamp for coresponding record
        lastValidUtcTimeOffset  = lastUtcTimeOffset;  // to serve as default UtcTimeOffset for coresponding record
      }
    ;

  callEventStartTimeStamp_mandopt:
      callEventStartTimeStamp
    | /* EMPTY */
      {
        // Set error code
	edrMissingInput(DETAIL.CHARGING_START_TIMESTAMP);
      }
    ;

  callOriginator_opt:
      IFW_TAP3.CallOriginator
      {
        callNumberType = callOriginatorType;
      }
      callingNumber_opt
      clirIndicator_opt
      {
          // for optimization resons we are populating ClirIndicator in DEATIL.USAGE_CLASS
          edrConnectToken(DETAIL.USAGE_CLASS,"IFW_TAP3.ClirIndicator.CLIR_INDICATOR");
      }
      IFW_TAP3.Block_END
      {
        // normalize the number
        // edrString(DETAIL.B_NUMBER) = convertCli(edrString(DETAIL.B_NUMBER),
        //                                         edrString(DETAIL.B_MODIFICATION_INDICATOR),
        //                                         edrLong(DETAIL.B_TYPE_OF_NUMBER),
        //                                         NORM_NAC,
        //                                         calledNumberAnalysisIACarray[0], // NORM_IAC,
        //                                         calledNumberAnalysisCCarray[0], // NORM_CC,
        //                                         NORM_IAC_SIGN,
        //                                         NORM_NDC );
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0);
      }
    ;

  callTypeGroup_opt:
      IFW_TAP3.CallTypeGroup
      callTypeLevel1_mandopt
      callTypeLevel2_mandopt
      callTypeLevel3_mandopt
      calledCountryCode_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        // Set error code
      }
    ;

  callTypeLevel1_mandopt:
      IFW_TAP3.CallTypeLevel1
      {
        edrConnectToken(DETAIL.CONNECT_TYPE, "IFW_TAP3.CallTypeLevel1.CALL_TYPE_LEVEL");
      }
    | /* EMPTY */
      {
        // Set error code
	edrMissingInput(DETAIL.CONNECT_TYPE);
      }
    ;

  callTypeLevel2_mandopt:
      IFW_TAP3.CallTypeLevel2
      {
        edrString(DETAIL.CONNECT_TYPE) = edrString(DETAIL.CONNECT_TYPE)
                                       + longToStr(tokenLong("IFW_TAP3.CallTypeLevel2.CALL_TYPE_LEVEL"));
      }
    | /* EMPTY */
      {
        // Set error code
	// Missing condition will be handled in TAP Detail Validation
      }
    ;

  callTypeLevel3_mandopt:
      IFW_TAP3.CallTypeLevel3
      {
        edrConnectToken(DETAIL.CONNECT_SUB_TYPE, "IFW_TAP3.CallTypeLevel3.CALL_TYPE_LEVEL");
      }
    | /* EMPTY */
      {
        // Set error code
	edrMissingInput(DETAIL.CONNECT_SUB_TYPE);
      }
    ;

  calledCountryCode_opt:
      IFW_TAP3.CalledCountryCode
      {
        edrConnectToken(DETAIL.CALLED_COUNTRY_CODE, "IFW_TAP3.CalledCountryCode.CALLED_COUNTRY_CODE");
      }
    | /* EMPTY */
      {
        // Set error code
        edrMissingInput(DETAIL.CALLED_COUNTRY_CODE);
      }
    ;

  callingNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        edrString(DETAIL.B_NUMBER)             = strIAC + tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
        edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
	edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0) = strIAC +
                  tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0);
      }
    ;

  camelCallReference_opt:
      IFW_TAP3.CamelCallReference
      {
        callNumberType = camelCallReferenceType;
      }
      camelMscAddress_mandopt
      camelReferenceNumber_mandopt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

 camelDestinationNumber:
      IFW_TAP3.AddressStringDigits
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0,
                        "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        // edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0) =
        //                 convertCli(edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0),
        //                            "00",
        //                            edrLong(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_TYPE_OF_NUMBER, 0),
        //                            NORM_NAC,
        //                            calledNumberAnalysisIACarray[0], // NORM_IAC,
        //                            calledNumberAnalysisCCarray[0], // NORM_CC,
        //                            NORM_IAC_SIGN,
        //                            NORM_NDC );
        edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0) = strIAC +
		edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0);
      }
    ;

  threeGcamelDestination_opt:
      camelDestinationNumber
    | gprsDestination
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0);
      }
    ;

  camelInitiatedCFIndicator_opt:
      IFW_TAP3.CamelInitiatedCFIndicator
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.CAMEL_INITIATED_CF_INDICATOR, 0,
                        "IFW_TAP3.CamelInitiatedCFIndicator.CAMEL_INITIATED_CF_INDICATOR");
      }
    | /* EMPTY */
	{
	edrMissingInput(DETAIL.ASS_CAMEL_EXT.CAMEL_INITIATED_CF_INDICATOR, 0);
	}
    ;

  camelModificationList:
      camelModificationList
      IFW_TAP3.CamelModification
      {
        lastCamelModificationList = lastCamelModificationList + ", " +
                                    longToStr( tokenLong("IFW_TAP3.CamelModification.CAMEL_MODIFICATION") );
      }
    | IFW_TAP3.CamelModification
      {
        lastCamelModificationList = longToStr( tokenLong("IFW_TAP3.CamelModification.CAMEL_MODIFICATION") );
        // token connection to the first element of the list
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.CAMEL_MODIFICATION_LIST, 0, "IFW_TAP3.CamelModification.CAMEL_MODIFICATION");
      }
    ;

  camelModificationList_opt:
      IFW_TAP3.CamelModificationList
      {
        lastCamelModificationList = "";
      }
      camelModificationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CAMEL_EXT.CAMEL_MODIFICATION_LIST, 0);
        lastCamelModificationList = "";
      }
    ;

  camelModificationList_opt2:
      camelModificationList
    | /* EMPTY */ //accept empty list
    ;

  camelMscAddress_mandopt:
      IFW_TAP3.AddressStringDigits         // mscAddress
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
	// Normalize the number
	edrString(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0) = strIAC + edrString(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0);
      }
    | /* EMPTY */
      {
       edrMissingInput(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0);
      }
    ;

  camelReferenceNumber_mandopt:
      IFW_TAP3.CamelCallReferenceNumber
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.CAMEL_REFERENCE_NUMBER, 0,
                        "IFW_TAP3.CamelCallReferenceNumber.CAMEL_CALL_REFERENCE_NUMBER");
      }
    | /* EMPTY */
     {
      edrMissingInput(DETAIL.ASS_CAMEL_EXT.CAMEL_REFERENCE_NUMBER, 0);
     }
    ;

  camelServerAddress_mandopt:
      IFW_TAP3.CamelServerAddress  //camelServerAddress
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0, "IFW_TAP3.CamelServerAddress.CAMEL_SERVER_ADDRESS");
	// Normalize the number
        edrString(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0) = strIAC + edrString(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0);
      }
    | /* EMPTY */
      {
        // Set error code
	edrMissingInput(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0);
      }
    ;

  camelServiceKey_mandopt:
      IFW_TAP3.CamelServiceKey
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVICE_KEY, 0, "IFW_TAP3.CamelServiceKey.CAMEL_SERVICE_KEY");
      }
    | /* EMPTY */
      {
       // Set error code
       edrMissingInput(DETAIL.ASS_CAMEL_EXT.SERVICE_KEY, 0);
      }
    ;

  camelServiceLevel_mandopt:
      IFW_TAP3.CamelServiceLevel
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVICE_LEVEL, 0, "IFW_TAP3.CamelServiceLevel.CAMEL_SERVICE_LEVEL");
      }
    | /* EMPTY */
      {
       // Set error code
       edrMissingInput(DETAIL.ASS_CAMEL_EXT.SERVICE_LEVEL, 0);
      }
    ;

  camelServiceUsed_opt:
      IFW_TAP3.CamelServiceUsed
      {
        service_Type = service_Camel;
        if ( edrAddDatablock( DETAIL.ASS_CAMEL_EXT ) == false )
        {
          String Msg = "failed to add ASS_CAMEL_EXT datablock for EDR "+longToStr(records);
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg); //TODO check for consequences
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        }
        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)       = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_CAMEL_EXT.RECORD_TYPE, 0)  = extension_CAMEL;
        edrLong(DETAIL.ASS_CAMEL_EXT.RECORD_NUMBER, 0)  = records;
	related_record = records;

        callNumberType = camelServerType;
      }
      camelServerAddress_mandopt
      camelServiceLevel_mandopt
      camelServiceKey_mandopt
      defaultCallHandlingIndicator_opt
      camelCallReference_opt
      chargeInformation_opt
      {
        // add the charge info provided by the Camel ChargeDetail block to the global Detail
        updateBasicDetailWithCamelCharge();
      }
      camelInitiatedCFIndicator_opt
      camelModificationList_opt
      {
        edrString(DETAIL.ASS_CAMEL_EXT.CAMEL_MODIFICATION_LIST, 0) = lastCamelModificationList;
      }
      threeGcamelDestination_opt
      cseInformation_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        // set missing
	edrMissingInput(DETAIL.ASS_CAMEL_EXT.RECORD_TYPE, 0);
      }
    ;

  causeForTerm_opt:
      IFW_TAP3.CauseForTerm
      {
        // CALL_COMPLETION_INDICATOR must be stored in a 2 digit string (prepend with 0 if necessary)
        edrConnectToken(DETAIL.CALL_COMPLETION_INDICATOR, "IFW_TAP3.CauseForTerm.CAUSE_FOR_TERM");
        if (tokenLong("IFW_TAP3.CauseForTerm.CAUSE_FOR_TERM") < 10)
        {
          edrString(DETAIL.CALL_COMPLETION_INDICATOR) = "0" + edrString(DETAIL.CALL_COMPLETION_INDICATOR);
        }
      }
    | /* EMPTY */
      {
        // set missing
	edrMissingInput(DETAIL.CALL_COMPLETION_INDICATOR);
      }
    ;

  cellId_opt:
      IFW_TAP3.CellId
      {
        String nullFiller = buildNullFiller(5, strLength( tokenString("IFW_TAP3.CellId.CELL_ID") ) );
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.CELL_ID, 0, "IFW_TAP3.CellId.CELL_ID");
          if (nullFiller!="")
          {
            edrString(DETAIL.ASS_GPRS_EXT.CELL_ID, 0)=
                strReplace(tokenString("IFW_TAP3.CellId.CELL_ID"), 0, 0,  nullFiller);
          }
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.CELL_ID, 0, "IFW_TAP3.CellId.CELL_ID");
          if (nullFiller!="")
          {
            edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0)=
                strReplace(tokenString("IFW_TAP3.CellId.CELL_ID"), 0, 0,  nullFiller);
          }
        }
      }
    | /* EMPTY */
      {
        // set missing
        if (record_Type == record_GPRS)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.CELL_ID, 0);
	}
	else
	{
	  edrMissingInput(DETAIL.ASS_GSMW_EXT.CELL_ID, 0);
	}
      }
      ;

  channelCoding_basicHSCSD_mandopt:
      IFW_TAP3.ChannelCoding
      {
       edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.CHANNEL_CODING_USED, 0, bsPacketIdx, 0,
			"IFW_TAP3.ChannelCoding.CHANNEL_CODING");
      }

    | /* EMPTY */
      {
        // Set error code
	edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.CHANNEL_CODING_USED, 0, bsPacketIdx, 0);
      }
    ;

  channelCoding_mandopt:
      IFW_TAP3.ChannelCoding
      {
       edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.CHANNEL_CODING_USED, 0, bsPacketIdx, 0, pmidx,
			"IFW_TAP3.ChannelCoding.CHANNEL_CODING");
      }

    | /* EMPTY */
      {
        // Set error code
	edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.CHANNEL_CODING_USED, 0, bsPacketIdx, 0, pmidx);
      }
    ;

  channelCodingAcceptableList:
      channelCodingAcceptableList
      IFW_TAP3.ChannelCoding
      {
        lastChannelCoding = lastChannelCoding + ", " +
			longToStr(tokenLong("IFW_TAP3.ChannelCoding.CHANNEL_CODING"));
      }
    | IFW_TAP3.ChannelCoding
      {
        lastChannelCoding = longToStr(tokenLong("IFW_TAP3.ChannelCoding.CHANNEL_CODING"));
      }
    ;

  channelCodingAcceptableList_mandopt:
      IFW_TAP3.ChannelCodingAcceptableList
      {
        lastChannelCoding = "";
      }
      channelCodingAcceptableList
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastChannelCoding = "";
	edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.CHANNEL_CODING_OK_LIST, 0, bsPacketIdx, 0);
      }
    ;

  chargeableUnits_opt:
      IFW_TAP3.ChargeableUnits
      {
        lastChargeableUnits = tokenLong("IFW_TAP3.ChargeableUnits.CHARGEABLE_UNITS");
        edrConnectToken(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, ACBidx, CPidx,
                        "IFW_TAP3.ChargeableUnits.CHARGEABLE_UNITS");
        // edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, ACBidx, CPidx) =
        //            longToDecimal(lastChargeableUnits); //TODO CONNECT
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, ACBidx, CPidx);
        lastChargeableUnits = 0;
      }
    ;

  chargeableSubscriber:
      simChargeableSubscriber
    | minChargeableSubscriber
    ;

  chargeableSubscriber_mandopt:
      chargeableSubscriber
    | /* EMPTY */
      {
        // Set severe error code
        if ( (record_Type == record_MSS) )
        {
          // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
	  String offset = "-1";
          edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
          // edrAddError("ERR_TAP3_RET", 3, "severe", "21", tag, depth, offset, arrayIndex, ruleID);
          edrAddError("ERR_TAP3_RET", 3, "severe", "30", "11", "3", offset, "-1", "Missing Chargeableable Subscriber ");
          setAssociatedTapErr("ERR_TAP3_MISSING_CHARGEABLE_SUBCRIBER", 3,"30" ,"11" ,"3");	
        }
        else if ( (record_Type == record_MOC) )
        {
          // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
	  String offset = "-1";
          edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
          // edrAddError("ERR_TAP3_RET", 3, "severe", "21", tag, depth, offset, arrayIndex, ruleID);
          edrAddError("ERR_TAP3_RET", 3, "severe", "30", "147", "4", offset, "-1", "Missing Chargeableable Subscriber ");
          setAssociatedTapErr("ERR_TAP3_MISSING_CHARGEABLE_SUBCRIBER", 3,"30" ,"147" ,"4");	
        }
        else if ( (record_Type == record_MTC) )
        {
          // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
	  String offset = "-1";
          edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
          // edrAddError("ERR_TAP3_RET", 3, "severe", "21", tag, depth, offset, arrayIndex, ruleID);
          edrAddError("ERR_TAP3_RET", 3, "severe", "30", "153", "4", offset, "-1", "Missing Chargeableable Subscriber ");
          setAssociatedTapErr("ERR_TAP3_MISSING_CHARGEABLE_SUBCRIBER", 3,"30" ,"153" ,"4");	
        }
      }
    ;

  chargedUnits_opt:
      IFW_TAP3.ChargedUnits
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, ACBidx, CPidx,  "IFW_TAP3.ChargedUnits.CHARGED_UNITS");
        lastChargedUnits = tokenLong("IFW_TAP3.ChargedUnits.CHARGED_UNITS");
      }
    | /* EMPTY */
      {
        lastChargedUnits = 0;
	// Set missing
	edrMissingInput(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, ACBidx, CPidx);
      }
    ;

  chargeDetail:
      IFW_TAP3.ChargeDetail
      {
        successiveChargeDetail = successiveChargeDetail +1;
//logStdout("successive chargeDetail block number "+longToStr(successiveChargeDetail)+
//" for chargeInformation"+longToStr(successiveChargeInformation)+" for EDR "+
//longToStr(edrLong(DETAIL.RECORD_NUMBER))+"\n");
        initializeChargeDetailTempFields();

        // add the CP(s) for BasicServiceUsed / GprsServiceUsed / CamelServiceUsed / VasServiceUsed /
        //                   MSSrecord / SCUrecord / CONTrecord / LOCNrecord
//        if ( (service_Type == service_Basic) or
//             (service_Type == service_Gprs) or
//             (service_Type == service_Camel) or
//             (service_Type == service_Vas) or
//             (service_Type == service_Suppl) or
//             (record_Type == record_SCU) or
//             (record_Type == record_CONT) or
//             (record_Type == record_LOCN))
        {
          if ( edrAddDatablock( DETAIL.ASS_CBD.CP ) == false )
          {
            String Msg ="failed to add CHARGE_PACKET datablock " + longToStr(successiveChargeDetail) +
                        " for ASS_CBD " + longToStr(successiveChargeInformation) +
                        " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
            edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

          }
          CPidx                    = successiveChargePacket;
          successiveChargePacket   = successiveChargePacket   +1;
          successiveChargePacketCI = successiveChargePacketCI +1;

          records = records+1;
          edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
          edrString(DETAIL.ASS_CBD.CP.RECORD_TYPE, ACBidx, CPidx) = extension_CP;
          edrLong(DETAIL.ASS_CBD.CP.RECORD_NUMBER, ACBidx, CPidx) = records;
          edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, ACBidx, CPidx) = related_record;
          edrLong(DETAIL.ASS_CBD.CP.RELATED_CHARGE_INFO_ID, ACBidx, CPidx) = related_info_id;

        }
        //defaults
//      edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, ACBidx, CPidx)          = "R"; // overwritten below
        edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, ACBidx, CPidx)     = "*";
        edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, ACBidx, CPidx)        = "S";
        edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, ACBidx, CPidx)            = "N";
        edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, ACBidx, CPidx)  = "R";
        edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, ACBidx, CPidx)  = "N";
        edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, ACBidx, CPidx)          = "W";
      }
      chargeType_opt
      charge_opt
      chargeableUnits_opt
      chargedUnits_opt
      chargeDetailTimeStamp_opt
      dayCategory_mandopt
      dayCategorySubtype_opt
      timeBand_mandopt
      timeBandSubtype_opt
      multiRateIndicator_opt
      {
        // add the CP(s) for BasicServiceUsed / GprsServiceUsed / CamelServiceUsed / VasServiceUsed /
        //                   MSSrecord / SCUrecord / CONTrecord / LOCNrecord
//        if ( (service_Type == service_Basic) or
//             (service_Type == service_Gprs) or
//             (service_Type == service_Camel) or
//             (service_Type == service_Vas) or
//             (service_Type == service_Suppl) or
//             (record_Type == record_SCU) or
//             (record_Type == record_CONT) or
//             (record_Type == record_LOCN))
        {
          // Store the collected data
          Decimal ChargedAmountValue = (lastCharge * lastExchangeRateFactor); //after discount, before tax
          edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, ACBidx, CPidx)  = ChargedAmountValue ; // connected in block charge_opt

          edrString(DETAIL.ASS_CBD.CP.RUM, ACBidx, CPidx)                    = lastChargedItem; //cannot be connected !!

          // used for aggregation packet special treatement
          if ( lastChargeType == "00" )
          {
            lastCPidx_00                                                = CPidx;
            lastChargedAmountValue_00                                   = ChargedAmountValue;
            lastChargeableUnits_00                                      = lastChargeableUnits;
            lastChargedUnits_00                                         = lastChargedUnits;
          }

          if (bUseLocalCurrency)
          {
            edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, CPidx)= theLocalCurrency;
            edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, CPidx)         = (1.0 / lastExchangeRateFactorValue); //connected in block exchangeRateCode_opt
            edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, CPidx)      = theTapCurrency;

	    if (theLocalCurrencyIsMissing == true)
            {
	      edrMissingInput(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, CPidx);
            }
	    else if (theLocalCurrency == "")
	    {
	      edrEmptyInput(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, CPidx);
            }
          }
          else
          {
            edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, CPidx)= theTapCurrency;
            edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, CPidx)         = lastExchangeRateFactorValue; //connected in block exchangeRateCode_opt
            edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, CPidx)      = theLocalCurrency;

	    if (theLocalCurrencyIsMissing == true)
            {
	      edrMissingInput(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, CPidx);
            }
	    else if (theLocalCurrency == "")
	    {
	      edrEmptyInput(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, CPidx);
            }
          }

          edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, CPidx)   = strToDate(lastChargeDetailTimeStamp);//cannot be connected

          if ( service_Type == service_Vas )
          {
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, ACBidx, CPidx)       = getVasShortDesc( lastVasCode );
          }
          else if ( service_Type == service_Camel )
          {
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, ACBidx, CPidx)       = "CAMEL";
          }

          // summing of values to store afterwards on the DETAIL level
          sumChargedAmountValueCI = sumChargedAmountValueCI     + ChargedAmountValue;
          sumChargeableUnitsCI    = sumChargeableUnitsCI        + lastChargeableUnits;
          sumChargedUnitsCI       = sumChargedUnitsCI           + lastChargedUnits;
          if      (lastChargedItem == "D") //Duration
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, CPidx)   = "SEC";
          }
          else if ( (lastChargedItem == "V") or (lastChargedItem == "X") ) //Volume sent / Volume global
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, CPidx)   = "BYT";
          }
          else if (lastChargedItem == "W") //Volume received
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, CPidx)   = "BYT";
          }
          else if (lastChargedItem == "E") //Event
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, CPidx)   = "CLK";
          }
          else
          {
            //nothing
          }
        }
      }
      IFW_TAP3.Block_END
    ;

  chargeDetailTimeStamp_opt:
      IFW_TAP3.ChargingTimeStamp
      {
        timeStampType = chargeDetailTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
      {
        lastChargeDetailTimeStamp = lastLocalTimeStamp; //TODO check if we really dont need the utcTimeOffset
      }
    | /* EMPTY */
      {
        lastChargeDetailTimeStamp = lastValidLocalTimeStamp;
      }
    ;

  chargeDetailList:
      chargeDetailList chargeDetail
    | chargeDetail
    ;

  chargeDetailList_mandopt:
      IFW_TAP3.ChargeDetailList
      chargeDetailList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
       // Validation will be done within I rules
      }
    ;

  chargeDetailList_opt2:
      chargeDetailList
    | /* EMPTY */
    ;

  chargeInformation_bs:
      {
        related_info_id = related_info_id + 1;
      }
      chargeInformation
    ;

  chargeInformation:
      IFW_TAP3.ChargeInformation
      {
        successiveChargeInformation     = successiveChargeInformation +1;
        successiveChargeInformationPerBS     = successiveChargeInformationPerBS +1;
        initializeChargeDetailTempFields();
        successiveChargeDetail          = 0;
        successiveTaxDetail             = 0;
        successiveChargePacketCI        = 0;

        lastCPidx_00                    = (-1); //invalid, ie. not received
        lastChargedAmountValue_00       = 0.0;
        lastChargeableUnits_00          = 0;
        lastChargedUnits_00             = 0;

        sumTaxChargeCI                  = 0.0;
        sumTaxAmountCI                  = 0.0;
        sumChargedAmountValueCI         = 0.0;
        sumChargeableUnitsCI            = 0;
        sumChargedUnitsCI               = 0;
	
        lastDiscountValueCI             = 0.0;   // Initialize CI block sum to 0
	
        exchangeRateCodeIsMissing       = false; // Initialize ExchangeRateCode to be non-empty

//	related_info_id = related_info_id + 1;

        // create only one ASS_CBD per BasicServiceUsed / GprsServiceUsed /
        //                             MSSrecord / SCUrecord / VASrecord / CONTrecord / LOCNrecord
        if ( (service_Type == service_Basic) or
             (service_Type == service_Gprs) or
             (record_Type == record_MSS) or
             (record_Type == record_SCU) or
             (record_Type == record_VAS) or
             (record_Type == record_CONT) or
             (record_Type == record_LOCN)
           )
        {
	  // Create multiple ASS_CBD, one for each BasicServiceUsed
	  // successiveChargeInformationPerBS is checked for this which is reset when a new 
	  // Basic service is created.
          if ((successiveChargeInformation == 1) or (successiveChargeInformationPerBS == 1))
          {
            ACBidx	= successiveChargeInformation - 1;
            if ( edrAddDatablock( DETAIL.ASS_CBD ) == false )
            {
              String Msg = "failed to add ASS_CBD datablock "+longToStr(successiveChargeInformation)+
                           " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
              edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

            }
            records = records+1;
            edrLong( DETAIL.NUMBER_ASSOCIATED_RECORDS)= edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
            edrString( DETAIL.ASS_CBD.RECORD_TYPE, ACBidx) = extension_CBD;
            edrLong( DETAIL.ASS_CBD.RECORD_NUMBER, ACBidx) = records;

          }
        }
      }
      chargedItem_mandopt
      exchangeRateCode_opt
      callTypeGroup_opt
      chargeDetailList_mandopt
      {
        // Check that the aggragation chargeDetail (ie ChargeType=="00") is not a duplicate of real charges.
        if ( lastCPidx_00 >= 0 )
        {
          // if more than 1 CP was added
          if (successiveChargePacketCI > 1)
          {
            // if the sum of all ChargedAmountValue is more than that of the aggregation packet
            // then it means that it is really used for charge aggragation (ie it duplicates the charges)
            if ( sumChargedAmountValueCI > lastChargedAmountValue_00 )
            {
              // decrement the sum counters
              sumChargedAmountValueCI   = lastChargedAmountValue_00;
              // flag the aggregation CP as duplicate (Alternative Price model) //TODO check if this is enough
              edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, ACBidx, lastCPidx_00) = "A";
            }
            // same thing for the ChargeableUnits
            if ( lastChargeableUnits_00 > 0 )
            {
              sumChargeableUnitsCI = lastChargeableUnits_00;
            }
            // same thing for the ChargedUnits
            if ( lastChargedUnits_00 > 0 )
            {
              sumChargedUnitsCI = lastChargedUnits_00;
            }
          }
        }
        // update the sums on the Charge information level
        sumChargedAmountValueFile       = sumChargedAmountValueFile             + sumChargedAmountValueCI;
        sumChargedAmountValueEDR        = sumChargedAmountValueEDR              + sumChargedAmountValueCI;
	sumChargedAmountValueBS		= sumChargedAmountValueBS		+ sumChargedAmountValueCI;

        if      (lastChargedItem == "D") //Duration
        {
          sumChargeableUnitsDuration    = sumChargeableUnitsDuration            + sumChargeableUnitsCI;
        }
        else if ( (lastChargedItem == "V") or (lastChargedItem == "X") ) //Volume sent / Volume global
        {
          sumChargeableUnitsVolumeSent  = sumChargeableUnitsVolumeSent          + sumChargeableUnitsCI;
        }
        else if (lastChargedItem == "W") //Volume received
        {
          sumChargeableUnitsVolumeReceived= sumChargeableUnitsVolumeReceived    + sumChargeableUnitsCI;
        }
        else if (lastChargedItem == "E") //Event
        {
          sumChargeableUnitsEvents      = sumChargeableUnitsEvents              + sumChargeableUnitsCI;
          sumChargeableUnitsEventsBS    = sumChargeableUnitsEventsBS            + sumChargeableUnitsCI;
        }

        //make sure a CP for ChargeType=="00" is the last CP (if not, create it or move it)
        if (lastCPidx_00 >= 0) // if there is a ChargeType=="00" packet
        {
          //if it is not the last of the list, duplicate it at the end
          if (lastCPidx_00 != (successiveChargePacket-1))
          {
            if ( edrAddDatablock( DETAIL.ASS_CBD.CP ) == false )
            {
              String Msg = "failed to add CHARGE_PACKET datablock " + longToStr(successiveChargeDetail) +
                           " for ASS_CBD " + longToStr(successiveChargeInformation) +
                           " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
              edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

            }
            CPidx                    = successiveChargePacket;
            successiveChargePacket   = successiveChargePacket   +1;
            successiveChargePacketCI = successiveChargePacketCI +1;

            records = records+1;
            edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)          = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
            edrString(DETAIL.ASS_CBD.CP.RECORD_TYPE, ACBidx, CPidx) = extension_CP;
            edrLong(DETAIL.ASS_CBD.CP.RECORD_NUMBER, ACBidx, CPidx) = records;
            edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, ACBidx, CPidx) = related_record;
            edrLong(DETAIL.ASS_CBD.CP.RELATED_CHARGE_INFO_ID, ACBidx, CPidx) = related_info_id;

            // flag the original aggregation packet as not aggregation CP and as duplicate
            edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, ACBidx, lastCPidx_00)    = "A";
            edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, ACBidx, lastCPidx_00)    = ""; //so that it is not recorgnized by the output

            //defaults
//          edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, ACBidx, CPidx)             = "R"; //default is overwritten a few lines after
            edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, ACBidx, CPidx)        = "*";
//          edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, ACBidx, CPidx)           = "S";
            edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, ACBidx, CPidx)               = "N";
            edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, ACBidx, CPidx)     = "R";
            edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, ACBidx, CPidx)     = "N";
            // duplicated
            edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, ACBidx, CPidx)             = "W";
            edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, ACBidx, CPidx)           = "A";
            edrString(DETAIL.ASS_CBD.CP.RUM, ACBidx, CPidx)                       =
                        edrString(DETAIL.ASS_CBD.CP.RUM, ACBidx, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, ACBidx, CPidx)           = "00";
            edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, ACBidx, CPidx)     =
			edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, ACBidx, lastCPidx_00) ;
            edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, ACBidx, CPidx)   =
			edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, ACBidx, lastCPidx_00);
            edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, ACBidx, CPidx)=
			edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, ACBidx, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, CPidx)   =
			edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, lastCPidx_00);
            edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, CPidx)            =
			edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, CPidx)         =
			edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, lastCPidx_00);
            edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, CPidx)    =
			edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.DAY_CODE, ACBidx, CPidx)                  =
			edrString(DETAIL.ASS_CBD.CP.DAY_CODE, ACBidx, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, ACBidx, CPidx)        =
			edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, ACBidx, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, ACBidx, CPidx)          =
			edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, ACBidx, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, CPidx)      =
			edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, lastCPidx_00);
          }
        }
        else if (successiveChargePacketCI >= 1)// if there is a packet but no ChargeType=="00" packet
        {
          //create the ChargeType=="00" packet on the end (!! only for record/services that should be processed !!)
          if ( edrAddDatablock( DETAIL.ASS_CBD.CP ) == false )
          {
            String Msg = "failed to add CHARGE_PACKET datablock " + longToStr(successiveChargeDetail) +
                         " for ASS_CBD " + longToStr(successiveChargeInformation) +
                         " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
            edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

          }
          CPidx                    = successiveChargePacket;
          successiveChargePacket   = successiveChargePacket   +1;
          successiveChargePacketCI = successiveChargePacketCI +1;

          records = records+1;
          edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)          = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
          edrString(DETAIL.ASS_CBD.CP.RECORD_TYPE, ACBidx, CPidx) = extension_CP;
          edrLong(DETAIL.ASS_CBD.CP.RECORD_NUMBER, ACBidx, CPidx) = records;
          edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, ACBidx, CPidx) = related_record;
          edrLong(DETAIL.ASS_CBD.CP.RELATED_CHARGE_INFO_ID, ACBidx, CPidx) = related_info_id;

          Long prevCPidx           = CPidx -1 ; //the last one added is used as sample
          //defaults
//        edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, ACBidx, CPidx)             = "R"; //default is overwritten a few lines after
          edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, ACBidx, CPidx)        = "*";
//        edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, ACBidx, CPidx)           = "S";
          edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, ACBidx, CPidx)               = "N";
          edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, ACBidx, CPidx)     = "R";
          edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, ACBidx, CPidx)     = "N";
          // generated
          edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, ACBidx, CPidx)             = "W";
          edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, ACBidx, CPidx)           = "A";
          edrString(DETAIL.ASS_CBD.CP.RUM, ACBidx, CPidx)                       =
			edrString(DETAIL.ASS_CBD.CP.RUM, ACBidx, prevCPidx);
          edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, ACBidx, CPidx)           = "00";
          edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, ACBidx, CPidx)     = sumChargedAmountValueCI ;
          edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, ACBidx, CPidx)   = longToDecimal(sumChargedUnitsCI);
          edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, ACBidx, CPidx)= longToDecimal(sumChargeableUnitsCI);
          edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, CPidx)   =
			edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, ACBidx, prevCPidx);
          edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, CPidx)            =
			edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, prevCPidx);
          edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, CPidx)         =
			edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, ACBidx, prevCPidx);
          edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, CPidx)    =
			edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, prevCPidx);
          if (successiveChargePacketCI == 2)
          {
            edrString(DETAIL.ASS_CBD.CP.DAY_CODE, ACBidx, CPidx)                =
			edrString(DETAIL.ASS_CBD.CP.DAY_CODE, ACBidx, prevCPidx);
            edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, ACBidx, CPidx)      =
			edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, ACBidx, prevCPidx);
          }
          else
          {
            edrString(DETAIL.ASS_CBD.CP.DAY_CODE, ACBidx, CPidx)                = "N";
            edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, ACBidx, CPidx)      = "I";
          }
          edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, ACBidx, CPidx)          =
			edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, ACBidx, prevCPidx);
          edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, CPidx)      =
			edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, ACBidx, prevCPidx);
        }
      }
      taxInformationList_opt
      {
        // increment the EDR and File counters for Blocks taken into account
        if (successiveChargePacketCI >= 1)// packets were created for this CI
        {
          sumTaxChargeEDR = sumTaxChargeEDR  + sumTaxChargeCI;
          sumTaxChargeBS  = sumTaxChargeBS   + sumTaxChargeCI;
          sumTaxChargeFile= sumTaxChargeFile + sumTaxChargeCI;
        }
        // increment the counter for every TaxCharge (for statistcs and checks)
        sumTaxChargeFileAll= sumTaxChargeFileAll + sumTaxChargeCI;

	// validate tax amount with the charge amount
        if ( sumTaxAmountCI >  sumChargedAmountValueCI )
	{
	  // Set error code
          // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_CONT_EXT));
          String offset = "-1";
          edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
          edrAddError("ERR_TAP3_RET", 3, "severe", "100", "398", "7", offset, "-1",
		"Taxable amount greater than charge amount");
          setAssociatedTapErr("ERR_TAP3_TAX_GT_CHARGE_AMOUNT", 3,"100" ,"398" ,"7");	
        }

      }
      discountInformation_opt
      {
        if (successiveChargePacketCI >= 1)// packets were created for this CI
        {
          // if there is a CP to store this info, use it
//        edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, ACBidx, successiveChargePacket-1) = (lastDiscountValue * lastExchangeRateFactor);

          // Compute the Charge Information block level Discount Value
          lastDiscountValueCI  = lastDiscountValue * lastExchangeRateFactor;

          // Compute the TAP3 File level sum of Discount Values
          sumDiscountValueFile = sumDiscountValueFile + lastDiscountValueCI;

          edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, ACBidx, CPidx) = lastDiscountValueCI;
        }

        // This check is done here to avoid the setting up of Missing flag, 
        // when the CP packet was yet to be created in chargedItem_mandopt.
        if (lastChargedItem == "")
        {
          edrMissingInput(DETAIL.ASS_CBD.CP.RUM, ACBidx, CPidx);
        }

        // This check is done here to avoid the setting up of Missing flag,
        // when the CP packet was yet to be created in exchangeRateCode_opt.
        if (exchangeRateCodeIsMissing == true)
        {
          edrMissingInput(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, CPidx);
        }
      }
      IFW_TAP3.Block_END
    ;

  chargeInformation_mandopt:
      {
	related_info_id = 1;
      }
      chargeInformation
    | /* EMPTY */
      {
       // Error code will be set within I rules.
      }
    ;

  chargeInformation_opt:
      {
	related_info_id = 1;
      }
      chargeInformation
    | /* EMPTY */
    ;

  chargeInformationList_mandopt:
      IFW_TAP3.ChargeInformationList
      chargeInformationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
       // Error Code will be set within I rules
       // (IRULE) Rule is not defined
      }
    ;

  chargeInformationList_opt:
      IFW_TAP3.ChargeInformationList
      chargeInformationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  chargeInformationList_opt2:
      chargeInformationList
    | /* EMPTY */ //accept empty list
    ;

  chargeInformationList:
      chargeInformationList
      chargeInformation_bs
    | chargeInformation_bs
    ;

  chargedItem_mandopt:
      IFW_TAP3.ChargedItem
      {
        lastChargedItem = tokenString("IFW_TAP3.ChargedItem.CHARGED_ITEM");
      }
    | /* EMPTY */
      {
	lastChargedItem = "";
	// Set error code
	// Error code MISSING will be set in the chargeInformation block
      }
    ;

  chargeType_opt:
      IFW_TAP3.ChargeType
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, ACBidx, CPidx,  "IFW_TAP3.ChargeType.CHARGE_TYPE");
        lastChargeType = tokenString("IFW_TAP3.ChargeType.CHARGE_TYPE");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, ACBidx, CPidx);
        lastChargeType = "";
      }
    ;

  charge_opt:
      IFW_TAP3.Charge
      {
        // NB: charge after discount, but before tax
        edrConnectToken(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, ACBidx, CPidx,  "IFW_TAP3.Charge.CHARGE");
        lastCharge = (longToDecimal(tokenLong("IFW_TAP3.Charge.CHARGE")) / theAbsoluteAmountDivider);
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, ACBidx, CPidx);
        lastCharge = 0.0;
      }
    ;

  chargingCharacteristics_opt:
      IFW_TAP3.ChargingCharacteristics
      {
          // For optimization reasons in keeping lesser new fields to the EDR container
          // we are poppulating ChargingCharacteristics in DETAIL.USAGE_CLASS
          edrConnectToken(DETAIL.USAGE_CLASS,"IFW_TAP3.ChargingCharacteristics.CHARGING_CHARACTERISTICS");
      } 
    | /* EMPTY */
    ;

  chargingId_mandopt:
      IFW_TAP3.ChargingId
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0, "IFW_TAP3.ChargingId.CHARGING_ID");
//      edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0) =
//                decimalToStr(tokenDecimal("IFW_TAP3.ChargingId.CHARGING_ID"), 0); //TODO CONNECT
//      edrString(DETAIL.CHAIN_REFERENCE)  =
//                edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0); //TODO activate for GPRS callAssembly
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0);
      }
    ;

  chargedPartyStatus_mandopt:
      IFW_TAP3.ChargedPartyStatus
    | /* EMPTY */
      {
	chargedPartyStatusIsMissing = true;
      }
    ;

  chargingPoint_mandopt:
      IFW_TAP3.ChargingPoint
      {
        String tmp_chargingPoint = tokenString ( "IFW_TAP3.ChargingPoint.CHARGING_POINT" );

        String offset;

        // Check whether Charged Party Status value is either "C" or "D"
        if ( (tmp_chargingPoint != "C") and
             (tmp_chargingPoint != "D") )
        {
          // If not "C" or "D", then raise appropriate error
          offset = "-1";
          edrString(DETAIL.ERROR_REJECT_TYPE) = "ERR_TAP3_RET";
          edrSetIsValidDetail(false);
          edrAddError("ERR_TAP3_RET", 3, "severe", "20", "73", "5",
                    offset, "-1", "Out Of Range Charging Point");
          setAssociatedTapErr("ERR_TAP3_OOR_CHARGING_POINT", 3 ,"20" ,"73" ,"5");
        }
      }
    | /* EMPTY */
      {
       // Sever error
       // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSM_EXT));
       String offset = "-1";
       edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
       edrAddError("ERR_TAP3_RET", 3, "severe", "32", "193", "4", offset, "-1", "Missing Charging Point");
       setAssociatedTapErr("ERR_TAP3_MISSING_CHARGING_POINT", 3,"32" ,"193" ,"4");	
      }
    ;

  chargingTimeStamp_opt: // at the service level
      IFW_TAP3.ChargingTimeStamp
      {
        timeStampType = chargingTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
      {
        if ( ( (service_Type == service_Basic) or (service_Type == service_Gprs) ) or
             ( (record_Type == record_MSS) or (record_Type == record_SCU) or (record_Type == record_VAS))
           )
        {
          // replace the default Tap3Detail level Timestamp
          lastValidLocalTimeStamp = lastLocalTimeStamp;
          lastValidUtcTimeOffset  = lastUtcTimeOffset;
        }
      }
    | /* EMPTY */
    ;

  chargedPartyIdType_mandopt:
      IFW_TAP3.ChargedPartyIdType
      {
	edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.TYPE, 0, 0,
			chargedPartyIdIdx, "IFW_TAP3.ChargedPartyIdType.CHARGED_PARTY_ID_TYPE");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.TYPE, 0, 0,
			chargedPartyIdIdx);
      }
    ;

  chargedPartyIdentifier_mandopt:
      IFW_TAP3.ChargedPartyIdentifier
      {
	edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.IDENTIFIER, 0, 0,  chargedPartyIdIdx,
			 "IFW_TAP3.ChargedPartyIdentifier.CHARGED_PARTY_IDENTIFIER");
      }
    | /* EMPTY */
      {
       edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.IDENTIFIER, 0, 0,
			chargedPartyIdIdx);
      }
    ;

  clirIndicator_opt:
      IFW_TAP3.ClirIndicator
    | /* EMPTY */
    ;

  completionTimeStamp_mandopt:
      IFW_TAP3.CompletionTimeStamp
      {
        timeStampType = scuCompletionTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
	completionTimeStampIsMissing = true;
      }
    ;

  countryCode:
      IFW_TAP3.CountryCode
      {
        lastCalledNumberAnalysisCC                       = tokenString("IFW_TAP3.CountryCode.COUNTRY_CODE");
        calledNumberAnalysisCCarray[lastCode][lastCcIdx] = tokenString("IFW_TAP3.CountryCode.COUNTRY_CODE");
        lastCcIdx                                        = lastCcIdx + 1;
      }
    ;

  countryCodeList_mandopt:
      IFW_TAP3.CountryCodeList
      {
        lastCcIdx = 0;
      }
      countryCodeList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        /* Set Fatal Error */
        requestBatchReject(246, -1, 3,  0,  30, "ERR_TAP3_MISSING_COUNTRY_CODE_LIST");
      }
    ;

  countryCodeList_opt2:
      countryCodeList1
    | /* EMPTY */
    ;

  countryCodeList1:
      countryCodeList1 countryCode
    | countryCode
    ;

  cseInformation_opt:
      IFW_TAP3.CseInformation
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.CSE_INFORMATION, 0, "IFW_TAP3.CseInformation.CSE_INFORMATION");
      }
    | /* EMPTY */
    ;

  currencyConversionList:
      currencyConversionList
      currencyConversion
    | currencyConversion
    ;

  currencyConversionList_opt:
      IFW_TAP3.CurrencyConversionList
      currencyConversionList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  customerIdType_mandopt:
      IFW_TAP3.CustomerIdType
      {
	if (blockType == trackingCustomerIdBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.TYPE, 0, 0,
			  trackingCustIdx, "IFW_TAP3.CustomerIdType.CUSTOMER_ID_TYPE");
	}
	else if (blockType == trackedCustomerIdBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.TYPE, 0, 0,
			  trackedCustIdx, "IFW_TAP3.CustomerIdType.CUSTOMER_ID_TYPE");
	}
      }
    | /* EMPTY */
      {
	if (blockType == trackingCustomerIdBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.TYPE, 0, 0,
			  trackingCustIdx);
	}
	else if (blockType == trackedCustomerIdBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.TYPE, 0, 0,
			  trackedCustIdx);
	}
      }
    ;

  customerIdentifier_mandopt:
      IFW_TAP3.CustomerIdentifier
      {
	if (blockType == trackingCustomerIdBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0,
			  trackingCustIdx, "IFW_TAP3.CustomerIdentifier.CUSTOMER_IDENTIFIER");
	}
	else if (blockType == trackedCustomerIdBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0,
			  trackedCustIdx, "IFW_TAP3.CustomerIdentifier.CUSTOMER_IDENTIFIER");
	}
      }
    | /* EMPTY */
      {
	if (blockType == trackingCustomerIdBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0,
			  trackingCustIdx);
	}
	else if (blockType == trackedCustomerIdBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0,
			  trackedCustIdx);
	}
      }
    ;

  dataVolumeReference_opt:
      IFW_TAP3.DataVolumeReference
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.DATA_VOLUME_REFERENCE, 0, bsPacketIdx,
                        "IFW_TAP3.DataVolumeReference.DATA_VOLUME_REFERENCE");
      }
    | /* EMPTY */
    ;

  gprsdataVolumeIncoming_mandopt:
      IFW_TAP3.DataVolumeIncoming
      {
        edrConnectToken(DETAIL.VOLUME_RECEIVED, "IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.VOLUME_RECEIVED, 0, gsPacketIdx,
                        "IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING");
        sumDataVolumeIncoming  = sumDataVolumeIncoming +
                                 longToDecimal(tokenLong("IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING"));
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.VOLUME_RECEIVED, 0, gsPacketIdx);
      }
    ;

  gprsdataVolumeOutgoing_mandopt:
      IFW_TAP3.DataVolumeOutgoing
      {
        edrConnectToken(DETAIL.VOLUME_SENT, "IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.VOLUME_SENT, 0, gsPacketIdx,
                        "IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING");
        sumDataVolumeOutgoing  = sumDataVolumeOutgoing +
                                 longToDecimal(tokenLong("IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING"));
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.VOLUME_SENT, 0, gsPacketIdx);
      }
    ;

  dateTime:    // Missing DateTime in files
      localTimeStamp_mandopt
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
        switch (timeStampType)
        {
          case(callEventStartTimeStampType):
          {
            edrConnectToken(DETAIL.CHARGING_START_TIMESTAMP, "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
            edrConnectToken(DETAIL.CHARGING_END_TIMESTAMP,  "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
          }
          break;
          case(chargingTimeStampType):
          {
//            if ( ( (service_Type == service_Gprs) ) or
            if ( (record_Type == record_MSS) or (record_Type == record_SCU) or (record_Type == record_VAS))
            {
              // replace the default Tap3Detail level Timestamp
              edrConnectToken(DETAIL.CHARGING_START_TIMESTAMP, "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
              edrConnectToken(DETAIL.CHARGING_END_TIMESTAMP,  "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
            }
	    if (service_Type == service_Basic)
	    {
              // replace the default Tap3Detail level Timestamp
               edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHARGING_START_TIMESTAMP, 0, bsPacketIdx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
               edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHARGING_END_TIMESTAMP, 0, bsPacketIdx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
	    }
	    if (service_Type == service_Suppl)
	    {
              // replace the default Tap3Detail level Timestamp
               edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.CHARGING_START_TIMESTAMP, 0, ssPacketIdx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
               edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.CHARGING_END_TIMESTAMP, 0, ssPacketIdx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
	    }
	    if (service_Type == service_Vas)
	    {
              // replace the default Tap3Detail level Timestamp
               edrConnectToken(DETAIL.ASS_VAS_EXT.CHARGING_START_TIMESTAMP, vasidx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
               edrConnectToken(DETAIL.ASS_VAS_EXT.CHARGING_END_TIMESTAMP, vasidx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
	    }
	    if (blockType == gprsServiceUsageBlockType)
	    {
              // replace the default Tap3Detail level Timestamp
               edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.CHARGING_START_TIMESTAMP, 0, gsPacketIdx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
               edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.CHARGING_END_TIMESTAMP, 0, gsPacketIdx,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
	    }
            if (blockType == gprsServiceUsedBlockType)
            {
              // replace the default Tap3Detail level Timestamp
               edrConnectToken(DETAIL.ASS_GPRS_EXT.SERVICE_USED_CHARGING_START_TIMESTAMP, 0,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
            }

          }
          break;
          case(scuDepositTimeStampType):
          {
            edrConnectToken(DETAIL.CHARGING_START_TIMESTAMP, "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
          }
          break;
          case(scuCompletionTimeStampType):
          {
            edrConnectToken(DETAIL.CHARGING_END_TIMESTAMP,  "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
          }
          break;
          case(chargeDetailTimeStampType):
          {
            //cannot be connected because CP is not yet created !!!
            //edrConnectToken(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, CPidx,
            //                "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");//cannot be connected
          }
          break;
	  case(hscsdModificationTimestampType):
	  {
           edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.MODIFICATION_TIMESTAMP,
			   0, bsPacketIdx, 0, pmidx,  "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
	  }
	  break;
          case(pDPContextStartTimestampType):
          {
            //This is for partial GPRS calls
            edrConnectToken(DETAIL.ASS_GPRS_EXT.PDP_CONTEXT_START_TIMESTAMP,0,
                               "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
          }
          break;
          default:
          break;
        }
      }
      utcTimeOffsetCode_mandopt
      {
        // get the corresponding UtcTimeOffset from the UtcTimeOffsetCode
        lastUtcTimeOffset  = getUtcTimeOffset( tokenLong("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE") );
        switch (timeStampType)
        {
          case(callEventStartTimeStampType):
          {
            edrConnectToken(DETAIL.UTC_TIME_OFFSET, "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
            edrString(DETAIL.UTC_TIME_OFFSET) = lastUtcTimeOffset;
          }
          break;
          case(chargingTimeStampType):
          {
//            if ( ( (service_Type == service_Gprs) ) or
            if ( (record_Type == record_MSS) or (record_Type == record_SCU) or (record_Type == record_VAS))
            {
              // replace the default Tap3Detail level Timestamp
              edrConnectToken(DETAIL.UTC_TIME_OFFSET, "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
              edrString(DETAIL.UTC_TIME_OFFSET) = lastUtcTimeOffset;
            }
	    if ( service_Type == service_Basic )
	    {
              // replace the default Tap3Detail level Timestamp
	      edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.UTC_TIME_OFFSET, 0, bsPacketIdx,
                              "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
	      edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.UTC_TIME_OFFSET, 0, bsPacketIdx) = lastUtcTimeOffset;
	    }
	    if ( service_Type == service_Suppl )
	    {
              // replace the default Tap3Detail level Timestamp
	      edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.UTC_TIME_OFFSET, 0, ssPacketIdx,
                              "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
	      edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.UTC_TIME_OFFSET, 0, ssPacketIdx) = lastUtcTimeOffset;
	    }

	    if ( service_Type == service_Vas )
	    {
              // replace the default Tap3Detail level Timestamp
	      edrConnectToken(DETAIL.ASS_VAS_EXT.UTC_TIME_OFFSET, vasidx,
                              "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
	      edrString(DETAIL.ASS_VAS_EXT.UTC_TIME_OFFSET, vasidx) = lastUtcTimeOffset;
	    }
	    if ( blockType == gprsServiceUsageBlockType )
	    {
              // replace the default Tap3Detail level Timestamp
	      edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.UTC_TIME_OFFSET, 0, gsPacketIdx,
                              "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
	      edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UTC_TIME_OFFSET, 0, gsPacketIdx) = lastUtcTimeOffset;
	    }
            if (blockType == gprsServiceUsedBlockType)
            {
              // replace the default Tap3Detail level Timestamp
               edrString(DETAIL.ASS_GPRS_EXT.SERVICE_USED_UTC_TIME_OFFSET, 0) = lastUtcTimeOffset;
            }

          }
          break;
          case(scuDepositTimeStampType):
          {
            edrConnectToken(DETAIL.UTC_TIME_OFFSET, "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
            edrString(DETAIL.UTC_TIME_OFFSET) = lastUtcTimeOffset;
          }
          break;
          case(scuCompletionTimeStampType):
          {
          }
          break;
          case(chargeDetailTimeStampType):
          {
          }
          break;
	  case(hscsdModificationTimestampType):
	  {
           edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.UTC_TIME_OFFSET,
                           0, bsPacketIdx, 0, pmidx,  "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
           edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.UTC_TIME_OFFSET,
                     0, bsPacketIdx, 0,  pmidx) = lastUtcTimeOffset;
	  }
	  break;
          case(pDPContextStartTimestampType):
          {
            //This is for partial GPRS calls
            edrString(DETAIL.ASS_GPRS_EXT.PDP_UTC_TIME_OFFSET, 0) = lastUtcTimeOffset;
          }
          default:
          break;
        }
      }
    | IFW_TAP3.DateTime
      localTimeStamp_mandopt
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      utcTimeOffsetCode_mandopt
      {
        // get the corresponding UtcTimeOffset from the UtcTimeOffsetCode
        lastUtcTimeOffset  = getUtcTimeOffset( tokenLong("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE") );
      }
      IFW_TAP3.Block_END
    ;

  dateTimeLong: // Missing DateTimeLong in files
      localTimeStamp_mandopt
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      utcTimeOffset_mandopt
      {
        lastUtcTimeOffset = tokenString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET");
      }
    | IFW_TAP3.DateTimeLong
      localTimeStamp_mandopt
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      utcTimeOffset_mandopt
      {
        lastUtcTimeOffset = tokenString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET");
      }
      IFW_TAP3.Block_END
    ;

  dayCategory_mandopt:
      IFW_TAP3.DayCategory
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.DAY_CODE, ACBidx, CPidx, "IFW_TAP3.DayCategory.DAY_CATEGORY");
      }
    | /* EMPTY */
      {
       edrMissingInput(DETAIL.ASS_CBD.CP.DAY_CODE, ACBidx, CPidx);
      }
    ;

  dayCategorySubtype_opt:
      IFW_TAP3.DayCategorySubtype
    | /* EMPTY */
    ;

  defaultCallHandlingIndicator_opt:
      IFW_TAP3.DefaultCallHandlingIndicator
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.DEFAULT_CALL_HANDLING_INDICATOR, 0,
                        "IFW_TAP3.DefaultCallHandlingIndicator.DEFAULT_CALL_HANDLING_INDICATOR");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CAMEL_EXT.DEFAULT_CALL_HANDLING_INDICATOR, 0);
      }
    ;

  depositTimeStamp_mandopt:
      IFW_TAP3.DepositTimeStamp
      {
        timeStampType = scuDepositTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
	depositTimeStampIsMissing = true;
      }
    ;

  destination:
      IFW_TAP3.Destination
      {
        callNumberType = callDestinationType;
      }
      calledNumber_opt
      dialledDigits_opt
      calledPlace_opt
      calledRegion_opt
      calledNumAnalysisCode_opt
      IFW_TAP3.Block_END
      {
        // normalize the internal representation of the B_NUMBER
        // String bNumberString = edrString(DETAIL.B_NUMBER);
        // bNumberString = convertCli(bNumberString,
        //                            edrString(DETAIL.B_MODIFICATION_INDICATOR),
        //                            edrLong(DETAIL.B_TYPE_OF_NUMBER),
        //                            NORM_NAC,
        //                            calledNumberAnalysisIACarray[getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)], // NORM_IAC,
        //                            calledNumberAnalysisCCarray[ getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)], // NORM_CC,
        //                            NORM_IAC_SIGN,
        //                            NORM_NDC);

        // lastCalledNumAnalysisCode = 1;
      }
    ;

  destination_opt:
      destination
    | /* EMPTY */
      {
        // Set the Destination field flag as missing.
        // The validation will be done in the IFW_TAP3.TeleServiceCode section of basicServiceCode.
        destinationIsMissing = true;
      }
    ;

  destinationNetwork_opt:
      IFW_TAP3.DestinationNetwork
      {
        edrConnectToken(DETAIL.DESTINATION_NETWORK, "IFW_TAP3.DestinationNetwork.NETWORK_ID");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.DESTINATION_NETWORK);
      }
    ;

  dialledDigits_opt:
      IFW_TAP3.DialledDigits
      {
	// This should never be normalized.
	edrConnectToken(DETAIL.C_NUMBER, "IFW_TAP3.DialledDigits.DIALLED_DIGITS");
        edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.DialledDigits.DIALLED_DIGITS");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0);
      }
    ;

  discountApplied:
      IFW_TAP3.DiscountValue
      {
        discountApplied_Type[lastCode] = discountApplied_fixedDiscountValue;
        discountApplied[lastCode]      = tokenLong("IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT");
        if (discountEntries <= lastCode)
        {
          discountEntries              = lastCode + 1;
        }
      }
    | IFW_TAP3.DiscountRate
      {
        discountApplied_Type[lastCode] = discountApplied_discountRate;
        discountApplied[lastCode]      = tokenLong("IFW_TAP3.DiscountRate.PERCENTAGE_RATE");

        // Check whether Discount Rate is in the range 0.00 to 100.00
        if ( (discountApplied[lastCode] < 0) or
             (discountApplied[lastCode] > 10000) )
        {
          // If not, then set the appropriate Out of Range Fatal Error.
          requestBatchReject(92, -1, 7,  0,  20, "ERR_TAP3_DISCOUNT_RATE_OOR");
        }

        if (discountEntries <= lastCode)
        {
          discountEntries              = lastCode + 1;
        }
      }
    ;

  discountApplied_mandopt:
      discountApplied
   | /* EMPTY */
      {
	// Set Fatal Error
        requestBatchReject(94, -1, 3,  0,  30, "ERR_TAP3_MISSING_DISCOUNT_APPLIED");
      }
   ;

  discountCode_mandopt:
      IFW_TAP3.DiscountCode
      {
         // Set Fatal Error.

        lastDiscountCode = tokenLong("IFW_TAP3.DiscountCode.DISCOUNT_CODE");
           if((lastDiscountCode < 0) or ( lastDiscountCode >99))
           {
                    requestBatchReject(94, -1, 3, 0, 20, "ERR_TAP3_DISCOUNT_CODE_OOR");
           }
        lastDiscountCode = tokenLong("IFW_TAP3.DiscountCode.DISCOUNT_CODE");
        if (getDiscountAppliedType(lastDiscountCode) == discountApplied_fixedDiscountValue)
        {
          edrConnectToken(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE,
                          ACBidx, CPidx, "IFW_TAP3.DiscountCode.DISCOUNT_CODE");
        }
        // in case of discountApplied_discountRate, the DiscountValue is mandatory.
      }
    | /* EMPTY */
      {
        // Set severe error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_CBD.CP.
        //			GRANTED_DISCOUNT_AMOUNT_VALUE, ACBidx, CPidx));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "96", "6", offset, "-1", "Missing discount code");
        setAssociatedTapErr("ERR_TAP3_MISSING_DISCOUNT_CODE", 3,"30" ,"96" ,"6");	
      }
    ;

  discountInformation:
      IFW_TAP3.DiscountInformation
      discountCode_mandopt
      discountValue_opt
      IFW_TAP3.Block_END
    ;

  discountInformation_opt:
      discountInformation
    | /* EMPTY */
    ;

  discountValue_opt:
      IFW_TAP3.DiscountValue
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE,
                        ACBidx, CPidx, "IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT");
        lastDiscountValue = ( longToDecimal(tokenLong("IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT")) / theAbsoluteAmountDivider);

        //if discountvalue is present then discount applied type is discountRate.
        //populating this information in DISCOUNTMODEL_CODE will help carry the information
        //of discount type to the EDR. 
        edrString(DETAIL.ASS_CBD.CP.DISCOUNTMODEL_CODE,ACBidx, CPidx) = 
                                                         longToStr(discountApplied_discountRate);
      }
    | /* EMPTY */
      {
        if (getDiscountAppliedType(lastDiscountCode) == discountApplied_fixedDiscountValue)
        {
          lastDiscountValue = ( longToDecimal(getDiscountApplied(lastDiscountCode)) / theAbsoluteAmountDivider);
        }
        // in case of discountApplied_discountRate, the DiscountValue is mandatory.
      }
    ;

  discounting:
      IFW_TAP3.Discounting
      discountingCode_mandopt
      discountApplied_mandopt
      IFW_TAP3.Block_END
    ;

  discountingCode_mandopt:
      IFW_TAP3.DiscountCode
      {
        Long tmpDiscountCode = tokenLong("IFW_TAP3.DiscountCode.DISCOUNT_CODE");
		// Set Fatal Error
        if((tmpDiscountCode < 0) or ( tmpDiscountCode >99))
        {
                requestBatchReject(94, -1, 3, 0, 20, "ERR_TAP3_DISCOUNT_CODE_OOR");
        }
      }
    | /* EMPTY */
      {
	// Set Fatal Error
        requestBatchReject(94, -1, 3,  0,  31, "ERR_TAP3_MISSING_DISCOUNTING_CODE");
      }
    ;

  discountingList:
      discountingList
      discounting
    | discounting
    ;

  discountingList_opt:
      IFW_TAP3.DiscountingList
      discountingList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  distanceChargeBandCode_opt:
      IFW_TAP3.DistanceChargeBandCode
    | /* EMPTY */
    ;

  dualServiceCode:
      IFW_TAP3.DualTeleServiceCode
      {
        lastBasicDualService = "0" + tokenString("IFW_TAP3.DualTeleServiceCode.DUAL_TELE_SERVICE_CODE");
      }
    | IFW_TAP3.DualBearerServiceCode
      {
        lastBasicDualService = "1" + tokenString("IFW_TAP3.DualBearerServiceCode.DUAL_BEARER_SERVICE_CODE");

      }
    ;

  dualServiceRequested_opt:
      dualServiceCode
    | /* EMPTY */
      {
        lastBasicDualService = "";
      }
    ;

  equipmentInformation:
      IFW_TAP3.EquipmentInformation
      mobileStationClassMark_opt
      imeiOrEsn_opt
      IFW_TAP3.Block_END
    ;

  equipmentInformation_opt:
      equipmentInformation
    | /* EMPTY */
      {
        // Set severe error code
        if ( (record_Type == record_MSS) )
        {
          // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSM_EXT));
	  String offset = "-1";
          edrAddError("ERR_TAP3_RET", 1, "warning", "34", "11", "3", offset, "-1", "Missing Equipment Information");
          setAssociatedTapErr("ERR_TAP3_MISSING_EQUIPMENT_INFO", 1,"34" ,"11" ,"3");	
        }
      }
    ;

  equipmentId_mandopt:
      IFW_TAP3.EquipmentId
      {
	if (blockType == trackingCustomerEqptBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.IDENTIFIER,
			  0, 0, 0,  "IFW_TAP3.EquipmentId.EQUIPMENT_ID");
	}
	else if (blockType == trackedCustomerEqptBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.IDENTIFIER,
			  0, 0, 0,  "IFW_TAP3.EquipmentId.EQUIPMENT_ID");
	}
	else if (blockType == chargedPartyEquipmentBlockType)
	{
          edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.IDENTIFIER,
                          0, 0, 0,  "IFW_TAP3.EquipmentId.EQUIPMENT_ID");
        }
      }
    | /* EMPTY */
     {
	if (blockType == trackingCustomerEqptBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.IDENTIFIER,
			  0, 0, 0);
	}
	else if (blockType == trackedCustomerEqptBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.IDENTIFIER,
			  0, 0, 0);
	}
	else if (blockType == chargedPartyEquipmentBlockType)
	{
          edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.IDENTIFIER,
                          0, 0, 0);
        }
      }
    ;

  equipmentIdType_mandopt:
      IFW_TAP3.EquipmentIdType
      {
	if (blockType == trackingCustomerEqptBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.TYPE,
			  0, 0, 0,  "IFW_TAP3.EquipmentIdType.EQUIPMENT_ID_TYPE");
	}
	else if (blockType == trackedCustomerEqptBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.TYPE,
			  0, 0, 0,  "IFW_TAP3.EquipmentIdType.EQUIPMENT_ID_TYPE");
	}
	else if (blockType == chargedPartyEquipmentBlockType)
	{
          edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.TYPE,
                          0, 0, 0,  "IFW_TAP3.EquipmentIdType.EQUIPMENT_ID_TYPE");
        }
      }
    | /* EMPTY */
      {
	if (blockType == trackingCustomerEqptBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.TYPE,
			  0, 0, 0);
	}
	else if (blockType == trackedCustomerEqptBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.TYPE,
			  0, 0, 0);
	}
	else if (blockType == chargedPartyEquipmentBlockType)
	{
          edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.TYPE,
                          0, 0, 0);
        }
      }
    ;

  exchangeRateCode_opt:
      IFW_TAP3.ExchangeRateCode
      {
        lastExchangeRateFactorValue     = getExchangeRateFactor( tokenLong("IFW_TAP3.ExchangeRateCode.CODE") );
        //edrConnectToken(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, ACBidx, CPidx,  "IFW_TAP3.ExchangeRateCode.CODE");
        if (bUseLocalCurrency)
        {
          lastExchangeRateFactor        = lastExchangeRateFactorValue;
        }
        else
        {
          lastExchangeRateFactor        = 1.0;  // (to store SDRcount)
        }
      }
    | /* EMPTY */
      {
        //this case only happens when no ChargeDetail with a charge are attached
        lastExchangeRateFactorValue     = 1.0;
        lastExchangeRateFactor          = lastExchangeRateFactorValue;

        exchangeRateCodeIsMissing       = true; // Set the ExchangeRateCode as Empty
      }
    ;

  exchangeRateCode_mandopt1:
      IFW_TAP3.ExchangeRateCode
    | /* EMPTY */
      {
	// Set Fatal Error
        requestBatchReject(106, -1, 3,  0,  30, "ERR_TAP3_MISSING_EXCHANGE_RATE_CODE");
      }
    ;

  exchangeRate_mandopt:
      IFW_TAP3.ExchangeRate
    | /* EMPTY */
      {
	// Set Fatal Error
        requestBatchReject(106, -1, 3,  0,  32, "ERR_TAP3_MISSING_EXCHANGE_RATE");
      }
    ;

  currencyConversion:
      IFW_TAP3.CurrencyConversion
      exchangeRateCode_mandopt1
      {
        lastCode                        = tokenLong("IFW_TAP3.ExchangeRateCode.CODE");
        exchangeRateCode[lastCode]      = lastCode;
        if((exchangeRateCode[lastCode] < 0) or (exchangeRateCode[lastCode] > 99))
          requestBatchReject(105, -1, 4,  0,  20, "ERR_TAP3_EXCHANGE_RATE_CODE_OOR");
      }
      numberOfDecimalPlaces_mandopt
      {
        numberOfDecimalPlaces[lastCode] = tokenLong("IFW_TAP3.NumberOfDecimalPlaces.NUMBER_OF_DECIMAL_PLACES");
      }
      exchangeRate_mandopt
      {
        exchangeRate[lastCode]          = tokenLong("IFW_TAP3.ExchangeRate.EXCHANGE_RATE");
        Long i;
        Long nbDecimals = 1;
        for (i=0 ; i < numberOfDecimalPlaces[lastCode] ; i=i+1)
        {
          nbDecimals = nbDecimals * 10;
        }
        exchangeRateFactor[lastCode]    = ( longToDecimal(exchangeRate[lastCode]) / longToDecimal(nbDecimals) );
        if (currencyEntries <= lastCode)
        {
          currencyEntries               = lastCode +1;
        }
      }
      IFW_TAP3.Block_END
    ;

  fileAvailableTimeStamp:
      IFW_TAP3.FileAvailableTimeStamp
      {
        timeStampType = fileAvailableTimeStampType;
      }
      dateTimeLong
      IFW_TAP3.Block_END
      {
        theFileAvailableTimeStamp     = lastLocalTimeStamp;
        theFileAvailableUtcTimeOffset = lastUtcTimeOffset;
      }
    ;

  fileAvailableTimeStamp_mandopt:
      fileAvailableTimeStamp
      {
        edrDate(HEADER.TRANSMISSION_DATE) = strToDate(theFileAvailableTimeStamp);
      }
    | /* EMPTY */
      {
	edrMissingInput(HEADER.TRANSMISSION_DATE);
      }
    ;

  fileCreationTimeStamp:
      IFW_TAP3.FileCreationTimeStamp
      {
        timeStampType = fileCreationTimeStampType;
      }
      dateTimeLong
      IFW_TAP3.Block_END
      {
        theFileCreationTimeStamp     = lastLocalTimeStamp;
        theFileCreationUtcTimeOffset = lastUtcTimeOffset;
      }
    ;

  fileCreationTimeStamp_mandopt:
      fileCreationTimeStamp
      {
        edrDate(HEADER.CREATION_TIMESTAMP) = strToDate(theFileCreationTimeStamp);
        edrString(HEADER.UTC_TIME_OFFSET)  = theFileCreationUtcTimeOffset;
      }
    | /* EMPTY */
      {
        edrMissingInput(HEADER.CREATION_TIMESTAMP);
      }
    ;

  fileSequenceNumber_mandopt:
      IFW_TAP3.FileSequenceNumber
    | /* EMPTY */
      {
        edrMissingInput(HEADER.SEQUENCE_NUMBER);
      }
    ;

  fileTypeIndicator_opt:
      IFW_TAP3.FileTypeIndicator
      {
		// Set Fatal Error.
		// Error is set based on the check done using the FileTypeIndicator and FileName.
		// The below code is used to check FileTypeIndicator which is "T" with Starting character
		// of the FileName. If FileName is not "T" then error is generated.

        theFileTypeIndicator = tokenString("IFW_TAP3.FileTypeIndicator.FILE_TYPE_INDICATOR");
        String FileName = strSubstr(CURRENT_STREAM_NAME, 0, 1);
        Long StrtoAscii_1 = strByteValue(FileName);
        Long StrtoAscii_2 = strByteValue(theFileTypeIndicator);
        Long StrtoAscii_3 = strByteValue("T");
        if((StrtoAscii_2 == StrtoAscii_3) and (StrtoAscii_1 != StrtoAscii_3))
        {
          requestBatchReject(110, -1, 2, 0, 38, "ERR_TAP3_FILETYPE_INDICATOR_MISMATCH");
		}
	
      }
    | /* EMPTY */
      {
        theFileTypeIndicator = "";
      }
    ;

  fraudMonitorIndicator_opt:
      IFW_TAP3.FraudMonitorIndicator
      {
        edrConnectToken(DETAIL.FRAUD_MONITOR_INDICATOR,
                           "IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.FRAUD_MONITOR_INDICATOR);
      }
    ;

  fnur_opt:
      IFW_TAP3.Fnur
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.FNUR, 0, bsPacketIdx, "IFW_TAP3.Fnur.FNUR");
      }
    | /* EMPTY */
    ;

  geographicalLocation_opt:
      IFW_TAP3.GeographicalLocation
      servingNetworkGeo_opt
      servingBid_opt
      servingLocationDescription_opt
      longitude_opt
      latitude_opt
      {
          edrString(DETAIL.GEOGRAPHICAL_LOCATION) = geographicalLocation;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  servingNetworkGeo_opt:
      IFW_TAP3.ServingNetwork
      {
          geographicalLocation = geographicalLocation + servingNetworkKey + ",";
          geographicalLocation = geographicalLocation + tokenString("IFW_TAP3.ServingNetwork.SERVING_NETWORK") + ",";
      }
    | /* EMPTY */
    ;

  gprsBasicCallInformation:
      IFW_TAP3.GprsBasicCallInformation
      {
        service_Type                    = service_Gprs;
      }
      fraudMonitorIndicator_opt
      gprsChargeableSubscriber_mandopt
      rapFileSequenceNumber_opt
      networkType_opt
      gprsDestination_mandopt
      callEventStartTimeStamp_mandopt
      totalCallEventDuration_mandopt
      causeForTerm_opt
      partialTypeIndicator_opt
      pDPContextStartTimestamp_opt
      networkInitPDPContext_opt
      chargingId_mandopt
      IFW_TAP3.Block_END
    ;

  gprsBasicCallInformation_mandopt:
       gprsBasicCallInformation
     | /* EMPTY */
       {
        // Set severe error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "31", "14", "3", offset, "-1", "Missing Gprs Basic Information");
        setAssociatedTapErr("ERR_TAP3_MISSING_GPRS_BASIC_INFO", 3,"31" ,"14" ,"3");	
       }
     ;

  gprsCall:
      IFW_TAP3.GprsCall
      {
        if ( createNewDetail(record_GPRS, type_GPRS) == false )
        {
          //TODO something
        }
        edrString(DETAIL.BASIC_SERVICE) = "813"; // gprs
      }
      typeOfControllingNode_mandopt
      {
        Long tmp_TypeOfControllingNode=tokenLong("IFW_TAP3.TypeOfControllingNode.TYPE_OF_CONTROLLING_NODE");
        if      (tmp_TypeOfControllingNode == 1) //SGSN
        {
          edrString(DETAIL.RECORD_TYPE) = type_GPRS_SG;
        }
        else if (tmp_TypeOfControllingNode == 2) //GGSN
        {
          edrString(DETAIL.RECORD_TYPE) = type_GPRS_GG;
        }
        else                                     //assembled
        {
          edrString(DETAIL.RECORD_TYPE) = type_GPRS_assembled;
        }
      }
      gprsBasicCallInformation_mandopt
      gprsLocationInformation_mandopt
      equipmentInformation_opt
      gprsServiceUsed_mandopt
      camelServiceUsed_opt
      valueAddedServiceUsedList_opt
      {
        // add the charge info provided by the VAS ChargeDetail block to the global Detail
        updateBasicDetailWithVasCharge();
      }
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  chargeableSubscriber_GprsCompatibility:
      chargeableSubscriber
    | // for compatibility with before tap0304
      IFW_TAP3.Imsi
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0, "IFW_TAP3.Imsi.IMSI");
        edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)      = "I"; //I=IMSI , M=MSISDN, P=IP ,  S=SIM ,  ...
      }
      msisdn_opt
    | // EMPTY
      {
        // Set severe error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "115", "3", offset, "-1", "Missing Chargeableable Subscriber");
        setAssociatedTapErr("ERR_TAP3_MISSING_CHARGEABLE_SUBSCRIBER", 3,"30" ,"115" ,"3");	
      }
    ;


  gprsChargeableSubscriber:
      IFW_TAP3.GprsChargeableSubscriber
      chargeableSubscriber_GprsCompatibility
      pdpType_mandopt
      pdpAddress_opt
      chargingCharacteristics_opt
      IFW_TAP3.Block_END
    ;

  gprsChargeableSubscriber_mandopt:
      gprsChargeableSubscriber
    | /* EMPTY */
      {
        // Set error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "114", "4", offset, "-1", "Missing Gprs Chargeable Sub");
        setAssociatedTapErr("ERR_TAP3_MISSING_GPRS_CHARGEABLE_SUBSCRIBER", 3,"30" ,"114" ,"4");	
      }
    ;

  pdpAddress_opt:
      IFW_TAP3.PdpAddress
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.PDP_ADDRESS, 0, "IFW_TAP3.PdpAddress.PDP_ADDRESS");
      }
    | /* EMPTY */
    ;

  pdpType_mandopt:
      IFW_TAP3.PdpType
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.PDP_TYPE, 0, "IFW_TAP3.PdpType.PDP_TYPE");

        // Set severe error.

	    Long tmp_pdpType;
	    tmp_pdpType = tokenLong("IFW_TAP3.PdpType.PDP_TYPE");
	    if((tmp_pdpType < 1) or (tmp_pdpType > 2))
	      edrAddError("ERR_TAP3_PDP_TYPE_OOR",3,"severe","20","168","5","0","-1","Pdp Type value out of range.");
//      edrString(DETAIL.ASS_GPRS_EXT.PDP_TYPE, 0)      = longToStr( tokenLong("IFW_TAP3.PdpType.PDP_TYPE") );
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GPRS_EXT.PDP_TYPE, 0);
      }
    ;

  accessPointNameNI_mandopt:
      IFW_TAP3.AccessPointNameNI
      {
        lastAPN = tokenString("IFW_TAP3.AccessPointNameNI.ACCESS_POINT_NAME_NI");
      }
    | /* EMPTY */
      {
        // Set error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "116", "5", offset, "-1", "Missing Access Point NI");
        setAssociatedTapErr("ERR_TAP3_MISSING_ACCESS_POINT_NI", 3,"30" ,"116" ,"5");	
      }
    ;

  accessPointNameOI_opt:
      IFW_TAP3.AccessPointNameOI
      {
        lastAPN = lastAPN +", "+ tokenString("IFW_TAP3.AccessPointNameOI.ACCESS_POINT_NAME_OI");
      }
    | /* EMPTY */
    ;

  AccessPointName_GprsCompatibility:
      accessPointNameNI_mandopt
      accessPointNameOI_opt
    ;

  gprsDestination:
      IFW_TAP3.GprsDestination
      AccessPointName_GprsCompatibility
      remotePdpAddressList_opt
      {
        if (service_Type == service_Camel)
        {
          edrString(DETAIL.ASS_CAMEL_EXT.DEST_GPRS_APN_ADDRESS, 0)       = lastAPN;
          edrString(DETAIL.ASS_CAMEL_EXT.DEST_GPRS_PDP_REMOTE_ADDRESS, 0)= lastRemotePdpAddressList;
        }
        else
        {
          edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)       = lastAPN;
          edrString(DETAIL.ASS_GPRS_EXT.PDP_REMOTE_ADDRESS, 0)= lastRemotePdpAddressList;
        }
      }
      IFW_TAP3.Block_END
    ;

  gprsDestination_mandopt:
     gprsDestination
    | /* EMPTY */
      {
       // Set error code
       // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
       String offset = "-1";
       edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
       edrAddError("ERR_TAP3_RET", 3, "severe", "32", "114", "4", offset, "-1", "Missing Gprs Destination");
       setAssociatedTapErr("ERR_TAP3_MISSING_GPRS_DESTINATION", 3,"32" ,"114" ,"4");	
      }
    ;

  gprsLocationInformation:
      IFW_TAP3.GprsLocationInformation
      gprsNetworkLocation_mandopt
      homeLocationInformation_opt
      geographicalLocation_opt
      IFW_TAP3.Block_END
    ;

  gprsLocationInformation_mandopt:
      gprsLocationInformation
    | /* EMPTY */
      {
       // Set error code
       // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
       String offset = "-1";
       edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
       edrAddError("ERR_TAP3_RET", 3, "severe", "32", "14", "3", offset, "-1", "Missing Gprs Location Info");
       setAssociatedTapErr("ERR_TAP3_MISSING_GPRS_LOC_INFO", 3,"32" ,"14" ,"3");	
      }
    ;

  gprsNetworkLocation:
      IFW_TAP3.GprsNetworkLocation
      recEntityCodeList_mandopt
      locationArea_opt
      cellId_opt
      IFW_TAP3.Block_END
    ;

  gprsNetworkLocation_mandopt:
      gprsNetworkLocation
    | /* EMPTY */
      {
       // Set error code
       // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
       String offset = "-1";
       edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
       edrAddError("ERR_TAP3_RET", 3, "severe", "30", "117", "4", offset, "-1", "Missing Gprs Network Location");
       setAssociatedTapErr("ERR_TAP3_MISSING_GPRS_NETWORK_LOC", 3,"30" ,"117" ,"4");	
      }
    ;

  gprsServiceUsage:
      IFW_TAP3.GprsServiceUsage
      {
	blockType = gprsServiceUsageBlockType;
        // add a corresponding block
        if ( edrAddDatablock( DETAIL.ASS_GPRS_EXT.GS_PACKET ) == false )
        {
          String Msg = "failed to add ASS_GPRS_EXT.GS_PACKET datablock";
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++
        }
      }
      chargingTimeStamp_opt
      qoSRequested_opt
      qoSUsed_opt
      gprsdataVolumeIncoming_mandopt
      gprsdataVolumeOutgoing_mandopt
      {
       gsPacketIdx = gsPacketIdx + 1;
      }
      IFW_TAP3.Block_END
    ;

  gprsServiceUsageList:
      gprsServiceUsageList gprsServiceUsage
    | gprsServiceUsage
    ;

  gprsServiceUsageList_mandopt:
      IFW_TAP3.GprsServiceUsageList
      gprsServiceUsageList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  gprsServiceUsed:
      IFW_TAP3.GprsServiceUsed
      {
        // initialise the counters of volume (different block for each QoS)
        sumDataVolumeIncoming           =0.0;
        sumDataVolumeOutgoing           =0.0;
        blockType                       = gprsServiceUsedBlockType;        
      }
      gprsServiceUsageList_mandopt
      {
        service_Type                    = service_Gprs;
        edrDecimal(DETAIL.VOLUME_RECEIVED) = sumDataVolumeIncoming;
        edrDecimal(DETAIL.VOLUME_SENT)     = sumDataVolumeOutgoing;
      }
      chargingTimeStamp_opt
      {
        initializeChargeInfoTempFields();
      }
      chargeInformationList_mandopt
      {
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      IFW_TAP3.Block_END
    ;

  gprsServiceUsed_mandopt:
      gprsServiceUsed
    | /* EMPTY */
      {
       // Set error code
       // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GPRS_EXT));
       String offset = "-1";
       edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
       edrAddError("ERR_TAP3_RET", 3, "severe", "34", "14", "3", offset, "-1", "Missing Gprs Service Used");
       setAssociatedTapErr("ERR_TAP3_MISSING_GPRS_SERVICE_USED", 3,"34" ,"14" ,"3");	
      }
    ;

  gsmChargeableSubscriber:
      IFW_TAP3.GsmChargeableSubscriber
      imsi_opt
      msisdn_opt
      IFW_TAP3.Block_END
    ;

  homeBid_opt:
      IFW_TAP3.HomeBid
    | /* EMPTY */
      {
	// Set Warnning Message
	String offset = "-1";
        edrAddError("ERR_TAP3_RET", 1, "warning", "30", "123", "5", offset, "-1", "Missing home bid");
        setAssociatedTapErr("ERR_TAP3_MISSING_HOME_BID", 1,"30" ,"123" ,"5");	
      }
    ;

  homeLocationInformation_opt:
      IFW_TAP3.HomeLocationInformation
      homeBid_opt
      locationDescr_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  imsi_mandopt:
      IFW_TAP3.Imsi
    | /* EMPTY */
      {
	imsiIsMissing = true;
      }
    ;

  imsi_opt:
      IFW_TAP3.Imsi
    | /* EMPTY */
    ;

  localTimeStamp_mandopt:
      IFW_TAP3.LocalTimeStamp
    | /* EMPTY */
    ;

  locationDescr_opt:
      IFW_TAP3.LocationDescription
    | /* EMPTY */
      {
	// Set Warnning Message
	String offset = "-1";
        edrAddError("ERR_TAP3_RET", 1, "warning", "31", "123", "5", offset, "-1", "Missing location desc");
        setAssociatedTapErr("ERR_TAP3_MISSING_LOC_DESC", 1,"31" ,"123" ,"5");	
      }
    ;

  homeIdType_mandopt:
      IFW_TAP3.HomeIdType
      {
        switch (blockType)
	{
          case chargedPartyHomeBlockType:
	    edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.TYPE, 0, 0,
			    chargedPartyHomeIdx, "IFW_TAP3.HomeIdType.HOME_ID_TYPE");
	    break;
          case trackedCustomerHomeBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0,
			    trackedCustHomeIdx, "IFW_TAP3.HomeIdType.HOME_ID_TYPE");
	    break;
          case trackingCustomerHomeBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0,
			    trackingCustHomeIdx, "IFW_TAP3.HomeIdType.HOME_ID_TYPE");
	    break;
          default:
	    break;
	}
      }
    | /* EMPTY */
      {
	 homeIdTypeIsMissing = true;
      }
    ;

  homeIdentifier_mandopt:
      IFW_TAP3.HomeIdentifier
      {
        switch (blockType)
	{
          case chargedPartyHomeBlockType:
	    edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.IDENTIFIER, 0, 0,
			    chargedPartyHomeIdx, "IFW_TAP3.HomeIdentifier.HOME_IDENTIFIER");
	    break;
          case trackedCustomerHomeBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0,
			    trackedCustHomeIdx, "IFW_TAP3.HomeIdentifier.HOME_IDENTIFIER");
	    break;
          case trackingCustomerHomeBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0,
			    trackingCustHomeIdx, "IFW_TAP3.HomeIdentifier.HOME_IDENTIFIER");
	    break;
          default:
	    break;
	}
      }
    | /* EMPTY */
      {
	homeIdentifierIsMissing = true;
      }
    ;

  hSCSDInformation:
      IFW_TAP3.HSCSDInformation
      {
        // add a corresponding block
        if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET ) == false )
        {
          String Msg = "failed to add ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET datablock";
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        }
      }
      basicHSCSDParameters_mandopt
      hSCSDParameterModificationList_opt
      IFW_TAP3.Block_END
    ;

  hSCSDInformation_opt:
      hSCSDInformation
    | /* EMPTY */
    ;

  hSCSDParameterModificationList_opt:
      IFW_TAP3.HSCSDParameterModificationList
      hSCSDParameterModificationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  hSCSDParameterModificationList_opt2:
      hSCSDParameterModificationList
    | /* EMPTY */ //accept empty list
    ;

  hSCSDParameterModificationList:
      hSCSDParameterModificationList
      hSCSDParameterModification
    | hSCSDParameterModification
    ;

  hSCSDParameterModification:
      IFW_TAP3.HSCSDParameterModification
      {
        // add a corresponding block
        if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST ) == false )
        {
          String Msg = "failed to add ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST datablock";
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        }
      }
      aiurRequested_hpm_opt
      numberOfChannels_opt
      channelCoding_mandopt
      numberOfChannelsUsed_mandopt
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.NUMBER_OF_CHANNELS_USED, 0, bsPacketIdx, 0, pmidx,
			"IFW_TAP3.NumberOfChannelsUsed.NUMBER_OF_CHANNELS_USED");
        if (numberOfChannelsUsedIsMissing == true)
	{
	 edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.NUMBER_OF_CHANNELS_USED,
		0, bsPacketIdx, 0, pmidx);
	 numberOfChannelsUsedIsMissing = false;
        }
      }
      initiatingParty_mandopt
      modificationTimestamp_mandopt
      {
       // Increase the pmidx
       pmidx = pmidx + 1;
      }
      IFW_TAP3.Block_END
    ;

  iac:
      IFW_TAP3.Iac
      {
        lastCalledNumberAnalysisIAC                        = tokenString("IFW_TAP3.Iac.IAC");
        calledNumberAnalysisIACarray[lastCode][lastIacIdx] = tokenString("IFW_TAP3.Iac.IAC");
        lastIacIdx                                         = lastIacIdx + 1;
      }
    ;

  iacList_mandopt:
      IFW_TAP3.IacList
      {
        lastIacIdx = 0;
      }
      iacList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        /* Set Fatal Error */
        requestBatchReject(246, -1, 3,  0,  31, "ERR_TAP3_MISSING_IAC_LIST");
      }
    ;


  iacList_opt2:
      iacList1
    | /* EMPTY */
    ;

  iacList1:
      iacList1
      iac
    | iac
    ;

  imeiOrEsn_opt:
      IFW_TAP3.Imei
      {
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.DEVICE_NUMBER, 0, "IFW_TAP3.Imei.IMEI");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0, "IFW_TAP3.Imei.IMEI");
        }
      }
    | IFW_TAP3.Esn
    | /* EMTPY */
      {
        if (record_Type != record_GPRS)
        {
          edrMissingInput(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0);
        }
      }
    ;

  initiatingParty_mandopt:
      IFW_TAP3.InitiatingParty
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.INITIATING_PARTY, 0, bsPacketIdx, 0, pmidx,
			"IFW_TAP3.InitiatingParty.INITIATING_PARTY");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.INITIATING_PARTY, 0, bsPacketIdx, 0, pmidx);
      }
    ;

  ipAddress:
      IFW_TAP3.IPTextV4Address
      {
        last_ipAddress     = tokenString("IFW_TAP3.IPTextV4Address.IP_TEXT_V4_ADDRESS");
      }
    | IFW_TAP3.IPTextV6Address
      {
        last_ipAddress     = tokenString("IFW_TAP3.IPTextV6Address.IP_TEXT_V6_ADDRESS");
      }
    ;

  latitude_opt:
      IFW_TAP3.Latitude
      {
          geographicalLocation = geographicalLocation + latitudeKey + ",";
          geographicalLocation = geographicalLocation + tokenString("IFW_TAP3.Latitude.LATITUDE") + ",";
      }
    | /* EMTPY */
    ;

  localCurrency_mandopt:
      IFW_TAP3.LocalCurrency
      {
        theLocalCurrency = tokenString("IFW_TAP3.LocalCurrency.CURRENCY");
      }
    | /* EMPTY */
      {
	theLocalCurrencyIsMissing = true;
      }
    ;

  locationArea_opt:
      IFW_TAP3.LocationArea
      {
        String nullFiller = buildNullFiller(5, strLength( tokenString("IFW_TAP3.LocationArea.LOCATION_AREA") ) );
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.LOCATION_AREA_INDICATOR, 0, "IFW_TAP3.LocationArea.LOCATION_AREA");
          if (nullFiller!="")
          {
            edrString(DETAIL.ASS_GPRS_EXT.LOCATION_AREA_INDICATOR, 0)=
                strReplace(tokenString("IFW_TAP3.LocationArea.LOCATION_AREA"), 0, 0,  nullFiller);
          }
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0, "IFW_TAP3.LocationArea.LOCATION_AREA") ;
          if (nullFiller!="")
          {
            edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0)=
                strReplace(tokenString("IFW_TAP3.LocationArea.LOCATION_AREA"), 0, 0,  nullFiller);
          }
        }
      }
    | /* EMTPY */
      {
        if (record_Type != record_GPRS)
        {
	  edrMissingInput(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0);
	}
      }
    ;

  locationIdType_mandopt:
      IFW_TAP3.LocationIdType
      {
        switch (blockType)
	{
          case chargedPartyLocnBlockType:
	    edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.TYPE, 0, 0,
			    chargedPartyLocnIdx, "IFW_TAP3.LocationIdType.LOCATION_ID_TYPE");
	    break;
          case trackedCustomerLocnBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.TYPE, 0, 0,
			    trackedCustLocnIdx, "IFW_TAP3.LocationIdType.LOCATION_ID_TYPE");
	    break;
          case trackingCustomerLocnBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.TYPE, 0, 0,
			    trackingCustLocnIdx, "IFW_TAP3.LocationIdType.LOCATION_ID_TYPE");
	    break;
          default:
	    break;
	}
      }
    | /* EMPTY */
     {
        switch (blockType)
	{
          case chargedPartyLocnBlockType:
	    edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.TYPE, 0, 0,
			    chargedPartyLocnIdx);
	    break;
          case trackedCustomerLocnBlockType:
	    edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.TYPE, 0, 0,
			    trackedCustLocnIdx);
	    break;
          case trackingCustomerLocnBlockType:
	    edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.TYPE, 0, 0,
			    trackingCustLocnIdx);
	    break;
          default:
	    break;
	}
      }
    ;

  locationIdentifier_mandopt:
      IFW_TAP3.LocationIdentifier
      {
        switch (blockType)
	{
          case chargedPartyLocnBlockType:
	    edrConnectToken(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.IDENTIFIER, 0, 0,
			    chargedPartyLocnIdx, "IFW_TAP3.LocationIdentifier.LOCATION_IDENTIFIER");
	    break;
          case trackedCustomerLocnBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0,
			     trackedCustLocnIdx, "IFW_TAP3.LocationIdentifier.LOCATION_IDENTIFIER");
	    break;
          case trackingCustomerLocnBlockType:
	    edrConnectToken(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0,
			     trackingCustLocnIdx, "IFW_TAP3.LocationIdentifier.LOCATION_IDENTIFIER");
	    break;
          default:
	    break;
	}
      }
    | /* EMPTY */
      {
        switch (blockType)
	{
          case chargedPartyLocnBlockType:
	    edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.IDENTIFIER, 0, 0,
			    chargedPartyLocnIdx);
	    break;
          case trackedCustomerLocnBlockType:
	    edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0,
			     trackedCustLocnIdx);
	    break;
          case trackingCustomerLocnBlockType:
	    edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0,
			     trackingCustLocnIdx);
	    break;
          default:
	    break;
	}
      }
    ;

  locationInformation:
      IFW_TAP3.LocationInformation
      networkLocation_mandopt
      homeLocationInformation_opt
      geographicalLocation_opt
      IFW_TAP3.Block_END
    ;

  locationInformation_mandopt:
      locationInformation
    | /* EMPTY */
      {
       // Set error code
       // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
       String offset = "-1";
       edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
       if ( (record_Type == record_MOC) )
       {
         edrAddError("ERR_TAP3_RET", 3, "severe", "31", "9", "3", offset, "-1", "Missing Location Info");
         setAssociatedTapErr("ERR_TAP3_MISSING_LOC_INFO", 3,"31" ,"9" ,"3");	
       }
       else if ( (record_Type == record_MTC) )
       {
         edrAddError("ERR_TAP3_RET", 3, "severe", "31", "10", "3", offset, "-1", "Missing Location Info");
         setAssociatedTapErr("ERR_TAP3_MISSING_LOC_INFO", 3,"31" ,"10" ,"3");	
       }
       else if ((record_Type == record_MSS))
       {
         edrAddError("ERR_TAP3_RET", 3, "severe", "33", "11", "3", offset, "-1", "Missing Location Info");
         setAssociatedTapErr("ERR_TAP3_MISSING_LOC_INFO", 3,"33" ,"11" ,"3");	

       }
      }
    ;

  longitude_opt:
      IFW_TAP3.Longitude
      {
          geographicalLocation = geographicalLocation + longitudeKey + ",";
          geographicalLocation = geographicalLocation + tokenString("IFW_TAP3.Longitude.LONGITUDE") + ",";
      }
    | /* EMTPY */
    ;

  mdn_opt:
      IFW_TAP3.Mdn
    | /* EMPTY */
    ;

  min_mandopt:
      IFW_TAP3.Min
    | /* EMPTY */
      {
	// Set error
        // offset = longToStr(edrFieldTokenBytePos(
	//  DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0));
	String offset = "-1";
        edrString(DETAIL.ERROR_REJECT_TYPE) = "ERR_TAP3_RET";
	edrAddError("ERR_TAP3_RET", 3, "severe",  "30",  "199",  "5",
                    offset, "-1", "Missing Chargeable Subscriber");
        setAssociatedTapErr("ERR_TAP3_MISSING_CHARGEABLE_SUBSCRIBER", 3,"30" ,"199" ,"5");	
      }
    ;

  minChargeableSubscriber:
      IFW_TAP3.MinChargeableSubscriber
      min_mandopt
      mdn_opt
      IFW_TAP3.Block_END
    | IFW_TAP3.Min  // kept for compatibility with before Tap0304
    ;

  messageDescription_mandopt:
      IFW_TAP3.MessageDescription
      {
	if (messageDescriptionCodeIsMissing == false)
        {
          messageDescription[lastCode]     = tokenString("IFW_TAP3.MessageDescription.MESSAGE_DESCRIPTION");
          if (messageDescriptionEntries <= lastCode)
          {
            messageDescriptionEntries      = lastCode + 1;
          }
	}
      }
    | /* EMPTY */
      {
          String offset = "-1";
          edrAddError("ERR_TAP3_RET", 1, "warning", "31", "143", "2", offset, "-1", "Missing message description");
          setAssociatedTapErr("ERR_TAP3_MISSING_MESSAGE_DESC",1 ,"31" ,"143" ,"2");	
      }
    ;

  messageDescriptionCode_mandopt:
      IFW_TAP3.MessageDescriptionCode
    | /* EMPTY */
      {
	messageDescriptionCodeIsMissing = true;
      }
    ;

  messageDescriptionInformation:
      IFW_TAP3.MessageDescriptionInformation
      messageDescriptionCode_mandopt
      {
	if (messageDescriptionCodeIsMissing == true)
	{
          String offset = "-1";
          edrAddError("ERR_TAP3_RET", 1, "warning", "30", "143", "2", offset, "-1", "Missing message description code");
          setAssociatedTapErr("ERR_TAP3_MISSING_MESSAGE_DESC_CODE",1 ,"30" ,"143" ,"2");	
	  messageDescriptionCodeIsMissing = false;
        }
	else
	{
          lastCode                         = tokenLong("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE");
          messageDescriptionCode[lastCode] = lastCode;
	}
      }
      messageDescription_mandopt
      IFW_TAP3.Block_END
    ;

  messageDescriptionInfoList:
      messageDescriptionInfoList
      messageDescriptionInformation
    | messageDescriptionInformation
    ;

  messageDescriptionInfoList_opt:
      IFW_TAP3.MessageDescriptionInfoList
      {
        errorStateTap3 = beginTap3MessageDescrInfo;
      }
      messageDescriptionInfoList
      {
        errorStateTap3 = endTap3MessageDescrInfo;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  messageStatus_mandopt:
      IFW_TAP3.MessageStatus
    | /* EMPTY */
      {
	messageStatusIsMissing = true;
      }
    ;

  messageType_mandopt:
      IFW_TAP3.MessageType
    | /* EMPTY */
      {
	messageTypeIsMissing = true;
      }
    ;

  moBasicCallInformation:
      IFW_TAP3.MoBasicCallInformation
      fraudMonitorIndicator_opt
      chargeableSubscriber_mandopt
      rapFileSequenceNumber_opt
      networkType_opt
      destination_opt
      destinationNetwork_opt
      callEventStartTimeStamp_mandopt
      totalCallEventDuration_mandopt
      simToolkitIndicator_opt
      causeForTerm_opt
      IFW_TAP3.Block_END
    ;

  moBasicCallInformation_mandopt:
      moBasicCallInformation
    | /* empty */
      {
        // Set sever error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "9", "3", offset, "-1", "Missing moBasicCallInformation block");
        setAssociatedTapErr("ERR_TAP3_MISSING_MOBCI_BLOCK",3 ,"30" ,"9" ,"3");	
      }
    ;

  mobileOriginatedCall:
      IFW_TAP3.MobileOriginatedCall
      {
        if ( createNewDetail(record_MOC, type_MOC) == false )
        {
          //TODO something
        }

        // Assume that the Destination field is present.
        destinationIsMissing = false;
      }
      moBasicCallInformation_mandopt
      locationInformation_mandopt
      equipmentInformation_opt
      {
        initializeChargeInfoTempFields();
      }
      basicServiceUsedList_mandopt
      {
	// Reset the long duration indicator for the last basic service
	if (successiveBasicServiceUsed > 1)
	{
          edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.LONG_DURATION_INDICATOR, 0, bsPacketIdx ) = "L"; //the last record of the chain
	}
      }
      supplServiceUsedList_opt
      camelServiceUsed_opt
      valueAddedServiceUsedList_opt
      {
        // add the charge info provided by the VAS ChargeDetail block to the global Detail
        updateBasicDetailWithVasCharge();
      }
      dualServiceRequested_opt
      {
        edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE, 0) = lastBasicDualService;
      }
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  mobileTerminatedCall:
      IFW_TAP3.MobileTerminatedCall
      {
        if ( createNewDetail(record_MTC, type_MTC) == false )
        {
          //TODO something
        }
        edrLong(DETAIL.USAGE_DIRECTION) = 1;
      }
      mtBasicCallInformation_mandopt
      locationInformation_mandopt
      equipmentInformation_opt
      {
        initializeChargeInfoTempFields();
      }
      basicServiceUsedList_mandopt
      {
	// Reset the long duration indicator for the last basic service
	if (successiveBasicServiceUsed > 1)
	{
          edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.LONG_DURATION_INDICATOR, 0, bsPacketIdx ) = "L"; //the first record of the chain
	}
      }
      supplServiceUsedList_opt
      camelServiceUsed_opt
      valueAddedServiceUsedList_opt
      {
        // add the charge info provided by the VAS ChargeDetail block to the global Detail
        updateBasicDetailWithVasCharge();
      }
      dualServiceRequested_opt
      {
        edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE, 0) = lastBasicDualService;
      }
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  mobileStationClassMark_opt:
      IFW_TAP3.MobileStationClassMark
      {
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.MS_CLASS_MARK, 0, "IFW_TAP3.MobileStationClassMark.MOBILE_STATION_CLASS_MARK");
        }
        else // if ( (record_Type == record_MOC) or (record_Type == record_MTC) or (record_Type == record_MSS))
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.MS_CLASS_MARK, 0, "IFW_TAP3.MobileStationClassMark.MOBILE_STATION_CLASS_MARK");
        }
      }
    | /* EMPTY */
      {
        if (record_Type == record_GPRS)
        {
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.MS_CLASS_MARK, 0);
	}
	else
	{
	  edrMissingInput(DETAIL.ASS_GSMW_EXT.MS_CLASS_MARK, 0);
	}
      }
    ;

  modificationTimestamp_mandopt:
      IFW_TAP3.ModificationTimestamp
      {
        timeStampType = hscsdModificationTimestampType;
      }
      dateTime
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.MODIFICATION_TIMESTAMP,
		0, bsPacketIdx, 0, pmidx);
      }
    ;

  msisdn_opt:
      IFW_TAP3.Msisdn
      {
        edrString(DETAIL.A_NUMBER) = strIAC + tokenString("IFW_TAP3.Msisdn.MSISDN");
        // edrString(DETAIL.A_NUMBER) = convertCli(edrString(DETAIL.A_NUMBER),
        //                                         "00", 0,
        //                                         NORM_NAC,
        //                                         calledNumberAnalysisIACarray[0], // NORM_IAC,
        //                                         calledNumberAnalysisCCarray[0], // NORM_CC,
        //                                         NORM_IAC_SIGN,
        //                                         NORM_NDC );
        edrString(DETAIL.INTERN_A_NUMBER_ZONE) = edrString(DETAIL.A_NUMBER);

        if      (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.A_NUMBER_USER, 0, "IFW_TAP3.Msisdn.MSISDN");
          edrString(DETAIL.ASS_GPRS_EXT.A_NUMBER_USER, 0) = strIAC + tokenString("IFW_TAP3.Msisdn.MSISDN");
        }
        else if (record_Type == record_MTC)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.Msisdn.MSISDN");
          edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0) = strIAC +
			tokenString("IFW_TAP3.Msisdn.MSISDN");
        }
        else if (record_Type == record_SCU)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.Msisdn.MSISDN");
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.Msisdn.MSISDN");
          edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0) = strIAC + tokenString("IFW_TAP3.Msisdn.MSISDN");
          edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0) = strIAC +
			tokenString("IFW_TAP3.Msisdn.MSISDN");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.Msisdn.MSISDN");
          edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0) = strIAC + tokenString("IFW_TAP3.Msisdn.MSISDN");
        }
      }
    | /* EMPTY */
      {
        if (record_Type == record_SCU)
        {
          edrMissingInput(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0);
        }
        else if (record_Type == record_MTC)
	{
          edrMissingInput(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0);
        }
      }
    ;

  mtBasicCallInformation:
      IFW_TAP3.MtBasicCallInformation
      fraudMonitorIndicator_opt
      chargeableSubscriber_mandopt
      rapFileSequenceNumber_opt
      networkType_opt
      callOriginator_opt
      originatingNetwork_opt
      callEventStartTimeStamp_mandopt
      totalCallEventDuration_mandopt
      simToolkitIndicator_opt
      causeForTerm_opt
      IFW_TAP3.Block_END
    ;

  mtBasicCallInformation_mandopt:
      mtBasicCallInformation
    | /* EMPTY */
      {
        // Set sever error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "10", "3", offset, "-1", "Missing mtBasicCallInformation block");
        setAssociatedTapErr("ERR_TAP3_MISSING_MTBCI_BLOCK",3 ,"30" ,"10" ,"3");	
      }
    ;


  multiRateIndicator_opt:
      IFW_TAP3.MultiRateIndicator
    | /* EMPTY */
    ;

  networkInfo_mandopt:
      IFW_TAP3.NetworkInfo
      {
        errorStateTap3 = beginTap3NetworkInfo;
      }
      utcTimeOffsetInfoList_mandopt
      recEntityInfoList_opt
      networkType_mandopt
      {
        // here we are in the header, so we are getting info regarding the Sender Network
        theSenderNetworkType = tokenLong("IFW_TAP3.NetworkType.NETWORK_TYPE");
        if((theSenderNetworkType < 0) or (theSenderNetworkType > 2))
          requestBatchReject(157, -1, 2,  0,  20, "ERR_TAP3_NETWORK_TYPE_OOR");
      }
      calledNumAnalysisList_opt
      {
        errorStateTap3 = endTap3NetworkInfo;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        /* Set Fatal Error */
        requestBatchReject(1, -1, 1,  0,  32, "ERR_TAP3_MISSING_NETWORK_INFO");
      }
    ;

  networkInitPDPContext_opt:
      IFW_TAP3.NetworkInitPDPContext
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.NETWORK_INITIATED_PDP, 0, "IFW_TAP3.NetworkInitPDPContext.NETWORK_INIT_PDP_CONTEXT");
      }
    | /* EMPTY */
      {
        edrLong(DETAIL.ASS_GPRS_EXT.NETWORK_INITIATED_PDP, 0) = 0;
      }
    ;

  callReference_opt:
      IFW_TAP3.CallReference
      {
        if (record_Type == record_LOCN)
	{
          edrConnectToken(DETAIL.ASS_LOCN_EXT.CALL_REFERENCE, 0,
                          "IFW_TAP3.CallReference.CALL_REFERENCE");
        }
        else if (record_Type == record_MOC or record_Type == record_MTC or record_Type == record_MSS)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0,
                          "IFW_TAP3.CallReference.CALL_REFERENCE");
        }
      }
    | /* EMPTY */
    ;

  networkLocation:
      IFW_TAP3.NetworkLocation
      recEntityCode_mandopt
      {
        theRecEntityId = getRecEntityId(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
        //theRecEntityType= getRecEntityType(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
        if (recEntityCodeIsMissing == true)
        {
           // set Severe error

           edrAddError("ERR_TAP3_MISSING_REC_ENTITY_CODE",3,"severe","30","184","5","0","-1","Missing Record Entity code");
           recEntityCodeIsMissing = false ;
        }

	if (recEntityCodeIsMissing == true)
	{
	  if (record_Type == record_MOC)
	  {
	    edrMissingInput(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0);
          }
          else if (record_Type == record_MTC)
	  {
	    edrMissingInput(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION, 0);
          }
	  recEntityCodeIsMissing = false;
        }
	else
	{
          edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0) = theRecEntityId;
          edrString(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION, 0) = theRecEntityId;
          if (record_Type == record_MOC)
          {
            edrString(DETAIL.INTERN_A_NUMBER_ZONE) = "0000" + theRecEntityId;
          }
          else if (record_Type == record_MTC)
          {
            edrString(DETAIL.INTERN_B_NUMBER_ZONE) = "0000" + theRecEntityId;
          }
        }
      }
      callReference_opt
      locationArea_opt
      cellId_opt
      IFW_TAP3.Block_END
    ;

  networkLocation_mandopt:
      networkLocation
    | /* EMPTY */
      {
       // Sever error
       // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSM_EXT));
       String offset = "-1";
       edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
       edrAddError("ERR_TAP3_RET", 3, "severe", "30", "138", "4", offset, "-1", "Missing Network Location");
       setAssociatedTapErr("ERR_TAP3_MISSING_NETWORK_LOC",3 ,"30" ,"138" ,"4");	
      }
    ;

  networkType_mandopt:
      IFW_TAP3.NetworkType
    | /* EMPTY */
      {
       // Set Fatal Error
       requestBatchReject(6, -1, 2,  0,  34, "ERR_TAP3_MISSING_NETWORK_TYPE");
      }
    ;

  networkType_opt:
      IFW_TAP3.NetworkType
      {
        if (theSenderNetworkType == 0)
        {
          edrConnectToken(DETAIL.SOURCE_NETWORK_TYPE, "IFW_TAP3.NetworkType.NETWORK_TYPE");
//          edrString(DETAIL.SOURCE_NETWORK_TYPE)      = longToStr(tokenLong("IFW_TAP3.NetworkType.NETWORK_TYPE"));
        }
        else
        {
          // if theSenderNetworkType was set to any thing but mixed(ie. 0) then it overrides the Detail value
          edrString(DETAIL.SOURCE_NETWORK_TYPE)      = longToStr(theSenderNetworkType);
        }
      }
    | /* EMPTY */
      {
        edrString(DETAIL.SOURCE_NETWORK_TYPE)      = longToStr(theSenderNetworkType);
      }
    ;

  nonChargedNumber_mandopt: // only used for record_SCU
      IFW_TAP3.AddressStringDigits
      {
        if ( edrLong(DETAIL.USAGE_DIRECTION) == 0 )
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
          edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0) = strIAC + tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
          edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0) = strIAC + tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        }
        edrString(DETAIL.B_NUMBER) =  strIAC + tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
      {
        if ( edrLong(DETAIL.USAGE_DIRECTION) == 0 )
        {
          edrMissingInput(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0);
        }
        else
        {
          edrMissingInput(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0);
        }
      }
    ;

  nonChargedParty_mandopt:
      IFW_TAP3.NonChargedParty
      {
        callNumberType = nonChargedPartyType;
      }
      nonChargedNumber_mandopt
      calledNumAnalysisCode_opt
      IFW_TAP3.Block_END
      {
        //normalize the number
        // edrString(DETAIL.B_NUMBER) = convertCli(edrString(DETAIL.B_NUMBER),
        //                                         edrString(DETAIL.B_MODIFICATION_INDICATOR),
        //                                         edrLong(DETAIL.B_TYPE_OF_NUMBER),
        //                                         NORM_NAC,
        //                                         calledNumberAnalysisIACarray[getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)], // NORM_IAC,
        //                                         calledNumberAnalysisCCarray[ getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)], // NORM_CC,
        //                                         NORM_IAC_SIGN,
        //                                         NORM_NDC );
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
     //   lastCalledNumAnalysisCode = 1;
      }
    | /* EMPTY */
      {
	nonChargedPartyIsMissing = true;
      }
    ;

  numberOfChannels_opt:
      IFW_TAP3.NumberOfChannels
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.MAX_NUMBER_OF_CHANNELS , 0, bsPacketIdx, 0,  pmidx,  "IFW_TAP3.NumberOfChannels.NUMBER_OF_CHANNELS");
      }
    | /* EMPTY */
    ;

  numberOfChannels_basichscd_mandopt:
      IFW_TAP3.NumberOfChannels
      {
       edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.NUMBER_OF_CHANNELS, 0, bsPacketIdx, 0,
			"IFW_TAP3.NumberOfChannels.NUMBER_OF_CHANNELS");
      }
    | /* EMPTY */
      {
       edrMissingInput(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.NUMBER_OF_CHANNELS, 0, bsPacketIdx, 0);
      }
    ;


  numberOfChannelsUsed_mandopt:
      IFW_TAP3.NumberOfChannelsUsed
    | /* EMPTY */
      {
        numberOfChannelsUsedIsMissing = true;
      }
    ;

  numberOfDecimalPlaces_mandopt:
      IFW_TAP3.NumberOfDecimalPlaces
    | /* EMPTY */
      {
	// Set Fatal Error
        requestBatchReject(106, -1, 3,  0,  31, "ERR_TAP3_MISSING_NO_OF_DECIMAL_PLACES");
      }
    ;

  operatorSpecInformation_opt:
      IFW_TAP3.OperatorSpecInfoList
      operatorSpecInfoList_opt
      IFW_TAP3.Block_END
    | IFW_TAP3.OperatorSpecInformation // compatibility for before tap0304
      {
        storeTheOperatorSpecInformation();
      }
    | /* EMPTY */
    ;

  operatorSpecInfoList_opt:
      operatorSpecInfoList
    | /* EMPTY */
    ;

  operatorSpecInfoList:
      operatorSpecInfoList
      IFW_TAP3.OperatorSpecInformation
    | IFW_TAP3.OperatorSpecInformation //the first of the list
      {
        storeTheOperatorSpecInformation();
      }
    ;

  originatingNetwork_opt:
      IFW_TAP3.OriginatingNetwork
      {
        edrConnectToken(DETAIL.SOURCE_NETWORK, "IFW_TAP3.OriginatingNetwork.NETWORK_ID");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.SOURCE_NETWORK);
      }
    ;

  packetDataProtocollAddress:
      IFW_TAP3.PacketDataProtocollAddress
    ;

  partialTypeIndicator_opt:
      IFW_TAP3.PartialTypeIndicator
      {
        // only called in GPRS records, where we do not do splitting ourselves, ie we can copy this value
        edrConnectToken(DETAIL.LONG_DURATION_INDICATOR, "IFW_TAP3.PartialTypeIndicator.PARTIAL_TYPE_INDICATOR");
      }
    | /* EMPTY */
	{
		edrMissingInput(DETAIL.LONG_DURATION_INDICATOR);
	}
    ;

  pDPContextStartTimestamp_opt:
      IFW_TAP3.PDPContextStartTimestamp
      {
        timeStampType = pDPContextStartTimestampType;
      }
      dateTime
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  priorityCode_mandopt:
      IFW_TAP3.PriorityCode
    | /* EMPTY */
      {
	priorityCodeIsMissing = true;
      }
    ;

  qoSAllocRetenPriority_opt:
      IFW_TAP3.QoSAllocRetenPriority
      {
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + QosAllocRetenPriorityKey + ",";
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + tokenString("IFW_TAP3.QoSAllocRetenPriority.QOS_INTEGER") + ",";
      }
    | /* EMPTY */
    ;

  qoSDelay_mandopt:
      IFW_TAP3.QoSDelay
    | /* EMPTY */
      {
	qoSDelayIsMissing = true;
      }
    ;

  qoSGuaranteedBitRateDownlink_opt:
      IFW_TAP3.QoSGuaranteedBitRateDownlink
      {
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + QosGuaranteedBitRateDownLnKey + ",";
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + tokenString("IFW_TAP3.QoSGuaranteedBitRateDownlink.QOS_BYTE") + ",";
      }
    | /* EMPTY */
    ;

  qoSGuaranteedBitRateUplink_opt:
      IFW_TAP3.QoSGuaranteedBitRateUplink
      {
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + QosGuaranteedBitRateUpLnKey + ",";
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + tokenString("IFW_TAP3.QoSGuaranteedBitRateUplink.QOS_BYTE") + ",";
      }
    | /* EMPTY */
    ;

  qoSMaxBitRateDownlink_mandopt:
      IFW_TAP3.QoSMaxBitRateDownlink
      {
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + QosMaxBitRateDownLnKey + ",";
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + tokenString("IFW_TAP3.QoSMaxBitRateDownlink.QOS_BYTE") + ",";
      }
    | /* EMPTY */
    ;

  qoSMaxBitRateUplink_mandopt:
      IFW_TAP3.QoSMaxBitRateUplink
      {
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + QosMaxBitRateUpLnKey + ",";
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + tokenString("IFW_TAP3.QoSMaxBitRateUplink.QOS_BYTE") + ",";
      }
    | /* EMPTY */
    ;

  qoSMeanThroughput_mandopt:
      IFW_TAP3.QoSMeanThroughput
    | /* EMPTY */
      {
        qoSMeanThroughputIsMissing = true;
      }
    ;

  qoSPeakThroughput_mandopt:
      IFW_TAP3.QoSPeakThroughput
    | /* EMPTY */
      {
	qoSPeakThroughputIsMissing = true;
      }
    ;

  qoSPrecedence_mandopt:
      IFW_TAP3.QoSPrecedence
    | /* EMPTY */
      {
        qoSPrecedenceIsMissing = true;
      }
    ;

  qoSReliability_mandopt:
      IFW_TAP3.QoSReliability
    | /* EMPTY */
      {
         qoSReliabilityIsMissing = true;
      }
    ;

  qoSRequested_opt:
      IFW_TAP3.GSMQoSRequested
      qoSDelay_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_DELAY, 0, "IFW_TAP3.QoSDelay.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_DELAY, 0, gsPacketIdx,  "IFW_TAP3.QoSDelay.QOS_INTEGER");
	if (qoSDelayIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_DELAY, 0, gsPacketIdx);
	  qoSDelayIsMissing = false;
        }
      }
      qoSMeanThroughput_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_MEAN_THROUGHPUT, 0, "IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_MEAN_THROUGHPUT, 0, gsPacketIdx,  "IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
	if (qoSMeanThroughputIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_MEAN_THROUGHPUT, 0, gsPacketIdx);
	  qoSMeanThroughputIsMissing = false;
        }
      }
      qoSPeakThroughput_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PEAK_THROUGHPUT, 0, "IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_PEAK_THROUGHPUT, 0, gsPacketIdx,  "IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
	if (qoSPeakThroughputIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_PEAK_THROUGHPUT, 0, gsPacketIdx);
	  qoSPeakThroughputIsMissing = false;
        }
      }
      qoSPrecedence_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PRECEDENCE, 0, "IFW_TAP3.QoSPrecedence.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_PRECEDENCE, 0, gsPacketIdx,  "IFW_TAP3.QoSPrecedence.QOS_INTEGER");
	if (qoSPrecedenceIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_PRECEDENCE, 0, gsPacketIdx);
	  qoSPrecedenceIsMissing = false;
        }
      }
      qoSReliability_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_RELIABILITY, 0, "IFW_TAP3.QoSReliability.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_RELIABILITY, 0, gsPacketIdx,  "IFW_TAP3.QoSReliability.QOS_INTEGER");
	if (qoSReliabilityIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_RELIABILITY, 0, gsPacketIdx);
	  qoSReliabilityIsMissing = false;
        }
      }
      IFW_TAP3.Block_END
    |
      IFW_TAP3.UMTSQoSRequested
      qoSTrafficClass_mandopt
      qoSMaxBitRateUplink_mandopt
      qoSMaxBitRateDownlink_mandopt
      qoSGuaranteedBitRateDownlink_opt
      qoSGuaranteedBitRateUplink_opt
      qoSAllocRetenPriority_opt
      {
          edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_REQUESTED,0,gsPacketIdx) = strUMTSQosReqOrUsed; 

          //Reset the strUMTSQosReqOrUsed field for reuse
          strUMTSQosReqOrUsed = "";
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  qoSTrafficClass_mandopt:
      IFW_TAP3.QoSTrafficClass
      {
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + QosTrafficClassKey + ",";
          strUMTSQosReqOrUsed = strUMTSQosReqOrUsed + tokenString("IFW_TAP3.QoSTrafficClass.QOS_INTEGER") + ",";
      }
    | /* EMPTY */
    ;

  qoSUsed_opt:
      IFW_TAP3.GSMQoSUsed
      qoSDelay_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_DELAY, 0, "IFW_TAP3.QoSDelay.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_DELAY, 0, gsPacketIdx, "IFW_TAP3.QoSDelay.QOS_INTEGER");
	if (qoSDelayIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_DELAY, 0, gsPacketIdx);
	  qoSDelayIsMissing = false;
        }
      }
      qoSMeanThroughput_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_MEAN_THROUGHPUT, 0, "IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_MEAN_THROUGHPUT, 0, gsPacketIdx, "IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
	if (qoSMeanThroughputIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_MEAN_THROUGHPUT, 0, gsPacketIdx);
	  qoSMeanThroughputIsMissing = false;
        }
      }
      qoSPeakThroughput_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_PEAK_THROUGHPUT, 0, "IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_PEAK_THROUGHPUT, 0, gsPacketIdx, "IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
	if (qoSPeakThroughputIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_PEAK_THROUGHPUT, 0, gsPacketIdx);
	  qoSPeakThroughputIsMissing = false;
        }
      }
      qoSPrecedence_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_PRECEDENCE, 0, "IFW_TAP3.QoSPrecedence.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_PRECEDENCE, 0, gsPacketIdx, "IFW_TAP3.QoSPrecedence.QOS_INTEGER");
	if (qoSPrecedenceIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_PRECEDENCE, 0, gsPacketIdx);
	  qoSPrecedenceIsMissing = false;
        }
      }
      qoSReliability_mandopt
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_RELIABILITY, 0, "IFW_TAP3.QoSReliability.QOS_INTEGER");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_RELIABILITY, 0, gsPacketIdx, "IFW_TAP3.QoSReliability.QOS_INTEGER");
	if (qoSReliabilityIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_RELIABILITY, 0, gsPacketIdx);
	  qoSReliabilityIsMissing = false;
        }
      }
      IFW_TAP3.Block_END
    |
      IFW_TAP3.UMTSQoSUsed
      qoSTrafficClass_mandopt
      qoSMaxBitRateUplink_mandopt
      qoSMaxBitRateDownlink_mandopt
      qoSGuaranteedBitRateDownlink_opt
      qoSGuaranteedBitRateUplink_opt
      qoSAllocRetenPriority_opt
      {
          edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_USED, 0, gsPacketIdx) = strUMTSQosReqOrUsed; 

          //Reset the strUMTSQosReqOrUsed field for reuse
          strUMTSQosReqOrUsed = "";
      }
      IFW_TAP3.Block_END
    |
      // for compatibility with before tap0304
      IFW_TAP3.QoSUsed
      IFW_TAP3.QoSDelay
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_DELAY, 0, "IFW_TAP3.QoSDelay.QOS_INTEGER");
      }
      IFW_TAP3.QoSMeanThroughput
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_MEAN_THROUGHPUT, 0, "IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPeakThroughput
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_PEAK_THROUGHPUT, 0, "IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPrecedence
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_PRECEDENCE, 0, "IFW_TAP3.QoSPrecedence.QOS_INTEGER");
      }
      IFW_TAP3.QoSReliability
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_USED_RELIABILITY, 0, "IFW_TAP3.QoSReliability.QOS_INTEGER");
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  rapFileSequenceNumber_opt: //For CallEventDetails
      IFW_TAP3.RapFileSequenceNumber
      {
            edrConnectToken(DETAIL.RAP_FILE_SEQ_NO,
                            "IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER");
      }
    | /* EMPTY */
      {
            edrMissingInput(DETAIL.RAP_FILE_SEQ_NO);
      }
    ;

  rapFileSequenceNumberBatch_opt: //For BatchControlInformation and Notification
      IFW_TAP3.RapFileSequenceNumber
      {
            edrConnectToken(HEADER.RAP_FILE_SEQ_NO,
                            "IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER");
      }
    | /* EMPTY */
      {
            edrMissingInput(HEADER.RAP_FILE_SEQ_NO);
      }
    ;

  radioChannelRequested_opt:
      IFW_TAP3.RadioChannelRequested
      {
        edrConnectToken(DETAIL.QOS_REQUESTED, "IFW_TAP3.RadioChannelRequested.RADIO_CHANNEL_REQUESTED");
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.QOS_REQUESTED, 0, bsPacketIdx, "IFW_TAP3.RadioChannelRequested.RADIO_CHANNEL_REQUESTED");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.QOS_REQUESTED);
      }
    ;

  radioChannelUsed_opt:
      IFW_TAP3.RadioChannelUsed
      {
        edrConnectToken(DETAIL.QOS_USED, "IFW_TAP3.RadioChannelUsed.RADIO_CHANNEL_USED");
	edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.QOS_USED, 0, bsPacketIdx, "IFW_TAP3.RadioChannelUsed.RADIO_CHANNEL_USED");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.QOS_USED);
      }
    ;

  recEntityCode_mandopt:
      IFW_TAP3.RecEntityCode
    | /* EMPTY */
      {
        recEntityCodeIsMissing = true;
      }
    ;

  recEntityCodeList: // list in form 1*GGSN + n*SGSN
      recEntityCodeList
      recEntityCodeElement
    | recEntityCodeElement //first element of the list
    ;

  recEntityCodeElement:
      IFW_TAP3.RecEntityCode
      {
        theRecEntityType                                 = getRecEntityType(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE") );
        if      (theRecEntityType == recEntityType_GGSN)
        {
          edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0)                      = getRecEntityId(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
          edrString(DETAIL.ASS_GPRS_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0) = edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0);
        }
        else if (theRecEntityType == recEntityType_SGSN)
        {
          // overwrite to keep only the last element of the list
          // TODO: Once the Sol 42 Grammars are enhanced to handle multiple SGSN's,
          // the scalar SGSN_ADDRESS field in the ASSOCIATED_GPRS_EXTENSION container 
          // block description and the following statement needs to be removed.
          edrString(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0) = getRecEntityId(  tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE") );

          // Add support for Multiple SGSN
          if ( edrAddDatablock( DETAIL.ASS_GPRS_EXT.SGSN_INFO_LIST) == false )
          {
            String Msg = "failed to add ASS_GPRS_EXT.SGSN_INFO_LIST datablock for EDR "+longToStr(records);
            edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
          }
          else
          {
            edrString(DETAIL.ASS_GPRS_EXT.SGSN_INFO_LIST.SGSN_ADDRESS, 0, SGSNidx) = getRecEntityId(  tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE") );

            SGSNidx = SGSNidx + 1;
          }
        }
        else if (theRecEntityType == recEntityType_WLAN)
        {
          // overwrite to keep only the last element of the list
          edrString(DETAIL.ASS_GPRS_EXT.WLAN_ADDRESS, 0) = getRecEntityId(  tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE") );
        }
        else
        {
          // String Msg = "getRecEntityType("+longToStr(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"))+"), !=GGSN and !=SGSN";
          // edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        }
      }
    ;

  recEntityCodeList_mandopt:
      IFW_TAP3.RecEntityCodeList
      recEntityCodeList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_GPRS_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0);
      }
    ;

  recEntityCodeList_opt2:
      recEntityCodeList
    | /* EMPTY */
    ;

  recEntityId:
      IFW_TAP3.GmlcAddress
      {
        last_recEntityId_Type = recEntityId_gmlcAddress;
        last_recEntityId      = tokenString("IFW_TAP3.GmlcAddress.GMLC_ADDRESS");
      }
    | IFW_TAP3.MscId
      {
        last_recEntityId_Type = recEntityId_mscId;
        last_recEntityId      = tokenString("IFW_TAP3.MscId.MSC_ID");
      }
    | IFW_TAP3.Msisdn
      {
        last_recEntityId_Type = recEntityId_msisdn;
        last_recEntityId      = tokenString("IFW_TAP3.Msisdn.MSISDN");
      }
    | ipAddress // gsnAddress
      {
        last_recEntityId      = last_ipAddress;
        if ( strSearch( last_recEntityId, "." ) >= 0 )  // isIpV4
        {
          last_recEntityId_Type=recEntityId_iPTextV4Address;
        }
        else
        {
          last_recEntityId_Type=recEntityId_iPTextV6Address;
        }
      }
    ;

  recEntityId_mandopt:
      recEntityId
    | /* EMPTY */
      {
        recEntityIdIsMissing = true;
      }
    ;

  recEntityInfoList:
      recEntityInfoList
      recEntityInformation
    | /* EMPTY */
    ;

  recEntityInfoList_opt:
      IFW_TAP3.RecEntityInfoList
      recEntityInfoList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  recEntityInformation:
      IFW_TAP3.RecEntityInformation
      recEntityCode_mandopt
      {
	if (recEntityCodeIsMissing == true)
	{
	   // set fatal error
           requestBatchReject(183, -1, 3,  0,  30, "ERR_TAP3_MISSING_REC_ENTITY_CODE");
	   recEntityCodeIsMissing = false ;
        }
        lastCode                   = tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE");

	if(lastCode < 0)
	{
		requestBatchReject(184, -1, 3, 0, 20, "ERR_TAP3_REC_ENTITY_CODE_LESS_THAN_LOWER_LIMIT");
	}
	if(lastCode > 999)
	{
		requestBatchReject(184, -1, 3, 0, 20, "ERR_TAP3_REC_ENTITY_CODE_GREATER_THAN_UPPER_LIMIT");
	}
        recEntityCode[lastCode]    = lastCode;
      }
      recEntityType_mandopt
      {
	if (recEntityTypeIsMissing == true)
	{
	   // set fatal error
           requestBatchReject(183, -1, 3,  0,  31, "ERR_TAP3_MISSING_REC_ENTITY_TYPE");
	   recEntityTypeIsMissing = false;
        }
        recEntityType[lastCode]    = tokenLong("IFW_TAP3.RecEntityType.REC_ENTITY_TYPE");

        // Recording Entity Type should be in the range 1 to 6.
        if ( (recEntityType[lastCode] < 1) or (recEntityType[lastCode] > 6) )
        {
           // If not, set out of range fatal error
           requestBatchReject(186, -1, 3,  0,  20, "ERR_TAP3_REC_ENTITY_TYPE_OOR");
        }
      }
      recEntityId_mandopt
      {
	if (recEntityIdIsMissing == true)
	{
	   // set fatal error
           requestBatchReject(183, -1, 3,  0,  32, "ERR_TAP3_MISSING_REC_ENTITY_ID");
	   recEntityIdIsMissing = false;
        }
        recEntityId_Type[lastCode] = last_recEntityId_Type;
        recEntityId[lastCode]      = last_recEntityId;
        if (recEntityEntries <= lastCode)
        {
          recEntityEntries         = lastCode + 1;
        }
      }
      IFW_TAP3.Block_END
    ;

  recEntityType_mandopt:
      IFW_TAP3.RecEntityType
    | /* EMPTY */
      {
	recEntityTypeIsMissing = true;
      }
    ;

  recipient_mandopt:
      IFW_TAP3.Recipient
    | /* EMPTY */
    {
      edrMissingInput(HEADER.RECIPIENT);
    }
    ;

  releaseVersionNumber_mandopt:
      IFW_TAP3.ReleaseVersionNumber
    | /* EMPTY */
     {
       edrMissingInput(HEADER.RELEASE_VERSION);
     }
    ;

  remotePdpAddressList:
      remotePdpAddressList
      packetDataProtocollAddress
      {
        lastRemotePdpAddressList = lastRemotePdpAddressList + ", " +
                                   tokenString("IFW_TAP3.PacketDataProtocollAddress.PACKET_DATA_PROTOCOLL_ADDRESS");
      }
    | packetDataProtocollAddress
      {
        lastRemotePdpAddressList = tokenString("IFW_TAP3.PacketDataProtocollAddress.PACKET_DATA_PROTOCOLL_ADDRESS");
      }
    ;

  remotePdpAddressList_opt:
      IFW_TAP3.RemotePdpAddressList
      {
        lastRemotePdpAddressList = "";
      }
      remotePdpAddressList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastRemotePdpAddressList = "";
      }
    ;

  remotePdpAddressList_opt2:
      remotePdpAddressList
    | /* EMPTY */ //accept empty list
    ;

  scuBasicInformation:
      IFW_TAP3.ScuBasicInformation
      scuVasChargeableSubscriber_mandopt
      chargedPartyStatus_mandopt
      {
        edrConnectToken(DETAIL.USAGE_DIRECTION, "IFW_TAP3.ChargedPartyStatus.CHARGED_PARTY_STATUS");
	if (chargedPartyStatusIsMissing == true)
	{
	  edrMissingInput(DETAIL.USAGE_DIRECTION);
	  chargedPartyStatusIsMissing = false;
        }
      }
      nonChargedParty_mandopt
      {
	if (nonChargedPartyIsMissing == true)
	{
	  if (edrLong(DETAIL.USAGE_DIRECTION) == 0)
	  {
	    // Originated Call set sever error
            // Set severe error code
            // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
            String offset = "-1";
            edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
            edrAddError("ERR_TAP3_RET", 3, "severe", "32", "191", "4", offset, "-1", "Missing non charged party");
            setAssociatedTapErr("ERR_TAP3_MISSING_NON_CHARGED_PARTY",3 ,"32" ,"191" ,"4");	
          }
	  else
	  {
	    // Terminated call set warning
            // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
	    String offset = "-1";
            edrAddError("ERR_TAP3_RET", 1, "warning", "32", "191", "4", offset, "-1", "Missing non charged pary");
            setAssociatedTapErr("ERR_TAP3_MISSING_NON_CHARGED_PARTY",1 ,"32" ,"191" ,"4");	
          }
        }
      }
      clirIndicator_opt
      {
          // for optimization resons we are populating ClirIndicator in DEATIL.USAGE_CLASS
          edrConnectToken(DETAIL.USAGE_CLASS,"IFW_TAP3.ClirIndicator.CLIR_INDICATOR");
      }
      originatingNetwork_opt
      destinationNetwork_opt
      IFW_TAP3.Block_END
    ;

  scuBasicInformation_mandopt:
      scuBasicInformation
    | /* EMPTY */
      {
        // Set severe error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "12", "3", offset, "-1", "Missing scuBasicInformation block");
        setAssociatedTapErr("ERR_TAP3_MISSING_SCUBI_BLOCK",3 ,"30" ,"12" ,"3");	
      }
    ;

  scuChargeType:
      IFW_TAP3.ScuChargeType
      messageStatus_mandopt
      {
        // CALL_COMPLETION_INDICATOR must be stored in a 2 digit string (prepend with 0 if necessary)
        edrConnectToken(DETAIL.CALL_COMPLETION_INDICATOR, "IFW_TAP3.MessageStatus.MESSAGE_STATUS");
	if (messageStatusIsMissing == true)
	{
	  edrMissingInput(DETAIL.CALL_COMPLETION_INDICATOR);
        }
	else
	{
          if (tokenLong("IFW_TAP3.MessageStatus.MESSAGE_STATUS") < 10)
          {
            edrString(DETAIL.CALL_COMPLETION_INDICATOR) = "0" + edrString(DETAIL.CALL_COMPLETION_INDICATOR);
          }
        }
      }
      priorityCode_mandopt
      {
        edrConnectToken(DETAIL.QOS_REQUESTED, "IFW_TAP3.PriorityCode.PRIORITY_CODE");

		// Set severe error.

	    Long tmpPriorityCode;
	    tmpPriorityCode = tokenLong("IFW_TAP3.PriorityCode.PRIORITY_CODE");
	    if((tmpPriorityCode < 0) or (tmpPriorityCode >2))
	      edrAddError("ERR_TAP3_PRIORITY_CODE_OOR", 3, "severe", "20", "170", "5","0" , "-1", "Out of Range Priotity Code");
	if (priorityCodeIsMissing == true)
	{
	  edrMissingInput(DETAIL.QOS_REQUESTED);
        }
      }
      distanceChargeBandCode_opt
      {
          edrConnectToken(DETAIL.ZONE_DESCRIPTION,"IFW_TAP3.DistanceChargeBandCode.DISTANCE_CHARGE_BAND_CODE");
      }
      messageType_mandopt
      {
        edrConnectToken(DETAIL.QOS_USED, "IFW_TAP3.MessageType.MESSAGE_TYPE"); //TODO find a better storage
	if (messageTypeIsMissing == true)
	{
	  edrMissingInput(DETAIL.QOS_USED);
        }
      }
      messageDescriptionCode_mandopt
      {
        edrString(DETAIL.DESCRIPTION) = getMessageDescription(tokenLong("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE"));
	if (messageDescriptionCodeIsMissing == true)
	{
          String offset = "-1";
          edrAddError("ERR_TAP3_RET", 1, "warning", "34", "192", "2", offset, "-1", "Missing message description code");
          setAssociatedTapErr("ERR_TAP3_MISSING_MESSAGE_DESC_CODE",1 ,"34" ,"192" ,"2");	
	  messageDescriptionCodeIsMissing = false;
        }
      }
      IFW_TAP3.Block_END
    ;

  scuChargeType_mandopt:
      scuChargeType
    | /* EMPTY */
      {
	// Set severe error
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "35", "12", "3", offset, "-1", "Missing Scu Charge Type");
        setAssociatedTapErr("ERR_TAP3_MISSING_SCU_CHARGE_TYPE",3 ,"35" ,"12" ,"3");	
      }
    ;

  scuTimeStamps:
      IFW_TAP3.ScuTimeStamps
      depositTimeStamp_mandopt
      {
        // Mandatory field for SCU, will serve as a default
        lastValidLocalTimeStamp = lastLocalTimeStamp; // to serve as default LocalTimeStamp for coresponding record
        lastValidUtcTimeOffset  = lastUtcTimeOffset;  // to serve as default UtcTimeOffset for coresponding record

        // set a real timestamp on the CP if it is missing
        Long i;
        for (i=0 ; i< edrNumDatablocks( DETAIL.ASS_CBD.CP, ACBidx) ; i=i+1)
        {
          if (edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, i) == defLocalTime)
          {
            edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, ACBidx, i) = edrDate(DETAIL.CHARGING_START_TIMESTAMP);
          }
        }
        if (depositTimeStampIsMissing == true)
	{
	  edrMissingInput(DETAIL.CHARGING_START_TIMESTAMP);
        }
      }
      completionTimeStamp_mandopt
      {
        if (completionTimeStampIsMissing == true)
	{
	  edrMissingInput(DETAIL.CHARGING_END_TIMESTAMP);
        }
      }
      chargingPoint_mandopt
      IFW_TAP3.Block_END
    ;

  scuTimeStamps_mandopt:
      scuTimeStamps
    | /* EMPTY */
      {
	// Set severe error
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "36", "12", "3", offset, "-1", "Missing Scu Timestamps");
        setAssociatedTapErr("ERR_TAP3_MISSING_SCU_TIMESTAMPS",3 ,"36" ,"12" ,"3");	
      }
    ;

  scuVasChargeableSubscriber:
      gsmChargeableSubscriber
    | minChargeableSubscriber
    ;

  scuVasChargeableSubscriber_mandopt:
      scuVasChargeableSubscriber
    | /* EMPTY */
      {
        // Set severe error code
        if ( (record_Type == record_VAS) )
        {
          // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
	  String offset = "-1";
          edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
          // edrAddError("ERR_TAP3_RET", 3, "severe", "21", tag, depth, offset, arrayIndex, ruleID);
          edrAddError("ERR_TAP3_RET", 3, "severe", "30", "13", "3", offset, "-1", "Missing Chargeableable Subscriber ");
          setAssociatedTapErr("ERR_TAP3_MISSING_CHARGEABLE_SUBCRIBER",3 ,"30" ,"13" ,"3");	
        }
	else if ((record_Type == record_SCU))
	{
          // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_GSMW_EXT));
	  String offset = "-1";
          edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
          // edrAddError("ERR_TAP3_RET", 3, "severe", "21", tag, depth, offset, arrayIndex, ruleID);
          edrAddError("ERR_TAP3_RET", 3, "severe", "30", "191", "3", offset, "-1", "Missing Chargeableable Subscriber ");
          setAssociatedTapErr("ERR_TAP3_MISSING_CHARGEABLE_SUBCRIBER",3 ,"30" ,"191" ,"3");	
	}
      }
    ;

  sender_mandopt:
      IFW_TAP3.Sender
    | /* EMPTY */
      {
        edrMissingInput(HEADER.SENDER);
      }
    ;

  serviceCentreUsage:
      IFW_TAP3.ServiceCentreUsage
      {
        if ( createNewDetail(record_SCU, type_SCU) == false )
        {
          //TODO something
        }
        edrString(DETAIL.BASIC_SERVICE) = "E00";
      }
      fraudMonitorIndicator_opt
      scuBasicInformation_mandopt
      rapFileSequenceNumber_opt
      networkType_opt
      servingNetwork_opt
      recEntityCode_mandopt
      {
        edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0) = getRecEntityId(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
	if (recEntityCodeIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0);
	  recEntityCodeIsMissing = false;
        }
        initializeChargeInfoTempFields();
      }
      chargeInformation_mandopt
      {
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      scuChargeType_mandopt
      scuTimeStamps_mandopt
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  servingNetwork_opt:
      IFW_TAP3.ServingNetwork
      {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.SERVING_NETWORK,0,"IFW_TAP3.ServingNetwork.SERVING_NETWORK");
      }
    | /* EMPTY */
    ;

  servingBid_opt:
      IFW_TAP3.ServingBid
      {
          geographicalLocation = geographicalLocation + servingBIDKey + ",";
          geographicalLocation = geographicalLocation + tokenString("IFW_TAP3.ServingBid.SERVING_BID") + ",";
      }
    | /* EMPTY */
    ;

  servingLocationDescription_opt:
      IFW_TAP3.LocationDescription
      {
          geographicalLocation = geographicalLocation + servingLocationDescKey + ",";
          geographicalLocation = geographicalLocation + tokenString("IFW_TAP3.LocationDescription.LOCATION_DESCRIPTION") + ",";
      }
    | /* EMPTY */
    ;

  simChargeableSubscriber:
      IFW_TAP3.SimChargeableSubscriber
      imsi_mandopt
      {
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0, "IFW_TAP3.Imsi.IMSI");
          edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)    = "I"; //I=IMSI , M=MSISDN, P=IP ,  S=SIM ,  ...
	  if (imsiIsMissing == true)
	  {
	    edrMissingInput(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0);
	    imsiIsMissing = false;
          }
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0, "IFW_TAP3.Imsi.IMSI");
          edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)    = "I"; //I=IMSI , M=MSISDN, P=IP ,  S=SIM ,  ...
	  if (imsiIsMissing == true)
	  {
	    edrMissingInput(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0);
	    imsiIsMissing = false;
          }
        }
      }
      msisdn_opt
      IFW_TAP3.Block_END
    ;

  simToolkitIndicator_opt:
      IFW_TAP3.SimToolkitIndicator
      {
          // This field will be stored in DETAIL.DISCOUNT_KEY for optimization
          edrConnectToken(DETAIL.DISCOUNT_KEY,"IFW_TAP3.SimToolkitIndicator.SIM_TOOLKIT_INDICATOR");
      }
    | /* EMPTY */
    {
        edrMissingInput(DETAIL.DISCOUNT_KEY);
    } 
    ;

  speechVersionUsed_opt:
      IFW_TAP3.SpeechVersionUsed
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.SPEECH_VERSION_USED, 0, bsPacketIdx, "IFW_TAP3.SpeechVersionUsed.SPEECH_VERSION_USED");
      }
    | /* EMPTY */
    ;

  specificationVersionNumber_mandopt:
      IFW_TAP3.SpecificationVersionNumber
   | /* EMPTY */
     {
      edrMissingInput(HEADER.SPECIFICATION_VERSION_NUMBER);
     }
   ;

  speechVersionRequested_opt:
      IFW_TAP3.SpeechVersionRequested
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.SPEECH_VERSION_REQUESTED, 0, bsPacketIdx, "IFW_TAP3.SpeechVersionRequested.SPEECH_VERSION_REQUESTED");
      }
    | /* EMPTY */
    ;

  ssParameters_opt:
      IFW_TAP3.SsParameters
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_PARAMETERS, 0, ssPacketIdx,
			"IFW_TAP3.SsParameters.SS_PARAMETERS");
      }
    | /* EMPTY */
    ;

  supplServiceEvent:
      IFW_TAP3.SupplServiceEvent
      {
        if ( createNewDetail(record_MSS, type_MSS) == false )
        {
          //TODO something
        }
        edrString(DETAIL.BASIC_SERVICE) = "200"; // supplementary Service
      }
      fraudMonitorIndicator_opt
      chargeableSubscriber_mandopt
      rapFileSequenceNumber_opt
      networkType_opt
      locationInformation_mandopt
      equipmentInformation_opt //normally mandatory!, but should only give a warning
      {
        initializeChargeInfoTempFields();
      }
      supplServiceUsedEvent_mandopt
      {
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      simToolkitIndicator_opt
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  supplServiceUsed:
      IFW_TAP3.SupplServiceUsed
      {
        service_Type = service_Suppl;

        // add a corresponding SS_PACKET
        if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.SS_PACKET ) == false )
        {
          String Msg = "failed to add ASS_GSMW_EXT.SS_PACKET datablock";
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        }
        //get an index to the SS_PACKET
        ssPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS , 0);
        edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS , 0) = ssPacketIdx + 1;

        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_TYPE, 0, ssPacketIdx) = extension_SS_EVENT;
        edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_NUMBER, 0, ssPacketIdx) = records;
	related_record = records;
      }
      supplServiceCode_mandopt
      supplServiceActionCode_mandopt
      ssParameters_opt
      thirdPartyInformation_opt
      {
        // if (edrString(DETAIL.C_NUMBER) != defTelNumber)
        // {
        //   edrString(DETAIL.C_NUMBER) = convertCli(edrString(DETAIL.C_NUMBER),
        //                                           edrString(DETAIL.C_MODIFICATION_INDICATOR),
        //                                           edrLong(DETAIL.C_TYPE_OF_NUMBER),
        //                                           NORM_NAC,
        //                                           calledNumberAnalysisIACarray[0], // NORM_IAC,
        //                                           calledNumberAnalysisCCarray[0], // NORM_CC,
        //                                           NORM_IAC_SIGN,
        //                                           NORM_NDC );
        //  }
        edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);
      }
      chargingTimeStamp_opt
      chargeInformation_opt
      basicServiceCodeList_opt
      {
        // and store the last affected BasicService
        if (SsBasicServicesAffectedNb > 0)
        {
          edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE, 0) =
		SsBasicServicesAffected[SsBasicServicesAffectedNb-1]; //TODO find a better storage place
        }
        if (lastbasicServiceCodeSS != "")
	{
	 edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.BASIC_SERVICE_CODE_LIST, 0, ssPacketIdx) =lastbasicServiceCodeSS;
	}
      }
      IFW_TAP3.Block_END
    ;

  supplServiceUsedEvent:
      IFW_TAP3.SupplServiceUsed
      {
        service_Type = service_Suppl;

        // add a corresponding SS_PACKET
        if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.SS_PACKET ) == false )
        {
          String Msg = "failed to add ASS_GSMW_EXT.SS_PACKET datablock";
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        }
        //get an index to the SS_PACKET
        ssPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS , 0);
        edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS , 0) = ssPacketIdx + 1;

        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_TYPE, 0, ssPacketIdx) = extension_SS_EVENT;
        edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_NUMBER, 0, ssPacketIdx) = records;
	related_record = records;
      }
      supplServiceCode_mandopt
      supplServiceActionCode_mandopt
      ssParameters_opt
      thirdPartyInformation_opt
      {
        // if (edrString(DETAIL.C_NUMBER) != defTelNumber)
        // {
        //    edrString(DETAIL.C_NUMBER) = convertCli(edrString(DETAIL.C_NUMBER),
        //                                            edrString(DETAIL.C_MODIFICATION_INDICATOR),
        //                                            edrLong(DETAIL.C_TYPE_OF_NUMBER),
        //                                            NORM_NAC,
        //                                            calledNumberAnalysisIACarray[0], // NORM_IAC,
        //                                            calledNumberAnalysisCCarray[0], // NORM_CC,
        //                                            NORM_IAC_SIGN,
        //                                            NORM_NDC );
        //    edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);
        //  }
        edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);
      }
      chargingTimeStamp_opt
      chargeInformation_opt
      basicServiceCodeList_opt
      {
        // and store the last affected BasicService
        if (SsBasicServicesAffectedNb > 0)
        {
          edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE, 0) =
		SsBasicServicesAffected[SsBasicServicesAffectedNb-1]; //TODO find a better storage place
        }
        if (lastbasicServiceCodeSS != "")
	{
	 edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.BASIC_SERVICE_CODE_LIST, 0, ssPacketIdx) =lastbasicServiceCodeSS;
	}
      }
      IFW_TAP3.Block_END
    ;

  supplServiceCode:
      IFW_TAP3.SupplServiceCode
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT, 0, ssPacketIdx, "IFW_TAP3.SupplServiceCode.SUPPL_SERVICE_CODE");
      }
    ;

  supplServiceUsedEvent_mandopt:
      supplServiceUsedEvent
    | /* EMPTY */
    ;

  supplServiceCode_mandopt:
      supplServiceCode
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT, 0, ssPacketIdx);
      }
    ;

  supplServiceActionCode:
      IFW_TAP3.SupplServiceActionCode
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE, 0, ssPacketIdx, "IFW_TAP3.SupplServiceActionCode.SUPPL_SERVICE_ACTION_CODE");
      }
    ;

  supplServiceActionCode_mandopt:
      supplServiceActionCode
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE, 0, ssPacketIdx);
      }
    ;

  supplServiceUsedList:
      supplServiceUsedList supplServiceUsed
    | supplServiceUsed
    ;

  supplServiceUsedList_opt:
      IFW_TAP3.SupplServiceUsedList
      supplServiceUsedList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  supplServiceUsedList_opt2:
      supplServiceUsedList
    | /* EMPTY */ //accept empty list
    ;

  tapCurrency_opt:
      IFW_TAP3.TapCurrency
      {
        theTapCurrency = tokenString("IFW_TAP3.TapCurrency.TAP_CURRENCY");
      }
    | /* EMPTY */
      {
        theTapCurrency = "SDR"; // default
      }
    ;

  tapDecimalPlaces_mandopt:
      IFW_TAP3.TapDecimalPlaces
      {
        edrConnectToken(HEADER.TAP_DECIMAL_PLACES, "IFW_TAP3.TapDecimalPlaces.TAP_DECIMAL_PLACES");
        theTapDecimalPlaces      = tokenLong("IFW_TAP3.TapDecimalPlaces.TAP_DECIMAL_PLACES");
        theAbsoluteAmountDivider = 1.0;
        Long i;
        for (i=0 ; i < theTapDecimalPlaces ; i=i+1)
        {
          theAbsoluteAmountDivider = theAbsoluteAmountDivider * 10.0;
        }
//      theAbsoluteAmountDivider = 1.0;  //TODO Remove (CEDRIC for tests, to get SDR count)
      }
    | /* EMPTY */
      {
        edrMissingInput(HEADER.TAP_DECIMAL_PLACES);
      }
    ;

  taxChargeType_opt:
      IFW_TAP3.ChargeType
    | /* EMPTY */
    ;

  taxCode_mandopt:
      IFW_TAP3.TaxCode
    | /* EMPTY */
      {
	taxCodeIsMissing = true;
      }
    ;

   taxValue_mandopt:
      IFW_TAP3.TaxValue
    | /* EMPTY */
      {
	taxValueIsMissing = true;
      }
    ;

  taxInformation:
      IFW_TAP3.TaxInformation
      {
          successiveTaxDetail = successiveTaxDetail +1;
	  if (taxationListIsMissing == true)
	  {
            // Set Fatal Error
            requestBatchReject(5, -1, 2,  0,  30, "ERR_TAP3_MISSING_TAXATION_LIST");
	    taxationListIsMissing = false;
          }
          if ( edrAddDatablock( DETAIL.ASS_CBD.TP ) == false )
          {
            String Msg ="failed to add TAX_PACKET datablock " + longToStr(successiveTaxDetail) +
                        " for ASS_CBD " + longToStr(successiveTaxDetail) +
                        " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
            edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

          }
          TPidx = successiveTaxPacket;
	  successiveTaxPacket   = successiveTaxPacket   +1;
	  records = records+1;
	  edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)          = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
	  edrString(DETAIL.ASS_CBD.TP.RECORD_TYPE, ACBidx, TPidx) = extension_TP;
	  edrLong(DETAIL.ASS_CBD.TP.RECORD_NUMBER, ACBidx, TPidx) = records;
	  edrLong(DETAIL.ASS_CBD.TP.RELATED_RECORD_NUMBER, ACBidx, TPidx) = related_record;
	  edrLong(DETAIL.ASS_CBD.TP.RELATED_CHARGE_INFO_ID, ACBidx, TPidx) = related_info_id;
      }

      taxCode_mandopt
      {
        // we only store the last rate of the list (ie overwrite the previous rate)
        // TaxRate comes in TAP3 with 5 decimal places, and in ifw we store only 2
        // edrConnectToken(DETAIL.WHOLESALE_CHARGED_TAX_RATE, "IFW_TAP3.TaxCode.TAX_CODE");
        edrConnectToken(DETAIL.ASS_CBD.TP.TAX_CODE, ACBidx, TPidx,  "IFW_TAP3.TaxCode.TAX_CODE");
	if (taxCodeIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_CBD.TP.TAX_CODE, ACBidx, TPidx);
	  taxCodeIsMissing = false;
        }
	else
	{
          String taxRateStr    = getTaxRate( tokenLong("IFW_TAP3.TaxCode.TAX_CODE") );
          String taxTypeStr    = getTaxType( tokenLong("IFW_TAP3.TaxCode.TAX_CODE") );
	  edrString(DETAIL.ASS_CBD.TP.TAX_RATE, ACBidx, TPidx) = taxRateStr;
	  edrString(DETAIL.ASS_CBD.TP.TAX_TYPE, ACBidx, TPidx) = taxTypeStr;

          Long   taxRateStrlen = strLength( taxRateStr );
          if ( taxRateStrlen > 3 )
          {
            lastTaxRate  = strToLong( strSubstr( taxRateStr, 0, (taxRateStrlen - 3) ) );
          }
        }
      }
      taxValue_mandopt
      {
        edrConnectToken(DETAIL.WHOLESALE_CHARGED_TAX_VALUE, "IFW_TAP3.TaxValue.TAX_VALUE");
        edrConnectToken(DETAIL.ASS_CBD.TP.TAX_VALUE, ACBidx, TPidx,  "IFW_TAP3.TaxValue.TAX_VALUE");
	if (taxValueIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_CBD.TP.TAX_VALUE, ACBidx, TPidx);
	  taxValueIsMissing = false;
        }
	else
	{
          lastTaxCharge   = (longToDecimal(tokenLong("IFW_TAP3.TaxValue.TAX_VALUE")) / theAbsoluteAmountDivider) * lastExchangeRateFactor;
          sumTaxChargeCI  = sumTaxChargeCI   + lastTaxCharge;
	}
      }
      taxChargeType_opt
      {
        edrConnectToken(DETAIL.ASS_CBD.TP.CHARGE_TYPE, ACBidx, TPidx,  "IFW_TAP3.ChargeType.CHARGE_TYPE");
      }
      taxableAmount_opt
      {
        edrConnectToken(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, ACBidx, TPidx,  "IFW_TAP3.TaxableAmount.TAXABLE_AMOUNT");
	Decimal taxAmount = (longToDecimal(tokenLong("IFW_TAP3.TaxValue.TAX_VALUE")) / theAbsoluteAmountDivider) *
			lastExchangeRateFactor;

	if (taxableAmountIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, ACBidx, TPidx);
	  taxableAmountIsMissing = false;
        }

        sumTaxAmountCI = sumTaxAmountCI + taxAmount;
      }
      IFW_TAP3.Block_END
    ;

  taxInformationList:
      taxInformationList taxInformation
    | taxInformation
    ;

  taxInformationList_opt:
      IFW_TAP3.TaxInformationList
      {
        lastTaxCharge  = 0.0;
      }
      taxInformationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastTaxCharge  = 0.0;
      }
    ;

  taxInformationList_opt2:
      taxInformationList
    | /* EMPTY */ //accept empty list
    ;

  taxRate_opt:
      IFW_TAP3.TaxRate
      {
        taxRate[lastCode] = tokenString("IFW_TAP3.TaxRate.TAX_RATE");
      }
    | /* EMPTY */
    ;

  taxType_mandopt:
      IFW_TAP3.TaxType
    | /* EMPTY */
      {
	taxTypeIsMissing = true;
      }
    ;

  taxableAmount_opt:
      IFW_TAP3.TaxableAmount
    | /* EMPTY */
      {
	taxableAmountIsMissing = true;
      }
    ;

  taxation:
      IFW_TAP3.Taxation
      taxCode_mandopt
      {
        lastCode          = tokenLong("IFW_TAP3.TaxCode.TAX_CODE");
	if (taxCodeIsMissing == true)
	{
          // Set Fatal Error
          requestBatchReject(216, -1, 3,  0,  30, "ERR_TAP3_MISSING_TAX_CODE_FATAL_RETURN");
	  taxCodeIsMissing = false;
        }
	else
	{
          taxCode[lastCode] = lastCode;
          taxType[lastCode] = ""; // initialisation
	}
      }
      taxType_mandopt
      {
	if (taxTypeIsMissing == true)
	{
          // Set Fatal Error
          requestBatchReject(216, -1, 3,  0,  31, "ERR_TAP3_MISSING_TAX_TYPE");
	  taxTypeIsMissing = false;
        }
	else
	{
          taxType[lastCode] = tokenString("IFW_TAP3.TaxType.TAX_TYPE");
          taxRate[lastCode] = ""; // initialisation
	}
      }
      taxRate_opt
      {
        if (taxEntries <= lastCode)
        {
          taxEntries      = lastCode + 1;
        }
      }
      IFW_TAP3.Block_END
    ;

  taxationList_opt2:
    taxationList
    | /* EMPTY */
    {
    taxationListIsMissing = true;
    }
    ;

  taxationList:
      taxationList
      taxation
    | taxation
    ;

  taxationList_opt:
      IFW_TAP3.TaxationList
      taxationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    {
    taxationListIsMissing = true;
    }
    ;

  thirdPartyInformation:
      IFW_TAP3.ThirdPartyInformation
      {
        callNumberType = thirdPartyType;
      }
      thirdPartyNumber_opt
      clirIndicator_opt
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.CLIR_INDICATOR, 0, ssPacketIdx,
			"IFW_TAP3.ClirIndicator.CLIR_INDICATOR");
      }
      IFW_TAP3.Block_END
    ;

  thirdPartyInformation_opt:
      thirdPartyInformation
    | /* EMPTY */
    ;

  thirdPartyNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        edrConnectToken(DETAIL.C_NUMBER, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.THIRD_PARTY_NUMBER, 0, ssPacketIdx,
			"IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");

        edrString(DETAIL.C_NUMBER) = strIAC +
			tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");

        edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.THIRD_PARTY_NUMBER, 0, ssPacketIdx) = strIAC +
			tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");

      }
    | /* EMPTY */
    ;

  timeBand_mandopt:
      IFW_TAP3.TimeBand
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, ACBidx, CPidx, "IFW_TAP3.TimeBand.TIME_BAND");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, ACBidx, CPidx);
      }
    ;

  timeBandSubtype_opt:
      IFW_TAP3.TimeBandSubtype
    | /* EMPTY */
    ;
  totalChargeRefund_opt:
      IFW_TAP3.TotalChargeRefund
      {
	edrConnectToken(TRAILER.TOTAL_CHARGE_VALUE_LIST.TOTAL_CHARGE_REFUND, tcvidx,
			"IFW_TAP3.TotalChargeRefund.TOTAL_CHARGE_REFUND");
      }
    | /* EMPTY*/
    ;

  totalChargeType_mandopt:
      IFW_TAP3.ChargeType
      {
	edrConnectToken(TRAILER.TOTAL_CHARGE_VALUE_LIST.CHARGE_TYPE, tcvidx,
			"IFW_TAP3.ChargeType.CHARGE_TYPE");
        lastTotalChargeValueChargeType     = tokenString("IFW_TAP3.ChargeType.CHARGE_TYPE");

        // Check for Charge Type.
        // If it is "00" set chargeType00IsMissing to false.
        if (lastTotalChargeValueChargeType == "00")
        {
          chargeType00IsMissing = false;
        }
      }
    | /* EMPTY */
      {
	totalChargeTypeIsMissing = true;
      }
    ;

  totalChargeValue:
      IFW_TAP3.TotalChargeValue
      {
        if (edrAddDatablock(TRAILER.TOTAL_CHARGE_VALUE_LIST) == false)
        {
          String Msg = "failed to add TOTAL_CHARGE_VALUE datablock";
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++
        }
      }
      totalChargeType_mandopt
      {
	if (totalChargeTypeIsMissing == true)
	{
	  edrMissingInput(TRAILER.TOTAL_CHARGE_VALUE_LIST.CHARGE_TYPE, tcvidx);
	  totalChargeTypeIsMissing = false;
        }
      }
      absoluteAmount_mandopt
      {
	if (absoluteAmountIsMissing == true)
	{
	  edrMissingInput(TRAILER.TOTAL_CHARGE_VALUE_LIST.TOTAL_CHARGE_VALUE, tcvidx);
	  absoluteAmountIsMissing = false;
        }
      }
      totalChargeRefund_opt
      {
        tcvidx = tcvidx + 1;
      }
      IFW_TAP3.Block_END
    ;

  totalChargeValueList:
      totalChargeValueList
      totalChargeValue
      {
        if (lastTotalChargeValueChargeType == "00")
        {
          // if there is a record for aggregated charge, use it and forget the rest
          theTotalChargedValue_00 = tokenDecimal("IFW_TAP3.AbsoluteAmount.ABSOLUTE_AMOUNT");
        }
        else
        {
          theTotalChargedValue    = theTotalChargedValue + lastTotalChargeValueAbsoluteAmount;
        }
      }
    | totalChargeValue
      {
        theTotalChargedValue = 0.0;
        if (lastTotalChargeValueChargeType == "00")
        {
          // if there is a record for aggregated charge, use it and forget the rest
          theTotalChargedValue_00 = lastTotalChargeValueAbsoluteAmount;
        }
        else
        {
          theTotalChargedValue    = theTotalChargedValue + lastTotalChargeValueAbsoluteAmount;
        }
      }
    ;

  totalChargeValueList_mandopt:
      IFW_TAP3.TotalChargeValueList
      totalChargeValueList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  totalChargeValueList_opt2:
      totalChargeValueList
    | /* EMPTY */
    ;

  totalCallEventDuration:
      IFW_TAP3.TotalCallEventDuration
      {
       edrConnectToken(DETAIL.TOTAL_CALL_EVENT_DURATION, "IFW_TAP3.TotalCallEventDuration.TOTAL_CALL_EVENT_DURATION");
      }
    ;

  totalCallEventDuration_mandopt:
      totalCallEventDuration
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.TOTAL_CALL_EVENT_DURATION);
      }
    ;

  totalDiscountValue_mandopt:
      IFW_TAP3.TotalDiscountValue
      {
        theTotalDiscountValue = tokenDecimal("IFW_TAP3.TotalDiscountValue.TOTAL_DISCOUNT_VALUE");
      }
    | /* EMPTY */
      {
        edrMissingInput(TRAILER.TAP_TOTAL_DISCOUNT_VALUE);
      }
    ;

  totalTaxValue_mandopt:
      IFW_TAP3.TotalTaxValue
      {
        theTotalTaxValue = tokenDecimal("IFW_TAP3.TotalTaxValue.TOTAL_TAX_VALUE");
      }
    | /* EMPTY */
      {
        edrMissingInput(TRAILER.TAP_TOTAL_TAX_VALUE);
      }
    ;

  transferCutOffTimeStamp:
      IFW_TAP3.TransferCutOffTimeStamp
      {
        timeStampType = transferCutOffTimeStampType;
      }
      dateTimeLong
      IFW_TAP3.Block_END
      {
        theTransferCutOffTimeStamp     = lastLocalTimeStamp;
        theTransferCutOffUtcTimeOffset = lastUtcTimeOffset;
      }
    ;

  transferCutOffTimeStamp_mandopt:
      transferCutOffTimeStamp
      {
        edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP) = strToDate(theTransferCutOffTimeStamp);
      }
    | /* EMPTY */
      {
	edrMissingInput(HEADER.TRANSFER_CUTOFF_TIMESTAMP);
      }
    ;

  transparencyIndicator_opt:
      IFW_TAP3.TransparencyIndicator
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, bsPacketIdx, "IFW_TAP3.TransparencyIndicator.TRANSPARENCY_INDICATOR");
      }
    | /* EMPTY */
    ;

  typeOfControllingNode_mandopt:
      IFW_TAP3.TypeOfControllingNode
      {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.TYPE_OF_CONTROLLING_NODE,0,"IFW_TAP3.TypeOfControllingNode.TYPE_OF_CONTROLLING_NODE");
      }
    | /* EMPTY */
      {
        // Set sever error code
        String offset = longToStr( edrFieldTokenBytePos(DETAIL.RECORD_TYPE));
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "14", "3", offset, "-1", "TAP3.ASS_GPRS_EXT.RECORD_TYPE");
        setAssociatedTapErr("ERR_TAP3_ASS_GPRS_EXT_RECORD_TYPE",3 ,"30" ,"14" ,"3");	

        edrMissingInput(DETAIL.ASS_GPRS_EXT.TYPE_OF_CONTROLLING_NODE,0);
      }
    ;

  userProtocolIndicator_opt:
      IFW_TAP3.UserProtocolIndicator
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.BS_PACKET.USER_PROTOCOL_INDICATOR, 0, bsPacketIdx, "IFW_TAP3.UserProtocolIndicator.USER_PROTOCOL_INDICATOR");
      }
    | /* EMPTY */
    ;

  utcTimeOffset_mandopt:
      IFW_TAP3.UtcTimeOffset
    | /* EMPTY */
      {
	utcTimeOffsetIsMissing = true;
      }
    ;

  utcTimeOffsetCode_mandopt:
      IFW_TAP3.UtcTimeOffsetCode
    | /* EMPTY */
      {
	utcTimeOffsetCodeIsMissing = true;
      }
    ;

  utcTimeOffsetInfo:
      IFW_TAP3.UtcTimeOffsetInfo
      utcTimeOffsetCode_mandopt
      {
        Long utcoffcode               = tokenLong("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
	if ( utcTimeOffsetCodeIsMissing == true)
	{
	  // Set fatal error
          requestBatchReject(233, -1, 3,  0,  30, "ERR_TAP3_MISSING_UTC_TIME_OFFSET_CODE");
	  utcTimeOffsetCodeIsMissing  = false;
        }
	else
	{
          lastCode                    = utcoffcode;
          utcTimeOffsetCode[lastCode] = lastCode;
	}
      }
      utcTimeOffset_mandopt
      {
	String utcoffset              = tokenString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET");
	if ( utcTimeOffsetIsMissing == true)
	{
	  // Set fatal error
          requestBatchReject(233, -1, 3,  0,  31, "ERR_TAP3_MISSING_UTC_TIME_OFFSET");
	  utcTimeOffsetIsMissing = false;
        }
	else
	{
          utcTimeOffset[lastCode]     = utcoffset;
          if (utcTimeOffsetEntries <= lastCode)
          {
            utcTimeOffsetEntries      = lastCode + 1;
          }
        }
      }
      IFW_TAP3.Block_END
    ;

  utcTimeOffsetInfoList:
      IFW_TAP3.UtcTimeOffsetInfoList
      utcTimeOffsetInfoList2
      IFW_TAP3.Block_END
    ;

  utcTimeOffsetInfoList2:
      utcTimeOffsetInfoList2
      utcTimeOffsetInfo
    | utcTimeOffsetInfo
    ;

  utcTimeOffsetInfoList_mandopt:
      utcTimeOffsetInfoList
    | /* EMPTY */
      {
       // Set Fatal Error
       requestBatchReject(6, -1, 2,  0,  30, "ERR_TAP3_MISSING_UTC_TIME_OFFSET_INFO_LIST");
      }
    ;

  valueAddedService:
      IFW_TAP3.ValueAddedService
      {
        if ( createNewDetail(record_VAS, type_VAS) == false )
        {
          //TODO something
        }
        edrString(DETAIL.BASIC_SERVICE) = "E00";  // vas
      }
      fraudMonitorIndicator_opt
      scuVasChargeableSubscriber_mandopt
      rapFileSequenceNumber_opt
      networkType_opt
      servingNetwork_opt
      {
        initializeChargeInfoTempFields();
      }
      valueAddedServiceUsed_mandopt
      {
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();

        // add the VAS short description to the record
        edrString(DETAIL.ASS_GSMW_EXT.VAS_PRODUCT_CODE, 0) = getVasShortDesc( lastVasCode );
      }
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  valueAddedServiceUsed:
      IFW_TAP3.ValueAddedServiceUsed
      {
        service_Type = service_Vas;
        if ( edrAddDatablock( DETAIL.ASS_VAS_EXT ) == false )
        {
          String Msg = "failed to add ASS_VAS_EXT datablock for EDR "+longToStr(records);
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg); //TODO check for consequences
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++

        }
        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)          = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_VAS_EXT.RECORD_TYPE, vasidx)  = extension_VAS;
        edrLong(DETAIL.ASS_VAS_EXT.RECORD_NUMBER, vasidx)  = records;
	related_record = records;
      }
      vasCode_mandopt
      {
//        service_Type            = service_Vas;
        lastVasCode             = tokenLong("IFW_TAP3.VasCode.VAS_CODE");
        if (record_Type == record_VAS)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.VAS_PRODUCT_CODE, 0, "IFW_TAP3.VasCode.VAS_CODE");
        }
	edrConnectToken(DETAIL.ASS_VAS_EXT.VAS_CODE, vasidx, "IFW_TAP3.VasCode.VAS_CODE");
	if (vasCodeIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_VAS_EXT.VAS_CODE, vasidx);
	  // vasCodeIsMissing = false;
	}
	else
	{
          edrString(DETAIL.ASS_VAS_EXT.VAS_SHORT_DESC, vasidx) = getVasShortDesc( lastVasCode );
          edrString(DETAIL.ASS_VAS_EXT.VAS_DESC, vasidx)       = getVasDesc( lastVasCode );
	}
      }
      chargingTimeStamp_opt
      {
        lastVasLocalTimeStamp   = lastValidLocalTimeStamp;//TODO check validity
        lastVasUtcTimeOffset    = lastValidUtcTimeOffset; //TODO check validity
      }
      chargeInformation_opt
      {
       vasidx = vasidx + 1;
      }
      IFW_TAP3.Block_END
    ;

  valueAddedServiceUsed_mandopt:
      valueAddedServiceUsed
    | /* EMPTY */
      {
        // Error Setting will be done within I rules
      }
    ;

  valueAddedServiceUsedList:
      valueAddedServiceUsedList
      valueAddedServiceUsed
      {
	if (vasCodeIsMissing == false)
        {
          lastVasShortDescrList = lastVasShortDescrList + ", " + getVasShortDesc( lastVasCode );
	}
      }
    | valueAddedServiceUsed // first element of the list
      {
	if (vasCodeIsMissing == false)
        {
          lastVasShortDescrList = getVasShortDesc( lastVasCode );
	}
      }
    ;

  valueAddedServiceUsedList_opt:
      IFW_TAP3.ValueAddedServiceUsedList
      {
        lastVasShortDescrList = "";
      }
      valueAddedServiceUsedList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastVasShortDescrList = "";
      }
    ;

  valueAddedServiceUsedList_opt2:
      valueAddedServiceUsedList
      {
        vasCodeIsMissing = false;
      }
    | /* EMPTY */ //accept empty list
    ;

  vasCode_mandopt:
      IFW_TAP3.VasCode
    | /* EMPTY */
      {
	vasCodeIsMissing = true;
      }
    ;

  vasInformation:
      IFW_TAP3.VasInformation
      vasCode_mandopt
      {
        lastCode               = tokenLong("IFW_TAP3.VasCode.VAS_CODE");
	if (vasCodeIsMissing == true)
	{
          // Set fatal error
          requestBatchReject(238, -1, 2,  0,  30, "ERR_TAP3_MISSING_VAS_CODE");
	  vasCodeIsMissing = false;
        }
	else
	{
          vasCode[lastCode]    = lastCode;
	}
      }
      vasShortDescription_mandopt
      {
        vasShortDesc[lastCode] = tokenString("IFW_TAP3.VasShortDescription.VAS_SHORT_DESCRIPTION");
	if (vasShortDescriptionIsMissing == true)
	{
          // Set fatal error
          requestBatchReject(238, -1, 2,  0,  31, "ERR_TAP3_MISSING_VAS_SHORT_DESCRIPTION");
	  vasShortDescriptionIsMissing = false;
        }
      }
      vasDescription_mandopt
      IFW_TAP3.Block_END
    ;

  vasDescription_mandopt:
      IFW_TAP3.VasDescription
      {
        vasDesc[lastCode] = tokenString("IFW_TAP3.VasDescription.VAS_DESCRIPTION");
        if (vasEntries <= lastCode)
        {
          vasEntries = lastCode + 1;
        }
      }
    | /* EMTPY */
      {
        // Set a warning message
	String offset = "-1";
        edrAddError("ERR_TAP3_RET", 1, "warning", "32", "238", "2", offset, "-1", "Missing vas description");
        setAssociatedTapErr("ERR_TAP3_VAS_DESC",1 ,"32" ,"238" ,"2");	
      }
    ;

  vasInfoList_opt:
      IFW_TAP3.VasInfoList
      {
        errorStateTap3 = beginTap3VasInfo;
      }
      vasInfoList
      {
        errorStateTap3 = endTap3VasInfo;
      }
      IFW_TAP3.Block_END
    | /* EMTPY */
    ;

  vasInfoList:
      vasInfoList
      vasInformation
    | vasInformation
    ;


  vasShortDescription_mandopt:
      IFW_TAP3.VasShortDescription
    | /* EMPTY */
      {
	vasShortDescriptionIsMissing = true;
      }
    ;

  advisedChargeCurrency_opt:
      IFW_TAP3.AdvisedChargeCurrency
      {
        if (blockType == advisedChargeInfoBlockType)
        {
          edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE_CURRENCY, 0,
                          contentSvcUsedIdx, "IFW_TAP3.AdvisedChargeCurrency.ADVISED_CHARGE_CURRENCY");
        }
      }
    | /* EMPTY */
    ;

  totalAdvisedCharge_mandopt:
      IFW_TAP3.TotalAdvisedCharge
    | /* EMPTY */
      {
        // Set fatal error
        requestBatchReject(360, -1, 3,  0,  30, "ERR_TAP3_MISSING_TOTAL_ADVISED_CHARGE");
      }
    ;

  totalAdvisedChargeRefund_opt:
      IFW_TAP3.TotalAdvisedChargeRefund
    | /* EMPTY */
    ;

  totalCommission_opt:
      IFW_TAP3.TotalCommission
    | /* EMPTY */
    ;

  totalCommissionRefund_opt:
      IFW_TAP3.TotalCommissionRefund
    | /* EMPTY */
    ;

  totalAdvisedChargeValue:
      IFW_TAP3.TotalAdvisedChargeValue
      advisedChargeCurrency_opt
      totalAdvisedCharge_mandopt
      totalAdvisedChargeRefund_opt
      totalCommission_opt
      totalCommissionRefund_opt
      IFW_TAP3.Block_END
    ;

  totalAdvisedChargeValueList_opt:
      IFW_TAP3.TotalAdvisedChargeValueList
      totalAdvisedChargeValueList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  totalAdvisedChargeValueList_opt2:
      totalAdvisedChargeValueList
    | /* EMPTY */ //accept empty list
    ;

  totalAdvisedChargeValueList:
      totalAdvisedChargeValueList
      totalAdvisedChargeValue
    | totalAdvisedChargeValue
    ;

  totalDiscountRefund_opt:
      IFW_TAP3.TotalDiscountRefund
    | /* EMPTY */
    ;

//----------------------------------------------------------------------------
// Fields added for the ContentTransaction record
//
// This will attempt to hook up every single field that we know about into the
// appropriate field in the EDR container using edrConnect.  If the field was
// not supplied, NULL will end up in the EDR field, which is correct behavior.
//----------------------------------------------------------------------------

  contentTransaction:
      IFW_TAP3.ContentTransaction
      {
        if ( createNewDetail(record_CONT, type_CONT) == false )
        {
          //TODO something
        }
        record_Type  = record_CONT;
        service_Type = service_Content;
      }
      contentTransactionBasicInfo_mandopt
      chargedPartyInformation_mandopt
      servingPartiesInformation_mandopt
      {
	contentSvcUsedIdx = -1;
      }
      contentServiceUsedList_mandopt
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  contentTransactionBasicInfo_mandopt:
      IFW_TAP3.ContentTransactionBasicInfo
      fraudMonitorIndicator_opt
      rapFileSequenceNumber_opt
      orderPlacedTimeStamp_opt
      requestedDeliveryTimeStamp_opt
      actualDeliveryTimeStamp_opt
      totalTransactionDuration_opt
      transactionStatus_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        // Set sever error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_CONT_EXT));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "17", "3", offset, "-1", "Missing Content Basic Info");
        setAssociatedTapErr("ERR_TAP3_MISSING_CONTENT_BASIC_INFO",3 ,"30" ,"17" ,"3");	
      }
    ;

  orderPlacedTimeStamp_opt:
      IFW_TAP3.OrderPlacedTimeStamp
      IFW_TAP3.LocalTimeStamp
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.ORDER_PLACED_TIMESTAMP, 0,
                        "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      IFW_TAP3.UtcTimeOffsetCode
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.ORDER_PLACED_UTC_TIME_OFFSET, 0,
                        "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
      }
      IFW_TAP3.Block_END  // end of DateTime block
    | /* EMPTY */
    ;

  requestedDeliveryTimeStamp_opt:
      IFW_TAP3.RequestedDeliveryTimeStamp
      IFW_TAP3.DateTime
      IFW_TAP3.LocalTimeStamp
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.REQUESTED_DELIVERY_TIMESTAMP, 0,
                        "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      IFW_TAP3.UtcTimeOffsetCode
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.REQ_DELIVERY_UTC_TIME_OFFSET, 0,
                        "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
      }
      IFW_TAP3.Block_END  // end of DateTime block
    | /* EMPTY */
    ;

  actualDeliveryTimeStamp_opt:
      IFW_TAP3.ActualDeliveryTimeStamp
      IFW_TAP3.DateTime
      IFW_TAP3.LocalTimeStamp
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.ACTUAL_DELIVERY_TIMESTAMP, 0,
                        "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      IFW_TAP3.UtcTimeOffsetCode
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.ACT_DELIVERY_UTC_TIME_OFFSET, 0,
                        "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
      }
      IFW_TAP3.Block_END  // end of DateTime block
    | /* EMPTY */
    ;

  totalTransactionDuration_opt:
      IFW_TAP3.TotalCallEventDuration
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.TOTAL_TRANSACTION_DURATION, 0,
                        "IFW_TAP3.TotalCallEventDuration.TOTAL_CALL_EVENT_DURATION");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.TOTAL_TRANSACTION_DURATION, 0);
      }
    ;

  transactionStatus_opt:
      IFW_TAP3.TransactionStatus
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.TRANSACTION_STATUS, 0,
                        "IFW_TAP3.TransactionStatus.TRANSACTION_STATUS");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.TRANSACTION_STATUS, 0);
      }
    ;

  chargedPartyHomeIdentification:
      IFW_TAP3.ChargedPartyHomeIdentification
      {
        chargedPartyHomeIdx = chargedPartyHomeIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST ) == false )
        {
          String Msg ="Failed to add ChargedPartyHomeIdentification datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      homeIdType_mandopt
      {
        if (homeIdTypeIsMissing == true)
        {
	  edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.TYPE, 0, 0,
				    chargedPartyHomeIdx);
          homeIdTypeIsMissing = false;
        }
      }
      homeIdentifier_mandopt
      {
        if (homeIdentifierIsMissing == true)
        {
	 edrMissingInput(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.IDENTIFIER, 0, 0,
			    chargedPartyHomeIdx);
	 homeIdentifierIsMissing = false;
        }
      }
      IFW_TAP3.Block_END
    ;

  chargedPartyHomeIdList:
      chargedPartyHomeIdList
      chargedPartyHomeIdentification
    | chargedPartyHomeIdentification
    ;

  chargedPartyHomeIdList_opt:
      IFW_TAP3.ChargedPartyHomeIdList
      {
        blockType = chargedPartyHomeBlockType;
        chargedPartyHomeIdx = -1; // initialize index counter
      }
      chargedPartyHomeIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY*/
    ;

  chargedPartyHomeIdList_opt2:
      chargedPartyHomeIdList
    | /* EMPTY */ //accept empty list
    ;

  chargedPartyIdList:
      chargedPartyIdList
      chargedPartyIdentification
    | chargedPartyIdentification
    ;

  chargedPartyIdList_mandopt:
      IFW_TAP3.ChargedPartyIdList
      {
        chargedPartyIdIdx = -1; // initialize index counter
      }
      chargedPartyIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  chargedPartyIdList_opt2:
      chargedPartyIdList
    | /* EMPTY */
    ;

  chargedPartyIdentification:
      IFW_TAP3.ChargedPartyIdentification
      {
        chargedPartyIdIdx = chargedPartyIdIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST ) == false )
        {
          String Msg ="Failed to add ChargedPartyIdentification datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      chargedPartyIdType_mandopt
      chargedPartyIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  chargedPartyInformation_mandopt:
      IFW_TAP3.ChargedPartyInformation
      {
        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO ) == false )
        {
          String Msg ="Failed to add ChargedPartyInformation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      chargedPartyIdList_mandopt
      chargedPartyHomeIdList_opt
      chargedPartyLocationList_opt
      chargedPartyEquipment_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  chargedPartyLocation:
      IFW_TAP3.ChargedPartyLocation
      {
        chargedPartyLocnIdx = chargedPartyLocnIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST ) == false )
        {
          String Msg ="Failed to add ChargedPartyLocation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      locationIdType_mandopt
      locationIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  chargedPartyLocationList:
      chargedPartyLocationList
      chargedPartyLocation
    | chargedPartyLocation
    ;

  chargedPartyLocationList_opt:
      IFW_TAP3.ChargedPartyLocationList
      {
        blockType = chargedPartyLocnBlockType;
        chargedPartyLocnIdx = -1; // initialize index counter
      }
      chargedPartyLocationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY*/
    ;

  chargedPartyLocationList_opt2:
      chargedPartyLocationList
    | /* EMPTY */ //accept empty list
    ;

  chargedPartyEquipment_opt:
      IFW_TAP3.ChargedPartyEquipment
      {
	blockType = chargedPartyEquipmentBlockType;

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT ) == false )
        {
          String Msg ="Failed to add ChargedPartyEquipment datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      equipmentIdType_mandopt
      equipmentId_mandopt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  servingPartiesInformation_mandopt:
      IFW_TAP3.ServingPartiesInformation
      {
	blockType = servingPartiesInfoBlockType;

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO ) == false )
        {
          String Msg ="Failed to add ServingPartiesInformation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      contentProviderName_mandopt
      contentProviderIdList_opt
      internetServiceProviderIdList_opt
      networkList_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  contentProvider:
      IFW_TAP3.ContentProvider
      {
        contentProviderIdx = contentProviderIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST ) == false )
        {
          String Msg ="Failed to add ContentProvider datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      contentProviderIdType_mandopt
      contentProviderIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  contentProviderIdentifier_mandopt:
      IFW_TAP3.ContentProviderIdentifier
      {
	if (blockType == lCSSPIdBlockType)
	{
	  edrConnectToken(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.IDENTIFIER, 0, 0,  lcsspIdx,
                          "IFW_TAP3.ContentProviderIdentifier.CONTENT_PROVIDER_IDENTIFIER");
	}
	else if (blockType == contentProviderBlockType)
	{
          edrConnectToken(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.IDENTIFIER,
                          0, 0, contentProviderIdx,
                          "IFW_TAP3.ContentProviderIdentifier.CONTENT_PROVIDER_IDENTIFIER");
	}
      }
    | /* EMPTY */
      {
	if (blockType == lCSSPIdBlockType)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.IDENTIFIER, 0, 0,  lcsspIdx);
	}
	else if (blockType == contentProviderBlockType)
	{
          edrMissingInput(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.IDENTIFIER,
                          0, 0, contentProviderIdx);
	}
      }

    ;

  contentProviderIdList:
      contentProviderIdList
      contentProvider
    | contentProvider
    ;

  contentProviderIdList_opt:
      IFW_TAP3.ContentProviderIdList
      {
        blockType = contentProviderBlockType;
        contentProviderIdx = -1; // initialize index counter
      }
      contentProviderIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  contentProviderIdList_opt2:
      contentProviderIdList
    | /* EMPTY */ //accept empty list
    ;

  contentProviderIdType_mandopt:
      IFW_TAP3.ContentProviderIdType
      {
	if (blockType == lCSSPIdBlockType)
	{
          edrConnectToken(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.TYPE, 0, 0,  lcsspIdx,
                          "IFW_TAP3.ContentProviderIdType.CONTENT_PROVIDER_ID_TYPE");
	}
	else if (blockType == contentProviderBlockType)
	{
          edrConnectToken(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.TYPE,
                          0, 0, contentProviderIdx,
                          "IFW_TAP3.ContentProviderIdType.CONTENT_PROVIDER_ID_TYPE");
	}
      }
    | /* EMPTY */
      {
	if (blockType == lCSSPIdBlockType)
	{
          edrMissingInput(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.TYPE, 0, 0,  lcsspIdx);
	}
	else if (blockType == contentProviderBlockType)
	{
          edrMissingInput(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.TYPE,
                          0, 0, contentProviderIdx);
	}
      }

    ;

  contentProviderName_mandopt:
      IFW_TAP3.ContentProviderName
      {
	edrConnectToken(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_NAME, 0, 0,
			"IFW_TAP3.ContentProviderName.CONTENT_PROVIDER_NAME");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_NAME, 0, 0);
      }
    ;

  internetServiceProvider:
      IFW_TAP3.InternetServiceProvider
      {
        internetSvcProvIdx = internetSvcProvIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST ) == false )
        {
          String Msg ="Failed to add InternetServiceProviderId datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      IspIdType_mandopt
      IspIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  IspIdType_mandopt:
      IFW_TAP3.IspIdType
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.TYPE, 0, 0,
                        internetSvcProvIdx, "IFW_TAP3.IspIdType.ISP_ID_TYPE");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.TYPE, 0, 0,
			internetSvcProvIdx);
      }
    ;

  IspIdentifier_mandopt:
      IFW_TAP3.IspIdentifier
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.IDENTIFIER, 0, 0,
                        internetSvcProvIdx, "IFW_TAP3.IspIdentifier.ISP_IDENTIFIER");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.IDENTIFIER, 0, 0,
			internetSvcProvIdx);
      }
    ;

  internetServiceProviderIdList:
      internetServiceProviderIdList
      internetServiceProvider
    | internetServiceProvider
    ;

  internetServiceProviderIdList_opt:
      IFW_TAP3.InternetServiceProviderIdList
      {
        internetSvcProvIdx = -1; // initialize index counter
      }
      internetServiceProviderIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  internetServiceProviderIdList_opt2:
      internetServiceProviderIdList
    | /* EMPTY */ //accept empty list
    ;

  network:
      IFW_TAP3.Network
      {
        networkIdx = networkIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST ) == false )
        {
          String Msg ="Failed to add Network datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      networkIdType_mandopt
      networkIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  networkIdType_mandopt:
      IFW_TAP3.NetworkIdType
      {
	if (blockType == servingPartiesInfoBlockType)
	{
          edrConnectToken(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.TYPE, 0, 0,
                          networkIdx, "IFW_TAP3.NetworkIdType.NETWORK_ID_TYPE");
	}
	else if (blockType == lCSSPInfoBlockType)
	{
          edrConnectToken(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.NETWORK_LIST.TYPE, 0, 0,
                          networkIdx, "IFW_TAP3.NetworkIdType.NETWORK_ID_TYPE");
	}
      }
    | /* EMPTY */
      {
	if (blockType == servingPartiesInfoBlockType)
	{
          edrMissingInput(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.TYPE, 0, 0,
                          networkIdx);
	}
	else if (blockType == lCSSPInfoBlockType)
	{
          edrMissingInput(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.NETWORK_LIST.TYPE, 0, 0,
                          networkIdx);
	}

      }
    ;

  networkIdentifier_mandopt:
      IFW_TAP3.NetworkIdentifier
      {
	if (blockType == servingPartiesInfoBlockType)
	{
          edrConnectToken(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.IDENTIFIER, 0, 0,
                          networkIdx, "IFW_TAP3.NetworkIdentifier.NETWORK_ID");
	}
	else if (blockType == lCSSPInfoBlockType)
	{
          edrConnectToken(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.NETWORK_LIST.IDENTIFIER, 0, 0,
                          networkIdx, "IFW_TAP3.NetworkIdentifier.NETWORK_ID");
	}
      }
    | /* EMPTY */
      {
	if (blockType == servingPartiesInfoBlockType)
	{
          edrMissingInput(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.IDENTIFIER, 0, 0,
                          networkIdx);
	}
	else if (blockType == lCSSPInfoBlockType)
	{
          edrMissingInput(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.NETWORK_LIST.IDENTIFIER, 0, 0,
                          networkIdx);
	}
      }
    ;

  networkList:
      networkList
      network
    | network
    ;

  networkList_opt:
      IFW_TAP3.NetworkList
      {
        networkIdx = -1; // initialize index counter
      }
      networkList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  networkList_opt2:
      networkList
    | /* EMPTY */ //accept empty list
    ;

  contentServiceUsed:
      IFW_TAP3.ContentServiceUsed
      {
        service_Type = service_Content;

        contentSvcUsedIdx = contentSvcUsedIdx + 1;
        if ( edrAddDatablock( DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST ) == false )
        {
          String Msg ="Failed to add ContentServiceUsed datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      contentTransactionCode_mandopt
      contentTransactionType_mandopt
      objectType_opt
      transactionDescriptionSupp_opt
      transactionShortDescription_mandopt
      transactionDetailDescription_opt
      transactionIdentifier_mandopt
      transactionAuthCode_opt
      dataVolumeIncoming_opt
      dataVolumeOutgoing_opt
      totalDataVolume_opt
      chargeRefundIndicator_opt
      contentChargingPoint_opt
      chargeInformationList_opt
      {  
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      advisedChargeInformation_opt
      IFW_TAP3.Block_END
    ;

  contentServiceUsedList:
      contentServiceUsedList
      contentServiceUsed
    | contentServiceUsed
    ;

  contentServiceUsedList_mandopt:
      IFW_TAP3.ContentServiceUsedList
      contentServiceUsedList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  contentServiceUsedList_opt2:
      contentServiceUsedList
    | /* EMPTY */
    ;

  contentTransactionCode_mandopt:
      IFW_TAP3.ContentTransactionCode
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_CODE, 0,
                        contentSvcUsedIdx, "IFW_TAP3.ContentTransactionCode.CONT_CODE");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_CODE, 0,
			contentSvcUsedIdx);
      }
    ;

  contentTransactionType_mandopt:
      IFW_TAP3.ContentTransactionType
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_TYPE, 0,
                        contentSvcUsedIdx, "IFW_TAP3.ContentTransactionType.CONT_TYPE");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_TYPE, 0,
                        contentSvcUsedIdx);
      }
    ;

  objectType_opt:
      IFW_TAP3.ObjectType
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.OBJECT_TYPE, 0,
                        contentSvcUsedIdx, "IFW_TAP3.ObjectType.OBJECT_TYPE");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.OBJECT_TYPE, 0,
			contentSvcUsedIdx);
      }
    ;

  transactionDescriptionSupp_opt:
      IFW_TAP3.TransactionDescriptionSupp
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DESCRIPTION_SUPP, 0,
                        contentSvcUsedIdx, "IFW_TAP3.TransactionDescriptionSupp.TRANS_DESCR_SUPP");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DESCRIPTION_SUPP, 0,
			contentSvcUsedIdx);
      }
    ;

  transactionDetailDescription_opt:
      IFW_TAP3.TransactionDetailDescription
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DETAIL_DESCRIPTION, 0,
                        contentSvcUsedIdx, "IFW_TAP3.TransactionDetailDescription.TRANS_DETAIL_DESCR");
      }
    | /* EMPTY */
    ;

  transactionIdentifier_mandopt:
      IFW_TAP3.TransactionIdentifier
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_IDENTIFIER, 0,
                        contentSvcUsedIdx, "IFW_TAP3.TransactionIdentifier.TRANS_IDENTIFIER");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_IDENTIFIER, 0,
			contentSvcUsedIdx);
      }
    ;

  transactionShortDescription_mandopt:
      IFW_TAP3.TransactionShortDescription
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_SHORT_DESCRIPTION, 0,
                        contentSvcUsedIdx, "IFW_TAP3.TransactionShortDescription.TRANS_SHORT_DESCR");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_SHORT_DESCRIPTION, 0,
                        contentSvcUsedIdx);
      }
    ;

  transactionAuthCode_opt:
      IFW_TAP3.TransactionAuthCode
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_AUTH_CODE, 0,
                        contentSvcUsedIdx, "IFW_TAP3.TransactionAuthCode.TRANS_AUTH_CODE");
      }
    | /* EMPTY */
    ;

  dataVolumeIncoming_opt:
      IFW_TAP3.DataVolumeIncoming
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_INCOMING, 0,
                        contentSvcUsedIdx, "IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_INCOMING, 0,
			contentSvcUsedIdx);
      }
    ;

  dataVolumeOutgoing_opt:
      IFW_TAP3.DataVolumeOutgoing
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_OUTGOING, 0,
                        contentSvcUsedIdx, "IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_OUTGOING, 0,
			contentSvcUsedIdx);
      }

    ;

  totalDataVolume_opt:
      IFW_TAP3.TotalDataVolume
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TOTAL_DATA_VOLUME, 0,
                        contentSvcUsedIdx, "IFW_TAP3.TotalDataVolume.TOTAL_DATA_VOLUME");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TOTAL_DATA_VOLUME, 0,
			contentSvcUsedIdx);
      }
    ;

  chargeRefundIndicator_opt:
      IFW_TAP3.ChargeRefundIndicator
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CHARGE_REFUND_INDICATOR, 0,
                        contentSvcUsedIdx, "IFW_TAP3.ChargeRefundIndicator.CHARGE_REFUND_INDICATOR");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CHARGE_REFUND_INDICATOR, 0,
			contentSvcUsedIdx);
      }
    ;

  contentChargingPoint_opt:
      IFW_TAP3.ContentChargingPoint
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_CHARGING_POINT, 0,
                        contentSvcUsedIdx, "IFW_TAP3.ContentChargingPoint.CONTENT_CHARGING_POINT");
      }
    | /* EMPTY */
    ;

  advisedChargeInformation_opt:
      IFW_TAP3.AdvisedChargeInformation
      {
        blockType = advisedChargeInfoBlockType;
      }
      paidIndicator_opt
      paymentMethod_opt
      advisedChargeCurrency_opt
      advisedCharge_mandopt
      commission_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  paidIndicator_opt:
      IFW_TAP3.PaidIndicator
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAID_INDICATOR, 0,
                        contentSvcUsedIdx, "IFW_TAP3.PaidIndicator.PAID_INDICATOR");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAID_INDICATOR, 0,
			contentSvcUsedIdx);
      }
    ;

  paymentMethod_opt:
      IFW_TAP3.PaymentMethod
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAYMENT_METHOD, 0,
                        contentSvcUsedIdx, "IFW_TAP3.PaymentMethod.PAYMENT_METHOD");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAYMENT_METHOD, 0,
			contentSvcUsedIdx);
      }
    ;

  commission_opt:
      IFW_TAP3.Commission
      {
        edrConnectToken(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0,
                        contentSvcUsedIdx, "IFW_TAP3.Commission.COMMISSION");
      }
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION,
		0, contentSvcUsedIdx);
       }
    ;

//----------------------------------------------------------------------------
// Fields added for the LocationService record
//----------------------------------------------------------------------------

  locationService:
      IFW_TAP3.LocationService
      {
        if ( createNewDetail(record_LOCN, type_LOCN) == false )
        {
          //TODO something
        }
        record_Type  = record_LOCN;
        service_Type = service_Location;
      }
      fraudMonitorIndicator_opt
      rapFileSequenceNumber_opt
      recEntityCode_mandopt
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.REC_ENTITY_CODE, 0,
                        "IFW_TAP3.RecEntityCode.REC_ENTITY_CODE");
	if (recEntityCodeIsMissing == true)
	{
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.REC_ENTITY_CODE, 0);
	  recEntityCodeIsMissing = false;
        }
      }
      callReference_opt
      trackingCustomerInformation_opt
      lCSSPInformation_opt
      trackedCustomerInformation_opt
      locationServiceUsage_mandopt
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  trackingCustomerInformation_opt:
      IFW_TAP3.TrackingCustomerInformation
      {
        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO ) == false )
        {
          String Msg ="Failed to add TrackingCustomerInformation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      trackingCustomerIdList_mandopt
      trackingCustomerHomeIdList_opt
      trackingCustomerLocList_opt
      trackingCustomerEquipment_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  trackingCustomerIdList:
      trackingCustomerIdList
      trackingCustomerIdentification
    | trackingCustomerIdentification
    ;

  trackingCustomerIdList_mandopt:
      IFW_TAP3.TrackingCustomerIdList
      {
        blockType = trackingCustomerIdBlockType;
        trackingCustIdx = -1; // initialize index counter
      }
      trackingCustomerIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  trackingCustomerIdList_opt2:
       trackingCustomerIdList
    | /* EMPTY */
    ;

  trackingCustomerIdentification:
      IFW_TAP3.TrackingCustomerIdentification
      {
        trackingCustIdx = trackingCustIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST ) == false )
        {
          String Msg ="Failed to add TrackingCustomerId datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      customerIdType_mandopt
      customerIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  trackingCustomerHomeIdList_opt:
      IFW_TAP3.TrackingCustomerHomeIdList
      {
        blockType = trackingCustomerHomeBlockType;
        trackingCustHomeIdx = -1; // initialize index counter
      }
      trackingCustomerHomeIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
  ;

  trackingCustomerHomeIdList_opt2:
      trackingCustomerHomeIdList_opt2
      trackingCustomerHomeId
    | /* EMPTY */
    ;

  trackingCustomerHomeId:
      IFW_TAP3.TrackingCustomerHomeId
      {
        trackingCustHomeIdx = trackingCustHomeIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST ) == false )
        {
          String Msg ="Failed to add TrackingCustomerHomeId datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      homeIdType_mandopt
      {
        if (homeIdTypeIsMissing == true)
        {
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0,
				    trackingCustHomeIdx);
          homeIdTypeIsMissing = false;
        }
      }
      homeIdentifier_mandopt
      {
        if (homeIdentifierIsMissing == true)
        {
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0,
			    trackingCustHomeIdx);
          homeIdentifierIsMissing = false;
        }
      }
      IFW_TAP3.Block_END
    ;

  trackingCustomerLocList_opt:
      IFW_TAP3.TrackingCustomerLocList
      {
        blockType = trackingCustomerLocnBlockType;
        trackingCustLocnIdx = -1; // initialize index counter
      }
      trackingCustomerLocList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  trackingCustomerLocList_opt2:
      trackingCustomerLocList_opt2
      trackingCustomerLocation
    | /* EMPTY */
    ;

  trackingCustomerLocation:
      IFW_TAP3.TrackingCustomerLocation
      {
        trackingCustLocnIdx = trackingCustLocnIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST ) == false )
        {
          String Msg ="Failed to add TrackingCustomerLocation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      locationIdType_mandopt
      locationIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  trackingCustomerEquipment_opt:
      IFW_TAP3.TrackingCustomerEquipment
      {
        blockType = trackingCustomerEqptBlockType;

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT ) == false )
        {
          String Msg ="Failed to add TrackingCustomerEquipment datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      equipmentIdType_mandopt
      equipmentId_mandopt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  lCSSPInformation_opt:
      IFW_TAP3.LCSSPInformation
      {
	blockType = lCSSPInfoBlockType;

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.LCSSP_INFO ) == false )
        {
          String Msg ="Failed to add LCSSPInformation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      lCSSPIdentificationList_mandopt
      loc_iSPList_opt
      networkList_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  lCSSPIdentificationList:
      lCSSPIdentificationList
      lCSSPIdentification
    | lCSSPIdentification
    ;

  lCSSPIdentification:
      IFW_TAP3.LCSSPIdentification
      {
        lcsspIdx = lcsspIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST ) == false )
        {
          String Msg ="Failed to add LCSSPId datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      contentProviderIdType_mandopt
      contentProviderIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

   lCSSPIdentificationList_mandopt:
      IFW_TAP3.LCSSPIdentificationList
      {
        blockType = lCSSPIdBlockType;
        lcsspIdx = -1; // initialize index counter
      }
      lCSSPIdentificationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

    lCSSPIdentificationList_opt2:
	lCSSPIdentificationList
    | /* EMPTY */
    ;

  loc_iSPList_opt:
      IFW_TAP3.ISPList
      {
        internetSvcProvIdx = -1; // initialize index counter
      }
      loc_iSPList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  loc_iSPList_opt2:
      loc_ISPList
    | /* EMPTY */
    ;

  loc_ISPList:
      loc_ISPList
      loc_iSP
    | loc_iSP
    ;

  loc_iSP:
      IFW_TAP3.InternetServiceProvider
      {
        internetSvcProvIdx = internetSvcProvIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST ) == false )
        {
          String Msg ="Failed to add InternetServiceProviderId datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      loc_iSPIdType_mandopt
      loc_iSPIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  loc_iSPIdType_mandopt:
      IFW_TAP3.IspIdType
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST.TYPE, 0, 0,
                        internetSvcProvIdx, "IFW_TAP3.IspIdType.ISP_ID_TYPE");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST.TYPE, 0, 0,
                        internetSvcProvIdx);
      }
    ;

  loc_iSPIdentifier_mandopt:
      IFW_TAP3.IspIdentifier
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST.IDENTIFIER, 0, 0,
                        internetSvcProvIdx, "IFW_TAP3.IspIdentifier.ISP_IDENTIFIER");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST.IDENTIFIER, 0, 0,
                        internetSvcProvIdx);
      }
    ;

  trackedCustomerInformation_opt:
      IFW_TAP3.TrackedCustomerInformation
      {
        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO ) == false )
        {
          String Msg ="Failed to add TrackedCustomerInformation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      trackedCustomerIdList_mandopt
      trackedCustomerHomeIdList_opt
      trackedCustomerLocList_opt
      trackedCustomerEquipment_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  trackedCustomerIdList:
      trackedCustomerIdList
      trackedCustomerIdentification
    | trackedCustomerIdentification
    ;

  trackedCustomerIdList_mandopt:
      IFW_TAP3.TrackedCustomerIdList
      {
        blockType = trackedCustomerIdBlockType;
        trackedCustIdx = -1; // initialize index counter
      }
      trackedCustomerIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  trackedCustomerIdList_opt2:
      trackedCustomerIdList
    | /* EMPTY */
    ;

  trackedCustomerIdentification:
      IFW_TAP3.TrackedCustomerIdentification
      {
        trackingCustIdx = trackingCustIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST ) == false )
        {
          String Msg ="Failed to add TrackedCustomerId datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      customerIdType_mandopt
      customerIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  trackedCustomerHomeIdList_opt:
      IFW_TAP3.TrackedCustomerHomeIdList
      {
        blockType = trackedCustomerHomeBlockType;
        trackedCustHomeIdx = -1; // initialize index counter
      }
      trackedCustomerHomeIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  trackedCustomerHomeIdList_opt2:
      trackedCustomerHomeIdList_opt2
      trackedCustomerHomeId
    | /* EMPTY */
    ;

  trackedCustomerHomeId:
      IFW_TAP3.TrackedCustomerHomeId
      {
        trackedCustHomeIdx = trackedCustHomeIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST ) == false )
        {
          String Msg ="Failed to add TrackedCustomerHomeId datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      homeIdType_mandopt
      {
        if (homeIdTypeIsMissing == true)
        {
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0,
				    trackedCustHomeIdx);
          homeIdTypeIsMissing = false;
        }
      }
      homeIdentifier_mandopt
      {
        if (homeIdentifierIsMissing == true)
        {
	  edrMissingInput(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0,
			    trackedCustHomeIdx);
	  homeIdentifierIsMissing = false;
        }
      }
      IFW_TAP3.Block_END
    ;

  trackedCustomerLocList_opt:
      IFW_TAP3.TrackedCustomerLocList
      {
        blockType = trackedCustomerLocnBlockType;
        trackedCustLocnIdx = -1; // initialize index counter
      }
      trackedCustomerLocList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  trackedCustomerLocList_opt2:
      trackedCustomerLocList_opt2
      trackedCustomerLocation
    | /* EMPTY */
    ;

  trackedCustomerLocation:
      IFW_TAP3.TrackedCustomerLocation
      {
        trackedCustLocnIdx = trackedCustLocnIdx + 1; // increment index counter

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST ) == false )
        {
          String Msg ="Failed to add TrackedCustomerLocation datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      locationIdType_mandopt
      locationIdentifier_mandopt
      IFW_TAP3.Block_END
    ;

  trackedCustomerEquipment_opt:
      IFW_TAP3.TrackedCustomerEquipment
      {
        blockType = trackedCustomerEqptBlockType;

        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT ) == false )
        {
          String Msg ="Failed to add TrackedCustomerEquipment datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      equipmentIdType_mandopt
      equipmentId_mandopt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  locationServiceUsage_mandopt:
      IFW_TAP3.LocationServiceUsage
      {
        if ( edrAddDatablock( DETAIL.ASS_LOCN_EXT.SERVICE_USAGE ) == false )
        {
          String Msg ="Failed to add LocationServiceUsage datablock " +
                      "to EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER));
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        }
      }
      lCSQosRequested_mandopt
      lCSQosDelivered_opt
      chargingTimeStamp_opt
      chargeInformationList_mandopt
      {   
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  lCSQosRequested:
      lCSRequestTimestamp_mandopt
      horizontalAccuracyRequested_opt
      verticalAccuracyRequested_opt
      responseTimeCategory_opt
      trackingPeriod_opt
      trackingFrequency_opt
    ;

  lCSQosRequested_mandopt:
      IFW_TAP3.LCSQosRequested
      lCSQosRequested
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        // Set sever error code
        // String offset = longToStr( edrFieldTokenBytePos( DETAIL.ASS_LOCN_EXT.SERVICE_USAGE));
        String offset = "-1";
        edrString( DETAIL.ERROR_REJECT_TYPE ) = "ERR_TAP3_RET";
        edrAddError("ERR_TAP3_RET", 3, "severe", "30", "382", "4", offset, "-1", "Missing LSCQoS Requested");
        setAssociatedTapErr("ERR_TAP3_MISSING_LSCQOS_RESQUESTED",3 ,"30" ,"382" ,"4");	
      }
    ;

  lCSRequestTimestamp:
      IFW_TAP3.LCSRequestTimeStamp
      IFW_TAP3.LocalTimeStamp
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_REQUEST_TIMESTAMP, 0, 0,
                        "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      IFW_TAP3.UtcTimeOffsetCode
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_REQ_UTC_OFFSET, 0, 0,
                        "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
      }
      IFW_TAP3.Block_END
    ;

  lCSRequestTimestamp_mandopt:
	lCSRequestTimestamp
    | /* EMPTY */
      {
	edrMissingInput(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_REQUEST_TIMESTAMP, 0, 0);
      }
    ;


  horizontalAccuracyRequested_opt:
      IFW_TAP3.HorizontalAccuracyRequested
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_REQUESTED, 0, 0,
                        "IFW_TAP3.HorizontalAccuracyRequested.HORIZONTAL_ACCURACY_REQUESTED");
      }
    | /* EMPTY */
    ;

  verticalAccuracyRequested_opt:
      IFW_TAP3.VerticalAccuracyRequested
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_REQUESTED, 0, 0,
                        "IFW_TAP3.VerticalAccuracyRequested.VERTICAL_ACCURACY_REQUESTED");
      }
    | /* EMPTY */
    ;

  responseTimeCategory_opt:
      IFW_TAP3.ResponseTimeCategory
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME_CATEGORY, 0, 0,
                        "IFW_TAP3.ResponseTimeCategory.RESPONSE_TIME_CATEGORY");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME_CATEGORY, 0, 0);
      }
    ;

  trackingPeriod_opt:
      IFW_TAP3.TrackingPeriod
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.TRACKING_PERIOD, 0, 0,
                        "IFW_TAP3.TrackingPeriod.TRACKING_PERIOD");
      }
    | /* EMPTY */
    ;

  trackingFrequency_opt:
      IFW_TAP3.TrackingFrequency
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.REQ_TRACKING_FREQUENCY, 0, 0,
                        "IFW_TAP3.TrackingFrequency.TRACKING_FREQUENCY");
      }
    | /* EMPTY */
    ;

  lCSQosDelivered_opt:
      IFW_TAP3.LCSQosDelivered
      lCSTransactionStatus_opt
      horizontalAccuracyDelivered_opt
      verticalAccuracyDelivered_opt
      responseTime_opt
      positioningMethod_opt
      loc_trackingPeriod_opt
      loc_trackingFrequency_opt
      ageOfLocation_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  lCSTransactionStatus_opt:
      IFW_TAP3.LCSTransactionStatus
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_TRANS_STATUS, 0, 0,
                        "IFW_TAP3.LCSTransactionStatus.LCS_TRANSACTION_STATUS");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_TRANS_STATUS, 0, 0);
      }
    ;

  horizontalAccuracyDelivered_opt:
      IFW_TAP3.HorizontalAccuracyDelivered
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_DELIVERED, 0, 0,
                        "IFW_TAP3.HorizontalAccuracyDelivered.HORIZONTAL_ACCURACY_DELIVERED");
      }
    | /* EMPTY */
    ;

  verticalAccuracyDelivered_opt:
      IFW_TAP3.VerticalAccuracyDelivered
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_DELIVERED, 0, 0,
                        "IFW_TAP3.VerticalAccuracyDelivered.VERTICAL_ACCURACY_DELIVERED");
      }
    | /* EMPTY */
    ;

  responseTime_opt:
      IFW_TAP3.ResponseTime
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME, 0, 0,
                        "IFW_TAP3.ResponseTime.RESPONSE_TIME");
      }
    | /* EMPTY */
    ;

  positioningMethod_opt:
      IFW_TAP3.PositioningMethod
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.POSITIONING_METHOD, 0, 0,
                        "IFW_TAP3.PositioningMethod.POSITIONING_METHOD");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.POSITIONING_METHOD, 0, 0);
      }
    ;

  loc_trackingPeriod_opt:
      IFW_TAP3.TrackingPeriod
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_PERIOD, 0, 0,
                        "IFW_TAP3.TrackingPeriod.TRACKING_PERIOD");
      }
    | /* EMPTY */
    ;

  loc_trackingFrequency_opt:
      IFW_TAP3.TrackingFrequency
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_FREQUENCY, 0, 0,
                        "IFW_TAP3.TrackingFrequency.TRACKING_FREQUENCY");
      }
    | /* EMPTY */
    ;

  ageOfLocation_opt:
      IFW_TAP3.AgeOfLocation
      {
        edrConnectToken(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.AGE_OF_LOCATION, 0, 0,
                        "IFW_TAP3.AgeOfLocation.AGE_OF_LOCATION");
      }
    | /* EMPTY */
      {
        edrMissingInput(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.AGE_OF_LOCATION, 0, 0);
      }
    ;
}
