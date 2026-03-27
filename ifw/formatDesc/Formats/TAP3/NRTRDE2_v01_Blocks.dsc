//==============================================================================
// Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//
//------------------------------------------------------------------------------
// Block: FMD/TAP3
//------------------------------------------------------------------------------
// Module Description:
//   Description of the NRTRDE_0201 format
//
//------------------------------------------------------------------------------
//
//==============================================================================

NRTRDE_0201
{
  BlockEnd(FIX)
  {
    Info
    {
      Pattern = "\0\0";
    }
    dummy AscString(2);
  }

  FileEndFiller(FIX)
  {
    Info
    {
      Pattern = "\n";
    }
    dummy AscString(1);
  }

  FileFiller(FIX)
  {
    Info
    {
      Pattern = "\0";
    }
    dummy AscString(1);
  }

  AccessPointNameNI(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AccessPointNameNI TAP_AsciiString(16, "Application"); 
  }                      
                         
  AccessPointNameOI(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AccessPointNameOI TAP_AsciiString(17, "Application"); 
  }                      
                         
  AsciiString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    AsciiString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  BCDString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    BCDString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  BearerServiceCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    BearerServiceCode TAP_AsciiString(18, "Application"); 
  }                      
                         
  CallEventDuration(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallEventDuration ASN_Integer(19, "Application"); 
  }                      
                         
  CallEventList(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 2; 
      EndRecord = BlockEnd;               
    }                                       
  }                                         
                                            
  CallEventStartTimeStamp(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallEventStartTimeStamp TAP_AsciiString(21, "Application"); 
  }                      
                         
  CallEventsCount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallEventsCount ASN_Integer(20, "Application"); 
  }                      
                         
  CallReference(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallReference ASN_Integer(23, "Application"); 
  }                      
                         
  CallingNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CallingNumber TAP_AsciiString(22, "Application"); 
  }                      
                         
  CauseForTermination(ASN) 
  {                      
    Info                 
    {                    
    }                    
    CauseForTermination ASN_Integer(24, "Application"); 
  }                      
                         
  ChargeAmount(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargeAmount ASN_Integer(25, "Application"); 
  }                      
                         
  ChargingId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ChargingId ASN_Integer(26, "Application", 0, 8);
  }                      
                         
  ConnectedNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ConnectedNumber TAP_AsciiString(27, "Application"); 
  }                      
                         
  DataVolumeIncoming(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DataVolumeIncoming ASN_Integer(28, "Application"); 
  }                      
                         
  DataVolumeOutgoing(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DataVolumeOutgoing ASN_Integer(29, "Application"); 
  }                      
                         
  DialledDigits(ASN) 
  {                      
    Info                 
    {                    
    }                    
    DialledDigits TAP_AsciiString(30, "Application"); 
  }                      
                         
  FileAvailableTimeStamp(ASN) 
  {                      
    Info                 
    {                    
    }                    
    FileAvailableTimeStamp TAP_AsciiString(31, "Application"); 
  }                      
                         
  GgsnAddress(ASN) 
  {                      
    Info                 
    {                    
    }                    
    GgsnAddress TAP_AsciiString(32, "Application"); 
  }                      
                         
  Gprs(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 5; 
      EndRecord = BlockEnd;               
    }                                       
  }                                         
                                            
  HexString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    HexString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  Imei(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Imei ASN_BcdString(33, "Application"); 
  }                      
                         
  Imsi(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Imsi ASN_BcdString(34, "Application"); 
  }                      
                         
  Moc(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 3; 
      EndRecord = BlockEnd;               
    }                                       
  }                                         
                                            
  Mtc(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 4; 
      EndRecord = BlockEnd;               
    }                                       
  }                                         
                                            
  Nrtrde(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 1; 
      EndRecord = BlockEnd;               
    }                                       
  }                                         
                                            
  NumberString(ASN) 
  {                      
    Info                 
    {                    
    }                    
    NumberString TAP_AsciiString(4, "Universal"); 
  }                      
                         
  RecEntityId(ASN) 
  {                      
    Info                 
    {                    
    }                    
    RecEntityId TAP_AsciiString(35, "Application"); 
  }                      
                         
  Recipient(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Recipient TAP_AsciiString(36, "Application"); 
  }                      
                         
  ReleaseVersionNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ReleaseVersionNumber ASN_Integer(37, "Application"); 
  }                      
                         
  Sender(ASN) 
  {                      
    Info                 
    {                    
    }                    
    Sender TAP_AsciiString(38, "Application"); 
  }                      
                         
  SequenceNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SequenceNumber TAP_AsciiString(39, "Application"); 
  }                      
                         
  ServiceCode(ASN)                    
  {                                         
    Info                                    
    {                                       
      Application = 46; 
      EndRecord = BlockEnd;               
    }                                       
  }                                         
                                            
  SgsnAddress(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SgsnAddress TAP_AsciiString(40, "Application"); 
  }                      
                         
  SpecificationVersionNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SpecificationVersionNumber ASN_Integer(41, "Application"); 
  }                      
                         
  SupplementaryServiceCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    SupplementaryServiceCode TAP_AsciiString(42, "Application"); 
  }                      
                         
  TeleServiceCode(ASN) 
  {                      
    Info                 
    {                    
    }                    
    TeleServiceCode TAP_AsciiString(43, "Application"); 
  }                      
                         
  ThirdPartyNumber(ASN) 
  {                      
    Info                 
    {                    
    }                    
    ThirdPartyNumber TAP_AsciiString(44, "Application"); 
  }                      
                         
  UtcTimeOffset(ASN) 
  {                      
    Info                 
    {                    
    }                    
    UtcTimeOffset TAP_AsciiString(45, "Application"); 
  }                      
                         

}
