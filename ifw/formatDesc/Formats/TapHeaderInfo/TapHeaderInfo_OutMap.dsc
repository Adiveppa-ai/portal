//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: TapHeaderInfo_OutMap.dsc
//-------------------------------------------------------------------------------
//

TapHeaderInfo
{
  UTCOFFSET
  {
    STD_MAPPING
    {
      RECORD_TYPE          <- "UTC";
      UTCTIMEOFFSETCODE    <- TRAILER.ASS_UTCOFFSET.UTCTIMEOFFSETCODE;
      UTCTIMEOFFSET        <- TRAILER.ASS_UTCOFFSET.UTCTIMEOFFSET;
    }
  }

  RECENTITY
  {
    STD_MAPPING
    {
      RECORD_TYPE          <- "REC";
      RECENTITYCODE        <- TRAILER.ASS_RECENTITY.RECENTITYCODE;
      RECENTITYTYPE        <- TRAILER.ASS_RECENTITY.RECENTITYTYPE;
      RECENTITYID          <- TRAILER.ASS_RECENTITY.RECENTITYID;
    }
  }
}
