/*
* Copyright (c) 2000, 2023, Oracle and/or its affiliates. All rights reserved.
 *
 *      This material is the confidential property of Oracle Corporation or its
 *      licensors and may be used, reproduced, stored or transmitted only in
 *      accordance with a valid Oracle license or sublicense agreement.
 */

/*********************************************************************
 * This sample demonstrates how to call PCM_OP_TEST_LOOPBACK  opcode. 
 * The opcode simply echos back the flist that was passed to it.
 *********************************************************************/

#include <stdio.h>

#include "ops/base.h"
#include "pcm.h"
#include "pinlog.h"

pin_flist_t* create_flist();


/******************************************************************
 * Main function to run the example
 ******************************************************************/
int main() {
	pin_flist_t*        inflistp;
	pin_flist_t*        outflistp;
	pcm_context_t*      ctxp;
	pin_errbuf_t        ebuf;
	int64               database;

	/* Clear the error buffer */
	PIN_ERR_CLEAR_ERR(&ebuf);

	/* Get the input flist */
	inflistp = create_flist();

	/* Print input flist */
	fprintf(stdout, "\nflist sent to server\n");
	PIN_FLIST_PRINT(inflistp, NULL, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error: couldn't display input flist\n");
	  exit(1);
	}

	/* Open PCM connection. There must be a valid pin.conf
	 * file in the current directory. For more about context,
	 * see the context examples section.
	 */
	PCM_CONNECT(&ctxp, &database, &ebuf);

	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error opening pcm connection\n");
	  exit(1);
	}

	/* Call the opcode */
	PCM_OP(ctxp, PCM_OP_TEST_LOOPBACK, 0, inflistp, &outflistp, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error calling opcode\n");
	  exit(1);
	}

	/* Close PCM connection. */
	PCM_CONTEXT_CLOSE(ctxp, (int32) 0, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error closing pcm connection\n");
	  exit(1);
	}

	/* Print return flist */
	fprintf(stdout, "\nflist returned from server\n");
	PIN_FLIST_PRINT(outflistp, NULL, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error: couldn't output return flist\n");
	  exit(1);
	}
	return (0);
}

/*****************************************************************
 * Creates and returns flist of the form
 * 		0 PIN_FLD_POID                      POID [0] 0.0.0.1  -1 0
 *		0 PIN_FLD_LAST_NAME                  STR [0] "Mouse"
 *		0 PIN_FLD_FIRST_NAME                 STR [0] "Mickey"
 *****************************************************************/
pin_flist_t* create_flist() {
	pin_flist_t	    *flistp = NULL;
	int64           database = 1;	
	char            first[] = "Mickey";
	char            last[]  = "Mouse";
	pin_errbuf_t    ebuf;
	poid_t          *a_pdp = NULL;


	/* Clear the error buffer */
	PIN_ERR_CLEAR_ERR(&ebuf);

	/* Allocate the flist */
	flistp = PIN_FLIST_CREATE(&ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error creating flist");
	  exit(1);
	}

	/*******************************************************************
	 * PUT and SET
	 *
	 * Use PIN_FLIST_FLD_SET to add a copy of the field to an flist. 
	 * The value passed in does not have to be in dynamic memory and 
	 * it is unaffected by the macro.
	 *
	 * Use PIN_FLIST_FLD_PUT to add the field, including its data value 
	 * to an flist. The memory holding the value must be dynamically 
	 * allocated; useful to add a field to the flist without copying 
	 * its value. Once the value of the field has been added to the
	 * flist, the memory can no longer be accessed and the original 
	 * pointer is not valid.
	 * 
	 * Please see the flist documentation for more information.
	 ********************************************************************/
	 

	/* Create and add a type-only poid. */
	a_pdp = PIN_POID_CREATE(database, "/account", (int64)-1, &ebuf);
	PIN_FLIST_FLD_PUT(flistp, PIN_FLD_POID, a_pdp, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error creating and adding poid");
	  exit(1);
	}
	
	/* Add two strings */ 
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_FIRST_NAME, (void *)first, &ebuf);
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_LAST_NAME, (void *)last, &ebuf);
	if (PIN_ERR_IS_ERR(&ebuf)) {
	  fprintf(stderr, "error creating and adding strings");
	  exit(1);
	}

	return flistp;
}
