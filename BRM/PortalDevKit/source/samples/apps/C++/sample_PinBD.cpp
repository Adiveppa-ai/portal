/***************************************************************************
 *
 * Copyright (c) 2000, 2024, Oracle and/or its affiliates. 
 * All rights reserved. 
 *
 *  This material is the confidential property of Oracle Corporation or its 
 *  licensors and may be used, reproduced, stored or transmitted only in
 *  accordance with a valid Portal license or sublicense agreement.
 *
 ***************************************************************************/

/***************************************************************************
 * This example shows how to work with PinBigDecimal in Infranet:
 *
 *	1. Create a big decimal number from a string.
 *	2. Create a big decimal number from a double, preserve five decimal 
 *	   places, and use the default parameter for the "rounding mode".
 *     (See pin_decimal.h for the different rounding modes).
 *	3. Add two numbers together and store the result in a new variable.
 *	4. Convert a big decimal value to a string with its current precision.
 *     (number of places to the right of the decimal point).
 *  5. Add a PinBigDecimal value to an existing PinBigDecimal value.
 *  6. Subtract a PinBigDecimal value from an existing PinBigDecimal value.
 *  7. Multiply a PinBigDecimal value by another PinBigDecimal value.
 *  8. Divide a PinBigDecimal value by another PinBigDecimal value.
 *	9. Getting and setting the number of decimal places.
 * 10. Compare two PinBigDecimal variables for equality, inequality, and so on.
 * 11. Setting/getting a PinBigDecimal value into/from an Flist using the C API.
 * 12. Using the PinBigDecimal API with complex arithmetic expressions.
 *
 ***************************************************************************/

#include <stdio.h>
#include <iostream>

using namespace std;

#include <pcm.h>
#include <PinBigDecimal.h>
#include <PinErrorBuf.h>
#include <PinFlds.h>
#include <PinFlist.h>
#include <PinPoid.h>
#include <PinExc.h>
#include <PinLogger.h>


/* forward declarations */
ostream& operator<<(ostream&,PinEbufExc&);
void callTestPinBigDecimal();
void printPinBigDecimal(PinBigDecimal num);
void printFlist(const char* msg, pin_flist_t* flistp);

/******************************************************************
 * Main function to run the example
 ******************************************************************/
int main()
{
	callTestPinBigDecimal();
}

/***************************************************************************
 * test PinBigDecimal
 ***************************************************************************/

