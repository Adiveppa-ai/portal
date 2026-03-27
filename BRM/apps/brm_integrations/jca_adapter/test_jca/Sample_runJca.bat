@@
@ Below is a sample command that can be run from windows or Unix/Linux command line prompt.
@ Make sure you are in java home.
@ The command ->>
	"java -XX:+UseCompilerSafepoints -classpath <absolute path for JAR file>  -mx256m test.test <absolute path to the test Directory> <num of files to run in parallel>
  	<Target URL of the servletClient>"
@ Example ->>
@ if the testDir is C:\jca_test , number of files to run is  3, and the test computer host IP address is  10.132.174.227 then,
@the following entry  can be entered to a runJca.bat file for windows OR runJca.sh for Unix environment, and run the runJca file from the  Command line prompt
@ Alternatively, you can also run the command directly from the commnad line prompt ->>

@ "java -XX:+UseCompilerSafepoints -classpath C:\jca_test\testJca.jar  -mx256m test.test C:\jca_test 3
http://10.132.174.227:7001/BRMAdapterServletClient/BRMAdapterServletClient "

@@

