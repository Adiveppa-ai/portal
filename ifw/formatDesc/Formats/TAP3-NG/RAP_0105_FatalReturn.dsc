//==============================================================================
//
// Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

use EXT_AsnTree;        // iScript extension to build a Tree of ASN.1 object
                        // used to fill the Length value of the ASN.1 bloc,
                        // before printing on output stream



// ============================================================================
function addDateTimeLong(String timeStamp, String utcTimeOffset)
{
  asnTreeAddString("TAP_0312.LocalTimeStamp.LocalTimeStamp", timeStamp );
  if (utcTimeOffset == "")
  {
    String defUtcTimeOffset = "+0000";
    asnTreeAddString("TAP_0312.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset );
  }
  else
  {
    asnTreeAddString("TAP_0312.UtcTimeOffset.UtcTimeOffset", utcTimeOffset );
  }
}

// ============================================================================
function createBatchControlInfo ( String  sender,
                                  String  recipient,
                                  String  rapSeqNo,
                                  Date    creationTime,
                                  String  headerUtcTimeOffset,
                                  Long    specVersNo,
                                  Long    relVersNo,
                                  Long    rapSpecNo,
                                  Long    rapRelNo,
                                  String  typeInd,
                                  Long    tapDecimalPlaces,
                                  String  tapCurrency )
{
  asnTreePushTag("RAP_0105.RapBatchControlInfo");
    asnTreeAddString("TAP_0312.Sender.Sender", sender );
    asnTreeAddString("TAP_0312.Recipient.Recipient", recipient );

    asnTreeAddString("TAP_0312.RapFileSequenceNumber.RapFileSequenceNumber",
                        rapSeqNo);

    asnTreePushTag("RAP_0105.RapFileCreationTimeStamp");
      addDateTimeLong(dateToStr(creationTime), headerUtcTimeOffset);
    asnTreePop(); //asnTreePushTag("RAP_0105.RapFileCreationTimeStamp");

    asnTreePushTag("RAP_0105.RapFileAvailableTimeStamp");
      addDateTimeLong(dateToStr(creationTime), headerUtcTimeOffset);
    asnTreePop(); //asnTreePushTag("RAP_0105.RapFileAvailableTimeStamp");

    asnTreeAddInteger("TAP_0312.SpecificationVersionNumber.SpecificationVersionNumber",
                      specVersNo );

    asnTreeAddInteger("TAP_0312.ReleaseVersionNumber.ReleaseVersionNumber",
                      relVersNo);

    asnTreeAddInteger("RAP_0105.RapSpecificationVersionNumber.RapSpecificationVersionNumber",
                      rapSpecNo);

    asnTreeAddInteger("RAP_0105.RapReleaseVersionNumber.RapReleaseVersionNumber",
                      rapRelNo);

    if (typeInd == "T")
    {
      asnTreeAddString("TAP_0312.FileTypeIndicator.FileTypeIndicator",  
                       typeInd);
    }
    if( tapDecimalPlaces >= 0 )
    {
      asnTreeAddInteger("TAP_0312.TapDecimalPlaces.TapDecimalPlaces", tapDecimalPlaces);
    } 
    if( tapCurrency != "" and tapCurrency != "SDR" )
    {
      asnTreeAddString("TAP_0312.TapCurrency.TapCurrency", tapCurrency);
    }
    

  asnTreePop(); //asnTreePushTag("RAP_0105.RapBatchControlInfo");
}


// ============================================================================
function createAuditControl ( Long  totRetCharge,
                              Long  rapDetWritten )
{
  asnTreePushTag("RAP_0105.RapAuditControlInfo");

    asnTreeAddInteger("RAP_0105.TotalSevereReturnValue.TotalSevereReturnValue",
                     totRetCharge);

    asnTreeAddInteger("RAP_0105.ReturnDetailsCount.ReturnDetailsCount",
                      rapDetWritten);

  asnTreePop(); // asnTreePushTag("RAP_0105.RapAuditControlInfo");
}


// ============================================================================
function createFatalReturn( String  tapSeqNo,
                            Long    objOffset,
			    String  rlbkStr )
{

String  temp;
String  blockinfo;
String  errorDetail[];

Long    i;
Long    index;
Long    nbElem;


  index = strSearch(rlbkStr, ":"); // rlbkStr => Tag1,Tag2...,Error_code:Return_Tap_Block

  //Getting the Tags and error code
  temp  = strSubstr(rlbkStr, 0, index);
  nbElem = strSplit(errorDetail, temp, ",");


  asnTreePushTag("RAP_0105.ReturnDetailList");
    asnTreePushTag("RAP_0105.FatalReturn");
      asnTreeAddString("TAP_0312.FileSequenceNumber.FileSequenceNumber",
                         tapSeqNo);

   // Adding corresponding error block based on block
   // from which error is being generated.

   if( errorDetail[0] == "TransferBatch" )
   {
      asnTreePushTag("RAP_0105.TransferBatchError");
   }
   else if( errorDetail[0] == "BatchControlInfo")
   {
      asnTreePushTag("RAP_0105.BatchControlError");
   }
   else if( errorDetail[0] == "AccountingInfo")
   {
      asnTreePushTag("RAP_0105.AccountingInfoError");
   }
   else if( errorDetail[0] == "NetworkInfo")
   {
      asnTreePushTag("RAP_0105.NetworkInfoError");
   }
   else if( errorDetail[0] == "MessageDescription")
   {
      asnTreePushTag("RAP_0105.MessageDescriptionError");
   }
   else if( errorDetail[0] == "AuditControlInfo")
   {
      asnTreePushTag("RAP_0105.AuditControlInfoError");
   }
   else if( errorDetail[0] == "Notification")
   {
      asnTreePushTag("RAP_0105.NotificationError");
   }


     if( errorDetail[0] != "TransferBatch")
     {
        //Getting the original error TAP block
        blockinfo = strSubstr(rlbkStr, (index+1), (strLength(rlbkStr)-index-1));
 
        // Adding the original block(except for Transfer Batch Block)
        asnTreeAddBlob(strHexStrToStr(blockinfo)); 
     }
  
        //Adding the ErrorDetail list
        asnTreePushTag("RAP_0105.ErrorDetailList");
          asnTreePushTag("RAP_0105.ErrorDetail");

            asnTreePushTag("RAP_0105.ErrorContextList");

             for (i=1 ; i < (nbElem-1) ; i=i+1)
             {
              asnTreePushTag("RAP_0105.ErrorContext");
                asnTreeAddInteger("RAP_0105.PathItemId.PathItemId",
                                   strToLong(errorDetail[i]));
                //TODO - ItemOccurrence
                asnTreeAddInteger("RAP_0105.ItemLevel.ItemLevel", i);
              asnTreePop(); //  asnTreePushTag("RAP_0105.ErrorContext");
             }

            asnTreePop(); // asnTreePushTag("RAP_0105.ErrorContextList");

            if (objOffset >= 0)
            {
              asnTreeAddInteger("RAP_0105.ItemOffset.ItemOffset", objOffset);
            }

            asnTreeAddInteger("RAP_0105.ErrorCode.ErrorCode", strToLong(errorDetail[i]));

          asnTreePop(); // asnTreePushTag("RAP_0105.ErrorDetail");
        asnTreePop(); // asnTreePushTag("RAP_0105.ErrorDetailList");

      asnTreePop(); // asnTreePushTag("RAP_0105.Block_xxx_Error");
    asnTreePop(); // asnTreePushTag("RAP_0105.FatalReturn");
 
  asnTreePop(); // asnTreePushTag("RAP_0105.ReturnDetailList");

}


// ============================================================================
function writeRapFile(String  fileName,
                      String  sender,
                      String  recipient,
                      String  rapSeqNo,
                      Date    creationTime,
                      String  headerUtcTimeOffset,
                      Long    specVersNo,
                      Long    relVersNo,
                      Long    rapSpecNo,
                      Long    rapRelNo,
                      String  typeInd,
                      String  tapSeqNo,
                      Long    tapDecimalPlaces,
                      String  tapCurrency,
                      Long    totRetCharge,
                      Long    rapDetWritten,
                      Long    pathItemId,
                      Long    arrayIndex,
                      Long    objDepth,
                      Long    objOffset,
                      Long    errorCode,
                      String  rlbkStr)
{

  asnTreeCreate();

    asnTreePushTag("RAP_0105.ReturnBatch");

      createBatchControlInfo (sender,
                              recipient,
                              rapSeqNo,
                              creationTime,
                              headerUtcTimeOffset,
                              specVersNo,
                              relVersNo,
                              rapSpecNo,
                              rapRelNo,
                              typeInd,
                              tapDecimalPlaces,
                              tapCurrency);

      createFatalReturn(tapSeqNo,
                        objOffset,
			rlbkStr);


      createAuditControl (totRetCharge,
                          rapDetWritten );

    asnTreePop(); // asnTreePushTag("RAP_0105.ReturnBatch");
  
  asnTreeFlush(fileName);

  asnTreeDelete();
}


