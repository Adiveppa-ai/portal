-- ============================================================
--   DBMS name:      ORACLE Version 9 for simuLate             
--   Created on:     17.10.99  09:00                           
-- ============================================================

-- ============================================================
--   VERSION HISTORY
-- ============================================================
/* 
   17.10.99-at: createdd initial file
		- created role ROLE_JSA_ALL
		- created role ROLE_JSA_SEL
		- created user JSA
*/


-- ============================================================
--   Role: ROLE_JSA_SEL
-- ============================================================

create role ROLE_JSA_SEL;

grant create session to ROLE_JSA_SEL;


-- ============================================================
--   Role: ROLE_JSA_ALL
-- ============================================================

create role ROLE_JSA_ALL;

grant connect to ROLE_JSA_ALL;

grant create table         to ROLE_JSA_ALL;
grant create view          to ROLE_JSA_ALL;
grant create synonym       to ROLE_JSA_ALL;
grant create index         to ROLE_JSA_ALL;
grant create sequence      to ROLE_JSA_ALL;
grant create cluster       to ROLE_JSA_ALL;
grant create database link to ROLE_JSA_ALL;
grant alter session        to ROLE_JSA_ALL;


grant ROLE_JSA_SEL to ROLE_JSA_ALL;

-- ============================================================
--   User: JSA
-- ============================================================

create user 
	JSA identified by JSA 
	default tablespace JSA_TS_1_DAT 
	temporary tablespace TEMP 
	quota unlimited on JSA_TS_1_DAT 
	quota unlimited on JSA_TS_1_IDX; 

grant ROLE_JSA_ALL to JSA with admin option;

grant create public synonym to JSA;
