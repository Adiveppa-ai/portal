#ifndef TAM_TRANSID_HPP
#define TAM_TRANSID_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: TAM
//
//------------------------------------------------------------------------------
// Module Description:
//   Transaction id class implementation.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: TAM_TransId.hpp,v $
// $Revision: 1.9 $
// $Author: mliebmann $
// $Date: 2001/08/10 08:15:20 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: TAM_TransId.hpp,v $
// Revision 1.9  2001/08/10 08:15:20  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.8  2001/07/04 13:37:24  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.7  2001/06/18 15:10:30  bt
// Method asString() changed. Default parameter zeroPadded added.
//
// Revision 1.6  2001/04/23 13:48:09  bt
// const added to to????() methods.
//
// Revision 1.5  2001/04/19 14:44:27  bt
// Made method invalidate() public.
//
// Revision 1.4  2001/04/05 13:16:47  bt
// Methods restoreFrom(), saveOn() and binaryStoreSize() changed.
//
// Revision 1.3  2001/03/26 10:19:32  bt
// Description changed.
//
// Revision 1.2  2001/03/23 17:14:01  bt
// Methods restoreFrom(), saveOn() and binaryStoreSize() added.
//
// Revision 1.1  2001/03/22 16:27:19  bt
// Initial version.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif

/** This class represents the transaction id.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TAM_TransId.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.9 $</font></td>
    <td><font size=-1>$Date: 2001/08/10 08:15:20 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>

    <p>The transaction id is a signed integer.<br>
       Minimum value : -999999999999999999 <br>
       Maximum value :  999999999999999999 <br><br>

    <dl>
    <dt><b>Registry entries</b></dt>
    <dd>none</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>none</dd>
    </dl> 
*/
namespace TAM
{
class TransId D_THREADINFO
{
  public:

    /**@name Public Constructors */
    //@{

      /// Default constructor. Constructs a transaction id initialized to zero.
      TransId();

      /** Constructor with initialization from string
        * @param str The transaction id string for extraction. */
      TransId(const char* str);

      /** Constructor with initialization from int64.
        * @param value The int64 value. */
      TransId(const int64& value);

      /** Constructor with initialization from u_int64.
        * @param value The u_int64 value. */
      TransId(const u_int64& value);

      /** Constructor with initialization from double (maximum of 15 digits).
        * @param value The double value. */
      TransId(const double& value);

      /** Constructor with initialization from decimal (maximum of 15 digits).
        * @param value The decimal value. */
      TransId(const BAS::Decimal& value);

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~TransId();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Set self to zero.
      void zero();

      /// Negate self.
      void negate();

      /// Invalidate self.
      void invalidate();

      /// Returns true if self is valid, false otherwise.
      bool isValid() const;

      /// Returns true if self is zero, false otherwise.
      bool isZero() const;

      /// Returns true if self is negative, false otherwise.
      bool isNegative() const;

      /** Extract transaction id from string.
        * @param str The transaction id string for extraction.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool fromString(const char* str);

      /** Extract transaction id from string.
        * @param str The transaction id string for extraction.
        * @param pos Start position of part string for extraction.
        * @param len Length of part string for extraction.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool fromString(const char *str, size_t pos, size_t len);

      /** Converts a int64 value to a transaction id.
        * @param value The int64 value. */
      void fromLong(const int64& value);

      /** Converts a u_int64 value to a transaction id.
        * @param value The u_int64 value. */
      void fromUnsigned(const u_int64& value);

      /** Converts a double value (maximum of 15 digits) to a transaction id.
        * @param value The double value.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool fromDouble(const double& value);

      /** Converts a decimal value (maximum of 15 digits) to a transaction id.
        * @param value The decimal value.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool fromDecimal(const BAS::Decimal& value);

      /** Returns self as string.
        * @param zeroPadded If true, the result is padded with leading zeros.
        * @return The transaction id as string or invalid id '(invalid)'. */
      BAS::String asString(bool zeroPadded = false) const;

