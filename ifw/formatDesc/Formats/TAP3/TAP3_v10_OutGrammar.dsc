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
//   Output grammar file for the TAP3_v10 CDR format 
//
//------------------------------------------------------------------------------
// $Log: TAP3_v10_OutGrammar.dsc,v $
//
// Revision       14-Sep-2005   7.2_Patch   knijhawa
// PRSF00181931   Supporting optional field CallReference
//
// Revision       14-Sep-2005   7.2_Patch knijhawa
// PRSF00181928   TAP-Out - CallTypeGroup should be present only once in a MOC record
//
// Revision       14-Sep-2005   7.2_Patch knijhawa
// PRSF00181926   Tag CalledCountryCode set to a fixed and wrong value in TAP3 v10 Output grammar
//
// Revision       14-Sep-2005   7.2_Patch knijhawa
// PRSF00181924   Error in TAP Out grammar when emitting AccessPointNameOI
//
// Revision       26-Apr-2004   6.7_FP2 sraut
// PRSF00107203   TAX_VALUE and TAXABLE_AMOUNT changes for taxation plugin
//
// Revision       07-Jan-2004   6.7_FP1   sraut
// PRSF00084576   Add TAP3 changes for following blocks/sub-blocks:
//                Taxation, Content, Location, VAS, GPRS, HSCSD, 
//                TAP_TOTAL_CHARGE_VALUE_LIST
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
  use EXT_AsnTree;	// iScript extension to build a Tree of ASN.1 object
  			// used to fill the Length value of the ASN.1 bloc,
			// before printing on output stream

  const Long theTap3SpecificationVersionNumber = 3;
  const Long theTap3ReleaseVersionNumber       = 10;

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
  Decimal detailTotalChargeValueRefund[];
  
  // constants
  Long record_Header;
  Long record_Trailer;
  Long record_MOC;
  Long record_MTC;
  Long record_MSS;
  Long record_SCU;
  Long record_VAS;
  Long record_CONT;
  Long record_LOCN;
  Long record_GPRS;
  Long record_Type; // use to know which type of detail we are reading

  // constants
  Long service_Basic;
  Long service_Camel;
  Long service_Gprs;
  Long service_Suppl;
  Long service_Vas;
  Long service_Content;
  Long service_Location;
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
  String type_LOCN;
  String type_GPRS;
  String type_GPRS_SG;
  String type_GPRS_GG;
  String type_GPRS_assembled;
//String extension_GSMW;
//String extension_GPRS;
//String extension_CONT;
//String extension_LOCN;
//String extension_CBD;

  // for Header data storage
  String  headerUtcTimeOffset;
  Long    nbReceivedDetails;
  Long    nbWrittenDetails;
  Decimal theTotalDiscountValue;
  Decimal theTotalDiscountRefund;
  Decimal theTotalTaxValue;
  Decimal theTotalTaxValueRefund;
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
  Long    theVasInfoListIdx;
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
  String vasDesc[];
  
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
  Decimal totalChargeValueRefund[];

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
  String reg_DefaultCalledCountryCode;
  
  // storage of registry values
  String defaultTapCurrency;
  String defaultLocalCurrency;
  String defaultCalledCountryCode;

  String defaultChargedCurrency;
  

  Bool chargeRefundFlag;

  //Advised charge for Content service
  Bool advisedChargeDetectedFlag;
  String  advisedChargeCurrency[]; 
  Decimal totalAdvisedCharge[];
  Decimal totalAdvisedChargeRefund[];
  Decimal totalCommission[];
  Decimal totalCommissionRefund[];
  Long    totalAdvisedChargeCurrencyEntries;
  
  //Variables to identify the discount type
  Long discountApplied_fixedDiscountValue;
  Long discountApplied_discountRate;
  
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
    reg_DefaultCalledCountryCode        = reg_TapPipeline + ".CalledCountryCode";

    defaultCalledCountryCode            = regString(reg_DefaultCalledCountryCode);

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
    record_LOCN   =8;
    record_Type   =0; // use to know which type of detail we are reading

    service_Basic   =1;
    service_Camel   =2;
    service_Gprs    =3;
    service_Suppl   =4;
    service_Vas     =5;
    service_Content =6;
    service_Location=7;
    service_Type    =0; // use to know which type of service we are reading

    type_HEADER 	="010";
    type_TRAILER	="090";
    type_MOC    	="021";
    type_MTC    	="031";
    type_MSS    	="029";
    type_GPRS_SG	="040";
    type_GPRS_GG	="042";
    type_GPRS_assembled	=type_GPRS_GG;		//default for mixed ticket
    type_GPRS		=type_GPRS_assembled;	//default is mixed ticket
    type_SCU    	="050"; 
    type_VAS    	="060";
    type_CONT    	="070";
    type_LOCN    	="080";

