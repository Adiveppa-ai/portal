/***************************************************************************
 *
 *  @(#)% %
 *
* Copyright (c) 2000, 2016, Oracle and/or its affiliates. All rights reserved.
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ***************************************************************************/

  
/****************************************************************************
 * Model for the CreateCustomer example. The bulk of Infranet-specific code
 * is here. We perform several basic steps as a howto example:
 *      - open a database channel
 *      - retrieve the plan list
 *		- select desired plan
 *      - add the customer info to the plan
 *      - create the customer
 *      - close the database channel
 ****************************************************************************/

import java.util.*;
import java.io.IOException;
import java.io.File;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

import com.portal.pcm.*;
import com.portal.pcm.fields.*;


public class CreateCustomerModel {

	private ErrorLog 		fLog = null;
	private PortalContext 	fContext = null;
	private	FList			fPlanList;  // List of plans to which to add user
	private	long			fDatabaseNumber;
	private	Vector<FList> 		fPlanVector;	// indexed for use by GUI

	/****************************************************************
     * Constructor. Create an instance of CreateCustomerModel. 
     ****************************************************************/
	public CreateCustomerModel() {
		initErrorLog();
	}

	/****************************************************************
	 * Connect to Infranet server and create PortalContext object
	 * used for communicating with the server.
	 ****************************************************************/
	public void connect() throws EBufException {
	    fContext = new PortalContext();
	    fContext.connect();
	    fDatabaseNumber = fContext.getCurrentDB();
	    System.out.println("Connected with database number: " + fDatabaseNumber);
	}

    /****************************************************************
     * Retrieve from server list of plans that have been configured 
	 * using /group/plan_list object for specified owner using
	 * PCM_OP_CUST_POL_GET_PLANS opcode.
	 * 
	 * @param  planListOwner Plan list owner
	 * @return Vector of plans that have a name
     ****************************************************************/
    protected Vector getPlans(String planListOwner) throws EBufException, IOException {
		SparseArray planArray = null;
		fPlanVector = new Vector<FList>(20);
		try {
		    // Allocate the flist for loading the plans
		    FList inFlist = new FList();

		    // Create and add a type-only poid
		    Poid aPoid = new Poid( fDatabaseNumber);
		    inFlist.set( FldPoid.getInst(), aPoid );

		    // Try to get the plans listed in the 'admintool' plan list.
		    inFlist.set( FldAacAccess.getInst(), planListOwner );
		    // Call the GET_PLANS Custom policy FM opcode
			inFlist.dump();
		    FList outFlist = fContext.opcode(PortalOp.CUST_POL_GET_PLANS, inFlist);
		    outFlist.dump();
		    // Walk the plans array looking for a match.
		    planArray = outFlist.get(FldPlan.getInst());
		    Enumeration enumArr = planArray.getValueEnumerator();
		    while( enumArr.hasMoreElements() ) {
				FList plan = (FList)enumArr.nextElement();
				fPlanVector.add(plan);
		    }
			return fPlanVector;
		} catch( EBufException e ) {
		    fLog.log(ErrorLog.Error, "getPlans" +
			    System.getProperty("line.separator") +
			    e.toString());
		    throw e;
		}
    }

    /****************************************************************
     * Create new customer in the Infranet database with a given
	 * plan using PCM_OP_CUST_COMMIT_CUSTOMER opcode 
	 * 
	 * @param selectedPlanIndex plan index in array returned by getPlanNames()
	 * @param acctInfo specifies new customer information
     ****************************************************************/
    public void createCustomer(int selectedPlanIndex, CreateCustomerAccountInfo acctInfo)
			throws EBufException, IOException {
		try {
			setSelectedPlan(selectedPlanIndex);
	    	addAccountInfo(acctInfo);		// add acct info to plan list
	    	addInvoicePayinfo(acctInfo);
	    	fLog.log("Creating customer with login: " + acctInfo.fLogin);
	    	addService(acctInfo.fLogin, acctInfo.fPassword);
			System.out.println("Flist sent to PCM_OP_CUST_COMMIT_CUSTOMER opcode:");
	    	fPlanList.dump();
			System.out.println("Flist returned by PCM_OP_CUST_COMMIT_CUSTOMER opcode:");
		    FList outList = fContext.opcode(PortalOp.CUST_COMMIT_CUSTOMER, fPlanList);
		    outList.dump();
		    fLog.log(ErrorLog.Debug, "commit customer result flist"+
			    		System.getProperty("line.separator") + outList);
		} catch( EBufException e ) {
		    fLog.log(ErrorLog.Error, "createCustomer() error" +
			    System.getProperty("line.separator") +
			    e.toString());
		    throw e;
		}
    }

