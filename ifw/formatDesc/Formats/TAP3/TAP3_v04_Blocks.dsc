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
//   Description of the TAP3_v04 CDR format
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
// $RCSfile: TAP3_v04_Blocks.dsc,v $
// $Revision: 1.5 $
// $Author: cdiab $
// $Date: 2001/11/21 12:19:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TAP3_v04_Blocks.dsc,v $
// Revision 1.5  2001/11/21 12:19:24  cdiab
// PETS #41923 : add "real" parsing of ContentTransaction block for tap3
// -on input, the grammar is now set to parse the ContentTransaction record
// (and not just skip it). But we still do not store the data.
//
// Revision 1.4  2001/10/11 12:14:45  cdiab
// PETS #40345: in TAP3 Audit block, INTEGERS can up to 8 bytes
// we now use the ASN_HexString type to manage them and read them directly as Decimal.
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
// Revision 1.5  2001/07/26 09:25:08  cdiab
// PETS #37417 : ability to read Hex strings in Ascii strings.
// The HexString type in Tap3 is used to read string in Ascii but containing
// a Hex representation. the modification of the ASN_HexString type does that one
// more time (ie reads every byte as Hexa, and translates it to Ascii).
// Therefore all usage of ASN_HexString is replaced by use of TAP_AsciiString.
//
// Revision 1.0  2001/05/18 11:38:03  cdiab
// - Creation
//
//==============================================================================

