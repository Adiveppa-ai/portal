//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
//      
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

iScript
{
  use EXT_AsnTree;        // iScript extension to build a Tree of ASN.1 object
                          // used to fill the Length value of the ASN.1 bloc,
                          // before printing on output stream

  include "RAP_0103_MissingReturn.dsc";

  // constants
  const String extension_GSMW     ="520";
  const String extension_GPRS     ="540";
  const String extension_CONT     ="550";
  const String extension_LOCN     ="560";
  const String extension_SS_EVENT ="620";
  const String extension_BS_EVENT ="630";
  const String extension_CP       ="680";
  const String extension_TAP      ="670";
  const String extension_TP       ="695";
  const String extension_CAMEL    ="700";
  const String extension_VAS      ="710";
  const String extension_CBD      ="980"; //default CBD is global charge

  const String type_HEADER        ="010";
  const String type_TRAILER       ="090";
  const String type_MOC           ="021";
  const String type_MSS           ="029";
  const String type_MTC           ="031";
  const String type_GPRS_SG       ="040";
  const String type_GPRS_GG       ="042";
  const String type_GPRS_assembled="042"; //default for mixed ticket
  const String type_GPRS          ="042"; //default is mixed ticket
  const String type_SCU           ="050";
  const String type_VAS           ="060";
  const String type_CONT          ="070";
  const String type_LOCN          ="080";

  const Long RapSpecificationVersionNumber  = 1;
  const Long RapReleaseVersionNumber        = 3;

  //indexes to access parameters stored in the TAP3 error array
  const Long TAP_Severity     = 0;
  const Long TAP_ErrCode      = 1;
  const Long TAP_ObjTag       = 2;
  const Long ObjDepth         = 3;
  const Long ObjOffset        = 4;
  const Long ObjArrayIdx      = 5;  
  const Long ValidationRuleID = 6;
  const Long MaxParamCount    = 7;

  //indexes to access parameters stored in the TAP3 error(missing) array
  const Long Start_Seq_No_idx = 0;
  const Long End_Seq_No_idx   = 1;

  //registry string where to find user configurable values
  String reg_TapIOModule;
  String reg_RapOutStream;
  String reg_RapOutStreamPath;
  String reg_RapOutPrefix;
  String reg_RapSequencer;

  // storage of registry values
  String strRapOutStreamPath;
  String strRapOutPrefix;
  String strRapSequencer;
  
  String senderKeyStr;
  String startMissingSeqNumber; 
  String endMissingSeqNumber;
  String dataTypeIndicator;
  Long   tapSpecificationVersionNumber;
  Long   tapReleaseVersionNumber;
  
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
//  Long    theTap3SpecificationVersionNumber;
//  Long    theTap3ReleaseVersionNumber;
  String  defUtcTimeOffset;
  Long    rapDetailsWritten;
  Long    detailCount;
  String  rapSequenceNumber;
  String  tapSequenceNumber;
  Long    wholesaleChargeCount;
  Decimal wholesaleChargeSum;
  Decimal chargeMultiplier;

  Decimal wholesaleCharge[];
  String  paramList[];
  String  msgBuffer;

  String  toReturn_Sender;
  String  toReturn_Recipient;
  
  Bool missingErrorPresent;
  Bool fatalErrorPresent;
  Bool severeErrorPresent;
  String transId;
  
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function BEGIN
  {
    // init the variables
    actualSystime         = sysdate();
    defUtcTimeOffset      = "+0000";
    rapDetailsWritten     = 0;
    detailCount           = 0;
    rapSequenceNumber     = "";
    tapSequenceNumber     = "";
    wholesaleChargeCount  = 0;
    wholesaleChargeSum    = 0.0;
    chargeMultiplier      = 0.0;

    // initialisation of some constant values
    //---------------------------------------
    reg_TapIOModule       = registryNodeName();

    reg_RapOutStream      = reg_TapIOModule + ".Module.OutputStream.Module";

    reg_RapOutStreamPath  = reg_RapOutStream + ".OutputPath";
    strRapOutStreamPath   = regString(reg_RapOutStreamPath) + "/";

    reg_RapOutPrefix      = reg_RapOutStream + ".OutputPrefix";
    strRapOutPrefix       = regString(reg_RapOutPrefix);
 
    reg_RapSequencer      = reg_TapIOModule + ".Module.Sequencer";
    strRapSequencer       = regString(reg_RapSequencer);
    if (strRapSequencer  != "")
    {
      strRapSequencer= "ifw.SequencerPool."+strRapSequencer;
    }
    transId = "";
    dataTypeIndicator = "";
    tapSpecificationVersionNumber = -1;
    tapReleaseVersionNumber = -1;

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
  // -------------------------------------------------------------------------------------------
  function initForNewHeader
  {
    rapDetailsWritten     = 0;
    detailCount           = 0;
    wholesaleChargeCount  = 0;
    wholesaleChargeSum    = 0.0;
    chargeMultiplier      = 0.0;
    missingErrorPresent   = false;
    fatalErrorPresent     = false;
    severeErrorPresent    = false;
    startMissingSeqNumber = "";
    endMissingSeqNumber   = "";
    senderKeyStr          = "";
    
    headerUtcTimeOffset   = edrString(HEADER.UTC_TIME_OFFSET);
    transId               = edrString(HEADER.TRANS_ID);
    tapSequenceNumber     = longToStr(edrLong(HEADER.ORIGIN_SEQUENCE_NUMBER));
    rapSequenceNumber     = longToStr(edrLong(HEADER.SEQUENCE_NUMBER));
    tapSpecificationVersionNumber = edrLong(HEADER.SPECIFICATION_VERSION_NUMBER);
    tapReleaseVersionNumber = edrLong(HEADER.RELEASE_VERSION);
    dataTypeIndicator     = edrString(HEADER.DATA_TYPE_INDICATOR);
    toReturn_Sender       = edrString(HEADER.RECIPIENT);
    toReturn_Recipient    = edrString(HEADER.SENDER);

    //Make the Sequence number length to five
    switch (strLength(tapSequenceNumber))
    {
      case 0 : tapSequenceNumber="00000";                   break;
      case 1 : tapSequenceNumber="0000"+tapSequenceNumber;  break;
      case 2 : tapSequenceNumber="000"+tapSequenceNumber;   break;
      case 3 : tapSequenceNumber="00"+tapSequenceNumber;    break;
      case 4 : tapSequenceNumber="0"+tapSequenceNumber;     break;
      default:                                              break;
    }

    switch (strLength(rapSequenceNumber))
    {
      case 0 : rapSequenceNumber="00000";                   break;
      case 1 : rapSequenceNumber="0000"+rapSequenceNumber;  break;
      case 2 : rapSequenceNumber="000"+rapSequenceNumber;   break;
      case 3 : rapSequenceNumber="00"+rapSequenceNumber;    break;
      case 4 : rapSequenceNumber="0"+rapSequenceNumber;     break;
      default:                                              break;
    }
    
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
    //asnTreePushTag("RAP_0103.FatalReturn");
    //asnTreePop(); // asnTreePushTag("RAP_0103.FatalReturn");
    logPipeline("INFO on RAP output: EDR " + longToStr(edrLong(DETAIL.RECORD_NUMBER)) + 
                " contains an ERR_TAP3_RET with the Fatal severity (ie. rollback)");
    edrReject(); // send the EDR back to the standard reject stream (for recycling)
  }
  
  // -------------------------------------------------------------------------------------------
  //    handleMissingError
  // -------------------------------------------------------------------------------------------
  function handleMissingError
  {
    String sendArray[];
    String receiveArray[];
    String toReturn_RapSeqNum;
    String toReturn_RapFileName;
    String current_StreamName  = CURRENT_STREAM_NAME;

    //Create the return RAP file name
    if (current_StreamName != "")
    {
      toReturn_RapFileName = strRapOutStreamPath + strRapOutPrefix
                                      + toReturn_Sender + toReturn_Recipient;

      //Get a new Rap sequence number
      arrayClear( sendArray    );
      arrayClear( receiveArray );
      sendArray[0] = transId;
      sendArray[1] = "00000";

      //Setting the SEQ_GEN_KEY
      if ( senderKeyStr != "" )
      {
        sendArray[2] = senderKeyStr;
      }
      else
      {
        sendArray[2] = "-1";
      }

      //Request for a new sequence number
      if (strRapSequencer != "" and severeErrorPresent == true)
      {
        if ( reqSend(strRapSequencer, "REQ_NEWSEQUENCENUMBER",
                     sendArray, receiveArray)==true )
        {
          toReturn_RapSeqNum = receiveArray[0];
          msgBuffer="MISSING_SEQ: stream(" +current_StreamName+
                      "), The Missing RAP file generated with a RapSequence(" +toReturn_RapSeqNum+")";
          logPipeline(msgBuffer, 1);
        }
        else // reqSend(strRapSequencer ....)
        {
          toReturn_RapSeqNum = "";
          msgBuffer="MISSING_SEQ: stream(" +current_StreamName+
                                       ") could NOT get a RapSequence";
          logPipeline(msgBuffer, 1);
        }
      }
      else 
      {
        // This is to make sure that streamIsEmpty returns False
        // when sequence generated for Severe RAP is reused by Missing RAP.
        rapDetailsWritten = rapDetailsWritten + 1;
        toReturn_RapSeqNum = rapSequenceNumber;
      }

      if (toReturn_RapSeqNum != "")
      {

        //Making the fields to standard length five
        toReturn_RapSeqNum = strPad(toReturn_RapSeqNum, "0", 5, false);  
        startMissingSeqNumber = strPad(startMissingSeqNumber, "0", 5, false);
        endMissingSeqNumber   = strPad(endMissingSeqNumber  , "0", 5, false);

        //Put the Sequence number into the Filename
        toReturn_RapFileName = toReturn_RapFileName + toReturn_RapSeqNum;

        //  ASN Tree creation for Missing Sequence case 

        asnTreeCreate();

        asnTreePushTag("RAP_0103.ReturnBatch");
           Long returnBatchIdx = asnTreeStoreNode();
        asnTreePop(); // asnTreePushTag("RAP_0103.ReturnBatch");
    
        asnTreeGetStoredNode(returnBatchIdx); //Setting returnBatch as active node
  
        asnTreePushTag("RAP_0103.RapBatchControlInfo");
        asnTreeAddString("TAP_0311.Sender.Sender",    toReturn_Sender);
        asnTreeAddString("TAP_0311.Recipient.Recipient", toReturn_Recipient);
  
        asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber",
                            toReturn_RapSeqNum);
  
        asnTreePushTag("RAP_0103.RapFileCreationTimeStamp");
          addDateTimeLong(dateToStr(sysdate()), "+0000");
        asnTreePop(); //asnTreePushTag("RAP_0103.RapFileCreationTimeStamp");
  
        asnTreePushTag("RAP_0103.RapFileAvailableTimeStamp");
         addDateTimeLong(dateToStr(sysdate()), "+0000");
        asnTreePop(); //asnTreePushTag("RAP_0103.RapFileAvailableTimeStamp");
  
        asnTreeAddInteger("TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber",
                            tapSpecificationVersionNumber );
							
        asnTreeAddInteger("TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber", 
                            tapReleaseVersionNumber );
							
        asnTreeAddInteger("RAP_0103.RapSpecificationVersionNumber.RapSpecificationVersionNumber",
                          RapSpecificationVersionNumber );

        asnTreeAddInteger("RAP_0103.RapReleaseVersionNumber.RapReleaseVersionNumber",
                          RapReleaseVersionNumber );

        if (dataTypeIndicator == "T")
        {
          asnTreeAddString("TAP_0311.FileTypeIndicator.FileTypeIndicator", 
		                    dataTypeIndicator );
        }

        asnTreeAddInteger("TAP_0311.TapDecimalPlaces.TapDecimalPlaces",3);
  
        asnTreePop(); //asnTreePushTag("RAP_0103.RapBatchControlInfo");
  
        //Create the missing RAP
        writeMissingRapFile( toReturn_RapFileName,
                      startMissingSeqNumber,
                      endMissingSeqNumber,
                      tapSequenceNumber 
                      );
        if (strRapSequencer != "" and severeErrorPresent == true)
        {
          asnTreeFlush(toReturn_RapFileName);
        }
        else
        {
          asnTreeFlush();
        }
        asnTreeDelete();
  

        msgBuffer="MISSING_SEQ: Generated a Missing RAPfile("+toReturn_RapFileName+
                  ") for input stream("+current_StreamName+")";
        logPipeline(msgBuffer, 0);
      } 
    }
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
    Long    i;
    Long    nbElem;
    String  tags[];

    nbElem = strSplit(tags, paramList[TAP_ObjTag], ",");
 
    asnTreePushTag("RAP_0103.ErrorDetail");
      asnTreePushTag("RAP_0103.ErrorContextList");

      for (i=0 ; i < nbElem ; i=i+1)
      { 
        asnTreePushTag("RAP_0103.ErrorContext");

          asnTreeAddInteger("RAP_0103.PathItemId.PathItemId",
                             strToLong(tags[i]));
          //TO DO - ItemOccurrence 
          asnTreeAddInteger("RAP_0103.ItemLevel.ItemLevel", i+1);

        asnTreePop(); //  asnTreePushTag("RAP_0103.ErrorContext");
      }

      asnTreePop(); // asnTreePushTag("RAP_0103.ErrorContextList");
      
      checkNumber = strToLong(paramList[ObjOffset]);
      if (checkNumber >= 0)
      {
        asnTreeAddInteger("RAP_0103.ItemOffset.ItemOffset", checkNumber);
      }

      checkNumber = strToLong(paramList[TAP_ErrCode]);
      asnTreeAddInteger("RAP_0103.ErrorCode.ErrorCode", checkNumber);
    asnTreePop(); // asnTreePushTag("RAP_0103.ErrorDetail");
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function handleSevereError
  {
    Long    i;
    Long    paramCount=0;
    Bool    foundOne=false;

    rapDetailsWritten = rapDetailsWritten + 1;

    asnTreePushTag("RAP_0103.SevereReturn");
    asnTreeAddString("TAP_0311.FileSequenceNumber.FileSequenceNumber", 
                      tapSequenceNumber);

    // insert call event details
    asnTreeAddBlob(edrTokenString());
    asnTreePushTag("RAP_0103.ErrorDetailList");
    
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

    asnTreePop(); // asnTreePushTag("RAP_0103.ErrorDetailList");
    asnTreePop(); // asnTreePushTag("RAP_0103.SevereReturn");

    getTrailerInfos();
  }

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------

  function Long checkErrorSeverity
  {
    Long i;
    Long paramCount;    
    Long detailSeverity = NoTap3Severity;

    String dupErr = "";
    String dupTag = "";

   if ( edrHasError("INF_DUPLICATE_EDR") == true )
   {
     switch(edrString(DETAIL.RECORD_TYPE))
     {
       case type_MOC:
         {
           dupErr = "250";
           dupTag = "9";
         }
         break;

       case type_MTC:
         {
           dupErr = "251";
           dupTag = "10";
         }
         break;

       case type_MSS:
         {
           dupErr = "252";
           dupTag = "11";
         }
         break;

       case type_SCU:
         {
           dupErr = "253";
           dupTag = "12";
         }
         break;

       case type_GPRS:
         {
           dupErr = "255";
           dupTag = "14";
         }
         break;

       case type_CONT:
         {
           dupErr = "256";
           dupTag = "17";
         }
         break;

       case type_LOCN:
         {
           dupErr = "257";
           dupTag = "297";
         }
         break;
     }

     edrAddError("ERR_TAP3_RET", 3, "severe", dupErr, dupTag, "2", "0", "-1", "Call or event is duplicate");
     edrAddError("ERR_TAP3_SEVERE", 3, "ValidationRule ", dupTag, dupErr, "Call or event is duplicate"); 
     edrSetIsValidDetail(false);
   }

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
            severeErrorPresent = true;
            if (detailSeverity < SevereSeverity)
            {
              detailSeverity = SevereSeverity;
            } 
          }
          else if (paramList[TAP_Severity] == "fatal")
          {
            fatalErrorPresent = true;
            if (detailSeverity < FatalSeverity)
            {
              detailSeverity = FatalSeverity;
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
     else if (edrGetError(i) == "ERR_GAP_IN_SEQ_NUMBER")
      {

        //Incase of GAP error, set the severity to missing
        detailSeverity = MissingSeverity;
        missingErrorPresent = true;
        if (edrString(HEADER.SEQ_GEN_KEY) == edrString(HEADER.SENDER))
        {
          senderKeyStr = edrString(HEADER.SENDER);
        }

        //Get the error parameters
        paramCount = edrGetErrorParameters(i, paramList);

        //Get the missing sequence numbers
        startMissingSeqNumber = paramList[Start_Seq_No_idx];
        endMissingSeqNumber   = paramList[End_Seq_No_idx];
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
        asnTreePushTag("RAP_0103.ReturnBatch");
        rapDetailsWritten = rapDetailsWritten + 1;
        asnTreeAddBlob(edrTokenString());
        asnTreePop(); // 
      }
    };


  receive_stream:
    {
      asnTreeCreate();
      asnTreePushTag("RAP_0103.ReturnBatch");
         Long returnBatchIdx = asnTreeStoreNode();
      asnTreePop(); // asnTreePushTag("RAP_0103.ReturnBatch");

      asnTreeGetStoredNode(returnBatchIdx); //Setting returnBatch as active node
    }
    header
    {
      asnTreePushTag("RAP_0103.ReturnDetailList");
    }
    details_opt
    {
      asnTreePop(); // asnTreePushTag("RAP_0103.ReturnDetailList");
    }
    trailer
    {

      // In case a TAP file is not having Severe error but has Missing error
      // we want to reuse the Sequence used for Severe RAP for Missing RAP file.
      if ( severeErrorPresent == true or missingErrorPresent == false )
      {
        asnTreeFlush();
      }

      // Delete the data created for Severe RAP file.
      asnTreeDelete();

      // RAP missing should be only generated when the TAP file has no Fatal errors
      if ( missingErrorPresent == true and fatalErrorPresent == false)
      {
        //Getting the missing error details
        handleMissingError();
      }
    }
  ;
  
  header:
    HEADER
    {
      initForNewHeader();
      
      asnTreePushTag("RAP_0103.RapBatchControlInfo");

        toReturn_Sender = edrString(HEADER.RECIPIENT);
        toReturn_Recipient = edrString(HEADER.SENDER);

        asnTreeAddString("TAP_0311.Sender.Sender",    toReturn_Sender);
        asnTreeAddString("TAP_0311.Recipient.Recipient", toReturn_Recipient);

        asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber",
                          rapSequenceNumber);

        asnTreePushTag("RAP_0103.RapFileCreationTimeStamp");
          addDateTimeLong(dateToStr(actualSystime), headerUtcTimeOffset);
        asnTreePop(); //asnTreePushTag("RAP_0103.RapFileCreationTimeStamp");

        asnTreePushTag("RAP_0103.RapFileAvailableTimeStamp");
          addDateTimeLong(dateToStr(actualSystime), headerUtcTimeOffset);
        asnTreePop(); //asnTreePushTag("RAP_0103.RapFileAvailableTimeStamp");

        asnTreeAddInteger("TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber",
                          edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) );      

        asnTreeAddInteger("TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber",
                          edrLong(HEADER.RELEASE_VERSION) );
                           
        asnTreeAddInteger("RAP_0103.RapSpecificationVersionNumber.RapSpecificationVersionNumber",
                          RapSpecificationVersionNumber );

        asnTreeAddInteger("RAP_0103.RapReleaseVersionNumber.RapReleaseVersionNumber",
                          RapReleaseVersionNumber );

        if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
        {
          asnTreeAddString("TAP_0311.FileTypeIndicator.FileTypeIndicator",  
                           edrString(HEADER.DATA_TYPE_INDICATOR) );
        }
        
        if (edrLong(HEADER.TAP_DECIMAL_PLACES) >= 0)
        {
          asnTreeAddInteger("TAP_0311.TapDecimalPlaces.TapDecimalPlaces",
                              edrLong(HEADER.TAP_DECIMAL_PLACES) );
        }
                          
      asnTreePop(); //asnTreePushTag("RAP_0103.RapBatchControlInfo");

      //Check whether Missing error is set in Header
      if (checkErrorSeverity() == MissingSeverity)
      {
         //Getting the missing error details
      }
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

     if (checkErrorSeverity() == MissingSeverity)
      {
         //Getting the missing error details
      }

      Long   i;
      Long   rapDetailsCount = rapDetailsWritten; // From RAP1.3 (TD32311.doc) onwards 
						//Number of RAP Severe returned details 


      Long totalReturnedCharge = decimalToLong(round(wholesaleChargeSum * chargeMultiplier));

      asnTreePushTag("RAP_0103.RapAuditControlInfo");
      
        // we build 1 RAP file for every TAP3 file, so the list can contain only 1 element
        asnTreePushTag("RAP_0103.ReturnSummaryList");
          asnTreePushTag("RAP_0103.ReturnSummary");
            asnTreeAddString("TAP_0311.FileSequenceNumber.FileSequenceNumber",
                              tapSequenceNumber);
            asnTreeAddInteger("RAP_0103.SevereReturnValue.SevereReturnValue",
                             totalReturnedCharge);
          asnTreePop(); // asnTreePushTag("RAP_0103.ReturnSummary");
        asnTreePop(); // asnTreePushTag("RAP_0103.ReturnSummaryList");

      asnTreeAddInteger("RAP_0103.TotalSevereReturnValue.TotalSevereReturnValue",
                       totalReturnedCharge);

      asnTreeAddInteger("RAP_0103.ReturnDetailsCount.ReturnDetailsCount",
                        rapDetailsCount);

      asnTreePop(); // asnTreePushTag("RAP_0103.RapAuditControlInfo");
    };
}
