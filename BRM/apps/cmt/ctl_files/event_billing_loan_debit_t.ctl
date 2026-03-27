--
-- @(#)event_billing_loan_debit_t.ctl 1
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
   INTO TABLE EVENT_BILLING_LOAN_DEBIT_T
   (
	OBJ_ID0			INTEGER EXTERNAL TERMINATED BY ',',
-- Constant Values
	TYPE			CONSTANT '0',
	CHANNEL			CONSTANT ''
   )
