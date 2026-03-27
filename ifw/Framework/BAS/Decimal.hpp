#ifndef BAS_DECIMAL_HPP
#define BAS_DECIMAL_HPP
//=============================================================================
//
// Copyright (c) 2003, 2020, Oracle and/or its affiliates. All rights reserved.
//      This material is the confidential property of Oracle Corporation. or
//      its subsidiaries or licensors and may be used, reproduced, stored or 
//      transmitted only in accordance with a valid Oracle license or 
//      sublicense agreement.
//
//-----------------------------------------------------------------------------
// Block: BAS
//-----------------------------------------------------------------------------
// Module Description:
//   Declaration of Decimal value class. This class uses BAS_DecImpl which is 
//   based on Rogue Wave's RWDecimal<T> template. It stores the decimal in 
//   64-bits; and translates it to the (128-bit) BAS_DecImpl class
//   representation for performing arithmetic operations. [BAS_DecImpl used
//   to be the old BAS_Decimal class.]
//
// Current Issues:
//   None.
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        JP Krishnamoorthy
// Backup-Responsible: Giles Douglas
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 06-Sep-2005  Jitendra Y          Added RW not supported rounding modes
// 20-Jan-2004  gdouglas            Added a real NULL value
// 05-Mar-2003  Mike Ammon          Switch from roundDecimal() to round()
//                                  to workaround RogueWave bug. CO 33608
// 15-Jan-2003  JP Krishnamoorthy   Initial version.
//
//=============================================================================

#ifndef BAS_DECIMPL_HPP
  #include "BAS/DecImpl.hpp"
#endif
#ifndef BAS_LONGLONGDECIMPL_HPP
  #include "BAS/LongLongDecImpl.hpp"
#endif
#ifndef BAS_DATAVALUE_H
  #include "BAS/DataValue.hpp"
#endif

namespace BAS 
{
	class String;
	
	// Here I am defining the base multi precision integer type used in Decimal
	// and the base decimal type used for Decimal. If you want to change the
	// precsion change these typedefs, the are used everywhere in Decimal.
	typedef RWMP1Int             MPInt;
	typedef RWDecimal<MPInt> DecBase;
	
	/**
	 * Decimal representation class.
	 * Decouples operations from storage.
	 * @see BAS::DecImpl for storage of data
	 */
	class Decimal : public DataValue
	{
		D_SINGLETHREADED
		
	public:

		/** @name Constructors
		 */
		//@{
		/** Default constructor. 
		 */
		Decimal();

		/** Constructor with initialization from string 
		 *  @str Decimal string to convert
		 */
		Decimal(const char* str);
		
		/** Constructor with initialization from string 
		 *  @str Decimal string to convert
		 *  @len Number of characters to be used in the string
		 */
		Decimal(const char *str, size_t len);

		/** Constructor with initialization from integer
		 */
		Decimal(int i);

		/** Constructor with initialization from long
		 */
		Decimal(int64 l);

		/** Constructor with mantissa and number of digits after decimal point
		 *  If you want to construct a DecImpl for 1.234 you have to 
		 *  specify DecImpl( 1234, 3 ). 
		 *  @param x Mantissa to use
		 *  @param e Number of digits behind decimal point (has to be positiv)
		 */
		Decimal(int x, int e);

		/** Constructor with mantissa and number of digits after decimal point
		 *  If you want to construct a DecImpl for 1.234 you have to 
		 *  specify DecImpl( 1234, 3 ).
		 *  @param x Mantissa to use
		 *  @param e Number of digits behind decimal point (has to be positiv)
		 */
 		Decimal(long int x, int e);

		/** Copy constructor 
		 */
		Decimal(const Decimal &other);

		/** Ideally we don't need the following; but because 
		 * DecImpl::selfTest() refers to String::convert, let us take
		 * a short cut here.
		 */
		Decimal(const DecImpl &di);

		Decimal(const LongLongDecImpl &di);
		
		~Decimal();

		//@}

