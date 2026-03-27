DECLARE
	v_count PLS_INTEGER;
	v_stmt  VARCHAR2(255);
BEGIN
	SELECT
		count(*) INTO v_count
	FROM
		user_objects
	WHERE
		object_name = 'TMP_EVENT_ESSENTIALS';

	IF (v_count != 0) THEN
		v_stmt := 'DROP TABLE tmp_event_essentials';
		EXECUTE IMMEDIATE v_stmt;
	END IF;

	v_stmt := 'CREATE GLOBAL TEMPORARY TABLE tmp_event_essentials '
			|| '(obj_id0 number(38), balances_small varchar2(4000), balances_large clob) '
			|| 'ON COMMIT PRESERVE ROWS';
	EXECUTE IMMEDIATE v_stmt;
END;
/

CREATE OR REPLACE PACKAGE 
pin_fix_dd AS

	-- Constants
	objects				CONSTANT VARCHAR(255) := 'DD_OBJECTS_T';
	objects_fields			CONSTANT VARCHAR(255) := 'DD_OBJECTS_FIELDS_T';
	fields				CONSTANT VARCHAR(255) := 'DD_FIELDS_T';
	types				CONSTANT VARCHAR(255) := 'DD_TYPES_T';
	sub_bal_impacts_prefix  	CONSTANT VARCHAR2(8) := '1:7754';
	sub_balances_prefix     	CONSTANT VARCHAR2(8) := '2:7753';
	mon_impacts_prefix 		CONSTANT VARCHAR2(8) := '1:9232';
	mon_sub_bal_impacts_prefix    	CONSTANT VARCHAR2(8) := '1:9233';
	sub_bal_impacts_prefix_len 	NUMBER := LENGTH(sub_bal_impacts_prefix);
	sub_balances_prefix_len    	NUMBER := LENGTH(sub_balances_prefix);
	mon_impacts_prefix_len 		NUMBER := LENGTH(mon_impacts_prefix);
	mon_sub_bal_impacts_prefix_len  NUMBER := LENGTH(mon_sub_bal_impacts_prefix);
	ser_record_delimiter       	CONSTANT VARCHAR2(2) := CHR(10);
	ser_delimiter              	CONSTANT VARCHAR2(2) := ':';
	ser_field_value_delimiter  	CONSTANT VARCHAR2(2) := ',';
	poid_record_delimiter      	CONSTANT VARCHAR2(2) := ';';

	-- Variable
	TYPE ID2NAME_MAP_TYPE IS TABLE OF VARCHAR2(255) INDEX BY PLS_INTEGER;
	TYPE NAME2ID_MAP_TYPE IS TABLE OF NUMBER(38) INDEX BY VARCHAR2(255);
	TYPE DD_OBJS_OBJ_IDO_TAB IS TABLE OF NUMBER;
	TYPE DD_OBJS_NAME_TAB IS TABLE OF VARCHAR2(255);
	old_id2NAME_map ID2NAME_MAP_TYPE;
	new_id2name_map ID2NAME_MAP_TYPE;
	new_name2id_map NAME2ID_MAP_TYPE;
	init_done BOOLEAN := FALSE;
	use_balances_large BOOLEAN := FALSE;
	event_essentials_changed BOOLEAN := FALSE;
	dd_changed BOOLEAN := FALSE;
	dd_essentials_changed BOOLEAN := FALSE;

	-- Error
	ERR_TABLE_NOT_FOUND	CONSTANT INTEGER := -20001;
	ERR_BACKUP_FAILED	CONSTANT INTEGER := -20002;
	ERR_INVALID_FORMAT	CONSTANT INTEGER := -20003;
	ERR_NOT_FOUND		CONSTANT INTEGER := -20004;

	-- Procedures
	PROCEDURE validate_dd(primary_schema IN VARCHAR2);
	PROCEDURE update_dd(primary_schema IN VARCHAR2);
	PROCEDURE grant_dd(secondary_schema IN VARCHAR2);
	PROCEDURE update_events(i_commit_size IN NUMBER DEFAULT 100);
	PROCEDURE update_event(i_poid_id0 IN NUMBER);
	PROCEDURE fix_event_data(i_bal_small IN VARCHAR2, i_bal_large IN CLOB, o_bal_smalL IN OUT VARCHAR2, o_bal_large IN OUT CLOB);
	PROCEDURE init_dd_map;
	PROCEDURE update_virtual_columns;
	FUNCTION get_new_classid(old_class_id IN NUMBER) RETURN NUMBER;

END pin_fix_dd;
/

SHOW ERRORS;

CREATE OR REPLACE PACKAGE BODY pin_fix_dd AS

PROCEDURE grant_dd(secondary_schema IN VARCHAR2)
IS
	v_secondary_schema VARCHAR2(32) := UPPER(secondary_schema);
        v_sql VARCHAR2(512);
BEGIN
        EXECUTE IMMEDIATE 'GRANT ALL ON ' || objects || ' TO ' || v_secondary_schema;
        EXECUTE IMMEDIATE 'GRANT ALL ON ' || objects_fields || ' TO ' || v_secondary_schema;
        EXECUTE IMMEDIATE 'GRANT ALL ON ' || fields || ' TO ' || v_secondary_schema;
        EXECUTE IMMEDIATE 'GRANT ALL ON ' || types || ' TO ' || v_secondary_schema;
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- grant_dd input secondary schema = ' || v_secondary_schema);
        v_sql :=SUBSTR(SQLERRM, 1 , 400);
	DBMS_OUTPUT.PUT_LINE(v_sql);
	RAISE;
END grant_dd;

-- Validate dd_objects_t against the primary table.
PROCEDURE validate_dd_objects_fields(
  primary_schema IN VARCHAR2,
  class_name IN VARCHAR2)
IS
  -- Variable
  v_count NUMBER := 0;
  v_p_count NUMBER := 0;

BEGIN

  -- Check in the secondary count
  EXECUTE IMMEDIATE 'SELECT count(*) FROM dd_objects_fields_t ' ||
		'WHERE obj_id0 = (SELECT obj_id0 FROM dd_objects_t WHERE name = :class_name)' INTO v_count USING class_name;
  -- Check in the primary count
  EXECUTE IMMEDIATE 'SELECT count(*) FROM ' || primary_schema || '.dd_objects_fields_t ' ||
		'WHERE obj_id0 = (SELECT obj_id0 FROM ' || primary_schema || '.dd_objects_t WHERE name = :class_name)' INTO v_p_count USING class_name;

  -- Update the  current value
  IF (v_p_count != v_count) THEN
    RAISE NO_DATA_FOUND;
  END IF;

EXCEPTION
WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE(' ');
        DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_objects_fields fields count not same class_name ' || class_name);
        RAISE;
WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_objects_fields failed');
        DBMS_OUTPUT.PUT_LINE(SQLERRM);
        RAISE;
END validate_dd_objects_fields;


-- Validate dd_objects_t against the primary table.
PROCEDURE validate_dd_objects(
  primary_schema IN VARCHAR2,
  update_dd IN BOOLEAN) 
IS
  -- Variable
  v_p_obj_id0 NUMBER := 0;
  v_obj_id0 NUMBER := 0;
  v_name VARCHAR2(255);
  v_current_schema VARCHAR2(255);

  -- Cursor
  CURSOR dd_objects_records IS SELECT obj_id0, name FROM dd_objects_t order by obj_id0 desc;
