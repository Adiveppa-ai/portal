//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: SuspenseBatchRecord_OutMap.dsc
//-------------------------------------------------------------------------------
//

SUSPENSE_BATCH_RECORD
{
  //----------------------------------------------------------------------------
  // Header record
  //----------------------------------------------------------------------------
  HEADER 
  {
    STD_MAPPING
    {
      RECORD_TYPE                  <- "010";
      STORABLE_CLASS               <- "/suspended_batch/rapin";
    }
  }

  //----------------------------------------------------------------------------
  // Detail record
  //----------------------------------------------------------------------------
  DETAIL
  {
    STD_MAPPING
    {
      RECORD_TYPE                  <- "020";
      BATCH_ID                     <- DETAIL.BATCH_ID;

      BATCH_NAME                   <- DETAIL.ASS_SUSPENSE_EXT.SOURCE_FILENAME;
      SUSPENDED_BATCH_NAME         <- DETAIL.ASS_SUSPENSE_EXT.SOURCE_FILENAME;
      PIPELINE_NAME                <- DETAIL.ASS_SUSPENSE_EXT.PIPELINE_NAME;
      PIPELINE_CATEGORY            <- DETAIL.ASS_SUSPENSE_EXT.PIPELINE_CATEGORY;
      PIPELINE_ERROR_CODE          <- DETAIL.ASS_SUSPENSE_EXT.ERROR_CODE;
      SUSPENSE_REASON              <- DETAIL.ASS_SUSPENSE_EXT.SUSPENSE_REASON;

      SUSPENSION_TIME              <- DETAIL.ASS_ROAMING_EXT.SUSPENSION_TIME;
      SENDER                       <- DETAIL.ASS_ROAMING_EXT.SENDER;
      SEQUENCE_NUMBER              <- DETAIL.ASS_ROAMING_EXT.TAP_FILE_SEQ_NO;
      SUSPENDED_BATCH_PATH         <- DETAIL.ASS_ROAMING_EXT.TAP_FILE_PATH;
      RAP_FILE_SEQUENCE_NUMBER     <- DETAIL.ASS_ROAMING_EXT.RAP_FILE_SEQ_NO;
    }
  }
}
