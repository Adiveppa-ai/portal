--------------------------------------------------------------------------------
--
-- Copyright (c) 1998, 2010, Oracle and/or its affiliates. 
-- All rights reserved. 
--
--      This material is the confidential property of Oracle Corporation
--      or its licensors and may be used, reproduced, stored or transmitted
--      only in accordance with a valid Oracle license or sublicense agreement.
--
--------------------------------------------------------------------------------
-- Block: Database
--------------------------------------------------------------------------------
-- Module Description:
--   Update script from DB version v6.5.1 to v6.5.2.
--------------------------------------------------------------------------------
-- Responsible: Gireesh Malaksamudra
--------------------------------------------------------------------------------
-- Log:
-- 2002/10/23 pengelbr
-- PRSF00020915 database update scripts for IFW are not clear- they say 6.4 
-- should be 6.5, unclear how to move from 6.2-6.5 or 6.3-6.5 
--
-- 2002/10/15 gireesh
-- PRSF00020495 Change DATE to EDR_DATE for IFW_DUPLICATECHECK
--
-- 2002/09/27 gireesh
-- PRSF00018728 Adding table IFW_DUPLICATECHECK
--
--------------------------------------------------------------------------------

spool update_v6.5.1_v6.5.2.log

-- 
--   IFW_DUPLICATECHECK                                 
-- 
create table IFW_DUPLICATECHECK
(
    TRANS_ID            NUMBER(18)             not null,
    DATA                VARCHAR2(4000)          not null,
    EDR_DATE            DATE                   not null,
    constraint PK_IFW_DUPCK primary key (DATA)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_1_IDX
        storage
        (
        initial 32K
        next 32K
        minextents 1
        maxextents unlimited
        pctincrease 0
     )
)
pctfree 10
pctused 80
initrans 2
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_1_DAT;

grant select, insert, update, delete on IFW_DUPLICATECHECK to INTEGRATE_ROLE_ALL;

grant select on IFW_DUPLICATECHECK to INTEGRATE_ROLE_SEL;

comment on table IFW_DUPLICATECHECK is 'Duplicate detection based on the contents of DATA';

comment on column IFW_DUPLICATECHECK.TRANS_ID is 'Transaction Id';

comment on column IFW_DUPLICATECHECK.DATA is 'Duplicate Data';

comment on column IFW_DUPLICATECHECK.EDR_DATE is 'EDR Date';


--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.5.2', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