//  extension_GSMW 	="520";
//  extension_GPRS 	="540";
//  extension_CONT 	="550";
//  extension_LOCN 	="560";
//  extension_CBD  	="980";			//TODO check (here global charge)
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
    arrayClear( vasDesc );
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
    arrayClear( totalChargeValueRefund );
    totalChargeEntries = 1;
    totalChargeType[0] = "00";
    totalChargeValue[0]= 0.0;
    totalChargeValueRefund[0]= 0.0;

    // Trailer Total Discount
    theTotalDiscountValue = 0.0;
    theTotalDiscountRefund = 0.0;
    
    theTotalTaxValue = 0.0;
    theTotalTaxValueRefund = 0.0;
    
    // initialize TRAILER statistics
    firstCall_date	= MAX_DATE;
    firstCall_offset	= "+0000";
    lastCall_date	= MIN_DATE;
    lastCall_offset	= "+0000";

    // initialize the ASN_TreeNode indexes with invalid values
    theAccountingInfoIdx     = (-1);
    theNetworkInfoIdx        = (-1);
    theVasInfoListIdx            = (-1);
    theMessageDescriptionIdx = (-1);
    theDetailRootIdx         = (-1);
    lastDetailIdx            = (-1);
    
    // empty stream identification
    nbReceivedDetails	     = 0;
    nbWrittenDetails	     = 0;
    advisedChargeDetectedFlag = false;

    arrayClear( advisedChargeCurrency );
    arrayClear( totalAdvisedChargeRefund );
    arrayClear( totalAdvisedCharge );
    arrayClear( totalCommissionRefund );
    arrayClear( totalCommission );
    totalAdvisedChargeRefund[0] = 0.0;
    totalAdvisedCharge[0] = 0.0;
    totalCommissionRefund[0] = 0.0;
    totalCommission[0] = 0.0;
    totalAdvisedChargeCurrencyEntries = 0;


    discountApplied_discountRate       = 1;
    discountApplied_fixedDiscountValue = 2;
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
    //  return true;
    //}
    for (i=0 ; i<detailTotalChargeEntries ; i=i+1)
    {
      if (detailTotalChargeType[i] == TotalChargeType)
      {
        if( chargeRefundFlag == false )
            detailTotalChargeValue[i] = detailTotalChargeValue[i] + TotalChargeValue;
        else
            detailTotalChargeValueRefund[i] = detailTotalChargeValueRefund[i] + TotalChargeValue;

        return true;
      }
    }
    // if we get here, the type is not yet used.
    detailTotalChargeType[i] = TotalChargeType;

    if ( chargeRefundFlag == false )
        detailTotalChargeValue[i]= TotalChargeValue;
    else
        detailTotalChargeValueRefund[i]= TotalChargeValue;
        
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
          totalChargeValueRefund[i] = totalChargeValueRefund[i] + detailTotalChargeValueRefund[j];
          notupdated          = false;
        }
      }
      if (notupdated==true)
      {
        // if we get here, the type is not yet used.
        totalChargeType[i] = detailTotalChargeType[j];
        totalChargeValue[i]= detailTotalChargeValue[j];
        totalChargeValueRefund[i]= detailTotalChargeValueRefund[j];
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
      if ( chargeRefundFlag == false )
          theTotalDiscountValue = theTotalDiscountValue + detailDiscountValue ;
      else
          theTotalDiscountRefund = theTotalDiscountRefund + detailDiscountValue ;

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
      if ( chargeRefundFlag == false )
          theTotalTaxValue = theTotalTaxValue + detailTaxValue ;
      else
          theTotalTaxValueRefund = theTotalTaxValueRefund + detailTaxValue ;
   
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
  function Long getVasShortDescCode(String VasShortDesc, String VasDesc)
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
    vasDesc[i] = VasDesc;
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
      asnTreePushTag("IFW_TAP3.TaxationList");
      for (i=1 ; i<=taxEntries ; i=i+1)
      {
        asnTreePushTag("IFW_TAP3.Taxation");
        asnTreeAddInteger("IFW_TAP3.TaxCode.TAX_CODE", i);
        asnTreeAddString("IFW_TAP3.TaxType.TAX_TYPE", "13" ); //ie ValueAddedTax
        asnTreeAddString("IFW_TAP3.TaxRate.TAX_RATE", taxRate[i] );
        asnTreePop(); //asnTreePushTag("IFW_TAP3.Taxation");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.TaxationList");
    }
    if (discountEntries > 0)
    {
      asnTreePushTag("IFW_TAP3.DiscountingList");
      for (i=1 ; i<=discountEntries ; i=i+1)
      {
        asnTreePushTag("IFW_TAP3.Discounting");
        asnTreeAddInteger("IFW_TAP3.DiscountCode.DISCOUNT_CODE", i);
        asnTreeAddInteger("IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT", discountApplied[i] );
        asnTreePop(); //asnTreePushTag("IFW_TAP3.Discounting");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.DiscountingList");
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
      asnTreePushTag("IFW_TAP3.CurrencyConversionList");
      for (i=1 ; i<=exchangeRateEntries ; i=i+1)
      {
        asnTreePushTag("IFW_TAP3.CurrencyConversion");
        asnTreeAddInteger("IFW_TAP3.ExchangeRateCode.CODE", i);
        asnTreeAddInteger("IFW_TAP3.NumberOfDecimalPlaces.NUMBER_OF_DECIMAL_PLACES", theExchangeDecimalPlaces);
        asnTreeAddInteger("IFW_TAP3.ExchangeRate.EXCHANGE_RATE", exchangeRate[i]);
        asnTreePop(); //asnTreePushTag("IFW_TAP3.CurrencyConversion");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CurrencyConversionList");
    }
    else
    {
      // default is an exchange rate of 1/1
      asnTreePushTag("IFW_TAP3.CurrencyConversionList");
      asnTreePushTag("IFW_TAP3.CurrencyConversion");
      asnTreeAddInteger("IFW_TAP3.ExchangeRateCode.CODE", 1);
      asnTreeAddInteger("IFW_TAP3.NumberOfDecimalPlaces.NUMBER_OF_DECIMAL_PLACES", theExchangeDecimalPlaces);
      asnTreeAddInteger("IFW_TAP3.ExchangeRate.EXCHANGE_RATE", decimalToLong(theExchangeRateMultiplier));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CurrencyConversion");
      asnTreePop(); //asnTreePushTag("IFW_TAP3.CurrencyConversionList");
    }
    asnTreeAddInteger("IFW_TAP3.TapDecimalPlaces.TAP_DECIMAL_PLACES", theTapDecimalPlaces);
    asnTreePop(); //asnTreePushTag("IFW_TAP3.AccountingInfo");
    
    // theNetworkInfoIdx
    //=====================
    asnTreeGetStoredNode(theNetworkInfoIdx); // ie asnTreePushTag("IFW_TAP3.NetworkInfo");
    asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfoList");
    for (i=1 ; i<=utcTimeOffsetEntries ; i=i+1)
    {
      asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfo");
      asnTreeAddInteger("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE", i);
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", utcTimeOffset[i]  );
      asnTreePop(); //asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfo");
    }
    if (utcTimeOffsetEntries == 0)
    {
      asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfo");
      asnTreeAddInteger("IFW_TAP3.UtcTimeOffsetCode.UTC_TIME_OFFSET_CODE", 1);
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", defUtcTimeOffset  );
      asnTreePop(); //asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfo");
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.UtcTimeOffsetInfoList");
    if (recEntityEntries > 0)
    {
      asnTreePushTag("IFW_TAP3.RecEntityInfoList");
      for (i=1 ; i<=recEntityEntries ; i=i+1)
      {
	asnTreePushTag("IFW_TAP3.RecEntityInformation");
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
	asnTreePop(); //asnTreePushTag("IFW_TAP3.RecEntityInformation");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.RecEntityInfoList");
    }
    asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", theNetworkType);
    asnTreePushTag("IFW_TAP3.CalledNumAnalysisList");
    asnTreePushTag("IFW_TAP3.CalledNumAnalysis");
    asnTreeAddInteger("IFW_TAP3.CalledNumAnalysisCode.CALLED_NUM_ANALYSIS_CODE", 1);

    asnTreePushTag("IFW_TAP3.CountryCodeList");
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
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CountryCodeList");

    asnTreePushTag("IFW_TAP3.IacList");
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
    asnTreePop(); //asnTreePushTag("IFW_TAP3.IacList");
    
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CalledNumAnalysis");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CalledNumAnalysisList");
    asnTreePop(); //asnTreePushTag("IFW_TAP3.NetworkInfo");

    // theVasInfoListIdx
    //=====================
    if (vasEntries > 0)
    {
      asnTreeGetStoredNode(theVasInfoListIdx); // ie asnTreePushTag("IFW_TAP3.VasInfoList");
      for (i=1 ; i<=vasEntries ; i=i+1)
      {
	asnTreePushTag("IFW_TAP3.VasInformation");
	asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", i);
	asnTreeAddString("IFW_TAP3.VasShortDescription.VAS_SHORT_DESCRIPTION", vasShortDesc[i]  );
	asnTreeAddString("IFW_TAP3.VasDescription.VAS_DESCRIPTION", vasDesc[i]  );
	asnTreePop(); //asnTreePushTag("IFW_TAP3.VasInformation");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.VasInfoList");
    }
    else
    {
      asnTreeDeleteNodeByIndex(theVasInfoListIdx);
      theVasInfoListIdx = 0;
    }

    // theMessageDescriptionIdx
    //==========================
    if (messageDescriptionEntries > 0)
    {
      asnTreeGetStoredNode(theMessageDescriptionIdx); // ie asnTreePushTag("IFW_TAP3.MessageDescription");
      for (i=1 ; i<=messageDescriptionEntries ; i=i+1)
      {
	asnTreePushTag("IFW_TAP3.MessageDescriptionInformation");
	asnTreeAddInteger("IFW_TAP3.MessageDescriptionCode.MESSAGE_DESCRIPTION_CODE", i);
	asnTreeAddString("IFW_TAP3.MessageDescription.MESSAGE_DESCRIPTION", messageDescription[i]  );
	asnTreePop(); //asnTreePushTag("IFW_TAP3.MessageDescriptionInformation");
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
  
  function Bool addGeographicalLocation
  {
      asnTreePushTag("IFW_TAP3.GeographicalLocation");
      String tmpGeographicalLocation = edrString(DETAIL.GEOGRAPHICAL_LOCATION);
      String tmpGeoLocArray[];

      Long nbElem = strSplit(tmpGeoLocArray, tmpGeographicalLocation, ",");
      Long i;

      for (i = 0; i < nbElem; i = i+2) //Every even index will contain key, so we jump 2 (i = i+2)
      {
          switch(strToLong(tmpGeoLocArray[i]))
          {
             //These case values are defined as follwos in the input grammar
             //  const String servingNetworkKey        = "1";
             //  const String servingBIDKey            = "2";
             //  const String servingLocationDescKey   = "3";
             //  const String longitudeKey             = "4";
             //  const String latitudeKey              = "5";

             case 1: // This is ServingNetwork
                 asnTreeAddString("IFW_TAP3.ServingNetwork.SERVING_NETWORK", tmpGeoLocArray[i+1]);
             break;
             case 2: // This is ServingBID
                 asnTreeAddString("IFW_TAP3.ServingBid.SERVING_BID", tmpGeoLocArray[i+1]);
             break;
             case 3: // This is ServingLocationDescription
                 asnTreeAddString("IFW_TAP3.LocationDescription.LOCATION_DESCRIPTION", tmpGeoLocArray[i+1]);
             break;
             case 4: // This is Longitude
                  asnTreeAddInteger("IFW_TAP3.Longitude.LONGITUDE", strToLong(tmpGeoLocArray[i+1]));
             break;
             case 5: // This is Latitude
                 asnTreeAddInteger("IFW_TAP3.Latitude.LATITUDE", strToLong(tmpGeoLocArray[i+1]));
             break;
         }
              
      }
      asnTreePop(); // ("IFW_TAP3.GeographicalLocation");
      return true;
  }

  function addLocationInformation(String switchIdentification)
  {
    // IFW_TAP3.LocationInformation
    //============================
    asnTreePushTag("IFW_TAP3.LocationInformation");
    asnTreePushTag("IFW_TAP3.NetworkLocation");
   
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE", getRecEntityIdCode(switchIdentification,recEntityType_MSC) );
    if (edrString(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0) != "")
    {
      asnTreeAddString("IFW_TAP3.CallReference.CALL_REFERENCE", edrString(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0));
    }
    if (edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0) != "")
    {
      asnTreeAddInteger("IFW_TAP3.LocationArea.LOCATION_AREA",strToLong(edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0)) );
    }
    if (edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0) != "")
    {
      asnTreeAddInteger("IFW_TAP3.CellId.CELL_ID",strToLong(edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0)) );
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.NetworkLocation");

    // Add Geographical Location details
    if( edrString(DETAIL.GEOGRAPHICAL_LOCATION) != "")
        addGeographicalLocation();

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

    // Added for GPRS Multi-SGSN Support - Start

    // Get the count of SGSN blocks
    Long sgsnCount = edrNumDatablocks(DETAIL.ASS_GPRS_EXT.SGSN_INFO_LIST, 0);
    Long idxSGSN   = 0;

    // Loop through the list of SGSN's and add them to the ASN Tree
    for ( idxSGSN = 0; idxSGSN < sgsnCount; idxSGSN = idxSGSN + 1)
    {
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE",
      		        getRecEntityIdCode(edrString(DETAIL.ASS_GPRS_EXT.SGSN_INFO_LIST.SGSN_ADDRESS, 0, idxSGSN),
                                           recEntityType_SGSN));
    }

    // Added for GPRS Multi-SGSN Support - End

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

    if( edrString(DETAIL.GEOGRAPHICAL_LOCATION) != "")
        addGeographicalLocation();
    
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

  function Long addChargeInformation(Long startCPidx, Long nbCP,Long idxASSCBD, Long idxBlock)
  {
    Bool    multiRateSet = false;
    String  savedDayCategory;
    String  savedTimeBand;

    String  daycategory;
    String  timeband;
    String  startRUM             = edrString(DETAIL.ASS_CBD.CP.RUM, idxASSCBD, startCPidx);
    Decimal startEXCHANGE_RATE   = edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, idxASSCBD, startCPidx);
    String  startPRODUCTCODE_USED= edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, idxASSCBD, startCPidx);
    Decimal sumDiscountValue	  = 0.0 ;
    Decimal sumTaxValue	  = 0.0 ;
    Long tmpDiscountType;
    Long i; 

    String  thisTapCurrency       = edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, idxASSCBD, startCPidx);
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
    String  thisLocalCurrency     = edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, idxASSCBD, startCPidx);
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
      if ( strLength(edrString(DETAIL.CONNECT_TYPE)) >= 2 and (camelServiceDetected == false) and (vasServiceDetected == false) )
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
            asnTreeAddString("IFW_TAP3.CalledCountryCode.CALLED_COUNTRY_CODE", defaultCalledCountryCode );
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
    
    while ( (startRUM              == edrString(DETAIL.ASS_CBD.CP.RUM, idxASSCBD, currentCPidx))                and
//          (startEXCHANGE_RATE    == edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, idxASSCBD, currentCPidx))     and
            (startPRODUCTCODE_USED == edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, idxASSCBD, currentCPidx))   and
	    (lastChargeType        != "00")								and
	    (currentCPidx	   <  nbCP ) )
    {      
      //only write relevant ChargePackets (otherwise, skip to the next one)
      if (  ((edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, idxASSCBD, currentCPidx) == defaultChargedCurrency)and
             (edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE,       idxASSCBD, currentCPidx) == "S"))
          or((edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, idxASSCBD, currentCPidx) == defaultChargedCurrency)and
             (edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE,       idxASSCBD, currentCPidx) == "A")and
             (edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY,       idxASSCBD, currentCPidx) == "00"))
         )
      {
        lastChargeType = edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, idxASSCBD, currentCPidx);
        asnTreePushTag("IFW_TAP3.ChargeDetail");
	nbWrittenCP = nbWrittenCP +1;
        if (lastChargeType != "")
        {
          asnTreeAddString("IFW_TAP3.ChargeType.CHARGE_TYPE", lastChargeType);    
        }
        //if (edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, idxASSCBD, currentCPidx) != 0.0) //TODO uncomment to skip null charges
        {
          lastChargeValue = round(theAbsoluteAmountMultiplier * edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, idxASSCBD, currentCPidx));
          charge_00       = charge_00 + lastChargeValue;
          asnTreeAddInteger("IFW_TAP3.Charge.CHARGE", decimalToLong(lastChargeValue));
	  if (lastChargeType != "")
	  {
	    storeDetailTotalCharge( lastChargeType, lastChargeValue);
	  }
	  else
	  {
	    // ERROR: this case should never happen, ChargeType must always be set when charge!=0
	    //storeDetailTotalCharge( "99", lastChargeValue); //TODO this "99" is normally reserved
	  }
        }
	  
        lastChargedUnits    = decimalToLong(edrDecimal(DETAIL.ASS_CBD.CP.ROUNDED_QUANTITY_VALUE, idxASSCBD, currentCPidx));
        lastChargeableUnits = decimalToLong(edrDecimal(DETAIL.ASS_CBD.CP.CHARGEABLE_QUANTITY_VALUE, idxASSCBD, currentCPidx));
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
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, idxASSCBD, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        asnTreeAddString("IFW_TAP3.DayCategory.DAY_CATEGORY", edrString(DETAIL.ASS_CBD.CP.DAY_CODE, idxASSCBD, currentCPidx));    
        asnTreeAddString("IFW_TAP3.TimeBand.TIME_BAND",       edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, idxASSCBD, currentCPidx));    
        // Prepare to set the MultiRateIndicator field
        if (multiRateSet == false) {
          daycategory = edrString(DETAIL.ASS_CBD.CP.DAY_CODE, idxASSCBD, currentCPidx);    
          timeband = edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, idxASSCBD, currentCPidx);    
          if (idx == 0) {               // Cache on the first charge detail
            savedDayCategory = edrString(DETAIL.ASS_CBD.CP.DAY_CODE, idxASSCBD, currentCPidx);
            savedTimeBand = edrString(DETAIL.ASS_CBD.CP.TIME_INTERVAL_CODE, idxASSCBD, currentCPidx);
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

        sumDiscountValue = sumDiscountValue + edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, idxASSCBD, currentCPidx);

        //Get the discount applied type
        tmpDiscountType = strToLong(edrString(DETAIL.ASS_CBD.CP.DISCOUNTMODEL_CODE,idxASSCBD, currentCPidx));

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
      addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, idxASSCBD, startCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
      asnTreeAddString("IFW_TAP3.DayCategory.DAY_CATEGORY", "I");   // Independant of day 
      asnTreeAddString("IFW_TAP3.TimeBand.TIME_BAND",       "I");   // Independant of time     
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeDetail");
    }

    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeDetailList");


    if (edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE) != 0)
    {
        Long relatedChargeInfoIdCP = edrLong(DETAIL.ASS_CBD.CP.RELATED_CHARGE_INFO_ID, idxASSCBD, startCPidx);
        asnTreePushTag("IFW_TAP3.TaxInformationList");

        // changes start - Added TAX_PACKET related changes
        Long TPcount    = edrNumDatablocks( DETAIL.ASS_CBD.TP, idxASSCBD );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_TAX_PACKETS,0);
        Long currentTPidx = 0;

        for (currentTPidx = 0; TPcount > currentTPidx; currentTPidx = currentTPidx + 1)
        {
            Long idxTaxPacRelRec = edrLong(DETAIL.ASS_CBD.TP.RELATED_RECORD_NUMBER, idxASSCBD, currentTPidx) ;
            Long relatedChargeInfoIdTP = edrLong(DETAIL.ASS_CBD.TP.RELATED_CHARGE_INFO_ID, idxASSCBD, currentTPidx);

            if ( (idxTaxPacRelRec == idxBlock) and ( relatedChargeInfoIdTP == relatedChargeInfoIdCP) )
            {
                asnTreePushTag("IFW_TAP3.TaxInformation");
                // TaxRate comes in TAP3 with 5 decimal places, and in ifw we store only 2 ???
                asnTreeAddInteger("IFW_TAP3.TaxCode.TAX_CODE", getTaxRateCode(longToStr(edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE))+"000"));

                sumTaxValue = edrDecimal(DETAIL.ASS_CBD.TP.TAX_VALUE, idxASSCBD, currentTPidx);
                asnTreeAddInteger("IFW_TAP3.TaxValue.TAX_VALUE", edrLong(DETAIL.ASS_CBD.TP.TAX_VALUE, idxASSCBD, currentTPidx));
                if ((edrString(DETAIL.ASS_CBD.TP.CHARGE_TYPE, idxASSCBD, currentTPidx)) != "")
                {
                    asnTreeAddString("IFW_TAP3.ChargeType.CHARGE_TYPE", edrString(DETAIL.ASS_CBD.TP.CHARGE_TYPE, idxASSCBD, currentTPidx));
                }
                if ((edrLong(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, idxASSCBD, currentTPidx)) != 0)
                {
                    asnTreeAddInteger("IFW_TAP3.TaxableAmount.TAXABLE_AMOUNT", edrLong(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, idxASSCBD, currentTPidx));
                }
                storeDetailTotalTax(sumTaxValue);
                asnTreePop(); //asnTreePushTag("IFW_TAP3.TaxInformation");
            }
        }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.TaxInformationList");
      
	  // end - Added TAX_PACKET related changes
    }

    if (sumDiscountValue != 0.0)
    {
      asnTreePushTag("IFW_TAP3.DiscountInformation");
      sumDiscountValue      = trunc(theAbsoluteAmountMultiplier * sumDiscountValue);
      storeDetailTotalDiscount(sumDiscountValue);
      asnTreeAddInteger("IFW_TAP3.DiscountCode.DISCOUNT_CODE", getDiscountCode(decimalToLong(sumDiscountValue)));

      // Check for the discount applied type. if it is of type discount rate then DiscountValue should
      // be populated

      if ( tmpDiscountType == discountApplied_discountRate ) 
      {
          asnTreeAddInteger("IFW_TAP3.DiscountValue.ABSOLUTE_AMOUNT", decimalToLong(sumDiscountValue));
      }

      asnTreePop(); //asnTreePushTag("IFW_TAP3.DiscountInformation");
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargeInformation");

    if ( currentCPidx < nbCP ) // there are CPs left to write
    {
      if (edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, idxASSCBD, currentCPidx) == "CAMEL")
      {
        camelServiceDetected = true; // NB: global variable, do not reset to false once it is set to true !
      }
      else if (edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, idxASSCBD, currentCPidx) != startPRODUCTCODE_USED)
      {
        vasServiceDetected = true; // NB: global variable, do not reset to false once it is set to true !
      }
    }
    return currentCPidx;
  }

  function Long addCamelServiceUsed(Long startCPidx, Long nbCP)
  {
    asnTreePushTag("IFW_TAP3.CamelServiceUsed");
    asnTreeAddString("IFW_TAP3.CamelServerAddress.CAMEL_SERVER_ADDRESS", edrString(DETAIL.ASS_CAMEL_EXT.SERVER_ADDRESS, 0));
    asnTreeAddInteger("IFW_TAP3.CamelServiceLevel.CAMEL_SERVICE_LEVEL", edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_LEVEL, 0));
    asnTreeAddInteger("IFW_TAP3.CamelServiceKey.CAMEL_SERVICE_KEY", edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_KEY, 0));
    asnTreeAddInteger("IFW_TAP3.DefaultCallHandlingIndicator.DEFAULT_CALL_HANDLING_INDICATOR",
		      edrLong(DETAIL.ASS_CAMEL_EXT.DEFAULT_CALL_HANDLING_INDICATOR, 0));
    asnTreePushTag("IFW_TAP3.CamelCallReference");
    asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.ASS_CAMEL_EXT.MSC_ADDRESS, 0));
    asnTreeAddString("IFW_TAP3.CamelCallReferenceNumber.CAMEL_CALL_REFERENCE_NUMBER", edrString(DETAIL.ASS_CAMEL_EXT.CAMEL_REFERENCE_NUMBER, 0));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.CamelCallReference");
      
    // change start - Added code for related record number

      Long currentCPidx = 0;  //start from the beginning (first CP)
      Long CPcount      = edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
      if (CPcount > 0)
      {
        Long    recordNum               = edrLong(DETAIL.ASS_CAMEL_EXT.RECORD_NUMBER, 0);
        while ((camelServiceDetected == true) and (currentCPidx < CPcount))
        {
          Long relatedRecordNum = edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, 0, currentCPidx);

          // if detail record number and CP related record number match then add this charge info.
          if (recordNum == relatedRecordNum)
          {
            currentCPidx = addChargeInformation(currentCPidx, CPcount,0, relatedRecordNum);
          }
          else
          {
            currentCPidx =  currentCPidx + 1;
          }
        }
      }

    // change end - Added code for related record number
      
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
      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0));
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
			 strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), 0, (sepIndex) ) );
        asnTreeAddString("IFW_TAP3.AccessPointNameOI.ACCESS_POINT_NAME_OI",
			 strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), (sepIndex+2), 
			 	   strLength(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)) - (sepIndex+2) ) );
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
    
    //CSE Information
    if (edrString(DETAIL.ASS_CAMEL_EXT.CSE_INFORMATION, 0) != "")
    {
       asnTreeAddString("IFW_TAP3.CseInformation.CSE_INFORMATION", edrString(DETAIL.ASS_CAMEL_EXT.CSE_INFORMATION, 0));
    }

    asnTreePop(); //asnTreePushTag("IFW_TAP3.CamelServiceUsed");
    return currentCPidx;
  }

  
  // changes start - Added functions for HSCSD_INFORMATION_PACKET, BASIC_SERVICE_PACKET, ASSOCIATED_VAS_EXTENSION
  //                 and ChargeInformationForSS

  function Bool addHSCSDInformation(Long idx)
  {
    Long i = 0;
    Long count = 0;

    if ( edrNumDatablocks( DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET, 0, idx) > 0)
    {
      asnTreePushTag("IFW_TAP3.HSCSDInformation");
      asnTreePushTag("IFW_TAP3.BasicHSCSDParameters");
      if (edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.NUMBER_OF_CHANNELS, 0, idx, 0) != 0)
      {
        asnTreeAddInteger("IFW_TAP3.NumberOfChannels.NUMBER_OF_CHANNELS", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.NUMBER_OF_CHANNELS, 0, idx, 0));
      }
      asnTreePushTag("IFW_TAP3.ChannelCodingAcceptableList");
        String ListArray[]; 
        String ListString = edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.CHANNEL_CODING_OK_LIST, 0, idx, 0);
        Long nbElem = strSplit( ListArray, ListString, "," ); 
        for (i=0 ; i<nbElem ; i=i+1) 
        { 
          asnTreeAddInteger("IFW_TAP3.ChannelCoding.CHANNEL_CODING", strToLong(ListArray[i]));
        }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ChannelCodingAcceptableList");
      asnTreeAddInteger("IFW_TAP3.ChannelCoding.CHANNEL_CODING", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.CHANNEL_CODING_USED, 0, idx, 0));
      asnTreeAddInteger("IFW_TAP3.NumberOfChannelsUsed.NUMBER_OF_CHANNELS_USED", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.NUMBER_OF_CHANNELS_USED, 0, idx, 0));

      asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicHSCSDParameters"); 
      count = edrNumDatablocks(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST, 0, idx, 0);
      if (i > 0)
      {
        asnTreePushTag("IFW_TAP3.HSCSDParameterModificationList");
        for (i = 0; count > i; i = i + 1)
        {
          asnTreePushTag("IFW_TAP3.HSCSDParameterModification");
          if (edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.AIUR, 0, idx, 0,  i) != 0)
          {
            asnTreeAddInteger("IFW_TAP3.AiurRequested.AIUR_REQUESTED", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.AIUR, 0, idx, 0,  i));
          }
          if (edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.MAX_NUMBER_OF_CHANNELS, 0, idx, 0,  i) != 0)
          {
            asnTreeAddInteger("IFW_TAP3.NumberOfChannels.NUMBER_OF_CHANNELS", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.MAX_NUMBER_OF_CHANNELS, 0, idx, 0,  i));
          }
          asnTreeAddInteger("IFW_TAP3.ChannelCoding.CHANNEL_CODING", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.CHANNEL_CODING_USED, 0, idx, 0,  i));
          asnTreeAddInteger("IFW_TAP3.NumberOfChannelsUsed.NUMBER_OF_CHANNELS_USED", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.NUMBER_OF_CHANNELS_USED, 0, idx, 0,  i));
          asnTreeAddInteger("IFW_TAP3.InitiatingParty.INITIATING_PARTY", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.INITIATING_PARTY, 0, idx, 0,  i));
          asnTreePushTag("IFW_TAP3.ModificationTimestamp");
          addDateTime(dateToStr(edrDate(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.MODIFICATION_TIMESTAMP, 0, idx, 0, i)), edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.HSCSD_INFO_PACKET.PM_LIST.UTC_TIME_OFFSET, 0, idx, 0, i));
          asnTreePop(); //asnTreePushTag("IFW_TAP3.ModificationTimestamp");

          asnTreePop(); //asnTreePushTag("IFW_TAP3.HSCSDParameterModification");
        }
        asnTreePop(); //asnTreePushTag("IFW_TAP3.HSCSDParameterModificationList");
      }

      asnTreePop(); //asnTreePushTag("IFW_TAP3.HSCSDInformation");
    }
    return true;
  }


  function Bool addBasicServiceUsed
  {
    Long idx = 0;
    Long count = edrNumDatablocks( DETAIL.ASS_GSMW_EXT.BS_PACKET, 0);
    for (idx = 0; count > idx; idx = idx + 1)
    {
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
      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.QOS_REQUESTED, 0, idx) != "")
      {
        asnTreeAddInteger("IFW_TAP3.RadioChannelRequested.RADIO_CHANNEL_REQUESTED", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.QOS_REQUESTED, 0, idx)));
      }
      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.QOS_USED, 0, idx) != "")
      {
        asnTreeAddInteger("IFW_TAP3.RadioChannelUsed.RADIO_CHANNEL_USED", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.QOS_USED, 0, idx)));
      }
      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.SPEECH_VERSION_REQUESTED, 0, idx) != "")
      {
        asnTreeAddInteger("IFW_TAP3.SpeechVersionRequested.SPEECH_VERSION_REQUESTED", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.SPEECH_VERSION_REQUESTED, 0, idx)));
      }
      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.SPEECH_VERSION_USED, 0, idx) != "")
      {
        asnTreeAddInteger("IFW_TAP3.SpeechVersionUsed.SPEECH_VERSION_USED", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.SPEECH_VERSION_USED, 0, idx)));
      }
