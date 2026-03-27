Rem
Rem $Header: install_vob/nginstall/components/CORE/createPackages.sql /cgbubrm_mainbrm.portalbase/1 2017/05/22 05:12:00 mkothari Exp $
Rem
Rem createRoles.sql
Rem
Rem Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
Rem

CREATE or REPLACE PACKAGE common_package AS
FUNCTION user_exists (i_user_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN;

FUNCTION tablespace_exists (i_tbls_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN;
END common_package;
/

CREATE or REPLACE PACKAGE BODY common_package AS

FUNCTION user_exists (i_user_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM all_users
        WHERE username = UPPER(i_user_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END user_exists;

FUNCTION tablespace_exists (i_tbls_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_tablespaces
        WHERE tablespace_name = UPPER(i_tbls_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END tablespace_exists;

END common_package;
/

commit;
