/*
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *
 *      This material is the confidential property of Oracle Corporation or its
 *      licensors and may be used, reproduced, stored or transmitted only in
 *      accordance with a valid Oracle license or sublicense agreement.
 */

/*********************************************************************
 * This sample demonstrates how to call PCM_OP_TEST_LOOPBACK  opcode. 
 * The opcode simply echos back the flist that was passed to it.
 *********************************************************************/

#include <iostream>

#include "PinFlds.h"
#include "PinContext.h"
#include "PinFlist.h"
#include "PinPoid.h"
#include "PinExc.h"
#include "PinLogger.h"

using namespace std;

/* forward declarations */
void test_loopback();
void create_flist(PinFlistOwner&);
ostream& operator<<(ostream&, PinEbufExc&);

/******************************************************************
 * Main function to run the example
 ******************************************************************/
int main (int argc, char *argv[]) {
	test_loopback();
	return 0;
}


/******************************************************************
 * Call PCM_OP_TEST_LOOPBACK opcode
 ******************************************************************/
void test_loopback() {
	try {

		PinFlistOwner inFlist ;
		create_flist(inFlist);

		// Print input flist
        cout << "Flist sent to server:" << endl << inFlist << endl;
		
		// Open PCM connection. There must be a valid pin.conf
		// file in the current directory. For more about context,
		// see the context examples section.
		PinContextOwner context = PinContext::create();

		// Call the opcode
		PinFlistOwner outFlist;
		PCM_OPP(context, PCM_OP_TEST_LOOPBACK, 0, inFlist, outFlist);

		// Print return flist
        cout << "Flist returned from server:" << endl << outFlist << endl;

		// the connection is terminated automatically

	} catch (PinEbufExc &exc) {
		cout << "You weren't able to call the PCM_OP_TEST_LOOPBACK opcode.";
		cout << endl;
		cout << " * Do you have a correct pin.conf file in the classpath?";
		cout<< endl;
		cout << " * Is the Infranet server CM up?" << endl;
		cout << exc << endl;
	}
}

//===================================================================
// Creates and returns flist of the form
// 		0 PIN_FLD_POID                      POID [0] 0.0.0.1  -1 0
//		0 PIN_FLD_LAST_NAME                  STR [0] "Mouse"
//		0 PIN_FLD_FIRST_NAME                 STR [0] "Mickey"
//===================================================================
void create_flist(PinFlistOwner &flist) {

	// Create input flist
	flist = PinFlist::create();

	// Create a poid
	PinPoidDb dbno = (PinPoidDb) 1;
	PinPoidOwner poid = PinPoid::create(dbno, "/account", -1);

	// Create and add a type-only poid.
	flist->set(tsf_PIN_FLD_POID, poid);

	// Create and add two strings
	const char* first = (char *)"Mickey";
	const char* last  = (char *)"Mouse";

	flist->set(tsf_PIN_FLD_FIRST_NAME, first);
	flist->set(tsf_PIN_FLD_LAST_NAME, last);
}

ostream& operator<<(ostream &os, PinEbufExc &exc) {
        os << "Pin Exception";
        os << exc.getFlistRef() << endl;
        PIN_LOG(exc, PIN_ERR_LEVEL_ERROR, "");
        return os;
}