//logStdout("\nBS_PACKET.TRANSPARENCY_INDICATOR: " + longToStr(edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx)) +
//          "\nidx: " + longToStr(idx));
      if ((edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx) == 0) or (edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx) == 1))
      {
        asnTreeAddInteger("IFW_TAP3.TransparencyIndicator.TRANSPARENCY_INDICATOR", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx));
      }
      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.FNUR, 0, idx) != "")
      {
        asnTreeAddInteger("IFW_TAP3.Fnur.FNUR", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.FNUR, 0, idx)));
      }
      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.AIUR_REQUESTED, 0, idx) != "")
      {
        asnTreeAddInteger("IFW_TAP3.AiurRequested.AIUR_REQUESTED", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.AIUR_REQUESTED, 0, idx)));
      }
      if (edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.USER_PROTOCOL_INDICATOR, 0, idx) != 0)
      {
        asnTreeAddInteger("IFW_TAP3.UserProtocolIndicator.USER_PROTOCOL_INDICATOR", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.USER_PROTOCOL_INDICATOR, 0, idx));
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicService");
      if (dateToStr(edrDate(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHARGING_START_TIMESTAMP, 0, idx)) != "")
      {
        asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHARGING_START_TIMESTAMP, 0, idx)), edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.UTC_TIME_OFFSET, 0, idx));
        asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
      }

      asnTreePushTag("IFW_TAP3.ChargeInformationList");
      Long currentCPidx	= 0;  //start from the beginning (first CP)
      Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
      if (CPcount > 0)
      {
        Long 	recordNum		= edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.RECORD_NUMBER, 0, idx);
        while ((camelServiceDetected == false) and (vasServiceDetected == false) and (currentCPidx < CPcount))
        {
          Long relatedRecordNum = edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, idx, currentCPidx);

          // if detail record number and CP related record number match then add this charge info.
          if (recordNum == relatedRecordNum)
          {
            currentCPidx = addChargeInformation(currentCPidx, CPcount, idx, relatedRecordNum);
          }
          else
          {
            currentCPidx =  currentCPidx + 1;
          }
        }
      }
      else
      {
        addDefaultChargeInformation();
      }
      asnTreePop(); //     asnTreePushTag("IFW_TAP3.ChargeInformationList");

      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.DATA_VOLUME_REFERENCE, 0, idx) != "")
      {
        asnTreeAddInteger("IFW_TAP3.DataVolumeReference.DATA_VOLUME_REFERENCE", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.DATA_VOLUME_REFERENCE, 0, idx)));
      }
      
      addHSCSDInformation(idx);
  
      asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceUsed");

    }
    
    return true;
  }

  function Bool addValueAddedServiceUsedList (Long currentCPidx, Long CPcount)
  {
    Long idx = 0;
    Long count = 0;
    Long i = 0;

    count = edrNumDatablocks( DETAIL.ASS_VAS_EXT );

    if (count > 0)
    {      
      for (idx = 0; count > idx; idx = idx + 1)
      {
        asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
        //asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", getVasShortDescCode(edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, currentCPidx, 0)));
        //asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", getVasShortDescCode(longToStr(edrLong(DETAIL.ASS_VAS_EXT.VAS_CODE, idx))));
        asnTreeAddInteger("IFW_TAP3.VasCode.VAS_CODE", getVasShortDescCode(edrString(DETAIL.ASS_VAS_EXT.VAS_SHORT_DESC, idx), edrString(DETAIL.ASS_VAS_EXT.VAS_DESC, idx)));
        asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, currentCPidx, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");

        Long currentCPidx	= 0;  //start from the beginning (first CP)
        Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
        if (CPcount > 0)
        {	
          Long 	recordNum		= edrLong(DETAIL.ASS_VAS_EXT.RECORD_NUMBER, idx);
          while (currentCPidx < CPcount)
          {
            Long relatedRecordNum = edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, 0, currentCPidx);

            // if detail record number and CP related record number match then add this charge info.
            if ((currentCPidx < CPcount) and (recordNum == relatedRecordNum))
            {
              currentCPidx = addChargeInformation(currentCPidx, CPcount, 0, relatedRecordNum);
            }
            else
            {
              currentCPidx = currentCPidx + 1;
            }
          }
        }
        else
        {
          addDefaultChargeInformation();
        }

        asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsed");
      }
    }
    return true;
  }

  function Bool addChargeInformationForSS(Long idx)
  {
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if (CPcount > 0)
    {
      Long 	recordNum		= edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_NUMBER, 0, idx);
      while (currentCPidx < CPcount)
      {
        Long relatedRecordNum = edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, 0, currentCPidx);

        // if detail record number and CP related record number match then add this charge info.
        if (recordNum == relatedRecordNum)
        {
          currentCPidx = addChargeInformation(currentCPidx, CPcount,0, recordNum);
        }
        else
        {
          currentCPidx = currentCPidx + 1;
        }
      }
    }

    return true;
  }
  // change end - Added functions for HSCSD_INFORMATION_PACKET, BASIC_SERVICE_PACKET, ASSOCIATED_VAS_EXTENSION
  //                 and ChargeInformationForSS
  

  function Bool addDualServiceRequested
  {

    String basicDualServiceprefix;
    String basicDualServiceSuffix;
    if ( strLength(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0)) >= 3)
    {
      basicDualServiceprefix  = strSubstr(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0), 0, 1 ); //take the first 1 digit
      basicDualServiceSuffix = strSubstr(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0), 1, 2 ); //take the last  2 digits
    }
    if (basicDualServiceprefix == "0")
    {
      // prefix "0" -> TeleService
      asnTreeAddString("IFW_TAP3.DualTeleServiceCode.DUAL_TELE_SERVICE_CODE", basicDualServiceSuffix);
    }
    else if (basicDualServiceprefix == "1")
    {
      // prefix "1" -> BearerService
      asnTreeAddString("IFW_TAP3.DualBearerServiceCode.DUAL_BEARER_SERVICE_CODE", basicDualServiceSuffix);
    }

    return true;
  }

  function Bool processMOC
  {
    asnTreePushTag("IFW_TAP3.MobileOriginatedCall");
    lastDetailIdx = asnTreeStoreNode();
    
    // IFW_TAP3.MoBasicCallInformation
    //============================
    asnTreePushTag("IFW_TAP3.MoBasicCallInformation");

    if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
    {
      asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
    }

    asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");

    if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
    {
      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
    }

    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }
    if (edrString(DETAIL.B_NUMBER) != defTelNumber)
    {
      asnTreePushTag("IFW_TAP3.Destination");
      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.B_NUMBER));

      // Dialled Digits
      if (edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0) != "")
      {
         asnTreeAddString("IFW_TAP3.DialledDigits.DIALLED_DIGITS", edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0));
      }

      if (edrString(DETAIL.DESCRIPTION) != "")
      {
          String tmpDescription = edrString(DETAIL.DESCRIPTION);
          Long tmpDescLength = strLength(tmpDescription);
          Long tmpIdx        = strSearch(tmpDescription, ",");

          if (tmpIdx < 0)
          {
              // if we are here then DESCRIPTION contains only called place.
              asnTreeAddString("IFW_TAP3.CalledPlace.CALLED_PLACE",tmpDescription );
            
          }
          else
          {
              // if we are here then DESCRIPTION contains both called place and called region.
              asnTreeAddString("IFW_TAP3.CalledPlace.CALLED_PLACE", strSubstr(tmpDescription, 0, tmpIdx));
              asnTreeAddString("IFW_TAP3.CalledRegion.CALLED_REGION", 
                              strSubstr(tmpDescription,tmpIdx + 1, tmpDescLength - (tmpIdx + 1)));
            
          }
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

    // Populate SIM Toolkit Indicator
    if (edrString(DETAIL.DISCOUNT_KEY) != "")
        asnTreeAddString("IFW_TAP3.SimToolkitIndicator.SIM_TOOLKIT_INDICATOR", edrString(DETAIL.DISCOUNT_KEY));

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

    // change start - Added call for BASIC_SERVICE_PACKET

    addBasicServiceUsed();
    
    // change end - Added call for BASIC_SERVICE_PACKET

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

  // change start - Added SS_PACKET.SS_PARAMETERS
  if (edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_PARAMETERS, 0, currentSSidx) != "")
  {
    asnTreeAddString("IFW_TAP3.SsParameters.SS_PARAMETERS", edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_PARAMETERS, 0, currentSSidx));
  }
  // change end - Added SS_PACKET.SS_PARAMETERS

	if ( (currentSSidx == 0) and (edrString(DETAIL.C_NUMBER) != defTelNumber) ) // write only once
	{
	  asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	  asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.C_NUMBER));

          // CLIR Indicator
          Long clirIndicator = edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.CLIR_INDICATOR, 0, currentSSidx);
          if ( (clirIndicator == 0) or (clirIndicator == 1))
          {
              asnTreeAddInteger("IFW_TAP3.ClirIndicator.CLIR_INDICATOR", clirIndicator);
          }

	  asnTreePop(); //asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	}

    // change start - call addChargeInformationForSS
    //addChargeInformationForSS(currentSSidx);
    // change end - call addChargeInformationForSS

