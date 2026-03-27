//==============================================================================
//
//      Copyright (c) 1996 - 2009 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: EET.dsc
//-------------------------------------------------------------------------------
//

EET
{
  SEVERE_DETAIL(SEPARATED)
  {
    Info
    {
      States          = (EET);
      Pattern         = ".*\n";
      FieldSeparator  = ';';
      RecordSeparator = '\n';
    }
    
    TAP_FILE_SEQUENCE_NUMBER        AscInteger ();
    SENDER                          AscString  ();
    RECIPIENT                       AscString  ();
    PRIMARY_MSID                    AscString  ();
    SECONDARY_MSID                  AscString  ();
    CHARGING_START_TIMESTAMP        AscDateUnix();
  }

  FATAL_DETAIL(SEPARATED)
  {
    Info
    {
      States          = (EET);
      Pattern         = ".*\n";
      FieldSeparator  = ';';
      RecordSeparator = '\n';
    }
    
    TAP_FILE_SEQUENCE_NUMBER        AscInteger ();
    SENDER                          AscString  ();
    RECIPIENT                       AscString  ();
  }
}
