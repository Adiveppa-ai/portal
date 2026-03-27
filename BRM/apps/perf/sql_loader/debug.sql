--  Continuus file information --- %full_filespec: debug.sql~2:sql:2 %
CREATE OR REPLACE PACKAGE Debug AUTHID CURRENT_USER AS
	PROCEDURE Debug(p_desc IN VARCHAR2, p_val in VARCHAR2);
	PROCEDURE Reset;
END Debug;
/

CREATE OR REPLACE PACKAGE BODY Debug AS
	PROCEDURE Debug(p_desc IN VARCHAR2, p_val in VARCHAR2) IS
	BEGIN
		DBMS_OUTPUT.PUT_LINE(p_desc || ':' || p_val);
	END Debug;

	PROCEDURE Reset IS
	BEGIN
		DBMS_OUTPUT.DISABLE;
		DBMS_OUTPUT.ENABLE(1000000);
	END Reset;

BEGIN	/* Package initialization code */
	Reset;
END Debug;
/