///////////////////////BasicServiceCodeList begin///////////////////////////

         if ( edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.BASIC_SERVICE_CODE_LIST, 0, currentSSidx) != "")
         {
             asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
             String ListArray[]; 
             String ListString = 
                 edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.BASIC_SERVICE_CODE_LIST, 0, currentSSidx);

             String tmpServiceCode;

             Long nbElem = strSplit( ListArray, ListString, "," ); 
             Long i;
             for (i=0 ; i<nbElem ; i=i+1) 
             {
                 //Need to check whether the type of service is bearer service or tele service. 
                 if ( strStartsWith(ListArray[i],"0") ) //prefix is digit "0"
                 {
                     tmpServiceCode = strSubstr(ListArray[i], 1, (strLength(ListArray[i])-1) )    ;
                     asnTreeAddString("IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE", tmpServiceCode );
                 }
                 else //prefix is digit "1"
                 {
                     tmpServiceCode = strSubstr(ListArray[i], 1, (strLength(ListArray[i])-1) )    ;
                     asnTreeAddString("IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE", tmpServiceCode );
                 }
             }
             asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
         }

///////////////////////BasicServiceCodeList end///////////////////////////

	asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsed");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsedList");
    }

    // IFW_TAP3.CamelServiceUsed
    //============================
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      currentCPidx = addCamelServiceUsed(currentCPidx, CPcount);
    }

    // IFW_TAP3.ValueAddedServiceUsedList
    //============================
    if (vasServiceDetected == true)
    {
      asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");

      // change start - Added call to ASSOCIATED_VAS_EXTENSION function

      addValueAddedServiceUsedList(currentCPidx, CPcount);

      // change end - Added call to ASSOCIATED_VAS_EXTENSION function

      asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
    }

    // DualServiceRequested
    if(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0) != "")
        addDualServiceRequested();
    
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

    if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
    {
      asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
    }

    asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");

    if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
    {
      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
    }

    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }
    if (edrString(DETAIL.B_NUMBER) != defTelNumber)
    {
      asnTreePushTag("IFW_TAP3.CallOriginator");
      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.B_NUMBER));
      if (edrString(DETAIL.USAGE_CLASS) != "")
          asnTreeAddString("IFW_TAP3.ClirIndicator.CLIR_INDICATOR", edrString(DETAIL.USAGE_CLASS));

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

    // Populate SIM Toolkit Indicator
    if (edrString(DETAIL.DISCOUNT_KEY) != "")
        asnTreeAddString("IFW_TAP3.SimToolkitIndicator.SIM_TOOLKIT_INDICATOR", edrString(DETAIL.DISCOUNT_KEY));

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

    // change start - Added call to BASIC_SERVICE_PACKET

    addBasicServiceUsed();

    // change end - Added call to BASIC_SERVICE_PACKET

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
  if (edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_PARAMETERS, 0, currentSSidx) != "")
  {
    asnTreeAddString("IFW_TAP3.SsParameters.SS_PARAMETERS", edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_PARAMETERS, 0, currentSSidx));
  }
	if ( (currentSSidx == 0) and (edrString(DETAIL.C_NUMBER) != defTelNumber) ) // write only once
	{
	  asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	  asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.C_NUMBER));

          // CLIR Indicator
          Long clirIndicator = edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.CLIR_INDICATOR, 0, currentSSidx);
          if ( (clirIndicator == 0) or (clirIndicator == 1))
          {
              asnTreeAddInteger("IFW_TAP3.ClirIndicator.CLIR_INDICATOR", clirIndicator);
          }

	  asnTreePop(); //asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
	}

    // change start - Added call to addChargeInformationForSS
    //addChargeInformationForSS(currentSSidx);
    // change end - Added call to addChargeInformationForSS

///////////////////////BasicServiceCodeList begin///////////////////////////

         if ( edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.BASIC_SERVICE_CODE_LIST, 0, currentSSidx) != "")
         {
             asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
             String ListArray[]; 
             String ListString = 
                 edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.BASIC_SERVICE_CODE_LIST, 0, currentSSidx);

             String tmpServiceCode;

             Long nbElem = strSplit( ListArray, ListString, "," ); 
             Long i;
             for (i=0 ; i<nbElem ; i=i+1) 
             {
                 //Need to check whether the type of service is bearer service or tele service. 
                 if ( strStartsWith(ListArray[i],"0") ) //prefix is digit "0"
                 {
                     tmpServiceCode = strSubstr(ListArray[i], 1, (strLength(ListArray[i])-1) )    ;
                     asnTreeAddString("IFW_TAP3.TeleServiceCode.TELE_SERVICE_CODE", tmpServiceCode );
                 }
                 else //prefix is digit "1"
                 {
                     tmpServiceCode = strSubstr(ListArray[i], 1, (strLength(ListArray[i])-1) )    ;
                     asnTreeAddString("IFW_TAP3.BearerServiceCode.BEARER_SERVICE_CODE", tmpServiceCode );
                 }
             }
             asnTreePop(); //asnTreePushTag("IFW_TAP3.BasicServiceCodeList");
         }

