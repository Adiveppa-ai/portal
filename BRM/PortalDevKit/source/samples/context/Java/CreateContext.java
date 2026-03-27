/*********************************************************************
 * Copyright (c) 2000, 2024, Oracle and/or its affiliates. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 *
 *********************************************************************/

/*********************************************************************
 * This example shows how to use PortalContext object that creates
 * and manages connections to Infranet.
 *
 * A PortalContext has to be created before any opcodes may be called.
 *********************************************************************/

import com.portal.pcm.*;
import com.portal.pcm.fields.*;
import java.util.Properties;

public class CreateContext {

	/* MODIFY FOR YOUR ENVIRONMENT **********************************/
	private static final String	HOSTNAME	=	"localhost";
	private static final String	LOGIN		=	"root.0.0.0.1";
	private static final String	AUTH_KEY	=	"password";
	private static final String PORT        =   "11960";
	/****************************************************************/

    public static void main(String[] args) {
        CreateContext contextExample = new CreateContext();

		contextExample.createContextUsingPropertiesFile();
		contextExample.createContextUsingProperties();
		contextExample.createContextUsingFlist();
    }

	/***************************************************************
	 * Create a PortalContext object with settings defined
	 * in Infranet.properties file. There must be a valid
	 * Infranet.properties file in the classpath.
	 ***************************************************************/
	public void createContextUsingPropertiesFile() {
	    try {
			System.out.println("---------------------------------------------------------------");
			System.out.println("Creating PCM context using configuration in Infranet.properties");

			PortalContext ctx = new PortalContext();
			ctx.connect();

			System.out.println("Context successfully created.");
			// print out some info about the connection
			System.out.println("current DB: " + ctx.getCurrentDB());
			System.out.println("user ID:    " + ctx.getUserID());

			// close the connection
			ctx.close(true);
			System.out.println("PCM connection closed.");
	    } catch (EBufException ebufex) {
			System.out.println("Your connection to the server failed.");
			System.out.println(" * Do you have a correct Infranet.properties file in the classpath?");
			System.out.println(" * Is the Infranet server CM up?");
			System.out.println("Here's the error:");
			System.out.println(ebufex);
	    }
	}

	/**************************************************************
	 * Create a PortalContext object with settings defined
	 * in java.util.Properties object passed in.
	 **************************************************************/
	public void createContextUsingProperties() {
		System.out.println("---------------------------------------------------------------");
		System.out.println("Creating PCM context using configuration supplied in a Properties object...");
		Properties props = new Properties();

		// The connection string is of the form:
		// pcp://<login>:<password>@<hostname>:<port>/service/adminclient 1
		props.put("infranet.connection", 
				  "pcp://" + LOGIN + ":" + AUTH_KEY + "@" + HOSTNAME + 
				  ":" + PORT + "/service/admin_client 1");
	    props.put("infranet.login.type", "1");

		try {
			PortalContext ctx = new PortalContext();
			ctx.connect(props);

			System.out.println("Context successfully created.");
			// print out some info about the connection
			System.out.println("current DB: " + ctx.getCurrentDB());
			System.out.println("user ID:    " + ctx.getUserID());

			// close the connection
			ctx.close(true);
			System.out.println("PCM connection closed.");
	    } catch (EBufException ebufex) {
			System.out.println("Your connection to the server failed.");
			System.out.println(" * Have you modified 'HOST', 'LOGIN', 'PASSWORD' and 'PORT' variables at the top of this example?");
			System.out.println(" * Is the Infranet server CM up?");
			System.out.println("Here's the error:");
			System.out.println(ebufex);
	    }

	}

	/********************************************************************
	 * Create a PortalContext object with settings defined in flist 
	 * passed in. 
	 *
	 * The flist should be of the form (see documentation on 
	 * PCM_CONTEXT_OPEN):
	 *
	 *		0 PIN_FLD_POID            POID [0] 0.0.0.1 /service/pcm_client 0 0
	 *		0 PIN_FLD_TYPE            ENUM [0] 1
	 *		0 PIN_FLD_LOGIN            STR [0] "root.0.0.0.1"
	 *		0 PIN_FLD_PASSWD_CLEAR     STR [0] "password"
	 *		0 PIN_FLD_CM_PTRS        ARRAY [0] allocated 1, used 1
	 *		1     PIN_FLD_CM_PTR           STR [0] "ip <hostname> 11960"
	 ********************************************************************/
	public void createContextUsingFlist() {
		System.out.println("---------------------------------------------------------------");
		System.out.println("Creating PCM context using configuration supplied in an flist...");

		// create a connection pointer flist and 
		// add it to the connection pointer array
		FList cmPtr = new FList();
		cmPtr.set(FldCmPtr.getInst(), "ip " + HOSTNAME + " " + PORT);
		SparseArray cmPtrs = new SparseArray();
		cmPtrs.add(cmPtr);

		// create the main input flist
		FList flist = new FList();
		Poid connectionPoid = new Poid(1, 0, "/service/pcm_client");
		flist.set(FldPoid.getInst(), connectionPoid);
		flist.set(FldType.getInst(), 1);
		flist.set(FldLogin.getInst(), LOGIN);
		flist.set(FldPasswdClear.getInst(), AUTH_KEY);
		flist.set(FldCmPtrs.getInst(), cmPtrs);

		try {
			PortalContext ctx = new PortalContext();
			ctx.open(flist);

			System.out.println("Context successfully created.");
			// print out some info about the connection
			System.out.println("current DB: " + ctx.getCurrentDB());
			System.out.println("user ID:    " + ctx.getUserID());

			// close the connection
			ctx.close(true);
			System.out.println("PCM connection closed.");
	    } catch (EBufException ebufex) {
			System.out.println("Your connection to the server failed.");
			System.out.println(" * Have you modified 'HOST', 'LOGIN', 'PASSWORD' and 'PORT' variables at the top of this example?");
			System.out.println(" * Is the Infranet server CM up?");
			System.out.println("Here's the error:");
			System.out.println(ebufex);
	    }		
	}
}
