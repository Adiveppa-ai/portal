/***************************************************************************
 * Copyright (c) 2000, 2024, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation
 *  or its subsidiaries or licensors and may be used, reproduced, stored
 *  or transmitted only in accordance with a valid Oracle license or
 *  sublicense agreement.
 ***************************************************************************/

/***************************************************************************
 * Create a very simple flist and print it out. Retrieve the values
 * from the flist and print them out.
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

#include <stdlib.h>
#include <stdio.h>

#include <libgen.h>

#include "pin_errs.h"
#include "pcm.h"

/* forward declarations */
pin_flist_t* create_flist();
void traverse_flist(pin_flist_t*);


/******************************************************************
 * Main function to run the example
 ******************************************************************/
int main() {
  pin_flist_t*    simple_flistp;

  simple_flistp = create_flist();
  traverse_flist(simple_flistp);
  return 0;
}

/******************************************************************
 * Create flist of the form:
 * 		0 PIN_FLD_POID                      POID [0] 0.0.0.1  -1 0
 *		0 PIN_FLD_LAST_NAME                  STR [0] "Mouse"
 *		0 PIN_FLD_FIRST_NAME                 STR [0] "Mickey"
 ******************************************************************/
pin_flist_t* create_flist() {

	pin_flist_t*    flistp = NULL;
	int64           db = 1;	
	int64           id = -1;
	const char      *first = NULL;
	const char      *last  = NULL;
	pin_errbuf_t    ebuf;
	poid_t          *a_pdp = NULL;


	printf("\nCreate a simple flist:\n\n");

	/* Clear the error buffer (for safety) */
	PIN_ERR_CLEAR_ERR(&ebuf);

	/* Allocate flist */
	flistp = PIN_FLIST_CREATE(&ebuf);


	/*******************************************************************
	 * PUT and SET
	 *
	 * Use PIN_FLIST_FLD_SET to add a copy of the field to an flist. The
	 * value passed in does not have to be in dynamic memory and it is
	 * unaffected by the macro.
	 *
	 * Use PIN_FLIST_FLD_PUT to add the field, including its data value 
	 * to an flist. The memory holding the value must be dynamically 
	 * allocated; useful to add a field to the flist without copying 
	 * its value. Once the value of the field has been added to the
	 * flist, the memory can no longer be accessed and the original 
	 * pointer is not valid.
	 * 
	 * Please see the flist documentation for more information.
	 *******************************************************************/

	/* Create and add a type-only poid.	 */
	a_pdp = PIN_POID_CREATE(db, "/account", id, &ebuf);
	PIN_FLIST_FLD_PUT(flistp, PIN_FLD_POID, a_pdp, &ebuf);
	
	/* Create and add two strings */ 
	first = "Mickey";
	last  = "Mouse";
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_FIRST_NAME, (void *)first, &ebuf);
	PIN_FLIST_FLD_SET(flistp, PIN_FLD_LAST_NAME, (void *)last, &ebuf);

	PIN_FLIST_PRINT(flistp, NULL, &ebuf);

	printf("\n---------------------------------------------------------\n");

	return flistp;
}

/******************************************************************
 * Retrieve fields from flist and print them out.
 ******************************************************************/
void traverse_flist(pin_flist_t* flistp) {
	pin_errbuf_t    ebuf;
	char*           value = NULL;
	poid_t*         poid;

	/* Clear the error buffer (for safety) */
	PIN_ERR_CLEAR_ERR(&ebuf);


	printf("\nRetrieve and print flist fields:\n\n");

	poid = PIN_FLIST_FLD_GET(flistp, PIN_FLD_POID, 0, &ebuf);
	if (poid == NULL) {
	    printf("There was no element PIN_FLD_POID in the flist\n");
	} else {
	    printf("poid:       ");
		PIN_POID_PRINT(poid, stdout, &ebuf);
		printf("\n");
	}

	value = (char*)PIN_FLIST_FLD_GET(flistp, PIN_FLD_LAST_NAME, 0, &ebuf);
	if (value == NULL) {
	    printf("There was no element PIN_FLD_LAST_NAME in the flist\n");
	} else {
	    printf("last name:  %s\n", value);
	}

	value = (char*)PIN_FLIST_FLD_GET(flistp, PIN_FLD_FIRST_NAME, 0, &ebuf);
	if (value == NULL) {
	    printf("There was no element PIN_FLD_FIRST_NAME in the flist\n");
	} else {
	    printf("first name: %s\n", value);
	}

	/* Free the flist */
	PIN_FLIST_DESTROY_EX(&flistp, NULL);
}
