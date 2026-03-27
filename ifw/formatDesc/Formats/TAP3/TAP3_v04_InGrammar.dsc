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
//   Input grammar file for the TAP3_v04 CDR format
//
//------------------------------------------------------------------------------
// $Log: TAP3_v04_InGrammar.dsc,v $
// Log 2004/07/19 sraut
// - PRSF00121159: Propagation of CO PRSF00118838 - Fixed the order for 
//		   UMTSQoSRequested and UMTSQoSUsed blocks as per TD.57
//
// Log 2003/03/13 pgeiger
// - PRSF00034549 : TAP3 input grammar is not correct according to TD.57
//   specification, some "mandatory" fields should only give warning if missing
//
// Log 2002/08/30 cdiab
// - PRSF00017680 : TAP3 format correction - now the ASS_CP and SS_EVENT_PACKET
//   are on separate lines, so also have a RECORD_TYPE and a RECORD_NUMBER
//
// Log 2002/08/02 cdiab
// - updated the batch reject process:
//   howto: implement a check, and on failure, call requestBatchReject() with 
//          appropriate parameters to activate the batch reject in onRollback()
// - PRSF00015605: we now store the CalledCountryCode in DETAIL.CALLED_COUNTRY_CODE
//
// Revision 1.33  2002/06/21 16:32:17  cdiab
// - implemented the Batch reject functionnality, and for that, the ISCRIPT_INCLUDE
//   environment variable must be set to the xxx/FMD/Formats/TAP3 folder
//
// Revision 1.32  2002/06/12 16:32:17  cdiab
// - now expects CHARGING_ID to be of type Decimal, for the edrConnectToken to
//   read it correctly
// - for CPs on an SCU record, update the ASS_CBD.CP.CHARGING_START_TIMESTAMP after
//   receiving the Deposit timestamp, to set a valid default.
//
// Revision 1.31  2002/06/07 16:32:17  cdiab
// - connected most of the needed edr fields, decimal field are still to be done
// - set a default of "0" for DETAIL.x_NUMBERING_PLAN
// - prepend CELL_ID and LOCATION_AREA_INDICATOR with 0s to a size of 5 digits
//
// Revision 1.30  2002/06/07 16:32:17  cdiab
// - replaced every TAB with corresponding spaces
//
// Revision 1.29  2002/06/05 17:44:17  cdiab
// - store the tap decimal places on the HEADER to transmit it to the RAP output
//
// Revision 1.28  2002/05/27 16:20:47  cdiab
// - now strip the TransfertBatch and CallEventDetailList from what is attached
//   to the EDRs
//
// Revision 1.27  2002/03/13 08:20:47  cdiab
// PETS #42982 : No Tax Handling in TAP3-In and TAP3-Out
// -store sum of tax values for a tap3 record in WHOLESALE_CHARGED_TAX_VALUE.
// -update onParseError() to write more explicit error messages to the logs.
//
// Revision 1.26  2002/03/12 18:07:36  cdiab
// PETS #42982 : No Tax Handling in TAP3-In and TAP3-Out
// added storage of the sum of tax values for a detail in WHOLESALE_CHARGED_TAX_VALUE.
//
// Revision 1.25  2002/03/07 13:26:14  cdiab
// PETS #43622 : TAP 3.4 parse error
// Modify the input grammar to accept non populated structures for every optional
// SEQUENCE OF structure of the TAP3 format.
//
// Revision 1.24  2001/11/22 15:59:37  cdiab
// PETS #41974: TAP3 ChargePacket wrongly flaged as Alternative
//
// Revision 1.23  2001/11/22 15:20:12  cdiab
// PETS #41974: TAP3 ChargePacket wrongly flaged as Alternative
//
// Revision 1.22  2001/11/21 15:17:17  cdiab
// PETS #41865 : TAP3 notification record is not created when HEADER and TRAILER exist
// Until now, we mapped a Notification file to a HEADER (and the other way around).
// We should rather map a Notification file to a HEADER+TRAILER (without any DETAIL).
//
// Revision 1.21  2001/11/21 12:19:24  cdiab
// PETS #41923 : add "real" parsing of ContentTransaction block for tap3
// -on input, the grammar is now set to parse the ContentTransaction record
// (and not just skip it). But we still do not store the data.
//
// Revision 1.20  2001/11/15 15:16:52  cdiab
// PETS #41247: Parser: error messages for parse errors not helpful
// -added 2 EDR field initialisations workaround for (with) "errorProcessing" (tag)
// PETS #41646: TaxRate is wrong reading TAP3 files, decimal places are not considered
// -for TAP3v03 and TAP3v04 we now expect (and write out) TaxRate with 5
//  decimal places
//
// Revision 1.19  2001/11/13 11:42:38  cdiab
// PETS #40773 : CAMEL support for V4.30
//
// Revision 1.18  2001/10/25 12:55:44  cdiab
// PETS #40975 : TotalCharge in AuditControl != sum of ChargeAmounts
// The charge amounts in the charge detail blocks should be rounded
// (normal rounding) before inserted into the file, and also before
// being added to the total to be used in the TotalCharge (which then
// should be only truncated to the decimal places). (otherwise we get
// a mismatch because of the rounding)
// Same thing for discounting and totalDiscount except that there, we
// do not round the value, we truncate it.
//
// Revision 1.17  2001/10/23 18:10:00  cdiab
// PETS #40891: TAP3 parse error : v04 read / v01 v04 write
//
// Revision 1.16  2001/10/19 11:39:37  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// on input, if the aggregation ChargeDetail (ie. type "00") has a charge
// or chargeableUnits, we use these for our DETAIL fields (sums).
//
// Revision 1.15  2001/10/19 09:11:25  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// -in case of GPRS, now DETAIL.VOLUME_SENT and DETAIL.VOLUME_RECEIVED store the value
// given on the GprsServiceUsage block (and not a summing for the chargeable quantities
// from the ChargeDetail all stored on the VOLUME_SENT like previously)
//
// Revision 1.14  2001/10/18 16:31:28  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// -for tap0304 in DETAIL.ASS_GPRS_EXT.APN_ADDRESS, use the ',' and not '.'
// as separator, as it can be composed of IP adresses
// -for writing of decimal values, use round() (and not trunc()) to get an
// integer
// -we now always write the ChargeDetail.Charge, even if it is 0
// -NetworkType is written out for the details onlöy if it is set to mixed
// (ie. 0) in the registry
//
// Revision 1.13  2001/10/11 12:14:45  cdiab
// PETS #40345: in TAP3 Audit block, INTEGERS can up to 8 bytes
// we now use the ASN_HexString type to manage them and read them directly as Decimal.
//
// Revision 1.12  2001/10/11 10:57:44  cdiab
// PETS #40344: modify output grammar to generate Tap3 Notification
// -modified the grammar to map an incoming notification file to a HEADER
//
// Revision 1.11  2001/10/10 16:00:10  cdiab
// PETS #40293: correct little formats error in Tap3 implementation
// on input:
// -store on TRAILER block: FIRST_CHARGING_UTC_TIME_OFFSET, LAST_CHARGING_UTC_TIME_OFFSET
// -store on CHARGE_PACKET block: CHARGEABLE_QUANTITY_VALUE
// -store on ASS_GPRS block: A_NUMBER_USER (not normalized A_NUMBER)
// on output:
// -chargeableUnits,are written out
// -the real UtcTimeOffset for Earliest and Latest call are written to Audit block
// -if fileTypeIndicyator=="T", it is ommited
// -if totalTaxRefund (resp. totalDiscountRefund) is 0, it is ommited
// -if tapCurrency=="SDR" (red from the registry) ommit it
//
// Revision 1.10  2001/10/09 15:27:24  cdiab
// PETS #40225: Error reading ChargeDetail with ChargeType "00" (input)
// we now store all ChargeDetails as CP, but mark redundant CPs with
//    DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE = "A" (ie. alternative price model)
// +now ChargingId is read even if it holds on more that a long integer.
//
// Revision 1.9  2001/10/01 16:27:25  cdiab
// PETS #39726 : Number normalization must support multiple IAC's
// -TAP3 has been updated to use the new converCli method (previous checkin
// [v4-30-11] was only a workaround).
//
// Revision 1.8  2001/09/21 13:02:22  cdiab
// PETS #39723: Number normalisation in Tap3 has errors
// -Now we initialise by default x_NUMBER and INTERN_x_NUMBER_ZONE to <iac><cc>
// (defTelNumber) as retrieved from the input stream
// -Form MOC, INTERN_A_NUMBER_ZONE="0000"+ORIGINATING_SWITCH_ID
// -Form MTC, INTERN_B_NUMBER_ZONE="0000"+TERMINATING_SWITCH_ID
// -If number is flagged as modified, x_MODIFICATION_INDICATOR is set to "08"
// -transmit in HEADER.ORIGIN_COUNTRY_CODE, the defTelNumber used when no MSISDN
// was given on input (defTelNumber=<iac><cc>)
//
// Revision 1.7  2001/09/20 12:08:14  cdiab
// PETS #39644: be able to normalize a TelNum using arrays for CC and IAC
// On output we now use 2 new additional registry entries at the pipeline level:
//      InternationalAccessCodeList = 001,002,00,011
//      CountryCodeList             = 852,49,1
// These entries are used to build the CalledNumberAnalisys block which is used
// for number normalization when reading tap3 files.
// These registry entries have to be updated with a list of all iac and cc that
// can be used in the streams.
//
// I also used the oportunity to correct the fact that:
//   DETAIL.ASS_GPRS_EXT.CHARGING_ID is a String (was used as a Long)
//   DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE is a Decima (was used as a Long)
//
// Revision 1.6  2001/09/19 16:27:25  cdiab
// PETS #39644: be able to normalize a TelNum using arrays for CC and IAC
// now using convertCli2 for number normalization
//
// Revision 1.5  2001/09/14 15:00:54  cdiab
// PETS #39334: for tap0303 manage CALL_TYPE as for tap0304.
// i also used the oportunity to set defaults for registry values when they
// are not present in the registry file.
//
// Revision 1.4  2001/09/14 14:16:54  cdiab
// PETS #39333: in TAP3, add ability to select tap or local currency.
// We store the local and tap currency names on the ChargePacket, and the
// exchange rate from on to the other.
// on output side, we expect all values to be in tap currencies.
//
// Revision 1.3  2001/09/06 10:45:10  cdiab
// PETS #38890 : Errors when writing TAP3 to output.
// remove use of multiple blocks with same tag but different names.
// (the parser would always take the first found).
// now using HexString to read integer or OctetString objects.
//
// Revision 1.2  2001/09/05 12:05:35  cdiab
// PETS #38720 : add ability to write Tap3 v04 (TD57v3.8.2)
// added TAP3_v04_OutGrammar.dsc
// and modified input to be also able to read Tap0303 in the same pipeline.
//
// Revision 1.1  2001/08/03 13:34:16  cdiab
// PETS #37760 : add support for Tap0304 (TD57v3.8.2) input
// -added Blocks and InGrammar files for TAP3_v04
// -modfied TAP3_v01 so that the block definition of TAP3_v04 is backward compatible
// -removed Mapping files (were empty, and will never be used)
//
// Revision 1.14  2001/07/27 15:23:48  cdiab
// PETS #37569 : no error are attached to TAP3 edrs, only message in log.
// Modified TAP3_v01_InGrammar.dsc to attach an error to the EDR in place of
// writing to the pipeline.log file.
// I also used the opportunity to add the IFW_TAP3.Notification block recognition.
//
// Revision 1.13  2001/07/26 09:46:13  cdiab
// PETS #37348 : the called number is not normalized on input
// We now normalize A_NUMBER, INTERN_A_NUMBER_ZONE,
//                  B_NUMBER, INTERN_B_NUMBER_ZONE,
//                  C_NUMBER, INTERN_C_NUMBER_ZONE
// Modification done in TAP3_v01_InGrammar.dsc
//
// Revision 1.12  2001/07/12 10:40:04  cdiab
// -PETS #36928 : rename regestry root to ifw, remove console prints of start/end
// processing time.
//
// Revision 1.9  2001/06/05 15:40:12  cdiab
// now uses TapDecimalPlaces to calculate AbsoluteAmount values.
//
// Revision 1.4  2001/05/29 10:12:25  cdiab
// corrected Pb when ChargeType="00" and other ChargeDetail follow, but without
// any charge (in this case, store the charge from the "00" ChargeDetail on the
// last CP).
//
// Revision 1.0  2001/05/18 11:38:03  cdiab
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
  Long       record_Type   =0; // use to know which type of detail we are reading

  // constants
  const Long service_Basic  =1;
  const Long service_Camel  =2;
  const Long service_Gprs   =3;
  const Long service_Suppl  =4;
  const Long service_Vas    =5;
  const Long service_Content=6;
  Long       service_Type   =0; // use to know which type of service we are reading

  // constants
  const String type_HEADER        ="010";
  const String type_TRAILER       ="090";
  const String type_MOC           ="021";
  const String type_MTC           ="031";
  const String type_MSS           ="029";
  const String type_SCU           ="050";
  const String type_VAS           ="060";
  const String type_CONT          ="999"; //TODO get real type
  const String type_GPRS_SG       ="040";
  const String type_GPRS_GG       ="042";
  const String type_GPRS_assembled="042"; //default for mixed ticket
  const String type_GPRS          ="042"; //default is mixed ticket
  const String extension_GSMW     ="520";
  const String extension_GPRS     ="540";
  const String extension_CBD      ="980"; //default CBD is global charge
  const String extension_CAMEL    ="700";
  const String extension_CP       ="680";
  const String extension_SS_EVENT ="620";

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
  Long tap3Detail;
  Long details;
  Long successiveBasicServiceUsed;
  Long successiveChargeInformation;
  Long successiveChargeDetail;
  Long successiveChargePacket;
  Long successiveChargePacketCI;
  
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
  Decimal theTotalChargedValue_00;
  String  lastTotalChargeValueChargeType;
  Decimal lastTotalChargeValueAbsoluteAmount;
  Long    theSenderNetworkType;
  String  theLocalCurrency;
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

  // for GPRS Service usage
  String  lastRemotePdpAddressList;
  String  lastAPN;
  Decimal sumDataVolumeIncoming;
  Decimal sumDataVolumeOutgoing;

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
  Long    lastChargedUnits;
  String  lastChargeDetailTimeStamp;
  Long    lastTaxRate;
  Decimal lastTaxCharge;
  Decimal sumTaxChargeEDR;
  Decimal sumTaxChargeFile;
  Decimal sumTaxChargeFileAll;
  Decimal sumTaxChargeCI;
  Long    lastDiscountCode;
  Decimal lastDiscountValue;
  Decimal sumChargedAmountValueEDR;  // EDR level sum
  Decimal sumChargedAmountValueFile; // Tap3 File level sum
  Decimal sumChargedAmountValueCI;   // ChargeInformation block level sum

  Long    CPidx;
  Long    ssPacketIdx;
  Long    lastCPidx_00;
  Decimal lastChargedAmountValue_00;
  Long    lastChargeableUnits_00;
  Long    lastChargedUnits_00;
  
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
  Long   recEntityType[];
  Long   recEntityId_Type[]; // recEntityId_mscId/recEntityId_msisdn/recEntityId_iPTextV4Address/recEntityId_iPTextV6Address
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
  
  // storage of registry values
  String strRapSequencer;
  String strOriginCountryCode;
  String strSenderCountryCode;
  Bool   bUseLocalCurrency;

  // Error processing for Batch Reject
  String toReturn_StreamName    ="";
  String toReturn_ErrFileName   ="";
  String toReturn_RetFileName   ="";
  String toReturn_RetTmpFileName= "";
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
    
    //logPipeline( "TAP3_ERROR on "+errorBlockName ,3);
    logPipeline("TAP3_ERROR on "+errorBlockName+", at BytePos @"+longToStr(ERROR_TOKEN_BYTEPOS)+
                " (ie. @0x"+longToHexStr(ERROR_TOKEN_BYTEPOS)+
                "), Token hex content=<"+ERROR_TOKEN_ASC+">",3);
  }
  
  function onParseStart
  {
    lexState("STATE_TAP3");
  }
  
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
          logPipeline(msgBuffer,0);
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
            logPipeline(msgBuffer,1);
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
                        sysdate(),              //Date    creationTime,
                        defUtcTimeOffset,       //String  headerUtcTimeOffset, //TODO
                        theTap3SpecificationVersionNumber,
                        theTap3ReleaseVersionNumber,
                        1,      //Long    rapSpecNo,
                        1,      //Long    rapRelNo,
                        " ",    //String  typeInd,
                        strToLong(toReturn_TapSeqNum),
                        0,      //Long    totRetCharge,
                        0,      //Long    rapDetWritten,
                        toReturn_ObjTag,        //Long    pathItemId,
                        toReturn_ArrayIdx,      //Long    arrayIndex,
                        toReturn_ObjDepth,      //Long    objDepth,
                        toReturn_ObjOffset,     //Long    objOffset,
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

  function requestBatchReject(  Long ObjTag,
                                Long ArrayIdx,
                                Long ObjDepth,
                                Long ObjOffset,
                                Long ErrCode)
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
                        "), ArrayIdx(" +longToStr(toReturn_ObjTag)+
                        "), ObjDepth(" +longToStr(toReturn_ObjTag)+
                        "), ObjOffset("+longToStr(toReturn_ObjTag)+
                        "), ErrCode("  +longToStr(toReturn_ObjTag)+")";
    edrAddError("ERR_INPUT_REQUEST_ROLLBACK",3,rejReason);
  }

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
    bUseLocalCurrency = false;                   //this is default if is not specified
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
    recEntityId_mscId           = 1;
    recEntityId_msisdn          = 2;
    recEntityId_iPTextV4Address = 3;
    recEntityId_iPTextV6Address = 4;
      
    // initialisation of some runtime variables
    //-----------------------------------------
    startTime  = defLocalTime;
    stopTime   = defLocalTime;

  }

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
    tap3Detail                  = 0;
    details                     = 0;
    theSender                   = "";
    theRecipient                = "";
    theTap3SpecificationVersionNumber = 0; //TODO default?
    theTap3ReleaseVersionNumber       = 0; //TODO default?
    theFileSeqNum               = 0;
    theOrigFileSeqNum           = 0;
    theTotalChargedValue        = 0.0;
    theTotalChargedValue_00     = 0.0;
    lastLocalTimeStamp          = defLocalTimeStamp;
    lastUtcTimeOffset           = defUtcTimeOffset;
    sumChargedAmountValueFile   = 0.0;
    sumTaxChargeFile            = 0.0;
    sumTaxChargeFileAll         = 0.0;

    theLocalCurrency            = "SDR"; // default
    theTapCurrency              = "SDR"; // default
    theTapDecimalPlaces         = 0;     // manadatory tap3 field, will be overwritten
    theAbsoluteAmountDivider    = 1.0;   // corresponding to theTapDecimalPlaces
  }
   
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
    else
        logStdout( "ERROR: unknown detail type: "+longToStr(detailTypedId)+"\n" ); 
