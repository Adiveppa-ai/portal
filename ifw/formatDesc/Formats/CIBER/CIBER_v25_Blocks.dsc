//==============================================================================
//
// Copyright (c) 1996, 2014, Oracle and/or its affiliates. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD/CIBER
//------------------------------------------------------------------------------
// Module Description:
//   Description of the CIBER v 2.5 format.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: cdiab
//
// $RCSfile: CIBER_v25_Blocks.dsc $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: vinodrao $
// $Date: 2014/11/30 21:55:54 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: CIBER_v25_Blocks.dsc,v $
// Log 2002/07/12 cdiab
// -renaming of some fields which were too long
// -corrected description of the filler for every record type
//
// Revision 1.0  2002/04/15 13:54:55  cdiab
// -Creation
//
//==============================================================================

CIBER_V25
{


  //----------------------------------------------------------------------------
  // Header records
  //----------------------------------------------------------------------------

  BATCH_HEADER(FIX)
  {
    Info
    {
      Pattern = "01.{34}"; //"01.{198}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    BATCH_CREATION_DATE                 AscDate("%y%m%d");
    BATCH_SEQUENCE_NUMBER               AscInteger(3);
    SENDING_CARRIER_SID                 AscString(5);
    RECEIVING_CARRIER_SID               AscString(5);
    CIBER_RECORD_RELEASE_NUMBER         AscInteger(2);
    ORIGINAL_RETURN_INDICATOR           AscString(1);
    CURRENCY_TYPE                       AscString(2);
    SETTLEMENT_PERIOD                   AscString(6, '0', false);
//    SETTLEMENT_PERIOD                   AscDate("%y%m%d");
    CLEARINGHOUSE_ID                    AscString(1);
    CIBER_BATCH_REJECT_REASON_CODE      AscString(2);
    BATCH_CONTENTS                      AscString(1);
//  LOCAL_CARRIER_RESERVED              AscString(20);
//  SYSTEM_RESERVED_FILLER              AscString(144);
//  EOL                                 AscString(1);
  }

  BATCH_HEADER_CLEARINGHOUSE(FIX)
  {
    Info
    {
      Pattern = "02.{39}"; //"02.{198}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    BATCH_CREATION_DATE                 AscDate("%y%m%d");
    BATCH_SEQUENCE_NUMBER               AscInteger(3);
    SENDING_CLEARINGHOUSE_BID           AscString(5);
    ORIGINAL_SERVING_CARRIER_SID        AscString(5);
    CIBER_RECORD_RELEASE_NUMBER         AscInteger(2);
    ORIGINAL_RETURN_INDICATOR           AscString(1);
    CURRENCY_TYPE                       AscString(2);
    SETTLEMENT_PERIOD                   AscString(6, '0', false);
//    SETTLEMENT_PERIOD                   AscDate("%y%m%d");
    CLEARINGHOUSE_ID                    AscString(1);
    CIBER_BATCH_REJECT_REASON_CODE      AscString(2);
    ORIGINAL_HOME_CARRIER_SID           AscString(5);
    BATCH_CONTENTS                      AscString(1);
//  SYSTEM_RESERVED_FILLER              AscString(159);
//  EOL                                 AscString(1);
  }

  //----------------------------------------------------------------------------
  // Trailer records
  //----------------------------------------------------------------------------

  BATCH_TRAILER(FIX)
  {
    Info
    {
      Pattern = "98.{73}"; //"98.{198}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    BATCH_CREATION_DATE                 AscDate("%y%m%d");
    BATCH_SEQUENCE_NUMBER               AscInteger(3);
    SENDING_CARRIER_SID                 AscString(5);
    RECEIVING_CARRIER_SID               AscString(5);
    TOTAL_NUMBER_RECORDS                AscInteger(4);
    BATCH_TOTAL_CHARGE_AND_TAX          AscDecimal(12,false,2);
    SETTLEMENT_PERIOD                   AscString(6, '0', false);
//    SETTLEMENT_PERIOD                   AscDate("%y%m%d");
    CLEARINGHOUSE_ID                    AscString(1);
    R70_BATCH_TOTAL_CHARGE_TAX_SIGN     AscString(1);
    R70_ORIGINAL_TOTAL_CHARGE_TAX_SIGN  AscString(1);
    R70_SYSTEM_RESERVED_FILLER          AscString(3);
    ORIGINAL_TOTAL_NUMBER_RECORDS       AscInteger(4);
    ORIGINAL_TOTAL_CHARGE_AND_TAX       AscDecimal(12,false,2);
    SYSTEM_RESERVED_FILLER1             AscString(8);
    CURRENCY_TYPE                       AscString(2);
//  LOCAL_CARRIER_RESERVED              AscString(20);
//  SYSTEM_RESERVED_FILLER2             AscString(105);
//  EOL                                 AscString(1);
  }

  BATCH_TRAILER_CLEARINGHOUSE(FIX)
  {
    Info
    {
      Pattern = "97.{79}"; //"97.{198}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    BATCH_CREATION_DATE                 AscDate("%y%m%d");
    BATCH_SEQUENCE_NUMBER               AscInteger(3);
    SENDIND_CLEARINGHOUSE_BID           AscString(5);
    ORIGINAL_SERVING_CARRIER_SID        AscString(5);
    TOTAL_NUMBER_RECORDS                AscInteger(4);
    BATCH_TOTAL_CHARGE_AND_TAX          AscDecimal(12,false,2);
    SETTLEMENT_PERIOD                   AscString(6, '0', false);
//    SETTLEMENT_PERIOD                   AscDate("%y%m%d");
    CLEARINGHOUSE_ID                    AscString(1);
    R70_BATCH_TOTAL_CHARGE_TAX_SIGN     AscString(1);
    R70_ORIGINAL_TOTAL_CHARGE_TAX_SIGN  AscString(1);
    R70_SYSTEM_RESERVED_FILLER          AscString(3);
    ORIGINAL_HOME_CARRIER_SID           AscString(5);
    ORIGINAL_BATCH_SEQUENCE_NUMBER      AscInteger(3);
    ORIGINAL_BATCH_CREATION_DATE        AscDate("%y%m%d");
    ORIGINAL_TOTAL_NUMBER_RECORDS       AscInteger(4);
    ORIGINAL_TOTAL_CHARGE_AND_TAX       AscDecimal(12,false,2);
    CURRENCY_TYPE                       AscString(2);
//  SYSTEM_RESERVED_FILLER              AscString(119);
//  EOL                                 AscString(1);
  }

  //----------------------------------------------------------------------------
  // Different types of detailed records
  //----------------------------------------------------------------------------

  RECORD_10(FIX)
  {
    Info
    {
      Pattern = "10.{256}"; //"10.{256}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MOBILE_ID_NO_LENGTH                 AscInteger(2);
    MOBILE_ID_NO                        AscString(10, '0', true);
    MOBILE_ID_NO_OVERFLOW               AscString(5,  '0', true);
    ELECTRONIC_SERIAL_NO                AscString(11, '0', true);
    CALL_DATE                           AscDate("%y%m%d");
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(11,false,2);
    TOTAL_STATE_TAX                     AscDecimal(11,false,2);
    TOTAL_LOCAL_TAX                     AscDecimal(11,false,2);
    CALL_DIRECTION                      AscString(1);
    CALL_COMPLETION_INDICATOR           AscString(1);
    CALL_TERMINATION_INDICATOR          AscString(1);
    CALLED_NO_LENGTH                    AscInteger(2);
    CALLED_NO                           AscString(10, '0', true);
    CALLED_NO_OVERFLOW                  AscString(5 , '0', true);
    TEMP_LOCAL_DIRECTORY_NO             AscString(10, '0', true);
    CURRENCY_TYPE                       AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(3, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    MSG_ACCOUNTING_DIGITS               AscString(10, '0', true);
    SSU_CONNECT_TIME                    AscDate("%H%M%S");
    SSU_CHARGEABLE_TIME                 AscString(6, '0', false);
    SSU_ELAPSED_TIME                    AscString(6, '0', false);
    SSU_RATE_PERIOD                     AscString(2, '0', false);
    SSU_MULTIRATE_PERIOD                AscString(1, '0', false);
    SSU_CHARGE                          AscDecimal(11,false,2);
    MISC_SURCHARGE                      AscDecimal(11,false,2);
    MISC_SURCHARGE_DESC                 AscString(1, '0', false);
    PRINTED_CALL                        AscString(15);
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
    FILLER1                             AscString(11);
    LOCAL_CARRIER_RESERVED              AscString(20);
    SPECIAL_FEATURES_USED               AscString(5);
    CALLED_PLACE                        AscString(10);
    CALLED_STATE                        AscString(2); 
    SERVING_PLACE                       AscString(10);
    SERVING_STATE                       AscString(2);
//  EOL                                 AscString(1);
  }

  RECORD_11(FIX)
  {
    Info
    {
      Pattern = "11.{264}"; //"11.{310}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    RECV_CARRIER_SID                    AscString(5);
    MOBILE_ID_NO_LENGTH                 AscInteger(2);
    MOBILE_ID_NO                        AscString(10, '0', true);
    MOBILE_ID_NO_OVERFLOW               AscString(5,  '0', true);
    TRANS_CODE1                         AscString(8, '0', false);
    TRANS_CODE2                         AscString(2, '0', false);
    FILLER1                             AscString(1);
    CALL_DATE                           AscDate("%y%m%d");    
    SENDING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(11,false,2);
    TOTAL_STATE_TAX                     AscDecimal(11,false,2);
    TOTAL_LOCAL_TAX                     AscDecimal(11,false,2);
    MISC_SURCHARGE                      AscDecimal(11,false,2);
    MISC_SURCHARGE_DESC                 AscString(1, '0', false);
    FILLER2                             AscString(18, '0', true); //zero fill
    CURRENCY_TYPE                       AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(3, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    CHARGE_NO_1_IND                     AscString(2, '0', false);
    CHARGE_NO_1_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_1_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_1_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_1_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_1_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_1                         AscDecimal(11,false,2);
    CHARGE_NO_2_IND                     AscString(2, '0', false);
    CHARGE_NO_2_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_2_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_2_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_2_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_2_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_2                         AscDecimal(11,false,2);
    CHARGE_NO_3_IND                     AscString(2, '0', false);
    CHARGE_NO_3_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_3_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_3_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_3_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_3_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_3                         AscDecimal(11,false,2);
    CHARGE_NO_4_IND                     AscString(2, '0', false);
    CHARGE_NO_4_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_4_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_4_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_4_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_4_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_4                         AscDecimal(11,false,2);
    CHARGE_NO_1_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_2_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_3_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_4_SURCHARGE_IND           AscString(1, '0', false);
//  FILLER3                             AscString(26);
//  LOCAL_CARRIER_RESERVED              AscString(20);
//  EOL                                 AscString(1);
  }

  RECORD_20(FIX)
  {
    Info
    {
      Pattern = "20.{324}"; //"20.{324}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MOBILE_ID_NO_LENGTH                 AscInteger(2);
    MOBILE_ID_NO                        AscString(10, '0', true);
    MOBILE_ID_NO_OVERFLOW               AscString(5,  '0', true);
    ELECTRONIC_SERIAL_NO                AscString(11, '0', true);
    CALL_DATE                           AscDate("%y%m%d");    
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(11,false,2);
    TOTAL_STATE_TAX                     AscDecimal(11,false,2);
    TOTAL_LOCAL_TAX                     AscDecimal(11,false,2);
    CALL_DIRECTION                      AscString(1);
    CALL_COMPLETION_INDICATOR           AscString(1);
    CALL_TERMINATION_INDICATOR          AscString(1);
    CALLED_NO_LENGTH                    AscInteger(2);
    CALLED_NO                           AscString(10, '0', true);
    CALLED_NO_OVERFLOW                  AscString(5 , '0', true);
    TEMP_LOCAL_DIRECTORY_NO             AscString(10, '0', true);
    CURRENCY_TYPE                       AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(3, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    MSG_ACCOUNTING_DIGITS               AscString(10, '0', true);
    SSU_CONNECT_TIME                    AscDate("%H%M%S");
    SSU_CHARGEABLE_TIME                 AscString(6, '0', false);
    SSU_ELAPSED_TIME                    AscString(6, '0', false);
    SSU_RATE_PERIOD                     AscString(2, '0', false);
    SSU_MULTIRATE_PERIOD                AscString(1, '0', false);
    SSU_CHARGE                          AscDecimal(11,false,2);
    MISC_SURCHARGE                      AscDecimal(11,false,2);
    MISC_SURCHARGE_DESC                 AscString(1, '0', false);
    PRINTED_CALL                        AscString(15);
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
    FILLER1                             AscString(11);
    LOCAL_CARRIER_RESERVED              AscString(20);
    SPECIAL_FEATURES_USED               AscString(5);
    CALLED_PLACE                        AscString(10);
    CALLED_STATE                        AscString(2); 
    SERVING_PLACE                       AscString(10);
    SERVING_STATE                       AscString(2); 
    TOLL_CONNECT_TIME                   AscDate("%H%M%S");
    TOLL_CHARGEABLE_TIME                AscString(6, '0', false);
    TOLL_ELAPSED_TIME                   AscString(6, '0', false);
    TOLL_TARIFF_DESC                    AscString(2, '0', false);
    TOLL_RATE_PERIOD                    AscString(2, '0', false);
    TOLL_MULTIRATE_PERIOD               AscString(1, '0', false);
    TOLL_RATE_CLASS                     AscString(1, '0', false);
    TOLL_FROM_RATING_NPA_NXX            AscString(6, '0', true);
    TOLL_CHARGE                         AscDecimal(11,false,2);
    TOLL_STATE_TAX                      AscDecimal(11,false,2);
    TOLL_LOCAL_TAX                      AscDecimal(11,false,2);
    TOLL_NETWORK_CARRIER_ID             AscString(5, '0', false);
//  EOL                                 AscString(1);
 }

  RECORD_22(FIX)
  {
    Info
    {
      Pattern = "22.{395}"; //"22.{545}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MSID_INDICATOR                      AscString(1);
    MSID                                AscString(15, '0', true);
    MSISDN_MDN_LENGTH                   AscInteger(2);
    MSISDN_MDN                          AscString(15, '0', true);
    ESN_IMEI_INDICATOR                  AscString(1,  '0', false);
    ESN_IMEI                            AscString(19, '0', true);
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(10,false,2);
    FILLER1                             AscString(1);
    TOTAL_STATE_TAX                     AscDecimal(10,false,2);
    FILLER2                             AscString(1);
    TOTAL_LOCAL_TAX                     AscDecimal(10,false,2);
    FILLER3                             AscString(1);
    CALL_DATE                           AscDate("%y%m%d");    
    CALL_DIRECTION                      AscString(1);
    CALL_COMPLETION_INDICATOR           AscString(1);
    CALL_TERMINATION_INDICATOR          AscString(1);
    CALLER_ID_LENGTH                    AscInteger(2);
    CALLER_ID                           AscString(15, '0', true);
    CALLED_NO_LENGTH                    AscInteger(2);
    CALLED_NO                           AscString(15, '0', true);
    ROUTING_NO_LENGTH                   AscInteger(2);
    ROUTING_NO                          AscString(15, '0', true);   
    TLDN_NO_LENGTH                      AscInteger(2);
    TLDN_NO                             AscString(15, '0', true);   
    CURRENCY_TYPE                       AscString(2);
    FILLER4                             AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(11, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    MSG_ACCOUNTING_DIGITS               AscString(10, '0', true);
    AIR_CONNECT_TIME                    AscDate("%H%M%S");
    AIR_CHARGEABLE_TIME                 AscString(6, '0', false);
    AIR_ELAPSED_TIME                    AscString(6, '0', false);
    AIR_RATE_PERIOD                     AscString(2, '0', false);
    AIR_MULTIRATE_PERIOD                AscString(1, '0', false);
    AIR_CHARGE                          AscDecimal(10,false,2);
    FILLER5                             AscString(1);
    OTHER_CHARGE_1_INDICATOR            AscString(2, '0', false);
    OTHER_CHARGE_1                      AscDecimal(10,false,2);
    FILLER6                             AscString(1);
    FILLER7                             AscString(13);
    PRINTED_CALL                        AscString(15);
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
    SPECIAL_FEATURES_USED               AscString(5);
    CALLED_PLACE                        AscString(10);
    CALLED_STATE                        AscString(2); 
    CALLED_COUNTRY                      AscString(3); 
    SERVING_PLACE                       AscString(10);
    SERVING_STATE                       AscString(2); 
    SERVING_COUNTRY                     AscString(3); 
    TOLL_CONNECT_TIME                   AscDate("%H%M%S");
    TOLL_CHARGEABLE_TIME                AscString(6, '0', false);
    TOLL_ELAPSED_TIME                   AscString(6, '0', false);
    TOLL_TARIFF_DESC                    AscString(2, '0', false);
    TOLL_RATE_PERIOD                    AscString(2, '0', false);
    TOLL_MULTIRATE_PERIOD               AscString(1, '0', false);
    TOLL_RATE_CLASS                     AscString(1, '0', false);
    TOLL_RATING_POINT_LENGTH            AscInteger(2);
    TOLL_RATING_POINT                   AscString(10, '0', true);
    TOLL_CHARGE                         AscDecimal(10,false,2);
    FILLER8                             AscString(1);
    TOLL_STATE_TAX                      AscDecimal(10,false,2);
    FILLER9                             AscString(1);
    TOLL_LOCAL_TAX                      AscDecimal(10,false,2);
    FILLER10                            AscString(1);
    TOLL_NETWORK_CARRIER_ID             AscString(5, '0', false);
//  LOCAL_CARRIER_RESERVED              AscString(75);
//  FILLER12                            AscString(75);
//  EOL                                 AscString(1);
  }


  RECORD_30(FIX)
  {
    Info
    {
      Pattern = "30.{322}"; //"30.{349}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MOBILE_ID_NO_LENGTH                 AscInteger(2);
    MOBILE_ID_NO                        AscString(10, '0', true);
    MOBILE_ID_NO_OVERFLOW               AscString(5,  '0', true);
    ELECTRONIC_SERIAL_NO                AscString(11, '0', true);
    CALL_DATE                           AscDate("%y%m%d");    
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(11,false,2);
    TOTAL_STATE_TAX                     AscDecimal(11,false,2);
    TOTAL_LOCAL_TAX                     AscDecimal(11,false,2);
    CALL_DIRECTION                      AscString(1);
    CALL_COMPLETION_INDICATOR           AscString(1);
    CALL_TERMINATION_INDICATOR          AscString(1);
    CALLED_NO_LENGTH                    AscInteger(2);
    CALLED_NO                           AscString(10, '0', true);
    CALLED_NO_OVERFLOW                  AscString(5 , '0', true);
    TEMP_LOCAL_DIRECTORY_NO             AscString(10, '0', true);
    CURRENCY_TYPE                       AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(3, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    MSG_ACCOUNTING_DIGITS               AscString(10, '0', true);
    CHARGE_NO_1_IND                     AscString(2, '0', false);
    CHARGE_NO_1_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_1_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_1_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_1_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_1_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_1                         AscDecimal(11,false,2);
    CHARGE_NO_2_IND                     AscString(2, '0', false);
    CHARGE_NO_2_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_2_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_2_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_2_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_2_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_2                         AscDecimal(11,false,2);
    CHARGE_NO_3_IND                     AscString(2, '0', false);
    CHARGE_NO_3_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_3_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_3_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_3_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_3_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_3                         AscDecimal(11,false,2);
    CHARGE_NO_4_IND                     AscString(2, '0', false);
    CHARGE_NO_4_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_4_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_4_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_4_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_4_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_4                         AscDecimal(11,false,2);
    SERVING_PLACE                       AscString(10);
    SERVING_STATE                       AscString(2); 
    SPECIAL_FEATURES_USED               AscString(5);
    MISC_SURCHARGE                      AscDecimal(11,false,2);
    MISC_SURCHARGE_DESC                 AscString(1, '0', false);
    PRINTED_CALL                        AscString(15);
    FEATURE_USED_AFTER_HO_IND           AscString(1, '0', false);
    CHARGE_NO_1_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_2_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_3_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_4_SURCHARGE_IND           AscString(1, '0', false);
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
//  FILLER1                             AscString(7);
//  LOCAL_CARRIER_RESERVED              AscString(20);
//  EOL                                 AscString(1);
  }


  RECORD_32(FIX)
  {
    Info
    {
      Pattern = "32.{415}"; //"32.{565}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MSID_INDICATOR                      AscString(1);
    MSID                                AscString(15, '0', true);
    MSISDN_MDN_LENGTH                   AscInteger(2);
    MSISDN_MDN                          AscString(15, '0', true);
    ESN_IMEI_INDICATOR                  AscString(1,  '0', false);
    ESN_IMEI                            AscString(19, '0', true);
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(10,false,2);
    FILLER1                             AscString(1);
    TOTAL_STATE_TAX                     AscDecimal(10,false,2);
    FILLER2                             AscString(1);
    TOTAL_LOCAL_TAX                     AscDecimal(10,false,2);
    FILLER3                             AscString(1);
    CALL_DATE                           AscDate("%y%m%d");    
    CALL_DIRECTION                      AscString(1);
    CALL_COMPLETION_INDICATOR           AscString(1);
    CALL_TERMINATION_INDICATOR          AscString(1);
    CALLER_ID_LENGTH                    AscInteger(2);
    CALLER_ID                           AscString(15, '0', true);
    CALLED_NO_LENGTH                    AscInteger(2);
    CALLED_NO                           AscString(15, '0', true);
    ROUTING_NO_LENGTH                   AscInteger(2);
    ROUTING_NO                          AscString(15, '0', true);   
    TLDN_NO_LENGTH                      AscInteger(2);
    TLDN_NO                             AscString(15, '0', true);   
    CURRENCY_TYPE                       AscString(2);
    FILLER4                             AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(11, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    MSG_ACCOUNTING_DIGITS               AscString(10, '0', true);
    CHARGE_NO_1_IND                     AscString(2, '0', false);
    CHARGE_NO_1_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_1_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_1_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_1_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_1_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_1_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_1                         AscDecimal(10,false,2);
    FILLER5                             AscString(1);
    CHARGE_NO_2_IND                     AscString(2, '0', false);
    CHARGE_NO_2_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_2_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_2_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_2_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_2_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_2_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_2                         AscDecimal(10,false,2);
    FILLER6                             AscString(1);
    CHARGE_NO_3_IND                     AscString(2, '0', false);
    CHARGE_NO_3_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_3_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_3_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_3_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_3_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_3_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_3                         AscDecimal(10,false,2);
    FILLER7                             AscString(1);
    CHARGE_NO_4_IND                     AscString(2, '0', false);
    CHARGE_NO_4_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_4_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_4_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_4_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_4_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_4_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_4                         AscDecimal(10,false,2);
    FILLER8                             AscString(1);
    SERVING_PLACE                       AscString(10);
    SERVING_STATE                       AscString(2);
    SERVING_COUNTRY                     AscString(3); 
    SPECIAL_FEATURES_USED               AscString(5);
    OTHER_CHARGE_1_INDICATOR            AscString(2, '0', false);
    OTHER_CHARGE_1                      AscDecimal(10,false,2);
    FILLER9                             AscString(1);
    FILLER10                            AscString(13);
    PRINTED_CALL                        AscString(15);
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
    FEATURE_USED_AFTER_HO_IND           AscString(1, '0', false);
//  LOCAL_CARRIER_RESERVED              AscString(75);
//  FILLER11                            AscString(75);
//  EOL                                 AscString(1);
  }

  RECORD_42(FIX)
  {
    Info
    {
      Pattern = "42.{309}"; //"42.{460}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    RECV_CARRIER_SID                    AscString(5);
    MSID_INDICATOR                      AscString(1);
    MSID                                AscString(15, '0', true);
    MSISDN_MDN_LENGTH                   AscInteger(2);
    MSISDN_MDN                          AscString(15, '0', true);
    TRANS_CODE1                         AscString(8);
    TRANS_CODE2                         AscString(2);
    FILLER1                             AscString(10);
    SENDING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(10,false,2);
    FILLER2                             AscString(1);
    TOTAL_STATE_TAX                     AscDecimal(10,false,2);
    FILLER3                             AscString(1);
    TOTAL_LOCAL_TAX                     AscDecimal(10,false,2);
    FILLER4                             AscString(1);
    CALL_DATE                           AscDate("%y%m%d");     
    ROUTING_NO_LENGTH                   AscInteger(2);
    ROUTING_NO                          AscString(15, '0', true);   
    CURRENCY_TYPE                       AscString(2);
    FILLER5                             AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(11, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    OTHER_CHARGE_1_INDICATOR            AscString(2, '0', false);
    OTHER_CHARGE_1                      AscDecimal(10,false,2);
    FILLER6                             AscString(1);
    FILLER7                             AscString(13);
    CHARGE_NO_1_IND                     AscString(2, '0', false);
    CHARGE_NO_1_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_1_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_1_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_1_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_1_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_1_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_1                         AscDecimal(10,false,2);
    FILLER8                             AscString(1);
    CHARGE_NO_2_IND                     AscString(2, '0', false);
    CHARGE_NO_2_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_2_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_2_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_2_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_2_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_2_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_2                         AscDecimal(10,false,2);
    FILLER9                             AscString(1);
    CHARGE_NO_3_IND                     AscString(2, '0', false);
    CHARGE_NO_3_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_3_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_3_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_3_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_3_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_3_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_3                         AscDecimal(10,false,2);
    FILLER10                            AscString(1);
    CHARGE_NO_4_IND                     AscString(2, '0', false);
    CHARGE_NO_4_CONNECT_TIME            AscDate("%H%M%S");
    CHARGE_NO_4_CHARGEABLE_TIME         AscString(6, '0', false);
    CHARGE_NO_4_ELAPSED_TIME            AscString(6, '0', false);
    CHARGE_NO_4_RATE_PERIOD             AscString(2, '0', false);
    CHARGE_NO_4_MULTIRATE_PERIOD        AscString(1, '0', false);
    CHARGE_NO_4_SURCHARGE_IND           AscString(1, '0', false);
    CHARGE_NO_4                         AscDecimal(10,false,2);
//  FILLER11                            AscString(1);
//  LOCAL_CARRIER_RESERVED              AscString(75);
//  FILLER12                            AscString(75);
//  EOL                                 AscString(1);
  }


  RECORD_50(FIX)
  {
    Info
    {
      Pattern = "50.{191}"; //"50.{226}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MOBILE_ID_NO_LENGTH                 AscInteger(2);
    MOBILE_ID_NO                        AscString(10, '0', true);
    MOBILE_ID_NO_OVERFLOW               AscString(5,  '0', true);
    ELECTRONIC_SERIAL_NO                AscString(11, '0', true);
    OCC_START_DATE                      AscDate("%y%m%d");    
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(11,false,2);
    TOTAL_STATE_TAX                     AscDecimal(11,false,2);
    TOTAL_LOCAL_TAX                     AscDecimal(11,false,2);
    OCC_CHARGE                          AscDecimal(11,false,2);
    FET_EXEMPT_INDICATOR                AscString(1);
    PASS_THROUGH_CHARGE_IND             AscString(1);
    CURRENCY_TYPE                       AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(3, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    MSG_ACCOUNTING_DIGITS               AscString(10, '0', true);
    CONNECT_TIME                        AscDate("%H%M%S");
    RECORD_USE_INDICATOR                AscString(1, '0', false);
    OCC_DESCRIPTION                     AscString(25);
    SERVING_PLACE                       AscString(10);
    SERVING_STATE                       AscString(2); 
    MISC_SURCHARGE                      AscDecimal(11,false,2);
    MISC_SURCHARGE_DESC                 AscString(1, '0', false);
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
    OCC_END_DATE                        AscDate("%y%m%d");
    RECORD_CREATE_DATE                  AscDate("%y%m%d");
    SEQ_INDICATOR                       AscString(2, '0', false);
    OCC_INTERVAL_INDICATOR              AscString(1, '0', false);
//  LOCAL_CARRIER_RESERVED              AscString(20);
//  FILLER                              AscString(15);
//  EOL                                 AscString(1);
  }

  RECORD_52(FIX)
  {
    Info
    {
      Pattern = "52.{241}"; //"52.{391}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MSID_INDICATOR                      AscString(1);
    MSID                                AscString(15, '0', true);
    MSISDN_MDN_LENGTH                   AscInteger(2);
    MSISDN_MDN                          AscString(15, '0', true);
    ESN_IMEI_INDICATOR                  AscString(1,  '0', false);
    ESN_IMEI                            AscString(19, '0', true);
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(10,false,2);
    FILLER1                             AscString(1);
    TOTAL_STATE_TAX                     AscDecimal(10,false,2);
    FILLER2                             AscString(1);
    TOTAL_LOCAL_TAX                     AscDecimal(10,false,2);
    FILLER3                             AscString(1);
    OCC_START_DATE                      AscDate("%y%m%d");    
    CONNECT_TIME                        AscDate("%H%M%S");
    OCC_END_DATE                        AscDate("%y%m%d"); 
    OCC_INTERVAL_INDICATOR              AscString(1, '0', false);   
    OCC_CHARGE                          AscDecimal(10,false,2);
    FILLER4                             AscString(1);
    OCC_DESCRIPTION                     AscString(25);
    CURRENCY_TYPE                       AscString(2);
    FILLER5                             AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    INITIAL_CELL_SITE                   AscString(11, '0', false);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
    MSG_ACCOUNTING_DIGITS               AscString(10, '0', true);
    RECORD_USE_INDICATOR                AscString(1, '0', false);
    SERVING_PLACE                       AscString(10);
    SERVING_STATE                       AscString(2);
    SERVING_COUNTRY                     AscString(3);
    OTHER_CHARGE_1_INDICATOR            AscString(2, '0', false);
    OTHER_CHARGE_1                      AscDecimal(10,false,2);
    FILLER6                             AscString(1);
    FILLER7                             AscString(13);
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
    RECORD_CREATE_DATE                  AscDate("%y%m%d");
    SEQ_INDICATOR                       AscString(2, '0', false);
//  LOCAL_CARRIER_RESERVED              AscString(75);
//  FILLER8                             AscString(75);
//  EOL                                 AscString(1);
  }

  RECORD_70(FIX)
  {
    Info
    {
      Pattern = "70.{103}"; //"70.{349}\n";
      States = (STATE_CIBERV25);
      SuccState = STATE_EXPECT_FILLER;
    }
    CIBER_RECORD_TYPE                   AscString(2, '0', false);
    RETURN_CODE                         AscString(1, '0', false);
    RETURN_REASON_CODE                  AscString(2, '0', false);
    INVALID_FIELD_ID                    AscString(3, '0', false);
    HOME_CARRIER_SID                    AscString(5);
    MOBILE_ID_NO_LENGTH                 AscInteger(2);
    MOBILE_ID_NO                        AscString(10, '0', true);
    MOBILE_ID_NO_OVERFLOW               AscString(5,  '0', true);
    ELECTRONIC_SERIAL_NO                AscString(11, '0', true);
    EVENT_DATE                          AscDate("%y%m%d");    
    SERVING_CARRIER_SID                 AscString(5);
    TOTAL_CHARGE_AND_TAX                AscDecimal(11,false,2);
    TOTAL_STATE_TAX                     AscDecimal(11,false,2);
    TOTAL_LOCAL_TAX                     AscDecimal(11,false,2);
    MIN_ESN_APP_INDICATOR               AscString(1);
    R70_RECORD_USE_INDICATOR            AscString(2, '0', false);
    CURRENCY_TYPE                       AscString(2);
    ORIG_BATCH_SEQ_NO                   AscString(3);
    EVENT_TIME                          AscDate("%H%M%S");
    FRAUD_INDICATOR                     AscString(2);
    FRAUD_SUB_INDICATOR                 AscString(1);
    TIME_ZONE_INDICATOR                 AscString(2);
    DAYLIGHT_SAVINGS_INDICATOR          AscString(1);
//  FILLER1                             AscString(24);
//  FILLER2                             AscString(222);
//  EOL                                 AscString(1);
  }
  
  //----------------------------------------------------------------------------
  // Filler for optional fields
  //----------------------------------------------------------------------------

  CIBER_FILLER(SEPARATED)
  {
    Info
    {
      Pattern = ".*\n";
      FieldSeparator = ',';   // no impact as there is only one field
      RecordSeparator = '\n';
      States = (STATE_EXPECT_FILLER);
      SuccState = STATE_CIBERV25;
    }
    FILLER                              AscString();
  }
}
