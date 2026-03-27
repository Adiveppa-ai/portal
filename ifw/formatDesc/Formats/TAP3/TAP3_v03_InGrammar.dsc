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
//   Input grammar file for the TAP3_v03 CDR format
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Cedric Diab
//
// $RCSfile: TAP3_v03_InGrammar.dsc,v $
// $Revision: 1.22 $
// $Author: cdiab $
// $Date: 2001/11/22 15:59:37 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TAP3_v03_InGrammar.dsc,v $
// Revision 1.22  2001/11/22 15:59:37  cdiab
// PETS #41974: TAP3 ChargePacket wrongly flaged as Alternative
//
// Revision 1.21  2001/11/22 15:20:12  cdiab
// PETS #41974: TAP3 ChargePacket wrongly flaged as Alternative
//
// Revision 1.20  2001/11/21 15:17:17  cdiab
// PETS #41865 : TAP3 notification record is not created when HEADER and TRAILER exist
// Until now, we mapped a Notification file to a HEADER (and the other way around).
// We should rather map a Notification file to a HEADER+TRAILER (without any DETAIL).
//
// Revision 1.19  2001/11/15 15:16:52  cdiab
// PETS #41247: Parser: error messages for parse errors not helpful
// -added 2 EDR field initialisations workaround for (with) "errorProcessing" (tag)
// PETS #41646: TaxRate is wrong reading TAP3 files, decimal places are not considered
// -for TAP3v03 and TAP3v04 we now expect (and write out) TaxRate with 5
//  decimal places
//
// Revision 1.18  2001/11/13 11:42:38  cdiab
// PETS #40773 : CAMEL support for V4.30
//
// Revision 1.17  2001/10/25 12:55:44  cdiab
// PETS #40975 : TotalCharge in AuditControl != sum of ChargeAmounts
// The charge amounts in the charge detail blocks should be rounded
// (normal rounding) before inserted into the file, and also before
// being added to the total to be used in the TotalCharge (which then
// should be only truncated to the decimal places). (otherwise we get
// a mismatch because of the rounding)
// Same thing for discounting and totalDiscount except that there, we
// do not round the value, we truncate it.
//
// Revision 1.16  2001/10/23 18:10:00  cdiab
// PETS #40891: TAP3 parse error : v04 read / v01 v04 write
//
// Revision 1.15  2001/10/19 11:39:37  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// on input, if the aggregation ChargeDetail (ie. type "00") has a charge
// or chargeableUnits, we use these for our DETAIL fields (sums).
//
// Revision 1.14  2001/10/19 09:11:25  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// -in case of GPRS, now DETAIL.VOLUME_SENT and DETAIL.VOLUME_RECEIVED store the value
// given on the GprsServiceUsage block (and not a summing for the chargeable quantities
// from the ChargeDetail all stored on the VOLUME_SENT like previously)
//
// Revision 1.13  2001/10/18 16:31:28  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// -for tap0304 in DETAIL.ASS_GPRS_EXT.APN_ADDRESS, use the ',' and not '.'
// as separator, as it can be composed of IP adresses
// -for writing of decimal values, use round() (and not trunc()) to get an
// integer
// -we now always write the ChargeDetail.Charge, even if it is 0
// -NetworkType is written out for the details onlöy if it is set to mixed
// (ie. 0) in the registry
//
// Revision 1.12  2001/10/11 12:14:45  cdiab
// PETS #40345: in TAP3 Audit block, INTEGERS can up to 8 bytes
// we now use the ASN_HexString type to manage them and read them directly as Decimal.
//
// Revision 1.11  2001/10/11 10:57:44  cdiab
// PETS #40344: modify output grammar to generate Tap3 Notification
// -modified the grammar to map an incoming notification file to a HEADER
//
// Revision 1.10  2001/10/10 16:00:10  cdiab
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
// Revision 1.9  2001/10/09 15:27:24  cdiab
// PETS #40225: Error reading ChargeDetail with ChargeType "00" (input)
// we now store all ChargeDetails as CP, but mark redundant CPs with
//    DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE = "A" (ie. alternative price model)
// +now ChargingId is read even if it holds on more that a long integer.
//
// Revision 1.8  2001/10/01 16:27:25  cdiab
// PETS #39726 : Number normalization must support multiple IAC's
// -TAP3 has been updated to use the new converCli method (previous checkin
// [v4-30-11] was only a workaround).
//
// Revision 1.7  2001/09/21 13:01:48  cdiab
// PETS #39722: TAP3 v03: error in InGrammar
// The last 3 lines of the file was corrupted (unreadable special caracters).
//
// PETS #39723: Number normalisation in Tap3 has errors
// -Now we initialise by default x_NUMBER and INTERN_x_NUMBER_ZONE to <iac><cc>
// (defTelNumber) as retrieved from the input stream
// -Form MOC, INTERN_A_NUMBER_ZONE="0000"+ORIGINATING_SWITCH_ID
// -Form MTC, INTERN_B_NUMBER_ZONE="0000"+TERMINATING_SWITCH_ID
// -If number is flagged as modified, x_MODIFICATION_INDICATOR is set to "08"
// -transmit in HEADER.ORIGIN_COUNTRY_CODE, the defTelNumber used when no MSISDN
// was given on input (defTelNumber=<iac><cc>)
//
// Revision 1.6  2001/09/20 12:08:14  cdiab
// PETS #39644: be able to normalize a TelNum using arrays for CC and IAC
// On output we now use 2 new additional registry entries at the pipeline level:
//      InternationalAccessCodeList = 001,002,00,011
//      CountryCodeList		 = 852,49,1
// These entries are used to build the CalledNumberAnalisys block which is used
// for number normalization when reading tap3 files.
// These registry entries have to be updated with a list of all iac and cc that
// can be used in the streams.
//
// I also used the oportunity to correct the fact that:
//   DETAIL.ASS_GPRS_EXT.CHARGING_ID is a String (was used as a Long)
//   DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE is a Decima (was used as a Long)
//
// Revision 1.5  2001/09/19 16:27:25  cdiab
// PETS #39644: be able to normalize a TelNum using arrays for CC and IAC
// now using convertCli2 for number normalization
//
// Revision 1.4  2001/09/14 15:00:54  cdiab
// PETS #39334: for tap0303 manage CALL_TYPE as for tap0304.
// i also used the oportunity to set defaults for registry values when they
// are not present in the registry file.
//
// Revision 1.3  2001/09/14 14:16:54  cdiab
// PETS #39333: in TAP3, add ability to select tap or local currency.
// We store the local and tap currency names on the ChargePacket, and the
// exchange rate from on to the other.
// on output side, we expect all values to be in tap currencies.
//
// Revision 1.2  2001/09/06 10:45:10  cdiab
// PETS #38890 : Errors when writing TAP3 to output.
// remove use of multiple blocks with same tag but different names.
// (the parser would always take the first found).
// now using HexString to read integer or OctetString objects.
//
// Revision 1.1  2001/09/05 12:02:46  cdiab
// PETS #38719 : add ability to read Tap3 v03 (TD57v3.7.1)
// added TAP3_v03_InGrammar.dsc and TAP3_v03_Blocks.dsc
//
// Revision 1.15  2001/08/03 13:34:16  cdiab
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
// 		 B_NUMBER, INTERN_B_NUMBER_ZONE,
// 		 C_NUMBER, INTERN_C_NUMBER_ZONE
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
  
  // for statistics
  Date startTime;
  Date stopTime;
  
  // default values
  Date   defLocalTime;
  String defLocalTimeStamp;
  String defUtcTimeOffset;
  String defTelNumber;
  String defCauseForTerm;
  
  // for split details
  Long    chainReference;  
  Long    theLastEdrCopy; // index on copy

  // block counters
  Long records;
  Long tap3Detail;
  Long details;
  Long successiveBasicServiceUsed;
  Long successiveChargeInformation;
  Long successiveChargeDetail;
  Long successiveChargePacket;
  Long successiveChargePacketCI;
  
  // constants
  Long record_Header;
  Long record_Trailer;
  Long record_MOC;
  Long record_MTC;
  Long record_MSS;
  Long record_SCU;
  Long record_VAS;
  Long record_GPRS;
  Long record_Type; // use to know which type of detail we are reading

  // constants
  Long service_Basic;
  Long service_Camel;
  Long service_Gprs;
  Long service_Suppl;
  Long service_Vas;
  Long service_Type; // use to know which type of service we are reading
  
  // constants
  String type_HEADER;
  String type_TRAILER;
  String type_MOC;
  String type_MTC;
  String type_MSS;
  String type_SCU;
  String type_VAS;
  String type_GPRS;
  String type_GPRS_SG;
  String type_GPRS_GG;
  String type_GPRS_assembled;
  String extension_GSMW;
  String extension_GPRS;
  String extension_CBD;
  String extension_CAMEL;

  // for storage of Header/Trailer/Notification values
  String  theSender;
  String  theRecipient;
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
  Long   lastTypeOfNumber;
  Long   lastNumberingPlan;
  String lastNonChargedNumber;  // record_SCU
  Long   lastModificationIndicator;
  Long   lastCalledNumAnalysisCode;
  String lastCalledNumberAnalysisCC;
  String lastCalledNumberAnalysisIAC;
  Long   lastCode; // for initialisation lists in TAP3 header
  Long   lastRadioChannelRequested;
  Long   lastRadioChannelUsed;
  String lastBasicService;
  String lastBasicDualService;
  
  // storage of third party info for supplementary service
  Long   lastThirdPartyTypeOfNumber;
  Long   lastThirdPartyNumberingPlan;
  String lastThirdPartyNumber;
  Long   lastThirdPartyModificationIndicator;

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
  String lastRemotePdpAddressList;
  Long   lastQoSDelay;
  Long   lastQoSMeanThroughput;
  Long   lastQoSPeakThroughput;
  Long   lastQoSPrecedence;
  Long   lastQoSReliability;
  Long   lastQoSRequestedDelay;
  Long   lastQoSRequestedMeanThroughput;
  Long   lastQoSRequestedPeakThroughput;
  Long   lastQoSRequestedPrecedence;
  Long   lastQoSRequestedReliability;
  Long   lastQoSUsedDelay;
  Long   lastQoSUsedMeanThroughput;
  Long   lastQoSUsedPeakThroughput;
  Long   lastQoSUsedPrecedence;
  Long   lastQoSUsedReliability;
  Decimal sumDataVolumeIncoming;
  Decimal sumDataVolumeOutgoing;

  // for CAMEL Service
  String lastCamelModificationList;

  // store value from ChargeInformation Block
  String  lastChargedItem;
  Decimal lastExchangeRateFactor;
  Decimal lastExchangeRateFactorValue;
  Long    lastCallTypeLevel1;
  Long    lastCallTypeLevel2;
  Long    lastCallTypeLevel3;
  String  lastCalledCountryCode;
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
  String  lastDayCategory;
  String  lastTimeBand;
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
  String theRecEntityId;        // used at runtime
  
  // vasInfo
  Long   vasEntries;
  Long   vasCode[];
  String vasShortDesc[];
  String vasDesc[];

  // messageDescriptionInfo
  Long   messageDescriptionEntries;
  Long   messageDescriptionCode[];
  String messageDescription[];

  //regestry string where to find user configurable values
  String reg_TapPipeline;
  String reg_OriginCountryCode;
  String reg_SenderCountryCode;
  String reg_UseLocalCurrency;
  
  // storage of registry values
  String strOriginCountryCode;
  String strSenderCountryCode;
  Bool   bUseLocalCurrency;
  
  function onParseStart
  {
    lexState("STATE_TAP3");
  }
  
  function BEGIN
  {
    // initialisation of some constant values
    //---------------------------------------
    
    reg_TapPipeline	  = "ifw.Pipelines."+formatName()+".";
    reg_OriginCountryCode = reg_TapPipeline + "OriginCountryCode";
    reg_SenderCountryCode = reg_TapPipeline + "SenderCountryCode";
    reg_UseLocalCurrency  = reg_TapPipeline + "UseLocalCurrency";

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
    
    recEntityType_MSC		= 1;
    recEntityType_SMSC		= 2;
    recEntityType_GGSN		= 3;
    recEntityType_SGSN		= 4;
    recEntityId_mscId           = 1;
    recEntityId_msisdn          = 2;
    recEntityId_iPTextV4Address = 3;
    recEntityId_iPTextV6Address = 4;
  
    defLocalTime	= MIN_DATE;
    defLocalTimeStamp	= dateToStr(defLocalTime);
    defUtcTimeOffset	= "+0000";
    defTelNumber	= "000";
    defCauseForTerm	= "00";
    
    record_Header =11;
    record_Trailer=12;
    record_MOC    =1;
    record_MTC    =2;
    record_MSS    =3;
    record_SCU    =4;
    record_VAS    =5;
    record_GPRS   =6;
    record_Type   =0; // use to know which type of detail we are reading

    service_Basic =1;
    service_Camel =2;
    service_Gprs  =3;
    service_Suppl =4;
    service_Vas   =5;
    service_Type  =0; // use to know which type of service we are reading

    type_HEADER 	="010";
    type_TRAILER	="090";
    type_MOC		="021";
    type_MTC		="031";
    type_MSS		="029";
    type_SCU		="050"; 
    type_VAS    	="060";
    type_GPRS_SG	="040";
    type_GPRS_GG	="042";
    type_GPRS_assembled	=type_GPRS_GG;		//default for mixed ticket
    type_GPRS		=type_GPRS_assembled;	//default is mixed ticket
    extension_GSMW	="520";
    extension_GPRS	="540";
    extension_CBD	="980";			//TODO check (here global charge)
    extension_CAMEL	="700";
    
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
    chainReference		= 0;
    records			= 0;
    tap3Detail			= 0;
    details			= 0;
    theSender			= "";
    theRecipient		= "";
    theFileSeqNum		= 0;
    theOrigFileSeqNum		= 0;
    theTotalChargedValue	= 0.0;
    theTotalChargedValue_00	= 0.0;
    lastLocalTimeStamp		= defLocalTimeStamp;
    lastUtcTimeOffset		= defUtcTimeOffset;
    lastTypeOfNumber		= 0;
    lastNumberingPlan		= 0;
    lastModificationIndicator	= 0;
    sumChargedAmountValueFile   = 0.0;
    sumTaxChargeFile		= 0.0;
    sumTaxChargeFileAll		= 0.0;
      
    theLocalCurrency		= "SDR"; // default
    theTapCurrency		= "SDR"; // default
    theTapDecimalPlaces		= 0;     // manadatory tap3 field, will be overwritten
    theAbsoluteAmountDivider    = 1.0;   // corresponding to theTapDecimalPlaces
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
    else if ( detailTypedId==record_GPRS )
	logStdout( "IN_record_GPRS #"+longToStr(records)+"(Tap3#"+longToStr(tap3Detail)+")\n" );
    else
	logStdout( "ERROR: unknown detail type: "+longToStr(detailTypedId)+"\n" ); 
*/   

    // Add the Extension block to store service information
    if      (	( detailTypedId==record_MOC ) or
    		( detailTypedId==record_MTC ) or
		( detailTypedId==record_MSS ) or
		( detailTypedId==record_SCU ) or
		( detailTypedId==record_VAS )	)
    {
      if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT ) == false ) 
      { 
	String Msg = "failed to add ASS_GSMW_EXT datablock for EDR "+longToStr(records);
	edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
	return false; //TODO check for consequences
      }
      records = records+1;
      edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)			= 1;
      edrString(DETAIL.ASS_GSMW_EXT.RECORD_TYPE, 0)		= extension_GSMW;
      edrLong(DETAIL.ASS_GSMW_EXT.RECORD_NUMBER,0 )		= records;
      edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS, 0)	= 0;
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
      edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)			= 1;
      edrString(DETAIL.ASS_GPRS_EXT.RECORD_TYPE, 0)		= extension_GPRS;
      edrLong( DETAIL.ASS_GPRS_EXT.RECORD_NUMBER,0 )		= records;
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
    edrString(DETAIL.A_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_A_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.B_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.B_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_B_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.C_TYPE_OF_NUMBER)                   = 0;      // unknown
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

    // some detail level runtime values
    lastLocalTimeStamp		= defLocalTimeStamp;
    lastUtcTimeOffset		= defUtcTimeOffset;
    lastValidLocalTimeStamp	= defLocalTimeStamp;
    lastValidUtcTimeOffset	= defUtcTimeOffset;
    lastTypeOfNumber		= 0;
    lastNumberingPlan		= 0;
    lastModificationIndicator	= 0;
    lastCode			= 0;
    
    return true;
  }

  function initializeChargeDetailTempFields
  {
    // initialise ChargeDetail temporaey fields used to store the provided values
    lastChargeType		= "";
    lastCharge			= 0.0;
    lastChargeableUnits		= 0;
    lastChargedUnits		= 0;
    lastChargeDetailTimeStamp	= lastValidLocalTimeStamp;
    lastDayCategory		= "";
    lastTimeBand		= "";
    lastDiscountCode		= 0;
    lastDiscountValue		= 0.0; // initialised here because it is stored on the ChargePacket ! (and we only want to count it once)
  }
  function initializeChargeInfoTempFields
  {
    // initialise ChargeInformation temporary fields used to store the provided values
    // for a list of ChargeInformation blocks (CALLED ONLY ONCE PER GENERATED EDR RECORD !!!)
    // (a call to storeChargeInfoTempFields will be used to update the EDR with the data)
    lastChargedItem		= "";
    lastCallTypeLevel1		= 0;
    lastCallTypeLevel2		= 0;
    lastCallTypeLevel3		= 0;
    lastCalledCountryCode	= "";

    sumChargeableUnitsDuration		= 0;
    sumChargeableUnitsVolumeSent	= 0;
    sumChargeableUnitsVolumeReceived	= 0;
    sumChargeableUnitsEvents		= 0;
    lastTaxRate			= 0;
    lastTaxCharge		= 0.0;
    sumTaxChargeEDR		= 0.0;
    sumChargedAmountValueEDR    = 0.0;
    // initialise ChargeDetail temporary fields used to store the provided values
    lastChargeType		= "";
    lastCharge			= 0.0;
    lastChargeableUnits		= 0;
    lastChargedUnits		= 0;
    lastChargeDetailTimeStamp	= lastValidLocalTimeStamp;
    lastDayCategory		= "";
    lastTimeBand		= "";
    lastDiscountCode		= 0;
    lastDiscountValue		= 0.0; // initialised here because it is stored on the ChargePacket ! (and we only want to count it once)
  }
  function storeChargeInfoTempFields
  {
    if (successiveChargeInformation >= 1)
    {
      // default values
      edrString(DETAIL.ASS_CBD.SYSTEM_BRAND_CODE,0)	= "0";
      // store the collected chargeInformation data in the corresponding EDR
      edrString(DETAIL.CONNECT_TYPE)			= longToStr(lastCallTypeLevel1)+longToStr(lastCallTypeLevel2);
      edrString(DETAIL.CONNECT_SUB_TYPE)		= longToStr(lastCallTypeLevel3);
      if (sumChargeableUnitsDuration != 0)
      {
        edrDecimal(DETAIL.DURATION)			= longToDecimal(sumChargeableUnitsDuration);
      }
      if (record_Type != record_GPRS) //for GPRS, VOLUME_SENT and VOLUME_RECEIVED have already been updated by GprsServiceUsage
      {
        if (sumChargeableUnitsVolumeSent != 0)
        {
          edrDecimal(DETAIL.VOLUME_SENT)		= longToDecimal(sumChargeableUnitsVolumeSent);
        }
        if (sumChargeableUnitsVolumeReceived != 0)
        {
          edrDecimal(DETAIL.VOLUME_RECEIVED)		= longToDecimal(sumChargeableUnitsVolumeReceived);
        }
      }
      if (sumChargeableUnitsEvents != 0)
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)		= longToDecimal(sumChargeableUnitsEvents);
      }
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0)=successiveChargePacket;

      edrString(DETAIL.WHOLESALE_IMPACT_CATEGORY)	= "00";       // as for IFW_TAP3.ChargeType : global charge for ChargeInformation
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE)	= sumChargedAmountValueEDR;
      if (bUseLocalCurrency)
      {
        edrString(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY) = theLocalCurrency;
      }
      else
      {
        edrString(DETAIL.WHOLESALE_CHARGED_AMOUNT_CURRENCY) = theTapCurrency;
      }
      edrString(DETAIL.WHOLESALE_CHARGED_TAX_TREATMENT)	= "N";
      edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE)	= lastTaxRate;
      //edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)	= sumTaxChargeEDR; //TODO the coresponding field does not exist
    }
  }

  function updateBasicDetailWithVasCharge
  {
    if (successiveChargeInformation >= 1)
    {
      // store the collected chargeInformation data in the corresponding EDR
      if (sumChargeableUnitsDuration != 0)
      {
        edrDecimal(DETAIL.DURATION)			= longToDecimal(sumChargeableUnitsDuration);
      }
      if (record_Type != record_GPRS) //for GPRS, VOLUME_SENT and VOLUME_RECEIVED have already been updated by GprsServiceUsage
      {
        if (sumChargeableUnitsVolumeSent != 0)
        {
          edrDecimal(DETAIL.VOLUME_SENT)		= longToDecimal(sumChargeableUnitsVolumeSent);
        }
        if (sumChargeableUnitsVolumeReceived != 0)
        {
          edrDecimal(DETAIL.VOLUME_RECEIVED)		= longToDecimal(sumChargeableUnitsVolumeReceived);
        }
      }
      if (sumChargeableUnitsEvents != 0)
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)		= longToDecimal(sumChargeableUnitsEvents);
      }
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0)=successiveChargePacket;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE)	= sumChargedAmountValueEDR;
      //edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)	= sumTaxChargeEDR; //TODO the coresponding field does not exist
    }
  }

  function updateBasicDetailWithCamelCharge
  {
    if (successiveChargeInformation >= 1)
    {
      // store the collected chargeInformation data in the corresponding EDR
      if (sumChargeableUnitsDuration != 0)
      {
        edrDecimal(DETAIL.DURATION)			= longToDecimal(sumChargeableUnitsDuration);
      }
      if (record_Type != record_GPRS) //for GPRS, VOLUME_SENT and VOLUME_RECEIVED have already been updated by GprsServiceUsage
      {
        if (sumChargeableUnitsVolumeSent != 0)
        {
          edrDecimal(DETAIL.VOLUME_SENT)		= longToDecimal(sumChargeableUnitsVolumeSent);
        }
        if (sumChargeableUnitsVolumeReceived != 0)
        {
          edrDecimal(DETAIL.VOLUME_RECEIVED)		= longToDecimal(sumChargeableUnitsVolumeReceived);
        }
      }
      if (sumChargeableUnitsEvents != 0)
      {
        edrDecimal(DETAIL.NUMBER_OF_UNITS)		= longToDecimal(sumChargeableUnitsEvents);
      }
      edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0)=successiveChargePacket;
      edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE)	= sumChargedAmountValueEDR;
      //edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)	= sumTaxChargeEDR; //TODO the coresponding field does not exist
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
    if (CalledNumberAnalysisCode >= calledNumberAnalysisEntries)
    {
      // here, special case, it can be used as a default
      //logStdout( "Info: getIAC("+longToStr(CalledNumberAnalysisCode)+"), unknown CalledNumberAnalysisCode \n");
      return(NORM_IAC_STRING); //use default params
    }
    return( calledNumberAnalysisIAC[CalledNumberAnalysisCode] );
  }
  
  function String getCountryCode(Long CalledNumberAnalysisCode)
  {
    if (CalledNumberAnalysisCode >= calledNumberAnalysisEntries)
    {
      // here, special case, it can be used as a default
      //logStdout( "Info: getCountryCode("+longToStr(CalledNumberAnalysisCode)+"), unknown CalledNumberAnalysisCode \n");
      return(NORM_CC_STRING); //use default params
    }
    return( calledNumberAnalysisCC[CalledNumberAnalysisCode] );
  }

  function String getIacList
  {
    String localString = "";
    Long size1 = arraySize( calledNumberAnalysisIACarray );
    Long size2 = 0;
    Long i;
    Long j;
    for (i=1 ; i<size1 ; i=i+1)
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
    for (i=1 ; i<size1 ; i=i+1)
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
//logStdout( "  Start Tap0303 input :  " + dateToStr(startTime)+ "\n");         //TODO remove this line or just comment it
//logStdout( "  End   Tap0303 input :  " + dateToStr(stopTime) + "\n");         //TODO remove this line or just comment it
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
      fileCreationTimeStamp
      {
        edrDate(HEADER.CREATION_TIMESTAMP) = strToDate(theFileCreationTimeStamp);
        edrString(HEADER.UTC_TIME_OFFSET)  = theFileCreationUtcTimeOffset;
      }
      fileAvailableTimeStamp
      {
        edrDate(HEADER.TRANSMISSION_DATE) = strToDate(theFileAvailableTimeStamp);
      }
      transferCutOffTimeStamp
      {
        edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP) = strToDate(theTransferCutOffTimeStamp);
      }
      IFW_TAP3.SpecificationVersionNumber
      {
	edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) = tokenLong("IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER");    
      }
      IFW_TAP3.ReleaseVersionNumber
      {
	edrLong(HEADER.RELEASE_VERSION) = tokenLong("IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER");    
      }
      fileTypeIndicator_opt
      {
	edrString(HEADER.DATA_TYPE_INDICATOR) = theFileTypeIndicator;    
      }
      operatorSpecInformation_opt
      {
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
	record_Type = record_Header;
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
      }
      batchControlInfo
      accountingInfo_opt
      networkInfo
      {
        // for every stream, the default TelNnumber is different, built as <iac><cc>
	defTelNumber = convertCli(	"", "00", 0,
					NORM_NAC,
					calledNumberAnalysisIACarray[1],// NORM_IAC,
					calledNumberAnalysisCCarray[1], // NORM_CC,
					NORM_IAC_SIGN,
					NORM_NDC );
	edrString(HEADER.ORIGIN_COUNTRY_CODE) = defTelNumber; //strOriginCountryCode; //TODO check
	edrString(HEADER.SENDER_COUNTRY_CODE) = strSenderCountryCode; //TODO check (we take it from registry)
	edrString(HEADER.IAC_LIST)	      = getIacList();
	edrString(HEADER.CC_LIST)	      = getCcList();
      }
      vasInfo_opt
      messageDescriptionInfo_opt
      callEventDetails
      auditControlInfo
      IFW_TAP3.Block_END
    ;

  accountingInfo_opt:
      IFW_TAP3.AccountingInfo
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
	theTapDecimalPlaces      = tokenLong("IFW_TAP3.TapDecimalPlaces.TAP_DECIMAL_PLACES");
        theAbsoluteAmountDivider = 1.0;
	Long i;
	for (i=0 ; i < theTapDecimalPlaces ; i=i+1)
	{
	  theAbsoluteAmountDivider = theAbsoluteAmountDivider * 10.0;
	}
