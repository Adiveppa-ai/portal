#ifndef BAS_DATE_HPP
#define BAS_DATE_HPP
// @(#)%Portal Version: Date.hpp:PlatformR2Int:3:2006-Aug-14 10:46:43 %
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
//   Date class implementation.
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//------------------------------------------------------------------------------
// $Log: BAS_Date.hpp,v $
// Revision 1.18  2006/08/13  bertm
// PRSF00228028 - Added Date(u_int64) constructor for DateTime's use.
//
// Revision 1.17  2006/07/18 15:10:59  bertm
// PRSF00223955 - Get rid of "long"s in BAS and FSM modules
//
// Revision 1.16  2002/01/15 09:29:07  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.15  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.14  2001/03/29 11:07:32  bt
// Documentation changed.
//
// Revision 1.13  2001/03/12 15:31:40  bt
// Function toString(BAS_String& result, bool appendString = false) added.
//
// Revision 1.12  2000/09/26 12:15:53  bt
// Function date(BAS_String&,size_t,size_t) added.
//
// Revision 1.11  2000/06/20 15:32:29  sd
// - Constants are definded extern in header files and declared
//   int cpp file.
//
// Revision 1.10  2000/01/26 14:31:22  bt
// - check code review lines an correct all errors
// - constants INVALID_DATE, INVALID_TIME, INVALID_DATETIME added
//
// Revision 1.9  1999/11/10 09:04:33  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.8  1999/09/21 11:57:06  bt
// Constructors added.
//
// Revision 1.6  1999/07/08 10:24:43  bt
// Methods addMonths() and addYears() added.
//
// Revision 1.3  1999/06/28 15:48:32  bt
// Methods seconds() and julian() added.
//
// Revision 1.1  1999/06/11 12:42:53  bt
// Classes BAS_Date and BAS_Time added.
//
//==============================================================================

#ifndef RW_TOOLS_DATE_H
  #include <rw/rwdate.h>
#endif

