DECLARE
        v_sql_stmt              VARCHAR2(4000);
        v_errmsg                VARCHAR2(200);
        v_user_create_error  CONSTANT NUMBER := -20005;

BEGIN
        IF (NOT (common_package.tablespace_exists('pin00', v_errmsg))) THEN
                EXECUTE IMMEDIATE 'CREATE TABLESPACE pin00  DATAFILE ''pin00.dbf'' size 600M reuse autoextend on next 100M extent management local segment space management manual';
        END IF;
        IF (NOT (common_package.tablespace_exists('pinx00', v_errmsg))) THEN
                EXECUTE IMMEDIATE 'CREATE TABLESPACE pinx00  DATAFILE ''pinx00.dbf'' size 400M reuse autoextend on next 100M extent management local segment space management manual';
        END IF;
        IF (NOT (common_package.user_exists('integrate', v_errmsg))) THEN
                DBMS_OUTPUT.PUT_LINE('creating new user...');
                EXECUTE IMMEDIATE 'create user integrate identified by integrate default tablespace pin00 temporary tablespace TEMP quota unlimited on pin00 quota unlimited on pinx00';
                EXECUTE IMMEDIATE 'grant create public synonym , create synonym , drop public synonym , create any view , create sequence , create table , create any index , create procedure , resource, connect, alter session, create database link, execute any type, select any table to integrate';
                EXECUTE IMMEDIATE 'grant unlimited tablespace to integrate';
                EXECUTE IMMEDIATE 'grant select any table to integrate';
        END IF;
        EXCEPTION
        WHEN OTHERS THEN
             RAISE_APPLICATION_ERROR(v_user_create_error, 'DB User integrate creation has failed '||sqlerrm, TRUE);

END;
/
