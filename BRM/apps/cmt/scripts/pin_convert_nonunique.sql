--
-- @(#)convert_indexes_nonunique.sql 1
--
-- Copyright (c) 2004, 2017, Oracle and/or its affiliates. All rights reserved.
--
--     This material is the confidential property of Oracle Corporation
--     or its licensors and may be used, reproduced, stored or transmitted 
--     only in accordance with a valid Oracle license or sublicense agreement.
--
--
--
-- This script is used to convert unique indexes to non-unique for setting up scoped DM 
--
-- Replace tablespace PINX00 with the correct tablespace name and also update storage
-- characteristics accordingly

drop INDEX I_ACCOUNT_NO__ID;
drop INDEX I_ACCOUNT__ID;
drop INDEX I_ACCOUNT_NAMEINFO__ID;
drop INDEX I_BILLINFO__ID;
drop INDEX I_PAYINFO__ID;
drop INDEX I_INVOICE__ID;
drop INDEX I_BALANCE_GROUP__ID;
drop INDEX I_BILL__ID;
drop INDEX I_ITEM_NO__ID;
drop INDEX I_ITEM__ID;
drop INDEX I_UNIQUE_ACCOUNT_NO__ID;
drop INDEX I_UNIQUE_ACOUNT_NO__ACCOUNT_NO;
drop INDEX I_UNIQUENESS__ID;
drop INDEX I_BAL_GRP_BALS__ID;
drop INDEX I_BAL_GRP_SUB_BALS__ID;
drop INDEX I_SERVICE__ID;
drop INDEX I_SERVICE_ADMIN_PERMITTEDS__ID;
drop INDEX I_UNIQUENESS__LOGIN_TYPE;
drop INDEX I_GROUP__ID;

CREATE INDEX I_ACCOUNT_NO__ID ON ACCOUNT_T
(ACCOUNT_NO)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE INDEX I_ACCOUNT__ID ON ACCOUNT_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_ACCOUNT_NAMEINFO__ID ON ACCOUNT_NAMEINFO_T
(OBJ_ID0, REC_ID)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_BILLINFO__ID ON BILLINFO_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_PAYINFO__ID ON PAYINFO_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_INVOICE__ID ON INVOICE_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        2
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_BALANCE_GROUP__ID ON BAL_GRP_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_BILL__ID ON BILL_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        2
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_ITEM_NO__ID ON ITEM_T
(ITEM_NO, POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        2
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE INDEX I_ITEM__ID ON ITEM_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        2
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_UNIQUE_ACCOUNT_NO__ID ON UNIQUE_ACCT_NO_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE INDEX I_UNIQUE_ACOUNT_NO__ACCOUNT_NO ON UNIQUE_ACCT_NO_T
(ACCOUNT_NO)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE INDEX I_UNIQUENESS__ID ON UNIQUENESS_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_BAL_GRP_BALS__ID ON BAL_GRP_BALS_T
(OBJ_ID0, REC_ID)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_BAL_GRP_SUB_BALS__ID ON BAL_GRP_SUB_BALS_T
(OBJ_ID0, REC_ID2, REC_ID)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_SERVICE__ID ON SERVICE_T
(POID_ID0)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_SERVICE_ADMIN_PERMITTEDS__ID ON SERVICE_ADMIN_PERMITTEDS_T
(OBJ_ID0, REC_ID)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_UNIQUENESS__LOGIN_TYPE ON UNIQUENESS_T
(LOGIN, TYPE)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          32K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

CREATE INDEX I_GROUP__ID ON GROUP_T
(POID_ID0, TYPE_STR)
LOGGING
TABLESPACE PINX00
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            FREELISTS        1
            FREELIST GROUPS  1
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;

commit;