*/

    // Add the Extension block to store service information
    if      (   ( detailTypedId==record_MOC ) or
                ( detailTypedId==record_MTC ) or
                ( detailTypedId==record_MSS ) or
                ( detailTypedId==record_SCU ) or
                ( detailTypedId==record_CONT) or
                ( detailTypedId==record_VAS )  )
    {
      if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT ) == false ) 
      { 
        String Msg = "failed to add ASS_GSMW_EXT datablock for EDR "+longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        return false; //TODO check for consequences
      }
      records = records+1;
      edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)                 = 1;
      edrString(DETAIL.ASS_GSMW_EXT.RECORD_TYPE, 0)             = extension_GSMW;
      edrLong(DETAIL.ASS_GSMW_EXT.RECORD_NUMBER,0 )             = records;
      edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS, 0)      = 0;
    }
    else if ( detailTypedId==record_GPRS )
    {
      if ( edrAddDatablock( DETAIL.ASS_GPRS_EXT ) == false ) 
      { 
        String Msg = "failed to add ASS_GPRS_EXT datablock for EDR "+longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
        return false; //TODO check for consequences
      }
      records = records+1;
      edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)                 = 1;
      edrString(DETAIL.ASS_GPRS_EXT.RECORD_TYPE, 0)             = extension_GPRS;
      edrLong( DETAIL.ASS_GPRS_EXT.RECORD_NUMBER,0 )            = records;
      
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
    else
    {
      String Msg = "unknown detail type: "+longToStr(detailTypedId)+", for EDR "+longToStr(records);
      edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);  
