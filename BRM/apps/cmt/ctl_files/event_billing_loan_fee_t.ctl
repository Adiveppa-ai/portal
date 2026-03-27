--
-- @(#)event_billing_loan_fee_t.ctl 1
--
--     Copyright (c) 2023 Oracle. All rights reserved.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
LOAD DATA
APPEND
   INTO TABLE EVENT_BILLING_LOAN_FEE_T
   (
	OBJ_ID0		INTEGER EXTERNAL TERMINATED BY ',',
	AMOUNT		INTEGER EXTERNAL TERMINATED BY ','
   )
