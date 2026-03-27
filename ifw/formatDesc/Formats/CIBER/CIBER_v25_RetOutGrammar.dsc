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
//   Return grammar file for the CIBER v 2.5 format.
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
// $RCSfile: CIBER_v25_RetOutGrammar.dsc,v $
// $Revision: 1.0 $
// $Author: cdiab $
// $Date: 2002/07/25 16:27:22 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: CIBER_v25_RetOutGrammar.dsc,v $
// log 2002/10/09 cdiab
// - PRSF00020197: now using updateCiberTrailerForReturn() on the TRAILER
//
// Revision 1.0  2002/07/25 16:27:22  cdiab
// - Creation
//
//==============================================================================

//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  //indexes to access parameters stored in the CIBER error array
  //ERR_CIBER_RET | CIBER return: retReason(%s), retCode(%s), fieldId(%s), ruleID(%s).
  const Long CIBER_RetCode    = 0;
  const Long CIBER_RetReason  = 1;
  const Long CIBER_FieldId    = 2;
  const Long ValidationRuleID = 3;
  const Long MaxParamCount    = 4;

  // character pointers in the CIBER record strings
  const Long CIBER_Detail_ErrorStrStart = 2; // position where the Error description starts
  const Long CIBER_Detail_ErrorStrSize  = 6; // size in character of the Error description
  const Long CIBER_Header_OriginalReturnIndicator_Start = 23;
  const Long CIBER_Header_OriginalReturnIndicator_Size  = 1;
  const Long CIBER_Header_ClearinghouseID_Start = 32;
  const Long CIBER_Header_ClearinghouseID_Size  = 1;
  const Long CIBER_Header_SendingCarrier_Start = 11;
  const Long CIBER_Header_SendingCarrier_Size  = 5;
  const Long CIBER_Header_ReceivingCarrier_Start = 16;
  const Long CIBER_Header_ReceivingCarrier_Size  = 5;
  const Long CIBER_Header_BatchSequenceNumber_Start = 8;
  const Long CIBER_Header_BatchSequenceNumber_Size  = 3;
  const Long CIBER_Header_SettlementPeriod_Start = 26;
  const Long CIBER_Header_SettlementPeriod_Size  = 6;
  const Long CIBER_Trailer_ClearinghouseID_Start = 43;
  const Long CIBER_Trailer_ClearinghouseID_Size  = 1;
  const Long CIBER_Trailer_SendingCarrier_Start = 11;
  const Long CIBER_Trailer_SendingCarrier_Size  = 5;
  const Long CIBER_Trailer_ReceivingCarrier_Start = 16;
  const Long CIBER_Trailer_ReceivingCarrier_Size  = 5;
  const Long CIBER_Trailer_BatchSequenceNumber_Start = 8;
  const Long CIBER_Trailer_BatchSequenceNumber_Size  = 3;
  const Long CIBER_Trailer_SettlementPeriod_Start = 37;
  const Long CIBER_Trailer_SettlementPeriod_Size  = 6;

  // to be able to determine if the output can be deleted (if empty)
  Long nbWrittenDetails;
  function Bool streamIsEmpty
  {
    if ( nbWrittenDetails == 0 )
    {
      // Only HEADER and TRAILER
      return true;
    }
    // default
    return false;
  }


  function updateCiberDetailForReturn
  {
    // search for a valid CIBER format error
    Bool foundOne = false;
    Long nbErrors = edrNumErrors();
    Long i        = 0;
    while ( (foundOne!=true) and (i<nbErrors) )
    {
      // only check for CIBER format errors
      if (edrGetError(i) == "ERR_CIBER_RET") 
      {
        // get list of error parameters
        Long   paramCount=0;
        String paramList[];
        paramCount = edrGetErrorParameters(i, paramList);

        // check if enough parameters
        if ( paramCount == MaxParamCount )
        {
          // insert the error information in the original record
          String errorStr = paramList[CIBER_RetCode]
                          + paramList[CIBER_RetReason]
                          + paramList[CIBER_FieldId] ;
          
          if (strLength(errorStr) == CIBER_Detail_ErrorStrSize)
          {
            // retrieve original call event detail and fill in the Error description
            String updatedRecord = strReplace( edrTokenString(),
                                               CIBER_Detail_ErrorStrStart,
                                               CIBER_Detail_ErrorStrSize,
                                               errorStr);
            
            // write it out to the return stream and stop the loop
            outputWrite( updatedRecord );
            nbWrittenDetails = nbWrittenDetails + 1;
            foundOne = true;
          }
          else
          {
            logPipeline("ERROR on CIBER return: EDR "+ longToStr(edrLong(DETAIL.RECORD_NUMBER))+ 
                        " contains an ERR_CIBER_RET(+"+ longToStr(i)+
                        "+) error with parameters of the wrong size");
          }
        }
        else
        {
          logPipeline("ERROR on CIBER return: EDR "+ longToStr(edrLong(DETAIL.RECORD_NUMBER))+ 
                      " contains an ERR_CIBER_RET(+"+ longToStr(i)+
                      "+) error with the wrong number of parameters");
        }
      }
      
      // next error
      i=i+1;
    }

    if (foundOne==false)
    {
      // we didnt find a valid CIBER error definition,
      edrReject(); // send the EDR back to the standard reject stream (for recycling)
    }
  }


  function updateCiberHeaderForReturn
  {
    // retrieve the original record
    String updatedHeader = edrTokenString();
    String tmpString; //temporary buffer for string manipulations
    
    // set the Original/Return indicator to "2"
    updatedHeader = strReplace( updatedHeader,
                                CIBER_Header_OriginalReturnIndicator_Start,
                                CIBER_Header_OriginalReturnIndicator_Size,
                                "2" );

    // set the ClearinghouseID to "0"
    updatedHeader = strReplace( updatedHeader,
                                CIBER_Header_ClearinghouseID_Start,
                                CIBER_Header_ClearinghouseID_Size,
                                "0" );

    // swap sending and receiving SID/BID
    updatedHeader = strReplace( updatedHeader,
                                CIBER_Header_SendingCarrier_Start,
                                CIBER_Header_SendingCarrier_Size,
                                edrString(HEADER.RECIPIENT) );
    updatedHeader = strReplace( updatedHeader,
                                CIBER_Header_ReceivingCarrier_Start,
                                CIBER_Header_ReceivingCarrier_Size,
                                edrString(HEADER.SENDER) );

    // set a new Batch Sequence Number
    tmpString = strPad( longToStr(edrLong(HEADER.SEQUENCE_NUMBER)) , "0", 
                        CIBER_Header_BatchSequenceNumber_Size, false );
    updatedHeader = strReplace( updatedHeader,
                                CIBER_Header_BatchSequenceNumber_Start,
                                CIBER_Header_BatchSequenceNumber_Size,
                                tmpString );

    // set the settlementPeriod to "000000"
    updatedHeader = strReplace( updatedHeader,
                                CIBER_Header_SettlementPeriod_Start,
                                CIBER_Header_SettlementPeriod_Size,
                                "000000" );

    // write it out to the return stream
    outputWrite( updatedHeader );
  }


  function updateCiberTrailerForReturn
  {
    // retrieve the original record
    String updatedTrailer = edrTokenString();
    String tmpString; //temporary buffer for string manipulations
    
    // set the ClearinghouseID to "0"
    updatedTrailer= strReplace( updatedTrailer,
                                CIBER_Trailer_ClearinghouseID_Start,
                                CIBER_Trailer_ClearinghouseID_Size,
                                "0" );

    // swap sending and receiving SID/BID
    updatedTrailer= strReplace( updatedTrailer,
                                CIBER_Trailer_SendingCarrier_Start,
                                CIBER_Trailer_SendingCarrier_Size,
                                edrString(TRAILER.RECIPIENT) );
    updatedTrailer= strReplace( updatedTrailer,
                                CIBER_Trailer_ReceivingCarrier_Start,
                                CIBER_Trailer_ReceivingCarrier_Size,
                                edrString(TRAILER.SENDER) );

    // set a new Batch Sequence Number
    tmpString = strPad( longToStr(edrLong(TRAILER.SEQUENCE_NUMBER)) , "0", 
                        CIBER_Trailer_BatchSequenceNumber_Size, false );
    updatedTrailer= strReplace( updatedTrailer,
                                CIBER_Trailer_BatchSequenceNumber_Start,
                                CIBER_Trailer_BatchSequenceNumber_Size,
                                tmpString );

    // set the settlementPeriod to "000000"
    updatedTrailer= strReplace( updatedTrailer,
                                CIBER_Trailer_SettlementPeriod_Start,
                                CIBER_Trailer_SettlementPeriod_Size,
                                "000000" );

    // write it out to the return stream
    outputWrite( updatedTrailer );
  }



}

//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{
  receive_stream:
      HEADER
      {
        nbWrittenDetails = 0; // initialize counter for new file
        updateCiberHeaderForReturn();
      }
      details
      TRAILER
      {
        updateCiberTrailerForReturn();
      }
    ;

  details:
      details
      DETAIL
      {
        updateCiberDetailForReturn();
      }
    | /*EMPTY*/
    ;
}

