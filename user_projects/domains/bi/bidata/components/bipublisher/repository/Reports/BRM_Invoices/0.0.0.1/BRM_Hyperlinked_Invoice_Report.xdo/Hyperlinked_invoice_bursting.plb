DECLARE
   v_ddl_stmt VARCHAR2(100);
   v_count NUMBER;
BEGIN
   SELECT COUNT(table_name) INTO v_count FROM user_tables WHERE table_name = 'INVOICE_CHUNK_IDS';
   IF v_count <>0 THEN
   v_ddl_stmt :=  'drop table INVOICE_CHUNK_IDS';
   EXECUTE IMMEDIATE v_ddl_stmt;
   END IF;
END;
/
SHOW errors;
CREATE  global temporary TABLE INVOICE_CHUNK_IDS
(
  count  NUMBER,
  first  NUMBER,
  last  NUMBER
) on commit delete rows ;
/
SHOW errors;
CREATE OR REPLACE PACKAGE InvTypes wrapped 
a000000
367
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
9
140 e7
JTKlW58p8ud80kHCQTF5Qsmbz0Ywg5m49TOf9b9cpUfVmSZWWmIruHSLnvR0pp7OAjoSe5g5
OgfVMDnVNr57+Fu+Ebg+ZzWpnbAMNLBt+1mTz+McWVqUGkzrq1WOwVAOcLXK45NIni8c5Wau
H37fvkI5RAePwmBb4kfG9wRc//lrP6ieP2u83OI17H1hC8eoyIjTq10HaZHXQ/zB4Qas0jm6
gqamYNMJRg==

/
SHOW errors;
CREATE OR REPLACE PACKAGE INV wrapped 
a000000
367
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
9
17a 107
jbVtnIBctuMCCcBAl9I/HUxRJyUwgxDQrcvhf3TpJseenMqo0XxcBnVY50uASmo8XfnEyjVn
r4ubHnOVA8aQLL3TLK8XwcmUGlSJcBQKLo1Gw1LFNLp7MJiPsrDs6w34N9moyOIkTX6HO4Mk
Rlf5W0GEimWamNP98JpnjV7pPn6mCYq/h9jyFqsSVFu6NXL/E4BeGFQhbT9X6tbHBRURoQRZ
xblsVk9O/wcQKHQuuu1u8iuJa9bXBYfNAWoGORHMXgk=

/
SHOW errors;
CREATE OR REPLACE PACKAGE BODY INV wrapped 
a000000
367
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
b
ff8 55a
+C0vIEpXrHOJA7pSXnUvzQ3RDVAwg83qeW0FVy+5weSeVQfxztFWMQKGDr5MSwGtf/YMNfG/
A3NmJVWgGlahoevmayT5YMI7nLT6ea0WaFL7uxslgiByXyGG6V8ghog1vQwsady7aVY51q+s
glklGLYh7wmvZdl/zDCHswWzpqQQ8VQGvtM6uuGeLzuXRqVSW2yRR2PxwcpG6MH7O++bODh+
Q8PxkyzIAxICk+ls5tjxsIFjGLZHMOWN3soEUEWV6Qs+rlKVRIak+lpOjlSCVx7JDkQzHs0m
lC0Pb3RuhV4KU589+wXIuoUIvPqh/QpVgCDis10Ew+bIwYmJCJvbvMhjor9/xk51D/DiG7eh
IaQUkafrNZwIg/V4CXaZ05FQuWhyvenqWhWdy7MAMsOr/YQ1nqxsg36dud/Q9jJTzqAFeibX
6xrvJT9l//IHgITScxIf2ne5Z+7a7U8oCmqccucVez7CgyJC4dD4gfxLP+G2eLFg22+10KG1
k5mxxlEPjicfwpB60lB80vFwBEHkfkDGfVWLOkIDEJ340EukGIOPn7siJyvdFx9kQ/x+jiI/
DQ8gKPxzTvxqOn2qFEOctbDkmvGb/dLgvj2Hc4SAh1SEZ1++Ye1sYanCm6uHOdDiHCgJfGF9
h7WINz6vnEaL14MzwaOyk4vC4kxbEC5YRw7EGkH3DppTLJ1r2fkZ5xa1FyjcxCRnk9Bxmf/h
sx5esJcykw/wcgFBLq72gdRNnKSDbp4VAdcLfFE3TDdgFtm+yAvD25JkLdM1tpbF4RM8sS1t
P4raji61GTfvP0lVcNZETB8Z09EEdDbR2RCCavOheJa5OCRtE9wOi89TvmVOycaLSHMNvGXa
h62Uze4h3KxIwtuRqMdgatmQ+5Rx0rbAwFbry7/JI1QskZSVgznxWTUn8cxtVKcCHNC2VG0v
ScIGw8HRNULNwGvzYNuLPc/rzZGtbt8Ery3gkxvj2OsLOb/wOnPQb/GeMSi+fvNEkD5WnN/G
b/cbY2lw/mZsk3GUCZRSsnlsuwvcx3se8t/pHi4DaceMfDA3j+Gsa1MWcIqwJoAzhas53Jnm
F8C5bWBF4IyF5zbewuB1s9oWw/p0QzWrXuHPIXGHmjAhB7t/7LTb8SAOQVuo39HNEuZtDUHd
HTLiZE9SsbKcp4OUnOXighxhOZiVL9jtK1S0nCyaE9/QI9qJ5YLZytYMMQQRl2bbAoggyNfg
XaS030PiYD835eOS0I0IKIeOH400qYCUrWyMqDG7vxLSUwU/TLsoE81b9bQ9sI+lzeuSLgAL
zmHQGUJ5uufRt4savqC/0ay3nGfv5ZmfJ8vPxxoThihDfxCBH1NZmBQ=

/