//	theAbsoluteAmountDivider = 1.0;  //TODO Remove (CEDRIC for tests, to get SDR count)
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
      IFW_TAP3.TotalTaxValue
      IFW_TAP3.TotalDiscountValue
      IFW_TAP3.CallEventDetailsCount
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  batchControlInfo:
      IFW_TAP3.BatchControlInfo
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
      fileCreationTimeStamp
      {
        edrDate(HEADER.CREATION_TIMESTAMP) = strToDate(theFileCreationTimeStamp);
        edrString(HEADER.UTC_TIME_OFFSET)  = theFileCreationUtcTimeOffset;
      }
      transferCutOffTimeStamp
      {
        edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP) = strToDate(theTransferCutOffTimeStamp);
      }
      fileAvailableTimeStamp
      {
        edrDate(HEADER.TRANSMISSION_DATE) = strToDate(theFileAvailableTimeStamp);
      }
      IFW_TAP3.SpecificationVersionNumber
      {
	edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) = tokenLong("IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER");    
      }
      IFW_TAP3.ReleaseVersionNumber
      {
	edrLong(HEADER.RELEASE_VERSION) = tokenLong("IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER");    
      }
      fileTypeIndicator_opt
      {
	edrString(HEADER.DATA_TYPE_INDICATOR) = theFileTypeIndicator;    
      }
      rapFileSequenceNumber_opt
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  basicHSCSDParameters:
      IFW_TAP3.BasicHSCSDParameters
      fnur_opt
      aiurRequested_opt
      IFW_TAP3.NumberOfChannels
      channelCodingsAcceptable
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
	lastBasicService = "0" + tokenString("IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE") ;
      }
    | IFW_TAP3.BearerServiceCode
      {
	lastBasicService = "1" + tokenString("IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE") ;
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
      basicServiceCodeList
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        SsBasicServicesAffectedNb                          = 0; // initialisation
      }
    ;

  basicServiceUsed:
      IFW_TAP3.BasicServiceUsed
      {
	newBasicServiceBlock();
        service_Type			=service_Basic;
	lastRadioChannelRequested	=0;
	lastRadioChannelUsed		=0;
	lastBasicService		="011"; // default
      }
      basicService
      {
	edrString(DETAIL.BASIC_SERVICE)	=lastBasicService;
	edrLong(DETAIL.QOS_REQUESTED)   =lastRadioChannelRequested;
	edrLong(DETAIL.QOS_USED)        =lastRadioChannelUsed;
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
        lastCode				= lastCalledNumAnalysisCode;
	calledNumberAnalysisCode[lastCode]	= lastCode;
      }
      countryCodeTable
      {
	calledNumberAnalysisCC[lastCode]	= lastCalledNumberAnalysisCC; //we store only the last element
      }
      iacTable
      {
	calledNumberAnalysisIAC[lastCode]	= lastCalledNumberAnalysisIAC; //we store only the last element
        if (calledNumberAnalysisEntries <= lastCode)
	{
	  calledNumberAnalysisEntries = lastCode + 1;
	}
      }
      IFW_TAP3.Block_END
    ;
    
  calledNumAnalysisCode_opt:
      IFW_TAP3.CalledNumAnalysisCode
      {
        lastCalledNumAnalysisCode	= tokenLong("IFW_TAP3.CalledNumAnalysisCode.CALLED_NUM_ANALYSIS_CODE");
      }
    | /* EMPTY */
      {
        lastCalledNumAnalysisCode	= 1; // when only one entry, it can be omitted
      }
    ;

  calledNumAnalysisList:
      calledNumAnalysisList calledNumAnalysis 
    | calledNumAnalysis
    ;

  calledNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        edrString(DETAIL.B_NUMBER)                     = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.INTERN_B_NUMBER_ZONE)         = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0) = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
    ;

  calledPlace_opt:
      IFW_TAP3.CalledPlace
      {
        edrString(DETAIL.DESCRIPTION)                  = tokenString("IFW_TAP3.CalledPlace.CALLED_PLACE");
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
    ;

  callEventDetailList:
      callEventDetailList
      callEventDetailListElem
    | callEventDetailListElem
    ;
    
  callEventDetailListElem:
      {
	tap3Detail = tap3Detail +1;
      }
      callEventDetail
      {
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
      callEventDetailList
      IFW_TAP3.Block_END
    ;

  callEventStartTimeStamp:
      IFW_TAP3.CallEventStartTimeStamp
      dateTime
      IFW_TAP3.Block_END
      {
        //mandatory field for MOC, MTC, GPRS, will serve as a default timestamp
	lastValidLocalTimeStamp = lastLocalTimeStamp; // to serve as default LocalTimeStamp for coresponding record
	lastValidUtcTimeOffset  = lastUtcTimeOffset;  // to serve as default UtcTimeOffset for coresponding record
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) = strToDate(lastLocalTimeStamp);
	edrDate(DETAIL.CHARGING_END_TIMESTAMP)   = strToDate(lastLocalTimeStamp);
	edrString(DETAIL.UTC_TIME_OFFSET)        = lastUtcTimeOffset;
      }
    ;

  callingNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        edrString(DETAIL.B_NUMBER)                     = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.INTERN_B_NUMBER_ZONE)         = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
        edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER,0) = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
    ;

  callOriginator_opt:
      IFW_TAP3.CallOriginator
      typeOfNumber_opt
      numberingPlan_opt
      callingNumber_opt
      modificationIndicator_opt
      clirIndicator_opt
      IFW_TAP3.Block_END
      {
        edrLong(DETAIL.B_TYPE_OF_NUMBER)           = lastTypeOfNumber;
        edrString(DETAIL.B_NUMBERING_PLAN)         = longToStr(lastNumberingPlan);
	if (lastModificationIndicator > 0)
	{
          edrString(DETAIL.B_MODIFICATION_INDICATOR) = "08";
        }
        lastTypeOfNumber          = 0;
        lastNumberingPlan         = 0;
        lastModificationIndicator = 0;
	
	//normalize the number
	edrString(DETAIL.B_NUMBER) = convertCli(edrString(DETAIL.B_NUMBER), 
						edrString(DETAIL.B_MODIFICATION_INDICATOR), 
						edrLong(DETAIL.B_TYPE_OF_NUMBER),
						NORM_NAC,
						calledNumberAnalysisIACarray[1],// NORM_IAC,
						calledNumberAnalysisCCarray[1], // NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
	edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
      }
    | /* EMPTY */
    ;

  callType_opt:
      IFW_TAP3.CallType
      {
        switch ( tokenString("IFW_TAP3.CallType.CALL_TYPE") )
	{
	  case "M":
	  {
	    lastCallTypeLevel1	= 1;
	    lastCallTypeLevel2	= 1;
	  }
	  break;
	  case "N":
	  {
	    lastCallTypeLevel1	= 1;
	    lastCallTypeLevel2	= 2;
	  }
	  break;
	  case "I":
	  {
	    lastCallTypeLevel1	= 2;
	    lastCallTypeLevel2	= 1;
	  }
	  break;
	  case "P":
	  {
	    lastCallTypeLevel1	= 1;
	    lastCallTypeLevel2	= 4;
	  }
	  break;
	  default: 
	  {
	    lastCallTypeLevel1	= 0;
	    lastCallTypeLevel2	= 0;
            logFormat( "unknown IFW_TAP3.CallType (tap0303): "+tokenString("IFW_TAP3.CallType.CALL_TYPE"));
	  }
	  break;
	}
      }
    | /* EMPTY */
      {
        lastCallTypeLevel1	= 0;
        lastCallTypeLevel2	= 0;
      }
    ;

  callTypeSubtype_opt:
      IFW_TAP3.CallTypeSubtype
      {
        lastCallTypeLevel3 = strToLong(tokenString("IFW_TAP3.CallTypeSubtype.CALL_TYPE_SUBTYPE"));
      }
    | /* EMPTY */
      {
        lastCallTypeLevel3 = 0;
      }
    ;

  camelCallReference:
      IFW_TAP3.CamelCallReference
      typeOfNumber_opt                
      numberingPlan_opt               
      {
	edrLong(DETAIL.ASS_CAMEL_EXT.MSC_TYPE_OF_NUMBER, 0)	= lastTypeOfNumber;
	edrString(DETAIL.ASS_CAMEL_EXT.MSC_NUMBERING_PLAN, 0)	= longToStr(lastNumberingPlan);
      }
      IFW_TAP3.AddressStringDigits         // mscAddress
      {
	edrString(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0) = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
      IFW_TAP3.CamelCallReferenceNumber
      {
	edrString(DETAIL.ASS_CAMEL_EXT.CAMEL_REFERENCE_NUMBER, 0) = tokenString("IFW_TAP3.CamelCallReferenceNumber.CAMEL_CALL_REFERENCE_NUMBER");
      }
      IFW_TAP3.Block_END
    ;

  camelDestination:
      IFW_TAP3.CamelDestination
      typeOfNumber_opt
      numberingPlan_opt
      {
	edrLong(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_TYPE_OF_NUMBER, 0)  = lastTypeOfNumber;
	edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBERING_PLAN, 0)= longToStr(lastNumberingPlan);
      }
      IFW_TAP3.AddressStringDigits	// camelDestinationNumber
      {
	edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0)= tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
	edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0) =
			    convertCli(	edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER_ORIGINAL, 0), 
					"00", 
					edrLong(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_TYPE_OF_NUMBER, 0),
					NORM_NAC,
					calledNumberAnalysisIACarray[1],// NORM_IAC,
					calledNumberAnalysisCCarray[1], // NORM_CC,
					NORM_IAC_SIGN,
					NORM_NDC );
      }
      IFW_TAP3.Block_END
    ;

  camelDestination_opt:
      camelDestination
    | /* EMPTY */
    ;

  camelInitiatedCFIndicator_opt:
      IFW_TAP3.CamelInitiatedCFIndicator
      {
	edrLong(DETAIL.ASS_CAMEL_EXT.CAMEL_INITIATED_CF_INDICATOR, 0) =
		tokenLong("IFW_TAP3.CamelInitiatedCFIndicator.CAMEL_INITIATED_CF_INDICATOR");
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
      }
    ;

  camelModificationList_opt:
      IFW_TAP3.CamelModificationList
      camelModificationList
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastCamelModificationList = "";
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
        }
        records = records+1;
        edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)	= edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
        edrString(DETAIL.ASS_CAMEL_EXT.RECORD_TYPE, 0)	= extension_CAMEL;
        edrLong(DETAIL.ASS_CAMEL_EXT.RECORD_NUMBER, 0)	= records;
      }
      typeOfNumber_opt
      numberingPlan_opt
      {
	edrLong(DETAIL.ASS_CAMEL_EXT.SERVER_TYPE_OF_NUMBER, 0)	= lastTypeOfNumber;
	edrString(DETAIL.ASS_CAMEL_EXT.SERVER_NUMBERING_PLAN, 0)= longToStr(lastNumberingPlan);
      }
      IFW_TAP3.AddressStringDigits  //camelServerAddress
      {
	edrString(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0) = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
      IFW_TAP3.CamelServiceLevel
      {
	edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_LEVEL, 0) = tokenLong("IFW_TAP3.CamelServiceLevel.CAMEL_SERVICE_LEVEL");
      }
      IFW_TAP3.CamelServiceKey
      {
	edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_KEY, 0) = tokenLong("IFW_TAP3.CamelServiceKey.CAMEL_SERVICE_KEY");
      }
      defaultCallHandlingIndicator_opt
      camelCallReference
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
      camelDestination_opt  
      cseInformation_opt
      IFW_TAP3.Block_END
    | /* EMPTY */
    ;

  causeForTerm_opt:
      IFW_TAP3.CauseForTerm
      {
        // TAP3 codes must be stored in a 2 digit string (prepend with 0 if necessary)
	Long tmp_CFT = tokenLong("IFW_TAP3.CauseForTerm.CAUSE_FOR_TERM");
	if (tmp_CFT < 10)
	{
          edrString(DETAIL.CALL_COMPLETION_INDICATOR) = "0" + longToStr(tmp_CFT);
	}
	else
	{
          edrString(DETAIL.CALL_COMPLETION_INDICATOR) = longToStr(tmp_CFT);
	}
      }
    | /* EMPTY */
    ;

  cellId_opt:
      IFW_TAP3.CellId
      {
        if (record_Type == record_GPRS)
	{
	  edrString(DETAIL.ASS_GPRS_EXT.CELL_ID, 0) = longToStr( tokenLong("IFW_TAP3.CellId.CELL_ID") );
        }
	else
	{
	  edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0) = longToStr( tokenLong("IFW_TAP3.CellId.CELL_ID") );
	}
      }
    | /* EMPTY */
    ;

  channelCodingsAcceptable:
      IFW_TAP3.ChannelCodingsAcceptable
      channelCodingsList
      IFW_TAP3.Block_END
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
      }
    | /* EMPTY */
      {
	lastChargeableUnits = 0;
      }
    ;

  chargeableSubscriber:
      simChargeableSubscriber
    | IFW_TAP3.Min
    ;

  chargedUnits_opt:
      IFW_TAP3.ChargedUnits
      {
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
      }
      chargeType_opt
      charge_opt
      chargeableUnits_opt
      chargedUnits_opt
      chargeDetailTimeStamp_opt
      IFW_TAP3.DayCategory
      {
        lastDayCategory = tokenString("IFW_TAP3.DayCategory.DAY_CATEGORY");
      }
      dayCategorySubtype_opt
      IFW_TAP3.TimeBand
      {
        lastTimeBand = tokenString("IFW_TAP3.TimeBand.TIME_BAND");
      }
      timeBandSubtype_opt
      multiRateIndicator_opt
      {
        // add the CP(s) for BasicServiceUsed / GprsServiceUsed / CamelServiceUsed / VasServiceUsed / MSSrecord / SCUrecord
        if ( (service_Type == service_Basic) or (service_Type == service_Gprs) or (service_Type == service_Camel) or (service_Type == service_Vas) or
	     (record_Type == record_MSS) or (record_Type == record_SCU)
	   )
	{
	  if ( edrAddDatablock( DETAIL.ASS_CBD.CP ) == false ) 
	  {
	    String Msg = "failed to add CHARGE_PACKET datablock " + longToStr(successiveChargeDetail) +
			 " for ASS_CBD " + longToStr(successiveChargeInformation) +
			 " for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER));
	    edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
	  }	  
          successiveChargePacket   = successiveChargePacket   +1;
          successiveChargePacketCI = successiveChargePacketCI +1;

	  // Store the collected data
	  Long    CPidx              = successiveChargePacket-1 ;
	  Decimal ChargedAmountValue = (lastCharge * lastExchangeRateFactor); //after discount, before tax

	  //defaults
//	  edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)		= "R"; //default is overwritten a few lines after
	  edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, 0, CPidx)	= "*";
	  edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)	= "S";
	  edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, 0, CPidx)		= "N";
	  edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, CPidx)	= "R";
	  edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, 0, CPidx)	= "N";
	  // collected
	  edrString(DETAIL.ASS_CBD.CP.RUM, 0, CPidx)			= lastChargedItem;
	  edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)		= "W";
	  edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, CPidx)	= lastChargeType;
	  edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, CPidx)	= ChargedAmountValue ;
	  edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, CPidx)= longToDecimal(lastChargedUnits);
	  edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, CPidx)= longToDecimal(lastChargeableUnits);

	  // used for aggregation packet special treatement
	  if ( lastChargeType == "00" )
	  {
	    lastCPidx_00						= CPidx;
	    lastChargedAmountValue_00					= ChargedAmountValue;
	    lastChargeableUnits_00					= lastChargeableUnits;
            lastChargedUnits_00                                         = lastChargedUnits;
	  }

	  if (bUseLocalCurrency)
	  {
	    edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= theLocalCurrency;
	    edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)	  = (1.0 / lastExchangeRateFactorValue);
	    edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)	  = theTapCurrency;
	  }
	  else
	  {
	    edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= theTapCurrency;
	    edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)	  = lastExchangeRateFactorValue;
	    edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)	  = theLocalCurrency;
	  }

	  edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, CPidx) = strToDate(lastChargeDetailTimeStamp);
	  edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx)		= lastDayCategory;
	  edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx)	= lastTimeBand;

          if ( service_Type == service_Vas )
	  {
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)	= getVasShortDesc( lastVasCode );
	  }
          else if ( service_Type == service_Camel )
	  {
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)	= "CAMEL";
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
	successiveChargeInformation	= successiveChargeInformation +1;
	initializeChargeDetailTempFields();
	successiveChargeDetail		= 0;
	successiveChargePacketCI	= 0;

	lastCPidx_00			= (-1); //invalid, ie. not received
	lastChargedAmountValue_00	= 0.0;
	lastChargeableUnits_00		= 0;
	lastChargedUnits_00		= 0;
	
	sumTaxChargeCI			  = 0.0;
	sumChargedAmountValueCI		  = 0.0;
        sumChargeableUnitsCI              = 0;
        sumChargedUnitsCI                 = 0;

