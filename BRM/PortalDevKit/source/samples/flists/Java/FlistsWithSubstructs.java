/************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ************************************************************************/

/********************************************************************
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
 ********************************************************************/

import com.portal.pcm.*;
import com.portal.pcm.fields.*;

public class FlistsWithSubstructs {
	private FList flistWithSubstruct;

	/********************************************************************
	 * Main method to run the example
	 ********************************************************************/
	public static void main(String[] args) {
		FlistsWithSubstructs sample = new FlistsWithSubstructs();

		sample.createFlistWithSubstruct();
 	}


	/********************************************************************
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
	 ********************************************************************/
	public void createFlistWithSubstruct() {

		// flist for credit card info (elements of CC_INFO array)
		FList ccElement = new FList();
		ccElement.set(FldDebitExp.getInst(), "0905");
		ccElement.set(FldDebitNum.getInst(), "4444111122223333");
		ccElement.set(FldName.getInst(), "Joe Smith");

		// flist for substructure
		FList inheritedInfoSubstruct = new FList();
		inheritedInfoSubstruct.setElement( FldCcInfo.getInst(), 0, ccElement );

		// flist for elements of PAYINFO array
		FList payinfo = new FList();
		payinfo.set( FldInheritedInfo.getInst(), inheritedInfoSubstruct );
		payinfo.set( FldPoid.getInst(), new Poid( 1, -1, "/payinfo/cc" ) );

		// main flist
		flistWithSubstruct = new FList();
		flistWithSubstruct.setElement(FldPayinfo.getInst(), 0, payinfo);
		flistWithSubstruct.set(FldProgramName.getInst(), "Admin Manager");

		flistWithSubstruct.dump();
	}

}