///////////////////////BasicServiceCodeList end///////////////////////////
	asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsed");
      }
      asnTreePop(); //asnTreePushTag("IFW_TAP3.SupplServiceUsedList");
    }

    // IFW_TAP3.CamelServiceUsed
    //============================
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      currentCPidx = addCamelServiceUsed(currentCPidx, CPcount);
    }

    // IFW_TAP3.ValueAddedServiceUsedList
    //============================
    if (vasServiceDetected == true)
    {
      asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");

      // change start - Added call to ASSOCIATED_VAS_EXTENSION function

      addValueAddedServiceUsedList(currentCPidx, CPcount);

      // change end - Added call to ASSOCIATED_VAS_EXTENSION function

      asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedServiceUsedList");
    }

    // DualServiceRequested
    if(edrString(DETAIL.ASS_GSMW_EXT.BASIC_DUAL_SERVICE,0) != "")
        addDualServiceRequested();

    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.MobileTerminatedCall");
    return true;
  }

  function populateUMTSQosReqOrUsed ( String UMTSQosReqOrUsed)
  {
        String tmpUMTSQosReqOrUsedArray[];
        Long nbElem = strSplit(tmpUMTSQosReqOrUsedArray, UMTSQosReqOrUsed, ",");
        Long i;
  
        for (i = 0; i < nbElem; i = i+2) //Every even index will contain key, so we jump 2 (i = i+2)
        {
            switch(strToLong(tmpUMTSQosReqOrUsedArray[i]))
            {
               //These case values are defined as follwos in the input grammar
               //  const String QosTrafficClassKey                     = "1";
               //  const String QosMaxBitRateUpLnKey                   = "2";
               //  const String QosMaxBitRateDownLnKey                 = "3";
               //  const String QosGuaranteedBitRateDownLnKey          = "4";
               //  const String QosGuaranteedBitRateUpLnKey            = "5";
               //  const String QosAllocRetenPriorityKey               = "6";
  
               case 1: // This is QosTrafficClassKey
                   asnTreeAddInteger("IFW_TAP3.QoSTrafficClass.QOS_INTEGER", strToLong(tmpUMTSQosReqOrUsedArray[i+1]));
               break;
               case 2: // This is QosMaxBitRateUpLnKey
                   asnTreeAddString("IFW_TAP3.QoSMaxBitRateUplink.QOS_BYTE", tmpUMTSQosReqOrUsedArray[i+1]);
               break;
               case 3: // This is QosMaxBitRateDownLnKey
                   asnTreeAddString("IFW_TAP3.QoSMaxBitRateDownlink.QOS_BYTE", tmpUMTSQosReqOrUsedArray[i+1]);
               break;
               case 4: // This is QosGuaranteedBitRateDownLnKey
                    asnTreeAddString("IFW_TAP3.QoSGuaranteedBitRateDownlink.QOS_BYTE", tmpUMTSQosReqOrUsedArray[i+1]);
               break;
               case 5: // This is QosGuaranteedBitRateDownLnKey
                   asnTreeAddString("IFW_TAP3.QoSGuaranteedBitRateUplink.QOS_BYTE", tmpUMTSQosReqOrUsedArray[i+1]);
               break;
               case 6: // This is QosAllocRetenPriorityKey
                   asnTreeAddInteger("IFW_TAP3.QoSAllocRetenPriority.QOS_INTEGER", strToLong(tmpUMTSQosReqOrUsedArray[i+1]));
               break;
           }
            
       }
  }

  // changes start - Added function for GPRS_SERVICE_USAGE_PACKET
  function Bool addGprsServiceUsage
  {
    Long idx = 0;
    Long count = 0;
    Long i = 0;

    count = edrNumDatablocks( DETAIL.ASS_GPRS_EXT.GS_PACKET, 0 );

    for (idx = 0; count > idx; idx = idx + 1)
    {
      asnTreePushTag("IFW_TAP3.GprsServiceUsage");

      asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
      addDateTime(dateToStr(edrDate(DETAIL.ASS_GPRS_EXT.GS_PACKET.CHARGING_START_TIMESTAMP, 0, idx)), edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UTC_TIME_OFFSET, 0, idx));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");

      // GSMQoSRequested is optional and contains all mandatory fields.
      // So presence of one implies presence of GSMQoSRequested
      if (edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_DELAY, 0, idx) != "")
      {
        asnTreePushTag("IFW_TAP3.GSMQoSRequested");
        asnTreeAddInteger("IFW_TAP3.QoSDelay.QOS_INTEGER", 		   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_DELAY, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSMeanThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_MEAN_THROUGHPUT, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSPeakThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_PEAK_THROUGHPUT, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSPrecedence.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_PRECEDENCE, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSReliability.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_RELIABILITY, 0, idx)));
        asnTreePop(); //asnTreePushTag("IFW_TAP3.GSMQoSRequested");  
      }
      if (edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_DELAY, 0, idx) != "")
      {
        asnTreePushTag("IFW_TAP3.GSMQoSUsed");
        asnTreeAddInteger("IFW_TAP3.QoSDelay.QOS_INTEGER", 		   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_DELAY, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSMeanThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_MEAN_THROUGHPUT, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSPeakThroughput.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_PEAK_THROUGHPUT, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSPrecedence.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_PRECEDENCE, 0, idx)));
        asnTreeAddInteger("IFW_TAP3.QoSReliability.QOS_INTEGER",	   strToLong(edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_RELIABILITY, 0, idx)));
        asnTreePop(); //asnTreePushTag("IFW_TAP3.GSMQoSUsed");
      }

      // QualityOfServiceRequested can contain UMTSQualityOfServiceRequested or GSMQualityOfServiceRequested. The checking for this
      // would be decided based on whether the EDR field DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_REQUESTED_DELAY is populated or
      // the EDR field DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_REQUESTED is present. At any time in the EDR only one of these two 
      // fields should be present.
  
      if ( edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_REQUESTED,0,idx) != "")
      {
          asnTreePushTag("IFW_TAP3.UMTSQoSRequested");

          // Decode the comma separated values of UMTS_QOS_REQUESTED field of EDR.
          String tmpUMTSQosRequested = edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_REQUESTED,0,idx);
          
          populateUMTSQosReqOrUsed(tmpUMTSQosRequested);

          asnTreePop(); //asnTreePushTag("IFW_TAP3.UMTSQoSRequested");
         
      }

      // QualityOfServiceUsed can contain UMTSQualityOfServiceUsed or GSMQualityOfServiceUsed. The checking for this
      // would be decided based on whether the EDR field DETAIL.ASS_GPRS_EXT.GS_PACKET.QOS_USED_DELAY is populated or
      // the EDR field DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_USED is present. At any time in the EDR only one of these two 
      // fields should be present.

      if ( edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_USED,0,idx) != "")
      {
          asnTreePushTag("IFW_TAP3.UMTSQoSUsed");

          // Decode the comma separated values of UMTS_QOS_USED field of EDR.
          String tmpUMTSQosUsed = edrString(DETAIL.ASS_GPRS_EXT.GS_PACKET.UMTS_QOS_USED,0,idx);
          
          populateUMTSQosReqOrUsed(tmpUMTSQosUsed);

          asnTreePop(); //asnTreePushTag("IFW_TAP3.UMTSQoSUsed");
         
      }

      asnTreeAddInteger("IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING", decimalToLong(edrDecimal(DETAIL.ASS_GPRS_EXT.GS_PACKET.VOLUME_RECEIVED, 0, idx)));
      asnTreeAddInteger("IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING", decimalToLong(edrDecimal(DETAIL.ASS_GPRS_EXT.GS_PACKET.VOLUME_SENT, 0, idx)));

      asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsServiceUsage");
    }
    return true;
  }
  // changes end - Added function for GPRS_SERVICE_USAGE_PACKET


  function Bool processGPRS
  {
    asnTreePushTag("IFW_TAP3.GprsCall");
    lastDetailIdx = asnTreeStoreNode();
    
    asnTreeAddInteger("IFW_TAP3.TypeOfControllingNode.TYPE_OF_CONTROLLING_NODE", 
                                edrLong(DETAIL.ASS_GPRS_EXT.TYPE_OF_CONTROLLING_NODE,0)); 

    // IFW_TAP3.GprsBasicCallInformation
    //============================
    asnTreePushTag("IFW_TAP3.GprsBasicCallInformation");

    if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
    {
      asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
    }

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

    if ( edrString(DETAIL.USAGE_CLASS) != "")
        asnTreeAddString("IFW_TAP3.ChargingCharacteristics.CHARGING_CHARACTERISTICS", edrString(DETAIL.USAGE_CLASS));
        
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsChargeableSubscriber");

    if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
    {
      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
    }

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
                       strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), 0, (sepIndex) ) );
      asnTreeAddString("IFW_TAP3.AccessPointNameOI.ACCESS_POINT_NAME_OI",
                       strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), (sepIndex+2), 
		                 strLength(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)) - (sepIndex+2) ) );
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

    String tmpLongDurationIndicator = edrString(DETAIL.LONG_DURATION_INDICATOR);
    if (tmpLongDurationIndicator != "S")
    {
      asnTreeAddString("IFW_TAP3.PartialTypeIndicator.PARTIAL_TYPE_INDICATOR", tmpLongDurationIndicator);
    }

    // Populate PDPContextStartTimestamp if the partial call is of type Last or Intermediate.
    if ((tmpLongDurationIndicator == "I") or (tmpLongDurationIndicator == "L"))
    {
        String tmpContextStrtTime = dateToStr(edrDate(DETAIL.ASS_GPRS_EXT.PDP_CONTEXT_START_TIMESTAMP,0));
        if ( tmpContextStrtTime != "" )
        {
            asnTreePushTag("IFW_TAP3.PDPContextStartTimestamp");    
            addDateTime(tmpContextStrtTime, edrString(DETAIL.ASS_GPRS_EXT.PDP_UTC_TIME_OFFSET,0));
            asnTreePop(); //asnTreePushTag("IFW_TAP3.PDPContextStartTimestamp");
        }
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

    // changes start - Added call to addGprsServiceUsage

    addGprsServiceUsage();

    // changes end - Added call to addGprsServiceUsage

    asnTreePop(); //asnTreePushTag("IFW_TAP3.GprsServiceUsageList");

    // Populate ChargingTimestamp 
    String tmpChargingTimestamp = dateToStr(edrDate(DETAIL.ASS_GPRS_EXT.SERVICE_USED_CHARGING_START_TIMESTAMP,0));
    if ( tmpChargingTimestamp != "" )
    {
        asnTreePushTag("IFW_TAP3.ChargingTimeStamp");    
        addDateTime(tmpChargingTimestamp, edrString(DETAIL.ASS_GPRS_EXT.SERVICE_USED_UTC_TIME_OFFSET,0));
        asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
    }

    asnTreePushTag("IFW_TAP3.ChargeInformationList");
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if (CPcount > 0)
    {
      // change start - get the record number
      Long 	recordNum		= edrLong(DETAIL.ASS_GPRS_EXT.RECORD_NUMBER, 0);
      // change end - get the record number

      while ( (camelServiceDetected == false) and (vasServiceDetected == false) and (currentCPidx < CPcount) )
      {
        // change start - get the related record number and compare
        Long relatedRecordNum = edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, 0, currentCPidx);
        if (relatedRecordNum == recordNum)
        {
        // change end - get the related record number and compare
        currentCPidx = addChargeInformation(currentCPidx, CPcount, 0, relatedRecordNum);
        // change start - Added
        }
        else
        {
          currentCPidx = currentCPidx + 1;
        }
        // change end - Added
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

      // change start - Added call to addValueAddedServiceUsedList

      addValueAddedServiceUsedList(currentCPidx, CPcount);

      // change end - Added call to addValueAddedServiceUsedList

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
    if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
    {
      asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
    }

    asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");
    asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.SimChargeableSubscriber");

    if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
    {
      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
    }

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

      // CLIR Indicator
      Long clirIndicator = edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.CLIR_INDICATOR, 0, 0);
      if ( (clirIndicator == 0) or (clirIndicator == 1))
      {
          asnTreeAddInteger("IFW_TAP3.ClirIndicator.CLIR_INDICATOR", clirIndicator);
      }

      asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.C_NUMBER));
      asnTreePop(); //asnTreePushTag("IFW_TAP3.ThirdPartyInformation");
    }
    asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ChargingTimeStamp");

      // IFW_TAP3.ChargeInformation
      //============================
      Long currentCPidx	= 0;  //start from the beginning (first CP)
      Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
      if (CPcount > 0)
      {
        Long recordNumSS = edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.RECORD_NUMBER, 0, 0);
        currentCPidx = addChargeInformation(currentCPidx, CPcount, 0, recordNumSS);  //start from the beginning (first CP), and add ONLY 1 ChargeInformation block
        if (currentCPidx != CPcount)
        {
          // ERROR we shoould be able to store all ChargePackets on one ChargeInformation
	  logFormat("ERROR: processMSS(), currentCPidx="+longToStr(currentCPidx)+" < CPcount="+longToStr(CPcount)+" \n");
	  return false;
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
    
    // Populate SIM Toolkit Indicator
    if (edrString(DETAIL.DISCOUNT_KEY) != "")
        asnTreeAddString("IFW_TAP3.SimToolkitIndicator.SIM_TOOLKIT_INDICATOR", edrString(DETAIL.DISCOUNT_KEY));

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
    
    if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
    {
      asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
    }

    // IFW_TAP3.ScuBasicInformation
    //============================
    asnTreePushTag("IFW_TAP3.ScuBasicInformation");
    asnTreePushTag("IFW_TAP3.GsmChargeableSubscriber");
    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    }
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GsmChargeableSubscriber");
    asnTreeAddInteger("IFW_TAP3.ChargedPartyStatus.CHARGED_PARTY_STATUS", edrLong(DETAIL.USAGE_DIRECTION) );
    asnTreePushTag("IFW_TAP3.NonChargedParty");
    asnTreeAddString("IFW_TAP3.AddressStringDigits.ADDRESS_STRING_DIGITS", edrString(DETAIL.B_NUMBER));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.NonChargedParty");

    if (edrString(DETAIL.USAGE_CLASS) != "")
        asnTreeAddString("IFW_TAP3.ClirIndicator.CLIR_INDICATOR", edrString(DETAIL.USAGE_CLASS));
        
    asnTreeAddString("IFW_TAP3.OriginatingNetwork.NETWORK_ID", edrString(DETAIL.SOURCE_NETWORK));
    asnTreeAddString("IFW_TAP3.DestinationNetwork.NETWORK_ID", edrString(DETAIL.DESTINATION_NETWORK));
    asnTreePop(); //asnTreePushTag("IFW_TAP3.ScuBasicInformation");

    if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
    {
      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
    }

    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }

    String tmpServingNetwork = edrString(DETAIL.ASS_GSMW_EXT.SERVING_NETWORK,0);

    if ( (tmpServingNetwork != "") and (tmpServingNetwork != edrString(HEADER.SENDER)) )
        asnTreeAddString("IFW_TAP3.ServingNetwork.SERVING_NETWORK", tmpServingNetwork);
        
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE",
    		      getRecEntityIdCode(edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0),recEntityType_SMSC));

    // IFW_TAP3.ChargeInformation
    //============================
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    Long recordNumSCU = edrLong(DETAIL.ASS_GSMW_EXT.RECORD_NUMBER,0);
    if (CPcount > 0)
    {
	      currentCPidx = addChargeInformation(currentCPidx, CPcount, 0, recordNumSCU);  //start from the beginning (first CP), and add ONLY 1 ChargeInformation block
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

    if ( edrString(DETAIL.ZONE_DESCRIPTION) != "")
        asnTreeAddString("IFW_TAP3.DistanceChargeBandCode.DISTANCE_CHARGE_BAND_CODE", edrString(DETAIL.ZONE_DESCRIPTION));
        
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

    if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
    {
      asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
    }

    asnTreePushTag("IFW_TAP3.GsmChargeableSubscriber");
    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreeAddString("IFW_TAP3.Imsi.IMSI", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    }
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("IFW_TAP3.Msisdn.MSISDN", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("IFW_TAP3.GsmChargeableSubscriber");

    if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
    {
      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
    }

    if (theNetworkType == 0) //ie mixed
    {
      asnTreeAddInteger("IFW_TAP3.NetworkType.NETWORK_TYPE", strToLong(edrString(DETAIL.SOURCE_NETWORK_TYPE)));
    }

    if ( edrString(DETAIL.ASS_GSMW_EXT.SERVING_NETWORK,0) != "")
        asnTreeAddString("IFW_TAP3.ServingNetwork.SERVING_NETWORK", edrString(DETAIL.ASS_GSMW_EXT.SERVING_NETWORK,0));
    
    // IFW_TAP3.ValueAddedServiceUsed
    //============================

    // change start - Added call to addValueAddedServiceUsedList

      Long currentCPidx	= 0;  //start from the beginning (first CP)
      Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
      addValueAddedServiceUsedList(currentCPidx, CPcount);

    // change end - Added call to addValueAddedServiceUsedList
    
    // IFW_TAP3.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("IFW_TAP3.ValueAddedService");
    return true;
  }

  // changes start - Added functions addNetworkList, addAdvisedChargeInformation
  // Note: If the field is optional then only its existence is checked for it.

  function Bool addNetworkList  // This is common to ServingPartiesInformation and LCSSPInformation
  {
      Long idx = 0;
      Long nlCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST, 0, 0);
      if ( nlCount > 0 )
      {
        asnTreePushTag("IFW_TAP3.NetworkList");
        for (idx = 0; nlCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.Network");
          asnTreeAddInteger("IFW_TAP3.NetworkIdType.NETWORK_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.NetworkIdentifier.NETWORK_ID", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("IFW_TAP3.Network");
        }
        asnTreePop(); // asnTreePushTag("IFW_TAP3.NetworkList");
      }
      return true;
  }


  function Bool addAdvisedChargeInformation(Long idx)
  {
      // Note: AdvisedChargeInformation tag - This is optional. All the fields in containerDesc.dsc are moved up by one level.
      //       So, there is no check for block over here. In case first field is found the tag would be created.
      
      Bool a = false;
      Bool b = false;
      Bool c = false;
      Bool d = false;
      Bool e = false;

      a = (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAID_INDICATOR, 0, idx) != 0);
      b = (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAYMENT_METHOD, 0, idx) != 0);
      c = (edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE_CURRENCY, 0, idx) != "");
      d = (decimalToLong(edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0, idx)) != 0);
      e = (decimalToLong(edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0, idx)) != 0);

      String localAdvisedChargeCurrency;

      if (a or b or c or d or e)
      {
        advisedChargeDetectedFlag = true;
        asnTreePushTag("IFW_TAP3.AdvisedChargeInformation");

        if ( a )
        {
          asnTreeAddInteger("IFW_TAP3.PaidIndicator.PAID_INDICATOR", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAID_INDICATOR, 0, idx) );
        }
        if ( b )
        {
          asnTreeAddInteger("IFW_TAP3.PaymentMethod.PAYMENT_METHOD", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAYMENT_METHOD, 0, idx) );
        }
        if ( c )
        {
          localAdvisedChargeCurrency = edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE_CURRENCY, 0, idx);
          asnTreeAddString("IFW_TAP3.AdvisedChargeCurrency.ADVISED_CHARGE_CURRENCY", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE_CURRENCY, 0, idx) );
        }
        if ( d )
        {
          asnTreeAddInteger("IFW_TAP3.AdvisedCharge.ADVISED_CHARGE", decimalToLong(edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0, idx)));
        }
        if ( e )
        {
          asnTreeAddInteger("IFW_TAP3.Commission.COMMISSION", decimalToLong(edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0, idx)));
        }
