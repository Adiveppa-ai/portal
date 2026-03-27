//==============================================================================
//
//      Copyright (c) 1996 - 2008 Oracle. All rights reserved.
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
  asnTreeAddString("TAP_0311.LocalTimeStamp.LocalTimeStamp", timeStamp );
  if (utcTimeOffset == "")
  {
    String defUtcTimeOffset = "+0000";
    asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset );
  }
  else
  {
    asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", utcTimeOffset );
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
                                  String  typeInd )
{
  asnTreePushTag("RAP_0103.RapBatchControlInfo");
    asnTreeAddString("TAP_0311.Sender.Sender", sender );
    asnTreeAddString("TAP_0311.Recipient.Recipient", recipient );

    asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber",
                        rapSeqNo);

    asnTreePushTag("RAP_0103.RapFileCreationTimeStamp");
      addDateTimeLong(dateToStr(creationTime), headerUtcTimeOffset);
    asnTreePop(); //asnTreePushTag("RAP_0103.RapFileCreationTimeStamp");

    asnTreePushTag("RAP_0103.RapFileAvailableTimeStamp");
      addDateTimeLong(dateToStr(creationTime), headerUtcTimeOffset);
    asnTreePop(); //asnTreePushTag("RAP_0103.RapFileAvailableTimeStamp");

    asnTreeAddInteger("TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber",
                      specVersNo );

    asnTreeAddInteger("TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber",
                      relVersNo);

    asnTreeAddInteger("RAP_0103.RapSpecificationVersionNumber.RapSpecificationVersionNumber",
                      rapSpecNo);

    asnTreeAddInteger("RAP_0103.RapReleaseVersionNumber.RapReleaseVersionNumber",
                      rapRelNo);

    if (typeInd == "T")
    {
      asnTreeAddString("TAP_0311.FileTypeIndicator.FileTypeIndicator",  
                       typeInd);
    }

  asnTreePop(); //asnTreePushTag("RAP_0103.RapBatchControlInfo");
}


// ============================================================================
function createAuditControl ( Long  totRetCharge,
                              Long  rapDetWritten )
{
  asnTreePushTag("RAP_0103.RapAuditControlInfo");

    asnTreeAddInteger("RAP_0103.TotalSevereReturnValue.TotalSevereReturnValue",
                     totRetCharge);

    asnTreeAddInteger("RAP_0103.ReturnDetailsCount.ReturnDetailsCount",
                      rapDetWritten);

  asnTreePop(); // asnTreePushTag("RAP_0103.RapAuditControlInfo");
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


  asnTreePushTag("RAP_0103.ReturnDetailList");
    asnTreePushTag("RAP_0103.FatalReturn");
      asnTreeAddString("TAP_0311.FileSequenceNumber.FileSequenceNumber",
                         tapSeqNo);

   // Adding corresponding error block based on block
   // from which error is being generated.

   if( errorDetail[0] == "TransferBatch" )
   {
      asnTreePushTag("RAP_0103.TransferBatchError");
   }
   else if( errorDetail[0] == "BatchControlInfo")
   {
      asnTreePushTag("RAP_0103.BatchControlError");
   }
   else if( errorDetail[0] == "AccountingInfo")
   {
      asnTreePushTag("RAP_0103.AccountingInfoError");
   }
   else if( errorDetail[0] == "NetworkInfo")
   {
      asnTreePushTag("RAP_0103.NetworkInfoError");
   }
   else if( errorDetail[0] == "MessageDescription")
   {
      asnTreePushTag("RAP_0103.MessageDescriptionError");
   }
   else if( errorDetail[0] == "AuditControlInfo")
   {
      asnTreePushTag("RAP_0103.AuditControlInfoError");
   }
   else if( errorDetail[0] == "Notification")
   {
      asnTreePushTag("RAP_0103.NotificationError");
   }


     if( errorDetail[0] != "TransferBatch")
     {
        //Getting the original error TAP block
        blockinfo = strSubstr(rlbkStr, (index+1), (strLength(rlbkStr)-index-1));
 
        // Adding the original block(except for Transfer Batch Block)
        asnTreeAddBlob(strHexStrToStr(blockinfo)); 
     }
  
        //Adding the ErrorDetail list
        asnTreePushTag("RAP_0103.ErrorDetailList");
          asnTreePushTag("RAP_0103.ErrorDetail");

            asnTreePushTag("RAP_0103.ErrorContextList");

             for (i=1 ; i < (nbElem-1) ; i=i+1)
             {
              asnTreePushTag("RAP_0103.ErrorContext");
                asnTreeAddInteger("RAP_0103.PathItemId.PathItemId",
                                   strToLong(errorDetail[i]));
                //TODO - ItemOccurrence
                asnTreeAddInteger("RAP_0103.ItemLevel.ItemLevel", i);
              asnTreePop(); //  asnTreePushTag("RAP_0103.ErrorContext");
             }

            asnTreePop(); // asnTreePushTag("RAP_0103.ErrorContextList");

            if (objOffset >= 0)
            {
              asnTreeAddInteger("RAP_0103.ItemOffset.ItemOffset", objOffset);
            }

            asnTreeAddInteger("RAP_0103.ErrorCode.ErrorCode", strToLong(errorDetail[i]));

          asnTreePop(); // asnTreePushTag("RAP_0103.ErrorDetail");
        asnTreePop(); // asnTreePushTag("RAP_0103.ErrorDetailList");

      asnTreePop(); // asnTreePushTag("RAP_0103.Block_xxx_Error");
    asnTreePop(); // asnTreePushTag("RAP_0103.FatalReturn");
 
  asnTreePop(); // asnTreePushTag("RAP_0103.ReturnDetailList");

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

    asnTreePushTag("RAP_0103.ReturnBatch");

      createBatchControlInfo (sender,
                              recipient,
                              rapSeqNo,
                              creationTime,
                              headerUtcTimeOffset,
                              specVersNo,
                              relVersNo,
                              rapSpecNo,
                              rapRelNo,
                              typeInd);

      createFatalReturn(tapSeqNo,
                        objOffset,
			rlbkStr);


      createAuditControl (totRetCharge,
                          rapDetWritten );

    asnTreePop(); // asnTreePushTag("RAP_0103.ReturnBatch");
  
  asnTreeFlush(fileName);

  asnTreeDelete();
}


