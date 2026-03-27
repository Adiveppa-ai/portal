#ifndef BAS_DECIMPL_HPP
#define BAS_DECIMPL_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
// only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of integRate's decimal value class. This class is based on 
//   Rogue Wave's RWDecimal<T> template and is used to avoid rounding errors
//   during calculations.
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//------------------------------------------------------------------------------
// Revision 09-Feb-04 keshav
// PRSF00090986: Fix problem with high number of decimal places
//
// Revision 1.33  2002/01/16 13:39:35  sd
// - BAS_Decimal serialize is currently not machine independent
//
// Revision 1.32  2002/01/15 09:29:07  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.31  2001/10/08 15:33:53  cdiab
// PETS #40224: need 2 iScript methodes for conversion from/to strHex to/from Decimal
// added conversion methodes directly in the BAS_Decimal Type.
//
// Revision 1.30  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.29  2001/06/27 11:05:24  clohmann
// Parameter changed to reference.
//
// Revision 1.28  2001/06/19 12:41:38  sd
// - New parameter for the decimal point character
//
// Revision 1.27  2001/06/13 07:45:19  pengelbr
// New global function maxDecimal for FCT_MainRating.
//
// Revision 1.26  2001/01/19 13:40:08  pengelbr
// New function BAS_Decimal::setDecimalPrecision( int e ) to set the
// 'decimal point'.
// Functions skipSpaces now skip '0' also...
//
// Revision 1.25  2000/09/11 09:23:48  aro
// showNull flag set to 'true' by default.
//
// Revision 1.24  2000/08/11 08:50:03  aro
// BAS_Decimal now prints '0' instead of '(null)' per default.
//
// Revision 1.23  2000/06/29 15:39:09  bt
// Changes for AIX xlC V500.
//
// Revision 1.22  2000/03/08 12:19:36  sd
// New method isNull() added.
//
// Revision 1.21  2000/03/07 09:49:33  sd
// Behaviour of parameter showPoint in toString() changed. The decimal point
// will be suppressed if showPoint is set to false.
//
// Revision 1.20  2000/01/31 15:04:17  bt
// Includes for money mp1int and mp2int changed.
//
// Revision 1.19  2000/01/28 15:06:48  sd
// Precision changed from MP2Int to MP1Int.
// The old Precision is now used in BAS_LongDecimal
//
// Revision 1.18  2000/01/26 10:13:06  sd
// INVALID_DECIMAL added.
//
// Revision 1.17  2000/01/12 16:29:04  sd
// Some comparison operators added again ...
//
// Revision 1.11  2000/01/11 14:59:24  sd
// Constructor BAS_Decimal( long ) added.
//
// Revision 1.10  2000/01/05 10:49:22  sd
// Privat constructor BAS_Decimal(double) to prevent unintenionally use.
//
// Revision 1.9  1999/12/21 11:33:22  sd
// Some performance improvements.
// New operator=(int) added.
//
// Revision 1.8  1999/12/21 08:42:54  aro
// Fix in compiler defines.
//
// Revision 1.7  1999/12/21 08:37:07  sd
// QuickHack to support SUNPRO_CC V4.2 and RWMultiPrecisionInt.
//
// Revision 1.6  1999/12/20 13:00:35  sd
// Parameters for BAS_Decimal.toString() changed.
//
// Revision 1.5  1999/12/20 10:00:14  sd
// Include rw/dcmldefs.h added.
//
// BAS_Decimal is now a class to provide faster conversion to and from strings.
// Now there is also an assignment operator for decimal strings.
//
// Revision 1.2  1999/12/14 12:46:35  sd
// Introduction of BAS_Decimal.
//
// Revision 1.1  1999/12/13 16:06:52  sd
// Initial revision.
//
//==============================================================================

#ifndef RW_CURRENCY_MP1INT_H
  #include <rw/currency/mp1int.h>
#endif

