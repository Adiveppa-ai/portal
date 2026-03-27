--
-- @(#)cmt_balances_t.ctl 1
--
-- Copyright (c) 2004, 2023, Oracle and/or its affiliates.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
LOAD DATA
APPEND
   INTO TABLE CMT_BALANCES_BAL_T
   (
	POID_DB                 	INTEGER EXTERNAL TERMINATED BY ',',
	POID_ID0                	INTEGER EXTERNAL TERMINATED BY ',',
	CREATED_T               	INTEGER EXTERNAL TERMINATED BY ',',
	RESOURCE_ID			INTEGER EXTERNAL TERMINATED BY ',',
	ACCOUNT_OBJ_DB          	INTEGER EXTERNAL TERMINATED BY ',',
	ACCOUNT_OBJ_ID0         	INTEGER EXTERNAL TERMINATED BY ',',
	MOD_T                    	INTEGER EXTERNAL TERMINATED BY ',',
	BAL_GRP_OBJ_DB                  INTEGER EXTERNAL TERMINATED BY ',',
        BAL_GRP_OBJ_ID0                 INTEGER EXTERNAL TERMINATED BY ',',
	RESERVED_AMOUNT                 INTEGER EXTERNAL TERMINATED BY ',',
	CREDIT_LIMIT                 	INTEGER EXTERNAL TERMINATED BY ',',
	CREDIT_FLOOR                    INTEGER EXTERNAL TERMINATED BY ',',
	DYNAMIC_CREDIT_FLOOR		INTEGER EXTERNAL TERMINATED BY ',',
	OVERRIDE_CREDIT_LIMIT           INTEGER EXTERNAL TERMINATED BY ',',
	CREDIT_THRESHOLDS               INTEGER EXTERNAL TERMINATED BY ',',
	CREDIT_THRESHOLDS_FIXED         CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	CONSUMPTION_RULE                INTEGER EXTERNAL TERMINATED BY ',',
	CONSUMED_RESERVED_AMOUNT        INTEGER EXTERNAL TERMINATED BY ',',

-- Constant Values
	POID_TYPE              		CONSTANT '/cmt_balances_bal',
	POID_REV               		CONSTANT '0',
	READ_ACCESS            		CONSTANT 'L',
	WRITE_ACCESS           		CONSTANT 'L',
	ACCOUNT_OBJ_TYPE       		CONSTANT '/account',
	ACCOUNT_OBJ_REV        		CONSTANT '0',
        BAL_GRP_OBJ_TYPE                CONSTANT '/balance_group',
        BAL_GRP_OBJ_REV                 CONSTANT '1'
   )