BEGIN

  BEGIN
    -- Take a backup of the dd
    EXECUTE IMMEDIATE 'CREATE TABLE dd_objects_t_bak AS SELECT * FROM dd_objects_t';
    EXECUTE IMMEDIATE 'CREATE TABLE dd_objects_fields_t_bak AS SELECT * FROM dd_objects_fields_t';
  EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE(' '); -- Do nothing.
  END;

  FOR rec IN dd_objects_records
  LOOP
    v_obj_id0 := rec.obj_id0;
    v_name := rec.name;

    -- Check in the primary
    EXECUTE IMMEDIATE 'SELECT obj_id0 FROM ' || primary_schema || '.dd_objects_t ' ||
		'WHERE name = :object_name' INTO v_p_obj_id0 USING v_name;

    -- Update the  current value
    IF (v_p_obj_id0 != v_obj_id0) THEN
	dd_changed := TRUE;
	
	IF ((v_name = '/purchased_product') OR (v_name = '/purchased_discount') OR (v_name = '/product') OR (v_name = '/balance_group') OR ( v_name = '/balance_group/monitor')) THEN
		dd_essentials_changed := TRUE;
        END IF;

	IF (update_dd = FALSE) THEN
	  DBMS_OUTPUT.PUT_LINE('WARNING -- OBJECTS ' || v_name || ' has different id in primary');
	ELSE 
	  EXIT;
	END IF;
    END IF;

    validate_dd_objects_fields(primary_schema, v_name);
  END LOOP;

  IF (update_dd = TRUE AND dd_changed = TRUE) THEN
    v_current_schema := USER;

    -- Create Temporary Data Table 1
    EXECUTE IMMEDIATE 'CREATE TABLE temp_update_dd_01 AS (' ||
		'SELECT ' || v_current_schema || '.dd_objects_fields_t.obj_id0 obj_id0_s, ' || v_current_schema || '.dd_objects_fields_t.rec_id rec_id_s, ' ||
       		primary_schema || '.dd_objects_fields_t.obj_id0 obj_id0_p, ' || primary_schema || '.dd_objects_fields_t.rec_id rec_id_p ' ||
		'FROM ' || v_current_schema || '.dd_objects_t INNER JOIN ' ||
  		primary_schema || '.dd_objects_t ON ' || v_current_schema || '.dd_objects_t.name = ' || primary_schema || '.dd_objects_t.name ' ||
                'INNER JOIN ' || v_current_schema || '.dd_objects_fields_t ON ' ||
    		v_current_schema || '.dd_objects_t.obj_id0 = ' || v_current_schema || '.dd_objects_fields_t.obj_id0 AND ' ||
    		v_current_schema || '.dd_objects_fields_t.rec_id != 0 AND ' ||
    		v_current_schema || '.dd_objects_fields_t.parent_element_id = 0 ' ||
		'INNER JOIN ' || 
		primary_schema || '.dd_objects_fields_t ON ' ||
    		primary_schema || '.dd_objects_t.obj_id0 = ' || primary_schema || '.dd_objects_fields_t.obj_id0 AND ' ||
		primary_schema || '.dd_objects_fields_t.parent_element_id = 0 and ' ||
    		v_current_schema || '.dd_objects_fields_t.field_name = ' || primary_schema || '.dd_objects_fields_t.field_name)';

    -- Create Temporary Data Table 2
    EXECUTE IMMEDIATE 'CREATE TABLE temp_update_dd_02 AS (' ||
		'SELECT ' || v_current_schema || '.dd_objects_fields_t.obj_id0 obj_id0_s, ' || v_current_schema || '.dd_objects_fields_t.rec_id rec_id_s, ' ||
		v_current_schema || '.dd_objects_fields_t.parent_element_id p_id_s, '||
       		primary_schema || '.dd_objects_fields_t.obj_id0 obj_id0_p, ' || primary_schema || '.dd_objects_fields_t.rec_id rec_id_p, ' ||
		primary_schema || '.dd_objects_fields_t.parent_element_id p_id_p '|| 
		'FROM ' ||
  		v_current_schema || '.dd_objects_fields_t ' ||
		'INNER JOIN ' ||
  		'temp_update_dd_01 ON ' || 
    		v_current_schema || '.dd_objects_fields_t.obj_id0 = temp_update_dd_01.obj_id0_s AND ' ||
    		v_current_schema || '.dd_objects_fields_t.rec_id != 0 AND ' ||
    		v_current_schema || '.dd_objects_fields_t.parent_element_id = temp_update_dd_01.rec_id_s ' ||
		'INNER JOIN ' || primary_schema || '.dd_objects_fields_t ON ' ||
    		primary_schema || '.dd_objects_fields_t.obj_id0 = temp_update_dd_01.obj_id0_p AND ' ||
    		primary_schema || '.dd_objects_fields_t.parent_element_id = temp_update_dd_01.rec_id_p AND ' ||
    		v_current_schema || '.dd_objects_fields_t.field_name = ' || primary_schema || '.dd_objects_fields_t.field_name)';
	
    -- Create Temporary Data Table 3
    EXECUTE IMMEDIATE 'CREATE TABLE temp_update_dd_03 AS SELECT * FROM temp_update_dd_01 ' ||
		'UNION ' ||
		'SELECT obj_id0_s, rec_id_s, obj_id0_p, rec_id_p from temp_update_dd_02';
	
    -- Update Secondary DD_OBJECTS_FIELDS_T table.
    EXECUTE IMMEDIATE 'UPDATE dd_objects_fields_t SET (obj_id0, rec_id) = ' ||
		'(SELECT obj_id0_p, rec_id_p FROM temp_update_dd_03 WHERE obj_id0_s = obj_id0 ' ||
		'AND rec_id_s = rec_id) WHERE parent_element_id = 0';
    EXECUTE IMMEDIATE 'UPDATE dd_objects_fields_t SET (obj_id0, parent_element_id) = ' ||
		'(SELECT obj_id0_p, rec_id_p FROM temp_update_dd_03 WHERE obj_id0_s = obj_id0 ' ||
		'AND rec_id_s = parent_element_id) WHERE rec_id = 0';
    EXECUTE IMMEDIATE 'UPDATE dd_objects_fields_t SET (obj_id0, rec_id, parent_element_id) = ' ||
		'(SELECT obj_id0_p, rec_id_p, p_id_p FROM temp_update_dd_02 WHERE obj_id0_s = obj_id0 ' ||
		'AND rec_id_s = rec_id AND p_id_s = parent_element_id) WHERE rec_id != 0 AND parent_element_id != 0';
	
    -- Update Secondary DD_OBJECTS_T table.
    EXECUTE IMMEDIATE 'UPDATE ' || v_current_schema || '.dd_objects_t SET (obj_id0) = ' ||
		'(SELECT obj_id0 FROM ' ||
		primary_schema || '.dd_objects_t WHERE ' || primary_schema || '.dd_objects_t.name = ' || v_current_schema || '.dd_objects_t.name)';

    EXECUTE IMMEDIATE 'DROP TABLE temp_update_dd_01';
    EXECUTE IMMEDIATE 'DROP TABLE temp_update_dd_02';
    EXECUTE IMMEDIATE 'DROP TABLE temp_update_dd_03';

    COMMIT;
  END IF;


EXCEPTION
WHEN NO_DATA_FOUND THEN
	DBMS_OUTPUT.PUT_LINE(' ');
	DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_objects name ' || v_name || 
			' not found in primary schema ' || primary_schema);
	RAISE;
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_objects failed');
	DBMS_OUTPUT.PUT_LINE(SQLERRM);
	RAISE; 
END validate_dd_objects;

PROCEDURE validate_dd_fields(
  primary_schema IN VARCHAR2,
  update_dd IN BOOLEAN)
IS
  -- Variable
  v_p_field_num NUMBER := 0;
  v_field_num NUMBER := 0;
  v_field_type NUMBER := 0;
  v_field_name VARCHAR2(255);

  -- Cursor
  CURSOR dd_fields_records IS SELECT field_num, field_name, field_type FROM dd_fields_t;
BEGIN

  BEGIN
    -- Take a backup of the dd
    EXECUTE IMMEDIATE 'CREATE TABLE dd_fields_t_bak AS SELECT * FROM dd_fields_t';
  EXCEPTION
    WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE(' '); -- Do nothing.
  END;

  FOR rec IN dd_fields_records
  LOOP
    v_field_num := rec.field_num;
    v_field_name := rec.field_name;
    v_field_type := rec.field_type;

    -- Check in the primary
    EXECUTE IMMEDIATE 'SELECT field_num FROM ' || primary_schema || '.dd_fields_t ' ||
		'WHERE field_name = :field_name and field_type = :field_type'
		INTO v_p_field_num USING v_field_name, v_field_type;

    -- Update the  current value
    IF (v_p_field_num != v_field_num) THEN
      IF (update_dd = TRUE) THEN
        EXECUTE IMMEDIATE 'UPDATE dd_fields_t SET field_num = :p_field_num ' ||
		'WHERE field_name = :field_name and field_type = :field_type'
		USING v_p_field_num, v_field_name, v_field_type;
      ELSE
	DBMS_OUTPUT.PUT_LINE('WARNING -- FIELDS ' || v_field_name || ' has different id in primary');
	dd_changed := TRUE;
      END IF;
    END IF;
  END LOOP;

  COMMIT;