//logStdout("successive chargeInformation block number "+longToStr(successiveChargeInformation)+" for EDR "+longToStr(edrLong(DETAIL.RECORD_NUMBER))+"\n");
	
	// create only one ASS_CBD per BasicServiceUsed / GprsServiceUsed / MSSrecord / SCUrecord / VASrecord
        if ( (service_Type == service_Basic) or (service_Type == service_Gprs) or
	     (record_Type == record_MSS) or (record_Type == record_SCU) or (record_Type == record_VAS)
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
	    edrLong( DETAIL.NUMBER_ASSOCIATED_RECORDS)= edrLong( DETAIL.NUMBER_ASSOCIATED_RECORDS) +1;
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
      callType_opt
      callTypeSubtype_opt
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
	sumChargedAmountValueFile	= sumChargedAmountValueFile	   + sumChargedAmountValueCI;
	sumChargedAmountValueEDR	= sumChargedAmountValueEDR	   + sumChargedAmountValueCI;
	if      (lastChargedItem == "D") //Duration
	{
	  sumChargeableUnitsDuration	= sumChargeableUnitsDuration		+ sumChargeableUnitsCI;
	}
	else if ( (lastChargedItem == "V") or (lastChargedItem == "X") ) //Volume sent / Volume global
	{
	  sumChargeableUnitsVolumeSent	= sumChargeableUnitsVolumeSent		+ sumChargeableUnitsCI;
	}
	else if (lastChargedItem == "W") //Volume received
	{
	  sumChargeableUnitsVolumeReceived= sumChargeableUnitsVolumeReceived	+ sumChargeableUnitsCI;
	}
	else if (lastChargedItem == "E") //Event
	{
	  sumChargeableUnitsEvents	= sumChargeableUnitsEvents		+ sumChargeableUnitsCI;
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
	    Long CPidx               = successiveChargePacket;
            successiveChargePacket   = successiveChargePacket   +1;
            successiveChargePacketCI = successiveChargePacketCI +1;
	    
	    // flag the original aggregation packet as not aggregation CP and as duplicate
	    edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, lastCPidx_00) = "A";
	    edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, lastCPidx_00) = ""; //so that it is not recorgnized by the output

	    //defaults
