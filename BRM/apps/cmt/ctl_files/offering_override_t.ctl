--
-- @(#)offering_override_t.ctl 0
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
   INTO TABLE OFFERING_OVERRIDE_T
(
	POID_DB                     INTEGER EXTERNAL TERMINATED BY ',',
	POID_ID0                    INTEGER EXTERNAL TERMINATED BY ',',
	CREATED_T                   INTEGER EXTERNAL TERMINATED BY ',',
	MOD_T                       INTEGER EXTERNAL TERMINATED BY ',',
	OFFERING_OBJ_DB             INTEGER EXTERNAL TERMINATED BY ',',
	OFFERING_OBJ_ID0            INTEGER EXTERNAL TERMINATED BY ',',
	OFFERING_OBJ_TYPE           CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	ACCOUNT_OBJ_DB              INTEGER EXTERNAL TERMINATED BY ',',
	ACCOUNT_OBJ_ID0             INTEGER EXTERNAL TERMINATED BY ',',
-- Constant values
	POID_TYPE                   CONSTANT '/offering_override_values',
	POID_REV                    CONSTANT '0',
	READ_ACCESS                 CONSTANT 'L',
	WRITE_ACCESS                CONSTANT 'L',
	OFFERING_OBJ_REV            CONSTANT '1',
 	ACCOUNT_OBJ_TYPE            CONSTANT '/account',
	ACCOUNT_OBJ_REV             CONSTANT '1'
)
