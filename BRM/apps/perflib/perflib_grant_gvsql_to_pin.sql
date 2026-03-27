/* Copyright (c) 2021, Oracle and/or its affiliates. */
/*----------------------------------------------------------------------------+
 | MODULE: perflib_grant_gvsql_to_pin.sql
 |
 | DESCRIPTION:
 |
 | Grants access to the gv$sql view to the pin user. This must be done as the
 | DBA (sys user).
 |
 | INFORMATION:
 |
 | BRM Performance Tuning ...
 |
 | REVISION:
 |
 | $Revision: 1.2 $
 | $Author: ihargrea $
 | $Date: 2020/11/30 11:05:47 $
 +----------------------------------------------------------------------------*/
GRANT SELECT ON gv_$sql TO pin;
exit;
