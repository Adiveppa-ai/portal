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
//   Output grammar file for the TAP3_v04 CDR format 
//
//------------------------------------------------------------------------------
// $Log: TAP3_v04_OutGrammar.dsc,v $
//
// Log 2003/03/06 njalel
// -PRSF00029215: Make the selection of the charge packet based on  
// configurable currency type. 
//
// Log 2003/01/21 njalel
// -PRSF00028774: Set the multi rate indicator in the  
// Tap 3 Outcollect file 
//
// Log 2002/11/06 njalel
// -PRSF00022946: Set the tax value in the TAP 3 out grammar to be based
// on the DETAIL.WHOLESALE_CHARGED_TAX_VALUE instead of 0
//
// Log 2002/10/01 cdiab
// -PRSF00019289: DETAIL.QOS_USED and DETAIL.QOS_REQUESTED are handled as
//  integers (edrLong) instead as strings (edrString)
//
// Log 2002/08/02 cdiab
// -PRSF00015604: the AccountingInfo.Taxation.TaxRateDefinition.TaxType is now
//  set to "13" (for ValueAddedTax), and not "15" which was an invalid value
// -PRSF00015605: we now write the CalledCountryCode from DETAIL.CALLED_COUNTRY_CODE
//  if this field is not set, the grammar will fill it with "49" as default.
//
// Revision 1.30  2002/01/22 16:27:22  cdiab
// PETS #42811 : "Chargeable Units" present for "Charged Item" in A, E, F, I
// Now, the ChargeableUnits will be written only for ChargedItem D, V, W, X
//
// Revision 1.29  2002/01/21 14:45:22  cdiab
// PETS #43003: in TAP3 output, error when no utcTimeOffset are used.
// Because then the UtcTimeOffsetInfo of the NetworkInfo bloc is empty;
// a default with +0000 must at least be written.
//
// Revision 1.28  2001/11/29 13:31:13  cdiab
// PETS #42073: Wrong calculation of timestamps in TAP3.4 AuditControlInfo
// AuditControlInfo was built out of the TRAILER block, now it is build out
// of the DETAIL statistics.
//
// Revision 1.27  2001/11/21 15:17:17  cdiab
// PETS #41865 : TAP3 notification record is not created when HEADER and TRAILER exist
// Until now, we mapped a Notification file to a HEADER (and the other way around).
// We should rather map a Notification file to a HEADER+TRAILER (without any DETAIL).
//
// Revision 1.26  2001/11/15 15:15:58  cdiab
// PETS #41646: TaxRate is wrong reading TAP3 files, decimal places are not considered
// -for TAP3v03 and TAP3v04 we now expect (and write out) TaxRate with 5
//  decimal places
// PETS #41700: TAP3 does not add Charge Information
// -on output, we now use edrNumDatablocks() to determine how many sub-blocks
//  are present.
//
// Revision 1.25  2001/11/13 11:42:38  cdiab
// PETS #40773 : CAMEL support for V4.30
//
// Revision 1.24  2001/10/25 12:55:44  cdiab
// PETS #40975 : TotalCharge in AuditControl != sum of ChargeAmounts
// The charge amounts in the charge detail blocks should be rounded
// (normal rounding) before inserted into the file, and also before
// being added to the total to be used in the TotalCharge (which then
// should be only truncated to the decimal places). (otherwise we get
// a mismatch because of the rounding)
// Same thing for discounting and totalDiscount except that there, we
// do not round the value, we truncate it.
//
// Revision 1.23  2001/10/23 18:10:00  cdiab
// PETS #40891: TAP3 parse error : v04 read / v01 v04 write
//
// Revision 1.22  2001/10/19 11:58:51  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// -on output, if no charge present (ie total charge is also 0), build an empty
// totalCharge block for type "00" with value 0.
//
// Revision 1.21  2001/10/19 11:37:08  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// check that charge!=0 before summing it to the totalCharge.
//
// Revision 1.20  2001/10/18 16:31:28  cdiab
// PETS #40694: some errors are still in the TAP3 processing
// -for tap0304 in DETAIL.ASS_GPRS_EXT.APN_ADDRESS, use the ',' and not '.'
// as separator, as it can be composed of IP adresses
// -for writing of decimal values, use round() (and not trunc()) to get an
// integer
// -we now always write the ChargeDetail.Charge, even if it is 0
// -NetworkType is written out for the details onlöy if it is set to mixed
// (ie. 0) in the registry
//
// Revision 1.19  2001/10/11 15:59:29  cdiab
// PETS #40398: in tap3 out, CallType information is only for MOC
// for other record type, do not write out this block
//
// Revision 1.18  2001/10/11 15:12:16  cdiab
// PETS #40293: correct little formats error in Tap3 implementation
// the SpecificationVersionNumber and theTap3ReleaseVersionNumber has to be
// set statically by the output (converter) and not taken from the stream.
//
// Revision 1.17  2001/10/11 12:41:05  cdiab
// PETS #40345: in TAP3 Audit block, INTEGERS can up to 8 bytes
// decimals need to be truncated before conversion to strHex.
//
// Revision 1.15  2001/10/11 10:58:19  cdiab
// PETS #40344: modify output grammar to generate Tap3 Notification
// -generate Tap3 Notification file when only a HEADER (no Details and no
// TRAILER) is in the stream.
// -in the registry config of the TAP3 output, DeleteEmptyStream must be set to FALSE
// (TRUE is to be used only when the TAP3 grammar is used for the reject stream)
//
// Revision 1.14  2001/10/10 16:00:10  cdiab
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
// Revision 1.13  2001/10/09 15:26:44  cdiab
// PETS #40286: add the streamIsEmpty() function for all TAP3 out grammars
// +now ChargingId is written even if it holds on more that a long integer.
//
// Revision 1.12  2001/10/04 16:46:00  cdiab
// PETS #40066: in TAP3 output build the Audit-TotalChargeList
// +corrected error where DETAIL.VOLUME_RECEIVED DETAIL.VOLUME_SENT where read as
// Long instead of Decimal
// +now the tap3 header sequence number is prepended with 0 to reach 5 digits
// +when we read a CP where IMPACT_CATEGORY is "00" we store it on its individual
// ChargeInformation block.
//
// Revision 1.11  2001/10/01 16:27:25  cdiab
// PETS #39726 : Number normalization must support multiple IAC's
// -TAP3 has been updated to use the new converCli method (previous checkin
// [v4-30-11] was only a workaround).
//
// Revision 1.10  2001/09/26 11:58:00  cdiab
// PETS #39872: in tap3 output, only write relevant ChargePackets
// On output, we should only write Charge Packet with:
//       CP.CHARGED_CURRENCY_TYPE == "R" and CP.PRICEMODEL_TYPE == "S"
// others are duplicate used for rating purposes and should be ignored
//
// Revision 1.9  2001/09/21 12:59:45  cdiab
// PETS #39723: Number normalisation in Tap3 has errors
// -If x_MODIFICATION_INDICATOR!="00" flag the number as modified in TAP3
// -For MTC use TERMINATING_SWITCH_ID to build the RecEntityCode bloc
// -use HEADER.ORIGIN_COUNTRY_CODE to update defTelNumber (<iac><cc>) to know when
// an optional MSISDN is only filled with a default (not to be written to output)
//
// Revision 1.8  2001/09/20 13:09:43  cdiab
// PETS #39682: tap3, build a default ChargeInformation if no rating is done
// added a addDefaultChargeInformation() function to create a Non Chargeable block
// when no ChargePackets are present.
//
// Revision 1.7  2001/09/20 12:08:14  cdiab
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
// Revision 1.6  2001/09/18 13:04:23  cdiab
// PETS #39333: in TAP3, add ability to select tap or local currency.
// addendum: corrected a coding error in initialisation of defaults for LocalCurrency.
//
// Revision 1.5  2001/09/14 16:18:38  cdiab
// PETS #39333: in TAP3, add ability to select tap or local currency
// if EXCHANGE_RATE is not > 0.0 (ie not set), use 1.0 to still be able to process.
//
// Revision 1.4  2001/09/14 14:16:54  cdiab
// PETS #39333: in TAP3, add ability to select tap or local currency.
// We store the local and tap currency names on the ChargePacket, and the
// exchange rate from on to the other.
// on output side, we expect all values to be in tap currencies.
//
// Revision 1.3  2001/09/05 15:38:48  cdiab
// PETS #38890:
// last commit was done with wrong Pets number
//
// Revision 1.2  2001/09/05 12:24:42  cdiab
// PETS #38890 : Errors when writing TAP3 to output
// modified TAP3_v01_OutGrammar.dsc and TAP3_v04_OutGrammar.dsc
// 2 AsnTreePopTag() were missing after update of the aggregation
// DetailPacket in addChargeInformation().
//
// Revision 1.1  2001/09/05 12:05:35  cdiab
// PETS #38720 : add ability to write Tap3 v04 (TD57v3.8.2)
// added TAP3_v04_OutGrammar.dsc
// and modified input to be also able to read Tap0303 in the same pipeline.
//
// Revision 1.0  2001/08/30 11:38:03  cdiab
// - Creation
//
//==============================================================================


