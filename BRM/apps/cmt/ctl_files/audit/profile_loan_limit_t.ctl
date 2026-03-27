--
-- @(#)profile_loan_limit_t.ctl 1
--
--     Copyright (c) 2023 Oracle.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
LOAD DATA
APPEND
   INTO TABLE AU_PROFILE_LOAN_LIMIT_T
   (
	OBJ_ID0			INTEGER EXTERNAL TERMINATED BY ',',
	REC_ID			INTEGER EXTERNAL TERMINATED BY ',',
	VALID_FROM		INTEGER EXTERNAL TERMINATED BY ',',
	VALID_TO		INTEGER EXTERNAL TERMINATED BY ',',
	CREDIT_LIMIT		INTEGER EXTERNAL TERMINATED BY ','
    )