//	    edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)	= "R"; //default is overwritten a few lines after
	    edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, 0, CPidx)	= "*";
//	    edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)	= "S";
	    edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, 0, CPidx)		= "N";
	    edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, CPidx)= "R";
	    edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, 0, CPidx)= "N";
	    // duplicated
	    edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)	= "W";
	    edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)	= "A";
	    edrString(DETAIL.ASS_CBD.CP.RUM, 0, CPidx)			= edrString(DETAIL.ASS_CBD.CP.RUM, 0, lastCPidx_00);
	    edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, CPidx)	= "00";
	    edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, CPidx)= edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, lastCPidx_00) ;
	    edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, CPidx)= edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, lastCPidx_00);
	    edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, CPidx)= edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, lastCPidx_00);
	    edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, lastCPidx_00);
	    edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)	= edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, lastCPidx_00);
	    edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, lastCPidx_00);
	    edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, CPidx)= edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, lastCPidx_00);
	    edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx)		= edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, lastCPidx_00);
	    edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, lastCPidx_00);
            edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, lastCPidx_00);
	    edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, lastCPidx_00);
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
	  Long CPidx               = successiveChargePacket;
          successiveChargePacket   = successiveChargePacket   +1;
          successiveChargePacketCI = successiveChargePacketCI +1;
	  Long prevCPidx           = CPidx -1 ; //the last one added is used as sample
	  //defaults
