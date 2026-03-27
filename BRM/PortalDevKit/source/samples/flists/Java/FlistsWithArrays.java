/**************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 **************************************************************************/

/**************************************************************************
 * This class demonstrates how to create an flist containing arrays
 * and how to retrieve fields from arrays.
 *
 * An flist is the fundamental data structure used in Infranet. 
 * Flists (field lists) are containers that hold fields, each of which
 * is a pair of data field name and its value. Infranet processes can 
 * interpret data only an flist format. Infranet uses flists in these ways:
 *  - Storable objects are passed in the form of flists 
 *    between opcodes or programs that manipulate the storable objects.
 *  - Opcodes use flists to pass data between the Infranet applications 
 *    and the database. 
 **************************************************************************/

import com.portal.pcm.*;
import com.portal.pcm.fields.*;
import java.util.Enumeration;

public class FlistsWithArrays {
	private FList singleArrayFlist;
	private FList multiElemArrayFlist;
	private long  db = 1;
	private long  id = -1;

	/*******************************************************************
	 * Main method to run the example
	 ******************************************************************/
	public static void main(String[] args) {
		FlistsWithArrays sample = new FlistsWithArrays();

		sample.createFlistWithArray(); 		
		sample.traverseFlistWithArray();

		sample.createMultiElemArrayFlist();
		sample.traverseMultiElemArrayFlist();
 	}

	/******************************************************************
	 * Create a simple flist with an array. FList is of the form:
	 * 
	 * 0 PIN_FLD_POID                 POID [0] 0.0.0.1 /account -1 0
	 * 0 PIN_FLD_PROGRAM_NAME          STR [0] "Flist Tester"
	 * 0 PIN_FLD_NAMEINFO            ARRAY [0] 
	 * 1     PIN_FLD_LAST_NAME         STR [0] "Doe"
	 * 1     PIN_FLD_FIRST_NAME        STR [0] "John"
	 * 1     PIN_FLD_SALUTATION        STR [0] "Mr."
	 *
	 ******************************************************************/
	public void createFlistWithArray() {
		System.out.println("Create an flist containing an array with one element:");

		// create an FList object
		singleArrayFlist = new FList();

		// Array element for the name information
		FList nameInfoElem = new FList();
		nameInfoElem.set(FldSalutation.getInst(), "Mr.");
		nameInfoElem.set(FldFirstName.getInst(), "John");
		nameInfoElem.set(FldLastName.getInst(), "Doe");

		// Create nameinfo array and add the NameInfo flist to it
		SparseArray nameInfoArray = new SparseArray();
		nameInfoArray.add(nameInfoElem);

		// Set values into the main flist
		singleArrayFlist.set(FldNameinfo.getInst(), nameInfoArray);
		singleArrayFlist.set(FldPoid.getInst(), new Poid(db, id, "/account"));
		singleArrayFlist.set(FldProgramName.getInst(), "Flist Tester");

		// Print out the flist
		singleArrayFlist.dump();
	}

	/******************************************************************
	 * Retrieve fields from the flist array created in
	 * createFlistWithArray() method and print them out.
	 ******************************************************************/
	public void traverseFlistWithArray() {
		System.out.println("Traverse flist containing an array and print out its values");
		SparseArray array = null;

		// retrieve the array from the main flist
		try {
			array = singleArrayFlist.get(FldNameinfo.getInst());
		} catch (EBufException ebuf) {
			System.out.println("could not retrieve array from flist");
			ebuf.printStackTrace();
		}
		
		// retrieve the flist that's one of the elements in the array;
		// since the array has only a single element, we can use
		// getAnyElement() method
		FList arrayElem = array.getAnyElement();
		
		// retrieve the fields of the array element flist
		String salutation = null, first = null, last = null;
		try {
			salutation = arrayElem.get(FldSalutation.getInst());
			first = arrayElem.get(FldFirstName.getInst());
			last = arrayElem.get(FldLastName.getInst());
		} catch (EBufException ebuf) {
			System.out.println("could not retrieve element from flist");
			ebuf.printStackTrace();
		}

		// print out the fields
		System.out.println("salutation: " + salutation);
		System.out.println("first:      " + first);
		System.out.println("last:       " + last);
		System.out.println();
	}