		/** @name Interface exposed from DecImpl
		 */
		//@{
		/** Set mantissa and number of digits after decimal point.
		 *  If you want to set the decimal value to 1.234 you have use
		 *  specify set( 1234, 3 ).
		 *  @param x Mantissa to use
		 *  @param e Number of digits behind decimal point (has to be positiv)
		 */
		void set(int x, int e);

    /** Set mantissa and number of digits after decimal point
     *  If you want to set the decimal value to 1.234 you have use
     *  specify set( 1234, 3 ).
     *  @param x Mantissa to use
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
		void set(int64 x, int e);

    /** Set only the number of digits after decimal point
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
		void setDecimalPrecision(int e);

    /** Check if decimal == 0.0 
     */
		bool isNull() const;

		/** Assignment operator
		 * @param other Decimal to copy from
		 */
		Decimal& operator=(const Decimal& other);

    /** Assign the string value to instance. Check for DecImpl::NaN
     *  after assignment.
     *  @param str The decimal string to assign
     */
		Decimal& operator=(const char* str);

		
    /** Assign the integer value to instance. 
     *  @param i The integer to assign
     */
		Decimal& operator=(int i);

    /** Extract decimal number from string.
     *  @param str Decimal string for extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
		bool fromString(const char *str, char point = '.');

    /** Extract decimal number from part of a string
     *  @param str String for the decimal extraction
     *  @param pos Start position of part string for extraction
     *  @param len Length of part string for extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
		bool fromString(const char *str, size_t pos, size_t len, 
						char point = '.');

    /** Write the decimal number to string
     *  @param len
     *  @param precision Number of digits after the decimal point.
     *  @param showPoint <b>True</b> output of decimal point is enabled, 
	 * otherwise disabled.
     *  @param showNull Enables the conversion of the state DecImpl::null to
	 * "(null)" if set to <b>true</b>, "0" is used otherwise (default).
     *  @param point The character used as decimal point
     *  @param padChar
     */
		bool toString(String& str, int len = -1, int precision = -1, 
					  bool showPoint = true, bool showNull  = true, 
					  char padChar = '0', char point = '.') const;

    /** Extract decimal number from a Hexadecimal string in ASCII format
     *  @param str Hexadecimal string for the decimal extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
		bool fromHexString(const char *str, char point = '.');
	
    /** Extract decimal number from part of a Hexadecimal string in ASCII format
     *  @param str Hexadecimal for the decimal extraction
     *  @param pos Start position of part string for extraction
     *  @param len Length of part string for extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
	bool fromHexString(const char *str, size_t pos, size_t len, 
						   char point = '.');

    /** Write the decimal number to a Hexadecimal string in ASCII format
     *  @param len
     *  @param precision Number of digits after the decimal point.
     *  @param showPoint <b>True</b> output of decimal point is enabled, otherwise disabled.
     *  @param showNull Enables the conversion of the state DecImpl::null to "(null)"
     *                  if set to <b>true</b>, "0" is used otherwise (default).
     *  @param point The character used as decimal point
     *  @param padChar
     */
		bool toHexString(String& str, int len = -1, int precision = -1, 
						 bool showPoint = true, bool showNull  = true,
						 char padChar = '0', char point = '.') const;
 
    /** Serialize the decimal number into an output stream (currently not
     *  machine indepent!)
     *  @param out Output stream
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
		bool serialize(std::ostream& out) const;
       
    /** Restore the decimal number 
     *  @param in Input stream
     *  @return <b>true</b> on success, <b> false</b> otherwise
     */
		bool restore(std::istream& in);

		/** Self test
		 * Test oneself
		 * @return true for success
		 */
		static bool selfTest();

		//@}

		/** @name Interface exposed from DecBase (RWDecimal)
		 */

		//@{

