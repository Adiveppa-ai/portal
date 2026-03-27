//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD/CIBER
//------------------------------------------------------------------------------
// Module Description:
//   input grammar file for the CIBER v 2.5 format.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: cdiab
//
// $RCSfile: CIBER_v25_InGrammar.dsc,v $
// $Revision: 1.0 $
// $Author: cdiab $
// $Date: 2002/04/15 13:54:55 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: CIBER_v25_InGrammar.dsc,v $
// Log 2002/08/29 cdiab
// -store the wholesale charge and tax on the DETAIL
// -updated the DETAIL fields
// -activated the batch validation check for totalWholesaleCharge
//
// Log 2002/08/21 cdiab
// -set the DETAIL.ASS_CIBER_EXT.RECORD_TYPE to "702"
// -made foundReasonToReject global to ensure that Batch reject is only requested
//  once (on the first error)
// -corrected the check of the Batch creation date condition
// -commented the check of the totalWholesaleCharge as long as its calculation is
//  not implemented
//
// Log 2002/07/12 cdiab
// -corrected storing of the filler for the trailer
//
// Revision 1.0  2002/04/15 13:54:55  cdiab
// -Creation
//
//==============================================================================

//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  // Error processing for Batch Reject
  const Long CIBER_Header_OriginalReturnIndicator_Start = 23;
  const Long CIBER_Header_OriginalReturnIndicator_Size  = 1;
  const Long CIBER_Header_BatchRejectReasonCode_Start = 33;
  const Long CIBER_Header_BatchRejectReasonCode_Size  = 2;
  const Decimal SECONDS = 60.0;
  String toReturn_StreamName     = "";
  String toReturn_ErrFileName    = "";
  String toReturn_RetFileName    = "";
  String toReturn_RetTmpFileName = "";
  String toReturn_RetInd         = "";
  String toReturn_RejReason      = "";

  //some defaults
  const String defTelNumber     = "000";
  const String defUtcTimeOffset = "+0000";
  const String defCauseForTerm  = "22"; //for CIBER - calledParty answered, and normal termination
  const String servingSIDPrefix = "0000";

  // call directions
  const String record_MOC    = "1"; // Originating Call
  const String record_MTC    = "2"; // Terminating Call

  // integrate Record IDs
  const String type_HEADER        ="010";
  const String type_TRAILER       ="090";
  const String type_CIBER         ="701"; // TODO check if it is OK to use this ID
  const String extension_CIBER    ="702"; // TODO check if it is OK to use this ID

  //registry string where to find user configurable values
  String reg_Pipeline;
  String reg_IOModule;
  String reg_InputStream;
  String reg_RetSequencer;
  String strRetSequencer;

  // globals
  Long    totalNumBasics;
  Long    recordNumber;
  String  msgBuffer;
  Bool    checkForBatchRejectFlag;
  Bool    foundReasonToReject;

  Date    transferCutOff;
  Date    firstCall;
  Date    lastCall;
  Decimal totalWholesaleCharge;
  Decimal totalWholesaleTax;
  Decimal totalRetailCharge;
  Decimal totalRetailTax;

  //storage of Header information
  String batchContents;
  Date   batchCreation;
  String sendingCarrier;
  String receivingCarrier;
  
  function initializeForNewHeader
  {
    batchContents    = edrString(HEADER.BATCH_CONTENTS);
    batchCreation    = edrDate(HEADER.CREATION_TIMESTAMP);
    sendingCarrier   = edrString(HEADER.SENDER);
    receivingCarrier = edrString(HEADER.RECIPIENT);
  }
  
  function onParseError
  {
    logPipeline( "CIBER_ERROR at BytePos @"+longToStr(ERROR_TOKEN_BYTEPOS)+
    		 " (ie. @0x"+longToHexStr(ERROR_TOKEN_BYTEPOS)+
    		 "), Token hex content=<"+ERROR_TOKEN_HEX+">",3);
    logPipeline( "number of received Ciber records= "+longToStr(totalNumBasics),3);
  }

  function onParseStart
  {
    lexState("STATE_CIBERV25");
  }

  function BEGIN
  {
    // initialisation of some constant values
    //---------------------------------------
    reg_Pipeline     = "ifw.Pipelines." + pipelineName();
    reg_IOModule     = registryNodeName();
    reg_InputStream  = reg_IOModule + ".Module.InputStream.Module";
//logStdout("reg_InputStream(input) = "+reg_InputStream+"\n");
    reg_RetSequencer = reg_IOModule + ".Sequencer";
    strRetSequencer  = regString(reg_RetSequencer);
    if (strRetSequencer != "")
    {
      strRetSequencer= "ifw.SequencerPool."+strRetSequencer;
    }
    
    checkForBatchRejectFlag = true;
  }

  function Bool onRollback
  {
    String transID      = decimalToStr( tamTransId() );
    Long   nbTransItems = tamNumTransItems();
    String sendArray[];
    String receiveArray[];
    
    msgBuffer="ROLLBACK: called in CIBER input for transID("+transID+
              "), we have the stream("+toReturn_StreamName+
              ") which is waiting for this rollback";
//logStdout(msgBuffer+"\n");
        
    //toReturn_StreamName = CURRENT_STREAM_NAME; //for testing

    // set defaults for the fields that we must request from other modules
    toReturn_ErrFileName    = "";
    toReturn_RetFileName    = "";
    toReturn_RetTmpFileName = "";

    // get the real name of the rollbacked files that need to be post-processed
    //-------------------------------------------------------------------------
    if (toReturn_StreamName != "")
    {
      Long   i;
      // first, make sure it is really part of this transaction!
      for ( i=0; i<nbTransItems; i=i+1 ) 
      { 
        if ( tamStreamName(i) == toReturn_StreamName )
        {
          // get the error filename
          arrayClear( sendArray    );
          arrayClear( receiveArray );
          sendArray[0] = toReturn_StreamName ;
          if ( reqSend( reg_InputStream, "REQ_ERROR_FILENAME",
                        sendArray, receiveArray)==true )
          {
            toReturn_ErrFileName = receiveArray[0];
            if (toReturn_ErrFileName == toReturn_StreamName)
            {
              toReturn_ErrFileName = "";
            }
          }
          //get the return filename
          arrayClear( sendArray    );
          arrayClear( receiveArray );
          sendArray[0] = toReturn_StreamName ;
          if ( reqSend( reg_InputStream, "REQ_RETURN_FILENAME",
                        sendArray, receiveArray)==true )
          {
            toReturn_RetFileName = receiveArray[0];
            if (toReturn_RetFileName == toReturn_StreamName)
            {
              toReturn_RetFileName = "";
            }
          }
          //get the temporary return filename
          arrayClear( sendArray    );
          arrayClear( receiveArray );
          sendArray[0] = toReturn_StreamName ;
          if ( reqSend( reg_InputStream, "REQ_RETURN_TEMP_FILENAME",
                        sendArray, receiveArray)==true )
          {
            toReturn_RetTmpFileName = receiveArray[0];
            if (toReturn_RetTmpFileName == toReturn_StreamName)
            {
              toReturn_RetTmpFileName = "";
            }
          }
          
          msgBuffer="ROLLBACK: stream(" +toReturn_StreamName+
                  "), ErrorFile(" +toReturn_ErrFileName+
                  "), ReturnFile(" +toReturn_RetFileName+
                  "), ReturnTmpFile(" +toReturn_RetTmpFileName+")";
          logPipeline(msgBuffer,0);
//logStdout(msgBuffer+"\n");
        }
      }

      if (toReturn_ErrFileName != "")
      {
        msgBuffer="ROLLBACK: Returning stream("+toReturn_StreamName+
                  ") as CiberReturnFile("+toReturn_RetFileName+")";
//logStdout(msgBuffer+"\n");
                    
        if ( fileCopy( toReturn_ErrFileName, toReturn_RetTmpFileName) == false )
        {
          msgBuffer="ROLLBACK: FAILED copying the ErrFileName("+toReturn_ErrFileName+
                  ") to the RetTmpFileName("+toReturn_RetTmpFileName+")";
//logStdout(msgBuffer+"\n");
        }
        else
        {
          msgBuffer="ROLLBACK: SUCCESS copying the ErrFileName("+toReturn_ErrFileName+
                  ") to the RetTmpFileName("+toReturn_RetTmpFileName+")";
//logStdout(msgBuffer+"\n");
        }

        // build the returned CIBER file
        File retFilePtr;
        if ( fileOpen( retFilePtr, toReturn_RetTmpFileName, "r+" ) == true )
        {
          // update the return Indicator and reason
          String firstLine;
          fileReadLine( retFilePtr, firstLine, 255 );
          firstLine = strReplace( firstLine,
                                  CIBER_Header_OriginalReturnIndicator_Start,
                                  CIBER_Header_OriginalReturnIndicator_Size,
                                  toReturn_RetInd);
          firstLine = strReplace( firstLine,
                                  CIBER_Header_BatchRejectReasonCode_Start,
                                  CIBER_Header_BatchRejectReasonCode_Size,
                                  toReturn_RejReason);
          fileSeek( retFilePtr, 0 );
          if ( fileWriteStr( retFilePtr, firstLine ) == false )
          {
            msgBuffer="ROLLBACK: FAILED writing the returnInd/ReasonCode to file";
//logStdout(msgBuffer+"\n");
          }
          else
          {
            msgBuffer="ROLLBACK: SUCCESS writing the returnInd/ReasonCode to file";
//logStdout(msgBuffer+"\n");
          }
          
          // close the file
          fileClose( retFilePtr );

          // rename the tmpRetFile to retFile
          if (fileRename(toReturn_RetTmpFileName, toReturn_RetFileName) == false)
          {
            msgBuffer="ROLLBACK: FAILED renaming ("+toReturn_RetTmpFileName+
                  ") to ("+toReturn_RetFileName+")";
//logStdout(msgBuffer+"\n");
          }
          else
          {
            msgBuffer="ROLLBACK: SUCCESS renaming ("+toReturn_RetTmpFileName+
                  ") to ("+toReturn_RetFileName+")";
//logStdout(msgBuffer+"\n");
          }
        }
        else
        {
            msgBuffer="ROLLBACK: FAILED opening ("+toReturn_ErrFileName+")";
//logStdout(msgBuffer+"\n");
        }
      }
      else
      {
        msgBuffer="ROLLBACK: could not identify the errorstream for the input "+
                  "streamname("+toReturn_StreamName+"), so no return is possible";
//logStdout(msgBuffer+"\n");
      }
    }
    
    //reinitialization for next time...
    toReturn_StreamName     = "";
    toReturn_ErrFileName    = "";
    toReturn_RetFileName    = "";
    toReturn_RetTmpFileName = "";
    toReturn_RetInd         = "";
    toReturn_RejReason      = "";
    return true; //must return true if you dont want to stop integrate!
  }

  function resetStatisticValues
  {
    totalNumBasics       = 0;
    recordNumber         = 1; //the HEADER
    firstCall            = MAX_DATE;
    lastCall             = MIN_DATE;
    totalWholesaleCharge = 0.0;
    totalWholesaleTax    = 0.0;
    totalRetailCharge    = 0.0;
    totalRetailTax       = 0.0;
    transferCutOff       = edrDate( HEADER.TRANSFER_CUTOFF_TIMESTAMP );
  }

  function checkStatisticValues
  {
    // check the total number of basic records in the file
    if ( totalNumBasics != edrLong( TRAILER.TOTAL_NUMBER_OF_RECORDS ) )
    {
      edrAddError( "ERR_INVALID_RECORD_NUMBER", 3,
                   edrString( TRAILER.TOTAL_NUMBER_OF_RECORDS ),
                   longToStr( totalNumBasics ) );
    }
  }

  function updateBasicDetail(Long ciberRecordType)
  {
    String callDirection = "";
    String servingSID = "";
    // integrate defaults
    edrLong(DETAIL.DISCARDING)                         = 0;
    edrLong(DETAIL.A_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.A_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.A_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_A_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.B_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.B_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.B_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_B_NUMBER_ZONE)             = defTelNumber;
    edrLong(DETAIL.C_TYPE_OF_NUMBER)                   = 0;      // unknown
    edrString(DETAIL.C_NUMBERING_PLAN)                 = "0";
    edrString(DETAIL.C_NUMBER)                         = defTelNumber;
    edrString(DETAIL.INTERN_C_NUMBER_ZONE)             = defTelNumber;
    edrString(DETAIL.USAGE_DIRECTION)                  = "0";
    edrString(DETAIL.BASIC_SERVICE)                    = "011";
    edrString(DETAIL.CALL_COMPLETION_INDICATOR)        = defCauseForTerm;   // normal charging
    edrString(DETAIL.LONG_DURATION_INDICATOR)          = "S";    // single record (no chain)
    edrDate(DETAIL.CHARGING_START_TIMESTAMP)           = MIN_DATE;
    //edrDate(DETAIL.CHARGING_END_TIMESTAMP)             = MIN_DATE;
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
    
    // this stream's defaults
    edrDecimal(DETAIL.RETAIL_CHARGED_AMOUNT_VALUE)     = 0.0;
    edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE)  = 0.0;
    edrDecimal(DETAIL.RETAIL_CHARGED_TAX_VALUE)        = 0.0;
    edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE)     = 0.0;
    edrDate(DETAIL.CHARGING_START_TIMESTAMP)           = batchCreation;
    edrString(DETAIL.SOURCE_NETWORK)                   = sendingCarrier;
    edrString(DETAIL.DESTINATION_NETWORK)              = receivingCarrier;
    edrString(DETAIL.A_NUMBER)                         = defTelNumber;
    edrString(DETAIL.B_NUMBER)                         = defTelNumber;

    // Building the number strings out of the (len, no, overflow) triplet
    Long telnumLen = 0;
    switch ( ciberRecordType )
    { 
      case 10: 
      case 20:
      case 30:
      {
        telnumLen = edrLong(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO_LENGTH, 0);
        if (telnumLen <= 10)
        {
          edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0) =
                strSubstr(edrString(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO, 0),
                          0, telnumLen );
        }
        else
        {
          edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0) =
                edrString(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO, 0) +
                strSubstr(edrString(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO_OVERFLOW, 0),
                          0, (telnumLen-10) );
        }

        telnumLen = edrLong(DETAIL.ASS_CIBER_EXT.CALLED_NO_LENGTH, 0);
        if (telnumLen <= 10)
        {
          edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLED_NO, 0) =
                strSubstr(edrString(DETAIL.ASS_CIBER_EXT.CALLED_NO, 0),
                          0, telnumLen );
        }
        else
        {
          edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLED_NO, 0) =
                edrString(DETAIL.ASS_CIBER_EXT.CALLED_NO, 0) +
                strSubstr(edrString(DETAIL.ASS_CIBER_EXT.CALLED_NO_OVERFLOW, 0),
                          0, (telnumLen-10) );
        }
      }
      break;
      case 11:
      case 50:
      case 70:
      {
        telnumLen = edrLong(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO_LENGTH, 0);
        if (telnumLen <= 10)
        {
          edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0) =
                strSubstr(edrString(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO, 0),
                          0, telnumLen );
        }
        else
        {
          edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0) =
                edrString(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO, 0) +
                strSubstr(edrString(DETAIL.ASS_CIBER_EXT.MOBILE_ID_NO_OVERFLOW, 0),
                          0, (telnumLen-10) );
        }
      }
      break;
      case 22:
      case 32:
      {
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_MSISDN_MDN, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.MSISDN_MDN, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.MSISDN_MDN_LENGTH, 0) );
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLER_ID, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.CALLER_ID, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.CALLER_ID_LENGTH, 0) );
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLED_NO, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.CALLED_NO, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.CALLED_NO_LENGTH, 0) );
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_ROUTING_NO, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.ROUTING_NO, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.ROUTING_NO_LENGTH, 0) );
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_TLDN_NO, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.TLDN_NO, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.TLDN_NO_LENGTH, 0) );
      }
      break;
      case 42:
      {
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_MSISDN_MDN, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.MSISDN_MDN, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.MSISDN_MDN_LENGTH, 0) );
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_ROUTING_NO, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.ROUTING_NO, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.ROUTING_NO_LENGTH, 0) );
      }
      break;
      case 52:
      {
        edrString(DETAIL.ASS_CIBER_EXT.INTERN_MSISDN_MDN, 0) =
              strSubstr(edrString(DETAIL.ASS_CIBER_EXT.MSISDN_MDN, 0),
                        0, edrLong(DETAIL.ASS_CIBER_EXT.MSISDN_MDN_LENGTH, 0) );
      }
      break;
      default:
      {
        // nothing to do
      	// record is of unknown type: error already detected in mapCiberRecord()
      }
      break;
    }
    
    //get the total wholesale tax and charge (same for every record type)
    edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE) =
        edrDecimal(DETAIL.ASS_CIBER_EXT.TOTAL_STATE_TAX, 0) +
        edrDecimal(DETAIL.ASS_CIBER_EXT.TOTAL_LOCAL_TAX, 0);
    edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) =
        edrDecimal(DETAIL.ASS_CIBER_EXT.TOTAL_CHARGE_AND_TAX, 0) -
        edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE);
    
    
    //Here, update the Basic Detail fields specifics for each record type
    switch ( ciberRecordType )
    { 
      case 10: 
      case 20:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.HOME_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0);
        edrString(DETAIL.B_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLED_NO, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CALL_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.SSU_CONNECT_TIME, 0)) );

        edrDecimal(DETAIL.DURATION)          =
		strToDecimal(strSubstr(edrString(DETAIL.ASS_CIBER_EXT.SSU_CHARGEABLE_TIME,
			 0), 0, 4) ) * SECONDS +
			 strToDecimal(strSubstr(edrString(DETAIL.ASS_CIBER_EXT.SSU_CHARGEABLE_TIME,
			 0), 4, 2) );
        edrString(DETAIL.CONNECT_TYPE)       = edrString(DETAIL.ASS_CIBER_EXT.CALL_DIRECTION, 0);
        edrString(DETAIL.CALL_COMPLETION_INDICATOR) =
                edrString(DETAIL.ASS_CIBER_EXT.CALL_COMPLETION_INDICATOR, 0) +
                edrString(DETAIL.ASS_CIBER_EXT.CALL_TERMINATION_INDICATOR, 0);
      }
      break;
      case 11:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SENDING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.RECV_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CALL_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CONNECT_TIME, 0)) );
        edrDecimal(DETAIL.DURATION)          = strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0),
			 0, 4) ) * SECONDS + strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0), 4, 2) );
      }
      break;
      case 22:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.HOME_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLER_ID, 0);
        edrString(DETAIL.B_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLED_NO, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CALL_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.AIR_CONNECT_TIME, 0)) );
        edrDecimal(DETAIL.DURATION)          = strToDecimal(strSubstr(
		edrString(DETAIL.ASS_CIBER_EXT.AIR_CHARGEABLE_TIME, 0), 0, 4)) * SECONDS +
		strToDecimal(strSubstr(edrString(DETAIL.ASS_CIBER_EXT.AIR_CHARGEABLE_TIME, 0), 4, 2));
        edrString(DETAIL.CONNECT_TYPE)       = edrString(DETAIL.ASS_CIBER_EXT.CALL_DIRECTION, 0);
        edrString(DETAIL.CALL_COMPLETION_INDICATOR) =
                edrString(DETAIL.ASS_CIBER_EXT.CALL_COMPLETION_INDICATOR, 0) +
                edrString(DETAIL.ASS_CIBER_EXT.CALL_TERMINATION_INDICATOR, 0);
      }
      break;
      case 30:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.HOME_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0);
        edrString(DETAIL.B_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLED_NO, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CALL_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CONNECT_TIME, 0)) );
        edrDecimal(DETAIL.DURATION)          = strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0),
			 0, 4) ) * SECONDS + strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0), 4, 2) );
        edrString(DETAIL.CONNECT_TYPE)       = edrString(DETAIL.ASS_CIBER_EXT.CALL_DIRECTION, 0);
        edrString(DETAIL.CALL_COMPLETION_INDICATOR) =
                edrString(DETAIL.ASS_CIBER_EXT.CALL_COMPLETION_INDICATOR, 0) +
                edrString(DETAIL.ASS_CIBER_EXT.CALL_TERMINATION_INDICATOR, 0);
      }
      break;
      case 32:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.HOME_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLER_ID, 0);
        edrString(DETAIL.B_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_CALLED_NO, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CALL_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CONNECT_TIME, 0)) );
        edrDecimal(DETAIL.DURATION)          = strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0),
			 0, 4) ) * SECONDS + strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0), 4, 2) );
        edrString(DETAIL.CONNECT_TYPE)       = edrString(DETAIL.ASS_CIBER_EXT.CALL_DIRECTION, 0);
        edrString(DETAIL.CALL_COMPLETION_INDICATOR) =
                edrString(DETAIL.ASS_CIBER_EXT.CALL_COMPLETION_INDICATOR, 0) +
                edrString(DETAIL.ASS_CIBER_EXT.CALL_TERMINATION_INDICATOR, 0);
      }
      break;
      case 42:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SENDING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.RECV_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_MSISDN_MDN, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CALL_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CONNECT_TIME, 0)) );
        edrDecimal(DETAIL.DURATION)          = strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0),
			 0, 4) ) * SECONDS + strToDecimal(strSubstr(
			 edrString(DETAIL.ASS_CIBER_EXT.CHARGE_NO_1_CHARGEABLE_TIME, 0), 4, 2) );
      }
      break;
      case 50:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.HOME_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.OCC_START_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CONNECT_TIME, 0)) );
      }
      break;
      case 52:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.HOME_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_MSISDN_MDN, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.OCC_START_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.CONNECT_TIME, 0)) );
      }
      break;
      case 70:
      {
        edrString(DETAIL.SOURCE_NETWORK)     = edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
        edrString(DETAIL.DESTINATION_NETWORK)= edrString(DETAIL.ASS_CIBER_EXT.HOME_CARRIER_SID, 0);
        edrString(DETAIL.A_NUMBER)           = edrString(DETAIL.ASS_CIBER_EXT.INTERN_MOBILE_ID_NO, 0);
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) =
                strToDate(dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.EVENT_DATE, 0))
                         +dateToStr(edrDate(DETAIL.ASS_CIBER_EXT.EVENT_TIME, 0)) );
      }
      break;
      default:
      {
        // nothing to do
      	// record is of unknown type: error already detected in mapCiberRecord()
      }
      break;
    }
    edrString(DETAIL.INTERN_A_NUMBER_ZONE) = edrString(DETAIL.A_NUMBER);
    edrString(DETAIL.INTERN_B_NUMBER_ZONE) = edrString(DETAIL.B_NUMBER);
    callDirection = edrString(DETAIL.ASS_CIBER_EXT.CALL_DIRECTION, 0);
    servingSID = servingSIDPrefix + edrString(DETAIL.ASS_CIBER_EXT.SERVING_CARRIER_SID, 0);
    if ( callDirection == record_MOC )
    {
      edrString(DETAIL.INTERN_A_NUMBER_ZONE) = servingSID;
    }
    else if ( callDirection == record_MTC )
    {
      edrString(DETAIL.INTERN_B_NUMBER_ZONE) = servingSID;
    }
  }

  function mapCiberRecord(Long ciberRecordType)
  {
    totalNumBasics = totalNumBasics + 1;
    edrNew( DETAIL, CONTAINER_DETAIL );
    recordNumber = recordNumber +1;
    edrLong( DETAIL.RECORD_NUMBER ) = recordNumber;
    edrString( DETAIL.RECORD_TYPE ) = type_CIBER;
    
    edrAddDatablock( DETAIL.ASS_CIBER_EXT );
    recordNumber = recordNumber +1;
    edrLong(DETAIL.NUMBER_ASSOCIATED_RECORDS)        = 1;
    edrLong( DETAIL.ASS_CIBER_EXT.RECORD_NUMBER, 0 ) = recordNumber;
    edrString( DETAIL.ASS_CIBER_EXT.RECORD_TYPE, 0 ) = extension_CIBER;

    switch ( ciberRecordType )
    { 
      case 10: edrInputMap( "CIBER_V25.RECORD_10.STD_MAPPING" ); break; 
      case 11: edrInputMap( "CIBER_V25.RECORD_11.STD_MAPPING" ); break; 
      case 20: edrInputMap( "CIBER_V25.RECORD_20.STD_MAPPING" ); break; 
      case 22: edrInputMap( "CIBER_V25.RECORD_22.STD_MAPPING" ); break; 
      case 30: edrInputMap( "CIBER_V25.RECORD_30.STD_MAPPING" ); break; 
      case 32: edrInputMap( "CIBER_V25.RECORD_32.STD_MAPPING" ); break; 
      case 42: edrInputMap( "CIBER_V25.RECORD_42.STD_MAPPING" ); break; 
      case 50: edrInputMap( "CIBER_V25.RECORD_50.STD_MAPPING" ); break; 
      case 52: edrInputMap( "CIBER_V25.RECORD_52.STD_MAPPING" ); break; 
      case 70: edrInputMap( "CIBER_V25.RECORD_70.STD_MAPPING" ); break;
      default:
      {
        //there is an error in the input
	edrAddError( "ERR_ILL_RECORD_TYPE", 3, longToStr(ciberRecordType));
        return;
      }
      break;
    }

    // update the DETAIL fields from the ASS_CIBER_EXT data and create ChargePackets
    updateBasicDetail(ciberRecordType);

    // update statistic values
    totalWholesaleCharge = totalWholesaleCharge +
                           edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE);
    totalWholesaleTax    = totalWholesaleTax + 
                           edrDecimal(DETAIL.WHOLESALE_CHARGED_TAX_VALUE);
    totalRetailCharge    = totalRetailCharge + 
                           edrDecimal(DETAIL.RETAIL_CHARGED_AMOUNT_VALUE);
    totalRetailTax       = totalRetailTax +
                           edrDecimal(DETAIL.RETAIL_CHARGED_TAX_VALUE);

    // check the transfer cutoff
    if ( transferCutOff < edrDate( DETAIL.CHARGING_START_TIMESTAMP ) )
    {
      edrAddError( "ERR_TRANSFER_CUTOFF_VIOLATED", 3,
                    dateToStr( transferCutOff ),
                    dateToStr( edrDate(DETAIL.CHARGING_START_TIMESTAMP) ) );
    }
    
    // set the Trailer first and last call timestamp
    if ( firstCall > edrDate( DETAIL.CHARGING_START_TIMESTAMP ) )
    {
      firstCall = edrDate( DETAIL.CHARGING_START_TIMESTAMP );
    }
    if ( lastCall < edrDate( DETAIL.CHARGING_START_TIMESTAMP ) )
    {
      lastCall = edrDate( DETAIL.CHARGING_START_TIMESTAMP );
    }
  }
  
  function mapCiberDetailFiller(Long ciberRecordType)
  {
    edrInputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING" );
    //any special work on the optional part of the Detail is to be done here

    Long fillerLen = strLength( edrString(DETAIL.ASS_CIBER_EXT.FILLER, 0) );
    Long fillerMaxLen          = 0; //from the spec of every record
    Long LocCarResStart        = 0; //from the spec of every record
    Long LocCarResMaxLen       = 0; //from the spec of every record
    Long LocCarResAvailableLen = -1;//calculate for every record
    
    switch ( ciberRecordType )
    { 
      case 10:
      {
        fillerMaxLen          = 0;
      }
      break; 
      case 11:
      {
        fillerMaxLen          = 46;
        LocCarResStart        = 26;
        LocCarResMaxLen       = 20;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      break; 
      case 20:
      {
        fillerMaxLen          = 0;
      }
      break; 
      case 22:
      {
        fillerMaxLen          = 150;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 75;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      break; 
      case 30:
      {
        fillerMaxLen          = 27;
        LocCarResStart        = 7;
        LocCarResMaxLen       = 20;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      break; 
      case 32:
      {
        fillerMaxLen          = 150;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 75;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      break; 
      case 42:
      {
        fillerMaxLen          = 151;
        LocCarResStart        = 1;
        LocCarResMaxLen       = 75;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      case 50:
      {
        fillerMaxLen          = 35;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 20;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      case 52:
      {
        fillerMaxLen          = 150;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 75;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      case 70:
      {
        fillerMaxLen          = 246;
        LocCarResStart        = 24;
        LocCarResMaxLen       = 222;
        LocCarResAvailableLen = fillerLen-LocCarResStart;
      }
      default:
      {
        // nothing to do
      	// record is of unknown type: error already detected in mapCiberRecord()
      }
      break;
    }

    if ( LocCarResAvailableLen >= LocCarResMaxLen )
    {
      edrString(DETAIL.ASS_CIBER_EXT.LOCAL_CARRIER_RESERVED, 0) = 
          strSubstr( edrString(DETAIL.ASS_CIBER_EXT.FILLER, 0), 
                     LocCarResStart, LocCarResMaxLen );
          
      edrString(DETAIL.OPERATOR_SPECIFIC_INFO) = 
          edrString(DETAIL.ASS_CIBER_EXT.LOCAL_CARRIER_RESERVED, 0);
    }
    
    if (fillerLen > fillerMaxLen)
    {
      // report a warning (record is too long)
      edrAddError( "ERR_INCORRECT_FILLER_LENGTH", 2,
                   longToStr( fillerMaxLen ),
                   longToStr( fillerLen ) );
//logStdout("DETAIL("+longToStr(ciberRecordType)+") Warning : filler is too long("+longToStr(fillerLen)+")");
    }
  }

  
  function checkForBatchReject(Long ciberRecordType)
  {
    if (checkForBatchRejectFlag == false)
    {
      // we want to be able to switch Batch reject on/off
      return;
    }
  
    if (foundReasonToReject == true)
    {
      // if there is already a reason to reject the file, we dont need a second one
      return;
    }

    Date currentDate = sysdate();
    
    switch ( ciberRecordType )
    { 
      case 1:
      case 2:
      {
        // Header Reject reasons
        if( strMatch(edrString(HEADER.BATCH_CONTENTS), "0|1|2|3|4|5|6|7") == "" )
        {
          //Batch Contents
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "15";
        }
        else if( dateIsValid(edrDate(HEADER.CREATION_TIMESTAMP)) == false )
        {
          //Batch Creation Date
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "02";
        }
        else if( currentDate < edrDate(HEADER.CREATION_TIMESTAMP) )
        {
          //Batch Creation Date
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "03";
        }
        else if( ( edrLong(HEADER.SEQUENCE_NUMBER) < 1 ) or
                 ( edrLong(HEADER.SEQUENCE_NUMBER) > 999 ) )
        {
          //Batch Sequence Number
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "08";
        }
        else if(( strToLong(edrString(HEADER.SENDER)) < 1 ) or
                 ( strToLong(edrString(HEADER.SENDER)) > 99999 ) ) 
        {
          //Sending Carrier SID/BID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "04";
        }
        else if( ( strToLong(edrString(HEADER.RECIPIENT)) < 1 ) or
                 ( strToLong(edrString(HEADER.RECIPIENT)) > 99999 ) ) 
        {
          //Receiving Carrier SID/BID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "05";
        }
        else if( ( ( strMatch(edrString(HEADER.RETURN_INDICATOR), "1|2") != "" ) and
                   ( edrString(HEADER.BATCH_REJECT_REASON) != "00" )                    )
               or
                 ( ( edrString(HEADER.RETURN_INDICATOR) == "3" ) and
                   ( ( strToLong(edrString(HEADER.BATCH_REJECT_REASON)) <= 0  ) or
                     ( strToLong(edrString(HEADER.BATCH_REJECT_REASON)) > 42 ) ) )
               )
        {
          //CIBER Batch Reject Reason Code
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "09";
        }
        else if( ( edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) != 2  ) and
                 ( edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) != 25 ) )
        {
          //Ciber record release number
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "06";
        }
        else if( strMatch(edrString(HEADER.CLEARINGHOUSE_ID), "0|1|2|3|4|5") == "" )
        {
          //ClearinghouseID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "11";
        }
        else if( ( strToLong(edrString(HEADER.CURRENCY)) < 1 ) or
                 ( strToLong(edrString(HEADER.CURRENCY)) > 98) )
        {
          //Currency Type
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "07";
        }
        else if ( dateIsValid(strToDate(edrString(HEADER.SETTLEMENT_PERIOD),"%y%m%d")) == false ) 
        {
          //Settlement Period
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "12";
        }
        else if( strMatch(edrString(HEADER.RETURN_INDICATOR), "1|2|3") == "" )
        {
          //Original/Return Indicator
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "10";
        }
        else if( ( ciberRecordType == 2 ) and
                 ( strMatch(edrString(HEADER.SENDING_CLEARINGHOUSE_BID), 
                            "31102|31103|26238|26240|60059|     ") == "" ) )
        {
          //Sending Clearinghouse BID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "04";
        }
      }
      break; 
      case 97:
      case 98:
      {
        // Trailer Reject reasons
        if( ( dateIsValid(edrDate(TRAILER.CREATION_TIMESTAMP)) == false ) or
            ( currentDate < edrDate(TRAILER.CREATION_TIMESTAMP) ) )
        {
          //Batch Creation Date
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "22";
        }
        else if( ( edrLong(TRAILER.SEQUENCE_NUMBER) < 1 ) or
                 ( edrLong(TRAILER.SEQUENCE_NUMBER) > 999 ) )
        {
          //Batch Sequence Number
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "29";
        }
        else if(( strToLong(edrString(TRAILER.SENDER)) < 1 ) or
                 ( strToLong(edrString(TRAILER.SENDER)) > 99999 ) ) 
        {
          //Sending Carrier SID/BID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "23";
        }
        else if( ( strToLong(edrString(TRAILER.RECIPIENT)) < 1 ) or
                 ( strToLong(edrString(TRAILER.RECIPIENT)) > 99999 ) ) 
        {
          //Receiving Carrier SID/BID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "05";
        }
        else if( edrDecimal(TRAILER.TOTAL_WHOLESALE_CHARGED_VALUE) != (totalWholesaleCharge+totalWholesaleTax) )
        {
          //Batch Total Charge and Tax
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "26";
        }
        else if( ( strMatch(edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN), "0|A|J") == "" ) or
                 ( ( strMatch(batchContents, "0|1|2|4|5|6|7") != "" ) and
                   ( strMatch(edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN), "0") == "" ) ) )
        {
          //Batch Total Charge and Tax sign
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "38";
        }
        else if ( dateIsValid(strToDate(edrString(TRAILER.SETTLEMENT_PERIOD),"%y%m%d")) == false ) 
        {
          //Settlement Period
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "27";
        }
        else if( strMatch(edrString(TRAILER.CLEARINGHOUSE_ID), "0|1|2|3|4|5") == "" )
        {
          //ClearinghouseID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "30";
        }
        else if( ( strToLong(edrString(TRAILER.CURRENCY)) < 1 ) or
                 ( strToLong(edrString(TRAILER.CURRENCY)) > 98) )
        {
          //Currency Type
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "28";
        }
        else if( ( ciberRecordType == 97 ) and
                 ( dateIsValid(edrDate(TRAILER.ORIGINAL_CREATION_TIMESTAMP)) == false ) )
        {
          //Batch Creation Date
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "33";
        }
        else if( ( ciberRecordType == 97 ) and
                 ( ( edrLong(TRAILER.ORIGINAL_SEQUENCE_NUMBER) < 1 ) or
                   ( edrLong(TRAILER.ORIGINAL_SEQUENCE_NUMBER) > 999 ) ) )
        {
          //Original BatchSequence Number
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "32";
        }
        else if( edrDecimal(TRAILER.ORIGINAL_TOTAL_WHOLESALE_CHARGED_VALUE) < 0.0 )
        {
          //Original Total Charge and Tax
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "35";
        }
        else if( ( strMatch(edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN), "0|A|J") == "" ) or
                 ( ( strMatch(batchContents, "0|1|2|4|5|6|7") != "" ) and
                   ( strMatch(edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN), "0") == "" ) ) )
        {
          //Original Total Charge and Tax sign
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "39";
        }
        else if( ( edrLong(TRAILER.ORIGINAL_TOTAL_NUMBER_OF_RECORDS) < 1    ) or
                 ( edrLong(TRAILER.ORIGINAL_TOTAL_NUMBER_OF_RECORDS) > 9999 ) )
        {
          //Original Total Number of Records
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "34";
        }
        else if( ( ciberRecordType == 97 ) and
                 ( strMatch(edrString(TRAILER.SENDING_CLEARINGHOUSE_BID), 
                            "31102|31103|26238|26240|60059|     ") == "" ) )
        {
          //Sending Clearinghouse BID
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "23";
        }
        else if( ( edrLong(TRAILER.TOTAL_NUMBER_OF_RECORDS) < 1    ) or
                 ( edrLong(TRAILER.TOTAL_NUMBER_OF_RECORDS) > 9999 ) or
                 ( edrLong(TRAILER.TOTAL_NUMBER_OF_RECORDS) != totalNumBasics ) )
        {
          //Total Number of Records in Batch
          foundReasonToReject = true; 
          toReturn_RetInd     = "3";
          toReturn_RejReason  = "25";
          msgBuffer="ERROR: TrailerNbRecord=(" +longToStr(edrLong(TRAILER.TOTAL_NUMBER_OF_RECORDS))+
                  ") different from SummingNbRecord(" +longToStr(totalNumBasics)+
                  ") or (TrailerNbRecord is outside the [1-9999] range)";
          logPipeline(msgBuffer,0);
//logStdout(msgBuffer+"\n");
        }
      }
      break; 
      default:
      {
        // nothing to do
      	// this function should be called only for CIBER Header and Trailer records
      }
      break;
    }
    
    if (foundReasonToReject == true)
    {
      toReturn_StreamName = CURRENT_STREAM_NAME;
      String rejReason ="CIBER Batch Reject: stream(" +toReturn_StreamName+
                        "), RetInd(" +toReturn_RetInd+
                        "), RejReason(" +toReturn_RejReason+")";
      edrAddError("ERR_INPUT_REQUEST_ROLLBACK",3,rejReason);
    }
  }


}