	/******************************************************************
	 * Create an flist with an array that has multiple elements. Note the
	 * alternate way to add elements to an flist.
	 *
	 *		0 PIN_FLD_POID           POID [0] 0.0.0.1 /plan 9966 0
	 *		0 PIN_FLD_SERVICES      ARRAY [0] 
	 *		1     PIN_FLD_SERVICE_OBJ    POID [0] 0.0.0.1 /service/email -1 0
	 *		1     PIN_FLD_LOGIN           STR [0] "john"
	 *		0 PIN_FLD_SERVICES      ARRAY [1] 
	 *		1     PIN_FLD_SERVICE_OBJ    POID [0] 0.0.0.1 /service/ip -1 0
	 *		1     PIN_FLD_LOGIN           STR [0] "john"
	 *		0 PIN_FLD_SERVICES      ARRAY [1] 
	 *		1     PIN_FLD_SERVICE_OBJ    POID [0] 0.0.0.1 /service/web -1 0
	 *		1     PIN_FLD_LOGIN           STR [0] "john"
	 *****************************************************************/
	public void createMultiElemArrayFlist() {
		System.out.println("Create an flist containg an array with multiple elements:");

		multiElemArrayFlist = new FList();

		// add poid to an flist (most flists will have a poid)
		multiElemArrayFlist.set(FldPoid.getInst(), new Poid(db, 9966, "/plan"));

		// create the array and add it to the main flist
		SparseArray serviceArray = new SparseArray();
		multiElemArrayFlist.set(FldServices.getInst(), serviceArray);
		
		// create the flist that will be the first element of the array
		// (recall that an array element is an flist)
		FList service1 = new FList();
		service1.set(FldServiceObj.getInst(), new Poid(db, id, "/service/email"));
		service1.set(FldLogin.getInst(), "john");
		// add this flist to the array
		serviceArray.add(service1);


		// create the flist that will be the another element of the array
		FList service2 = new FList();
		service2.set(FldServiceObj.getInst(), new Poid(db, id, "/service/ip"));
		service2.set(FldLogin.getInst(), "john");
		// add this flist to the array
		serviceArray.add(service2);

		// create the flist that will be the another element of the array
		FList service3 = new FList();
		service3.set(FldServiceObj.getInst(), new Poid(db, id, "/service/web"));
		service3.set(FldLogin.getInst(), "john");
		// If element indeces matter (usually they do not), use 
		// setElement() method to add the element to the array;
		// array indeces do not need to be consecutive.
		multiElemArrayFlist.setElement(FldServices.getInst(), 2, service3);

		// print out the flist we created
		multiElemArrayFlist.dump();
	}

	/*******************************************************************
	 * Retrieve fields from the flist array created in
	 * createMultiElemArrayFlist() method and print them out.
	 *******************************************************************/
	public void traverseMultiElemArrayFlist() {
		System.out.println("Traverse flist containing an array with multiple elements and print them out.");
		SparseArray array = null;

		// retrieve the array from the main flist
		try {
			array = multiElemArrayFlist.get(FldServices.getInst());
		} catch (EBufException ebuf) {
			System.out.println("could not retrieve array from flist");
			ebuf.printStackTrace();
		}

		// one way to get the elements is to retrieve the 
		// array values directly; recall that each array element is an flist
		System.out.println("Elements of the FldServices array:");
		Enumeration valueEnum = array.getValueEnumerator();
		while(valueEnum.hasMoreElements()) {
			FList flist = (FList)valueEnum.nextElement();
			System.out.println(flist);
		}

		// if you know the array key of the element, you can retrieve it 
		// directly from the main flist; to demonstrate, we'll get the 
		// 2nd element (index 1) and print it out
		try {
			FList elem2 = multiElemArrayFlist.getElement(FldServices.getInst(), 1);
			System.out.println("2nd element of the FldServices array");
			elem2.dump();
		} catch (EBufException ebuf) {
			System.out.println("couldn't retrieve element");
			ebuf.printStackTrace();
		}
		
	}

}