		/** Cannot just do the typedef because there are use cases in the
		 * rest of the code for Decimal::TRUNCATE.
		 * typedef DecBase::RoundingMethod RoundingMethod;
		 */
		enum RoundingMethod {
			// RW supported rounding modes
			PLAIN    = DecBase::PLAIN,
			UP       = DecBase::UP,
			DOWN     = DecBase::DOWN,
			BANKERS  = DecBase::BANKERS,
			TRUNCATE = DecBase::TRUNCATE,
			// RW NOT supported rounding modes
			CEILING = 100, // Caution: Don't change this order 
			FLOOR,
			DOWN_ALT,
			FLOOR_ALT
		};
		
		/** Create a Decimal from a double.
		 * May induce inaccuracies of course
		 * @param d double to convert from
		 * @return Decimal instance containing closest possible approximation
		 * of parameter
		 */
		static Decimal from(double d);

		/** Convert to a double
		 * @return closest double approximation of stored value
		 */
		long double toDouble() const;

		/** Convert to int
		 * @see BAS::Decimal::RoundingMethod
		 * @param m rounding method
		 * @return int representing decimal after rounding
		 */
		long int toInt(DecBase::RoundingMethod m) const;

		/** Convert to int using PLAIN rounding method
		 * @return int value representing decimal 
		 */
		long int toInt() const;

		/** Get string representing container (decImpl) class
		 * @return BAS::String containing representation
		 */
		String toDecBaseString() const;

		/** Get absolute value
		 * @return Decimal containing absolute value
		 */
		Decimal abs() const;

		/** Get number of decimal places
		 * @return number of decimal places
		 */
		int decimalPlaces() const;

		/** see if represented value is a valid number
		 * @return true for yes
		 */
		bool isNumber() const;

		/** Negation operator
		 * @return negation of stored value 
		 */
		Decimal operator-() const;

		/** Addition operator
		 */
		Decimal& operator+=(const Decimal& a);

		/** Substraction operator
		 */
		Decimal& operator-=(const Decimal& a);

		/** Multiplication operator
		 */
		Decimal& operator*=(const Decimal& a);

		/** Division operator 
		 */
		Decimal& operator/=(const Decimal& a);

		//@}
		/** @name static functions
		 */

		//@{

		/** Get max value representable
		 * @return Decimal containing max value
		 */
		static Decimal maxValue();

		/** Get min value representable
		 * @return Decimal containing max value
		 */
		static Decimal minValue();

		/** Return base rounding method represented by parameter.
		 * Used to convert between the rounding methods internal to this
		 * class and those internal to the representation
		 * @param method Decimal rounding method
		 * @return DecBase rounding method
		 */
		static DecBase::RoundingMethod 
		decBaseRoundingMethod(Decimal::RoundingMethod method);

		/** Round a decimal using BAS::DecBase rounding method
		 * @param d decimal to round
		 * @param digits to use in round function
		 * @param method DecBase rounding method
		 * @return Decimal containing rounded value
		 */
		static Decimal roundDecimal(const Decimal& d, int digits, 
									DecBase::RoundingMethod method);

		/** Round a decimal using BAS::Decimal rounding method
		 * @param d decimal to round
		 * @param digits to use in round function
		 * @param method DecBase rounding method
		 * @return Decimal containing rounded value
		 */
		static Decimal roundDecimal(const Decimal& d, int digits, 
									Decimal::RoundingMethod method);


		/** Initializer for 'real' null decimal. This is the one that
		 * is actually null, as opposed to the other, which is zero
		 * @return Real Null Decimal
		 */
		static Decimal initRealDecimalNull();

		/** Initializer for null decimal
		 * @return Null decimal
		 */
		static Decimal initDecimalNull();

		/** Initializer for invalid decimal
		 * @return invalid decimal
		 */
		static Decimal initInvalidDecimal();

		/** Initializer for max 28 digit decimal support*/
		static bool initMax28DigitDecimalSupport();

		//@}

	private:
		
		friend Decimal operator+(const Decimal& a, const Decimal& b);
		friend Decimal operator-(const Decimal& a, const Decimal& b);
		friend Decimal operator*(const Decimal& a, const Decimal& b);
		friend Decimal operator/(const Decimal& a, const Decimal& b);
		
