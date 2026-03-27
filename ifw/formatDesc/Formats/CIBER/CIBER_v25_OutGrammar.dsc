//==============================================================================
//
// Copyright (c) 1996, 2014, Oracle and/or its affiliates. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD/CIBER
//------------------------------------------------------------------------------
// Module Description:
//   output grammar file for the CIBER v 2.5 format.
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
// $RCSfile: CIBER_v25_OutGrammar.dsc $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: vinodrao $
// $Date: 2014/11/30 21:55:54 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: CIBER_v25_OutGrammar.dsc,v $
// log 2002/10/09 cdiab
// PRSF00020197: corrected spelling for batchContainsR70
// and now use "not "+extension_CIBER instead of 123 on illegale rec type error
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
  // integrate Record IDs
  const String type_HEADER        ="010";
  const String type_TRAILER       ="090";
  const String type_CIBER         ="701"; // TODO check if it is OK to use this ID
  const String extension_CIBER    ="702"; // TODO check if it is OK to use this ID

  // globals
  Long    i;
  Long    j;
  Long    records;
  Long    packets;
  Long    recordNumber;
  Date    firstCall;
  Date    lastCall;
  Decimal totalWholesaleCharge;
  Decimal totalWholesaleTax;
  Decimal totalRetailCharge;
  Decimal totalRetailTax;
  Long    totalDetailsReceived;
  Long    totalDetailsWritten;

  // globals for CIBER
  Bool    detailIsCiberCompliant;
  Bool    batchContainsR70;
  Long    totalDetails70Written;
  Bool    iamclearinghouse;

  // constant values, regestry string to define user configurable values
  String reg_CiberIOModule;
  String reg_OutputModule;
  String reg_CiberPipeline;
  String reg_SendingSID;
  String reg_CiberCurrency;
  String reg_ReceivingSID;
  String reg_CiberVersionNumber;
  String reg_BatchContent;
  String reg_SendingClearingHouseBID;

  // Constant values to store the registry info
  String ciberCurrency;
  String sendingSID;
  String receivingSID;
  Long   ciberVersionNumber;
  String batchContents;
  String sendingClearingHouseBID;

  Long    batchSequenceNumber;
  String  headerSendingSID ;
  String  headerReceivingSID ;
  String  headerCiberCurrency ;
  String  headerSettlementPeriod;
  String  headerClearingHouseId ;
  String  headerClearingHouseBID ; 
  Date    headerCreationDate;

  iamclearinghouse = false; //TODO get it from the registry

  //----------------------------------------------------------------------------
  // Check if the file contains only HEADER and TRAILER
  //----------------------------------------------------------------------------
  function Bool streamIsEmpty
  {
    if ( recordNumber <= 2 )
    {
      // Only HEADER and TRAILER
      return true;
    }
    else
    {
      // At least one DETAIL
      return false;
    }
  }
 
  function BEGIN
  {
    // initialization of some registry variables
    reg_CiberPipeline		= "ifw.Pipelines."+formatName();
    reg_CiberIOModule		= registryNodeName();
    reg_OutputModule		= reg_CiberIOModule + ".Module.OutputStream.Module";

    reg_CiberCurrency		= reg_OutputModule + ".CiberCurrency";
    reg_ReceivingSID		= reg_OutputModule + ".ReceivingSID";
    reg_SendingSID		= reg_CiberPipeline + ".SendingSID";
    reg_CiberVersionNumber	= reg_CiberPipeline + ".CiberVersionNumber";
    reg_BatchContent		= reg_OutputModule + ".BatchContents";

//logStdout("reg_CiberCurrency" + reg_CiberCurrency + " \n"); 
//logStdout("reg_ReceivingSID" + reg_ReceivingSID + " \n"); 
//logStdout("reg_SendingSID" + reg_SendingSID + " \n"); 
//logStdout("reg_CiberVersionNumber" + reg_CiberVersionNumber + " \n"); 
//logStdout("reg_BatchContent" + reg_BatchContent + " \n"); 

    ciberCurrency		= regString(reg_CiberCurrency);
    if (ciberCurrency == "")
    {
      ciberCurrency		= "01"; // Default US Dollars
    }
//logStdout("ciberCurrency" + ciberCurrency + " \n"); 

    sendingSID			= regString(reg_SendingSID);
    if (sendingSID == "")
    {
      sendingSID		= "99999"; // Unknown SID 
    }
//logStdout("sendingSID" + sendingSID + " \n"); 

    receivingSID		= regString(reg_SendingSID);
    if (receivingSID == "")
    {
      receivingSID		= "99999"; // Unknown SID 
    }
//logStdout("receivingSID" + receivingSID + " \n"); 

    ciberVersionNumber		= strToLong(regString(reg_CiberVersionNumber));
    if (ciberVersionNumber == 0)
    {
      ciberVersionNumber	= 25; // Recent Version 
    }
//logStdout("ciberVersionNumber" + longToStr(ciberVersionNumber) + " \n"); 

    batchContents		= regString(reg_BatchContent);
    if (batchContents == "")
    {
      batchContents		= "1"; // The most commen type 
    }
//logStdout("batchContents" + batchContents + " \n"); 

    if (iamclearinghouse) {
      // Clearing House BID 
      reg_SendingClearingHouseBID  = reg_CiberPipeline + ".SendingClearingHouseBID";
      sendingClearingHouseBID	   = regString(reg_SendingClearingHouseBID);
      if (sendingClearingHouseBID == "")
      {
        sendingClearingHouseBID	= "99999"; // Unknown BID 
      }
    } 
  } 

  function buildCiberDetailFiller(Long ciberRecordType)
  {
    Long fillerMaxLen          = 0; //from the spec of every record
    Long LocCarResStart        = 0; //from the spec of every record
    Long LocCarResMaxLen       = 0; //from the spec of every record
    
    switch ( ciberRecordType )
    { 
      case 10:
      {
        //do nothing, the LocalCarrierReserved field is in middle of record
        fillerMaxLen          = 0;
      }
      break; 
      case 11:
      {
        fillerMaxLen          = 46;
        LocCarResStart        = 26;
        LocCarResMaxLen       = 20;
      }
      break; 
      case 20:
      {
        //do nothing, the LocalCarrierReserved field is in middle of record
        fillerMaxLen          = 0;
      }
      break; 
      case 22:
      {
        fillerMaxLen          = 150;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 75;
      }
      break; 
      case 30:
      {
        fillerMaxLen          = 27;
        LocCarResStart        = 7;
        LocCarResMaxLen       = 20;
      }
      break; 
      case 32:
      {
        fillerMaxLen          = 150;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 75;
      }
      break; 
      case 42:
      {
        fillerMaxLen          = 151;
        LocCarResStart        = 1;
        LocCarResMaxLen       = 75;
      }
      case 50:
      {
        fillerMaxLen          = 35;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 20;
      }
      case 52:
      {
        fillerMaxLen          = 150;
        LocCarResStart        = 0;
        LocCarResMaxLen       = 75;
      }
      case 70:
      {
        fillerMaxLen          = 246;
        LocCarResStart        = 24;
        LocCarResMaxLen       = 222;
      }
      default:
      {
      	//TODO report an error (record is of unknown type)
      }
      break;
    }

    if ( edrString(DETAIL.ASS_CIBER_EXT.LOCAL_CARRIER_RESERVED, 0) != "" )
    {
      edrString(DETAIL.ASS_CIBER_EXT.FILLER, 0) =
          strPad("", " ", LocCarResStart, true)
        + strPad( edrString(DETAIL.ASS_CIBER_EXT.LOCAL_CARRIER_RESERVED, 0),
                   " ", LocCarResMaxLen, true);
    }
    else if ( edrString(DETAIL.OPERATOR_SPECIFIC_INFO) != "")
    {
      edrString(DETAIL.ASS_CIBER_EXT.FILLER, 0) =
          strPad("", " ", LocCarResStart, true)
        + strPad( edrString(DETAIL.OPERATOR_SPECIFIC_INFO),
                   " ", LocCarResMaxLen, true);
    }
    else
    {
      edrString(DETAIL.ASS_CIBER_EXT.FILLER, 0) = "";
    }
  }

  function updateHeaderRecord
  {
//logStdout("updateHeaderRecord() \n"); 
  

    // Sending Carrier SID/BID
    if (edrString(HEADER.SENDER) == ""){
      edrString(HEADER.SENDER) = sendingSID;
    }
//logStdout("HEADER.SENDER "+sendingSID+"\n");

    // Receiving Carrier SID/BID
    if (edrString(HEADER.RECIPIENT) == ""){
      edrString(HEADER.RECIPIENT) = receivingSID;
    }
//logStdout("HEADER.RECIPIENT "+receivingSID+"\n");

    // Record Release Number 
    if (edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) == 0){
      edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) = ciberVersionNumber;
    }