//logStdout( "ERROR: unknown detail type: "+longToStr(detailTypedId)+"\n" ); 
      return false; //TODO check for consequences
    }

    // initialisation to defaults
    edrLong(DETAIL.DISCARDING)                         = 0;
    edrLong(DETAIL.A_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.A_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.A_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_A_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.B_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.B_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.B_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_B_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.C_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.C_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.C_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_C_NUMBER_ZONE)             = defTelNumber;
    edrString(DETAIL.USAGE_DIRECTION)                  = "0";
    edrString(DETAIL.BASIC_SERVICE)                    = "011";
    edrString(DETAIL.CALL_COMPLETION_INDICATOR)        = defCauseForTerm;   // normal charging
    edrString(DETAIL.LONG_DURATION_INDICATOR)          = "S";    // single record (no chain)
    edrDate(DETAIL.CHARGING_START_TIMESTAMP)           = defLocalTime;
    edrDate(DETAIL.CHARGING_END_TIMESTAMP)             = defLocalTime;
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
    successiveChargeDetail      = 0;
    successiveChargePacket      = 0;
    CPidx                       = 0; //index of the current ChargePacket

    // some detail level runtime values
    lastLocalTimeStamp          = defLocalTimeStamp;
    lastUtcTimeOffset           = defUtcTimeOffset;
    lastValidLocalTimeStamp     = defLocalTimeStamp;
    lastValidUtcTimeOffset      = defUtcTimeOffset;
    lastCode                    = 0;
    
    return true;
  }

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
  function storeChargeInfoTempFields
  {
    if (successiveChargeInformation >= 1)
    {
      // default values
      edrString(DETAIL.ASS_CBD.SYSTEM_BRAND_CODE,0)     = "0";
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
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0)=successiveChargePacket;

      edrString(DETAIL.WHOLESALE_IMPACT_CATEGORY)       = "00";       // as for IFW_TAP3.ChargeType : global charge for ChargeInformation
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) = sumChargedAmountValueEDR;
      if (bUseLocalCurrency)
      {
        edrString(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY) = theLocalCurrency;
      }
      else
      {
        edrString(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY) = theTapCurrency;
      }
      edrString(DETAIL.WHOLESALE_CHARGED_TAX_TREATMENT) = "N";
      edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE)        = lastTaxRate;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)    = sumTaxChargeEDR; //TODO check
    }
  }

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
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0)=successiveChargePacket;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) = sumChargedAmountValueEDR;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)    = sumTaxChargeEDR;  //TODO check
    }
  }

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
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0)=successiveChargePacket;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) = sumChargedAmountValueEDR;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)    = sumTaxChargeEDR;  //TODO check
    }
  }

  function Bool newBasicServiceBlock
  {
    service_Type                = service_Basic;
    successiveBasicServiceUsed  = successiveBasicServiceUsed +1;
    successiveChargeInformation = 0; // for this Service Block
    successiveChargeDetail      = 0; // for this one Charge Information
    successiveChargePacket      = 0; // for this EDR

    if (successiveBasicServiceUsed > 1)
    {
//logStdout("successive service block number "+longToStr(successiveBasicServiceUsed)+" for Tap3 record "+longToStr(tap3Detail)+"\n");
      if (successiveBasicServiceUsed == 2)
      {
        // get a new unique ID to chain all records for aggregation (do only once!)
        chainReference = chainReference +1;  
        edrString(DETAIL.CHAIN_REFERENCE)         = longToStr(chainReference);
        edrString(DETAIL.LONG_DURATION_INDICATOR) = "F"; //the first record of the chain
      }
      if ( edrSetCurrent( theLastEdrCopy ) == true ) 
      {
        theLastEdrCopy  = edrDuplicate();
        if ( theLastEdrCopy < 0 )  
        {  
          // failed to duplicate the edr, add error
          edrAddError( "ERR_EDR_DUPLICATION_FAILED", 4 );
          return false;
        }
        details=details+1;
        records=records+1;
//logStdout("record_xxx  #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+") [by duplication]\n" );
        edrLong(DETAIL.RECORD_NUMBER)             = records;
        edrString(DETAIL.CHAIN_REFERENCE)         = longToStr(chainReference);
        edrString(DETAIL.LONG_DURATION_INDICATOR) = "I"; //an intermediate record of the chain
      }
      else
      {
        // failed to edrSetCurrent on the copy edr, add error
        String Msg = "edrSetCurrent(theLastEdrCopy) FAILED before edrDuplicate()";
        edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
        return false;
      }
    }
    return true;
  }

  function Decimal getExchangeRateFactor(Long ExchangeRateCode)
  {
    if (ExchangeRateCode >= currencyEntries)
    {
      // this should never happen!
      String Msg = "getExchangeRateFactor("+longToStr(ExchangeRateCode)+"), unknown ExchangeRateCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return(1.0);
    }
    return(exchangeRateFactor[ExchangeRateCode]);
  }

  function Long getRecEntityType(Long RecEntityCode)
  {
    if (RecEntityCode >= recEntityEntries)
    {
      // this should never happen!
      String Msg = "getRecEntityType("+longToStr(RecEntityCode)+"), unknown RecEntityCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return(0);
    }
    return( recEntityType[RecEntityCode] );
  }
  function String getRecEntityId(Long RecEntityCode)
  {
    if (RecEntityCode >= recEntityEntries)
    {
      // this should never happen!
      String Msg = "getRecEntityId("+longToStr(RecEntityCode)+"), unknown RecEntityCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return("");
    }
    return( recEntityId[RecEntityCode] );
  }

  function String getVasShortDesc(Long VasCode)
  {
    if (VasCode >= vasEntries)
    {
      // this should never happen!
      String Msg = "getVasShortDesc("+longToStr(VasCode)+"), unknown VasCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return("");
    }
    return( vasShortDesc[VasCode] );
  }
  
  function Long getDiscountAppliedType(Long DiscountCode)
  {
    if (DiscountCode >= discountEntries)
    {
      // this should never happen!
      String Msg = "getDiscountAppliedType("+longToStr(DiscountCode)+"), unknown DiscountCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return(0);
    }
    return( discountApplied_Type[DiscountCode] );
  }
  function Long getDiscountApplied(Long DiscountCode)
  {
    if (DiscountCode >= discountEntries)
    {
      // this should never happen!
      String Msg = "getDiscountApplied("+longToStr(DiscountCode)+"), unknown DiscountCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return(0);
    }
    return( discountApplied[DiscountCode] );
  }

  function String getTaxRate(Long TaxCode)
  {
    if (TaxCode >= taxEntries)
    {
      // this should never happen!
      String Msg = "getTaxRate("+longToStr(TaxCode)+"), unknown TaxCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return("");
    }
    return( taxRate[TaxCode] );
  }

  function String getUtcTimeOffset(Long TimeOffsetCode)
  {
    if (TimeOffsetCode >= utcTimeOffsetEntries)
    {
      // this should never happen!
      String Msg = "getUtcTimeOffset("+longToStr(TimeOffsetCode)+"), unknown utcTimeOffsetCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return("");
    }
    return( utcTimeOffset[TimeOffsetCode] );
  }

  function String getMessageDescription(Long MessageDescriptionCode)
  {
    if (MessageDescriptionCode >= messageDescriptionEntries)
    {
      // this should never happen!
      String Msg = "getMessageDescription("+longToStr(MessageDescriptionCode)+"), unknown MessageDescriptionCode";
      edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
      return("");
    }
    return( messageDescription[MessageDescriptionCode] );
  }

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
        localString = localString + calledNumberAnalysisIACarray[i][j] + ",";
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
        localString = localString + calledNumberAnalysisCCarray[i][j] + ",";
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
      case (record_GPRS):
      {
        edrConnectToken(DETAIL.OPERATOR_SPECIFIC_INFO, "IFW_TAP3.OperatorSpecInformation.OPERATOR_SPEC_INFORMATION");
      }
      break;
      case (record_Header):
      {
        edrConnectToken(HEADER.OPERATOR_SPECIFIC_INFO, "IFW_TAP3.OperatorSpecInformation.OPERATOR_SPEC_INFORMATION");
      }
      break;
      case (record_Trailer):
      {
        edrConnectToken(TRAILER.OPERATOR_SPECIFIC_INFO, "IFW_TAP3.OperatorSpecInformation.OPERATOR_SPEC_INFORMATION");
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
//logStdout( "  Start Tap0304 input :  " + dateToStr(startTime)+ "\n");         //TODO remove this line or just comment it
//logStdout( "  End   Tap0304 input :  " + dateToStr(stopTime) + "\n");         //TODO remove this line or just comment it
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
      IFW_TAP3.Sender
      {
        theSender = tokenString("IFW_TAP3.Sender.PLMN_ID");
        edrString(HEADER.SENDER)= theSender;
      }
      IFW_TAP3.Recipient
      {
        theRecipient = tokenString("IFW_TAP3.Recipient.PLMN_ID");
        edrString(HEADER.RECIPIENT)= theRecipient;
      }
      IFW_TAP3.FileSequenceNumber
      {
        theFileSeqNum     = tokenLong("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER");
        theOrigFileSeqNum = theFileSeqNum;
        edrLong(HEADER.SEQUENCE_NUMBER)       = theFileSeqNum;
        edrLong(HEADER.ORIGIN_SEQUENCE_NUMBER)= theOrigFileSeqNum;
      }
      rapFileSequenceNumber_opt
      fileCreationTimeStamp_opt
      fileAvailableTimeStamp_opt
      transferCutOffTimeStamp_opt
      IFW_TAP3.SpecificationVersionNumber
      {
        edrConnectToken(HEADER.SPECIFICATION_VERSION_NUMBER, "IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER");
        theTap3SpecificationVersionNumber = edrLong(HEADER.SPECIFICATION_VERSION_NUMBER);
      }
      IFW_TAP3.ReleaseVersionNumber
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
      batchControlInfo
      accountingInfo_opt
      networkInfo
      {
        // for every stream, the default TelNnumber is different, built as <iac><cc>
        defTelNumber = convertCli(      "", "00", 0,
                                        NORM_NAC,
                                        calledNumberAnalysisIACarray[0],// NORM_IAC,
                                        calledNumberAnalysisCCarray[0], // NORM_CC,
                                        NORM_IAC_SIGN,
                                        NORM_NDC );
        edrString(HEADER.ORIGIN_COUNTRY_CODE) = defTelNumber; //strOriginCountryCode; //TODO check
        edrString(HEADER.SENDER_COUNTRY_CODE) = strSenderCountryCode; //TODO check (we take it from registry)
        edrString(HEADER.IAC_LIST)            = getIacList();
        edrString(HEADER.CC_LIST)             = getCcList();
      }
      vasInfo_opt
      messageDescriptionInfo_opt
      {
        errorStateTap3 = endTap3Header;
      }
      callEventDetails
      auditControlInfo
      IFW_TAP3.Block_END
      {
        createNewGarbageCollectorDetail();
      } 
    ;
        
        
  accountingInfo_opt:
      IFW_TAP3.AccountingInfo
      {
        errorStateTap3 = beginTap3AccountingInfo;
      }
      taxation_opt
      discounting_opt
      IFW_TAP3.LocalCurrency
      {
        theLocalCurrency = tokenString("IFW_TAP3.LocalCurrency.CURRENCY");
      }
      tapCurrency_opt
      currencyConversion_opt
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
        errorStateTap3 = endTap3AccountingInfo;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  aiurRequested_opt:
      IFW_TAP3.AiurRequested
    | /* EMPTY */
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

  auditControlInfo: 
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
      }
      earliestCallTimeStamp_opt
      latestCallTimeStamp_opt
      IFW_TAP3.TotalChargeValueList
      totalChargeValueList
      IFW_TAP3.Block_END
      {
        edrDecimal(TRAILER.TOTAL_RETAIL_CHARGED_VALUE)     = 0.0;
        edrDecimal(TRAILER.TOTAL_WHOLESALE_CHARGED_VALUE)  = sumChargedAmountValueFile;
      }
      totalTaxRefund_Compatibility
      IFW_TAP3.TotalTaxValue
      IFW_TAP3.TotalDiscountValue
      totalDiscountRefund_opt
      totalAdvisedChargeValueList_opt
      IFW_TAP3.CallEventDetailsCount
      operatorSpecInformation_opt
      {
        errorStateTap3 = endTap3AuditControlInfo;
      }
      IFW_TAP3.Block_END
    ;
    
  totalTaxRefund_Compatibility:
      IFW_TAP3.TotalTaxRefund
    | /* EMPTY */  //for compatibility with before tap0304
    ;
    
  batchControlInfo:
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
      IFW_TAP3.Sender
      {
        theSender = tokenString("IFW_TAP3.Sender.PLMN_ID");
        edrString(HEADER.SENDER)= theSender;
      }
      IFW_TAP3.Recipient
      {
        theRecipient = tokenString("IFW_TAP3.Recipient.PLMN_ID");
        edrString(HEADER.RECIPIENT)= theRecipient;
      }
      IFW_TAP3.FileSequenceNumber
      {
        theFileSeqNum     = tokenLong("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER");
        theOrigFileSeqNum = theFileSeqNum;
        edrLong(HEADER.SEQUENCE_NUMBER)       = theFileSeqNum;
        edrLong(HEADER.ORIGIN_SEQUENCE_NUMBER)= theOrigFileSeqNum;
      }
      fileCreationTimeStamp_opt
      transferCutOffTimeStamp_opt
      fileAvailableTimeStamp
      {
        edrDate(HEADER.TRANSMISSION_DATE) = strToDate(theFileAvailableTimeStamp);
      }
      IFW_TAP3.SpecificationVersionNumber
      {
        edrConnectToken(HEADER.SPECIFICATION_VERSION_NUMBER, "IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER");    
      }
      IFW_TAP3.ReleaseVersionNumber
      {
        edrConnectToken(HEADER.RELEASE_VERSION, "IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER");    
      }
      fileTypeIndicator_opt
      {
        edrString(HEADER.DATA_TYPE_INDICATOR) = theFileTypeIndicator;    
      }
      rapFileSequenceNumber_opt
      operatorSpecInformation_opt
      {
        errorStateTap3 = endTap3BatchControlInfo;
      }
      IFW_TAP3.Block_END
    ;

  basicHSCSDParameters:
      IFW_TAP3.BasicHSCSDParameters
      fnur_opt
      aiurRequested_opt
      IFW_TAP3.NumberOfChannels
      channelCodingsAcceptable_opt
      IFW_TAP3.ChannelCoding
      IFW_TAP3.NumberOfChannelsUsed
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)    = longToDecimal( tokenLong("IFW_TAP3.NumberOfChannelsUsed.NUMBER_OF_CHANNELS_USED") );    
        edrString(DETAIL.NUMBER_OF_UNITS_UOM) = "CHL";    
      }
      IFW_TAP3.Block_END
    ;

  basicService:
      IFW_TAP3.BasicService
      basicServiceCode
      radioChannelRequested_opt
      radioChannelUsed_opt
      speechVersionRequested_opt
      speechVersionUsed_opt
      transparencyIndicator_opt
      IFW_TAP3.Block_END
    ;

  basicServiceCode:
      IFW_TAP3.TeleServiceCode
      {
        edrConnectToken(DETAIL.BASIC_SERVICE, "IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE");
        edrString(DETAIL.BASIC_SERVICE) = "0" + edrString(DETAIL.BASIC_SERVICE) ;
      }
    | IFW_TAP3.BearerServiceCode
      {
        edrConnectToken(DETAIL.BASIC_SERVICE, "IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE");
        edrString(DETAIL.BASIC_SERVICE) = "1" + edrString(DETAIL.BASIC_SERVICE) ;
      }
    ;

  basicServiceCodeList:  //only used for supplementary services affected Basic Services
      basicServiceCodeList 
      basicServiceCode
      {
        SsBasicServicesAffected[SsBasicServicesAffectedNb] = lastBasicService ;
        SsBasicServicesAffectedNb                          = SsBasicServicesAffectedNb +1;
      }
    | basicServiceCode
      {
        SsBasicServicesAffected[SsBasicServicesAffectedNb] = lastBasicService ;
        SsBasicServicesAffectedNb                          = SsBasicServicesAffectedNb +1;
      }
    ;

  basicServiceCodeList_opt:
      IFW_TAP3.BasicServiceCodeList
      {
        SsBasicServicesAffectedNb                          = 0; // initialisation
      }
      basicServiceCodeList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        SsBasicServicesAffectedNb                          = 0; // initialisation
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
      basicService
      chargingTimeStamp_opt
      {
        initializeChargeInfoTempFields();
      }
      IFW_TAP3.ChargeInformationList
      chargeInformationList
      IFW_TAP3.Block_END
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


  calledNumAnalysis:
      IFW_TAP3.CalledNumAnalysis
      calledNumAnalysisCode_opt
      {
        calledNumberAnalysisCode[lastCode]      = lastCalledNumAnalysisCode;
      }
      countryCodeTable
      {
        calledNumberAnalysisCC[lastCode]        = lastCalledNumberAnalysisCC; //we store only the last element
      }
      iacTable
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
      {
        lastCode = 0; //the first taken is 0 because for calledNumAnalysis we make a list search
      }
      calledNumAnalysis // first element of the list
    ;

  calledNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        edrString(DETAIL.B_NUMBER)             = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
        edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
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
          if ( edrSetCurrent( theLastEdrCopy ) == true ) 
          { 
            edrDelete();
            theLastEdrCopy = 0;
          }
          else
          {
            String Msg = "edrSetCurrent(theLastEdrCopy) FAILED before edrDelete()";
            edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
          }
        }
      }
    ;

  callEventDetails:
      IFW_TAP3.CallEventDetailList
      {
        createNewGarbageCollectorDetail();
        errorStateTap3 = beginTap3DetailList;
      }
      callEventDetailList
      {
        errorStateTap3 = endTap3DetailList;
      }
      IFW_TAP3.Block_END
      {
        createNewGarbageCollectorDetail();
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
        //mandatory field for MOC, MTC, GPRS, will serve as a default timestamp
        lastValidLocalTimeStamp = lastLocalTimeStamp; // to serve as default LocalTimeStamp for coresponding record
        lastValidUtcTimeOffset  = lastUtcTimeOffset;  // to serve as default UtcTimeOffset for coresponding record
      }
    ;

  callingNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        edrString(DETAIL.B_NUMBER)             = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
        edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
    ;

  callOriginator_opt:
      IFW_TAP3.CallOriginator
      {
        callNumberType = callOriginatorType;
      }
      typeOfNumber_opt
      numberingPlan_opt
      callingNumber_opt
      modificationIndicator_opt
      clirIndicator_opt
      IFW_TAP3.Block_END
      {
        //normalize the number
        edrString(DETAIL.B_NUMBER) = convertCli(edrString(DETAIL.B_NUMBER), 
                                                edrString(DETAIL.B_MODIFICATION_INDICATOR), 
                                                edrLong(DETAIL.B_TYPE_OF_NUMBER),
                                                NORM_NAC,
                                                calledNumberAnalysisIACarray[0],// NORM_IAC,
                                                calledNumberAnalysisCCarray[0], // NORM_CC,
                                                NORM_IAC_SIGN,
                                                NORM_NDC );
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
      }
    | /* EMPTY */
    ;

  callTypeGroup_opt:
      IFW_TAP3.CallTypeGroup
      IFW_TAP3.CallTypeLevel1
      {
        edrConnectToken(DETAIL.CONNECT_TYPE, "IFW_TAP3.CallTypeLevel1.CALL_TYPE_LEVEL");
      }
      IFW_TAP3.CallTypeLevel2
      {
        edrString(DETAIL.CONNECT_TYPE) = edrString(DETAIL.CONNECT_TYPE)
                                       + longToStr(tokenLong("IFW_TAP3.CallTypeLevel2.CALL_TYPE_LEVEL"));
      }
      IFW_TAP3.CallTypeLevel3
      {
        edrConnectToken(DETAIL.CONNECT_SUB_TYPE, "IFW_TAP3.CallTypeLevel3.CALL_TYPE_LEVEL");
      }
      calledCountryCode_opt
      IFW_TAP3.Block_END
    |
      // for compatibility with before tap0304
      IFW_TAP3.CallType
      {
        edrConnectToken(DETAIL.CONNECT_TYPE, "IFW_TAP3.CallType.CALL_TYPE");
        switch ( tokenString("IFW_TAP3.CallType.CALL_TYPE") )
        {
          case "M":
          {
            edrString(DETAIL.CONNECT_TYPE) = "11";
          }
          break;
          case "N":
          {
            edrString(DETAIL.CONNECT_TYPE) = "12";
          }
          break;
          case "I":
          {
            edrString(DETAIL.CONNECT_TYPE) = "21";
          }
          break;
          case "P":
          {
            edrString(DETAIL.CONNECT_TYPE) = "14";
          }
          break;
          default: 
          {
            edrString(DETAIL.CONNECT_TYPE) = "00";
            logFormat( "unknown IFW_TAP3.CallType (tap0303): "+tokenString("IFW_TAP3.CallType.CALL_TYPE"));
          }
          break;
        }
      }
      callTypeSubtype_opt
    | /* EMPTY */
    ;

  callTypeSubtype_opt:
      IFW_TAP3.CallTypeSubtype
      {
        edrConnectToken(DETAIL.CONNECT_SUB_TYPE, "IFW_TAP3.CallTypeSubtype.CALL_TYPE_SUBTYPE");
      }
    | /* EMPTY */
      {
        edrString(DETAIL.CONNECT_SUB_TYPE) = "0";
      }
    ;
    
  calledCountryCode_opt:
      IFW_TAP3.CalledCountryCode
      {
        edrConnectToken(DETAIL.CALLED_COUNTRY_CODE, "IFW_TAP3.CalledCountryCode.CALLED_COUNTRY_CODE");
      }
    | /* EMPTY */
    ;

  camelCallReference_opt:
      IFW_TAP3.CamelCallReference
      {
        callNumberType = camelCallReferenceType;
      }
      typeOfNumber_opt                
      numberingPlan_opt               
      camelMscAddress_opt
      camelReferenceNumber_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  camelDestination:
      IFW_TAP3.CamelDestination
      {
        callNumberType = camelDestinationType;
      }
      typeOfNumber_opt
      numberingPlan_opt
      IFW_TAP3.AddressStringDigits // camelDestinationNumber
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0) =
                        convertCli(     edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0), 
                                        "00", 
                                        edrLong(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_TYPE_OF_NUMBER, 0),
                                        NORM_NAC,
                                        calledNumberAnalysisIACarray[0],// NORM_IAC,
                                        calledNumberAnalysisCCarray[0], // NORM_CC,
                                        NORM_IAC_SIGN,
                                        NORM_NDC );
      }
      IFW_TAP3.Block_END
    ;

  threeGcamelDestination_opt:
      camelDestination
    | gprsDestination
    | /* EMPTY */
    ;

  camelInitiatedCFIndicator_opt:
      IFW_TAP3.CamelInitiatedCFIndicator
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.CAMEL_INITIATED_CF_INDICATOR, 0,
                        "IFW_TAP3.CamelInitiatedCFIndicator.CAMEL_INITIATED_CF_INDICATOR");
      }
    | /* EMPTY */
    ;

  camelModificationList:
      camelModificationList
      IFW_TAP3.CamelModification
      {
        lastCamelModificationList = lastCamelModificationList + "," +
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
        lastCamelModificationList = "";
      }
    ;

  camelModificationList_opt2:
      camelModificationList
    | /* EMPTY */ //accept empty list
    ;

  camelMscAddress_opt:
      IFW_TAP3.AddressStringDigits         // mscAddress
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
    ;

  camelReferenceNumber_opt:
      IFW_TAP3.CamelCallReferenceNumber
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.CAMEL_REFERENCE_NUMBER, 0, "IFW_TAP3.CamelCallReferenceNumber.CAMEL_CALL_REFERENCE_NUMBER");
      }
    | /* EMPTY */
    ;

  camelServerAddress_opt:
      IFW_TAP3.AddressStringDigits  //camelServerAddress
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
    ;

  camelServiceKey_opt:
      IFW_TAP3.CamelServiceKey
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVICE_KEY, 0, "IFW_TAP3.CamelServiceKey.CAMEL_SERVICE_KEY");
      }
    | /* EMPTY */
    ;

  camelServiceUsed_opt:
      IFW_TAP3.CamelServiceUsed
      {
        service_Type = service_Camel;
        if ( edrAddDatablock( DETAIL.ASS_CAMEL_EXT ) == false ) 
        { 
          String Msg = "failed to add ASS_CAMEL_EXT datablock for EDR "+longToStr(records);
          edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg); //TODO check for consequences
        }
        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)       = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_CAMEL_EXT.RECORD_TYPE, 0)  = extension_CAMEL;
        edrLong(DETAIL.ASS_CAMEL_EXT.RECORD_NUMBER, 0)  = records;

        callNumberType = camelServerType;
      }
      typeOfNumber_opt
      numberingPlan_opt
      camelServerAddress_opt
      IFW_TAP3.CamelServiceLevel
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVICE_LEVEL, 0, "IFW_TAP3.CamelServiceLevel.CAMEL_SERVICE_LEVEL");
      }
      camelServiceKey_opt
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
                strReplace(tokenString("IFW_TAP3.CellId.CELL_ID"), 0, 0, nullFiller);
          }
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.CELL_ID, 0, "IFW_TAP3.CellId.CELL_ID");
          if (nullFiller!="")
          {
            edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0)=
                strReplace(tokenString("IFW_TAP3.CellId.CELL_ID"), 0, 0, nullFiller);
          }
        }
      }
    | /* EMPTY */
    ;

  channelCodingsAcceptable:
      IFW_TAP3.ChannelCodingsAcceptable
      channelCodingsList
      IFW_TAP3.Block_END
    ;

  channelCodingsAcceptable_opt:
      channelCodingsAcceptable
    | /* EMPTY */
    ;

  channelCodingsList: 
      channelCodingsList 
      IFW_TAP3.ChannelCoding
    | IFW_TAP3.ChannelCoding
    ;

  chargeableUnits_opt:
      IFW_TAP3.ChargeableUnits
      {
        lastChargeableUnits = tokenLong("IFW_TAP3.ChargeableUnits.CHARGEABLE_UNITS");
        edrConnectToken(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, CPidx, "IFW_TAP3.ChargeableUnits.CHARGEABLE_UNITS");
//        edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, CPidx)= longToDecimal(lastChargeableUnits); //TODO CONNECT
      }
    | /* EMPTY */
      {
        lastChargeableUnits = 0;
      }
    ;
    
  chargeableSubscriber:
      simChargeableSubscriber
    | minChargeableSubscriber
    ;

  chargedUnits_opt:
      IFW_TAP3.ChargedUnits
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, CPidx, "IFW_TAP3.ChargedUnits.CHARGED_UNITS");
        lastChargedUnits = tokenLong("IFW_TAP3.ChargedUnits.CHARGED_UNITS");
      }
    | /* EMPTY */
      {
        lastChargedUnits = 0;
      }
    ;

  chargeDetail:
      IFW_TAP3.ChargeDetail
      {
        successiveChargeDetail = successiveChargeDetail +1;
//logStdout("successive chargeDetail block number "+longToStr(successiveChargeDetail)+" for chargeInformation"+longToStr(successiveChargeInformation)+" for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER))+"\n");
        initializeChargeDetailTempFields();

        // add the CP(s) for BasicServiceUsed / GprsServiceUsed / CamelServiceUsed / VasServiceUsed / MSSrecord / SCUrecord
//        if ( (service_Type == service_Basic) or (service_Type == service_Gprs) or (service_Type == service_Camel) or (service_Type == service_Vas) or
//             (record_Type == record_SCU) or (service_Type == service_Suppl) or (record_Type == record_CONT)
//           )
        {
          if ( edrAddDatablock( DETAIL.ASS_CBD.CP ) == false ) 
          {
            String Msg ="failed to add CHARGE_PACKET datablock " + longToStr(successiveChargeDetail) +
                        " for ASS_CBD " + longToStr(successiveChargeInformation) +
                        " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
            edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
          }
          CPidx                    = successiveChargePacket;
          successiveChargePacket   = successiveChargePacket   +1;
          successiveChargePacketCI = successiveChargePacketCI +1;

          records = records+1;
          edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)          = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
          edrString(DETAIL.ASS_CBD.CP.RECORD_TYPE, 0, CPidx) = extension_CP;
          edrLong(DETAIL.ASS_CBD.CP.RECORD_NUMBER, 0, CPidx) = records;
        }
        //defaults
        edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)          = "R";
        edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, 0, CPidx)     = "*";
        edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)        = "S";
        edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, 0, CPidx)            = "N";
        edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, CPidx)  = "R";
        edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, 0, CPidx)  = "N";
        edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)          = "W";
      }
      chargeType_opt
      charge_opt
      chargeableUnits_opt
      chargedUnits_opt
      chargeDetailTimeStamp_opt
      IFW_TAP3.DayCategory
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx,"IFW_TAP3.DayCategory.DAY_CATEGORY");
      }
      dayCategorySubtype_opt
      IFW_TAP3.TimeBand
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx,"IFW_TAP3.TimeBand.TIME_BAND");
      }
      timeBandSubtype_opt
      multiRateIndicator_opt
      {
        // add the CP(s) for BasicServiceUsed / GprsServiceUsed / CamelServiceUsed / VasServiceUsed / MSSrecord / SCUrecord
//        if ( (service_Type == service_Basic) or (service_Type == service_Gprs) or (service_Type == service_Camel) or (service_Type == service_Vas) or
//             (record_Type == record_SCU) or (service_Type == service_Suppl) or (record_Type == record_CONT)
//           )
        {
          // Store the collected data
          Decimal ChargedAmountValue = (lastCharge * lastExchangeRateFactor); //after discount, before tax
          edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, CPidx)  = ChargedAmountValue ; // connected in block charge_opt

          edrString(DETAIL.ASS_CBD.CP.RUM, 0, CPidx)                    = lastChargedItem; //cannot be connected !!

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
            edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= theLocalCurrency;
            edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)         = (1.0 / lastExchangeRateFactorValue); //connected in block exchangeRateCode_opt
            edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)      = theTapCurrency;
          }
          else
          {
            edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= theTapCurrency;
            edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)         = lastExchangeRateFactorValue; //connected in block exchangeRateCode_opt
            edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)      = theLocalCurrency;
          }

          edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, CPidx)   = strToDate(lastChargeDetailTimeStamp);//cannot be connected

          if ( service_Type == service_Vas )
          {
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)     = getVasShortDesc( lastVasCode );
          }
          else if ( service_Type == service_Camel )
          {
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)     = "CAMEL";
          }

          // summing of values to store afterwards on the DETAIL level
          sumChargedAmountValueCI = sumChargedAmountValueCI     + ChargedAmountValue;
          sumChargeableUnitsCI    = sumChargeableUnitsCI        + lastChargeableUnits;
          sumChargedUnitsCI       = sumChargedUnitsCI           + lastChargedUnits;
          if      (lastChargedItem == "D") //Duration
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx) = "SEC";
          }
          else if ( (lastChargedItem == "V") or (lastChargedItem == "X") ) //Volume sent / Volume global
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx) = "BYT";
          }
          else if (lastChargedItem == "W") //Volume received
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx) = "BYT";
          }
          else if (lastChargedItem == "E") //Event
          {
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx) = "CLK";
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

  chargeInformation:
      IFW_TAP3.ChargeInformation
      {
        successiveChargeInformation     = successiveChargeInformation +1;
        initializeChargeDetailTempFields();
        successiveChargeDetail          = 0;
        successiveChargePacketCI        = 0;

        lastCPidx_00                    = (-1); //invalid, ie. not received
        lastChargedAmountValue_00       = 0.0;
        lastChargeableUnits_00          = 0;
        lastChargedUnits_00             = 0;
        
        sumTaxChargeCI                  = 0.0;
        sumChargedAmountValueCI         = 0.0;
        sumChargeableUnitsCI            = 0;
        sumChargedUnitsCI               = 0;
        
//logStdout("successive chargeInformation block number "+longToStr(successiveChargeInformation)+" for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER))+"\n");
        
        // create only one ASS_CBD per BasicServiceUsed / GprsServiceUsed / MSSrecord / SCUrecord / VASrecord / CONTrecord
        if ( (service_Type == service_Basic) or (service_Type == service_Gprs) or
             (record_Type == record_MSS) or (record_Type == record_SCU) or (record_Type == record_VAS) or (record_Type == record_CONT)
           )
        {
          if (successiveChargeInformation == 1)
          {
            if ( edrAddDatablock( DETAIL.ASS_CBD ) == false ) 
            { 
              String Msg = "failed to add ASS_CBD datablock "+longToStr(successiveChargeInformation)+
                           " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
              edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
            }
            records = records+1;
            edrLong( DETAIL.NUMBER_ASSOCIATED_RECORDS)= edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
            edrString( DETAIL.ASS_CBD.RECORD_TYPE, 0) = extension_CBD;
            edrLong( DETAIL.ASS_CBD.RECORD_NUMBER, 0) = records;  
          }
        }
      }
      IFW_TAP3.ChargedItem
      {
        lastChargedItem = tokenString("IFW_TAP3.ChargedItem.CHARGED_ITEM");
      }
      exchangeRateCode_opt
      callTypeGroup_opt
      IFW_TAP3.ChargeDetailList
      chargeDetailList
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
              edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE,       0, lastCPidx_00) = "A";
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
              edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
            }
            CPidx                    = successiveChargePacket;
            successiveChargePacket   = successiveChargePacket   +1;
            successiveChargePacketCI = successiveChargePacketCI +1;

            records = records+1;
            edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)          = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
            edrString(DETAIL.ASS_CBD.CP.RECORD_TYPE, 0, CPidx) = extension_CP;
            edrLong(DETAIL.ASS_CBD.CP.RECORD_NUMBER, 0, CPidx) = records;

            // flag the original aggregation packet as not aggregation CP and as duplicate
            edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, lastCPidx_00) = "A";
            edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, lastCPidx_00) = ""; //so that it is not recorgnized by the output

            //defaults