		friend bool operator<(const Decimal& a, const Decimal& b);
		friend bool operator>(const Decimal& a, const Decimal& b);
		friend bool operator<=(const Decimal& a, const Decimal& b);
		friend bool operator>=(const Decimal& a, const Decimal& b);
		friend bool operator==(const Decimal& a, const Decimal& b);
		friend bool operator!=(const Decimal& a, const Decimal& b);
		
		friend std::ostream&    operator<<(std::ostream& s, const Decimal &d);
		friend long double toDouble(const Decimal &d);
		friend long int    toInt(const Decimal &d);
		
		// Looks like toString(DecImpl&) is used only in selfTest()
		// I think intent is to use DecImpl.toString() everywhere.
		friend String  toString(const Decimal &d);
		
		static Decimal create(const Dec &i);
		
		/** Private constructor; Force others to use create() if necessary.
		 * Is this equiv to explicit?
		 */
		Decimal(Dec c) : decM(c) {;}
		
		/** @name Private and not implemented, to prevent unintenionally use
		 */
		//@{
		Decimal(double d);
		Decimal& operator=(double d);
		//@}

		/** data members */
		union
		{
		  Dec decM;
		  LongLongDecImpl* longLongDecImplPtrM;
		};
};
// Need to declare this - not implicit since it is in a namespace
String toString( const Decimal &d );

// Need to declare this - not implicit since it is in a namespace
String toString(const Decimal &d);

BAS_EXPORT extern const Decimal DECIMAL_NULL;
BAS_EXPORT extern const bool MAX28DIGIT_DECIMAL_SUPPORT;
BAS_EXPORT extern const Decimal DECIMAL_REALNULL;
BAS_EXPORT extern const Decimal INVALID_DECIMAL;

inline 
Decimal::Decimal()
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl();
    }
    else
    {
      decM = DecImpl::CSNull;
    }
}

inline 
Decimal::Decimal(const char* str)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl(str);
    }
    else
    {
      DecImpl di(str); 
      decM = di.toCompact(); 
    }
}

inline 
Decimal::Decimal(const char *str, size_t len)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl(str, len);
    }
    else
    { 
      DecImpl di(str, len);
      decM = di.toCompact(); 
    }	
}

inline 
Decimal::Decimal(int i)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl(i);
    }
    else
    { 
      DecImpl di(i);
      decM = di.toCompact(); 
    }	
}

inline 
Decimal::Decimal(int64 l)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl((long)l);
    }
    else
    { 
      DecImpl di((long)l);
      decM = di.toCompact(); 
    }	
}

inline 
Decimal::Decimal(int x, int e)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl(x, e);
    }
    else
    {
      DecImpl di(x, e); 
      decM = di.toCompact(); 
    }	
}

inline 
Decimal::Decimal(long int x, int e)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {	
      longLongDecImplPtrM = new LongLongDecImpl(x, e);
    }
    else
    { 
      DecImpl di(x, e); 
      decM = di.toCompact(); 
    }
}

inline 
Decimal::Decimal(const Decimal &other)  
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl();
      *longLongDecImplPtrM = *other.longLongDecImplPtrM;
    }
    else
    {
      decM = other.decM;
    }
}

inline 
Decimal::Decimal(const DecImpl &di) 
{
    if(!MAX28DIGIT_DECIMAL_SUPPORT)
    {
      decM = di.toCompact(); 
    }
}

inline 
Decimal::Decimal(const LongLongDecImpl &dec) 
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM = new LongLongDecImpl();
      *longLongDecImplPtrM = dec;
    }
}

inline
Decimal::~Decimal()
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      if(longLongDecImplPtrM)
      {
	delete longLongDecImplPtrM;
        longLongDecImplPtrM = NULL;
      }
    }
}

