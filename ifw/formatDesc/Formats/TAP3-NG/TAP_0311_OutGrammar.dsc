//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
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
  const Long theTap3ReleaseVersionNumber       = 11;

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
  String currencyCode_Default_1;
  String currencyCode_Default_2;
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
  String  senderFieldValue;
  String  recipientFieldValue;

  // for Trailer update
  Date   firstCall_date;
  String firstCall_offset;
  Date   lastCall_date;
  String lastCall_offset;
  
  // index to ASN_TreeNode objects
  Long    theAccountingInfoIdx;
  Long    theNetworkInfoIdx;
  Long    theMessageDescriptionIdx;
  Long    theDetailRootIdx;
  Long    lastDetailIdx;
  
  // taxation
  Long   taxEntries;
  String taxRate[];
  String chargeType[];
  String taxIndicator[];

  // recEntityInfo
  Long   recEntityEntries;
  Long   recEntityType[];    // recEntityType_MSC/recEntityType_SMSC/recEntityType_GGSN/recEntityType_SGSN
  String recEntityId[];
  Long   recEntityId_Type[]; // recEntityId_mscId/recEntityId_msisdn/recEntityId_iPTextV4Address/recEntityId_iPTextV6Address
  Long   recEntityType_MSC;
  Long   recEntityType_SMSC;
  Long   recEntityType_GGSN;
  Long   recEntityType_SGSN;
  Long   recEntityType_GMLC;
  Long   recEntityType_WLAN;
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
  String reg_Sender;
  String reg_Recipient;
  
  // storage of registry values
  String defaultTapCurrency;
  String defaultLocalCurrency;

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
    reg_Sender                          = reg_TapIOModule + ".Module.Sender";
    reg_Recipient                       = reg_TapIOModule + ".Module.Recipient";
    
    reg_TapCurrency			= reg_TapPipeline + ".TapCurrency";
    reg_TapDecimalPlaces		= reg_TapPipeline + ".TapDecimalPlaces";
    reg_ExchangeDecimalPlaces		= reg_TapPipeline + ".ExchangeRateDecimalPlaces";
    reg_NetworkType			= reg_TapPipeline + ".NetworkType";
    reg_chargedCurrencyType             = reg_TapPipeline + ".ChargedCurrencyType";

    senderFieldValue                    = regString(reg_Sender);
    recipientFieldValue                 = regString(reg_Recipient);

    defaultTapCurrency			= regString(reg_TapCurrency);
    if (defaultTapCurrency == "")
    {
      defaultTapCurrency		= "SDR";
    }
    defaultLocalCurrency		= defaultTapCurrency; // default