IFW_TAP3
{
  Block_END(FIX)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Pattern = "\0\0";
    }
    dummy AscString(2);
  }
  
  FileFiller(FIX)
  {
    Info
    {
      States = (STATE_TAP3);
      Pattern = "\0";
    }
    dummy AscString(1);
  }

  //----------------------------------------------------------------------------
  TransferBatch(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 1;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Notification(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 2;
      EndRecord   = Block_END;
    }
  }       

  //----------------------------------------------------------------------------
  CallEventDetailList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 3;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  BatchControlInfo(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 4;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  AccountingInfo(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 5;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  NetworkInfo(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 6;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  VasInfo(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 7;
      EndRecord   = Block_END;
    }
  }
        
  //----------------------------------------------------------------------------
  MessageDescriptionInfo(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 8;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  MobileOriginatedCall(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 9;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  MobileTerminatedCall(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 10;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  SupplServiceEvent(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 11;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ServiceCentreUsage(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 12;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ValueAddedService(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 13;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsCall(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 14;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  AuditControlInfo(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 15;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  LocalTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    LOCAL_TIME_STAMP                   ASN_NumberString(16, "Application" /*, 14, 14 */ );
  }

  //----------------------------------------------------------------------------
  AccessPointName(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ACCESS_POINT_NAME                  TAP_AsciiString(32, "Application");
  }

  //----------------------------------------------------------------------------
  AccessPointNameNI(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ACCESS_POINT_NAME_NI               TAP_AsciiString(261, "Application");
  }

  //----------------------------------------------------------------------------
  AccessPointNameOI(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ACCESS_POINT_NAME_OI               TAP_AsciiString(262, "Application");
  }

  //----------------------------------------------------------------------------
  AddressStringDigits(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ADDRESS_STRING_DIGITS              ASN_BcdString(33, "Application");
  }

  //----------------------------------------------------------------------------
  AiurRequested(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    AIUR_REQUESTED                     ASN_Integer(34, "Application");
  }

  //----------------------------------------------------------------------------
  BasicHSCSDParameters(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 35;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  BasicService(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 36;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  BasicServiceCodeList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 37;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  BasicServiceUsedList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 38;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  BasicServiceUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 39;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  BearerServiceCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    BEARER_SERVICE_CODE                TAP_AsciiString(40, "Application");
//    BEARER_SERVICE_CODE                ASN_HexString(40, "Application");
  }

  //----------------------------------------------------------------------------
  CallOriginator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 41;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CalledPlace(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALLED_PLACE                       TAP_AsciiString(42, "Application");
  }

  //----------------------------------------------------------------------------
  CallEventDetailsCount(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALL_EVENT_DETAIL_COUNT            ASN_Integer(43, "Application");
  }

  //----------------------------------------------------------------------------
  CallEventStartTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 44;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CallReference(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALL_REFERENCE                     ASN_HexString(45, "Application"); //to access as Decimal
//    CALL_REFERENCE                     ASN_OctetString(45, "Application"); // tap0304 and tap0303
//    CALL_REFERENCE                     ASN_Integer(45, "Application");     // tap0301
  }

  //----------------------------------------------------------------------------
  CalledRegion(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALLED_REGION                      TAP_AsciiString(46, "Application");
  }

  //----------------------------------------------------------------------------
  CallType(ASN)  //removed starting tap0304
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALL_TYPE                          TAP_AsciiString(47, "Application");
  }
  CallTypeSubtype(ASN)  //removed starting tap0304
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALL_TYPE_SUBTYPE                  TAP_AsciiString(48, "Application");
  }
  
  //----------------------------------------------------------------------------
  CallTypeGroup(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 258;
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------
  CallTypeLevel1(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALL_TYPE_LEVEL                    ASN_Integer(259, "Application");
  }
  //----------------------------------------------------------------------------
  CallTypeLevel2(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALL_TYPE_LEVEL                    ASN_Integer(255, "Application");
  }
  //----------------------------------------------------------------------------
  CallTypeLevel3(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALL_TYPE_LEVEL                    ASN_Integer(256, "Application");
  }
  //----------------------------------------------------------------------------
  CalledCountryCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALLED_COUNTRY_CODE                ASN_NumberString(257, "Application");
  }

  //----------------------------------------------------------------------------
  CamelCallReference(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 49;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CamelCallReferenceNumber(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CAMEL_CALL_REFERENCE_NUMBER        TAP_AsciiString(50, "Application");
//    CAMEL_CALL_REFERENCE_NUMBER        ASN_HexString(50, "Application");
  }

  //----------------------------------------------------------------------------
  CamelDestination(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 51;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CamelInitiatedCFIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CAMEL_INITIATED_CF_INDICATOR       ASN_Integer(52, "Application");
  }

  //----------------------------------------------------------------------------
  CamelModification(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CAMEL_MODIFICATION                 ASN_Integer(53, "Application");
  }

  //----------------------------------------------------------------------------
  CamelModificationList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 54;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CamelServiceKey(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CAMEL_SERVICE_KEY                  ASN_Integer(55, "Application");
  }

  //----------------------------------------------------------------------------
  CamelServiceLevel(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CAMEL_SERVICE_LEVEL                ASN_Integer(56, "Application");
  }

  //----------------------------------------------------------------------------
  CamelServiceUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 57;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CauseForTerm(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CAUSE_FOR_TERM                     ASN_Integer(58, "Application");
  }

  //----------------------------------------------------------------------------
  CellId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CELL_ID                            ASN_Integer(59, "Application");
  }

  //----------------------------------------------------------------------------
  ChannelCoding(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHANNEL_CODING                     ASN_Integer(60, "Application");
  }

  //----------------------------------------------------------------------------
  ChannelCodingsAcceptable(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 61;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Charge(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGE                             ASN_Integer(62, "Application");
  }

  //----------------------------------------------------------------------------
  ChargeDetail(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 63;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargeDetailList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 64;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargeableUnits(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGEABLE_UNITS                   ASN_Integer(65, "Application");
  }

  //----------------------------------------------------------------------------
  ChargedItem(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGED_ITEM                       TAP_AsciiString(66, "Application");
  }

  //----------------------------------------------------------------------------
  ChargedPartyStatus(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGED_PARTY_STATUS               ASN_Integer(67, "Application");
  }

  //----------------------------------------------------------------------------
  ChargedUnits(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGED_UNITS                      ASN_Integer(68, "Application");
  }

  //----------------------------------------------------------------------------
  ChargeInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 69;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargeInformationList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 70;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargeType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGE_TYPE                        ASN_NumberString(71, "Application");
  }

  //----------------------------------------------------------------------------
  ChargingId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGING_ID                        ASN_HexString(72, "Application"); //to access as Decimal
//    CHARGING_ID                        ASN_Integer(72, "Application"); //tap0304 and tap0301
//    CHARGING_ID                        ASN_OctetString(72, "Application"); //tap0303
  }

  //----------------------------------------------------------------------------
  ChargingPoint(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGING_POINT                     TAP_AsciiString(73, "Application");
  }

  //----------------------------------------------------------------------------
  ChargingCharacteristics(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGING_CHARACTERISTICS           ASN_HexString(263, "Application");
  }

  //----------------------------------------------------------------------------
  ChargingTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 74;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ClirIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CLIR_INDICATOR                     ASN_Integer(75, "Application");
  }

  //----------------------------------------------------------------------------
  CompletionTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 76;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CountryCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    COUNTRY_CODE                       ASN_NumberString(77, "Application");
  }

  //----------------------------------------------------------------------------
  CountryCodeTable(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 78;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CseInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CSE_INFORMATION                    TAP_AsciiString(79, "Application");
  }

  //----------------------------------------------------------------------------
  CurrencyConversion(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 80;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  DataVolume(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DATA_VOLUME                        ASN_Integer(81, "Application");
  }

  //----------------------------------------------------------------------------
  DataVolumeReference(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DATA_VOLUME_REFERENCE              ASN_Integer(82, "Application");
  }

  //----------------------------------------------------------------------------
  DateTime(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 83;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  DateTimeLong(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 84;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  DayCategory(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DAY_CATEGORY                       TAP_AsciiString(85, "Application");
  }

  //----------------------------------------------------------------------------
  DayCategorySubtype(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DAY_CATEGORY_SUBTYPE               TAP_AsciiString(86, "Application");
  }

  //----------------------------------------------------------------------------
  DefaultCallHandlingIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DEFAULT_CALL_HANDLING_INDICATOR    ASN_Integer(87, "Application");
  }

  //----------------------------------------------------------------------------
  DepositTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 88;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Destination(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 89;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  DestinationNetwork(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NETWORK_ID                         TAP_AsciiString(90, "Application");
  }

  //----------------------------------------------------------------------------
  DiscountCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DISCOUNT_CODE                      ASN_Integer(91, "Application");
  }

  //----------------------------------------------------------------------------
  DiscountRate(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PERCENTAGE_RATE                    TAP_PercentageRate(92, "Application");
  }

  //----------------------------------------------------------------------------
  DiscountValue(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ABSOLUTE_AMOUNT                    ASN_Integer(93, "Application");
  }

  //----------------------------------------------------------------------------
  DiscountDefinition(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 94;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Discounting(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 95;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  DiscountInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 96;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  DistanceChargeBandCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DISTANCE_CHARGE_BAND_CODE          TAP_AsciiString(98, "Application");
  }

  //----------------------------------------------------------------------------
  DualBearerServiceCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    DUAL_BEARER_SERVICE_CODE           TAP_AsciiString(99, "Application");
//    DUAL_BEARER_SERVICE_CODE           ASN_HexString(99, "Application");
  }

  //----------------------------------------------------------------------------
  DualTeleServiceCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    DUAL_TELE_SERVICE_CODE             TAP_AsciiString(100, "Application");
//    DUAL_TELE_SERVICE_CODE             ASN_HexString(100, "Application");
  }

  //----------------------------------------------------------------------------
  EarliestCallTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 101;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  EquipmentInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 102;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Esn(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ESN                                ASN_NumberString(103, "Application");
  }

  //----------------------------------------------------------------------------
  ExchangeRate(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    EXCHANGE_RATE                      ASN_Integer(104, "Application");
  }

  //----------------------------------------------------------------------------
  ExchangeRateCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CODE                               ASN_Integer(105, "Application");
  }

  //----------------------------------------------------------------------------
  ExchangeRateDefinition(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 106;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  FileAvailableTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 107;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  FileCreationTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 108;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  FileSequenceNumber(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    FILE_SEQUENCE_NUMBER               ASN_NumberString(109, "Application");    
  }

  //----------------------------------------------------------------------------
  FileTypeIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    FILE_TYPE_INDICATOR                TAP_AsciiString(110, "Application");    
  }

  //----------------------------------------------------------------------------
  Fnur(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    FNUR                               ASN_Integer(111, "Application");
  }

  //----------------------------------------------------------------------------
  FraudMonitorIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    FRAUD_MONITOR_INDICATOR            TAP_AsciiString(112, "Application");
  }

  //----------------------------------------------------------------------------
  GeographicalLocation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 113;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsBasicCallInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 114;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsChargeableSubscriber(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 115;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsDestination(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 116;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsLocationInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 117;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsNetworkLocation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 118;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsServiceUsage(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 119;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsServiceUsageList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 120;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GprsServiceUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 121;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  HomeBid(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    HOME_BID                           TAP_AsciiString(122, "Application");
  }

  //----------------------------------------------------------------------------
  HomeLocationInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 123;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  HSCSDInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 124;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  HSCSDParameterModification(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 125;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  HSCSDParameterModificationList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 140;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Iac(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    IAC                                ASN_NumberString(126, "Application");
  }

  //----------------------------------------------------------------------------
  IacTable(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 127;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Imei(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    IMEI                               ASN_BcdString(128, "Application");
  }

  //----------------------------------------------------------------------------
  Imsi(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    IMSI                               ASN_BcdString(129, "Application");
  }

  //----------------------------------------------------------------------------
  InitiatingParty(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    INITIATING_PARTY                   ASN_Integer(130, "Application");
  }

  //----------------------------------------------------------------------------
  IPTextV4Address(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    IP_TEXT_V4_ADDRESS                 TAP_AsciiString(131, "Application");
  }

  //----------------------------------------------------------------------------
  IPTextV6Address(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    IP_TEXT_V6_ADDRESS                 TAP_AsciiString(132, "Application");
  }


  //----------------------------------------------------------------------------
  LatestCallTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 133;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Latitude(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    LATITUDE                           ASN_Integer(134, "Application");
  }

  //----------------------------------------------------------------------------
  LocalCurrency(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CURRENCY                           TAP_Currency(135, "Application");
  }

  //----------------------------------------------------------------------------
  LocationArea(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    LOCATION_AREA                      ASN_Integer(136, "Application");
  }

  //----------------------------------------------------------------------------
  LocationDescription(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    LOCATION_DESCRIPTION               TAP_AsciiString(137, "Application");
  }

  //----------------------------------------------------------------------------
  LocationInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 138;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Longitude(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    LONGITUDE                          ASN_Integer(139, "Application");
  }

  //----------------------------------------------------------------------------
  Mdn(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MDN                                ASN_NumberString(253, "Application");
  }  

  //----------------------------------------------------------------------------
  MessageDescriptionCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MESSAGE_DESCRIPTION_CODE           ASN_Integer(141, "Application");
  }

  //----------------------------------------------------------------------------
  MessageDescription(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MESSAGE_DESCRIPTION                TAP_AsciiString(142, "Application");
  }

  //----------------------------------------------------------------------------
  MessageDescriptionDefinition(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 143;
      EndRecord   = Block_END;
    }
  }  

  //----------------------------------------------------------------------------
  MessageStatus(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MESSAGE_STATUS                     ASN_Integer(144, "Application");
  }  

  //----------------------------------------------------------------------------
  MessageType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MESSAGE_TYPE                       ASN_Integer(145, "Application");
  }  

  //----------------------------------------------------------------------------
  Min(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MIN                                ASN_NumberString(146, "Application");
  }  

  //----------------------------------------------------------------------------
  MinChargeableSubscriber(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 254;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  MoBasicCallInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 147;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  MobileStationClassMark(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MOBILE_STATION_CLASS_MARK           ASN_Integer(148, "Application");
  }

  //----------------------------------------------------------------------------
  ModificationIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MODIFICATION_INDICATOR             ASN_Integer(149, "Application");
  }


  //----------------------------------------------------------------------------
  ModificationTimestamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 150;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  MscId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MSC_ID                             TAP_AsciiString(151, "Application");
  }

  //----------------------------------------------------------------------------
  Msisdn(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MSISDN                             ASN_BcdString(152, "Application");
  }

  //----------------------------------------------------------------------------
  MtBasicCallInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 153;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  MultiRateIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    MULTI_RATE_INDICATOR               ASN_Integer(154, "Application");
  }

  //----------------------------------------------------------------------------
  NetworkId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NETWORK_ID                         TAP_AsciiString(155, "Application");
  }

  //----------------------------------------------------------------------------
  NetworkLocation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 156;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  NetworkType(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    NETWORK_TYPE                       ASN_Integer(157, "Application");
  }

  //----------------------------------------------------------------------------
  NonChargedParty(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 158;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  NumberOfDecimalPlaces(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NUMBER_OF_DECIMAL_PLACES           ASN_Integer(159, "Application");
  }

  //----------------------------------------------------------------------------
  NumberingPlan(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NUMBERING_PLAN                     ASN_Integer(160, "Application");
  }

  //----------------------------------------------------------------------------
  NumberOfChannels(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NUMBER_OF_CHANNELS                 ASN_Integer(161, "Application");
  }

  //----------------------------------------------------------------------------
  OperatorSpecInfoList(ASN) // added in tap0304
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 162;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  OperatorSpecInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    OPERATOR_SPEC_INFORMATION          TAP_AsciiString(163, "Application");
  }

  //----------------------------------------------------------------------------
  OriginatingNetwork(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NETWORK_ID                         TAP_AsciiString(164, "Application");
  }

  //----------------------------------------------------------------------------
  PacketDataProtocollAddress(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PACKET_DATA_PROTOCOLL_ADDRESS      TAP_AsciiString(165, "Application");
  }

  //----------------------------------------------------------------------------
  PartialTypeIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PARTIAL_TYPE_INDICATOR             TAP_AsciiString(166, "Application");
  }

  //----------------------------------------------------------------------------
  PdpAddress(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PDP_ADDRESS                       TAP_AsciiString(167, "Application");
  }

  //----------------------------------------------------------------------------
  PdpType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PDP_TYPE                           ASN_Integer(168, "Application");
  }  

  //----------------------------------------------------------------------------
  PDPContextStartTimestamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 260;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  PlmnId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PLMN_ID                            TAP_AsciiString(169, "Application");
  }  

  //----------------------------------------------------------------------------
  PriorityCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PRIORITY_CODE                      ASN_Integer(170, "Application");
  }  

  //----------------------------------------------------------------------------
  QoSAllocRetenPriority(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(275, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSDeliveryOrder(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(278, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSErroneousSDUs(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(277, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSHandlingpriority(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(276, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSMaxBitRateUplink(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_BYTE                           ASN_HexString(264, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSMaxBitRateDownlink(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_BYTE                           ASN_HexString(274, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSMaxSDUsize(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_BYTE                           ASN_HexString(265, "Application");
  }
   
  //----------------------------------------------------------------------------
  QoSDelay(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(171, "Application");
  }

  //----------------------------------------------------------------------------
  QoSInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 172;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  QoSMeanThroughput(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(173, "Application");
  }

  //----------------------------------------------------------------------------
  QoSPeakThroughput(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(174, "Application");
  }

  //----------------------------------------------------------------------------
  QoSPrecedence(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(175, "Application");
  }

  //----------------------------------------------------------------------------
  QoSReliability(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(176, "Application");
  }

  //----------------------------------------------------------------------------
  QoSRequested(ASN)  //removed starting tap0304
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 177;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  QoSUsed(ASN)  //removed starting tap0304
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 178;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  QoSResidualBER(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(266, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSSDUErrorRatio(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(267, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSTrafficClass(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_INTEGER                        ASN_Integer(268, "Application");
  }
  
  //----------------------------------------------------------------------------
  QoSTransferDelay(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    QOS_BYTE                           ASN_HexString(269, "Application");
  }
  
  //----------------------------------------------------------------------------
  GSMQoSRequested(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 272;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  GSMQoSUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 273;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  UMTSQoSRequested(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 270;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  UMTSQoSUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 271;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  RadioChannelRequested(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    RADIO_CHANNEL_REQUESTED            ASN_Integer(179, "Application");
  }

  //----------------------------------------------------------------------------
  RadioChannelUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    RADIO_CHANNEL_USED                 ASN_Integer(180, "Application");
  }

  //----------------------------------------------------------------------------
  RapFileSequenceNumber(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    FILE_SEQUENCE_NUMBER               TAP_AsciiString(181, "Application");
  }

  //----------------------------------------------------------------------------
  RecEntityDefinition(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 183;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  RecEntityCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    REC_ENTITY_CODE                    ASN_Integer(184, "Application");
  }

  //----------------------------------------------------------------------------
  RecEntityCodeList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 185;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  RecEntityType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    REC_ENTITY_TYPE                    ASN_Integer(186, "Application");
  }

  //----------------------------------------------------------------------------
  RecEntityTable(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 188;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Recipient(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    PLMN_ID                            TAP_AsciiString(182, "Application" /*, 5, 5 */);
  }

  //----------------------------------------------------------------------------
  ReleaseVersionNumber(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    RELEASE_VERSION_NUMBER             ASN_Integer(189, "Application");
  }

  //----------------------------------------------------------------------------
  RemotePdpAddressList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 190;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ScuBasicInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 191;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ScuChargeType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 192;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ScuTimeStamps(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 193;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  Sender(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    PLMN_ID                            TAP_AsciiString(196, "Application" /*, 5, 5 */);
  }

  //----------------------------------------------------------------------------
  ServiceCenterIdentity(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 197;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ServingBid(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    SERVING_BID                        TAP_AsciiString(198, "Application");
  }

  //----------------------------------------------------------------------------
  ServingNetwork(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    SERVING_NETWORK                    TAP_AsciiString(195, "Application");
  }

  //----------------------------------------------------------------------------
  SimChargeableSubscriber(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 199;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  SimToolkitIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    SIM_TOOLKIT_INDICATOR              TAP_AsciiString(200, "Application");
  }

  //----------------------------------------------------------------------------
  SpecificationVersionNumber(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    SPECIFICATION_VERSION_NUMBER        ASN_Integer(201, "Application");
  }


  //----------------------------------------------------------------------------
  SpeechVersionRequested(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    SPEECH_VERSION_REQUESTED           ASN_Integer(202, "Application");
  }

  //----------------------------------------------------------------------------
  SpeechVersionUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    SPEECH_VERSION_USED                ASN_Integer(203, "Application");
  }

  //----------------------------------------------------------------------------
  SsParameters(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    SS_PARAMETERS                      TAP_AsciiString(204, "Application");
  }

  //----------------------------------------------------------------------------
  SupplServiceUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 206;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  SupplServiceUsedList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 207;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  SupplServiceActionCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    SUPPL_SERVICE_ACTION_CODE          ASN_Integer(208, "Application");
  }

  //----------------------------------------------------------------------------
  SupplServiceCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    SUPPL_SERVICE_CODE                 TAP_AsciiString(209, "Application");
//    SUPPL_SERVICE_CODE                 ASN_HexString(209, "Application");
  }

  //----------------------------------------------------------------------------
  TapCurrency(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TAP_CURRENCY                       TAP_Currency(210, "Application");
  }

  //----------------------------------------------------------------------------
  Taxation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 211;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TaxCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TAX_CODE                           ASN_Integer(212, "Application");
  }

  //----------------------------------------------------------------------------
  TaxInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 213;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TaxInformationList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 214;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TaxRate(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }   
    TAX_RATE                           ASN_NumberString(215, "Application");
  }

  //----------------------------------------------------------------------------
  TaxRateDefinition(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 216;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TaxType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TAX_TYPE                           TAP_AsciiString(217, "Application");
  }

  //----------------------------------------------------------------------------
  TeleServiceCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TELE_SERVICE_CODE                  TAP_AsciiString(218, "Application");
//    TELE_SERVICE_CODE                  ASN_HexString(218, "Application");
  }

  //----------------------------------------------------------------------------
  ThirdPartyInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 219;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TimeBand(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TIME_BAND                          TAP_AsciiString(220, "Application");
  }

  //----------------------------------------------------------------------------
  TimeBandSubtype(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TIME_BAND_SUBTYPE                  TAP_AsciiString(221, "Application");
  }

  //----------------------------------------------------------------------------
  TotalAdvisedChargeValue(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 360;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TotalAdvisedChargeValueList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 361;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  AdvisedChargeCurrency(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ADVISED_CHARGE_CURRENCY            TAP_Currency(348, "Application");
  }
  //----------------------------------------------------------------------------
  TotalChargeRefund(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_CHARGE_REFUND		       ASN_HexString(355, "Application"); //to access it as Decimal
//    TOTAL_CHARGE_REFUND                ASN_Integer(355, "Application");
  }
  //----------------------------------------------------------------------------
  TotalAdvisedCharge(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_ADVISED_CHARGE	       ASN_HexString(356, "Application"); //to access it as Decimal
//    TOTAL_ADVISED_CHARGE               ASN_Integer(356, "Application");
  }
  //----------------------------------------------------------------------------
  TotalAdvisedChargeRefund(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_ADVISED_CHARGE_REFUND	       ASN_HexString(357, "Application"); //to access it as Decimal
//    TOTAL_ADVISED_CHARGE_REFUND        ASN_Integer(357, "Application");
  }
  //----------------------------------------------------------------------------
  TotalCommission(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_COMMISSION		       ASN_HexString(358, "Application"); //to access it as Decimal
//    TOTAL_COMMISSION                   ASN_Integer(358, "Application");
  }
  //----------------------------------------------------------------------------
  TotalCommissionRefund(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_COMMISSION_REFUND	       ASN_HexString(359, "Application"); //to access it as Decimal
//    TOTAL_COMMISSION_REFUND            ASN_Integer(359, "Application");
  }

  //----------------------------------------------------------------------------
  TotalChargeValue(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 222;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TotalCallEventDuration(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_CALL_EVENT_DURATION          ASN_Integer(223, "Application");
  }

  //----------------------------------------------------------------------------
  TotalChargeValueList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 224;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TotalDiscountValue(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_DISCOUNT_VALUE	       ASN_HexString(225, "Application"); //to access it as Decimal
//    TOTAL_DISCOUNT_VALUE               ASN_Integer(225, "Application");
  }

  //----------------------------------------------------------------------------
  TotalDiscountRefund(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_DISCOUNT_REFUND	       ASN_HexString(354, "Application"); //to access it as Decimal
//    TOTAL_DISCOUNT_REFUND               ASN_Integer(354, "Application");
  }

  //----------------------------------------------------------------------------
  TotalTaxValue(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_TAX_VALUE		       ASN_HexString(226, "Application"); //to access it as Decimal
//    TOTAL_TAX_VALUE                    ASN_Integer(226, "Application");
  }

  //----------------------------------------------------------------------------
  TotalTaxRefund(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_TAX_REFUND		       ASN_HexString(353, "Application"); //to access it as Decimal
//    TOTAL_TAX_REFUND                    ASN_Integer(353, "Application");
  }
  
  //----------------------------------------------------------------------------
  TransferCutOffTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 227;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TransparencyIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TRANSPARENCY_INDICATOR             ASN_Integer(228, "Application");
  }

  //----------------------------------------------------------------------------
  TypeOfControllingNode(ASN)
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    TYPE_OF_CONTROLLING_NODE           ASN_Integer(229, "Application");
  }

  //----------------------------------------------------------------------------
  TypeOfNumber(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TYPE_OF_NUMBER                     ASN_Integer(230, "Application");
  }

  //----------------------------------------------------------------------------
  UtcTimeOffset(ASN) 
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
    }
    UTC_TIME_OFFSET                    TAP_AsciiString(231, "Application");
  }

  //----------------------------------------------------------------------------
  UtcTimeOffsetCode(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
    }
    UTC_TIME_OFFSET_CODE               ASN_Integer(232, "Application");
  }

  //----------------------------------------------------------------------------
  UtcTimeOffsetDefinition(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 233;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  UtcTimeOffsetInfo(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 234;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ValueAddedServiceUsedList(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 235;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ValueAddedServiceUsed(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 236;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  VasCode(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
    }
    VAS_CODE                               ASN_Integer(237, "Application");
  }

  //----------------------------------------------------------------------------
  VasDefinition(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 238;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  VasDescription(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
    }
    VAS_DESCRIPTION                    TAP_Description(239, "Application");
  }

  //----------------------------------------------------------------------------
  VasShortDescription(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
    }
    VAS_SHORT_DESCRIPTION              TAP_Description(240, "Application");
  }

  //----------------------------------------------------------------------------
  AbsoluteAmount(ASN) 
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ABSOLUTE_AMOUNT                    ASN_HexString(241, "Application"); //to access it as Decimal
//    ABSOLUTE_AMOUNT                    ASN_Integer(241, "Application");
  }

  //----------------------------------------------------------------------------
  TapDecimalPlaces(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TAP_DECIMAL_PLACES                 ASN_Integer(244, "Application");
  }

  //----------------------------------------------------------------------------
  NetworkInitPDPContext(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NETWORK_INIT_PDP_CONTEXT           ASN_Integer(245, "Application");
  }

  //----------------------------------------------------------------------------
  CalledNumAnalysis(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 246;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  CalledNumAnalysisCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CALLED_NUM_ANALYSIS_CODE           ASN_Integer(247, "Application");
  }

  //----------------------------------------------------------------------------
  CalledNumAnalysisList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 249;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  DataVolumeIncoming(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DATA_VOLUME_INCOMING               ASN_Integer(250, "Application");
  }

  //----------------------------------------------------------------------------
  DataVolumeOutgoing(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    DATA_VOLUME_OUTGOING               ASN_Integer(251, "Application");
  }

  //----------------------------------------------------------------------------
  NumberOfChannelsUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NUMBER_OF_CHANNELS_USED            ASN_Integer(252, "Application");
  }

  //============================================================================
  // Fields added for the ContentTransaction record
  //============================================================================

  //----------------------------------------------------------------------------
  ContentTransaction(ASN) // new record type for tap0304
  {
    Info
    {
      States = (STATE_TAP3, RapState_01_01);
      Application = 17;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ContentTransactionBasicInfo(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 304;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargedPartyInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 324;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ServingPartiesInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 335;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ContentServiceUsed(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 352;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  OrderPlacementTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 300;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  RequestedDeliveryTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 301;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ActualDeliveryTimeStamp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 302;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  TransactionStatus(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TRANSACTION_STATUS                 ASN_Integer(303, "Application");
  }

  //----------------------------------------------------------------------------
  ChargedPartyEquipment(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 323;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  EquipmentIdType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    EQUIPMENT_ID_TYPE                  ASN_Integer(322, "Application");
  }
  
  //----------------------------------------------------------------------------
  ChargedPartyLocation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 320;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargedPartyLocationList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 321;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  LocationIdType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    LOCATION_ID_TYPE                   ASN_Integer(315, "Application");
  }
  
  //----------------------------------------------------------------------------
  CountryName(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    COUNTRY_NAME                       TAP_AsciiString(316, "Application");
  }

  //----------------------------------------------------------------------------
  CountryAsciCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    COUNTRY_ASCI_CODE                  TAP_AsciiString(317, "Application");
  }

  //----------------------------------------------------------------------------
  Region(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    REGION                             TAP_AsciiString(318, "Application");
  }

  //----------------------------------------------------------------------------
  Place(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PLACE                              TAP_AsciiString(319, "Application");
  }

  //----------------------------------------------------------------------------
  ChargedPartyHomeId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 313;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargedPartyHomeIdList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 314;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  HomeIdType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    HOME_ID_TYPE                       ASN_Integer(311, "Application");
  }
  
  //----------------------------------------------------------------------------
  Name(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NAME                               TAP_AsciiString(312, "Application");
  }
  
  //----------------------------------------------------------------------------
  ChargedPartyId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 309;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargedPartyIdList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 310;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ChargedPartyIdType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGED_PARTY_ID_TYPE              ASN_Integer(305, "Application");
  }
  
  //----------------------------------------------------------------------------
  LoginName(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    LOGIN_NAME                         TAP_AsciiString(306, "Application");
  }
  
  //----------------------------------------------------------------------------
  AccountNumber(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ACCOUNT_NUMBER                     TAP_AsciiString(307, "Application");
  }
  
  //----------------------------------------------------------------------------
  EmailAddress(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    EMAIL_ADDRESS                      TAP_AsciiString(308, "Application");
  }
  
  //----------------------------------------------------------------------------
  ContentProviderName(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CONTENT_PROVIDER_NAME              TAP_AsciiString(334, "Application");
  }
  
  //----------------------------------------------------------------------------
  ContentProviderId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 327;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ContentProviderIdList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 328;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  ProviderIdType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PROVIDER_ID_TYPE                   ASN_Integer(325, "Application");
  }
  
  //----------------------------------------------------------------------------
  Url(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    URL                                TAP_AsciiString(326, "Application");
  }

  //----------------------------------------------------------------------------
  InternetServiceProviderId(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 329;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  InternetServiceProviderIdList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 330;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  NetworkIdGroup(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 332;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  NetworkIdList(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 333;
      EndRecord   = Block_END;
    }
  }
  
  //----------------------------------------------------------------------------
  NetworkIdType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    NETWORK_ID_TYPE                   ASN_Integer(331, "Application");
  }
  
  //----------------------------------------------------------------------------
  ContentTransactionCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CONT_CODE                          ASN_Integer(336, "Application");
  }
  
  //----------------------------------------------------------------------------
  ContentTransactionType(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CONT_TYPE                          ASN_Integer(337, "Application");
  }
  
  //----------------------------------------------------------------------------
  TransactionDescriptionSupp(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TRANS_DESCR_SUPP                   ASN_Integer(338, "Application");
  }
  
  //----------------------------------------------------------------------------
  TransactionDetailDescription(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TRANS_DETAIL_DESCR                 TAP_AsciiString(339, "Application");
  }
  
  //----------------------------------------------------------------------------
  TransactionShortDescription(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TRANS_SHORT_DESCR                  TAP_AsciiString(340, "Application");
  }
  
  //----------------------------------------------------------------------------
  TransactionIdentifier(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TRANS_IDENTIFIER                   TAP_AsciiString(341, "Application");
  }
  
  //----------------------------------------------------------------------------
  TransactionAuthCode(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TRANS_AUTH_CODE                    TAP_AsciiString(342, "Application");
  }

  //----------------------------------------------------------------------------
  TotalDataVolume(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    TOTAL_DATA_VOLUME                  ASN_Integer(343, "Application");
  }
  
  //----------------------------------------------------------------------------
  ChargeRefundIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CHARGE_REFUND_INDICATOR            ASN_Integer(344, "Application");
  }
  
  //----------------------------------------------------------------------------
  ContentChargingPoint(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    CONTENT_CHARGING_POINT             ASN_Integer(345, "Application");
  }

  //----------------------------------------------------------------------------
  PaidIndicator(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PAID_INDICATOR                     ASN_Integer(346, "Application");
  }

  //----------------------------------------------------------------------------
  PaymentMethod(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    PAYMENT_METHOD                     ASN_Integer(347, "Application");
  }

  //----------------------------------------------------------------------------
  AdvisedCharge(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    ADVISED_CHARGE                     ASN_Integer(349, "Application");
  }

  //----------------------------------------------------------------------------
  Commission(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
    }
    COMMISSION                         ASN_Integer(350, "Application");
  }

  //----------------------------------------------------------------------------
  AdvisedChargeInformation(ASN)
  {
    Info
    {
      States = (STATE_TAP3);
      Application = 351;
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
}