//          edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)        = "R"; //default is overwritten a few lines after
            edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, 0, CPidx)   = "*";
//          edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)      = "S";
            edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, 0, CPidx)          = "N";
            edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, CPidx)= "R";
            edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, 0, CPidx)= "N";
            // duplicated
            edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)        = "W";
            edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)      = "A";
            edrString(DETAIL.ASS_CBD.CP.RUM, 0, CPidx)                  = edrString(DETAIL.ASS_CBD.CP.RUM, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, CPidx)      = "00";
            edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, CPidx)= edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, lastCPidx_00) ;
            edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, CPidx)= edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, lastCPidx_00);
            edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, CPidx)= edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, lastCPidx_00);
            edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)       = edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)    = edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, lastCPidx_00);
            edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, CPidx)= edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx)             = edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx)   = edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)     = edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx) = edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, lastCPidx_00);
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
            edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
          }
          CPidx                    = successiveChargePacket;
          successiveChargePacket   = successiveChargePacket   +1;
          successiveChargePacketCI = successiveChargePacketCI +1;

          records = records+1;
          edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)          = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
          edrString(DETAIL.ASS_CBD.CP.RECORD_TYPE, 0, CPidx) = extension_CP;
          edrLong(DETAIL.ASS_CBD.CP.RECORD_NUMBER, 0, CPidx) = records;

          Long prevCPidx           = CPidx -1 ; //the last one added is used as sample
          //defaults
//        edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)          = "R"; //default is overwritten a few lines after
          edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, 0, CPidx)     = "*";
