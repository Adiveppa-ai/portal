--------------------------------------------------------------------------------
--
--      Copyright (c) 2000 - 2006 Oracle. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation
--      or its licensors and may be used, reproduced, stored or transmitted
--      only in accordance with a valid Oracle license or sublicense agreement.
--
--------------------------------------------------------------------------------
-- Block: Database
--------------------------------------------------------------------------------
-- Module Description:
--   Enable Constraints on unmodified tables.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-01_v4-10-01_Constraints.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/12/21 14:22:16 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-01_v4-10-01_Constraints.sql,v $
-- Revision 1.2  2000/12/21 14:22:16  pengelbr
-- Updated to NOT modify INT_ISCRIPT and INT_RULE* tables.
-- iScript and iRules columns shall be of LONG type as before (v4-05).
--
-- Revision 1.1  2000/10/20 07:40:37  pengelbr
-- Modified/Added for v4-10-01 by PE.
--
--------------------------------------------------------------------------------

alter table SOL_REGISTRY
    add constraint FK_SOL_REGISTRY_SOL_SECTION foreign key  (SECTION)
       references SOL_SECTION (SECTION) on delete cascade
/

alter table AGG_CLASS_LNK
    add constraint FK_AGG_CLASSLNK_AGG_CLASS foreign key  (CLASS_ID)
       references AGG_CLASS (CLASS_ID) on delete cascade
/

alter table AGG_CLASS_LNK
    add constraint FK_AGG_CLASS_LNK_AGG_CLASSITEM foreign key  (CLASSITEM_ID)
       references AGG_CLASSITEM (CLASSITEM_ID) on delete cascade
/

alter table AGG_CLASSCON_LNK
    add constraint FK_AGG_CLSCONLNK_AGG_CLASSITEM foreign key  (CLASSITEM_ID)
       references AGG_CLASSITEM (CLASSITEM_ID) on delete cascade
/

alter table AGG_CLASSCON_LNK
    add constraint FK_AGG_CLSCONLNK_AGG_CLSCON foreign key  (CLASSCON_ID)
       references AGG_CLASSCON (CLASSCON_ID) on delete cascade
/

alter table AGG_EDRFORMAT_CNF
    add constraint FK_AGG_EDRF_CNF_AGG_EDRF foreign key  (FORMAT_ID)
       references AGG_EDRFORMAT (FORMAT_ID)
/

alter table AGG_EDRFORMAT_CNF
    add constraint FK_AGG_EDRF_CNF_AGG_EDRC_FIELD foreign key  (EDRCFIELD_ID)
       references AGG_EDRCFIELD (EDRCFIELD_ID)
/

