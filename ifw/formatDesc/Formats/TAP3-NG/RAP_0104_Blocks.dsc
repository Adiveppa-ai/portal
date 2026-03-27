RAP_0103
{
  AccountingInfoError(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 512; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  AckFileAvailableTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 515; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  AckFileCreationTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 516; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  Acknowledgement(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 535; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  AuditControlInfoError(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 513; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  BatchControlError(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 517; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  EndMissingSeqNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    EndMissingSeqNumber TAP_AsciiString(518, "Application"); 
  }                      
                         
  ErrorCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ErrorCode ASN_Integer(519, "Application"); 
  }                      
                         
  ErrorContext(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 545; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ErrorContextList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 549; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ErrorDetail(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 521; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ErrorDetailList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 520; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  FatalReturn(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 539; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ItemLevel(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ItemLevel ASN_Integer(548, "Application"); 
  }                      
                         
  ItemOccurrence(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ItemOccurrence ASN_Integer(547, "Application"); 
  }                      
                         
  ItemOffset(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ItemOffset ASN_Integer(524, "Application"); 
  }                      
                         
  MessageDescriptionError(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 522; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MessageDescriptionInfoList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 8; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MessageDescriptionInformationDefinition(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 143; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  MissingReturn(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 538; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  NetworkInfoError(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 523; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  NotificationError(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 552; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  OperatorSpecList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 551; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  PathItemId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    PathItemId ASN_Integer(546, "Application"); 
  }                      
                         
  RapAuditControlInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 541; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  RapBatchControlInfo(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 537; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  RapFileAvailableTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 525; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  RapFileCreationTimeStamp(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 526; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  RapReleaseVersionNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RapReleaseVersionNumber ASN_Integer(543, "Application"); 
  }                      
                         
  RapSpecificationVersionNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RapSpecificationVersionNumber ASN_Integer(544, "Application"); 
  }                      
                         
  ReturnBatch(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 534; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ReturnDetailList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 536; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  ReturnDetailsCount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ReturnDetailsCount ASN_Integer(528, "Application"); 
  }                      
                         
  RoamingPartner(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RoamingPartner TAP_AsciiString(550, "Application"); 
  }                      
                         
  SevereReturn(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 540; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            
  StartMissingSeqNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    StartMissingSeqNumber TAP_AsciiString(532, "Application"); 
  }                      
                         
  TotalSevereReturnTax(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalSevereReturnTax ASN_Integer(553, "Application"); 
  }                      
                         
  TotalSevereReturnValue(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TotalSevereReturnValue ASN_Integer(533, "Application"); 
  }                      
                         
  TransferBatchError(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 542; 
      EndRecord = ASN1.BlockEnd;               
    }                                       
  }                                         
                                            

}