// Hack to solve problems with RW
#if (defined(__SUNPRO_CC) && (__SUNPRO_CC == 0x420))
#undef __SUNPRO_CC
#define __SUNPRO_CC 0x500
#ifndef RW_CURRENCY_MP2INT_H
  #include <rw/currency/mp2int.h>
#endif
#undef __SUNPRO_CC
#define __SUNPRO_CC 0x420
#else
#ifndef RW_CURRENCY_MP2INT_H
  #include <rw/currency/mp2int.h>
#endif
#endif

#ifndef RW_TOOLS_CSTRING_COMPAT_H
  #include <rw/cstring.h>
#endif
#ifndef RW_CURRENCY_DECIMAL_H
  #include <rw/currency/decimal.h>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_DEFS_HPP
  #include "BAS/Defs.hpp"
#endif


// Here I am defining the base multi precision integer type used in BAS_DecImpl
// and the base decimal type used for BAS_DecImpl. If you want to change the
// precsion change these typedefs, the are used everywhere in BAS_DecImpl.
namespace BAS
{
class String;
class Decimal;

typedef RWMP1Int             MPInt;
typedef RWDecimal<MPInt> DecBase;
typedef rwuint64 Dec;

/** 
 */
class DecImpl : public DecBase D_THREADINFO_M
{
  D_SINGLETHREADED

  public:

    /**@name DecImpl constructors and destructor */
    //@{

    /** Default constructor. 
     */
    DecImpl();

    /** Constructor with initialization from base class.
     */
    DecImpl( const DecBase& b );

    /** Constructor with initialization from string 
     *  @str Decimal string to convert
     */
    DecImpl( const char* str );

    /** Constructor with initialization from string 
     *  @str Decimal string to convert
     *  @len Number of characters to be used in the string
     */
    DecImpl( const char* str, size_t len );

    /** Constructor with initialization from integer
     */
    DecImpl( int i );

    /** Constructor with initialization from long
     */
    DecImpl( long l );

    /** Constructor with mantissa and number of digits after decimal point
     *  If you want to construct a DecImpl for 1.234 you have to 
     *  specify DecImpl( 1234, 3 ). 
     *  @param x Mantissa to use
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
    DecImpl( int x, int e );

    /** Constructor with mantissa and number of digits after decimal point
     *  If you want to construct a DecImpl for 1.234 you have to 
     *  specify DecImpl( 1234, 3 ).
     *  @param x Mantissa to use
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
    DecImpl( long int x, int e );

    //@}

    /**@name DecImpl public member functions */
    //@{

    /** Set mantissa and number of digits after decimal point.
     *  If you want to set the decimal value to 1.234 you have use
     *  specify set( 1234, 3 ).
     *  @param x Mantissa to use
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
    void set( int x, int e );

    /** Set mantissa and number of digits after decimal point
     *  If you want to set the decimal value to 1.234 you have use
     *  specify set( 1234, 3 ).
     *  @param x Mantissa to use
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
    void set( long int x, int e );

    /** Set only the number of digits after decimal point
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
    void setDecimalPrecision( int e );

    /** Check if decimal == 0.0 
     */
    bool isNull() const;

    /** Assign the string value to instance. Check for DecImpl::NaN
     *  after assignment.
     *  @param str The decimal string to assign
     */
    DecImpl& operator=( const char* str );

    /** Assign the integer value to instance. 
     *  @param i The integer to assign
     */
    DecImpl& operator=( int i );

    /** Extract decimal number from string.
     *  @param str Decimal string for extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
    bool fromString( const char *str,
                     char point = '.' );

    /** Extract decimal number from part of a string
     *  @param str String for the decimal extraction
     *  @param pos Start position of part string for extraction
     *  @param len Length of part string for extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
    bool fromString( const char *str, size_t pos, size_t len, 
                     char point = '.' );

    /** Write the decimal number to string
     *  @param len
     *  @param precision Number of digits after the decimal point.
     *  @param showPoint <b>True</b> output of decimal point is enabled, otherwise disabled.
     *  @param showNull Enables the conversion of the state DecImpl::null to "(null)"
     *                  if set to <b>true</b>, "0" is used otherwise (default).
     *  @param point The character used as decimal point
     *  @param padChar
     */
    bool toString( String& str, 
                   int len = -1, 
                   int precision = -1, 
                   bool showPoint = true,
                   bool showNull  = true,
                   char padChar = '0',
                   char point = '.' ) const;

