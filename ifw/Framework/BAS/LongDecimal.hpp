#ifndef BAS_LONGDECIMAL_HPP
#define BAS_LONGDECIMAL_HPP
// @(#)%Portal Version: LongDecimal.hpp:PlatformR2Int:2:2006-Jul-19 16:15:02 %
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of integRate's long decimal value class. This class is based
//   on Rogue Wave's RWDecimal<T> template and is used to avoid rounding errors
//   during calculations.
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//------------------------------------------------------------------------------
// $Log: BAS_LongDecimal.hpp,v $
// Revision 1.7  2006/07/18 15:10:59  bertm
// PRSF00223955 - Get rid of "long"s in BAS and FSM modules
//
// Revision 1.6  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.5  2000/06/29 15:39:09  bt
// Changes for AIX xlC V500.
//
// Revision 1.4  2000/03/08 14:03:40  sd
// Added include for <rw/math.h> to fix some problems with exception handling.
//
// Revision 1.3  2000/03/08 13:04:38  sd
// New function isNull() added.
//
// Revision 1.2  2000/01/31 15:04:17  bt
// Includes for money mp1int and mp2int changed.
//
// Revision 1.1  2000/01/28 15:08:43  sd
// Initial revision of new BAS_LongDecimal (former BAS_Decimal).
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

#ifndef BAS_DEFS_HPP
  #include "BAS/Defs.hpp"
#endif
namespace BAS 
{
class String;

// Here I am defining the base multi precision integer type used in 
// LongDecimal and the base decimal type used for LongDecimal. If you
// want to change the precsion change these typedefs, the are used everywhere 
// in LongDecimal.
typedef RWMP2Int                 MPLongInt;
typedef RWDecimal<MPLongInt> LongDecBase;

/**
 * \class LongDecimal LongDecimal.h "BAS/LongDecimal.h"
 * \internal
 */
class LongDecimal : public LongDecBase, public DataValue
{
  D_SINGLETHREADED

  public:

    /**@name LongDecimal constructors and destructor */
    //@{

    /** Default constructor. 
     */
    LongDecimal();

    /** Constructor with initialization from base class.
     */
    LongDecimal( const LongDecBase& b );

    /** Constructor with initialization from string 
     *  @str LongDecimal string to convert
     */
    LongDecimal( const char* str );

    /** Constructor with initialization from integer
     */
    LongDecimal( int i );

    /** Constructor with initialization from long
     */
    LongDecimal( long l );

    /** Constructor with mantissa and number of digits after decimal point
     *  If you want to construct a LongDecimal for 1.234 you have to 
     *  specify LongDecimal( 1234, 3 ). 
     *  @param x Mantissa to use
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
    LongDecimal( int x, int e );

    /** Constructor with mantissa and number of digits after decimal point
     *  If you want to construct a LongDecimal for 1.234 you have to 
     *  specify LongDecimal( 1234, 3 ).
     *  @param x Mantissa to use
     *  @param e Number of digits behind decimal point (has to be positiv)
     */
    LongDecimal( long int x, int e );

    //@}

    /**@name LongDecimal public member functions */
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

    /** Check if decimal == 0.0 
     */
    bool isNull() const;

    /** Assign the string value to instance. Check for LongDecimal::NaN
     *  after assignment.
     *  @param str The decimal string to assign
     */
    LongDecimal& operator=( const char* str );

    /** Assign the integer value to instance. 
     *  @param i The integer to assign
     */
    LongDecimal& operator=( int i );

    /** Extract decimal number from string.
     *  @param str LongDecimal string for extraction
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
    bool fromString( const char *str );

    /** Extract decimal number from part of a string
     *  @param str String for the decimal extraction
     *  @param pos Start position of part string for extraction
     *  @param len Length of part string for extraction
     *  @return <b>true</b> if string is correct decimal, <b>false</b> otherwise
     */
    bool fromString( const char *str, size_t pos, size_t len );

    /** Write the decimal number to string
     */
    bool toString( String& str, 
		   int len = -1, 
		   int precision = -1, 
		   bool showpoint = false,
		   char padChar = '0' ) const;

    /** Comparison operators for LongDecBase
     */
    friend bool operator<(  const LongDecBase& decBase, 
                            const LongDecimal& decimal );
    friend bool operator<(  const LongDecimal& decimal, 
                            const LongDecBase& decBase );
    friend bool operator<(  const LongDecimal& left, 
                            const LongDecimal& right );
    friend bool operator>(  const LongDecBase& decBase, 
                            const LongDecimal& decimal );
    friend bool operator>(  const LongDecimal& decimal, 
                            const LongDecBase& decBase );
    friend bool operator>(  const LongDecimal& left, 
                            const LongDecimal& right );
    friend bool operator==( const LongDecBase& decBase, 
                            const LongDecimal& decimal );
    friend bool operator==( const LongDecimal& decimal, 
                            const LongDecBase& decBase );
    friend bool operator==( const LongDecimal& left, 
                            const LongDecimal& right );

