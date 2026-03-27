--
-- @(#) myclass_rules_t.ctl 2
--
--     Copyright (c) 2005-2006 Oracle. All rights reserved.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
LOAD DATA
APPEND
    INTO TABLE MYCLASS_RULES_T
    (
        OBJ_ID0    INTEGER EXTERNAL TERMINATED BY ',', 
        REC_ID     INTEGER EXTERNAL TERMINATED BY ',', 
        RUM_ID     INTEGER EXTERNAL TERMINATED BY ',', 
        DESCR     CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"', 
        START_T   INTEGER EXTERNAL TERMINATED BY ','
     )