//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  use EXT_AsnTree;	// iScript extension to build a Tree of ASN.1 object
  			// used to fill the Length value of the ASN.1 bloc,
			// before printing on output stream

  const Long theTap3SpecificationVersionNumber = 3;
  const Long theTap3ReleaseVersionNumber       = 4;

  // for statistics
  Date startTime;
  Date stopTime;

  // default values
  Date   defLocalTime;
  String defLocalTimeStamp;
  String defUtcTimeOffset;

  // default values for tap3 (not necessary to store them in output file)
  String defTelNumber;
  String defCauseForTerm;
  
  // runtime global
  Bool    supplServiceDetected;
  Bool    camelServiceDetected;
  Bool    vasServiceDetected;
  Decimal detailDiscountValue;
  Decimal detailTaxValue;
  Long    detailTotalChargeEntries;
  String  detailTotalChargeType[];
  Decimal detailTotalChargeValue[];
  
  // constants
  Long record_Header;
  Long record_Trailer;
  Long record_MOC;
  Long record_MTC;
  Long record_MSS;
  Long record_SCU;
  Long record_VAS;
  Long record_CONT;
  Long record_GPRS;
  Long record_Type; // use to know which type of detail we are reading

  // constants
  Long service_Basic;
  Long service_Camel;
  Long service_Gprs;
  Long service_Suppl;
  Long service_Vas;
  Long service_Content;
  Long service_Type; // use to know which type of service we are reading
  
  // constants
  String type_HEADER;
  String type_TRAILER;
  String type_MOC;
  String type_MTC;
  String type_MSS;
  String type_SCU;
  String type_VAS;
  String type_CONT;
  String type_GPRS;
  String type_GPRS_SG;
  String type_GPRS_GG;
  String type_GPRS_assembled;
  String extension_GSMW;
  String extension_GPRS;
  String extension_CBD;

  // for Header data storage
  String  headerUtcTimeOffset;
  Long    nbReceivedDetails;
  Long    nbWrittenDetails;
  Decimal theTotalDiscountValue;
  Decimal theTotalTaxValue;
  String  recordNum;
  String  recordType;
  Decimal theAbsoluteAmountMultiplier;
  Long    theTapDecimalPlaces;
  String  theTapCurrency;
  String  theLocalCurrency; 
  Long    theExchangeRate;
  Long    theExchangeDecimalPlaces;
  Decimal theExchangeRateMultiplier;
  Long    theNetworkType;
  String  theIacList;
  String  theCcList;

  // for Trailer update
  Date   firstCall_date;
  String firstCall_offset;
  Date   lastCall_date;
  String lastCall_offset;
  
  // index to ASN_TreeNode objects
  Long    theAccountingInfoIdx;
  Long    theNetworkInfoIdx;
  Long    theVasInfoIdx;
  Long    theMessageDescriptionIdx;
  Long    theDetailRootIdx;
  Long    lastDetailIdx;
  
  // taxation
  Long   taxEntries;
  String taxRate[];

  // recEntityInfo
  Long   recEntityEntries;
  Long   recEntityType[];    // recEntityType_MSC/recEntityType_SMSC/recEntityType_GGSN/recEntityType_SGSN
  String recEntityId[];
  Long   recEntityId_Type[]; // recEntityId_mscId/recEntityId_msisdn/recEntityId_iPTextV4Address/recEntityId_iPTextV6Address
  Long   recEntityType_MSC;
  Long   recEntityType_SMSC;
  Long   recEntityType_GGSN;
  Long   recEntityType_SGSN;
  Long   recEntityId_mscId;
  Long   recEntityId_msisdn;
  Long   recEntityId_iPTextV4Address;
  Long   recEntityId_iPTextV6Address;

  // utcTimeOffsetInfo
  Long   utcTimeOffsetEntries;
  String utcTimeOffset[];
  
  // vasInfo
  Long   vasEntries;
  String vasShortDesc[];
  
  // messageDescriptionInfo
  Long   messageDescriptionEntries;
  String messageDescription[];

  // discounting
  Long discountEntries;
  Long discountApplied[];

  // currencyConversion
  Long exchangeRateEntries;
  Long exchangeRate[];

  // Audit Total Charge
  Long    totalChargeEntries;
  String  totalChargeType[];
  Decimal totalChargeValue[];

  // constant values, regestry string where to find user configurable values
  String reg_TapIOModule;
  String reg_OutputModule;
  String reg_TapPipeline;
  String reg_TapDecimalPlaces;
  String reg_TapCurrency;
  String reg_ExchangeDecimalPlaces;
  String reg_NetworkType;
  String reg_UseLocalCurrency;
  String reg_chargedCurrencyType;
  
  // storage of registry values
  String defaultTapCurrency;
  String defaultLocalCurrency;

  String defaultChargedCurrency;
  
  // NB: Notification files are considered empty and will be deleted if in the
  //     registry you have DeleteEmptyStream=true for the TAP3 output stream
  function Bool streamIsEmpty
  {
    // a notification is identified by a Header and a Trailer (no Details)
    // a transfertBatch is identified by a Header, 1 or more Details, and a Trailer
    if ( nbWrittenDetails == 0 )
    {
      // Only HEADER and TRAILER
      return true;
    }
    // default
    return false;
  }

  function BEGIN
  {
    // initialisation of some runtime variables
    //-----------------------------------------
    reg_TapPipeline			= "ifw.Pipelines."+formatName();
    reg_TapIOModule			= registryNodeName();
    //logStdout("reg_TapIOModule(output) = "+reg_TapIOModule+"\n");
    reg_OutputModule			= reg_TapIOModule + ".Module.OutputStream.Module";
    
    reg_TapCurrency			= reg_TapPipeline + ".TapCurrency";
    reg_TapDecimalPlaces		= reg_TapPipeline + ".TapDecimalPlaces";
    reg_ExchangeDecimalPlaces		= reg_TapPipeline + ".ExchangeRateDecimalPlaces";
    reg_NetworkType			= reg_TapPipeline + ".NetworkType";
    reg_chargedCurrencyType             = reg_TapPipeline + ".ChargedCurrencyType";

    defaultTapCurrency			= regString(reg_TapCurrency);
    if (defaultTapCurrency == "")
    {
      defaultTapCurrency		= "SDR";
    }
    defaultLocalCurrency		= defaultTapCurrency; // default
    theTapDecimalPlaces			= strToLong( regString(reg_TapDecimalPlaces) );
    if (theTapDecimalPlaces == 0)
    {
      theTapDecimalPlaces		= 3;
    }
    theExchangeDecimalPlaces		= strToLong( regString(reg_ExchangeDecimalPlaces) );
    if (theExchangeDecimalPlaces == 0)
    {
      theExchangeDecimalPlaces		= 3;
    }
    theNetworkType			= strToLong( regString(reg_NetworkType) ); // 0 is accepted

    defaultChargedCurrency		= regString(reg_chargedCurrencyType);
    if (defaultChargedCurrency == "")
    {
      defaultChargedCurrency		= "R"; // default. R means rated and set by the main rating.
    }

    
    theAbsoluteAmountMultiplier = 1.0;
    Long i;
    for (i=0 ; i < theTapDecimalPlaces ; i=i+1)
    {
      theAbsoluteAmountMultiplier = theAbsoluteAmountMultiplier * 10.0;
    }
    theExchangeRateMultiplier = 1.0;
    for (i=0 ; i < theExchangeDecimalPlaces ; i=i+1)
    {
      theExchangeRateMultiplier = theExchangeRateMultiplier * 10.0;
    }

    // initialisation of some constant values
    //---------------------------------------
    
    defLocalTime	= MIN_DATE;
    defLocalTimeStamp	= dateToStr(defLocalTime);
    defUtcTimeOffset	= "+0000";
    defTelNumber	= "000";
    defCauseForTerm	= "00";

    recEntityType_MSC		= 1;
    recEntityType_SMSC		= 2;
    recEntityType_GGSN		= 3;
    recEntityType_SGSN		= 4;
    recEntityId_mscId           = 1;
    recEntityId_msisdn          = 2;
    recEntityId_iPTextV4Address = 3;
    recEntityId_iPTextV6Address = 4;

    record_Header =11;
    record_Trailer=12;
    record_MOC    =1;
    record_MTC    =2;
    record_MSS    =3;
    record_SCU    =4;
    record_VAS    =5;
    record_GPRS   =6;
    record_CONT   =7;
    record_Type   =0; // use to know which type of detail we are reading

    service_Basic  =1;
    service_Camel  =2;
    service_Gprs   =3;
    service_Suppl  =4;
    service_Vas    =5;
    service_Content=6;
    service_Type   =0; // use to know which type of service we are reading

    type_HEADER 	="010";
    type_TRAILER	="090";
    type_MOC    	="021";
    type_MTC    	="031";
    type_MSS    	="029";
    type_SCU    	="050"; 
    type_VAS    	="060";
    type_CONT    	="999"; //TODO get real type
    type_GPRS_SG	="040";
    type_GPRS_GG	="042";
    type_GPRS_assembled	=type_GPRS_GG;		//default for mixed ticket
    type_GPRS		=type_GPRS_assembled;	//default is mixed ticket
    extension_GSMW 	="520";
    extension_GPRS 	="540";
    extension_CBD  	="980";			//TODO check (here global charge)
  }

  function initializeForNewHeader
  {
    // initialisation of some runtime arrays
    //-----------------------------------------
    // taxation
    taxEntries = 0;
    arrayClear( taxRate );
    // recEntityInfo
    recEntityEntries = 0;
    arrayClear( recEntityType );
    arrayClear( recEntityId );
    arrayClear( recEntityId_Type );
    // utcTimeOffsetInfo
    utcTimeOffsetEntries = 0;
    arrayClear( utcTimeOffset );
    // vasInfo
    vasEntries = 0;
    arrayClear( vasShortDesc );
    // messageDescriptionInfo
    messageDescriptionEntries = 0;
    arrayClear( messageDescription );
    // discounting
    discountEntries = 0;
    arrayClear( discountApplied );
    // Currency
    exchangeRateEntries = 0;
    arrayClear( exchangeRate );
    //currency names
    theTapCurrency   = "";
    theLocalCurrency = "";
    // Trailer Total Charge
    arrayClear( totalChargeType );
    arrayClear( totalChargeValue );
    totalChargeEntries = 1;
    totalChargeType[0] = "00";
    totalChargeValue[0]= 0.0;
    // Trailer Total Discount
    theTotalDiscountValue = 0.0;
    
    theTotalTaxValue = 0.0;
    
    // initialize TRAILER statistics
    firstCall_date	= MAX_DATE;
    firstCall_offset	= "+0000";
    lastCall_date	= MIN_DATE;
    lastCall_offset	= "+0000";

    // initialize the ASN_TreeNode indexes with invalid values
    theAccountingInfoIdx     = (-1);
    theNetworkInfoIdx        = (-1);
    theVasInfoIdx            = (-1);
    theMessageDescriptionIdx = (-1);
    theDetailRootIdx         = (-1);
    lastDetailIdx            = (-1);
    
    // empty stream identification
    nbReceivedDetails	     = 0;
    nbWrittenDetails	     = 0;
  }

  function Bool storeDetailTotalDiscount(Decimal ChargeInfoDiscountValue)
  {
    detailDiscountValue = detailDiscountValue + ChargeInfoDiscountValue;
    return true;
  }

  function Bool storeDetailTotalTax(Decimal ChargeInfoTaxValue)
  {
    detailTaxValue = detailTaxValue + ChargeInfoTaxValue;
    return true;
  }

  function Bool storeDetailTotalCharge(String TotalChargeType, Decimal TotalChargeValue)
  {
    Long i;
    //if (TotalChargeValue == 0.0)
    //{
    // return true;
    //}
    for (i=0 ; i<detailTotalChargeEntries ; i=i+1)
    {
      if (detailTotalChargeType[i] == TotalChargeType)
      {
        detailTotalChargeValue[i] = detailTotalChargeValue[i] + TotalChargeValue;
        return true;
      }
    }
    // if we get here, the type is not yet used.
    detailTotalChargeType[i] = TotalChargeType;
    detailTotalChargeValue[i]= TotalChargeValue;
    detailTotalChargeEntries = detailTotalChargeEntries + 1;
    return true;
  }

  function Bool updateAuditTotalCharge
  {
    Long i;
    Long j;
    Bool notupdated;
    for (j=0 ; j<detailTotalChargeEntries ; j=j+1)
    {
      notupdated = true;
      for (i=0 ; ( (i<totalChargeEntries) and (notupdated==true) ); i=i+1)
      {
        if (totalChargeType[i] == detailTotalChargeType[j])
        {
          totalChargeValue[i] = totalChargeValue[i] + detailTotalChargeValue[j];
          notupdated          = false;
        }
      }
      if (notupdated==true)
      {
        // if we get here, the type is not yet used.
        totalChargeType[i] = detailTotalChargeType[j];
        totalChargeValue[i]= detailTotalChargeValue[j];
        totalChargeEntries = totalChargeEntries + 1;
      }
    }
    return true;
  }

  function Bool updateAuditTotalDiscount
  {
    if (detailDiscountValue == 0.0)
    {
      return true;
    }
    else
    {
      theTotalDiscountValue = theTotalDiscountValue + detailDiscountValue ;
      return true;
    }
  }
  
  function Bool updateAuditTotalTax
  {
    if (detailTaxValue == 0.0)
    {
      return true;
    }
    else
    {
      theTotalTaxValue = theTotalTaxValue + detailTaxValue ;
      return true;
    }
  }
  
  function Long getDiscountCode(Long DiscountAmount)
  {
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=discountEntries ; i=i+1)
    {
      if (discountApplied[i] == DiscountAmount)
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    discountApplied[i] = DiscountAmount;
    discountEntries    = discountEntries + 1;
    return i;
  }

  function Long getTaxRateCode(String TaxRate)
  {
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=taxEntries ; i=i+1)
    {
      if (taxRate[i] == TaxRate)
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    taxRate[i] = TaxRate;
    taxEntries = taxEntries + 1;
    return i;
  }

  function Bool isIPv4(String IPstring)
  {
    // IPv4= 1.2.3.4
    if ( strSearch( IPstring, "." ) >= 0 )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
  function Bool isIPv6(String IPstring)
  {
    // IPv6= 1:2:3:4:5:6:7:8
    if ( strSearch( IPstring, ":" ) >= 0 )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
  function Long getRecEntityIdCode(String RecEntityId, Long RecEntityType)
  {
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=recEntityEntries ; i=i+1)
    {
      if ( (recEntityId[i] == RecEntityId) and (recEntityType[i] == RecEntityType) )
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    recEntityId[i]   = RecEntityId;
    recEntityType[i] = RecEntityType;
    recEntityEntries = recEntityEntries + 1;
    
    if      ((recEntityType[i] == recEntityType_GGSN) or (recEntityType[i] == recEntityType_SGSN))
    {
      // differentiate between IPv4 and IPv6
      if ( strSearch( RecEntityId, ":" ) >= 0 )  // IPv6= 1:2:3:4:5:6:7:8
      {
        recEntityId_Type[i] = recEntityId_iPTextV6Address;
      }
      else
      {
        recEntityId_Type[i] = recEntityId_iPTextV4Address;
      }
    }
    else if (recEntityType[i] == recEntityType_MSC)
    {
      recEntityId_Type[i] = recEntityId_mscId;
    }
    else if (recEntityType[i] == recEntityType_SMSC)
    {
      recEntityId_Type[i] = recEntityId_msisdn;
    }

    return i;
  }
  function Long getVasShortDescCode(String VasShortDesc)
  {
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=vasEntries ; i=i+1)
    {
      if (vasShortDesc[i] == VasShortDesc)
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    vasShortDesc[i] = VasShortDesc;
    vasEntries      = vasEntries + 1;
    return i;
  }
  function Long getUtcTimeOffsetCode(String UtcTimeOffset)
  {
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=utcTimeOffsetEntries ; i=i+1)
    {
      if (utcTimeOffset[i] == UtcTimeOffset)
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    utcTimeOffset[i]     = UtcTimeOffset;
    utcTimeOffsetEntries = utcTimeOffsetEntries + 1;
    return i;
  }
  function Long getMessageDescriptionCode(String MessageDescription)
  {
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=messageDescriptionEntries ; i=i+1)
    {
      if (messageDescription[i] == MessageDescription)
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    messageDescription[i]     = MessageDescription;
    messageDescriptionEntries = messageDescriptionEntries + 1;
    return i;
  }
  function Long getExchangeRateCode(Decimal ExchangeRate)
  {
    Long tapExchangeRate = decimalToLong( ExchangeRate * theExchangeRateMultiplier);
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=exchangeRateEntries ; i=i+1)
    {
      if (exchangeRate[i] == tapExchangeRate)
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    exchangeRate[i]     = tapExchangeRate;
    exchangeRateEntries = exchangeRateEntries + 1;
    return i;
  }

  function updateTap3HeaderWithCodeLists
  {
    Long i; //iterator
    
    // theAccountingInfoIdx
    //=====================
    asnTreeGetStoredNode(theAccountingInfoIdx); // ie. asnTreePushTag("IFW_TAP3.AccountingInfo");
    if (taxEntries > 0)
    {
      asnTreePushTag("IFW_TAP3.Taxation");
      for (i=1 ; i<=taxEntries ; i=i+1)
      {
        asnTreePushTag("IFW_TAP3.TaxRateDefinition");
        asnTreeAddInteger("IFW_TAP3.TaxCode.TAX_CODE", i);
        asnTreeAddString("IFW_TAP3.TaxType.TAX_TYPE", "13" ); //ie ValueAddedTax
        asnTreeAddString("IFW_TAP3.TaxRate.TAX_RATE", taxRate[i] );
        asnTreePop(); //asnTreePushTag("IFW_TAP3.TaxRateDefinition");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.Taxation");
    }
    if (discountEntries > 0)
    {
      asnTreePushTag("IFW_TAP3.Discounting");
      for (i=1 ; i<=discountEntries ; i=i+1)
      {
        asnTreePushTag("IFW_TAP3.DiscountDefinition");
        asnTreeAddInteger("IFW_TAP3.DiscountCode.DISCOUNT_CODE", i);
        asnTreeAddInteger("IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT", discountApplied[i] );
        asnTreePop(); //asnTreePushTag("IFW_TAP3.DiscountDefinition");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.Discounting");
    }
    if (theLocalCurrency != "")
    {
      asnTreeAddString("IFW_TAP3.LocalCurrency.CURRENCY",   theLocalCurrency);
    }
    else
    {
      //TODO error ?
      asnTreeAddString("IFW_TAP3.LocalCurrency.CURRENCY",   defaultLocalCurrency);
    }

    if ( (theTapCurrency != "") and (theTapCurrency != defaultTapCurrency) )
    {
      asnTreeAddString("IFW_TAP3.TapCurrency.TAP_CURRENCY", theTapCurrency);
    }

    if (exchangeRateEntries > 0)
    {
      asnTreePushTag("IFW_TAP3.CurrencyConversion");
      for (i=1 ; i<=exchangeRateEntries ; i=i+1)
      {
        asnTreePushTag("IFW_TAP3.ExchangeRateDefinition");
        asnTreeAddInteger("IFW_TAP3.ExchangeRateCode.CODE", i);
        asnTreeAddInteger("IFW_TAP3.NumberOfDecimalPlaces.NUMBER_OF_DECIMAL_PLACES", theExchangeDecimalPlaces);
        asnTreeAddInteger("IFW_TAP3.ExchangeRate.EXCHANGE_RATE", exchangeRate[i]);
        asnTreePop(); //asnTreePushTag("IFW_TAP3.ExchangeRateDefinition");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CurrencyConversion");
    }
    else
    {
      // default is an exchange rate of 1/1
      asnTreePushTag("IFW_TAP3.CurrencyConversion");
      asnTreePushTag("IFW_TAP3.ExchangeRateDefinition");
      asnTreeAddInteger("IFW_TAP3.ExchangeRateCode.CODE", 1);
      asnTreeAddInteger("IFW_TAP3.NumberOfDecimalPlaces.NUMBER_OF_DECIMAL_PLACES", theExchangeDecimalPlaces);
      asnTreeAddInteger("IFW_TAP3.ExchangeRate.EXCHANGE_RATE", decimalToLong(theExchangeRateMultiplier));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ExchangeRateDefinition");
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CurrencyConversion");
    }
    asnTreeAddInteger("IFW_TAP3.TapDecimalPlaces.TAP_DECIMAL_PLACES", theTapDecimalPlaces);
    asnTreePop(); //asnTreePushTag("IFW_TAP3.AccountingInfo");
    
    // theNetworkInfoIdx
    //=====================
    asnTreeGetStoredNode(theNetworkInfoIdx); // ie asnTreePushTag("IFW_TAP3.NetworkInfo");
    asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfo");
    for (i=1 ; i<=utcTimeOffsetEntries ; i=i+1)
    {
      asnTreePushTag("IFW_TAP3.UtcTimeOffsetDefinition");
      asnTreeAddInteger("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE", i);
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", utcTimeOffset[i]  );
      asnTreePop(); //asnTreePushTag("IFW_TAP3.UtcTimeOffsetDefinition");
    }
    if (utcTimeOffsetEntries == 0)
    {
      asnTreePushTag("IFW_TAP3.UtcTimeOffsetDefinition");
      asnTreeAddInteger("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE", 1);
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", defUtcTimeOffset  );
      asnTreePop(); //asnTreePushTag("IFW_TAP3.UtcTimeOffsetDefinition");
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfo");
    if (recEntityEntries > 0)
    {
      asnTreePushTag("IFW_TAP3.RecEntityTable");
      for (i=1 ; i<=recEntityEntries ; i=i+1)
      {
	asnTreePushTag("IFW_TAP3.RecEntityDefinition");
	asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE",      i);
	asnTreeAddInteger("IFW_TAP3.RecEntityType.REC_ENTITY_TYPE",	     recEntityType[i]);
	if      (recEntityId_Type[i] == recEntityId_mscId)
	{
	  asnTreeAddString("IFW_TAP3.MscId.MSC_ID",			     recEntityId[i]);
	}
	else if (recEntityId_Type[i] == recEntityId_iPTextV4Address)
	{
	  asnTreeAddString("IFW_TAP3.IPTextV4Address.IP_TEXT_V4_ADDRESS",recEntityId[i]);
	}
	else if (recEntityId_Type[i] == recEntityId_iPTextV6Address)
	{
	  asnTreeAddString("IFW_TAP3.IPTextV6Address.IP_TEXT_V6_ADDRESS",recEntityId[i]);
	}
	else //if (recEntityId_Type[i] == recEntityId_msisdn)
	{
	  asnTreeAddString("IFW_TAP3.Msisdn.MSISDN",		     recEntityId[i]);
	}
	asnTreePop(); //asnTreePushTag("IFW_TAP3.RecEntityDefinition");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.RecEntityTable");
    }
    asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", theNetworkType);
    asnTreePushTag("IFW_TAP3.CalledNumAnalysisList");
    asnTreePushTag("IFW_TAP3.CalledNumAnalysis");
    asnTreeAddInteger("IFW_TAP3.CalledNumAnalysisCode.CALLED_NUM_ANALYSIS_CODE", 1);

    asnTreePushTag("IFW_TAP3.CountryCodeTable");
    // theCcList is a comma sparated list
    Long tmpListLen = strLength(theCcList);
    Long tmpIdx	    = 0;
    Long tmpIdxPrev = 0;
    while (tmpIdx < tmpListLen)
    {
      tmpIdxPrev	= tmpIdx;
      tmpIdx		= strSearch(theCcList, ",", tmpIdxPrev);
      if (tmpIdx < 0)
      {
        tmpIdx = tmpListLen ;
      }
      asnTreeAddString("IFW_TAP3.CountryCode.COUNTRY_CODE", 
      			strSubstr(theCcList, tmpIdxPrev, (tmpIdx - tmpIdxPrev)) );
      tmpIdx = tmpIdx + 1; //skip this comma if there is one
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CountryCodeTable");

    asnTreePushTag("IFW_TAP3.IacTable");
    // theIacList is a comma sparated list
    tmpListLen = strLength(theIacList);
    tmpIdx     = 0;
    tmpIdxPrev = 0;
    while (tmpIdx < tmpListLen)
    {
      tmpIdxPrev	= tmpIdx;
      tmpIdx		= strSearch(theIacList, ",", tmpIdxPrev);
      if (tmpIdx < 0)
      {
        tmpIdx = tmpListLen ;
      }
      asnTreeAddString("IFW_TAP3.Iac.IAC",
      			strSubstr(theIacList, tmpIdxPrev, (tmpIdx - tmpIdxPrev)) );
      tmpIdx = tmpIdx + 1; //skip this comma if there is one
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.IacTable");
    
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CalledNumAnalysis");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CalledNumAnalysisList");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.NetworkInfo");

    // theVasInfoIdx
    //=====================
    if (vasEntries > 0)
    {
      asnTreeGetStoredNode(theVasInfoIdx); // ie asnTreePushTag("IFW_TAP3.VasInfo");
      for (i=1 ; i<=vasEntries ; i=i+1)
      {
	asnTreePushTag("IFW_TAP3.VasDefinition");
	asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", i);
	asnTreeAddString("IFW_TAP3.VasShortDescription.VAS_SHORT_DESCRIPTION", vasShortDesc[i]  );
	asnTreeAddString("IFW_TAP3.VasDescription.VAS_DESCRIPTION", vasShortDesc[i]  );
	asnTreePop(); //asnTreePushTag("IFW_TAP3.VasDefinition");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.VasInfo");
    }
    else
    {
      asnTreeDeleteNodeByIndex(theVasInfoIdx);
      theVasInfoIdx = 0;
    }

    // theMessageDescriptionIdx
    //==========================
    if (messageDescriptionEntries > 0)
    {
      asnTreeGetStoredNode(theMessageDescriptionIdx); // ie asnTreePushTag("IFW_TAP3.MessageDescription");
      for (i=1 ; i<=messageDescriptionEntries ; i=i+1)
      {
	asnTreePushTag("IFW_TAP3.MessageDescriptionDefinition");
	asnTreeAddInteger("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE", i);
	asnTreeAddString("IFW_TAP3.MessageDescription.MESSAGE_DESCRIPTION", messageDescription[i]  );
	asnTreePop(); //asnTreePushTag("IFW_TAP3.MessageDescriptionDefinition");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.MessageDescription");
    }
    else
    {
      asnTreeDeleteNodeByIndex(theMessageDescriptionIdx);
      theMessageDescriptionIdx = 0;
    }
  }
  
  function addDateTimeLong(String timeStamp, String utcTimeOffset)
  {
    asnTreeAddString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP", timeStamp );
    if (utcTimeOffset == "")
    {
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", defUtcTimeOffset );
    }
    else
    {
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", utcTimeOffset );
    }
  }
  function addDateTime(String timeStamp, String utcTimeOffset)
  {
    asnTreeAddString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP", timeStamp );
    if (utcTimeOffset == "")
    {
      asnTreeAddInteger("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE",getUtcTimeOffsetCode(defUtcTimeOffset));
    }
    else
    {
      asnTreeAddInteger("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE",getUtcTimeOffsetCode(utcTimeOffset));
    }
  }
  
  function addLocationInformation(String switchIdentification)
  {
    // IFW_TAP3.LocationInformation
    //============================
    asnTreePushTag("IFW_TAP3.LocationInformation");
    asnTreePushTag("IFW_TAP3.NetworkLocation");
   
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE", getRecEntityIdCode(switchIdentification,recEntityType_MSC) );
    if (edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0) != "")
    {
      asnTreeAddInteger("IFW_TAP3.LocationArea.LOCATION_AREA",strToLong(edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0)) );
    }
    if (edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0) != "")
    {
      asnTreeAddInteger("IFW_TAP3.CellId.CELL_ID",strToLong(edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0)) );
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.NetworkLocation");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.LocationInformation");
  }
    
  function addGprsLocationInformation
  {
    // IFW_TAP3.GprsLocationInformation
    //============================
    asnTreePushTag("IFW_TAP3.GprsLocationInformation");
    asnTreePushTag("IFW_TAP3.GprsNetworkLocation");
    asnTreePushTag("IFW_TAP3.RecEntityCodeList");
   
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE",
    		      getRecEntityIdCode(edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0),recEntityType_GGSN));
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE",
    		      getRecEntityIdCode(edrString(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0),recEntityType_SGSN));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.RecEntityCodeList");
    if (edrString(DETAIL.ASS_GPRS_EXT.LOCATION_AREA_INDICATOR, 0) != "")
    {
      asnTreeAddInteger("IFW_TAP3.LocationArea.LOCATION_AREA",strToLong(edrString(DETAIL.ASS_GPRS_EXT.LOCATION_AREA_INDICATOR, 0)) );
    }
    if (edrString(DETAIL.ASS_GPRS_EXT.CELL_ID, 0) != "")
    {
      asnTreeAddInteger("IFW_TAP3.CellId.CELL_ID",strToLong(edrString(DETAIL.ASS_GPRS_EXT.CELL_ID, 0)) );
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsNetworkLocation");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsLocationInformation");
  }

  function addEquipmentInformation
  {
    // IFW_TAP3.EquipmentInformation
    //============================
    if ( (edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) != "") or (edrLong(DETAIL.ASS_GSMW_EXT.MS_CLASS_MARK, 0) != 0) )
    {
      asnTreePushTag("IFW_TAP3.EquipmentInformation");
      if (edrLong(DETAIL.ASS_GSMW_EXT.MS_CLASS_MARK, 0) != 0)
      {
        asnTreeAddInteger("IFW_TAP3.MobileStationClassMark.MOBILE_STATION_CLASS_MARK", edrLong(DETAIL.ASS_GSMW_EXT.MS_CLASS_MARK, 0) );
      }
      if (edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) != "")
      {
        asnTreeAddString("IFW_TAP3.Imei.IMEI", edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) );
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.EquipmentInformation");
    }
  }

  function addOperatorSpecInfoList(String theInfo)
  {
    if ( theInfo != "")
    {
      asnTreePushTag("IFW_TAP3.OperatorSpecInfoList");
      asnTreeAddString("IFW_TAP3.OperatorSpecInformation.OPERATOR_SPEC_INFORMATION", theInfo );
      asnTreePop(); //asnTreePushTag("IFW_TAP3.OperatorSpecInfoList");
    }
  }

  function addDefaultChargeInformation
  {
    // add an empty Charge information block (if no ASS_CBD with CP is present)
    asnTreePushTag("IFW_TAP3.ChargeInformation");
    asnTreeAddString("IFW_TAP3.ChargedItem.CHARGED_ITEM", "N");	// non chargeable
    asnTreePushTag("IFW_TAP3.ChargeDetailList");
    asnTreePushTag("IFW_TAP3.ChargeDetail");
    asnTreeAddString("IFW_TAP3.DayCategory.DAY_CATEGORY", "I");	// Independant of day 
    asnTreeAddString("IFW_TAP3.TimeBand.TIME_BAND",       "I");	// Independant of time     
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeDetail");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeDetailList");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeInformation");
  }

  function Long addChargeInformation(Long startCPidx, Long nbCP)
  {
    Bool    multiRateSet = false;
    String  savedDayCategory;
    String  savedTimeBand;

    String  daycategory;
    String  timeband;
    String  startRUM		 = edrString(DETAIL.ASS_CBD.CP.RUM, 0, startCPidx);
    Decimal startEXCHANGE_RATE	 = edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, startCPidx);
    String  startPRODUCTCODE_USED= edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, startCPidx);
    Decimal sumDiscountValue	  = 0.0 ;
    Decimal sumTaxValue	  = 0.0 ;
    Long i; 

    String  thisTapCurrency	  = edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, 0, startCPidx);
    if ( (thisTapCurrency != theTapCurrency) and (thisTapCurrency != "") )
    {
      if (theTapCurrency == "")
      {
        // first tap currency block from this file - we store it
        theTapCurrency = thisTapCurrency;
      }
      else
      {
        // TODO error, multiple different TapCurrencies used in the same stream
        logFormat( "ERROR: Using TapCurrency ("+thisTapCurrency+") in a stream already using TapCurrency ("+theTapCurrency+")\n" );
      } 
    }
    String  thisLocalCurrency	  = edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, 0, startCPidx);
    if ( (thisLocalCurrency != theLocalCurrency) and (thisLocalCurrency != "") )
    {
      if (theLocalCurrency == "")
      {
        // first local currency block from this file - we store it
        theLocalCurrency = thisLocalCurrency;
      }
      else
      {
        // TODO error, multiple different LocalCurrency used in the same stream
        logFormat( "ERROR: Using LocalCurrency ("+thisLocalCurrency+") in a stream already using LocalCurrency ("+theLocalCurrency+")\n" );
      } 
    }

    asnTreePushTag("IFW_TAP3.ChargeInformation");
    asnTreeAddString("IFW_TAP3.ChargedItem.CHARGED_ITEM", startRUM);
    Bool bPrintChargeableUnits = false;
    if ( (startRUM == "D") or
         (startRUM == "V") or (startRUM == "W") or (startRUM == "X") )
    {
      bPrintChargeableUnits = true;
    }
    
    if (startEXCHANGE_RATE > 0.0)
    {
      asnTreeAddInteger("IFW_TAP3.ExchangeRateCode.CODE", getExchangeRateCode(startEXCHANGE_RATE) );
    }
    else
    {
      asnTreeAddInteger("IFW_TAP3.ExchangeRateCode.CODE", getExchangeRateCode(1.0) );
    }
    
    if (record_Type == record_MOC)
    {
      if ( strLength(edrString(DETAIL.CONNECT_TYPE)) >= 2)
      {
        asnTreePushTag("IFW_TAP3.CallTypeGroup");
        asnTreeAddInteger("IFW_TAP3.CallTypeLevel1.CALL_TYPE_LEVEL", strToLong(strSubstr( edrString(DETAIL.CONNECT_TYPE), 0, 1)) );
        asnTreeAddInteger("IFW_TAP3.CallTypeLevel2.CALL_TYPE_LEVEL", strToLong(strSubstr( edrString(DETAIL.CONNECT_TYPE), 1, 1)) );
        asnTreeAddInteger("IFW_TAP3.CallTypeLevel3.CALL_TYPE_LEVEL", strToLong(edrString(DETAIL.CONNECT_SUB_TYPE)) );
        if ( strSubstr( edrString(DETAIL.CONNECT_TYPE), 0, 1) == "2" )
        {
          // only write this one for international calls
          if ( edrString(DETAIL.CALLED_COUNTRY_CODE) != "" )
          {
            asnTreeAddString("IFW_TAP3.CalledCountryCode.CALLED_COUNTRY_CODE", edrString(DETAIL.CALLED_COUNTRY_CODE) );
          }
          else
          {
            //if the countryCode is not given, write a default
            asnTreeAddString("IFW_TAP3.CalledCountryCode.CALLED_COUNTRY_CODE", "49" );
          }
        }
        asnTreePop(); //asnTreePushTag("IFW_TAP3.CallTypeGroup");
      }
    }

    asnTreePushTag("IFW_TAP3.ChargeDetailList");
    
    Decimal charge_00	      = 0.0 ;
    Long    chargedUnits_00   = 0;
    Long    chargeableUnits_00= 0;
    
    Long   lastChargedUnits   = 0 ;
    Long   lastChargeableUnits= 0;
    Decimal lastChargeValue   = 0.0 ;
    String lastChargeType     = "";
    Long   currentCPidx       = startCPidx;
    Long   nbWrittenCP        = 0;
    Long   idx                = 0;
    
    while ( (startRUM		   == edrString(DETAIL.ASS_CBD.CP.RUM, 0, currentCPidx))		and
//    	    (startEXCHANGE_RATE	   == edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, 0, currentCPidx))	and
	    (startPRODUCTCODE_USED == edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, currentCPidx))   and
	    (lastChargeType        != "00")								and
	    (currentCPidx	   <  nbCP ) )
    {      
      //only write relevant ChargePackets (otherwise, skip to the next one)
      if (  ((edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, currentCPidx) == defaultChargedCurrency)and
             (edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE,       0, currentCPidx) == "S"))
	  or((edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, 0, currentCPidx) == defaultChargedCurrency)and
	     (edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE,       0, currentCPidx) == "A")and
	     (edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY,	 0, currentCPidx) == "00"))
	 )
      {
	lastChargeType = edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, 0, currentCPidx);
        asnTreePushTag("IFW_TAP3.ChargeDetail");
	nbWrittenCP = nbWrittenCP +1;
        if (lastChargeType != "")
        {
          asnTreeAddString("IFW_TAP3.ChargeType.CHARGE_TYPE", lastChargeType);    
        }
        //if (edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, currentCPidx) != 0.0) //TODO uncomment to skip null charges
        {
	  lastChargeValue = round(theAbsoluteAmountMultiplier * edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, currentCPidx));
          charge_00       = charge_00 + lastChargeValue;
          asnTreeAddInteger("IFW_TAP3.Charge.CHARGE", decimalToLong(lastChargeValue));
	  if (lastChargeType != "")
	  {
	    storeDetailTotalCharge( lastChargeType, lastChargeValue);
	  }
	  else
	  {
	    // ERROR: this case should never happen, ChargeType must always be set when charge!=0
	    storeDetailTotalCharge( "99", lastChargeValue); //TODO this "99" is normally reserved
	  }
        }
	  
	lastChargedUnits    = decimalToLong(edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, 0, currentCPidx));
	lastChargeableUnits = decimalToLong(edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, 0, currentCPidx));
	if (lastChargeableUnits == 0)
	{
	  lastChargeableUnits = lastChargedUnits;
	}
        chargedUnits_00    = chargedUnits_00    + lastChargedUnits;
        chargeableUnits_00 = chargeableUnits_00 + lastChargeableUnits;
	if (bPrintChargeableUnits)
	{
          asnTreeAddInteger("IFW_TAP3.ChargeableUnits.CHARGEABLE_UNITS", lastChargeableUnits);    
	}
        asnTreeAddInteger("IFW_TAP3.ChargedUnits.CHARGED_UNITS", lastChargedUnits);
	  
        asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        asnTreeAddString("IFW_TAP3.DayCategory.DAY_CATEGORY", edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, currentCPidx));    
        asnTreeAddString("IFW_TAP3.TimeBand.TIME_BAND",       edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, currentCPidx));    
	// Prepare to set the MultiRateIndicator field
	if (multiRateSet == false) {
          daycategory = edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, currentCPidx);    
          timeband = edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, currentCPidx);    
	  if (idx == 0) {		// Cache on the first charge detail
            savedDayCategory = edrString(DETAIL.ASS_CBD.CP.DAY_CODE, 0, currentCPidx);
            savedTimeBand = edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, 0, currentCPidx);
	  } else {			// Compare on other charge details
	    if (( savedDayCategory != daycategory ) or
		( savedTimeBand != timeband )) {
		  multiRateSet = true;		// Set if either changed
                  asnTreeAddInteger("IFW_TAP3.MultiRateIndicator.MULTI_RATE_INDICATOR", 1);    // hardcode as per standard
	    }
	  }
	} else {			// multiRateSet is set to true
          asnTreeAddInteger("IFW_TAP3.MultiRateIndicator.MULTI_RATE_INDICATOR", 1);    // hardcode as per standard
	}
	idx = idx + 1;		// increment our local charge detail counter

        sumDiscountValue = sumDiscountValue + edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, 0, currentCPidx);
        asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeDetail");
        currentCPidx = currentCPidx + 1;
      }
      else
      {
        // skip irrelevent CP
        currentCPidx = currentCPidx + 1;
      }
    }

    if (lastChargeType != "00")
    {
      //add an aggregation packet if no one is present
      asnTreePushTag("IFW_TAP3.ChargeDetail");
      asnTreeAddString("IFW_TAP3.ChargeType.CHARGE_TYPE",   "00");  // aggregation
      asnTreeAddInteger("IFW_TAP3.Charge.CHARGE", decimalToLong(charge_00));    
      storeDetailTotalCharge( "00", charge_00);
      if (bPrintChargeableUnits)
      {
        asnTreeAddInteger("IFW_TAP3.ChargeableUnits.CHARGEABLE_UNITS", chargeableUnits_00);
      }
      asnTreeAddInteger("IFW_TAP3.ChargedUnits.CHARGED_UNITS", chargedUnits_00);    
      asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
      addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, startCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
      asnTreeAddString("IFW_TAP3.DayCategory.DAY_CATEGORY", "I");   // Independant of day 
      asnTreeAddString("IFW_TAP3.TimeBand.TIME_BAND",       "I");   // Independant of time     
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeDetail");
    }

    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeDetailList");


    if (edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE) != 0)
    {
      asnTreePushTag("IFW_TAP3.TaxInformationList");
      asnTreePushTag("IFW_TAP3.TaxInformation");
      // TaxRate comes in TAP3 with 5 decimal places, and in ifw we store only 2
      asnTreeAddInteger("IFW_TAP3.TaxCode.TAX_CODE", getTaxRateCode(longToStr(edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE))+"000"));
      sumTaxValue = round(theAbsoluteAmountMultiplier * edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE));
      asnTreeAddInteger("IFW_TAP3.Charge.CHARGE", decimalToLong(sumTaxValue));
      storeDetailTotalTax(sumTaxValue);
      asnTreePop(); //asnTreePushTag("IFW_TAP3.TaxInformation");
      asnTreePop(); //asnTreePushTag("IFW_TAP3.TaxInformationList");
    }


    if (sumDiscountValue != 0.0)
    {
      asnTreePushTag("IFW_TAP3.DiscountInformation");
      sumDiscountValue      = trunc(theAbsoluteAmountMultiplier * sumDiscountValue);
      storeDetailTotalDiscount(sumDiscountValue);
      asnTreeAddInteger("IFW_TAP3.DiscountCode.DISCOUNT_CODE", getDiscountCode(decimalToLong(sumDiscountValue)));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.DiscountInformation");
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeInformation");

    if ( currentCPidx < nbCP ) // there are CPs left to write
    {
      if (edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, currentCPidx) == "CAMEL")
      {
        camelServiceDetected = true; // NB: global variable, do not reset to false once it is set to true !
      }
      else if (edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, currentCPidx) != startPRODUCTCODE_USED)
      {
        vasServiceDetected = true; // NB: global variable, do not reset to false once it is set to true !
      }
    }
    return currentCPidx;
  }

  function Long addCamelServiceUsed(Long startCPidx, Long nbCP)
  {
    asnTreePushTag("IFW_TAP3.CamelServiceUsed");
    asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.ASS_CAMEL_EXT.SERVER_TYPE_OF_NUMBER, 0));
    asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.ASS_CAMEL_EXT.SERVER_NUMBERING_PLAN, 0)));
    asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0));
    asnTreeAddInteger("IFW_TAP3.CamelServiceLevel.CAMEL_SERVICE_LEVEL", edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_LEVEL, 0));
    asnTreeAddInteger("IFW_TAP3.CamelServiceKey.CAMEL_SERVICE_KEY", edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_KEY, 0));
    asnTreeAddInteger("IFW_TAP3.DefaultCallHandlingIndicator.DEFAULT_CALL_HANDLING_INDICATOR",
		      edrLong(DETAIL.ASS_CAMEL_EXT.DEFAULT_CALL_HANDLING_INDICATOR, 0));
    asnTreePushTag("IFW_TAP3.CamelCallReference");
    asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.ASS_CAMEL_EXT.MSC_TYPE_OF_NUMBER, 0));
    asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.ASS_CAMEL_EXT.MSC_NUMBERING_PLAN, 0)));
    asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0));
    asnTreeAddString("IFW_TAP3.CamelCallReferenceNumber.CAMEL_CALL_REFERENCE_NUMBER", edrString(DETAIL.ASS_CAMEL_EXT.CAMEL_REFERENCE_NUMBER, 0));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CamelCallReference");
      
    Long currentCPidx = startCPidx;
    if ( (camelServiceDetected == true) and (startCPidx < nbCP) )
    {
      currentCPidx = addChargeInformation(startCPidx, nbCP);
    }
      
    if (edrLong(DETAIL.ASS_CAMEL_EXT.CAMEL_INITIATED_CF_INDICATOR, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.CamelInitiatedCFIndicator.CAMEL_INITIATED_CF_INDICATOR", 1);
    }

    // Camel Modification List
    String tmpList    = edrString(DETAIL.ASS_CAMEL_EXT.CAMEL_MODIFICATION_LIST, 0);
    Long   tmpListLen = strLength(tmpList);
    if (tmpListLen > 0)
    {
      asnTreePushTag("IFW_TAP3.CamelModificationList");
      Long   tmpIdx		= 0;
      Long   tmpIdxPrev	= 0;
      while (tmpIdx < tmpListLen)
      {
        tmpIdxPrev	= tmpIdx;
        tmpIdx	= strSearch(tmpList, ",", tmpIdxPrev);
        if (tmpIdx < 0)
        {
          tmpIdx = tmpListLen ;
        }
        asnTreeAddInteger("IFW_TAP3.CamelModification.CAMEL_MODIFICATION",
			  strToLong(strSubstr(tmpList, tmpIdxPrev, (tmpIdx - tmpIdxPrev))) );
        tmpIdx = tmpIdx + 1; //skip this comma
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CamelModificationList");
    }
     
    // Camel Destination / Gprs Destination
    if (edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0) != "")
    {
      asnTreePushTag("IFW_TAP3.CamelDestination");
      asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_TYPE_OF_NUMBER, 0));
      asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBERING_PLAN, 0)));
      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CamelDestination");
    }
    else if (edrString(DETAIL.ASS_CAMEL_EXT.DEST_GPRS_APN_ADDRESS, 0) != "")
    {
      asnTreePushTag("IFW_TAP3.GprsDestination");
      Long sepIndex = strSearch( edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), ",");
      if (sepIndex < 0)
      {
        asnTreeAddString("IFW_TAP3.AccessPointNameNI.ACCESS_POINT_NAME_NI", edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0));
      }
      else
      {
        asnTreeAddString("IFW_TAP3.AccessPointNameNI.ACCESS_POINT_NAME_NI", 
			 strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), 0, (sepIndex-1) ) );
        asnTreeAddString("IFW_TAP3.AccessPointNameOI.ACCESS_POINT_NAME_OI",
			 strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), (sepIndex+1), 
			 	   strLength(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)) ) );
      }
      String tmpPdpList    = edrString(DETAIL.ASS_GPRS_EXT.PDP_REMOTE_ADDRESS, 0);
      Long   tmpPdpListLen = strLength(tmpPdpList);
      if (tmpPdpListLen > 0)
      {
        asnTreePushTag("IFW_TAP3.RemotePdpAddressList");
        Long   tmpIdx		= 0;
        Long   tmpIdxPrev	= 0;
        while (tmpIdx < tmpPdpListLen)
        {
          tmpIdxPrev	= tmpIdx;
          tmpIdx	= strSearch(tmpPdpList, ",", tmpIdxPrev);
          if (tmpIdx < 0)
          {
            tmpIdx = tmpPdpListLen ;
          }
          asnTreeAddString("IFW_TAP3.PacketDataProtocollAddress.PACKET_DATA_PROTOCOLL_ADDRESS",
			    strSubstr(tmpPdpList, tmpIdxPrev, (tmpIdx - tmpIdxPrev)) );
          tmpIdx = tmpIdx + 1; //skip this comma
        }
        asnTreePop(); //asnTreePushTag("IFW_TAP3.RemotePdpAddressList");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsDestination");
    }
    
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CamelServiceUsed");
    return currentCPidx;
  }

  function Bool processMOC
  {
    asnTreePushTag("IFW_TAP3.MobileOriginatedCall");
    lastDetailIdx = asnTreeStoreNode();
    
    // IFW_TAP3.MoBasicCallInformation
    //============================
    asnTreePushTag("IFW_TAP3.MoBasicCallInformation");
    asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }
    if (edrString(DETAIL.B_NUMBER) != defTelNumber)
    {
      asnTreePushTag("IFW_TAP3.Destination");
      asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.B_TYPE_OF_NUMBER));
      asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.B_NUMBERING_PLAN)));
      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.B_NUMBER));
      if ( strToLong(edrString(DETAIL.B_MODIFICATION_INDICATOR)) != 0 )
      {
        asnTreeAddInteger("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR", 1);
      }
      if (edrString(DETAIL.DESCRIPTION) != "")
      {
        asnTreeAddString("IFW_TAP3.CalledPlace.CALLED_PLACE", edrString(DETAIL.DESCRIPTION));
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.Destination");
    }
    if (edrString(DETAIL.DESTINATION_NETWORK) != "")
    {
      asnTreeAddString("IFW_TAP3.DestinationNetwork.NETWORK_ID", edrString(DETAIL.DESTINATION_NETWORK));
    }
    asnTreePushTag("IFW_TAP3.CallEventStartTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CallEventStartTimeStamp");
    asnTreeAddInteger("IFW_TAP3.TotalCallEventDuration.TOTAL_CALL_EVENT_DURATION", decimalToLong(edrDecimal(DETAIL.DURATION)) );
    if (edrString(DETAIL.CALL_COMPLETION_INDICATOR) != defCauseForTerm)
    {
      asnTreeAddInteger("IFW_TAP3.CauseForTerm.CAUSE_FOR_TERM", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.MoBasicCallInformation");

    // IFW_TAP3.LocationInformation
    //============================
    addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION,0) );
    
    // IFW_TAP3.EquipmentInformation
    //============================
    addEquipmentInformation();
    
    // IFW_TAP3.BasicServiceUsedList
    //============================
    asnTreePushTag("IFW_TAP3.BasicServiceUsedList");
    asnTreePushTag("IFW_TAP3.BasicServiceUsed");
    asnTreePushTag("IFW_TAP3.BasicService");
    if ( strStartsWith(edrString(DETAIL.BASIC_SERVICE),"0") ) //prefix is digit "0"
    {
      String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) )    ;
      asnTreeAddString("IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE", tmp_ServiceCode );
    }
    else //prefix is digit "1"
    {
      String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) )    ;
      asnTreeAddString("IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE", tmp_ServiceCode );
    }
    if (strToLong(edrString(DETAIL.QOS_REQUESTED)) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.RadioChannelRequested.RADIO_CHANNEL_REQUESTED", strToLong(edrString(DETAIL.QOS_REQUESTED)) );
    }
    if (strToLong(edrString(DETAIL.QOS_USED)) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.RadioChannelUsed.RADIO_CHANNEL_USED", strToLong(edrString(DETAIL.QOS_USED)) );
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicService");
    asnTreePushTag("IFW_TAP3.ChargeInformationList");
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if (CPcount > 0)
    {
      while ( (camelServiceDetected == false) and (vasServiceDetected == false) and (currentCPidx < CPcount) )
      {
         currentCPidx = addChargeInformation(currentCPidx, CPcount);
      }
    }
    else
    {
      addDefaultChargeInformation();
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeInformationList");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceUsed");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceUsedList");

    // IFW_TAP3.SupplServiceUsed (NB: without ChargeInformation!)
    //============================
    Long SScount = edrNumDatablocks( DETAIL.ASS_GSMW_EXT.SS_PACKET, 0 ); //edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS,0);
    if (SScount > 0)
    {
      asnTreePushTag("IFW_TAP3.SupplServiceUsedList");
      Long currentSSidx;
      for ( currentSSidx=0 ; (currentSSidx < SScount) ; currentSSidx=currentSSidx+1)
      {
	asnTreePushTag("IFW_TAP3.SupplServiceUsed");
	asnTreeAddString("IFW_TAP3.SupplServiceCode.SUPPL_SERVICE_CODE", edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,currentSSidx) );
	asnTreeAddInteger("IFW_TAP3.SupplServiceActionCode.SUPPL_SERVICE_ACTION_CODE", strToLong(edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,currentSSidx)) );
	if ( (currentSSidx == 0) and (edrString(DETAIL.C_NUMBER) != defTelNumber) ) // write only once
	{
	  asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	  asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.C_TYPE_OF_NUMBER));
	  asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.C_NUMBERING_PLAN)));
	  asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.C_NUMBER));
          if ( strToLong(edrString(DETAIL.C_MODIFICATION_INDICATOR)) != 0 )
          {
            asnTreeAddInteger("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR", 1);
          }
	  asnTreePop(); //asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	}
	asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsed");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsedList");
    }

    // IFW_TAP3.CamelServiceUsed
    //============================
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      currentCPidx = addCamelServiceUsed(currentCPidx, CPcount);
    }

    // IFW_TAP3.ValueAddedServiceUsedList
    //============================
    if (vasServiceDetected == true)
    {
      asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
      while (currentCPidx < CPcount)
      {
	asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
	asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", getVasShortDescCode(edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, currentCPidx)));
	asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
	addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
	asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        if (currentCPidx < CPcount)
        {
	  currentCPidx = addChargeInformation(currentCPidx, CPcount);
        }
	asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
    }
    
    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.MobileOriginatedCall");
    return true;
  }
  
  function Bool processMTC
  {
    asnTreePushTag("IFW_TAP3.MobileTerminatedCall");
    lastDetailIdx = asnTreeStoreNode();
    
    // IFW_TAP3.MtBasicCallInformation
    //============================
    asnTreePushTag("IFW_TAP3.MtBasicCallInformation");
    asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }
    if (edrString(DETAIL.B_NUMBER) != defTelNumber)
    {
      asnTreePushTag("IFW_TAP3.CallOriginator");
      asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.B_TYPE_OF_NUMBER));
      asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.B_NUMBERING_PLAN)));
      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.B_NUMBER));
      if ( strToLong(edrString(DETAIL.B_MODIFICATION_INDICATOR)) != 0 )
      {
        asnTreeAddInteger("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR", 1);
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CallOriginator");
    }
    if (edrString(DETAIL.SOURCE_NETWORK) != "")
    {
      asnTreeAddString("IFW_TAP3.OriginatingNetwork.NETWORK_ID", edrString(DETAIL.SOURCE_NETWORK));
    }
    asnTreePushTag("IFW_TAP3.CallEventStartTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CallEventStartTimeStamp");
    asnTreeAddInteger("IFW_TAP3.TotalCallEventDuration.TOTAL_CALL_EVENT_DURATION", decimalToLong(edrDecimal(DETAIL.DURATION)) );
    if (edrString(DETAIL.CALL_COMPLETION_INDICATOR) != defCauseForTerm)
    {
      asnTreeAddInteger("IFW_TAP3.CauseForTerm.CAUSE_FOR_TERM", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.MtBasicCallInformation");

    // IFW_TAP3.LocationInformation
    //============================
    if ( edrString(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION,0) != "")
    {
      addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION,0) );
    }
    else
    {
      addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION,0) );
    }
    
    // IFW_TAP3.EquipmentInformation
    //============================
    addEquipmentInformation();
    
    // IFW_TAP3.BasicServiceUsedList
    //============================
    asnTreePushTag("IFW_TAP3.BasicServiceUsedList");
    asnTreePushTag("IFW_TAP3.BasicServiceUsed");
    asnTreePushTag("IFW_TAP3.BasicService");
    if ( strStartsWith(edrString(DETAIL.BASIC_SERVICE),"0") ) //prefix is digit "0"
    {
      String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) )    ;
      asnTreeAddString("IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE", tmp_ServiceCode );
    }
    else //prefix is digit "1"
    {
      String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) )    ;
      asnTreeAddString("IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE", tmp_ServiceCode );
    }
    if (strToLong(edrString(DETAIL.QOS_REQUESTED)) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.RadioChannelRequested.RADIO_CHANNEL_REQUESTED", strToLong(edrString(DETAIL.QOS_REQUESTED)) );
    }
    if (strToLong(edrString(DETAIL.QOS_USED)) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.RadioChannelUsed.RADIO_CHANNEL_USED", strToLong(edrString(DETAIL.QOS_USED)) );
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicService");
    asnTreePushTag("IFW_TAP3.ChargeInformationList");
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if (CPcount > 0)
    {
      while ( (camelServiceDetected == false) and (vasServiceDetected == false) and (currentCPidx < CPcount) )
      {
         currentCPidx = addChargeInformation(currentCPidx, CPcount);
      }
    }
    else
    {
      addDefaultChargeInformation();
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeInformationList");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceUsed");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceUsedList");

    // IFW_TAP3.SupplServiceUsed (NB: without ChargeInformation!)
    //============================
    Long SScount = edrNumDatablocks( DETAIL.ASS_GSMW_EXT.SS_PACKET, 0 ); //edrLong(DETAIL.ASS_GSMW_EXT.NUMBER_OF_SS_PACKETS,0);
    if (SScount > 0)
    {
      asnTreePushTag("IFW_TAP3.SupplServiceUsedList");
      Long currentSSidx;
      for ( currentSSidx=0 ; (currentSSidx < SScount) ; currentSSidx=currentSSidx+1)
      {
	asnTreePushTag("IFW_TAP3.SupplServiceUsed");
	asnTreeAddString("IFW_TAP3.SupplServiceCode.SUPPL_SERVICE_CODE", edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,currentSSidx) );
	asnTreeAddInteger("IFW_TAP3.SupplServiceActionCode.SUPPL_SERVICE_ACTION_CODE", strToLong(edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,currentSSidx)) );
	if ( (currentSSidx == 0) and (edrString(DETAIL.C_NUMBER) != defTelNumber) ) // write only once
	{
	  asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	  asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.C_TYPE_OF_NUMBER));
	  asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.C_NUMBERING_PLAN)));
	  asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.C_NUMBER));
          if ( strToLong(edrString(DETAIL.C_MODIFICATION_INDICATOR)) != 0 )
          {
            asnTreeAddInteger("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR", 1);
          }
	  asnTreePop(); //asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	}
	asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsed");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsedList");
    }

    // IFW_TAP3.CamelServiceUsed
    //============================
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      currentCPidx = addCamelServiceUsed(currentCPidx, CPcount);
    }

    // IFW_TAP3.ValueAddedServiceUsedList
    //============================
    if (vasServiceDetected == true)
    {
      asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
      while (currentCPidx < CPcount)
      {
	asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
	asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", getVasShortDescCode(edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, currentCPidx)));
	asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
	addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
	asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        if (currentCPidx < CPcount)
        {
	  currentCPidx = addChargeInformation(currentCPidx, CPcount);
        }
	asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
    }

    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.MobileTerminatedCall");
    return true;
  }
  
  function Bool processGPRS
  {
    asnTreePushTag("IFW_TAP3.GprsCall");
    lastDetailIdx = asnTreeStoreNode();
    
    if      (edrString(DETAIL.RECORD_TYPE) == type_GPRS_GG)
    {
      asnTreeAddInteger("IFW_TAP3.TypeOfControllingNode.TYPE_OF_CONTROLLING_NODE", 2);
    }
    else if (edrString(DETAIL.RECORD_TYPE) == type_GPRS_SG)
    {
      asnTreeAddInteger("IFW_TAP3.TypeOfControllingNode.TYPE_OF_CONTROLLING_NODE", 1);
    }
    else //if (edrString(DETAIL.RECORD_TYPE) == type_GPRS_assembled)
    {
      asnTreeAddInteger("IFW_TAP3.TypeOfControllingNode.TYPE_OF_CONTROLLING_NODE", 0);
    }

    // IFW_TAP3.GprsBasicCallInformation
    //============================
    asnTreePushTag("IFW_TAP3.GprsBasicCallInformation");
    asnTreePushTag("IFW_TAP3.GprsChargeableSubscriber");
    asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddInteger("IFW_TAP3.PdpType.PDP_TYPE", strToLong(edrString(DETAIL.ASS_GPRS_EXT.PDP_TYPE,0)));
    asnTreeAddString("IFW_TAP3.PdpAddress.PDP_ADDRESS", edrString(DETAIL.ASS_GPRS_EXT.PDP_ADDRESS,0));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsChargeableSubscriber");
    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }
    
    asnTreePushTag("IFW_TAP3.GprsDestination");
    Long sepIndex = strSearch( edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), ",");
    if (sepIndex < 0)
    {
      asnTreeAddString("IFW_TAP3.AccessPointNameNI.ACCESS_POINT_NAME_NI", edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0));
    }
    else
    {
      asnTreeAddString("IFW_TAP3.AccessPointNameNI.ACCESS_POINT_NAME_NI", 
                       strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), 0, (sepIndex-1) ) );
      asnTreeAddString("IFW_TAP3.AccessPointNameOI.ACCESS_POINT_NAME_OI",
                       strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), (sepIndex+1), 
		                 strLength(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)) ) );
    }
    String tmpPdpList    = edrString(DETAIL.ASS_GPRS_EXT.PDP_REMOTE_ADDRESS, 0);
    Long   tmpPdpListLen = strLength(tmpPdpList);
    if (tmpPdpListLen > 0)
    {
      asnTreePushTag("IFW_TAP3.RemotePdpAddressList");
      Long   tmpIdx	= 0;
      Long   tmpIdxPrev	= 0;
      while (tmpIdx < tmpPdpListLen)
      {
        tmpIdxPrev	= tmpIdx;
        tmpIdx		= strSearch(tmpPdpList, ",", tmpIdxPrev);
        if (tmpIdx < 0)
        {
          tmpIdx = tmpPdpListLen ;
        }
        asnTreeAddString("IFW_TAP3.PacketDataProtocollAddress.PACKET_DATA_PROTOCOLL_ADDRESS",
			  strSubstr(tmpPdpList, tmpIdxPrev, (tmpIdx - tmpIdxPrev)) );
        tmpIdx = tmpIdx + 1; //skip this comma
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.RemotePdpAddressList");
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsDestination");

    asnTreePushTag("IFW_TAP3.CallEventStartTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CallEventStartTimeStamp");
    asnTreeAddInteger("IFW_TAP3.TotalCallEventDuration.TOTAL_CALL_EVENT_DURATION", decimalToLong(edrDecimal(DETAIL.DURATION)) );
    if (edrString(DETAIL.CALL_COMPLETION_INDICATOR) != defCauseForTerm)
    {
      asnTreeAddInteger("IFW_TAP3.CauseForTerm.CAUSE_FOR_TERM", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
    }
    if (edrString(DETAIL.LONG_DURATION_INDICATOR) != "S")
    {
      asnTreeAddString("IFW_TAP3.PartialTypeIndicator.PARTIAL_TYPE_INDICATOR", edrString(DETAIL.LONG_DURATION_INDICATOR));
    }
    if (edrLong(DETAIL.ASS_GPRS_EXT.NETWORK_INITIATED_PDP, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.NetworkInitPDPContext.NETWORK_INIT_PDP_CONTEXT", edrLong(DETAIL.ASS_GPRS_EXT.NETWORK_INITIATED_PDP, 0) );
    }
    asnTreeAddString("IFW_TAP3.ChargingId.CHARGING_ID", decimalToStrHex(strToDecimal(edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0))) );
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsBasicCallInformation");

    // IFW_TAP3.GprsLocationInformation
    //============================
    addGprsLocationInformation();
    
    // IFW_TAP3.EquipmentInformation
    //============================
    addEquipmentInformation();
    
    // IFW_TAP3.GprsServiceUsed
    //============================
    asnTreePushTag("IFW_TAP3.GprsServiceUsed");
    asnTreePushTag("IFW_TAP3.GprsServiceUsageList");
    asnTreePushTag("IFW_TAP3.GprsServiceUsage");
    asnTreePushTag("IFW_TAP3.GSMQoSRequested");
    asnTreeAddInteger("IFW_TAP3.QoSDelay.QOS_INTEGER", 		   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_DELAY, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSMeanThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_MEAN_THROUGHPUT, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSPeakThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PEAK_THROUGHPUT, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSPrecedence.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_PRECEDENCE, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSReliability.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_REQUESTED_RELIABILITY, 0)));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GSMQoSRequested");  
    asnTreePushTag("IFW_TAP3.GSMQoSUsed");
    asnTreeAddInteger("IFW_TAP3.QoSDelay.QOS_INTEGER", 		   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_DELAY, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSMeanThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_MEAN_THROUGHPUT, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSPeakThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_PEAK_THROUGHPUT, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSPrecedence.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_PRECEDENCE, 0)));
    asnTreeAddInteger("IFW_TAP3.QoSReliability.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.QOS_USED_RELIABILITY, 0)));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GSMQoSUsed");
    asnTreeAddInteger("IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING", decimalToLong(edrDecimal(DETAIL.VOLUME_RECEIVED)));
    asnTreeAddInteger("IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING", decimalToLong(edrDecimal(DETAIL.VOLUME_SENT)));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsServiceUsage");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsServiceUsageList");

    asnTreePushTag("IFW_TAP3.ChargeInformationList");
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if (CPcount > 0)
    {
      while ( (camelServiceDetected == false) and (vasServiceDetected == false) and (currentCPidx < CPcount) )
      {
         currentCPidx = addChargeInformation(currentCPidx, CPcount);
      }
    }
    else
    {
      addDefaultChargeInformation();
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeInformationList");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsServiceUsed");

    // IFW_TAP3.CamelServiceUsed
    //============================
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      currentCPidx = addCamelServiceUsed(currentCPidx, CPcount);
    }

    // IFW_TAP3.ValueAddedServiceUsedList
    //============================
    if (vasServiceDetected == true)
    {
      asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
      while (currentCPidx < CPcount)
      {
	asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
	asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", getVasShortDescCode(edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, 0, currentCPidx)));
	asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
	addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
	asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        if (currentCPidx < CPcount)
        {
	  currentCPidx = addChargeInformation(currentCPidx, CPcount);
        }
	asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
    }

    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsCall");
    return true;
  }
  
  function Bool processMSS
  {
    asnTreePushTag("IFW_TAP3.SupplServiceEvent");
    lastDetailIdx = asnTreeStoreNode();
    
    asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }

    // IFW_TAP3.LocationInformation
    //============================
    addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION,0) );
    
    // IFW_TAP3.EquipmentInformation
    //============================
    addEquipmentInformation();
    
    // IFW_TAP3.SupplServiceUsed
    //============================
    asnTreePushTag("IFW_TAP3.SupplServiceUsed");
    asnTreeAddString("IFW_TAP3.SupplServiceCode.SUPPL_SERVICE_CODE", edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,0) );
    asnTreeAddInteger("IFW_TAP3.SupplServiceActionCode.SUPPL_SERVICE_ACTION_CODE", strToLong(edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,0)) );
    if (edrString(DETAIL.C_NUMBER) != defTelNumber)
    {
      asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
      asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.C_TYPE_OF_NUMBER));
      asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.C_NUMBERING_PLAN)));
      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.C_NUMBER));
      if ( strToLong(edrString(DETAIL.C_MODIFICATION_INDICATOR)) != 0 )
      {
        asnTreeAddInteger("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR", 1);
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
    }
    asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
    if (edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) == 2) // ie ASS_GSMW_EXT + ASS_CBD
    {
      // IFW_TAP3.ChargeInformation
      //============================
      Long currentCPidx	= 0;  //start from the beginning (first CP)
      Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
      if (CPcount > 0)
      {
        currentCPidx = addChargeInformation(currentCPidx, CPcount);  //start from the beginning (first CP), and add ONLY 1 ChargeInformation block
        if (currentCPidx != CPcount)
        {
          // ERROR we shoould be able to store all ChargePackets on one ChargeInformation
	  logFormat("ERROR: processMSS(), currentCPidx="+longToStr(currentCPidx)+" < CPcount="+longToStr(CPcount)+" \n");
	  return false;
        }
      }
    }
    String basicDualServiceprefix;
    String basicDualServiceSuffixe;
    if ( strLength(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0)) >= 3)
    {
      basicDualServiceprefix  = strSubstr(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0), 0, 1 ); //take the first 1 digit
      basicDualServiceSuffixe = strSubstr(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0), 1, 2 ); //take the last  2 digits
    }
    if (basicDualServiceprefix == "0")
    {
      // prefix "0" -> TeleService
      asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
      asnTreeAddString("IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE", basicDualServiceSuffixe);
      asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
    }
    else if (basicDualServiceprefix == "1")
    {
      // prefix "1" -> BearerService
      asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
      asnTreeAddString("IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE", basicDualServiceSuffixe);
      asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
    }
    else
    {
      //TODO error check?
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsed");
    
    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceEvent");
    return true;
  }
  
  function Bool processSCU
  {
    asnTreePushTag("IFW_TAP3.ServiceCentreUsage");
    lastDetailIdx = asnTreeStoreNode();
    
    // IFW_TAP3.ScuBasicInformation
    //============================
    asnTreePushTag("IFW_TAP3.ScuBasicInformation");
    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
      asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    }
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    }
    asnTreeAddInteger("IFW_TAP3.ChargedPartyStatus.CHARGED_PARTY_STATUS", edrLong(DETAIL.USAGE_DIRECTION) );
    asnTreePushTag("IFW_TAP3.NonChargedParty");
    if (edrLong(DETAIL.B_TYPE_OF_NUMBER) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.TypeOfNumber.TYPE_OF_NUMBER",  edrLong(DETAIL.B_TYPE_OF_NUMBER));
    }
    if (strToLong(edrString(DETAIL.B_NUMBERING_PLAN)) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.NumberingPlan.NUMBERING_PLAN", strToLong(edrString(DETAIL.B_NUMBERING_PLAN)));
    }
    asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.B_NUMBER));
    if (strToLong(edrString(DETAIL.B_MODIFICATION_INDICATOR)) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.ModificationIndicator.MODIFICATION_INDICATOR", 1);
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.NonChargedParty");
    asnTreeAddString("IFW_TAP3.OriginatingNetwork.NETWORK_ID", edrString(DETAIL.SOURCE_NETWORK));
    asnTreeAddString("IFW_TAP3.DestinationNetwork.NETWORK_ID", edrString(DETAIL.DESTINATION_NETWORK));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ScuBasicInformation");

    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }
   
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE",
    		      getRecEntityIdCode(edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0),recEntityType_SMSC));

    // IFW_TAP3.ChargeInformation
    //============================
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if (CPcount > 0)
    {
      currentCPidx = addChargeInformation(currentCPidx, CPcount);  //start from the beginning (first CP), and add ONLY 1 ChargeInformation block
      if (currentCPidx != CPcount)
      {
        // ERROR we shoould be able to store all ChargePackets on one ChargeInformation
        logFormat("ERROR: processSCU(), currentCPidx="+longToStr(currentCPidx)+" < CPcount="+longToStr(CPcount)+" \n");
        return false;
      }
    }
    else
    {
      addDefaultChargeInformation(); // ChargeInformation is mandatory block for SCU
    }

    // IFW_TAP3.ScuChargeType
    //============================
    asnTreePushTag("IFW_TAP3.ScuChargeType");
    asnTreeAddInteger("IFW_TAP3.MessageStatus.MESSAGE_STATUS", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)));
    asnTreeAddInteger("IFW_TAP3.PriorityCode.PRIORITY_CODE", strToLong(edrString(DETAIL.QOS_REQUESTED)));
    asnTreeAddInteger("IFW_TAP3.MessageType.MESSAGE_TYPE", strToLong(edrString(DETAIL.QOS_USED)));  //TODO find a better storage
    asnTreeAddInteger("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE", getMessageDescriptionCode(edrString(DETAIL.DESCRIPTION)));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ScuChargeType");
    
    // IFW_TAP3.ScuTimeStamps
    //============================
    asnTreePushTag("IFW_TAP3.ScuTimeStamps");
    asnTreePushTag("IFW_TAP3.DepositTimeStamp");	//ie ChargingPoint "D"
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.DepositTimeStamp");
    asnTreePushTag("IFW_TAP3.CompletionTimeStamp");	//ie ChargingPoint "C"
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_END_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CompletionTimeStamp");
    asnTreeAddString("IFW_TAP3.ChargingPoint.CHARGING_POINT", "D"); //TODO check if it is ok to use always Deposit Timestamp for charging
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ScuTimeStamps");

    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.ServiceCentreUsage");
    return true;
  }
  
  function Bool processVAS
  {
    asnTreePushTag("IFW_TAP3.ValueAddedService");
    lastDetailIdx = asnTreeStoreNode();

    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
      asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    }
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    }
    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }
    
    // IFW_TAP3.ValueAddedServiceUsed
    //============================
    asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
    asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", getVasShortDescCode(edrString(DETAIL.ASS_GSMW_EXT.VAS_PRODUCT_CODE,0)));
    asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
    if (edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS) == 2) // ie ASS_GSMW_EXT + ASS_CBD
    {
      // IFW_TAP3.ChargeInformation
      //============================
      Long currentCPidx	= 0;  //start from the beginning (first CP)
      Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
      if (CPcount > 0)
      {
        currentCPidx = addChargeInformation(currentCPidx, CPcount);  //start from the beginning (first CP), and add ONLY 1 ChargeInformation block
        if (currentCPidx != CPcount)
        {
          // ERROR we shoould be able to store all ChargePackets on one ChargeInformation
          logFormat("ERROR: processVAS(), currentCPidx="+longToStr(currentCPidx)+" < CPcount="+longToStr(CPcount)+" \n");
          return false;
        }
      }
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
    
    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedService");
    return true;
  }

  function Bool processCONT // TODO build this output when we support it
  {
    logStdout("ERROR: processCONT(), writting record of this type (Content Transaction) is not yet supported.\n"); //TODO comment this line
    logFormat("ERROR: processCONT(), writting record of this type (Content Transaction) is not yet supported.\n");
    edrAddError( "ERR_ILL_RECORD_TYPE", 3, recordType); // Major
    lastDetailIdx = (-1);
    return false;
  }
}

