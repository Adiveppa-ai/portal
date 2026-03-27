--
-- @(#)bal_grp_bals_t.ctl 3
--
-- Copyright (c) 2023 Oracle and/or its affiliates.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
LOAD DATA
APPEND
   INTO TABLE AU_BAL_GRP_BALS_T
   (
	OBJ_ID0        		INTEGER EXTERNAL TERMINATED BY ',',	
	REC_ID         		INTEGER EXTERNAL TERMINATED BY ',',
	OUTSTANDING_AMOUNT      INTEGER EXTERNAL TERMINATED BY ',',
	RESERVED_AMOUNT		INTEGER EXTERNAL TERMINATED BY ',',
	CREDIT_PROFILE 		INTEGER EXTERNAL TERMINATED BY ',',
	CONSUMPTION_RULE	INTEGER EXTERNAL TERMINATED BY ',',
        CONSUMED_RESERVED_AMOUNT	INTEGER EXTERNAL TERMINATED BY ',',
-- Constant Values
	NEXT_BAL       		CONSTANT '0'
   )
