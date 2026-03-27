//==============================================================================
//
// Copyright (c) 2009, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

  //use EXT_AsnTree;        // iScript extension to build a Tree of ASN.1 object
                          // used to fill the Length value of the ASN.1 bloc,
                          // before printing on output stream


function addDateTime(String timeStamp, String utcTimeOffset)
{
  asnTreeAddString("TAP_0312.LocalTimeStamp.LocalTimeStamp", timeStamp );
  if (utcTimeOffset == "")
  {
    String defUtcTimeOffset      = "+0000";
    asnTreeAddString("TAP_0312.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset );
  }
  else
  {
    asnTreeAddString("TAP_0312.UtcTimeOffset.UtcTimeOffset", utcTimeOffset );
  }
}

    
  function prepareStopRapBatchControl
  {
        String rapSequenceNumber     = longToStr(edrLong(HEADER.SEQUENCE_NUMBER));
		switch (strLength(rapSequenceNumber))
		{
		  case 0 : rapSequenceNumber="00000";                   break;
		  case 1 : rapSequenceNumber="0000"+rapSequenceNumber;  break;
		  case 2 : rapSequenceNumber="000"+rapSequenceNumber;   break;
		  case 3 : rapSequenceNumber="00"+rapSequenceNumber;    break;
		  case 4 : rapSequenceNumber="0"+rapSequenceNumber;     break;
		  default:                                              break;
		}
		
                asnTreePushTag("RAP_0105.ReturnBatch");
                Long returnBatchIdx = asnTreeStoreNode();
                asnTreePop(); // asnTreePushTag("RAP_0105.ReturnBatch");
                asnTreeGetStoredNode(returnBatchIdx); //Setting returnBatch as active node
		
		asnTreePushTag("RAP_0105.RapBatchControlInfo");
		
			asnTreeAddString("TAP_0312.Sender.Sender",    edrString(HEADER.SENDER));
			asnTreeAddString("TAP_0312.Recipient.Recipient", edrString(HEADER.RECIPIENT));
	  
			asnTreeAddString("TAP_0312.RapFileSequenceNumber.RapFileSequenceNumber",
								rapSequenceNumber);
	  
			asnTreePushTag("RAP_0105.RapFileCreationTimeStamp");
			  addDateTime(dateToStr(sysdate()), "+0000");
			asnTreePop(); //asnTreePushTag("RAP_0105.RapFileCreationTimeStamp");
	  
			asnTreePushTag("RAP_0105.RapFileAvailableTimeStamp");
			 addDateTime(dateToStr(sysdate()), "+0000");
			asnTreePop(); //asnTreePushTag("RAP_0105.RapFileAvailableTimeStamp");
	  
			asnTreeAddInteger("TAP_0312.SpecificationVersionNumber.SpecificationVersionNumber",
								edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) );
								
			asnTreeAddInteger("TAP_0312.ReleaseVersionNumber.ReleaseVersionNumber", 
								edrLong(HEADER.RELEASE_VERSION) );
								
			asnTreeAddInteger("RAP_0105.RapSpecificationVersionNumber.RapSpecificationVersionNumber",
							  RapSpecificationVersionNumber );

			asnTreeAddInteger("RAP_0105.RapReleaseVersionNumber.RapReleaseVersionNumber",
							  RapReleaseVersionNumber );
		
		asnTreePop(); //asnTreePushTag("RAP_0105.RapBatchControlInfo");
  
  }
  
  function prepareStopRapReturnDetail
  {
  
    String lastSequenceNumber     = longToStr(edrLong(HEADER.ASS_ROAMING_EXT.LAST_SEQ_NUM,0));  
	switch (strLength(lastSequenceNumber))
	{
	  case 0 : lastSequenceNumber="00000";                   break;
	  case 1 : lastSequenceNumber="0000"+lastSequenceNumber;  break;
	  case 2 : lastSequenceNumber="000"+lastSequenceNumber;   break;
	  case 3 : lastSequenceNumber="00"+lastSequenceNumber;    break;
	  case 4 : lastSequenceNumber="0"+lastSequenceNumber;     break;
	  default:                                              break;
	}
		
	asnTreePushTag("RAP_0105.ReturnDetailList");

    Long missingBlockIdx = asnTreeStoreNode();

     asnTreePushTag("RAP_0105.StopReturn");

      asnTreeAddString("RAP_0105.LastSeqNumber.LastSeqNumber", lastSequenceNumber);

     asnTreePop(); // asnTreePushTag("RAP_0105.StopReturn");
    asnTreePop(); // asnTreePushTag("RAP_0105.ReturnDetailList");

  }
  
  function prepareStopRapAuditControl
  {
	Long   rapDetailsCount = 1; // From RAP1.4, as the Return Detail cannot be repeated
                                  // and the field must always be 1.

      Long totalReturnedCharge = 0; // TotalReturnedCharge is zero incase of missing

      asnTreePushTag("RAP_0105.RapAuditControlInfo");

      Long rapAuditControlInfoIdx = asnTreeStoreNode();

        // we build 1 RAP file for every TAP3 file, so the list can contain only 1 element

        asnTreeAddInteger("RAP_0105.TotalSevereReturnValue.TotalSevereReturnValue",
                         totalReturnedCharge);

        asnTreeAddInteger("RAP_0105.ReturnDetailsCount.ReturnDetailsCount",
                          rapDetailsCount);

      asnTreePop(); // asnTreePushTag("RAP_0105.RapAuditControlInfo");
  
  }

 function handleStopReturn
 {
    prepareStopRapBatchControl();
    prepareStopRapReturnDetail();   
    prepareStopRapAuditControl();

 } 
  
