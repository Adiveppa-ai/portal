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
1140 597
pcS/8n+Ift91RDLnsLBMgoChgqowg81UuiAF344ZA6pE/mm0o/DdvXx0TR8d0+kx5mwlyibb
KZnuG0jBYksdxmJ8DiQ/B4miCaeJvn18fmeyhR+b2nrEu8gHh0DOeVdJFuAIpPIpsp6VcHxU
wEChcbisi6LFBMk+G56WnpKfIWdJZBaJMGuikkrd4eNvQqLOUwLTZV0J+pzKRtSWHSeEXVUl
ffImFE7RyhfEngOs8kZUqPixbZRJdQhUlug3DmdkYtHFLt5fmdEEIKE5e9yyeTkX137Y4U5D
0ncYtJYMOWAaLUxTIT379pz2hSk0+qHNCpCAIOKzXY6J1reWYvEHCkFCqMf0SOZKH6idq0wu
G7dwe+OFemPWn9sMPXmuUhZa79afi581FkXm0yKjN7mPzEj1dET656cRmPg0mhkgdwgG3p0Q
aQUHoQwaP2xuQ8skYLvE0NAFVQfte1GokptjYnh36DXzV6RyxoEI64LhHxLpPJhbro/5S5Ms
eCgO4J95on6oz5DSZGO4k2bB46PBM7uqscz7E5Cd3yuWI3/m7w+RELSKSvxqhpKGguw1piHb
Ew8sd1h71oc7+B2b7bV5x7UHIz8jaDwnqLlzFWnG3eR94tbThNDIQHm3u374ZC070CcP7hAf
D/nzRXE/sNm1AtGC9WFoOto8eMDn4QtKJCDjYjcrh4bI3YwxhjVl1KfNCyGoUHk68VA2LUXw
uIDfk2PCXeLWvFFZG7hgxkHx1L7NPzRgnFUAOQ7kT6RXVWCml6Ndo1gaqCNV6lziugicCAtY
G+v5XO2f0jRRLibKcadSfqBFDurdqHUacYV/l+ZzSKA2UHQBRDeh9h60QiQzsp7oqiDdoc9J
eRf9HewfGS//BCEr0dlM7bGhyMkXT6q1K36jSuySuHNCBoGPPRmSXr4BYdjADHeV3l9GDfqe
t2NZiHlIuXTmr+m/ZyMFunm4Hkg2htYaDlQeZ/E+Wi4h5fMKeuuxX+fU4dv0Vlc9vm1po+xu
3kbzLUIqmtJSwqvc1V+PVC0U86KnKX8fyvA6Opyr05kxsr7Y84iQ1Vbq38Zv84C+aQ7+Zhuh
VJEJATi9O2wghNxeeyAMKxqBSETdvszrQjdwHazZ6aevgfTUh0uAK3/bIe/10R+8EQ6I/TZg
Dvcb1UCI7ftR8snmGVoLWcocXFZkF4d1E/41pLSFOZpnAJnstHzE/jur9mI3WzDixE9SBXSc
pyWOnOVhfxxhNpivG1S6O0tLnFqa7HvQI0U+XMmnNTnqwglps1H09sk05ivWN+pLMpekgD8h
VSMXk4j4jxXtVl1EesUMPoiy+u6mH6n4c7lOi7houSJRhrzYrIZPrhN4AdDuHiI6u90cmfDX
GuUhnDM8YFCYvcNR7EteXqVcoepDKNJ1+aUfIU2k5w==

/