//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{
  receive_stream:
      {
//startTime = sysdate(); //TODO remove this line or just comment it
        //initialisations of memory structure
	initializeForNewHeader();
	asnTreeCreate();
      }
      HEADER
      edr_stream
      {
        //print to output, and release memory structure
	asnTreeFlush();
	asnTreeDelete();
//stopTime = sysdate(); //TODO remove this line or just comment it
//logStdout( "  Start processing output: " + dateToStr(startTime ) + "\n"); //TODO remove this line or just comment it
//logStdout( "  End   processing output: " + dateToStr(stopTime ) + "\n");  //TODO remove this line or just comment it
      }
    ;

  edr_stream:
      header_Notification
      TRAILER //Notification = HEADER+TRAILER (without any DETAIL)
    |
      {
	asnTreePushTag("IFW_TAP3.TransferBatch");
      }
      header_TransfertBatch
      {
	asnTreePushTag("IFW_TAP3.CallEventDetailList");
	theDetailRootIdx = asnTreeStoreNode();
      }
      details
      {
	asnTreePop(); //asnTreePushTag("IFW_TAP3.CallEventDetailList");
      }
      trailer
      {
	asnTreePop(); //asnTreePushTag("IFW_TAP3.TransferBatch");
	
	// go back to header and store the lists of Code/Value for Tap3 fields
	updateTap3HeaderWithCodeLists();
      }
    ;
    
  header_Notification:  
      {
//logStdout( "NOTIFICATION WAS DETECTED\n");
	record_Type		= record_Header;
 	recordNum		= longToStr(edrLong(HEADER.RECORD_NUMBER)) ;
	headerUtcTimeOffset	= edrString(HEADER.UTC_TIME_OFFSET);

	asnTreePushTag("IFW_TAP3.Notification");
	asnTreeAddString("IFW_TAP3.Sender.PLMN_ID",   edrString(HEADER.SENDER) );
	asnTreeAddString("IFW_TAP3.Recipient.PLMN_ID",edrString(HEADER.RECIPIENT) );
	String theSequenceNumber = longToStr(edrLong(HEADER.SEQUENCE_NUMBER));
	switch (strLength(theSequenceNumber))
	{
	  case 0 : theSequenceNumber="00000";			break;
	  case 1 : theSequenceNumber="0000"+theSequenceNumber;	break;
	  case 2 : theSequenceNumber="000"+theSequenceNumber;	break;
	  case 3 : theSequenceNumber="00"+theSequenceNumber;	break;
	  case 4 : theSequenceNumber="0"+theSequenceNumber;	break;
	  default: 						break;
	}
        asnTreeAddString("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER",theSequenceNumber );
	asnTreePushTag("IFW_TAP3.FileCreationTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("IFW_TAP3.FileCreationTimeStamp");
	asnTreePushTag("IFW_TAP3.FileAvailableTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSMISSION_DATE)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("IFW_TAP3.FileAvailableTimeStamp");
	asnTreePushTag("IFW_TAP3.TransferCutOffTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("IFW_TAP3.TransferCutOffTimeStamp");
	asnTreeAddInteger("IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER",theTap3SpecificationVersionNumber );
	asnTreeAddInteger("IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER",theTap3ReleaseVersionNumber );
	if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
	{
	  asnTreeAddString("IFW_TAP3.FileTypeIndicator.FILE_TYPE_INDICATOR",  edrString(HEADER.DATA_TYPE_INDICATOR) );
	}
        addOperatorSpecInfoList(edrString(HEADER.OPERATOR_SPECIFIC_INFO));
	asnTreePop(); //asnTreePushTag("IFW_TAP3.Notification");
      }
    ;

  header_TransfertBatch:  
      {
        defTelNumber		= edrString(HEADER.ORIGIN_COUNTRY_CODE);
	record_Type		= record_Header;
 	recordNum		= longToStr(edrLong(HEADER.RECORD_NUMBER)) ;
	headerUtcTimeOffset	= edrString(HEADER.UTC_TIME_OFFSET);
	theIacList		= edrString(HEADER.IAC_LIST);
	theCcList		= edrString(HEADER.CC_LIST);
	if (theIacList == "")
	{
	  theIacList		= NORM_IAC_STRING;
	}	
	if (theCcList == "")
	{
	  theCcList		= NORM_CC_STRING;
	}
//logStdout( "IFW_TAP3.HEADER.STD_MAPPING "+ recordNum +"\n"  );
	
	asnTreePushTag("IFW_TAP3.BatchControlInfo");
	asnTreeAddString("IFW_TAP3.Sender.PLMN_ID",   edrString(HEADER.SENDER) );
	asnTreeAddString("IFW_TAP3.Recipient.PLMN_ID",edrString(HEADER.RECIPIENT) );
	String theSequenceNumber = longToStr(edrLong(HEADER.SEQUENCE_NUMBER));
	switch (strLength(theSequenceNumber))
	{
	  case 0 : theSequenceNumber="00000";			break;
	  case 1 : theSequenceNumber="0000"+theSequenceNumber;	break;
	  case 2 : theSequenceNumber="000"+theSequenceNumber;	break;
	  case 3 : theSequenceNumber="00"+theSequenceNumber;	break;
	  case 4 : theSequenceNumber="0"+theSequenceNumber;	break;
	  default: 						break;
	}
        asnTreeAddString("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER",theSequenceNumber );
	asnTreePushTag("IFW_TAP3.FileCreationTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("IFW_TAP3.FileCreationTimeStamp");
	asnTreePushTag("IFW_TAP3.TransferCutOffTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("IFW_TAP3.TransferCutOffTimeStamp");
	asnTreePushTag("IFW_TAP3.FileAvailableTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSMISSION_DATE)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("IFW_TAP3.FileAvailableTimeStamp");
	asnTreeAddInteger("IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER",theTap3SpecificationVersionNumber );
	asnTreeAddInteger("IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER",theTap3ReleaseVersionNumber );
	if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
	{
	  asnTreeAddString("IFW_TAP3.FileTypeIndicator.FILE_TYPE_INDICATOR",  edrString(HEADER.DATA_TYPE_INDICATOR) );
	}
        addOperatorSpecInfoList(edrString(HEADER.OPERATOR_SPECIFIC_INFO));
	asnTreePop(); //asnTreePushTag("IFW_TAP3.BatchControlInfo");

	asnTreePushTag("IFW_TAP3.AccountingInfo");
	theAccountingInfoIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("IFW_TAP3.AccountingInfo");

	asnTreePushTag("IFW_TAP3.NetworkInfo");
	theNetworkInfoIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("IFW_TAP3.NetworkInfo");

	asnTreePushTag("IFW_TAP3.VasInfo");
	theVasInfoIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("IFW_TAP3.VasInfo");

	asnTreePushTag("IFW_TAP3.MessageDescriptionInfo");
	theMessageDescriptionIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("IFW_TAP3.MessageDescriptionInfo");
      }
    ;
    
  trailer:  
      TRAILER
      {
	record_Type = record_Trailer;
	recordNum   = longToStr(edrLong(TRAILER.RECORD_NUMBER)) ;
//logStdout( "IFW_TAP3.TRAILER.STD_MAPPING "+ recordNum +"(TotaChargeAmount="+decimalToStr(edrDecimal(TRAILER.TOTAL_WHOLESALE_CHARGED_VALUE))+")\n"  );

	asnTreePushTag("IFW_TAP3.AuditControlInfo");

	asnTreePushTag("IFW_TAP3.EarliestCallTimeStamp");
	addDateTimeLong( dateToStr(firstCall_date), firstCall_offset );
	asnTreePop(); //asnTreePushTag("IFW_TAP3.EarliestCallTimeStamp");
	
	asnTreePushTag("IFW_TAP3.LatestCallTimeStamp");
	addDateTimeLong( dateToStr(lastCall_date), lastCall_offset );
	asnTreePop(); //asnTreePushTag("IFW_TAP3.LatestCallTimeStamp");

	asnTreePushTag("IFW_TAP3.TotalChargeValueList");
	Long i;
	for (i=0 ; i<totalChargeEntries ; i=i+1)
	{
	  asnTreePushTag("IFW_TAP3.TotalChargeValue");
	  asnTreeAddString("IFW_TAP3.ChargeType.CHARGE_TYPE", totalChargeType[i] );
	  asnTreeAddString("IFW_TAP3.AbsoluteAmount.ABSOLUTE_AMOUNT",
	  		   decimalToStrHex( trunc(totalChargeValue[i]) ) );
	  asnTreePop(); //asnTreePushTag("IFW_TAP3.TotalChargeValue");
	}
	asnTreePop(); //asnTreePushTag("IFW_TAP3.TotalChargeValueList");
	//asnTreeAddString("IFW_TAP3.TotalTaxRefund.TOTAL_TAX_REFUND", decimalToStrHex(trunc(0.0)));//present only if >0
	asnTreeAddString("IFW_TAP3.TotalTaxValue.TOTAL_TAX_VALUE", decimalToStrHex( trunc(theTotalTaxValue)));
	asnTreeAddString("IFW_TAP3.TotalDiscountValue.TOTAL_DISCOUNT_VALUE",
			 decimalToStrHex( trunc(theTotalDiscountValue) ) );
	//asnTreeAddString("IFW_TAP3.TotalDiscountRefund.TOTAL_DISCOUNT_REFUND", decimalToStrHex(trunc(0.0)));//present only if >0
	asnTreeAddInteger("IFW_TAP3.CallEventDetailsCount.CALL_EVENT_DETAIL_COUNT", nbWrittenDetails);
        addOperatorSpecInfoList(edrString(TRAILER.OPERATOR_SPECIFIC_INFO));
	asnTreePop(); //asnTreePushTag("IFW_TAP3.AuditControlInfo");
      }
    ;

  details: // this is a non empty list of DETAILS
      details
      oneDetail
    | oneDetail
    ;
    
  oneDetail: 
      DETAIL
      {
        nbReceivedDetails	= nbReceivedDetails +1;
	recordNum		= longToStr(edrLong(DETAIL.RECORD_NUMBER)) ;
	recordType		= edrString(DETAIL.RECORD_TYPE);
	supplServiceDetected	= false;
	camelServiceDetected	= false;
	vasServiceDetected	= false;
	// used for Trailer update
	detailDiscountValue	= 0.0;
	detailTaxValue		= 0.0;
	arrayClear( detailTotalChargeType );
	arrayClear( detailTotalChargeValue );
	detailTotalChargeEntries = 0;

//logStdout("IFW_TAP3.DETAIL.STD_MAPPING "+recordNum+" (Type:"+recordType+")\n");
	Bool retval;

	if      (recordType == type_MOC)
	{
	  record_Type = record_MOC;
	  retval = processMOC();
	}
	else if (recordType == type_MTC)
	{
	  record_Type = record_MTC;
	  retval = processMTC();
	}
	else if ( (recordType == type_GPRS_GG) or (recordType == type_GPRS_SG) or (recordType == type_GPRS_assembled) )
	{
	  record_Type = record_GPRS;
	  retval = processGPRS();
	}
	else if (recordType == type_MSS)
	{
	  record_Type = record_MSS;
	  retval = processMSS();
	}
	else if (recordType == type_SCU)
	{
	  record_Type = record_SCU;
	  retval = processSCU();
	}
	else if (recordType == type_VAS)
	{
	  record_Type = record_VAS;
	  retval = processVAS();
	}
	else if (recordType == type_CONT)
	{
	  record_Type = record_CONT;
	  retval = processCONT();
	}
	else
	{
	  record_Type = 0; //ie. invalid
//	  logStdout( "ERROR: tap3 illegal record type ("+recordType+") - EDR "+recordNum+" will be rejected\n" );
	  edrAddError( "ERR_ILL_RECORD_TYPE", 3, recordType); // Major
	  retval        = false;
	  lastDetailIdx = (-1);
 	}
	
	if (retval == false)
	{
	  if (lastDetailIdx >= 0) //ie. recordType was recognized
	  {
//          logStdout( "ERROR: record type ("+recordType+") - EDR "+recordNum+" will be rejected\n" );
	    edrAddError( "INF_EDR_REJECTED", 3); // Major //TODO, use a better message 
            logFormat( "ERROR: processing failed, record type ("+recordType+") - EDR "+recordNum+" will be rejected\n" );
	    // if we began nuilding the ASN.1 output, delete the node sub-tree
	    asnTreeGetStoredNode(theDetailRootIdx);
	    asnTreeDeleteNodeByIndex(lastDetailIdx);
	    lastDetailIdx = (-1);
	  }
	  edrReject();
	}
	else
	{
	  // Update the TRAILER statistic
	  nbWrittenDetails = nbWrittenDetails +1;
          if ( edrDate( DETAIL.CHARGING_START_TIMESTAMP ) < firstCall_date )
          {
            firstCall_date   = edrDate( DETAIL.CHARGING_START_TIMESTAMP );
	    firstCall_offset = edrString( DETAIL.UTC_TIME_OFFSET );
          }
          if ( edrDate( DETAIL.CHARGING_START_TIMESTAMP ) > lastCall_date )
          {
            lastCall_date   = edrDate( DETAIL.CHARGING_START_TIMESTAMP );
	    lastCall_offset = edrString( DETAIL.UTC_TIME_OFFSET );
          }
	  updateAuditTotalCharge();
	  updateAuditTotalDiscount();
	  updateAuditTotalTax();
	}
      }
    ;
}