inline bool 
Decimal::isNull() const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return longLongDecImplPtrM->isNull();
    }
    else
    { 
      return ((decM & DecImpl::CMState) == DecImpl::CSNull); 
    }
}

inline Decimal& 
Decimal::operator=(const Decimal& other)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      if(this != &other)
      {
        *longLongDecImplPtrM = *other.longLongDecImplPtrM;
      }
    }
    else
    {
      decM = other.decM;
    } 
    return *this; 
}

inline Decimal& 
Decimal::operator=(const char* str)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec(str); 
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di(str); 
      decM = di.toCompact(); 
    }
    return *this; 
}

inline Decimal& 
Decimal::operator=(int i)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec(i); 
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di(i); 
      decM = di.toCompact(); 
    }
    return *this; 
}

inline bool 
Decimal::fromString(const char *str, char point)
{ 
    bool result; 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec; 
      result = dec.fromString(str, point);
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di; 
      result = di.fromString(str, point);
      decM = di.toCompact(); 
    }
    return result; 
}

inline bool 
Decimal::fromString(const char *str, size_t pos, size_t len, char point)
{ 
    bool result;
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec; 
      result = dec.fromString(str, pos, len, point);
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di; 
      result = di.fromString(str, pos, len, point);
      decM = di.toCompact(); 
    }
    return result; 
}
		
inline bool 
Decimal::toString(String& str, int len, int precision, 
				  bool showPoint, bool showNull,
				  char padChar, char point) const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return longLongDecImplPtrM->toString(str, len, precision, showPoint, showNull,
							    padChar, point);
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM); 
      return di.toString(str, len, precision, showPoint, showNull, 
						    padChar, point);
    }
}

inline bool
Decimal::fromHexString(const char *str, char point)
{
    bool result;
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec; 
      result = dec.fromHexString(str, point);
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di; 
      result = di.fromHexString(str, point);
      decM = di.toCompact(); 
    }
    return result; 
}

inline bool
Decimal::fromHexString(const char *str, size_t pos, size_t len, char point)
{ 
    bool result; 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec; 
      result = dec.fromHexString(str, pos, len, point);
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di; 
      result = di.fromHexString(str, pos, len, point);
      decM = di.toCompact(); 
    }
    return result; 
}

inline bool 
Decimal::toHexString(String& str, int len, int precision, 
					 bool showPoint, bool showNull,
					 char padChar, char point) const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return longLongDecImplPtrM->toHexString(str, len, precision, showPoint, showNull, 
							  padChar, point);
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM); 
      return di.toHexString(str, len, precision, showPoint, showNull, 
		      					padChar, point);
    }
}

inline bool 
Decimal::serialize(std::ostream& out) const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return longLongDecImplPtrM->serialize(out);
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM);
      return di.serialize(out);
    }
}

inline bool 
Decimal::restore(std::istream& in)
{
    bool result;

    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec; 
      result = dec.restore(in);
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di; 
      result = di.restore(in);
      decM = di.toCompact();
    }
    return result;
}

inline Decimal 
Decimal::from(double d)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec = LongLongDecImpl::from(d);
      return Decimal(dec);
    }
    else
    {
      DecImpl di = DecImpl::from(d);
      return create(di.toCompact());
    }
}

inline long double 
Decimal::toDouble() const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return LongLongDecBase::convertToDouble(*longLongDecImplPtrM);
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM);
      return DecBase::convertToDouble(di);
    }
}

inline long int 
Decimal::toInt(DecBase::RoundingMethod m) const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return LongLongDecBase::convertToInt(*longLongDecImplPtrM, m);
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM);
      return DecBase::convertToInt(di, m);
    }
}

inline long int 
Decimal::toInt() const
{
	return toInt(DecBase::PLAIN);
}

inline Decimal 
Decimal::abs() const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return Decimal(LongLongDecBase::absoluteValue(*longLongDecImplPtrM));
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM);
      di = DecBase::absoluteValue (di);
      return create(di.toCompact());
    }
}