//	  edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)	= "R"; //default is overwritten a few lines after
	  edrString(DETAIL.ASS_CBD.CP.SERVICE_CLASS_USED, 0, CPidx)	= "*";
//	  edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)	= "S";
	  edrString(DETAIL.ASS_CBD.CP.CHARGE_TYPE, 0, CPidx)		= "N";
	  edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, CPidx)= "R";
	  edrString(DETAIL.ASS_CBD.CP.CHARGED_TAX_TREATMENT, 0, CPidx)= "N";
	  // generated
	  edrString(DETAIL.ASS_CBD.CP.RATEPLAN_TYPE, 0, CPidx)	= "W";
	  edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE, 0, CPidx)	= "A";
	  edrString(DETAIL.ASS_CBD.CP.RUM, 0, CPidx)			= edrString(DETAIL.ASS_CBD.CP.RUM, 0, prevCPidx);
	  edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, CPidx)	= "00";
	  edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, CPidx)	= sumChargedAmountValueCI ;
	  edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, CPidx)	= longToDecimal(sumChargedUnitsCI);
	  edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, CPidx)	= longToDecimal(sumChargeableUnitsCI);
	  edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, CPidx)= edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, prevCPidx);
	  edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, CPidx)	= edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, prevCPidx);
	  edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, prevCPidx);
	  edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, CPidx)= edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, prevCPidx);
	  if (successiveChargePacketCI == 2)
	  {
	    edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx)		= edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, prevCPidx);
	    edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, prevCPidx);
	  }
	  else
	  {
	    edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, CPidx)		= "N";
	    edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, CPidx)	= "I";
          }
          edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, prevCPidx);
	  edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, CPidx)	= edrString(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_UOM, 0, prevCPidx);
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
	  edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, 0, successiveChargePacket-1)= (lastDiscountValue * lastExchangeRateFactor);
	}
      }
      IFW_TAP3.Block_END
    ;

  chargeInformation_opt:
      chargeInformation
    | /* EMPTY */
    ;

  chargeInformationList:
      chargeInformationList chargeInformation
    | chargeInformation
    ;

  chargeType_opt:
      IFW_TAP3.ChargeType
      {
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
        lastCharge = (longToDecimal(tokenLong("IFW_TAP3.Charge.CHARGE")) / theAbsoluteAmountDivider);
      }
    | /* EMPTY */
      {
        lastCharge = 0.0;
      }
    ;

  chargingTimeStamp_opt:
      IFW_TAP3.ChargingTimeStamp
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
          edrDate(DETAIL.CHARGING_START_TIMESTAMP) = strToDate(lastLocalTimeStamp);
	  edrDate(DETAIL.CHARGING_END_TIMESTAMP)   = strToDate(lastLocalTimeStamp);
	  edrString(DETAIL.UTC_TIME_OFFSET)        = lastUtcTimeOffset;
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
	edrString(DETAIL.ASS_CAMEL_EXT.CSE_INFORMATION, 0) = tokenString("IFW_TAP3.CseInformation.CSE_INFORMATION");
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
      }
      IFW_TAP3.UtcTimeOffsetCode
      {
	// get the corresponding UtcTimeOffset from the UtcTimeOffsetCode
	lastUtcTimeOffset  = getUtcTimeOffset( tokenLong("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE") );
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
	edrLong(DETAIL.ASS_CAMEL_EXT.DEFAULT_CALL_HANDLING_INDICATOR, 0) = 
		tokenLong("IFW_TAP3.DefaultCallHandlingIndicator.DEFAULT_CALL_HANDLING_INDICATOR");
      }
    | /* EMPTY */
    ;  

  destination:
      IFW_TAP3.Destination
      typeOfNumber_opt
      numberingPlan_opt
      calledNumber_opt
      modificationIndicator_opt
      calledPlace_opt
      calledRegion_opt
      calledNumAnalysisCode_opt
      IFW_TAP3.Block_END
      {
        edrLong(DETAIL.B_TYPE_OF_NUMBER)           = lastTypeOfNumber;
        edrString(DETAIL.B_NUMBERING_PLAN)         = longToStr(lastNumberingPlan);
	if (lastModificationIndicator > 0)
	{
          edrString(DETAIL.B_MODIFICATION_INDICATOR) = "08";
        }
	
	//normalize the number
	edrString(DETAIL.B_NUMBER) = convertCli(edrString(DETAIL.B_NUMBER), 
						edrString(DETAIL.B_MODIFICATION_INDICATOR), 
						edrLong(DETAIL.B_TYPE_OF_NUMBER),
						NORM_NAC,
						calledNumberAnalysisIACarray[lastCalledNumAnalysisCode],// NORM_IAC,
						calledNumberAnalysisCCarray[lastCalledNumAnalysisCode],// NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
	edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);

        lastTypeOfNumber          = 0;
        lastNumberingPlan         = 0;
        lastModificationIndicator = 0;
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
        edrString(DETAIL.DESTINATION_NETWORK) = tokenString("IFW_TAP3.DestinationNetwork.NETWORK_ID");
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
	lastExchangeRateFactorValue	= getExchangeRateFactor( tokenLong("IFW_TAP3.ExchangeRateCode.CODE") );
	if (bUseLocalCurrency)
	{
	  lastExchangeRateFactor	= lastExchangeRateFactorValue;
	}
	else
	{
	  lastExchangeRateFactor	= 1.0;  // (to store SDRcount)
	}
      }
    | /* EMPTY */
      {
        //this case only happens when no ChargeDetail with a charge are attached
        lastExchangeRateFactorValue	= 1.0;
	lastExchangeRateFactor		= lastExchangeRateFactorValue;
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
	exchangeRateFactor[lastCode]	= ( longToDecimal(exchangeRate[lastCode]) / longToDecimal(nbDecimals) );
	if (currencyEntries <= lastCode)
	{
	  currencyEntries               = lastCode +1;
	}
      }
      IFW_TAP3.Block_END
    ;

  fileAvailableTimeStamp:
      IFW_TAP3.FileAvailableTimeStamp
      dateTimeLong
      IFW_TAP3.Block_END
      {
        theFileAvailableTimeStamp     = lastLocalTimeStamp;
        theFileAvailableUtcTimeOffset = lastUtcTimeOffset;
      }
    ;      

  fileCreationTimeStamp:
      IFW_TAP3.FileCreationTimeStamp
      dateTimeLong
      IFW_TAP3.Block_END
      {
        theFileCreationTimeStamp     = lastLocalTimeStamp;
        theFileCreationUtcTimeOffset = lastUtcTimeOffset;
      }
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
      networkInitPDPContext_opt
      IFW_TAP3.ChargingId
      {
	edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0)	= decimalToStr(tokenDecimal("IFW_TAP3.ChargingId.CHARGING_ID"),0);
	//edrString(DETAIL.CHAIN_REFERENCE)		= edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0); //TODO activate for GPRS callAssembly
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
      valueAddedServiceUsedList_opt
      {
        // add the charge info provided by the VAS ChargeDetail block to the global Detail
	updateBasicDetailWithVasCharge();
      }
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  gprsChargeableSubscriber:
      IFW_TAP3.GprsChargeableSubscriber
      IFW_TAP3.Imsi
      {
        edrString(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0) = tokenString("IFW_TAP3.Imsi.IMSI");
        edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)    = "I"; //I=IMSI , M=MSISDN, P=IP , S=SIM , ...
      }
      msisdn_opt
      IFW_TAP3.PdpType
      {
        edrString(DETAIL.ASS_GPRS_EXT.PDP_TYPE, 0)    = longToStr( tokenLong("IFW_TAP3.PdpType.PDP_TYPE") );
      }
      IFW_TAP3.PdpAddress
      {
        edrString(DETAIL.ASS_GPRS_EXT.PDP_ADDRESS, 0) = tokenString("IFW_TAP3.PdpAddress.PDP_ADDRESS");
      }
      IFW_TAP3.Block_END
    ;

  gprsDestination:
      IFW_TAP3.GprsDestination
      IFW_TAP3.AccessPointName
      {
        edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0) = tokenString("IFW_TAP3.AccessPointName.ACCESS_POINT_NAME");
      }
      remotePdpAddressList_opt
      {
        edrString(DETAIL.ASS_GPRS_EXT.PDP_REMOTE_ADDRESS, 0) = lastRemotePdpAddressList ;
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
	sumDataVolumeIncoming  = sumDataVolumeIncoming + 
				 longToDecimal(tokenLong("IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING"));
      }
      IFW_TAP3.DataVolumeOutgoing
      {
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
	service_Type		        = service_Gprs;
	// initialise the counters of volume (different block for each QoS)
 	lastQoSRequestedDelay		=0;
	lastQoSRequestedMeanThroughput	=0;
	lastQoSRequestedPeakThroughput	=0;
	lastQoSRequestedPrecedence	=0;
	lastQoSRequestedReliability	=0;
 	lastQoSUsedDelay		=0;
	lastQoSUsedMeanThroughput	=0;
	lastQoSUsedPeakThroughput	=0;
	lastQoSUsedPrecedence		=0;
	lastQoSUsedReliability		=0;
        sumDataVolumeIncoming		=0.0;
        sumDataVolumeOutgoing		=0.0;
      }
      IFW_TAP3.GprsServiceUsageList
      gprsServiceUsageList
      IFW_TAP3.Block_END
      {
        // store the collected data
	edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_DELAY, 0)		= longToStr(lastQoSRequestedDelay);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_MEAN_THROUGHPUT, 0)	= longToStr(lastQoSRequestedMeanThroughput);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PEAK_THROUGHPUT, 0)	= longToStr(lastQoSRequestedPeakThroughput);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PRECEDENCE, 0)	= longToStr(lastQoSRequestedPrecedence);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_RELIABILITY, 0)	= longToStr(lastQoSRequestedReliability);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_DELAY, 0)		= longToStr(lastQoSUsedDelay);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_MEAN_THROUGHPUT, 0)	= longToStr(lastQoSUsedMeanThroughput);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_PEAK_THROUGHPUT, 0)	= longToStr(lastQoSUsedPeakThroughput);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_PRECEDENCE, 0)		= longToStr(lastQoSUsedPrecedence);
	edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_RELIABILITY, 0)		= longToStr(lastQoSUsedReliability);	
	edrDecimal(DETAIL.VOLUME_RECEIVED) 				= sumDataVolumeIncoming;
	edrDecimal(DETAIL.VOLUME_SENT)     				= sumDataVolumeOutgoing;
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

  gsnAddress:
      IFW_TAP3.IPTextV4Address
      {
        last_recEntityId_Type = recEntityId_iPTextV4Address;
        last_recEntityId      = tokenString("IFW_TAP3.IPTextV4Address.IP_TEXT_V4_ADDRESS");
      } 
    | IFW_TAP3.IPTextV6Address
      {
        last_recEntityId_Type = recEntityId_iPTextV6Address;
        last_recEntityId      = tokenString("IFW_TAP3.IPTextV6Address.IP_TEXT_V6_ADDRESS");
      } 
    ;

  homeLocationInformation_opt:
      IFW_TAP3.HomeLocationInformation
      IFW_TAP3.HomeBid
      IFW_TAP3.LocationDescription
      IFW_TAP3.Block_END
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
      hSCSDParameterModificationList
      IFW_TAP3.Block_END
    | /* EMPTY */
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
      	  edrString(DETAIL.ASS_GPRS_EXT.DEVICE_NUMBER, 0) = tokenString("IFW_TAP3.Imei.IMEI");
        }
	else
	{
      	  edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) = tokenString("IFW_TAP3.Imei.IMEI");
        }	
      }
    | IFW_TAP3.Esn
    | /* EMTPY */
    ;
    

  latitude_opt:
      IFW_TAP3.Latitude
    | /* EMTPY */
    ;

  locationArea_opt:
      IFW_TAP3.LocationArea
      {
        if (record_Type == record_GPRS)
	{
	  edrString(DETAIL.ASS_GPRS_EXT.LOCATION_AREA_INDICATOR, 0) = longToStr( tokenLong("IFW_TAP3.LocationArea.LOCATION_AREA") );
        }
	else
	{
      	  edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0) = longToStr( tokenLong("IFW_TAP3.LocationArea.LOCATION_AREA") );
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
      messageDescriptionDefinitionList
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
      	  edrLong(DETAIL.ASS_GPRS_EXT.MS_CLASS_MARK, 0) = tokenLong("IFW_TAP3.MobileStationClassMark.MOBILE_STATION_CLASS_MARK");
	}
	else // if ( (record_Type == record_MOC) or (record_Type == record_MTC) or (record_Type == record_MSS))
	{
      	  edrLong(DETAIL.ASS_GSMW_EXT.MS_CLASS_MARK, 0) = tokenLong("IFW_TAP3.MobileStationClassMark.MOBILE_STATION_CLASS_MARK");
	}
      }
    | /* EMPTY */
    ;

  modificationIndicator_opt:
      IFW_TAP3.ModificationIndicator
      {
        lastModificationIndicator = tokenLong("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR");
      }
    | /* EMPTY */
      {
        lastModificationIndicator = 0;
      }
    ;
   

  msisdn_opt:
      IFW_TAP3.Msisdn
      {
//	edrString(DETAIL.A_NUMBER)             = tokenString("IFW_TAP3.Msisdn.MSISDN");
	edrString(DETAIL.A_NUMBER) = convertCli( tokenString("IFW_TAP3.Msisdn.MSISDN"),
						"00", 0,
						NORM_NAC,
						calledNumberAnalysisIACarray[1],// NORM_IAC,
						calledNumberAnalysisCCarray[1], // NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
        edrString(DETAIL.INTERN_A_NUMBER_ZONE) = edrString(DETAIL.A_NUMBER);
	
	if      (record_Type == record_GPRS)
	{
          edrString(DETAIL.ASS_GPRS_EXT.A_NUMBER_USER, 0) = tokenString("IFW_TAP3.Msisdn.MSISDN");
	}
        else if (record_Type == record_MTC)
	{
          edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0) = tokenString("IFW_TAP3.Msisdn.MSISDN");
	}
	else
	{
          edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0) = tokenString("IFW_TAP3.Msisdn.MSISDN");
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
      utcTimeOffsetInfo
      recEntityInfo_opt
      IFW_TAP3.NetworkType
      {
        // here we are in the header, so we are getting info regarding the Sender Network
	theSenderNetworkType = tokenLong("IFW_TAP3.NetworkType.NETWORK_TYPE");
      }
      IFW_TAP3.CalledNumAnalysisList
      calledNumAnalysisList
      IFW_TAP3.Block_END
      IFW_TAP3.Block_END
    ;

  networkInitPDPContext_opt:
      IFW_TAP3.NetworkInitPDPContext
      {
        edrLong(DETAIL.ASS_GPRS_EXT.NETWORK_INITIATED_PDP, 0) = tokenLong("IFW_TAP3.NetworkInitPDPContext.NETWORK_INIT_PDP_CONTEXT");
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
	theRecEntityId	= getRecEntityId(tokenLong("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE"));
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
          edrString(DETAIL.SOURCE_NETWORK_TYPE)      = longToStr(tokenLong("IFW_TAP3.NetworkType.NETWORK_TYPE"));
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

  nonChargedNumber:
      IFW_TAP3.AddressStringDigits
      {
        lastNonChargedNumber = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    ;

  nonChargedParty:
      IFW_TAP3.NonChargedParty
      typeOfNumber_opt
      numberingPlan_opt
      nonChargedNumber
      calledNumAnalysisCode_opt
      modificationIndicator_opt
      IFW_TAP3.Block_END
      {
        edrLong(DETAIL.B_TYPE_OF_NUMBER)                 = lastTypeOfNumber;
        edrString(DETAIL.B_NUMBERING_PLAN)               = longToStr(lastNumberingPlan);
	if ( edrLong(DETAIL.USAGE_DIRECTION) == 0 )
	{
          edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0) = lastNonChargedNumber;
	}
	else
	{
          edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0) = edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER,0);
          edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER,0) = lastNonChargedNumber;
	}
	if (lastModificationIndicator > 0)
	{
          edrString(DETAIL.B_MODIFICATION_INDICATOR) = "08";
        }
	
