--
-- @(#)offering_override_usagemap_buf.ctl 0
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
INFILE * "str '|'"
APPEND
   INTO TABLE offering_override_usagemap_buf
   FIELDS TERMINATED BY ','
   (
        OBJ_ID0                 INTEGER EXTERNAL TERMINATED BY ',',
        REC_ID                  INTEGER EXTERNAL TERMINATED BY ',',
        DATE_RANGE_BUF          CHAR(4000) OPTIONALLY ENCLOSED BY '***' and '***'
   )
