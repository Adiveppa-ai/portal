/***************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ***************************************************************************/

/***************************************************************************
 *  This example demonstrates how to create a new customer account 
 *  in Infranet. 
 * 
 *  This example follows the Model/View/Controller pattern. The bulk of 
 *  Infranet-specific logicis in CreateCustomerModel. The UI is in
 *  CreateCustomerUI. The CreateCustomer class serves as the starting
 *  point for the example.
 ***************************************************************************/

import java.util.*;
import java.io.IOException;
import java.io.File;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

import com.portal.pcm.*;
import com.portal.pcm.fields.*;

public class CreateCustomer implements WindowListener{

	/****************************************************************
	 * Main method that runs this example.
	 ****************************************************************/
    public static void main(String[] args) {
		CreateCustomer custCreator = new CreateCustomer();

		try {
		  custCreator.buildGUI();
		} catch (EBufException ex) {
		  System.out.println("Error running this sample:");
		  System.out.println(ex);
		}
	}

	/****************************************************************
	 * Constructor. Creates the model and connects to the server.
	 ****************************************************************/
   	public CreateCustomer() {
		try {
			fCreateCustomerModel = new CreateCustomerModel();
			fCreateCustomerModel.connect();

		} catch(EBufException e) {
		    e.printStackTrace();
		}
	}

	/****************************************************************
	 * Method that builds this sample's GUI 
	 ****************************************************************/
   	protected void buildGUI() throws EBufException {
		JFrame frame = new JFrame("Create Customer Sample");
		final int kWidth = 570;
		final int kHeight = 520;
		frame.setSize(kWidth, kHeight);
		frame.addWindowListener(this);
		frame.getContentPane().setLayout(new BorderLayout());
		frame.getContentPane().add(
				   new CreateCustomerUI(fCreateCustomerModel), 
				   BorderLayout.CENTER);
		frame.setVisible(true);
    }


	/****************************************************************
	 * Implement WindowListener interface to handle window closing
	 ****************************************************************/
	public void windowActivated(WindowEvent e) {}
	public void windowClosed(WindowEvent e) {}
	public void windowDeactivated(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowOpened(WindowEvent e) {}
	public void windowClosing(WindowEvent e) {
		fCreateCustomerModel.close();
		System.exit(0);
	}

	private CreateCustomerModel	fCreateCustomerModel;
}