#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif
#ifndef BAS_DATAVALUE_H
  #include "BAS/DataValue.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace BAS 
{

/**
 *\class Date Date.h "BAS/Date.h"
 This class represents a date (based on RWDate).

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Date.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:51:26 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>
                                                                   
    <p>The date is stored as the number of seconds
       since 00:00:00 January 1, 1901.<br>
       The last date that can be represented with four-byte
       (32-bit) unsigned long is February 5, 2037.<br>
       The internal representation is time zone adjusted.<br><br>

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
class Date : public DataValue
{
  D_SINGLETHREADED

  public:

    /** Enumeration week day number.
        <ul>
        <li> WDN_UNKNOWN = 0
        <li> WDN_MON     = 1
        <li> WDN_TUE     = 2
        <li> WDN_WED     = 3
        <li> WDN_THU     = 4
        <li> WDN_FRI     = 5
        <li> WDN_SAT     = 6
        <li> WDN_SUN     = 7
        <li> WDN_HOL     = 8
        </ul>
    */ 
    enum weekDayNumber
    {
      WDN_UNKNOWN = 0,
      WDN_MON     = 1,
      WDN_TUE     = 2,
      WDN_WED     = 3,
      WDN_THU     = 4,
      WDN_FRI     = 5,
      WDN_SAT     = 6,
      WDN_SUN     = 7,
      WDN_HOL     = 8
    };

    /**@name Public Constructors */
    //@{

      /// Constructs an invalid date object.
      Date();

      /** Constructs a date object with today's date.
        * @param zone The time zone. */
      Date(const RWZone& zone);

      /** Constructs a date object with the given string.
        * @param dateString String with the format 'YYYYMMDD'. */
      Date(const String& dateString);

      /** Constructs a date object with the given string.
        * @param dateString String with the format 'YYYYMMDD'.
        * @param len        Length of the string. */
      Date(const char *dateString, size_t len);

      /** Constructs a date object with the given values.
        * @param day The day should be 01-31.
        * @param month The month should be 01-12.
        * @param year The year should be 1901-2037. */
      Date(const u_int32 day,
           const u_int32 month,
           const u_int32 year);

      /** Constructs a date object with the given number of
        *   seconds since 00:00:00 January 1, 1901. Any
        *   fractional day-seconds will be truncated. */
      Date(u_int64 seconds);

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~Date();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Set the date of self to an invalid value.
      void clear();

      /// Returns true if this is a valid date, false otherwise.
      bool isValid() const;

      /** Changes the date of self to today's date.
        * @param zone The time zone, which defaults to local time.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool date(const RWZone& zone = RWZone::local());

      /** Changes the date of self to the given string.
        * @param str String for the date extraction
        *            with the substring format 'YYYYMMDD'.
        * @param pos Start position of the substring which defaults to zero.
        * @param len Length of the substring which defaults to length of str.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool date(const String& str,
                const size_t pos = 0,
                const size_t len = RW_NPOS);

      /** Changes the date of self to the given values.
        * @param day The day should be 01-31.
        * @param month The month should be 01-12.
        * @param year The year should be 1901-2037.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool date(const u_int32 day,
                const u_int32 month,
                const u_int32 year);

      /** Changes the date of self to the given julian day number.
        * @param jday The julian day number.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool julian(const u_int32 jday);

      /** Changes the date of self to the given number of seconds.
        * @param secs The number of seconds since 00:00:00 01/01/1901.<br>
        *             A modulo 86,400 will be done on "secs" to see if<br>
        *             it contains any fractional day seconds.  If<br>
        *             "secs" is not modulo 86,400, then this object will<br>
        *              be set to an invalid date.  If "secs" is modulo 86,400,<br>
        *             then the object is set to the "secs" value.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool seconds(const u_int64 secs);

      /** Add the given number of days to self (negative values are allowed).
        * @param numOfDays The number of days.
        * @return <tt>true</tt> The given days were added successfully,<br>
        *         <tt>false</tt> otherwise. */
      bool addDays(const int64 numOfDays);

      /** Add the given number of months to self (negative values are allowed).
        * @param numOfMonths The number of months.
        * @return <tt>true</tt> The given months were added successfully,<br>
        *         <tt>false</tt> otherwise. */
      bool addMonths(const int64 numOfMonths);

      /** Add the given number of years to self (negative values are allowed).
        * @param numOfYears The number of years.
        * @return <tt>true</tt> The given years were added successfully,<br>
        *         <tt>false</tt> otherwise. */
      bool addYears(const int64 numOfYears);

      /// Returns the julian day number.
      u_int32 julian() const;

      /// Returns the number of seconds since 00:00:00 01/01/1901.
      u_int64 seconds() const;

      /** Extract day, month and year of self.
        * @param day The returned day.
        * @param month The returned month.
        * @param year The returned year.
        * @return <tt>true</tt> extract successful,<br>
        *         <tt>false</tt> invalid date. */
      bool extract(u_int32& day,
                   u_int32& month,
                   u_int32& year) const;

      /** Returns the number of the day of the week,
        * where Monday = 1 , ... , Sunday = 7 , Error = 0. */
      u_int32 weekDay() const;

      /** Returns the date as string with the format 'YYYYMMDD'.
        * @return The date as string or a null string in case of failure. */
      String asString() const;

      /** Returns the date as string reference with the format 'YYYYMMDD'.
        * @param result The returned date as string.
        * @param appendString If true, the date is appended to the result.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> invalid date. */
      bool toString(String& result, bool appendString = false) const;

      /** Compares date of self as seconds since 00:00:00 01/01/1901.
        * @param date The date to be compared with self.
        * @return <tt>0</tt> if self is equal to <B>date</B>,<br>
        *         <tt>1</tt> if self is greater than <B>date</B>,<br>
        *         <tt>-1</tt> if self is less than <B>date</B>. */
      int compareTo(const Date& date) const;

      /** Check if date of self is between d1 and d2, inclusive.
        * @param d1 The first date to be compared with self.
        * @param d2 The second date to be compared with self.
        * @return <tt>true</tt> d1 is less than or equal to d2 and
        *                       the date is between d1 and d2,<br>
        *         <tt>false</tt> otherwise. */
      bool between(const Date& d1, const Date& d2) const;

      /** Serialize the date
        * @param out The output stream for the serialization
        * @return <tt>true</tt> on success,
        *         <tt>false</tt> otherwise */
      bool serialize(std::ostream& out) const;

      /** Restore the date from an input stream
        * @param in The input stream to use
        * @return <tt>true</tt> on success,
        *         <tt>false</tt> otherwise */
      bool restore(std::istream& in);

      /// Returns the earliest date that can be represented by Date.
      static Date min();

      /// Returns the latest date that can be represented by Date.
      static Date max();

      /** Self test method (<em>for internal use only</em>).
        * @return <tt>True</tt> if class test was successful,<br>
                  <tt>false</tt> otherwise. */
      static bool selfTest();

    //@}

    /**@name Related Global Operators */
    //@{

      /** Operator equal-to (==).
        * @param d1 The first date to be compared.
        * @param d2 The second date to be compared.
        * @return <tt>true</tt> if <B>d1</B> is equal to <B>d2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator==(const Date& d1, const Date& d2);

      /** Operator not-equal-to (!=).
        * @param d1 The first date to be compared.
        * @param d2 The second date to be compared.
        * @return <tt>true</tt> if <B>d1</B> is not equal to <B>d2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator!=(const Date& d1, const Date& d2);

      /** Operator less-than (<).
        * @param d1 The first date to be compared.
        * @param d2 The second date to be compared.
        * @return <tt>true</tt> if <B>d1</B> is less than <B>d2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<(const Date& d1, const Date& d2);

      /** Operator less-than-or-equal (<=).
        * @param d1 The first date to be compared.
        * @param d2 The second date to be compared.
        * @return <tt>true</tt> if <B>d1</B> is less than or equal <B>d2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<=(const Date& d1, const Date& d2);

      /** Operator greater-than (>).
        * @param d1 The first date to be compared.
        * @param d2 The second date to be compared.
        * @return <tt>true</tt> if <B>d1</B> is greater than <B>d2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>(const Date& d1, const Date& d2);

      /** Operator greater-than-or-equal (>=).
        * @param d1 The first date to be compared.
        * @param d2 The second date to be compared.
        * @return <tt>true</tt> if <B>d1</B> is greater than or equal <B>d2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>=(const Date& d1, const Date& d2);

      /** Output operator (format 'YYYY/MM/DD' or invalid date '####/##/##').
        * @param os The output stream.
        * @param date The date to be written to the stream. */
      friend std::ostream& operator<<(std::ostream& os, const Date& date);

    //@}
	
  private:

    // The following private attributes and functions are used internally.

      friend class DateTime;

      u_int64   dateM;     // date, stored as
                           // number of seconds since 00:00:00 01/01/1901

    // Class members.

      BAS_EXPORT static const u_int64 monInYearCM;
      BAS_EXPORT static const u_int64 secsInDayCM;
      BAS_EXPORT static const u_int64 minSecsCM;
      BAS_EXPORT static const u_int64 invalidSecsCM;
      BAS_EXPORT static const u_int64 maxSecsCM;
      BAS_EXPORT static const u_int64 maxDaysCM;

    // Convert string to date.

      bool toDate(const String& str,
                  const size_t pos = 0,
                  const size_t len = RW_NPOS);

      bool toDate(const char *str,
                  const size_t pos,
                  const size_t len);
};