//logStdout("HEADER.SPECIFICATION_VERSION_NUMBER "+longToStr(ciberVersionNumber)+"\n");

    // Original Return Indicator
    if (edrString(HEADER.RETURN_INDICATOR) == ""){
      edrString(HEADER.RETURN_INDICATOR) = "1";
    }      
	
    // Currency Type 
    if (edrString(HEADER.CURRENCY) == ""){
      edrString(HEADER.CURRENCY) = ciberCurrency;
    }      
	
    // Settlement Period 
    if (edrString(HEADER.SETTLEMENT_PERIOD) == ""){
      edrString(HEADER.SETTLEMENT_PERIOD) = "000000";
    }     
//logStdout("HEADER.SETTLEMENT_PERIOD "+edrString(HEADER.SETTLEMENT_PERIOD)+"\n");

    // Clearing House Id
    if (edrString(HEADER.CLEARINGHOUSE_ID) == ""){
      edrString(HEADER.CLEARINGHOUSE_ID) = "0";
    }      
	
    // BATCH_REJECT_REASON 
    if (edrString(HEADER.BATCH_REJECT_REASON) == ""){
      edrString(HEADER.BATCH_REJECT_REASON) = "00";
    }      

    // Batch Contents 
    if (edrString(HEADER.BATCH_CONTENTS) == ""){
      edrString(HEADER.BATCH_CONTENTS) = batchContents;
    }      
