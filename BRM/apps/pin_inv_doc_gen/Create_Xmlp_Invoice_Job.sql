Rem
Rem $Header: bus_platform_vob/financial/apps/pin_inv_doc_gen_12c/src/Create_Xmlp_Invoice_Job.sql /cgbubrm_mainbrm.portalbase/1 2017/04/18 22:05:01 crunkana Exp $
Rem
Rem Create_Xmlp_Invoice_Job.sql
Rem
Rem Copyright (c) 2008, 2017, Oracle and/or its affiliates. 
Rem All rights reserved.
Rem
Rem    NAME
Rem      Create_Xmlp_Invoice_Job.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      This script creates XMLP_INVOICE_JOB table in schedular database. 
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    viprasad    12/22/08 - Created
Rem

CREATE TABLE XMLP_INVOICE_JOB
(
JOB_ID int ,
INVOICE_OBJ_ID int
)tablespace <tablespacename> storage (initial 100k next 100k pctincrease 0 );
