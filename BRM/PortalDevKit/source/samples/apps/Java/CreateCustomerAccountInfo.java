/***************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ***************************************************************************/

/***************************************************************************
 * CreateCustomerAccountInfo contains the customer-specific information 
 * necessary to create a single account.
 ***************************************************************************/

class CreateCustomerAccountInfo {

	protected String 	fFirstName;
	protected String	fLastName;
	protected String	fAddress;
	protected String	fCity;
	protected String	fState;
	protected String	fZipcode;
	protected String	fLogin;
	protected String	fPassword;

	public CreateCustomerAccountInfo() {}
}
