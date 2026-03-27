//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

TAP_0311
{
  AbsoluteAmount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AbsoluteAmount ASN_Integer(2, "Universal"); 
  }                      
                         
  AccessPointNameNI(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AccessPointNameNI TAP_AsciiString(261, "Application"); 
  }                      
                         
  AccessPointNameOI(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AccessPointNameOI TAP_AsciiString(262, "Application"); 
  }                      
                         
  AccountingInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 5; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ActualDeliveryTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 302; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  AddressStringDigits(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AddressStringDigits ASN_BcdString(4, "Universal"); 
  }                      
                         
  AdvisedCharge(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AdvisedCharge ASN_Integer(349, "Application"); 
  }                      
                         
  AdvisedChargeCurrency(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AdvisedChargeCurrency TAP_AsciiString(348, "Application"); 
  }                      
                         
  AdvisedChargeInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 351; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  AgeOfLocation(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AgeOfLocation ASN_Integer(396, "Application"); 
  }                      
                         
  AsciiString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AsciiString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  AuditControlInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 15; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BCDString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    BCDString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  BasicService(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 36; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BasicServiceCode(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 426; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BasicServiceCodeList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 37; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BasicServiceUsed(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 39; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BasicServiceUsedList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 38; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BatchControlInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 4; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BearerServiceCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    BearerServiceCode TAP_AsciiString(40, "Application"); 
  }                      
                         
  CallEventDetailList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 3; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  CallEventDetailsCount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallEventDetailsCount ASN_Integer(43, "Application"); 
  }                      
                         
  CallEventStartTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 44; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  CallOriginator(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 41; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  CallReference(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallReference TAP_AsciiString(45, "Application"); 
  }                      
                         
  CallTypeGroup(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 258; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  CallTypeLevel1(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallTypeLevel1 ASN_Integer(259, "Application"); 
  }                      
                         
  CallTypeLevel2(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallTypeLevel2 ASN_Integer(255, "Application"); 
  }                      
                         
  CallTypeLevel3(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallTypeLevel3 ASN_Integer(256, "Application"); 
  }                      
                         
  CalledNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CalledNumber ASN_BcdString(407, "Application"); 
  }                      
                         
  CalledPlace(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CalledPlace TAP_AsciiString(42, "Application"); 
  }                      
                         
  CalledRegion(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CalledRegion TAP_AsciiString(46, "Application"); 
  }                      
                         
  CallingNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallingNumber ASN_BcdString(405, "Application"); 
  }                      
                         
  CamelDestinationNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CamelDestinationNumber ASN_BcdString(404, "Application"); 
  }                      
                         
  CamelInvocationFee(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CamelInvocationFee ASN_Integer(422, "Application"); 
  }                      
                         
  CamelServiceKey(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CamelServiceKey ASN_Integer(55, "Application"); 
  }                      
                         
  CamelServiceLevel(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CamelServiceLevel ASN_Integer(56, "Application"); 
  }                      
                         
  CamelServiceUsed(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 57; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  CauseForTerm(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CauseForTerm ASN_Integer(58, "Application"); 
  }                      
                         
  CellId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CellId ASN_Integer(59, "Application"); 
  }                      
                         
  Charge(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Charge ASN_Integer(62, "Application", 0, 8); 
  }                      
                         
  ChargeDetail(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 63; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargeDetailList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 64; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargeDetailTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 410; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargeInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 69; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargeInformationList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 70; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargeRefundIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargeRefundIndicator ASN_Integer(344, "Application"); 
  }                      
                         
  ChargeType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargeType TAP_AsciiString(71, "Application"); 
  }                      
                         
  ChargeableSubscriber(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 427; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargeableUnits(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargeableUnits ASN_Integer(65, "Application", 0, 8); 
  }                      
                         
  ChargedItem(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargedItem TAP_AsciiString(66, "Application"); 
  }                      
                         
  ChargedPartyEquipment(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 323; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyHomeIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 314; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyHomeIdentification(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 313; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 310; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargedPartyIdType ASN_Integer(305, "Application"); 
  }                      
                         
  ChargedPartyIdentification(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 309; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargedPartyIdentifier TAP_AsciiString(287, "Application"); 
  }                      
                         
  ChargedPartyInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 324; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyLocation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 320; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyLocationList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 321; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ChargedPartyStatus(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargedPartyStatus ASN_Integer(67, "Application"); 
  }                      
                         
  ChargedUnits(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargedUnits ASN_Integer(68, "Application", 0, 8); 
  }                      
                         
  ChargingId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargingId ASN_Integer(72, "Application", 0, 8); 
  }                      
                         
  ChargingPoint(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargingPoint TAP_AsciiString(73, "Application"); 
  }                      
                         
  ChargingTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 74; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ClirIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ClirIndicator ASN_Integer(75, "Application"); 
  }                      
                         
  Code(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Code ASN_Integer(2, "Universal"); 
  }                      
                         
  Commission(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Commission ASN_Integer(350, "Application"); 
  }                      
                         
  CompletionTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 76; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ContentChargingPoint(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ContentChargingPoint ASN_Integer(345, "Application"); 
  }                      
                         
  ContentProvider(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 327; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ContentProviderIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 328; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ContentProviderIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ContentProviderIdType ASN_Integer(291, "Application"); 
  }                      
                         
  ContentProviderIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ContentProviderIdentifier TAP_AsciiString(292, "Application"); 
  }                      
                         
  ContentProviderName(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ContentProviderName TAP_AsciiString(334, "Application"); 
  }                      
                         
  ContentServiceUsed(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 352; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ContentServiceUsedList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 285; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ContentTransaction(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 17; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ContentTransactionBasicInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 304; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ContentTransactionCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ContentTransactionCode ASN_Integer(336, "Application"); 
  }                      
                         
  ContentTransactionType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ContentTransactionType ASN_Integer(337, "Application"); 
  }                      
                         
  CseInformation(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CseInformation TAP_AsciiString(79, "Application"); 
  }                      
                         
  Currency(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Currency TAP_AsciiString(4, "Universal"); 
  }                      
                         
  CurrencyConversion(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 106; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  CurrencyConversionList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 80; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  CustomerIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CustomerIdType ASN_Integer(363, "Application"); 
  }                      
                         
  CustomerIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CustomerIdentifier TAP_AsciiString(364, "Application"); 
  }                      
                         
  DataVolume(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DataVolume ASN_Integer(2, "Universal"); 
  }                      
                         
  DataVolumeIncoming(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DataVolumeIncoming ASN_Integer(250, "Application", 0, 8); 
  }                      
                         
  DataVolumeOutgoing(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DataVolumeOutgoing ASN_Integer(251, "Application", 0, 8); 
  }                      
                         
  DateTime(ASN)                    
  {                                         
    Info                                    
    {                                       
      Universal = 16; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  DateTimeLong(ASN)                    
  {                                         
    Info                                    
    {                                       
      Universal = 16; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  DefaultCallHandlingIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DefaultCallHandlingIndicator ASN_Integer(87, "Application"); 
  }                      
                         
  DepositTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 88; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  Destination(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 89; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  DestinationNetwork(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DestinationNetwork TAP_AsciiString(90, "Application"); 
  }                      
                         
  DialledDigits(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DialledDigits TAP_AsciiString(279, "Application"); 
  }                      
                         
  Discount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Discount ASN_Integer(412, "Application"); 
  }                      
                         
  DiscountApplied(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 428; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  DiscountCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DiscountCode ASN_Integer(91, "Application"); 
  }                      
                         
  DiscountInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 96; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  DiscountRate(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DiscountRate ASN_Integer(92, "Application"); 
  }                      
                         
  DiscountableAmount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DiscountableAmount ASN_Integer(423, "Application"); 
  }                      
                         
  Discounting(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 94; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  DiscountingList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 95; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  DistanceChargeBandCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DistanceChargeBandCode TAP_AsciiString(98, "Application"); 
  }                      
                         
  EarliestCallTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 101; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  EquipmentId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    EquipmentId TAP_AsciiString(290, "Application"); 
  }                      
                         
  EquipmentIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    EquipmentIdType ASN_Integer(322, "Application"); 
  }                      
                         
  Esn(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Esn TAP_AsciiString(103, "Application"); 
  }                      
                         
  ExchangeRate(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ExchangeRate ASN_Integer(104, "Application"); 
  }                      
                         
  ExchangeRateCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ExchangeRateCode ASN_Integer(105, "Application"); 
  }                      
                         
  FileAvailableTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 107; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  FileCreationTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 108; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  FileSequenceNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    FileSequenceNumber TAP_AsciiString(109, "Application"); 
  }                      
                         
  FileTypeIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    FileTypeIndicator TAP_AsciiString(110, "Application"); 
  }                      
                         
  FixedDiscountValue(ASN) 
  {                      
    Info                 
    {                    
    }                    
    FixedDiscountValue ASN_Integer(411, "Application"); 
  }                      
                         
  Fnur(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Fnur ASN_Integer(111, "Application"); 
  }                      
                         
  GeographicalLocation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 113; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GprsBasicCallInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 114; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GprsCall(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 14; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GprsChargeableSubscriber(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 115; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GprsDestination(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 116; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GprsLocationInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 117; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GprsNetworkLocation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 118; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GprsServiceUsed(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 121; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GsmChargeableSubscriber(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 286; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  GuaranteedBitRate(ASN) 
  {                      
    Info                 
    {                    
    }                    
    GuaranteedBitRate TAP_AsciiString(420, "Application"); 
  }                      
                         
  HSCSDIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HSCSDIndicator TAP_AsciiString(424, "Application"); 
  }                      
                         
  HexString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HexString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  HomeBid(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HomeBid TAP_AsciiString(122, "Application"); 
  }                      
                         
  HomeIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HomeIdType ASN_Integer(311, "Application"); 
  }                      
                         
  HomeIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HomeIdentifier TAP_AsciiString(288, "Application"); 
  }                      
                         
  HomeLocationDescription(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HomeLocationDescription TAP_AsciiString(413, "Application"); 
  }                      
                         
  HomeLocationInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 123; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  HorizontalAccuracyDelivered(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HorizontalAccuracyDelivered ASN_Integer(392, "Application"); 
  }                      
                         
  HorizontalAccuracyRequested(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HorizontalAccuracyRequested ASN_Integer(385, "Application"); 
  }                      
                         
  IMSSignallingContext(ASN) 
  {                      
    Info                 
    {                    
    }                    
    IMSSignallingContext ASN_Integer(418, "Application"); 
  }                      
                         
  ISPList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 378; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  Imei(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Imei ASN_BcdString(128, "Application"); 
  }                      
                         
  ImeiOrEsn(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 429; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  Imsi(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Imsi ASN_BcdString(129, "Application"); 
  }                      
                         
  InternetServiceProvider(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 329; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  InternetServiceProviderIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 330; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  IspIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    IspIdType ASN_Integer(293, "Application"); 
  }                      
                         
  IspIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    IspIdentifier TAP_AsciiString(294, "Application"); 
  }                      
                         
  LCSQosDelivered(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 390; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LCSQosRequested(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 383; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LCSRequestTimestamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 384; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LCSSPIdentification(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 375; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LCSSPIdentificationList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 374; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LCSSPInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 373; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LCSTransactionStatus(ASN) 
  {                      
    Info                 
    {                    
    }                    
    LCSTransactionStatus ASN_Integer(391, "Application"); 
  }                      
                         
  LatestCallTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 133; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LocalCurrency(ASN) 
  {                      
    Info                 
    {                    
    }                    
    LocalCurrency TAP_AsciiString(135, "Application"); 
  }                      
                         
  LocalTimeStamp(ASN) 
  {                      
    Info                 
    {                    
    }                    
    LocalTimeStamp TAP_AsciiString(16, "Application"); 
  }                      
                         
  LocationArea(ASN) 
  {                      
    Info                 
    {                    
    }                    
    LocationArea ASN_Integer(136, "Application"); 
  }                      
                         
  LocationIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    LocationIdType ASN_Integer(315, "Application"); 
  }                      
                         
  LocationIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    LocationIdentifier TAP_AsciiString(289, "Application"); 
  }                      
                         
  LocationInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 138; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LocationService(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 297; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  LocationServiceUsage(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 382; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MaximumBitRate(ASN) 
  {                      
    Info                 
    {                    
    }                    
    MaximumBitRate TAP_AsciiString(421, "Application"); 
  }                      
                         
  Mdn(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Mdn TAP_AsciiString(253, "Application"); 
  }                      
                         
  MessageDescription(ASN) 
  {                      
    Info                 
    {                    
    }                    
    MessageDescription TAP_AsciiString(142, "Application"); 
  }                      
                         
  MessageDescriptionCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    MessageDescriptionCode ASN_Integer(141, "Application"); 
  }                      
                         
  MessageDescriptionInfoList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 8; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MessageDescriptionInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 143; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MessageStatus(ASN) 
  {                      
    Info                 
    {                    
    }                    
    MessageStatus ASN_Integer(144, "Application"); 
  }                      
                         
  MessageType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    MessageType ASN_Integer(145, "Application"); 
  }                      
                         
  Min(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Min TAP_AsciiString(146, "Application"); 
  }                      
                         
  MinChargeableSubscriber(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 254; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MoBasicCallInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 147; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MobileOriginatedCall(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 9; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MobileTerminatedCall(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 10; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  Msisdn(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Msisdn ASN_BcdString(152, "Application"); 
  }                      
                         
  MtBasicCallInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 153; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  Network(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 332; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  NetworkAccessIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NetworkAccessIdentifier TAP_AsciiString(417, "Application"); 
  }                      
                         
  NetworkIdType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NetworkIdType ASN_Integer(331, "Application"); 
  }                      
                         
  NetworkIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NetworkIdentifier TAP_AsciiString(295, "Application"); 
  }                      
                         
  NetworkInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 6; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  NetworkInitPDPContext(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NetworkInitPDPContext ASN_Integer(245, "Application"); 
  }                      
                         
  NetworkList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 333; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  NetworkLocation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 156; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  NonChargedNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NonChargedNumber TAP_AsciiString(402, "Application"); 
  }                      
                         
  Notification(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 2; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  NumberOfDecimalPlaces(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NumberOfDecimalPlaces ASN_Integer(159, "Application"); 
  }                      
                         
  NumberString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NumberString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  ObjectType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ObjectType ASN_Integer(281, "Application"); 
  }                      
                         
  OperatorSpecInfoList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 162; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  OperatorSpecInformation(ASN) 
  {                      
    Info                 
    {                    
    }                    
    OperatorSpecInformation TAP_AsciiString(163, "Application"); 
  }                      
                         
  OrderPlacedTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 300; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  OriginatingNetwork(ASN) 
  {                      
    Info                 
    {                    
    }                    
    OriginatingNetwork TAP_AsciiString(164, "Application"); 
  }                      
                         
  PDPContextStartTimestamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 260; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  PacketDataProtocolAddress(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PacketDataProtocolAddress TAP_AsciiString(165, "Application"); 
  }                      
                         
  PaidIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PaidIndicator ASN_Integer(346, "Application"); 
  }                      
                         
  PartialTypeIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PartialTypeIndicator TAP_AsciiString(166, "Application"); 
  }                      
                         
  PaymentMethod(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PaymentMethod ASN_Integer(347, "Application"); 
  }                      
                         
  PdpAddress(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PdpAddress TAP_AsciiString(167, "Application"); 
  }                      
                         
  PercentageRate(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PercentageRate ASN_Integer(2, "Universal"); 
  }                      
                         
  PlmnId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PlmnId TAP_AsciiString(169, "Application"); 
  }                      
                         
  PositioningMethod(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PositioningMethod ASN_Integer(395, "Application"); 
  }                      
                         
  PriorityCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PriorityCode ASN_Integer(170, "Application"); 
  }                      
                         
  RapFileSequenceNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RapFileSequenceNumber TAP_AsciiString(181, "Application"); 
  }                      
                         
  RecEntityCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RecEntityCode ASN_Integer(184, "Application"); 
  }                      
                         
  RecEntityCodeList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 185; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  RecEntityId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RecEntityId TAP_AsciiString(400, "Application"); 
  }                      
                         
  RecEntityInfoList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 188; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  RecEntityInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 183; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  RecEntityType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RecEntityType ASN_Integer(186, "Application"); 
  }                      
                         
  Recipient(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Recipient TAP_AsciiString(182, "Application"); 
  }                      
                         
  ReleaseVersionNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ReleaseVersionNumber ASN_Integer(189, "Application"); 
  }                      
                         
  RequestedDeliveryTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 301; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ResponseTime(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ResponseTime ASN_Integer(394, "Application"); 
  }                      
                         
  ResponseTimeCategory(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ResponseTimeCategory ASN_Integer(387, "Application"); 
  }                      
                         
  SMSDestinationNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SMSDestinationNumber TAP_AsciiString(419, "Application"); 
  }                      
                         
  SMSOriginator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SMSOriginator TAP_AsciiString(425, "Application"); 
  }                      
                         
  ScuBasicInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 191; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ScuChargeType(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 192; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ScuChargeableSubscriber(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 430; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ScuTimeStamps(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 193; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  Sender(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Sender TAP_AsciiString(196, "Application"); 
  }                      
                         
  ServiceCentreUsage(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 12; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ServingBid(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ServingBid TAP_AsciiString(198, "Application"); 
  }                      
                         
  ServingLocationDescription(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ServingLocationDescription TAP_AsciiString(414, "Application"); 
  }                      
                         
  ServingNetwork(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ServingNetwork TAP_AsciiString(195, "Application"); 
  }                      
                         
  ServingPartiesInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 335; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  SimChargeableSubscriber(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 199; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  SimToolkitIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SimToolkitIndicator TAP_AsciiString(200, "Application"); 
  }                      
                         
  SpecificationVersionNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SpecificationVersionNumber ASN_Integer(201, "Application"); 
  }                      
                         
  SsParameters(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SsParameters TAP_AsciiString(204, "Application"); 
  }                      
                         
  SupplServiceActionCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SupplServiceActionCode ASN_Integer(208, "Application"); 
  }                      
                         
  SupplServiceCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SupplServiceCode TAP_AsciiString(209, "Application"); 
  }                      
                         
  SupplServiceEvent(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 11; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  SupplServiceUsed(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 206; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TapCurrency(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TapCurrency TAP_AsciiString(210, "Application"); 
  }                      
                         
  TapDecimalPlaces(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TapDecimalPlaces ASN_Integer(244, "Application"); 
  }                      
                         
  TaxCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TaxCode ASN_Integer(212, "Application"); 
  }                      

  TaxIndicator(ASN)
  {
    Info
    {
    }
    TaxIndicator TAP_AsciiString(432, "Application");
  }
                         
  TaxInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 213; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TaxInformationList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 214; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TaxRate(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TaxRate TAP_AsciiString(215, "Application"); 
  }                      
                         
  TaxType(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TaxType TAP_AsciiString(217, "Application"); 
  }                      
                         
  TaxValue(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TaxValue ASN_Integer(397, "Application"); 
  }                      
                         
  TaxableAmount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TaxableAmount ASN_Integer(398, "Application"); 
  }                      
                         
  Taxation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 216; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TaxationList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 211; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TeleServiceCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TeleServiceCode TAP_AsciiString(218, "Application"); 
  }                      
                         
  ThirdPartyInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 219; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ThirdPartyNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ThirdPartyNumber ASN_BcdString(403, "Application"); 
  }                      
                         
  ThreeGcamelDestination(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 431; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TotalAdvisedCharge(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalAdvisedCharge ASN_Integer(356, "Application", 0, 8); 
  }                      
                         
  TotalAdvisedChargeRefund(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalAdvisedChargeRefund ASN_Integer(357, "Application", 0, 8); 
  }                      
                         
  TotalAdvisedChargeValue(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 360; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TotalAdvisedChargeValueList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 361; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TotalCallEventDuration(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalCallEventDuration ASN_Integer(223, "Application"); 
  }                      
                         
  TotalCharge(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalCharge ASN_Integer(415, "Application", 0, 8); 
  }                      
                         
  TotalChargeRefund(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalChargeRefund ASN_Integer(355, "Application", 0, 8); 
  }                      
                         
  TotalCommission(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalCommission ASN_Integer(358, "Application", 0, 8); 
  }                      
                         
  TotalCommissionRefund(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalCommissionRefund ASN_Integer(359, "Application", 0, 8); 
  }                      
                         
  TotalDataVolume(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalDataVolume ASN_Integer(343, "Application", 0, 8); 
  }                      
                         
  TotalDiscountRefund(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalDiscountRefund ASN_Integer(354, "Application", 0, 8); 
  }                      
                         
  TotalDiscountValue(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalDiscountValue ASN_Integer(225, "Application", 0, 8); 
  }                      
                         
  TotalTaxRefund(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalTaxRefund ASN_Integer(353, "Application", 0, 8); 
  }                      
                         
  TotalTaxValue(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalTaxValue ASN_Integer(226, "Application", 0, 8); 
  }                      
                         
  TotalTransactionDuration(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalTransactionDuration ASN_Integer(416, "Application"); 
  }                      
                         
  TrackedCustomerEquipment(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 381; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackedCustomerHomeId(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 377; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackedCustomerHomeIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 376; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackedCustomerIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 370; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackedCustomerIdentification(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 372; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackedCustomerInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 367; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackedCustomerLocList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 379; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackedCustomerLocation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 380; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerEquipment(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 371; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerHomeId(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 366; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerHomeIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 365; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerIdList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 299; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerIdentification(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 362; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerInformation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 298; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerLocList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 368; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingCustomerLocation(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 369; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TrackingFrequency(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TrackingFrequency ASN_Integer(389, "Application"); 
  }                      
                         
  TrackingPeriod(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TrackingPeriod ASN_Integer(388, "Application"); 
  }                      
                         
  TransactionAuthCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TransactionAuthCode TAP_AsciiString(342, "Application"); 
  }                      
                         
  TransactionDescriptionSupp(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TransactionDescriptionSupp ASN_Integer(338, "Application"); 
  }                      
                         
  TransactionDetailDescription(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TransactionDetailDescription TAP_AsciiString(339, "Application"); 
  }                      
                         
  TransactionIdentifier(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TransactionIdentifier TAP_AsciiString(341, "Application"); 
  }                      
                         
  TransactionShortDescription(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TransactionShortDescription TAP_AsciiString(340, "Application"); 
  }                      
                         
  TransactionStatus(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TransactionStatus ASN_Integer(303, "Application"); 
  }                      
                         
  TransferBatch(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 1; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TransferCutOffTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 227; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  TransparencyIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TransparencyIndicator ASN_Integer(228, "Application"); 
  }                      
                         
  UserProtocolIndicator(ASN) 
  {                      
    Info                 
    {                    
    }                    
    UserProtocolIndicator ASN_Integer(280, "Application"); 
  }                      
                         
  UtcTimeOffset(ASN) 
  {                      
    Info                 
    {                    
    }                    
    UtcTimeOffset TAP_AsciiString(231, "Application"); 
  }                      
                         
  UtcTimeOffsetCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    UtcTimeOffsetCode ASN_Integer(232, "Application"); 
  }                      
                         
  UtcTimeOffsetInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 233; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  UtcTimeOffsetInfoList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 234; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  VerticalAccuracyDelivered(ASN) 
  {                      
    Info                 
    {                    
    }                    
    VerticalAccuracyDelivered ASN_Integer(393, "Application"); 
  }                      
                         
  VerticalAccuracyRequested(ASN) 
  {                      
    Info                 
    {                    
    }                    
    VerticalAccuracyRequested ASN_Integer(386, "Application"); 
  }                      
                         

}