//	edrString(DETAIL.B_NUMBER)			 = lastNonChargedNumber;
//	edrString(DETAIL.INTERN_B_NUMBER_ZONE)		 = lastNonChargedNumber;
	//normalize the number
	edrString(DETAIL.B_NUMBER) = convertCli(lastNonChargedNumber, 
						edrString(DETAIL.B_MODIFICATION_INDICATOR), 
						edrLong(DETAIL.B_TYPE_OF_NUMBER),
						NORM_NAC,
						calledNumberAnalysisIACarray[lastCalledNumAnalysisCode],// NORM_IAC,
						calledNumberAnalysisCCarray[lastCalledNumAnalysisCode], // NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
	edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);

        lastTypeOfNumber          = 0;
        lastNumberingPlan         = 0;
	lastNonChargedNumber      = defTelNumber;
        lastModificationIndicator = 0;
	lastCalledNumAnalysisCode = 1;
      }
    ;

  numberingPlan_opt:
      IFW_TAP3.NumberingPlan
      {
        lastNumberingPlan = tokenLong("IFW_TAP3.NumberingPlan.NUMBERING_PLAN");
      }
    | /* EMPTY */
      {
        lastNumberingPlan = 0;
      }
    ;

  numberOfChannels_opt:
      IFW_TAP3.NumberOfChannels
    | /* EMPTY */
    ;

  operatorSpecInformation_opt:
      IFW_TAP3.OperatorSpecInformation
    | /* EMPTY */
    ;

  originatingNetwork_opt:
      IFW_TAP3.OriginatingNetwork
      {
        edrString(DETAIL.SOURCE_NETWORK) = tokenString("IFW_TAP3.OriginatingNetwork.NETWORK_ID");
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
        edrString(DETAIL.LONG_DURATION_INDICATOR) = tokenString("IFW_TAP3.PartialTypeIndicator.PARTIAL_TYPE_INDICATOR");
      }
    | /* EMPTY */
    ;
   
  qoSInformation:
      IFW_TAP3.QoSDelay
      {
        lastQoSDelay = tokenLong("IFW_TAP3.QoSDelay.QOS_INTEGER");
      }
      IFW_TAP3.QoSMeanThroughput
      {
        lastQoSMeanThroughput = tokenLong("IFW_TAP3.QoSMeanThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPeakThroughput
      {
        lastQoSPeakThroughput = tokenLong("IFW_TAP3.QoSPeakThroughput.QOS_INTEGER");
      }
      IFW_TAP3.QoSPrecedence
      {
        lastQoSPrecedence = tokenLong("IFW_TAP3.QoSPrecedence.QOS_INTEGER");
      }
      IFW_TAP3.QoSReliability
      {
        lastQoSReliability = tokenLong("IFW_TAP3.QoSReliability.QOS_INTEGER");
      }
    ;

  qoSRequested_opt:
      IFW_TAP3.QoSRequested
      qoSInformation
      IFW_TAP3.Block_END
      {
	lastQoSRequestedDelay		= lastQoSDelay;
	lastQoSRequestedMeanThroughput	= lastQoSMeanThroughput;	
	lastQoSRequestedPeakThroughput	= lastQoSPeakThroughput;	
	lastQoSRequestedPrecedence	= lastQoSPrecedence;	
	lastQoSRequestedReliability	= lastQoSReliability;		
      }
    | /* EMPTY */
      {
        //initialisation
	lastQoSRequestedDelay		= 0;
	lastQoSRequestedMeanThroughput	= 0;
	lastQoSRequestedPeakThroughput	= 0;
	lastQoSRequestedPrecedence	= 0;
	lastQoSRequestedReliability	= 0;
      }
    ;

  qoSUsed:
      IFW_TAP3.QoSUsed
      qoSInformation
      IFW_TAP3.Block_END
      {
	lastQoSUsedDelay		= lastQoSDelay;
	lastQoSUsedMeanThroughput	= lastQoSMeanThroughput;	
	lastQoSUsedPeakThroughput	= lastQoSPeakThroughput;	
	lastQoSUsedPrecedence		= lastQoSPrecedence;	
	lastQoSUsedReliability		= lastQoSReliability;		
      }
    ;

  rapFileSequenceNumber_opt:
      IFW_TAP3.RapFileSequenceNumber
    | /* EMPTY */
    ;

  radioChannelRequested_opt:
      IFW_TAP3.RadioChannelRequested
      {
	lastRadioChannelRequested = tokenLong("IFW_TAP3.RadioChannelRequested.RADIO_CHANNEL_REQUESTED");    
      }
    | /* EMPTY */
      {
	lastRadioChannelRequested = 0;    
      }
    ;

  radioChannelUsed_opt:
      IFW_TAP3.RadioChannelUsed
      {
	lastRadioChannelUsed = tokenLong("IFW_TAP3.RadioChannelUsed.RADIO_CHANNEL_USED");
      }
    | /* EMPTY */
      {
	lastRadioChannelUsed = 0;
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
    | gsnAddress
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
      remotePdpAddressList
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastRemotePdpAddressList = "";
      }
    ;
   
  scuBasicInformation:
      IFW_TAP3.ScuBasicInformation
      scuVasChargeableSubscriber
      IFW_TAP3.ChargedPartyStatus
      {
        edrLong(DETAIL.USAGE_DIRECTION) = tokenLong("IFW_TAP3.ChargedPartyStatus.CHARGED_PARTY_STATUS");
      }
      nonChargedParty
      clirIndicator_opt
      originatingNetwork_opt
      destinationNetwork_opt
      IFW_TAP3.Block_END
    ;

  scuChargeType:
      IFW_TAP3.ScuChargeType
      IFW_TAP3.MessageStatus
      {
        edrString(DETAIL.CALL_COMPLETION_INDICATOR) = longToStr(tokenLong("IFW_TAP3.MessageStatus.MESSAGE_STATUS"));
      }
      IFW_TAP3.PriorityCode
      {
        edrString(DETAIL.QOS_REQUESTED) = longToStr(tokenLong("IFW_TAP3.PriorityCode.PRIORITY_CODE"));
      }
      distanceChargeBandCode_opt
      IFW_TAP3.MessageType
      {
        edrString(DETAIL.QOS_USED) = longToStr(tokenLong("IFW_TAP3.MessageType.MESSAGE_TYPE")); //TODO find a better storage
      }
      IFW_TAP3.MessageDescriptionCode
      {
        edrString(DETAIL.DESCRIPTION) = getMessageDescription(tokenLong("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE"));
      }
      IFW_TAP3.Block_END
    ;

  scuTimeStamps:
      IFW_TAP3.ScuTimeStamps
      IFW_TAP3.DepositTimeStamp
      dateTime
      IFW_TAP3.Block_END
      {
        // Mandatory field for SCU, will serve as a default
	lastValidLocalTimeStamp = lastLocalTimeStamp; // to serve as default LocalTimeStamp for coresponding record
	lastValidUtcTimeOffset  = lastUtcTimeOffset;  // to serve as default UtcTimeOffset for coresponding record
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) = strToDate(lastLocalTimeStamp);
        edrString(DETAIL.UTC_TIME_OFFSET)        = lastUtcTimeOffset;
      }
      IFW_TAP3.CompletionTimeStamp
      dateTime
      IFW_TAP3.Block_END
      {
        edrDate(DETAIL.CHARGING_END_TIMESTAMP)   = strToDate(lastLocalTimeStamp);
      }
      IFW_TAP3.ChargingPoint
      IFW_TAP3.Block_END
    ;

  scuVasChargeableSubscriber:
      simChargeableSubscriber
    | IFW_TAP3.Msisdn
      {
//	edrString(DETAIL.A_NUMBER)			= tokenString("IFW_TAP3.Msisdn.MSISDN");
	edrString(DETAIL.A_NUMBER) = convertCli( tokenString("IFW_TAP3.Msisdn.MSISDN"),
						"00", 0,
						NORM_NAC,
						calledNumberAnalysisIACarray[1],// NORM_IAC,
						calledNumberAnalysisCCarray[1], // NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
        edrString(DETAIL.INTERN_A_NUMBER_ZONE)		= edrString(DETAIL.A_NUMBER);
        edrString(DETAIL.ASS_GSMW_EXT.A_NUMBER_USER, 0)	= tokenString("IFW_TAP3.Msisdn.MSISDN");
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
        edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) = tokenString("IFW_TAP3.Imsi.IMSI");
        edrString(DETAIL.TYPE_OF_A_IDENTIFICATION)    = "I"; //I=IMSI , M=MSISDN, P=IP , S=SIM , ...
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
      supplServiceUsed
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
      IFW_TAP3.SupplServiceCode
      {
	service_Type		  = service_Suppl;
	lastSupplServiceEventCode = tokenString("IFW_TAP3.SupplServiceCode.SUPPL_SERVICE_CODE");
      }
      IFW_TAP3.SupplServiceActionCode
      {
	lastSupplServiceActionCode = longToStr( tokenLong("IFW_TAP3.SupplServiceActionCode.SUPPL_SERVICE_ACTION_CODE") );	     
      }
      ssParameters_opt
      thirdPartyInformation_opt
      chargingTimeStamp_opt
      chargeInformation_opt
      basicServiceCodeList_opt
      IFW_TAP3.Block_END
      {
	Long tmp_SsPacketIdx= 0;
        if (record_Type == record_MSS)
	{
	  // add a corresponding SS_PACKET
	  if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.SS_PACKET ) == false ) 
	  { 
	    String Msg = "failed to add ASS_GSMW_EXT.SS_PACKET datablock";
	    edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
	  }
	  //store the data in the SS_PACKET
	  tmp_SsPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0);
	  edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,tmp_SsPacketIdx)    = lastSupplServiceEventCode;
	  edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,tmp_SsPacketIdx) = lastSupplServiceActionCode;
	  edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0)                   = tmp_SsPacketIdx + 1;
	      
	  // and the third party info
	  edrLong(DETAIL.C_TYPE_OF_NUMBER)           = lastThirdPartyTypeOfNumber;
	  edrString(DETAIL.C_NUMBERING_PLAN)         = longToStr(lastThirdPartyNumberingPlan);
	  if (lastThirdPartyModificationIndicator > 0)
	  {
            edrString(DETAIL.C_MODIFICATION_INDICATOR) = "08";
          }
	  
