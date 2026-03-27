Rem
Rem $Header: install_vob/nginstall/components/pipeline/createRoles.sql /cgbubrm_mainbrm.portalbase/3 2017/05/22 05:12:00 mkothari Exp $
Rem
Rem createRoles.sql
Rem
Rem Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
Rem
Rem    NAME
Rem      createRoles.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem

create role ROLE_JSA_SEL;
create role ROLE_JSA_ALL;

create role INTEGRATE_ROLE_SEL;
grant create session to INTEGRATE_ROLE_SEL;
grant ROLE_JSA_SEL to INTEGRATE_ROLE_SEL;
grant ROLE_JSA_ALL to INTEGRATE_ROLE_SEL;

create role INTEGRATE_ROLE_ALL;
grant connect to INTEGRATE_ROLE_ALL;
grant INTEGRATE_ROLE_SEL to INTEGRATE_ROLE_ALL;
