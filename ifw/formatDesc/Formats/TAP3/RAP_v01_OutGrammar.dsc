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
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: RAP_v01_OutGrammar.dsc,v $
// $Revision: 1.0 $
// $Author: jkeckste $
// $Date: 2002/05/21 12:19:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: RAP_v01_OutGrammar.dsc,v $
// Revision 1.1  2002/06/05 16:27:22  cdiab
// - take the TAP3 version number from the HEADER (not hard coded anymore)
// - order the errors according to their severity and process only the highest
// - send back non RAP edrs to standard reject stream (all which is not severe)
// - make a distinction between the TAP3 and the RAP file sequence numbers
// - the Audit/ReturnSummary can only contain 1 element: the totalReturnCharge
// - TotalSevereReturnValue = round(Sum all return charges set to decimal places)
// - a new parameter (ValidationRuleID) was added  to the ERR_TAP3_RET msg.
//
// Revision 1.0  2002/05/21 12:19:24  jkeckste
// - Creation
//
//==============================================================================

iScript
{
  use EXT_AsnTree;        // iScript extension to build a Tree of ASN.1 object
                          // used to fill the Length value of the ASN.1 bloc,
                          // before printing on output stream

  const Long RapSpecificationVersionNumber  = 1;
  const Long RapReleaseVersionNumber        = 1;

  //indexes to access parameters stored in the TAP3 error array
  const Long TAP_Severity     = 0;
  const Long TAP_ErrCode      = 1;
  const Long TAP_ObjTag       = 2;
  const Long ObjDepth         = 3;
  const Long ObjOffset        = 4;
  const Long ObjArrayIdx      = 5;  
  const Long ValidationRuleID = 6;
  const Long MaxParamCount    = 7;
  
  //local identifier for the TAP3 severities
  const Long NoTap3Severity   = 0; // the edr was sent to the wrong output stream!
  const Long WarningSeverity  = 1; // warning is no real error
  const Long BadParamSeverity = 2; // could be severe, but we cannot write it out
  const Long UnknownSeverity  = 3; // could be written out as severe (params are here)
  const Long SevereSeverity   = 4;
  const Long FatalSeverity    = 5; // will never be written out by this grammar
  const Long MissingSeverity  = 6; // will never be written out by this grammar
  
  // define all variables
  Date    actualSystime; 
  String  headerUtcTimeOffset;
  String  rapSpecVersionNumber;
  String  rapRelVersionNumber;
  String  defUtcTimeOffset;
  Long    rapDetailsWritten;
  Long    detailCount;
  Long    rapSequenceNumber;
  Long    tapSequenceNumber;
  Long    wholesaleChargeCount;
  Decimal wholesaleChargeSum;
  Decimal chargeMultiplier;

  Decimal wholesaleCharge[];
  String  paramList[];
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function BEGIN
  {
    // init the variables
    actualSystime         = sysdate();
    defUtcTimeOffset      = "+0000";
    rapDetailsWritten     = 0;
    detailCount           = 0;
    rapSequenceNumber     = 0;
    tapSequenceNumber     = 0;
    wholesaleChargeCount  = 0;
    wholesaleChargeSum    = 0.0;
    chargeMultiplier      = 0.0;
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  // NB: Notification files are considered empty and will be deleted if in the
  //     registry you have DeleteEmptyStream=true for the RAP output stream
  function Bool streamIsEmpty
  {
    // a notification is identified by a Header and a Trailer (no Details)
    // a transfertBatch is identified by a Header, 1 or more Details, and a Trailer
    if ( rapDetailsWritten == 0 )
    {
      // Only HEADER and TRAILER
      return true;
    }
    // default
    return false;
  }
  
  // -------------------------------------------------------------------------------------------
  // common functions
  // -------------------------------------------------------------------------------------------
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
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function initForNewHeader
  {
    rapDetailsWritten     = 0;
    detailCount           = 0;
    wholesaleChargeCount  = 0;
    wholesaleChargeSum    = 0.0;
    chargeMultiplier      = 0.0;
    
    headerUtcTimeOffset   = edrString(HEADER.UTC_TIME_OFFSET);
    tapSequenceNumber     = edrLong(HEADER.ORIGIN_SEQUENCE_NUMBER);
    rapSequenceNumber     = edrLong(HEADER.SEQUENCE_NUMBER);
    
    arrayClear(wholesaleCharge);

    chargeMultiplier      = 1.0;
    Long i;
    for (i=0 ; i < edrLong(HEADER.TAP_DECIMAL_PLACES) ; i=i+1)
    {
      chargeMultiplier = chargeMultiplier * 10.0;
    }
  }
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function getTrailerInfos
  {
    wholesaleCharge[wholesaleChargeCount] = 
      round(edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) * chargeMultiplier);
    wholesaleChargeSum = 
      wholesaleChargeSum + edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE);
    wholesaleChargeCount = wholesaleChargeCount + 1;
  }
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleFatalError
  {
    //asnTreePushTag("IFW_RAP.FatalReturn");
    //asnTreePop(); // asnTreePushTag("IFW_RAP.FatalReturn");
    logPipeline("INFO on RAP output: EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + 
                " contains an ERR_TAP3_RET with the Fatal severity (ie. rollback)");
    edrReject(); // send the EDR back to the standard reject stream (for recycling)
  }
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleMissingError
  {
    //asnTreePushTag("IFW_RAP.MissingReturn");
    //asnTreePop(); // asnTreePushTag("IFW_RAP.MissingReturn");
    logPipeline("INFO on RAP output: EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + 
                " contains an ERR_TAP3_RET with the Missing severity (ie. rollback)");
    edrReject(); // send the EDR back to the standard reject stream (for recycling)
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleWarningError
  {
    logPipeline("ERROR on RAP output: EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + 
                " contains an ERR_TAP3_RET but only with warnings (NOT returnable)");
    edrReject(); // send the EDR back to the standard reject stream (for recycling)
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleUnknownError
  {
    logPipeline("ERROR on RAP output: EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + 
                " contains an ERR_TAP3_RET error with an unknown severity");
    edrReject(); // send the EDR back to the standard reject stream (for recycling)
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleBadParamError
  {
    logPipeline("ERROR on RAP output: EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + 
                " contains an ERR_TAP3_RET error with the wrong number of parameters");
    edrReject(); // send the EDR back to the standard reject stream (for recycling)
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleNoTap3Error
  {
    logPipeline("ERROR on RAP output: EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + 
                " does not contain any ERR_TAP3_RET error");
    edrReject(); // send the EDR back to the standard reject stream (for recycling)
  }
 
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function setSevereErrorList 
  {
    Long checkNumber = 0;

    asnTreePushTag("IFW_RAP.ErrorDetail");
      asnTreePushTag("IFW_RAP.ErrorContextList");
        asnTreePushTag("IFW_RAP.ErrorContext");
          asnTreeAddInteger("IFW_RAP.PathItemId.PATH_ITEM_ID", 
                             strToLong(paramList[TAP_ObjTag]));

          // check if an index is present
          checkNumber = strToLong(paramList[ObjArrayIdx]);
          if (checkNumber > 0)
          {
            asnTreeAddInteger("IFW_RAP.ItemOccurrence.ITEM_OCCURRENCE", checkNumber);
          }

          checkNumber = strToLong(paramList[ObjDepth]);
          asnTreeAddInteger("IFW_RAP.ItemLevel.ITEM_LEVEL", checkNumber);
        asnTreePop(); //  asnTreePushTag("IFW_RAP.ErrorContext");
      asnTreePop(); // asnTreePushTag("IFW_RAP_ErrorContextList");
      
      checkNumber = strToLong(paramList[ObjOffset]);
      if (checkNumber >= 0)
      {
        asnTreeAddInteger("IFW_RAP.ItemOffset.ITEM_OFFSET", checkNumber);
      }

      checkNumber = strToLong(paramList[TAP_ErrCode]);
      asnTreeAddInteger("IFW_RAP.ErrorCode.ERROR_CODE", checkNumber);
    asnTreePop(); // asnTreePushTag("IFW_RAP.ErrorDetail");
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleSevereError
  {
    Long    i;
    Long    paramCount=0;
    Bool    foundOne=false;

    rapDetailsWritten = rapDetailsWritten + 1;

    asnTreePushTag("IFW_RAP.SevereReturn");
    asnTreeAddInteger("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER", 
                      tapSequenceNumber);

    // insert call event details
    asnTreeAddBlob(edrTokenString());
    asnTreePushTag("IFW_RAP.ErrorDetailList");
    
    for ( i=0; i < edrNumErrors(); i=i+1 ) 
    { 
      if (edrGetError(i) == "ERR_TAP3_RET") 
      {
        // get parameter list 
        paramCount = edrGetErrorParameters(i, paramList);

        // check if enough parameters, and is severe error
        if ( (paramCount == MaxParamCount) and
             (paramList[TAP_Severity] == "severe") )
        {
          setSevereErrorList();
        }
      }
    }

    asnTreePop(); // asnTreePushTag("IFW_RAP.ErrorDetailList");
    asnTreePop(); // asnTreePushTag("IFW_RAP.SevereReturn");

    getTrailerInfos();
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------

  function Long checkErrorSeverity
  {
    Long i;
    Long paramCount;    
    Long detailSeverity = NoTap3Severity;

    for ( i=0; i < edrNumErrors(); i=i+1 ) 
    { 
      if (edrGetError(i) == "ERR_TAP3_RET") 
      {
        paramCount = edrGetErrorParameters(i, paramList);

        // check if enough parameters
        if (paramCount != MaxParamCount) 
        {
          if (detailSeverity < BadParamSeverity)
          {
            detailSeverity = BadParamSeverity;
          } 
          logPipeline( "ERROR: Insufficient parameters in container "
                     + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + "."
                     + " Expect "
                     + longToStr(MaxParamCount) + " but get " 
                     + longToStr(paramCount) );
        }
        else
        {
          if (paramList[TAP_Severity] == "severe")
          {
            if (detailSeverity < SevereSeverity)
            {
              detailSeverity = SevereSeverity;
            } 
          }
          else if (paramList[TAP_Severity] == "fatal")
          {
            if (detailSeverity < FatalSeverity)
            {
              detailSeverity = FatalSeverity;
            } 
          }
          else if (paramList[TAP_Severity] == "missing")
          {
            if (detailSeverity < MissingSeverity)
            {
              detailSeverity = MissingSeverity;
            } 
          }
          else if (paramList[TAP_Severity] == "warning")
          {
            if (detailSeverity < WarningSeverity)
            {
              detailSeverity = WarningSeverity;
            } 
          }
          else
          {
            logPipeline( "ERROR: Unknown severity for RAP " + paramList[TAP_Severity]);
            if (detailSeverity < UnknownSeverity)
            {
              detailSeverity = UnknownSeverity;
            } 
          }
        }
      }
    }
    return detailSeverity;
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
}
  

Grammar
{

  receiveStream0:
    receive_stream;

  receive_stream2:
    {
      asnTreeCreate();
      rapDetailsWritten = 0;
      detailCount       = 0;
    }
    HEADER
    details2_opt
    TRAILER
    {
      asnTreeFlush();
      asnTreeDelete();
    }
  ;

  details2_opt:
      detailList2
    | /* EMPTY */
    ;

  detailList2:
      detailList2
      oneDetail2
    | oneDetail2
    ;      
  
  oneDetail2:
    DETAIL
    {
      detailCount = detailCount + 1;
      if (detailCount == 2) 
      {
        asnTreePushTag("IFW_RAP.ReturnBatch");
        rapDetailsWritten = rapDetailsWritten + 1;
        asnTreeAddBlob(edrTokenString());
        asnTreePop(); // 
      }
    };


  receive_stream:
    {
      asnTreeCreate();
      asnTreePushTag("IFW_RAP.ReturnBatch");
    }
    header
    {
      asnTreePushTag("IFW_RAP.ReturnDetailList");
    }
    details_opt
    {
      asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnDetailList");
    }
    trailer
    {
      asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnBatch");
      asnTreeFlush();
      asnTreeDelete();
    }
  ;
  
  header:
    HEADER
    {
      initForNewHeader();
      
      asnTreePushTag("IFW_RAP.RapBatchControlInfo");
        asnTreeAddString("IFW_TAP3.Sender.PLMN_ID",   edrString(HEADER.SENDER) );
        asnTreeAddString("IFW_TAP3.Recipient.PLMN_ID",edrString(HEADER.RECIPIENT) );

        asnTreeAddInteger("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER",
                          rapSequenceNumber);

        asnTreePushTag("IFW_RAP.RapFileCreationTimeStamp");
          addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), headerUtcTimeOffset);
        asnTreePop(); //asnTreePushTag("IFW_RAP.RapFileCreationTimeStamp");

        asnTreePushTag("IFW_RAP.RapFileAvailableTimeStamp");
          addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), headerUtcTimeOffset);
        asnTreePop(); //asnTreePushTag("IFW_RAP.RapFileAvailableTimeStamp");

        asnTreeAddInteger("IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER",
                          edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) );      

        asnTreeAddInteger("IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER",
                          edrLong(HEADER.RELEASE_VERSION) );
                           
        asnTreeAddInteger("IFW_RAP.RapSpecificationVersionNumber.RAP_SPECIFICATION_VERSION_NUMBER",
                          RapSpecificationVersionNumber );

        asnTreeAddInteger("IFW_RAP.RapReleaseVersionNumber.RAP_RELEASE_VERSION_NUMBER",
                          RapReleaseVersionNumber );

        if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
        {
          asnTreeAddString("IFW_TAP3.FileTypeIndicator.FILE_TYPE_INDICATOR",  
                           edrString(HEADER.DATA_TYPE_INDICATOR) );
        }
                           
      asnTreePop(); //asnTreePushTag("IFW_RAP.RapBatchControlInfo");
    };
  
  details_opt:
      detailList
    | /* EMPTY */
    ;
    
  detailList:
      detailList
      oneDetail
    | oneDetail
    ;      
  
  oneDetail:
    DETAIL
    {
      detailCount = detailCount + 1;
      switch ( checkErrorSeverity() )
      {
        case SevereSeverity:
                handleSevereError();
        break;
        case MissingSeverity:
                handleMissingError();
        break;
        case FatalSeverity:
                handleFatalError();
        break;
        case WarningSeverity:
                handleWarningError();
        break;
        case UnknownSeverity:
                handleUnknownError();
        break;
        case BadParamSeverity:
                handleBadParamError();
        break;
        case NoTap3Severity:
                handleNoTap3Error();
        break;
      }
    };

  trailer:
    TRAILER
    {
      Long   i;
      String totalReturnedCharge = decimalToStrHex(round(wholesaleChargeSum * chargeMultiplier));
      asnTreePushTag("IFW_RAP.RapAuditControlInfo");
      
        // we build 1 RAP file for every TAP3 file, so the list can contain only 1 element
        asnTreePushTag("IFW_RAP.ReturnSummaryList");
          asnTreePushTag("IFW_RAP.ReturnSummary");
            asnTreeAddInteger("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER",
                              tapSequenceNumber);
            asnTreeAddString("IFW_RAP.SevereReturnValue.SEVERE_RETURN_VALUE",
                             totalReturnedCharge);
          asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnSummary");
        asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnSummaryList");

        asnTreeAddString("IFW_RAP.TotalSevereReturnValue.TOTAL_SEVERE_RETURN_VALUE",
                         totalReturnedCharge);

        asnTreeAddInteger("IFW_RAP.ReturnDetailsCount.RETURN_DETAILS_COUNT",
                          rapDetailsWritten);

      asnTreePop(); // asnTreePushTag("IFW_RAP.RapAuditControlInfo");
    };
}
