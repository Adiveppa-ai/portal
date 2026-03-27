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
// $RCSfile: RAP_v01_FatalReturn.dsc,v $
// $Revision: 1.0 $
// $Author: jkeckste $
// $Date: 2002/05/21 12:19:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: RAP_v01_FatalReturn.dsc,v $
//
// Revision 1.0  2002/05/21 12:19:24  jkeckste
// - Creation
//
//==============================================================================

use EXT_AsnTree;        // iScript extension to build a Tree of ASN.1 object
                        // used to fill the Length value of the ASN.1 bloc,
                        // before printing on output stream



// ============================================================================
function addDateTimeLong(String timeStamp, String utcTimeOffset)
{
  asnTreeAddString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP", timeStamp );
  if (utcTimeOffset == "")
  {
    String defUtcTimeOffset      = "+0000";
    asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", defUtcTimeOffset );
  }
  else
  {
    asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", utcTimeOffset );
  }
}

// ============================================================================
function createBatchControlInfo ( String  sender,
                                  String  recipient,
                                  Long    rapSeqNo,
                                  Date    creationTime,
                                  String  headerUtcTimeOffset,
                                  Long    specVersNo,
                                  Long    relVersNo,
                                  Long    rapSpecNo,
                                  Long    rapRelNo,
                                  String  typeInd )
{
  asnTreePushTag("IFW_RAP.RapBatchControlInfo");
    asnTreeAddString("IFW_TAP3.Sender.PLMN_ID", sender );
    asnTreeAddString("IFW_TAP3.Recipient.PLMN_ID", recipient );

    asnTreeAddInteger("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER",
                      rapSeqNo);

    asnTreePushTag("IFW_RAP.RapFileCreationTimeStamp");
      addDateTimeLong(dateToStr(creationTime), headerUtcTimeOffset);
    asnTreePop(); //asnTreePushTag("IFW_RAP.RapFileCreationTimeStamp");

    asnTreePushTag("IFW_RAP.RapFileAvailableTimeStamp");
      addDateTimeLong(dateToStr(creationTime), headerUtcTimeOffset);
    asnTreePop(); //asnTreePushTag("IFW_RAP.RapFileAvailableTimeStamp");

    asnTreeAddInteger("IFW_TAP3.SpecificationVersionNumber.SPECIFICATION_VERSION_NUMBER",
                      specVersNo );

    asnTreeAddInteger("IFW_TAP3.ReleaseVersionNumber.RELEASE_VERSION_NUMBER",
                      relVersNo);

    asnTreeAddInteger("IFW_RAP.RapSpecificationVersionNumber.RAP_SPECIFICATION_VERSION_NUMBER",
                      rapSpecNo);

    asnTreeAddInteger("IFW_RAP.RapReleaseVersionNumber.RAP_RELEASE_VERSION_NUMBER",
                      rapRelNo);

    if (typeInd == "T")
    {
      asnTreeAddString("IFW_TAP3.FileTypeIndicator.FILE_TYPE_INDICATOR",  
                       typeInd);
    }

  asnTreePop(); //asnTreePushTag("IFW_RAP.RapBatchControlInfo");
}


// ============================================================================
function createAuditControl ( Long  tapSeqNo,
                              Long  totRetCharge,
                              Long  rapDetWritten )
{
  asnTreePushTag("IFW_RAP.RapAuditControlInfo");

    // we build 1 RAP file for every TAP3 file, so the list can contain only 1 element
    asnTreePushTag("IFW_RAP.ReturnSummaryList");
      asnTreePushTag("IFW_RAP.ReturnSummary");
        asnTreeAddInteger("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER",
                          tapSeqNo);
        asnTreeAddInteger("IFW_RAP.SevereReturnValue.SEVERE_RETURN_VALUE",
                         totRetCharge);
      asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnSummary");
    asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnSummaryList");

    asnTreeAddInteger("IFW_RAP.TotalSevereReturnValue.TOTAL_SEVERE_RETURN_VALUE",
                     totRetCharge);

    asnTreeAddInteger("IFW_RAP.ReturnDetailsCount.RETURN_DETAILS_COUNT",
                      rapDetWritten);

  asnTreePop(); // asnTreePushTag("IFW_RAP.RapAuditControlInfo");
}


// ============================================================================
function createFatalReturn( Long  tapSeqNo,
                            Long  pathItemId,
                            Long  arrayIndex,
                            Long  objDepth,
                            Long  objOffset,
                            Long  errorCode )
{

  asnTreePushTag("IFW_RAP.ReturnDetailList");
    asnTreePushTag("IFW_RAP.FatalReturn");
      asnTreeAddInteger("IFW_TAP3.FileSequenceNumber.FILE_SEQUENCE_NUMBER",
                         tapSeqNo);
      asnTreePushTag("IFW_RAP.TransferBatchError");
        asnTreePushTag("IFW_RAP.ErrorDetailList");
          asnTreePushTag("IFW_RAP.ErrorDetail");
            asnTreePushTag("IFW_RAP.ErrorContextList");
              asnTreePushTag("IFW_RAP.ErrorContext");
                asnTreeAddInteger("IFW_RAP.PathItemId.PATH_ITEM_ID", 
                                   pathItemId);

                // check if an index is present
                if (arrayIndex > 0)
                {
                  asnTreeAddInteger("IFW_RAP.ItemOccurrence.ITEM_OCCURRENCE", 
                                     arrayIndex);
                }

                asnTreeAddInteger("IFW_RAP.ItemLevel.ITEM_LEVEL", objDepth);
              asnTreePop(); //  asnTreePushTag("IFW_RAP.ErrorContext");
            asnTreePop(); // asnTreePushTag("IFW_RAP_ErrorContextList");

            if (objOffset >= 0)
            {
              asnTreeAddInteger("IFW_RAP.ItemOffset.ITEM_OFFSET", objOffset);
            }

            asnTreeAddInteger("IFW_RAP.ErrorCode.ERROR_CODE", errorCode);
          asnTreePop(); // asnTreePushTag("IFW_RAP.ErrorDetail");
        asnTreePop(); // asnTreePushTag("IFW_RAP.ErrorDetailList");
      asnTreePop(); // asnTreePushTag("IFW_RAP.TransferBatchError");
    asnTreePop(); // asnTreePushTag("IFW_RAP.FatalReturn");
  
  asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnDetailList");
}

// ============================================================================
function writeRapFile(String  fileName,
                      String  sender,
                      String  recipient,
                      Long    rapSeqNo,
                      Date    creationTime,
                      String  headerUtcTimeOffset,
                      Long    specVersNo,
                      Long    relVersNo,
                      Long    rapSpecNo,
                      Long    rapRelNo,
                      String  typeInd,
                      Long    tapSeqNo,
                      Long    totRetCharge,
                      Long    rapDetWritten,
                      Long    pathItemId,
                      Long    arrayIndex,
                      Long    objDepth,
                      Long    objOffset,
                      Long    errorCode )
{

  asnTreeCreate();

    asnTreePushTag("IFW_RAP.ReturnBatch");

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
                        pathItemId,
                        arrayIndex,
                        objDepth,
                        objOffset,
                        errorCode);


      createAuditControl (tapSeqNo,
                          totRetCharge,
                          rapDetWritten );

    asnTreePop(); // asnTreePushTag("IFW_RAP.ReturnBatch");
  
  asnTreeFlush(fileName);

  asnTreeDelete();
}