//    theTapDecimalPlaces			= strToLong( regString(reg_TapDecimalPlaces) );
//    if (theTapDecimalPlaces == 0)
//    {
//      theTapDecimalPlaces		= 3;
//    }
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

    
//    theAbsoluteAmountMultiplier = 1.0;
//    Long i;
//    for (i=0 ; i < theTapDecimalPlaces ; i=i+1)
//    {
//      theAbsoluteAmountMultiplier = theAbsoluteAmountMultiplier * 10.0;
//    }
	Long i;
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
    recEntityType_GMLC          = 5;
    recEntityType_WLAN          = 6;
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

    currencyCode_Default_1 = "SDR";
    currencyCode_Default_2 = "XDR";
  }

  function initializeForNewHeader
  {
    // initialisation of some runtime arrays
    //-----------------------------------------
    // taxation
    taxEntries = 0;
    arrayClear( taxRate );
    arrayClear( chargeType );
    arrayClear( taxIndicator );
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
	{
            detailTotalChargeValue[i] = detailTotalChargeValue[i] + TotalChargeValue;
	}
        else
	{
	    detailTotalChargeValueRefund[i] = detailTotalChargeValueRefund[i] + TotalChargeValue;
	}

        return true;
      }
    }
    // if we get here, the type is not yet used.
    detailTotalChargeType[i] = TotalChargeType;

    if ( chargeRefundFlag == false )
    {
        detailTotalChargeValue[i]= TotalChargeValue;
    }     
    else
    {
        detailTotalChargeValueRefund[i]= TotalChargeValue;
    }
        
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
      { 
          theTotalDiscountValue = theTotalDiscountValue + detailDiscountValue ;
      }
      else
      {
          theTotalDiscountRefund = theTotalDiscountRefund + detailDiscountValue ;
      }

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
      {
          theTotalTaxValue = theTotalTaxValue + detailTaxValue ;
      } 
      else
      {
          theTotalTaxValueRefund = theTotalTaxValueRefund + detailTaxValue ;
      }       
   
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

  function Long getTaxRateCode(String TaxRate, String ChargeType, String TaxIndicator)
  {
    //NB: the codes start at index 1 !!!
    Long i;
    for (i=1 ; i<=taxEntries ; i=i+1)
    {
      if ( (taxRate[i] == TaxRate) and (chargeType[i] == ChargeType) and
           (taxIndicator[i] == TaxIndicator) ) 
          
      {
        return i;
      }
    }
    // if we get here, it is not yet stored so store it
    taxRate[i] = TaxRate;
    chargeType[i] = ChargeType; 
    taxIndicator[i] = TaxIndicator;
    taxEntries = taxEntries + 1;
    return i;
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
    
    if ((recEntityType[i] == recEntityType_GGSN) or (recEntityType[i] == recEntityType_SGSN) or
        (recEntityType[i] == recEntityType_GMLC) or (recEntityType[i] == recEntityType_WLAN))
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
    asnTreeGetStoredNode(theAccountingInfoIdx); // ie. asnTreePushTag("TAP_0311.AccountingInfo");
    if (taxEntries > 0)
    {
      asnTreePushTag("TAP_0311.TaxationList");
      for (i=1 ; i<=taxEntries ; i=i+1)
      {
        asnTreePushTag("TAP_0311.Taxation");
        asnTreeAddInteger("TAP_0311.TaxCode.TaxCode", i);
        asnTreeAddString("TAP_0311.TaxType.TaxType", "13" ); //ie ValueAddedTax
        asnTreeAddString("TAP_0311.TaxRate.TaxRate", taxRate[i] );
        if(chargeType[i] != "")
        {
          asnTreeAddString("TAP_0311.ChargeType.ChargeType", chargeType[i] );
        }
        if(taxIndicator[i] != "")
        {
          asnTreeAddString("TAP_0311.TaxIndicator.TaxIndicator", taxIndicator[i] );
        }
        asnTreePop(); //asnTreePushTag("TAP_0311.Taxation");
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.TaxationList");
    }
    if (discountEntries > 0)
    {
      asnTreePushTag("TAP_0311.DiscountingList");
      for (i=1 ; i<=discountEntries ; i=i+1)
      {
        asnTreePushTag("TAP_0311.Discounting");
        asnTreeAddInteger("TAP_0311.DiscountCode.DiscountCode", i);
        asnTreePushTag("TAP_0311.DiscountApplied");
        asnTreeAddInteger("TAP_0311.FixedDiscountValue.FixedDiscountValue", discountApplied[i] );
        asnTreePop(); //asnTreePushTag("TAP_0311.DiscountApplied");
        asnTreePop(); //asnTreePushTag("TAP_0311.Discounting");
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.DiscountingList");
    }
    if (theLocalCurrency != "")
    {
      asnTreeAddString("TAP_0311.LocalCurrency.LocalCurrency",   theLocalCurrency);
    }
    else
    {
      //TODO error ?
      asnTreeAddString("TAP_0311.LocalCurrency.LocalCurrency",   defaultLocalCurrency);
    }

    if ( (theTapCurrency != "") and (theTapCurrency != defaultTapCurrency) and (theTapCurrency != currencyCode_Default_1) and (theTapCurrency != currencyCode_Default_2) )
    {
      asnTreeAddString("TAP_0311.TapCurrency.TapCurrency", theTapCurrency);
    }

    if (exchangeRateEntries > 0)
    {
      asnTreePushTag("TAP_0311.CurrencyConversionList");
      for (i=1 ; i<=exchangeRateEntries ; i=i+1)
      {
        asnTreePushTag("TAP_0311.CurrencyConversion");
        asnTreeAddInteger("TAP_0311.ExchangeRateCode.ExchangeRateCode", i);
        asnTreeAddInteger("TAP_0311.NumberOfDecimalPlaces.NumberOfDecimalPlaces", theExchangeDecimalPlaces);
        asnTreeAddInteger("TAP_0311.ExchangeRate.ExchangeRate", exchangeRate[i]);
        asnTreePop(); //asnTreePushTag("TAP_0311.CurrencyConversion");
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.CurrencyConversionList");
    }
    else
    {
      // default is an exchange rate of 1/1
      asnTreePushTag("TAP_0311.CurrencyConversionList");
      asnTreePushTag("TAP_0311.CurrencyConversion");
      asnTreeAddInteger("TAP_0311.ExchangeRateCode.ExchangeRateCode", 1);
      asnTreeAddInteger("TAP_0311.NumberOfDecimalPlaces.NumberOfDecimalPlaces", theExchangeDecimalPlaces);
      asnTreeAddInteger("TAP_0311.ExchangeRate.ExchangeRate", decimalToLong(theExchangeRateMultiplier));
      asnTreePop(); //asnTreePushTag("TAP_0311.CurrencyConversion");
      asnTreePop(); //asnTreePushTag("TAP_0311.CurrencyConversionList");
    }
    asnTreeAddInteger("TAP_0311.TapDecimalPlaces.TapDecimalPlaces", theTapDecimalPlaces);
    asnTreePop(); //asnTreePushTag("TAP_0311.AccountingInfo");
    
    // theNetworkInfoIdx
    //=====================
    asnTreeGetStoredNode(theNetworkInfoIdx); // ie asnTreePushTag("TAP_0311.NetworkInfo");
    asnTreePushTag("TAP_0311.UtcTimeOffsetInfoList");
    for (i=1 ; i<=utcTimeOffsetEntries ; i=i+1)
    {
      asnTreePushTag("TAP_0311.UtcTimeOffsetInfo");
      asnTreeAddInteger("TAP_0311.UtcTimeOffsetCode.UtcTimeOffsetCode", i);
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", utcTimeOffset[i]  );
      asnTreePop(); //asnTreePushTag("TAP_0311.UtcTimeOffsetInfo");
    }
    if (utcTimeOffsetEntries == 0)
    {
      asnTreePushTag("TAP_0311.UtcTimeOffsetInfo");
      asnTreeAddInteger("TAP_0311.UtcTimeOffsetCode.UtcTimeOffsetCode", 1);
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset  );
      asnTreePop(); //asnTreePushTag("TAP_0311.UtcTimeOffsetInfo");
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.UtcTimeOffsetInfoList");
    if (recEntityEntries > 0)
    {
      asnTreePushTag("TAP_0311.RecEntityInfoList");
      for (i=1 ; i<=recEntityEntries ; i=i+1)
      {
	asnTreePushTag("TAP_0311.RecEntityInformation");
	asnTreeAddInteger("TAP_0311.RecEntityCode.RecEntityCode",      i);
	asnTreeAddInteger("TAP_0311.RecEntityType.RecEntityType",	     recEntityType[i]);

        //recEntityId
        asnTreeAddString("TAP_0311.RecEntityId.RecEntityId", recEntityId[i]);

	asnTreePop(); //asnTreePushTag("TAP_0311.RecEntityInformation");
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.RecEntityInfoList");
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.NetworkInfo");


    // theMessageDescriptionIdx
    //==========================
    if (messageDescriptionEntries > 0)
    {
      asnTreeGetStoredNode(theMessageDescriptionIdx); // ie asnTreePushTag("TAP_0311.MessageDescription");
      for (i=1 ; i<=messageDescriptionEntries ; i=i+1)
      {
	asnTreePushTag("TAP_0311.MessageDescriptionInformation");
	asnTreeAddInteger("TAP_0311.MessageDescriptionCode.MessageDescriptionCode", i);
	asnTreeAddString("TAP_0311.MessageDescription.MessageDescription", messageDescription[i]  );
	asnTreePop(); //asnTreePushTag("TAP_0311.MessageDescriptionInformation");
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.MessageDescription");
    }
    else
    {
      asnTreeDeleteNodeByIndex(theMessageDescriptionIdx);
      theMessageDescriptionIdx = 0;
    }
  }
  
  function addDateTimeLong(String timeStamp, String utcTimeOffset)
  {
    asnTreeAddString("TAP_0311.LocalTimeStamp.LocalTimeStamp", timeStamp );
    if (utcTimeOffset == "")
    {
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset );
    }
    else
    {
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", utcTimeOffset );
    }
  }
  function addDateTime(String timeStamp, String utcTimeOffset)
  {
    asnTreeAddString("TAP_0311.LocalTimeStamp.LocalTimeStamp", timeStamp );
    if (utcTimeOffset == "")
    {
      asnTreeAddInteger("TAP_0311.UtcTimeOffsetCode.UtcTimeOffsetCode",getUtcTimeOffsetCode(defUtcTimeOffset));
    }
    else
    {
      asnTreeAddInteger("TAP_0311.UtcTimeOffsetCode.UtcTimeOffsetCode",getUtcTimeOffsetCode(utcTimeOffset));
    }
  }
  
  function Bool addGeographicalLocation
  {
      asnTreePushTag("TAP_0311.GeographicalLocation");
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
                 asnTreeAddString("TAP_0311.ServingNetwork.ServingNetwork", tmpGeoLocArray[i+1]);
             break;
             case 2: // This is ServingBID
                 asnTreeAddString("TAP_0311.ServingBid.ServingBid", tmpGeoLocArray[i+1]);
             break;
             case 3: // This is ServingLocationDescription
                 asnTreeAddString("TAP_0311.ServingLocationDescription.ServingLocationDescription", tmpGeoLocArray[i+1]);
             break;
         }
              
      }
      asnTreePop(); // ("TAP_0311.GeographicalLocation");
      return true;
  }

  function addLocationInformation(String switchIdentification)
  {
    // TAP_0311.LocationInformation
    //============================
    asnTreePushTag("TAP_0311.LocationInformation");
    asnTreePushTag("TAP_0311.NetworkLocation");
   
    if (switchIdentification != "")
    {
      asnTreeAddInteger("TAP_0311.RecEntityCode.RecEntityCode", getRecEntityIdCode(switchIdentification,recEntityType_MSC) );
    }

    if (edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.LocationArea.LocationArea",strToLong(edrString(DETAIL.ASS_GSMW_EXT.LOCATION_AREA_INDICATOR, 0)) );
    }
    if (edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.CellId.CellId",strToLong(edrString(DETAIL.ASS_GSMW_EXT.CELL_ID, 0)) );
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.NetworkLocation");

    // Add Geographical Location details
    if( edrString(DETAIL.GEOGRAPHICAL_LOCATION) != "")
        addGeographicalLocation();

    asnTreePop(); //asnTreePushTag("TAP_0311.LocationInformation");
  }
    
  function addGprsLocationInformation
  {
    // TAP_0311.GprsLocationInformation
    //============================
    asnTreePushTag("TAP_0311.GprsLocationInformation");
    asnTreePushTag("TAP_0311.GprsNetworkLocation");
    asnTreePushTag("TAP_0311.RecEntityCodeList");
   
    if ( edrString(DETAIL.ASS_GPRS_EXT.WLAN_ADDRESS, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.RecEntityCode.RecEntityCode",
    	getRecEntityIdCode(edrString(DETAIL.ASS_GPRS_EXT.WLAN_ADDRESS, 0),recEntityType_WLAN));
    }

    if ( edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.RecEntityCode.RecEntityCode",
    	getRecEntityIdCode(edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0),recEntityType_GGSN));
    }

    // Added for GPRS Multi-SGSN Support - Start

    // Get the count of SGSN blocks
    Long sgsnCount = edrNumDatablocks(DETAIL.ASS_GPRS_EXT.SGSN_INFO_LIST, 0);
    Long idxSGSN   = 0;

    // Loop through the list of SGSN's and add them to the ASN Tree
    for ( idxSGSN = 0; idxSGSN < sgsnCount; idxSGSN = idxSGSN + 1)
    {
      if ( edrString(DETAIL.ASS_GPRS_EXT.SGSN_INFO_LIST.SGSN_ADDRESS, 0, idxSGSN) != "")
      {
        asnTreeAddInteger("TAP_0311.RecEntityCode.RecEntityCode",
      	  getRecEntityIdCode(edrString(DETAIL.ASS_GPRS_EXT.SGSN_INFO_LIST.SGSN_ADDRESS, 0, idxSGSN),
          recEntityType_SGSN));
      }
    }

    // Added for GPRS Multi-SGSN Support - End

    asnTreePop(); //asnTreePushTag("TAP_0311.RecEntityCodeList");
    if (edrString(DETAIL.ASS_GPRS_EXT.LOCATION_AREA_INDICATOR, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.LocationArea.LocationArea",strToLong(edrString(DETAIL.ASS_GPRS_EXT.LOCATION_AREA_INDICATOR, 0)) );
    }
    if (edrString(DETAIL.ASS_GPRS_EXT.CELL_ID, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.CellId.CellId",strToLong(edrString(DETAIL.ASS_GPRS_EXT.CELL_ID, 0)) );
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.GprsNetworkLocation");

    asnTreePushTag("TAP_0311.HomeLocationInformation");
    if (edrString(DETAIL.ASS_ROAMING_EXT.HOME_BID, 0) != "")
      asnTreeAddString("TAP_0311.HomeBid.HomeBid", edrString(DETAIL.ASS_ROAMING_EXT.HOME_BID, 0));

    if (edrString(DETAIL.ASS_ROAMING_EXT.HOMELOCATION_DESCRIPTION, 0) != "")
    {
      asnTreeAddString("TAP_0311.HomeLocationDescription.HomeLocationDescription", 
                       edrString(DETAIL.ASS_ROAMING_EXT.HOMELOCATION_DESCRIPTION, 0));
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.HomeLocationInformation");

    if( edrString(DETAIL.GEOGRAPHICAL_LOCATION) != "")
        addGeographicalLocation();
    
    asnTreePop(); //asnTreePushTag("TAP_0311.GprsLocationInformation");
  }


  function addEquipmentIdentifier
  {
    // TAP_0311.EquipmentIdentifier
    //============================
      if (edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) != "")
      {
        asnTreePushTag("TAP_0311.ImeiOrEsn");
        asnTreeAddString("TAP_0311.Imei.Imei", edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) );
        asnTreePop(); //asnTreePushTag("TAP_0311.ImeiOrEsn");
      }
  }

  function addOperatorSpecInfoList(String theInfo)
  {
    if ( theInfo != "")
    {
      asnTreePushTag("TAP_0311.OperatorSpecInfoList");
      asnTreeAddString("TAP_0311.OperatorSpecInformation.OperatorSpecInformation", theInfo );
      asnTreePop(); //asnTreePushTag("TAP_0311.OperatorSpecInfoList");
    }
  }

  function addDefaultChargeInformation
  {
    // add an empty Charge information block (if no ASS_CBD with CP is present)
    asnTreePushTag("TAP_0311.ChargeInformation");
    asnTreeAddString("TAP_0311.ChargedItem.ChargedItem", "N");	// non chargeable
    asnTreePushTag("TAP_0311.ChargeDetailList");
    asnTreePushTag("TAP_0311.ChargeDetail");
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeDetail");
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeDetailList");
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeInformation");
  }

  function Long addChargeInformation(Long startCPidx, Long nbCP,Long idxASSCBD, Long idxBlock)
  {
    Bool    multiRateSet = false;
    String  savedDayCategory;
    String  savedTimeBand;

    String  daycategory;
    String  timeband;
    String  startRUM		 = edrString(DETAIL.ASS_CBD.CP.RUM, idxASSCBD, startCPidx);
    Decimal startEXCHANGE_RATE	 = edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, idxASSCBD, startCPidx);
    String  startPRODUCTCODE_USED= edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, idxASSCBD, startCPidx);
    Decimal sumDiscountValue	  = 0.0 ;
    Decimal sumTaxValue	  = 0.0 ;
    Long tmpDiscountType;
    Long i; 

    String  thisTapCurrency	  = edrString(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_CURRENCY, idxASSCBD, startCPidx);
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
    String  thisLocalCurrency	  = edrString(DETAIL.ASS_CBD.CP.EXCHANGE_CURRENCY, idxASSCBD, startCPidx);
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

    asnTreePushTag("TAP_0311.ChargeInformation");
    asnTreeAddString("TAP_0311.ChargedItem.ChargedItem", startRUM);
    Bool bPrintChargeableUnits = false;
    if ( (startRUM == "D") or
         (startRUM == "V") or (startRUM == "W") or (startRUM == "X") )
    {
      bPrintChargeableUnits = true;
    }
    
    if (startEXCHANGE_RATE > 0.0)
    {
      asnTreeAddInteger("TAP_0311.ExchangeRateCode.ExchangeRateCode", getExchangeRateCode(startEXCHANGE_RATE) );
    }
    else
    {
      asnTreeAddInteger("TAP_0311.ExchangeRateCode.ExchangeRateCode", getExchangeRateCode(1.0) );
    }
    
    if (record_Type == record_MOC or record_Type == record_GPRS)
    {
      String callTypeLevel[];
      Long numberofcallTypeLevel = strSplit( callTypeLevel, edrString(DETAIL.CONNECT_TYPE), "," );

      if ( strLength(edrString(DETAIL.CONNECT_TYPE)) >= 2 and (camelServiceDetected == false) and (vasServiceDetected == false) )
      {
        asnTreePushTag("TAP_0311.CallTypeGroup");
        asnTreeAddInteger("TAP_0311.CallTypeLevel1.CallTypeLevel1", strToLong(callTypeLevel[0]) );
        asnTreeAddInteger("TAP_0311.CallTypeLevel2.CallTypeLevel2",  strToLong(callTypeLevel[1]) );
        asnTreeAddInteger("TAP_0311.CallTypeLevel3.CallTypeLevel3", strToLong(edrString(DETAIL.CONNECT_SUB_TYPE)) );
        asnTreePop(); //asnTreePushTag("TAP_0311.CallTypeGroup");
      }
    }


    asnTreePushTag("TAP_0311.ChargeDetailList");
    
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
    
    while ( (startRUM		   == edrString(DETAIL.ASS_CBD.CP.RUM, idxASSCBD, currentCPidx))		and
//    	    (startEXCHANGE_RATE	   == edrDecimal(DETAIL.ASS_CBD.CP.EXCHANGE_RATE, idxASSCBD, currentCPidx))	and
	    (startPRODUCTCODE_USED == edrString(DETAIL.ASS_CBD.CP.PRODUCTCODE_USED, idxASSCBD, currentCPidx))   and
	    (lastChargeType        != "00")								and
	    (currentCPidx	   <  nbCP ) )
    {      
      //only write relevant ChargePackets (otherwise, skip to the next one)
      if (  ((edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, idxASSCBD, currentCPidx) == defaultChargedCurrency)and
             (edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE,       idxASSCBD, currentCPidx) == "S"))
	  or((edrString(DETAIL.ASS_CBD.CP.CHARGED_CURRENCY_TYPE, idxASSCBD, currentCPidx) == defaultChargedCurrency)and
	     (edrString(DETAIL.ASS_CBD.CP.PRICEMODEL_TYPE,       idxASSCBD, currentCPidx) == "A")and
	     (edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY,	 idxASSCBD, currentCPidx) == "00"))
	 )
      {
	lastChargeType = edrString(DETAIL.ASS_CBD.CP.IMPACT_CATEGORY, idxASSCBD, currentCPidx);
        asnTreePushTag("TAP_0311.ChargeDetail");
	nbWrittenCP = nbWrittenCP +1;
        if (lastChargeType != "")
        {
          asnTreeAddString("TAP_0311.ChargeType.ChargeType", lastChargeType);    
        }
        //if (edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, 0, currentCPidx) != 0.0) //TODO uncomment to skip null charges
        {
	  lastChargeValue = round(theAbsoluteAmountMultiplier * edrDecimal(DETAIL.ASS_CBD.CP.CHARGED_AMOUNT_VALUE, idxASSCBD, currentCPidx));
          charge_00       = charge_00 + lastChargeValue;
          asnTreeAddInteger("TAP_0311.Charge.Charge", decimalToLong(lastChargeValue));
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
          asnTreeAddInteger("TAP_0311.ChargeableUnits.ChargeableUnits", lastChargeableUnits);    
	}
        asnTreeAddInteger("TAP_0311.ChargedUnits.ChargedUnits", lastChargedUnits);
	  
        asnTreePushTag("TAP_0311.ChargeDetailTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, idxASSCBD, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop(); //asnTreePushTag("TAP_0311.ChargeDetailTimeStamp");

	idx = idx + 1;		// increment our local charge detail counter

        sumDiscountValue = sumDiscountValue + edrDecimal(DETAIL.ASS_CBD.CP.GRANTED_DISCOUNT_AMOUNT_VALUE, idxASSCBD, currentCPidx);

        //Get the discount applied type
        tmpDiscountType = strToLong(edrString(DETAIL.ASS_CBD.CP.DISCOUNTMODEL_CODE,idxASSCBD, currentCPidx));

        asnTreePop(); //asnTreePushTag("TAP_0311.ChargeDetail");
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
      asnTreePushTag("TAP_0311.ChargeDetail");
      asnTreeAddString("TAP_0311.ChargeType.ChargeType",   "00");  // aggregation
      asnTreeAddInteger("TAP_0311.Charge.Charge", decimalToLong(charge_00));    
      storeDetailTotalCharge( "00", charge_00);
      if (bPrintChargeableUnits)
      {
        asnTreeAddInteger("TAP_0311.ChargeableUnits.ChargeableUnits", chargeableUnits_00);
      }
      asnTreeAddInteger("TAP_0311.ChargedUnits.ChargedUnits", chargedUnits_00);    
      asnTreePushTag("TAP_0311.ChargeDetailTimeStamp");
      //asnTreePushTag("TAP_0311.ChargingTimeStamp");
      addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, idxASSCBD, startCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
      //asnTreePop(); //asnTreePushTag("TAP_0311.ChargingTimeStamp");
      asnTreePop(); //asnTreePushTag("TAP_0311.ChargeDetailTimeStamp");

      asnTreePop(); //asnTreePushTag("TAP_0311.ChargeDetail");
    }

    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeDetailList");


    if (edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE) != 0)
    {
	Long relatedChargeInfoIdCP = edrLong(DETAIL.ASS_CBD.CP.RELATED_CHARGE_INFO_ID, idxASSCBD, startCPidx);
      asnTreePushTag("TAP_0311.TaxInformationList");

        // changes start - Added TAX_PACKET related changes
        Long TPcount	= edrNumDatablocks( DETAIL.ASS_CBD.TP, idxASSCBD );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_TAX_PACKETS,0);
        Long currentTPidx = 0;

        for (currentTPidx = 0; TPcount > currentTPidx; currentTPidx = currentTPidx + 1)
        {
	    Long idxTaxPacRelRec = edrLong(DETAIL.ASS_CBD.TP.RELATED_RECORD_NUMBER, idxASSCBD, currentTPidx) ;
	    Long relatedChargeInfoIdTP = edrLong(DETAIL.ASS_CBD.TP.RELATED_CHARGE_INFO_ID, idxASSCBD, currentTPidx);

	    if ( (idxTaxPacRelRec == idxBlock) and ( relatedChargeInfoIdTP == relatedChargeInfoIdCP) )
	    {
                String charge_Type = edrString(DETAIL.ASS_CBD.TP.CHARGE_TYPE, idxASSCBD, currentTPidx);
                String tax_Indicator = edrString(DETAIL.ASS_CBD.TP.TAX_INDICATOR, idxASSCBD, currentTPidx);
                asnTreePushTag("TAP_0311.TaxInformation");
                // TaxRate comes in TAP3 with 5 decimal places, and in ifw we store only 2 ???
                asnTreeAddInteger("TAP_0311.TaxCode.TaxCode", getTaxRateCode(longToStr(edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE))+"000", charge_Type, tax_Indicator));

                sumTaxValue = edrDecimal(DETAIL.ASS_CBD.TP.TAX_VALUE, idxASSCBD, currentTPidx);
                asnTreeAddInteger("TAP_0311.TaxValue.TaxValue", decimalToLong(edrDecimal(DETAIL.ASS_CBD.TP.TAX_VALUE, idxASSCBD, currentTPidx)));
                if ((edrLong(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, idxASSCBD, currentTPidx)) != 0)
                {
                    asnTreeAddInteger("TAP_0311.TaxableAmount.TaxableAmount", edrLong(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, idxASSCBD, currentTPidx));
                }
                storeDetailTotalTax(sumTaxValue);
                asnTreePop(); //asnTreePushTag("TAP_0311.TaxInformation");
        }
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.TaxInformationList");
      
	  // end - Added TAX_PACKET related changes
    }

    if (sumDiscountValue != 0.0)
    {
      asnTreePushTag("TAP_0311.DiscountInformation");
      sumDiscountValue      = trunc(theAbsoluteAmountMultiplier * sumDiscountValue);
      storeDetailTotalDiscount(sumDiscountValue);
      asnTreeAddInteger("TAP_0311.DiscountCode.DiscountCode", getDiscountCode(decimalToLong(sumDiscountValue)));

      // Check for the discount applied type. if it is of type discount rate then DiscountValue should
      // be populated

      if ( tmpDiscountType == discountApplied_discountRate ) 
      {
          asnTreeAddInteger("TAP_0311.Discount.Discount", decimalToLong(sumDiscountValue));
      }

      if (edrDecimal(DETAIL.ASS_ROAMING_EXT.DISCOUNTABLE_AMOUNT, 0) != 0.0)
      {
        asnTreeAddInteger("TAP_0311.DiscountableAmount.DiscountableAmount", 
                          decimalToLong(edrDecimal(DETAIL.ASS_ROAMING_EXT.DISCOUNTABLE_AMOUNT, 0)));
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.DiscountInformation");
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeInformation");

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

function addCamelTaxInformation(Long nbCP,Long idxASSCBD, Long idxBlock)
{
    if (edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE) != 0)
    {
      asnTreePushTag("TAP_0311.TaxInformationList");

    Decimal sumTaxValue	  = 0.0 ;

        // changes start - Added TAX_PACKET related changes
        Long TPcount	= edrNumDatablocks( DETAIL.ASS_CBD.TP, idxASSCBD );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_TAX_PACKETS,0);
        Long currentTPidx = 0;

        for (currentTPidx = 0; TPcount > currentTPidx; currentTPidx = currentTPidx + 1)
        {
	    Long idxTaxPacRelRec = edrLong(DETAIL.ASS_CBD.TP.RELATED_RECORD_NUMBER, idxASSCBD, currentTPidx) ;
	    Long relatedChargeInfoIdTP = edrLong(DETAIL.ASS_CBD.TP.RELATED_CHARGE_INFO_ID, idxASSCBD, currentTPidx);

	    if ( (idxTaxPacRelRec == idxBlock)) 
	    {
                String charge_Type = edrString(DETAIL.ASS_CBD.TP.CHARGE_TYPE, idxASSCBD, currentTPidx);
                String tax_Indicator = edrString(DETAIL.ASS_CBD.TP.TAX_INDICATOR, idxASSCBD, currentTPidx);
                asnTreePushTag("TAP_0311.TaxInformation");
                // TaxRate comes in TAP3 with 5 decimal places, and in ifw we store only 2 ???
                asnTreeAddInteger("TAP_0311.TaxCode.TaxCode", getTaxRateCode(longToStr(edrLong(DETAIL.WHOLESALE_CHARGED_TAX_RATE))+"000", charge_Type, tax_Indicator));

                sumTaxValue = edrDecimal(DETAIL.ASS_CBD.TP.TAX_VALUE, idxASSCBD, currentTPidx);
                asnTreeAddInteger("TAP_0311.TaxValue.TaxValue", decimalToLong(edrDecimal(DETAIL.ASS_CBD.TP.TAX_VALUE, idxASSCBD, currentTPidx)));
                if ((edrLong(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, idxASSCBD, currentTPidx)) != 0)
                {
                    asnTreeAddInteger("TAP_0311.TaxableAmount.TaxableAmount", edrLong(DETAIL.ASS_CBD.TP.TAXABLE_AMOUNT, idxASSCBD, currentTPidx));
                }
                storeDetailTotalTax(sumTaxValue);
                asnTreePop(); //asnTreePushTag("TAP_0311.TaxInformation");
        }
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.TaxInformationList");
      
	  // end - Added TAX_PACKET related changes
    }
}

  function addCamelServiceUsed( Long nbCP)
  {
    asnTreePushTag("TAP_0311.CamelServiceUsed");
    asnTreeAddInteger("TAP_0311.CamelServiceLevel.CamelServiceLevel", edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_LEVEL, 0));
    asnTreeAddInteger("TAP_0311.CamelServiceKey.CamelServiceKey", edrLong(DETAIL.ASS_CAMEL_EXT.SERVICE_KEY, 0));
    asnTreeAddInteger("TAP_0311.DefaultCallHandlingIndicator.DefaultCallHandlingIndicator",
		      edrLong(DETAIL.ASS_CAMEL_EXT.DEFAULT_CALL_HANDLING_INDICATOR, 0));


    // change start - Added code for related record number



    Long recordNum = edrLong(DETAIL.ASS_CAMEL_EXT.RECORD_NUMBER, 0);
    addCamelTaxInformation(0,0,recordNum);

    // change end - Added code for related record number

     
    // Camel Invocation Fee
    if (edrLong(DETAIL.ASS_CAMEL_EXT.SERVER_TYPE_OF_NUMBER,0) != 0)
    {
        asnTreeAddInteger("TAP_0311.CamelInvocationFee.CamelInvocationFee",edrLong(DETAIL.ASS_CAMEL_EXT.SERVER_TYPE_OF_NUMBER,0));
        storeDetailTotalCharge( "00",longToDecimal(edrLong(DETAIL.ASS_CAMEL_EXT.SERVER_TYPE_OF_NUMBER,0)));
    }

    // Camel Destination / Gprs Destination
    if (edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0) != "")
    {
      asnTreePushTag("TAP_0311.ThreeGcamelDestination");
      asnTreeAddString("TAP_0311.CamelDestinationNumber.CamelDestinationNumber", edrString(DETAIL.ASS_CAMEL_EXT.DEST_GSMW_NUMBER, 0));
      asnTreePop(); //asnTreePushTag("TAP_0311.ThreeGcamelDestination");
    }
    else if (edrString(DETAIL.ASS_CAMEL_EXT.DEST_GPRS_APN_ADDRESS, 0) != "")
    {
      asnTreePushTag("TAP_0311.ThreeGcamelDestination");
      asnTreePushTag("TAP_0311.GprsDestination");
      Long sepIndex = strSearch( edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), ",");
      if (sepIndex < 0)
      {
        asnTreeAddString("TAP_0311.AccessPointNameNI.AccessPointNameNI", edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0));
      }
      else
      {
        asnTreeAddString("TAP_0311.AccessPointNameNI.AccessPointNameNI", 
			 strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), 0, sepIndex) );
        asnTreeAddString("TAP_0311.AccessPointNameOI.AccessPointNameOI",
			 strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), (sepIndex+1), 
			 	   strLength(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)) - (sepIndex+1) ) );
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.GprsDestination");
      asnTreePop(); //asnTreePushTag("TAP_0311.ThreeGcamelDestination");
    }
    
    //CSE Information
    if (edrString(DETAIL.ASS_CAMEL_EXT.CSE_INFORMATION, 0) != "")
    {
       asnTreeAddString("TAP_0311.CseInformation.CseInformation", edrString(DETAIL.ASS_CAMEL_EXT.CSE_INFORMATION, 0));
    }

    asnTreePop(); //asnTreePushTag("TAP_0311.CamelServiceUsed");
    return;
  }

  


  function Bool addBasicServiceUsed
  {
    Long idx = 0;
    Long count = edrNumDatablocks( DETAIL.ASS_GSMW_EXT.BS_PACKET, 0);
    for (idx = 0; count > idx; idx = idx + 1)
    {
      asnTreePushTag("TAP_0311.BasicServiceUsed");
      
      asnTreePushTag("TAP_0311.BasicService");

      asnTreePushTag("TAP_0311.BasicServiceCode");

      if ( strStartsWith(edrString(DETAIL.BASIC_SERVICE),"0") ) //prefix is digit "0"
      {
        String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) )    ;
        asnTreeAddString("TAP_0311.TeleServiceCode.TeleServiceCode", tmp_ServiceCode );
      }
      else //prefix is digit "1"
      {
        String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) )    ;
        asnTreeAddString("TAP_0311.BearerServiceCode.BearerServiceCode", tmp_ServiceCode );
      }

      asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceCode");

