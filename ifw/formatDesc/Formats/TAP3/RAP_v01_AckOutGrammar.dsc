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
// $RCSfile: TAP3_v04_Blocks.dsc,v $
// $Revision: 1.5 $
// $Author: jkeckste $
// $Date: 2002/05/21 12:19:24 $
// $Locker:  $
//------------------------------------------------------------------------------

iScript
{
  use EXT_AsnTree;        // iScript extension to build a Tree of ASN.1 object
                          // used to fill the Length value of the ASN.1 bloc,
                          // before printing on output stream


  String  headerUtcTimeOffset;
  Long    sequenceNumber;
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
    asnTreeAddString("IFW_TAP3.LocalTimeStamp.LOCAL_TIME_STAMP", timeStamp );
    if (utcTimeOffset == "")
    {
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", defUtcTimeOffset );
    }
    else
    {
      asnTreeAddString("IFW_TAP3.UtcTimeOffset.UTC_TIME_OFFSET", utcTimeOffset );
    }
  }
  
  // -------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------

	function buildAckData
  {
  	asnTreePushTag("IFW_RAP.Acknowledgement");

	    headerUtcTimeOffset   = edrString(HEADER.UTC_TIME_OFFSET);
  	  sequenceNumber        = edrLong(HEADER.SEQUENCE_NUMBER);

      asnTreeAddString("IFW_TAP3.Sender.PLMN_ID",   edrString(HEADER.SENDER) );
      asnTreeAddString("IFW_TAP3.Recipient.PLMN_ID",edrString(HEADER.RECIPIENT) );

      asnTreeAddString("IFW_TAP3.RapFileSequenceNumber.FILE_SEQUENCE_NUMBER",
                                    longToStr(sequenceNumber));

      asnTreePushTag("IFW_RAP.AckFileCreationTimeStamp");
        addDateTimeLong(dateToStr(edrDate(HEADER.CREATION_TIMESTAMP)), 
      								  headerUtcTimeOffset);
      asnTreePop(); //asnTreePushTag("IFW_RAP.AckFileCreationTimeStamp");

      asnTreePushTag("IFW_RAP.AckFileAvailableTimeStamp");
        addDateTimeLong(dateToStr(edrDate(HEADER.TRANSMISSION_DATE)), 
      								  headerUtcTimeOffset);
      asnTreePop(); //asnTreePushTag("IFW_RAP.AckFileAvailableTimeStamp");

      if (edrString(HEADER.DATA_TYPE_INDICATOR) == "T")
      {
        asnTreeAddString("IFW_TAP3.FileTypeIndicator.FILE_TYPE_INDICATOR",  
                                     edrString(HEADER.DATA_TYPE_INDICATOR) );
      }

    
    asnTreePop();	// asnTreePush("IFW_RAP.Acknowledgement");
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
