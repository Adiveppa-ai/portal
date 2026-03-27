--
-- @(#)item_t.ctl 3
--
-- Copyright (c) 2023, Oracle and/or its affiliates.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
LOAD DATA
APPEND
   INTO TABLE ITEM_T
   (
	ACCOUNT_OBJ_DB                   INTEGER EXTERNAL TERMINATED BY ',',
	ACCOUNT_OBJ_ID0                  INTEGER EXTERNAL TERMINATED BY ',',
	BILLINFO_OBJ_DB                  INTEGER EXTERNAL TERMINATED BY ',',
	BILLINFO_OBJ_ID0                 INTEGER EXTERNAL TERMINATED BY ',',
	BILL_OBJ_DB                      INTEGER EXTERNAL TERMINATED BY ',',
	BILL_OBJ_ID0                     INTEGER EXTERNAL TERMINATED BY ',',	
	BILL_OBJ_TYPE			 CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	AR_BILLINFO_OBJ_DB               INTEGER EXTERNAL TERMINATED BY ',',
	AR_BILLINFO_OBJ_ID0              INTEGER EXTERNAL TERMINATED BY ',',
	AR_BILL_OBJ_DB                   INTEGER EXTERNAL TERMINATED BY ',',
	AR_BILL_OBJ_TYPE		 CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	AR_BILL_OBJ_ID0                  INTEGER EXTERNAL TERMINATED BY ',',
	CREATED_T                        INTEGER EXTERNAL TERMINATED BY ',',
	MOD_T				 INTEGER EXTERNAL TERMINATED BY ',',
	EFFECTIVE_T			 INTEGER EXTERNAL TERMINATED BY ',',	
	CURRENCY                         INTEGER EXTERNAL TERMINATED BY ',',	
	POID_DB                          INTEGER EXTERNAL TERMINATED BY ',',
	POID_ID0                         INTEGER EXTERNAL TERMINATED BY ',',
	POID_TYPE                        CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	ITEM_CLASS			 INTEGER EXTERNAL TERMINATED BY ',',
	AR_ITEM_OBJ_DB			 INTEGER EXTERNAL TERMINATED BY ',',
	AR_ITEM_OBJ_ID0			 INTEGER EXTERNAL TERMINATED BY ',',
	AR_ITEM_OBJ_TYPE		 CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	SERVICE_OBJ_DB                   INTEGER EXTERNAL TERMINATED BY ',',
	SERVICE_OBJ_ID0                  INTEGER EXTERNAL TERMINATED BY ',',
	SERVICE_OBJ_TYPE                 CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	BAL_GRP_OBJ_DB                   INTEGER EXTERNAL TERMINATED BY ',',
	BAL_GRP_OBJ_ID0                  INTEGER EXTERNAL TERMINATED BY ',',
	BAL_GRP_OBJ_TYPE                 CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	BAL_GRP_OBJ_REV                  INTEGER EXTERNAL TERMINATED BY ',',
	NAME				 CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	STATUS				 INTEGER EXTERNAL TERMINATED BY ',',
	DUE				 INTEGER EXTERNAL TERMINATED BY ',',
	RECVD				 INTEGER EXTERNAL TERMINATED BY ',',
	ITEM_TOTAL			 INTEGER EXTERNAL TERMINATED BY ',',

-- Constant Values
	ACCOUNT_OBJ_TYPE                 CONSTANT '/account',
	ACCOUNT_OBJ_REV                  CONSTANT '0',
	ADJUSTED                         CONSTANT '0',
	AR_BILLINFO_OBJ_TYPE             CONSTANT '/billinfo',
	AR_BILLINFO_OBJ_REV              CONSTANT '0',
	AR_BILL_OBJ_REV                  CONSTANT '0', 
	AR_ITEM_OBJ_REV			 CONSTANT '0',
	BILLINFO_OBJ_TYPE                CONSTANT '/billinfo',
	BILLINFO_OBJ_REV                 CONSTANT '0',
	BILL_OBJ_REV                     CONSTANT '0',
	CURRENCY_OPERATOR                CONSTANT '0',
	CURRENCY_RATE                    CONSTANT '0',
	CURRENCY_SECONDARY               CONSTANT '0',
	DISPUTED                         CONSTANT '0',
	DUE_T                            CONSTANT '0',
	POID_REV                         CONSTANT '0',
	READ_ACCESS                      CONSTANT 'L',
	SERVICE_OBJ_REV                  CONSTANT '0',	
	TRANSFERED                       CONSTANT '0',
	WRITEOFF                         CONSTANT '0',
	ARCHIVE_STATUS                   CONSTANT '0',
	CLOSED_T                         CONSTANT '0',
	OPENED_T                         CONSTANT '0',
	GL_SEGMENT                       CONSTANT '.',
	WRITE_ACCESS                     CONSTANT 'L'
-- These fields will be entered as NULL	
--	EVENT_POID_LIST                  NULL
--	GL_SEGMENT                       NULL
--	ITEM_NO                          NULL
   )	