inline int 
Decimal::decimalPlaces() const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return longLongDecImplPtrM->decimalPlaces();
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM);
      return di.decimalPlaces();
    }
}

inline bool 
Decimal::isNumber() const
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return longLongDecImplPtrM->isNumber();
    }
    else
    {
      return ((decM & DecImpl::CMState) == DecImpl::CSNormal);
    }
}

inline Decimal 
Decimal::operator-() const
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return Decimal(-*longLongDecImplPtrM);
    }
    else
    {
      return create(DecImpl::negateCompact(decM));
    }
}

inline Decimal 
Decimal::maxValue()
{
    // Do we need to optimize this with a static const?
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec = LongLongDecBase::maxValue(); 
      return Decimal(dec);
    }
    else
    {
      DecImpl di = DecBase::maxValue(); 
      return create (di.toCompact());
    }
}

inline Decimal 
Decimal::minValue()
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec = LongLongDecBase::minValue(); 
      return Decimal(dec);
    }
    else
    {
      DecImpl di = DecBase::minValue(); 
      return create (di.toCompact());
    }
}

inline DecBase::RoundingMethod 
Decimal::decBaseRoundingMethod(Decimal::RoundingMethod method)
{
	DecBase::RoundingMethod m;
    
	switch (method) 
	{
	case Decimal::UP: 
		m = DecBase::UP; 
		break;
	case Decimal::DOWN: // same as TRUNCATE
		m = DecBase::DOWN;
		break;
	case Decimal::BANKERS: 
		m = DecBase::BANKERS;
		break;
	case Decimal::PLAIN: //fallthru 
	default:
		m = DecBase::PLAIN; 
		break;
	}
	return (m);
}

inline Decimal 
Decimal::roundDecimal(const Decimal& d, int digits, 
					  DecBase::RoundingMethod method)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec = round(*d.longLongDecImplPtrM, digits, method);
      return Decimal(dec);
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(d.decM);
      di = round(di, digits, method);
      return Decimal::create(di.toCompact());
    }
}

inline Decimal 
Decimal::roundDecimal(const Decimal& d, int digits, 
					  Decimal::RoundingMethod method)
{
	// RW supported modes
	if (method < Decimal::CEILING)
	{
		return roundDecimal(d, digits, decBaseRoundingMethod(method));
	}
	// RW NOT supported modes
	else
	{
		Decimal dec = d;
		bool ltz, gtz;
		if(MAX28DIGIT_DECIMAL_SUPPORT)
		{
			LongLongDecImpl zero =  LongLongDecImpl(0);
			LongLongDecImpl di = *d.longLongDecImplPtrM;
			ltz = di < zero;
			gtz = di > zero;
		}
		else
		{
			DecImpl zero =  DecImpl(0);
			DecImpl di = DecImpl::createFromCompact(d.decM);
			ltz = di < zero;
			gtz = di > zero;
		}
		switch(method)
		{
			case Decimal::CEILING:
			{
				if (gtz)
				{
					method = UP;
				}
				else if (ltz)
				{
					method = DOWN;
				}
				break;
			}
			case FLOOR:
			{
				if (gtz)
				{
					method = DOWN;
				}
				else if (ltz)
				{
					method = UP;
				}
				break;
			}
			case FLOOR_ALT:
			{
				if (gtz)
				{
					method = DOWN_ALT; // fallthru
				}
				else
				{
					method = UP;
					break;
				}
			}
			case DOWN_ALT:
			{
				// Perform a round nearest with scale of digits+1.
				// This is done so that we can correct (4/3)*6000 = 8000.
				// Without this correction we will see result 7999.999...98
				// We want to correct only when rounding mode is XXXX_ALT
				// If we want, we can pass the mode as DOWN_ALT,
				// because decBaseRoudingMethod(DOWN_ALT) will do PLAIN.
				// default case is to do PLAIN.
				dec = Decimal::roundDecimal(d, digits+1, 
       	     		Decimal::decBaseRoundingMethod(PLAIN));

				method = DOWN;
				break;
			}
			default:
			{
				break;
			}
		}
			// default is handled by roundDecimal call.
			return roundDecimal(const_cast<Decimal&>(dec), digits, decBaseRoundingMethod(method));
	}
}

