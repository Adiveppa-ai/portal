--
-- @(#)offering_override_usagemap_t.ctl 0
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
   INTO TABLE OFFERING_OVERRIDE_USAGEMAP_T
   (
	OBJ_ID0                     INTEGER EXTERNAL TERMINATED BY ',',
	REC_ID                      INTEGER EXTERNAL TERMINATED BY ',',
	END_T                       INTEGER EXTERNAL TERMINATED BY ',',
	EVENT_TYPE                  CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
	DATE_RANGE_SIZE             INTEGER EXTERNAL TERMINATED BY ','
)
