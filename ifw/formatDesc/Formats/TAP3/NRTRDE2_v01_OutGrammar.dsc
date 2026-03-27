//==============================================================================
//
// Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD/NRTRDE_0201
//------------------------------------------------------------------------------
// Module Description:
//   Output grammar file for the NRTRDE_0201 format
//
//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  use EXT_AsnTree;      // iScript extension to build a Tree of ASN.1 object
                        // used to fill the Length value of the ASN.1 bloc,
                        // before printing on output stream

  Long   nbWrittenDetails;
  Bool   detailIsPresent;

  const Long theNrtrdeSpecificationVersionNumber = 2;
  const Long theNrtrdeReleaseVersionNumber       = 1;
  
  // for Header data storage
  String  headerUtcTimeOffset;
  String  senderFieldValue;  
  String  recipientFieldValue;
  String  recordType;

  // constant
  String type_MOC;
  String type_MTC;
  String type_GPRS_SG;
  String type_GPRS_GG;

  // constant values, regestry string where to find user configurable values
  String reg_TapIOModule;
  String reg_Sender;  
  String reg_Recipient;

  // If there is no details records then output stream will be deleted if in the
  // registry you have DeleteEmptyStream=true for the NRTRDE output stream
  function Bool streamIsEmpty
  {
    if ( nbWrittenDetails == 0 )
    {
      return true;
    }
    // default
    return false;
  }

  function BEGIN
  {
    reg_TapIOModule                     = registryNodeName();
    reg_Sender                          = reg_TapIOModule + ".Module.Sender";    
    reg_Recipient                       = reg_TapIOModule + ".Module.Recipient";
    senderFieldValue                    = regString(reg_Sender);
    recipientFieldValue                 = regString(reg_Recipient);
    
    // initialisation of some constant values
    //---------------------------------------
    type_MOC            ="021";
    type_MTC            ="031";
    type_GPRS_SG        ="040";
    type_GPRS_GG        ="042";

    detailIsPresent     = false;

  }
  
  function processMOC
  {
    asnTreePushTag("NRTRDE_0201.Moc");
    asnTreeAddString("NRTRDE_0201.Imsi.Imsi", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
    if (edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) != "")
    {
      asnTreeAddString("NRTRDE_0201.Imei.Imei", edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) );
    }
    asnTreeAddString("NRTRDE_0201.CallEventStartTimeStamp.CallEventStartTimeStamp", 
                                                          dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)) );
    asnTreeAddString("NRTRDE_0201.UtcTimeOffset.UtcTimeOffset", edrString(DETAIL.UTC_TIME_OFFSET));
    asnTreeAddInteger("NRTRDE_0201.CallEventDuration.CallEventDuration", decimalToLong(edrDecimal(DETAIL.DURATION)) );
    asnTreeAddInteger("NRTRDE_0201.CauseForTermination.CauseForTermination", 
                                                       strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
    asnTreePushTag("NRTRDE_0201.ServiceCode");

    if ( strStartsWith(edrString(DETAIL.BASIC_SERVICE),"0") ) //prefix is digit "0"
    {
      String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) );
      asnTreeAddString("NRTRDE_0201.TeleServiceCode.TeleServiceCode", tmp_ServiceCode);
    }
    else //prefix is digit "1"
    {
      String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) );
      asnTreeAddString("NRTRDE_0201.BearerServiceCode.BearerServiceCode", tmp_ServiceCode);
    }

    asnTreePop(); //asnTreePushTag("NRTRDE_0201.ServiceCode");
    if( edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,0) != "" )
    {
      asnTreeAddString("NRTRDE_0201.SupplementaryServiceCode.SupplementaryServiceCode", 
                                                             edrString(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT,0,0) );
    }
    if (edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0) != "")
    {
      asnTreeAddString("NRTRDE_0201.DialledDigits.DialledDigits", edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS,0));
    }
    if( edrString(DETAIL.B_NUMBER) != "" )
    {
      asnTreeAddString("NRTRDE_0201.ConnectedNumber.ConnectedNumber", edrString(DETAIL.B_NUMBER));
    }
    if( edrString(DETAIL.C_NUMBER) != "" )
    {
      asnTreeAddString("NRTRDE_0201.ThirdPartyNumber.ThirdPartyNumber", edrString(DETAIL.C_NUMBER));
    }
    asnTreeAddString("NRTRDE_0201.RecEntityId.RecEntityId", edrString(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0) );
    if( edrString(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0) != "" )
    {
      asnTreeAddString("NRTRDE_0201.CallReference.CallReference", edrString(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0));
    }
    if( edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) >= 0.0 )
    {
      asnTreeAddInteger("NRTRDE_0201.ChargeAmount.ChargeAmount", 
                                    (decimalToLong(edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE)) * 1000) );
    }
    asnTreePop(); //asnTreePushTag("NRTRDE_0201.Moc");
 }

 function processMTC
 {
   asnTreePushTag("NRTRDE_0201.Mtc");

   asnTreeAddString("NRTRDE_0201.Imsi.Imsi", edrString(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0) );
   if (edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) != "")
   {
     asnTreeAddString("NRTRDE_0201.Imei.Imei", edrString(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0) );
   }
   asnTreeAddString("NRTRDE_0201.CallEventStartTimeStamp.CallEventStartTimeStamp",
                                                         dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)) );
   asnTreeAddString("NRTRDE_0201.UtcTimeOffset.UtcTimeOffset", edrString(DETAIL.UTC_TIME_OFFSET));
   asnTreeAddInteger("NRTRDE_0201.CallEventDuration.CallEventDuration", decimalToLong(edrDecimal(DETAIL.DURATION)) );
   asnTreeAddInteger("NRTRDE_0201.CauseForTermination.CauseForTermination",
                                                      strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
   asnTreePushTag("NRTRDE_0201.ServiceCode");

   if ( strStartsWith(edrString(DETAIL.BASIC_SERVICE),"0") ) //prefix is digit "0"
   {
     String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) );
     asnTreeAddString("NRTRDE_0201.TeleServiceCode.TeleServiceCode", tmp_ServiceCode);
   }
   else //prefix is digit "1"
   {
     String tmp_ServiceCode = strSubstr(edrString(DETAIL.BASIC_SERVICE), 1, (strLength(edrString(DETAIL.BASIC_SERVICE))-1) );
     asnTreeAddString("NRTRDE_0201.BearerServiceCode.BearerServiceCode", tmp_ServiceCode);
   }

   asnTreePop(); //asnTreePushTag("NRTRDE_0201.ServiceCode");

   if ( edrString(DETAIL.B_NUMBER) != "" )
   {
     asnTreeAddString("NRTRDE_0201.CallingNumber.CallingNumber", edrString(DETAIL.B_NUMBER));
   }
   asnTreeAddString("NRTRDE_0201.RecEntityId.RecEntityId", edrString(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION, 0) );
   if ( edrString(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0) != "" )
   {
     asnTreeAddString("NRTRDE_0201.CallReference.CallReference", edrString(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0));
   }
   if( edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) >= 0.0 )
   {
     asnTreeAddInteger("NRTRDE_0201.ChargeAmount.ChargeAmount", 
                                   (decimalToLong(edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE)) * 1000) );
   }
   asnTreePop(); //asnTreePushTag("NRTRDE_0201.Mtc"); 
 }
 function processGPRS
 {
   asnTreePushTag("NRTRDE_0201.Gprs");

   asnTreeAddString("NRTRDE_0201.Imsi.Imsi", edrString(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0) );
   if (edrString(DETAIL.ASS_GPRS_EXT.DEVICE_NUMBER, 0) != "")
   {
     asnTreeAddString("NRTRDE_0201.Imei.Imei", edrString(DETAIL.ASS_GPRS_EXT.DEVICE_NUMBER, 0) );
   }
   asnTreeAddString("NRTRDE_0201.CallEventStartTimeStamp.CallEventStartTimeStamp",
                                                         dateToStr(edrDate(DETAIL.CHARGING_START_TIMESTAMP)) );
   asnTreeAddString("NRTRDE_0201.UtcTimeOffset.UtcTimeOffset", edrString(DETAIL.UTC_TIME_OFFSET));
   asnTreeAddInteger("NRTRDE_0201.CallEventDuration.CallEventDuration", decimalToLong(edrDecimal(DETAIL.DURATION)) );
   asnTreeAddInteger("NRTRDE_0201.CauseForTermination.CauseForTermination",
                                                      strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR)) );
   Long sepIndex = strSearch( edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), ",");
   if (sepIndex < 0)
   {
     asnTreeAddString("NRTRDE_0201.AccessPointNameNI.AccessPointNameNI", edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0));
   }
   else
   {
     asnTreeAddString("NRTRDE_0201.AccessPointNameNI.AccessPointNameNI", 
                      strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), 0, sepIndex) );
     asnTreeAddString("NRTRDE_0201.AccessPointNameOI.AccessPointNameOI",
                      strSubstr(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0), (sepIndex+1), 
	                 strLength(edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)) - (sepIndex+1) ) );
    }
   asnTreeAddInteger("NRTRDE_0201.DataVolumeIncoming.DataVolumeIncoming", decimalToLong(edrDecimal(DETAIL.VOLUME_RECEIVED)) );
   asnTreeAddInteger("NRTRDE_0201.DataVolumeOutgoing.DataVolumeOutgoing", decimalToLong(edrDecimal(DETAIL.VOLUME_SENT)) );
   asnTreeAddString("NRTRDE_0201.SgsnAddress.SgsnAddress", edrString(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0) );
   asnTreeAddString("NRTRDE_0201.GgsnAddress.GgsnAddress", edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0) );
   asnTreeAddInteger("NRTRDE_0201.ChargingId.ChargingId", decimalToLong(edrDecimal(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0)) );
   if( edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE) >= 0.0 )
   {
     asnTreeAddInteger("NRTRDE_0201.ChargeAmount.ChargeAmount", 
                                   (decimalToLong(edrDecimal(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE)) * 1000) );
   }
   asnTreePop(); //asnTreePushTag("NRTRDE_0201.Gprs");
 }

}

