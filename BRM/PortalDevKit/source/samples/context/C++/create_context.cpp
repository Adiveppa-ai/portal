/***************************************************************************
 * Copyright (c) 2000, 2024, Oracle and/or its affiliates. 
 *
 *  This material is the confidential property of Oracle Corporation or its
 *  licensors and may be used, reproduced, stored or transmitted only in 
 *  accordance with a valid Oracle license or sublicense agreement.
 ***************************************************************************/

#include <iostream>

#include "PinFlds.h"
#include "PinContext.h"
#include "PinFlist.h"
#include "PinPoid.h"
#include "PinExc.h"
#include "PinLogger.h"

/***************************************************************************
 * This example shows how to open and manage connections to Infranet.
 * An open connection has to be created before any opcodes 
 * may be called.
 ***************************************************************************/

/***************************************************************************
 * MODIFY FOR YOUR ENVIRONMENT
 ***************************************************************************/
#define HOSTNAME "localhost"        // hostname running Infranet CM
#define LOGIN    "root.0.0.0.1"     // login for an Infranet account
#define PASSWORD ""         	    // password for login above
#define PORT	 " 11960"

using namespace std; 

/* forward declarations */
ostream& operator<<(ostream&,PinEbufExc&);
void openContextUsingConfigFile();
void openContextUsingFlist();
void callTestOpcode(PinContextBase &context);



/******************************************************************
 * Main function to run the example
 ******************************************************************/
int main (int argc, char *argv[]) {

	openContextUsingConfigFile();
	openContextUsingFlist();

	return 0;
}


/***************************************************************************
 * Open a PCM context with settings defined in pin.conf file. 
 * There must be a valid pin.conf file in the current directory.
 ***************************************************************************/

void openContextUsingConfigFile() {
	try {

		cout << "Creating PCM context using configuration in pin.conf...";
		cout << endl;

		// Open a PCM context with settings defined in pin.conf file.
		PinContextOwner context = PinContext::create();

		// Call test opcode to verify that connection is open
		callTestOpcode(context);

		// the connection is terminated automatically

	} catch (PinEbufExc &exc) {
	    cout << "Connection to the server failed." << endl;
		cout << " * Do you have a correct pin.conf file in this directory?";
		cout << " * Is the Infranet server CM up?";
		cout << exc << endl;
	}
}

/***************************************************************************
 * Open a PCM context using settings defined in flist passed in.
 * The flist should be of the form (see documentation on PCM_CONTEXT_OPEN):
 *
 *		0 PIN_FLD_POID            POID [0] 0.0.0.1 /service/pcm_client 0 0
 *		0 PIN_FLD_TYPE            ENUM [0] 1
 *		0 PIN_FLD_LOGIN            STR [0] "root.0.0.0.1"
 *		0 PIN_FLD_PASSWD_CLEAR     STR [0] "password"
 *		0 PIN_FLD_CM_PTRS        ARRAY [0] allocated 1, used 1
 *		1     PIN_FLD_CM_PTR           STR [0] "ip <hostname> 11960"
 ***************************************************************************/

void openContextUsingFlist()
{
	try {

		cout << "Creating PCM context using configuration supplied in an flist..." << endl;

		// Create input flist
		PinFlistOwner	input = PinFlist::create();

		// Create a poid
		PinPoidDb 	dbno = (PinPoidDb) 1;
		PinPoidOwner 	poid = PinPoid::create(dbno, "/service/pcm_client", -1);

		// Note that a "pointer (->)" is used even though "input"
		// is an object, not a pointer to an object.
		input->set(tsf_PIN_FLD_POID, poid);

		int	type = 1;
		// Set PIN_FLD_TYPE to flist
		input->set(tsf_PIN_FLD_TYPE, type);

		const char*	login	= LOGIN;
		// Add PIN_FLD_LOGIN field to flist
		input->set(tsf_PIN_FLD_LOGIN, login);

		const char*	authCode = PASSWORD;
		// Add PIN_FLD_PASSWD_CLEAR field to flist
		input->set(tsf_PIN_FLD_PASSWD_CLEAR, authCode);

		
		// Create CM_PTRS array with a single entry for the host
		// we're connecting to
		PinFlistObserver cmptrsp = input->add(tsf_PIN_FLD_CM_PTRS, 0);


		char	string[80] = "";
		char*	cmptr	 = NULL;
		const char*   hostname = HOSTNAME;

		cmptr = strcat(strcat(strcat(string, "ip "), hostname), PORT);
		
		cmptrsp->set(tsf_PIN_FLD_CM_PTR, cmptr);


		// Print out the flist we constructed that will be used to open
		// PCM context
        cout << "Flist used to open PCM context:" << endl << input << endl;


		// Open the context with configuration info in the flist
		PinContextOwner context = PinContext::create(input);


		// Call test opcode to verify that connection is open
		callTestOpcode(context);


		cout << "PCM connection closed." << endl;

		// the connection is terminated automatically

	} catch (PinEbufExc &exc) {
	    cout << "Connection to the server failed." << endl;
		cout << " * Do you have a correct pin.conf file in this directory?";
		cout << " * Is the Infranet server CM up?";
		cout << exc << endl;
	}
}


/***************************************************************************
 * Call PCM_OP_TEST_LOOPBACK to verify that context is valid.
 * If we can successfully call the opcode, we're fairly sure we
 * have a good context.
 ***************************************************************************/

void callTestOpcode(PinContextBase &context)
{
	// Create input flist
	PinFlistOwner	input = PinFlist::create();

	// Create a poid
	PinPoidDb	dbno = (PinPoidDb) 1;
	PinPoidOwner	poid = PinPoid::create(dbno, "/account", -1);

	// Note that a "pointer (->)" is used even though "input"
	// is an object, not a pointer to an object.
	input->set(tsf_PIN_FLD_POID, poid);
	input->set(tsf_PIN_FLD_STRING, "Test Flist");

	// Invoke opcode
	PinFlistOwner output;
	PCM_OPP(context, PCM_OP_TEST_LOOPBACK, 0, input, output);
	
	// If no errors have been encountered calling the opcode,
	// we have a good context, so print out a "success" message.
	//
	cout << "Context successfully created." << endl;
}

ostream& operator<<(ostream &os, PinEbufExc &exc) {
        os << "Pin Exception";
        os << exc.getFlistRef() << endl;
        PIN_LOG(exc, PIN_ERR_LEVEL_ERROR, "");
        return os;
};


