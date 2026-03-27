--
-- @(#)uniqueness_t.ctl 1
--
--     Copyright (c) 2007 Oracle. All rights reserved.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
LOAD DATA
APPEND
   INTO TABLE UNIQUE_ACCT_NO_T
   (
	POID_DB				INTEGER EXTERNAL TERMINATED BY ',', 
	POID_ID0			INTEGER EXTERNAL TERMINATED BY ',', 
	CREATED_T			INTEGER EXTERNAL TERMINATED BY ',', 
	MOD_T				INTEGER EXTERNAL TERMINATED BY ',', 
	ACCOUNT_OBJ_DB			INTEGER EXTERNAL TERMINATED BY ',', 
	ACCOUNT_OBJ_ID0			INTEGER EXTERNAL TERMINATED BY ',', 
	ACCOUNT_NO			CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"', 
--      Constant ValueS
        POID_TYPE                       CONSTANT '/unique_account_no',
        POID_REV                        CONSTANT '0',
        READ_ACCESS                     CONSTANT 'L',
        WRITE_ACCESS                    CONSTANT 'L',
        ACCOUNT_OBJ_TYPE                CONSTANT '/account',
        ACCOUNT_OBJ_REV                 CONSTANT '0'
)
