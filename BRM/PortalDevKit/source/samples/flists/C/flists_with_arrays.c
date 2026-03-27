/***************************************************************************
 * Copyright (c) 2000, 2023, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation
 *  or its subsidiaries or licensors and may be used, reproduced, stored
 *  or transmitted only in accordance with a valid Oracle license or
 *  sublicense agreement.
 ***************************************************************************/

/**************************************************************************
 * This class demonstrates how to create an flist containing arrays
 * and how to retrieve fields from from flists with arrays.
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

#include <stdlib.h>
#include <stdio.h>

#include <libgen.h>

#include "pin_errs.h"
#include "pcm.h"

/* forward declarations */
void create_flist_with_array(pin_flist_t*);
void traverse_flist_with_array(pin_flist_t*);
void create_multi_elem_array_flist(pin_flist_t*);
void traverse_multi_elem_array_flist(pin_flist_t*);

/******************************************************************
 * Main method to run the example
 ******************************************************************/
int main() {
	pin_flist_t*     single_array_flistp;
	pin_flist_t*     multi_elem_array_flistp;
	pin_errbuf_t     ebuf;
	
	PIN_ERR_CLEAR_ERR(&ebuf);

	/* Flist sample with single array. */
	single_array_flistp = PIN_FLIST_CREATE(&ebuf);
	create_flist_with_array(single_array_flistp);
	traverse_flist_with_array(single_array_flistp);

	/* Flist sample with an array containing multiple elements. */
	multi_elem_array_flistp = PIN_FLIST_CREATE(&ebuf);
	create_multi_elem_array_flist(multi_elem_array_flistp);
	traverse_multi_elem_array_flist(multi_elem_array_flistp);
	return 0;
}


/***********************************************************************
 * Create a simple flist with an array. Flist is of the form:
 *
 * 0 PIN_FLD_POID                 POID [0] 0.0.0.1 /account -1 0
 * 0 PIN_FLD_PROGRAM_NAME          STR [0] "Flist Tester"
 * 0 PIN_FLD_NAMEINFO            ARRAY [0]
 * 1     PIN_FLD_LAST_NAME         STR [0] "Doe"
 * 1     PIN_FLD_FIRST_NAME        STR [0] "John"
 * 1     PIN_FLD_SALUTATION        STR [0] "Mr."
 ***********************************************************************/
void create_flist_with_array(pin_flist_t* flistp) {

	pin_flist_t*     nameinfop = NULL;
	int64            db = 1;
	int64            id = -1;
	poid_t*          pdp = NULL;
	const char*      prog_name = "Flist Tester";
	const char*      first_name = "John";
	const char*      last_name = "Doe";
	const char*      salutation = "Mr.";
	pin_errbuf_t     ebuf;
	
	printf("\nCreate an flist containing an array with a single element:\n\n");

	/* Clear the error buffer */
	PIN_ERR_CLEAR_ERR(&ebuf);


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

	/* Create and add a type-only poid and program name fields */
	pdp = PIN_POID_CREATE(db, "/account", id, &ebuf);
	PIN_FLIST_FLD_PUT(flistp, PIN_FLD_POID, pdp, &ebuf);

	PIN_FLIST_FLD_SET(flistp, PIN_FLD_PROGRAM_NAME, (void*)prog_name, &ebuf);

	/* Create the array element. */
	nameinfop = PIN_FLIST_ELEM_ADD(flistp, PIN_FLD_NAMEINFO, 0, &ebuf);

	/* Add fields to array element flist */
	PIN_FLIST_FLD_SET(nameinfop, PIN_FLD_LAST_NAME, (void*)last_name, &ebuf);
	PIN_FLIST_FLD_SET(nameinfop, PIN_FLD_FIRST_NAME, (void*)first_name, &ebuf);
	PIN_FLIST_FLD_SET(nameinfop, PIN_FLD_SALUTATION, (void*)salutation, &ebuf);

	PIN_FLIST_PRINT(flistp, NULL, &ebuf);

	printf("\n---------------------------------------------------------\n");
}


/***********************************************************************
 * Retrieve fields from the flist array created in
 * create_flist_with_array() function and print them out.
 ***********************************************************************/
void traverse_flist_with_array(pin_flist_t* flistp) {
    pin_flist_t*    elem;
	pin_errbuf_t    ebuf;
	char*           value = NULL;

	PIN_ERR_CLEAR_ERR(&ebuf);

	printf("\nTraverse flist containing an array\nand print out array element values\n\n");

	/*
	 * Get the 0-th element of the PIN_FLD_NAMEINFO array
	 */
	elem = (pin_flist_t*)PIN_FLIST_ELEM_GET(flistp, PIN_FLD_NAMEINFO, 0, 0, &ebuf);
	if (elem == NULL) {
	    printf("There was no array element PIN_FLD_NAMEINFO in the flist\n");
		return;
	}

	/*
	 * Retrieve the flist fields
	 */
	value = (char*)PIN_FLIST_FLD_GET(elem, PIN_FLD_SALUTATION, 0, &ebuf);
	if (value == NULL) {
	    printf("There was no element PIN_FLD_SALUTATION in the flist\n");
	} else {
	    printf("salutation:   %s\n", value);
	}

	value = (char*)PIN_FLIST_FLD_GET(elem, PIN_FLD_LAST_NAME, 0, &ebuf);
	if (value == NULL) {
	    printf("There was no element PIN_FLD_LAST_NAME in the flist\n");
	} else {
	    printf("last:         %s\n", value);
	}


	value = (char*)PIN_FLIST_FLD_GET(elem, PIN_FLD_FIRST_NAME, 0, &ebuf);
	if (value == NULL) {
	    printf("There was no element PIN_FLD_FIRST_NAME in the flist\n");
	} else {
	    printf("first:        %s\n", value);
	}


	printf("\n---------------------------------------------------------\n");
}

