//==============================================================================
//
// Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
//
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

iScript                                       
{                                             
  Long   parentContextLength[];               
  Long   level;                               
  Bool   isAList[];                           
                                              
  String currBlock;                           
  String currContext;                         
  Long   indices[];                           
  Long   nIndices;                            
                                              


/////////////////////////////////////////////////////////////////////////
  use EXT_AsnTree;
  
  String reg_NotificationFilePath       = "";
  String reg_NotificationFilePrefix     = "";

  String strNotificationFilePath        = "";
  String strNotificationFilePrefix      = "";

  String  headerSender;
  String  headerRecipient;
  Long    headerRapFileSeqNo;
  String  headerUtcTimeOffset;
  Long    startSeqNum;
  Long    endSeqNum;

  Long    theTap3SpecificationVersionNumber;
  Long    theTap3ReleaseVersionNumber;
  String  theFileTypeIndicator;

  String prevContext;
  Long prevIndices[];
  Long nPrevIndices;
  
  function addDateTimeLong(String timeStamp, String utcTimeOffset)
  {
    asnTreeAddString("TAP_0311.LocalTimeStamp.LocalTimeStamp", timeStamp);
    if (utcTimeOffset == "")
    {
      String defUtcTimeOffset = "+0000";
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", defUtcTimeOffset);
    }
    else
    {
      asnTreeAddString("TAP_0311.UtcTimeOffset.UtcTimeOffset", utcTimeOffset);
    }
  }

  function addOperatorSpecInfoList(String theInfo)
  {
    if (theInfo != "")
    {
      asnTreePushTag("TAP_0311.OperatorSpecInfoList");
      asnTreeAddString("TAP_0311.OperatorSpecInformation.OperatorSpecInformation", theInfo);
      asnTreePop(); //asnTreePushTag("TAP_0311.OperatorSpecInfoList");
    }
  }

  function writeNotificationFile(String fileName, String theSequenceNumber)
  {
    Date actualSystime = sysdate();
    String rapSeqNumber;

    asnTreeCreate();

    asnTreePushTag("TAP_0311.Notification");

        asnTreeAddString("TAP_0311.Sender.Sender", headerRecipient);
        asnTreeAddString("TAP_0311.Recipient.Recipient", headerSender);

        asnTreeAddString("TAP_0311.FileSequenceNumber.FileSequenceNumber", theSequenceNumber);

        rapSeqNumber = strPad(longToStr(headerRapFileSeqNo), "0", 5, false);
        asnTreeAddString("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber", rapSeqNumber);

        asnTreePushTag("TAP_0311.FileCreationTimeStamp");
          addDateTimeLong(dateToStr(actualSystime), headerUtcTimeOffset);
        asnTreePop(); //asnTreePushTag("TAP_0311.FileCreationTimeStamp");

        asnTreePushTag("TAP_0311.FileAvailableTimeStamp");
          addDateTimeLong(dateToStr(actualSystime), headerUtcTimeOffset);
        asnTreePop(); //asnTreePushTag("TAP_0311.FileAvailableTimeStamp");

        asnTreePushTag("TAP_0311.TransferCutOffTimeStamp");
          addDateTimeLong(dateToStr(actualSystime), headerUtcTimeOffset);
        asnTreePop(); //asnTreePushTag("TAP_0311.TransferCutOffTimeStamp");

        asnTreeAddInteger("TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber", theTap3SpecificationVersionNumber);
        asnTreeAddInteger("TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber", theTap3ReleaseVersionNumber);

        if (theFileTypeIndicator == "T")
        {
          asnTreeAddString("TAP_0311.FileTypeIndicator.FileTypeIndicator",  theFileTypeIndicator);
        }

        //addOperatorSpecInfoList(edrString(DETAIL.OPERATOR_SPECIFIC_INFO));

     asnTreePop(); //asnTreePushTag("TAP_0311.Notification");

   asnTreeFlush(fileName);
   asnTreeDelete();
  }

  function generateNotification
  {
    Long   seqNumber;
    String notificationFilename;
    String tmp_notificationFilename;

    String notificationSeqNumber;

    tmp_notificationFilename = strNotificationFilePath + "/" + strNotificationFilePrefix +
                               headerRecipient + headerSender;

    //Setting endSeqNum as startSeqNum if endSeqNum is missing
    if(endSeqNum == 0)
	{
      endSeqNum = startSeqNum;
	}

    //Generate the sequence of notification files
    for(seqNumber = startSeqNum; seqNumber <= endSeqNum; seqNumber = seqNumber + 1)
    {
      notificationSeqNumber = strPad(longToStr(seqNumber), "0", 5, false);
      notificationFilename = tmp_notificationFilename + notificationSeqNumber;
      writeNotificationFile(notificationFilename, notificationSeqNumber);
    }
  }

  function Bool onRollback
  {
    Long seqNumber;
    String notificationFilename;
    String tmp_notificationFilename;
    String notificationSeqNumber;

    /* Deleting the Notification files incase of Rollback */
    tmp_notificationFilename = strNotificationFilePath + "/" + strNotificationFilePrefix +
                               headerRecipient + headerSender;

    for(seqNumber = startSeqNum; seqNumber <= endSeqNum; seqNumber = seqNumber + 1)
    {
      notificationSeqNumber = strPad(longToStr(seqNumber), "0", 5, false);
      notificationFilename = tmp_notificationFilename + notificationSeqNumber;
      fileDelete(notificationFilename);
    }

   return true;
  }

  function BEGIN
  {
    reg_NotificationFilePath   = registryNodeName() + ".NotificationFilePath";
    strNotificationFilePath    = regString(reg_NotificationFilePath);

    reg_NotificationFilePrefix = registryNodeName() + ".NotificationFilePrefix";
    strNotificationFilePrefix  = regString(reg_NotificationFilePrefix);
  }

  function initializeForNewStream
  {
    headerSender = "";
    headerRecipient = "";
    headerRapFileSeqNo = 0;
    headerUtcTimeOffset = "";
    
    startSeqNum = 0;
    endSeqNum = 0;

    theTap3SpecificationVersionNumber = 0;
    theTap3ReleaseVersionNumber = 0;
    
    theFileTypeIndicator = "";
  
    prevContext = "";
	  nPrevIndices = 0;
  }

  function onField(String currToken)
  {
    switch (currToken)
    {
      case "TAP_0311.Sender.Sender":
      {
        if ( currContext == "HEADER.acknowledgement.sender" or
             currContext == "HEADER.rapBatchControlInfoRap.sender" )
        {
          headerSender = edrStringEx ( currContext, indices, nIndices );
        }
      }
      break;
      
      case "TAP_0311.Recipient.Recipient":
      {
        if ( currContext == "HEADER.acknowledgement.recipient" or
             currContext == "HEADER.rapBatchControlInfoRap.recipient" )
        {
          headerRecipient = edrStringEx ( currContext, indices, nIndices );
        }
      }
      break;
      
      case "TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber":
      {
        if ( currContext == "HEADER.acknowledgement.rapFileSequenceNumber" or
             currContext == "HEADER.rapBatchControlInfoRap.rapFileSequenceNumber" )
        {
          headerRapFileSeqNo = strToLong(edrStringEx( currContext, indices, nIndices ));
        }
      }
      break;
      
      case "RAP_0103.StartMissingSeqNumber.StartMissingSeqNumber":
      {
        startSeqNum = strToLong(edrStringEx( currContext, indices, nIndices ));
      }
      break;
      
      case "RAP_0103.EndMissingSeqNumber.EndMissingSeqNumber":
      {
        endSeqNum = strToLong(edrStringEx( currContext, indices, nIndices ));
      }
      break;
      
      case "TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber":
      {
        if ( currContext == "HEADER.acknowledgement.specificationVersionNumber" or
             currContext == "HEADER.rapBatchControlInfoRap.specificationVersionNumber" )
        {
          theTap3SpecificationVersionNumber = edrLongEx( currContext, indices, nIndices );
        }
      }
      break;
      
      case "TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber":
      {
        if ( currContext == "HEADER.acknowledgement.releaseVersionNumber" or
             currContext == "HEADER.rapBatchControlInfoRap.releaseVersionNumber" )
        {
          theTap3ReleaseVersionNumber = edrLongEx( currContext, indices, nIndices );
        }
      }
      break;
      
      case "TAP_0311.FileTypeIndicator.FileTypeIndicator":
      {
        if ( currContext == "HEADER.acknowledgement.fileTypeIndicator" or
             currContext == "HEADER.rapBatchControlInfoRap.fileTypeIndicator" )
        {
          theFileTypeIndicator = edrStringEx( currContext, indices, nIndices );
        }
      }
      break;
    }
  }

  function onBlockEnd(String currToken)
  {
    switch (currToken)
    {
      case "RAP_0103.Acknowledgement":
      {
        edrNew(TRAILER, CONTAINER_TRAILER);
      }
      break;

      case "RAP_0103.MissingReturn":
      {
        generateNotification();
      }
      break;
      
      case "TAP_0311.MobileOriginatedCall":
      case "TAP_0311.MobileTerminatedCall":
      case "TAP_0311.SupplServiceEvent":
      case "TAP_0311.ServiceCentreUsage":
      case "TAP_0311.GprsCall":
      case "TAP_0311.ContentTransaction":
      case "TAP_0311.LocationService":
	  {
		Long i;
        currContext = prevContext;
		for (i = 0; i < nPrevIndices; i = i + 1)
		{
		  indices[i] = prevIndices[i];
		}
		nIndices = nPrevIndices;
      }
      break;    
    }
  }
  
  function onBlockStart(String currToken)
  {
    switch (currToken)
    {
      case "RAP_0103.Acknowledgement":
      {
        edrNew(HEADER, CONTAINER_HEADER);

        currContext = "HEADER.acknowledgement";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;

      case "RAP_0103.RapBatchControlInfo":
      {
        edrNew(HEADER, CONTAINER_HEADER);

        currContext = "HEADER.rapBatchControlInfoRap";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;

      case "RAP_0103.MissingReturn":
      {
        edrNew(DETAIL, CONTAINER_DETAIL);

        currContext = "DETAIL.missingReturn";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;

      case "RAP_0103.FatalReturn":
      {
        edrNew(DETAIL, CONTAINER_DETAIL);

        currContext = "DETAIL.fatalReturn";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;

      case "RAP_0103.SevereReturn":
      {
        edrNew(DETAIL, CONTAINER_DETAIL);

        currContext = "DETAIL.severeReturn";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;

      case "RAP_0103.RapAuditControlInfo":
      {
        edrNew(TRAILER, CONTAINER_TRAILER);

        currContext = "TRAILER.rapAuditControlInfo";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
	  
      case "TAP_0311.MobileOriginatedCall":
      {
		Long i;
        prevContext = currContext;
		for (i = 0; i < nIndices; i = i + 1)
		{
		  prevIndices[i] = indices[i];
		}
		nPrevIndices = nIndices;

        currContext = "DETAIL.mobileOriginatedCall";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
    
      case "TAP_0311.MobileTerminatedCall":
      {
		Long i;
        prevContext = currContext;
		for (i = 0; i < nIndices; i = i + 1)
		{
		  prevIndices[i] = indices[i];
		}
		nPrevIndices = nIndices;

        currContext = "DETAIL.mobileTerminatedCall";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
    
      case "TAP_0311.SupplServiceEvent":
      {
		Long i;
        prevContext = currContext;
		for (i = 0; i < nIndices; i = i + 1)
		{
		  prevIndices[i] = indices[i];
		}
		nPrevIndices = nIndices;

        currContext = "DETAIL.supplServiceEvent";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
    
      case "TAP_0311.ServiceCentreUsage":
      {
		Long i;
        prevContext = currContext;
		for (i = 0; i < nIndices; i = i + 1)
		{
		  prevIndices[i] = indices[i];
		}
		nPrevIndices = nIndices;

        currContext = "DETAIL.serviceCentreUsage";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
    
      case "TAP_0311.GprsCall":
      {
		Long i;
        prevContext = currContext;
		for (i = 0; i < nIndices; i = i + 1)
		{
		  prevIndices[i] = indices[i];
		}
		nPrevIndices = nIndices;

        currContext = "DETAIL.gprsCall";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
    
      case "TAP_0311.ContentTransaction":
      {
		Long i;
        prevContext = currContext;
		for (i = 0; i < nIndices; i = i + 1)
		{
		  prevIndices[i] = indices[i];
		}
		nPrevIndices = nIndices;

        currContext = "DETAIL.contentTransaction";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
    
      case "TAP_0311.LocationService":
      {
		Long i;
        prevContext = currContext;
		for (i = 0; i < nIndices; i = i + 1)
		{
		  prevIndices[i] = indices[i];
		}
		nPrevIndices = nIndices;

        currContext = "DETAIL.locationService";
        indices[0] = 0; nIndices = 1;

        edrAddDatablockEx(currContext, indices, 0);
      }
      break;
    }
  }
/////////////////////////////////////////////////////////////////////////

                                                
  function __initializeForNewStream           
  {                                           
    level = 0;                                
                                              
    currBlock = "";                         
    currContext = "";                       
    nIndices = 0;                             
                                              
    initializeForNewStream();                 
  }                                           
                                              
  function __onBlockStart(String currToken, Bool isList)    
  {                                                         
    if ( currContext != "" )                              
    {                                                       
       parentContextLength[level] = strLength(currContext);                     
       level = level + 1;                                                       
       isAList[level] = isList;                                                 
                                                                                
       currContext = currContext + "." + currBlock;                           
       indices[nIndices] = edrNumDatablocksEx(currContext, indices, nIndices);  
       edrAddDatablockEx(currContext, indices, nIndices);                       
       nIndices = nIndices + 1;               
    }                                         
                                              
    onBlockStart(currToken);                  
  }                                           
                                              
  function __onBlockEnd(String currToken)     
  {                                           
    onBlockEnd(currToken);                    
                                              
    if ( currContext != "" )                
    {                                         
      if ( level <= 0 )                       
      {                                       
        //logStdout("Warning: Grammar configuration, currContext: " + currContext + ", currToken: " + currToken + "\n");  
        //logStdout("Warning: Automatically resetting currContext.\n");                                                       
        currContext = "";                   
        return;                               
      }                                       
                                              
      level = level - 1;                      
      currContext = strSubstr(currContext, 0, parentContextLength[level]);                                                     
      nIndices = nIndices - 1;                
    }                                         
    else if ( level > 0 )                     
    {                                         
      logPipeline("Error: currContext reseted at wrong place, currToken: " + currToken + "\n");                             
      level = 0;                              
      nIndices = 0;                           
    }                                         
  }                                           
                                              
  function __onField(String currToken)                                         
  {                                                                            
    String prevContext = currContext;                                          
    if (isAList[level] == true)                                                
    {                                                                          
      currContext = currContext + "." + currBlock + "_Elem";               
      indices[nIndices] = edrNumDatablocksEx(currContext, indices, nIndices);  
      edrAddDatablockEx(currContext, indices, nIndices);                       
      nIndices = nIndices + 1;                                                 
                                                                               
      currContext = currContext + "." + currBlock;                           
      edrConnectTokenEx(currContext, indices, nIndices, currToken);            
      onField(currToken);                                                      
      nIndices = nIndices - 1;                                                 
    }                                                                          
    else                                                                       
    {                                                                          
      currContext = currContext + "." + currBlock;                           
      edrConnectTokenEx(currContext, indices, nIndices, currToken);            
      onField(currToken);                                                      
    }                                                                          
    currContext = prevContext;                                                 
  }                                           
}                                             
                                              
Grammar                                       
{                                             
  __inputStream:                              
      {                                       
        __initializeForNewStream();           
      }                                       
      inputStream                             
    ;                                         


/////////////////////////////////////////////////////////////////////////
  inputStream:
      {
        logPipeline("Info: parsed inputStream\n");
      }
      RapDataInterChange
      fileFiller
    ;

  fileFiller:
      fileFiller
      fileFillerElement
    |
    ;

  fileFillerElement:
      ASN1.BlockEnd
    | ASN1.FileFiller
    | ASN1.FileEndFiller
    ;
/////////////////////////////////////////////////////////////////////////

                                                
                                                                                 
  AbsoluteAmount_opt:                                                         
      AbsoluteAmount                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AbsoluteAmount:                                                             
      TAP_0311.AbsoluteAmount                                        
      {                                                                          
        __onField("TAP_0311.AbsoluteAmount.AbsoluteAmount");    
        //logStdout("Parsed Leaf AbsoluteAmount\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  AccessPointNameNI_opt:                                                         
      AccessPointNameNI                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AccessPointNameNI:                                                             
      TAP_0311.AccessPointNameNI                                        
      {                                                                          
        __onField("TAP_0311.AccessPointNameNI.AccessPointNameNI");    
        //logStdout("Parsed Leaf AccessPointNameNI\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  AccessPointNameOI_opt:                                                         
      AccessPointNameOI                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AccessPointNameOI:                                                             
      TAP_0311.AccessPointNameOI                                        
      {                                                                          
        __onField("TAP_0311.AccessPointNameOI.AccessPointNameOI");    
        //logStdout("Parsed Leaf AccessPointNameOI\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  AccountingInfo_opt:                                           
      AccountingInfo                                            
    |                                                              
    ;                                                              
                                                                   
  AccountingInfo:                                               
      TAP_0311.AccountingInfo                                 
      {                                                                   
        __onBlockStart("TAP_0311.AccountingInfo", false);   
        //logStdout("Parsed Sequence AccountingInfo\n");              
      }                                                                   
      taxation_AccountingInfo     
      discounting_AccountingInfo     
      localCurrency_AccountingInfo     
      tapCurrency_AccountingInfo     
      currencyConversionInfo_AccountingInfo     
      tapDecimalPlaces_AccountingInfo     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.AccountingInfo");     
        //logStdout("AccountingInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  taxation_AccountingInfo:                                                       
      {                                                                                 
        currBlock = "taxation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxationList_opt                                                       
    ;                                                                                   
                                                                                        
  discounting_AccountingInfo:                                                       
      {                                                                                 
        currBlock = "discounting";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountingList_opt                                                       
    ;                                                                                   
                                                                                        
  localCurrency_AccountingInfo:                                                       
      {                                                                                 
        currBlock = "localCurrency";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalCurrency_opt                                                       
    ;                                                                                   
                                                                                        
  tapCurrency_AccountingInfo:                                                       
      {                                                                                 
        currBlock = "tapCurrency";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TapCurrency_opt                                                       
    ;                                                                                   
                                                                                        
  currencyConversionInfo_AccountingInfo:                                                       
      {                                                                                 
        currBlock = "currencyConversionInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CurrencyConversionList_opt                                                       
    ;                                                                                   
                                                                                        
  tapDecimalPlaces_AccountingInfo:                                                       
      {                                                                                 
        currBlock = "tapDecimalPlaces";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TapDecimalPlaces_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  AccountingInfoError_opt:                                           
      AccountingInfoError                                            
    |                                                              
    ;                                                              
                                                                   
  AccountingInfoError:                                               
      RAP_0103.AccountingInfoError                                 
      {                                                                   
        __onBlockStart("RAP_0103.AccountingInfoError", false);   
        //logStdout("Parsed Sequence AccountingInfoError\n");              
      }                                                                   
      accountingInfo_AccountingInfoError     
      errorDetail_AccountingInfoError     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.AccountingInfoError");     
        //logStdout("AccountingInfoError Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  accountingInfo_AccountingInfoError:                                                       
      {                                                                                 
        currBlock = "accountingInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AccountingInfo_opt                                                       
    ;                                                                                   
                                                                                        
  errorDetail_AccountingInfoError:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  AckFileAvailableTimeStamp_opt:                                           
      AckFileAvailableTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  AckFileAvailableTimeStamp:                                               
      RAP_0103.AckFileAvailableTimeStamp                                 
      {                                                                   
        __onBlockStart("RAP_0103.AckFileAvailableTimeStamp", false);   
        //logStdout("Parsed Sequence AckFileAvailableTimeStamp\n");              
      }                                                                   
      localTimeStamp_AckFileAvailableTimeStamp     
      utcTimeOffset_AckFileAvailableTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.AckFileAvailableTimeStamp");     
        //logStdout("AckFileAvailableTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_AckFileAvailableTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_AckFileAvailableTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  AckFileCreationTimeStamp_opt:                                           
      AckFileCreationTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  AckFileCreationTimeStamp:                                               
      RAP_0103.AckFileCreationTimeStamp                                 
      {                                                                   
        __onBlockStart("RAP_0103.AckFileCreationTimeStamp", false);   
        //logStdout("Parsed Sequence AckFileCreationTimeStamp\n");              
      }                                                                   
      localTimeStamp_AckFileCreationTimeStamp     
      utcTimeOffset_AckFileCreationTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.AckFileCreationTimeStamp");     
        //logStdout("AckFileCreationTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_AckFileCreationTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_AckFileCreationTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  Acknowledgement_opt:                                           
      Acknowledgement                                            
    |                                                              
    ;                                                              
                                                                   
  Acknowledgement:                                               
      RAP_0103.Acknowledgement                                 
      {                                                                   
        __onBlockStart("RAP_0103.Acknowledgement", false);   
        //logStdout("Parsed Sequence Acknowledgement\n");              
      }                                                                   
      sender_Acknowledgement     
      recipient_Acknowledgement     
      rapFileSequenceNumber_Acknowledgement     
      ackFileCreationTimeStamp_Acknowledgement     
      ackFileAvailableTimeStamp_Acknowledgement     
      fileTypeIndicator_Acknowledgement     
      operatorSpecList_Acknowledgement     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.Acknowledgement");     
        //logStdout("Acknowledgement Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  sender_Acknowledgement:                                                       
      {                                                                                 
        currBlock = "sender";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Sender_opt                                                       
    ;                                                                                   
                                                                                        
  recipient_Acknowledgement:                                                       
      {                                                                                 
        currBlock = "recipient";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Recipient_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_Acknowledgement:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  ackFileCreationTimeStamp_Acknowledgement:                                                       
      {                                                                                 
        currBlock = "ackFileCreationTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AckFileCreationTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  ackFileAvailableTimeStamp_Acknowledgement:                                                       
      {                                                                                 
        currBlock = "ackFileAvailableTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AckFileAvailableTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  fileTypeIndicator_Acknowledgement:                                                       
      {                                                                                 
        currBlock = "fileTypeIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileTypeIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecList_Acknowledgement:                                                       
      {                                                                                 
        currBlock = "operatorSpecList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  ActualDeliveryTimeStamp_opt:                                           
      ActualDeliveryTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  ActualDeliveryTimeStamp:                                               
      TAP_0311.ActualDeliveryTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.ActualDeliveryTimeStamp", false);   
        //logStdout("Parsed Sequence ActualDeliveryTimeStamp\n");              
      }                                                                   
      localTimeStamp_ActualDeliveryTimeStamp     
      utcTimeOffsetCode_ActualDeliveryTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ActualDeliveryTimeStamp");     
        //logStdout("ActualDeliveryTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_ActualDeliveryTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_ActualDeliveryTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  AddressStringDigits_opt:                                                         
      AddressStringDigits                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AddressStringDigits:                                                             
      TAP_0311.AddressStringDigits                                        
      {                                                                          
        __onField("TAP_0311.AddressStringDigits.AddressStringDigits");    
        //logStdout("Parsed Leaf AddressStringDigits\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  AdvisedCharge_opt:                                                         
      AdvisedCharge                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AdvisedCharge:                                                             
      TAP_0311.AdvisedCharge                                        
      {                                                                          
        __onField("TAP_0311.AdvisedCharge.AdvisedCharge");    
        //logStdout("Parsed Leaf AdvisedCharge\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  AdvisedChargeCurrency_opt:                                                         
      AdvisedChargeCurrency                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AdvisedChargeCurrency:                                                             
      TAP_0311.AdvisedChargeCurrency                                        
      {                                                                          
        __onField("TAP_0311.AdvisedChargeCurrency.AdvisedChargeCurrency");    
        //logStdout("Parsed Leaf AdvisedChargeCurrency\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  AdvisedChargeInformation_opt:                                           
      AdvisedChargeInformation                                            
    |                                                              
    ;                                                              
                                                                   
  AdvisedChargeInformation:                                               
      TAP_0311.AdvisedChargeInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.AdvisedChargeInformation", false);   
        //logStdout("Parsed Sequence AdvisedChargeInformation\n");              
      }                                                                   
      paidIndicator_AdvisedChargeInformation     
      paymentMethod_AdvisedChargeInformation     
      advisedChargeCurrency_AdvisedChargeInformation     
      advisedCharge_AdvisedChargeInformation     
      commission_AdvisedChargeInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.AdvisedChargeInformation");     
        //logStdout("AdvisedChargeInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  paidIndicator_AdvisedChargeInformation:                                                       
      {                                                                                 
        currBlock = "paidIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PaidIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  paymentMethod_AdvisedChargeInformation:                                                       
      {                                                                                 
        currBlock = "paymentMethod";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PaymentMethod_opt                                                       
    ;                                                                                   
                                                                                        
  advisedChargeCurrency_AdvisedChargeInformation:                                                       
      {                                                                                 
        currBlock = "advisedChargeCurrency";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AdvisedChargeCurrency_opt                                                       
    ;                                                                                   
                                                                                        
  advisedCharge_AdvisedChargeInformation:                                                       
      {                                                                                 
        currBlock = "advisedCharge";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AdvisedCharge_opt                                                       
    ;                                                                                   
                                                                                        
  commission_AdvisedChargeInformation:                                                       
      {                                                                                 
        currBlock = "commission";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Commission_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  AgeOfLocation_opt:                                                         
      AgeOfLocation                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AgeOfLocation:                                                             
      TAP_0311.AgeOfLocation                                        
      {                                                                          
        __onField("TAP_0311.AgeOfLocation.AgeOfLocation");    
        //logStdout("Parsed Leaf AgeOfLocation\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  AsciiString_opt:                                                         
      AsciiString                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AsciiString:                                                             
      TAP_0311.AsciiString                                        
      {                                                                          
        __onField("TAP_0311.AsciiString.AsciiString");    
        //logStdout("Parsed Leaf AsciiString\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  AuditControlInfo_opt:                                           
      AuditControlInfo                                            
    |                                                              
    ;                                                              
                                                                   
  AuditControlInfo:                                               
      TAP_0311.AuditControlInfo                                 
      {                                                                   
        __onBlockStart("TAP_0311.AuditControlInfo", false);   
        //logStdout("Parsed Sequence AuditControlInfo\n");              
      }                                                                   
      earliestCallTimeStamp_AuditControlInfo     
      latestCallTimeStamp_AuditControlInfo     
      totalCharge_AuditControlInfo     
      totalChargeRefund_AuditControlInfo     
      totalTaxRefund_AuditControlInfo     
      totalTaxValue_AuditControlInfo     
      totalDiscountValue_AuditControlInfo     
      totalDiscountRefund_AuditControlInfo     
      totalAdvisedChargeValueList_AuditControlInfo     
      callEventDetailsCount_AuditControlInfo     
      operatorSpecInformation_AuditControlInfo     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.AuditControlInfo");     
        //logStdout("AuditControlInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  earliestCallTimeStamp_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "earliestCallTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EarliestCallTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  latestCallTimeStamp_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "latestCallTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LatestCallTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  totalCharge_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalCharge";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalCharge_opt                                                       
    ;                                                                                   
                                                                                        
  totalChargeRefund_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalChargeRefund";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalChargeRefund_opt                                                       
    ;                                                                                   
                                                                                        
  totalTaxRefund_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalTaxRefund";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalTaxRefund_opt                                                       
    ;                                                                                   
                                                                                        
  totalTaxValue_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalTaxValue";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalTaxValue_opt                                                       
    ;                                                                                   
                                                                                        
  totalDiscountValue_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalDiscountValue";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalDiscountValue_opt                                                       
    ;                                                                                   
                                                                                        
  totalDiscountRefund_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalDiscountRefund";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalDiscountRefund_opt                                                       
    ;                                                                                   
                                                                                        
  totalAdvisedChargeValueList_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalAdvisedChargeValueList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalAdvisedChargeValueList_opt                                                       
    ;                                                                                   
                                                                                        
  callEventDetailsCount_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "callEventDetailsCount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventDetailsCount_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_AuditControlInfo:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  AuditControlInfoError_opt:                                           
      AuditControlInfoError                                            
    |                                                              
    ;                                                              
                                                                   
  AuditControlInfoError:                                               
      RAP_0103.AuditControlInfoError                                 
      {                                                                   
        __onBlockStart("RAP_0103.AuditControlInfoError", false);   
        //logStdout("Parsed Sequence AuditControlInfoError\n");              
      }                                                                   
      auditControlInfo_AuditControlInfoError     
      errorDetail_AuditControlInfoError     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.AuditControlInfoError");     
        //logStdout("AuditControlInfoError Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  auditControlInfo_AuditControlInfoError:                                                       
      {                                                                                 
        currBlock = "auditControlInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AuditControlInfo_opt                                                       
    ;                                                                                   
                                                                                        
  errorDetail_AuditControlInfoError:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  BasicService_opt:                                           
      BasicService                                            
    |                                                              
    ;                                                              
                                                                   
  BasicService:                                               
      TAP_0311.BasicService                                 
      {                                                                   
        __onBlockStart("TAP_0311.BasicService", false);   
        //logStdout("Parsed Sequence BasicService\n");              
      }                                                                   
      serviceCode_BasicService     
      transparencyIndicator_BasicService     
      fnur_BasicService     
      userProtocolIndicator_BasicService     
      guaranteedBitRate_BasicService     
      maximumBitRate_BasicService     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.BasicService");     
        //logStdout("BasicService Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  serviceCode_BasicService:                                                       
      {                                                                                 
        currBlock = "serviceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BasicServiceCode_opt                                                       
    ;                                                                                   
                                                                                        
  transparencyIndicator_BasicService:                                                       
      {                                                                                 
        currBlock = "transparencyIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransparencyIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  fnur_BasicService:                                                       
      {                                                                                 
        currBlock = "fnur";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Fnur_opt                                                       
    ;                                                                                   
                                                                                        
  userProtocolIndicator_BasicService:                                                       
      {                                                                                 
        currBlock = "userProtocolIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UserProtocolIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  guaranteedBitRate_BasicService:                                                       
      {                                                                                 
        currBlock = "guaranteedBitRate";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GuaranteedBitRate_opt                                                       
    ;                                                                                   
                                                                                        
  maximumBitRate_BasicService:                                                       
      {                                                                                 
        currBlock = "maximumBitRate";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MaximumBitRate_opt                                                       
    ;                                                                                   
                                                                                        
                                                                
  BasicServiceCode_opt:                                        
      BasicServiceCode                                         
    |                                                           
    ;                                                           
                                                                
  BasicServiceCode:                                                       
      TAP_0311.BasicServiceCode                                  
      {                                                                    
        __onBlockStart("TAP_0311.BasicServiceCode", false);    
        //logStdout("Parsed Choice BasicServiceCode\n");                 
      }                                                         
      BasicServiceCode_elems                                   
      ASN1.BlockEnd                                                
      {                                                         
        __onBlockEnd("TAP_0311.BasicServiceCode");  
        //logStdout("BasicServiceCode Choice END.\n");        
      }                                                         
    ;                                                           
                                                                
  BasicServiceCode_elems:                                      
      teleServiceCode_BasicServiceCode     
    | bearerServiceCode_BasicServiceCode     
    ;                                                           
                                                                
  teleServiceCode_BasicServiceCode:                                                       
      {                                                                                 
        currBlock = "teleServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TeleServiceCode                                                           
    ;                                                                                   
                                                                                        
  bearerServiceCode_BasicServiceCode:                                                       
      {                                                                                 
        currBlock = "bearerServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BearerServiceCode                                                           
    ;                                                                                   
                                                                                        
                                                                                        
  BasicServiceCodeList_opt:                                                                
      TAP_0311.BasicServiceCodeList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.BasicServiceCodeList", true);                  
        //logStdout("Parsed List BasicServiceCodeList\n");                                
      }                                                                                 
      BasicServiceCodeList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.BasicServiceCodeList");                          
        //logStdout("BasicServiceCodeList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  BasicServiceCodeList:                                                                    
      BasicServiceCodeList                                                                 
      BasicServiceCode_BasicServiceCodeList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  BasicServiceCode_BasicServiceCodeList:                                                       
      {                                                                                 
        currBlock = "BasicServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BasicServiceCode                                                           
    ;                                                                                   
                                                                   
  BasicServiceUsed_opt:                                           
      BasicServiceUsed                                            
    |                                                              
    ;                                                              
                                                                   
  BasicServiceUsed:                                               
      TAP_0311.BasicServiceUsed                                 
      {                                                                   
        __onBlockStart("TAP_0311.BasicServiceUsed", false);   
        //logStdout("Parsed Sequence BasicServiceUsed\n");              
      }                                                                   
      basicService_BasicServiceUsed     
      chargingTimeStamp_BasicServiceUsed     
      chargeInformationList_BasicServiceUsed     
      hSCSDIndicator_BasicServiceUsed     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.BasicServiceUsed");     
        //logStdout("BasicServiceUsed Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  basicService_BasicServiceUsed:                                                       
      {                                                                                 
        currBlock = "basicService";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BasicService_opt                                                       
    ;                                                                                   
                                                                                        
  chargingTimeStamp_BasicServiceUsed:                                                       
      {                                                                                 
        currBlock = "chargingTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargingTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  chargeInformationList_BasicServiceUsed:                                                       
      {                                                                                 
        currBlock = "chargeInformationList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeInformationList_opt                                                       
    ;                                                                                   
                                                                                        
  hSCSDIndicator_BasicServiceUsed:                                                       
      {                                                                                 
        currBlock = "hSCSDIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HSCSDIndicator_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  BasicServiceUsedList_opt:                                                                
      TAP_0311.BasicServiceUsedList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.BasicServiceUsedList", true);                  
        //logStdout("Parsed List BasicServiceUsedList\n");                                
      }                                                                                 
      BasicServiceUsedList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.BasicServiceUsedList");                          
        //logStdout("BasicServiceUsedList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  BasicServiceUsedList:                                                                    
      BasicServiceUsedList                                                                 
      BasicServiceUsed_BasicServiceUsedList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  BasicServiceUsed_BasicServiceUsedList:                                                       
      {                                                                                 
        currBlock = "BasicServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BasicServiceUsed                                                           
    ;                                                                                   
                                                                   
  BatchControlError_opt:                                           
      BatchControlError                                            
    |                                                              
    ;                                                              
                                                                   
  BatchControlError:                                               
      RAP_0103.BatchControlError                                 
      {                                                                   
        __onBlockStart("RAP_0103.BatchControlError", false);   
        //logStdout("Parsed Sequence BatchControlError\n");              
      }                                                                   
      batchControlInfo_BatchControlError     
      errorDetail_BatchControlError     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.BatchControlError");     
        //logStdout("BatchControlError Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  batchControlInfo_BatchControlError:                                                       
      {                                                                                 
        currBlock = "batchControlInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BatchControlInfo_opt                                                       
    ;                                                                                   
                                                                                        
  errorDetail_BatchControlError:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  BatchControlInfo_opt:                                           
      BatchControlInfo                                            
    |                                                              
    ;                                                              
                                                                   
  BatchControlInfo:                                               
      TAP_0311.BatchControlInfo                                 
      {                                                                   
        __onBlockStart("TAP_0311.BatchControlInfo", false);   
        //logStdout("Parsed Sequence BatchControlInfo\n");              
      }                                                                   
      sender_BatchControlInfo     
      recipient_BatchControlInfo     
      fileSequenceNumber_BatchControlInfo     
      fileCreationTimeStamp_BatchControlInfo     
      transferCutOffTimeStamp_BatchControlInfo     
      fileAvailableTimeStamp_BatchControlInfo     
      specificationVersionNumber_BatchControlInfo     
      releaseVersionNumber_BatchControlInfo     
      fileTypeIndicator_BatchControlInfo     
      rapFileSequenceNumber_BatchControlInfo     
      operatorSpecInformation_BatchControlInfo     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.BatchControlInfo");     
        //logStdout("BatchControlInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  sender_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "sender";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Sender_opt                                                       
    ;                                                                                   
                                                                                        
  recipient_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "recipient";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Recipient_opt                                                       
    ;                                                                                   
                                                                                        
  fileSequenceNumber_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "fileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  fileCreationTimeStamp_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "fileCreationTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileCreationTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  transferCutOffTimeStamp_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "transferCutOffTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransferCutOffTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  fileAvailableTimeStamp_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "fileAvailableTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileAvailableTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  specificationVersionNumber_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "specificationVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SpecificationVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  releaseVersionNumber_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "releaseVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReleaseVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  fileTypeIndicator_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "fileTypeIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileTypeIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_BatchControlInfo:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  BearerServiceCode_opt:                                                         
      BearerServiceCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  BearerServiceCode:                                                             
      TAP_0311.BearerServiceCode                                        
      {                                                                          
        __onField("TAP_0311.BearerServiceCode.BearerServiceCode");    
        //logStdout("Parsed Leaf BearerServiceCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
  Bid_opt:         
      Bid          
    |                            
    ;                            
                                 
  Bid:             
      AsciiString               
    ;                            
                                      
  CallEventDetail_opt:              
      CallEventDetail               
    |                                 
    ;                                 
                                      
  CallEventDetail:                  
      {                               
        __onBlockStart("", false);  
      }                               
      CallEventDetail_elems         
      {                               
        __onBlockEnd("");           
      }                               
    ;                                 
                                      
  CallEventDetail_elems:            
      mobileOriginatedCall_CallEventDetail     
    | mobileTerminatedCall_CallEventDetail     
    | supplServiceEvent_CallEventDetail     
    | serviceCentreUsage_CallEventDetail     
    | gprsCall_CallEventDetail     
    | contentTransaction_CallEventDetail     
    | locationService_CallEventDetail     
    ;                                 
                                      
  mobileOriginatedCall_CallEventDetail:                                                       
      {                                                                                 
        currBlock = "mobileOriginatedCall";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MobileOriginatedCall                                                           
    ;                                                                                   
                                                                                        
  mobileTerminatedCall_CallEventDetail:                                                       
      {                                                                                 
        currBlock = "mobileTerminatedCall";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MobileTerminatedCall                                                           
    ;                                                                                   
                                                                                        
  supplServiceEvent_CallEventDetail:                                                       
      {                                                                                 
        currBlock = "supplServiceEvent";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SupplServiceEvent                                                           
    ;                                                                                   
                                                                                        
  serviceCentreUsage_CallEventDetail:                                                       
      {                                                                                 
        currBlock = "serviceCentreUsage";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServiceCentreUsage                                                           
    ;                                                                                   
                                                                                        
  gprsCall_CallEventDetail:                                                       
      {                                                                                 
        currBlock = "gprsCall";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsCall                                                           
    ;                                                                                   
                                                                                        
  contentTransaction_CallEventDetail:                                                       
      {                                                                                 
        currBlock = "contentTransaction";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentTransaction                                                           
    ;                                                                                   
                                                                                        
  locationService_CallEventDetail:                                                       
      {                                                                                 
        currBlock = "locationService";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationService                                                           
    ;                                                                                   
                                                                                        
                                                                                 
  CallEventDetailsCount_opt:                                                         
      CallEventDetailsCount                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CallEventDetailsCount:                                                             
      TAP_0311.CallEventDetailsCount                                        
      {                                                                          
        __onField("TAP_0311.CallEventDetailsCount.CallEventDetailsCount");    
        //logStdout("Parsed Leaf CallEventDetailsCount\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  CallEventStartTimeStamp_opt:                                           
      CallEventStartTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  CallEventStartTimeStamp:                                               
      TAP_0311.CallEventStartTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.CallEventStartTimeStamp", false);   
        //logStdout("Parsed Sequence CallEventStartTimeStamp\n");              
      }                                                                   
      localTimeStamp_CallEventStartTimeStamp     
      utcTimeOffsetCode_CallEventStartTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.CallEventStartTimeStamp");     
        //logStdout("CallEventStartTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_CallEventStartTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_CallEventStartTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  CallOriginator_opt:                                           
      CallOriginator                                            
    |                                                              
    ;                                                              
                                                                   
  CallOriginator:                                               
      TAP_0311.CallOriginator                                 
      {                                                                   
        __onBlockStart("TAP_0311.CallOriginator", false);   
        //logStdout("Parsed Sequence CallOriginator\n");              
      }                                                                   
      callingNumber_CallOriginator     
      clirIndicator_CallOriginator     
      sMSOriginator_CallOriginator     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.CallOriginator");     
        //logStdout("CallOriginator Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  callingNumber_CallOriginator:                                                       
      {                                                                                 
        currBlock = "callingNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallingNumber_opt                                                       
    ;                                                                                   
                                                                                        
  clirIndicator_CallOriginator:                                                       
      {                                                                                 
        currBlock = "clirIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ClirIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  sMSOriginator_CallOriginator:                                                       
      {                                                                                 
        currBlock = "sMSOriginator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SMSOriginator_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  CallReference_opt:                                                         
      CallReference                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CallReference:                                                             
      TAP_0311.CallReference                                        
      {                                                                          
        __onField("TAP_0311.CallReference.CallReference");    
        //logStdout("Parsed Leaf CallReference\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  CallTypeGroup_opt:                                           
      CallTypeGroup                                            
    |                                                              
    ;                                                              
                                                                   
  CallTypeGroup:                                               
      TAP_0311.CallTypeGroup                                 
      {                                                                   
        __onBlockStart("TAP_0311.CallTypeGroup", false);   
        //logStdout("Parsed Sequence CallTypeGroup\n");              
      }                                                                   
      callTypeLevel1_CallTypeGroup     
      callTypeLevel2_CallTypeGroup     
      callTypeLevel3_CallTypeGroup     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.CallTypeGroup");     
        //logStdout("CallTypeGroup Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  callTypeLevel1_CallTypeGroup:                                                       
      {                                                                                 
        currBlock = "callTypeLevel1";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallTypeLevel1_opt                                                       
    ;                                                                                   
                                                                                        
  callTypeLevel2_CallTypeGroup:                                                       
      {                                                                                 
        currBlock = "callTypeLevel2";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallTypeLevel2_opt                                                       
    ;                                                                                   
                                                                                        
  callTypeLevel3_CallTypeGroup:                                                       
      {                                                                                 
        currBlock = "callTypeLevel3";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallTypeLevel3_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  CallTypeLevel1_opt:                                                         
      CallTypeLevel1                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CallTypeLevel1:                                                             
      TAP_0311.CallTypeLevel1                                        
      {                                                                          
        __onField("TAP_0311.CallTypeLevel1.CallTypeLevel1");    
        //logStdout("Parsed Leaf CallTypeLevel1\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CallTypeLevel2_opt:                                                         
      CallTypeLevel2                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CallTypeLevel2:                                                             
      TAP_0311.CallTypeLevel2                                        
      {                                                                          
        __onField("TAP_0311.CallTypeLevel2.CallTypeLevel2");    
        //logStdout("Parsed Leaf CallTypeLevel2\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CallTypeLevel3_opt:                                                         
      CallTypeLevel3                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CallTypeLevel3:                                                             
      TAP_0311.CallTypeLevel3                                        
      {                                                                          
        __onField("TAP_0311.CallTypeLevel3.CallTypeLevel3");    
        //logStdout("Parsed Leaf CallTypeLevel3\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CalledNumber_opt:                                                         
      CalledNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CalledNumber:                                                             
      TAP_0311.CalledNumber                                        
      {                                                                          
        __onField("TAP_0311.CalledNumber.CalledNumber");    
        //logStdout("Parsed Leaf CalledNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CalledPlace_opt:                                                         
      CalledPlace                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CalledPlace:                                                             
      TAP_0311.CalledPlace                                        
      {                                                                          
        __onField("TAP_0311.CalledPlace.CalledPlace");    
        //logStdout("Parsed Leaf CalledPlace\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CalledRegion_opt:                                                         
      CalledRegion                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CalledRegion:                                                             
      TAP_0311.CalledRegion                                        
      {                                                                          
        __onField("TAP_0311.CalledRegion.CalledRegion");    
        //logStdout("Parsed Leaf CalledRegion\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CallingNumber_opt:                                                         
      CallingNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CallingNumber:                                                             
      TAP_0311.CallingNumber                                        
      {                                                                          
        __onField("TAP_0311.CallingNumber.CallingNumber");    
        //logStdout("Parsed Leaf CallingNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CamelDestinationNumber_opt:                                                         
      CamelDestinationNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CamelDestinationNumber:                                                             
      TAP_0311.CamelDestinationNumber                                        
      {                                                                          
        __onField("TAP_0311.CamelDestinationNumber.CamelDestinationNumber");    
        //logStdout("Parsed Leaf CamelDestinationNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CamelInvocationFee_opt:                                                         
      CamelInvocationFee                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CamelInvocationFee:                                                             
      TAP_0311.CamelInvocationFee                                        
      {                                                                          
        __onField("TAP_0311.CamelInvocationFee.CamelInvocationFee");    
        //logStdout("Parsed Leaf CamelInvocationFee\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CamelServiceKey_opt:                                                         
      CamelServiceKey                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CamelServiceKey:                                                             
      TAP_0311.CamelServiceKey                                        
      {                                                                          
        __onField("TAP_0311.CamelServiceKey.CamelServiceKey");    
        //logStdout("Parsed Leaf CamelServiceKey\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CamelServiceLevel_opt:                                                         
      CamelServiceLevel                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CamelServiceLevel:                                                             
      TAP_0311.CamelServiceLevel                                        
      {                                                                          
        __onField("TAP_0311.CamelServiceLevel.CamelServiceLevel");    
        //logStdout("Parsed Leaf CamelServiceLevel\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  CamelServiceUsed_opt:                                           
      CamelServiceUsed                                            
    |                                                              
    ;                                                              
                                                                   
  CamelServiceUsed:                                               
      TAP_0311.CamelServiceUsed                                 
      {                                                                   
        __onBlockStart("TAP_0311.CamelServiceUsed", false);   
        //logStdout("Parsed Sequence CamelServiceUsed\n");              
      }                                                                   
      camelServiceLevel_CamelServiceUsed     
      camelServiceKey_CamelServiceUsed     
      defaultCallHandling_CamelServiceUsed     
      exchangeRateCode_CamelServiceUsed     
      taxInformation_CamelServiceUsed     
      discountInformation_CamelServiceUsed     
      camelInvocationFee_CamelServiceUsed     
      threeGcamelDestination_CamelServiceUsed     
      cseInformation_CamelServiceUsed     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.CamelServiceUsed");     
        //logStdout("CamelServiceUsed Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  camelServiceLevel_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "camelServiceLevel";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CamelServiceLevel_opt                                                       
    ;                                                                                   
                                                                                        
  camelServiceKey_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "camelServiceKey";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CamelServiceKey_opt                                                       
    ;                                                                                   
                                                                                        
  defaultCallHandling_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "defaultCallHandling";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DefaultCallHandlingIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  exchangeRateCode_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "exchangeRateCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ExchangeRateCode_opt                                                       
    ;                                                                                   
                                                                                        
  taxInformation_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "taxInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxInformationList_opt                                                       
    ;                                                                                   
                                                                                        
  discountInformation_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "discountInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountInformation_opt                                                       
    ;                                                                                   
                                                                                        
  camelInvocationFee_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "camelInvocationFee";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CamelInvocationFee_opt                                                       
    ;                                                                                   
                                                                                        
  threeGcamelDestination_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "threeGcamelDestination";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ThreeGcamelDestination_opt                                                       
    ;                                                                                   
                                                                                        
  cseInformation_CamelServiceUsed:                                                       
      {                                                                                 
        currBlock = "cseInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CseInformation_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  CauseForTerm_opt:                                                         
      CauseForTerm                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CauseForTerm:                                                             
      TAP_0311.CauseForTerm                                        
      {                                                                          
        __onField("TAP_0311.CauseForTerm.CauseForTerm");    
        //logStdout("Parsed Leaf CauseForTerm\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CellId_opt:                                                         
      CellId                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CellId:                                                             
      TAP_0311.CellId                                        
      {                                                                          
        __onField("TAP_0311.CellId.CellId");    
        //logStdout("Parsed Leaf CellId\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Charge_opt:                                                         
      Charge                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Charge:                                                             
      TAP_0311.Charge                                        
      {                                                                          
        __onField("TAP_0311.Charge.Charge");    
        //logStdout("Parsed Leaf Charge\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ChargeDetail_opt:                                           
      ChargeDetail                                            
    |                                                              
    ;                                                              
                                                                   
  ChargeDetail:                                               
      TAP_0311.ChargeDetail                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargeDetail", false);   
        //logStdout("Parsed Sequence ChargeDetail\n");              
      }                                                                   
      chargeType_ChargeDetail     
      charge_ChargeDetail     
      chargeableUnits_ChargeDetail     
      chargedUnits_ChargeDetail     
      chargeDetailTimeStamp_ChargeDetail     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargeDetail");     
        //logStdout("ChargeDetail Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargeType_ChargeDetail:                                                       
      {                                                                                 
        currBlock = "chargeType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeType_opt                                                       
    ;                                                                                   
                                                                                        
  charge_ChargeDetail:                                                       
      {                                                                                 
        currBlock = "charge";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Charge_opt                                                       
    ;                                                                                   
                                                                                        
  chargeableUnits_ChargeDetail:                                                       
      {                                                                                 
        currBlock = "chargeableUnits";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeableUnits_opt                                                       
    ;                                                                                   
                                                                                        
  chargedUnits_ChargeDetail:                                                       
      {                                                                                 
        currBlock = "chargedUnits";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedUnits_opt                                                       
    ;                                                                                   
                                                                                        
  chargeDetailTimeStamp_ChargeDetail:                                                       
      {                                                                                 
        currBlock = "chargeDetailTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeDetailTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ChargeDetailList_opt:                                                                
      TAP_0311.ChargeDetailList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ChargeDetailList", true);                  
        //logStdout("Parsed List ChargeDetailList\n");                                
      }                                                                                 
      ChargeDetailList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ChargeDetailList");                          
        //logStdout("ChargeDetailList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargeDetailList:                                                                    
      ChargeDetailList                                                                 
      ChargeDetail_ChargeDetailList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargeDetail_ChargeDetailList:                                                       
      {                                                                                 
        currBlock = "ChargeDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeDetail                                                           
    ;                                                                                   
                                                                   
  ChargeDetailTimeStamp_opt:                                           
      ChargeDetailTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  ChargeDetailTimeStamp:                                               
      TAP_0311.ChargeDetailTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargeDetailTimeStamp", false);   
        //logStdout("Parsed Sequence ChargeDetailTimeStamp\n");              
      }                                                                   
      localTimeStamp_ChargeDetailTimeStamp     
      utcTimeOffsetCode_ChargeDetailTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargeDetailTimeStamp");     
        //logStdout("ChargeDetailTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_ChargeDetailTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_ChargeDetailTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  ChargeInformation_opt:                                           
      ChargeInformation                                            
    |                                                              
    ;                                                              
                                                                   
  ChargeInformation:                                               
      TAP_0311.ChargeInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargeInformation", false);   
        //logStdout("Parsed Sequence ChargeInformation\n");              
      }                                                                   
      chargedItem_ChargeInformation     
      exchangeRateCode_ChargeInformation     
      callTypeGroup_ChargeInformation     
      chargeDetailList_ChargeInformation     
      taxInformation_ChargeInformation     
      discountInformation_ChargeInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargeInformation");     
        //logStdout("ChargeInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargedItem_ChargeInformation:                                                       
      {                                                                                 
        currBlock = "chargedItem";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedItem_opt                                                       
    ;                                                                                   
                                                                                        
  exchangeRateCode_ChargeInformation:                                                       
      {                                                                                 
        currBlock = "exchangeRateCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ExchangeRateCode_opt                                                       
    ;                                                                                   
                                                                                        
  callTypeGroup_ChargeInformation:                                                       
      {                                                                                 
        currBlock = "callTypeGroup";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallTypeGroup_opt                                                       
    ;                                                                                   
                                                                                        
  chargeDetailList_ChargeInformation:                                                       
      {                                                                                 
        currBlock = "chargeDetailList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeDetailList_opt                                                       
    ;                                                                                   
                                                                                        
  taxInformation_ChargeInformation:                                                       
      {                                                                                 
        currBlock = "taxInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxInformationList_opt                                                       
    ;                                                                                   
                                                                                        
  discountInformation_ChargeInformation:                                                       
      {                                                                                 
        currBlock = "discountInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountInformation_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ChargeInformationList_opt:                                                                
      TAP_0311.ChargeInformationList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ChargeInformationList", true);                  
        //logStdout("Parsed List ChargeInformationList\n");                                
      }                                                                                 
      ChargeInformationList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ChargeInformationList");                          
        //logStdout("ChargeInformationList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargeInformationList:                                                                    
      ChargeInformationList                                                                 
      ChargeInformation_ChargeInformationList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargeInformation_ChargeInformationList:                                                       
      {                                                                                 
        currBlock = "ChargeInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeInformation                                                           
    ;                                                                                   
                                                                                 
  ChargeRefundIndicator_opt:                                                         
      ChargeRefundIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargeRefundIndicator:                                                             
      TAP_0311.ChargeRefundIndicator                                        
      {                                                                          
        __onField("TAP_0311.ChargeRefundIndicator.ChargeRefundIndicator");    
        //logStdout("Parsed Leaf ChargeRefundIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ChargeType_opt:                                                         
      ChargeType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargeType:                                                             
      TAP_0311.ChargeType                                        
      {                                                                          
        __onField("TAP_0311.ChargeType.ChargeType");    
        //logStdout("Parsed Leaf ChargeType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                
  ChargeableSubscriber_opt:                                        
      ChargeableSubscriber                                         
    |                                                           
    ;                                                           
                                                                
  ChargeableSubscriber:                                                       
      TAP_0311.ChargeableSubscriber                                  
      {                                                                    
        __onBlockStart("TAP_0311.ChargeableSubscriber", false);    
        //logStdout("Parsed Choice ChargeableSubscriber\n");                 
      }                                                         
      ChargeableSubscriber_elems                                   
      ASN1.BlockEnd                                                
      {                                                         
        __onBlockEnd("TAP_0311.ChargeableSubscriber");  
        //logStdout("ChargeableSubscriber Choice END.\n");        
      }                                                         
    ;                                                           
                                                                
  ChargeableSubscriber_elems:                                      
      simChargeableSubscriber_ChargeableSubscriber     
    | minChargeableSubscriber_ChargeableSubscriber     
    ;                                                           
                                                                
  simChargeableSubscriber_ChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "simChargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SimChargeableSubscriber                                                           
    ;                                                                                   
                                                                                        
  minChargeableSubscriber_ChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "minChargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MinChargeableSubscriber                                                           
    ;                                                                                   
                                                                                        
                                                                                 
  ChargeableUnits_opt:                                                         
      ChargeableUnits                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargeableUnits:                                                             
      TAP_0311.ChargeableUnits                                        
      {                                                                          
        __onField("TAP_0311.ChargeableUnits.ChargeableUnits");    
        //logStdout("Parsed Leaf ChargeableUnits\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ChargedItem_opt:                                                         
      ChargedItem                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargedItem:                                                             
      TAP_0311.ChargedItem                                        
      {                                                                          
        __onField("TAP_0311.ChargedItem.ChargedItem");    
        //logStdout("Parsed Leaf ChargedItem\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ChargedPartyEquipment_opt:                                           
      ChargedPartyEquipment                                            
    |                                                              
    ;                                                              
                                                                   
  ChargedPartyEquipment:                                               
      TAP_0311.ChargedPartyEquipment                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargedPartyEquipment", false);   
        //logStdout("Parsed Sequence ChargedPartyEquipment\n");              
      }                                                                   
      equipmentIdType_ChargedPartyEquipment     
      equipmentId_ChargedPartyEquipment     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargedPartyEquipment");     
        //logStdout("ChargedPartyEquipment Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  equipmentIdType_ChargedPartyEquipment:                                                       
      {                                                                                 
        currBlock = "equipmentIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EquipmentIdType_opt                                                       
    ;                                                                                   
                                                                                        
  equipmentId_ChargedPartyEquipment:                                                       
      {                                                                                 
        currBlock = "equipmentId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EquipmentId_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ChargedPartyHomeIdList_opt:                                                                
      TAP_0311.ChargedPartyHomeIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ChargedPartyHomeIdList", true);                  
        //logStdout("Parsed List ChargedPartyHomeIdList\n");                                
      }                                                                                 
      ChargedPartyHomeIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ChargedPartyHomeIdList");                          
        //logStdout("ChargedPartyHomeIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargedPartyHomeIdList:                                                                    
      ChargedPartyHomeIdList                                                                 
      ChargedPartyHomeIdentification_ChargedPartyHomeIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargedPartyHomeIdentification_ChargedPartyHomeIdList:                                                       
      {                                                                                 
        currBlock = "ChargedPartyHomeIdentification";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyHomeIdentification                                                           
    ;                                                                                   
                                                                   
  ChargedPartyHomeIdentification_opt:                                           
      ChargedPartyHomeIdentification                                            
    |                                                              
    ;                                                              
                                                                   
  ChargedPartyHomeIdentification:                                               
      TAP_0311.ChargedPartyHomeIdentification                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargedPartyHomeIdentification", false);   
        //logStdout("Parsed Sequence ChargedPartyHomeIdentification\n");              
      }                                                                   
      homeIdType_ChargedPartyHomeIdentification     
      homeIdentifier_ChargedPartyHomeIdentification     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargedPartyHomeIdentification");     
        //logStdout("ChargedPartyHomeIdentification Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  homeIdType_ChargedPartyHomeIdentification:                                                       
      {                                                                                 
        currBlock = "homeIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeIdType_opt                                                       
    ;                                                                                   
                                                                                        
  homeIdentifier_ChargedPartyHomeIdentification:                                                       
      {                                                                                 
        currBlock = "homeIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ChargedPartyIdList_opt:                                                                
      TAP_0311.ChargedPartyIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ChargedPartyIdList", true);                  
        //logStdout("Parsed List ChargedPartyIdList\n");                                
      }                                                                                 
      ChargedPartyIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ChargedPartyIdList");                          
        //logStdout("ChargedPartyIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargedPartyIdList:                                                                    
      ChargedPartyIdList                                                                 
      ChargedPartyIdentification_ChargedPartyIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargedPartyIdentification_ChargedPartyIdList:                                                       
      {                                                                                 
        currBlock = "ChargedPartyIdentification";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyIdentification                                                           
    ;                                                                                   
                                                                                 
  ChargedPartyIdType_opt:                                                         
      ChargedPartyIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargedPartyIdType:                                                             
      TAP_0311.ChargedPartyIdType                                        
      {                                                                          
        __onField("TAP_0311.ChargedPartyIdType.ChargedPartyIdType");    
        //logStdout("Parsed Leaf ChargedPartyIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ChargedPartyIdentification_opt:                                           
      ChargedPartyIdentification                                            
    |                                                              
    ;                                                              
                                                                   
  ChargedPartyIdentification:                                               
      TAP_0311.ChargedPartyIdentification                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargedPartyIdentification", false);   
        //logStdout("Parsed Sequence ChargedPartyIdentification\n");              
      }                                                                   
      chargedPartyIdType_ChargedPartyIdentification     
      chargedPartyIdentifier_ChargedPartyIdentification     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargedPartyIdentification");     
        //logStdout("ChargedPartyIdentification Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargedPartyIdType_ChargedPartyIdentification:                                                       
      {                                                                                 
        currBlock = "chargedPartyIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyIdType_opt                                                       
    ;                                                                                   
                                                                                        
  chargedPartyIdentifier_ChargedPartyIdentification:                                                       
      {                                                                                 
        currBlock = "chargedPartyIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  ChargedPartyIdentifier_opt:                                                         
      ChargedPartyIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargedPartyIdentifier:                                                             
      TAP_0311.ChargedPartyIdentifier                                        
      {                                                                          
        __onField("TAP_0311.ChargedPartyIdentifier.ChargedPartyIdentifier");    
        //logStdout("Parsed Leaf ChargedPartyIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ChargedPartyInformation_opt:                                           
      ChargedPartyInformation                                            
    |                                                              
    ;                                                              
                                                                   
  ChargedPartyInformation:                                               
      TAP_0311.ChargedPartyInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargedPartyInformation", false);   
        //logStdout("Parsed Sequence ChargedPartyInformation\n");              
      }                                                                   
      chargedPartyIdList_ChargedPartyInformation     
      chargedPartyHomeIdList_ChargedPartyInformation     
      chargedPartyLocationList_ChargedPartyInformation     
      chargedPartyEquipment_ChargedPartyInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargedPartyInformation");     
        //logStdout("ChargedPartyInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargedPartyIdList_ChargedPartyInformation:                                                       
      {                                                                                 
        currBlock = "chargedPartyIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyIdList_opt                                                       
    ;                                                                                   
                                                                                        
  chargedPartyHomeIdList_ChargedPartyInformation:                                                       
      {                                                                                 
        currBlock = "chargedPartyHomeIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyHomeIdList_opt                                                       
    ;                                                                                   
                                                                                        
  chargedPartyLocationList_ChargedPartyInformation:                                                       
      {                                                                                 
        currBlock = "chargedPartyLocationList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyLocationList_opt                                                       
    ;                                                                                   
                                                                                        
  chargedPartyEquipment_ChargedPartyInformation:                                                       
      {                                                                                 
        currBlock = "chargedPartyEquipment";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyEquipment_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  ChargedPartyLocation_opt:                                           
      ChargedPartyLocation                                            
    |                                                              
    ;                                                              
                                                                   
  ChargedPartyLocation:                                               
      TAP_0311.ChargedPartyLocation                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargedPartyLocation", false);   
        //logStdout("Parsed Sequence ChargedPartyLocation\n");              
      }                                                                   
      locationIdType_ChargedPartyLocation     
      locationIdentifier_ChargedPartyLocation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargedPartyLocation");     
        //logStdout("ChargedPartyLocation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  locationIdType_ChargedPartyLocation:                                                       
      {                                                                                 
        currBlock = "locationIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationIdType_opt                                                       
    ;                                                                                   
                                                                                        
  locationIdentifier_ChargedPartyLocation:                                                       
      {                                                                                 
        currBlock = "locationIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ChargedPartyLocationList_opt:                                                                
      TAP_0311.ChargedPartyLocationList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ChargedPartyLocationList", true);                  
        //logStdout("Parsed List ChargedPartyLocationList\n");                                
      }                                                                                 
      ChargedPartyLocationList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ChargedPartyLocationList");                          
        //logStdout("ChargedPartyLocationList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargedPartyLocationList:                                                                    
      ChargedPartyLocationList                                                                 
      ChargedPartyLocation_ChargedPartyLocationList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ChargedPartyLocation_ChargedPartyLocationList:                                                       
      {                                                                                 
        currBlock = "ChargedPartyLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyLocation                                                           
    ;                                                                                   
                                                                                 
  ChargedPartyStatus_opt:                                                         
      ChargedPartyStatus                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargedPartyStatus:                                                             
      TAP_0311.ChargedPartyStatus                                        
      {                                                                          
        __onField("TAP_0311.ChargedPartyStatus.ChargedPartyStatus");    
        //logStdout("Parsed Leaf ChargedPartyStatus\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ChargedUnits_opt:                                                         
      ChargedUnits                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargedUnits:                                                             
      TAP_0311.ChargedUnits                                        
      {                                                                          
        __onField("TAP_0311.ChargedUnits.ChargedUnits");    
        //logStdout("Parsed Leaf ChargedUnits\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ChargingId_opt:                                                         
      ChargingId                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargingId:                                                             
      TAP_0311.ChargingId                                        
      {                                                                          
        __onField("TAP_0311.ChargingId.ChargingId");    
        //logStdout("Parsed Leaf ChargingId\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ChargingPoint_opt:                                                         
      ChargingPoint                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargingPoint:                                                             
      TAP_0311.ChargingPoint                                        
      {                                                                          
        __onField("TAP_0311.ChargingPoint.ChargingPoint");    
        //logStdout("Parsed Leaf ChargingPoint\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ChargingTimeStamp_opt:                                           
      ChargingTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  ChargingTimeStamp:                                               
      TAP_0311.ChargingTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.ChargingTimeStamp", false);   
        //logStdout("Parsed Sequence ChargingTimeStamp\n");              
      }                                                                   
      localTimeStamp_ChargingTimeStamp     
      utcTimeOffsetCode_ChargingTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ChargingTimeStamp");     
        //logStdout("ChargingTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_ChargingTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_ChargingTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  ClirIndicator_opt:                                                         
      ClirIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ClirIndicator:                                                             
      TAP_0311.ClirIndicator                                        
      {                                                                          
        __onField("TAP_0311.ClirIndicator.ClirIndicator");    
        //logStdout("Parsed Leaf ClirIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Code_opt:                                                         
      Code                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Code:                                                             
      TAP_0311.Code                                        
      {                                                                          
        __onField("TAP_0311.Code.Code");    
        //logStdout("Parsed Leaf Code\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Commission_opt:                                                         
      Commission                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Commission:                                                             
      TAP_0311.Commission                                        
      {                                                                          
        __onField("TAP_0311.Commission.Commission");    
        //logStdout("Parsed Leaf Commission\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  CompletionTimeStamp_opt:                                           
      CompletionTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  CompletionTimeStamp:                                               
      TAP_0311.CompletionTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.CompletionTimeStamp", false);   
        //logStdout("Parsed Sequence CompletionTimeStamp\n");              
      }                                                                   
      localTimeStamp_CompletionTimeStamp     
      utcTimeOffsetCode_CompletionTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.CompletionTimeStamp");     
        //logStdout("CompletionTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_CompletionTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_CompletionTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  ContentChargingPoint_opt:                                                         
      ContentChargingPoint                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ContentChargingPoint:                                                             
      TAP_0311.ContentChargingPoint                                        
      {                                                                          
        __onField("TAP_0311.ContentChargingPoint.ContentChargingPoint");    
        //logStdout("Parsed Leaf ContentChargingPoint\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ContentProvider_opt:                                           
      ContentProvider                                            
    |                                                              
    ;                                                              
                                                                   
  ContentProvider:                                               
      TAP_0311.ContentProvider                                 
      {                                                                   
        __onBlockStart("TAP_0311.ContentProvider", false);   
        //logStdout("Parsed Sequence ContentProvider\n");              
      }                                                                   
      contentProviderIdType_ContentProvider     
      contentProviderIdentifier_ContentProvider     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ContentProvider");     
        //logStdout("ContentProvider Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  contentProviderIdType_ContentProvider:                                                       
      {                                                                                 
        currBlock = "contentProviderIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentProviderIdType_opt                                                       
    ;                                                                                   
                                                                                        
  contentProviderIdentifier_ContentProvider:                                                       
      {                                                                                 
        currBlock = "contentProviderIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentProviderIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ContentProviderIdList_opt:                                                                
      TAP_0311.ContentProviderIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ContentProviderIdList", true);                  
        //logStdout("Parsed List ContentProviderIdList\n");                                
      }                                                                                 
      ContentProviderIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ContentProviderIdList");                          
        //logStdout("ContentProviderIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ContentProviderIdList:                                                                    
      ContentProviderIdList                                                                 
      ContentProvider_ContentProviderIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ContentProvider_ContentProviderIdList:                                                       
      {                                                                                 
        currBlock = "ContentProvider";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentProvider                                                           
    ;                                                                                   
                                                                                 
  ContentProviderIdType_opt:                                                         
      ContentProviderIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ContentProviderIdType:                                                             
      TAP_0311.ContentProviderIdType                                        
      {                                                                          
        __onField("TAP_0311.ContentProviderIdType.ContentProviderIdType");    
        //logStdout("Parsed Leaf ContentProviderIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ContentProviderIdentifier_opt:                                                         
      ContentProviderIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ContentProviderIdentifier:                                                             
      TAP_0311.ContentProviderIdentifier                                        
      {                                                                          
        __onField("TAP_0311.ContentProviderIdentifier.ContentProviderIdentifier");    
        //logStdout("Parsed Leaf ContentProviderIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ContentProviderName_opt:                                                         
      ContentProviderName                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ContentProviderName:                                                             
      TAP_0311.ContentProviderName                                        
      {                                                                          
        __onField("TAP_0311.ContentProviderName.ContentProviderName");    
        //logStdout("Parsed Leaf ContentProviderName\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ContentServiceUsed_opt:                                           
      ContentServiceUsed                                            
    |                                                              
    ;                                                              
                                                                   
  ContentServiceUsed:                                               
      TAP_0311.ContentServiceUsed                                 
      {                                                                   
        __onBlockStart("TAP_0311.ContentServiceUsed", false);   
        //logStdout("Parsed Sequence ContentServiceUsed\n");              
      }                                                                   
      contentTransactionCode_ContentServiceUsed     
      contentTransactionType_ContentServiceUsed     
      objectType_ContentServiceUsed     
      transactionDescriptionSupp_ContentServiceUsed     
      transactionShortDescription_ContentServiceUsed     
      transactionDetailDescription_ContentServiceUsed     
      transactionIdentifier_ContentServiceUsed     
      transactionAuthCode_ContentServiceUsed     
      dataVolumeIncoming_ContentServiceUsed     
      dataVolumeOutgoing_ContentServiceUsed     
      totalDataVolume_ContentServiceUsed     
      chargeRefundIndicator_ContentServiceUsed     
      contentChargingPoint_ContentServiceUsed     
      chargeInformationList_ContentServiceUsed     
      advisedChargeInformation_ContentServiceUsed     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ContentServiceUsed");     
        //logStdout("ContentServiceUsed Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  contentTransactionCode_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "contentTransactionCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentTransactionCode_opt                                                       
    ;                                                                                   
                                                                                        
  contentTransactionType_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "contentTransactionType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentTransactionType_opt                                                       
    ;                                                                                   
                                                                                        
  objectType_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "objectType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ObjectType_opt                                                       
    ;                                                                                   
                                                                                        
  transactionDescriptionSupp_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "transactionDescriptionSupp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransactionDescriptionSupp_opt                                                       
    ;                                                                                   
                                                                                        
  transactionShortDescription_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "transactionShortDescription";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransactionShortDescription_opt                                                       
    ;                                                                                   
                                                                                        
  transactionDetailDescription_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "transactionDetailDescription";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransactionDetailDescription_opt                                                       
    ;                                                                                   
                                                                                        
  transactionIdentifier_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "transactionIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransactionIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
  transactionAuthCode_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "transactionAuthCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransactionAuthCode_opt                                                       
    ;                                                                                   
                                                                                        
  dataVolumeIncoming_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "dataVolumeIncoming";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DataVolumeIncoming_opt                                                       
    ;                                                                                   
                                                                                        
  dataVolumeOutgoing_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "dataVolumeOutgoing";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DataVolumeOutgoing_opt                                                       
    ;                                                                                   
                                                                                        
  totalDataVolume_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "totalDataVolume";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalDataVolume_opt                                                       
    ;                                                                                   
                                                                                        
  chargeRefundIndicator_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "chargeRefundIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeRefundIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  contentChargingPoint_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "contentChargingPoint";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentChargingPoint_opt                                                       
    ;                                                                                   
                                                                                        
  chargeInformationList_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "chargeInformationList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeInformationList_opt                                                       
    ;                                                                                   
                                                                                        
  advisedChargeInformation_ContentServiceUsed:                                                       
      {                                                                                 
        currBlock = "advisedChargeInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AdvisedChargeInformation_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ContentServiceUsedList_opt:                                                                
      TAP_0311.ContentServiceUsedList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ContentServiceUsedList", true);                  
        //logStdout("Parsed List ContentServiceUsedList\n");                                
      }                                                                                 
      ContentServiceUsedList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ContentServiceUsedList");                          
        //logStdout("ContentServiceUsedList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ContentServiceUsedList:                                                                    
      ContentServiceUsedList                                                                 
      ContentServiceUsed_ContentServiceUsedList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ContentServiceUsed_ContentServiceUsedList:                                                       
      {                                                                                 
        currBlock = "ContentServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentServiceUsed                                                           
    ;                                                                                   
                                                                   
  ContentTransaction_opt:                                           
      ContentTransaction                                            
    |                                                              
    ;                                                              
                                                                   
  ContentTransaction:                                               
      TAP_0311.ContentTransaction                                 
      {                                                                   
        __onBlockStart("TAP_0311.ContentTransaction", false);   
        //logStdout("Parsed Sequence ContentTransaction\n");              
      }                                                                   
      contentTransactionBasicInfo_ContentTransaction     
      chargedPartyInformation_ContentTransaction     
      servingPartiesInformation_ContentTransaction     
      contentServiceUsed_ContentTransaction     
      operatorSpecInformation_ContentTransaction     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ContentTransaction");     
        //logStdout("ContentTransaction Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  contentTransactionBasicInfo_ContentTransaction:                                                       
      {                                                                                 
        currBlock = "contentTransactionBasicInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentTransactionBasicInfo_opt                                                       
    ;                                                                                   
                                                                                        
  chargedPartyInformation_ContentTransaction:                                                       
      {                                                                                 
        currBlock = "chargedPartyInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyInformation_opt                                                       
    ;                                                                                   
                                                                                        
  servingPartiesInformation_ContentTransaction:                                                       
      {                                                                                 
        currBlock = "servingPartiesInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServingPartiesInformation_opt                                                       
    ;                                                                                   
                                                                                        
  contentServiceUsed_ContentTransaction:                                                       
      {                                                                                 
        currBlock = "contentServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentServiceUsedList_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_ContentTransaction:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  ContentTransactionBasicInfo_opt:                                           
      ContentTransactionBasicInfo                                            
    |                                                              
    ;                                                              
                                                                   
  ContentTransactionBasicInfo:                                               
      TAP_0311.ContentTransactionBasicInfo                                 
      {                                                                   
        __onBlockStart("TAP_0311.ContentTransactionBasicInfo", false);   
        //logStdout("Parsed Sequence ContentTransactionBasicInfo\n");              
      }                                                                   
      rapFileSequenceNumber_ContentTransactionBasicInfo     
      orderPlacedTimeStamp_ContentTransactionBasicInfo     
      requestedDeliveryTimeStamp_ContentTransactionBasicInfo     
      actualDeliveryTimeStamp_ContentTransactionBasicInfo     
      totalTransactionDuration_ContentTransactionBasicInfo     
      transactionStatus_ContentTransactionBasicInfo     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ContentTransactionBasicInfo");     
        //logStdout("ContentTransactionBasicInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  rapFileSequenceNumber_ContentTransactionBasicInfo:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  orderPlacedTimeStamp_ContentTransactionBasicInfo:                                                       
      {                                                                                 
        currBlock = "orderPlacedTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OrderPlacedTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  requestedDeliveryTimeStamp_ContentTransactionBasicInfo:                                                       
      {                                                                                 
        currBlock = "requestedDeliveryTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RequestedDeliveryTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  actualDeliveryTimeStamp_ContentTransactionBasicInfo:                                                       
      {                                                                                 
        currBlock = "actualDeliveryTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ActualDeliveryTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  totalTransactionDuration_ContentTransactionBasicInfo:                                                       
      {                                                                                 
        currBlock = "totalTransactionDuration";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalTransactionDuration_opt                                                       
    ;                                                                                   
                                                                                        
  transactionStatus_ContentTransactionBasicInfo:                                                       
      {                                                                                 
        currBlock = "transactionStatus";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransactionStatus_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  ContentTransactionCode_opt:                                                         
      ContentTransactionCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ContentTransactionCode:                                                             
      TAP_0311.ContentTransactionCode                                        
      {                                                                          
        __onField("TAP_0311.ContentTransactionCode.ContentTransactionCode");    
        //logStdout("Parsed Leaf ContentTransactionCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ContentTransactionType_opt:                                                         
      ContentTransactionType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ContentTransactionType:                                                             
      TAP_0311.ContentTransactionType                                        
      {                                                                          
        __onField("TAP_0311.ContentTransactionType.ContentTransactionType");    
        //logStdout("Parsed Leaf ContentTransactionType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CseInformation_opt:                                                         
      CseInformation                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CseInformation:                                                             
      TAP_0311.CseInformation                                        
      {                                                                          
        __onField("TAP_0311.CseInformation.CseInformation");    
        //logStdout("Parsed Leaf CseInformation\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Currency_opt:                                                         
      Currency                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Currency:                                                             
      TAP_0311.Currency                                        
      {                                                                          
        __onField("TAP_0311.Currency.Currency");    
        //logStdout("Parsed Leaf Currency\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  CurrencyConversion_opt:                                           
      CurrencyConversion                                            
    |                                                              
    ;                                                              
                                                                   
  CurrencyConversion:                                               
      TAP_0311.CurrencyConversion                                 
      {                                                                   
        __onBlockStart("TAP_0311.CurrencyConversion", false);   
        //logStdout("Parsed Sequence CurrencyConversion\n");              
      }                                                                   
      exchangeRateCode_CurrencyConversion     
      numberOfDecimalPlaces_CurrencyConversion     
      exchangeRate_CurrencyConversion     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.CurrencyConversion");     
        //logStdout("CurrencyConversion Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  exchangeRateCode_CurrencyConversion:                                                       
      {                                                                                 
        currBlock = "exchangeRateCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ExchangeRateCode_opt                                                       
    ;                                                                                   
                                                                                        
  numberOfDecimalPlaces_CurrencyConversion:                                                       
      {                                                                                 
        currBlock = "numberOfDecimalPlaces";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NumberOfDecimalPlaces_opt                                                       
    ;                                                                                   
                                                                                        
  exchangeRate_CurrencyConversion:                                                       
      {                                                                                 
        currBlock = "exchangeRate";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ExchangeRate_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  CurrencyConversionList_opt:                                                                
      TAP_0311.CurrencyConversionList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.CurrencyConversionList", true);                  
        //logStdout("Parsed List CurrencyConversionList\n");                                
      }                                                                                 
      CurrencyConversionList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.CurrencyConversionList");                          
        //logStdout("CurrencyConversionList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  CurrencyConversionList:                                                                    
      CurrencyConversionList                                                                 
      CurrencyConversion_CurrencyConversionList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  CurrencyConversion_CurrencyConversionList:                                                       
      {                                                                                 
        currBlock = "CurrencyConversion";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CurrencyConversion                                                           
    ;                                                                                   
                                                                                 
  CustomerIdType_opt:                                                         
      CustomerIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CustomerIdType:                                                             
      TAP_0311.CustomerIdType                                        
      {                                                                          
        __onField("TAP_0311.CustomerIdType.CustomerIdType");    
        //logStdout("Parsed Leaf CustomerIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CustomerIdentifier_opt:                                                         
      CustomerIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CustomerIdentifier:                                                             
      TAP_0311.CustomerIdentifier                                        
      {                                                                          
        __onField("TAP_0311.CustomerIdentifier.CustomerIdentifier");    
        //logStdout("Parsed Leaf CustomerIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  DataVolume_opt:                                                         
      DataVolume                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DataVolume:                                                             
      TAP_0311.DataVolume                                        
      {                                                                          
        __onField("TAP_0311.DataVolume.DataVolume");    
        //logStdout("Parsed Leaf DataVolume\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  DataVolumeIncoming_opt:                                                         
      DataVolumeIncoming                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DataVolumeIncoming:                                                             
      TAP_0311.DataVolumeIncoming                                        
      {                                                                          
        __onField("TAP_0311.DataVolumeIncoming.DataVolumeIncoming");    
        //logStdout("Parsed Leaf DataVolumeIncoming\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  DataVolumeOutgoing_opt:                                                         
      DataVolumeOutgoing                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DataVolumeOutgoing:                                                             
      TAP_0311.DataVolumeOutgoing                                        
      {                                                                          
        __onField("TAP_0311.DataVolumeOutgoing.DataVolumeOutgoing");    
        //logStdout("Parsed Leaf DataVolumeOutgoing\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  DateTime_opt:                                           
      DateTime                                            
    |                                                              
    ;                                                              
                                                                   
  DateTime:                                               
      TAP_0311.DateTime                                 
      {                                                                   
        __onBlockStart("TAP_0311.DateTime", false);   
        //logStdout("Parsed Sequence DateTime\n");              
      }                                                                   
      localTimeStamp_DateTime     
      utcTimeOffsetCode_DateTime     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.DateTime");     
        //logStdout("DateTime Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_DateTime:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_DateTime:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  DateTimeLong_opt:                                           
      DateTimeLong                                            
    |                                                              
    ;                                                              
                                                                   
  DateTimeLong:                                               
      TAP_0311.DateTimeLong                                 
      {                                                                   
        __onBlockStart("TAP_0311.DateTimeLong", false);   
        //logStdout("Parsed Sequence DateTimeLong\n");              
      }                                                                   
      localTimeStamp_DateTimeLong     
      utcTimeOffset_DateTimeLong     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.DateTimeLong");     
        //logStdout("DateTimeLong Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_DateTimeLong:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_DateTimeLong:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  DefaultCallHandlingIndicator_opt:                                                         
      DefaultCallHandlingIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DefaultCallHandlingIndicator:                                                             
      TAP_0311.DefaultCallHandlingIndicator                                        
      {                                                                          
        __onField("TAP_0311.DefaultCallHandlingIndicator.DefaultCallHandlingIndicator");    
        //logStdout("Parsed Leaf DefaultCallHandlingIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  DepositTimeStamp_opt:                                           
      DepositTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  DepositTimeStamp:                                               
      TAP_0311.DepositTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.DepositTimeStamp", false);   
        //logStdout("Parsed Sequence DepositTimeStamp\n");              
      }                                                                   
      localTimeStamp_DepositTimeStamp     
      utcTimeOffsetCode_DepositTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.DepositTimeStamp");     
        //logStdout("DepositTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_DepositTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_DepositTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  Destination_opt:                                           
      Destination                                            
    |                                                              
    ;                                                              
                                                                   
  Destination:                                               
      TAP_0311.Destination                                 
      {                                                                   
        __onBlockStart("TAP_0311.Destination", false);   
        //logStdout("Parsed Sequence Destination\n");              
      }                                                                   
      calledNumber_Destination     
      dialledDigits_Destination     
      calledPlace_Destination     
      calledRegion_Destination     
      sMSDestinationNumber_Destination     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.Destination");     
        //logStdout("Destination Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  calledNumber_Destination:                                                       
      {                                                                                 
        currBlock = "calledNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CalledNumber_opt                                                       
    ;                                                                                   
                                                                                        
  dialledDigits_Destination:                                                       
      {                                                                                 
        currBlock = "dialledDigits";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DialledDigits_opt                                                       
    ;                                                                                   
                                                                                        
  calledPlace_Destination:                                                       
      {                                                                                 
        currBlock = "calledPlace";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CalledPlace_opt                                                       
    ;                                                                                   
                                                                                        
  calledRegion_Destination:                                                       
      {                                                                                 
        currBlock = "calledRegion";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CalledRegion_opt                                                       
    ;                                                                                   
                                                                                        
  sMSDestinationNumber_Destination:                                                       
      {                                                                                 
        currBlock = "sMSDestinationNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SMSDestinationNumber_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  DestinationNetwork_opt:                                                         
      DestinationNetwork                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DestinationNetwork:                                                             
      TAP_0311.DestinationNetwork                                        
      {                                                                          
        __onField("TAP_0311.DestinationNetwork.DestinationNetwork");    
        //logStdout("Parsed Leaf DestinationNetwork\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  DialledDigits_opt:                                                         
      DialledDigits                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DialledDigits:                                                             
      TAP_0311.DialledDigits                                        
      {                                                                          
        __onField("TAP_0311.DialledDigits.DialledDigits");    
        //logStdout("Parsed Leaf DialledDigits\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Discount_opt:                                                         
      Discount                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Discount:                                                             
      TAP_0311.Discount                                        
      {                                                                          
        __onField("TAP_0311.Discount.Discount");    
        //logStdout("Parsed Leaf Discount\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                
  DiscountApplied_opt:                                        
      DiscountApplied                                         
    |                                                           
    ;                                                           
                                                                
  DiscountApplied:                                                       
      TAP_0311.DiscountApplied                                  
      {                                                                    
        __onBlockStart("TAP_0311.DiscountApplied", false);    
        //logStdout("Parsed Choice DiscountApplied\n");                 
      }                                                         
      DiscountApplied_elems                                   
      ASN1.BlockEnd                                                
      {                                                         
        __onBlockEnd("TAP_0311.DiscountApplied");  
        //logStdout("DiscountApplied Choice END.\n");        
      }                                                         
    ;                                                           
                                                                
  DiscountApplied_elems:                                      
      fixedDiscountValue_DiscountApplied     
    | discountRate_DiscountApplied     
    ;                                                           
                                                                
  fixedDiscountValue_DiscountApplied:                                                       
      {                                                                                 
        currBlock = "fixedDiscountValue";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FixedDiscountValue                                                           
    ;                                                                                   
                                                                                        
  discountRate_DiscountApplied:                                                       
      {                                                                                 
        currBlock = "discountRate";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountRate                                                           
    ;                                                                                   
                                                                                        
                                                                                 
  DiscountCode_opt:                                                         
      DiscountCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DiscountCode:                                                             
      TAP_0311.DiscountCode                                        
      {                                                                          
        __onField("TAP_0311.DiscountCode.DiscountCode");    
        //logStdout("Parsed Leaf DiscountCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  DiscountInformation_opt:                                           
      DiscountInformation                                            
    |                                                              
    ;                                                              
                                                                   
  DiscountInformation:                                               
      TAP_0311.DiscountInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.DiscountInformation", false);   
        //logStdout("Parsed Sequence DiscountInformation\n");              
      }                                                                   
      discountCode_DiscountInformation     
      discount_DiscountInformation     
      discountableAmount_DiscountInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.DiscountInformation");     
        //logStdout("DiscountInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  discountCode_DiscountInformation:                                                       
      {                                                                                 
        currBlock = "discountCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountCode_opt                                                       
    ;                                                                                   
                                                                                        
  discount_DiscountInformation:                                                       
      {                                                                                 
        currBlock = "discount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Discount_opt                                                       
    ;                                                                                   
                                                                                        
  discountableAmount_DiscountInformation:                                                       
      {                                                                                 
        currBlock = "discountableAmount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountableAmount_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  DiscountRate_opt:                                                         
      DiscountRate                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DiscountRate:                                                             
      TAP_0311.DiscountRate                                        
      {                                                                          
        __onField("TAP_0311.DiscountRate.DiscountRate");    
        //logStdout("Parsed Leaf DiscountRate\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
  DiscountValue_opt:         
      DiscountValue          
    |                            
    ;                            
                                 
  DiscountValue:             
      AbsoluteAmount               
    ;                            
                                                                                 
  DiscountableAmount_opt:                                                         
      DiscountableAmount                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DiscountableAmount:                                                             
      TAP_0311.DiscountableAmount                                        
      {                                                                          
        __onField("TAP_0311.DiscountableAmount.DiscountableAmount");    
        //logStdout("Parsed Leaf DiscountableAmount\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  Discounting_opt:                                           
      Discounting                                            
    |                                                              
    ;                                                              
                                                                   
  Discounting:                                               
      TAP_0311.Discounting                                 
      {                                                                   
        __onBlockStart("TAP_0311.Discounting", false);   
        //logStdout("Parsed Sequence Discounting\n");              
      }                                                                   
      discountCode_Discounting     
      discountApplied_Discounting     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.Discounting");     
        //logStdout("Discounting Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  discountCode_Discounting:                                                       
      {                                                                                 
        currBlock = "discountCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountCode_opt                                                       
    ;                                                                                   
                                                                                        
  discountApplied_Discounting:                                                       
      {                                                                                 
        currBlock = "discountApplied";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DiscountApplied_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  DiscountingList_opt:                                                                
      TAP_0311.DiscountingList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.DiscountingList", true);                  
        //logStdout("Parsed List DiscountingList\n");                                
      }                                                                                 
      DiscountingList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.DiscountingList");                          
        //logStdout("DiscountingList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  DiscountingList:                                                                    
      DiscountingList                                                                 
      Discounting_DiscountingList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  Discounting_DiscountingList:                                                       
      {                                                                                 
        currBlock = "Discounting";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Discounting                                                           
    ;                                                                                   
                                                                                 
  DistanceChargeBandCode_opt:                                                         
      DistanceChargeBandCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  DistanceChargeBandCode:                                                             
      TAP_0311.DistanceChargeBandCode                                        
      {                                                                          
        __onField("TAP_0311.DistanceChargeBandCode.DistanceChargeBandCode");    
        //logStdout("Parsed Leaf DistanceChargeBandCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  EarliestCallTimeStamp_opt:                                           
      EarliestCallTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  EarliestCallTimeStamp:                                               
      TAP_0311.EarliestCallTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.EarliestCallTimeStamp", false);   
        //logStdout("Parsed Sequence EarliestCallTimeStamp\n");              
      }                                                                   
      localTimeStamp_EarliestCallTimeStamp     
      utcTimeOffset_EarliestCallTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.EarliestCallTimeStamp");     
        //logStdout("EarliestCallTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_EarliestCallTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_EarliestCallTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  EndMissingSeqNumber_opt:                                                         
      EndMissingSeqNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  EndMissingSeqNumber:                                                             
      RAP_0103.EndMissingSeqNumber                                        
      {                                                                          
        __onField("RAP_0103.EndMissingSeqNumber.EndMissingSeqNumber");    
        //logStdout("Parsed Leaf EndMissingSeqNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  EquipmentId_opt:                                                         
      EquipmentId                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  EquipmentId:                                                             
      TAP_0311.EquipmentId                                        
      {                                                                          
        __onField("TAP_0311.EquipmentId.EquipmentId");    
        //logStdout("Parsed Leaf EquipmentId\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  EquipmentIdType_opt:                                                         
      EquipmentIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  EquipmentIdType:                                                             
      TAP_0311.EquipmentIdType                                        
      {                                                                          
        __onField("TAP_0311.EquipmentIdType.EquipmentIdType");    
        //logStdout("Parsed Leaf EquipmentIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ErrorCode_opt:                                                         
      ErrorCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ErrorCode:                                                             
      RAP_0103.ErrorCode                                        
      {                                                                          
        __onField("RAP_0103.ErrorCode.ErrorCode");    
        //logStdout("Parsed Leaf ErrorCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ErrorContext_opt:                                           
      ErrorContext                                            
    |                                                              
    ;                                                              
                                                                   
  ErrorContext:                                               
      RAP_0103.ErrorContext                                 
      {                                                                   
        __onBlockStart("RAP_0103.ErrorContext", false);   
        //logStdout("Parsed Sequence ErrorContext\n");              
      }                                                                   
      pathItemId_ErrorContext     
      itemOccurrence_ErrorContext     
      itemLevel_ErrorContext     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.ErrorContext");     
        //logStdout("ErrorContext Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  pathItemId_ErrorContext:                                                       
      {                                                                                 
        currBlock = "pathItemId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PathItemId_opt                                                       
    ;                                                                                   
                                                                                        
  itemOccurrence_ErrorContext:                                                       
      {                                                                                 
        currBlock = "itemOccurrence";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ItemOccurrence_opt                                                       
    ;                                                                                   
                                                                                        
  itemLevel_ErrorContext:                                                       
      {                                                                                 
        currBlock = "itemLevel";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ItemLevel_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ErrorContextList_opt:                                                                
      RAP_0103.ErrorContextList                                               
      {                                                                                 
        __onBlockStart("RAP_0103.ErrorContextList", true);                  
        //logStdout("Parsed List ErrorContextList\n");                                
      }                                                                                 
      ErrorContextList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("RAP_0103.ErrorContextList");                          
        //logStdout("ErrorContextList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ErrorContextList:                                                                    
      ErrorContextList                                                                 
      ErrorContext_ErrorContextList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ErrorContext_ErrorContextList:                                                       
      {                                                                                 
        currBlock = "ErrorContext";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorContext                                                           
    ;                                                                                   
                                                                   
  ErrorDetail_opt:                                           
      ErrorDetail                                            
    |                                                              
    ;                                                              
                                                                   
  ErrorDetail:                                               
      RAP_0103.ErrorDetail                                 
      {                                                                   
        __onBlockStart("RAP_0103.ErrorDetail", false);   
        //logStdout("Parsed Sequence ErrorDetail\n");              
      }                                                                   
      errorContext_ErrorDetail     
      itemOffset_ErrorDetail     
      errorCode_ErrorDetail     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.ErrorDetail");     
        //logStdout("ErrorDetail Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  errorContext_ErrorDetail:                                                       
      {                                                                                 
        currBlock = "errorContext";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorContextList_opt                                                       
    ;                                                                                   
                                                                                        
  itemOffset_ErrorDetail:                                                       
      {                                                                                 
        currBlock = "itemOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ItemOffset_opt                                                       
    ;                                                                                   
                                                                                        
  errorCode_ErrorDetail:                                                       
      {                                                                                 
        currBlock = "errorCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  ErrorDetailList_opt:                                                                
      RAP_0103.ErrorDetailList                                               
      {                                                                                 
        __onBlockStart("RAP_0103.ErrorDetailList", true);                  
        //logStdout("Parsed List ErrorDetailList\n");                                
      }                                                                                 
      ErrorDetailList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("RAP_0103.ErrorDetailList");                          
        //logStdout("ErrorDetailList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ErrorDetailList:                                                                    
      ErrorDetailList                                                                 
      ErrorDetail_ErrorDetailList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ErrorDetail_ErrorDetailList:                                                       
      {                                                                                 
        currBlock = "ErrorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetail                                                           
    ;                                                                                   
                                                                                 
  Esn_opt:                                                         
      Esn                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Esn:                                                             
      TAP_0311.Esn                                        
      {                                                                          
        __onField("TAP_0311.Esn.Esn");    
        //logStdout("Parsed Leaf Esn\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ExchangeRate_opt:                                                         
      ExchangeRate                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ExchangeRate:                                                             
      TAP_0311.ExchangeRate                                        
      {                                                                          
        __onField("TAP_0311.ExchangeRate.ExchangeRate");    
        //logStdout("Parsed Leaf ExchangeRate\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ExchangeRateCode_opt:                                                         
      ExchangeRateCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ExchangeRateCode:                                                             
      TAP_0311.ExchangeRateCode                                        
      {                                                                          
        __onField("TAP_0311.ExchangeRateCode.ExchangeRateCode");    
        //logStdout("Parsed Leaf ExchangeRateCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  FatalReturn_opt:                                           
      FatalReturn                                            
    |                                                              
    ;                                                              
                                                                   
  FatalReturn:                                               
      RAP_0103.FatalReturn                                 
      {                                                                   
        __onBlockStart("RAP_0103.FatalReturn", false);   
        //logStdout("Parsed Sequence FatalReturn\n");              
      }                                                                   
      fileSequenceNumber_FatalReturn     
      transferBatchError_FatalReturn     
      notificationError_FatalReturn     
      batchControlError_FatalReturn     
      accountingInfoError_FatalReturn     
      networkInfoError_FatalReturn     
      messageDescriptionError_FatalReturn     
      auditControlInfoError_FatalReturn     
      operatorSpecList_FatalReturn     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.FatalReturn");     
        //logStdout("FatalReturn Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  fileSequenceNumber_FatalReturn:                                                       
      {                                                                                 
        currBlock = "fileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  transferBatchError_FatalReturn:                                                       
      {                                                                                 
        currBlock = "transferBatchError";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransferBatchError_opt                                                       
    ;                                                                                   
                                                                                        
  notificationError_FatalReturn:                                                       
      {                                                                                 
        currBlock = "notificationError";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NotificationError_opt                                                       
    ;                                                                                   
                                                                                        
  batchControlError_FatalReturn:                                                       
      {                                                                                 
        currBlock = "batchControlError";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BatchControlError_opt                                                       
    ;                                                                                   
                                                                                        
  accountingInfoError_FatalReturn:                                                       
      {                                                                                 
        currBlock = "accountingInfoError";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AccountingInfoError_opt                                                       
    ;                                                                                   
                                                                                        
  networkInfoError_FatalReturn:                                                       
      {                                                                                 
        currBlock = "networkInfoError";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkInfoError_opt                                                       
    ;                                                                                   
                                                                                        
  messageDescriptionError_FatalReturn:                                                       
      {                                                                                 
        currBlock = "messageDescriptionError";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageDescriptionError_opt                                                       
    ;                                                                                   
                                                                                        
  auditControlInfoError_FatalReturn:                                                       
      {                                                                                 
        currBlock = "auditControlInfoError";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AuditControlInfoError_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecList_FatalReturn:                                                       
      {                                                                                 
        currBlock = "operatorSpecList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  FileAvailableTimeStamp_opt:                                           
      FileAvailableTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  FileAvailableTimeStamp:                                               
      TAP_0311.FileAvailableTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.FileAvailableTimeStamp", false);   
        //logStdout("Parsed Sequence FileAvailableTimeStamp\n");              
      }                                                                   
      localTimeStamp_FileAvailableTimeStamp     
      utcTimeOffset_FileAvailableTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.FileAvailableTimeStamp");     
        //logStdout("FileAvailableTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_FileAvailableTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_FileAvailableTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  FileCreationTimeStamp_opt:                                           
      FileCreationTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  FileCreationTimeStamp:                                               
      TAP_0311.FileCreationTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.FileCreationTimeStamp", false);   
        //logStdout("Parsed Sequence FileCreationTimeStamp\n");              
      }                                                                   
      localTimeStamp_FileCreationTimeStamp     
      utcTimeOffset_FileCreationTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.FileCreationTimeStamp");     
        //logStdout("FileCreationTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_FileCreationTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_FileCreationTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  FileSequenceNumber_opt:                                                         
      FileSequenceNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  FileSequenceNumber:                                                             
      TAP_0311.FileSequenceNumber                                        
      {                                                                          
        __onField("TAP_0311.FileSequenceNumber.FileSequenceNumber");    
        //logStdout("Parsed Leaf FileSequenceNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  FileTypeIndicator_opt:                                                         
      FileTypeIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  FileTypeIndicator:                                                             
      TAP_0311.FileTypeIndicator                                        
      {                                                                          
        __onField("TAP_0311.FileTypeIndicator.FileTypeIndicator");    
        //logStdout("Parsed Leaf FileTypeIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  FixedDiscountValue_opt:                                                         
      FixedDiscountValue                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  FixedDiscountValue:                                                             
      TAP_0311.FixedDiscountValue                                        
      {                                                                          
        __onField("TAP_0311.FixedDiscountValue.FixedDiscountValue");    
        //logStdout("Parsed Leaf FixedDiscountValue\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Fnur_opt:                                                         
      Fnur                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Fnur:                                                             
      TAP_0311.Fnur                                        
      {                                                                          
        __onField("TAP_0311.Fnur.Fnur");    
        //logStdout("Parsed Leaf Fnur\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  GeographicalLocation_opt:                                           
      GeographicalLocation                                            
    |                                                              
    ;                                                              
                                                                   
  GeographicalLocation:                                               
      TAP_0311.GeographicalLocation                                 
      {                                                                   
        __onBlockStart("TAP_0311.GeographicalLocation", false);   
        //logStdout("Parsed Sequence GeographicalLocation\n");              
      }                                                                   
      servingNetwork_GeographicalLocation     
      servingBid_GeographicalLocation     
      servingLocationDescription_GeographicalLocation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GeographicalLocation");     
        //logStdout("GeographicalLocation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  servingNetwork_GeographicalLocation:                                                       
      {                                                                                 
        currBlock = "servingNetwork";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServingNetwork_opt                                                       
    ;                                                                                   
                                                                                        
  servingBid_GeographicalLocation:                                                       
      {                                                                                 
        currBlock = "servingBid";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServingBid_opt                                                       
    ;                                                                                   
                                                                                        
  servingLocationDescription_GeographicalLocation:                                                       
      {                                                                                 
        currBlock = "servingLocationDescription";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServingLocationDescription_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GprsBasicCallInformation_opt:                                           
      GprsBasicCallInformation                                            
    |                                                              
    ;                                                              
                                                                   
  GprsBasicCallInformation:                                               
      TAP_0311.GprsBasicCallInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.GprsBasicCallInformation", false);   
        //logStdout("Parsed Sequence GprsBasicCallInformation\n");              
      }                                                                   
      gprsChargeableSubscriber_GprsBasicCallInformation     
      rapFileSequenceNumber_GprsBasicCallInformation     
      gprsDestination_GprsBasicCallInformation     
      callEventStartTimeStamp_GprsBasicCallInformation     
      totalCallEventDuration_GprsBasicCallInformation     
      causeForTerm_GprsBasicCallInformation     
      partialTypeIndicator_GprsBasicCallInformation     
      pDPContextStartTimestamp_GprsBasicCallInformation     
      networkInitPDPContext_GprsBasicCallInformation     
      chargingId_GprsBasicCallInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GprsBasicCallInformation");     
        //logStdout("GprsBasicCallInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  gprsChargeableSubscriber_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "gprsChargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsChargeableSubscriber_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  gprsDestination_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "gprsDestination";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsDestination_opt                                                       
    ;                                                                                   
                                                                                        
  callEventStartTimeStamp_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "callEventStartTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventStartTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  totalCallEventDuration_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "totalCallEventDuration";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalCallEventDuration_opt                                                       
    ;                                                                                   
                                                                                        
  causeForTerm_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "causeForTerm";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CauseForTerm_opt                                                       
    ;                                                                                   
                                                                                        
  partialTypeIndicator_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "partialTypeIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PartialTypeIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  pDPContextStartTimestamp_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "pDPContextStartTimestamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PDPContextStartTimestamp_opt                                                       
    ;                                                                                   
                                                                                        
  networkInitPDPContext_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "networkInitPDPContext";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkInitPDPContext_opt                                                       
    ;                                                                                   
                                                                                        
  chargingId_GprsBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "chargingId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargingId_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GprsCall_opt:                                           
      GprsCall                                            
    |                                                              
    ;                                                              
                                                                   
  GprsCall:                                               
      TAP_0311.GprsCall                                 
      {                                                                   
        __onBlockStart("TAP_0311.GprsCall", false);   
        //logStdout("Parsed Sequence GprsCall\n");              
      }                                                                   
      gprsBasicCallInformation_GprsCall     
      gprsLocationInformation_GprsCall     
      equipmentIdentifier_GprsCall     
      gprsServiceUsed_GprsCall     
      camelServiceUsed_GprsCall     
      operatorSpecInformation_GprsCall     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GprsCall");     
        //logStdout("GprsCall Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  gprsBasicCallInformation_GprsCall:                                                       
      {                                                                                 
        currBlock = "gprsBasicCallInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsBasicCallInformation_opt                                                       
    ;                                                                                   
                                                                                        
  gprsLocationInformation_GprsCall:                                                       
      {                                                                                 
        currBlock = "gprsLocationInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsLocationInformation_opt                                                       
    ;                                                                                   
                                                                                        
  equipmentIdentifier_GprsCall:                                                       
      {                                                                                 
        currBlock = "equipmentIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ImeiOrEsn_opt                                                       
    ;                                                                                   
                                                                                        
  gprsServiceUsed_GprsCall:                                                       
      {                                                                                 
        currBlock = "gprsServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsServiceUsed_opt                                                       
    ;                                                                                   
                                                                                        
  camelServiceUsed_GprsCall:                                                       
      {                                                                                 
        currBlock = "camelServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CamelServiceUsed_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_GprsCall:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GprsChargeableSubscriber_opt:                                           
      GprsChargeableSubscriber                                            
    |                                                              
    ;                                                              
                                                                   
  GprsChargeableSubscriber:                                               
      TAP_0311.GprsChargeableSubscriber                                 
      {                                                                   
        __onBlockStart("TAP_0311.GprsChargeableSubscriber", false);   
        //logStdout("Parsed Sequence GprsChargeableSubscriber\n");              
      }                                                                   
      chargeableSubscriber_GprsChargeableSubscriber     
      pdpAddress_GprsChargeableSubscriber     
      networkAccessIdentifier_GprsChargeableSubscriber     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GprsChargeableSubscriber");     
        //logStdout("GprsChargeableSubscriber Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargeableSubscriber_GprsChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "chargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeableSubscriber_opt                                                       
    ;                                                                                   
                                                                                        
  pdpAddress_GprsChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "pdpAddress";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PdpAddress_opt                                                       
    ;                                                                                   
                                                                                        
  networkAccessIdentifier_GprsChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "networkAccessIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkAccessIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GprsDestination_opt:                                           
      GprsDestination                                            
    |                                                              
    ;                                                              
                                                                   
  GprsDestination:                                               
      TAP_0311.GprsDestination                                 
      {                                                                   
        __onBlockStart("TAP_0311.GprsDestination", false);   
        //logStdout("Parsed Sequence GprsDestination\n");              
      }                                                                   
      accessPointNameNI_GprsDestination     
      accessPointNameOI_GprsDestination     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GprsDestination");     
        //logStdout("GprsDestination Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  accessPointNameNI_GprsDestination:                                                       
      {                                                                                 
        currBlock = "accessPointNameNI";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AccessPointNameNI_opt                                                       
    ;                                                                                   
                                                                                        
  accessPointNameOI_GprsDestination:                                                       
      {                                                                                 
        currBlock = "accessPointNameOI";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AccessPointNameOI_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GprsLocationInformation_opt:                                           
      GprsLocationInformation                                            
    |                                                              
    ;                                                              
                                                                   
  GprsLocationInformation:                                               
      TAP_0311.GprsLocationInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.GprsLocationInformation", false);   
        //logStdout("Parsed Sequence GprsLocationInformation\n");              
      }                                                                   
      gprsNetworkLocation_GprsLocationInformation     
      homeLocationInformation_GprsLocationInformation     
      geographicalLocation_GprsLocationInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GprsLocationInformation");     
        //logStdout("GprsLocationInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  gprsNetworkLocation_GprsLocationInformation:                                                       
      {                                                                                 
        currBlock = "gprsNetworkLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsNetworkLocation_opt                                                       
    ;                                                                                   
                                                                                        
  homeLocationInformation_GprsLocationInformation:                                                       
      {                                                                                 
        currBlock = "homeLocationInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeLocationInformation_opt                                                       
    ;                                                                                   
                                                                                        
  geographicalLocation_GprsLocationInformation:                                                       
      {                                                                                 
        currBlock = "geographicalLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GeographicalLocation_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GprsNetworkLocation_opt:                                           
      GprsNetworkLocation                                            
    |                                                              
    ;                                                              
                                                                   
  GprsNetworkLocation:                                               
      TAP_0311.GprsNetworkLocation                                 
      {                                                                   
        __onBlockStart("TAP_0311.GprsNetworkLocation", false);   
        //logStdout("Parsed Sequence GprsNetworkLocation\n");              
      }                                                                   
      recEntity_GprsNetworkLocation     
      locationArea_GprsNetworkLocation     
      cellId_GprsNetworkLocation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GprsNetworkLocation");     
        //logStdout("GprsNetworkLocation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  recEntity_GprsNetworkLocation:                                                       
      {                                                                                 
        currBlock = "recEntity";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityCodeList_opt                                                       
    ;                                                                                   
                                                                                        
  locationArea_GprsNetworkLocation:                                                       
      {                                                                                 
        currBlock = "locationArea";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationArea_opt                                                       
    ;                                                                                   
                                                                                        
  cellId_GprsNetworkLocation:                                                       
      {                                                                                 
        currBlock = "cellId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CellId_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GprsServiceUsed_opt:                                           
      GprsServiceUsed                                            
    |                                                              
    ;                                                              
                                                                   
  GprsServiceUsed:                                               
      TAP_0311.GprsServiceUsed                                 
      {                                                                   
        __onBlockStart("TAP_0311.GprsServiceUsed", false);   
        //logStdout("Parsed Sequence GprsServiceUsed\n");              
      }                                                                   
      iMSSignallingContext_GprsServiceUsed     
      dataVolumeIncoming_GprsServiceUsed     
      dataVolumeOutgoing_GprsServiceUsed     
      chargeInformationList_GprsServiceUsed     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GprsServiceUsed");     
        //logStdout("GprsServiceUsed Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  iMSSignallingContext_GprsServiceUsed:                                                       
      {                                                                                 
        currBlock = "iMSSignallingContext";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      IMSSignallingContext_opt                                                       
    ;                                                                                   
                                                                                        
  dataVolumeIncoming_GprsServiceUsed:                                                       
      {                                                                                 
        currBlock = "dataVolumeIncoming";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DataVolumeIncoming_opt                                                       
    ;                                                                                   
                                                                                        
  dataVolumeOutgoing_GprsServiceUsed:                                                       
      {                                                                                 
        currBlock = "dataVolumeOutgoing";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DataVolumeOutgoing_opt                                                       
    ;                                                                                   
                                                                                        
  chargeInformationList_GprsServiceUsed:                                                       
      {                                                                                 
        currBlock = "chargeInformationList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeInformationList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  GsmChargeableSubscriber_opt:                                           
      GsmChargeableSubscriber                                            
    |                                                              
    ;                                                              
                                                                   
  GsmChargeableSubscriber:                                               
      TAP_0311.GsmChargeableSubscriber                                 
      {                                                                   
        __onBlockStart("TAP_0311.GsmChargeableSubscriber", false);   
        //logStdout("Parsed Sequence GsmChargeableSubscriber\n");              
      }                                                                   
      imsi_GsmChargeableSubscriber     
      msisdn_GsmChargeableSubscriber     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.GsmChargeableSubscriber");     
        //logStdout("GsmChargeableSubscriber Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  imsi_GsmChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "imsi";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imsi_opt                                                       
    ;                                                                                   
                                                                                        
  msisdn_GsmChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "msisdn";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Msisdn_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  GuaranteedBitRate_opt:                                                         
      GuaranteedBitRate                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  GuaranteedBitRate:                                                             
      TAP_0311.GuaranteedBitRate                                        
      {                                                                          
        __onField("TAP_0311.GuaranteedBitRate.GuaranteedBitRate");    
        //logStdout("Parsed Leaf GuaranteedBitRate\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  HSCSDIndicator_opt:                                                         
      HSCSDIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HSCSDIndicator:                                                             
      TAP_0311.HSCSDIndicator                                        
      {                                                                          
        __onField("TAP_0311.HSCSDIndicator.HSCSDIndicator");    
        //logStdout("Parsed Leaf HSCSDIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  HexString_opt:                                                         
      HexString                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HexString:                                                             
      TAP_0311.HexString                                        
      {                                                                          
        __onField("TAP_0311.HexString.HexString");    
        //logStdout("Parsed Leaf HexString\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  HomeBid_opt:                                                         
      HomeBid                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HomeBid:                                                             
      TAP_0311.HomeBid                                        
      {                                                                          
        __onField("TAP_0311.HomeBid.HomeBid");    
        //logStdout("Parsed Leaf HomeBid\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  HomeIdType_opt:                                                         
      HomeIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HomeIdType:                                                             
      TAP_0311.HomeIdType                                        
      {                                                                          
        __onField("TAP_0311.HomeIdType.HomeIdType");    
        //logStdout("Parsed Leaf HomeIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  HomeIdentifier_opt:                                                         
      HomeIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HomeIdentifier:                                                             
      TAP_0311.HomeIdentifier                                        
      {                                                                          
        __onField("TAP_0311.HomeIdentifier.HomeIdentifier");    
        //logStdout("Parsed Leaf HomeIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  HomeLocationDescription_opt:                                                         
      HomeLocationDescription                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HomeLocationDescription:                                                             
      TAP_0311.HomeLocationDescription                                        
      {                                                                          
        __onField("TAP_0311.HomeLocationDescription.HomeLocationDescription");    
        //logStdout("Parsed Leaf HomeLocationDescription\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  HomeLocationInformation_opt:                                           
      HomeLocationInformation                                            
    |                                                              
    ;                                                              
                                                                   
  HomeLocationInformation:                                               
      TAP_0311.HomeLocationInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.HomeLocationInformation", false);   
        //logStdout("Parsed Sequence HomeLocationInformation\n");              
      }                                                                   
      homeBid_HomeLocationInformation     
      homeLocationDescription_HomeLocationInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.HomeLocationInformation");     
        //logStdout("HomeLocationInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  homeBid_HomeLocationInformation:                                                       
      {                                                                                 
        currBlock = "homeBid";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeBid_opt                                                       
    ;                                                                                   
                                                                                        
  homeLocationDescription_HomeLocationInformation:                                                       
      {                                                                                 
        currBlock = "homeLocationDescription";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeLocationDescription_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  HorizontalAccuracyDelivered_opt:                                                         
      HorizontalAccuracyDelivered                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HorizontalAccuracyDelivered:                                                             
      TAP_0311.HorizontalAccuracyDelivered                                        
      {                                                                          
        __onField("TAP_0311.HorizontalAccuracyDelivered.HorizontalAccuracyDelivered");    
        //logStdout("Parsed Leaf HorizontalAccuracyDelivered\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  HorizontalAccuracyRequested_opt:                                                         
      HorizontalAccuracyRequested                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HorizontalAccuracyRequested:                                                             
      TAP_0311.HorizontalAccuracyRequested                                        
      {                                                                          
        __onField("TAP_0311.HorizontalAccuracyRequested.HorizontalAccuracyRequested");    
        //logStdout("Parsed Leaf HorizontalAccuracyRequested\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  IMSSignallingContext_opt:                                                         
      IMSSignallingContext                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  IMSSignallingContext:                                                             
      TAP_0311.IMSSignallingContext                                        
      {                                                                          
        __onField("TAP_0311.IMSSignallingContext.IMSSignallingContext");    
        //logStdout("Parsed Leaf IMSSignallingContext\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                        
  ISPList_opt:                                                                
      TAP_0311.ISPList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.ISPList", true);                  
        //logStdout("Parsed List ISPList\n");                                
      }                                                                                 
      ISPList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.ISPList");                          
        //logStdout("ISPList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ISPList:                                                                    
      ISPList                                                                 
      InternetServiceProvider_ISPList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  InternetServiceProvider_ISPList:                                                       
      {                                                                                 
        currBlock = "InternetServiceProvider";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      InternetServiceProvider                                                           
    ;                                                                                   
                                                                                 
  Imei_opt:                                                         
      Imei                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Imei:                                                             
      TAP_0311.Imei                                        
      {                                                                          
        __onField("TAP_0311.Imei.Imei");    
        //logStdout("Parsed Leaf Imei\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                
  ImeiOrEsn_opt:                                        
      ImeiOrEsn                                         
    |                                                           
    ;                                                           
                                                                
  ImeiOrEsn:                                                       
      TAP_0311.ImeiOrEsn                                  
      {                                                                    
        __onBlockStart("TAP_0311.ImeiOrEsn", false);    
        //logStdout("Parsed Choice ImeiOrEsn\n");                 
      }                                                         
      ImeiOrEsn_elems                                   
      ASN1.BlockEnd                                                
      {                                                         
        __onBlockEnd("TAP_0311.ImeiOrEsn");  
        //logStdout("ImeiOrEsn Choice END.\n");        
      }                                                         
    ;                                                           
                                                                
  ImeiOrEsn_elems:                                      
      imei_ImeiOrEsn     
    | esn_ImeiOrEsn     
    ;                                                           
                                                                
  imei_ImeiOrEsn:                                                       
      {                                                                                 
        currBlock = "imei";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imei                                                           
    ;                                                                                   
                                                                                        
  esn_ImeiOrEsn:                                                       
      {                                                                                 
        currBlock = "esn";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Esn                                                           
    ;                                                                                   
                                                                                        
                                                                                 
  Imsi_opt:                                                         
      Imsi                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Imsi:                                                             
      TAP_0311.Imsi                                        
      {                                                                          
        __onField("TAP_0311.Imsi.Imsi");    
        //logStdout("Parsed Leaf Imsi\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  InternetServiceProvider_opt:                                           
      InternetServiceProvider                                            
    |                                                              
    ;                                                              
                                                                   
  InternetServiceProvider:                                               
      TAP_0311.InternetServiceProvider                                 
      {                                                                   
        __onBlockStart("TAP_0311.InternetServiceProvider", false);   
        //logStdout("Parsed Sequence InternetServiceProvider\n");              
      }                                                                   
      ispIdType_InternetServiceProvider     
      ispIdentifier_InternetServiceProvider     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.InternetServiceProvider");     
        //logStdout("InternetServiceProvider Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  ispIdType_InternetServiceProvider:                                                       
      {                                                                                 
        currBlock = "ispIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      IspIdType_opt                                                       
    ;                                                                                   
                                                                                        
  ispIdentifier_InternetServiceProvider:                                                       
      {                                                                                 
        currBlock = "ispIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      IspIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  InternetServiceProviderIdList_opt:                                                                
      TAP_0311.InternetServiceProviderIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.InternetServiceProviderIdList", true);                  
        //logStdout("Parsed List InternetServiceProviderIdList\n");                                
      }                                                                                 
      InternetServiceProviderIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.InternetServiceProviderIdList");                          
        //logStdout("InternetServiceProviderIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  InternetServiceProviderIdList:                                                                    
      InternetServiceProviderIdList                                                                 
      InternetServiceProvider_InternetServiceProviderIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  InternetServiceProvider_InternetServiceProviderIdList:                                                       
      {                                                                                 
        currBlock = "InternetServiceProvider";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      InternetServiceProvider                                                           
    ;                                                                                   
                                                                                 
  IspIdType_opt:                                                         
      IspIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  IspIdType:                                                             
      TAP_0311.IspIdType                                        
      {                                                                          
        __onField("TAP_0311.IspIdType.IspIdType");    
        //logStdout("Parsed Leaf IspIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  IspIdentifier_opt:                                                         
      IspIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  IspIdentifier:                                                             
      TAP_0311.IspIdentifier                                        
      {                                                                          
        __onField("TAP_0311.IspIdentifier.IspIdentifier");    
        //logStdout("Parsed Leaf IspIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ItemLevel_opt:                                                         
      ItemLevel                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ItemLevel:                                                             
      RAP_0103.ItemLevel                                        
      {                                                                          
        __onField("RAP_0103.ItemLevel.ItemLevel");    
        //logStdout("Parsed Leaf ItemLevel\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ItemOccurrence_opt:                                                         
      ItemOccurrence                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ItemOccurrence:                                                             
      RAP_0103.ItemOccurrence                                        
      {                                                                          
        __onField("RAP_0103.ItemOccurrence.ItemOccurrence");    
        //logStdout("Parsed Leaf ItemOccurrence\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ItemOffset_opt:                                                         
      ItemOffset                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ItemOffset:                                                             
      RAP_0103.ItemOffset                                        
      {                                                                          
        __onField("RAP_0103.ItemOffset.ItemOffset");    
        //logStdout("Parsed Leaf ItemOffset\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  LCSQosDelivered_opt:                                           
      LCSQosDelivered                                            
    |                                                              
    ;                                                              
                                                                   
  LCSQosDelivered:                                               
      TAP_0311.LCSQosDelivered                                 
      {                                                                   
        __onBlockStart("TAP_0311.LCSQosDelivered", false);   
        //logStdout("Parsed Sequence LCSQosDelivered\n");              
      }                                                                   
      lCSTransactionStatus_LCSQosDelivered     
      horizontalAccuracyDelivered_LCSQosDelivered     
      verticalAccuracyDelivered_LCSQosDelivered     
      responseTime_LCSQosDelivered     
      positioningMethod_LCSQosDelivered     
      trackingPeriod_LCSQosDelivered     
      trackingFrequency_LCSQosDelivered     
      ageOfLocation_LCSQosDelivered     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LCSQosDelivered");     
        //logStdout("LCSQosDelivered Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  lCSTransactionStatus_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "lCSTransactionStatus";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LCSTransactionStatus_opt                                                       
    ;                                                                                   
                                                                                        
  horizontalAccuracyDelivered_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "horizontalAccuracyDelivered";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HorizontalAccuracyDelivered_opt                                                       
    ;                                                                                   
                                                                                        
  verticalAccuracyDelivered_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "verticalAccuracyDelivered";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      VerticalAccuracyDelivered_opt                                                       
    ;                                                                                   
                                                                                        
  responseTime_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "responseTime";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ResponseTime_opt                                                       
    ;                                                                                   
                                                                                        
  positioningMethod_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "positioningMethod";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PositioningMethod_opt                                                       
    ;                                                                                   
                                                                                        
  trackingPeriod_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "trackingPeriod";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingPeriod_opt                                                       
    ;                                                                                   
                                                                                        
  trackingFrequency_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "trackingFrequency";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingFrequency_opt                                                       
    ;                                                                                   
                                                                                        
  ageOfLocation_LCSQosDelivered:                                                       
      {                                                                                 
        currBlock = "ageOfLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AgeOfLocation_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  LCSQosRequested_opt:                                           
      LCSQosRequested                                            
    |                                                              
    ;                                                              
                                                                   
  LCSQosRequested:                                               
      TAP_0311.LCSQosRequested                                 
      {                                                                   
        __onBlockStart("TAP_0311.LCSQosRequested", false);   
        //logStdout("Parsed Sequence LCSQosRequested\n");              
      }                                                                   
      lCSRequestTimestamp_LCSQosRequested     
      horizontalAccuracyRequested_LCSQosRequested     
      verticalAccuracyRequested_LCSQosRequested     
      responseTimeCategory_LCSQosRequested     
      trackingPeriod_LCSQosRequested     
      trackingFrequency_LCSQosRequested     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LCSQosRequested");     
        //logStdout("LCSQosRequested Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  lCSRequestTimestamp_LCSQosRequested:                                                       
      {                                                                                 
        currBlock = "lCSRequestTimestamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LCSRequestTimestamp_opt                                                       
    ;                                                                                   
                                                                                        
  horizontalAccuracyRequested_LCSQosRequested:                                                       
      {                                                                                 
        currBlock = "horizontalAccuracyRequested";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HorizontalAccuracyRequested_opt                                                       
    ;                                                                                   
                                                                                        
  verticalAccuracyRequested_LCSQosRequested:                                                       
      {                                                                                 
        currBlock = "verticalAccuracyRequested";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      VerticalAccuracyRequested_opt                                                       
    ;                                                                                   
                                                                                        
  responseTimeCategory_LCSQosRequested:                                                       
      {                                                                                 
        currBlock = "responseTimeCategory";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ResponseTimeCategory_opt                                                       
    ;                                                                                   
                                                                                        
  trackingPeriod_LCSQosRequested:                                                       
      {                                                                                 
        currBlock = "trackingPeriod";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingPeriod_opt                                                       
    ;                                                                                   
                                                                                        
  trackingFrequency_LCSQosRequested:                                                       
      {                                                                                 
        currBlock = "trackingFrequency";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingFrequency_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  LCSRequestTimestamp_opt:                                           
      LCSRequestTimestamp                                            
    |                                                              
    ;                                                              
                                                                   
  LCSRequestTimestamp:                                               
      TAP_0311.LCSRequestTimestamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.LCSRequestTimestamp", false);   
        //logStdout("Parsed Sequence LCSRequestTimestamp\n");              
      }                                                                   
      localTimeStamp_LCSRequestTimestamp     
      utcTimeOffsetCode_LCSRequestTimestamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LCSRequestTimestamp");     
        //logStdout("LCSRequestTimestamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_LCSRequestTimestamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_LCSRequestTimestamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  LCSSPIdentification_opt:                                           
      LCSSPIdentification                                            
    |                                                              
    ;                                                              
                                                                   
  LCSSPIdentification:                                               
      TAP_0311.LCSSPIdentification                                 
      {                                                                   
        __onBlockStart("TAP_0311.LCSSPIdentification", false);   
        //logStdout("Parsed Sequence LCSSPIdentification\n");              
      }                                                                   
      contentProviderIdType_LCSSPIdentification     
      contentProviderIdentifier_LCSSPIdentification     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LCSSPIdentification");     
        //logStdout("LCSSPIdentification Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  contentProviderIdType_LCSSPIdentification:                                                       
      {                                                                                 
        currBlock = "contentProviderIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentProviderIdType_opt                                                       
    ;                                                                                   
                                                                                        
  contentProviderIdentifier_LCSSPIdentification:                                                       
      {                                                                                 
        currBlock = "contentProviderIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentProviderIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  LCSSPIdentificationList_opt:                                                                
      TAP_0311.LCSSPIdentificationList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.LCSSPIdentificationList", true);                  
        //logStdout("Parsed List LCSSPIdentificationList\n");                                
      }                                                                                 
      LCSSPIdentificationList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.LCSSPIdentificationList");                          
        //logStdout("LCSSPIdentificationList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  LCSSPIdentificationList:                                                                    
      LCSSPIdentificationList                                                                 
      LCSSPIdentification_LCSSPIdentificationList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  LCSSPIdentification_LCSSPIdentificationList:                                                       
      {                                                                                 
        currBlock = "LCSSPIdentification";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LCSSPIdentification                                                           
    ;                                                                                   
                                                                   
  LCSSPInformation_opt:                                           
      LCSSPInformation                                            
    |                                                              
    ;                                                              
                                                                   
  LCSSPInformation:                                               
      TAP_0311.LCSSPInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.LCSSPInformation", false);   
        //logStdout("Parsed Sequence LCSSPInformation\n");              
      }                                                                   
      lCSSPIdentificationList_LCSSPInformation     
      iSPList_LCSSPInformation     
      networkList_LCSSPInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LCSSPInformation");     
        //logStdout("LCSSPInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  lCSSPIdentificationList_LCSSPInformation:                                                       
      {                                                                                 
        currBlock = "lCSSPIdentificationList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LCSSPIdentificationList_opt                                                       
    ;                                                                                   
                                                                                        
  iSPList_LCSSPInformation:                                                       
      {                                                                                 
        currBlock = "iSPList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ISPList_opt                                                       
    ;                                                                                   
                                                                                        
  networkList_LCSSPInformation:                                                       
      {                                                                                 
        currBlock = "networkList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  LCSTransactionStatus_opt:                                                         
      LCSTransactionStatus                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  LCSTransactionStatus:                                                             
      TAP_0311.LCSTransactionStatus                                        
      {                                                                          
        __onField("TAP_0311.LCSTransactionStatus.LCSTransactionStatus");    
        //logStdout("Parsed Leaf LCSTransactionStatus\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  LatestCallTimeStamp_opt:                                           
      LatestCallTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  LatestCallTimeStamp:                                               
      TAP_0311.LatestCallTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.LatestCallTimeStamp", false);   
        //logStdout("Parsed Sequence LatestCallTimeStamp\n");              
      }                                                                   
      localTimeStamp_LatestCallTimeStamp     
      utcTimeOffset_LatestCallTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LatestCallTimeStamp");     
        //logStdout("LatestCallTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_LatestCallTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_LatestCallTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  LocalCurrency_opt:                                                         
      LocalCurrency                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  LocalCurrency:                                                             
      TAP_0311.LocalCurrency                                        
      {                                                                          
        __onField("TAP_0311.LocalCurrency.LocalCurrency");    
        //logStdout("Parsed Leaf LocalCurrency\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  LocalTimeStamp_opt:                                                         
      LocalTimeStamp                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  LocalTimeStamp:                                                             
      TAP_0311.LocalTimeStamp                                        
      {                                                                          
        __onField("TAP_0311.LocalTimeStamp.LocalTimeStamp");    
        //logStdout("Parsed Leaf LocalTimeStamp\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  LocationArea_opt:                                                         
      LocationArea                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  LocationArea:                                                             
      TAP_0311.LocationArea                                        
      {                                                                          
        __onField("TAP_0311.LocationArea.LocationArea");    
        //logStdout("Parsed Leaf LocationArea\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
  LocationDescription_opt:         
      LocationDescription          
    |                            
    ;                            
                                 
  LocationDescription:             
      AsciiString               
    ;                            
                                                                                 
  LocationIdType_opt:                                                         
      LocationIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  LocationIdType:                                                             
      TAP_0311.LocationIdType                                        
      {                                                                          
        __onField("TAP_0311.LocationIdType.LocationIdType");    
        //logStdout("Parsed Leaf LocationIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  LocationIdentifier_opt:                                                         
      LocationIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  LocationIdentifier:                                                             
      TAP_0311.LocationIdentifier                                        
      {                                                                          
        __onField("TAP_0311.LocationIdentifier.LocationIdentifier");    
        //logStdout("Parsed Leaf LocationIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  LocationInformation_opt:                                           
      LocationInformation                                            
    |                                                              
    ;                                                              
                                                                   
  LocationInformation:                                               
      TAP_0311.LocationInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.LocationInformation", false);   
        //logStdout("Parsed Sequence LocationInformation\n");              
      }                                                                   
      networkLocation_LocationInformation     
      homeLocationInformation_LocationInformation     
      geographicalLocation_LocationInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LocationInformation");     
        //logStdout("LocationInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  networkLocation_LocationInformation:                                                       
      {                                                                                 
        currBlock = "networkLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkLocation_opt                                                       
    ;                                                                                   
                                                                                        
  homeLocationInformation_LocationInformation:                                                       
      {                                                                                 
        currBlock = "homeLocationInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeLocationInformation_opt                                                       
    ;                                                                                   
                                                                                        
  geographicalLocation_LocationInformation:                                                       
      {                                                                                 
        currBlock = "geographicalLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GeographicalLocation_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  LocationService_opt:                                           
      LocationService                                            
    |                                                              
    ;                                                              
                                                                   
  LocationService:                                               
      TAP_0311.LocationService                                 
      {                                                                   
        __onBlockStart("TAP_0311.LocationService", false);   
        //logStdout("Parsed Sequence LocationService\n");              
      }                                                                   
      rapFileSequenceNumber_LocationService     
      recEntityCode_LocationService     
      callReference_LocationService     
      trackingCustomerInformation_LocationService     
      lCSSPInformation_LocationService     
      trackedCustomerInformation_LocationService     
      locationServiceUsage_LocationService     
      operatorSpecInformation_LocationService     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LocationService");     
        //logStdout("LocationService Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  rapFileSequenceNumber_LocationService:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  recEntityCode_LocationService:                                                       
      {                                                                                 
        currBlock = "recEntityCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityCode_opt                                                       
    ;                                                                                   
                                                                                        
  callReference_LocationService:                                                       
      {                                                                                 
        currBlock = "callReference";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallReference_opt                                                       
    ;                                                                                   
                                                                                        
  trackingCustomerInformation_LocationService:                                                       
      {                                                                                 
        currBlock = "trackingCustomerInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerInformation_opt                                                       
    ;                                                                                   
                                                                                        
  lCSSPInformation_LocationService:                                                       
      {                                                                                 
        currBlock = "lCSSPInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LCSSPInformation_opt                                                       
    ;                                                                                   
                                                                                        
  trackedCustomerInformation_LocationService:                                                       
      {                                                                                 
        currBlock = "trackedCustomerInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerInformation_opt                                                       
    ;                                                                                   
                                                                                        
  locationServiceUsage_LocationService:                                                       
      {                                                                                 
        currBlock = "locationServiceUsage";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationServiceUsage_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_LocationService:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  LocationServiceUsage_opt:                                           
      LocationServiceUsage                                            
    |                                                              
    ;                                                              
                                                                   
  LocationServiceUsage:                                               
      TAP_0311.LocationServiceUsage                                 
      {                                                                   
        __onBlockStart("TAP_0311.LocationServiceUsage", false);   
        //logStdout("Parsed Sequence LocationServiceUsage\n");              
      }                                                                   
      lCSQosRequested_LocationServiceUsage     
      lCSQosDelivered_LocationServiceUsage     
      chargingTimeStamp_LocationServiceUsage     
      chargeInformationList_LocationServiceUsage     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.LocationServiceUsage");     
        //logStdout("LocationServiceUsage Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  lCSQosRequested_LocationServiceUsage:                                                       
      {                                                                                 
        currBlock = "lCSQosRequested";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LCSQosRequested_opt                                                       
    ;                                                                                   
                                                                                        
  lCSQosDelivered_LocationServiceUsage:                                                       
      {                                                                                 
        currBlock = "lCSQosDelivered";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LCSQosDelivered_opt                                                       
    ;                                                                                   
                                                                                        
  chargingTimeStamp_LocationServiceUsage:                                                       
      {                                                                                 
        currBlock = "chargingTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargingTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  chargeInformationList_LocationServiceUsage:                                                       
      {                                                                                 
        currBlock = "chargeInformationList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeInformationList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  MaximumBitRate_opt:                                                         
      MaximumBitRate                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  MaximumBitRate:                                                             
      TAP_0311.MaximumBitRate                                        
      {                                                                          
        __onField("TAP_0311.MaximumBitRate.MaximumBitRate");    
        //logStdout("Parsed Leaf MaximumBitRate\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Mdn_opt:                                                         
      Mdn                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Mdn:                                                             
      TAP_0311.Mdn                                        
      {                                                                          
        __onField("TAP_0311.Mdn.Mdn");    
        //logStdout("Parsed Leaf Mdn\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  MessageDescription_opt:                                                         
      MessageDescription                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  MessageDescription:                                                             
      TAP_0311.MessageDescription                                        
      {                                                                          
        __onField("TAP_0311.MessageDescription.MessageDescription");    
        //logStdout("Parsed Leaf MessageDescription\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  MessageDescriptionCode_opt:                                                         
      MessageDescriptionCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  MessageDescriptionCode:                                                             
      TAP_0311.MessageDescriptionCode                                        
      {                                                                          
        __onField("TAP_0311.MessageDescriptionCode.MessageDescriptionCode");    
        //logStdout("Parsed Leaf MessageDescriptionCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  MessageDescriptionError_opt:                                           
      MessageDescriptionError                                            
    |                                                              
    ;                                                              
                                                                   
  MessageDescriptionError:                                               
      RAP_0103.MessageDescriptionError                                 
      {                                                                   
        __onBlockStart("RAP_0103.MessageDescriptionError", false);   
        //logStdout("Parsed Sequence MessageDescriptionError\n");              
      }                                                                   
      messageDescriptionInfo_MessageDescriptionError     
      errorDetail_MessageDescriptionError     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.MessageDescriptionError");     
        //logStdout("MessageDescriptionError Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  messageDescriptionInfo_MessageDescriptionError:                                                       
      {                                                                                 
        currBlock = "messageDescriptionInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageDescriptionInfoList_opt                                                       
    ;                                                                                   
                                                                                        
  errorDetail_MessageDescriptionError:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  MessageDescriptionInfoList_opt:                                                                
      RAP_0103.MessageDescriptionInfoList                                               
      {                                                                                 
        __onBlockStart("RAP_0103.MessageDescriptionInfoList", true);                  
        //logStdout("Parsed List MessageDescriptionInfoList\n");                                
      }                                                                                 
      MessageDescriptionInfoList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("RAP_0103.MessageDescriptionInfoList");                          
        //logStdout("MessageDescriptionInfoList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  MessageDescriptionInfoList:                                                                    
      MessageDescriptionInfoList                                                                 
      MessageDescriptionInformationDefinition_MessageDescriptionInfoList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  MessageDescriptionInformationDefinition_MessageDescriptionInfoList:                                                       
      {                                                                                 
        currBlock = "MessageDescriptionInformationDefinition";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageDescriptionInformationDefinition                                                           
    ;                                                                                   
                                                                   
  MessageDescriptionInformationDefinition_opt:                                           
      MessageDescriptionInformationDefinition                                            
    |                                                              
    ;                                                              
                                                                   
  MessageDescriptionInformationDefinition:                                               
      RAP_0103.MessageDescriptionInformationDefinition                                 
      {                                                                   
        __onBlockStart("RAP_0103.MessageDescriptionInformationDefinition", false);   
        //logStdout("Parsed Sequence MessageDescriptionInformationDefinition\n");              
      }                                                                   
      messageDescriptionCode_MessageDescriptionInformationDefinition     
      messageDescription_MessageDescriptionInformationDefinition     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.MessageDescriptionInformationDefinition");     
        //logStdout("MessageDescriptionInformationDefinition Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  messageDescriptionCode_MessageDescriptionInformationDefinition:                                                       
      {                                                                                 
        currBlock = "messageDescriptionCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageDescriptionCode_opt                                                       
    ;                                                                                   
                                                                                        
  messageDescription_MessageDescriptionInformationDefinition:                                                       
      {                                                                                 
        currBlock = "messageDescription";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageDescription_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  MessageStatus_opt:                                                         
      MessageStatus                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  MessageStatus:                                                             
      TAP_0311.MessageStatus                                        
      {                                                                          
        __onField("TAP_0311.MessageStatus.MessageStatus");    
        //logStdout("Parsed Leaf MessageStatus\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  MessageType_opt:                                                         
      MessageType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  MessageType:                                                             
      TAP_0311.MessageType                                        
      {                                                                          
        __onField("TAP_0311.MessageType.MessageType");    
        //logStdout("Parsed Leaf MessageType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Min_opt:                                                         
      Min                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Min:                                                             
      TAP_0311.Min                                        
      {                                                                          
        __onField("TAP_0311.Min.Min");    
        //logStdout("Parsed Leaf Min\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  MinChargeableSubscriber_opt:                                           
      MinChargeableSubscriber                                            
    |                                                              
    ;                                                              
                                                                   
  MinChargeableSubscriber:                                               
      TAP_0311.MinChargeableSubscriber                                 
      {                                                                   
        __onBlockStart("TAP_0311.MinChargeableSubscriber", false);   
        //logStdout("Parsed Sequence MinChargeableSubscriber\n");              
      }                                                                   
      min_MinChargeableSubscriber     
      mdn_MinChargeableSubscriber     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.MinChargeableSubscriber");     
        //logStdout("MinChargeableSubscriber Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  min_MinChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "min";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Min_opt                                                       
    ;                                                                                   
                                                                                        
  mdn_MinChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "mdn";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Mdn_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  MissingReturn_opt:                                           
      MissingReturn                                            
    |                                                              
    ;                                                              
                                                                   
  MissingReturn:                                               
      RAP_0103.MissingReturn                                 
      {                                                                   
        __onBlockStart("RAP_0103.MissingReturn", false);   
        //logStdout("Parsed Sequence MissingReturn\n");              
      }                                                                   
      startMissingSeqNumber_MissingReturn     
      endMissingSeqNumber_MissingReturn     
      operatorSpecList_MissingReturn     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.MissingReturn");     
        //logStdout("MissingReturn Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  startMissingSeqNumber_MissingReturn:                                                       
      {                                                                                 
        currBlock = "startMissingSeqNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      StartMissingSeqNumber_opt                                                       
    ;                                                                                   
                                                                                        
  endMissingSeqNumber_MissingReturn:                                                       
      {                                                                                 
        currBlock = "endMissingSeqNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EndMissingSeqNumber_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecList_MissingReturn:                                                       
      {                                                                                 
        currBlock = "operatorSpecList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  MoBasicCallInformation_opt:                                           
      MoBasicCallInformation                                            
    |                                                              
    ;                                                              
                                                                   
  MoBasicCallInformation:                                               
      TAP_0311.MoBasicCallInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.MoBasicCallInformation", false);   
        //logStdout("Parsed Sequence MoBasicCallInformation\n");              
      }                                                                   
      chargeableSubscriber_MoBasicCallInformation     
      rapFileSequenceNumber_MoBasicCallInformation     
      destination_MoBasicCallInformation     
      destinationNetwork_MoBasicCallInformation     
      callEventStartTimeStamp_MoBasicCallInformation     
      totalCallEventDuration_MoBasicCallInformation     
      simToolkitIndicator_MoBasicCallInformation     
      causeForTerm_MoBasicCallInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.MoBasicCallInformation");     
        //logStdout("MoBasicCallInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargeableSubscriber_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "chargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeableSubscriber_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  destination_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "destination";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Destination_opt                                                       
    ;                                                                                   
                                                                                        
  destinationNetwork_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "destinationNetwork";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DestinationNetwork_opt                                                       
    ;                                                                                   
                                                                                        
  callEventStartTimeStamp_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "callEventStartTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventStartTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  totalCallEventDuration_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "totalCallEventDuration";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalCallEventDuration_opt                                                       
    ;                                                                                   
                                                                                        
  simToolkitIndicator_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "simToolkitIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SimToolkitIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  causeForTerm_MoBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "causeForTerm";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CauseForTerm_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  MobileOriginatedCall_opt:                                           
      MobileOriginatedCall                                            
    |                                                              
    ;                                                              
                                                                   
  MobileOriginatedCall:                                               
      TAP_0311.MobileOriginatedCall                                 
      {                                                                   
        __onBlockStart("TAP_0311.MobileOriginatedCall", false);   
        //logStdout("Parsed Sequence MobileOriginatedCall\n");              
      }                                                                   
      basicCallInformation_MobileOriginatedCall     
      locationInformation_MobileOriginatedCall     
      equipmentIdentifier_MobileOriginatedCall     
      basicServiceUsedList_MobileOriginatedCall     
      supplServiceCode_MobileOriginatedCall     
      thirdPartyInformation_MobileOriginatedCall     
      camelServiceUsed_MobileOriginatedCall     
      operatorSpecInformation_MobileOriginatedCall     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.MobileOriginatedCall");     
        //logStdout("MobileOriginatedCall Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  basicCallInformation_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "basicCallInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MoBasicCallInformation_opt                                                       
    ;                                                                                   
                                                                                        
  locationInformation_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "locationInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationInformation_opt                                                       
    ;                                                                                   
                                                                                        
  equipmentIdentifier_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "equipmentIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ImeiOrEsn_opt                                                       
    ;                                                                                   
                                                                                        
  basicServiceUsedList_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "basicServiceUsedList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BasicServiceUsedList_opt                                                       
    ;                                                                                   
                                                                                        
  supplServiceCode_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "supplServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SupplServiceCode_opt                                                       
    ;                                                                                   
                                                                                        
  thirdPartyInformation_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "thirdPartyInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ThirdPartyInformation_opt                                                       
    ;                                                                                   
                                                                                        
  camelServiceUsed_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "camelServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CamelServiceUsed_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_MobileOriginatedCall:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  MobileTerminatedCall_opt:                                           
      MobileTerminatedCall                                            
    |                                                              
    ;                                                              
                                                                   
  MobileTerminatedCall:                                               
      TAP_0311.MobileTerminatedCall                                 
      {                                                                   
        __onBlockStart("TAP_0311.MobileTerminatedCall", false);   
        //logStdout("Parsed Sequence MobileTerminatedCall\n");              
      }                                                                   
      basicCallInformation_MobileTerminatedCall     
      locationInformation_MobileTerminatedCall     
      equipmentIdentifier_MobileTerminatedCall     
      basicServiceUsedList_MobileTerminatedCall     
      camelServiceUsed_MobileTerminatedCall     
      operatorSpecInformation_MobileTerminatedCall     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.MobileTerminatedCall");     
        //logStdout("MobileTerminatedCall Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  basicCallInformation_MobileTerminatedCall:                                                       
      {                                                                                 
        currBlock = "basicCallInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MtBasicCallInformation_opt                                                       
    ;                                                                                   
                                                                                        
  locationInformation_MobileTerminatedCall:                                                       
      {                                                                                 
        currBlock = "locationInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationInformation_opt                                                       
    ;                                                                                   
                                                                                        
  equipmentIdentifier_MobileTerminatedCall:                                                       
      {                                                                                 
        currBlock = "equipmentIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ImeiOrEsn_opt                                                       
    ;                                                                                   
                                                                                        
  basicServiceUsedList_MobileTerminatedCall:                                                       
      {                                                                                 
        currBlock = "basicServiceUsedList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BasicServiceUsedList_opt                                                       
    ;                                                                                   
                                                                                        
  camelServiceUsed_MobileTerminatedCall:                                                       
      {                                                                                 
        currBlock = "camelServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CamelServiceUsed_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_MobileTerminatedCall:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  Msisdn_opt:                                                         
      Msisdn                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Msisdn:                                                             
      TAP_0311.Msisdn                                        
      {                                                                          
        __onField("TAP_0311.Msisdn.Msisdn");    
        //logStdout("Parsed Leaf Msisdn\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  MtBasicCallInformation_opt:                                           
      MtBasicCallInformation                                            
    |                                                              
    ;                                                              
                                                                   
  MtBasicCallInformation:                                               
      TAP_0311.MtBasicCallInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.MtBasicCallInformation", false);   
        //logStdout("Parsed Sequence MtBasicCallInformation\n");              
      }                                                                   
      chargeableSubscriber_MtBasicCallInformation     
      rapFileSequenceNumber_MtBasicCallInformation     
      callOriginator_MtBasicCallInformation     
      originatingNetwork_MtBasicCallInformation     
      callEventStartTimeStamp_MtBasicCallInformation     
      totalCallEventDuration_MtBasicCallInformation     
      simToolkitIndicator_MtBasicCallInformation     
      causeForTerm_MtBasicCallInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.MtBasicCallInformation");     
        //logStdout("MtBasicCallInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargeableSubscriber_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "chargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeableSubscriber_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  callOriginator_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "callOriginator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallOriginator_opt                                                       
    ;                                                                                   
                                                                                        
  originatingNetwork_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "originatingNetwork";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OriginatingNetwork_opt                                                       
    ;                                                                                   
                                                                                        
  callEventStartTimeStamp_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "callEventStartTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventStartTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  totalCallEventDuration_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "totalCallEventDuration";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalCallEventDuration_opt                                                       
    ;                                                                                   
                                                                                        
  simToolkitIndicator_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "simToolkitIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SimToolkitIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  causeForTerm_MtBasicCallInformation:                                                       
      {                                                                                 
        currBlock = "causeForTerm";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CauseForTerm_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  Network_opt:                                           
      Network                                            
    |                                                              
    ;                                                              
                                                                   
  Network:                                               
      TAP_0311.Network                                 
      {                                                                   
        __onBlockStart("TAP_0311.Network", false);   
        //logStdout("Parsed Sequence Network\n");              
      }                                                                   
      networkIdType_Network     
      networkIdentifier_Network     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.Network");     
        //logStdout("Network Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  networkIdType_Network:                                                       
      {                                                                                 
        currBlock = "networkIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkIdType_opt                                                       
    ;                                                                                   
                                                                                        
  networkIdentifier_Network:                                                       
      {                                                                                 
        currBlock = "networkIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  NetworkAccessIdentifier_opt:                                                         
      NetworkAccessIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NetworkAccessIdentifier:                                                             
      TAP_0311.NetworkAccessIdentifier                                        
      {                                                                          
        __onField("TAP_0311.NetworkAccessIdentifier.NetworkAccessIdentifier");    
        //logStdout("Parsed Leaf NetworkAccessIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
  NetworkId_opt:         
      NetworkId          
    |                            
    ;                            
                                 
  NetworkId:             
      AsciiString               
    ;                            
                                                                                 
  NetworkIdType_opt:                                                         
      NetworkIdType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NetworkIdType:                                                             
      TAP_0311.NetworkIdType                                        
      {                                                                          
        __onField("TAP_0311.NetworkIdType.NetworkIdType");    
        //logStdout("Parsed Leaf NetworkIdType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  NetworkIdentifier_opt:                                                         
      NetworkIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NetworkIdentifier:                                                             
      TAP_0311.NetworkIdentifier                                        
      {                                                                          
        __onField("TAP_0311.NetworkIdentifier.NetworkIdentifier");    
        //logStdout("Parsed Leaf NetworkIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  NetworkInfo_opt:                                           
      NetworkInfo                                            
    |                                                              
    ;                                                              
                                                                   
  NetworkInfo:                                               
      TAP_0311.NetworkInfo                                 
      {                                                                   
        __onBlockStart("TAP_0311.NetworkInfo", false);   
        //logStdout("Parsed Sequence NetworkInfo\n");              
      }                                                                   
      utcTimeOffsetInfo_NetworkInfo     
      recEntityInfo_NetworkInfo     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.NetworkInfo");     
        //logStdout("NetworkInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  utcTimeOffsetInfo_NetworkInfo:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetInfoList_opt                                                       
    ;                                                                                   
                                                                                        
  recEntityInfo_NetworkInfo:                                                       
      {                                                                                 
        currBlock = "recEntityInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  NetworkInfoError_opt:                                           
      NetworkInfoError                                            
    |                                                              
    ;                                                              
                                                                   
  NetworkInfoError:                                               
      RAP_0103.NetworkInfoError                                 
      {                                                                   
        __onBlockStart("RAP_0103.NetworkInfoError", false);   
        //logStdout("Parsed Sequence NetworkInfoError\n");              
      }                                                                   
      networkInfo_NetworkInfoError     
      errorDetail_NetworkInfoError     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.NetworkInfoError");     
        //logStdout("NetworkInfoError Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  networkInfo_NetworkInfoError:                                                       
      {                                                                                 
        currBlock = "networkInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkInfo_opt                                                       
    ;                                                                                   
                                                                                        
  errorDetail_NetworkInfoError:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  NetworkInitPDPContext_opt:                                                         
      NetworkInitPDPContext                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NetworkInitPDPContext:                                                             
      TAP_0311.NetworkInitPDPContext                                        
      {                                                                          
        __onField("TAP_0311.NetworkInitPDPContext.NetworkInitPDPContext");    
        //logStdout("Parsed Leaf NetworkInitPDPContext\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                        
  NetworkList_opt:                                                                
      TAP_0311.NetworkList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.NetworkList", true);                  
        //logStdout("Parsed List NetworkList\n");                                
      }                                                                                 
      NetworkList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.NetworkList");                          
        //logStdout("NetworkList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  NetworkList:                                                                    
      NetworkList                                                                 
      Network_NetworkList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  Network_NetworkList:                                                       
      {                                                                                 
        currBlock = "Network";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Network                                                           
    ;                                                                                   
                                                                   
  NetworkLocation_opt:                                           
      NetworkLocation                                            
    |                                                              
    ;                                                              
                                                                   
  NetworkLocation:                                               
      TAP_0311.NetworkLocation                                 
      {                                                                   
        __onBlockStart("TAP_0311.NetworkLocation", false);   
        //logStdout("Parsed Sequence NetworkLocation\n");              
      }                                                                   
      recEntityCode_NetworkLocation     
      callReference_NetworkLocation     
      locationArea_NetworkLocation     
      cellId_NetworkLocation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.NetworkLocation");     
        //logStdout("NetworkLocation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  recEntityCode_NetworkLocation:                                                       
      {                                                                                 
        currBlock = "recEntityCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityCode_opt                                                       
    ;                                                                                   
                                                                                        
  callReference_NetworkLocation:                                                       
      {                                                                                 
        currBlock = "callReference";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallReference_opt                                                       
    ;                                                                                   
                                                                                        
  locationArea_NetworkLocation:                                                       
      {                                                                                 
        currBlock = "locationArea";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationArea_opt                                                       
    ;                                                                                   
                                                                                        
  cellId_NetworkLocation:                                                       
      {                                                                                 
        currBlock = "cellId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CellId_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  NonChargedNumber_opt:                                                         
      NonChargedNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NonChargedNumber:                                                             
      TAP_0311.NonChargedNumber                                        
      {                                                                          
        __onField("TAP_0311.NonChargedNumber.NonChargedNumber");    
        //logStdout("Parsed Leaf NonChargedNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  Notification_opt:                                           
      Notification                                            
    |                                                              
    ;                                                              
                                                                   
  Notification:                                               
      TAP_0311.Notification                                 
      {                                                                   
        __onBlockStart("TAP_0311.Notification", false);   
        //logStdout("Parsed Sequence Notification\n");              
      }                                                                   
      sender_Notification     
      recipient_Notification     
      fileSequenceNumber_Notification     
      rapFileSequenceNumber_Notification     
      fileCreationTimeStamp_Notification     
      fileAvailableTimeStamp_Notification     
      transferCutOffTimeStamp_Notification     
      specificationVersionNumber_Notification     
      releaseVersionNumber_Notification     
      fileTypeIndicator_Notification     
      operatorSpecInformation_Notification     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.Notification");     
        //logStdout("Notification Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  sender_Notification:                                                       
      {                                                                                 
        currBlock = "sender";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Sender_opt                                                       
    ;                                                                                   
                                                                                        
  recipient_Notification:                                                       
      {                                                                                 
        currBlock = "recipient";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Recipient_opt                                                       
    ;                                                                                   
                                                                                        
  fileSequenceNumber_Notification:                                                       
      {                                                                                 
        currBlock = "fileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_Notification:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  fileCreationTimeStamp_Notification:                                                       
      {                                                                                 
        currBlock = "fileCreationTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileCreationTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  fileAvailableTimeStamp_Notification:                                                       
      {                                                                                 
        currBlock = "fileAvailableTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileAvailableTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  transferCutOffTimeStamp_Notification:                                                       
      {                                                                                 
        currBlock = "transferCutOffTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TransferCutOffTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  specificationVersionNumber_Notification:                                                       
      {                                                                                 
        currBlock = "specificationVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SpecificationVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  releaseVersionNumber_Notification:                                                       
      {                                                                                 
        currBlock = "releaseVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReleaseVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  fileTypeIndicator_Notification:                                                       
      {                                                                                 
        currBlock = "fileTypeIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileTypeIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_Notification:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  NotificationError_opt:                                           
      NotificationError                                            
    |                                                              
    ;                                                              
                                                                   
  NotificationError:                                               
      RAP_0103.NotificationError                                 
      {                                                                   
        __onBlockStart("RAP_0103.NotificationError", false);   
        //logStdout("Parsed Sequence NotificationError\n");              
      }                                                                   
      notification_NotificationError     
      errorDetail_NotificationError     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.NotificationError");     
        //logStdout("NotificationError Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  notification_NotificationError:                                                       
      {                                                                                 
        currBlock = "notification";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Notification_opt                                                       
    ;                                                                                   
                                                                                        
  errorDetail_NotificationError:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  NumberOfDecimalPlaces_opt:                                                         
      NumberOfDecimalPlaces                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NumberOfDecimalPlaces:                                                             
      TAP_0311.NumberOfDecimalPlaces                                        
      {                                                                          
        __onField("TAP_0311.NumberOfDecimalPlaces.NumberOfDecimalPlaces");    
        //logStdout("Parsed Leaf NumberOfDecimalPlaces\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  NumberString_opt:                                                         
      NumberString                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NumberString:                                                             
      TAP_0311.NumberString                                        
      {                                                                          
        __onField("TAP_0311.NumberString.NumberString");    
        //logStdout("Parsed Leaf NumberString\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ObjectType_opt:                                                         
      ObjectType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ObjectType:                                                             
      TAP_0311.ObjectType                                        
      {                                                                          
        __onField("TAP_0311.ObjectType.ObjectType");    
        //logStdout("Parsed Leaf ObjectType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                        
  OperatorSpecInfoList_opt:                                                                
      TAP_0311.OperatorSpecInfoList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.OperatorSpecInfoList", true);                  
        //logStdout("Parsed List OperatorSpecInfoList\n");                                
      }                                                                                 
      OperatorSpecInfoList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.OperatorSpecInfoList");                          
        //logStdout("OperatorSpecInfoList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  OperatorSpecInfoList:                                                                    
      OperatorSpecInfoList                                                                 
      OperatorSpecInformation_OperatorSpecInfoList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  OperatorSpecInformation_OperatorSpecInfoList:                                                       
      {                                                                                 
        currBlock = "OperatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInformation                                                           
    ;                                                                                   
                                                                                 
  OperatorSpecInformation_opt:                                                         
      OperatorSpecInformation                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  OperatorSpecInformation:                                                             
      TAP_0311.OperatorSpecInformation                                        
      {                                                                          
        __onField("TAP_0311.OperatorSpecInformation.OperatorSpecInformation");    
        //logStdout("Parsed Leaf OperatorSpecInformation\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                        
  OperatorSpecList_opt:                                                                
      RAP_0103.OperatorSpecList                                               
      {                                                                                 
        __onBlockStart("RAP_0103.OperatorSpecList", true);                  
        //logStdout("Parsed List OperatorSpecList\n");                                
      }                                                                                 
      OperatorSpecList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("RAP_0103.OperatorSpecList");                          
        //logStdout("OperatorSpecList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  OperatorSpecList:                                                                    
      OperatorSpecList                                                                 
      OperatorSpecInformation_OperatorSpecList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  OperatorSpecInformation_OperatorSpecList:                                                       
      {                                                                                 
        currBlock = "OperatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInformation                                                           
    ;                                                                                   
                                                                   
  OrderPlacedTimeStamp_opt:                                           
      OrderPlacedTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  OrderPlacedTimeStamp:                                               
      TAP_0311.OrderPlacedTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.OrderPlacedTimeStamp", false);   
        //logStdout("Parsed Sequence OrderPlacedTimeStamp\n");              
      }                                                                   
      localTimeStamp_OrderPlacedTimeStamp     
      utcTimeOffsetCode_OrderPlacedTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.OrderPlacedTimeStamp");     
        //logStdout("OrderPlacedTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_OrderPlacedTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_OrderPlacedTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  OriginatingNetwork_opt:                                                         
      OriginatingNetwork                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  OriginatingNetwork:                                                             
      TAP_0311.OriginatingNetwork                                        
      {                                                                          
        __onField("TAP_0311.OriginatingNetwork.OriginatingNetwork");    
        //logStdout("Parsed Leaf OriginatingNetwork\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  PDPContextStartTimestamp_opt:                                           
      PDPContextStartTimestamp                                            
    |                                                              
    ;                                                              
                                                                   
  PDPContextStartTimestamp:                                               
      TAP_0311.PDPContextStartTimestamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.PDPContextStartTimestamp", false);   
        //logStdout("Parsed Sequence PDPContextStartTimestamp\n");              
      }                                                                   
      localTimeStamp_PDPContextStartTimestamp     
      utcTimeOffsetCode_PDPContextStartTimestamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.PDPContextStartTimestamp");     
        //logStdout("PDPContextStartTimestamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_PDPContextStartTimestamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_PDPContextStartTimestamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  PacketDataProtocolAddress_opt:                                                         
      PacketDataProtocolAddress                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PacketDataProtocolAddress:                                                             
      TAP_0311.PacketDataProtocolAddress                                        
      {                                                                          
        __onField("TAP_0311.PacketDataProtocolAddress.PacketDataProtocolAddress");    
        //logStdout("Parsed Leaf PacketDataProtocolAddress\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PaidIndicator_opt:                                                         
      PaidIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PaidIndicator:                                                             
      TAP_0311.PaidIndicator                                        
      {                                                                          
        __onField("TAP_0311.PaidIndicator.PaidIndicator");    
        //logStdout("Parsed Leaf PaidIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PartialTypeIndicator_opt:                                                         
      PartialTypeIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PartialTypeIndicator:                                                             
      TAP_0311.PartialTypeIndicator                                        
      {                                                                          
        __onField("TAP_0311.PartialTypeIndicator.PartialTypeIndicator");    
        //logStdout("Parsed Leaf PartialTypeIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PathItemId_opt:                                                         
      PathItemId                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PathItemId:                                                             
      RAP_0103.PathItemId                                        
      {                                                                          
        __onField("RAP_0103.PathItemId.PathItemId");    
        //logStdout("Parsed Leaf PathItemId\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PaymentMethod_opt:                                                         
      PaymentMethod                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PaymentMethod:                                                             
      TAP_0311.PaymentMethod                                        
      {                                                                          
        __onField("TAP_0311.PaymentMethod.PaymentMethod");    
        //logStdout("Parsed Leaf PaymentMethod\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PdpAddress_opt:                                                         
      PdpAddress                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PdpAddress:                                                             
      TAP_0311.PdpAddress                                        
      {                                                                          
        __onField("TAP_0311.PdpAddress.PdpAddress");    
        //logStdout("Parsed Leaf PdpAddress\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PercentageRate_opt:                                                         
      PercentageRate                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PercentageRate:                                                             
      TAP_0311.PercentageRate                                        
      {                                                                          
        __onField("TAP_0311.PercentageRate.PercentageRate");    
        //logStdout("Parsed Leaf PercentageRate\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PlmnId_opt:                                                         
      PlmnId                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PlmnId:                                                             
      TAP_0311.PlmnId                                        
      {                                                                          
        __onField("TAP_0311.PlmnId.PlmnId");    
        //logStdout("Parsed Leaf PlmnId\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PositioningMethod_opt:                                                         
      PositioningMethod                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PositioningMethod:                                                             
      TAP_0311.PositioningMethod                                        
      {                                                                          
        __onField("TAP_0311.PositioningMethod.PositioningMethod");    
        //logStdout("Parsed Leaf PositioningMethod\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  PriorityCode_opt:                                                         
      PriorityCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  PriorityCode:                                                             
      TAP_0311.PriorityCode                                        
      {                                                                          
        __onField("TAP_0311.PriorityCode.PriorityCode");    
        //logStdout("Parsed Leaf PriorityCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  RapAuditControlInfo_opt:                                           
      RapAuditControlInfo                                            
    |                                                              
    ;                                                              
                                                                   
  RapAuditControlInfo:                                               
      RAP_0103.RapAuditControlInfo                                 
      {                                                                   
        __onBlockStart("RAP_0103.RapAuditControlInfo", false);   
        //logStdout("Parsed Sequence RapAuditControlInfo\n");              
      }                                                                   
      totalSevereReturnValue_RapAuditControlInfo     
      returnDetailsCount_RapAuditControlInfo     
      operatorSpecList_RapAuditControlInfo     
      totalSevereReturnTax_RapAuditControlInfo     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.RapAuditControlInfo");     
        //logStdout("RapAuditControlInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  totalSevereReturnValue_RapAuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalSevereReturnValue";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalSevereReturnValue_opt                                                       
    ;                                                                                   
                                                                                        
  returnDetailsCount_RapAuditControlInfo:                                                       
      {                                                                                 
        currBlock = "returnDetailsCount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReturnDetailsCount_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecList_RapAuditControlInfo:                                                       
      {                                                                                 
        currBlock = "operatorSpecList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecList_opt                                                       
    ;                                                                                   
                                                                                        
  totalSevereReturnTax_RapAuditControlInfo:                                                       
      {                                                                                 
        currBlock = "totalSevereReturnTax";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalSevereReturnTax_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  RapBatchControlInfo_opt:                                           
      RapBatchControlInfo                                            
    |                                                              
    ;                                                              
                                                                   
  RapBatchControlInfo:                                               
      RAP_0103.RapBatchControlInfo                                 
      {                                                                   
        __onBlockStart("RAP_0103.RapBatchControlInfo", false);   
        //logStdout("Parsed Sequence RapBatchControlInfo\n");              
      }                                                                   
      sender_RapBatchControlInfo     
      recipient_RapBatchControlInfo     
      rapFileSequenceNumber_RapBatchControlInfo     
      rapFileCreationTimeStamp_RapBatchControlInfo     
      rapFileAvailableTimeStamp_RapBatchControlInfo     
      specificationVersionNumber_RapBatchControlInfo     
      releaseVersionNumber_RapBatchControlInfo     
      rapSpecificationVersionNumber_RapBatchControlInfo     
      rapReleaseVersionNumber_RapBatchControlInfo     
      fileTypeIndicator_RapBatchControlInfo     
      roamingPartner_RapBatchControlInfo     
      operatorSpecList_RapBatchControlInfo     
      tapDecimalPlaces_RapBatchControlInfo
      tapCurrency_RapBatchControlInfo
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.RapBatchControlInfo");     
        //logStdout("RapBatchControlInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  sender_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "sender";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Sender_opt                                                       
    ;                                                                                   
                                                                                        
  recipient_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "recipient";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Recipient_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileCreationTimeStamp_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "rapFileCreationTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileCreationTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileAvailableTimeStamp_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "rapFileAvailableTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileAvailableTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  specificationVersionNumber_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "specificationVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SpecificationVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  releaseVersionNumber_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "releaseVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReleaseVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  rapSpecificationVersionNumber_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "rapSpecificationVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapSpecificationVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  rapReleaseVersionNumber_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "rapReleaseVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapReleaseVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  fileTypeIndicator_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "fileTypeIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileTypeIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  roamingPartner_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "roamingPartner";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RoamingPartner_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecList_RapBatchControlInfo:                                                       
      {                                                                                 
        currBlock = "operatorSpecList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecList_opt                                                       
    ;                                                                                   
  
  tapDecimalPlaces_RapBatchControlInfo:
     {
       currBlock = "tapDecimalPlaces";
       //logStdout("currContext= " + currContext + "\n");
     }
     TapDecimalPlaces_opt
   ;

  tapCurrency_RapBatchControlInfo:
     {
       currBlock = "tapCurrency";
       //logStdout("currContext= " + currContext + "\n");
     }
     TapCurrency_opt
   ; 
                                                                                        
                                      
  RapDataInterChange_opt:              
      RapDataInterChange               
    |                                 
    ;                                 
                                      
  RapDataInterChange:                  
      {                               
        __onBlockStart("", false);  
      }                               
      RapDataInterChange_elems         
      {                               
        __onBlockEnd("");           
      }                               
    ;                                 
                                      
  RapDataInterChange_elems:            
      returnBatch_RapDataInterChange     
    | acknowledgement_RapDataInterChange     
    ;                                 
                                      
  returnBatch_RapDataInterChange:                                                       
      {                                                                                 
        currBlock = "returnBatch";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReturnBatch                                                           
    ;                                                                                   
                                                                                        
  acknowledgement_RapDataInterChange:                                                       
      {                                                                                 
        currBlock = "acknowledgement";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Acknowledgement                                                           
    ;                                                                                   
                                                                                        
                                                                   
  RapFileAvailableTimeStamp_opt:                                           
      RapFileAvailableTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  RapFileAvailableTimeStamp:                                               
      RAP_0103.RapFileAvailableTimeStamp                                 
      {                                                                   
        __onBlockStart("RAP_0103.RapFileAvailableTimeStamp", false);   
        //logStdout("Parsed Sequence RapFileAvailableTimeStamp\n");              
      }                                                                   
      localTimeStamp_RapFileAvailableTimeStamp     
      utcTimeOffset_RapFileAvailableTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.RapFileAvailableTimeStamp");     
        //logStdout("RapFileAvailableTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_RapFileAvailableTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_RapFileAvailableTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  RapFileCreationTimeStamp_opt:                                           
      RapFileCreationTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  RapFileCreationTimeStamp:                                               
      RAP_0103.RapFileCreationTimeStamp                                 
      {                                                                   
        __onBlockStart("RAP_0103.RapFileCreationTimeStamp", false);   
        //logStdout("Parsed Sequence RapFileCreationTimeStamp\n");              
      }                                                                   
      localTimeStamp_RapFileCreationTimeStamp     
      utcTimeOffset_RapFileCreationTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.RapFileCreationTimeStamp");     
        //logStdout("RapFileCreationTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_RapFileCreationTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_RapFileCreationTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  RapFileSequenceNumber_opt:                                                         
      RapFileSequenceNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  RapFileSequenceNumber:                                                             
      TAP_0311.RapFileSequenceNumber                                        
      {                                                                          
        __onField("TAP_0311.RapFileSequenceNumber.RapFileSequenceNumber");    
        //logStdout("Parsed Leaf RapFileSequenceNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  RapReleaseVersionNumber_opt:                                                         
      RapReleaseVersionNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  RapReleaseVersionNumber:                                                             
      RAP_0103.RapReleaseVersionNumber                                        
      {                                                                          
        __onField("RAP_0103.RapReleaseVersionNumber.RapReleaseVersionNumber");    
        //logStdout("Parsed Leaf RapReleaseVersionNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  RapSpecificationVersionNumber_opt:                                                         
      RapSpecificationVersionNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  RapSpecificationVersionNumber:                                                             
      RAP_0103.RapSpecificationVersionNumber                                        
      {                                                                          
        __onField("RAP_0103.RapSpecificationVersionNumber.RapSpecificationVersionNumber");    
        //logStdout("Parsed Leaf RapSpecificationVersionNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  RecEntityCode_opt:                                                         
      RecEntityCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  RecEntityCode:                                                             
      TAP_0311.RecEntityCode                                        
      {                                                                          
        __onField("TAP_0311.RecEntityCode.RecEntityCode");    
        //logStdout("Parsed Leaf RecEntityCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                        
  RecEntityCodeList_opt:                                                                
      TAP_0311.RecEntityCodeList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.RecEntityCodeList", true);                  
        //logStdout("Parsed List RecEntityCodeList\n");                                
      }                                                                                 
      RecEntityCodeList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.RecEntityCodeList");                          
        //logStdout("RecEntityCodeList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  RecEntityCodeList:                                                                    
      RecEntityCodeList                                                                 
      RecEntityCode_RecEntityCodeList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  RecEntityCode_RecEntityCodeList:                                                       
      {                                                                                 
        currBlock = "RecEntityCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityCode                                                           
    ;                                                                                   
                                                                                 
  RecEntityId_opt:                                                         
      RecEntityId                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  RecEntityId:                                                             
      TAP_0311.RecEntityId                                        
      {                                                                          
        __onField("TAP_0311.RecEntityId.RecEntityId");    
        //logStdout("Parsed Leaf RecEntityId\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                        
  RecEntityInfoList_opt:                                                                
      TAP_0311.RecEntityInfoList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.RecEntityInfoList", true);                  
        //logStdout("Parsed List RecEntityInfoList\n");                                
      }                                                                                 
      RecEntityInfoList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.RecEntityInfoList");                          
        //logStdout("RecEntityInfoList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  RecEntityInfoList:                                                                    
      RecEntityInfoList                                                                 
      RecEntityInformation_RecEntityInfoList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  RecEntityInformation_RecEntityInfoList:                                                       
      {                                                                                 
        currBlock = "RecEntityInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityInformation                                                           
    ;                                                                                   
                                                                   
  RecEntityInformation_opt:                                           
      RecEntityInformation                                            
    |                                                              
    ;                                                              
                                                                   
  RecEntityInformation:                                               
      TAP_0311.RecEntityInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.RecEntityInformation", false);   
        //logStdout("Parsed Sequence RecEntityInformation\n");              
      }                                                                   
      recEntityCode_RecEntityInformation     
      recEntityType_RecEntityInformation     
      recEntityId_RecEntityInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.RecEntityInformation");     
        //logStdout("RecEntityInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  recEntityCode_RecEntityInformation:                                                       
      {                                                                                 
        currBlock = "recEntityCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityCode_opt                                                       
    ;                                                                                   
                                                                                        
  recEntityType_RecEntityInformation:                                                       
      {                                                                                 
        currBlock = "recEntityType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityType_opt                                                       
    ;                                                                                   
                                                                                        
  recEntityId_RecEntityInformation:                                                       
      {                                                                                 
        currBlock = "recEntityId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityId_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  RecEntityType_opt:                                                         
      RecEntityType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  RecEntityType:                                                             
      TAP_0311.RecEntityType                                        
      {                                                                          
        __onField("TAP_0311.RecEntityType.RecEntityType");    
        //logStdout("Parsed Leaf RecEntityType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Recipient_opt:                                                         
      Recipient                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Recipient:                                                             
      TAP_0311.Recipient                                        
      {                                                                          
        __onField("TAP_0311.Recipient.Recipient");    
        //logStdout("Parsed Leaf Recipient\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ReleaseVersionNumber_opt:                                                         
      ReleaseVersionNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ReleaseVersionNumber:                                                             
      TAP_0311.ReleaseVersionNumber                                        
      {                                                                          
        __onField("TAP_0311.ReleaseVersionNumber.ReleaseVersionNumber");    
        //logStdout("Parsed Leaf ReleaseVersionNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  RequestedDeliveryTimeStamp_opt:                                           
      RequestedDeliveryTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  RequestedDeliveryTimeStamp:                                               
      TAP_0311.RequestedDeliveryTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.RequestedDeliveryTimeStamp", false);   
        //logStdout("Parsed Sequence RequestedDeliveryTimeStamp\n");              
      }                                                                   
      localTimeStamp_RequestedDeliveryTimeStamp     
      utcTimeOffsetCode_RequestedDeliveryTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.RequestedDeliveryTimeStamp");     
        //logStdout("RequestedDeliveryTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_RequestedDeliveryTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffsetCode_RequestedDeliveryTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  ResponseTime_opt:                                                         
      ResponseTime                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ResponseTime:                                                             
      TAP_0311.ResponseTime                                        
      {                                                                          
        __onField("TAP_0311.ResponseTime.ResponseTime");    
        //logStdout("Parsed Leaf ResponseTime\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ResponseTimeCategory_opt:                                                         
      ResponseTimeCategory                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ResponseTimeCategory:                                                             
      TAP_0311.ResponseTimeCategory                                        
      {                                                                          
        __onField("TAP_0311.ResponseTimeCategory.ResponseTimeCategory");    
        //logStdout("Parsed Leaf ResponseTimeCategory\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ReturnBatch_opt:                                           
      ReturnBatch                                            
    |                                                              
    ;                                                              
                                                                   
  ReturnBatch:                                               
      RAP_0103.ReturnBatch                                 
      {                                                                   
        __onBlockStart("RAP_0103.ReturnBatch", false);   
        //logStdout("Parsed Sequence ReturnBatch\n");              
      }                                                                   
      rapBatchControlInfoRap_ReturnBatch     
      returnDetails_ReturnBatch     
      rapAuditControlInfo_ReturnBatch     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.ReturnBatch");     
        //logStdout("ReturnBatch Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  rapBatchControlInfoRap_ReturnBatch:                                                       
      {                                                                                 
        currBlock = "rapBatchControlInfoRap";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapBatchControlInfo_opt                                                       
    ;                                                                                   
                                                                                        
  returnDetails_ReturnBatch:                                                       
      {                                                                                 
        currBlock = "returnDetails";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReturnDetailList_opt                                                       
    ;                                                                                   
                                                                                        
  rapAuditControlInfo_ReturnBatch:                                                       
      {                                                                                 
        currBlock = "rapAuditControlInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapAuditControlInfo_opt                                                       
    ;                                                                                   
                                                                                        
                                      
  ReturnDetail_opt:              
      ReturnDetail               
    |                                 
    ;                                 
                                      
  ReturnDetail:                  
      {                               
        __onBlockStart("", false);  
      }                               
      ReturnDetail_elems         
      {                               
        __onBlockEnd("");           
      }                               
    ;                                 
                                      
  ReturnDetail_elems:            
      missingReturn_ReturnDetail     
    | fatalReturn_ReturnDetail     
    | severeReturn_ReturnDetail     
    ;                                 
                                      
  missingReturn_ReturnDetail:                                                       
      {                                                                                 
        currBlock = "missingReturn";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MissingReturn                                                           
    ;                                                                                   
                                                                                        
  fatalReturn_ReturnDetail:                                                       
      {                                                                                 
        currBlock = "fatalReturn";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FatalReturn                                                           
    ;                                                                                   
                                                                                        
  severeReturn_ReturnDetail:                                                       
      {                                                                                 
        currBlock = "severeReturn";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SevereReturn                                                           
    ;                                                                                   
                                                                                        
                                                                                        
  ReturnDetailList_opt:                                                                
      RAP_0103.ReturnDetailList                                               
      {                                                                                 
        __onBlockStart("RAP_0103.ReturnDetailList", true);                  
        //logStdout("Parsed List ReturnDetailList\n");                                
      }                                                                                 
      ReturnDetailList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("RAP_0103.ReturnDetailList");                          
        //logStdout("ReturnDetailList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  ReturnDetailList:                                                                    
      ReturnDetailList                                                                 
      ReturnDetail_ReturnDetailList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  ReturnDetail_ReturnDetailList:                                                       
      {                                                                                 
        currBlock = "ReturnDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReturnDetail                                                           
    ;                                                                                   
                                                                                 
  ReturnDetailsCount_opt:                                                         
      ReturnDetailsCount                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ReturnDetailsCount:                                                             
      RAP_0103.ReturnDetailsCount                                        
      {                                                                          
        __onField("RAP_0103.ReturnDetailsCount.ReturnDetailsCount");    
        //logStdout("Parsed Leaf ReturnDetailsCount\n");                         
      }                                                                          
    ;                                                                            
                                                                   
  RoamingPartner_opt:                                                         
      RoamingPartner                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  RoamingPartner:                                                             
      RAP_0103.RoamingPartner                                        
      {                                                                          
        __onField("RAP_0103.RoamingPartner.RoamingPartner");    
        //logStdout("Parsed Leaf RoamingPartner\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SMSDestinationNumber_opt:                                                         
      SMSDestinationNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SMSDestinationNumber:                                                             
      TAP_0311.SMSDestinationNumber                                        
      {                                                                          
        __onField("TAP_0311.SMSDestinationNumber.SMSDestinationNumber");    
        //logStdout("Parsed Leaf SMSDestinationNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SMSOriginator_opt:                                                         
      SMSOriginator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SMSOriginator:                                                             
      TAP_0311.SMSOriginator                                        
      {                                                                          
        __onField("TAP_0311.SMSOriginator.SMSOriginator");    
        //logStdout("Parsed Leaf SMSOriginator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ScuBasicInformation_opt:                                           
      ScuBasicInformation                                            
    |                                                              
    ;                                                              
                                                                   
  ScuBasicInformation:                                               
      TAP_0311.ScuBasicInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.ScuBasicInformation", false);   
        //logStdout("Parsed Sequence ScuBasicInformation\n");              
      }                                                                   
      chargeableSubscriber_ScuBasicInformation     
      chargedPartyStatus_ScuBasicInformation     
      nonChargedNumber_ScuBasicInformation     
      clirIndicator_ScuBasicInformation     
      originatingNetwork_ScuBasicInformation     
      destinationNetwork_ScuBasicInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ScuBasicInformation");     
        //logStdout("ScuBasicInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargeableSubscriber_ScuBasicInformation:                                                       
      {                                                                                 
        currBlock = "chargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ScuChargeableSubscriber_opt                                                       
    ;                                                                                   
                                                                                        
  chargedPartyStatus_ScuBasicInformation:                                                       
      {                                                                                 
        currBlock = "chargedPartyStatus";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargedPartyStatus_opt                                                       
    ;                                                                                   
                                                                                        
  nonChargedNumber_ScuBasicInformation:                                                       
      {                                                                                 
        currBlock = "nonChargedNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NonChargedNumber_opt                                                       
    ;                                                                                   
                                                                                        
  clirIndicator_ScuBasicInformation:                                                       
      {                                                                                 
        currBlock = "clirIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ClirIndicator_opt                                                       
    ;                                                                                   
                                                                                        
  originatingNetwork_ScuBasicInformation:                                                       
      {                                                                                 
        currBlock = "originatingNetwork";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OriginatingNetwork_opt                                                       
    ;                                                                                   
                                                                                        
  destinationNetwork_ScuBasicInformation:                                                       
      {                                                                                 
        currBlock = "destinationNetwork";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DestinationNetwork_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  ScuChargeType_opt:                                           
      ScuChargeType                                            
    |                                                              
    ;                                                              
                                                                   
  ScuChargeType:                                               
      TAP_0311.ScuChargeType                                 
      {                                                                   
        __onBlockStart("TAP_0311.ScuChargeType", false);   
        //logStdout("Parsed Sequence ScuChargeType\n");              
      }                                                                   
      messageStatus_ScuChargeType     
      priorityCode_ScuChargeType     
      distanceChargeBandCode_ScuChargeType     
      messageType_ScuChargeType     
      messageDescriptionCode_ScuChargeType     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ScuChargeType");     
        //logStdout("ScuChargeType Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  messageStatus_ScuChargeType:                                                       
      {                                                                                 
        currBlock = "messageStatus";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageStatus_opt                                                       
    ;                                                                                   
                                                                                        
  priorityCode_ScuChargeType:                                                       
      {                                                                                 
        currBlock = "priorityCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      PriorityCode_opt                                                       
    ;                                                                                   
                                                                                        
  distanceChargeBandCode_ScuChargeType:                                                       
      {                                                                                 
        currBlock = "distanceChargeBandCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DistanceChargeBandCode_opt                                                       
    ;                                                                                   
                                                                                        
  messageType_ScuChargeType:                                                       
      {                                                                                 
        currBlock = "messageType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageType_opt                                                       
    ;                                                                                   
                                                                                        
  messageDescriptionCode_ScuChargeType:                                                       
      {                                                                                 
        currBlock = "messageDescriptionCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MessageDescriptionCode_opt                                                       
    ;                                                                                   
                                                                                        
                                                                
  ScuChargeableSubscriber_opt:                                        
      ScuChargeableSubscriber                                         
    |                                                           
    ;                                                           
                                                                
  ScuChargeableSubscriber:                                                       
      TAP_0311.ScuChargeableSubscriber                                  
      {                                                                    
        __onBlockStart("TAP_0311.ScuChargeableSubscriber", false);    
        //logStdout("Parsed Choice ScuChargeableSubscriber\n");                 
      }                                                         
      ScuChargeableSubscriber_elems                                   
      ASN1.BlockEnd                                                
      {                                                         
        __onBlockEnd("TAP_0311.ScuChargeableSubscriber");  
        //logStdout("ScuChargeableSubscriber Choice END.\n");        
      }                                                         
    ;                                                           
                                                                
  ScuChargeableSubscriber_elems:                                      
      gsmChargeableSubscriber_ScuChargeableSubscriber     
    | minChargeableSubscriber_ScuChargeableSubscriber     
    ;                                                           
                                                                
  gsmChargeableSubscriber_ScuChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "gsmChargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GsmChargeableSubscriber                                                           
    ;                                                                                   
                                                                                        
  minChargeableSubscriber_ScuChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "minChargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      MinChargeableSubscriber                                                           
    ;                                                                                   
                                                                                        
                                                                   
  ScuTimeStamps_opt:                                           
      ScuTimeStamps                                            
    |                                                              
    ;                                                              
                                                                   
  ScuTimeStamps:                                               
      TAP_0311.ScuTimeStamps                                 
      {                                                                   
        __onBlockStart("TAP_0311.ScuTimeStamps", false);   
        //logStdout("Parsed Sequence ScuTimeStamps\n");              
      }                                                                   
      depositTimeStamp_ScuTimeStamps     
      completionTimeStamp_ScuTimeStamps     
      chargingPoint_ScuTimeStamps     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ScuTimeStamps");     
        //logStdout("ScuTimeStamps Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  depositTimeStamp_ScuTimeStamps:                                                       
      {                                                                                 
        currBlock = "depositTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DepositTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  completionTimeStamp_ScuTimeStamps:                                                       
      {                                                                                 
        currBlock = "completionTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CompletionTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  chargingPoint_ScuTimeStamps:                                                       
      {                                                                                 
        currBlock = "chargingPoint";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargingPoint_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  Sender_opt:                                                         
      Sender                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Sender:                                                             
      TAP_0311.Sender                                        
      {                                                                          
        __onField("TAP_0311.Sender.Sender");    
        //logStdout("Parsed Leaf Sender\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ServiceCentreUsage_opt:                                           
      ServiceCentreUsage                                            
    |                                                              
    ;                                                              
                                                                   
  ServiceCentreUsage:                                               
      TAP_0311.ServiceCentreUsage                                 
      {                                                                   
        __onBlockStart("TAP_0311.ServiceCentreUsage", false);   
        //logStdout("Parsed Sequence ServiceCentreUsage\n");              
      }                                                                   
      basicInformation_ServiceCentreUsage     
      rapFileSequenceNumber_ServiceCentreUsage     
      servingNetwork_ServiceCentreUsage     
      recEntityCode_ServiceCentreUsage     
      chargeInformation_ServiceCentreUsage     
      scuChargeType_ServiceCentreUsage     
      scuTimeStamps_ServiceCentreUsage     
      operatorSpecInformation_ServiceCentreUsage     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ServiceCentreUsage");     
        //logStdout("ServiceCentreUsage Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  basicInformation_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "basicInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ScuBasicInformation_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  servingNetwork_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "servingNetwork";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServingNetwork_opt                                                       
    ;                                                                                   
                                                                                        
  recEntityCode_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "recEntityCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityCode_opt                                                       
    ;                                                                                   
                                                                                        
  chargeInformation_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "chargeInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeInformation_opt                                                       
    ;                                                                                   
                                                                                        
  scuChargeType_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "scuChargeType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ScuChargeType_opt                                                       
    ;                                                                                   
                                                                                        
  scuTimeStamps_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "scuTimeStamps";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ScuTimeStamps_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_ServiceCentreUsage:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  ServingBid_opt:                                                         
      ServingBid                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ServingBid:                                                             
      TAP_0311.ServingBid                                        
      {                                                                          
        __onField("TAP_0311.ServingBid.ServingBid");    
        //logStdout("Parsed Leaf ServingBid\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ServingLocationDescription_opt:                                                         
      ServingLocationDescription                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ServingLocationDescription:                                                             
      TAP_0311.ServingLocationDescription                                        
      {                                                                          
        __onField("TAP_0311.ServingLocationDescription.ServingLocationDescription");    
        //logStdout("Parsed Leaf ServingLocationDescription\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ServingNetwork_opt:                                                         
      ServingNetwork                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ServingNetwork:                                                             
      TAP_0311.ServingNetwork                                        
      {                                                                          
        __onField("TAP_0311.ServingNetwork.ServingNetwork");    
        //logStdout("Parsed Leaf ServingNetwork\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ServingPartiesInformation_opt:                                           
      ServingPartiesInformation                                            
    |                                                              
    ;                                                              
                                                                   
  ServingPartiesInformation:                                               
      TAP_0311.ServingPartiesInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.ServingPartiesInformation", false);   
        //logStdout("Parsed Sequence ServingPartiesInformation\n");              
      }                                                                   
      contentProviderName_ServingPartiesInformation     
      contentProviderIdList_ServingPartiesInformation     
      internetServiceProviderIdList_ServingPartiesInformation     
      networkList_ServingPartiesInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ServingPartiesInformation");     
        //logStdout("ServingPartiesInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  contentProviderName_ServingPartiesInformation:                                                       
      {                                                                                 
        currBlock = "contentProviderName";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentProviderName_opt                                                       
    ;                                                                                   
                                                                                        
  contentProviderIdList_ServingPartiesInformation:                                                       
      {                                                                                 
        currBlock = "contentProviderIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ContentProviderIdList_opt                                                       
    ;                                                                                   
                                                                                        
  internetServiceProviderIdList_ServingPartiesInformation:                                                       
      {                                                                                 
        currBlock = "internetServiceProviderIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      InternetServiceProviderIdList_opt                                                       
    ;                                                                                   
                                                                                        
  networkList_ServingPartiesInformation:                                                       
      {                                                                                 
        currBlock = "networkList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      NetworkList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  SevereReturn_opt:                                           
      SevereReturn                                            
    |                                                              
    ;                                                              
                                                                   
  SevereReturn:                                               
      RAP_0103.SevereReturn                                 
      {                                                                   
        __onBlockStart("RAP_0103.SevereReturn", false);   
        //logStdout("Parsed Sequence SevereReturn\n");              
      }                                                                   
      fileSequenceNumber_SevereReturn     
      callEventDetail_SevereReturn     
      errorDetail_SevereReturn     
      operatorSpecList_SevereReturn     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.SevereReturn");     
        //logStdout("SevereReturn Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  fileSequenceNumber_SevereReturn:                                                       
      {                                                                                 
        currBlock = "fileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  callEventDetail_SevereReturn:                                                       
      {                                                                                 
        currBlock = "callEventDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventDetail_opt                                                       
    ;                                                                                   
                                                                                        
  errorDetail_SevereReturn:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecList_SevereReturn:                                                       
      {                                                                                 
        currBlock = "operatorSpecList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecList_opt                                                       
    ;                                                                                   
                                                                                 
  SimChargeableSubscriber_opt:                                           
      SimChargeableSubscriber                                            
    |                                                              
    ;                                                              
                                                                   
  SimChargeableSubscriber:                                               
      TAP_0311.SimChargeableSubscriber                                 
      {                                                                   
        __onBlockStart("TAP_0311.SimChargeableSubscriber", false);   
        //logStdout("Parsed Sequence SimChargeableSubscriber\n");              
      }                                                                   
      imsi_SimChargeableSubscriber     
      msisdn_SimChargeableSubscriber     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.SimChargeableSubscriber");     
        //logStdout("SimChargeableSubscriber Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  imsi_SimChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "imsi";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imsi_opt                                                       
    ;                                                                                   
                                                                                        
  msisdn_SimChargeableSubscriber:                                                       
      {                                                                                 
        currBlock = "msisdn";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Msisdn_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  SimToolkitIndicator_opt:                                                         
      SimToolkitIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SimToolkitIndicator:                                                             
      TAP_0311.SimToolkitIndicator                                        
      {                                                                          
        __onField("TAP_0311.SimToolkitIndicator.SimToolkitIndicator");    
        //logStdout("Parsed Leaf SimToolkitIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SpecificationVersionNumber_opt:                                                         
      SpecificationVersionNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SpecificationVersionNumber:                                                             
      TAP_0311.SpecificationVersionNumber                                        
      {                                                                          
        __onField("TAP_0311.SpecificationVersionNumber.SpecificationVersionNumber");    
        //logStdout("Parsed Leaf SpecificationVersionNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SsParameters_opt:                                                         
      SsParameters                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SsParameters:                                                             
      TAP_0311.SsParameters                                        
      {                                                                          
        __onField("TAP_0311.SsParameters.SsParameters");    
        //logStdout("Parsed Leaf SsParameters\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  StartMissingSeqNumber_opt:                                                         
      StartMissingSeqNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  StartMissingSeqNumber:                                                             
      RAP_0103.StartMissingSeqNumber                                        
      {                                                                          
        __onField("RAP_0103.StartMissingSeqNumber.StartMissingSeqNumber");    
        //logStdout("Parsed Leaf StartMissingSeqNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SupplServiceActionCode_opt:                                                         
      SupplServiceActionCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SupplServiceActionCode:                                                             
      TAP_0311.SupplServiceActionCode                                        
      {                                                                          
        __onField("TAP_0311.SupplServiceActionCode.SupplServiceActionCode");    
        //logStdout("Parsed Leaf SupplServiceActionCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SupplServiceCode_opt:                                                         
      SupplServiceCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SupplServiceCode:                                                             
      TAP_0311.SupplServiceCode                                        
      {                                                                          
        __onField("TAP_0311.SupplServiceCode.SupplServiceCode");    
        //logStdout("Parsed Leaf SupplServiceCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  SupplServiceEvent_opt:                                           
      SupplServiceEvent                                            
    |                                                              
    ;                                                              
                                                                   
  SupplServiceEvent:                                               
      TAP_0311.SupplServiceEvent                                 
      {                                                                   
        __onBlockStart("TAP_0311.SupplServiceEvent", false);   
        //logStdout("Parsed Sequence SupplServiceEvent\n");              
      }                                                                   
      chargeableSubscriber_SupplServiceEvent     
      rapFileSequenceNumber_SupplServiceEvent     
      locationInformation_SupplServiceEvent     
      equipmentIdentifier_SupplServiceEvent     
      supplServiceUsed_SupplServiceEvent     
      operatorSpecInformation_SupplServiceEvent     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.SupplServiceEvent");     
        //logStdout("SupplServiceEvent Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  chargeableSubscriber_SupplServiceEvent:                                                       
      {                                                                                 
        currBlock = "chargeableSubscriber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeableSubscriber_opt                                                       
    ;                                                                                   
                                                                                        
  rapFileSequenceNumber_SupplServiceEvent:                                                       
      {                                                                                 
        currBlock = "rapFileSequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RapFileSequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  locationInformation_SupplServiceEvent:                                                       
      {                                                                                 
        currBlock = "locationInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationInformation_opt                                                       
    ;                                                                                   
                                                                                        
  equipmentIdentifier_SupplServiceEvent:                                                       
      {                                                                                 
        currBlock = "equipmentIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ImeiOrEsn_opt                                                       
    ;                                                                                   
                                                                                        
  supplServiceUsed_SupplServiceEvent:                                                       
      {                                                                                 
        currBlock = "supplServiceUsed";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SupplServiceUsed_opt                                                       
    ;                                                                                   
                                                                                        
  operatorSpecInformation_SupplServiceEvent:                                                       
      {                                                                                 
        currBlock = "operatorSpecInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      OperatorSpecInfoList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  SupplServiceUsed_opt:                                           
      SupplServiceUsed                                            
    |                                                              
    ;                                                              
                                                                   
  SupplServiceUsed:                                               
      TAP_0311.SupplServiceUsed                                 
      {                                                                   
        __onBlockStart("TAP_0311.SupplServiceUsed", false);   
        //logStdout("Parsed Sequence SupplServiceUsed\n");              
      }                                                                   
      supplServiceCode_SupplServiceUsed     
      supplServiceActionCode_SupplServiceUsed     
      ssParameters_SupplServiceUsed     
      chargingTimeStamp_SupplServiceUsed     
      chargeInformation_SupplServiceUsed     
      basicServiceCodeList_SupplServiceUsed     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.SupplServiceUsed");     
        //logStdout("SupplServiceUsed Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  supplServiceCode_SupplServiceUsed:                                                       
      {                                                                                 
        currBlock = "supplServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SupplServiceCode_opt                                                       
    ;                                                                                   
                                                                                        
  supplServiceActionCode_SupplServiceUsed:                                                       
      {                                                                                 
        currBlock = "supplServiceActionCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SupplServiceActionCode_opt                                                       
    ;                                                                                   
                                                                                        
  ssParameters_SupplServiceUsed:                                                       
      {                                                                                 
        currBlock = "ssParameters";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SsParameters_opt                                                       
    ;                                                                                   
                                                                                        
  chargingTimeStamp_SupplServiceUsed:                                                       
      {                                                                                 
        currBlock = "chargingTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargingTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  chargeInformation_SupplServiceUsed:                                                       
      {                                                                                 
        currBlock = "chargeInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeInformation_opt                                                       
    ;                                                                                   
                                                                                        
  basicServiceCodeList_SupplServiceUsed:                                                       
      {                                                                                 
        currBlock = "basicServiceCodeList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BasicServiceCodeList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  TapCurrency_opt:                                                         
      TapCurrency                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TapCurrency:                                                             
      TAP_0311.TapCurrency                                        
      {                                                                          
        __onField("TAP_0311.TapCurrency.TapCurrency");    
        //logStdout("Parsed Leaf TapCurrency\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TapDecimalPlaces_opt:                                                         
      TapDecimalPlaces                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TapDecimalPlaces:                                                             
      TAP_0311.TapDecimalPlaces                                        
      {                                                                          
        __onField("TAP_0311.TapDecimalPlaces.TapDecimalPlaces");    
        //logStdout("Parsed Leaf TapDecimalPlaces\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TaxCode_opt:                                                         
      TaxCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TaxCode:                                                             
      TAP_0311.TaxCode                                        
      {                                                                          
        __onField("TAP_0311.TaxCode.TaxCode");    
        //logStdout("Parsed Leaf TaxCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  TaxIndicator_opt:                                                         
      TaxIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TaxIndicator:                                                             
      TAP_0311.TaxIndicator                                        
      {                                                                          
        __onField("TAP_0311.TaxIndicator.TaxIndicator");    
        //logStdout("Parsed Leaf TaxIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  TaxInformation_opt:                                           
      TaxInformation                                            
    |                                                              
    ;                                                              
                                                                   
  TaxInformation:                                               
      TAP_0311.TaxInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.TaxInformation", false);   
        //logStdout("Parsed Sequence TaxInformation\n");              
      }                                                                   
      taxCode_TaxInformation     
      taxValue_TaxInformation     
      taxableAmount_TaxInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TaxInformation");     
        //logStdout("TaxInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  taxCode_TaxInformation:                                                       
      {                                                                                 
        currBlock = "taxCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxCode_opt                                                       
    ;                                                                                   
                                                                                        
  taxValue_TaxInformation:                                                       
      {                                                                                 
        currBlock = "taxValue";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxValue_opt                                                       
    ;                                                                                   
                                                                                        
  taxableAmount_TaxInformation:                                                       
      {                                                                                 
        currBlock = "taxableAmount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxableAmount_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  TaxInformationList_opt:                                                                
      TAP_0311.TaxInformationList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TaxInformationList", true);                  
        //logStdout("Parsed List TaxInformationList\n");                                
      }                                                                                 
      TaxInformationList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TaxInformationList");                          
        //logStdout("TaxInformationList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TaxInformationList:                                                                    
      TaxInformationList                                                                 
      TaxInformation_TaxInformationList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TaxInformation_TaxInformationList:                                                       
      {                                                                                 
        currBlock = "TaxInformation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxInformation                                                           
    ;                                                                                   
                                                                                 
  TaxRate_opt:                                                         
      TaxRate                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TaxRate:                                                             
      TAP_0311.TaxRate                                        
      {                                                                          
        __onField("TAP_0311.TaxRate.TaxRate");    
        //logStdout("Parsed Leaf TaxRate\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TaxType_opt:                                                         
      TaxType                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TaxType:                                                             
      TAP_0311.TaxType                                        
      {                                                                          
        __onField("TAP_0311.TaxType.TaxType");    
        //logStdout("Parsed Leaf TaxType\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TaxValue_opt:                                                         
      TaxValue                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TaxValue:                                                             
      TAP_0311.TaxValue                                        
      {                                                                          
        __onField("TAP_0311.TaxValue.TaxValue");    
        //logStdout("Parsed Leaf TaxValue\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TaxableAmount_opt:                                                         
      TaxableAmount                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TaxableAmount:                                                             
      TAP_0311.TaxableAmount                                        
      {                                                                          
        __onField("TAP_0311.TaxableAmount.TaxableAmount");    
        //logStdout("Parsed Leaf TaxableAmount\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  Taxation_opt:                                           
      Taxation                                            
    |                                                              
    ;                                                              
                                                                   
  Taxation:                                               
      TAP_0311.Taxation                                 
      {                                                                   
        __onBlockStart("TAP_0311.Taxation", false);   
        //logStdout("Parsed Sequence Taxation\n");              
      }                                                                   
      taxCode_Taxation     
      taxType_Taxation     
      taxRate_Taxation     
      chargeType_Taxation     
      taxIndicator_Taxation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.Taxation");     
        //logStdout("Taxation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  taxCode_Taxation:                                                       
      {                                                                                 
        currBlock = "taxCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxCode_opt                                                       
    ;                                                                                   
                                                                                        
  taxType_Taxation:                                                       
      {                                                                                 
        currBlock = "taxType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxType_opt                                                       
    ;                                                                                   
                                                                                        
  taxRate_Taxation:                                                       
      {                                                                                 
        currBlock = "taxRate";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxRate_opt                                                       
    ;                                                                                   
                                                                                        
  chargeType_Taxation:                                                       
      {                                                                                 
        currBlock = "chargeType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeType_opt                                                       
    ;                                                                                   
                                                                                        
  taxIndicator_Taxation:                                                       
      {                                                                                 
        currBlock = "taxIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TaxIndicator_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  TaxationList_opt:                                                                
      TAP_0311.TaxationList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TaxationList", true);                  
        //logStdout("Parsed List TaxationList\n");                                
      }                                                                                 
      TaxationList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TaxationList");                          
        //logStdout("TaxationList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TaxationList:                                                                    
      TaxationList                                                                 
      Taxation_TaxationList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  Taxation_TaxationList:                                                       
      {                                                                                 
        currBlock = "Taxation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Taxation                                                           
    ;                                                                                   
                                                                                 
  TeleServiceCode_opt:                                                         
      TeleServiceCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TeleServiceCode:                                                             
      TAP_0311.TeleServiceCode                                        
      {                                                                          
        __onField("TAP_0311.TeleServiceCode.TeleServiceCode");    
        //logStdout("Parsed Leaf TeleServiceCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  ThirdPartyInformation_opt:                                           
      ThirdPartyInformation                                            
    |                                                              
    ;                                                              
                                                                   
  ThirdPartyInformation:                                               
      TAP_0311.ThirdPartyInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.ThirdPartyInformation", false);   
        //logStdout("Parsed Sequence ThirdPartyInformation\n");              
      }                                                                   
      thirdPartyNumber_ThirdPartyInformation     
      clirIndicator_ThirdPartyInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.ThirdPartyInformation");     
        //logStdout("ThirdPartyInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  thirdPartyNumber_ThirdPartyInformation:                                                       
      {                                                                                 
        currBlock = "thirdPartyNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ThirdPartyNumber_opt                                                       
    ;                                                                                   
                                                                                        
  clirIndicator_ThirdPartyInformation:                                                       
      {                                                                                 
        currBlock = "clirIndicator";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ClirIndicator_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  ThirdPartyNumber_opt:                                                         
      ThirdPartyNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ThirdPartyNumber:                                                             
      TAP_0311.ThirdPartyNumber                                        
      {                                                                          
        __onField("TAP_0311.ThirdPartyNumber.ThirdPartyNumber");    
        //logStdout("Parsed Leaf ThirdPartyNumber\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                
  ThreeGcamelDestination_opt:                                        
      ThreeGcamelDestination                                         
    |                                                           
    ;                                                           
                                                                
  ThreeGcamelDestination:                                                       
      TAP_0311.ThreeGcamelDestination                                  
      {                                                                    
        __onBlockStart("TAP_0311.ThreeGcamelDestination", false);    
        //logStdout("Parsed Choice ThreeGcamelDestination\n");                 
      }                                                         
      ThreeGcamelDestination_elems                                   
      ASN1.BlockEnd                                                
      {                                                         
        __onBlockEnd("TAP_0311.ThreeGcamelDestination");  
        //logStdout("ThreeGcamelDestination Choice END.\n");        
      }                                                         
    ;                                                           
                                                                
  ThreeGcamelDestination_elems:                                      
      camelDestinationNumber_ThreeGcamelDestination     
    | gprsDestination_ThreeGcamelDestination     
    ;                                                           
                                                                
  camelDestinationNumber_ThreeGcamelDestination:                                                       
      {                                                                                 
        currBlock = "camelDestinationNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CamelDestinationNumber                                                           
    ;                                                                                   
                                                                                        
  gprsDestination_ThreeGcamelDestination:                                                       
      {                                                                                 
        currBlock = "gprsDestination";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GprsDestination                                                           
    ;                                                                                   
                                                                                        
                                                                                 
  TotalAdvisedCharge_opt:                                                         
      TotalAdvisedCharge                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalAdvisedCharge:                                                             
      TAP_0311.TotalAdvisedCharge                                        
      {                                                                          
        __onField("TAP_0311.TotalAdvisedCharge.TotalAdvisedCharge");    
        //logStdout("Parsed Leaf TotalAdvisedCharge\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalAdvisedChargeRefund_opt:                                                         
      TotalAdvisedChargeRefund                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalAdvisedChargeRefund:                                                             
      TAP_0311.TotalAdvisedChargeRefund                                        
      {                                                                          
        __onField("TAP_0311.TotalAdvisedChargeRefund.TotalAdvisedChargeRefund");    
        //logStdout("Parsed Leaf TotalAdvisedChargeRefund\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  TotalAdvisedChargeValue_opt:                                           
      TotalAdvisedChargeValue                                            
    |                                                              
    ;                                                              
                                                                   
  TotalAdvisedChargeValue:                                               
      TAP_0311.TotalAdvisedChargeValue                                 
      {                                                                   
        __onBlockStart("TAP_0311.TotalAdvisedChargeValue", false);   
        //logStdout("Parsed Sequence TotalAdvisedChargeValue\n");              
      }                                                                   
      advisedChargeCurrency_TotalAdvisedChargeValue     
      totalAdvisedCharge_TotalAdvisedChargeValue     
      totalAdvisedChargeRefund_TotalAdvisedChargeValue     
      totalCommission_TotalAdvisedChargeValue     
      totalCommissionRefund_TotalAdvisedChargeValue     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TotalAdvisedChargeValue");     
        //logStdout("TotalAdvisedChargeValue Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  advisedChargeCurrency_TotalAdvisedChargeValue:                                                       
      {                                                                                 
        currBlock = "advisedChargeCurrency";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AdvisedChargeCurrency_opt                                                       
    ;                                                                                   
                                                                                        
  totalAdvisedCharge_TotalAdvisedChargeValue:                                                       
      {                                                                                 
        currBlock = "totalAdvisedCharge";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalAdvisedCharge_opt                                                       
    ;                                                                                   
                                                                                        
  totalAdvisedChargeRefund_TotalAdvisedChargeValue:                                                       
      {                                                                                 
        currBlock = "totalAdvisedChargeRefund";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalAdvisedChargeRefund_opt                                                       
    ;                                                                                   
                                                                                        
  totalCommission_TotalAdvisedChargeValue:                                                       
      {                                                                                 
        currBlock = "totalCommission";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalCommission_opt                                                       
    ;                                                                                   
                                                                                        
  totalCommissionRefund_TotalAdvisedChargeValue:                                                       
      {                                                                                 
        currBlock = "totalCommissionRefund";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalCommissionRefund_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  TotalAdvisedChargeValueList_opt:                                                                
      TAP_0311.TotalAdvisedChargeValueList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TotalAdvisedChargeValueList", true);                  
        //logStdout("Parsed List TotalAdvisedChargeValueList\n");                                
      }                                                                                 
      TotalAdvisedChargeValueList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TotalAdvisedChargeValueList");                          
        //logStdout("TotalAdvisedChargeValueList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TotalAdvisedChargeValueList:                                                                    
      TotalAdvisedChargeValueList                                                                 
      TotalAdvisedChargeValue_TotalAdvisedChargeValueList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TotalAdvisedChargeValue_TotalAdvisedChargeValueList:                                                       
      {                                                                                 
        currBlock = "TotalAdvisedChargeValue";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TotalAdvisedChargeValue                                                           
    ;                                                                                   
                                                                                 
  TotalCallEventDuration_opt:                                                         
      TotalCallEventDuration                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalCallEventDuration:                                                             
      TAP_0311.TotalCallEventDuration                                        
      {                                                                          
        __onField("TAP_0311.TotalCallEventDuration.TotalCallEventDuration");    
        //logStdout("Parsed Leaf TotalCallEventDuration\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalCharge_opt:                                                         
      TotalCharge                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalCharge:                                                             
      TAP_0311.TotalCharge                                        
      {                                                                          
        __onField("TAP_0311.TotalCharge.TotalCharge");    
        //logStdout("Parsed Leaf TotalCharge\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalChargeRefund_opt:                                                         
      TotalChargeRefund                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalChargeRefund:                                                             
      TAP_0311.TotalChargeRefund                                        
      {                                                                          
        __onField("TAP_0311.TotalChargeRefund.TotalChargeRefund");    
        //logStdout("Parsed Leaf TotalChargeRefund\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalCommission_opt:                                                         
      TotalCommission                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalCommission:                                                             
      TAP_0311.TotalCommission                                        
      {                                                                          
        __onField("TAP_0311.TotalCommission.TotalCommission");    
        //logStdout("Parsed Leaf TotalCommission\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalCommissionRefund_opt:                                                         
      TotalCommissionRefund                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalCommissionRefund:                                                             
      TAP_0311.TotalCommissionRefund                                        
      {                                                                          
        __onField("TAP_0311.TotalCommissionRefund.TotalCommissionRefund");    
        //logStdout("Parsed Leaf TotalCommissionRefund\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalDataVolume_opt:                                                         
      TotalDataVolume                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalDataVolume:                                                             
      TAP_0311.TotalDataVolume                                        
      {                                                                          
        __onField("TAP_0311.TotalDataVolume.TotalDataVolume");    
        //logStdout("Parsed Leaf TotalDataVolume\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalDiscountRefund_opt:                                                         
      TotalDiscountRefund                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalDiscountRefund:                                                             
      TAP_0311.TotalDiscountRefund                                        
      {                                                                          
        __onField("TAP_0311.TotalDiscountRefund.TotalDiscountRefund");    
        //logStdout("Parsed Leaf TotalDiscountRefund\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalDiscountValue_opt:                                                         
      TotalDiscountValue                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalDiscountValue:                                                             
      TAP_0311.TotalDiscountValue                                        
      {                                                                          
        __onField("TAP_0311.TotalDiscountValue.TotalDiscountValue");    
        //logStdout("Parsed Leaf TotalDiscountValue\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalSevereReturnTax_opt:                                                         
      TotalSevereReturnTax                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalSevereReturnTax:                                                             
      RAP_0103.TotalSevereReturnTax                                        
      {                                                                          
        __onField("RAP_0103.TotalSevereReturnTax.TotalSevereReturnTax");    
        //logStdout("Parsed Leaf TotalSevereReturnTax\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalSevereReturnValue_opt:                                                         
      TotalSevereReturnValue                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalSevereReturnValue:                                                             
      RAP_0103.TotalSevereReturnValue                                        
      {                                                                          
        __onField("RAP_0103.TotalSevereReturnValue.TotalSevereReturnValue");    
        //logStdout("Parsed Leaf TotalSevereReturnValue\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalTaxRefund_opt:                                                         
      TotalTaxRefund                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalTaxRefund:                                                             
      TAP_0311.TotalTaxRefund                                        
      {                                                                          
        __onField("TAP_0311.TotalTaxRefund.TotalTaxRefund");    
        //logStdout("Parsed Leaf TotalTaxRefund\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalTaxValue_opt:                                                         
      TotalTaxValue                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalTaxValue:                                                             
      TAP_0311.TotalTaxValue                                        
      {                                                                          
        __onField("TAP_0311.TotalTaxValue.TotalTaxValue");    
        //logStdout("Parsed Leaf TotalTaxValue\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TotalTransactionDuration_opt:                                                         
      TotalTransactionDuration                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TotalTransactionDuration:                                                             
      TAP_0311.TotalTransactionDuration                                        
      {                                                                          
        __onField("TAP_0311.TotalTransactionDuration.TotalTransactionDuration");    
        //logStdout("Parsed Leaf TotalTransactionDuration\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  TrackedCustomerEquipment_opt:                                           
      TrackedCustomerEquipment                                            
    |                                                              
    ;                                                              
                                                                   
  TrackedCustomerEquipment:                                               
      TAP_0311.TrackedCustomerEquipment                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackedCustomerEquipment", false);   
        //logStdout("Parsed Sequence TrackedCustomerEquipment\n");              
      }                                                                   
      equipmentIdType_TrackedCustomerEquipment     
      equipmentId_TrackedCustomerEquipment     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackedCustomerEquipment");     
        //logStdout("TrackedCustomerEquipment Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  equipmentIdType_TrackedCustomerEquipment:                                                       
      {                                                                                 
        currBlock = "equipmentIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EquipmentIdType_opt                                                       
    ;                                                                                   
                                                                                        
  equipmentId_TrackedCustomerEquipment:                                                       
      {                                                                                 
        currBlock = "equipmentId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EquipmentId_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  TrackedCustomerHomeId_opt:                                           
      TrackedCustomerHomeId                                            
    |                                                              
    ;                                                              
                                                                   
  TrackedCustomerHomeId:                                               
      TAP_0311.TrackedCustomerHomeId                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackedCustomerHomeId", false);   
        //logStdout("Parsed Sequence TrackedCustomerHomeId\n");              
      }                                                                   
      homeIdType_TrackedCustomerHomeId     
      homeIdentifier_TrackedCustomerHomeId     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackedCustomerHomeId");     
        //logStdout("TrackedCustomerHomeId Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  homeIdType_TrackedCustomerHomeId:                                                       
      {                                                                                 
        currBlock = "homeIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeIdType_opt                                                       
    ;                                                                                   
                                                                                        
  homeIdentifier_TrackedCustomerHomeId:                                                       
      {                                                                                 
        currBlock = "homeIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  TrackedCustomerHomeIdList_opt:                                                                
      TAP_0311.TrackedCustomerHomeIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TrackedCustomerHomeIdList", true);                  
        //logStdout("Parsed List TrackedCustomerHomeIdList\n");                                
      }                                                                                 
      TrackedCustomerHomeIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TrackedCustomerHomeIdList");                          
        //logStdout("TrackedCustomerHomeIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackedCustomerHomeIdList:                                                                    
      TrackedCustomerHomeIdList                                                                 
      TrackedCustomerHomeId_TrackedCustomerHomeIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackedCustomerHomeId_TrackedCustomerHomeIdList:                                                       
      {                                                                                 
        currBlock = "TrackedCustomerHomeId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerHomeId                                                           
    ;                                                                                   
                                                                                        
  TrackedCustomerIdList_opt:                                                                
      TAP_0311.TrackedCustomerIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TrackedCustomerIdList", true);                  
        //logStdout("Parsed List TrackedCustomerIdList\n");                                
      }                                                                                 
      TrackedCustomerIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TrackedCustomerIdList");                          
        //logStdout("TrackedCustomerIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackedCustomerIdList:                                                                    
      TrackedCustomerIdList                                                                 
      TrackedCustomerIdentification_TrackedCustomerIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackedCustomerIdentification_TrackedCustomerIdList:                                                       
      {                                                                                 
        currBlock = "TrackedCustomerIdentification";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerIdentification                                                           
    ;                                                                                   
                                                                   
  TrackedCustomerIdentification_opt:                                           
      TrackedCustomerIdentification                                            
    |                                                              
    ;                                                              
                                                                   
  TrackedCustomerIdentification:                                               
      TAP_0311.TrackedCustomerIdentification                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackedCustomerIdentification", false);   
        //logStdout("Parsed Sequence TrackedCustomerIdentification\n");              
      }                                                                   
      customerIdType_TrackedCustomerIdentification     
      customerIdentifier_TrackedCustomerIdentification     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackedCustomerIdentification");     
        //logStdout("TrackedCustomerIdentification Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  customerIdType_TrackedCustomerIdentification:                                                       
      {                                                                                 
        currBlock = "customerIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CustomerIdType_opt                                                       
    ;                                                                                   
                                                                                        
  customerIdentifier_TrackedCustomerIdentification:                                                       
      {                                                                                 
        currBlock = "customerIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CustomerIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  TrackedCustomerInformation_opt:                                           
      TrackedCustomerInformation                                            
    |                                                              
    ;                                                              
                                                                   
  TrackedCustomerInformation:                                               
      TAP_0311.TrackedCustomerInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackedCustomerInformation", false);   
        //logStdout("Parsed Sequence TrackedCustomerInformation\n");              
      }                                                                   
      trackedCustomerIdList_TrackedCustomerInformation     
      trackedCustomerHomeIdList_TrackedCustomerInformation     
      trackedCustomerLocList_TrackedCustomerInformation     
      trackedCustomerEquipment_TrackedCustomerInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackedCustomerInformation");     
        //logStdout("TrackedCustomerInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  trackedCustomerIdList_TrackedCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackedCustomerIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerIdList_opt                                                       
    ;                                                                                   
                                                                                        
  trackedCustomerHomeIdList_TrackedCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackedCustomerHomeIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerHomeIdList_opt                                                       
    ;                                                                                   
                                                                                        
  trackedCustomerLocList_TrackedCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackedCustomerLocList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerLocList_opt                                                       
    ;                                                                                   
                                                                                        
  trackedCustomerEquipment_TrackedCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackedCustomerEquipment";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerEquipment_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  TrackedCustomerLocList_opt:                                                                
      TAP_0311.TrackedCustomerLocList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TrackedCustomerLocList", true);                  
        //logStdout("Parsed List TrackedCustomerLocList\n");                                
      }                                                                                 
      TrackedCustomerLocList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TrackedCustomerLocList");                          
        //logStdout("TrackedCustomerLocList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackedCustomerLocList:                                                                    
      TrackedCustomerLocList                                                                 
      TrackedCustomerLocation_TrackedCustomerLocList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackedCustomerLocation_TrackedCustomerLocList:                                                       
      {                                                                                 
        currBlock = "TrackedCustomerLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackedCustomerLocation                                                           
    ;                                                                                   
                                                                   
  TrackedCustomerLocation_opt:                                           
      TrackedCustomerLocation                                            
    |                                                              
    ;                                                              
                                                                   
  TrackedCustomerLocation:                                               
      TAP_0311.TrackedCustomerLocation                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackedCustomerLocation", false);   
        //logStdout("Parsed Sequence TrackedCustomerLocation\n");              
      }                                                                   
      locationIdType_TrackedCustomerLocation     
      locationIdentifier_TrackedCustomerLocation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackedCustomerLocation");     
        //logStdout("TrackedCustomerLocation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  locationIdType_TrackedCustomerLocation:                                                       
      {                                                                                 
        currBlock = "locationIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationIdType_opt                                                       
    ;                                                                                   
                                                                                        
  locationIdentifier_TrackedCustomerLocation:                                                       
      {                                                                                 
        currBlock = "locationIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  TrackingCustomerEquipment_opt:                                           
      TrackingCustomerEquipment                                            
    |                                                              
    ;                                                              
                                                                   
  TrackingCustomerEquipment:                                               
      TAP_0311.TrackingCustomerEquipment                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackingCustomerEquipment", false);   
        //logStdout("Parsed Sequence TrackingCustomerEquipment\n");              
      }                                                                   
      equipmentIdType_TrackingCustomerEquipment     
      equipmentId_TrackingCustomerEquipment     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackingCustomerEquipment");     
        //logStdout("TrackingCustomerEquipment Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  equipmentIdType_TrackingCustomerEquipment:                                                       
      {                                                                                 
        currBlock = "equipmentIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EquipmentIdType_opt                                                       
    ;                                                                                   
                                                                                        
  equipmentId_TrackingCustomerEquipment:                                                       
      {                                                                                 
        currBlock = "equipmentId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      EquipmentId_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  TrackingCustomerHomeId_opt:                                           
      TrackingCustomerHomeId                                            
    |                                                              
    ;                                                              
                                                                   
  TrackingCustomerHomeId:                                               
      TAP_0311.TrackingCustomerHomeId                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackingCustomerHomeId", false);   
        //logStdout("Parsed Sequence TrackingCustomerHomeId\n");              
      }                                                                   
      homeIdType_TrackingCustomerHomeId     
      homeIdentifier_TrackingCustomerHomeId     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackingCustomerHomeId");     
        //logStdout("TrackingCustomerHomeId Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  homeIdType_TrackingCustomerHomeId:                                                       
      {                                                                                 
        currBlock = "homeIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeIdType_opt                                                       
    ;                                                                                   
                                                                                        
  homeIdentifier_TrackingCustomerHomeId:                                                       
      {                                                                                 
        currBlock = "homeIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      HomeIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  TrackingCustomerHomeIdList_opt:                                                                
      TAP_0311.TrackingCustomerHomeIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TrackingCustomerHomeIdList", true);                  
        //logStdout("Parsed List TrackingCustomerHomeIdList\n");                                
      }                                                                                 
      TrackingCustomerHomeIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TrackingCustomerHomeIdList");                          
        //logStdout("TrackingCustomerHomeIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackingCustomerHomeIdList:                                                                    
      TrackingCustomerHomeIdList                                                                 
      TrackingCustomerHomeId_TrackingCustomerHomeIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackingCustomerHomeId_TrackingCustomerHomeIdList:                                                       
      {                                                                                 
        currBlock = "TrackingCustomerHomeId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerHomeId                                                           
    ;                                                                                   
                                                                                        
  TrackingCustomerIdList_opt:                                                                
      TAP_0311.TrackingCustomerIdList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TrackingCustomerIdList", true);                  
        //logStdout("Parsed List TrackingCustomerIdList\n");                                
      }                                                                                 
      TrackingCustomerIdList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TrackingCustomerIdList");                          
        //logStdout("TrackingCustomerIdList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackingCustomerIdList:                                                                    
      TrackingCustomerIdList                                                                 
      TrackingCustomerIdentification_TrackingCustomerIdList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackingCustomerIdentification_TrackingCustomerIdList:                                                       
      {                                                                                 
        currBlock = "TrackingCustomerIdentification";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerIdentification                                                           
    ;                                                                                   
                                                                   
  TrackingCustomerIdentification_opt:                                           
      TrackingCustomerIdentification                                            
    |                                                              
    ;                                                              
                                                                   
  TrackingCustomerIdentification:                                               
      TAP_0311.TrackingCustomerIdentification                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackingCustomerIdentification", false);   
        //logStdout("Parsed Sequence TrackingCustomerIdentification\n");              
      }                                                                   
      customerIdType_TrackingCustomerIdentification     
      customerIdentifier_TrackingCustomerIdentification     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackingCustomerIdentification");     
        //logStdout("TrackingCustomerIdentification Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  customerIdType_TrackingCustomerIdentification:                                                       
      {                                                                                 
        currBlock = "customerIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CustomerIdType_opt                                                       
    ;                                                                                   
                                                                                        
  customerIdentifier_TrackingCustomerIdentification:                                                       
      {                                                                                 
        currBlock = "customerIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CustomerIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  TrackingCustomerInformation_opt:                                           
      TrackingCustomerInformation                                            
    |                                                              
    ;                                                              
                                                                   
  TrackingCustomerInformation:                                               
      TAP_0311.TrackingCustomerInformation                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackingCustomerInformation", false);   
        //logStdout("Parsed Sequence TrackingCustomerInformation\n");              
      }                                                                   
      trackingCustomerIdList_TrackingCustomerInformation     
      trackingCustomerHomeIdList_TrackingCustomerInformation     
      trackingCustomerLocList_TrackingCustomerInformation     
      trackingCustomerEquipment_TrackingCustomerInformation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackingCustomerInformation");     
        //logStdout("TrackingCustomerInformation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  trackingCustomerIdList_TrackingCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackingCustomerIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerIdList_opt                                                       
    ;                                                                                   
                                                                                        
  trackingCustomerHomeIdList_TrackingCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackingCustomerHomeIdList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerHomeIdList_opt                                                       
    ;                                                                                   
                                                                                        
  trackingCustomerLocList_TrackingCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackingCustomerLocList";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerLocList_opt                                                       
    ;                                                                                   
                                                                                        
  trackingCustomerEquipment_TrackingCustomerInformation:                                                       
      {                                                                                 
        currBlock = "trackingCustomerEquipment";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerEquipment_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  TrackingCustomerLocList_opt:                                                                
      TAP_0311.TrackingCustomerLocList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.TrackingCustomerLocList", true);                  
        //logStdout("Parsed List TrackingCustomerLocList\n");                                
      }                                                                                 
      TrackingCustomerLocList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.TrackingCustomerLocList");                          
        //logStdout("TrackingCustomerLocList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackingCustomerLocList:                                                                    
      TrackingCustomerLocList                                                                 
      TrackingCustomerLocation_TrackingCustomerLocList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  TrackingCustomerLocation_TrackingCustomerLocList:                                                       
      {                                                                                 
        currBlock = "TrackingCustomerLocation";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TrackingCustomerLocation                                                           
    ;                                                                                   
                                                                   
  TrackingCustomerLocation_opt:                                           
      TrackingCustomerLocation                                            
    |                                                              
    ;                                                              
                                                                   
  TrackingCustomerLocation:                                               
      TAP_0311.TrackingCustomerLocation                                 
      {                                                                   
        __onBlockStart("TAP_0311.TrackingCustomerLocation", false);   
        //logStdout("Parsed Sequence TrackingCustomerLocation\n");              
      }                                                                   
      locationIdType_TrackingCustomerLocation     
      locationIdentifier_TrackingCustomerLocation     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TrackingCustomerLocation");     
        //logStdout("TrackingCustomerLocation Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  locationIdType_TrackingCustomerLocation:                                                       
      {                                                                                 
        currBlock = "locationIdType";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationIdType_opt                                                       
    ;                                                                                   
                                                                                        
  locationIdentifier_TrackingCustomerLocation:                                                       
      {                                                                                 
        currBlock = "locationIdentifier";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocationIdentifier_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  TrackingFrequency_opt:                                                         
      TrackingFrequency                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TrackingFrequency:                                                             
      TAP_0311.TrackingFrequency                                        
      {                                                                          
        __onField("TAP_0311.TrackingFrequency.TrackingFrequency");    
        //logStdout("Parsed Leaf TrackingFrequency\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TrackingPeriod_opt:                                                         
      TrackingPeriod                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TrackingPeriod:                                                             
      TAP_0311.TrackingPeriod                                        
      {                                                                          
        __onField("TAP_0311.TrackingPeriod.TrackingPeriod");    
        //logStdout("Parsed Leaf TrackingPeriod\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TransactionAuthCode_opt:                                                         
      TransactionAuthCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TransactionAuthCode:                                                             
      TAP_0311.TransactionAuthCode                                        
      {                                                                          
        __onField("TAP_0311.TransactionAuthCode.TransactionAuthCode");    
        //logStdout("Parsed Leaf TransactionAuthCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TransactionDescriptionSupp_opt:                                                         
      TransactionDescriptionSupp                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TransactionDescriptionSupp:                                                             
      TAP_0311.TransactionDescriptionSupp                                        
      {                                                                          
        __onField("TAP_0311.TransactionDescriptionSupp.TransactionDescriptionSupp");    
        //logStdout("Parsed Leaf TransactionDescriptionSupp\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TransactionDetailDescription_opt:                                                         
      TransactionDetailDescription                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TransactionDetailDescription:                                                             
      TAP_0311.TransactionDetailDescription                                        
      {                                                                          
        __onField("TAP_0311.TransactionDetailDescription.TransactionDetailDescription");    
        //logStdout("Parsed Leaf TransactionDetailDescription\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TransactionIdentifier_opt:                                                         
      TransactionIdentifier                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TransactionIdentifier:                                                             
      TAP_0311.TransactionIdentifier                                        
      {                                                                          
        __onField("TAP_0311.TransactionIdentifier.TransactionIdentifier");    
        //logStdout("Parsed Leaf TransactionIdentifier\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TransactionShortDescription_opt:                                                         
      TransactionShortDescription                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TransactionShortDescription:                                                             
      TAP_0311.TransactionShortDescription                                        
      {                                                                          
        __onField("TAP_0311.TransactionShortDescription.TransactionShortDescription");    
        //logStdout("Parsed Leaf TransactionShortDescription\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TransactionStatus_opt:                                                         
      TransactionStatus                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TransactionStatus:                                                             
      TAP_0311.TransactionStatus                                        
      {                                                                          
        __onField("TAP_0311.TransactionStatus.TransactionStatus");    
        //logStdout("Parsed Leaf TransactionStatus\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  TransferBatchError_opt:                                           
      TransferBatchError                                            
    |                                                              
    ;                                                              
                                                                   
  TransferBatchError:                                               
      RAP_0103.TransferBatchError                                 
      {                                                                   
        __onBlockStart("RAP_0103.TransferBatchError", false);   
        //logStdout("Parsed Sequence TransferBatchError\n");              
      }                                                                   
      errorDetail_TransferBatchError     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("RAP_0103.TransferBatchError");     
        //logStdout("TransferBatchError Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  errorDetail_TransferBatchError:                                                       
      {                                                                                 
        currBlock = "errorDetail";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ErrorDetailList_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  TransferCutOffTimeStamp_opt:                                           
      TransferCutOffTimeStamp                                            
    |                                                              
    ;                                                              
                                                                   
  TransferCutOffTimeStamp:                                               
      TAP_0311.TransferCutOffTimeStamp                                 
      {                                                                   
        __onBlockStart("TAP_0311.TransferCutOffTimeStamp", false);   
        //logStdout("Parsed Sequence TransferCutOffTimeStamp\n");              
      }                                                                   
      localTimeStamp_TransferCutOffTimeStamp     
      utcTimeOffset_TransferCutOffTimeStamp     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.TransferCutOffTimeStamp");     
        //logStdout("TransferCutOffTimeStamp Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  localTimeStamp_TransferCutOffTimeStamp:                                                       
      {                                                                                 
        currBlock = "localTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      LocalTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_TransferCutOffTimeStamp:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  TransparencyIndicator_opt:                                                         
      TransparencyIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  TransparencyIndicator:                                                             
      TAP_0311.TransparencyIndicator                                        
      {                                                                          
        __onField("TAP_0311.TransparencyIndicator.TransparencyIndicator");    
        //logStdout("Parsed Leaf TransparencyIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  UserProtocolIndicator_opt:                                                         
      UserProtocolIndicator                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  UserProtocolIndicator:                                                             
      TAP_0311.UserProtocolIndicator                                        
      {                                                                          
        __onField("TAP_0311.UserProtocolIndicator.UserProtocolIndicator");    
        //logStdout("Parsed Leaf UserProtocolIndicator\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  UtcTimeOffset_opt:                                                         
      UtcTimeOffset                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  UtcTimeOffset:                                                             
      TAP_0311.UtcTimeOffset                                        
      {                                                                          
        __onField("TAP_0311.UtcTimeOffset.UtcTimeOffset");    
        //logStdout("Parsed Leaf UtcTimeOffset\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  UtcTimeOffsetCode_opt:                                                         
      UtcTimeOffsetCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  UtcTimeOffsetCode:                                                             
      TAP_0311.UtcTimeOffsetCode                                        
      {                                                                          
        __onField("TAP_0311.UtcTimeOffsetCode.UtcTimeOffsetCode");    
        //logStdout("Parsed Leaf UtcTimeOffsetCode\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  UtcTimeOffsetInfo_opt:                                           
      UtcTimeOffsetInfo                                            
    |                                                              
    ;                                                              
                                                                   
  UtcTimeOffsetInfo:                                               
      TAP_0311.UtcTimeOffsetInfo                                 
      {                                                                   
        __onBlockStart("TAP_0311.UtcTimeOffsetInfo", false);   
        //logStdout("Parsed Sequence UtcTimeOffsetInfo\n");              
      }                                                                   
      utcTimeOffsetCode_UtcTimeOffsetInfo     
      utcTimeOffset_UtcTimeOffsetInfo     
      ASN1.BlockEnd                                                   
      {                                                            
        __onBlockEnd("TAP_0311.UtcTimeOffsetInfo");     
        //logStdout("UtcTimeOffsetInfo Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  utcTimeOffsetCode_UtcTimeOffsetInfo:                                                       
      {                                                                                 
        currBlock = "utcTimeOffsetCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetCode_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_UtcTimeOffsetInfo:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                        
  UtcTimeOffsetInfoList_opt:                                                                
      TAP_0311.UtcTimeOffsetInfoList                                               
      {                                                                                 
        __onBlockStart("TAP_0311.UtcTimeOffsetInfoList", true);                  
        //logStdout("Parsed List UtcTimeOffsetInfoList\n");                                
      }                                                                                 
      UtcTimeOffsetInfoList                                                                 
      ASN1.BlockEnd                                                                        
      {                                                                                 
        __onBlockEnd("TAP_0311.UtcTimeOffsetInfoList");                          
        //logStdout("UtcTimeOffsetInfoList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  UtcTimeOffsetInfoList:                                                                    
      UtcTimeOffsetInfoList                                                                 
      UtcTimeOffsetInfo_UtcTimeOffsetInfoList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  UtcTimeOffsetInfo_UtcTimeOffsetInfoList:                                                       
      {                                                                                 
        currBlock = "UtcTimeOffsetInfo";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffsetInfo                                                           
    ;                                                                                   
                                                                                 
  VerticalAccuracyDelivered_opt:                                                         
      VerticalAccuracyDelivered                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  VerticalAccuracyDelivered:                                                             
      TAP_0311.VerticalAccuracyDelivered                                        
      {                                                                          
        __onField("TAP_0311.VerticalAccuracyDelivered.VerticalAccuracyDelivered");    
        //logStdout("Parsed Leaf VerticalAccuracyDelivered\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  VerticalAccuracyRequested_opt:                                                         
      VerticalAccuracyRequested                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  VerticalAccuracyRequested:                                                             
      TAP_0311.VerticalAccuracyRequested                                        
      {                                                                          
        __onField("TAP_0311.VerticalAccuracyRequested.VerticalAccuracyRequested");    
        //logStdout("Parsed Leaf VerticalAccuracyRequested\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
}                                             
