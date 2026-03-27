/*****************************************************************************
 *
 * Copyright (c) 2000, 2024, Oracle and/or its affiliates. 
 *
 *  This material is the confidential property of Oracle Corporation or its
 *  licensors and may be used, reproduced, stored or transmitted only in 
 *  accordance with a valid Oracle license or sublicense agreement.
 *
 *
 *  To run this program you need to create custom class and fields
 *  Use the Storable Class Editor to create storable event classes and fields.
 *	Create the storable class of type /event/activity/email
 *	Create the following custom fields with following IDs
 *	   EMAIL_EVENT_INFO   PIN_FLDT_SUBSTRUCT [0]   ID# 10001
 *	        EMAIL_FROM    PIN_FLDT_STR [0]             10002
 *	        EMAIL_TO      PIN_FLDT_STR [0]             10003
 *
 *  Drag the EMAIL_EVENT_INFO field under /event/activity/email class and 
 *  EMAIL_FROM and EMAIL_TO fields under EMAIL_EVENT_INFO field.
 *  Commit the above class to the database.
 *
 *  Modify the environment below before you compile the program.
 *
 *  To run this program from commandline
 *  USAGE: sample_act
 ****************************************************************************/

#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

#include "PinFlds.h"
#include "PinContext.h"
#include "PinFlist.h"
#include "PinPoid.h"
#include "PinExc.h"
#include "PinLogger.h"
#include "customfld.h"

//===================================================================
// This example shows how to generate customer activity event for a
// service event type. Use this program to generate email activity 
// event for a given account. 
//===================================================================

//===================================================================
// MODIFY FOR YOUR ENVIRONMENT
//===================================================================
#define HOSTNAME 	"<infranet_host>"	// hostname running Infranet CM
#define LOGIN    	"root.0.0.0.1"		// login for an Infranet account
#define PORT	 	" 11960"
#define PASSWORD 	""			// password for login above
#define EMAILFROM 	"jane@portal.com"
#define EMAILTO		"joe@portal.com"
#define CUSTOMER_LOGIN 	"<name@server.ext>" 	// ex: john@portal.com

//===================================================================

// forward declarations
void findService(PinContextBase &context, PinFlistOwner &outflist);
void callSampleAct(PinContextBase &context);
void createInheritedInfoSubstruct(PinFlistOwner &inheritedInfo);
void generateEvent(PinContextBase &context, PinFlistOwner &rlist,
					PinFlistObserver &resultList);
void openContextUsingFlist(PinContextOwner &context);
ostream& operator<<(ostream&, PinEbufExc&);

