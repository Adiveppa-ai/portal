/***************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ***************************************************************************/

/***************************************************************************
 * This sample demonstrates how to create an flist with array and how
 * to retrieve elements from an flist.
 *
 * An flist is the fundamental data structure used in Infranet. 
 * Flists (field lists) are containers that hold fields, each of which
 * is a pair of data field name and its value. Infranet processes can 
 * interpret data only an flist format. Infranet uses flists in these ways:
 *  - Storable objects are passed in the form of flists 
 *    between opcodes or programs that manipulate the storable objects.
 *  - Opcodes use flists to pass data between the Infranet applications 
 *    and the database. 
 ***************************************************************************/

#include <stdio.h>
#include <iostream>

#include "PinFlds.h"
#include "PinFlist.h"
#include "PinPoid.h"
#include "PinExc.h"
#include "PinLogger.h"

using namespace std;

// forward declarations
ostream& operator<<(ostream&, PinEbufExc&);
void createFlistWithArray(PinFlistOwner&);
void traverseFlistWithArray(PinFlistOwner&);
void createMultiElemArrayFlist(PinFlistOwner&);
void traverseMultiElemArrayFlist(PinFlistOwner&);
void createAndTraverseFListWithArray();
void createAndTraverseMultiElemArrayFlist();


/*******************************************************************
 * Main method to run the example
 ******************************************************************/
int main (int argc,	char *argv[]) {

	createAndTraverseFListWithArray();

	createAndTraverseMultiElemArrayFlist();

	return 0;
}


/***************************************************************************
 * Create a simple flist with an array. FList is of the form:
 * 
 * 0 PIN_FLD_POID                 POID [0] 0.0.0.1 /account -1 0
 * 0 PIN_FLD_PROGRAM_NAME          STR [0] "Flist Tester"
 * 0 PIN_FLD_NAMEINFO            ARRAY [0] allocated 3, used 3
 * 1     PIN_FLD_LAST_NAME         STR [0] "Doe"
 * 1     PIN_FLD_FIRST_NAME        STR [0] "John"
 * 1     PIN_FLD_SALUTATION        STR [0] "Mr."
 ***************************************************************************/
void createAndTraverseFListWithArray()
{
	try {

		cout << "Create an flist containing an array with one element:";
		cout << endl;

		PinFlistOwner inFlist ;
		createFlistWithArray(inFlist);

		// Print input flist
        cout << "Flist:" << endl << inFlist << endl;

		cout << "Traverse flist containing an array and print out its values";
		cout << endl;
		
		traverseFlistWithArray(inFlist) ;

	} catch (PinEbufExc &exc) {
	    cout << "There is an error running this example" << endl;
		cout << exc << endl;
	}
}

void createFlistWithArray(PinFlistOwner &singleArrayFlist) {

	// create an FList object
	singleArrayFlist = PinFlist::create();

	// Array element for the name information
	PinFlistOwner nameInfoElem = PinFlist::create();

	// Add three strings
	nameInfoElem->set(tsf_PIN_FLD_SALUTATION, "Mr.");
	nameInfoElem->set(tsf_PIN_FLD_FIRST_NAME, "John");
	nameInfoElem->set(tsf_PIN_FLD_LAST_NAME, "Doe");

	PinRecId id = 1 ;  // number doesn't matter; arrays are non-sequential
	singleArrayFlist->set(tsf_PIN_FLD_NAMEINFO, nameInfoElem, id);


	// Create a poid
	PinPoidDb	dbno = (PinPoidDb) 1;
	PinPoidOwner	poid = PinPoid::create(dbno, "/account", -1);

	singleArrayFlist->set(tsf_PIN_FLD_POID, poid);
	singleArrayFlist->set(tsf_PIN_FLD_STRING, "Flist Tester");

}


/***************************************************************************
 * Retrieve fields from the flist array created in
 * createFlistWithArray() method and print them out.
 ***************************************************************************/
void traverseFlistWithArray(PinFlistOwner &singleArrayFlist) {

   	PinFlistObserver nameInfoElem;
	PinPoidObserver	poid;
	PinStrObserver	testName;
	PinStrObserver	salut;
	PinStrObserver	first;
	PinStrObserver	last;

	// retrieve the array from the main flist
	try {
    	nameInfoElem = singleArrayFlist->get(tsf_PIN_FLD_NAMEINFO, 1);
		poid = singleArrayFlist->get(tsf_PIN_FLD_POID);
		testName = singleArrayFlist->get(tsf_PIN_FLD_STRING);
	} catch (PinEbufExc &exc) {
	    cout << "There was a problem retrieving the array from the flist. ";
		cout << endl;
		cout << exc << endl;
	}
		
	// retrieve the fields of the array element flist
	try {
		salut = nameInfoElem->get(tsf_PIN_FLD_SALUTATION);
		first = nameInfoElem->get(tsf_PIN_FLD_FIRST_NAME);
		last = nameInfoElem->get(tsf_PIN_FLD_LAST_NAME);
	} catch (PinEbufExc &exc) {
	    cout << "There was a problem retrieving elements from the flist.";
		cout << endl;
		cout << exc << endl;
	}

	// print out the fields
	cout << "testName: " << testName->value() << endl;
	cout << "poid: " << poid << endl;
	cout << "first: " << first->value() << endl;
	cout << "last: " << last->value() << endl;
		
}

