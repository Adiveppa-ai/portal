--------------------------------------------------------------------------------
--
-- Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved. 
--      
--      This material is the confidential property of Oracle Corporation or its
--      licensors and may be used, reproduced, stored or transmitted only in
--      accordance with a valid Oracle license or sublicense agreement.
--
-- Module Description:
--   Table used for generating Stop Rap
--
--------------------------------------------------------------------------------

--
-- TABLE: IFW_TAPINFO
--

CREATE TABLE "IFW_TAPINFO" (
         "SENDER"                VARCHAR2(5)  NOT NULL,
         "RECIPIENT"             VARCHAR2(5)  NOT NULL,
         "SEQ_GEN_KEY"           VARCHAR2(50) NOT NULL,
         "LASTSEQNUMBER"         NUMBER(10)   NOT NULL,
         "SPECIFICATIONVERSION"  NUMBER(5)    NOT NULL,
         "RELEASEVERSION"        NUMBER(5)    NOT NULL,
         "TAPFILEDATE"           DATE         NOT NULL,
         "LASTSTOPRAPDATE"       DATE
        )
/
