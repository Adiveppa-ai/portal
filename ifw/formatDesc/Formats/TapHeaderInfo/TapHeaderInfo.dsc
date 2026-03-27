//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: TapHeaderInfo.dsc
//-------------------------------------------------------------------------------
//

TapHeaderInfo
{
  UTCOFFSET(SEPARATED)
  {
    Info
    {
      Pattern         = "UTC.*\n";
      FieldSeparator  = ';';
      RecordSeparator = '\n';
    }

    RECORD_TYPE       AscString ();
    UTCTIMEOFFSETCODE AscInteger();
    UTCTIMEOFFSET     AscString ();
  }

  RECENTITY(SEPARATED)
  {
    Info
    {
      Pattern         = "REC.*\n";
      FieldSeparator  = ';';
      RecordSeparator = '\n';
    }
    
    RECORD_TYPE       AscString ();
    RECENTITYCODE     AscInteger();
    RECENTITYTYPE     AscInteger();
    RECENTITYID       AscString ();
  }
}