      /** Write self to a string.
        * @param result The transaction id as string.
        * @param appendString If true, the id is appended to the result.
        * @param len The length that shall be padded.
        * @param padChar The pad character.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise (invalid id). */
      bool toString(BAS::String& result,
                    bool appendString = false,
                    size_t len = 0,
                    char padChar = '0') const;

      /** Write self to a int64 value.
        * @param result The transaction id as int64 value.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool toLong(int64& result) const;

      /** Write self to a u_int64 value.
        * @param result The transaction id as u_int64 value.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool toUnsigned(u_int64& result) const;

      /** Write self to a double value.
        * @param result The transaction id as double value.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool toDouble(double& result) const;

      /** Write self to a decimal value.
        * @param result The transaction id as decimal value.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> otherwise. */
      bool toDecimal(BAS::Decimal& result) const;

      /** Restore the internal representation of self from memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      void binaryRestore(char*& ptr);

      /** Save the internal representation of self to memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      void binarySave(char*& ptr) const;

      /// Returns the number of bytes necessary to store self.
      u_int64 binaryStoreSize() const;

    //@}

    /**@name Public Member Operators */
    //@{

      /** Add the given transaction id to self.
        * @param id The transaction id.
        * @return Reference to self. */
      TransId& operator+=(const TransId& id);

      /** Add the given u_int64 value to self.
        * @param value The u_int64 value.
        * @return Reference to self. */
      TransId& operator+=(const u_int64 value);

      /** Substract the given transaction id from self.
        * @param id The transaction id.
        * @return Reference to self. */
      TransId& operator-=(const TransId& id);

      /** Substract the given u_int64 value from self.
        * @param value The u_int64 value.
        * @return Reference to self. */
      TransId& operator-=(const u_int64 value);

    //@}

    /**@name Related Global Operators */
    //@{

      /** Operator equal-to (==).
        * @param id1 The first transaction id to be compared.
        * @param id2 The second transaction id to be compared.
        * @return <tt>true</tt> if <B>id1</B> is equal to <B>id2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator==(const TransId& id1, const TransId& id2);

      /** Operator not-equal-to (!=).
        * @param id1 The first transaction id to be compared.
        * @param id2 The second transaction id to be compared.
        * @return <tt>true</tt> if <B>id1</B> is not equal to <B>id2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator!=(const TransId& id1, const TransId& id2);

      /** Operator less-than (<).
        * @param id1 The first transaction id to be compared.
        * @param id2 The second transaction id to be compared.
        * @return <tt>true</tt> if <B>id1</B> is less than <B>id2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<(const TransId& id1, const TransId& id2);

      /** Operator less-than-or-equal (<=).
        * @param id1 The first transaction id to be compared.
        * @param id2 The second transaction id to be compared.
        * @return <tt>true</tt> if <B>id1</B> is less than or equal <B>id2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<=(const TransId& id1, const TransId& id2);

      /** Operator greater-than (>).
        * @param id1 The first transaction id to be compared.
        * @param id2 The second transaction id to be compared.
        * @return <tt>true</tt> if <B>id1</B> is greater than <B>id2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>(const TransId& id1, const TransId& id2);

      /** Operator greater-than-or-equal (>=).
        * @param id1 The first transaction id to be compared.
        * @param id2 The second transaction id to be compared.
        * @return <tt>true</tt> if <B>id1</B> is greater than or equal <B>id2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>=(const TransId& id1, const TransId& id2);

      /** Output operator (number or invalid id '(invalid)').
        * @param os The output stream.
        * @param id The transaction id to be written to the stream. */
      friend std::ostream& operator<<(std::ostream& os, const TransId& id);

    //@}

  private:

    // The following private attributes and functions are used internally.

      int64 transIdLowM;

      int64 transIdHighM;

    // Add the given int64 values.

