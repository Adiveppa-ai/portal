-- ============================================================
-- To enable the customers super user to add new users, modules and to link 
-- these a default superuser (JSA) must be created manually. 
-- ============================================================



-- ============================================================
-- INSERT DEFAULT JSA USER
-- ============================================================
Insert Into JSA_USER ( 
	USER_ID, 
	ACTIVE, 
	LOGIN, 
	USR_FIRSTNAME, 
	USR_LASTNAME, 
	ENTRYDATE, 
	ENTRYBY, 
	RECVER) 
Values (
	0, 
	1, 
	'JSA', 
	'Default', 
	'JSA ADMIN', 
	SYSDATE, 
	0, 
	0
);

Insert Into JSA_USER ( 
	USER_ID, 
	ACTIVE, 
	LOGIN, 
	USR_FIRSTNAME, 
	USR_LASTNAME, 
	ENTRYDATE, 
	ENTRYBY, 
	RECVER) 
Values (
	JSA_SEQ_USER_ID.NEXTVAL, 
	1, 
	'INTEGRATE', 
	'Default', 
	'IntegRate DB Admin', 
	SYSDATE, 
	0, 
	0
);

commit;