/***************************************************************************
 * Create an flist with an array that has multiple elements. Note the
 * alternate way to add elements to an flist.
 *
 *		0 PIN_FLD_POID           POID [0] 0.0.0.1 /plan 9966 0
 *		0 PIN_FLD_SERVICES      ARRAY [0] allocated 20, used 4
 *		1     PIN_FLD_SERVICE_OBJ    POID [0] 0.0.0.1 /service/email -1 0
 *		1     PIN_FLD_LOGIN           STR [0] "john"
 *		0 PIN_FLD_SERVICES      ARRAY [1] allocated 20, used 4
 *		1     PIN_FLD_SERVICE_OBJ    POID [0] 0.0.0.1 /service/ip -1 0
 *		1     PIN_FLD_LOGIN           STR [0] "john"
 *		0 PIN_FLD_SERVICES      ARRAY [1] allocated 20, used 4
 *		1     PIN_FLD_SERVICE_OBJ    POID [0] 0.0.0.1 /service/web -1 0
 *		1     PIN_FLD_LOGIN           STR [0] "john"
 ***************************************************************************/

void createAndTraverseMultiElemArrayFlist() {
	try {

	    cout << "Create an flist containg an array with multiple elements." ;
		cout << endl;

		PinFlistOwner inFlist ;
		createMultiElemArrayFlist(inFlist);

		// Print input flist
        cout << "Flist:" << endl << inFlist << endl;

		cout << "Traverse flist containing an array with multiple elements and print them out." << endl;
		
		traverseMultiElemArrayFlist(inFlist) ;


	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
}

void createMultiElemArrayFlist(PinFlistOwner &multiArrayFlist) {

	// create an FList object
	multiArrayFlist = PinFlist::create();

	// Create a poid
	PinPoidDb	dbno = (PinPoidDb) 1;
	PinPoidOwner	poid = PinPoid::create(dbno, "/plan", 9966);

	multiArrayFlist->set(tsf_PIN_FLD_POID, poid);

	// create the flist that will be the first element of the array
	// (recall that an array element is an flist)
	PinFlistOwner service1 = PinFlist::create();

	PinPoidOwner	poid1 = PinPoid::create(dbno, "/service/email", -1);
	service1->set(tsf_PIN_FLD_SERVICE_OBJ, poid1);
	service1->set(tsf_PIN_FLD_LOGIN, "john");

	PinRecId id1 = 1 ;
	multiArrayFlist->set(tsf_PIN_FLD_SERVICES, service1, id1);


	// create the flist that will be the another element of the array
	PinFlistOwner service2 = PinFlist::create();

	PinPoidOwner	poid2 = PinPoid::create(dbno, "/service/ip", -1);
	service2->set(tsf_PIN_FLD_SERVICE_OBJ, poid2);
	service2->set(tsf_PIN_FLD_LOGIN, "john");

	PinRecId id2 = 2 ;
	multiArrayFlist->set(tsf_PIN_FLD_SERVICES, service2, id2);


	// create the flist that will be the another element of the array
	PinFlistOwner service3 = PinFlist::create();

	PinPoidOwner	poid3 = PinPoid::create(dbno, "/service/web", -1);
	service3->set(tsf_PIN_FLD_SERVICE_OBJ, poid3);
	service3->set(tsf_PIN_FLD_LOGIN, "john");

	PinRecId id3 = 3 ;
	multiArrayFlist->set(tsf_PIN_FLD_SERVICES, service3, id3);

}

/***************************************************************************
 * Retrieve fields from the flist array created in
 * createMultiElemArrayFlist() method and print them out.
 ***************************************************************************/
void traverseMultiElemArrayFlist(PinFlistOwner &multiArrayFlist) {

   	PinFlistObserver	nameInfoElem;

	// retrieve the array from the main flist
	try {
		PinFlistObserver service1 = multiArrayFlist->get(tsf_PIN_FLD_SERVICES, 1);
		PinFlistObserver service2 = multiArrayFlist->get(tsf_PIN_FLD_SERVICES, 2);
		PinFlistObserver service3 = multiArrayFlist->get(tsf_PIN_FLD_SERVICES, 3);

	// print out services
		cout << "service1: " << service1 << endl;
		cout << "service2: " << service2 << endl;
		cout << "service3: " << service3 << endl;
	
	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}

	// Walk through the services array in the multiArrayFlist
	// using an "observing" iterator
	cout << "Walk through the services array in the multiArrayFlist using an \"observing\" iterator." << endl;
	try {
		PinElemObservingIterator iter;
		for (iter = multiArrayFlist->getElements(tsf_PIN_FLD_SERVICES);
		     iter.hasMore(); ) {
		
			PinFlistObserver service = iter.next();
	
			PinPoidObserver	poid = service->get(tsf_PIN_FLD_SERVICE_OBJ);
			PinStrObserver	login = service->get(tsf_PIN_FLD_LOGIN);
		
			// print out the fields
			cout << "poid: " << poid << endl;
			cout << "login: " << login->value() << endl;
		}
	
	} catch (PinEbufExc &exc) {

		cout << exc << endl;
	}
}

ostream& operator<<(ostream &os, PinEbufExc &exc) {
        os << "Pin Exception";
        os << exc.getFlistRef() << endl;
        PIN_LOG(exc, PIN_ERR_LEVEL_ERROR, "");
        return os;
}


