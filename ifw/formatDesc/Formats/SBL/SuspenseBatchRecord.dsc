//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: SuspenseBatchRecord.dsc
//-------------------------------------------------------------------------------
//

SUSPENSE_BATCH_RECORD
{
  //----------------------------------------------------------------------------
  // Header record
  //----------------------------------------------------------------------------
  HEADER(SEPARATED)
  {
    Info
    {
      Pattern = "010.*\n";
      FieldSeparator = '\t';
      RecordSeparator = '\n';
    }
    
    RECORD_TYPE                         AscString();
    STORABLE_CLASS                      AscString();
  }

  //----------------------------------------------------------------------------
  // Detail record
  //----------------------------------------------------------------------------
  DETAIL(SEPARATED)
  {
    Info
    {
      Pattern = "020.*\n";
      FieldSeparator = '\t';
      RecordSeparator = '\n';
    }
    
    RECORD_TYPE                         AscString();
    SENDER                              AscString();
    BATCH_ID                            AscString();
    SEQUENCE_NUMBER                     AscInteger();
    BATCH_NAME                          AscString();
    SUSPENDED_BATCH_PATH                AscString();
    SUSPENDED_BATCH_NAME                AscString();
    PIPELINE_NAME                       AscString();
    PIPELINE_CATEGORY                   AscString();
    PIPELINE_ERROR_CODE                 AscInteger();
    SUSPENSE_REASON                     AscInteger();
    SUSPENSION_TIME                     AscDateUnix();
    RAP_FILE_SEQUENCE_NUMBER            AscInteger();
  }

  //----------------------------------------------------------------------------
  // Trailer Record
  //----------------------------------------------------------------------------
  // no trailer defined in suspense_create format

}
