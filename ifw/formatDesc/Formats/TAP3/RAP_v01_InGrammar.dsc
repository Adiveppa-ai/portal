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
// $Log: RAP_v01_InGrammar.dsc,v $
//
// Log 2003/04/11 pgeiger
// - PRSF00028555 : Need support for TAP3.10 standard
//
// Revision 1.1  2002/06/12 16:27:22  cdiab
// - remove the usage of the EXT_AsnTree extension (not needed in the input)
// - corrected the structuring of the returnDetailList object
// - removed the "compatibility with before tap0304" as we do not write out a
//   format previous to tap0304.
//
// Revision 1.0  2002/05/21 12:19:24  jkeckste
// - Creation
//
//==============================================================================

iScript
{
  const String type_HEADER         ="010";
  const String type_HEADER_for_Ack ="000";

  String  lastLocalTimeStamp;
  String  lastUtcTimeOffset;
  String  theFileTypeIndicator;
  String  theFileCreationTimeStamp;
  String  theFileCreationUtcTimeOffset;
  String  theFileAvailableTimeStamp;
  String  theFileAvailableUtcTimeOffset;

  // -------------------------------------------------
  function onParseError //this function is only called with integrate v4-40-xx
  {
    // Error processing
    logPipeline("RAP_ERROR at BytePos @"+longToStr(ERROR_TOKEN_BYTEPOS)+
                " (ie. @0x"+longToHexStr(ERROR_TOKEN_BYTEPOS)+
                "), Token hex content=<"+ERROR_TOKEN_ASC+">",3);
  }

  // -------------------------------------------------
  function onParseStart
  {
    lexState("RapState_01_01");
  }

  // -------------------------------------------------
  function BEGIN
  {
  }

}

  
  
// ----------------------------------------------------------------------------

