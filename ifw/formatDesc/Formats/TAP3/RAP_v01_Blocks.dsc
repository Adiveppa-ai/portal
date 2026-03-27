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
//   Description of the RAP CDR format
//
//------------------------------------------------------------------------------
// $Log: RAP_v01_Blocks.dsc,v $
//
// Log 2003/04/11 pgeiger
// - PRSF00028555 : Need support for TAP3.10 standard
//
//------------------------------------------------------------------------------

IFW_RAP
{
  Block_END(FIX)
  {
    Info
    {
      States    = (RapState_01_01);
      Pattern   = "\0\0";
    }
    dummy AscString(2);
  }

  //----------------------------------------------------------------------------
  ReturnBatch(ASN)
  {
    Info
    {
      Application = 534;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------
  Acknowledgement(ASN)
  {
    Info
    {
      Application = 535;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------
  RapBatchControlInfo(ASN)
  {
    Info
    {
      Application = 537;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------
  ReturnDetailList(ASN)
  {
    Info
    {
      Application = 536;
      States  	  = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------
  MissingReturn(ASN)
  {
    Info
    {
      Application = 538;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------
  
  FatalReturn(ASN)
  {
    Info
    {
      Application = 539;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------
  
  SevereReturn(ASN)
  {
    Info
    {
      Application = 540;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  RapAuditControlInfo(ASN)
  {
    Info
    {
      Application = 541;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  AccountingInfoError(ASN)
  {
    Info
    {
      Application = 512;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  AuditControlInfoError(ASN)
  {
    Info
    {
      Application = 513;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  AckFileAvailableTimeStamp(ASN)
  {
    Info
    {
      Application = 515;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  AckFileCreationTimeStamp(ASN)
  {
    Info
    {
      Application = 516;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  BatchControlError(ASN)
  {
    Info
    {
      Application = 517;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  EndMissingSeqNumber(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    END_MISSING_SEQ_NUMBER    TAP_AsciiString(518, "Application");  // FileSequenceNumber
  }
  //----------------------------------------------------------------------------

  ErrorCode(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    ERROR_CODE    ASN_Integer(519, "Application");
  }
  //----------------------------------------------------------------------------
  
  ErrorContext(ASN)
  {
    Info
    {
      Application = 545;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  ErrorContextList(ASN)
  {
    Info
    {
      Application = 549;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  ErrorDetail(ASN)
  {
    Info
    {
      Application = 521;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  ErrorDetailList(ASN)
  {
    Info
    {
      Application = 520;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  ItemLevel(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    ITEM_LEVEL    ASN_Integer(548, "Application");
  }
  //----------------------------------------------------------------------------
  
  ItemOccurrence(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    ITEM_OCCURRENCE    ASN_Integer(547, "Application");
  }
  //----------------------------------------------------------------------------

  ItemOffset(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    ITEM_OFFSET    ASN_Integer(524, "Application");
  }
  //----------------------------------------------------------------------------

  MessageDescriptionError(ASN)
  {
    Info
    {
      Application = 522;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  NetworkInfoError(ASN)
  {
    Info
    {
      Application = 523;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  PathItemId(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    PATH_ITEM_ID    ASN_Integer(546, "Application");
  }
  //----------------------------------------------------------------------------

  RapFileAvailableTimeStamp(ASN)
  {
    Info
    {
      Application = 525;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  RapFileCreationTimeStamp(ASN)
  {
    Info
    {
      Application = 526;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  RapReleaseVersionNumber(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    RAP_RELEASE_VERSION_NUMBER    ASN_Integer(543, "Application");
  }
  //----------------------------------------------------------------------------

  RapSpecificationVersionNumber(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    RAP_SPECIFICATION_VERSION_NUMBER   ASN_Integer(544, "Application");
  }
  //----------------------------------------------------------------------------

  ReturnDetailsCount(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    RETURN_DETAILS_COUNT    ASN_Integer(528, "Application");
  }
  //----------------------------------------------------------------------------

  ReturnSummary(ASN)
  {
    Info
    {
      Application = 530;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  ReturnSummaryList(ASN)
  {
    Info
    {
      Application = 531;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  RoamingPartner(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    RoamingPartner      TAP_AsciiString(550, "Application");  // PLMN_ID
  }
  //----------------------------------------------------------------------------

  SevereReturnValue(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    SEVERE_RETURN_VALUE   ASN_HexString(529, "Application");  // AbsoluteAmount
  }
  //----------------------------------------------------------------------------

  StartMissingSeqNumber(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    START_MISSING_SEQ_NUMBER    ASN_NumberString(532, "Application");  // FileSequenceNumber
  }
  //----------------------------------------------------------------------------

  TotalSevereReturnValue(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    TOTAL_SEVERE_RETURN_VALUE    ASN_HexString(533, "Application"); // AbsoluteAmount
  }
  //----------------------------------------------------------------------------

  TransferBatchError(ASN)
  {
    Info
    {
      Application = 542;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }
  //----------------------------------------------------------------------------

  VASInformationError(ASN)
  {
    Info
    {
      Application = 527;
      States      = (RapState_01_01);
      EndRecord   = Block_END;
    }
  }

  //----------------------------------------------------------------------------
  EquipmentInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    EQUIPMENT_INFORMATION         ASN_Blob(102, "Application");
  }

  //----------------------------------------------------------------------------
  LocationInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    LOCATION_INFORMATION         ASN_Blob(138, "Application");
  }

  //----------------------------------------------------------------------------
  BasicServiceUsedList(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    BASIC_SERVICE_USED_LIST         ASN_Blob(38, "Application");
  }
    
  //----------------------------------------------------------------------------
  SupplServiceUsedList(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    SUPPL_SERVICE_USED_LIST         ASN_Blob(207, "Application");
  }

  //----------------------------------------------------------------------------
  CamelServiceUsed(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    CAMEL_SERVICE_USED         ASN_Blob(57, "Application");
  }

  //----------------------------------------------------------------------------
  ValueAddedServiceUsedList(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    VALUE_ADDED_SERVICE_USED_LIST         ASN_Blob(235, "Application");
  }

  //----------------------------------------------------------------------------
  MoBasicCallInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    MO_BASIC_CALL_INFORMATION         ASN_Blob(147, "Application");
  }
  
  //----------------------------------------------------------------------------
  MtBasicCallInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    MT_BASIC_CALL_INFORMATION     ASN_Blob(153, "Application");
  }

 
  //----------------------------------------------------------------------------
  SimChargeableSubscriber(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    SIM_CHARGEABLE_SUBSCRIBER     ASN_Blob(199, "Application");
  }

  //----------------------------------------------------------------------------
  MinChargeableSubscriber(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    MIN_CHARGEABLE_SUBSCRIBER     ASN_Blob(254, "Application");
  }
  
  //----------------------------------------------------------------------------
  SupplServiceUsed(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    SUPPL_SERVICE_USED         ASN_Blob(206, "Application");
  }

  //----------------------------------------------------------------------------
  ScuBasicInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    SCU_BASIC_INFORMATION         ASN_Blob(191, "Application");
  }
  
  //----------------------------------------------------------------------------
  RecEntitiyCode(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    REC_ENTITIY_CODE         ASN_Integer(184, "Application");
  }

  //----------------------------------------------------------------------------
  ChargeInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    CHARGE_INFORMATION         ASN_Blob(69, "Application");
  }
  
  //----------------------------------------------------------------------------
  ScuChargeType(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    SCU_CHARGE_TYPE         ASN_Blob(192, "Application");
  }
  
  //----------------------------------------------------------------------------
  ScuTimeStamps(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    SCU_TIME_STAMPS         ASN_Blob(193, "Application");
  }
  
  //----------------------------------------------------------------------------
  ValueAddedServiceUsed(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    VALUE_ADDED_SERVICE_USED         ASN_Blob(236, "Application");
  }

  //----------------------------------------------------------------------------
  GprsBasicCallInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    GPRS_BASIC_CALL_INFORMATION    ASN_Blob(114, "Application");
  }
  
  //----------------------------------------------------------------------------
  GprsLocationInformation(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    GPRS_LOCATION_INFORMATION    ASN_Blob(117, "Application");
  }
  
  //----------------------------------------------------------------------------
  GprsServiceUsed(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    GPRS_SERVICE_USED    ASN_Blob(121, "Application");
  }
  
  //----------------------------------------------------------------------------
  ContentTransactionBlob(ASN) 
  {
    Info
    {
      States      = (RapState_01_01);
    }
    CONTENT_TRANSACTION_BLOB    ASN_Blob(17, "Application");
  }

  //----------------------------------------------------------------------------
  OperatorSpecList(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    OPERATOR_SPEC_LIST         ASN_Blob(551, "Application");
  }
    
  //----------------------------------------------------------------------------
  NotificationError(ASN)
  {
    Info
    {
      States      = (RapState_01_01);
    }
    NOTIFICATION_ERROR         ASN_Blob(552, "Application");
  }
    

}