/***********************************************************************
 *
 * Create an flist with an array that has multiple elements.
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
 ***********************************************************************/
void create_multi_elem_array_flist(pin_flist_t* flistp) {

	pin_errbuf_t     ebuf;
	int64            db = 1;
	int64            id = -1;
	poid_t*          pdp = NULL;
	poid_t*          email_pdp = NULL;
	poid_t*          ip_pdp = NULL;
	poid_t*          web_pdp = NULL;
	const char*      svc_login = "john";
	pin_flist_t*     svc1_flistp;
	pin_flist_t*     svc2_flistp;
	pin_flist_t*     svc3_flistp;

	printf("\nCreate an flist containg an array with multiple elements:\n\n");

	/*
	 * Clear the error buffer
	 */
	PIN_ERR_CLEAR_ERR(&ebuf);

	/*
	 * Create and add a type-only poid and program name fields
	 */
	pdp = PIN_POID_CREATE(db, "/plan", 9966, &ebuf);
	PIN_FLIST_FLD_PUT(flistp, PIN_FLD_POID, pdp, &ebuf);

	/*
	 * Create and add values to flist that will be the 
	 * first element in the array.
	 */
	svc1_flistp = PIN_FLIST_ELEM_ADD(flistp, PIN_FLD_SERVICES, 0, &ebuf);
	email_pdp = PIN_POID_CREATE(db, "/service/email", id, &ebuf);
	PIN_FLIST_FLD_SET(svc1_flistp, PIN_FLD_SERVICE_OBJ, (void*)email_pdp, &ebuf);
	PIN_FLIST_FLD_SET(svc1_flistp, PIN_FLD_LOGIN, (void*)svc_login, &ebuf);

	/*
	 * Create and add values to flist that will be the 
	 * second element in the array.
	 */
	svc2_flistp = PIN_FLIST_ELEM_ADD(flistp, PIN_FLD_SERVICES, 1, &ebuf);
	ip_pdp = PIN_POID_CREATE(db, "/service/ip", id, &ebuf);
	PIN_FLIST_FLD_SET(svc2_flistp, PIN_FLD_SERVICE_OBJ, (void*)ip_pdp, &ebuf);
	PIN_FLIST_FLD_SET(svc2_flistp, PIN_FLD_LOGIN, (void*)svc_login, &ebuf);

	/*
	 * Create and add values to flist that will be the 
	 * third element in the array.
	 */
	svc3_flistp = PIN_FLIST_ELEM_ADD(flistp, PIN_FLD_SERVICES, 2, &ebuf);
	web_pdp = PIN_POID_CREATE(db, "/service/web", id, &ebuf);
	PIN_FLIST_FLD_SET(svc3_flistp, PIN_FLD_SERVICE_OBJ, (void*)web_pdp, &ebuf);
	PIN_FLIST_FLD_SET(svc3_flistp, PIN_FLD_LOGIN, (void*)svc_login, &ebuf);


	PIN_FLIST_PRINT(flistp, NULL, &ebuf);

	printf("\n---------------------------------------------------------\n");

}

/***********************************************************************
 * Retrieve service fields from array created in
 * create_multi_elem_array_flist() function and print them out.
 ***********************************************************************/
void traverse_multi_elem_array_flist(pin_flist_t* flistp) {
	pin_errbuf_t    ebuf;
	pin_flist_t*    elem;
	char*           login;
	poid_t*         svc_poid;
	int             i;

	PIN_ERR_CLEAR_ERR(&ebuf);

	printf("\nTraverse flist containing an array with multiple elements\nand print out element values\n\n");

	for(i = 0; i <= 2; i++) {
	    elem = (pin_flist_t*)PIN_FLIST_ELEM_GET(flistp, PIN_FLD_SERVICES, i, 0, &ebuf);
		if (elem == NULL) {
		    printf("There's no array element PIN_FLD_SERVICES in the flist\n");
			continue;
		}
		/* Retrieve and print PIN_FLD_LOGIN field */
		login = (char*)PIN_FLIST_FLD_GET(elem, PIN_FLD_LOGIN, 0, &ebuf);
		if (login == NULL) {
		  printf("There was no element PIN_FLD_LOGIN in the flist\n");
		} else {
		  printf("login:         %s\n", login);
		}

		/* Retrieve and print service poid (PIN_FLD_SERVICE_OBJ) field */
		svc_poid = (poid_t*)PIN_FLIST_FLD_GET(elem, PIN_FLD_SERVICE_OBJ, 0, &ebuf);
		if (svc_poid == NULL) {
		  printf("There was no element PIN_FLD_SERVICE_OJB in the flist\n");
		} else {
		  printf("service poid:  ");
		  PIN_POID_PRINT(svc_poid, stdout, &ebuf);
		  printf("\n");
		}	
	
	}

	printf("\n---------------------------------------------------------\n");
}