    /** Extract decimal number from a Hexadecimal string in ASCII format
     *  @param str Hexadecimal string for the decimal extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
    bool fromHexString( const char *str,
                        char point = '.' );

    /** Extract decimal number from part of a Hexadecimal string in ASCII format
     *  @param str Hexadecimal for the decimal extraction
     *  @param pos Start position of part string for extraction
     *  @param len Length of part string for extraction
     *  @param point The character used as decimal point
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
    bool fromHexString( const char *str, size_t pos, size_t len, 
                        char point = '.' );

    /** Write the decimal number to a Hexadecimal string in ASCII format
     *  @param len
     *  @param precision Number of digits after the decimal point.
     *  @param showPoint <b>True</b> output of decimal point is enabled, otherwise disabled.
     *  @param showNull Enables the conversion of the state DecImpl::null to "(null)"
     *                  if set to <b>true</b>, "0" is used otherwise (default).
     *  @param point The character used as decimal point
     *  @param padChar
     */
    bool toHexString( String& str, 
                      int len = -1, 
                      int precision = -1, 
                      bool showPoint = true,
                      bool showNull  = true,
                      char padChar = '0',
                      char point = '.' ) const;

    /** Serialize the decimal number into an output stream (currently not
     *  machine indepent!)
     *  @param out Output stream
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool serialize( std::ostream& out ) const;

    /** Restore the decimal number 
     *  @param in Input stream
     *  @return <b>true</b> on success, <b> false</b> otherwise
     */
    bool restore( std::istream& in );

	/** Compact the decimal number to the Dec form.
	 *  @return Equivalent Dec value.
	 */
    Dec toCompact() const;

	/** Expand the passed compact Dec value to the DecImpl form.
	 *  @param i input Dec value.
	 *  @return Equivalent decimal number.
	 */
    static DecImpl createFromCompact( const Dec i );

    /** Comparison operators for DecBase
     */
    friend bool operator<(  const DecBase& decBase, 
                            const DecImpl& decimal );
    friend bool operator<(  const DecImpl& decimal, 
                            const DecBase& decBase );
    friend bool operator<(  const DecImpl& left, 
                            const DecImpl& right );
    friend bool operator>(  const DecBase& decBase, 
                            const DecImpl& decimal );
    friend bool operator>(  const DecImpl& decimal, 
                            const DecBase& decBase );
    friend bool operator>(  const DecImpl& left, 
                            const DecImpl& right );
    friend bool operator==( const DecBase& decBase, 
                            const DecImpl& decimal );
    friend bool operator==( const DecImpl& decimal, 
                            const DecBase& decBase );
    friend bool operator==( const DecImpl& left, 
                            const DecImpl& right );

    /** Execute DecImpl's self test
     */
    static bool selfTest();

    //@}
    
  protected:
    static const char* skipSpaces( const char *str );
    static const char* skipSpacesUntil( const char *str, const char *end );

    friend class Decimal;