//logStdout("HEADER.BATCH_CONTENTS "+batchContents+"\n");

    if (iamclearinghouse) {
      // Clearing House BID 
      if (edrString(HEADER.SENDING_CLEARINGHOUSE_BID) == ""){
     	edrString(HEADER.SENDING_CLEARINGHOUSE_BID) = sendingClearingHouseBID; 
      }
   }
  }

  function updateTrailerRecord
  {
    // Creation Time  
    if (dateToStr(edrDate(TRAILER.CREATION_TIMESTAMP)) == ""){
      edrDate(TRAILER.CREATION_TIMESTAMP) = headerCreationDate;
    }      
	
    // Sending Carrier SID/BID
    if (edrString(TRAILER.SENDER) == ""){
      edrString(TRAILER.SENDER) = headerSendingSID;
    }

    // Receiving Carrier SID/BID
    if (edrString(TRAILER.RECIPIENT) == ""){
      edrString(TRAILER.RECIPIENT) = headerReceivingSID;
    }

    // Currency Type 
    if (edrString(TRAILER.CURRENCY) == ""){
      edrString(TRAILER.CURRENCY) = headerCiberCurrency;
    }      
	
    // Settlement Period 
    if (edrString(TRAILER.SETTLEMENT_PERIOD) == ""){
      edrString(TRAILER.SETTLEMENT_PERIOD) = headerSettlementPeriod;
    }     

    // Clearing House Id
    if (edrString(TRAILER.CLEARINGHOUSE_ID) == ""){
      edrString(TRAILER.CLEARINGHOUSE_ID) = headerClearingHouseId;
    }      

    if (iamclearinghouse) {
      // Clearing House BID 
      if (edrString(TRAILER.SENDING_CLEARINGHOUSE_BID) == ""){
     	edrString(TRAILER.SENDING_CLEARINGHOUSE_BID) == headerClearingHouseBID; 
      }
    }
 }
}

