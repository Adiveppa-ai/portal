/***************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ***************************************************************************/

/***************************************************************************
 * This class is the GUI element for CreateCustomer sample.
 ***************************************************************************/

import java.awt.event.*;
import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;

import com.portal.pcm.*;
import com.portal.pcm.fields.*;

//==============================================
public class CreateCustomerUI extends JPanel
		implements ActionListener {

	//-------------------------------------------
	private final static int kRadix = 10;
	private final static int kWidth = 420;
	private CreateCustomerModel	fCreateCustomerModel;
	private CreateCustomerAccountInfo	fCreateCustomerAccountInfo;

	private JButton		fGetPlanListButton;
	private JButton		fNewAccountButton;
	private	ButtonGroup	fPlanGroup;

	private JTextField	fPlanListNameField;
	private JTextField	fFirstNameField;
	private JTextField	fLastNameField;
	private JTextField	fAddressField;
	private JTextField	fCityField;
	private JTextField	fStateField;
	private JTextField	fZipcodeField;
	private JTextField	fServiceLoginField;
	private JTextField	fServicePasswordField;

	private JPanel		fPlanListPanel;
        private CreateCustomerUI lnkCreateCustomerUI;
	//-------------------------------------------
	public CreateCustomerUI(CreateCustomerModel model) 	{
		fCreateCustomerModel = model;
		fCreateCustomerAccountInfo = new CreateCustomerAccountInfo();

		setLayout(new FlowLayout());

		// icon
		add(new JLabel(new ImageIcon("portal_logo.gif")));

		// plan data
 		add(createPlanTypePanel());

 		add(createPlanListPanel());

		// account data
 		add(createNameInfoPanel());
 		add(createServiceLoginPanel());

		fNewAccountButton = new JButton("Create New Account");
		fNewAccountButton.setEnabled(false);
		fNewAccountButton.addActionListener(this);
		add(fNewAccountButton);
	}

	//----------------------------------------------------------------
	protected JPanel createPlanTypePanel() {
		JPanel panel = new JPanel();
		panel.setBorder(new BevelBorder(BevelBorder.RAISED));

		panel.add(new JLabel("Plan List Owner:"));
		fPlanListNameField = new JTextField("CSR", 20);	// columns
		panel.add(fPlanListNameField);
		fGetPlanListButton = new JButton("Get Plan List");
		fGetPlanListButton.addActionListener(this);
		panel.add(fGetPlanListButton);

		return panel;
	}

	//----------------------------------------------------------------
	protected JPanel createPlanListPanel() {
		fPlanGroup = new ButtonGroup();
		fPlanListPanel = new JPanel();
		fPlanListPanel.setPreferredSize(new Dimension(kWidth, 200));
		final int kRows = 0;
		final int kColumns = 1;
		fPlanListPanel.setLayout(new GridLayout(kRows, kColumns));
		fPlanListPanel.setBorder(new BevelBorder(BevelBorder.LOWERED));
		return fPlanListPanel;
	}

	//----------------------------------------------------------------
	protected JPanel createNameInfoPanel() {
		JPanel panel = new JPanel();
		panel.setLayout(new FlowLayout());
		final int kHeight = 90;
		panel.setPreferredSize(new Dimension(kWidth, kHeight));
		panel.setBackground(Color.pink);
		panel.setBorder(new BevelBorder(BevelBorder.RAISED));

		panel.add(new JLabel("First:"));
		fFirstNameField = new JTextField("", 10);	// columns
		panel.add(fFirstNameField);

		panel.add(new JLabel("Last:"));
		fLastNameField = new JTextField("", 20);	// columns
		panel.add(fLastNameField);

		panel.add(new JLabel("Address:"));
		fAddressField = new JTextField("10200 South De Anza Blvd", 31);
		panel.add(fAddressField);

		panel.add(new JLabel("City:"));
		fCityField = new JTextField("Cupertino", 15);	// columns
		panel.add(fCityField);

		panel.add(new JLabel("State:"));
		fStateField = new JTextField("CA", 2);	// columns
		panel.add(fStateField);

		panel.add(new JLabel("Zip:"));
		fZipcodeField = new JTextField("95104", 5);	// columns
		panel.add(fZipcodeField);

		return panel;
	}

	//----------------------------------------------------------------
	protected JPanel createServiceLoginPanel() {
		JPanel panel = new JPanel();
		panel.setBackground(new Color(0.5f, 1.0f, 1.0f));	// green-blue
		panel.setBorder(new BevelBorder(BevelBorder.RAISED));

		panel.add(new JLabel("Unique Login:"));
		final int kColumns = 15;
		fServiceLoginField = new JTextField("loginXXX", kColumns);
		panel.add(fServiceLoginField);

		panel.add(new JLabel("Password:"));
		fServicePasswordField = new JTextField("myPW", kColumns);
		panel.add(fServicePasswordField);

		return panel;
	}

	//----------------------------------------------------------------
	protected void buildPlanList() {
		String planListName	= fPlanListNameField.getText();
		try {
			String[] planNames = fCreateCustomerModel.getPlanNames(planListName);
			fPlanListPanel.removeAll();
			for (int i = 0; i < planNames.length; i++) {
				JRadioButton button = new JRadioButton(planNames[i]);
				button.addActionListener(this);
				button.setMnemonic(Character.forDigit(i, kRadix));
				fPlanListPanel.add(button);
				fPlanGroup.add(button);
				fPlanListPanel.revalidate();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	//----------------------------------------------------------------
	protected void createNewAccount() {
		ButtonModel selectedModel = fPlanGroup.getSelection();
		int selectedMnemonic = selectedModel.getMnemonic();
		int offset = 48;	// ascii 0
		int selectedIndex = selectedMnemonic - offset;	// 0, 1, ...
		fCreateCustomerAccountInfo.fFirstName = fFirstNameField.getText();
		fCreateCustomerAccountInfo.fLastName 	= fLastNameField.getText();
		fCreateCustomerAccountInfo.fAddress   = fAddressField.getText();
		fCreateCustomerAccountInfo.fCity 		= fCityField.getText();
		fCreateCustomerAccountInfo.fState 	= fStateField.getText();
		fCreateCustomerAccountInfo.fZipcode 	= fZipcodeField.getText();
		fCreateCustomerAccountInfo.fLogin 	= fServiceLoginField.getText();
		fCreateCustomerAccountInfo.fPassword 	= fServicePasswordField.getText();
		try {
			fCreateCustomerModel.createCustomer(selectedIndex, fCreateCustomerAccountInfo);
		} catch (Exception e) {e.printStackTrace();}
	}

	//----------------------------------------------------------------
	public void actionPerformed(ActionEvent ev) {
		if (ev.getSource() == fGetPlanListButton) {
			buildPlanList();
		} else if (ev.getSource() == fNewAccountButton) {
			createNewAccount();
		} else if (ev.getSource() instanceof JRadioButton) {
			fNewAccountButton.setEnabled(true);
		}
	}

	//-------------------------------------------
}
