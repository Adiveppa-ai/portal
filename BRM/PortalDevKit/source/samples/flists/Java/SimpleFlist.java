/*********************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 **************************************************************************/

/**********************************************************************
 * This class demonstrates how to create a simple flist and how to
 * retrieve fields from an flist.
 *
 * An flist is the fundamental data structure used in Infranet. 
 * Flists (field lists) are containers that hold fields, each of which
 * is a pair of data field name and its value. Infranet processes can 
 * interpret data only an flist format. Infranet uses flists in these ways:
 *  - Storable objects are passed in the form of flists 
 *    between opcodes or programs that manipulate the storable objects.
 *  - Opcodes use flists to pass data between the Infranet applications 
 *    and the database. 
 **********************************************************************/

import com.portal.pcm.*;
import com.portal.pcm.fields.*;

public class SimpleFlist {
	private FList flist;

	/********************************************************
	 * Main method to run the example
	 ********************************************************/
	public static void main(String[] args) {
		SimpleFlist example = new SimpleFlist();
		example.createFlist();
		example.traverseFlist();
    }

	/********************************************************
	 * Create a very simple flist and print it out.
	 * The constructed flist is of the form:
	 * 	0 PIN_FLD_POID             POID [0] 0.0.0.1 /account -1 0
	 *	0 PIN_FLD_LAST_NAME         STR [0] "Mouse"
	 *	0 PIN_FLD_FIRST_NAME        STR [0] "Mickey"
	 *	0 PIN_FLD_INT_VAL           INT [0] 42
	 ********************************************************/
 	public void createFlist() {
		// create an flist object
		flist = new FList();

		// add some data to the flist
		flist.set(FldPoid.getInst(), new Poid(1, -1, "/account"));
		flist.set(FldFirstName.getInst(), "Mickey");
		flist.set(FldLastName.getInst(), "Mouse");
		flist.set(FldIntVal.getInst(), 42);

		// Print the flist.
		flist.dump();
	}

	/********************************************************
	 * Retrieve fields from the flist created in 
	 * createFlist() method and print them out.
	 ********************************************************/
	public void traverseFlist() {
		Poid poid = null;
		String first = null, last = null;
		Integer num = null;

		try {
			// retrieve the fields from the flist
			poid = flist.get(FldPoid.getInst());
			first = flist.get(FldFirstName.getInst());
			last = flist.get(FldLastName.getInst());
			num = flist.get(FldIntVal.getInst());
		} catch (EBufException ebuf) {
			System.out.println("Field retrieved is not in the flist.");
			ebuf.printStackTrace();
		}
		
		// print out the fields
		System.out.println("poid:  " + poid);
		System.out.println("first: " + first);
		System.out.println("last:  " + last);
		System.out.println("num:   " + num);
	}

}