EXCEPTION
WHEN NO_DATA_FOUND THEN
	DBMS_OUTPUT.PUT_LINE(' ');
	DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_fields name ' || v_field_name || 
			' not found in primary schema ' || primary_schema);
	RAISE;
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_fields failed');
	DBMS_OUTPUT.PUT_LINE(SQLERRM);
	RAISE; 
END validate_dd_fields;

-- Validate dd_types_t against the primary table.
PROCEDURE validate_dd_types(
  primary_schema IN VARCHAR2,
  update_dd IN BOOLEAN)
IS
  -- Variable
  v_p_obj_id0 NUMBER := 0;
  v_obj_id0 NUMBER := 0;
  v_name VARCHAR2(255);

  -- Cursor
  CURSOR dd_types_records IS SELECT obj_id0, name FROM dd_types_t;
BEGIN

  BEGIN
    -- Take a backup of the dd
    EXECUTE IMMEDIATE 'CREATE TABLE dd_types_t_bak AS SELECT * FROM dd_types_t';
  EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE(' '); -- Do nothing.
  END;

  FOR rec IN dd_types_records
  LOOP
    v_obj_id0 := rec.obj_id0;
    v_name := rec.name;

    -- Check in the primary
    EXECUTE IMMEDIATE 'SELECT obj_id0 FROM ' || primary_schema || '.dd_types_t ' ||
		'WHERE name = :type_name' INTO v_p_obj_id0 USING v_name;

    -- Update the  current value
    IF (v_p_obj_id0 != v_obj_id0) THEN
      IF (update_dd = TRUE) THEN
        EXECUTE IMMEDIATE 'UPDATE dd_types_t SET obj_id0 = :p_obj_id0 ' ||
		'WHERE name = :type_name' USING v_p_obj_id0, v_name;
      ELSE
	DBMS_OUTPUT.PUT_LINE('WARNING -- FIELDS ' || v_name || ' has different id in primary');
	dd_changed := TRUE;
      END IF;
    END IF;
  END LOOP;

  COMMIT;

EXCEPTION
WHEN NO_DATA_FOUND THEN
	DBMS_OUTPUT.PUT_LINE(' ');
	DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_types name ' || v_name || 
			' not found in primary schema ' || primary_schema);
	RAISE;
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd_types failed');
	DBMS_OUTPUT.PUT_LINE(SQLERRM);
	RAISE; 
END validate_dd_types;

PROCEDURE validate_dd(
  primary_schema In VARCHAR2)
IS
BEGIN
  dd_changed := FALSE;
  validate_dd_types(primary_schema, FALSE);
  validate_dd_fields(primary_schema, FALSE);
  validate_dd_objects(primary_schema, FALSE);
  DBMS_OUTPUT.PUT_LINE('INFO -- Validation done.');
  IF (dd_changed = TRUE) THEN
    DBMS_OUTPUT.PUT_LINE('VIRT FIX NEEDED -- Yes.');
  ELSE
    DBMS_OUTPUT.PUT_LINE('VIRT FIX NEEDED -- No.');
  END IF;
  IF (dd_essentials_changed = TRUE) THEN
    DBMS_OUTPUT.PUT_LINE('ESSENTIALS FIX NEEDED -- Yes.');
  ELSE
    DBMS_OUTPUT.PUT_LINE('ESSENTIALS FIX NEEDED -- No.');
  END IF;
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- validate_dd failed');
	DBMS_OUTPUT.PUT_LINE(SQLERRM);
	RAISE; 
END validate_dd;

PROCEDURE update_dd(
  primary_schema In VARCHAR2)
IS
BEGIN
  dd_changed := FALSE;
  validate_dd_types(primary_schema, TRUE);
  validate_dd_fields(primary_schema, TRUE);
  validate_dd_objects(primary_schema, TRUE);
  DBMS_OUTPUT.PUT_LINE('INFO -- Update done.');
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- update_dd failed');
	DBMS_OUTPUT.PUT_LINE(SQLERRM);
	RAISE; 
END update_dd;

FUNCTION check_dd(dd_name VARCHAR2)
RETURN BOOLEAN
IS
	-- Variables
	v_counter NUMBER := 0; 
	v_status BOOLEAN := FALSE; 
	v_dd_name VARCHAR2(32) := UPPER(dd_name);
BEGIN

	-- Check the presence of the table.
	SELECT COUNT(*) INTO v_counter FROM user_tables WHERE table_name = v_dd_name;

	IF (v_counter > 0) THEN
		-- Table does exist.
		v_status := TRUE;
	ELSE
		v_status := FALSE;
	END IF;

	RETURN v_status;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('error -- check_dd input dd_name = ' || v_dd_name);
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END check_dd;

PROCEDURE init_dd_map
IS
	-- Variables
	v_status BOOLEAN := FALSE; 
	v_stmt_old VARCHAR2(500) := 'SELECT OBJ_ID0, NAME FROM ' || objects || '_BAK'; 
	v_stmt_new VARCHAR2(500) := 'SELECT OBJ_ID0, NAME FROM ' || objects; 
	v_obj_id0_array DD_OBJS_OBJ_IDO_TAB;
	v_name_array DD_OBJS_NAME_TAB;

	-- Exceptions
	e_tablenotfound EXCEPTION;
BEGIN
	old_id2name_map.DELETE();
	new_id2name_map.DELETE();
	new_name2id_map.DELETE();

	-- Check if the backup table exists.
	v_status := check_dd(objects || '_BAK');
	IF (v_status = FALSE) THEN
		--DBMS_OUTPUT.PUT_LINE('DEBUG -- init_dd_map INPUT dd_name = ' || objects || '_BAK missing');
		RAISE e_tablenotfound;
	END IF;
	
	
	EXECUTE IMMEDIATE v_stmt_old BULK COLLECT INTO v_obj_id0_array, v_name_array;	
	FOR rec IN v_obj_id0_array.FIRST .. v_obj_id0_array.LAST
	LOOP
		old_id2name_map(v_obj_id0_array(rec)) := v_name_array(rec);
	END LOOP;

	EXECUTE IMMEDIATE v_stmt_new BULK COLLECT INTO v_obj_id0_array, v_name_array;	
	FOR rec IN v_obj_id0_array.FIRST .. v_obj_id0_array.LAST
	LOOP
		new_id2name_map(v_obj_id0_array(rec)) := v_name_array(rec);
		new_name2id_map(v_name_array(rec)) := v_obj_id0_array(rec);
	END LOOP;
	
	init_done := TRUE;

EXCEPTION
WHEN e_tablenotfound THEN
	DBMS_OUTPUT.PUT_LINE(' ');
	DBMS_OUTPUT.PUT_LINE('ERROR -- init_dd_map ' || objects || '_BAK table not found');
	RAISE_APPLICATION_ERROR(ERR_TABLE_NOT_FOUND, 'table not found');
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- init_dd_map');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END init_dd_map;

FUNCTION get_old_name(obj_id0 IN NUMBER)
RETURN VARCHAR2
IS
	v_name VARCHAR2(255); 
BEGIN

	IF (init_done = FALSE) THEN
		init_dd_map();
	END IF;

	IF (obj_id0 = -1) THEN
		v_name := '';
	ELSE
		v_name := old_id2name_map(obj_id0);
	END IF;

	RETURN v_name;

END get_old_name;

FUNCTION get_new_name(obj_id0 IN NUMBER)
RETURN VARCHAR2
IS
	v_name VARCHAR2(255); 
BEGIN

	IF (init_done = FALSE) THEN
		init_dd_map();
	END IF;

	IF (obj_id0 = -1) THEN
		v_name := '';
	ELSE
		v_name := new_id2name_map(obj_id0);
	END IF;

	RETURN v_name;

END get_new_name;

FUNCTION get_new_id(name IN VARCHAR2)
RETURN NUMBER
IS
	v_obj_id0 NUMBER;
BEGIN

	IF (init_done = FALSE) THEN
		init_dd_map();
	END IF;
	
	IF(name IS NULL) THEN
		v_obj_id0 := -1;
	ELSIF (name = '') THEN
		v_obj_id0 := -1;
	ELSE
		v_obj_id0 := new_name2id_map(name);
	END IF;

	RETURN v_obj_id0;

