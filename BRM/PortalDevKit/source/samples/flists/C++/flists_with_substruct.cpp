/***************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ***************************************************************************/

/***************************************************************************
 * This sample demonstrates how to create an flist with a substruct 
 * and how to retrieve elements from an flist.
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
#include "PinContext.h"
#include "PinFlist.h"
#include "PinPoid.h"
#include "PinExc.h"
#include "PinLogger.h"

using namespace std;

// forward declarations
ostream& operator<<(ostream&,PinEbufExc&);
void createFlistWithSubstruct(PinFlistOwner&);
void traverseFlistWithSubstruct(PinFlistOwner&);
void createAndTraverseFListWithSubstruct();

/*******************************************************************
 * Main method to run the example
 ******************************************************************/
int main (int argc, char *argv[]) {
	createAndTraverseFListWithSubstruct();
	return 0;
}


/***************************************************************************
 * Create an flist with a substruct. Flist is of the form:
 *
 * 0 PIN_FLD_PROGRAM_NAME    STR [0] "Admin Manager"
 * 0 PIN_FLD_PAYINFO       ARRAY [1] allocated 2, used 2
 * 1     PIN_FLD_POID           POID [0] 0.0.0.1 /payinfo/cc -1 0
 * 1     PIN_FLD_INHERITED_INFO SUBSTRUCT [0] allocated 1, used 1
 * 2         PIN_FLD_CC_INFO       ARRAY [0] allocated 3, used 3
 * 3             PIN_FLD_DEBIT_EXP       STR [0] "0905"
 * 3             PIN_FLD_DEBIT_NUM       STR [0] "4444111122223333"
 * 3             PIN_FLD_NAME            STR [0] "Joe Smith"
 ***************************************************************************/
void createAndTraverseFListWithSubstruct() {
	try {

		cout << "Test Create FList With Substruct..." << endl;

		PinFlistOwner inFlist ;
		createFlistWithSubstruct(inFlist);

		// Print input flist
        cout << "Flist:" << endl << inFlist << endl;

		cout << "Traverse flist containing an substruct and print out its values" << endl;
		
		traverseFlistWithSubstruct(inFlist) ;


	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
}

void createFlistWithSubstruct(PinFlistOwner &flistWithSubstruct) {

	// flist for credit card info (elements of CC_INFO array)
	PinFlistOwner cc = PinFlist::create();

	cc->set(tsf_PIN_FLD_DEBIT_EXP, "0905");
	cc->set(tsf_PIN_FLD_DEBIT_NUM, "4444111122223333");
	cc->set(tsf_PIN_FLD_NAME, "Joe Smith");

	// flist for substructure
	PinFlistOwner sub = PinFlist::create();
	sub->set(tsf_PIN_FLD_CC_INFO, cc, 0 );

	// Create a poid
	PinPoidDb	dbno = (PinPoidDb) 1;
	PinPoidOwner	poid = PinPoid::create(dbno, "/payinfo/cc", -1);

	// flist for elements of PAYINFO array
	PinFlistOwner payinfo = PinFlist::create() ;
	payinfo->set( tsf_PIN_FLD_INHERITED_INFO, sub );
	payinfo->set( tsf_PIN_FLD_POID, poid );

	// main flist
	flistWithSubstruct = PinFlist::create();
	flistWithSubstruct->set( tsf_PIN_FLD_PAYINFO, payinfo, 0);
	flistWithSubstruct->set( tsf_PIN_FLD_PROGRAM_NAME, "Admin Manager");

}


/***************************************************************************
 * Retrieve fields from the flist array created in
 * createFlistWithArray() method and print them out.
 ***************************************************************************/
void traverseFlistWithSubstruct(PinFlistOwner &flistWithSubstruct) {

   	PinFlistObserver cc;
   	PinFlistObserver sub;
   	PinFlistObserver payinfo;
	PinPoidObserver	poid;

	PinStrObserver	debitExp;
	PinStrObserver	debitNum;
	PinStrObserver	name;
	PinStrObserver	programName;

	// retrieve the array from the main flist
	try {
		payinfo = flistWithSubstruct->get( tsf_PIN_FLD_PAYINFO, 0);
		programName = flistWithSubstruct->get( tsf_PIN_FLD_PROGRAM_NAME);
		
	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
		
	try {
		sub = payinfo->get( tsf_PIN_FLD_INHERITED_INFO );
		poid = payinfo->get( tsf_PIN_FLD_POID );
		cc = sub->get(tsf_PIN_FLD_CC_INFO, 0);
		debitExp = cc->get(tsf_PIN_FLD_DEBIT_EXP);
		debitNum = cc->get(tsf_PIN_FLD_DEBIT_NUM);
		name = cc->get(tsf_PIN_FLD_NAME);
	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
		

	// print out the fields
	cout << "programName: " << programName->value() << endl;
	cout << "poid: " << poid << endl;
	cout << "name: " << name->value() << endl;
	cout << "debitExp: " << debitExp->value() << endl;
	cout << "debitNum: " << debitNum->value() << endl;
}

ostream& operator<<(ostream &os, PinEbufExc &exc) {
        os << "Pin Exception";
        os << exc.getFlistRef() << endl;
        PIN_LOG(exc, PIN_ERR_LEVEL_ERROR, "");
        return os;
}


