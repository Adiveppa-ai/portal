/
/ $Header: optional_mgrs_vob/brm_integrations/jca_adapter/test_jca/readme.txt /cgbubrm_7.5.0.portalbase/1 2015/11/27 04:03:17 nishahan Exp $
/
/ readme.txt
/
/ Copyright (c) 2012, Oracle. All Rights Reserved.
/
/   NAME
/     readme.txt - Test multiple opcodes in parallel  
/
/   DESCRIPTION
/   java program which can invoke JCA servlet (as deployed on the weblogic server) and can send multiple parallel requests to the servlet.  
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/
/   MODIFIED   (MM/DD/YY)
/   ndharrni    07/09/12 - Creation
/
How to Test JCA from windows command line
JcaTest is a java program which can invoke JCA servlet (as deployed on the weblogic server) and can send multiple parallel requests to the servlet. This enables JCA testing in multithreaded environment.  
For each request . JCA connects to BRM (internally to CM), hence number of max thread for the test will depend upon the number of connections configured from JCA. In weblogic server, usually configuration can be changed thru weblogic server console. Currently this test program supports only XA mode of transaction.

.	Pre-requisite for  JCA  End-to-End test
Note . all the test steps below are for weblogic server installed in windows environment.  On a different platform, test steps may need to be alerted appropriately.
1)	Deploy OracleBRMJCA15Adapter.rar
2)	Deploy  weblogic_startup.jar
3)	Deploy  BRMAdapterServletClient.war

Refer - Deploy BRM-JCA on weblogic Server
 http://ocinfodev.us.oracle.com/final/brm/74/wwhelp/wwhimpl/js/html/wwhelp.htm.

.	Setting up JCA test directory
Create a directory in windows, For example in my C drive I created a dir jca_test
testDir  = .C:/jca_test..

.	Generate test files, one file for each opcode. The file test file should be named as test1,test 2 , test3
Say I want to run 3 opcodes in parallel, then I will generate 3 files under the directory C:\jca_test.
As below --
C:/jca_test/test1
C:/jca_test/test2
C:/jca_test/test3
Each test file will need two parameters - Opcode name and the input XML

Example  file test1 .
#Test file to test  PCM_OP_READ_OBJ opcode  ( all lines starting with # will be consider as a comment)
OPCODE=PCM_OP_READ_OBJ;
MESSAGE=<PCM_OP_READ_OBJ_inputFlist xmlns:brm="http://xmlns.oracle.com/BRM/schemas/BusinessOpcodes" xmlns="http://xmlns.oracle.com/BRM/schemas/BusinessOpcodes">
<POID>0.0.0.1 /account 1 0</POID>
</PCM_OP_READ_OBJ_inputFlist>;

Note: end of the opcode name/message  should  have a semicolon (. ;.) at the end.

.	Copy testJca.jar file and runJca.bat in the test directory.

.	Verify PATH variable has and entry for JAVA . For example .
On Cmd line  enter ->  java .version and then javac . version 
These commands should show correct JAVA path.

.	Modify Sample_runJca.bat  to pass in correct arguments,  this file takes classpath and three command line arguments .
**-Please note-Sample_runJca.bat file is just an example, you can name file whatever you want; or you can run the command directly from the command 
** line prompt; 
--Sample classpath is 
-classpath C:\jca_test\testJca.jar    ( modify as per your test directory)
1 ) testDir  ( For example in this doc , the test Dir is C:\jca_test)

2) number of tests to run in parallel (For example in this doc , number of thread are 3

3) target URL,( enter the correct URL for the servlet client, for example -
Target URL is - > http://10.132.174.227:7001/BRMAdapterServletClient/BRMAdapterServletClient)
where 10.132.174.227 is host IP  -- change it as per your PC.
7001 is the weblogicServer port address, change it, if weblogic port address is different on your test system.
Rest in the URL will remain same


.	On cmd line prompt
Enter  - cd <test dir>
Enter  - runJca.bat ( or type in the command which is in the Sample_runJca.bat manually )

.	Test results .
For each test case, one test.out file will be generated in the test directory, which will have outputXML .
(Additionally on cmd line prompt each thread will flush its output, generally if the response is really big so checking the test.out will be more convenient)