END get_new_id;

FUNCTION get_new_classid(old_class_id IN NUMBER)
RETURN NUMBER
IS
	v_class_name VARCHAR2(255);
	v_class_id NUMBER;
BEGIN
	BEGIN

		v_class_name := get_old_name(old_class_id);
		v_class_id := get_new_id(v_class_name);

		IF (old_class_id <> v_class_id) THEN
			event_essentials_changed := TRUE;
		END IF;

		RETURN v_class_id;
	
	EXCEPTION
	WHEN NO_DATA_FOUND THEN
	
		v_class_name := get_new_name(old_class_id);

		-- This record was already converted.
		-- No exception. So return the input value
		RETURN old_class_id;
	END;		
	

EXCEPTION
WHEN NO_DATA_FOUND THEN
	DBMS_OUTPUT.PUT_LINE(' ');
	DBMS_OUTPUT.PUT_LINE('ERROR -- get_new_classid obj_id0 ' || TO_CHAR(old_class_id) || ' not found');
	RAISE_APPLICATION_ERROR(ERR_NOT_FOUND, 'obj_id0 not found');
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- get_new_classid');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END get_new_classid;

FUNCTION string_length(
	i_bal_small    IN VARCHAR2,
	i_bal_large    IN CLOB)
RETURN NUMBER IS
	v_data_len NUMBER; 
BEGIN

	IF (use_balances_large = FALSE) THEN
		v_data_len := LENGTH(i_bal_small);
	ELSE
		v_data_len := DBMS_LOB.GETLENGTH(i_bal_large);
	END IF;

	RETURN v_data_len;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- string_length');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE; 
END string_length;

PROCEDURE string_copy_from_bal(
	i_d_value       IN OUT VARCHAR2,
	i_s_bal_small   IN VARCHAR2, 
	i_s_bal_large   IN CLOB,
	i_s_offset	    IN NUMBER,
	i_s_length	    IN NUMBER)
IS
	v_tmp_lob clob := EMPTY_CLOB();
BEGIN

	IF (use_balances_large = FALSE) THEN
		i_d_value := SUBSTR(i_s_bal_small, i_s_offset, i_s_length);
	ELSE
		i_d_value := DBMS_LOB.SUBSTR(i_s_bal_large, i_s_length, i_s_offset);
	END IF;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- string_copy_from_bal');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE; 
END string_copy_from_bal;

PROCEDURE string_copy_to_bal(
	i_s_value       IN VARCHAR2,
	i_d_bal_small   IN OUT VARCHAR2, 
	i_d_bal_large   IN OUT CLOB,
	i_d_offset	    IN NUMBER,
	i_s_length	    IN NUMBER)
IS
	v_tmp_str clob := TO_CLOB(i_s_value);
BEGIN

	IF (use_balances_large = FALSE) THEN
		i_d_bal_small := CONCAT(i_d_bal_small, i_s_value);
	ELSE
		DBMS_LOB.COPY(i_d_bal_large, v_tmp_str, i_s_length, i_d_offset);
	END IF;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- string_copy_to_bal');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE; 
END string_copy_to_bal;

FUNCTION substr_string(
	i_bal_small     IN VARCHAR2,
	i_bal_large     IN CLOB,
	i_offset        IN NUMBER,
	i_length     	IN NUMBER)
RETURN VARCHAR2 IS
	v_str  VARCHAR(4000);
BEGIN

	IF (use_balances_large = FALSE) THEN
		v_str := SUBSTR(i_bal_small, i_offset, i_length);
	ELSE
		v_str := TO_CHAR(DBMS_LOB.SUBSTR(i_bal_large, i_length, i_offset));
	END IF;

	RETURN v_str;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- substr_string');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END substr_string;

FUNCTION find_string_str(
	i_str     IN VARCHAR2,
	i_pattern       IN VARCHAR2,
	i_offset        IN NUMBER DEFAULT 1,
	i_occurence     IN NUMBER DEFAULT 1)
RETURN NUMBER IS
	v_index  NUMBER;
BEGIN

	v_index := INSTR(i_str, i_pattern, i_offset, i_occurence);

	RETURN v_index;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- find_string_str');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END find_string_str;

FUNCTION find_string(
	i_bal_small     IN VARCHAR2,
	i_bal_large     IN CLOB,
	i_pattern       IN VARCHAR2,
	i_offset        IN NUMBER DEFAULT 1,
	i_occurence     IN NUMBER DEFAULT 1)
RETURN NUMBER IS
	v_index  NUMBER;
BEGIN

	IF (use_balances_large = FALSE) THEN
		v_index := INSTR(i_bal_small, i_pattern, i_offset, i_occurence);
	ELSE
		v_index := DBMS_LOB.INSTR(i_bal_large, i_pattern, i_offset);
	END IF;

	RETURN v_index;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- find_string');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END find_string;

FUNCTION get_next_number(
	i_bal_small     IN VARCHAR2,
	i_bal_large     IN CLOB,
	i_pattern       IN VARCHAR2,
	i_start_index   IN NUMBER,
	o_end_index     OUT NUMBER)
RETURN VARCHAR2 IS
	-- Variables
	v_field_value   VARCHAR2(255);

	-- Exceptions
	e_invalidformat 	EXCEPTION;
BEGIN
	IF (use_balances_large = FALSE) THEN
		o_end_index := INSTR(i_bal_small, i_pattern, i_start_index);
		IF (o_end_index = 0) THEN
			RAISE e_invalidformat;
		ELSE
			v_field_value := RTRIM(SUBSTR(i_bal_small, i_start_index,
				o_end_index - i_start_index));
		END IF;
	ELSE
		o_end_index := DBMS_LOB.INSTR(i_bal_large, i_pattern, i_start_index);
		IF (o_end_index = 0) THEN
			RAISE e_invalidformat;
		ELSE
			v_field_value := RTRIM(DBMS_LOB.SUBSTR(i_bal_large,
					o_end_index - i_start_index, i_start_index));
		END IF;
	END IF;

	RETURN v_field_value;
	
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- get_next_number');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END get_next_number;

FUNCTION get_next_string(
	i_bal_small     IN VARCHAR2,
	i_bal_large     IN CLOB,
	i_pattern       IN VARCHAR2,
	i_start_index   IN NUMBER,
	o_end_index     OUT NUMBER)
RETURN VARCHAR IS
	-- Variables
	v_field_value  VARCHAR(255);

	-- Exceptions
	e_invalidformat 	EXCEPTION;
BEGIN
	IF (use_balances_large = FALSE) THEN
		o_end_index := INSTR(i_bal_small, i_pattern, i_start_index);
		IF (o_end_index = 0) THEN
			RAISE e_invalidformat;
		ELSE
			v_field_value := RTRIM(SUBSTR(i_bal_small, i_start_index + 1,
				o_end_index - i_start_index - 2));
		END IF;
	ELSE
		o_end_index := DBMS_LOB.INSTR(i_bal_large, i_pattern, i_start_index);
		IF (o_end_index = 0) THEN
			RAISE e_invalidformat;
		ELSE
			v_field_value := RTRIM(DBMS_LOB.SUBSTR(i_bal_large,
				o_end_index - i_start_index - 2, i_start_index + 1));
		END IF;
	END IF;

	RETURN v_field_value;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- get_next_string');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END get_next_string;

PROCEDURE process_monitor_impacts(
	i_bal_small IN VARCHAR,
	i_bal_large IN CLOB,
	i_offset IN NUMBER,
	o_bal_small IN OUT VARCHAR, 
	o_bal_large IN OUT CLOB, 
	o_offset IN OUT NUMBER)
IS
	-- Variables
	v_index NUMBER := 0;
	v_end_index NUMBER := 0;
	v_line VARCHAR(4000);
	v_line_len VARCHAR(4000);
	v_header VARCHAR2(255);
	v_account_obj_id0 VARCHAR(22);
	v_account_obj_db VARCHAR(22);
	v_account_obj_type_id_old NUMBER;
	v_account_obj_type_id NUMBER;
	v_amount VARCHAR(255);
	v_bal_grp_obj_id0 VARCHAR(22);
	v_bal_grp_obj_db VARCHAR(22);
	v_bal_grp_obj_type_id_old NUMBER;
	v_bal_grp_obj_type_id NUMBER;
	v_resource_id VARCHAR2(22);