//	  edrString(DETAIL.C_NUMBER)                 = lastThirdPartyNumber;
	  //normalize the number
	  edrString(DETAIL.C_NUMBER) = convertCli(lastThirdPartyNumber, 
						edrString(DETAIL.C_MODIFICATION_INDICATOR), 
						edrLong(DETAIL.C_TYPE_OF_NUMBER),
						NORM_NAC,
						calledNumberAnalysisIACarray[1],// NORM_IAC,
						calledNumberAnalysisCCarray[1], // NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
	  edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);

	  // and the last affected BasicService
	  if (SsBasicServicesAffectedNb > 0)
	  {
	    edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE, 0) = SsBasicServicesAffected[SsBasicServicesAffectedNb-1]; //TODO find a better storage place
	  }
	}
	else if ( (record_Type == record_MOC) or (record_Type == record_MTC) )
	{
          // add a SS_PACKET to each duplicated record using a BasicService of the list of affected services
	  // (or to All of them if there are no specified affected services)
	  Long iterIdx        = 0;
	  Long iterCodes      = 0;
	  Long NbUsedRecords  = theLastEdrCopy;
	  if (NbUsedRecords == 0)
	  {
	    NbUsedRecords=1;
	  }
	  for ( iterIdx = 0 ; iterIdx < NbUsedRecords ; iterIdx = iterIdx + 1 )
	  {
	    edrSetCurrent(iterIdx);
	    
	    if ( SsBasicServicesAffectedNb == 0 )
	    {
	      // add a corresponding SS_PACKET
	      if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.SS_PACKET ) == false ) 
	      { 
		String Msg = "failed to add ASS_GSMW_EXT.SS_PACKET datablock";
		edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
	      }
	      tmp_SsPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0);
	      edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,tmp_SsPacketIdx)    = lastSupplServiceEventCode;
	      edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,tmp_SsPacketIdx) = lastSupplServiceActionCode;
	      edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0)                   = tmp_SsPacketIdx + 1;
	      
	      // and the third party info
	      edrLong(DETAIL.C_TYPE_OF_NUMBER)           = lastThirdPartyTypeOfNumber;
	      edrString(DETAIL.C_NUMBERING_PLAN)         = longToStr(lastThirdPartyNumberingPlan);
	      if (lastThirdPartyModificationIndicator > 0)
	      {
                edrString(DETAIL.C_MODIFICATION_INDICATOR) = "08";
              }