    ///////////////////////////////////
    // Encoding scheme  (jpk) 
    // ---------------
    // High 16 bits of the resulting 64-bit int:
    //  F E D C   B A 9 8   7 6 5 4   3 2 1 0
    //  X s f f   f f e e   e e e m   m m m m
    //    where
    //      X = don't care
    //      s = sign bit (1 if neg)
    //      f = state bit (flags)
    //      e = exponent
    //      m = mantissa
    // 
    // The remaining low 48 bits contain the rest of the mantissa.
    //
    // Using 32-bit int is more efficient for bit ops than 64-bit int.
    // The integer we use for encoding the sign, state and exponent:
    //  F E D C   B A 9 8   7 6 5 4   3 2 1 0   
    //  0 0 0 0   0 0 s f   f f f e   e e e e
    // 
    // Notes:
    // 1. Absolute value of mantissa is stored.
    // 2. Minimal shifts: Sign ORed in.
    // 3. Most shifts are on int32 or uint32;
    // 4. Safe to use int32, because our sign bit will never be set.
    // 
    // The performance is very sensitive to the encoding method and the 
    // algorithm used. Any change here needs thorough review and 
    // benchmarking.
    //
    // The decoding algorithm works about 15% faster if fromCompact takes
    // the arguments state, exponent and mantissa instead of the ref to 
    // the DecImpl object. For cleanliness we won't do that.
    //
    // The translation methods need to be part of DecImpl instead of
    // Decimal, because they need to access the members of 
    // DecBase.


    enum Shifts { 
        SSign       = 1, 
        SState      = 4, 
        SExponent   = 5, 
        SRestLow    = 10,
        SRestHigh   = 53
    };

    enum Masks  { 
        MSign           = 0x0001,
        MState          = 0x000F, 
        MExponent       = 0x001F,
        MSignNoShift    = 0x0200, 
        MRestLow        = 0x03FF
    };

    // These constants allow operation on Dec directly without decoding
    BAS_EXPORT static const Dec CNull;     // 0.0 (decimal null)
    BAS_EXPORT static const Dec CSNormal;  // normal state
    BAS_EXPORT static const Dec CSNull;    // null state
    BAS_EXPORT static const Dec CSInvalid; // NaN state
    BAS_EXPORT static const Dec CSCtorErr; // constructor error
    BAS_EXPORT static const Dec CSMissing; // missing

    BAS_EXPORT static const Dec CMSign;
    BAS_EXPORT static const Dec CMState;
    BAS_EXPORT static const Dec CMExponent;
    BAS_EXPORT static const Dec CMMantissa;

    void fromCompact( const Dec& i );
    static Dec negateCompact( const Dec& i );

	BAS_EXPORT static const BAS::MPInt* pow16CM[];
	BAS_EXPORT static const MPInt* pow10CM[];
	BAS_EXPORT static const int maxPow16DigitsCM;
	BAS_EXPORT static const int maxPow10DigitsCM;
	BAS_EXPORT static const int maxPrecisionCM;
	BAS_EXPORT static const int lookupCM[];
	BAS_EXPORT static const char lookupHexCM[];
  private:
    // Private and not implemented, to prevent unintenionally use
    DecImpl( double d );
    DecImpl& operator=( double d );

