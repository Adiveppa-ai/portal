--
-- @(#)group_sharing_products_t.ctl 3
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
   INTO TABLE GROUP_SHARING_PRODUCTS_T
   (
	OBJ_ID0                    INTEGER EXTERNAL TERMINATED BY ',',
	REC_ID                     INTEGER EXTERNAL TERMINATED BY ',',
	PRODUCT_OBJ_DB             INTEGER EXTERNAL TERMINATED BY ',',
	PRODUCT_OBJ_ID0            INTEGER EXTERNAL TERMINATED BY ',',
	OFFERING_OBJ_DB            INTEGER EXTERNAL TERMINATED BY ',',
	OFFERING_OBJ_ID0           INTEGER EXTERNAL TERMINATED BY ',',
-- Constant Values	
	PRODUCT_OBJ_TYPE           CONSTANT '/product',
	PRODUCT_OBJ_REV            CONSTANT '0',
	OFFERING_OBJ_TYPE          CONSTANT '/purchased_product',
	OFFERING_OBJ_REV           CONSTANT '0'
   )	