//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{
  //----------------------------------------------------------------------------
  // the entry point of the stream processing
  //----------------------------------------------------------------------------
  ciber25_stream:
      ciber25_standardBatch
    | ciber25_clearinghouseBatch
    ;
    
  ciber25_standardBatch:
      CIBER_V25.BATCH_HEADER
      {
        foundReasonToReject = false; //needed to only request the batch reject once
        edrNew( HEADER, CONTAINER_HEADER );
        recordNumber = 1;
        edrLong( HEADER.RECORD_NUMBER ) = recordNumber;
        
        edrInputMap( "CIBER_V25.BATCH_HEADER.STD_MAPPING" );
        resetStatisticValues();
        initializeForNewHeader();
      }
      CIBER_V25.CIBER_FILLER 
      {
        edrInputMap( "CIBER_V25.CIBER_FILLER.HEADER_MAPPING" );
        
        Long fillerLen = strLength( edrString(HEADER.CIBER_FILLER) );
        if ( fillerLen >= 20 )
        {
          edrString(HEADER.OPERATOR_SPECIFIC_INFO) = 
              strSubstr( edrString(HEADER.CIBER_FILLER), 0, 20 );
        }
        if ( fillerLen > 164 )
        {
          // report a warning (record is too long)
          edrAddError( "ERR_INCORRECT_FILLER_LENGTH", 2,
                       "164", longToStr( fillerLen ) );
//logStdout("HEADER Warning : filler is too long("+longToStr(fillerLen)+")");
        }
        checkForBatchReject( strToLong(edrString(HEADER.CIBER_RECORD_TYPE)) );
      }
      details
      CIBER_V25.BATCH_TRAILER
      {
        edrNew( TRAILER, CONTAINER_TRAILER );
        recordNumber = recordNumber +1;
        edrLong( TRAILER.RECORD_NUMBER ) = recordNumber;

        edrInputMap( "CIBER_V25.BATCH_TRAILER.STD_MAPPING" );
        checkStatisticValues();
      }
      CIBER_V25.CIBER_FILLER 
      {
        edrInputMap( "CIBER_V25.CIBER_FILLER.TRAILER_MAPPING" );
        
        Long fillerLen = strLength( edrString(TRAILER.CIBER_FILLER) );
        if ( fillerLen >= 20 )
        {
          edrString(TRAILER.OPERATOR_SPECIFIC_INFO) = 
              strSubstr( edrString(TRAILER.CIBER_FILLER), 0, 20 );
        }
        if ( fillerLen > 125 )
        {
          // report a warning (record is too long)
          edrAddError( "ERR_INCORRECT_FILLER_LENGTH", 2,
                       "125", longToStr( fillerLen ) );
//logStdout("TRAILER Warning : filler is too long("+longToStr(fillerLen)+")");
        }
        checkForBatchReject( strToLong(edrString(TRAILER.CIBER_RECORD_TYPE)) );
      }
   ;

  ciber25_clearinghouseBatch:
      CIBER_V25.BATCH_HEADER_CLEARINGHOUSE 
      {
        foundReasonToReject = false; //needed to only request the batch reject once
        edrNew( HEADER, CONTAINER_HEADER );
        recordNumber = 1;
        edrLong( HEADER.RECORD_NUMBER ) = recordNumber;

        edrInputMap( "CIBER_V25.BATCH_HEADER_CLEARINGHOUSE.STD_MAPPING" );
        resetStatisticValues();
        initializeForNewHeader();
      }
      CIBER_V25.CIBER_FILLER 
      {
        edrInputMap( "CIBER_V25.CIBER_FILLER.HEADER_MAPPING" );

        Long fillerLen = strLength( edrString(HEADER.CIBER_FILLER) );
        if ( fillerLen > 159 )
        {
          // report a warning (record is too long)
          edrAddError( "ERR_INCORRECT_FILLER_LENGTH", 2,
                       "159", longToStr( fillerLen ) );
//logStdout("HEADER Warning : filler is too long("+longToStr(fillerLen)+")");
        }
        checkForBatchReject( strToLong(edrString(HEADER.CIBER_RECORD_TYPE)) );
      }
      details
      CIBER_V25.BATCH_TRAILER_CLEARINGHOUSE 
      {
        edrNew( TRAILER, CONTAINER_TRAILER );
        recordNumber = recordNumber +1;
        edrLong( TRAILER.RECORD_NUMBER ) = recordNumber;

        edrInputMap( "CIBER_V25.BATCH_TRAILER_CLEARINGHOUSE.STD_MAPPING" );
        checkStatisticValues();
      }
      CIBER_V25.CIBER_FILLER 
      {
        edrInputMap( "CIBER_V25.CIBER_FILLER.TRAILER_MAPPING" );

        Long fillerLen = strLength( edrString(TRAILER.CIBER_FILLER) );
        if ( fillerLen > 119 )
        {
          // report a warning (record is too long)
          edrAddError( "ERR_INCORRECT_FILLER_LENGTH", 2,
                       "119", longToStr( fillerLen ) );
//logStdout("TRAILER Warning : filler is too long("+longToStr(fillerLen)+")");
        }
        checkForBatchReject( strToLong(edrString(TRAILER.CIBER_RECORD_TYPE)) );
      }
    ;
    
  details:
      details
      onedetail
    | /* EMPTY */
    ;

  onedetail:
      CIBER_V25.RECORD_10 
      {
        mapCiberRecord(10);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(10);
      }
    | CIBER_V25.RECORD_11
      {
        mapCiberRecord(11);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(11);
      }
    | CIBER_V25.RECORD_20
      {
        mapCiberRecord(20);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(20);
      }
    | CIBER_V25.RECORD_22
      {
        mapCiberRecord(22);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(22);
      }
    | CIBER_V25.RECORD_30
      {
        mapCiberRecord(30);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(30);
      }
    | CIBER_V25.RECORD_32
      {
        mapCiberRecord(32);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(32);
      }
    | CIBER_V25.RECORD_42
      {
        mapCiberRecord(42);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(42);
      }
    | CIBER_V25.RECORD_50
      {
        mapCiberRecord(50);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(50);
      }
    | CIBER_V25.RECORD_52
      {
        mapCiberRecord(52);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(52);
      }
    | CIBER_V25.RECORD_70
      {
        mapCiberRecord(70);
      }
      CIBER_V25.CIBER_FILLER 
      {
        mapCiberDetailFiller(70);
      }
    ;
}
