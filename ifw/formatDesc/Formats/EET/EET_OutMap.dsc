//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: EET_OutMap.dsc
//-------------------------------------------------------------------------------
//

EET
{
  SEVERE_DETAIL
  {
    STD_MAPPING
    {
      SENDER                      <- DETAIL.ASS_ROAMING_EXT.RECIPIENT;
      RECIPIENT                   <- DETAIL.ASS_ROAMING_EXT.SENDER;
      TAP_FILE_SEQUENCE_NUMBER    <- DETAIL.ASS_ROAMING_EXT.TAP_FILE_SEQ_NO;
      PRIMARY_MSID                <- DETAIL.A_NUMBER;
      SECONDARY_MSID              <- DETAIL.ASS_ROAMING_EXT.PORT_NUMBER;
      CHARGING_START_TIMESTAMP    <- DETAIL.CHARGING_START_TIMESTAMP;
    }
  }

  FATAL_DETAIL
  {
    STD_MAPPING
    {
      SENDER                      <- DETAIL.ASS_ROAMING_EXT.RECIPIENT;
      RECIPIENT                   <- DETAIL.ASS_ROAMING_EXT.SENDER;
      TAP_FILE_SEQUENCE_NUMBER    <- DETAIL.ASS_ROAMING_EXT.TAP_FILE_SEQ_NO;
    }
  }
}