//logStdout("\nBS_PACKET.TRANSPARENCY_INDICATOR: " + longToStr(edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx)) +
//          "\nidx: " + longToStr(idx));
      if ((edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx) == 0) or (edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx) == 1))
      {
        asnTreeAddInteger("TAP_0311.TransparencyIndicator.TransparencyIndicator", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.TRANSPARENCY_INDICATOR, 0, idx));
      }
      if (edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.FNUR, 0, idx) != "")
      {
        asnTreeAddInteger("TAP_0311.Fnur.Fnur", strToLong(edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.FNUR, 0, idx)));
      }
      if (edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.USER_PROTOCOL_INDICATOR, 0, idx) != 0)
      {
        asnTreeAddInteger("TAP_0311.UserProtocolIndicator.UserProtocolIndicator", edrLong(DETAIL.ASS_GSMW_EXT.BS_PACKET.USER_PROTOCOL_INDICATOR, 0, idx));
      }

      if (edrString(DETAIL.ASS_ROAMING_EXT.GUARANTEED_BIT_RATE, 0) != "")
      {
        // Stored the string as HexString
        String str = strStrToHexStr(edrString(DETAIL.ASS_ROAMING_EXT.GUARANTEED_BIT_RATE, 0));
        asnTreeAddString("TAP_0311.GuaranteedBitRate.GuaranteedBitRate", str);
      }

      if (edrString(DETAIL.ASS_ROAMING_EXT.MAXIMUM_BIT_RATE, 0) != "")
      {
        // Stored the string as HexString
        String str = strStrToHexStr(edrString(DETAIL.ASS_ROAMING_EXT.MAXIMUM_BIT_RATE, 0));
        asnTreeAddString("TAP_0311.MaximumBitRate.MaximumBitRate", str);
      }

      asnTreePop(); //asnTreePushTag("TAP_0311.BasicService");
      if (dateToStr(edrDate(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHARGING_START_TIMESTAMP, 0, idx)) != "")
      {
        asnTreePushTag("TAP_0311.ChargingTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_GSMW_EXT.BS_PACKET.CHARGING_START_TIMESTAMP, 0, idx)), edrString(DETAIL.ASS_GSMW_EXT.BS_PACKET.UTC_TIME_OFFSET, 0, idx));
        asnTreePop(); //asnTreePushTag("TAP_0311.ChargingTimeStamp");
      }

      asnTreePushTag("TAP_0311.ChargeInformationList");
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
      asnTreePop(); //     asnTreePushTag("TAP_0311.ChargeInformationList");

      
      if (edrString(DETAIL.ASS_ROAMING_EXT.HSCSD_INDICATOR, 0) != "")
      {
        asnTreeAddString("TAP_0311.HSCSDIndicator.HSCSDIndicator", edrString(DETAIL.ASS_ROAMING_EXT.HSCSD_INDICATOR, 0));
      }

      asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceUsed");

    }
    
    return true;
  }

  // change end - Added functions for HSCSD_INFORMATION_PACKET, BASIC_SERVICE_PACKET, ASSOCIATED_VAS_EXTENSION
  //                 and ChargeInformationForSS
  

  function Bool processMOC
  {
    asnTreePushTag("TAP_0311.MobileOriginatedCall");
    lastDetailIdx = asnTreeStoreNode();
    
    // TAP_0311.MoBasicCallInformation
    //============================
    asnTreePushTag("TAP_0311.MoBasicCallInformation");
    asnTreePushTag("TAP_0311.ChargeableSubscriber");
    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreePushTag("TAP_0311.SimChargeableSubscriber");
      asnTreeAddString("TAP_0311.Imsi.Imsi", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
      if (edrString(DETAIL.A_NUMBER) != defTelNumber)
      {
        asnTreeAddString("TAP_0311.Msisdn.Msisdn", edrString(DETAIL.A_NUMBER));
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.SimChargeableSubscriber");
    }
    else if(edrString(DETAIL.ASS_ROAMING_EXT.MOBILE_ID_NUMBER, 0) != "")
    {
      asnTreePushTag("TAP_0311.MinChargeableSubscriber");
      asnTreeAddString("TAP_0311.Min.Min", edrString(DETAIL.ASS_ROAMING_EXT.MOBILE_ID_NUMBER, 0));

      if (edrString(DETAIL.ASS_ROAMING_EXT.MOBILE_DIR_NUMBER, 0) != "")
        asnTreeAddString("TAP_0311.Mdn.Mdn", edrString(DETAIL.ASS_ROAMING_EXT.MOBILE_DIR_NUMBER, 0));

      asnTreePop(); //asnTreePushTag("TAP_0311.MinChargeableSubscriber");
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeableSubscriber");

    if(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0) != 0)
    {
      String rapFileSeqNo = longToStr(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0));
      rapFileSeqNo = strPad(rapFileSeqNo, "0", 5, false);

      asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapFileSeqNo);
    }

    if ((edrString(DETAIL.B_NUMBER) != defTelNumber) or (edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0) != ""))
    {
      asnTreePushTag("TAP_0311.Destination");

      if (( edrString(DETAIL.BASIC_SERVICE) == "020") or ( edrString(DETAIL.BASIC_SERVICE) == "022"))
      {
        asnTreeAddString("TAP_0311.CalledNumber.CalledNumber", edrString(DETAIL.ASS_GSMW_EXT.SMSC_ADDRESS,0));
      }
      else
      {
        asnTreeAddString("TAP_0311.CalledNumber.CalledNumber", edrString(DETAIL.B_NUMBER));
      }

      // Dialled Digits
      if (edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0) != "")
      {
         asnTreeAddString("TAP_0311.DialledDigits.DialledDigits", edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0));
      }

      if (edrString(DETAIL.DESCRIPTION) != "")
      {

          String tmpDescription = edrString(DETAIL.DESCRIPTION);
          Long tmpDescLength = strLength(tmpDescription);
          Long tmpIdx        = strSearch(tmpDescription, ",");

          if (tmpIdx < 0)
          {
              // if we are here then DESCRIPTION contains only called place.
              asnTreeAddString("TAP_0311.CalledPlace.CalledPlace",tmpDescription );
            
          }
          else
          {
              // if we are here then DESCRIPTION contains both called place and called region.
              asnTreeAddString("TAP_0311.CalledPlace.CalledPlace", strSubstr(tmpDescription, 0, tmpIdx));
              asnTreeAddString("TAP_0311.CalledRegion.CalledRegion", 
                              strSubstr(tmpDescription,tmpIdx + 1, tmpDescLength - (tmpIdx + 1)));
            
          }
      }
      if (edrString(DETAIL.ASS_ROAMING_EXT.SMS_DESTINATION_NUMBER, 0) != "")
      {
        asnTreeAddString("TAP_0311.SMSDestinationNumber.SMSDestinationNumber", 
                         edrString(DETAIL.ASS_ROAMING_EXT.SMS_DESTINATION_NUMBER, 0));
      }
      asnTreePop(); //asnTreePushTag("TAP_0311.Destination");
    }
    if (edrString(DETAIL.DESTINATION_NETWORK) != "")
    {
      asnTreeAddString("TAP_0311.DestinationNetwork.DestinationNetwork", edrString(DETAIL.DESTINATION_NETWORK));
    }
    asnTreePushTag("TAP_0311.CallEventStartTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("TAP_0311.CallEventStartTimeStamp");
    asnTreeAddInteger("TAP_0311.TotalCallEventDuration.TotalCallEventDuration", decimalToLong(edrDecimal(DETAIL.DURATION)) );

    // Populate SIM Toolkit Indicator
    if (edrString(DETAIL.DISCOUNT_KEY) != "")
        asnTreeAddString("TAP_0311.SimToolkitIndicator.SimToolkitIndicator", edrString(DETAIL.DISCOUNT_KEY));

    if (edrString(DETAIL.CALL_COMPLETION_INDICATOR) != defCauseForTerm)
    {
      asnTreeAddInteger("TAP_0311.CauseForTerm.CauseForTerm", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.MoBasicCallInformation");

    // TAP_0311.LocationInformation
    //============================
    addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION,0) );
    
    
    // TAP_0311.EquipmentIdentifier
    //============================
    addEquipmentIdentifier();

    // TAP_0311.BasicServiceUsedList
    //============================
    asnTreePushTag("TAP_0311.BasicServiceUsedList");

    // change start - Added call for BASIC_SERVICE_PACKET

    addBasicServiceUsed();
    
    // change end - Added call for BASIC_SERVICE_PACKET

    asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceUsedList");

       
        //SupplServiceCode
        if ( edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,0) != "" )
        {
	    asnTreeAddString("TAP_0311.SupplServiceCode.SupplServiceCode", edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,0) );
        }

        //ThirdPartyInformation
	if (edrString(DETAIL.C_NUMBER) != defTelNumber) // write only once
	{
	  asnTreePushTag("TAP_0311.ThirdPartyInformation");
	  asnTreeAddString("TAP_0311.ThirdPartyNumber.ThirdPartyNumber", edrString(DETAIL.C_NUMBER));

          // CLIR Indicator
          Long clirIndicator = edrLong(DETAIL.ASS_GSMW_EXT.SS_PACKET.CLIR_INDICATOR, 0, 0);
          if ( (clirIndicator == 0) or (clirIndicator == 1))
          {
              asnTreeAddInteger("TAP_0311.ClirIndicator.ClirIndicator", clirIndicator);
          }

	  asnTreePop(); //asnTreePushTag("TAP_0311.ThirdPartyInformation");
	}


    // TAP_0311.CamelServiceUsed
    //============================
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      addCamelServiceUsed( CPcount);
    }

    
    // TAP_0311.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("TAP_0311.MobileOriginatedCall");
    return true;
  }
  
  function Bool processMTC
  {
    asnTreePushTag("TAP_0311.MobileTerminatedCall");
    lastDetailIdx = asnTreeStoreNode();
    
    // TAP_0311.MtBasicCallInformation
    //============================
    asnTreePushTag("TAP_0311.MtBasicCallInformation");
    asnTreePushTag("TAP_0311.ChargeableSubscriber");
    asnTreePushTag("TAP_0311.SimChargeableSubscriber");
    asnTreeAddString("TAP_0311.Imsi.Imsi", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("TAP_0311.Msisdn.Msisdn", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.SimChargeableSubscriber");
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeableSubscriber");

    if(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0) != 0)
    {
      String rapFileSeqNo = longToStr(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0));
      rapFileSeqNo = strPad(rapFileSeqNo, "0", 5, false);

      asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapFileSeqNo);
    }

    if (edrString(DETAIL.B_NUMBER) != defTelNumber)
    {
      asnTreePushTag("TAP_0311.CallOriginator");
      if (( edrString(DETAIL.BASIC_SERVICE) == "020") or ( edrString(DETAIL.BASIC_SERVICE) == "021"))
      {
        asnTreeAddString("TAP_0311.CallingNumber.CallingNumber", edrString(DETAIL.ASS_GSMW_EXT.SMSC_ADDRESS, 0));
      }
      else
      {
        asnTreeAddString("TAP_0311.CallingNumber.CallingNumber", edrString(DETAIL.B_NUMBER));
      }
      if (edrString(DETAIL.ASS_ROAMING_EXT.CLIR_INDICATOR, 0) != "")
          asnTreeAddInteger("TAP_0311.ClirIndicator.ClirIndicator", strToLong(edrString(DETAIL.ASS_ROAMING_EXT.CLIR_INDICATOR, 0)));
      if (edrString(DETAIL.ASS_ROAMING_EXT.SMS_ORIGINATOR, 0) != "")
        asnTreeAddString("TAP_0311.SMSOriginator.SMSOriginator", edrString(DETAIL.ASS_ROAMING_EXT.SMS_ORIGINATOR, 0));

      asnTreePop(); //asnTreePushTag("TAP_0311.CallOriginator");
    }
    if (edrString(DETAIL.SOURCE_NETWORK) != "")
    {
      asnTreeAddString("TAP_0311.OriginatingNetwork.OriginatingNetwork", edrString(DETAIL.SOURCE_NETWORK));
    }
    asnTreePushTag("TAP_0311.CallEventStartTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("TAP_0311.CallEventStartTimeStamp");
    asnTreeAddInteger("TAP_0311.TotalCallEventDuration.TotalCallEventDuration", decimalToLong(edrDecimal(DETAIL.DURATION)) );

    // Populate SIM Toolkit Indicator
    if (edrString(DETAIL.DISCOUNT_KEY) != "")
        asnTreeAddString("TAP_0311.SimToolkitIndicator.SimToolkitIndicator", edrString(DETAIL.DISCOUNT_KEY));

    if (edrString(DETAIL.CALL_COMPLETION_INDICATOR) != defCauseForTerm)
    {
      asnTreeAddInteger("TAP_0311.CauseForTerm.CauseForTerm", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.MtBasicCallInformation");

    // TAP_0311.LocationInformation
    //============================
    if ( edrString(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION,0) != "")
    {
      addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION,0) );
    }
    else
    {
      addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION,0) );
    }
    
    
    // TAP_0311.EquipmentIdentifier
    //============================
    addEquipmentIdentifier();

    // TAP_0311.BasicServiceUsedList
    //============================
    asnTreePushTag("TAP_0311.BasicServiceUsedList");

    // change start - Added call to BASIC_SERVICE_PACKET

    addBasicServiceUsed();

    // change end - Added call to BASIC_SERVICE_PACKET

    asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceUsedList");


    // TAP_0311.CamelServiceUsed
    //============================
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      addCamelServiceUsed(CPcount);
    }


    // TAP_0311.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("TAP_0311.MobileTerminatedCall");
    return true;
  }



  // changes end - Added function for GPRS_SERVICE_USAGE_PACKET


  function Bool processGPRS
  {
    asnTreePushTag("TAP_0311.GprsCall");
    lastDetailIdx = asnTreeStoreNode();
    

    // TAP_0311.GprsBasicCallInformation
    //============================
    asnTreePushTag("TAP_0311.GprsBasicCallInformation");
    asnTreePushTag("TAP_0311.GprsChargeableSubscriber");
    asnTreePushTag("TAP_0311.ChargeableSubscriber");
    asnTreePushTag("TAP_0311.SimChargeableSubscriber");
    asnTreeAddString("TAP_0311.Imsi.Imsi", edrString(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("TAP_0311.Msisdn.Msisdn", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.SimChargeableSubscriber");
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeableSubscriber");
    asnTreeAddString("TAP_0311.PdpAddress.PdpAddress", edrString(DETAIL.ASS_GPRS_EXT.PDP_ADDRESS,0));
    if (edrString(DETAIL.ASS_ROAMING_EXT.NETWORKACCESS_IDENTIFIER, 0) != "")
    {
      asnTreeAddString("TAP_0311.NetworkAccessIdentifier.NetworkAccessIdentifier", 
                       edrString(DETAIL.ASS_ROAMING_EXT.NETWORKACCESS_IDENTIFIER, 0));
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.GprsChargeableSubscriber");

    if(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0) != 0)
    {
      String rapFileSeqNo = longToStr(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0));
      rapFileSeqNo = strPad(rapFileSeqNo, "0", 5, false);

      asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapFileSeqNo);
    }
    
    asnTreePushTag("TAP_0311.GprsDestination");
    Long sepIndex = strSearch( edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), ",");
    if (sepIndex < 0)
    {
      asnTreeAddString("TAP_0311.AccessPointNameNI.AccessPointNameNI", edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0));
    }
    else
    {
      asnTreeAddString("TAP_0311.AccessPointNameNI.AccessPointNameNI", 
                       strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), 0, sepIndex) );
      asnTreeAddString("TAP_0311.AccessPointNameOI.AccessPointNameOI",
                       strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), (sepIndex+1), 
		                 strLength(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)) - (sepIndex+1) ) );
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.GprsDestination");

    asnTreePushTag("TAP_0311.CallEventStartTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("TAP_0311.CallEventStartTimeStamp");
    asnTreeAddInteger("TAP_0311.TotalCallEventDuration.TotalCallEventDuration", decimalToLong(edrDecimal(DETAIL.DURATION)) );
    if (edrString(DETAIL.CALL_COMPLETION_INDICATOR) != defCauseForTerm)
    {
      asnTreeAddInteger("TAP_0311.CauseForTerm.CauseForTerm", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
    }


    String tmpLongDurationIndicator = edrString(DETAIL.LONG_DURATION_INDICATOR);
    if (tmpLongDurationIndicator != "S")
    {
      asnTreeAddString("TAP_0311.PartialTypeIndicator.PartialTypeIndicator", tmpLongDurationIndicator);
    }

    // Populate PDPContextStartTimestamp if the partial call is of type Last or Intermediate.
    if ((tmpLongDurationIndicator == "I") or (tmpLongDurationIndicator == "L"))
    {
        String tmpContextStrtTime = dateToStr(edrDate(DETAIL.ASS_GPRS_EXT.PDP_CONTEXT_START_TIMESTAMP,0));
        if ( tmpContextStrtTime != "" )
        {
            asnTreePushTag("TAP_0311.PDPContextStartTimestamp");    
            addDateTime(tmpContextStrtTime, edrString(DETAIL.ASS_GPRS_EXT.PDP_UTC_TIME_OFFSET,0));
            asnTreePop(); //asnTreePushTag("TAP_0311.PDPContextStartTimestamp");
        }
    }

    if (edrLong(DETAIL.ASS_GPRS_EXT.NETWORK_INITIATED_PDP, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.NetworkInitPDPContext.NetworkInitPDPContext", edrLong(DETAIL.ASS_GPRS_EXT.NETWORK_INITIATED_PDP, 0) );
    }
    asnTreeAddInteger("TAP_0311.ChargingId.ChargingId", strToLong(edrString(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0)));
    asnTreePop(); //asnTreePushTag("TAP_0311.GprsBasicCallInformation");

    // TAP_0311.GprsLocationInformation
    //============================
    addGprsLocationInformation();
    
    
    // TAP_0311.EquipmentIdentifier
    //============================
    addEquipmentIdentifier();

    // TAP_0311.GprsServiceUsed
    //============================
    asnTreePushTag("TAP_0311.GprsServiceUsed");
    
    asnTreeAddInteger("TAP_0311.IMSSignallingContext.IMSSignallingContext", 
                     decimalToLong(edrDecimal(DETAIL.ASS_ROAMING_EXT.ISM_SIGNALLING_CONTEXT, 0)));
    //DataVolumeIncoming
      asnTreeAddInteger("TAP_0311.DataVolumeIncoming.DataVolumeIncoming", decimalToLong(edrDecimal(DETAIL.VOLUME_RECEIVED)) );

    //DataVolumeOutgoing
      asnTreeAddInteger("TAP_0311.DataVolumeOutgoing.DataVolumeOutgoing", decimalToLong(edrDecimal(DETAIL.VOLUME_SENT)) );

    asnTreePushTag("TAP_0311.ChargeInformationList");
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
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeInformationList");
    asnTreePop(); //asnTreePushTag("TAP_0311.GprsServiceUsed");

    // TAP_0311.CamelServiceUsed
    //============================
    if ( edrNumDatablocks(DETAIL.ASS_CAMEL_EXT) > 0 ) 
    {
      addCamelServiceUsed(CPcount);
    }


    // TAP_0311.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("TAP_0311.GprsCall");
    return true;
  }
  
  function Bool processMSS
  {
    asnTreePushTag("TAP_0311.SupplServiceEvent");
    lastDetailIdx = asnTreeStoreNode();
    
    asnTreePushTag("TAP_0311.ChargeableSubscriber");
    asnTreePushTag("TAP_0311.SimChargeableSubscriber");
    asnTreeAddString("TAP_0311.Imsi.Imsi", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("TAP_0311.Msisdn.Msisdn", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.SimChargeableSubscriber");
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargeableSubscriber");

    if(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0) != 0)
    {
      String rapFileSeqNo = longToStr(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0));
      rapFileSeqNo = strPad(rapFileSeqNo, "0", 5, false);

      asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapFileSeqNo);
    }

    // TAP_0311.LocationInformation
    //============================
    addLocationInformation( edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION,0) );
    
    
    // TAP_0311.EquipmentIdentifier
    //============================
    addEquipmentIdentifier();
    
    // TAP_0311.SupplServiceUsed
    //============================
    asnTreePushTag("TAP_0311.SupplServiceUsed");
    asnTreeAddString("TAP_0311.SupplServiceCode.SupplServiceCode", edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,0) );
    asnTreeAddInteger("TAP_0311.SupplServiceActionCode.SupplServiceActionCode", strToLong(edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.ACTION_CODE,0,0)) );
    asnTreePushTag("TAP_0311.ChargingTimeStamp");
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("TAP_0311.ChargingTimeStamp");
      // TAP_0311.ChargeInformation
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
      asnTreePushTag("TAP_0311.BasicServiceCodeList");
      asnTreePushTag("TAP_0311.BasicServiceCode");
      asnTreeAddString("TAP_0311.TeleServiceCode.TeleServiceCode", basicDualServiceSuffixe);
      asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceCode");
      asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceCodeList");
    }
    else if (basicDualServiceprefix == "1")
    {
      // prefix "1" -> BearerService
      asnTreePushTag("TAP_0311.BasicServiceCodeList");
      asnTreePushTag("TAP_0311.BasicServiceCode");
      asnTreeAddString("TAP_0311.BearerServiceCode.BearerServiceCode", basicDualServiceSuffixe);
      asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceCode");
      asnTreePop(); //asnTreePushTag("TAP_0311.BasicServiceCodeList");
    }
    else
    {
      //TODO error check?
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.SupplServiceUsed");
    
    // Populate SIM Toolkit Indicator
    if (edrString(DETAIL.DISCOUNT_KEY) != "")
        asnTreeAddString("TAP_0311.SimToolkitIndicator.SimToolkitIndicator", edrString(DETAIL.DISCOUNT_KEY));

    // TAP_0311.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("TAP_0311.SupplServiceEvent");
    return true;
  }
  
  function Bool processSCU
  {
    asnTreePushTag("TAP_0311.ServiceCentreUsage");
    lastDetailIdx = asnTreeStoreNode();
    
    // TAP_0311.ScuBasicInformation
    //============================
    asnTreePushTag("TAP_0311.ScuBasicInformation");
    asnTreePushTag("TAP_0311.ScuChargeableSubscriber");
    asnTreePushTag("TAP_0311.GsmChargeableSubscriber");
    if (edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) != "")
    {
      asnTreeAddString("TAP_0311.Imsi.Imsi", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    }
    if (edrString(DETAIL.A_NUMBER) != defTelNumber)
    {
      asnTreeAddString("TAP_0311.Msisdn.Msisdn", edrString(DETAIL.A_NUMBER));
    }
    asnTreePop(); //asnTreePushTag("TAP_0311.GsmChargeableSubscriber");
    asnTreePop(); //asnTreePushTag("TAP_0311.ScuChargeableSubscriber");
    asnTreeAddInteger("TAP_0311.ChargedPartyStatus.ChargedPartyStatus", strToLong(edrString(DETAIL.USAGE_DIRECTION)) );

    asnTreeAddString("TAP_0311.NonChargedNumber.NonChargedNumber", edrString(DETAIL.B_NUMBER));

    if (edrString(DETAIL.ASS_ROAMING_EXT.CLIR_INDICATOR, 0) != "")
        asnTreeAddInteger("TAP_0311.ClirIndicator.ClirIndicator", strToLong(edrString(DETAIL.ASS_ROAMING_EXT.CLIR_INDICATOR, 0)));
        
    asnTreeAddString("TAP_0311.OriginatingNetwork.OriginatingNetwork", edrString(DETAIL.SOURCE_NETWORK));
    asnTreeAddString("TAP_0311.DestinationNetwork.DestinationNetwork", edrString(DETAIL.DESTINATION_NETWORK));
    asnTreePop(); //asnTreePushTag("TAP_0311.ScuBasicInformation");

    if(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0) != 0)
    {
      String rapFileSeqNo = longToStr(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0));
      rapFileSeqNo = strPad(rapFileSeqNo, "0", 5, false);

      asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapFileSeqNo);
    }

    if ( edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.RecEntityCode.RecEntityCode",
        getRecEntityIdCode(edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0),recEntityType_SMSC));
    }

    // TAP_0311.ChargeInformation
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

    // TAP_0311.ScuChargeType
    //============================
    asnTreePushTag("TAP_0311.ScuChargeType");
    asnTreeAddInteger("TAP_0311.MessageStatus.MessageStatus", strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)));
    asnTreeAddInteger("TAP_0311.PriorityCode.PriorityCode", strToLong(edrString(DETAIL.QOS_REQUESTED)));

    if ( edrString(DETAIL.ZONE_DESCRIPTION) != "")
        asnTreeAddString("TAP_0311.DistanceChargeBandCode.DistanceChargeBandCode", edrString(DETAIL.ZONE_DESCRIPTION));
        
    asnTreeAddInteger("TAP_0311.MessageType.MessageType", strToLong(edrString(DETAIL.QOS_USED)));  //TODO find a better storage
    asnTreeAddInteger("TAP_0311.MessageDescriptionCode.MessageDescriptionCode", getMessageDescriptionCode(edrString(DETAIL.DESCRIPTION)));
    asnTreePop(); //asnTreePushTag("TAP_0311.ScuChargeType");
    
    // TAP_0311.ScuTimeStamps
    //============================
    asnTreePushTag("TAP_0311.ScuTimeStamps");
    asnTreePushTag("TAP_0311.DepositTimeStamp");	//ie ChargingPoint "D"
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("TAP_0311.DepositTimeStamp");
    asnTreePushTag("TAP_0311.CompletionTimeStamp");	//ie ChargingPoint "C"
    addDateTime(dateToStr(edrDate(DETAIL.CHARGING_END_TIMESTAMP)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop(); //asnTreePushTag("TAP_0311.CompletionTimeStamp");
    asnTreeAddString("TAP_0311.ChargingPoint.ChargingPoint", "D"); //TODO check if it is ok to use always Deposit Timestamp for charging
    asnTreePop(); //asnTreePushTag("TAP_0311.ScuTimeStamps");

    // TAP_0311.OperatorSpecInfoList
    //==============================
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

    asnTreePop(); //asnTreePushTag("TAP_0311.ServiceCentreUsage");
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
        asnTreePushTag("TAP_0311.NetworkList");
        for (idx = 0; nlCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.Network");
          asnTreeAddInteger("TAP_0311.NetworkIdType.NetworkIdType", edrLong(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.NetworkIdentifier.NetworkIdentifier", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.NETWORK_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("TAP_0311.Network");
        }
        asnTreePop(); // asnTreePushTag("TAP_0311.NetworkList");
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
        asnTreePushTag("TAP_0311.AdvisedChargeInformation");

        if ( a )
        {
          asnTreeAddInteger("TAP_0311.PaidIndicator.PaidIndicator", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAID_INDICATOR, 0, idx) );
        }
        if ( b )
        {
          asnTreeAddInteger("TAP_0311.PaymentMethod.PaymentMethod", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.PAYMENT_METHOD, 0, idx) );
        }
        if ( c )
        {
          localAdvisedChargeCurrency = edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE_CURRENCY, 0, idx);
          asnTreeAddString("TAP_0311.AdvisedChargeCurrency.AdvisedChargeCurrency", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE_CURRENCY, 0, idx) );
        }
        if ( d )
        {
          asnTreeAddInteger("TAP_0311.AdvisedCharge.AdvisedCharge", decimalToLong(edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.ADVISED_CHARGE, 0, idx)));
        }
        if ( e )
        {
          asnTreeAddInteger("TAP_0311.Commission.Commission", decimalToLong(edrDecimal(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.COMMISSION, 0, idx)));
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
        asnTreePop(); // asnTreePushTag("TAP_0311.AdvisedChargeInformation");
      }
      return true;
  }


  function Bool processCONT // Supported since Apollo.1
  {
    asnTreePushTag("TAP_0311.ContentTransaction");
    lastDetailIdx = asnTreeStoreNode();

    Long idx = 0; // index used inside for loop

    // TAP_0311.contentTransactionBasicInfo
    //================================================

    asnTreePushTag("TAP_0311.ContentTransactionBasicInfo");

//      if (edrString(DETAIL.ASS_CONT_EXT.RAP_FILE_SEQ_NO, 0) != "")
//      {
//        asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", edrString(DETAIL.ASS_CONT_EXT.RAP_FILE_SEQ_NO, 0) );
//      }

      if(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0) != 0)
      {
        String rapFileSeqNo = longToStr(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0));
        rapFileSeqNo = strPad(rapFileSeqNo, "0", 5, false);

        asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapFileSeqNo);
      }

      if (dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ORDER_PLACED_TIMESTAMP, 0)) != "")
      {
        asnTreePushTag("TAP_0311.OrderPlacedTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ORDER_PLACED_TIMESTAMP, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop();  // asnTreePushTag("TAP_0311.OrderPlacedTimeStamp");
      }
      if (dateToStr(edrDate(DETAIL.ASS_CONT_EXT.REQUESTED_DELIVERY_TIMESTAMP, 0)) != "")
      {
        asnTreePushTag("TAP_0311.RequestedDeliveryTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CONT_EXT.REQUESTED_DELIVERY_TIMESTAMP, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop();  // asnTreePushTag("TAP_0311.RequestedDeliveryTimeStamp");
      }
      if (dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ACTUAL_DELIVERY_TIMESTAMP, 0)) != "")
      {
        asnTreePushTag("TAP_0311.ActualDeliveryTimeStamp");
        addDateTime(dateToStr(edrDate(DETAIL.ASS_CONT_EXT.ACTUAL_DELIVERY_TIMESTAMP, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
        asnTreePop();  // asnTreePushTag("TAP_0311.ActualDeliveryTimeStamp");
      }
      if (edrLong(DETAIL.ASS_CONT_EXT.TOTAL_TRANSACTION_DURATION, 0) != 0)
      {
        
        asnTreeAddInteger("TAP_0311.TotalTransactionDuration.TotalTransactionDuration", edrLong(DETAIL.ASS_CONT_EXT.TOTAL_TRANSACTION_DURATION, 0) );
      }
      if (edrLong(DETAIL.ASS_CONT_EXT.TRANSACTION_STATUS, 0) != 0)
      {
        asnTreeAddInteger("TAP_0311.TransactionStatus.TransactionStatus", edrLong(DETAIL.ASS_CONT_EXT.TRANSACTION_STATUS, 0) );
      }
    
    asnTreePop();	// 1. asnTreePushTag("TAP_0311.contentTransactionBasicInfo")

    // TAP_0311.chargedPartyInformation
    //================================================

    asnTreePushTag("TAP_0311.ChargedPartyInformation");

      Long IDcount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST, 0, 0); // edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST, 0);
      if ( IDcount > 0 )
      {
        asnTreePushTag("TAP_0311.ChargedPartyIdList");
        for (idx = 0; IDcount > idx; idx = idx + 1)
        {
          asnTreePushTag("TAP_0311.ChargedPartyIdentification");
          asnTreeAddInteger("TAP_0311.ChargedPartyIdType.ChargedPartyIdType", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.ChargedPartyIdentifier.ChargedPartyIdentifier", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("TAP_0311.ChargedPartyIdentification");
        }
        asnTreePop(); // asnTreePushTag("TAP_0311.ChargedPartyIdList");
      }

      Long homeIDCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST, 0, 0);
      if ( homeIDCount > 0 )
      {
        asnTreePushTag("TAP_0311.ChargedPartyHomeIdList");
        for (idx = 0; homeIDCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.ChargedPartyHomeIdentification");
          asnTreeAddInteger("TAP_0311.HomeIdType.HomeIdType", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.HomeIdentifier.HomeIdentifier", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.HOMEID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("TAP_0311.ChargedPartyHomeIdentification");
        }
        asnTreePop(); // asnTreePushTag("TAP_0311.ChargedPartyHomeIdList");
      }

      Long locationCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST, 0, 0);
      if ( locationCount > 0 )
      {
        asnTreePushTag("TAP_0311.ChargedPartyLocationList");
        for (idx = 0; locationCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.ChargedPartyLocation");
          asnTreeAddInteger("TAP_0311.LocationIdType.LocationIdType", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.LocationIdentifier.LocationIdentifier", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.LOCATION_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("TAP_0311.ChargedPartyLocation");
        }
        asnTreePop(); // asnTreePushTag("TAP_0311.ChargedPartyLocationList");
      }

      if (edrNumDatablocks(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT, 0, 0) > 0)
      {
          asnTreePushTag("TAP_0311.ChargedPartyEquipment");
          asnTreeAddInteger("TAP_0311.EquipmentIdType.EquipmentIdType", edrLong(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.TYPE, 0, 0, 0) );
          asnTreeAddString("TAP_0311.EquipmentId.EquipmentId", edrString(DETAIL.ASS_CONT_EXT.CHARGED_PARTY_INFO.EQUIPMENT.IDENTIFIER, 0, 0, 0) );
          asnTreePop(); // asnTreePushTag("TAP_0311.ChargedPartyLocation");
      }

    asnTreePop();	// 2. asnTreePushTag("TAP_0311.chargedPartyInformation")


    // TAP_0311.servingPartiesInformation
    //================================================
    
    Long spiCount = 0;

    asnTreePushTag("TAP_0311.ServingPartiesInformation");

      asnTreeAddString("TAP_0311.ContentProviderName.ContentProviderName", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_NAME, 0, 0));

      spiCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST, 0, 0);
      if ( spiCount > 0 )
      {
        asnTreePushTag("TAP_0311.ContentProviderIdList");
        for (idx = 0; spiCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.ContentProvider");
          asnTreeAddInteger("TAP_0311.ContentProviderIdType.ContentProviderIdType", edrLong(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.ContentProviderIdentifier.ContentProviderIdentifier", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.PROVIDER_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("TAP_0311.ContentProvider");
        }
        asnTreePop(); // asnTreePushTag("TAP_0311.ContentProviderIdList");
      }
      spiCount = 0;
  
      spiCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST, 0, 0);
      if ( spiCount > 0 )
      {
        asnTreePushTag("TAP_0311.InternetServiceProviderIdList");
        for (idx = 0; spiCount > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.InternetServiceProvider");
          asnTreeAddInteger("TAP_0311.IspIdType.IspIdType", edrLong(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.IspIdentifier.IspIdentifier", edrString(DETAIL.ASS_CONT_EXT.SERVING_PARTIES_INFO.ISP_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); // asnTreePushTag("TAP_0311.InternetServiceProvider");
        }
        asnTreePop(); // asnTreePushTag("TAP_0311.InternetServiceProviderIdList");
      }
      spiCount = 0;

      addNetworkList();

    asnTreePop();	// 3. asnTreePushTag("TAP_0311.servingPartiesInformation")


    // TAP_0311.contentServiceUsedList
    //================================================
    
    Long csulCount = 0;
    Long currentCPidx	= 0;  //start from the beginning (first CP)
    Long CPcount	= edrNumDatablocks( DETAIL.ASS_CBD.CP, 0 );//edrLong(DETAIL.ASS_CBD.NUMBER_OF_CHARGE_PACKETS,0);


      csulCount = edrNumDatablocks( DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST, 0);

      asnTreePushTag("TAP_0311.ContentServiceUsedList");    // As it is mandatory count > 0 is not checked!
      for (idx = 0; csulCount > idx; idx = idx + 1)
      {       
        asnTreePushTag("TAP_0311.ContentServiceUsed");
        asnTreeAddInteger("TAP_0311.ContentTransactionCode.ContentTransactionCode", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_CODE, 0, idx) );
        asnTreeAddInteger("TAP_0311.ContentTransactionType.ContentTransactionType", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_TRANSACTION_TYPE, 0, idx) );
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.OBJECT_TYPE, 0, idx) != 0)
        {
          asnTreeAddInteger("TAP_0311.ObjectType.ObjectType", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.OBJECT_TYPE, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DESCRIPTION_SUPP, 0, idx) != 0)
        {
          asnTreeAddInteger("TAP_0311.TransactionDescriptionSupp.TransactionDescriptionSupp", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DESCRIPTION_SUPP, 0, idx) );
        }
        asnTreeAddString("TAP_0311.TransactionShortDescription.TransactionShortDescription", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_SHORT_DESCRIPTION, 0, idx) );
        if (edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DETAIL_DESCRIPTION, 0, idx) != "")
        {
          asnTreeAddString("TAP_0311.TransactionDetailDescription.TransactionDetailDescription", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_DETAIL_DESCRIPTION, 0, idx) );
        }
        if (edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_IDENTIFIER, 0, idx) != "")
        {
          asnTreeAddString("TAP_0311.TransactionIdentifier.TransactionIdentifier", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_IDENTIFIER, 0, idx) );
        }
        if (edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_AUTH_CODE, 0, idx) != "")
        {
          asnTreeAddString("TAP_0311.TransactionAuthCode.TransactionAuthCode", edrString(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TRANSACTION_AUTH_CODE, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_INCOMING, 0, idx) != 0)
        {
          asnTreeAddInteger("TAP_0311.DataVolumeIncoming.DataVolumeIncoming", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_INCOMING, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_OUTGOING, 0, idx) != 0)
        {
          asnTreeAddInteger("TAP_0311.DataVolumeOutgoing.DataVolumeOutgoing", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.DATA_VOLUME_OUTGOING, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TOTAL_DATA_VOLUME, 0, idx) != 0)
        {
          asnTreeAddInteger("TAP_0311.TotalDataVolume.TotalDataVolume", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.TOTAL_DATA_VOLUME, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CHARGE_REFUND_INDICATOR, 0, idx) != 0)
        {
          chargeRefundFlag = true;
          asnTreeAddInteger("TAP_0311.ChargeRefundIndicator.ChargeRefundIndicator", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CHARGE_REFUND_INDICATOR, 0, idx) );
        }
        if (edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_CHARGING_POINT, 0, idx) != 0)
        {
          asnTreeAddInteger("TAP_0311.ContentChargingPoint.ContentChargingPoint", edrLong(DETAIL.ASS_CONT_EXT.SERVICE_USED_LIST.CONTENT_CHARGING_POINT, 0, idx) );
        }

        asnTreePushTag("TAP_0311.ChargeInformationList");
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
        asnTreePop(); //    asnTreePushTag("TAP_0311.ChargeInformationList");

        addAdvisedChargeInformation(idx);

        asnTreePop(); // asnTreePushTag("TAP_0311.contentServiceUsed");
      }

    asnTreePop();	// 4. asnTreePushTag("TAP_0311. contentServiceUsedList")


    // TAP_0311.operatorSpecInformation
    //================================================
    
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));
   

    asnTreePop();	// asnTreePushTag("TAP_0311.ContentTransaction");

    return true;
  }


  function Bool addTrackingCustomerInformation
  {
    Long count = 0;
    Long idx = 0;

    if (edrNumDatablocks(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO, 0) > 0)
    {
      asnTreePushTag("TAP_0311.TrackingCustomerInformation");

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST, 0, 0);

      asnTreePushTag("TAP_0311.TrackingCustomerIdList");

      for (idx = 0; count > idx; idx = idx + 1)
      {       
        asnTreePushTag("TAP_0311.TrackingCustomerIdentification");
        asnTreeAddInteger("TAP_0311.CustomerIdType.CustomerIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.TYPE, 0, 0, idx) );
        asnTreeAddString("TAP_0311.CustomerIdentifier.CustomerIdentifier", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackingCustomerIdentification")
      }

      asnTreePop(); //  asnTreePushTag("TAP_0311.TrackingCustomerIdList")
      count = 0;

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("TAP_0311.TrackingCustomerHomeIdList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.TrackingCustomerHomeId");
          asnTreeAddInteger("TAP_0311.HomeIdType.HomeIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.HomeIdentifier.HomeIdentifier", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("TAP_0311.TrackingCustomerHomeId")
        }

        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackingCustomerHomeIdList")
      }
      count = 0;

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("TAP_0311.TrackingCustomerLocList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.TrackingCustomerLocation");
          asnTreeAddInteger("TAP_0311.LocationIdType.LocationIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.LocationIdentifier.LocationIdentifier", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("TAP_0311.TrackingCustomerLocation")
        }

        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackingCustomerLocList")
      }
      count = 0;

      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("TAP_0311.TrackingCustomerEquipment");

        asnTreeAddInteger("TAP_0311.EquipmentIdType.EquipmentIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.TYPE, 0, 0, 0) );
        asnTreeAddString("TAP_0311.EquipmentId.EquipmentId", edrString(DETAIL.ASS_LOCN_EXT.TRACKING_CUST_INFO.EQUIPMENT.IDENTIFIER, 0, 0, 0) );

        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackingCustomerEquipment")
      }


      asnTreePop();  // asnTreePushTag("TAP_0311.TrackingCustomerInformation")
    }

    return true;
  }


  function Bool addLCSSPInformation
  {
    Long count = 0;
    Long idx = 0;

    if (edrNumDatablocks(DETAIL.ASS_LOCN_EXT.LCSSP_INFO, 0) > 0)
    {
      asnTreePushTag("TAP_0311.LCSSPInformation");

      count = edrNumDatablocks(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST, 0, 0);

      asnTreePushTag("TAP_0311.LCSSPIdentificationList");

      for (idx = 0; count > idx; idx = idx + 1)
      {       
        asnTreePushTag("TAP_0311.LCSSPIdentification");
        if (edrLong(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.TYPE, 0, 0, idx) != 0)
        {
          asnTreeAddInteger("TAP_0311.ContentProviderIdType.ContentProviderIdType", edrLong(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.TYPE, 0, 0, idx) );
        }
        asnTreeAddString("TAP_0311.ContentProviderIdentifier.ContentProviderIdentifier", edrString(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
        asnTreePop(); //  asnTreePushTag("TAP_0311.LCSSPIdentification")
      }
      asnTreePop(); //  asnTreePushTag("TAP_0311.LCSSPIdentificationList")
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("TAP_0311.ISPList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.InternetServiceProvider");
          asnTreeAddInteger("TAP_0311.IspIdType.IspIdType", edrLong(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.IspIdentifier.IspIdentifier", edrString(DETAIL.ASS_LOCN_EXT.LCSSP_INFO.ISP_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("TAP_0311.InternetServiceProvider")
        }

        asnTreePop(); //  asnTreePushTag("TAP_0311.ISPList")
      }
      count = 0;


      addNetworkList();

    
      asnTreePop(); //  asnTreePushTag("TAP_0311.LCSSPInformation")
    }

    return true;
  }


  function Bool addTrackedCustomerInformation
  {
    Long count = 0;
    Long idx = 0;

    if (edrNumDatablocks(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO, 0) > 0)
    {
      asnTreePushTag("TAP_0311.TrackedCustomerInformation");

      count = edrNumDatablocks(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST, 0, 0);

      asnTreePushTag("TAP_0311.TrackedCustomerIdList");

      for (idx = 0; count > idx; idx = idx + 1)
      {       
        asnTreePushTag("TAP_0311.TrackedCustomerIdentification");
        asnTreeAddInteger("TAP_0311.CustomerIdType.CustomerIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.TYPE, 0, 0, idx) );
        asnTreeAddString("TAP_0311.CustomerIdentifier.CustomerIdentifier", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.ID_LIST.IDENTIFIER, 0, 0, idx) );
        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerIdentification")
      }

      asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerIdList")
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("TAP_0311.TrackedCustomerHomeIdList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.TrackedCustomerHomeId");
          asnTreeAddInteger("TAP_0311.HomeIdType.HomeIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.TYPE, 0, 0, idx) );
          asnTreeAddString("TAP_0311.HomeIdentifier.HomeIdentifier", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.HOME_ID_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerHomeId")
        }

        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerHomeIdList")
      }
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("TAP_0311.TrackedCustomerLocList");

        for (idx = 0; count > idx; idx = idx + 1)
        {       
          asnTreePushTag("TAP_0311.TrackedCustomerLocation");
          if (edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.TYPE, 0, 0, idx) != 0)
          {
            asnTreeAddInteger("TAP_0311.LocationIdType.LocationIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.TYPE, 0, 0, idx) );
          }
          asnTreeAddString("TAP_0311.LocationIdentifier.LocationIdentifier", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.LOCATION_LIST.IDENTIFIER, 0, 0, idx) );
          asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerLocation")
        }

        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerLocList")
      }
      count = 0;


      count = edrNumDatablocks( DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT, 0, 0);

      if (count > 0)
      {
        asnTreePushTag("TAP_0311.TrackedCustomerEquipment");

        asnTreeAddInteger("TAP_0311.EquipmentIdType.EquipmentIdType", edrLong(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.TYPE, 0, 0, 0) );
        asnTreeAddString("TAP_0311.EquipmentId.EquipmentId", edrString(DETAIL.ASS_LOCN_EXT.TRACKED_CUST_INFO.EQUIPMENT.IDENTIFIER, 0, 0, 0) );

        asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerEquipment")
      }

    
      asnTreePop(); //  asnTreePushTag("TAP_0311.TrackedCustomerInformation")
    }

    return true;
  }


  function Bool addLocationServiceUsage
  {
    asnTreePushTag("TAP_0311.LocationServiceUsage");


    // TAP_0311.LCSQosRequested
    //=====================================

    asnTreePushTag("TAP_0311.LCSQosRequested");

    asnTreePushTag("TAP_0311.LCSRequestTimestamp");
    addDateTime(dateToStr(edrDate(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_REQUEST_TIMESTAMP, 0, 0)), edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreePop();  // asnTreePushTag("TAP_0311.LCSRequestTimestamp");

    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_REQUESTED, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.HorizontalAccuracyRequested.HorizontalAccuracyRequested", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_REQUESTED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_REQUESTED, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.VerticalAccuracyRequested.VerticalAccuracyRequested", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_REQUESTED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME_CATEGORY, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.ResponseTimeCategory.ResponseTimeCategory", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME_CATEGORY, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.TRACKING_PERIOD, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.TrackingPeriod.TrackingPeriod", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.TRACKING_PERIOD, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.REQ_TRACKING_FREQUENCY, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.TrackingFrequency.TrackingFrequency", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.REQ_TRACKING_FREQUENCY, 0, 0) );
    }

    asnTreePop(); // asnTreePushTag("TAP_0311.LCSQosRequested");


    // TAP_0311.LCSQosDelivered
    //======================================

    asnTreePushTag("TAP_0311.LCSQosDelivered");

    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_TRANS_STATUS, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.LCSTransactionStatus.LCSTransactionStatus", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.LCS_TRANS_STATUS, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_DELIVERED, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.HorizontalAccuracyDelivered.HorizontalAccuracyDelivered", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.H_ACCURACY_DELIVERED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_DELIVERED, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.VerticalAccuracyDelivered.VerticalAccuracyDelivered", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.V_ACCURACY_DELIVERED, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.ResponseTime.ResponseTime", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.RESPONSE_TIME, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.POSITIONING_METHOD, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.PositioningMethod.PositioningMethod", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.POSITIONING_METHOD, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_PERIOD, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.TrackingPeriod.TrackingPeriod", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_PERIOD, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_FREQUENCY, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.TrackingFrequency.TrackingFrequency", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.DEL_TRACKING_FREQUENCY, 0, 0) );
    }
    if (edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.AGE_OF_LOCATION, 0, 0) != 0)
    {
      asnTreeAddInteger("TAP_0311.AgeOfLocation.AgeOfLocation", edrLong(DETAIL.ASS_LOCN_EXT.SERVICE_USAGE.AGE_OF_LOCATION, 0, 0) );
    }

    asnTreePop(); // asnTreePushTag("TAP_0311.LCSQosRequested");


    // TAP_0311.ChargingTimeStamp
    //======================================

    //if (dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)) != "")
    //{
     // asnTreePushTag("TAP_0311.ChargingTimeStamp");
      //addDateTime(dateToStr(edrDate(DETAIL.ASS_CBD.CP.CHARGING_START_TIMESTAMP, 0, currentCPidx)), edrString(DETAIL.UTC_TIME_OFFSET));