//------------------------------------------------------------------------------
// Some constants.
//------------------------------------------------------------------------------

extern const Date INVALID_DATE;

//------------------------------------------------------------------------------
// Output operator (format 'YYYY/MM/DD' or invalid date '####/##/##')
//------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& os, const Date& date);

//------------------------------------------------------------------------------
// Operator equal-to (==)
//------------------------------------------------------------------------------

inline bool
operator==(const Date& d1, const Date& d2)
{
  return (d1.dateM == d2.dateM);
}

//------------------------------------------------------------------------------
// Operator not-equal-to (!=)
//------------------------------------------------------------------------------

inline bool
operator!=(const Date& d1, const Date& d2)
{
  return (d1.dateM != d2.dateM);
}

//------------------------------------------------------------------------------
// Operator less-than (<)
//------------------------------------------------------------------------------

inline bool
operator<(const Date& d1, const Date& d2)
{
  return (d1.dateM < d2.dateM);
}

//------------------------------------------------------------------------------
// Operator less-than-or-equal (<=)
//------------------------------------------------------------------------------

inline bool
operator<=(const Date& d1, const Date& d2)
{
  return (d1.dateM <= d2.dateM);
}

//------------------------------------------------------------------------------
// Operator greater-than (>)
//------------------------------------------------------------------------------

inline bool
operator>(const Date& d1, const Date& d2)
{
  return (d1.dateM > d2.dateM);
}

//------------------------------------------------------------------------------
// Operator greater-than-or-equal (>=)
//------------------------------------------------------------------------------

inline bool
operator>=(const Date& d1, const Date& d2)
{
  return (d1.dateM >= d2.dateM);
}

//------------------------------------------------------------------------------
// Set the date of self to an invalid value
//------------------------------------------------------------------------------

inline void
Date::clear()
{
  dateM = Date::invalidSecsCM;
}

//------------------------------------------------------------------------------
// Returns true if this is a valid date, false otherwise
//------------------------------------------------------------------------------

inline bool
Date::isValid() const
{
  return (dateM < Date::invalidSecsCM);
}

//------------------------------------------------------------------------------
// Changes the date of self to the given string (format 'YYYYMMDD')
//------------------------------------------------------------------------------

inline bool
Date::date(const String& str,
           const size_t pos,
           const size_t len)
{
  return toDate(str,pos,len);
}

//------------------------------------------------------------------------------
// Returns the julian day number
//------------------------------------------------------------------------------

inline u_int32
Date::julian() const
{
  return (u_int32) ((dateM / Date::secsInDayCM) + rwJul1901);
}

//------------------------------------------------------------------------------
// Returns the number of seconds since 00:00:00 01/01/1901
//------------------------------------------------------------------------------

inline u_int64
Date::seconds() const
{
  return dateM;
}

//------------------------------------------------------------------------------
// Compares date of self as seconds since 00:00:00 01/01/1901
//------------------------------------------------------------------------------

inline int
Date::compareTo(const Date& date) const
{
  return (dateM == date.dateM ? 0 : (dateM > date.dateM ? 1 : -1));
}

//------------------------------------------------------------------------------
// Check if date of self is between d1 and d2, inclusive
//------------------------------------------------------------------------------

inline bool
Date::between(const Date& d1, const Date& d2) const
{
  return ((dateM >= d1.dateM) && (dateM <= d2.dateM));
}

inline bool 
toDate(ConstSubString &str, Date& d)
{
  d = Date(str.data(), str.length());
  return true;
}

typedef Date ShortDate; 
}
#endif // BAS_DATE_HPP

