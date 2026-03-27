//==============================================================================
//
//      Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

iScript
{
  use EXT_AsnTree;        // iScript extension to build a Tree of ASN.1 object
                          // used to fill the Length value of the ASN.1 bloc,
                          // before printing on output stream


  String  headerUtcTimeOffset;
  String  sequenceNumber;
  String  defUtcTimeOffset;
  String  type_HEADER;
  String  type_HEADER_for_Ack;
  Bool    flushTree;

  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------
  function BEGIN
  {
    // init the variables
    defUtcTimeOffset      = "+0000";
    type_HEADER 	        ="010";
    type_HEADER_for_Ack 	="000";
    flushTree             = false;
  }

  // -------------------------------------------------------------------------------------------
  function Bool streamIsEmpty
  {
    if (flushTree == false)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  // -------------------------------------------------------------------------------------------
  // common functions
  // -------------------------------------------------------------------------------------------
  function addDateTimeLong(String timeStamp, String utcTimeOffset)
  {
    asnTreeAddString("TAP_0311.LocalTimeStamp.LocalTimeStamp", timeStamp );
    if (utcTimeOffset == "")
    {
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset );
    }
    else
    {
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", utcTimeOffset );
    }
  }
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------

  function buildAckData
  {
      asnTreePushTag("RAP_0103.Acknowledgement");

      headerUtcTimeOffset   = edrString(HEADER.UTC_TIME_OFFSET);
      sequenceNumber        = longToStr(edrLong(HEADER.SEQUENCE_NUMBER));

      //Making the Sequence number length to five
      switch (strLength(sequenceNumber))
      {
        case 0 : sequenceNumber="00000";                break;
        case 1 : sequenceNumber="0000"+sequenceNumber;  break;
        case 2 : sequenceNumber="000"+sequenceNumber;   break;
        case 3 : sequenceNumber="00"+sequenceNumber;    break;
        case 4 : sequenceNumber="0"+sequenceNumber;     break;
        default:                                        break;
      }

      asnTreeAddString("TAP_0311.Sender.Sender",   edrString(HEADER.RECIPIENT) ); 
      asnTreeAddString("TAP_0311.Recipient.Recipient",edrString(HEADER.SENDER) );

      asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber",
                                                                sequenceNumber);

      asnTreePushTag("RAP_0103.AckFileCreationTimeStamp");
        addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), 
      								  headerUtcTimeOffset);
      asnTreePop(); //asnTreePushTag("RAP_0103.AckFileCreationTimeStamp");

      asnTreePushTag("RAP_0103.AckFileAvailableTimeStamp");
        addDateTimeLong(dateToStr(edrDate(HEADER.TRANSMISSION_DATE)), 
      								  headerUtcTimeOffset);
      asnTreePop(); //asnTreePushTag("RAP_0103.AckFileAvailableTimeStamp");

      if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
      {
        asnTreeAddString("TAP_0311.FileTypeIndicator.FileTypeIndicator",  
                                     edrString(HEADER.DATA_TYPE_INDICATOR) );
      }

    
    asnTreePop();	// asnTreePush("RAP_0103.Acknowledgement");
  }


// -------------------------------------------------------------------------------------------
  function receiveAckFile
  {
  
    logPipeline("Receive acknowledge file from sender: "+
                 edrString(HEADER.SENDER)+
                 ". File sequence number is: "+
                 edrString(HEADER.SEQUENCE_NUMBER));
  }

}

// -------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------

Grammar
{
  receive_stream:
    header
   	{
      if (edrString(HEADER.RECORD_TYPE) == type_HEADER)
      {
        flushTree = true;
        asnTreeCreate();
        buildAckData();
      } 
      else
      {
        flushTree = false;
        receiveAckFile();
      }
    }
    details
    trailer
    {
      if (flushTree == true)
      {
        asnTreeFlush();
        asnTreeDelete();
      }
    }
  ;
  
  header:
    HEADER
		;
      
  details:
    detailList_opt
    | /* EMPTY */
    ;
    
  detailList_opt:
      detailList_opt
      oneDetail
    | oneDetail
    ;      
  
  oneDetail:
    DETAIL
    ;
  
  trailer:
    TRAILER
    ;
}