void callTestPinBigDecimal()
{
    char buf[100];
    char buf1[100];
    char buf2[100];
	
	cout << "Create a big decimal number from a string..." << endl << endl;
    
	// Create a big decimal number from a string
	//
    const char* pnum_str = "99";
    PinBigDecimal num1( "22.57" );
    PinBigDecimal num2( pnum_str  );

	printPinBigDecimal(num1);
	printPinBigDecimal(num2);

	cout << "Create a big decimal number from a double..." << endl << endl;

    // Create a big decimal number from a double, preserve five decimal 
    // places, and use the default parameter for the "rounding mode".
    // See pin_decimal.h for the different rounding modes.
    //
    PinBigDecimal num3( 22.578979, 5 );

	printPinBigDecimal(num3);

    // Create a big decimal number from a double, preserve two decimal 
    // places, and specify the "rounding mode".  See pin_decimal.h for 
    // the different rounding modes.
    //
    double double_val = 99.9823;
    PinBigDecimal num4( double_val, 2, ROUND_HALF_DOWN );

	printPinBigDecimal(num4);

	cout << "Add two numbers together and store the result in a new variable..." << endl << endl;

    // Add two numbers together and store the result in a new variable.
    //
    // Note: Since objects are being used you never have to call 
    //       pin_decimal_destroy() like you do when you use the 
    //       C API.  This is because the PinBigDecimal objects 
    //       handle all of the memory management for you via the 
    //       constructor and destructor.
    //
    PinBigDecimal sum = num3 + num4;

    sum.toString( buf, sizeof( buf ), sum.getNumDecimalPlaces() );
    num3.toString( buf1, sizeof( buf1 ), num3.getNumDecimalPlaces() );
    num4.toString( buf2, sizeof( buf2 ), num4.getNumDecimalPlaces() );

	cout << buf1 << " + " << buf2 << " is: " << buf << endl;

	cout << "Convert a big decimal value to a string with its current precision..." << endl << endl;

    // Convert a big decimal value to a string with its current precision.
    // (number of places to the right of the decimal point)
    //
    // Note: The default parameter for the 3rd argument of the 
    //       PinBigDecimal::toString() method was not implemented 
    //       correctly so you must call PinBigDedcimal::getNumDecimalPlaces() 
    //       to obtain the number of places to the right of the decimal point 
    //       for the 3rd argument of the toString() method.  This should 
    //       be fixed in 6.1.
    //
    num3.toString( buf, sizeof( buf ), num3.getNumDecimalPlaces() );
	cout << "The string value for num3 is " << buf << " and there are " << 
		num3.getNumDecimalPlaces() << " places to the right of the decimal point." << endl;

    
    // Another example of converting PinBigDecimal variables to strings
    //
    num3.toString( buf, sizeof( buf ), num3.getNumDecimalPlaces() );
    num4.toString( buf1, sizeof( buf1 ), num4.getNumDecimalPlaces() );
    sum.toString( buf2, sizeof( buf2 ), sum.getNumDecimalPlaces() );
	cout << "The sum of " << buf << " and " << buf1 << " is: " << buf2 << endl;

	cout << "Add a PinBigDecimal value to an existing PinBigDecimal value..." << endl << endl;

    // Add a PinBigDecimal value to an existing PinBigDecimal value.
    //
    num4 += num3;
    num1 += PinBigDecimal( "99.733" );

	printPinBigDecimal(num4);
	printPinBigDecimal(num1);

	cout << "Substract a PinBigDecimal value from an existing PinBigDecimal value..." << endl << endl;

    // Subtraction examples
    //
    PinBigDecimal diff = num3 - num4;

    num3.toString( buf, sizeof( buf ), num3.getNumDecimalPlaces() );
    num4.toString( buf1, sizeof( buf1 ), num4.getNumDecimalPlaces() );
    diff.toString( buf2, sizeof( buf2 ), diff.getNumDecimalPlaces() );

	cout << buf << " - " << buf1 << " is: " << buf2 << endl;

	cout << "Multiply a PinBigDecimal value by an existing PinBigDecimal value..." << endl << endl;

    // Multiplication examples
    //
    num1 = "18.432897498237423232";
    num2 = "3.493748932749823342323232334";
    num3 = num1 * num2;
    num1.toString( buf, sizeof( buf ), num1.getNumDecimalPlaces() );
    num2.toString( buf1, sizeof( buf1 ), num2.getNumDecimalPlaces() );
    num3.toString( buf2, sizeof( buf2 ), num3.getNumDecimalPlaces() );

	cout << buf << " * " << buf1 << " is: " << buf2 << endl;

	cout << "Divide a PinBigDecimal value by an existing PinBigDecimal value..." << endl << endl;

    // Division Examples
    //
    // Note: When using operator/() or operator/=() the scale (the number of places
    //       to the decimal point) used will be DEF_DIV_DECIMAL_PLACES (10) and the
    //       rounding mode used will be DEF_ROUNDING_MODE (ROUND_HALF_UP).
    //
    num1 = "18.4328";
    num2 = "3.4937";

	num3 = num1 / num2;
    num1.toString( buf, sizeof( buf ), num1.getNumDecimalPlaces() );
    num2.toString( buf1, sizeof( buf1 ), num2.getNumDecimalPlaces() );
    num3.toString( buf2, sizeof( buf2 ), num3.getNumDecimalPlaces() );

	cout << buf << " / " << buf1 << " is: " << buf2 << endl;
    
    // The above statement "num3 = num1 / num2" will NOT be the same as the following call 
    // to the divide method.
    //
    num4 = num1;
    num4.divide( num2, 9, ROUND_HALF_UP );
    num4.toString( buf2, sizeof( buf2 ), num4.getNumDecimalPlaces() );

	cout << buf << " divided by " << buf1 << " is: " << buf2 << endl;
    
	cout << "Getting and setting the number of decimal places..." << endl;

    // Getting and setting the number of decimal places
    //

	cout << "Compare two PinBigDecimal variables for equality, inequality, and so on..." << endl << endl;

    // Compare two PinBigDecimal variables for equality, inequality,
    // and so on.
    //
    sum.toString( buf1, sizeof( buf1 ), sum.getNumDecimalPlaces() );
    num4.toString( buf2, sizeof( buf2 ), num4.getNumDecimalPlaces() );
    if ( sum < num4 )
    {
    	cout << buf1 << " is less than " << buf2 << endl;
    }
    else
    if ( sum > num4 )
    {
    	cout << buf1 << " is greater than " << buf2 << endl;
    }
    else
    if ( sum != num4 )
    {
    	cout << buf1 << " is not equal to " << buf2 << endl;
    }
    else
    if ( sum == num4 )
    {
    	cout << buf1 << " is equal to " << buf2 << endl;
    }

    // **Note: Be aware that the PinBigDecimal class will throw an 
    //         exception if you try do an arithmic operation involving
    //         a PinBigDecimal variable containing "null"
    // 
    char* pnull = 0;
    PinBigDecimal null_val = PinBigDecimal( pnull );
    try
    {
        PinBigDecimal bad_idea;  // The default constructor will set the value to zero.
        bad_idea += null_val;
    	cout << "The program should NEVER get here..." << endl << endl;
    }
    catch ( const PinEbufExc& /*cExcptn*/ )
    {
        null_val.toString( buf, sizeof( buf ), 2 );
    	cout << "The string value of a null PinBigDecimal is: " << buf << endl << endl;
    }

   	cout << "Setting/getting a PinBigDecimal value into/from an Flist using the C API." << endl << endl;
    // Setting/getting a PinBigDecimal value into/from an Flist using the C API.
    //
    // Note: When using the PIN_FLIST_FLD_SET macro use the PinBigDecimal.get() 
    //       method to retrieve the pointer to the to the actual big decimal 
    //       number (pin_decimal_t*)
    //
    PinErrorBuf  ebuf; 
    pin_flist_t* flistp     = PIN_FLIST_CREATE( &ebuf );
    PIN_FLIST_FLD_SET( flistp, PIN_FLD_DUE, sum.get(), &ebuf );
    ::printFlist( "The Flist I just created with C API...", flistp );

    
	PinBigDecimal due( (pin_decimal_t*) PIN_FLIST_FLD_GET( flistp, PIN_FLD_DUE, 1, &ebuf ) );
    PIN_FLIST_DESTROY_EX( &flistp, 0 );
    due.toString( buf, sizeof( buf ), due.getNumDecimalPlaces() );
   	cout << "The value pulled from the Flist for PIN_FLD_DUE is: " << buf << endl;

   	cout << "Setting/getting a PinBigDecimal value into/from an Flist using the C++ API." << endl << endl;

    // Setting/getting a PinBigDecimal value into/from an Flist using the C++ API.
    //
    PinFlistOwner cpp_flist = PinFlist::create(); 
    cpp_flist->set( tsf_PIN_FLD_DUE, sum );

    due = cpp_flist->get( tsf_PIN_FLD_DUE )->get();
    due.toString( buf, sizeof( buf ), due.getNumDecimalPlaces() );

   	cout << "The value pulled from the Flist for PIN_FLD_DUE is: " << buf << endl;
    
   	cout << "Using the PinBigDecimal API with complex arithmetic expressions." << endl << endl;
    // Using the PinBigDecimal API with complex arithmetic expressions.
    //
    PinBigDecimal m_dDue( "10" );
    PinBigDecimal m_dDisputed;
    PinBigDecimal m_dAdjusted;
    PinBigDecimal m_dReceived( 10.00, 0 );
    PinBigDecimal m_dTransferred;
    PinBigDecimal dTemp = m_dDue - ( m_dDisputed + m_dAdjusted + m_dReceived ) + m_dTransferred;

	// If no errors have been encountered calling the opcode,
	// we have a good context, so print out a "success" message.
	//
	cout << "PinBigDecimal successfully tested." << endl;
}

ostream& operator<<(ostream &os, PinEbufExc &exc) {
        os << "Pin Exception";
        os << exc.getFlistRef() << endl;
        PIN_LOG(exc, PIN_ERR_LEVEL_ERROR, "");
        return os;
};

void printPinBigDecimal(PinBigDecimal num) {
    char buf[100];

    num.toString( buf, sizeof( buf ), num.getNumDecimalPlaces() );
	cout << buf << endl;
}

void printFlist(const char* msg, pin_flist_t* flistp)
{
    PIN_ERR_SET_LEVEL( PIN_ERR_LEVEL_DEBUG );
    PIN_ERR_LOG_FLIST( PIN_ERR_LEVEL_DEBUG, (char*) msg, flistp );

    PinErrorBuf  ebuf;
    int32        tmp_len;
    char*        tmp_buf = NULL;

    ::pin_flist_to_str( flistp, &tmp_buf, &tmp_len, &ebuf );
    ::printf( "%s\n%s", msg, tmp_buf );

}