    /****************************************************************
	 * Add to the plan flist customer-specific information for the new 
	 * account being created.
     ****************************************************************/
    protected void addAccountInfo(CreateCustomerAccountInfo info) {
		// Create a new FList to hold bill info information
		// Since we're using INVOICE bill type, we also need
		// to add PAYINFO array; see the addInvoicePayinfo() method
		FList billInfo = new FList();
		billInfo.set( FldBillType.getInst(), PortalEnums.PinBillType.INVOICE );

		// Add bill info to the plan flist
		fPlanList.setElement( FldBillinfo.getInst(), 0, billInfo );

		// Create a new FList to hold nameinfo information
		FList nameInfo = new FList();
		nameInfo.set( FldLastName.getInst(), info.fLastName );
		nameInfo.set( FldFirstName.getInst(), info.fFirstName );
		nameInfo.set( FldAddress.getInst(), info.fAddress );
		nameInfo.set( FldCity.getInst(), info.fCity );
		nameInfo.set( FldState.getInst(), info.fState );
		nameInfo.set( FldZip.getInst(), info.fZipcode );
		nameInfo.set( FldCountry.getInst(), "USA" );
		nameInfo.set( FldEmailAddr.getInst(), info.fLogin+"@galaxy.com" );

		// Add the name info to the plan flist
		fPlanList.setElement( FldNameinfo.getInst(), 1, nameInfo );
    }

	/****************************************************************
	 * Add invoice PAYINFO array to the flist that supplies 
	 * information necessary to generate an invoice. In this case,
	 * we are assuming the invoice will be sent to the 
	 * subscriber.
	 ****************************************************************/
	protected void addInvoicePayinfo(CreateCustomerAccountInfo info) {
		// Create an FList to contain payinfo data
		FList payInfo = new FList();
		payInfo.set( FldBillType.getInst(), PortalEnums.PinBillType.INVOICE );
		payInfo.set(FldPoid.getInst(), new Poid(fDatabaseNumber, -1, "/payinfo/invoice"));

		// Create an FList for inherited info substructure
		FList sub = new FList();

		// Create an FList for invoice data
		FList invoiceInfo = new FList();
		invoiceInfo.set( FldDeliveryPrefer.getInst(), 1 );
		Poid fmt = new Poid( fDatabaseNumber, -1, "/config/invoice" );
		invoiceInfo.set( FldInvFormat.getInst(), fmt );
		invoiceInfo.set( FldInvTerms.getInst(), 0 );
		invoiceInfo.set( FldName.getInst(), info.fLastName );
		invoiceInfo.set( FldAddress.getInst(), info.fAddress );
		invoiceInfo.set( FldCity.getInst(), info.fCity );
		invoiceInfo.set( FldState.getInst(), info.fState );
		invoiceInfo.set( FldZip.getInst(), info.fZipcode );
		invoiceInfo.set( FldCountry.getInst(), "USA" );
		invoiceInfo.set( FldEmailAddr.getInst(), info.fLogin+"@galaxy.com" );
		invoiceInfo.set( FldInvInstr.getInst(), "sample invoice instruction" );

		// Now, put it all together
		sub.setElement( FldInvInfo.getInst(), 0, invoiceInfo );
		payInfo.set( FldInheritedInfo.getInst(), sub );
		fPlanList.setElement( FldPayinfo.getInst(), 1, payInfo );
    }

    /********************************************************************
     * Add the requested login and password to each service
     * array element found on the plan flist.
     *
     * @param login Username of the new user. <b>Should be unique</b>
     * @param password Password of the new user. <b>Should be unique</b>
     ********************************************************************/
    protected void addService(String login, String password )
						throws EBufException, IOException {
		try {
		    // For each service, we need to provide a login and password
		    SparseArray services = fPlanList.get( FldServices.getInst() );
		    Enumeration enumArr = services.getValueEnumerator();

		    // Because we are working with Java references,
		    // just adding to the flist works fine
		    while( enumArr.hasMoreElements() ) {
		        FList service = (FList)enumArr.nextElement();
				service.set( FldLogin.getInst(), login );
				service.set( FldPasswdClear.getInst(), password );
		    }
		} catch( EBufException e ) {
		    // catch the exception, log it, and then rethrow it
		    fLog.log( ErrorLog.Error, "sample_add_service error" +
			     System.getProperty("line.separator") +
			     e.toString() );
		    throw e;
		}
    }

	/*************************************************************
	 * Specify which plan will be used when creating new customer.
	 * @param index of plan in the array returned by getPlanNames()
	 *************************************************************/
    public void setSelectedPlan(int index) {
		fPlanList = (FList)fPlanVector.elementAt(index);
		System.out.println("Selected fPlanList: \n" +  fPlanList);
    }

	/*************************************************************
	 * Close the connection to Infranet server.
	 *************************************************************/
	public void close() {
	    try{
			if (fContext != null) {
		 		fContext.close(true);
			}
	    } catch (EBufException e) {e.printStackTrace();}
	}



    /****************************************************************
     * Get names of list of plans to present to users.
	 *
	 * @param  planListOwner name of plan list owner
	 * @return Vector of plans that have a name
     ****************************************************************/
	public String[] getPlanNames(String planListOwner)
			throws EBufException, IOException {
		Vector plans = getPlans(planListOwner);
		int number = plans.size();
		String[] planNames = new String[number];
		for (int i = 0; i < number; i++) {
			FList plan = (FList)plans.elementAt(i);
			String planName = plan.get( FldName.getInst());
			planNames[i] = planName;
		}
		return planNames;
    }


    /****************************************************************
     * Create a named log for this application.
     ****************************************************************/
    protected void initErrorLog() {
		try {
		    fLog = PortalContext.getDefaultLog();
		    fLog.setName( "CreateCustomerLog" );
		    fLog.setFlags( ErrorLog.All );
		} catch( Exception e ) {
		    System.err.println("Logging Error");
		    e.printStackTrace();
		}
    }
}