inline Decimal
Decimal::initRealDecimalNull()
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return Decimal();
    }
    return create(DecImpl::CSNull);
}

inline Decimal 
Decimal::initDecimalNull() 
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return from(0.0);
    }
    return create(DecImpl::CNull); 
}

inline Decimal 
Decimal::initInvalidDecimal()
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec =  LongLongDecBase::NaNValue();
      return Decimal(dec);
    }
    return create(DecImpl::CSInvalid); 
}

inline bool
Decimal::initMax28DigitDecimalSupport()
{
    const char* env_var = "MAX28DIGIT_DECIMAL_SUPPORT";
    char* env_val = getenv(env_var);

    if(env_val && toUpper(env_val) == "Y")
    {
      return true;
    }
    return false;
}

inline Decimal 
Decimal::create(const Dec &i)
{
	return Decimal(i);
}

inline void 
Decimal::set(int x, int e)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    { 
      LongLongDecImpl dec(x, e);
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di(x, e);
      decM = di.toCompact(); 
    }
}

inline void 
Decimal::set(int64 x, int e)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl dec((long int) x, e); 
      *longLongDecImplPtrM = dec;
    }
    else
    {
      DecImpl di((long int) x, e); 
      decM = di.toCompact(); 
    }
}

inline void 
Decimal::setDecimalPrecision(int e)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      longLongDecImplPtrM->setDecimalPrecision(e);
    }
    else
    {
      DecImpl di = DecImpl::createFromCompact(decM); 
      di.setDecimalPrecision(e);
      decM = di.toCompact(); 
    }
}

inline const Decimal&
maxDecimal(const Decimal& a, const Decimal& b)
{
    return ((a < b) ? b : a);
}

inline Decimal
abs(const Decimal &d)
{
    return d.abs();
    
}

inline Decimal
round(const Decimal& d, int digits, 
       DecBase::RoundingMethod method = DecBase::PLAIN)
{
    return Decimal::roundDecimal(d, digits, method);
}

inline Decimal
round(const Decimal& d, int digits, Decimal::RoundingMethod method)
{
    return Decimal::roundDecimal (d, digits, method);
}

inline long int
toInt(const Decimal& d, Decimal::RoundingMethod method)
{
    return d.toInt (Decimal::decBaseRoundingMethod(method));
}

inline long int
toInt(const Decimal& d, DecBase::RoundingMethod method)
{
    return d.toInt (method);
}

inline std::ostream&
operator<<(std::ostream& s, const Decimal &d)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      s << *d.longLongDecImplPtrM;
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(d.decM);
      s << lhs;
    }
    return (s);
}

inline long double 
toDouble(const Decimal &d)
{
    return d.toDouble ();
}

inline long int
toInt(const Decimal &d)
{
    return d.toInt ();
}

inline Decimal
operator+(const Decimal& a, const Decimal& b)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl result = *a.longLongDecImplPtrM + *b.longLongDecImplPtrM;
      return Decimal(result);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      DecImpl result = lhs + rhs;

      return Decimal::create(result.toCompact());
    }
}

inline Decimal
operator-(const Decimal& a, const Decimal& b)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl result = *a.longLongDecImplPtrM - *b.longLongDecImplPtrM;
      return Decimal(result);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      DecImpl result = lhs - rhs;

      return Decimal::create(result.toCompact());
    }
}

inline Decimal
operator*(const Decimal& a, const Decimal& b)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl result = *a.longLongDecImplPtrM * *b.longLongDecImplPtrM;
      return Decimal(result);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      DecImpl result = lhs * rhs;

      return Decimal::create(result.toCompact());
    }
}

