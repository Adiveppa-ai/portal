Rem
Rem $Header: install_vob/nginstall/components/CORE/grant.sql /cgbubrm_mainbrm.portalbase/2 2017/07/11 01:11:12 mkothari Exp $
Rem
Rem Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    mkothari    05/22/17 - Created
Rem

grant unlimited tablespace to pin15;
grant execute on dbms_lock to pin15;
grant execute on dbms_aq to pin15;
grant execute on dbms_aqadm to pin15;
grant select on sys.gv_$aq to pin15;
grant INTEGRATE_ROLE_ALL to pin15 with admin option;