//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{
  receive_stream:
  {
    // empty stream identification
    nbWrittenDetails = 0;

    asnTreeCreate();
  }
  HEADER
  edr_stream
  {
    //print to output, and release memory structure
    asnTreeFlush();
    asnTreeDelete();
  }
  ;
   
   edr_stream:
   {
    asnTreePushTag("NRTRDE_0201.Nrtrde");
   }
   header
   details
   trailer
   {
    asnTreePop(); //asnTreePushTag("NRTRDE_0201.Nrtrde");
   }
   ;
    
   header:
   {
      headerUtcTimeOffset     = edrString(HEADER.UTC_TIME_OFFSET);
      
      asnTreeAddInteger("NRTRDE_0201.SpecificationVersionNumber.SpecificationVersionNumber",theNrtrdeSpecificationVersionNumber );
      asnTreeAddInteger("NRTRDE_0201.ReleaseVersionNumber.ReleaseVersionNumber",theNrtrdeReleaseVersionNumber );
      if(senderFieldValue != "")
      {
        asnTreeAddString("NRTRDE_0201.Sender.Sender", senderFieldValue);
      }
      else
      {
        asnTreeAddString("NRTRDE_0201.Sender.Sender", edrString(HEADER.SENDER));
      }

      if(recipientFieldValue != "")
      {
        asnTreeAddString("NRTRDE_0201.Recipient.Recipient", recipientFieldValue);
      }
      else
      {
        asnTreeAddString("NRTRDE_0201.Recipient.Recipient", edrString(HEADER.RECIPIENT));
      }
      String theSequenceNumber = longToStr(edrLong(HEADER.SEQUENCE_NUMBER));
      switch (strLength(theSequenceNumber))
      {
        case 0 : theSequenceNumber="0000000";            break;
        case 1 : theSequenceNumber="000000"+theSequenceNumber;    break;
        case 2 : theSequenceNumber="00000"+theSequenceNumber;    break;
        case 3 : theSequenceNumber="0000"+theSequenceNumber;    break;
        case 4 : theSequenceNumber="000"+theSequenceNumber;    break;
        case 5 : theSequenceNumber="00"+theSequenceNumber;    break;
        case 6 : theSequenceNumber="0"+theSequenceNumber;    break;
        default:                         break;
      }
      asnTreeAddString("NRTRDE_0201.SequenceNumber.SequenceNumber",theSequenceNumber ); 
      asnTreeAddString("NRTRDE_0201.FileAvailableTimeStamp.FileAvailableTimeStamp", dateToStr(edrDate(HEADER.TRANSMISSION_DATE)) );
      asnTreeAddString("NRTRDE_0201.UtcTimeOffset.UtcTimeOffset", headerUtcTimeOffset); 

    }
    ;
    
    trailer:
    TRAILER
    { 
       if ( detailIsPresent == true )
       {
         asnTreePop(); //asnTreePushTag("NRTRDE_0201.CallEventList");
       }
       asnTreeAddInteger("NRTRDE_0201.CallEventsCount.CallEventsCount", nbWrittenDetails);
    }
   ; 


    details: 
    details
    DETAIL 
    { 
      String recordType              = edrString(DETAIL.RECORD_TYPE);

      detailIsPresent = true;

      if ( nbWrittenDetails == 0 )
      {
        asnTreePushTag("NRTRDE_0201.CallEventList");
      }
      if (recordType == type_MOC)
      {
        nbWrittenDetails = nbWrittenDetails + 1;
        processMOC();
      }
      else if (recordType == type_MTC)
      {
        nbWrittenDetails = nbWrittenDetails + 1;
        processMTC();
      }
      else if ( (recordType == type_GPRS_GG) or (recordType == type_GPRS_SG) )
      {
        nbWrittenDetails = nbWrittenDetails + 1;
        processGPRS();
      } 
    } 
    |  /* Empty */
    ; 
}
      
