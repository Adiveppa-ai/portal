/**************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ***************************************************************************/

#include <stdio.h>
#include <iostream>

#include "PinFlds.h"
#include "PinFlist.h"
#include "PinPoid.h"
#include "PinExc.h"
#include "PinLogger.h"

/************************************************************************
 * This sample demonstrates how to create a simple flist and how to
 * retrieve elements from an flist.
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

using namespace std;

// forward declarations
ostream& operator<<(ostream&, PinEbufExc&);
void createFlist(PinFlistOwner&);
void traverseFlist(PinFlistOwner&);
void createAndTraverseFList();



/*******************************************************************
 * Main method to run the example
 ******************************************************************/
int main (int argc, char *argv[]) {
	createAndTraverseFList();
	return 0;
}


/************************************************************************
 * Create a very simple FList and print it out.
 * The constructed FList is of the form:
 * 	0 PIN_FLD_POID                      POID [0] 0.0.0.1 /account -1 0
 *	0 PIN_FLD_LAST_NAME                  STR [0] "Mouse"
 *	0 PIN_FLD_FIRST_NAME                 STR [0] "Mickey"
 *  0 PIN_FLD_INT_VAL					 INT [0] 42
 ************************************************************************/
void createAndTraverseFList() {
	try {

		cout << "Test Create FList..." << endl;

		PinFlistOwner inFlist ;
		createFlist(inFlist);

		// Print input flist
        cout << "Flist:" << endl << inFlist << endl;

		cout << "Traverse FList..." << endl;
		
		traverseFlist(inFlist) ;


	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
}


/************************************************************************
 * Creates and returns flist of the form
 * 		0 PIN_FLD_POID                      POID [0] 0.0.0.1  -1 0
 *		0 PIN_FLD_LAST_NAME                  STR [0] "Mouse"
 *		0 PIN_FLD_FIRST_NAME                 STR [0] "Mickey"
 ************************************************************************/
void createFlist(PinFlistOwner &flistp) {

	// Create input flist
	flistp = PinFlist::create();

	// Create a poid
	PinPoidDb	dbno = (PinPoidDb) 1;
	PinPoidOwner	poid = PinPoid::create(dbno, "/account", -1);

	// Create and add a type-only poid.
	flistp->set(tsf_PIN_FLD_POID, poid);

	// Add two strings
	flistp->set(tsf_PIN_FLD_FIRST_NAME, "Mickey");
	flistp->set(tsf_PIN_FLD_LAST_NAME, "Mouse");

	// Add integer value
	flistp->set(tsf_PIN_FLD_INT_VAL, 42);
}

/************************************************************************
 * Retrieve fields from the flist created in 
 * createFlist method and print them out.
 ************************************************************************/
void traverseFlist(PinFlistOwner &flistp) {

	// retrieve the fields from the flist
	PinPoidObserver	poid = flistp->get(tsf_PIN_FLD_POID);
	
	PinStrObserver	first = flistp->get(tsf_PIN_FLD_FIRST_NAME);
	PinStrObserver	last = flistp->get(tsf_PIN_FLD_LAST_NAME);

	PinIntObserver	num = flistp->get(tsf_PIN_FLD_INT_VAL);

	// print out the fields
	cout << "poid: " << poid << endl;
	cout << "first: " << first->value() << endl;
	cout << "last: " << last->value() << endl;
	cout << "num: " << num->value() << endl;
		
}

ostream& operator<<(ostream &os, PinEbufExc &exc) {
        os << "Pin Exception";
        os << exc.getFlistRef() << endl;
        PIN_LOG(exc, PIN_ERR_LEVEL_ERROR, "");
        return os;
}