BEGIN
	-- Format is 1:9232:0:1;21812;/account,6777,1;233232;/balance_group,76677
	-- Order Of the fields are
	-- PIN_FLD_ACCOUNT_OBJ
	-- PIN_FLD_AMOUNT
	-- PIN_FLD_BAL_GRP_OBJ
	-- PIN_FLD_RESOURCE_ID

	-- Read Header
	v_index := find_string(i_bal_small, i_bal_large, ser_delimiter, i_offset, 3);
	string_copy_from_bal(v_header, i_bal_small, i_bal_large, i_offset, v_index - i_offset);
	v_index := v_index + 1;

	-- Read account_obj_db
	v_account_obj_db := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read account_obj_id
	v_account_obj_id0 := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read class id account_obj_type_id
	v_account_obj_type_id_old := TO_NUMBER(get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index));
	v_index := v_end_index + 1; 

	-- Get the new class id.
	v_account_obj_type_id := get_new_classid(v_account_obj_type_id_old);

	-- Read amount
	v_amount := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read bal_grp_obj_db
	v_bal_grp_obj_db := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read bal_grp_obj_id
	v_bal_grp_obj_id0 := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read bal_grp_obj_type_id
	v_bal_grp_obj_type_id_old := TO_NUMBER(get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index));
	v_index := v_end_index + 1; 

	-- Get the new class id.
	v_bal_grp_obj_type_id := get_new_classid(v_bal_grp_obj_type_id_old);

	-- Read resource_id
	v_resource_id := get_next_number(i_bal_small, i_bal_large, SER_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	v_line := v_header || SER_DELIMITER || v_account_obj_db || POID_RECORD_DELIMITER || v_account_obj_id0 || POID_RECORD_DELIMITER || TO_CHAR(v_account_obj_type_id) || 
			SER_FIELD_VALUE_DELIMITER || v_amount || SER_FIELD_VALUE_DELIMITER || v_bal_grp_obj_db || POID_RECORD_DELIMITER || v_bal_grp_obj_id0 || 
			POID_RECORD_DELIMITER || TO_CHAR(v_bal_grp_obj_type_id) || SER_FIELD_VALUE_DELIMITER || v_resource_id || SER_RECORD_DELIMITER;

	v_line_len := LENGTH(v_line);
	string_copy_to_bal(v_line, o_bal_small, o_bal_large, o_offset, v_line_len);

	o_offset := o_offset + v_line_len;

	--DBMS_OUTPUT.PUT_LINE('DEBUG -- process_monitor_impacts');
	--DBMS_OUTPUT.PUT_LINE(v_line);

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- process_monitor_impacts');
	DBMS_OUTPUT.PUT_LINE(v_line);
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END process_monitor_impacts;

PROCEDURE process_sub_bal_impacts(
	i_bal_small IN VARCHAR,
	i_bal_large IN CLOB,
	i_offset IN NUMBER,
	o_bal_small IN OUT VARCHAR, 
	o_bal_large IN OUT CLOB, 
	o_offset IN OUT NUMBER)
IS
	-- Variables
	v_index NUMBER := 0;
	v_end_index NUMBER := 0;
	v_line VARCHAR(4000);
	v_line_len VARCHAR(4000);
	v_header VARCHAR2(255);
	v_bal_grp_obj_id0 VARCHAR(22);
	v_bal_grp_obj_db VARCHAR(22);
	v_bal_grp_obj_type_id_old NUMBER;
	v_bal_grp_obj_type_id NUMBER;
	v_resource_id VARCHAR2(22);

BEGIN
	-- Format is 1:7754:0:1;233232;/balance_group,76677
	-- Order Of the fields are
	-- PIN_FLD_BAL_GRP_OBJ
	-- PIN_FLD_RESOURCE_ID

	-- Read Header
	v_index := find_string(i_bal_small, i_bal_large, SER_DELIMITER, i_offset, 3);
	string_copy_from_bal(v_header, i_bal_small, i_bal_large, i_offset, v_index - i_offset);
	v_index := v_index + 1;

	-- Read bal_grp_obj_db
	v_bal_grp_obj_db := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read bal_grp_obj_id
	v_bal_grp_obj_id0 := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read bal_grp_obj_type_id
	v_bal_grp_obj_type_id_old := TO_NUMBER(get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index));
	v_index := v_end_index + 1; 

	-- Get the new class id.
	v_bal_grp_obj_type_id := get_new_classid(v_bal_grp_obj_type_id_old);

	-- Read resource_id
	v_resource_id := get_next_number(i_bal_small, i_bal_large, ser_record_delimiter, v_index, v_end_index);
	v_index := v_end_index + 1; 

	v_line := v_header || SER_DELIMITER || v_bal_grp_obj_db || POID_RECORD_DELIMITER || v_bal_grp_obj_id0 || POID_RECORD_DELIMITER ||
			TO_CHAR(v_bal_grp_obj_type_id) || SER_FIELD_VALUE_DELIMITER || v_resource_id || SER_RECORD_DELIMITER;

	v_line_len := LENGTH(v_line);
	string_copy_to_bal(v_line, o_bal_small, o_bal_large, o_offset, v_line_len);

	o_offset := o_offset + v_line_len;
	
	--DBMS_OUTPUT.PUT_LINE('DEBUG -- PROCESS_SUB_BAL_IMPACTS');
	--DBMS_OUTPUT.PUT_LINE(V_LINE);
	
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- process_sub_bal_impacts');
	DBMS_OUTPUT.PUT_LINE(v_line);
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END process_sub_bal_impacts;

PROCEDURE process_sub_balances(
	i_bal_small IN VARCHAR,
	i_bal_large IN CLOB,
	i_offset IN NUMBER,
	o_bal_small IN OUT VARCHAR, 
	o_bal_large IN OUT CLOB, 
	o_offset IN OUT NUMBER)
IS
	-- Variables
	v_index NUMBER := 0;
	v_end_index NUMBER := 0;
	v_line VARCHAR(4000);
	v_line_len VARCHAR(4000);
	v_header VARCHAR2(255);
	v_amount VARCHAR2(22);
	v_contributor_str VARCHAR2(255);
	v_grantor_obj_id0 VARCHAR(22);
	v_grantor_obj_db VARCHAR(22);
	v_grantor_obj_type_id_old NUMBER;
	v_grantor_obj_type_id NUMBER;
	v_rollover_data VARCHAR2(22);
	v_valid_from VARCHAR2(22);
	v_valid_from_details VARCHAR2(22);
	v_valid_to VARCHAR2(22);
	v_valid_to_details VARCHAR2(22);

