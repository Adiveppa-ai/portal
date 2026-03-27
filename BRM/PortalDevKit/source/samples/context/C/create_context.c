/***************************************************************************
* Copyright (c) 2000, 2024, Oracle and/or its affiliates. 
 *
 * This material is the confidential property of Oracle Corporation or
 * its licensors and may be used, reproduced, stored or transmitted only
 * in accordance with a valid Oracle license or sublicense agreement.
 ***************************************************************************/

/*******************************************************************
 * This example shows how to open and manage connections to Infranet.
 * An open connection has to be created before any opcodes 
 * may be called.
 *******************************************************************/

#include <stdio.h>
#include <string.h>

#include "pcm.h"
#include "ops/base.h"
#include "pinlog.h"

/*******************************************************************
 * MODIFY FOR YOUR ENVIRONMENT
 *******************************************************************/
#define HOSTNAME "localhost"        /* hostname running Infranet CM */
#define PORT     "11960"            /* CM port on hostname */
#define LOGIN    "root.0.0.0.1"     /* login for an Infranet account */
#define PASSWORD ""         	    /* password for login above */
/*******************************************************************/

/* forward declarations */
void open_context_using_config_file();
void open_context_using_flist();
void call_test_opcode(pcm_context_t* ctxp);


/******************************************************************
 * Main function to run the example
 ******************************************************************/
int main() {
	open_context_using_config_file();
	open_context_using_flist();
	return 0;
}

/*******************************************************************
 * Open a PCM context with settings defined in pin.conf file. 
 * There must be a valid pin.conf file in the current directory.
 *******************************************************************/
void open_context_using_config_file() {
	pin_errbuf_t     ebuf;
	int64            database = 1;
	pcm_context_t*   ctxp;

	printf("\nCreating PCM context using configuration in pin.conf...\n");
	/* Clear the error buffer */
	PIN_ERR_CLEAR_ERR(&ebuf);

	/* Open PCM connection */
	PCM_CONNECT(&ctxp, &database, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  printf("Error opening pcm connection.\n");
	  printf(" * Do you have a valid pin.conf file in the current directory?");
	  printf(" * Is the Infranet server CM up?");
	  exit(1);
	}

	/* Call test opcode to verify that connection is open */
	call_test_opcode(ctxp);

	/* Close PCM connection */
	PCM_CONTEXT_CLOSE(ctxp, (int32) 0, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  printf("Error closing pcm connection\n");
	  exit(1);
	}
	printf("PCM connection closed.\n");
}

/*************************************************************************
 * Open a PCM context using settings defined in flist passed in.
 * The flist should be of the form (see documentation on PCM_CONTEXT_OPEN):
 *
 *		0 PIN_FLD_POID            POID [0] 0.0.0.1 /service/pcm_client 0 0
 *		0 PIN_FLD_TYPE            ENUM [0] 1
 *		0 PIN_FLD_LOGIN            STR [0] "root.0.0.0.1"
 *		0 PIN_FLD_PASSWD_CLEAR     STR [0] "password"
 *		0 PIN_FLD_CM_PTRS        ARRAY [0] allocated 1, used 1
 *		1     PIN_FLD_CM_PTR           STR [0] "ip <hostname> 11960"
 *************************************************************************/
void open_context_using_flist() {
	pin_flist_t*     flistp;
	pin_flist_t*     cmptrsp;
	pcm_context_t*   ctxp;
	pin_errbuf_t     ebuf;
	char             login[]    = LOGIN;
	char             authCode[] = PASSWORD;
	char             hostname[] = HOSTNAME;
	char             cmptr[256];
	poid_t*          poidp;
	int              type = 1;
	
	printf("\nCreating PCM context using configuration supplied in an flist...\n");

	/* Clear the error buffer */
	PIN_ERR_CLEAR_ERR(&ebuf);
	
	/* Allocate flist */
	flistp = PIN_FLIST_CREATE(&ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error creating flist");
		exit(1);
	}
	
	/* Create and add a poid. */
	poidp = PIN_POID_CREATE(1, "/service/pcm_client", (int64)-1, &ebuf);
	PIN_FLIST_FLD_PUT(flistp, PIN_FLD_POID, poidp, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error creating and adding poid");
		exit(1);
	}
	
	/* Set PIN_FLD_TYPE to flist */
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_TYPE, &type, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error adding PIN_FLD_TYPE to flist");
		exit(1);
	}
	
	/* Add PIN_FLD_LOGIN field to flist */
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_LOGIN, (void*)login, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error adding PIN_FLD_TYPE to flist");
		exit(1);
	}
	
	/* Add PIN_FLD_PASSWD_CLEAR field to flist */
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_PASSWD_CLEAR, (void*)authCode, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error adding PIN_FLD_PASSWD_CLEAR to flist");
		exit(1);
	}
	
	/* Create CM_PTRS array with a single entry for the host
	 * we're connecting to */
	cmptrsp = PIN_FLIST_ELEM_ADD(flistp, PIN_FLD_CM_PTRS, 0, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error adding PIN_FLD_CM_PTRS to flist");
		exit(1);
	}

	pin_snprintf(cmptr, sizeof(cmptr), "ip %s %s", hostname, PORT);

	PIN_FLIST_FLD_SET(cmptrsp, PIN_FLD_CM_PTR, (void*)cmptr, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error adding PIN_FLD_CM_PTR to flist");
		exit(1);
	}

	/* Print out the flist we constructed that will be used to open
	 * PCM context */
	fprintf(stdout, "Flist used to open PCM context:\n");
	PIN_FLIST_PRINT(flistp, NULL, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error printing");
		exit(1);
	}
	
	/* Open the context with configuration info in the flist */
	PCM_CONTEXT_OPEN(&ctxp, flistp, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "could not open context");
		exit(1);
	}

	/* Call test opcode to verify that connection is open */
	call_test_opcode(ctxp);

	/* Close PCM connection */
	PCM_CONTEXT_CLOSE(ctxp, (int32) 0, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error closing pcm connection\n");
	  exit(1);
	}
	printf("PCM connection closed.\n");
}

/*******************************************************************
 * Call PCM_OP_TEST_LOOPBACK to verify that context is valid.
 * If we can successfully call the opcode, we're fairly sure we
 * have a good context.
 *******************************************************************/
void call_test_opcode(pcm_context_t* ctxp) {
	pin_flist_t*   flistp;
	pin_flist_t*   outflistp = NULL;
	pin_errbuf_t   ebuf;
	poid_t*        pdp = NULL;
	char           string[] = "Test Flist";
	

	/* Clear the error buffer */
	PIN_ERR_CLEAR_ERR(&ebuf);

	/* Allocate flist */
	flistp = PIN_FLIST_CREATE(&ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
		fprintf(stderr, "error creating flist");
		exit(1);
	}

	/* Add fields to the flist */
	pdp = PIN_POID_CREATE(1, "/account", (int64)-1, &ebuf);
	PIN_FLIST_FLD_PUT(flistp, PIN_FLD_POID, pdp, &ebuf);
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_STRING, (void *)string, &ebuf); /*X*/
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error adding fields to flist");
	  exit(1);
	}

	/* Call opcode */
	PCM_OP(ctxp, PCM_OP_TEST_LOOPBACK, 0, flistp, &outflistp, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error calling opcode\n");
	  exit(1);
	}

	/* If no errors have been encountered calling the opcode,
	 * we have a good context, so print out a "success" message.
	 */
	printf("Context successfully created.\n");
}
