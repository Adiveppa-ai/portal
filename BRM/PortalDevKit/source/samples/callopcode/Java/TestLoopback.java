/************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ************************************************************************/

/************************************************************************
 * This sample demonstrates how to call PCM_OP_TEST_LOOPBACK 
 * opcode. The opcode simply echos back to the caller the flist
 * that was passed to it.
 ************************************************************************/

import com.portal.pcm.*;
import com.portal.pcm.fields.*;

public class TestLoopback {
	private static boolean logout = true;

	public static void main(String[] args) {
		try {
			// Get the input flist
			FList inflist = createFList();

			// Print input flist
			System.out.println("Input flist");
			System.out.println(inflist);

			// Create PCM connext necessary for connecting to the server. 
	 		// A valid Infranet.properties file should be in the classpath.
	 		// See context examples for additional information.
			PortalContext ctx = new PortalContext();
			ctx.connect();

			// Call the opcode
			FList outflist = ctx.opcode(PortalOp.TEST_LOOPBACK, inflist);

			// Close PCM connection
			ctx.close(logout);

			// Print the return flist
			System.out.println("Output flist:");
			outflist.dump(); // this is an alternate way to print out an flist

			System.out.println("Success!");

		} catch (EBufException ebuf) {
			System.out.println("You weren't able to call the PCM_OP_TEST_LOOPBACK opcode.");
			System.out.println(" * Do you have a correct Infranet.properties file in the classpath?");
			System.out.println(" * Is the Infranet server CM up?");
			System.out.println("Here's the error:");
			System.out.println(ebuf);
		}
	}

	/*******************************************************************
	 * Create and return a simple FList of the form:
	 * 		0 PIN_FLD_POID                      POID [0] 0.0.0.1  -1 0
	 *		0 PIN_FLD_LAST_NAME                  STR [0] "Mouse"
	 *		0 PIN_FLD_FIRST_NAME                 STR [0] "Mickey"
	 *******************************************************************/
	public static FList createFList() throws EBufException {
		// create the flist
		FList flist = new FList();

		// add data to the flist
		flist.set(FldPoid.getInst(), new Poid(1));
		flist.set(FldFirstName.getInst(), "Mickey");
		flist.set(FldLastName.getInst(), "Mouse");

		return flist;
	}
}
