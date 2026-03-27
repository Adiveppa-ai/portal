--------------------------------------------------------------------------------
--
-- Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
--      
--      This material is the confidential property of Oracle Corporation or its
--      licensors and may be used, reproduced, stored or transmitted only in
--      accordance with a valid Oracle license or sublicense agreement.
--
-- Module Description:
--   Default tables for NRTRDE Report Generation
--
--------------------------------------------------------------------------------

--
-- TABLE: NRTRDE_FILES
--

CREATE TABLE "NRTRDE_FILES" (	
  "FILENAME"              VARCHAR2(80 BYTE)               NOT NULL ENABLE, 
  "SENDER"                VARCHAR2(80 BYTE), 
  "RECIPIENT"             VARCHAR2(80 BYTE), 
  "SEQNO"                 NUMBER, 
  "FILEPROCESSEDTIME"     DATE DEFAULT SYSDATE            NOT NULL ENABLE, 
  "FILEDELIVERYREPORTED"  VARCHAR2(1 BYTE) DEFAULT 'N'    NOT NULL ENABLE, 
  CONSTRAINT "NRTRDE_FILES_PK1" PRIMARY KEY ("FILENAME") ENABLE 
)
/

--
-- TABLE: NRTRDE_ERRORS
--

CREATE TABLE "NRTRDE_ERRORS" ( 
  "FILENAME"              VARCHAR2(80 BYTE)               NOT NULL ENABLE, 
  "RECORDNUMBER"          NUMBER, 
  "RECORDTYPE"            VARCHAR2(80 BYTE), 
  "ERRORCODELIST"         VARCHAR2(80 BYTE)               NOT NULL ENABLE, 
  "ERRORREPORTED"         VARCHAR2(1 BYTE) DEFAULT 'N'    NOT NULL ENABLE, 
  "SENDER"                VARCHAR2(80 BYTE), 
  CONSTRAINT "NRTRDE_ERRORS_NRTRDE_FILE_FK1" FOREIGN KEY ("FILENAME") REFERENCES "NRTRDE_FILES" ("FILENAME") ENABLE 
)
/

--
-- TABLE: NRTRDE_SEQUENCES
--

CREATE TABLE "NRTRDE_SEQUENCES" (	
  "SEQNO"                 NUMBER                          NOT NULL ENABLE, 
  "SEQTYPE"               VARCHAR2(1 BYTE)                NOT NULL ENABLE, 
  "OPERATOR"              VARCHAR2(80 BYTE)               NOT NULL ENABLE, 
  CONSTRAINT "NRTRDE_SEQUENCES_PK1" PRIMARY KEY ("SEQNO", "SEQTYPE", "OPERATOR") ENABLE 
)
/
