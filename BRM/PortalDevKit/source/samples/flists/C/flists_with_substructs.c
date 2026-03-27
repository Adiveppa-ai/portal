/***************************************************************************
 * Copyright (c) 2000, 2023, Oracle and/or its affiliates.
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation
 *  or its subsidiaries or licensors and may be used, reproduced, stored
 *  or transmitted only in accordance with a valid Oracle license or
 *  sublicense agreement.
 ***************************************************************************/


/**************************************************************************
 * This class demonstrates how to create an flist containing a substruct.
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

/******************************************************************
 * This example demonstrates how to create an flist with a 
 * substruct. Flist is of the form:
 *
 * 0 PIN_FLD_PROGRAM_NAME    STR [0] "Admin Manager"
 * 0 PIN_FLD_PAYINFO       ARRAY [1]
 * 1     PIN_FLD_POID           POID [0] 0.0.0.1 /payinfo/cc -1 0
 * 1     PIN_FLD_INHERITED_INFO SUBSTRUCT [0]
 * 2         PIN_FLD_CC_INFO       ARRAY [0]
 * 3             PIN_FLD_DEBIT_EXP       STR [0] "0905"
 * 3             PIN_FLD_DEBIT_NUM       STR [0] "4444111122223333"
 * 3             PIN_FLD_NAME            STR [0] "Joe Smith"
 *
 *******************************************************************/
int main() {
    pin_errbuf_t     ebuf;
	pin_flist_t*     flistp;
	pin_flist_t*     payinfo;
	pin_flist_t*     cc;
	pin_flist_t*     substruct;
	poid_t*          pdp;
	int64            db = 1;
	int64            id = -1;
	const char       *prog_name = "Admin Manager";
	const char       *debit_exp = "0905";
	const char       *debit_num = "4444111122223333";
	const char       *name = "Joe Smith";

	printf("\nCreate an flist containing a substruct:\n\n");
	
	PIN_ERR_CLEAR_ERR(&ebuf);

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

	PIN_FLIST_FLD_SET(flistp, PIN_FLD_PROGRAM_NAME, (void*)prog_name, &ebuf);

	payinfo = PIN_FLIST_ELEM_ADD(flistp, PIN_FLD_PAYINFO, 0, &ebuf);

	pdp = PIN_POID_CREATE(db, "/payinfo/cc", id, &ebuf);
	PIN_FLIST_FLD_PUT(payinfo, PIN_FLD_POID, pdp, &ebuf);

	substruct = PIN_FLIST_SUBSTR_ADD(payinfo, PIN_FLD_INHERITED_INFO, &ebuf);
	cc = PIN_FLIST_ELEM_ADD(substruct, PIN_FLD_CC_INFO, 0, &ebuf);

	PIN_FLIST_FLD_SET(cc, PIN_FLD_DEBIT_EXP, (void*)debit_exp, &ebuf);
	PIN_FLIST_FLD_SET(cc, PIN_FLD_DEBIT_NUM, (void*)debit_num, &ebuf);
	PIN_FLIST_FLD_SET(cc, PIN_FLD_NAME, (void*)name, &ebuf);


	PIN_FLIST_PRINT(flistp, NULL, &ebuf);
	return 0;
}