    /** Execute LongDecimal's self test
     */
    static bool selfTest();

    //@}
  protected:
    static const char* skipSpaces( const char *str );
    static const char* skipSpacesUntil( const char *str, const char *end );

  private:
    // Privat and not implemented, to prevent unintenionally use
    LongDecimal( double d );
    LongDecimal& operator=( double d );
};

BAS_EXPORT extern const LongDecimal LONGDECIMAL_NULL;
BAS_EXPORT extern const LongDecimal INVALID_LONGDECIMAL;

//==============================================================================
// Default constructor
//==============================================================================
inline
LongDecimal::LongDecimal()
  : LongDecBase()
{
}

//==============================================================================
// Constructor with initialization from base class
//==============================================================================
inline
LongDecimal::LongDecimal( const LongDecBase& b )
  : LongDecBase( b )
{
}

//==============================================================================
// Constructor for initialization from integer
//==============================================================================
inline
LongDecimal::LongDecimal( int i )
  : LongDecBase( i )
{
}

//==============================================================================
// Constructor for initialization from long
//==============================================================================
inline
LongDecimal::LongDecimal( long l )
  : LongDecBase( l )
{
}

//==============================================================================
// Initialization from string
//==============================================================================
inline
LongDecimal::LongDecimal( const char *str )
{
  this->fromString( str );
}

//==============================================================================
// Initialization with mantissa and exponent
//==============================================================================
inline 
LongDecimal::LongDecimal( int x, int e )
  : LongDecBase( x, e )
{
}

//==============================================================================
// Set mantissa and exponent
//==============================================================================
inline void
LongDecimal::set( int x, int e )
{
  RWASSERT( e >= 0 );
  mantissa_ = x;
  exponent_ = e;
  state_    = LongDecimal::normal;
}

//==============================================================================
// Set mantissa and exponent
//==============================================================================
inline void
LongDecimal::set( long int x, int e )
{
  RWASSERT( e >= 0 );
  mantissa_ = x;
  exponent_ = e;
  state_    = LongDecimal::normal;
}

//==============================================================================
// Assignement from const char pointer
//==============================================================================
inline LongDecimal&
LongDecimal::operator=( const char* str )
{
  RWPRECONDITION( str != 0 );
  this->fromString( str );
  return *this;
}

//==============================================================================
// Assignement from integer
//==============================================================================
inline LongDecimal&
LongDecimal::operator=( int i )
{
  mantissa_ = i;
  exponent_ = 0;
  state_    = LongDecimal::normal;
  return *this;
}

//==============================================================================
// Return pointer to first non space character in string
//==============================================================================
inline const char*
LongDecimal::skipSpaces( const char *ptr )
{
  while ( *ptr == ' ' ) ptr++;
  return ptr; 
}

//==============================================================================
// Return pointer to first non space character in string
//==============================================================================
inline const char*
LongDecimal::skipSpacesUntil( const char *ptr, const char* end )
{
  while ( (*ptr == ' ' ) && (ptr <= end) )
  { 
    ptr++;
  }

  return ptr;
}

//==============================================================================
// Comparison operators for LongDecBase
//==============================================================================
inline bool 
operator<( const LongDecBase& decBase, const LongDecimal& decimal )
{
  return (LongDecBase::lessThan(decBase, decimal) != 0);
}

inline bool 
operator<( const LongDecimal& decimal, const LongDecBase& decBase )
{
  return (LongDecBase::lessThan(decimal, decBase) != 0);
}

inline bool 
operator>( const LongDecBase& decBase, const LongDecimal& decimal )
{
  return (LongDecBase::lessThan(decimal, decBase) != 0);
}

inline bool 
operator>( const LongDecimal& decimal, const LongDecBase& decBase )
{
  return (LongDecBase::lessThan(decBase, decimal) != 0);
}

inline bool
operator==( const LongDecimal& decimal, const LongDecBase& decBase )
{
  return (LongDecBase::equal(decimal, decBase) != 0);
}

inline bool
operator==( const LongDecBase& decBase, const LongDecimal& decimal )
{
  return (LongDecBase::equal(decBase, decimal) != 0);
}

inline bool 
operator<( const LongDecimal& left, const LongDecimal& right )
{
  return (LongDecBase::lessThan(left, right) != 0);
}

inline bool 
operator>( const LongDecimal& left, const LongDecimal& right )
{
  return (LongDecBase::lessThan(right, left) != 0);
}

inline bool
operator==( const LongDecimal& left, const LongDecimal& right )
{
  return (LongDecBase::equal(left,right ) != 0);
}
}

#endif // BAS_LONGDECIMAL_HPP