      void add(const int64& lowVal, const int64& highVal);

    // Substract the given int64 values.

      void substract(const int64& lowVal, const int64& highVal);

    // Check for an overflow condition and set self.

      void checkForOverflow(int64& lowRes, int64& highRes);

    // Adjust the unsigned values to fit into self.

      void adjustUnsigned(u_int64& lowVal, u_int64& highVal);

};

//------------------------------------------------------------------------------
// Set self to zero
//------------------------------------------------------------------------------

inline void
TransId::zero()
{
  transIdLowM = 0;

  transIdHighM = 0;
}

//------------------------------------------------------------------------------
// Negate self
//------------------------------------------------------------------------------

inline void
TransId::negate()
{
  if (isValid() == true)
  {
    transIdLowM = -transIdLowM;

    transIdHighM = -transIdHighM;
  }
}

//------------------------------------------------------------------------------
// Invalidate self
//------------------------------------------------------------------------------

inline void
TransId::invalidate()
{
  transIdLowM = 0;

  transIdHighM = 1000000000L;
}

//------------------------------------------------------------------------------
// Returns true if self is valid, false otherwise
//------------------------------------------------------------------------------

inline bool
TransId::isValid() const
{
  return (transIdHighM < 1000000000L);
}

//------------------------------------------------------------------------------
// Returns true if self is zero, false otherwise
//------------------------------------------------------------------------------

inline bool
TransId::isZero() const
{
  return ((transIdLowM == 0) && (transIdHighM == 0));
}

//------------------------------------------------------------------------------
// Returns true if self is negative, false otherwise
//------------------------------------------------------------------------------

inline bool
TransId::isNegative() const
{
  return ((transIdLowM < 0) || (transIdHighM < 0));
}

//------------------------------------------------------------------------------
// Extract transaction id from string
//------------------------------------------------------------------------------

inline bool
TransId::fromString(const char* str)
{
  return fromString(str,0,strlen(str));
}

//------------------------------------------------------------------------------
// Converts a decimal value (maximum of 15 digits) to a transaction id
//------------------------------------------------------------------------------

inline bool
TransId::fromDecimal(const BAS::Decimal& value)
{
  return fromDouble((double) BAS::toDouble(value));
}

//------------------------------------------------------------------------------
// Returns self as string
//------------------------------------------------------------------------------

inline BAS::String
TransId::asString(bool zeroPadded) const
{
  BAS::String result;

  size_t len = 0;

  if (zeroPadded == true)
  {
    len = 18;
  }

  if (toString(result,false,len) == false)
  {
    result = "(invalid)";
  }

  return result;
}

//------------------------------------------------------------------------------
// Restore the internal representation of self from memory area
//------------------------------------------------------------------------------

inline void
TransId::binaryRestore(char*& ptr)
{
  memcpy(&transIdLowM,ptr,sizeof(transIdLowM));
  ptr += sizeof(transIdLowM);

  memcpy(&transIdHighM,ptr,sizeof(transIdHighM));
  ptr += sizeof(transIdHighM);
}

//------------------------------------------------------------------------------
// Save the internal representation of self to memory area
//------------------------------------------------------------------------------

inline void
TransId::binarySave(char*& ptr) const
{
  memcpy(ptr,&transIdLowM,sizeof(transIdLowM));
  ptr += sizeof(transIdLowM);

  memcpy(ptr,&transIdHighM,sizeof(transIdHighM));
  ptr += sizeof(transIdHighM);
}

//------------------------------------------------------------------------------
// Returns the number of bytes necessary to store self
//------------------------------------------------------------------------------

inline u_int64
TransId::binaryStoreSize() const
{
  return (sizeof(transIdLowM) +
          sizeof(transIdHighM));
}

//------------------------------------------------------------------------------
// Add the given transaction id to self
//------------------------------------------------------------------------------

inline TransId&
TransId::operator+=(const TransId& id)
{
  if (id.isValid() == true)
  {
    add(id.transIdLowM,id.transIdHighM);
  }
  else
  {
    invalidate();
  }

  return *this;
}

//------------------------------------------------------------------------------
// Substract the given transaction id from self
//------------------------------------------------------------------------------

inline TransId&
TransId::operator-=(const TransId& id)
{
  if (id.isValid() == true)
  {
    substract(id.transIdLowM,id.transIdHighM);
  }
  else
  {
    invalidate();
  }

  return *this;
}

//------------------------------------------------------------------------------
// Add the given int64 values
//------------------------------------------------------------------------------

inline void
TransId::add(const int64& lowVal, const int64& highVal)
{
  if (isValid() == true)
  {
    int64 lowRes = transIdLowM + lowVal;
 
    int64 highRes = transIdHighM + highVal;

    checkForOverflow(lowRes,highRes);
  }
}

//------------------------------------------------------------------------------
// Substract the given int64 values
//------------------------------------------------------------------------------

inline void
TransId::substract(const int64& lowVal, const int64& highVal)
{
  if (isValid() == true)
  {
    int64 lowRes = transIdLowM - lowVal;
 
    int64 highRes = transIdHighM - highVal;

    checkForOverflow(lowRes,highRes);
  }
}

//------------------------------------------------------------------------------
// Adjust the unsigned values to fit into self
//------------------------------------------------------------------------------

inline void
TransId::adjustUnsigned(u_int64& lowVal, u_int64& highVal)
{
  while (lowVal >= 1000000000UL)
  {
    lowVal -= 1000000000UL;

    ++highVal;
  }
}

//------------------------------------------------------------------------------
// Output operator
//------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& os, const TransId& id);

//------------------------------------------------------------------------------
// Operator equal-to (==)
//------------------------------------------------------------------------------

inline bool
operator==(const TransId& id1, const TransId& id2)
{
  return ((id1.transIdHighM == id2.transIdHighM) &&
          (id1.transIdLowM == id2.transIdLowM));
}

//------------------------------------------------------------------------------
// Operator not-equal-to (!=)
//------------------------------------------------------------------------------

inline bool
operator!=(const TransId& id1, const TransId& id2)
{
  return ((id1.transIdHighM != id2.transIdHighM) ||
          (id1.transIdLowM != id2.transIdLowM));
}

//------------------------------------------------------------------------------
// Operator less-than (<)
//------------------------------------------------------------------------------

inline bool
operator<(const TransId& id1, const TransId& id2)
{
  return ((id1.transIdHighM < id2.transIdHighM) ||
          ((id1.transIdHighM == id2.transIdHighM) &&
           (id1.transIdLowM < id2.transIdLowM)));
}

//------------------------------------------------------------------------------
// Operator less-than-or-equal (<=)
//------------------------------------------------------------------------------

inline bool
operator<=(const TransId& id1, const TransId& id2)
{
  return ((id1.transIdHighM < id2.transIdHighM) ||
          ((id1.transIdHighM == id2.transIdHighM) &&
           (id1.transIdLowM <= id2.transIdLowM)));
}

//------------------------------------------------------------------------------
// Operator greater-than (>)
//------------------------------------------------------------------------------

inline bool
operator>(const TransId& id1, const TransId& id2)
{
  return ((id1.transIdHighM > id2.transIdHighM) ||
          ((id1.transIdHighM == id2.transIdHighM) &&
           (id1.transIdLowM > id2.transIdLowM)));
}

//------------------------------------------------------------------------------
// Operator greater-than-or-equal (>=)
//------------------------------------------------------------------------------

inline bool
operator>=(const TransId& id1, const TransId& id2)
{
  return ((id1.transIdHighM > id2.transIdHighM) ||
          ((id1.transIdHighM == id2.transIdHighM) &&
           (id1.transIdLowM >= id2.transIdLowM)));
}
}
#endif // TRANSID_HPP