//	      edrString(DETAIL.C_NUMBER)                 = lastThirdPartyNumber;
	      //normalize the number
	      edrString(DETAIL.C_NUMBER) = convertCli(lastThirdPartyNumber, 
						edrString(DETAIL.C_MODIFICATION_INDICATOR), 
						edrLong(DETAIL.C_TYPE_OF_NUMBER),
						NORM_NAC,
						calledNumberAnalysisIACarray[1],// NORM_IAC,
						calledNumberAnalysisCCarray[1], // NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
	      edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);
	    }
	    else
	    {
	      for ( iterCodes = 0 ; iterCodes < SsBasicServicesAffectedNb ; iterCodes = iterCodes + 1 )
	      {
	        if ( edrString(DETAIL.BASIC_SERVICE) == SsBasicServicesAffected[iterCodes] )
	        {
	          // add a corresponding SS_PACKET
	          if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.SS_PACKET ) == false ) 
	          { 
		    String Msg = "failed to add ASS_GSMW_EXT.SS_PACKET datablock";
		    edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
	          }
	          tmp_SsPacketIdx = edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0);
	          edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,tmp_SsPacketIdx)    = lastSupplServiceEventCode;
	          edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,tmp_SsPacketIdx) = lastSupplServiceActionCode;
	          edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS ,0)                   = tmp_SsPacketIdx + 1;
	      
	          // and the third party info
	          edrLong(DETAIL.C_TYPE_OF_NUMBER)           = lastThirdPartyTypeOfNumber;
	          edrString(DETAIL.C_NUMBERING_PLAN)         = longToStr(lastThirdPartyNumberingPlan);
		  if (lastThirdPartyModificationIndicator > 0)
		  {
	            edrString(DETAIL.C_MODIFICATION_INDICATOR) = "08";
	          }

//		  edrString(DETAIL.C_NUMBER)                 = lastThirdPartyNumber;
		  //normalize the number
		  edrString(DETAIL.C_NUMBER) = convertCli(lastThirdPartyNumber, 
						edrString(DETAIL.C_MODIFICATION_INDICATOR), 
						edrLong(DETAIL.C_TYPE_OF_NUMBER),
						NORM_NAC,
						calledNumberAnalysisIACarray[1],// NORM_IAC,
						calledNumberAnalysisCCarray[1], // NORM_CC,
						NORM_IAC_SIGN,
						NORM_NDC );
	          edrString(DETAIL.INTERN_C_NUMBER_ZONE) = edrString(DETAIL.C_NUMBER);
	        }
	      }
 	    }
	  }
	}
	else
	{ 
	  String Msg = "supplServiceUsed received for record_Type != (MOC, MTC, MSS)";
	  edrAddError( "ERR_TAP3_INPUT_ERROR", 3, Msg);  
	}
      }
    ;

  supplServiceUsedList:
      supplServiceUsedList supplServiceUsed
    | supplServiceUsed
    ;

  supplServiceUsedList_opt:
      IFW_TAP3.SupplServiceUsedList
      supplServiceUsedList
      IFW_TAP3.Block_END
    | /* EMPTY */
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
	String taxRateStr    = getTaxRate( tokenLong("IFW_TAP3.TaxCode.TAX_CODE") );
	Long   taxRateStrlen = strLength( taxRateStr );
	if ( taxRateStrlen > 3 )
	{
	  lastTaxRate  = strToLong( strSubstr( taxRateStr, 0, (taxRateStrlen - 3) ) );
        }
      }
      IFW_TAP3.Charge
      {
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
      taxInformationList
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastTaxCharge  = 0.0;
      }
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
      typeOfNumber_opt
      numberingPlan_opt
      thirdPartyNumber_opt
      modificationIndicator_opt
      clirIndicator_opt
      IFW_TAP3.Block_END
      {
        lastThirdPartyTypeOfNumber          = lastTypeOfNumber;
        lastThirdPartyNumberingPlan         = lastNumberingPlan;
        lastThirdPartyModificationIndicator = lastModificationIndicator;
        lastTypeOfNumber          = 0;
        lastNumberingPlan         = 0;
        lastModificationIndicator = 0;
      }
    ;

  thirdPartyInformation_opt:
      thirdPartyInformation
    | /* EMPTY */
      {
        lastThirdPartyNumber    	    = defTelNumber;
        lastThirdPartyTypeOfNumber          = 0;
        lastThirdPartyNumberingPlan         = 0;
        lastThirdPartyModificationIndicator = 0;
      }
    ;

  thirdPartyNumber_opt:
      IFW_TAP3.AddressStringDigits
      {
        lastThirdPartyNumber = tokenString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS");
      }
    | /* EMPTY */
      {
        lastThirdPartyNumber = defTelNumber;
      }
    ;

  timeBandSubtype_opt:
      IFW_TAP3.TimeBandSubtype
    | /* EMPTY */
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
      dateTimeLong
      IFW_TAP3.Block_END
      {
        theTransferCutOffTimeStamp     = lastLocalTimeStamp;
        theTransferCutOffUtcTimeOffset = lastUtcTimeOffset;
      }
    ;

  transparencyIndicator_opt:
      IFW_TAP3.TransparencyIndicator
    | /* EMPTY */
    ;

  typeOfNumber_opt:
      IFW_TAP3.TypeOfNumber
      {
        lastTypeOfNumber = tokenLong("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER");
      }
    | /* EMPTY */
      {
        lastTypeOfNumber = 0;
      }
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
      {
	initializeChargeInfoTempFields();
      }
      valueAddedServiceUsed
      {
        // store the collected chargeInformation data in the corresponding EDR
	storeChargeInfoTempFields();

        // add the VAS short description to the record
        edrString(DETAIL.ASS_GSMW_EXT.VAS_PRODUCT_CODE, 0) = getVasShortDesc( lastVasCode );
	edrDate(DETAIL.CHARGING_START_TIMESTAMP)           = strToDate( lastVasLocalTimeStamp );
	edrDate(DETAIL.CHARGING_END_TIMESTAMP)		   = strToDate( lastVasLocalTimeStamp );
	edrString(DETAIL.UTC_TIME_OFFSET)                  = lastVasUtcTimeOffset;
      }
      operatorSpecInformation_opt
      IFW_TAP3.Block_END
    ;

  valueAddedServiceUsed:
      IFW_TAP3.ValueAddedServiceUsed
      IFW_TAP3.VasCode
      {
	service_Type	      = service_Vas;
        lastVasCode           = tokenLong("IFW_TAP3.VasCode.VAS_CODE");
      }
      chargingTimeStamp_opt
      {
	lastVasLocalTimeStamp = lastValidLocalTimeStamp;//TODO check validity
	lastVasUtcTimeOffset  = lastValidUtcTimeOffset; //TODO check validity
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
      valueAddedServiceUsedList
      IFW_TAP3.Block_END
    | /* EMPTY */
      {
        lastVasShortDescrList = "";
      }
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
      IFW_TAP3.VasDescription
      {
	vasDesc[lastCode] = tokenString("IFW_TAP3.VasDescription.VAS_DESCRIPTION");
        if (vasEntries <= lastCode)
	{
	  vasEntries = lastCode + 1;
	}
      }
      IFW_TAP3.Block_END
    ;

  vasInfo_opt:
      IFW_TAP3.VasInfo
      vasInfoList
      IFW_TAP3.Block_END
    | /* EMTPY */
    ;

  vasInfoList:
      vasInfoList vasDefinition
    | vasDefinition
    ;
}