void sampleAct()
{
	try {

		// Open a PCM context using settings defined in flist passed in.
		PinContextOwner context;
		openContextUsingFlist(context);

		// Call test opcode to verify that connection is open
		callSampleAct(context);

		// the connection is terminated automatically

	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
}


void callSampleAct(PinContextBase &context)
{
	// Create input flist
	PinFlistOwner eService;
	PinFlistObserver resultList;

	findService(context, eService) ;
	generateEvent(context, eService, resultList) ;

}

void findService(PinContextBase &context, PinFlistOwner &outflist) 
{
	PinFlistOwner inflist = PinFlist::create();

	// Create a poid
	PinPoidDb	dbno = (PinPoidDb) 1;
	PinPoidOwner	tmppoid = PinPoid::create(dbno, "/service/email", -1);

    cout << "tmppoid:" << endl << tmppoid << endl;

	// Note that a "pointer (->)" is used even though "input"
	// is an object, not a pointer to an object.
    inflist->set(tsf_PIN_FLD_POID,	tmppoid);
    inflist->set(tsf_PIN_FLD_LOGIN,	CUSTOMER_LOGIN);

    try {
	   context->op(PCM_OP_ACT_FIND, 0, inflist, outflist);
       cout << "outflist:" << endl << outflist << endl;
	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
}

void  generateEvent(PinContextBase &context, PinFlistOwner &rlist,
					PinFlistObserver &resultList)
{
    //set up the inputflist for PCM_OP_ACT_ACTIVITY, execute opcode, and
    //get resulting event poid

    PinPoidObserver eventPoid;
	PinFlistOwner inflist;
	PinFlistOwner outflist;

	try {

		PinPoidObserver	servicePoid = rlist->get(tsf_PIN_FLD_POID);
	    PinPoidObserver	accountPoid = rlist->get(tsf_PIN_FLD_ACCOUNT_OBJ);

        cout << "servicePoid:" << endl << servicePoid << endl;
        cout << "accountPoid:" << endl << accountPoid << endl;


		inflist = PinFlist::create();
		PinFlistOwner flt;

	    time_t whenEventUsageOccurred = pin_virtual_time(NULL);

		inflist->set( tsf_PIN_FLD_POID, accountPoid );
		inflist->set( tsf_PIN_FLD_SERVICE_OBJ, servicePoid );
	    inflist->set( tsf_PIN_FLD_PROGRAM_NAME, "Admin tool" );
	    inflist->set( tsf_PIN_FLD_START_T, whenEventUsageOccurred );
	    inflist->set( tsf_PIN_FLD_END_T, whenEventUsageOccurred );
	    inflist->set( tsf_PIN_FLD_OBJ_TYPE, "/email");

		createInheritedInfoSubstruct(flt);
	    inflist->set( tsf_PIN_FLD_INHERITED_INFO, flt );

       cout << "inflist:" << endl << inflist << endl;

	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}

    // Call PCM_OP_ACT_ACTIVITY.
    try {
        context->op(PCM_OP_ACT_ACTIVITY, 0, inflist, outflist);
        cout << "outflist:" << endl << outflist << endl;
	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
}


void createInheritedInfoSubstruct(PinFlistOwner &inheritedInfo)
{
	PinFlistOwner substruct = PinFlist::create();

	substruct->set(tsf_PIN_FLD_EMAIL_FROM, EMAILFROM);
    substruct->set(tsf_PIN_FLD_EMAIL_TO,	EMAILTO);

	inheritedInfo = PinFlist::create();
    inheritedInfo->set( tsf_PIN_FLD_EMAIL_EVENT_INFO, substruct );

}


//=================================================================
// Open a PCM context using settings defined in flist passed in.
// The flist should be of the form (see documentation on PCM_CONTEXT_OPEN):
//
//		0 PIN_FLD_POID            POID [0] 0.0.0.1 /service/admin_client 0 0
//		0 PIN_FLD_TYPE            ENUM [0] 1
//		0 PIN_FLD_LOGIN            STR [0] "root.0.0.0.1"
//		0 PIN_FLD_PASSWD_CLEAR     STR [0] "password"
//		0 PIN_FLD_CM_PTRS        ARRAY [0] allocated 1, used 1
//		1     PIN_FLD_CM_PTR           STR [0] "ip <hostname> 11960"
//=================================================================

void openContextUsingFlist(PinContextOwner &context)
{
	try {

		cout << "Creating PCM context using configuration supplied in an flist..." << endl;

		// Create input flist
		PinFlistOwner	input = PinFlist::create();

		// Create a poid
		PinPoidDb 	dbno = (PinPoidDb) 1;
		PinPoidOwner 	poid = PinPoid::create(dbno, "/service/admin_client", -1);

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
		context = PinContext::create(input);


	} catch (PinEbufExc &exc) {
		cout << exc << endl;
	}
}


ostream& 
operator<<(
	ostream &os, 
	PinEbufExc &exc)
{
        os << "Pin Exception";
        os << exc.getFlistRef() << endl;
        PIN_LOG(exc, PIN_ERR_LEVEL_ERROR, "");
        return os;
};

/////////////////////////////////////////////////////////////////////
int main (
	int		argc,
	char	*argv[])
{
	sampleAct();
	exit(0);
}