//        edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)        = "S";
          edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, 0, CPidx)            = "N";
          edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, CPidx)  = "R";
          edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, 0, CPidx)  = "N";
          // generated
          edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)          = "W";
          edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)        = "A";
          edrString(DETAIL.ASS_CBD.CP.RUM, 0, CPidx)                    = edrString(DETAIL.ASS_CBD.CP.RUM, 0, prevCPidx);
          edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, CPidx)        = "00";
          edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, CPidx)  = sumChargedAmountValueCI ;
          edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, CPidx)        = longToDecimal(sumChargedUnitsCI);
          edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, CPidx)     = longToDecimal(sumChargeableUnitsCI);
          edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, prevCPidx);
          edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)         = edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, prevCPidx);
          edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)      = edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, prevCPidx);
          edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, CPidx) = edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, prevCPidx);
          if (successiveChargePacketCI == 2)
          {
            edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx)             = edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, prevCPidx);
            edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx)   = edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, prevCPidx);
          }
          else
          {
            edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx)             = "N";
            edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx)   = "I";
          }
          edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)       = edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, prevCPidx);
          edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx)   = edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, prevCPidx);
        }
      }
      IFW_TAP3.Block_END
      taxInformationList_opt
      {
        // increment the EDR and File counters for Blocks taken into account
        if (successiveChargePacketCI >= 1)// packets were created for this CI
        {
          sumTaxChargeEDR = sumTaxChargeEDR  + sumTaxChargeCI;
          sumTaxChargeFile= sumTaxChargeFile + sumTaxChargeCI;
        }
        // increment the counter for every TaxCharge (for statistcs and checks)
        sumTaxChargeFileAll= sumTaxChargeFileAll + sumTaxChargeCI;
      }
      discountInformation_opt
      {
        if (successiveChargePacketCI >= 1)// packets were created for this CI
        {
          // if there is a CP to store this info, use it
//        edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, 0, successiveChargePacket-1)= (lastDiscountValue * lastExchangeRateFactor);
          edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, 0, CPidx)= (lastDiscountValue * lastExchangeRateFactor);
        }
      }
      IFW_TAP3.Block_END
    ;

  chargeInformation_opt:
      chargeInformation
    | /* EMPTY */
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
      chargeInformationList chargeInformation
    | chargeInformation
    ;

  chargeType_opt:
      IFW_TAP3.ChargeType
      {
        edrConnectToken(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, CPidx, "IFW_TAP3.ChargeType.CHARGE_TYPE");
        lastChargeType = tokenString("IFW_TAP3.ChargeType.CHARGE_TYPE");
      }
    | /* EMPTY */
      {
        lastChargeType = "";
      }
    ;

  charge_opt:
      IFW_TAP3.Charge
      {
        // NB: charge after discount, but before tax
        edrConnectToken(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, CPidx, "IFW_TAP3.Charge.CHARGE");
        lastCharge = (longToDecimal(tokenLong("IFW_TAP3.Charge.CHARGE")) / theAbsoluteAmountDivider);
      }
    | /* EMPTY */
      {
        lastCharge = 0.0;
      }
    ;

  chargingCharacteristics_opt:
      IFW_TAP3.ChargingCharacteristics
    | /* EMPTY */
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

  clirIndicator_opt:
      IFW_TAP3.ClirIndicator
    | /* EMPTY */
    ;

  countryCode:
      IFW_TAP3.CountryCode
      {
        lastCalledNumberAnalysisCC                       = tokenString("IFW_TAP3.CountryCode.COUNTRY_CODE");
        calledNumberAnalysisCCarray[lastCode][lastCcIdx] = tokenString("IFW_TAP3.CountryCode.COUNTRY_CODE");
        lastCcIdx                                        = lastCcIdx + 1;
      }
    ;

  countryCodeList:
      countryCodeList countryCode
    | countryCode
    ;

  countryCodeTable:
      IFW_TAP3.CountryCodeTable
      {
        lastCcIdx = 0;
      }
      countryCodeList
      IFW_TAP3.Block_END
    ;

  cseInformation_opt:
      IFW_TAP3.CseInformation
      {
        edrConnectToken(DETAIL.ASS_CAMEL_EXT.CSE_INFORMATION, 0, "IFW_TAP3.CseInformation.CSE_INFORMATION");
      }
    | /* EMPTY */
    ;
    

  currencyConversion_opt:
      IFW_TAP3.CurrencyConversion
      exchangeRateDefinitionList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  dataVolumeReference_opt:
      IFW_TAP3.DataVolumeReference
    | /* EMPTY */
    ;

  dateTime:    // Missing DateTime in files
      IFW_TAP3.LocalTimeStamp
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
        switch (timeStampType)
        {
          case(callEventStartTimeStampType):
          {
            edrConnectToken(DETAIL.CHARGING_START_TIMESTAMP, "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
            edrConnectToken(DETAIL.CHARGING_END_TIMESTAMP,   "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
          }
          break;
          case(chargingTimeStampType):
          {
            if ( ( (service_Type == service_Basic) or (service_Type == service_Gprs) ) or
                 ( (record_Type == record_MSS) or (record_Type == record_SCU) or (record_Type == record_VAS))
               )
            {
              // replace the default Tap3Detail level Timestamp
              edrConnectToken(DETAIL.CHARGING_START_TIMESTAMP, "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
              edrConnectToken(DETAIL.CHARGING_END_TIMESTAMP,   "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
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
            edrConnectToken(DETAIL.CHARGING_END_TIMESTAMP,   "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
          }
          break;
          case(chargeDetailTimeStampType):
          {
            //cannot be connected because CP is not yet created !!!
            //edrConnectToken(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, CPidx, "IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");//cannot be connected
          }
          break;
          default:
          break;
        }
      }
      IFW_TAP3.UtcTimeOffsetCode
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
            if ( ( (service_Type == service_Basic) or (service_Type == service_Gprs) ) or
                 ( (record_Type == record_MSS) or (record_Type == record_SCU) or (record_Type == record_VAS))
               )
            {
              // replace the default Tap3Detail level Timestamp
              edrConnectToken(DETAIL.UTC_TIME_OFFSET, "IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
              edrString(DETAIL.UTC_TIME_OFFSET) = lastUtcTimeOffset;
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
          default:
          break;
        }
      }
    | IFW_TAP3.DateTime
      IFW_TAP3.LocalTimeStamp
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      IFW_TAP3.UtcTimeOffsetCode    
      {
        // get the corresponding UtcTimeOffset from the UtcTimeOffsetCode
        lastUtcTimeOffset  = getUtcTimeOffset( tokenLong("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE") );
      }
      IFW_TAP3.Block_END
    ;

  dateTimeLong: // Missing DateTimeLong in files
      IFW_TAP3.LocalTimeStamp
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      IFW_TAP3.UtcTimeOffset
      {
        lastUtcTimeOffset = tokenString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET");
      }
    | IFW_TAP3.DateTimeLong
      IFW_TAP3.LocalTimeStamp
      {
        lastLocalTimeStamp = tokenString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP");
      }
      IFW_TAP3.UtcTimeOffset    
      {
        lastUtcTimeOffset = tokenString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET");
      }
      IFW_TAP3.Block_END
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
    ;  

  destination:
      IFW_TAP3.Destination
      {
        callNumberType = callDestinationType;
      }
      typeOfNumber_opt
      numberingPlan_opt
      calledNumber_opt
      modificationIndicator_opt
      calledPlace_opt
      calledRegion_opt
      calledNumAnalysisCode_opt
      IFW_TAP3.Block_END
      {
        //normalize the number
        edrString(DETAIL.B_NUMBER) = convertCli(edrString(DETAIL.B_NUMBER), 
                                                edrString(DETAIL.B_MODIFICATION_INDICATOR), 
                                                edrLong(DETAIL.B_TYPE_OF_NUMBER),
                                                NORM_NAC,
                                                calledNumberAnalysisIACarray[getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)],// NORM_IAC,
                                                calledNumberAnalysisCCarray[ getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)],// NORM_CC,
                                                NORM_IAC_SIGN,
                                                NORM_NDC );
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
        lastCalledNumAnalysisCode = 1;
      }
    ;

  destination_opt:
      destination
    | /* EMPTY */
    ;  
    
  destinationNetwork_opt:
      IFW_TAP3.DestinationNetwork
      {
        edrConnectToken(DETAIL.DESTINATION_NETWORK, "IFW_TAP3.DestinationNetwork.NETWORK_ID");
      }
    | /* EMPTY */
    ;  

  discounting_opt:
      IFW_TAP3.Discounting
      discountDefinitionList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;  

  discountApplied:
      IFW_TAP3.DiscountValue
      {
        discountApplied_Type[lastCode] = discountApplied_fixedDiscountValue;
        discountApplied[lastCode]      = tokenLong("IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT");
      }
    | IFW_TAP3.DiscountRate
      {
        discountApplied_Type[lastCode] = discountApplied_discountRate;
        discountApplied[lastCode]      = tokenLong("IFW_TAP3.DiscountRate.PERCENTAGE_RATE");
      }
    ;

  discountDefinitionList:
      discountDefinitionList
      discountDefinition
    | discountDefinition
    ;

  discountDefinition:
      IFW_TAP3.DiscountDefinition
      IFW_TAP3.DiscountCode
      {
        lastCode               = tokenLong("IFW_TAP3.DiscountCode.DISCOUNT_CODE");
        discountCode[lastCode] = lastCode;
      }
      discountApplied
      {
        if (discountEntries <= lastCode)
        {
          discountEntries     = lastCode + 1;
        }
      }
      IFW_TAP3.Block_END
    ;

  discountInformation:
      IFW_TAP3.DiscountInformation
      IFW_TAP3.DiscountCode
      {
        lastDiscountCode = tokenLong("IFW_TAP3.DiscountCode.DISCOUNT_CODE");
        if (getDiscountAppliedType(lastDiscountCode) == discountApplied_fixedDiscountValue)
        {
          edrConnectToken(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, 0, CPidx, "IFW_TAP3.DiscountCode.DISCOUNT_CODE");
        }
        // in case of discountApplied_discountRate, the DiscountValue is mandatory.
      }
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
        edrConnectToken(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, 0, CPidx, "IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT");
        lastDiscountValue = ( longToDecimal(tokenLong("IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT")) / theAbsoluteAmountDivider);
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
    ;

  exchangeRateCode_opt:
      IFW_TAP3.ExchangeRateCode
      {
        lastExchangeRateFactorValue     = getExchangeRateFactor( tokenLong("IFW_TAP3.ExchangeRateCode.CODE") );
        edrConnectToken(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx, "IFW_TAP3.ExchangeRateCode.CODE");
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
      }
    ;
 
  exchangeRateDefinitionList:
      exchangeRateDefinitionList
      exchangeRateDefinition
    | exchangeRateDefinition
    ;

  exchangeRateDefinition:
      IFW_TAP3.ExchangeRateDefinition
      IFW_TAP3.ExchangeRateCode
      {
        lastCode                        = tokenLong("IFW_TAP3.ExchangeRateCode.CODE");
        exchangeRateCode[lastCode]      = lastCode;
      }
      IFW_TAP3.NumberOfDecimalPlaces
      {
        numberOfDecimalPlaces[lastCode] = tokenLong("IFW_TAP3.NumberOfDecimalPlaces.NUMBER_OF_DECIMAL_PLACES");
      }
      IFW_TAP3.ExchangeRate
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

  fileAvailableTimeStamp_opt:
      fileAvailableTimeStamp
      {
        edrDate(HEADER.TRANSMISSION_DATE) = strToDate(theFileAvailableTimeStamp);
      }
    | /* EMPTY */
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

  fileCreationTimeStamp_opt:
      fileCreationTimeStamp
      {
        edrDate(HEADER.CREATION_TIMESTAMP) = strToDate(theFileCreationTimeStamp);
        edrString(HEADER.UTC_TIME_OFFSET)  = theFileCreationUtcTimeOffset;
      }
    | /* EMPTY */
    ;

  fileTypeIndicator_opt:
      IFW_TAP3.FileTypeIndicator
      {
        theFileTypeIndicator = tokenString("IFW_TAP3.FileTypeIndicator.FILE_TYPE_INDICATOR");    
      }
    | /* EMPTY */
      {
        theFileTypeIndicator = "";
      }
    ;

  fraudMonitorIndicator_opt:
      IFW_TAP3.FraudMonitorIndicator
    | /* EMPTY */
    ;

  fnur_opt:
      IFW_TAP3.Fnur
    | /* EMPTY */
    ;

  geographicalLocation_opt:
      IFW_TAP3.GeographicalLocation
      servingNetwork_opt
      servingBid_opt
      servingLocationDescription_opt
      longitude_opt
      latitude_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  gprsBasicCallInformation:     
      IFW_TAP3.GprsBasicCallInformation
      fraudMonitorIndicator_opt
      gprsChargeableSubscriber
      rapFileSequenceNumber_opt
      networkType_opt
      gprsDestination
      callEventStartTimeStamp
      totalCallEventDuration
      causeForTerm_opt
      partialTypeIndicator_opt
      pDPContextStartTimestamp_opt
      networkInitPDPContext_opt
      IFW_TAP3.ChargingId
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0, "IFW_TAP3.ChargingId.CHARGING_ID");
//      edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0) = decimalToStr(tokenDecimal("IFW_TAP3.ChargingId.CHARGING_ID"),0); //TODO CONNECT
        //edrString(DETAIL.CHAIN_REFERENCE)  = edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0); //TODO activate for GPRS callAssembly
      }
      IFW_TAP3.Block_END
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
      IFW_TAP3.TypeOfControllingNode
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
      gprsBasicCallInformation
      gprsLocationInformation
      equipmentInformation_opt
      gprsServiceUsed
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
        edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)      = "I"; //I=IMSI , M=MSISDN, P=IP , S=SIM , ...
      }
      msisdn_opt
    ;
    
  gprsChargeableSubscriber:
      IFW_TAP3.GprsChargeableSubscriber
      chargeableSubscriber_GprsCompatibility
      IFW_TAP3.PdpType
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.PDP_TYPE, 0, "IFW_TAP3.PdpType.PDP_TYPE");      
//      edrString(DETAIL.ASS_GPRS_EXT.PDP_TYPE, 0)      = longToStr( tokenLong("IFW_TAP3.PdpType.PDP_TYPE") );
      }
      pdpAddress_opt
      chargingCharacteristics_opt
      IFW_TAP3.Block_END
    ;

  pdpAddress_opt:
      IFW_TAP3.PdpAddress
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.PDP_ADDRESS, 0, "IFW_TAP3.PdpAddress.PDP_ADDRESS");
      }
    | /* EMPTY */
    ;

  accessPointNameOI_opt:
      IFW_TAP3.AccessPointNameOI
      {
        lastAPN = lastAPN +","+ tokenString("IFW_TAP3.AccessPointNameOI.ACCESS_POINT_NAME_OI");
      }
    | /* EMPTY */
    ;

  AccessPointName_GprsCompatibility:
      IFW_TAP3.AccessPointNameNI
      {
        lastAPN = tokenString("IFW_TAP3.AccessPointNameNI.ACCESS_POINT_NAME_NI");
      }
      accessPointNameOI_opt
    | IFW_TAP3.AccessPointName // for compatibility with before tap0304
      {
        lastAPN = tokenString("IFW_TAP3.AccessPointName.ACCESS_POINT_NAME");
      }
    ;
    
  gprsDestination:
      IFW_TAP3.GprsDestination
      AccessPointName_GprsCompatibility
      remotePdpAddressList_opt
      {
        if (service_Type == service_Camel)
        {
          edrString(DETAIL.ASS_CAMEL_EXT.DEST_GPRS_APN_ADDRESS, 0)       = lastAPN ;
          edrString(DETAIL.ASS_CAMEL_EXT.DEST_GPRS_PDP_REMOTE_ADDRESS, 0)= lastRemotePdpAddressList ;
        }
        else
        {
          edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)       = lastAPN ;
          edrString(DETAIL.ASS_GPRS_EXT.PDP_REMOTE_ADDRESS, 0)= lastRemotePdpAddressList ;
        }
      }
      IFW_TAP3.Block_END
    ;

  gprsLocationInformation:
      IFW_TAP3.GprsLocationInformation
      gprsNetworkLocation
      homeLocationInformation_opt
      geographicalLocation_opt
      IFW_TAP3.Block_END
    ;

  gprsNetworkLocation:
      IFW_TAP3.GprsNetworkLocation
      IFW_TAP3.RecEntityCodeList
      recEntityCodeList
      IFW_TAP3.Block_END
      locationArea_opt
      cellId_opt
      IFW_TAP3.Block_END
    ;

  gprsServiceUsage:
      IFW_TAP3.GprsServiceUsage
      chargingTimeStamp_opt
      qoSRequested_opt
      qoSUsed
      IFW_TAP3.DataVolumeIncoming
      {
        edrConnectToken(DETAIL.VOLUME_RECEIVED, "IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING");
        sumDataVolumeIncoming  = sumDataVolumeIncoming +
                                 longToDecimal(tokenLong("IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING"));
      }
      IFW_TAP3.DataVolumeOutgoing
      {
        edrConnectToken(DETAIL.VOLUME_SENT, "IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING");
        sumDataVolumeOutgoing  = sumDataVolumeOutgoing +
                                 longToDecimal(tokenLong("IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING"));
      }
      IFW_TAP3.Block_END
    ;

  gprsServiceUsageList:
      gprsServiceUsageList gprsServiceUsage
    | gprsServiceUsage
    ;

  gprsServiceUsed:
      IFW_TAP3.GprsServiceUsed
      {
        service_Type                    = service_Gprs;
        // initialise the counters of volume (different block for each QoS)
        sumDataVolumeIncoming           =0.0;
        sumDataVolumeOutgoing           =0.0;
      }
      IFW_TAP3.GprsServiceUsageList
      gprsServiceUsageList
      IFW_TAP3.Block_END
      {
        edrDecimal(DETAIL.VOLUME_RECEIVED) = sumDataVolumeIncoming;
        edrDecimal(DETAIL.VOLUME_SENT)     = sumDataVolumeOutgoing;
      }
      chargingTimeStamp_opt
      {
        initializeChargeInfoTempFields();
      }
      IFW_TAP3.ChargeInformationList
      chargeInformationList
      IFW_TAP3.Block_END
      {
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      IFW_TAP3.Block_END
    ;
   
  homeBid_opt:
      IFW_TAP3.HomeBid
    | /* EMPTY */
    ;
  
  homeLocationInformation_opt:
      IFW_TAP3.HomeLocationInformation
      homeBid_opt
      locationDescr_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  locationDescr_opt:
      IFW_TAP3.LocationDescription
    | /* EMPTY */
    ;

  hSCSDInformation:
      IFW_TAP3.HSCSDInformation
      basicHSCSDParameters
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
      aiurRequested_opt
      numberOfChannels_opt
      IFW_TAP3.ChannelCoding
      IFW_TAP3.NumberOfChannelsUsed
      IFW_TAP3.InitiatingParty
      IFW_TAP3.ModificationTimestamp
      {
        timeStampType = hscsdModificationTimestampType;
      }
      dateTime
      IFW_TAP3.Block_END
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

  iacList:
      iacList iac
    | iac
    ;

  iacTable:
      IFW_TAP3.IacTable
      {
        lastIacIdx = 0;
      }
      iacList
      IFW_TAP3.Block_END
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
    | /* EMTPY */
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
                strReplace(tokenString("IFW_TAP3.LocationArea.LOCATION_AREA"), 0, 0, nullFiller);
          }
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0, "IFW_TAP3.LocationArea.LOCATION_AREA") ;
          if (nullFiller!="")
          {
            edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0)=
                strReplace(tokenString("IFW_TAP3.LocationArea.LOCATION_AREA"), 0, 0, nullFiller);
          }
        }
      }
    | /* EMTPY */
    ;

  locationDescription_opt:
      IFW_TAP3.LocationDescription
    | /* EMTPY */
    ;

  locationInformation:
      IFW_TAP3.LocationInformation
      networkLocation
      homeLocationInformation_opt
      geographicalLocation_opt
      IFW_TAP3.Block_END
    ;

  longitude_opt:
      IFW_TAP3.Longitude
    | /* EMTPY */
    ;

  mdn_opt:
      IFW_TAP3.Mdn
    | /* EMPTY */
    ;

  minChargeableSubscriber:
      IFW_TAP3.MinChargeableSubscriber
      IFW_TAP3.Min
      mdn_opt
      IFW_TAP3.Block_END
    | IFW_TAP3.Min  // kept for compatibility with before Tap0304
    ;

  messageDescriptionCode_opt:
      IFW_TAP3.MessageDescriptionCode
      {
        edrString(DETAIL.DESCRIPTION) = getMessageDescription(tokenLong("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE"));
      }
    | /* EMPTY */
    ;

  messageDescriptionDefinition:
      IFW_TAP3.MessageDescriptionDefinition
      IFW_TAP3.MessageDescriptionCode
      {
        lastCode                         = tokenLong("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE");
        messageDescriptionCode[lastCode] = lastCode;
      }
      IFW_TAP3.MessageDescription
      {
        messageDescription[lastCode]     = tokenString("IFW_TAP3.MessageDescription.MESSAGE_DESCRIPTION");
        if (messageDescriptionEntries <= lastCode)
        {
          messageDescriptionEntries      = lastCode + 1;
        }
      }
      IFW_TAP3.Block_END
    ;
 
  messageDescriptionDefinitionList:
      messageDescriptionDefinitionList messageDescriptionDefinition
    | messageDescriptionDefinition
    ;

  messageDescriptionInfo_opt:
      IFW_TAP3.MessageDescriptionInfo
      {
        errorStateTap3 = beginTap3MessageDescrInfo;
      }
      messageDescriptionDefinitionList
      {
        errorStateTap3 = endTap3MessageDescrInfo;
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  moBasicCallInformation:  
      IFW_TAP3.MoBasicCallInformation
      fraudMonitorIndicator_opt
      chargeableSubscriber
      rapFileSequenceNumber_opt
      networkType_opt
      destination_opt
      destinationNetwork_opt
      callEventStartTimeStamp
      totalCallEventDuration
      simToolkitIndicator_opt
      causeForTerm_opt
      IFW_TAP3.Block_END
    ;

  mobileOriginatedCall:
      IFW_TAP3.MobileOriginatedCall
      {
        if ( createNewDetail(record_MOC, type_MOC) == false )
        {
          //TODO something
        }
      }
      moBasicCallInformation
      locationInformation
      equipmentInformation_opt
      {
        // use edrDuplicate() to get a template for every BasicServiceUsed
        theLastEdrCopy = edrDuplicate();
      }
      IFW_TAP3.BasicServiceUsedList
      basicServiceUsedList
      IFW_TAP3.Block_END
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
      mtBasicCallInformation
      locationInformation
      equipmentInformation_opt
      {
        // use edrDuplicate() to get a template for every BasicServiceUsed
        theLastEdrCopy = edrDuplicate();
      }
      IFW_TAP3.BasicServiceUsedList
      basicServiceUsedList
      IFW_TAP3.Block_END
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
    ;

  modificationIndicator_opt:
      IFW_TAP3.ModificationIndicator
      {
        //lastModificationIndicator = tokenLong("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR");
        switch (callNumberType)
        {
          case (callOriginatorType):
          case (callDestinationType):
          case (nonChargedPartyType):
          {
            edrConnectToken(DETAIL.B_MODIFICATION_INDICATOR, "IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR");
            if (tokenLong("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR") > 0)
            {
              edrString(DETAIL.B_MODIFICATION_INDICATOR) = "08";
            }
          }
          break;
          case (thirdPartyType):
          {
            edrConnectToken(DETAIL.C_MODIFICATION_INDICATOR, "IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR");
            if (tokenLong("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR") > 0)
            {
              edrString(DETAIL.C_MODIFICATION_INDICATOR) = "08";
            }
          }
          break;
        }
      }
    | /* EMPTY */
    ;
   

  msisdn_opt:
      IFW_TAP3.Msisdn
      {
        edrString(DETAIL.A_NUMBER) = tokenString("IFW_TAP3.Msisdn.MSISDN");
        edrString(DETAIL.A_NUMBER) = convertCli( edrString(DETAIL.A_NUMBER),
                                                "00", 0,
                                                NORM_NAC,
                                                calledNumberAnalysisIACarray[0],// NORM_IAC,
                                                calledNumberAnalysisCCarray[0], // NORM_CC,
                                                NORM_IAC_SIGN,
                                                NORM_NDC );
        edrString(DETAIL.INTERN_A_NUMBER_ZONE) = edrString(DETAIL.A_NUMBER);
        
        if      (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.A_NUMBER_USER, 0, "IFW_TAP3.Msisdn.MSISDN");
        }
        else if (record_Type == record_MTC)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.Msisdn.MSISDN");
        }
        else if (record_Type == record_SCU)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.Msisdn.MSISDN");
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.Msisdn.MSISDN");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.Msisdn.MSISDN");
        }
      }
    | /* EMPTY */
    ;

  mtBasicCallInformation:
      IFW_TAP3.MtBasicCallInformation
      fraudMonitorIndicator_opt
      chargeableSubscriber
      rapFileSequenceNumber_opt
      networkType_opt
      callOriginator_opt
      originatingNetwork_opt
      callEventStartTimeStamp
      totalCallEventDuration
      simToolkitIndicator_opt
      causeForTerm_opt
      IFW_TAP3.Block_END
    ;

  multiRateIndicator_opt:
      IFW_TAP3.MultiRateIndicator
    | /* EMPTY */
    ;

  networkInfo:
      IFW_TAP3.NetworkInfo
      {
        errorStateTap3 = beginTap3NetworkInfo;
      }
      utcTimeOffsetInfo
      recEntityInfo_opt
      IFW_TAP3.NetworkType
      {
        // here we are in the header, so we are getting info regarding the Sender Network
        theSenderNetworkType = tokenLong("IFW_TAP3.NetworkType.NETWORK_TYPE");
      }
      calledNumAnalysisList_opt
      {
        errorStateTap3 = endTap3NetworkInfo;
      }
      IFW_TAP3.Block_END
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
    | /* EMPTY */
    ;
    
  networkLocation:
      IFW_TAP3.NetworkLocation
      IFW_TAP3.RecEntityCode
      {
        theRecEntityId = getRecEntityId(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
        //theRecEntityType= getRecEntityType(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
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
      callReference_opt
      locationArea_opt
      cellId_opt
      IFW_TAP3.Block_END
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

  nonChargedNumber_opt: // only used for record_SCU
      IFW_TAP3.AddressStringDigits
      {
        if ( edrLong(DETAIL.USAGE_DIRECTION) == 0 )
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        }
        edrString(DETAIL.B_NUMBER) =  tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
    ;

  nonChargedParty_opt:
      IFW_TAP3.NonChargedParty
      {
        callNumberType = nonChargedPartyType;
      }
      typeOfNumber_opt
      numberingPlan_opt
      nonChargedNumber_opt
      calledNumAnalysisCode_opt
      modificationIndicator_opt
      IFW_TAP3.Block_END
      {
        //normalize the number
        edrString(DETAIL.B_NUMBER) = convertCli(edrString(DETAIL.B_NUMBER), 
                                                edrString(DETAIL.B_MODIFICATION_INDICATOR), 
                                                edrLong(DETAIL.B_TYPE_OF_NUMBER),
                                                NORM_NAC,
                                                calledNumberAnalysisIACarray[getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)],// NORM_IAC,
                                                calledNumberAnalysisCCarray[ getCalledNumberAnalysisCodeIdx(lastCalledNumAnalysisCode)], // NORM_CC,
                                                NORM_IAC_SIGN,
                                                NORM_NDC );
        edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
        lastCalledNumAnalysisCode = 1;
      }
    | /* EMPTY */
    ;

  numberingPlan_opt:
      IFW_TAP3.NumberingPlan
      {
        //lastNumberingPlan = tokenLong("IFW_TAP3.NumberingPlan.NUMBERING_PLAN");
        switch (callNumberType)
        {
          case (callOriginatorType):
          case (callDestinationType):
          case (nonChargedPartyType):
          {
            edrConnectToken(DETAIL.B_NUMBERING_PLAN, "IFW_TAP3.NumberingPlan.NUMBERING_PLAN");
          }
          break;
          case (camelCallReferenceType):
          {
            edrConnectToken(DETAIL.ASS_CAMEL_EXT.MSC_NUMBERING_PLAN, 0, "IFW_TAP3.NumberingPlan.NUMBERING_PLAN");
          }
          break;
          case (camelDestinationType):
          {
            edrConnectToken(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBERING_PLAN, 0, "IFW_TAP3.NumberingPlan.NUMBERING_PLAN");
          }
          break;
          case (camelServerType):
          {
            edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVER_NUMBERING_PLAN, 0, "IFW_TAP3.NumberingPlan.NUMBERING_PLAN");
          }
          break;
          case (thirdPartyType):
          {
            edrConnectToken(DETAIL.C_NUMBERING_PLAN, "IFW_TAP3.NumberingPlan.NUMBERING_PLAN");
          }
          break;
        }
      }
    | /* EMPTY */
    ;

  numberOfChannels_opt:
      IFW_TAP3.NumberOfChannels
    | /* EMPTY */
    ;

  operatorSpecInformation_opt:
      IFW_TAP3.OperatorSpecInfoList
      operatorSpecInformationList_opt
      IFW_TAP3.Block_END
    | IFW_TAP3.OperatorSpecInformation // compatibility for before tap0304
      {
        storeTheOperatorSpecInformation();
      }
    | /* EMPTY */
    ;
    
  operatorSpecInformationList_opt:
      operatorSpecInformationList
    | /* EMPTY */
    ;

  operatorSpecInformationList:
      operatorSpecInformationList
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

  qoSRequested_opt:
      IFW_TAP3.GSMQoSRequested
      IFW_TAP3.QoSDelay
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_DELAY, 0, "IFW_TAP3.QoSDelay.QOS_INTEGER");
      }
      IFW_TAP3.QoSMeanThroughput
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_MEAN_THROUGHPUT, 0, "IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPeakThroughput
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PEAK_THROUGHPUT, 0, "IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPrecedence
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PRECEDENCE, 0, "IFW_TAP3.QoSPrecedence.QOS_INTEGER");
      }
      IFW_TAP3.QoSReliability
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_RELIABILITY, 0, "IFW_TAP3.QoSReliability.QOS_INTEGER");
      }
      IFW_TAP3.Block_END
    |
      IFW_TAP3.UMTSQoSRequested
      IFW_TAP3.QoSTrafficClass
      IFW_TAP3.QoSMaxBitRateUplink
      IFW_TAP3.QoSMaxBitRateDownlink
      IFW_TAP3.QoSDeliveryOrder
      IFW_TAP3.QoSMaxSDUsize
      IFW_TAP3.QoSSDUErrorRatio
      IFW_TAP3.QoSResidualBER
      IFW_TAP3.QoSErroneousSDUs
      IFW_TAP3.QoSTransferDelay
      IFW_TAP3.QoSHandlingpriority
      IFW_TAP3.QoSAllocRetenPriority
      IFW_TAP3.Block_END
    |
      // for compatibility with before tap0304
      IFW_TAP3.QoSRequested
      IFW_TAP3.QoSDelay
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_DELAY, 0, "IFW_TAP3.QoSDelay.QOS_INTEGER");
      }
      IFW_TAP3.QoSMeanThroughput
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_MEAN_THROUGHPUT, 0, "IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPeakThroughput
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PEAK_THROUGHPUT, 0, "IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPrecedence
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PRECEDENCE, 0, "IFW_TAP3.QoSPrecedence.QOS_INTEGER");
      }
      IFW_TAP3.QoSReliability
      {
        edrConnectToken(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_RELIABILITY, 0, "IFW_TAP3.QoSReliability.QOS_INTEGER");
      }
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  qoSUsed:
      IFW_TAP3.GSMQoSUsed
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
    |
      IFW_TAP3.UMTSQoSUsed
      IFW_TAP3.QoSTrafficClass
      IFW_TAP3.QoSMaxBitRateUplink
      IFW_TAP3.QoSMaxBitRateDownlink
      IFW_TAP3.QoSDeliveryOrder
      IFW_TAP3.QoSMaxSDUsize
      IFW_TAP3.QoSSDUErrorRatio
      IFW_TAP3.QoSResidualBER
      IFW_TAP3.QoSErroneousSDUs
      IFW_TAP3.QoSTransferDelay
      IFW_TAP3.QoSHandlingpriority
      IFW_TAP3.QoSAllocRetenPriority
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
    ;

  rapFileSequenceNumber_opt:
      IFW_TAP3.RapFileSequenceNumber
    | /* EMPTY */
    ;

  radioChannelRequested_opt:
      IFW_TAP3.RadioChannelRequested
      {
        edrConnectToken(DETAIL.QOS_REQUESTED, "IFW_TAP3.RadioChannelRequested.RADIO_CHANNEL_REQUESTED");
      }
    | /* EMPTY */
    ;

  radioChannelUsed_opt:
      IFW_TAP3.RadioChannelUsed
      {
        edrConnectToken(DETAIL.QOS_USED, "IFW_TAP3.RadioChannelUsed.RADIO_CHANNEL_USED");
      }
    | /* EMPTY */
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
          edrString(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0) = getRecEntityId(  tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE") );
        }
        else
        {
          String Msg = "getRecEntityType("+longToStr(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"))+"), !=GGSN and !=SGSN";
          edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
        }
      }
    ;

  recEntityDefinition:
      IFW_TAP3.RecEntityDefinition
      IFW_TAP3.RecEntityCode
      {
        lastCode                   = tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE");
        recEntityCode[lastCode]    = lastCode;
      }
      IFW_TAP3.RecEntityType
      {
        recEntityType[lastCode]    = tokenLong("IFW_TAP3.RecEntityType.REC_ENTITY_TYPE");
      }
      recEntityId
      {
        recEntityId_Type[lastCode] = last_recEntityId_Type;
        recEntityId[lastCode]      = last_recEntityId;
        if (recEntityEntries <= lastCode)
        {
          recEntityEntries         = lastCode + 1;
        }
      }
      IFW_TAP3.Block_END
    ;

  recEntityDefinitionList:
      recEntityDefinitionList
      recEntityDefinition
    | /* EMPTY */
    ;

  recEntityId:
      IFW_TAP3.MscId
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

  recEntityInfo_opt:
      IFW_TAP3.RecEntityTable
      recEntityDefinitionList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  remotePdpAddressList:
      remotePdpAddressList
      packetDataProtocollAddress
      {
        lastRemotePdpAddressList = lastRemotePdpAddressList + "," +
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
      scuVasChargeableSubscriber
      IFW_TAP3.ChargedPartyStatus
      {
        edrConnectToken(DETAIL.USAGE_DIRECTION, "IFW_TAP3.ChargedPartyStatus.CHARGED_PARTY_STATUS");
      }
      nonChargedParty_opt
      clirIndicator_opt
      originatingNetwork_opt
      destinationNetwork_opt
      IFW_TAP3.Block_END
    ;

  scuChargeType:
      IFW_TAP3.ScuChargeType
      IFW_TAP3.MessageStatus
      {
        // CALL_COMPLETION_INDICATOR must be stored in a 2 digit string (prepend with 0 if necessary)
        edrConnectToken(DETAIL.CALL_COMPLETION_INDICATOR, "IFW_TAP3.MessageStatus.MESSAGE_STATUS");
        if (tokenLong("IFW_TAP3.MessageStatus.MESSAGE_STATUS") < 10)
        {
          edrString(DETAIL.CALL_COMPLETION_INDICATOR) = "0" + edrString(DETAIL.CALL_COMPLETION_INDICATOR);
        }
      }
      IFW_TAP3.PriorityCode
      {
        edrConnectToken(DETAIL.QOS_REQUESTED, "IFW_TAP3.PriorityCode.PRIORITY_CODE");
      }
      distanceChargeBandCode_opt
      IFW_TAP3.MessageType
      {
        edrConnectToken(DETAIL.QOS_USED, "IFW_TAP3.MessageType.MESSAGE_TYPE"); //TODO find a better storage
      }
      messageDescriptionCode_opt
      IFW_TAP3.Block_END
    ;

  scuTimeStamps:
      IFW_TAP3.ScuTimeStamps
      IFW_TAP3.DepositTimeStamp
      {
        timeStampType = scuDepositTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
      {
        // Mandatory field for SCU, will serve as a default
        lastValidLocalTimeStamp = lastLocalTimeStamp; // to serve as default LocalTimeStamp for coresponding record
        lastValidUtcTimeOffset  = lastUtcTimeOffset;  // to serve as default UtcTimeOffset for coresponding record
        
        // set a real timestamp on the CP if it is missing
        Long i;
        for (i=0 ; i< edrNumDatablocks( DETAIL.ASS_CBD.CP, 0) ; i=i+1)
        {
          if (edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, i) == defLocalTime)
          {
            edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, i) = edrDate(DETAIL.CHARGING_START_TIMESTAMP);
          }
        }
      }
      IFW_TAP3.CompletionTimeStamp
      {
        timeStampType = scuCompletionTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
      IFW_TAP3.ChargingPoint
      IFW_TAP3.Block_END
    ;

  scuVasChargeableSubscriber:
      simChargeableSubscriber
    | IFW_TAP3.Msisdn
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0, "IFW_TAP3.Msisdn.MSISDN");
        if (record_Type == record_SCU)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "IFW_TAP3.Msisdn.MSISDN");
        }
        
        edrString(DETAIL.A_NUMBER) = tokenString("IFW_TAP3.Msisdn.MSISDN");
        edrString(DETAIL.A_NUMBER) = convertCli( edrString(DETAIL.A_NUMBER),
                                                "00", 0,
                                                NORM_NAC,
                                                calledNumberAnalysisIACarray[0],// NORM_IAC,
                                                calledNumberAnalysisCCarray[0], // NORM_CC,
                                                NORM_IAC_SIGN,
                                                NORM_NDC );
        edrString(DETAIL.INTERN_A_NUMBER_ZONE) = edrString(DETAIL.A_NUMBER);
      }
    | IFW_TAP3.Min
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
      scuBasicInformation
      rapFileSequenceNumber_opt
      networkType_opt
      servingNetwork_opt
      IFW_TAP3.RecEntityCode
      {
        edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0) = getRecEntityId(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
        initializeChargeInfoTempFields();
      }
      chargeInformation
      {
        // store the collected chargeInformation data in the corresponding EDR
        storeChargeInfoTempFields();
      }
      scuChargeType
      scuTimeStamps
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  servingNetwork_opt:
      IFW_TAP3.ServingNetwork
    | /* EMPTY */
    ;
    
  servingBid_opt:
      IFW_TAP3.ServingBid
    | /* EMPTY */
    ;

  servingLocationDescription_opt:
      IFW_TAP3.LocationDescription
    | /* EMPTY */
    ;

  simChargeableSubscriber:
      IFW_TAP3.SimChargeableSubscriber
      IFW_TAP3.Imsi
      {
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0, "IFW_TAP3.Imsi.IMSI");
          edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)    = "I"; //I=IMSI , M=MSISDN, P=IP , S=SIM , ...
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0, "IFW_TAP3.Imsi.IMSI");
          edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)    = "I"; //I=IMSI , M=MSISDN, P=IP , S=SIM , ...
        }
      }
      msisdn_opt
      IFW_TAP3.Block_END
    ;

  simToolkitIndicator_opt:
      IFW_TAP3.SimToolkitIndicator
    | /* EMPTY */
    ;

  speechVersionUsed_opt:
      IFW_TAP3.SpeechVersionUsed
    | /* EMPTY */
    ;

  speechVersionRequested_opt:
      IFW_TAP3.SpeechVersionRequested
    | /* EMPTY */
    ;

  ssParameters_opt:
      IFW_TAP3.SsParameters
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
      chargeableSubscriber
      rapFileSequenceNumber_opt
      networkType_opt
      locationInformation
      equipmentInformation_opt //normally mandatory!, but should only give a warning
      {
        initializeChargeInfoTempFields();
      }
      supplServiceUsedEvent
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
          edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
        }
        //get an index to the SS_PACKET
        ssPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0);
        edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0) = ssPacketIdx + 1;

        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_TYPE,0,ssPacketIdx) = extension_SS_EVENT;
        edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_NUMBER,0,ssPacketIdx) = records;
      }              
      supplServiceCode_opt
      supplServiceActionCode_opt
      ssParameters_opt
      thirdPartyInformation_opt
      {
        if (edrString(DETAIL.C_NUMBER) != defTelNumber)
        {
          edrString(DETAIL.C_NUMBER) = convertCli(edrString(DETAIL.C_NUMBER), 
                                                edrString(DETAIL.C_MODIFICATION_INDICATOR), 
                                                edrLong(DETAIL.C_TYPE_OF_NUMBER),
                                                NORM_NAC,
                                                calledNumberAnalysisIACarray[0],// NORM_IAC,
                                                calledNumberAnalysisCCarray[0], // NORM_CC,
                                                NORM_IAC_SIGN,
                                                NORM_NDC );
          edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);
        }
      }
      chargingTimeStamp_opt
      chargeInformation_opt
      basicServiceCodeList_opt
      {
        // and store the last affected BasicService
        if (SsBasicServicesAffectedNb > 0)
        {
          edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE, 0) = SsBasicServicesAffected[SsBasicServicesAffectedNb-1]; //TODO find a better storage place
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
          edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
        }
        //get an index to the SS_PACKET
        ssPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0);
        edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0) = ssPacketIdx + 1;

        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) = edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_TYPE,0,ssPacketIdx) = extension_SS_EVENT;
        edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_NUMBER,0,ssPacketIdx) = records;
      }              
      supplServiceCode
      supplServiceActionCode
      ssParameters_opt
      thirdPartyInformation_opt
      {
        if (edrString(DETAIL.C_NUMBER) != defTelNumber)
        {
          edrString(DETAIL.C_NUMBER) = convertCli(edrString(DETAIL.C_NUMBER), 
                                                edrString(DETAIL.C_MODIFICATION_INDICATOR), 
                                                edrLong(DETAIL.C_TYPE_OF_NUMBER),
                                                NORM_NAC,
                                                calledNumberAnalysisIACarray[0],// NORM_IAC,
                                                calledNumberAnalysisCCarray[0], // NORM_CC,
                                                NORM_IAC_SIGN,
                                                NORM_NDC );
          edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);
        }
      }
      chargingTimeStamp_opt
      chargeInformation_opt
      basicServiceCodeList_opt
      {
        // and store the last affected BasicService
        if (SsBasicServicesAffectedNb > 0)
        {
          edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE, 0) = SsBasicServicesAffected[SsBasicServicesAffectedNb-1]; //TODO find a better storage place
        }
      }
      IFW_TAP3.Block_END
    ;

  supplServiceCode:
      IFW_TAP3.SupplServiceCode
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,ssPacketIdx, "IFW_TAP3.SupplServiceCode.SUPPL_SERVICE_CODE");
      }
    ;

  supplServiceCode_opt:
      supplServiceCode
    | /* EMPTY */
    ;

  supplServiceActionCode:
      IFW_TAP3.SupplServiceActionCode
      {
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,ssPacketIdx, "IFW_TAP3.SupplServiceActionCode.SUPPL_SERVICE_ACTION_CODE");
      }
    ;

  supplServiceActionCode_opt:
      supplServiceActionCode
    | /* EMPTY */
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

  taxation_opt:
      IFW_TAP3.Taxation 
      taxRateDefinitionList
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  taxInformation:
      IFW_TAP3.TaxInformation
      IFW_TAP3.TaxCode
      { 
        // we only store the last rate of the list (ie overwrite the previous rate)
        // TaxRate comes in TAP3 with 5 decimal places, and in ifw we store only 2
        edrConnectToken(DETAIL.WHOLESALE_CHARGED_TAX_RATE, "IFW_TAP3.TaxCode.TAX_CODE");
        String taxRateStr    = getTaxRate( tokenLong("IFW_TAP3.TaxCode.TAX_CODE") );
        Long   taxRateStrlen = strLength( taxRateStr );
        if ( taxRateStrlen > 3 )
        {
          lastTaxRate  = strToLong( strSubstr( taxRateStr, 0, (taxRateStrlen - 3) ) );
        }
      }
      IFW_TAP3.Charge
      {
        edrConnectToken(DETAIL.WHOLESALE_CHARGED_TAX_VALUE, "IFW_TAP3.Charge.CHARGE");
        lastTaxCharge   = (longToDecimal(tokenLong("IFW_TAP3.Charge.CHARGE")) / theAbsoluteAmountDivider) * lastExchangeRateFactor;
        sumTaxChargeCI  = sumTaxChargeCI   + lastTaxCharge;
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

  taxRateDefinitionList:
      taxRateDefinitionList
      taxRateDefinition
    | taxRateDefinition 
    ;

  taxRateDefinition:
      IFW_TAP3.TaxRateDefinition
      IFW_TAP3.TaxCode
      {
        lastCode          = tokenLong("IFW_TAP3.TaxCode.TAX_CODE");
        taxCode[lastCode] = lastCode;
      }
      IFW_TAP3.TaxType
      {
        taxType[lastCode] = tokenString("IFW_TAP3.TaxType.TAX_TYPE");
        taxRate[lastCode] = ""; // initialisation
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
 
  taxRate_opt:
      IFW_TAP3.TaxRate
      {
        taxRate[lastCode] = tokenString("IFW_TAP3.TaxRate.TAX_RATE");
      }
    | /* EMPTY */
    ;

  thirdPartyInformation:
      IFW_TAP3.ThirdPartyInformation
      {
        callNumberType = thirdPartyType;
      }
      typeOfNumber_opt
      numberingPlan_opt
      thirdPartyNumber_opt
      modificationIndicator_opt
      clirIndicator_opt
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
      }
    | /* EMPTY */
    ;

  timeBandSubtype_opt:
      IFW_TAP3.TimeBandSubtype
    | /* EMPTY */
    ;
  totalChargeRefund_opt:
      IFW_TAP3.TotalChargeRefund
    | /* EMPTY*/
    ;
  
  totalChargeValue:
      IFW_TAP3.TotalChargeValue
      IFW_TAP3.ChargeType
      {
        lastTotalChargeValueChargeType     = tokenString("IFW_TAP3.ChargeType.CHARGE_TYPE");
      }
      IFW_TAP3.AbsoluteAmount
      {
        lastTotalChargeValueAbsoluteAmount = tokenDecimal("IFW_TAP3.AbsoluteAmount.ABSOLUTE_AMOUNT");
      }
      totalChargeRefund_opt
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

  totalCallEventDuration:
      IFW_TAP3.TotalCallEventDuration
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

  transferCutOffTimeStamp_opt:
      transferCutOffTimeStamp
      {
        edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP) = strToDate(theTransferCutOffTimeStamp);
      }
    | /* EMPTY */ 
    ;

  transparencyIndicator_opt:
      IFW_TAP3.TransparencyIndicator
    | /* EMPTY */
    ;

  typeOfNumber_opt:
      IFW_TAP3.TypeOfNumber
      {
        //lastTypeOfNumber = tokenLong("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER");
        switch (callNumberType)
        {
          case (callOriginatorType):
          case (callDestinationType):
          case (nonChargedPartyType):
          {
            edrConnectToken(DETAIL.B_TYPE_OF_NUMBER, "IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER");
          }
          break;
          case (camelCallReferenceType):
          {
            edrConnectToken(DETAIL.ASS_CAMEL_EXT.MSC_TYPE_OF_NUMBER, 0, "IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER");
          }
          break;
          case (camelDestinationType):
          {
            edrConnectToken(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_TYPE_OF_NUMBER, 0, "IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER");
          }
          break;
          case (camelServerType):
          {
            edrConnectToken(DETAIL.ASS_CAMEL_EXT.SERVER_TYPE_OF_NUMBER, 0, "IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER");
          }
          break;
          case (thirdPartyType):
          {
            edrConnectToken(DETAIL.C_TYPE_OF_NUMBER, "IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER");
          }
          break;
        }
      }
    | /* EMPTY */
    ;


  utcTimeOffsetInfo:
      IFW_TAP3.UtcTimeOffsetInfo
      utcTimeOffsetDefinitionList
      IFW_TAP3.Block_END
    ;

  utcTimeOffsetDefinition:
      IFW_TAP3.UtcTimeOffsetDefinition
      IFW_TAP3.UtcTimeOffsetCode
      {
        lastCode                    = tokenLong("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE");
        utcTimeOffsetCode[lastCode] = lastCode;
      }
      IFW_TAP3.UtcTimeOffset
      {
        utcTimeOffset[lastCode]     = tokenString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET");
        if (utcTimeOffsetEntries <= lastCode)
        {
          utcTimeOffsetEntries      = lastCode + 1;
        }
      }
      IFW_TAP3.Block_END
    ;

  utcTimeOffsetDefinitionList:
      utcTimeOffsetDefinitionList
      utcTimeOffsetDefinition
    | utcTimeOffsetDefinition
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
      scuVasChargeableSubscriber
      rapFileSequenceNumber_opt
      networkType_opt
      servingNetwork_opt
      {
        initializeChargeInfoTempFields();
      }
      valueAddedServiceUsed
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
      IFW_TAP3.VasCode
      {
        service_Type            = service_Vas;
        lastVasCode             = tokenLong("IFW_TAP3.VasCode.VAS_CODE");
        if (record_Type == record_VAS)
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.VAS_PRODUCT_CODE, 0, "IFW_TAP3.VasCode.VAS_CODE");
        }
      }
      chargingTimeStamp_opt
      {
        lastVasLocalTimeStamp   = lastValidLocalTimeStamp;//TODO check validity
        lastVasUtcTimeOffset    = lastValidUtcTimeOffset; //TODO check validity
      }
      chargeInformation_opt
      IFW_TAP3.Block_END
    ;

  valueAddedServiceUsedList:
      valueAddedServiceUsedList
      valueAddedServiceUsed
      {
        lastVasShortDescrList = lastVasShortDescrList + "," + getVasShortDesc( lastVasCode );
      }
    | valueAddedServiceUsed // first element of the list
      {
        lastVasShortDescrList = getVasShortDesc( lastVasCode );
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
    | /* EMPTY */ //accept empty list
    ;

  vasDefinition:
      IFW_TAP3.VasDefinition
      IFW_TAP3.VasCode
      {
        lastCode               = tokenLong("IFW_TAP3.VasCode.VAS_CODE");
        vasCode[lastCode]      = lastCode;
      }
      IFW_TAP3.VasShortDescription
      {
        vasShortDesc[lastCode] = tokenString("IFW_TAP3.VasShortDescription.VAS_SHORT_DESCRIPTION");
      }
      vasDescription_opt
      IFW_TAP3.Block_END
    ;

  vasDescription_opt:
      IFW_TAP3.VasDescription
      {
        vasDesc[lastCode] = tokenString("IFW_TAP3.VasDescription.VAS_DESCRIPTION");
        if (vasEntries <= lastCode)
        {
          vasEntries = lastCode + 1;
        }
      }
    | /* EMTPY */
    ;

  vasInfo_opt:
      IFW_TAP3.VasInfo
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
      vasInfoList vasDefinition
    | vasDefinition
    ;

  advisedChargeCurrency_opt:
      IFW_TAP3.AdvisedChargeCurrency
    | /* EMPTY */
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
      IFW_TAP3.TotalAdvisedCharge
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
//----------------------------------------------------------------------------

  contentTransaction: //TODO evrerything
      IFW_TAP3.ContentTransaction
      {
        //logStdout("Info: We just received a ContentTransaction detail (will not be processed).\n");
        //logPipeline("Info: We just received a ContentTransaction detail (will not be processed)" ,2);
        if ( createNewDetail(record_CONT, type_CONT) == false )
        {
          //TODO something
        }
        //record_Type  = record_CONT;
        //service_Type = service_Content;
      }
      contentTransactionBasicInfo
      chargedPartyInformation
      servingPartiesInformation
      contentServiceUsed
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  contentTransactionBasicInfo:
      IFW_TAP3.ContentTransactionBasicInfo
      fraudMonitorIndicator_opt
      rapFileSequenceNumber_opt
      orderPlacementTimeStamp_opt
      requestedDeliveryTimeStamp_opt
      actualDeliveryTimeStamp_opt
      totalTransactionDuration_opt
      transactionStatus_opt
      IFW_TAP3.Block_END
    ;
    
  orderPlacementTimeStamp_opt:
      IFW_TAP3.OrderPlacementTimeStamp
      {
        timeStampType = orderPlacementTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  requestedDeliveryTimeStamp_opt:
      IFW_TAP3.RequestedDeliveryTimeStamp
      {
        timeStampType = requestedDeliveryTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  actualDeliveryTimeStamp_opt:
      IFW_TAP3.ActualDeliveryTimeStamp
      {
        timeStampType = actualDeliveryTimeStampType;
      }
      dateTime
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  totalTransactionDuration_opt:
      IFW_TAP3.TotalCallEventDuration
    | /* EMPTY */
    ;
  
  transactionStatus_opt:
      IFW_TAP3.TransactionStatus
    | /* EMPTY */
    ;
  
  chargedPartyInformation:
      IFW_TAP3.ChargedPartyInformation
      IFW_TAP3.ChargedPartyIdList
      chargedPartyIdList
      IFW_TAP3.Block_END
      chargedPartyHomeIdList_opt
      chargedPartyLocationList_opt
      chargedPartyEquipment_opt
      IFW_TAP3.Block_END
    ;
    
  chargedPartyIdList:
      chargedPartyIdList
      chargedPartyId
    | chargedPartyId
    ;
    
  chargedPartyId:
      IFW_TAP3.ChargedPartyId
      IFW_TAP3.ChargedPartyIdType
      chargedPartyIdentification
      IFW_TAP3.Block_END
    ;
    
  chargedPartyIdentification:
      IFW_TAP3.Msisdn
    | IFW_TAP3.Imsi
    | IFW_TAP3.Min
    | ipAddress
    | IFW_TAP3.LoginName
    | IFW_TAP3.AccountNumber
    | IFW_TAP3.EmailAddress
    ;

  chargedPartyHomeIdList_opt:
      IFW_TAP3.ChargedPartyHomeIdList
      chargedPartyHomeIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY*/
    ;

  chargedPartyHomeIdList_opt2:
      chargedPartyHomeIdList
    | /* EMPTY */ //accept empty list
    ;

  chargedPartyHomeIdList:
      chargedPartyHomeIdList
      chargedPartyHomeId
    | chargedPartyHomeId
    ;

  chargedPartyHomeId:
      IFW_TAP3.ChargedPartyHomeId
      IFW_TAP3.HomeIdType
      homeIdentifier
      IFW_TAP3.Block_END
    ;

  homeIdentifier:
      IFW_TAP3.Name
    | IFW_TAP3.PlmnId
    | IFW_TAP3.HomeBid
    | IFW_TAP3.LocationDescription
    ;

  chargedPartyLocationList_opt:
      IFW_TAP3.ChargedPartyLocationList
      chargedPartyLocationList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY*/
    ;

  chargedPartyLocationList_opt2:
      chargedPartyLocationList
    | /* EMPTY */ //accept empty list
    ;

  chargedPartyLocationList:
      chargedPartyLocationList
      chargedPartyLocation
    | chargedPartyLocation
    ;

  chargedPartyLocation:
      IFW_TAP3.ChargedPartyLocation
      IFW_TAP3.LocationIdType
      LocationIdentifier
      IFW_TAP3.Block_END
    ;

  LocationIdentifier:
      IFW_TAP3.CountryName
    | IFW_TAP3.CountryCode
    | IFW_TAP3.CountryAsciCode
    | IFW_TAP3.Region
    | IFW_TAP3.Place
    | ipAddress
    ;

  chargedPartyEquipment_opt:
      IFW_TAP3.ChargedPartyEquipment
      IFW_TAP3.EquipmentIdType
      equipmentId
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;
    
  equipmentId:
      IFW_TAP3.Imei
    | IFW_TAP3.Esn
    ;

  servingPartiesInformation:
      IFW_TAP3.ServingPartiesInformation
      IFW_TAP3.ContentProviderName
      contentProviderIdList_opt
      internetServiceProviderIdList_opt
      networkIdList_opt
      IFW_TAP3.Block_END
    ;
    
  contentProviderIdList_opt:
      IFW_TAP3.ContentProviderIdList
      contentProviderIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  contentProviderIdList_opt2:
      contentProviderIdList
    | /* EMPTY */ //accept empty list
    ;

  contentProviderIdList:
      contentProviderIdList
      contentProviderId
    | contentProviderId
    ;

  contentProviderId:
      IFW_TAP3.ContentProviderId
      IFW_TAP3.ProviderIdType
      providerId
      IFW_TAP3.Block_END
    ;

  providerId:
      IFW_TAP3.Name
    | IFW_TAP3.PlmnId
    | IFW_TAP3.Url
    | ipAddress
    ;
  
  internetServiceProviderIdList_opt:
      IFW_TAP3.InternetServiceProviderIdList
      internetServiceProviderIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  internetServiceProviderIdList_opt2:
      internetServiceProviderIdList
    | /* EMPTY */ //accept empty list
    ;

  internetServiceProviderIdList:
      internetServiceProviderIdList
      internetServiceProviderId
    | internetServiceProviderId
    ;

  internetServiceProviderId:
      IFW_TAP3.InternetServiceProviderId
      IFW_TAP3.ProviderIdType
      providerId
      IFW_TAP3.Block_END
    ;

  networkIdList_opt:
      IFW_TAP3.NetworkIdList
      networkIdList_opt2
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  networkIdList_opt2:
      networkIdList
    | /* EMPTY */ //accept empty list
    ;

  networkIdList:
      networkIdList
      networkIdGroup
    | networkIdGroup
    ;

  networkIdGroup:
      IFW_TAP3.NetworkIdGroup
      IFW_TAP3.NetworkIdType
      networkDesc
      IFW_TAP3.Block_END
    ;

  networkDesc:
      IFW_TAP3.Name
    | IFW_TAP3.PlmnId
    | IFW_TAP3.HomeBid
    | IFW_TAP3.LocationDescription
    | IFW_TAP3.AccessPointName
    ;

  contentServiceUsed:
      IFW_TAP3.ContentServiceUsed
      {
        service_Type = service_Content;
      }
      IFW_TAP3.ContentTransactionCode
      IFW_TAP3.ContentTransactionType
      transactionDescriptionSupp_opt
      IFW_TAP3.TransactionShortDescription
      transactionDetailDescription_opt
      IFW_TAP3.TransactionIdentifier
      transactionAuthCode_opt
      dataVolumeIncoming_opt
      dataVolumeOutgoing_opt
      totalDataVolume_opt
      chargeRefundIndicator_opt
      contentChargingPoint_opt
      chargeInformationList_opt
      advisedChargeInformation_opt
      IFW_TAP3.Block_END
    ;

  transactionDescriptionSupp_opt:
      IFW_TAP3.TransactionDescriptionSupp
    | /* EMPTY */
    ;
    
  transactionDetailDescription_opt:
      IFW_TAP3.TransactionDetailDescription
    | /* EMPTY */
    ;
    
  transactionAuthCode_opt:
      IFW_TAP3.TransactionAuthCode
    | /* EMPTY */
    ;
    
  dataVolumeIncoming_opt:
      IFW_TAP3.DataVolumeIncoming
    | /* EMPTY */
    ;
    
  dataVolumeOutgoing_opt:
      IFW_TAP3.DataVolumeOutgoing
    | /* EMPTY */
    ;
    
  totalDataVolume_opt:
      IFW_TAP3.TotalDataVolume
    | /* EMPTY */
    ;
    
  chargeRefundIndicator_opt:
      IFW_TAP3.ChargeRefundIndicator
    | /* EMPTY */
    ;
    
  contentChargingPoint_opt:
      IFW_TAP3.ContentChargingPoint
    | /* EMPTY */
    ;

  advisedChargeInformation_opt:
      IFW_TAP3.AdvisedChargeInformation
      paidIndicator_opt
      paymentMethod_opt
      advisedChargeCurrency_opt
      IFW_TAP3.AdvisedCharge
      commission_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  paidIndicator_opt:
      IFW_TAP3.PaidIndicator
    | /* EMPTY */
    ;

  paymentMethod_opt:
      IFW_TAP3.PaymentMethod
    | /* EMPTY */
    ;

  commission_opt:
      IFW_TAP3.Commission
    | /* EMPTY */
    ;
}