///////////////Update TotalAdvisedChargevalue for Audit control Information////////////////
    Long i;
    Bool notUpdated = false;
      for (i=0 ; (i<totalAdvisedChargeCurrencyEntries) and (notUpdated == false); i=i+1)
      {
        if (advisedChargeCurrency[i] == localAdvisedChargeCurrency)
        {
          if ( chargeRefundFlag == true)
          {
              totalAdvisedChargeRefund[i] = totalAdvisedChargeRefund[i] + edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0, idx);
              totalCommissionRefund[i] = totalCommissionRefund[i] + edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0, idx);
          }
          else
          {
              totalAdvisedCharge[i] = totalAdvisedCharge[i] + edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0, idx);
              totalCommission[i] = totalCommission[i] + edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0, idx);
          }
          notUpdated = true;
        }
      }

      if( notUpdated == false )
      {
        // if we get here, the type is not yet used.
        advisedChargeCurrency[totalAdvisedChargeCurrencyEntries] = localAdvisedChargeCurrency;

          if ( chargeRefundFlag == true)
          {
              totalAdvisedChargeRefund[totalAdvisedChargeCurrencyEntries] = 
                        totalAdvisedChargeRefund[totalAdvisedChargeCurrencyEntries] + 
                        edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0, idx);

              totalCommissionRefund[totalAdvisedChargeCurrencyEntries] = 
                        totalCommissionRefund[totalAdvisedChargeCurrencyEntries] + 
                        edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0, idx);
          }
          else
          {
              totalAdvisedCharge[totalAdvisedChargeCurrencyEntries] = 
                        totalAdvisedCharge[totalAdvisedChargeCurrencyEntries] + 
                        edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0, idx);

              totalCommission[totalAdvisedChargeCurrencyEntries] = 
                        totalCommission[totalAdvisedChargeCurrencyEntries] + 
                        edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0, idx);
          }

        totalAdvisedChargeCurrencyEntries = totalAdvisedChargeCurrencyEntries + 1;
      }
