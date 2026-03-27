--
-- @(#) myclass_t.ctl 2
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
    INTO TABLE MYCLASS_T
    (
        POID_DB             INTEGER EXTERNAL TERMINATED BY ',',
        POID_ID0            INTEGER EXTERNAL TERMINATED BY ',',
        POID_TYPE           CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
        POID_REV            INTEGER EXTERNAL TERMINATED BY ',',
        CREATED_T           INTEGER EXTERNAL TERMINATED BY ',',
        MOD_T               INTEGER EXTERNAL TERMINATED BY ',',
        READ_ACCESS         CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
        WRITE_ACCESS        CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
        ACCOUNT_OBJ_DB      INTEGER EXTERNAL TERMINATED BY ',',
        ACCOUNT_OBJ_ID0     INTEGER EXTERNAL TERMINATED BY ',',
        ACCOUNT_OBJ_TYPE    CHAR TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"',
        ACCOUNT_OBJ_REV     INTEGER EXTERNAL TERMINATED BY ','
    )