Grammar
{
  inputStream:
    returnBatch
    |
    acknowledge
  ;

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
  acknowledge:
    IFW_RAP.Acknowledgement
      {
        if ( edrNew( HEADER, CONTAINER_HEADER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 ); // abort processing of the input stream
          logFormat( "ERROR: Failed to create HEADER" );
        }
        edrString(HEADER.RECORD_TYPE)         = type_HEADER_for_Ack;
        edrLong(HEADER.RECORD_NUMBER)         = 1;
      }
      IFW_TAP3.Sender
      {
        edrString(HEADER.SENDER)= tokenString("IFW_TAP3.Sender.PLMN_ID");
      }
      IFW_TAP3.Recipient
      {
        edrString(HEADER.RECIPIENT)= tokenString("IFW_TAP3.Recipient.PLMN_ID");
      }
      IFW_TAP3.RapFileSequenceNumber
      {
        edrLong(HEADER.SEQUENCE_NUMBER) = tokenLong("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER");
      }
      ackFileCreationTimeStamp
      {
        edrDate(HEADER.CREATION_TIMESTAMP) = strToDate(theFileCreationTimeStamp);
        edrString(HEADER.UTC_TIME_OFFSET)  = theFileCreationUtcTimeOffset;
      }
      ackFileAvailableTimeStamp
      {
        edrDate(HEADER.TRANSMISSION_DATE) = strToDate(theFileAvailableTimeStamp);
      }
      fileTypeIndicator_opt
      {
        edrString(HEADER.DATA_TYPE_INDICATOR) = theFileTypeIndicator;    
      }
      operatorSpecInformation_opt
    IFW_RAP.Block_END   // IFW_RAP.Acknowledgement
      {
        if ( edrNew( TRAILER, CONTAINER_TRAILER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 ); //TODO abort processing of the input stream
          logFormat( "ERROR: Failed to create TRAILER" );
        }
      }
  ;

// ----------------------------------------------------------------------------
//  Return Batch
// ----------------------------------------------------------------------------
  returnBatch:
    IFW_RAP.ReturnBatch
      {
        if ( edrNew( HEADER, CONTAINER_HEADER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 ); //TODO abort processing of the input stream
          logFormat( "ERROR: Failed to create HEADER" );
        }
        edrString(HEADER.RECORD_TYPE)         = type_HEADER;
        edrLong(HEADER.RECORD_NUMBER)         = 1;
      }
      rapBatchControlInfo    
      IFW_RAP.ReturnDetailList
        returnDetailList
      IFW_RAP.Block_END       // ReturnDetailList  
      auditControlInfo
      {
        if ( edrNew( TRAILER, CONTAINER_TRAILER ) == false )
        {
          edrAddError( "ERR_EDR_CREATE", 4 ); //TODO abort processing of the input stream
          logFormat( "ERROR: Failed to create TRAILER" );
        }
      }
    IFW_RAP.Block_END       // ReturnBatch
  ;

  
// ----------------------------------------------------------------------------
//  RAP Audit Control Information
// ----------------------------------------------------------------------------
    auditControlInfo:
      IFW_RAP.RapAuditControlInfo
        returnSummaryList_opt
        IFW_RAP.TotalSevereReturnValue
        IFW_RAP.ReturnDetailsCount
        operatorSpecInformation_opt
      IFW_RAP.Block_END       // RapAuditControlInfo
    ;
    
// ----------------------------------------------------------------------------
    returnSummaryList_opt:
      IFW_RAP.ReturnSummaryList
        returnSummaryList_opt2
      IFW_RAP.Block_END     // ReturnSummaryList
      | // Empty
    ;

// ----------------------------------------------------------------------------
    returnSummaryList_opt2:
      returnSummaryList_opt2
      returnSummary
      | // Empty
    ;
      
// ----------------------------------------------------------------------------
    returnSummary:
      IFW_RAP.ReturnSummary
        IFW_TAP3.FileSequenceNumber
        severeRetValue_opt
      IFW_RAP.Block_END       // ReturnSummary
    ;

// ----------------------------------------------------------------------------
    severeRetValue_opt:
      IFW_RAP.SevereReturnValue
      | // Empty
    ;

// ----------------------------------------------------------------------------
//  Return Detail
// ----------------------------------------------------------------------------
  returnDetailList:  
    returnDetailList
    returnDetail
    |
    returnDetail
  ;

// ----------------------------------------------------------------------------
  returnDetail:
    missingReturn
    |
    fatalReturn
    |
    severeReturn
  ;

// ----------------------------------------------------------------------------
  missingReturn:
    IFW_RAP.MissingReturn
      IFW_RAP.StartMissingSeqNumber
      endMissingNumber_opt
      operatorSpecInformation_opt
    IFW_RAP.Block_END     // MissingReturn
  ;
    
// ----------------------------------------------------------------------------
  endMissingNumber_opt:
    IFW_RAP.EndMissingSeqNumber
    |   // Empty
  ;
  
// ----------------------------------------------------------------------------
  fatalReturn:
    IFW_RAP.FatalReturn
      fileSequenceNumber_opt
      transferBatchError_opt
      notificationError_opt
      batchControlError_opt
      accountingInfoError_opt
      networkInfoError_opt
      VASInfoError_opt
      messageDescError_opt
      auditControlInfoError_opt
      operatorSpecInformation_opt
    IFW_RAP.Block_END
  ;
    
// ----------------------------------------------------------------------------
  fileSequenceNumber_opt:
      IFW_TAP3.FileSequenceNumber
    | // Empty
    ;
    
// ----------------------------------------------------------------------------
  transferBatchError_opt:
    IFW_RAP.TransferBatchError
      errorDetailList
    IFW_RAP.Block_END  
    | // Empty
    ;
    
// ----------------------------------------------------------------------------
  batchControlError_opt:
    IFW_RAP.BatchControlError
      IFW_RAP.RapBatchControlInfo
      errorDetailList
    IFW_RAP.Block_END
    | // Empty
    ;

// ----------------------------------------------------------------------------
  accountingInfoError_opt:
    IFW_RAP.AccountingInfoError
      IFW_TAP3.AccountingInfo
      errorDetailList
    IFW_RAP.Block_END
    | // Empty
    ;

// ----------------------------------------------------------------------------
  networkInfoError_opt:
    IFW_RAP.NetworkInfoError
      IFW_TAP3.NetworkInfo
      errorDetailList
    IFW_RAP.Block_END  
    | // Empty
    ;

// ----------------------------------------------------------------------------
  notificationError_opt:
    IFW_RAP.NotificationError
      IFW_TAP3.Notification
      errorDetailList
    IFW_RAP.Block_END
    | // Empty
    ;

// ----------------------------------------------------------------------------
  VASInfoError_opt:
    IFW_RAP.VASInformationError
      IFW_TAP3.VasInfo
      errorDetailList
    IFW_RAP.Block_END
    | // Empty
    ;

// ----------------------------------------------------------------------------
  messageDescError_opt:
    IFW_RAP.MessageDescriptionError
      IFW_TAP3.MessageDescriptionInfo
      errorDetailList
    IFW_RAP.Block_END
    | // Empty
    ;

// ----------------------------------------------------------------------------
  auditControlInfoError_opt:
    IFW_RAP.AuditControlInfoError
      IFW_TAP3.AuditControlInfo
      errorDetailList
    IFW_RAP.Block_END
    | // Empty
    ;

// ----------------------------------------------------------------------------
  severeReturn:
    IFW_RAP.SevereReturn
      IFW_TAP3.FileSequenceNumber
      callEventDetail
      errorDetailList
      operatorSpecInformation_opt
    IFW_RAP.Block_END
  ;

// ----------------------------------------------------------------------------
  callEventDetail:
      mobileOriginatedCall
    | mobileTerminatedCall
    | supplServiceEvent 
    | serviceCentreUsage
    | valueAddedService 
    | gprsCall
    | contentTransaction
    ;

// ----------------------------------------------------------------------------
  camelServiceUsed_opt:
    IFW_RAP.CamelServiceUsed
    | // Empty
  ;

// ----------------------------------------------------------------------------
  valueAddedServiceUsedList_opt:
    IFW_RAP.ValueAddedServiceUsedList
    | // Empty
  ;

// ----------------------------------------------------------------------------
  equipmentInformation_opt:
    IFW_RAP.EquipmentInformation
    | // Empty
  ;

// ----------------------------------------------------------------------------
  mobileOriginatedCall:
    IFW_TAP3.MobileOriginatedCall
      {
//        logPipeline("IFW_TAP3.MobileOriginatedCall detected");
      }
      IFW_RAP.MoBasicCallInformation
      IFW_RAP.LocationInformation
      equipmentInformation_opt
      IFW_RAP.BasicServiceUsedList
      supplServiceUsedList_opt
      camelServiceUsed_opt
      valueAddedServiceUsedList_opt
      dualServiceRequested_opt
      operatorSpecInformation_opt
    IFW_TAP3.Block_END
  ;

// ----------------------------------------------------------------------------
  supplServiceUsedList_opt:
    IFW_RAP.SupplServiceUsedList
    | // Empty
  ;
      
// ----------------------------------------------------------------------------
  dualServiceRequested_opt:
    IFW_TAP3.DualTeleServiceCode
    |
    IFW_TAP3.DualBearerServiceCode
    | // Empty
  ;

// ----------------------------------------------------------------------------
  mobileTerminatedCall:
    IFW_TAP3.MobileTerminatedCall
      {
//        logPipeline("IFW_TAP3.MobileTerminatedCall detected");
      }
      IFW_RAP.MtBasicCallInformation
      IFW_RAP.LocationInformation
      equipmentInformation_opt
      IFW_RAP.BasicServiceUsedList
      supplServiceUsedList_opt
      camelServiceUsed_opt
      valueAddedServiceUsedList_opt
      dualServiceRequested_opt
      operatorSpecInformation_opt
    IFW_TAP3.Block_END
    ;

// ----------------------------------------------------------------------------
  supplServiceEvent:
    IFW_TAP3.SupplServiceEvent
      {
//        logPipeline("IFW_TAP3.SupplServiceEvent detected");
      }
      fraudMonitorIndicator_opt
      chargeableSubscriber
      rapFileSequenceNumber_opt
      networkType_opt
      IFW_RAP.LocationInformation
      IFW_RAP.EquipmentInformation
      IFW_RAP.SupplServiceUsed
      simToolkitIndicator_opt
      operatorSpecInformation_opt
    IFW_TAP3.Block_END
  ;

// ----------------------------------------------------------------------------
  simToolkitIndicator_opt:
    IFW_TAP3.SimToolkitIndicator
    | // Empty
  ;

// ----------------------------------------------------------------------------
  networkType_opt:
    IFW_TAP3.NetworkType
    | // Empty
  ;    

// ----------------------------------------------------------------------------
  rapFileSequenceNumber_opt:
    IFW_TAP3.RapFileSequenceNumber
    | // Empty
  ;

// ----------------------------------------------------------------------------
  chargeableSubscriber:
    IFW_RAP.SimChargeableSubscriber
    |
    IFW_RAP.MinChargeableSubscriber
  ;

// ----------------------------------------------------------------------------
  fraudMonitorIndicator_opt:
    IFW_TAP3.FraudMonitorIndicator
    | // Empty
  ;

// ----------------------------------------------------------------------------
  serviceCentreUsage:
    IFW_TAP3.ServiceCentreUsage
      {
//        logPipeline("IFW_TAP3.ServiceCentreUsage detected");
      }
      fraudMonitorIndicator_opt
      IFW_RAP.ScuBasicInformation
      rapFileSequenceNumber_opt
      networkType_opt
      servingNetwork_opt
      IFW_RAP.RecEntitiyCode
      IFW_RAP.ChargeInformation
      IFW_RAP.ScuChargeType
      IFW_RAP.ScuTimeStamps
      operatorSpecInformation_opt
    IFW_TAP3.Block_END
  ;

// ----------------------------------------------------------------------------
  servingNetwork_opt:
    IFW_TAP3.ServingNetwork
    | // Empty
  ;

// ----------------------------------------------------------------------------
  valueAddedService:
    IFW_TAP3.ValueAddedService
      {
//        logPipeline("IFW_TAP3.ValueAddedService detected");
      }
      fraudMonitorIndicator_opt
      scuVasChargeableSubscriber
      rapFileSequenceNumber_opt
      networkType_opt
      servingNetwork_opt
      IFW_RAP.ValueAddedServiceUsed
      operatorSpecInformation_opt
    IFW_TAP3.Block_END
  ;
  
// ----------------------------------------------------------------------------
  scuVasChargeableSubscriber:
    IFW_RAP.SimChargeableSubscriber
    |
    IFW_TAP3.Msisdn
    |
    IFW_TAP3.Min
  ;

// ----------------------------------------------------------------------------
  gprsCall:
    IFW_TAP3.GprsCall
      {
//        logPipeline("IFW_TAP3.GprsCall detected");
      }
      IFW_TAP3.TypeOfControllingNode
      IFW_RAP.GprsBasicCallInformation
      IFW_RAP.GprsLocationInformation
      equipmentInformation_opt
      IFW_RAP.GprsServiceUsed
      camelServiceUsed_opt
      valueAddedServiceUsedList_opt
      operatorSpecInformation_opt
    IFW_TAP3.Block_END
  ;

// ----------------------------------------------------------------------------
  contentTransaction:
    IFW_RAP.ContentTransactionBlob
    ;

// ----------------------------------------------------------------------------
//  Batch Control Information
// ----------------------------------------------------------------------------
  rapBatchControlInfo:
    IFW_RAP.RapBatchControlInfo
    
      IFW_TAP3.Sender
      {
        edrString(HEADER.SENDER)= tokenString("IFW_TAP3.Sender.PLMN_ID");
      }
      IFW_TAP3.Recipient
      {
        edrString(HEADER.RECIPIENT)= tokenString("IFW_TAP3.Recipient.PLMN_ID");
      }
      IFW_TAP3.RapFileSequenceNumber
      {
        edrLong(HEADER.SEQUENCE_NUMBER) = tokenLong("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER");
      }
      fileCreationTimeStamp
      {
        edrDate(HEADER.CREATION_TIMESTAMP) = strToDate(theFileCreationTimeStamp);
        edrString(HEADER.UTC_TIME_OFFSET)  = theFileCreationUtcTimeOffset;
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
      IFW_RAP.RapSpecificationVersionNumber
      IFW_RAP.RapReleaseVersionNumber
      fileTypeIndicator_opt
      {
        edrString(HEADER.DATA_TYPE_INDICATOR) = theFileTypeIndicator;    
      }
      operatorSpecInformation_opt
    IFW_RAP.Block_END     // RapBatchControlInfo
   
  ;  

// ----------------------------------------------------------------------------
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
  
// ----------------------------------------------------------------------------
//  Operator Secification Information
// ----------------------------------------------------------------------------
  operatorSpecInformation_opt:
      IFW_TAP3.OperatorSpecInfoList
        operatorSpecInformationList
      IFW_TAP3.Block_END
    |
      IFW_RAP.OperatorSpecList
        operatorSpecInformationList
      IFW_RAP.Block_END
    | /* EMPTY */
    ;
    
  operatorSpecInformationList:
      operatorSpecInformationList
      IFW_TAP3.OperatorSpecInformation
    | IFW_TAP3.OperatorSpecInformation // the first one
      {
        // TODO : IMPLEMENT HERE THE LOOKUP FOR THE STORED ORIGINAL SWITCH CDR
        // if there is a record Identifier, it is in this string, so use it!
      }
    ;

// ----------------------------------------------------------------------------
//  File creation time stamp for acknowledge files
// ----------------------------------------------------------------------------
  ackFileCreationTimeStamp:
    IFW_RAP.AckFileCreationTimeStamp
    dateTimeLong
    IFW_RAP.Block_END
    {
      theFileCreationTimeStamp     = lastLocalTimeStamp;
      theFileCreationUtcTimeOffset = lastUtcTimeOffset;
    }
    ;

  ackFileAvailableTimeStamp:
    IFW_RAP.AckFileAvailableTimeStamp
    dateTimeLong
    IFW_RAP.Block_END
    {
      theFileAvailableTimeStamp     = lastLocalTimeStamp;
      theFileAvailableUtcTimeOffset = lastUtcTimeOffset;
    }
    ;


// ----------------------------------------------------------------------------
//  File creation time stamp for rap files
// ----------------------------------------------------------------------------
  fileCreationTimeStamp:
    IFW_RAP.RapFileCreationTimeStamp
    dateTimeLong
    IFW_RAP.Block_END
    {
      theFileCreationTimeStamp     = lastLocalTimeStamp;
      theFileCreationUtcTimeOffset = lastUtcTimeOffset;
    }
    ;

  fileAvailableTimeStamp:
    IFW_RAP.RapFileAvailableTimeStamp
    dateTimeLong
    IFW_RAP.Block_END
    {
      theFileAvailableTimeStamp     = lastLocalTimeStamp;
      theFileAvailableUtcTimeOffset = lastUtcTimeOffset;
    }
    ;
 
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
//  Error Detail
// ----------------------------------------------------------------------------

  errorDetailList:
    IFW_RAP.ErrorDetailList
      errorDetailList2
    IFW_RAP.Block_END    // ErrorDetailList
  ;

  errorDetailList2:
    errorDetailList2
    errorDetail
    | // Emtpy
  ;

  errorDetail:
    IFW_RAP.ErrorDetail
      errorContextList_opt
      itemOffset_opt
      IFW_RAP.ErrorCode
    IFW_RAP.Block_END    // ErrorDetail
    ;

  errorContextList_opt:
    IFW_RAP.ErrorContextList
      errorContextList2
    IFW_RAP.Block_END    // ErrorContextList
    | // Empty
  ;

  errorContextList2:
    errorContextList2
    errorContext
    | // Empty
  ;
    
  errorContext:
    IFW_RAP.ErrorContext
      IFW_RAP.PathItemId
      itemOccurrence_opt
      IFW_RAP.ItemLevel
    IFW_RAP.Block_END   // ErrorContext
    ;
    
  itemOccurrence_opt:
    IFW_RAP.ItemOccurrence
    | // Empty
    ;

  itemOffset_opt:
    IFW_RAP.ItemOffset
    | // Empty
    ;
}