    DecImpl( Dec d );
    DecImpl& operator=( Dec d );
};

extern const DecImpl DECIMPL_NULL;
extern const DecImpl INVALID_DECIMPL;

//==============================================================================
// Default constructor
//==============================================================================
inline
DecImpl::DecImpl()
  : DecBase()
{
}

//==============================================================================
// Constructor with initialization from base class
//==============================================================================
inline
DecImpl::DecImpl( const DecBase& b )
  : DecBase( b )
{
}

//==============================================================================
// Constructor for initialization from integer
//==============================================================================
inline
DecImpl::DecImpl( int i )
  : DecBase( i )
{
}

//==============================================================================
// Constructor for initialization from long
//==============================================================================
inline
DecImpl::DecImpl( long l )
  : DecBase( l )
{
}

//==============================================================================
// Initialization from string
//==============================================================================
inline
DecImpl::DecImpl( const char *str )
{
    this->fromString( str );
}

inline
DecImpl::DecImpl( const char *str, size_t len )
{
    this->fromString( str, 0, len );
}

//==============================================================================
// Initialization with mantissa and exponent
//==============================================================================
inline 
DecImpl::DecImpl( int x, int e )
  : DecBase( x, e )
{
}

//==============================================================================
// Initialization with mantissa and exponent
//==============================================================================
inline 
DecImpl::DecImpl( long int x, int e )
  : DecBase( x, e )
{
}

//==============================================================================
// Set mantissa and exponent
//==============================================================================
inline void
DecImpl::set( int x, int e )
{
  RWASSERT( e >= 0 );
  mantissa_ = x;
  exponent_ = e;
  state_    = DecImpl::normal;
}

//==============================================================================
// Set mantissa and exponent
//==============================================================================
inline void
DecImpl::set( long int x, int e )
{
  RWASSERT( e >= 0 );
  mantissa_ = x;
  exponent_ = e;
  state_    = DecImpl::normal;
}

//==============================================================================
// Set exponent
//==============================================================================
inline void
DecImpl::setDecimalPrecision( int e )
{
  RWASSERT( e >= 0 );
  exponent_ = e;
  state_    = DecImpl::normal;
}

//==============================================================================
// Assignement from const char pointer
//==============================================================================
inline DecImpl&
DecImpl::operator=( const char* str )
{
    RWPRECONDITION( str != 0 );
    this->fromString( str );
    return *this;
}

//==============================================================================
// Assignement from integer
//==============================================================================
inline DecImpl&
DecImpl::operator=( int i )
{
  mantissa_ = i;
  exponent_ = 0;
  state_    = DecImpl::normal;
  return *this;
}

//==============================================================================
// Return pointer to first non space character in string
//==============================================================================
inline const char*
DecImpl::skipSpaces( const char *ptr )
{
  while ( *ptr == ' ' || *ptr == '0' ) ptr++;
  return ptr; 
}

//==============================================================================
// Return pointer to first non space character in string
//==============================================================================
inline const char*
DecImpl::skipSpacesUntil( const char *ptr, const char* end )
{
  while ( (*ptr == ' ' || *ptr == '0' ) && (ptr <= end) )
  { 
    ptr++;
  }

  return ptr;
}

//==============================================================================
// Comparison operators for DecBase
//==============================================================================
inline bool 
operator<( const DecBase& decBase, const DecImpl& decimal )
{
  return ( DecBase::lessThan( decBase, decimal ) != 0 );
}

inline bool 
operator<( const DecImpl& decimal, const DecBase& decBase )
{
    return ( DecBase::lessThan( decimal, decBase ) != 0 );
}

inline bool 
operator>( const DecBase& decBase, const DecImpl& decimal )
{
  return ( DecBase::lessThan( decimal, decBase ) != 0 );
}

inline bool 
operator>( const DecImpl& decimal, const DecBase& decBase )
{
    return ( DecBase::lessThan( decBase, decimal ) != 0 );
}

inline bool
operator==( const DecImpl& decimal, const DecBase& decBase )
{
    return ( DecBase::equal( decimal, decBase ) != 0 );
}

inline bool
operator==( const DecBase& decBase, const DecImpl& decimal )
{
    return ( DecBase::equal( decBase, decimal ) != 0 );
}

inline bool 
operator<( const DecImpl& left, const DecImpl& right )
{
    return ( DecBase::lessThan( left, right ) != 0 );
}

inline bool 
operator>( const DecImpl& left, const DecImpl& right )
{
    return ( DecBase::lessThan( right, left ) != 0 );
}

inline bool
operator==( const DecImpl& left, const DecImpl& right )
{
    return ( DecBase::equal( left, right ) != 0 );
}

inline const DecImpl&
maxDecimal( const DecImpl& decimal1, const DecImpl& decimal2 )
{
  if ( decimal1 < decimal2 )
    return decimal2;
  else
    return decimal1;
}

inline Dec
DecImpl::negateCompact( const Dec& i )
{
    // Just flip the sign bit
    return ( i ^ CMSign );
}

// The global function toString(DecBase&) needs to
// be overloaded; otherwise the crummy slow RW toString will get 
// executed instead of the fast toString() method provided in this
// class.
String toString( const DecImpl &decimal );
}
#endif // BAS_DECIMPL_HPP