//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{

  //----------------------------------------------------------------------------
  // The EDR stream
  //----------------------------------------------------------------------------
  edr_stream:
      HEADER
        { 
          recordNumber         = 1;
          firstCall            = MAX_DATE;
          lastCall             = MIN_DATE;
          totalWholesaleCharge = 0.0;
          totalWholesaleTax    = 0.0;
          totalRetailCharge    = 0.0;
          totalRetailTax       = 0.0;

          totalDetailsReceived = 0;
          totalDetailsWritten  = 0;
          totalDetails70Written= 0;
          batchContainsR70    = false;
         
	  batchSequenceNumber = 0;
          headerSendingSID =  "";
          headerReceivingSID = "";
          headerCiberCurrency = "";
          headerSettlementPeriod = "";
          headerClearingHouseId = "";
     	  headerClearingHouseBID = ""; 
	  headerCreationDate     = MIN_DATE;

	  // Update the header information before writting the 
	  // header CIBER record
	  updateHeaderRecord();

          if ( edrString(HEADER.BATCH_CONTENTS) == "3")
          {
            batchContainsR70 = true;
          }

	  if (iamclearinghouse)
	  {
            edrString(HEADER.CIBER_FILLER) = "";
            edrOutputMap( "CIBER_V25.BATCH_HEADER_CLEARINGHOUSE.STD_MAPPING" );
            edrOutputMap( "CIBER_V25.CIBER_FILLER.HEADER_MAPPING" );
	  }
	  else
	  {
            if (edrString(HEADER.OPERATOR_SPECIFIC_INFO) != "")
            {
              edrString(HEADER.CIBER_FILLER) =
                  strPad(edrString(HEADER.OPERATOR_SPECIFIC_INFO)," ",20,true);
            }
            else
            {
              edrString(HEADER.CIBER_FILLER) = "";
            }
            edrOutputMap( "CIBER_V25.BATCH_HEADER.STD_MAPPING" );
            edrOutputMap( "CIBER_V25.CIBER_FILLER.HEADER_MAPPING" );
	  }

          // Get the batch sequence number
        batchSequenceNumber = edrLong(HEADER.SEQUENCE_NUMBER);
        headerSendingSID =  edrString(HEADER.SENDER);
        headerReceivingSID = edrString(HEADER.RECIPIENT);
        headerCiberCurrency = edrString(HEADER.CURRENCY);
        headerSettlementPeriod = edrString(HEADER.SETTLEMENT_PERIOD);
        headerClearingHouseId = edrString(HEADER.CLEARINGHOUSE_ID);
     	  headerClearingHouseBID = edrString(HEADER.SENDING_CLEARINGHOUSE_BID); 
	  headerCreationDate     = edrDate(HEADER.CREATION_TIMESTAMP);

        }
      details
      TRAILER
        {
          recordNumber = recordNumber + 1;
          edrLong( TRAILER.RECORD_NUMBER )           = recordNumber;
          edrLong( TRAILER.TOTAL_NUMBER_OF_RECORDS ) = totalDetailsWritten;
          edrDate( TRAILER.FIRST_START_TIMESTAMP )   = firstCall;
          edrDate( TRAILER.LAST_START_TIMESTAMP )    = lastCall;
          edrDecimal(TRAILER.TOTAL_RETAIL_CHARGED_VALUE)   =totalRetailCharge+totalRetailTax;
          edrDecimal(TRAILER.TOTAL_WHOLESALE_CHARGED_VALUE)=totalWholesaleCharge+totalWholesaleTax;

	  // Set trailer original record numbers and charges
	  if (edrLong(TRAILER.ORIGINAL_TOTAL_NUMBER_OF_RECORDS) == 0) {
	      edrLong(TRAILER.ORIGINAL_TOTAL_NUMBER_OF_RECORDS) = totalDetailsWritten;
	  }

	  if (edrDecimal(TRAILER.ORIGINAL_TOTAL_WHOLESALE_CHARGED_VALUE) == 0.0) {
	      edrDecimal(TRAILER.ORIGINAL_TOTAL_WHOLESALE_CHARGED_VALUE) = 
		totalWholesaleCharge+totalWholesaleTax;
	  }

	  // Update the header information before writting the 
	  // header CIBER record
	  updateTrailerRecord();

          if ( batchContainsR70 == false)
          {
            edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN)   = "";
            edrString(TRAILER.CIBER_R70_ORIGINAL_TOTALS_SIGN)= "";
          }
	  else    // TODO check on this part could be removed
	  {
	   if (edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN) == "")
	   {
	     if ((totalWholesaleCharge+totalWholesaleTax) >= 0.00 ) {
	       edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN) = "A";
             }
	     else {
	       edrString(TRAILER.CIBER_R70_BATCH_TOTALS_SIGN) = "J";	
             }
           }

	   if (edrString(TRAILER.CIBER_R70_ORIGINAL_TOTALS_SIGN) == "")
	   {
	     if ((totalWholesaleCharge+totalWholesaleTax) >= 0.00 ) {
	       edrString(TRAILER.CIBER_R70_ORIGINAL_TOTALS_SIGN) = "A";
             }
	     else {
	       edrString(TRAILER.CIBER_R70_ORIGINAL_TOTALS_SIGN) = "J";	
             }
           }

          }

	  if (iamclearinghouse)
	  {
            edrString(TRAILER.CIBER_FILLER) = "";
            edrOutputMap( "CIBER_V25.BATCH_TRAILER_CLEARINGHOUSE.STD_MAPPING" );
            edrOutputMap( "CIBER_V25.CIBER_FILLER.TRAILER_MAPPING" );
	  }
	  else
	  {
            if (edrString(TRAILER.OPERATOR_SPECIFIC_INFO) != "")
            {
              edrString(TRAILER.CIBER_FILLER) =
                  strPad(edrString(TRAILER.OPERATOR_SPECIFIC_INFO)," ",20,true);
            }
            else
            {
              edrString(TRAILER.CIBER_FILLER) = "";
            }
            edrOutputMap( "CIBER_V25.BATCH_TRAILER.STD_MAPPING" );
            edrOutputMap( "CIBER_V25.CIBER_FILLER.TRAILER_MAPPING" );
	  }
        }
    ;


  //----------------------------------------------------------------------------
  // A list of DETAIL records (optionnaly empty)
  //----------------------------------------------------------------------------
  details: 
      details 
      DETAIL
        {

        totalDetailsReceived   = totalDetailsReceived + 1;
	  detailIsCiberCompliant = false;
	  Long idx = 0; 

          // Write the ASSOCIATED_CIBER_EXTENSION record (if provided)
          if ( edrNumDatablocks( DETAIL.ASS_CIBER_EXT ) > 0 )
          {
            detailIsCiberCompliant = true;
            recordNumber           = recordNumber + 1;
            totalDetailsWritten    = totalDetailsWritten + 1;

            Long ciberRecordType =
               strToLong(edrString(DETAIL.ASS_CIBER_EXT.CIBER_RECORD_TYPE,0));
              
	    // Set the sequence number in each detail record
	    //if ( edrLong(DETAIL.ASS_CIBER_EXT.ORIG_BATCH_SEQ_NO,idx) == 0) {
	     //  edrLong(DETAIL.ASS_CIBER_EXT.ORIG_BATCH_SEQ_NO,idx) = batchSequenceNumber;
            //}
	      if(strToLong(edrString(DETAIL.ASS_CIBER_EXT.ORIG_BATCH_SEQ_NO,idx)) == 0){
	         edrString(DETAIL.ASS_CIBER_EXT.ORIG_BATCH_SEQ_NO,idx) = longToStr(batchSequenceNumber);
	         }

            buildCiberDetailFiller( ciberRecordType );

            switch ( ciberRecordType ) 
            { 
              case 10:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_10.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 11:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_11.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 20:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_20.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 22:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_22.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 30:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_30.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 32:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_32.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 42:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_42.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 50:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_50.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 52:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_52.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
	      }
	      break; 
              case 70:
	      {
	        edrOutputMap( "CIBER_V25.RECORD_70.STD_MAPPING", 0 );
	        edrOutputMap( "CIBER_V25.CIBER_FILLER.DETAIL_MAPPING", 0 );
                totalDetails70Written = totalDetails70Written + 1;
	      }
	      break;
              default:
	      {
	        detailIsCiberCompliant = false;
                recordNumber           = recordNumber - 1;
                totalDetailsWritten    = totalDetailsWritten - 1;
		edrAddError( "ERR_ILL_RECORD_TYPE", 3,
		              edrString(DETAIL.ASS_CIBER_EXT.CIBER_RECORD_TYPE,0) );//TODO get a better error message
	      }
	      break;
            }
	  }
	  else
	  {
	    // the ASS_CIBER_EXT is missing
	    edrAddError( "ERR_ILL_RECORD_TYPE", 3, "not "+extension_CIBER);
            logPipeline( "ERROR: no ASS_CIBER_EXT found on EDR "+longToStr(totalDetailsReceived)+", it will be rejected\n" );
	  }
 
	  if (detailIsCiberCompliant)
	  {
            //--------------------------------------------------------------------
            // Update the statistic
            //--------------------------------------------------------------------
            if ( edrDate( DETAIL.CHARGING_START_TIMESTAMP ) < firstCall )
            {
              firstCall = edrDate( DETAIL.CHARGING_START_TIMESTAMP );
            }
            if ( edrDate( DETAIL.CHARGING_START_TIMESTAMP ) > lastCall )
            {
              lastCall = edrDate( DETAIL.CHARGING_START_TIMESTAMP );
            }
            totalWholesaleCharge = totalWholesaleCharge + 
	                           edrDecimal( DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE );
            totalWholesaleTax    = totalWholesaleTax + 
	                           edrDecimal( DETAIL.WHOLESALE_CHARGED_TAX_VALUE );
            totalRetailCharge    = totalRetailCharge + 
	                           edrDecimal( DETAIL.RETAIL_CHARGED_AMOUNT_VALUE );
            totalRetailTax       = totalRetailTax + 
	                           edrDecimal( DETAIL.RETAIL_CHARGED_TAX_VALUE );
          }
	  else
	  {
	    // error
	    edrAddError( "INF_EDR_REJECTED", 3); // Major
	    edrReject();
	  }
	  idx = idx + 1;
        }
    | /* EMPTY */
    ;
}