///////////////////////////////////////////////////////////////////////////////////////////
        asnTreePop(); // asnTreePushTag("IFW_TAP3.AdvisedChargeInformation");
      }
      return true;
  }


  function Bool processCONT // Supported since Apollo.1
  {
    asnTreePushTag("IFW_TAP3.ContentTransaction");
    lastDetailIdx = asnTreeStoreNode();

    Long idx = 0; // index used inside for loop

    // IFW_TAP3.contentTransactionBasicInfo
    //================================================

    asnTreePushTag("IFW_TAP3.ContentTransactionBasicInfo");

      if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
      {
        asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
      }
      if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
      {
        asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
      }
      if (dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ORDER_PLACED_TIMESTAMP, 0)) != "")
      {
        asnTreePushTag("IFW_TAP3.OrderPlacedTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ORDER_PLACED_TIMESTAMP, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop();  // asnTreePushTag("IFW_TAP3.OrderPlacedTimeStamp");
      }
      if (dateToStr(edrDate(DETAIL.ASS_CONT_EXT.REQUESTED_DELIVERY_TIMESTAMP, 0)) != "")
      {
        asnTreePushTag("IFW_TAP3.RequestedDeliveryTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CONT_EXT.REQUESTED_DELIVERY_TIMESTAMP, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop();  // asnTreePushTag("IFW_TAP3.RequestedDeliveryTimeStamp");
      }
      if (dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ACTUAL_DELIVERY_TIMESTAMP, 0)) != "")
      {
        asnTreePushTag("IFW_TAP3.ActualDeliveryTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ACTUAL_DELIVERY_TIMESTAMP, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop();  // asnTreePushTag("IFW_TAP3.ActualDeliveryTimeStamp");
      }
      if (edrLong(DETAIL.ASS_CONT_EXT.TOTAL_TRANSACTION_DURATION, 0) != 0)
      {
        asnTreeAddInteger("IFW_TAP3.TotalCallEventDuration.TOTAL_CALL_EVENT_DURATION", edrLong(DETAIL.ASS_CONT_EXT.TOTAL_TRANSACTION_DURATION, 0) );
      }
      if (edrLong(DETAIL.ASS_CONT_EXT.TRANSACTION_STATUS, 0) != 0)
      {
        asnTreeAddInteger("IFW_TAP3.TransactionStatus.TRANSACTION_STATUS", edrLong(DETAIL.ASS_CONT_EXT.TRANSACTION_STATUS, 0) );
      }
    
    asnTreePop();	// 1. asnTreePushTag("IFW_TAP3.contentTransactionBasicInfo")

    // IFW_TAP3.chargedPartyInformation
    //================================================

    asnTreePushTag("IFW_TAP3.ChargedPartyInformation");

      Long IDcount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST, 0, 0); // edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST, 0);
      if ( IDcount > 0 )
      {
        asnTreePushTag("IFW_TAP3.ChargedPartyIdList");
        for (idx = 0; IDcount > idx; idx = idx + 1)
        {
          asnTreePushTag("IFW_TAP3.ChargedPartyIdentification");
          asnTreeAddInteger("IFW_TAP3.ChargedPartyIdType.CHARGED_PARTY_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.ChargedPartyIdentifier.CHARGED_PARTY_IDENTIFIER", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargedPartyIdentification");
        }
        asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargedPartyIdList");
      }

      Long homeIDCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST, 0, 0);
      if ( homeIDCount > 0 )
      {
        asnTreePushTag("IFW_TAP3.ChargedPartyHomeIdList");
        for (idx = 0; homeIDCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.ChargedPartyHomeIdentification");
          asnTreeAddInteger("IFW_TAP3.HomeIdType.HOME_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.HomeIdentifier.HOME_IDENTIFIER", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargedPartyHomeIdentification");
        }
        asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargedPartyHomeIdList");
      }

      Long locationCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST, 0, 0);
      if ( locationCount > 0 )
      {
        asnTreePushTag("IFW_TAP3.ChargedPartyLocationList");
        for (idx = 0; locationCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.ChargedPartyLocation");
          asnTreeAddInteger("IFW_TAP3.LocationIdType.LOCATION_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.LocationIdentifier.LOCATION_IDENTIFIER", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargedPartyLocation");
        }
        asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargedPartyLocationList");
      }

      if (edrNumDatablocks(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT, 0, 0) > 0)
      {
          asnTreePushTag("IFW_TAP3.ChargedPartyEquipment");
          asnTreeAddInteger("IFW_TAP3.EquipmentIdType.EQUIPMENT_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.TYPE, 0, 0, 0) );
          asnTreeAddString("IFW_TAP3.EquipmentId.EQUIPMENT_ID", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.IDENTIFIER, 0, 0, 0) );
          asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargedPartyLocation");
      }

    asnTreePop();	// 2. asnTreePushTag("IFW_TAP3.chargedPartyInformation")


    // IFW_TAP3.servingPartiesInformation
    //================================================
    
    Long spiCount = 0;

    asnTreePushTag("IFW_TAP3.ServingPartiesInformation");

      asnTreeAddString("IFW_TAP3.ContentProviderName.CONTENT_PROVIDER_NAME", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_NAME, 0, 0));

      spiCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST, 0, 0);
      if ( spiCount > 0 )
      {
        asnTreePushTag("IFW_TAP3.ContentProviderIdList");
        for (idx = 0; spiCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.ContentProvider");
          asnTreeAddInteger("IFW_TAP3.ContentProviderIdType.CONTENT_PROVIDER_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.ContentProviderIdentifier.CONTENT_PROVIDER_IDENTIFIER", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("IFW_TAP3.ContentProvider");
        }
        asnTreePop(); // asnTreePushTag("IFW_TAP3.ContentProviderIdList");
      }
      spiCount = 0;
  
      spiCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST, 0, 0);
      if ( spiCount > 0 )
      {
        asnTreePushTag("IFW_TAP3.InternetServiceProviderIdList");
        for (idx = 0; spiCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.InternetServiceProvider");
          asnTreeAddInteger("IFW_TAP3.IspIdType.ISP_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.IspIdentifier.ISP_IDENTIFIER", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("IFW_TAP3.InternetServiceProvider");
        }
        asnTreePop(); // asnTreePushTag("IFW_TAP3.InternetServiceProviderIdList");
      }
      spiCount = 0;

      addNetworkList();

    asnTreePop();	// 3. asnTreePushTag("IFW_TAP3.servingPartiesInformation")


    // IFW_TAP3.contentServiceUsedList
    //================================================
    
    Long csulCount = 0;
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);

      csulCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST, 0);

      asnTreePushTag("IFW_TAP3.ContentServiceUsedList");    // As it is mandatory count > 0 is not checked!
      for (idx = 0; csulCount > idx; idx = idx + 1)
      {       
        asnTreePushTag("IFW_TAP3.ContentServiceUsed");
        asnTreeAddInteger("IFW_TAP3.ContentTransactionCode.CONT_CODE", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_CODE, 0, idx) );
        asnTreeAddInteger("IFW_TAP3.ContentTransactionType.CONT_TYPE", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_TYPE, 0, idx) );
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.OBJECT_TYPE, 0, idx) != 0)
        {
          asnTreeAddInteger("IFW_TAP3.ObjectType.OBJECT_TYPE", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.OBJECT_TYPE, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DESCRIPTION_SUPP, 0, idx) != 0)
        {
          asnTreeAddInteger("IFW_TAP3.TransactionDescriptionSupp.TRANS_DESCR_SUPP", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DESCRIPTION_SUPP, 0, idx) );
        }
        asnTreeAddString("IFW_TAP3.TransactionShortDescription.TRANS_SHORT_DESCR", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_SHORT_DESCRIPTION, 0, idx) );
        if (edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DETAIL_DESCRIPTION, 0, idx) != "")
        {
          asnTreeAddString("IFW_TAP3.TransactionDetailDescription.TRANS_DETAIL_DESCR", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DETAIL_DESCRIPTION, 0, idx) );
        }
        if (edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_IDENTIFIER, 0, idx) != "")
        {
          asnTreeAddString("IFW_TAP3.TransactionIdentifier.TRANS_IDENTIFIER", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_IDENTIFIER, 0, idx) );
        }
        if (edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_AUTH_CODE, 0, idx) != "")
        {
          asnTreeAddString("IFW_TAP3.TransactionAuthCode.TRANS_AUTH_CODE", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_AUTH_CODE, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_INCOMING, 0, idx) != 0)
        {
          asnTreeAddInteger("IFW_TAP3.DataVolumeIncoming.DATA_VOLUME_INCOMING", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_INCOMING, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_OUTGOING, 0, idx) != 0)
        {
          asnTreeAddInteger("IFW_TAP3.DataVolumeOutgoing.DATA_VOLUME_OUTGOING", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_OUTGOING, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TOTAL_DATA_VOLUME, 0, idx) != 0)
        {
          asnTreeAddInteger("IFW_TAP3.TotalDataVolume.TOTAL_DATA_VOLUME", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TOTAL_DATA_VOLUME, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CHARGE_REFUND_INDICATOR, 0, idx) != 0)
        {
          chargeRefundFlag = true;
          asnTreeAddInteger("IFW_TAP3.ChargeRefundIndicator.CHARGE_REFUND_INDICATOR", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CHARGE_REFUND_INDICATOR, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_CHARGING_POINT, 0, idx) != 0)
        {
          asnTreeAddInteger("IFW_TAP3.ContentChargingPoint.CONTENT_CHARGING_POINT", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_CHARGING_POINT, 0, idx) );
        }

        asnTreePushTag("IFW_TAP3.ChargeInformationList");
        currentCPidx = 0;
        if (CPcount > 0)
        {
          Long 	recordNum		= edrLong(DETAIL.ASS_CONT_EXT.RECORD_NUMBER, idx);
          while ((camelServiceDetected == false) and (vasServiceDetected == false) and (currentCPidx < CPcount))
          {
            Long relatedRecordNum = edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, 0, currentCPidx);

            // if detail record number and CP related record number match then add this charge info.
            if (recordNum == relatedRecordNum)
            {
              currentCPidx = addChargeInformation(currentCPidx, CPcount, 0, relatedRecordNum);
            }
            else
            {
              currentCPidx = currentCPidx + 1;
            }
          }
        }
        else
        {
          addDefaultChargeInformation();
        }
        asnTreePop(); //    asnTreePushTag("IFW_TAP3.ChargeInformationList");

        addAdvisedChargeInformation(idx);

        asnTreePop(); // asnTreePushTag("IFW_TAP3.contentServiceUsed");
      }

    asnTreePop();	// 4. asnTreePushTag("IFW_TAP3. contentServiceUsedList")


    // IFW_TAP3.operatorSpecInformation
    //================================================
    
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));
   

    asnTreePop();	// asnTreePushTag("IFW_TAP3.ContentTransaction");

    return true;
  }


  function Bool addTrackingCustomerInformation
  {
    Long count = 0;
    Long idx = 0;

    if (edrNumDatablocks(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO, 0) > 0)
    {
      asnTreePushTag("IFW_TAP3.TrackingCustomerInformation");

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST, 0, 0);

      asnTreePushTag("IFW_TAP3.TrackingCustomerIdList");

      for (idx = 0; count > idx; idx = idx + 1)
      {       
        asnTreePushTag("IFW_TAP3.TrackingCustomerIdentification");
        asnTreeAddInteger("IFW_TAP3.CustomerIdType.CUSTOMER_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.TYPE, 0, 0, idx) );
        asnTreeAddString("IFW_TAP3.CustomerIdentifier.CUSTOMER_IDENTIFIER", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackingCustomerIdentification")
      }

      asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackingCustomerIdList")
      count = 0;

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("IFW_TAP3.TrackingCustomerHomeIdList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.TrackingCustomerHomeId");
          asnTreeAddInteger("IFW_TAP3.HomeIdType.HOME_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.HomeIdentifier.HOME_IDENTIFIER", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackingCustomerHomeId")
        }

        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackingCustomerHomeIdList")
      }
      count = 0;

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("IFW_TAP3.TrackingCustomerLocList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.TrackingCustomerLocation");
          asnTreeAddInteger("IFW_TAP3.LocationIdType.LOCATION_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.LocationIdentifier.LOCATION_IDENTIFIER", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackingCustomerLocation")
        }

        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackingCustomerLocList")
      }
      count = 0;

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("IFW_TAP3.TrackingCustomerEquipment");

        asnTreeAddInteger("IFW_TAP3.EquipmentIdType.EQUIPMENT_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.TYPE, 0, 0, 0) );
        asnTreeAddString("IFW_TAP3.EquipmentId.EQUIPMENT_ID", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.IDENTIFIER, 0, 0, 0) );

        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackingCustomerEquipment")
      }


      asnTreePop();  // asnTreePushTag("IFW_TAP3.TrackingCustomerInformation")
    }

    return true;
  }


  function Bool addLCSSPInformation
  {
    Long count = 0;
    Long idx = 0;

    if (edrNumDatablocks(DETAIL.ASS_LOCN_EXT.LCSSP_INFO, 0) > 0)
    {
      asnTreePushTag("IFW_TAP3.LCSSPInformation");

      count = edrNumDatablocks(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST, 0, 0);

      asnTreePushTag("IFW_TAP3.LCSSPIdentificationList");

      for (idx = 0; count > idx; idx = idx + 1)
      {       
        asnTreePushTag("IFW_TAP3.LCSSPIdentification");
        if (edrLong(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.TYPE, 0, 0, idx) != 0)
        {
          asnTreeAddInteger("IFW_TAP3.ContentProviderIdType.CONTENT_PROVIDER_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.TYPE, 0, 0, idx) );
        }
        asnTreeAddString("IFW_TAP3.ContentProviderIdentifier.CONTENT_PROVIDER_IDENTIFIER", edrString(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
        asnTreePop(); //  asnTreePushTag("IFW_TAP3.LCSSPIdentification")
      }
      asnTreePop(); //  asnTreePushTag("IFW_TAP3.LCSSPIdentificationList")
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("IFW_TAP3.ISPList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.InternetServiceProvider");
          asnTreeAddInteger("IFW_TAP3.IspIdType.ISP_ID_TYPE", edrLong(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.IspIdentifier.ISP_IDENTIFIER", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("IFW_TAP3.InternetServiceProvider")
        }

        asnTreePop(); //  asnTreePushTag("IFW_TAP3.ISPList")
      }
      count = 0;


      addNetworkList();

    
      asnTreePop(); //  asnTreePushTag("IFW_TAP3.LCSSPInformation")
    }

    return true;
  }


  function Bool addTrackedCustomerInformation
  {
    Long count = 0;
    Long idx = 0;

    if (edrNumDatablocks(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO, 0) > 0)
    {
      asnTreePushTag("IFW_TAP3.TrackedCustomerInformation");

      count = edrNumDatablocks(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST, 0, 0);

      asnTreePushTag("IFW_TAP3.TrackedCustomerIdList");

      for (idx = 0; count > idx; idx = idx + 1)
      {       
        asnTreePushTag("IFW_TAP3.TrackedCustomerIdentification");
        asnTreeAddInteger("IFW_TAP3.CustomerIdType.CUSTOMER_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.TYPE, 0, 0, idx) );
        asnTreeAddString("IFW_TAP3.CustomerIdentifier.CUSTOMER_IDENTIFIER", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerIdentification")
      }

      asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerIdList")
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("IFW_TAP3.TrackedCustomerHomeIdList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.TrackedCustomerHomeId");
          asnTreeAddInteger("IFW_TAP3.HomeIdType.HOME_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("IFW_TAP3.HomeIdentifier.HOME_IDENTIFIER", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerHomeId")
        }

        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerHomeIdList")
      }
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("IFW_TAP3.TrackedCustomerLocList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("IFW_TAP3.TrackedCustomerLocation");
          if (edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.TYPE, 0, 0, idx) != 0)
          {
            asnTreeAddInteger("IFW_TAP3.LocationIdType.LOCATION_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.TYPE, 0, 0, idx) );
          }
          asnTreeAddString("IFW_TAP3.LocationIdentifier.LOCATION_IDENTIFIER", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerLocation")
        }

        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerLocList")
      }
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("IFW_TAP3.TrackedCustomerEquipment");

        asnTreeAddInteger("IFW_TAP3.EquipmentIdType.EQUIPMENT_ID_TYPE", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.TYPE, 0, 0, idx) );
        asnTreeAddString("IFW_TAP3.EquipmentId.EQUIPMENT_ID", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.IDENTIFIER, 0, 0, idx) );

        asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerEquipment")
      }

    
      asnTreePop(); //  asnTreePushTag("IFW_TAP3.TrackedCustomerInformation")
    }

    return true;
  }


  function Bool addLocationServiceUsage
  {
    asnTreePushTag("IFW_TAP3.LocationServiceUsage");


    // IFW_TAP3.LCSQosRequested
    //=====================================

    asnTreePushTag("IFW_TAP3.LCSQosRequested");

    asnTreePushTag("IFW_TAP3.LCSRequestTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_REQUEST_TIMESTAMP, 0, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop();  // asnTreePushTag("IFW_TAP3.LCSRequestTimeStamp");

    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_REQUESTED, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.HorizontalAccuracyRequested.HORIZONTAL_ACCURACY_REQUESTED", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_REQUESTED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_REQUESTED, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.VerticalAccuracyRequested.VERTICAL_ACCURACY_REQUESTED", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_REQUESTED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME_CATEGORY, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.ResponseTimeCategory.RESPONSE_TIME_CATEGORY", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME_CATEGORY, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.TRACKING_PERIOD, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.TrackingPeriod.TRACKING_PERIOD", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.TRACKING_PERIOD, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.REQ_TRACKING_FREQUENCY, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.TrackingFrequency.TRACKING_FREQUENCY", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.REQ_TRACKING_FREQUENCY, 0, 0) );
    }

    asnTreePop(); // asnTreePushTag("IFW_TAP3.LCSQosRequested");


    // IFW_TAP3.LCSQosDelivered
    //======================================

    asnTreePushTag("IFW_TAP3.LCSQosDelivered");

    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_TRANS_STATUS, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.LCSTransactionStatus.LCS_TRANSACTION_STATUS", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_TRANS_STATUS, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_DELIVERED, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.HorizontalAccuracyDelivered.HORIZONTAL_ACCURACY_DELIVERED", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_DELIVERED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_DELIVERED, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.VerticalAccuracyDelivered.VERTICAL_ACCURACY_DELIVERED", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_DELIVERED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.ResponseTime.RESPONSE_TIME", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.POSITIONING_METHOD, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.PositioningMethod.POSITIONING_METHOD", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.POSITIONING_METHOD, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_PERIOD, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.TrackingPeriod.TRACKING_PERIOD", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_PERIOD, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_FREQUENCY, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.TrackingFrequency.TRACKING_FREQUENCY", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_FREQUENCY, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.AGE_OF_LOCATION, 0, 0) != 0)
    {
      asnTreeAddInteger("IFW_TAP3.AgeOfLocation.AGE_OF_LOCATION", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.AGE_OF_LOCATION, 0, 0) );
    }

    asnTreePop(); // asnTreePushTag("IFW_TAP3.LCSQosRequested");


    // IFW_TAP3.ChargingTimeStamp
    //======================================

    //if (dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)) != "")
    //{
     // asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
      //addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