//      asnTreePop(); // asnTreePushTag("TAP_0311.ChargingTimeStamp");
//    }


    // TAP_0311.ChargeInformationList
    //======================================

    asnTreePushTag("TAP_0311.ChargeInformationList");

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

    asnTreePop(); // asnTreePushTag("TAP_0311.ChargeInformationList");



    asnTreePop(); //  asnTreePushTag("TAP_0311.LocationServiceUsage")

    return true;
  }


  function Bool processLOCN // Supported since Apollo.1
  {
    asnTreePushTag("TAP_0311.LocationService");
    lastDetailIdx = asnTreeStoreNode();

    Long idx = 0; // index used inside for loop

//    if (edrString(DETAIL.ASS_CONT_EXT.RAP_FILE_SEQ_NO, 0) != "")
//    {
//      asnTreeAddString("TAP_0311.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER", edrString(DETAIL.ASS_CONT_EXT.RAP_FILE_SEQ_NO, 0) );
//    }

    if(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0) != 0)
    {
      String rapFileSeqNo = longToStr(edrLong(DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO, 0));
      rapFileSeqNo = strPad(rapFileSeqNo, "0", 5, false);

      asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapFileSeqNo);
    }

    if (edrString(DETAIL.ASS_LOCN_EXT.GMLC_ADDRESS, 0) != "")
    {
      asnTreeAddInteger("TAP_0311.RecEntityCode.RecEntityCode",
        getRecEntityIdCode(edrString(DETAIL.ASS_LOCN_EXT.GMLC_ADDRESS, 0), recEntityType_GMLC));
    } 
    
    if (edrString(DETAIL.ASS_LOCN_EXT.CALL_REFERENCE, 0) != "")
    {
      asnTreeAddString("TAP_0311.CallReference.CallReference", edrString(DETAIL.ASS_LOCN_EXT.CALL_REFERENCE, 0));
    }

    // TAP_0311.TrackingCustomerInformation
    //================================================

    addTrackingCustomerInformation();

  
    // TAP_0311.lCSSPInformation
    //================================================

    addLCSSPInformation();

  
    // TAP_0311.TrackedCustomerInformation
    //================================================

    addTrackedCustomerInformation();

  
    // TAP_0311.LocationServiceUsage
    //================================================

    addLocationServiceUsage();

  
    // TAP_0311.operatorSpecInformation
    //================================================
    
    addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));
   

    asnTreePop();	// asnTreePushTag("TAP_0311.LocationService");

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
	asnTreePushTag("TAP_0311.TransferBatch");
      }
      header_TransfertBatch
      {
	asnTreePushTag("TAP_0311.CallEventDetailList");
	theDetailRootIdx = asnTreeStoreNode();
      }
      details
      {
	asnTreePop(); //asnTreePushTag("TAP_0311.CallEventDetailList");
      }
      trailer
      {
	asnTreePop(); //asnTreePushTag("TAP_0311.TransferBatch");
	
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

	asnTreePushTag("TAP_0311.Notification");

        if(senderFieldValue != "")
        {
	  asnTreeAddString("TAP_0311.Sender.Sender", senderFieldValue);
        }
        else
        {
          asnTreeAddString("TAP_0311.Sender.Sender", edrString(HEADER.SENDER));
        }

        if(recipientFieldValue != "")
        {
          asnTreeAddString("TAP_0311.Recipient.Recipient", recipientFieldValue);
        }
        else
        {
          asnTreeAddString("TAP_0311.Recipient.Recipient", edrString(HEADER.RECIPIENT));
        }
 
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
        asnTreeAddString("TAP_0311.FileSequenceNumber.FileSequenceNumber",theSequenceNumber );
	asnTreePushTag("TAP_0311.FileCreationTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("TAP_0311.FileCreationTimeStamp");
	asnTreePushTag("TAP_0311.FileAvailableTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSMISSION_DATE)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("TAP_0311.FileAvailableTimeStamp");
	asnTreePushTag("TAP_0311.TransferCutOffTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("TAP_0311.TransferCutOffTimeStamp");
	asnTreeAddInteger("TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber",theTap3SpecificationVersionNumber );
	asnTreeAddInteger("TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber",theTap3ReleaseVersionNumber );
	if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
	{
	  asnTreeAddString("TAP_0311.FileTypeIndicator.FileTypeIndicator",  edrString(HEADER.DATA_TYPE_INDICATOR) );
	}
        addOperatorSpecInfoList(edrString(HEADER.OPERATOR_SPECIFIC_INFO));
	asnTreePop(); //asnTreePushTag("TAP_0311.Notification");
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
	theTapDecimalPlaces     = edrLong(HEADER.TAP_DECIMAL_PLACES);
	if (theTapDecimalPlaces == 0)
	{
		theTapDecimalPlaces  = strToLong( regString(reg_TapDecimalPlaces) );
		if (theTapDecimalPlaces == 0)
		{
			theTapDecimalPlaces  = 3;
		}
	}

	theAbsoluteAmountMultiplier = 1.0;
	Long i;
	for (i=0 ; i < theTapDecimalPlaces ; i=i+1)
	{
		theAbsoluteAmountMultiplier = theAbsoluteAmountMultiplier * 10.0;
	}

//logStdout( "TAP_0311.HEADER.STD_MAPPING "+ recordNum +"\n"  );
	
	asnTreePushTag("TAP_0311.BatchControlInfo");

        if(senderFieldValue != "")
        {
          asnTreeAddString("TAP_0311.Sender.Sender", senderFieldValue);
        }
        else
        {
          asnTreeAddString("TAP_0311.Sender.Sender", edrString(HEADER.SENDER));
        }

        if(recipientFieldValue != "")
        {
          asnTreeAddString("TAP_0311.Recipient.Recipient", recipientFieldValue);
        }
        else
        {
          asnTreeAddString("TAP_0311.Recipient.Recipient", edrString(HEADER.RECIPIENT));
        }

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
        asnTreeAddString("TAP_0311.FileSequenceNumber.FileSequenceNumber",theSequenceNumber );
	asnTreePushTag("TAP_0311.FileCreationTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("TAP_0311.FileCreationTimeStamp");
	asnTreePushTag("TAP_0311.TransferCutOffTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSFER_CUTOFF_TIMESTAMP)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("TAP_0311.TransferCutOffTimeStamp");
	asnTreePushTag("TAP_0311.FileAvailableTimeStamp");
	addDateTimeLong(dateToStr(edrDate(HEADER.TRANSMISSION_DATE)), headerUtcTimeOffset);
	asnTreePop(); //asnTreePushTag("TAP_0311.FileAvailableTimeStamp");
	asnTreeAddInteger("TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber",theTap3SpecificationVersionNumber );
	asnTreeAddInteger("TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber",theTap3ReleaseVersionNumber );
	if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
	{
	  asnTreeAddString("TAP_0311.FileTypeIndicator.FileTypeIndicator",  edrString(HEADER.DATA_TYPE_INDICATOR) );
	}
        addOperatorSpecInfoList(edrString(HEADER.OPERATOR_SPECIFIC_INFO));
	asnTreePop(); //asnTreePushTag("TAP_0311.BatchControlInfo");

	asnTreePushTag("TAP_0311.AccountingInfo");
	theAccountingInfoIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("TAP_0311.AccountingInfo");

	asnTreePushTag("TAP_0311.NetworkInfo");
	theNetworkInfoIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("TAP_0311.NetworkInfo");


	asnTreePushTag("TAP_0311.MessageDescriptionInfoList");
	theMessageDescriptionIdx = asnTreeStoreNode();
        //Nothing to do now, node will be accessed using updateTap3HeaderWithCodeLists(xxx)
	asnTreePop(); //asnTreePushTag("TAP_0311.MessageDescriptionInfoList");
      }
    ;
    
  trailer:  
      TRAILER
      {
	record_Type = record_Trailer;
	recordNum   = longToStr(edrLong(TRAILER.RECORD_NUMBER)) ;
//logStdout( "TAP_0311.TRAILER.STD_MAPPING "+ recordNum +"(TotaChargeAmount="+decimalToStr(edrDecimal(TRAILER.TOTAL_WHOLESALE_CHARGED_VALUE))+")\n"  );

	asnTreePushTag("TAP_0311.AuditControlInfo");

	asnTreePushTag("TAP_0311.EarliestCallTimeStamp");
	addDateTimeLong( dateToStr(firstCall_date), firstCall_offset );
	asnTreePop(); //asnTreePushTag("TAP_0311.EarliestCallTimeStamp");
	
	asnTreePushTag("TAP_0311.LatestCallTimeStamp");
	addDateTimeLong( dateToStr(lastCall_date), lastCall_offset );
	asnTreePop(); //asnTreePushTag("TAP_0311.LatestCallTimeStamp");

    //TotalCharge
    asnTreeAddInteger("TAP_0311.TotalCharge.TotalCharge", decimalToLong(totalChargeValue[0])); 

      //TotalChargeRefund
    if ( totalChargeValueRefund[0] > 0.0) 
	  asnTreeAddInteger("TAP_0311.TotalChargeRefund.TotalChargeRefund", decimalToLong( trunc(totalChargeValueRefund[0])));

    if ( theTotalTaxValueRefund > 0.0 )
	  asnTreeAddInteger("TAP_0311.TotalTaxRefund.TotalTaxRefund", decimalToLong(trunc(theTotalTaxValueRefund)));//present only if >0

	asnTreeAddInteger("TAP_0311.TotalTaxValue.TotalTaxValue", decimalToLong( trunc(theTotalTaxValue)));
	asnTreeAddInteger("TAP_0311.TotalDiscountValue.TotalDiscountValue",
			 decimalToLong( trunc(theTotalDiscountValue) ) );

        if ( theTotalDiscountRefund > 0.0 )
	    asnTreeAddInteger("TAP_0311.TotalDiscountRefund.TotalDiscountRefund", decimalToLong(trunc(theTotalDiscountRefund)));//present only if >0

//////////////////////////TotalAdvisedChargeValue/////////////////////////////////////
        // Add TotalAdvisedChargeValue if advisedChargeDetectedFlag is true
        if ( advisedChargeDetectedFlag == true )
        {
            asnTreePushTag("TAP_0311.TotalAdvisedChargeValueList");
            
            Long i;
            for (i=0 ; (i<totalAdvisedChargeCurrencyEntries); i=i+1)
            {
                asnTreePushTag("TAP_0311.TotalAdvisedChargeValue");

                if ( advisedChargeCurrency[i] != "")
                    asnTreeAddString("TAP_0311.AdvisedChargeCurrency.AdvisedChargeCurrency", advisedChargeCurrency[i]);

                if ( totalAdvisedCharge[i] > 0.0 )
                    asnTreeAddInteger("TAP_0311.TotalAdvisedCharge.TotalAdvisedCharge", decimalToLong( trunc(totalAdvisedCharge[i])));

                if ( totalAdvisedChargeRefund[i] > 0.0 )
                    asnTreeAddInteger("TAP_0311.TotalAdvisedChargeRefund.TotalAdvisedChargeRefund", decimalToLong( trunc(totalAdvisedChargeRefund[i])));

                if ( totalCommission[i] > 0.0 )
                    asnTreeAddInteger("TAP_0311.TotalCommission.TotalCommission", decimalToLong( trunc(totalCommission[i])));

                if ( totalCommissionRefund[i] > 0.0 )
                    asnTreeAddInteger("TAP_0311.TotalCommissionRefund.TotalCommissionRefund", decimalToLong( trunc(totalCommissionRefund[i])));

                asnTreePop(); //asnTreePushTag("TAP_0311.TotalAdvisedChargeValue");

            }

            asnTreePop(); //asnTreePushTag("TAP_0311.TotalAdvisedChargeValueList");
        }
		
//////////////////////////////////////////////////////////////////////////////////////
	asnTreeAddInteger("TAP_0311.CallEventDetailsCount.CallEventDetailsCount", nbWrittenDetails);
        addOperatorSpecInfoList(edrString(TRAILER.OPERATOR_SPECIFIC_INFO));
	asnTreePop(); //asnTreePushTag("TAP_0311.AuditControlInfo");
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

//logStdout("TAP_0311.DETAIL.STD_MAPPING "+recordNum+" (Type:"+recordType+")\n");
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
