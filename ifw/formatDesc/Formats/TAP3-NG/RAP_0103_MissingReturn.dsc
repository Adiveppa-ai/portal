//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

// -------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------
function addDateTimeLong(String timeStamp, String utcTimeOffset)
{
  asnTreeAddString("TAP_0311.LocalTimeStamp.LocalTimeStamp", timeStamp );
  if (utcTimeOffset == "")
  {
    String defUtcTimeOffset      = "+0000";
    asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset );
  }
  else
  {
    asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", utcTimeOffset );
  }
}

// -------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------
function Long createMissingReturn (String  startMissingSeqNumber,
                          String endMissingSeqNumber )
{
    asnTreePushTag("RAP_0103.ReturnDetailList");

    Long missingBlockIdx = asnTreeStoreNode();

     asnTreePushTag("RAP_0103.MissingReturn");

      asnTreeAddString("RAP_0103.StartMissingSeqNumber.StartMissingSeqNumber", startMissingSeqNumber);

      //Populate the end sequence number only incase of a range
      if (startMissingSeqNumber != endMissingSeqNumber)
      {
          asnTreeAddString("RAP_0103.EndMissingSeqNumber.EndMissingSeqNumber", endMissingSeqNumber);
      }

     asnTreePop(); // asnTreePushTag("RAP_0103.MissingReturn");
    asnTreePop(); // asnTreePushTag("RAP_0103.ReturnDetailList");

    return(missingBlockIdx);

}

// -------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------
function Long createAuditControl (String tapSequenceNumber)
{

      Long   rapDetailsCount = 1; // From RAP1.3, as the Return Detail cannot be repeated
                                  // and the field must always be 1.

      Long totalReturnedCharge = 0; // TotalReturnedCharge is zero incase of missing

      asnTreePushTag("RAP_0103.RapAuditControlInfo");

      Long rapAuditControlInfoIdx = asnTreeStoreNode();

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

      return(rapAuditControlInfoIdx);

}

// -------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------
function writeMissingRapFile (String  fileName,
                      String  startMissingSeqNumber,
                      String  endMissingSeqNumber,
                      String  tapSequenceNumber)
{

      Long missingBlockIdx = createMissingReturn (startMissingSeqNumber,
                                                     endMissingSeqNumber);

      Long rapAuditControlInfoIdx = createAuditControl (tapSequenceNumber);
 

} 