//      asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargingTimeStamp");
//    }


    // IFW_TAP3.ChargeInformationList
    //======================================

    asnTreePushTag("IFW_TAP3.ChargeInformationList");

    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if (CPcount > 0)
    {
      Long 	recordNum		= edrLong(DETAIL.ASS_LOCN_EXT.RECORD_NUMBER, 0);
      while ((camelServiceDetected == false) and (vasServiceDetected == false) and (currentCPidx < CPcount))
      {
        Long relatedRecordNum = edrLong(DETAIL.ASS_CBD.CP.RELATED_RECORD_NUMBER, 0, currentCPidx);

        // if detail record number and CP related record number match then add this charge info.
        if (recordNum == relatedRecordNum)
        {
          currentCPidx = addChargeInformation(currentCPidx, CPcount, 0, relatedRecordNum);
        }
        else
        {
          currentCPidx = currentCPidx + 1;
        }
      }
    }
    else
    {
      addDefaultChargeInformation();
    }

    asnTreePop(); // asnTreePushTag("IFW_TAP3.ChargeInformationList");



    asnTreePop(); //  asnTreePushTag("IFW_TAP3.LocationServiceUsage")

    return true;
  }


  function Bool processLOCN // Supported since Apollo.1
  {
    asnTreePushTag("IFW_TAP3.LocationService");
    lastDetailIdx = asnTreeStoreNode();

    Long idx = 0; // index used inside for loop

    if (edrString(DETAIL.FRAUD_MONITOR_INDICATOR) != "")
    {
      asnTreeAddString("IFW_TAP3.FraudMonitorIndicator.FRAUD_MONITOR_INDICATOR", edrString(DETAIL.FRAUD_MONITOR_INDICATOR) );
    }
    if (edrString(DETAIL.RAP_FILE_SEQ_NO) != "")
    {
      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.RAP_FILE_SEQ_NO) );
    }
    asnTreeAddInteger("IFW_TAP3.RecEntityCode.REC_ENTITY_CODE", edrLong(DETAIL.ASS_LOCN_EXT.REC_ENTITY_CODE, 0));
    if (edrString(DETAIL.ASS_LOCN_EXT.CALL_REFERENCE, 0) != "")
    {
      asnTreeAddString("IFW_TAP3.CallReference.CALL_REFERENCE", edrString(DETAIL.ASS_LOCN_EXT.CALL_REFERENCE, 0));
    }


    // IFW_TAP3.TrackingCustomerInformation
    //================================================

    addTrackingCustomerInformation();

  
    // IFW_TAP3.lCSSPInformation
    //================================================

    addLCSSPInformation();

  
    // IFW_TAP3.TrackedCustomerInformation
    //================================================

    addTrackedCustomerInformation();

  
    // IFW_TAP3.LocationServiceUsage
    //================================================

    addLocationServiceUsage();

  
    // IFW_TAP3.operatorSpecInformation
    //================================================
    
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));
   

    asnTreePop();	// asnTreePushTag("IFW_TAP3.LocationService");

    return true;
  }

  // changes end - 
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

        if (edrString(HEADER.RAP_FILE_SEQ_NO) != "")
        {
          asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(HEADER.RAP_FILE_SEQ_NO) );
        }

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

        if (edrString(HEADER.RAP_FILE_SEQ_NO) != "")
        {
          asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(HEADER.RAP_FILE_SEQ_NO) );
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

	asnTreePushTag("IFW_TAP3.VasInfoList");
	theVasInfoListIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("IFW_TAP3.VasInfoList");

	asnTreePushTag("IFW_TAP3.MessageDescriptionInfoList");
	theMessageDescriptionIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("IFW_TAP3.MessageDescriptionInfoList");
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
  
  // changes start - Addition for TAP_TOTAL_CHARGE_VALUE_LIST

  Long idx = 0;
  for (idx = 0; totalChargeEntries > idx; idx = idx + 1)
  {       
    asnTreePushTag("IFW_TAP3.TotalChargeValue");
    asnTreeAddString("IFW_TAP3.ChargeType.CHARGE_TYPE", totalChargeType[idx]);
    asnTreeAddInteger("IFW_TAP3.AbsoluteAmount.ABSOLUTE_AMOUNT", decimalToLong(totalChargeValue[idx]));
    if ( totalChargeValueRefund[idx] > 0.0)
        asnTreeAddString("IFW_TAP3.TotalChargeRefund.TOTAL_CHARGE_REFUND", decimalToStrHex( trunc(totalChargeValueRefund[idx])));
        
    asnTreePop(); //asnTreePushTag("IFW_TAP3.TotalChargeValue");
  }

  // changes end - Addition for TAP_TOTAL_CHARGE_VALUE_LIST

	asnTreePop(); //asnTreePushTag("IFW_TAP3.TotalChargeValueList");

        if ( theTotalTaxValueRefund > 0.0 )
            asnTreeAddString("IFW_TAP3.TotalTaxRefund.TOTAL_TAX_REFUND", decimalToStrHex(trunc(theTotalTaxValueRefund)));//present only if >0

	asnTreeAddString("IFW_TAP3.TotalTaxValue.TOTAL_TAX_VALUE", decimalToStrHex( trunc(theTotalTaxValue)));
	asnTreeAddString("IFW_TAP3.TotalDiscountValue.TOTAL_DISCOUNT_VALUE",
			 decimalToStrHex( trunc(theTotalDiscountValue) ) );

        if ( theTotalDiscountRefund > 0.0 )
            asnTreeAddString("IFW_TAP3.TotalDiscountRefund.TOTAL_DISCOUNT_REFUND", decimalToStrHex(trunc(theTotalDiscountRefund)));//present only if >0

//////////////////////////TotalAdvisedChargeValue/////////////////////////////////////
        // Add TotalAdvisedChargeValue if advisedChargeDetectedFlag is true
        if ( advisedChargeDetectedFlag == true )
        {
            asnTreePushTag("IFW_TAP3.TotalAdvisedChargeValueList");
            
            Long i;
            for (i=0 ; (i<totalAdvisedChargeCurrencyEntries); i=i+1)
            {
                asnTreePushTag("IFW_TAP3.TotalAdvisedChargeValue");

                if ( advisedChargeCurrency[i] != "")
                    asnTreeAddString("IFW_TAP3.AdvisedChargeCurrency.ADVISED_CHARGE_CURRENCY", advisedChargeCurrency[i]);

                if ( totalAdvisedCharge[i] > 0.0 )
                    asnTreeAddString("IFW_TAP3.TotalAdvisedCharge.TOTAL_ADVISED_CHARGE", decimalToStrHex( trunc(totalAdvisedCharge[i])));

                if ( totalAdvisedChargeRefund[i] > 0.0 )
                    asnTreeAddString("IFW_TAP3.TotalAdvisedChargeRefund.TOTAL_ADVISED_CHARGE_REFUND", decimalToStrHex( trunc(totalAdvisedChargeRefund[i])));

                if ( totalCommission[i] > 0.0 )
                    asnTreeAddString("IFW_TAP3.TotalCommission.TOTAL_COMMISSION", decimalToStrHex( trunc(totalCommission[i])));

                if ( totalCommissionRefund[i] > 0.0 )
                    asnTreeAddString("IFW_TAP3.TotalCommissionRefund.TOTAL_COMMISSION_REFUND", decimalToStrHex( trunc(totalCommissionRefund[i])));

                asnTreePop(); //asnTreePushTag("IFW_TAP3.TotalAdvisedChargeValue");

            }

            asnTreePop(); //asnTreePushTag("IFW_TAP3.TotalAdvisedChargeValueList");
        }
                
//////////////////////////////////////////////////////////////////////////////////////

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
        arrayClear( detailTotalChargeValueRefund );
	detailTotalChargeEntries = 0;

//logStdout("IFW_TAP3.DETAIL.STD_MAPPING "+recordNum+" (Type:"+recordType+")\n");
	Bool retval;

        chargeRefundFlag = false;

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
	else if (recordType == type_LOCN)
	{
	  record_Type = record_LOCN;
	  retval = processLOCN();
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