BEGIN
	-- Format is 2:7753:0:0:21.345,"",1;/purchased_product;1743,549,1070544665,1070544224,1111,2222
	-- Order Of the fields are
	-- PIN_FLD_AMOUNT
	-- PIN_FLD_CONTRIBUTOR_STR
	-- PIN_FLD_GRANTOR_OBJ
	-- PIN_FLD_ROLLOVER_DATA
	-- PIN_FLD_VALID_FROM
	-- PIN_FLD_VALID_FROM_DETAILS
	-- PIN_FLD_VALID_TO
	-- PIN_FLD_VALID_TO_DETAILS

	-- Read Header
	v_index := find_string(i_bal_small, i_bal_large, SER_DELIMITER, i_offset, 4);
	string_copy_from_bal(v_header, i_bal_small, i_bal_large, i_offset, v_index - i_offset);
	v_index := v_index + 1;

	-- Read amount
	v_amount := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 
	
	-- Read contributor_str
	v_contributor_str := '"' || get_next_string(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index) || '"';
	v_index := v_end_index + 1; 

	-- Read grantor_grp_obj_db
	v_grantor_obj_db := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read grantor_grp_obj_id
	v_grantor_obj_id0 := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read grantor_grp_obj_type_id
	v_grantor_obj_type_id_old := TO_NUMBER(get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index));
	v_index := v_end_index + 1; 

	-- Get the new class id.
	v_grantor_obj_type_id := get_new_classid(v_grantor_obj_type_id_old);

	-- Read rollover_data
	v_rollover_data := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 
	
	-- Read valid_from
	v_valid_from := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read valid_from_details
	v_valid_from_details := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read valid_to
	v_valid_to := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read valid_to_details
	v_valid_to_details := get_next_number(i_bal_small, i_bal_large, SER_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	v_line := v_header || SER_DELIMITER || v_amount || SER_FIELD_VALUE_DELIMITER || v_contributor_str || SER_FIELD_VALUE_DELIMITER ||
			v_grantor_obj_db || POID_RECORD_DELIMITER || v_grantor_obj_id0 || POID_RECORD_DELIMITER ||
			TO_CHAR(v_grantor_obj_type_id) || SER_FIELD_VALUE_DELIMITER || v_rollover_data  || SER_FIELD_VALUE_DELIMITER ||
			v_valid_from || SER_FIELD_VALUE_DELIMITER || v_valid_from_details || SER_FIELD_VALUE_DELIMITER || 
			v_valid_to || SER_FIELD_VALUE_DELIMITER || v_valid_to_details || SER_RECORD_DELIMITER;

	v_line_len := LENGTH(v_line);
	string_copy_to_bal(v_line, o_bal_small, o_bal_large, o_offset, v_line_len);

	o_offset := o_offset + v_line_len;

	--DBMS_OUTPUT.PUT_LINE('DEBUG -- process_sub_balances');
	--DBMS_OUTPUT.PUT_LINE(v_line);
	
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- process_sub_balances');
	DBMS_OUTPUT.PUT_LINE(v_line);
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END process_sub_balances;

PROCEDURE process_monitor_sub_bal_imp(
	i_bal_small IN VARCHAR,
	i_bal_large IN CLOB,
	i_offset IN NUMBER,
	o_bal_small IN OUT VARCHAR, 
	o_bal_large IN OUT CLOB, 
	o_offset IN OUT NUMBER)
IS
	-- Variables
	v_index NUMBER := 0;
	v_end_index NUMBER := 0;
	v_line VARCHAR(4000);
	v_line_len VARCHAR(4000);
	v_header VARCHAR2(255);
	v_bal_grp_obj_id0 VARCHAR(22);
	v_bal_grp_obj_db VARCHAR(22);
	v_bal_grp_obj_type_id_old NUMBER;
	v_bal_grp_obj_type_id NUMBER;
	v_resource_id VARCHAR2(22);

BEGIN
	-- Format is 1:9233:0:1;233232;/balance_group,76677
	-- Order Of the fields are
	-- PIN_FLD_BAL_GRP_OBJ
	-- PIN_FLD_RESOURCE_ID

	-- Read Header
	v_index := find_string(i_bal_small, i_bal_large, SER_DELIMITER, i_offset, 3);
	string_copy_from_bal(v_header, i_bal_small, i_bal_large, i_offset, v_index - i_offset);
	v_index := v_index + 1;

	-- Read bal_grp_obj_db
	v_bal_grp_obj_db := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read bal_grp_obj_id
	v_bal_grp_obj_id0 := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read bal_grp_obj_type_id
	v_bal_grp_obj_type_id_old := TO_NUMBER(get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index));
	v_index := v_end_index + 1; 

	-- Get the new class id.
	v_bal_grp_obj_type_id := get_new_classid(v_bal_grp_obj_type_id_old);

	-- Read resource_id
	v_resource_id := get_next_number(i_bal_small, i_bal_large, SER_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	v_line := v_header || SER_DELIMITER || v_bal_grp_obj_db || POID_RECORD_DELIMITER || v_bal_grp_obj_id0 || POID_RECORD_DELIMITER ||
			TO_CHAR(v_bal_grp_obj_type_id) || SER_FIELD_VALUE_DELIMITER || v_resource_id || ser_record_delimiter;

	v_line_len := LENGTH(v_line);
	string_copy_to_bal(v_line, o_bal_small, o_bal_large, o_offset, v_line_len);

	o_offset := o_offset + v_line_len;

	--DBMS_OUTPUT.PUT_LINE('DEBUG -- process_mon_sub_bal_impacts');
	--DBMS_OUTPUT.PUT_LINE(v_line);

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- process_mon_sub_bal_impacts');
	DBMS_OUTPUT.PUT_LINE(v_line);
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END process_monitor_sub_bal_imp;

PROCEDURE process_monitor_sub_balances(
	i_bal_small IN VARCHAR,
	i_bal_large IN CLOB,
	i_offset IN NUMBER,
	o_bal_small IN OUT VARCHAR, 
	o_bal_large IN OUT CLOB, 
	o_offset IN OUT NUMBER)
IS
	-- Variables
	v_index NUMBER := 0;
	v_end_index NUMBER := 0;
	v_line VARCHAR(4000);
	v_line_len VARCHAR(4000);
	v_header VARCHAR2(255);
	v_amount VARCHAR2(22);
	v_contributor_str VARCHAR2(255);
	v_grantor_obj_id0 VARCHAR(22);
	v_grantor_obj_db VARCHAR(22);
	v_grantor_obj_type_id_old NUMBER;
	v_grantor_obj_type_id NUMBER;
	v_valid_from VARCHAR2(22);
	v_valid_from_details VARCHAR2(22);
	v_valid_to VARCHAR2(22);
	v_valid_to_details VARCHAR2(22);

BEGIN
	-- Format is 2:7753:0:0:21.345,"",1;/purchased_product;1743,1070544665,1070544224,1111,2222
	-- Order Of the fields are
	-- PIN_FLD_AMOUNT
	-- PIN_FLD_CONTRIBUTOR_STR
	-- PIN_FLD_GRANTOR_OBJ
	-- PIN_FLD_VALID_FROM
	-- PIN_FLD_VALID_FROM_DETAILS
	-- PIN_FLD_VALID_TO
	-- PIN_FLD_VALID_TO_DETAILS

	-- Read Header
	v_index := find_string(i_bal_small, i_bal_large, SER_DELIMITER, i_offset, 4);
	string_copy_from_bal(v_header, i_bal_small, i_bal_large, i_offset, v_index - i_offset);
	v_index := v_index + 1;

	-- Read amount
	v_amount := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 
	
	-- Read contributor_str
	v_contributor_str := '"' || get_next_string(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index) || '"';
	v_index := v_end_index + 1; 

	-- Read grantor_grp_obj_db
	v_grantor_obj_db := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read grantor_grp_obj_id
	v_grantor_obj_id0 := get_next_number(i_bal_small, i_bal_large, POID_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read grantor_grp_obj_type_id
	v_grantor_obj_type_id_old := TO_NUMBER(get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index));
	v_index := v_end_index + 1; 

	-- Get the new class id.
	v_grantor_obj_type_id := get_new_classid(v_grantor_obj_type_id_old);

	-- Read valid_from
	v_valid_from := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read valid_from_details
	v_valid_from_details := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read valid_to
	v_valid_to := get_next_number(i_bal_small, i_bal_large, SER_FIELD_VALUE_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	-- Read valid_to_details
	v_valid_to_details := get_next_number(i_bal_small, i_bal_large, SER_RECORD_DELIMITER, v_index, v_end_index);
	v_index := v_end_index + 1; 

	v_line := v_header || SER_DELIMITER || v_amount || SER_FIELD_VALUE_DELIMITER || v_contributor_str || SER_FIELD_VALUE_DELIMITER ||
			v_grantor_obj_db || POID_RECORD_DELIMITER || v_grantor_obj_id0 || POID_RECORD_DELIMITER ||
			TO_CHAR(v_grantor_obj_type_id) || SER_FIELD_VALUE_DELIMITER || v_valid_from || SER_FIELD_VALUE_DELIMITER ||
			v_valid_from_details || SER_FIELD_VALUE_DELIMITER || v_valid_to || SER_FIELD_VALUE_DELIMITER ||
			v_valid_to_details || SER_RECORD_DELIMITER;

	v_line_len := length(v_line);
	string_copy_to_bal(v_line, o_bal_small, o_bal_large, o_offset, v_line_len);

	o_offset := o_offset + v_line_len;

	--DBMS_OUTPUT.PUT_LINE('DEBUG -- process_monitor_sub_balances');
	--DBMS_OUTPUT.PUT_LINE(v_line);
	
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- process_monitor_sub_balances');
	DBMS_OUTPUT.PUT_LINE(v_line);
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END process_monitor_sub_balances;

PROCEDURE fix_event_data (
	i_bal_small IN VARCHAR2, 
	i_bal_large IN CLOB, 
	o_bal_small IN OUT VARCHAR2, 
	o_bal_large IN OUT CLOB)
IS
	-- Variables
	v_tmp_offset NUMBER := 0;
	i_offset NUMBER := 0;
	o_offset NUMBER := 0;
	v_length NUMBER := 0;
	v_version VARCHAR(255);
	v_line VARCHAR(4000);
	v_bal_large CLOB;
	v_sub_bal_impacts BOOLEAN := FALSE;
	v_monitor_sub_bal_impacts BOOLEAN := FALSE;

	-- Exceptions
	e_invalidformat  EXCEPTION;
BEGIN
	use_balances_large := FALSE;
	
	IF (NVL(DBMS_LOB.GETLENGTH(i_bal_large),0) <> 0) THEN
		DBMS_LOB.CREATETEMPORARY(v_bal_large, TRUE);
		use_balances_large := TRUE;
	END IF;

	--
	-- Get the total data length.
	-- 
	v_length := string_length(i_bal_small, i_bal_large);

	--
	-- Copy the Version Number.
	--
	v_tmp_offset := find_string(i_bal_small, i_bal_large, SER_RECORD_DELIMITER, 1);
	v_version := substr_string(i_bal_small, i_bal_large, 1, v_tmp_offset);
	string_copy_to_bal(v_version, o_bal_small, v_bal_large, 1, v_tmp_offset);
	i_offset := v_tmp_offset + 1; -- Point to next line.
	o_offset := v_tmp_offset + 1; -- Point to next line.

	--DBMS_OUTPUT.PUT_LINE('DEBUG -- fix_event_data');
	--DBMS_OUTPUT.PUT_LINE('--' || v_version || '--');
  
	WHILE (i_offset < v_length)
	LOOP
		v_tmp_offset := find_string(i_bal_small, i_bal_large, SER_RECORD_DELIMITER, i_offset);
		v_line := substr_string(i_bal_small, i_bal_large, i_offset, v_tmp_offset - i_offset);

		IF (find_string_str(v_line, mon_impacts_prefix) <> 0) THEN
			process_monitor_impacts(i_bal_small, i_bal_large, i_offset, o_bal_small, v_bal_large, o_offset);
			v_sub_bal_impacts := FALSE;
			v_monitor_sub_bal_impacts := FALSE;
		ELSIF (find_string_str(v_line, sub_bal_impacts_prefix) <> 0) THEN
			process_sub_bal_impacts(i_bal_small, i_bal_large, i_offset, o_bal_small, v_bal_large, o_offset);
			v_sub_bal_impacts := TRUE;
			v_monitor_sub_bal_impacts := FALSE;
		ELSIF (find_string_str(v_line, sub_balances_prefix) <> 0) THEN
			IF (v_sub_bal_impacts = TRUE) THEN
				process_sub_balances(i_bal_small, i_bal_large, i_offset, o_bal_small, v_bal_large, o_offset);
			ELSIF (v_monitor_sub_bal_impacts = TRUE) THEN
				process_monitor_sub_balances(i_bal_small, i_bal_large, i_offset, o_bal_small, v_bal_large, o_offset);
			ELSE
				RAISE e_invalidformat;
			END IF;
		ELSIF (find_string_str(v_line, mon_sub_bal_impacts_prefix) <> 0) THEN
			process_monitor_sub_bal_imp(i_bal_small, i_bal_large, i_offset, o_bal_small, v_bal_large, o_offset);
			v_monitor_sub_bal_impacts := TRUE;
			v_sub_bal_impacts := FALSE;
		ELSE
			i_offset := v_length + 1;
		END IF;

		v_tmp_offset := find_string(i_bal_small, i_bal_large, SER_RECORD_DELIMITER, i_offset);
		IF (v_tmp_offset <> 0) THEN
			i_offset := v_tmp_offset + 1;
		END IF;

	END LOOP;

	IF (use_balances_large = TRUE) THEN
		o_bal_large := v_bal_large;
	END IF;

	use_balances_large := FALSE;

EXCEPTION
WHEN e_invalidformat THEN
	DBMS_OUTPUT.PUT_LINE(' ');
	DBMS_OUTPUT.PUT_LINE('ERROR -- fix_event_data');
	RAISE_APPLICATION_ERROR(ERR_INVALID_FORMAT, 'invalid format');
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- fix_event_data');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END fix_event_data;

PROCEDURE update_event_data (
	i_obj_id0 IN NUMBER, 
	i_bal_small IN VARCHAR2, 
	i_bal_large IN CLOB)
IS
BEGIN

	EXECUTE IMMEDIATE 'UPDATE '
		|| 'event_essentials_t SET balances_small = :bal_small, '
		|| 'balances_large = :bal_large WHERE obj_id0 = :obj_id0' 
		USING i_bal_small, i_bal_large, i_obj_id0;
	
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- update_event_data');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END update_event_data;

PROCEDURE update_events (i_commit_size IN NUMBER DEFAULT 100)
IS
	-- Variable
	v_batch_size NUMBER := 0;
	v_records_size NUMBER := 0;
	v_total_size NUMBER := 0;
	o_bal_small  VARCHAR2(4000) := NULL;
	o_bal_large  CLOB := NULL;
	v_event_batch_changed BOOLEAN := FALSE;	

	-- Cursor
	CURSOR evt_records IS SELECT * FROM tmp_event_essentials;

BEGIN

	-- Truncate the temp table.
	EXECUTE IMMEDIATE 'TRUNCATE TABLE tmp_event_essentials';

	-- Populate the temp table.
	EXECUTE IMMEDIATE 'INSERT INTO '
			|| 'tmp_event_essentials SELECT obj_id0, balances_small, ' 
			|| 'balances_large FROM event_essentials_t'; 
	COMMIT;

	FOR evt IN evt_records
	LOOP
	        event_essentials_changed := FALSE;	
		v_records_size := v_records_size + 1;

		o_bal_small := NULL;
		o_bal_large := NULL;

		-- Fix the class id's for the event data.
		fix_event_data (evt.balances_small, 
				evt.balances_large, o_bal_small, o_bal_large);

		IF (event_essentials_changed = TRUE) THEN
			-- Update the fixed class id's for the event data.
			update_event_data (evt.obj_id0, o_bal_small, o_bal_large);
			v_batch_size := v_batch_size + 1;
			v_event_batch_changed := TRUE;
		END IF;

		IF (v_batch_size = i_commit_size) THEN
			-- Commit size reached. Do a commit.
			IF (v_event_batch_changed = TRUE) THEN
				COMMIT;
				v_total_size := v_total_size + v_batch_size;
				v_batch_size := 0;
				v_event_batch_changed := FALSE;
				DBMS_OUTPUT.PUT_LINE('INFO -- update_events ' || v_total_size || ' records commited');
			END IF;
		END IF;
	END LOOP;

	IF (v_batch_size <> 0) THEN
		COMMIT;
		v_total_size := v_total_size + v_batch_size;
		DBMS_OUTPUT.PUT_LINE('INFO -- update_events ' || v_total_size || ' records commited');
	END IF;

	DBMS_OUTPUT.PUT_LINE('INFO -- update_events done -- ' || v_total_size || ' -- records commited');
	DBMS_OUTPUT.PUT_LINE('INFO -- update_events done -- ' || v_records_size || ' -- records processed');

	EXECUTE IMMEDIATE 'TRUNCATE TABLE tmp_event_essentials';

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- update_events commit size ' || TO_CHAR(i_commit_size));
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE; 
END update_events;

PROCEDURE update_event (i_poid_id0 IN NUMBER)
IS
	-- Variable
	o_bal_small  VARCHAR2(4000) := NULL;
	o_bal_large  CLOB := NULL;
	i_bal_small  VARCHAR2(4000) := NULL;
	i_bal_large  CLOB := NULL;

BEGIN
	event_essentials_changed := FALSE;	

	SELECT balances_small, balances_large INTO i_bal_small, i_bal_large FROM event_essentials_t WHERE obj_id0 = i_poid_id0;

	-- Fix the class id' for the event data.
	fix_event_data (i_bal_small, i_bal_large, 
			o_bal_small, o_bal_large);

	--DBMS_OUTPUT.PUT_LINE('DEBUG -- UPDATE_EVENT ');
	--IF (NVL(DBMS_LOB.GETLENGTH(O_BAL_LARGE),0) = 0) THEN
	--	DBMS_OUTPUT.PUT_LINE(O_BAL_SMALL);
	--ELSE
	--	DBMS_OUTPUT.PUT_LINE(O_BAL_LARGE);
	--END IF;

	-- Update the fixed class id' for the event data.
	IF (event_essentials_changed = TRUE) THEN
		update_event_data (i_poid_id0, o_bal_small, o_bal_large);
		
		COMMIT;
	END IF;

	DBMS_OUTPUT.PUT_LINE('INFO -- update_event obj_id0 ' || i_poid_id0 || ' record commited');
EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- update_event input poid ' || TO_CHAR(i_poid_id0));
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE; 
END update_event;

FUNCTION is_vc_enabled
RETURN BOOLEAN IS
	-- Variables
	v_virtual_flag	NUMBER := 0;
	v_return	BOOLEAN := FALSE;
        v_vcol_exists   NUMBER := 0;
        v_event_type    VARCHAR2(16) := '/event';

BEGIN
        select count(*) into v_vcol_exists from user_tab_cols where table_name = 'DD_OBJECTS_T' and column_name = 'VIRTUAL_FLAG';
        if (v_vcol_exists > 0) THEN
                EXECUTE IMMEDIATE 'select virtual_flag FROM  dd_objects_t where name like :event_type' INTO v_virtual_flag using v_event_type;

                IF (v_virtual_flag = 1) THEN
                        v_return := TRUE;
                END IF;
        END IF;
        RETURN v_return;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- is_vc_enabled');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END is_vc_enabled;

PROCEDURE update_virtual_column (
	table_name VARCHAR2,
	column_name VARCHAR2)
IS
	-- Variables
	v_stmt VARCHAR2(4000) := 0;
BEGIN

	v_stmt := 'UPDATE ' || table_name || ' SET ' ||
		column_name || ' = pin_fix_dd.get_new_classid(' || column_name ||
		') WHERE ' || column_name || ' != pin_fix_dd.get_new_classid(' ||
		column_name || ') AND ' || column_name || ' IS NOT NULL';	
	
	EXECUTE IMMEDIATE v_stmt;

	COMMIT;

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- update_virtual_column ' ||  v_stmt);
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END update_virtual_column;

PROCEDURE update_by_partition (
	i_table_name VARCHAR2,
	i_column_name VARCHAR2)
IS
	-- Variables
	v_tab_part_name VARCHAR2(255);
	v_table_name VARCHAR2(32) := UPPER(i_table_name);
	

	-- Cursors
	CURSOR partition_record IS 
		SELECT partition_name 
		FROM user_tab_partitions 
		WHERE table_name = v_table_name;
BEGIN

	DBMS_OUTPUT.PUT_LINE('INFO -- Begin processing table ' || i_table_name || ' column ' || i_column_name);
	FOR part_rec IN partition_record
	LOOP
		v_tab_part_name := i_table_name || ' PARTITION (' || 
			part_rec.partition_name || ')';

		update_virtual_column(v_tab_part_name, i_column_name);
		DBMS_OUTPUT.PUT_LINE('INFO -- Done processing partition ' || part_rec.partition_name);
	END LOOP;

	DBMS_OUTPUT.PUT_LINE('INFO -- Done processing table ' || i_table_name || ' column ' || i_column_name);

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- update_by_partition');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END update_by_partition;

PROCEDURE update_virtual_columns
IS
	v_col_name VARCHAR2(50);

	CURSOR vc_columns_record IS 
		SELECT t1.sm_item_name AS table_name,
       		t2.sm_item_name AS column_name
		FROM dd_objects_fields_t t1, dd_objects_fields_t t2 
		WHERE t1.sm_item_name NOT LIKE 'event_essentials_t' 
		AND t2.field_type = 7 AND t2.parent_element_id = t1.rec_id 
		AND t1.obj_id0 IN 
		(SELECT obj_id0 FROM dd_objects_t WHERE name LIKE '/event' OR name LIKE '/event/%');
BEGIN
	IF (is_vc_enabled() = FALSE) THEN
		DBMS_OUTPUT.PUT_LINE('INFO -- Virtual Column disabled');
		DBMS_OUTPUT.PUT_LINE('INFO -- Done with virtual column update ');
		
		RETURN;
	END IF;

	FOR vc_cols IN vc_columns_record
	LOOP
		v_col_name := SUBSTR(vc_cols.column_name, 2) || '_type_id';
		update_by_partition(vc_cols.table_name, v_col_name);

	END LOOP;

	DBMS_OUTPUT.PUT_LINE('INFO -- Done with virtual column update ');

EXCEPTION
WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('ERROR -- update_virtual_columns');
	DBMS_OUTPUT.PUT_LINE(sqlerrm);
	RAISE;
END update_virtual_columns;

END pin_fix_dd;
/

SHOW ERRORS;

CREATE OR REPLACE PROCEDURE test_conversion 
IS
	i_bal_small VARCHAR(4000);
	o_bal_small VARCHAR(4000);
	i_bal_large CLOB;
	o_bal_large CLOB;
BEGIN
 
	i_bal_small := 'C1,3.0
1:9232:0:1;2181255147;1000,6777,1;2181255147;1021,876
1:7754:0:1;2181255147;1021,6777
2:7753:0:0:21.345,"",1;111;1809,549,1070544665,1070544224,1111,2222
2:7753:1:0:35.675,"",1;111;1809,747,1071588567,1070564300,3333,4444
1:7754:1:1;2181255147;1021,7001
2:7753:0:1:10.0589,"",1;111;1809,840,1071588567,1070545000,0,0
2:7753:1:1:21.89,"Testing",1;111;1809,240,1071588567,1070544300,0,0
1:9233:0:1;2181255147647;1021,7001
2:7753:0:0:10.0589,"",1;111;1809,1071588567,1070545000,0,0
2:7753:1:0:21.89,"Testing",1;111;1809,1071588567,1070544300,0,0
';	

	i_bal_large := NULL;
	o_bal_small := NULL;
	o_bal_large := NULL;

	pin_fix_dd.fix_event_data(i_bal_small, 
		i_bal_large, o_bal_small, o_bal_large);

	DBMS_OUTPUT.PUT_LINE('DEBUG -- test_conversion  bal_small');
	DBMS_OUTPUT.PUT_LINE('DEBUG -- input bal_small');
	DBMS_OUTPUT.PUT_LINE(i_bal_small);
	DBMS_OUTPUT.PUT_LINE('DEBUG -- output bal_small');
	DBMS_OUTPUT.PUT_LINE(o_bal_small);

	i_bal_large := TO_CLOB('C1,3.0
1:9232:0:1;2181255147;1000,6777,1;2181255147;1021,876
1:7754:0:1;2181255147;1021,6777
2:7753:0:0:21.345,"",1;111;1809,549,1070544665,1070544224,1111,2222
2:7753:1:0:35.675,"",1;111;1809,747,1071588567,1070564300,3333,4444
1:7754:1:1;2181255147;1021,7001
2:7753:0:1:10.0589,"",1;111;1809,840,1071588567,1070545000,0,0
2:7753:1:1:21.89,"Testing",1;111;1809,240,1071588567,1070544300,0,0
1:9233:0:1;2181255147647;1021,7001
2:7753:0:0:10.0589,"",1;111;1809,1071588567,1070545000,0,0
2:7753:1:0:21.89,"Testing",1;111;1809,1071588567,1070544300,0,0
');	

	i_bal_small := NULL;
	o_bal_small := NULL;
	o_bal_large := NULL;

	pin_fix_dd.fix_event_data(i_bal_small, i_bal_large, 
			o_bal_small, o_bal_large);

	DBMS_OUTPUT.PUT_LINE('DEBUG -- test_conversion  bal_large');
	DBMS_OUTPUT.PUT_LINE('DEBUG -- input bal_large');
	DBMS_OUTPUT.PUT_LINE(i_bal_large);
	DBMS_OUTPUT.PUT_LINE('DEBUG -- output bal_large');
	DBMS_OUTPUT.PUT_LINE(o_bal_large);

END test_conversion;
/

SHOW ERRORS;