inline Decimal
operator/(const Decimal& a, const Decimal& b)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      LongLongDecImpl result = *a.longLongDecImplPtrM / *b.longLongDecImplPtrM;
      return Decimal(result);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      DecImpl result = lhs / rhs;

      return Decimal::create(result.toCompact());
    }
}

inline Decimal& 
Decimal::operator+=(const Decimal&a)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      *longLongDecImplPtrM = *longLongDecImplPtrM + *a.longLongDecImplPtrM;
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(decM);
      DecImpl rhs = DecImpl::createFromCompact(a.decM);

      DecImpl result = lhs + rhs;

      decM = result.toCompact(); 
    }
    return (*this); 
}

inline Decimal& 
Decimal::operator-=(const Decimal&a)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      *longLongDecImplPtrM = *longLongDecImplPtrM - *a.longLongDecImplPtrM;
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(decM);
      DecImpl rhs = DecImpl::createFromCompact(a.decM);

      DecImpl result = lhs - rhs;

      decM = result.toCompact(); 
    }
    return (*this); 
}

inline Decimal& 
Decimal::operator*=(const Decimal&a)
{ 
  if(MAX28DIGIT_DECIMAL_SUPPORT)
  {
    *longLongDecImplPtrM = *longLongDecImplPtrM * *a.longLongDecImplPtrM;
  }
  else
  {
    DecImpl lhs = DecImpl::createFromCompact(decM);
    DecImpl rhs = DecImpl::createFromCompact(a.decM);

    DecImpl result = lhs * rhs;

    decM = result.toCompact(); 
  }
  return (*this); 
}

inline Decimal& 
Decimal::operator/=(const Decimal&a)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      *longLongDecImplPtrM = *longLongDecImplPtrM / *a.longLongDecImplPtrM;
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(decM);
      DecImpl rhs = DecImpl::createFromCompact(a.decM);

      DecImpl result = lhs / rhs;

      decM = result.toCompact(); 
    }
    return (*this); 
}

inline bool
operator==(const Decimal& a, const Decimal& b)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return ((LongLongDecBase::equal(*a.longLongDecImplPtrM, *b.longLongDecImplPtrM)) != 0);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      return ((DecBase::equal(lhs, rhs)) != 0);
    }
}

inline bool
operator!=(const Decimal& a, const Decimal& b)
{
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return ((! LongLongDecBase::equal(*a.longLongDecImplPtrM, *b.longLongDecImplPtrM)) != 0);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      return ((! DecBase::equal(lhs, rhs)) != 0);
    }
}

inline bool
operator<(const Decimal& a, const Decimal& b)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return (LongLongDecBase::lessThan(*a.longLongDecImplPtrM, *b.longLongDecImplPtrM) != 0);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      return (DecBase::lessThan(lhs, rhs) != 0);
    }
}

inline bool
operator>(const Decimal& a, const Decimal& b)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return (LongLongDecBase::lessThan(*b.longLongDecImplPtrM, *a.longLongDecImplPtrM) != 0);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      return (DecBase::lessThan(rhs, lhs) != 0);
    }
}

inline bool
operator<=(const Decimal& a, const Decimal& b)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return ((! LongLongDecBase::lessThan(*b.longLongDecImplPtrM, *a.longLongDecImplPtrM)) != 0);
    }
    else
    {
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      return ((! DecBase::lessThan(rhs, lhs)) != 0);
    }
}

inline bool
operator>=(const Decimal& a, const Decimal& b)
{ 
    if(MAX28DIGIT_DECIMAL_SUPPORT)
    {
      return ((! LongLongDecBase::lessThan(*a.longLongDecImplPtrM, *b.longLongDecImplPtrM)) != 0); 
    }
    else
    { 
      DecImpl lhs = DecImpl::createFromCompact(a.decM);
      DecImpl rhs = DecImpl::createFromCompact(b.decM);

      return ((! DecBase::lessThan(lhs, rhs)) != 0);
    }
}
}
#endif /* BAS_DECIMAL_HPP */
