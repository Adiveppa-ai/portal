#ifndef BAS_DATETIME_HPP
#define BAS_DATETIME_HPP
//==============================================================================
//
// Copyright (c) 1998, 2018, Oracle and/or its affiliates. All rights reserved.
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   Date and time class implementation.
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//------------------------------------------------------------------------------
// $Log: BAS_DateTime.hpp,v $
// Revision 1.30  2006/08/13  bertm
// PRSF00228028 - Reduce the memory size of BAS::DateTime
//
// Revision 1.29  2006/07/18 15:10:59  bertm
// PRSF00223955 - Get rid of "long"s in BAS and FSM modules
//
// Revision 1.28  2002/01/15 09:29:07  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.27  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.26  2001/07/03 08:41:31  bt
// - PETS #36553 Input of AscDate("%H%M%S") failed without error.
// - Method dateTime(BAS_String&,BAS_String&,size_t,size_t) changed.
//
// Revision 1.25  2001/06/20 14:50:33  bt
// Documentation changed.
//
// Revision 1.24  2001/06/20 14:46:45  bt
// Methods secondsUnix() added.
//
// Revision 1.23  2001/03/30 16:41:26  bt
// Methods secondsGMT() added and documentation changed.
//
// Revision 1.22  2001/03/28 07:46:49  bt
// Binary store and restore methods changed.
//
// Revision 1.21  2001/03/23 16:43:04  bt
// Methods restoreFrom(), saveOn() and binaryStoreSize() added.
//
// Revision 1.20  2001/03/12 15:32:07  bt
// Function toString(BAS_String& result) added.
//
// Revision 1.19  2000/09/26 12:19:37  bt
// Functions dateTime(BAS_String&, size_t, size_t) and
// dateTime(BAS_String&, BAS_String&, size_t, size_t) added.
//
// Revision 1.18  2000/06/20 15:32:29  sd
// - Constants are definded extern in header files and declared
//   int cpp file.
//
// Revision 1.17  2000/05/16 13:45:45  jkeckst
// add new function to set date with mask.
//
// Revision 1.16  2000/01/26 14:31:22  bt
// - check code review lines an correct all errors
// - constants INVALID_DATE, INVALID_TIME, INVALID_DATETIME added
//
// Revision 1.15  1999/11/10 09:04:33  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.14  1999/09/21 11:57:06  bt
// Constructors added.
//
// Revision 1.12  1999/07/08 10:24:43  bt
// Methods addMonths() and addYears() added.
//
// Revision 1.9  1999/06/28 15:48:32  bt
// Methods seconds() and julian() added.
//
// Revision 1.6  1999/06/11 12:42:53  bt
// Classes BAS_Date and BAS_Time added.
//
// Revision 1.5  1999/06/10 12:02:52  aro
// Online doc updated.
//
// Revision 1.3  1999/06/08 13:00:04  bt
// Method addDays() added.
//
// Revision 1.2  1999/06/07 16:38:27  bt
// First usable version.
//
// Revision 1.1  1999/06/03 16:07:26  bt
// Initial version.
//==============================================================================

#ifndef RW_TOOLS_TIME_H
  #include <rw/rwtime.h>
#endif
#ifndef RW_TOOLS_DATE_H
  #include <rw/rwdate.h>
#endif

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_DATE_HPP
  #include "BAS/Date.hpp"
#endif
#ifndef BAS_TIME_HPP
  #include "BAS/Time.hpp"
#endif
#ifndef BAS_DATAVALUE_H
  #include "BAS/DataValue.hpp"
#endif

namespace BAS
{
/** This class represents a date and time (based on RWDate).

    <p>The time portion is stored as number of seconds within the day.<br>
       The date portion and both parts (date and time) are stored as<br>
       the number of seconds since 00:00:00 January 1, 1901.<br>
       The last date and time that can be represented with four-byte<br>
       (32-bit) unsigned long is 23:59:59 February 5, 2037.<br>
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
	class DateTime: public DataValue
{
  D_SINGLETHREADED

  public:

    /**@name Public Constructors */
    //@{

      /// Constructs an invalid date and time object.
      DateTime();

      /** Constructs an date and time object with the present time.
        * @param zone The time zone. */
      DateTime(const RWZone& zone);

      /** Constructs an date and time object with the given values.
        * @param date The date as Date.
        * @param time The time as Time. */
      DateTime(const Date& date,const Time& time);

      /** Constructs an date and time object with the given string.
        * @param dateTimeString String with the
        * format 'YYYYMMDDHHMMSS', 'YYYYMMDDHH:MM:SS' or 'YYYYMMDDHH:MM'. */
      DateTime(const String& dateTimeString);

      /** Constructs an date and time object with the given values.
        * @param day The day should be 01-31.
        * @param month The month should be 01-12.
        * @param year The year should be 1901-2037.
        * @param hour The hour should be 00-23.
        * @param minute The minute should be 00-59.
        * @param second The second should be 00-59. */
      DateTime(const u_int32 day,
               const u_int32 month,
               const u_int32 year,
               const u_int32 hour,
               const u_int32 minute,
               const u_int32 second);

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~DateTime();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Set the date and time of self to invalid values.
      void clear();

      /// Returns true if this is a valid date and time, false otherwise.
      bool isValid() const;

      /// Returns the date portion of self.
      const Date date() const;

      /** Changes the date portion of self to the given value.
        * @param date The date as Date.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool date(const Date& date);

      /** Changes the date portion of self to the given string.
        * @param dateString String with the format 'YYYYMMDD'.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool date(const String& dateString);

      /** Changes the date portion of self to the given values.
        * @param day The day should be 01-31.
        * @param month The month should be 01-12.
        * @param year The year should be 1901-2037.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date. */
      bool date(const u_int32 day,
                const u_int32 month,
                const u_int32 year);

      /// Changes the date portion of self to the given julian day number.
      bool date(const u_int32 jday);

      /// Returns the time portion of self.
      const Time time() const;

      /** Changes the time portion of self to the given value.
        * @param time The time as Time.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid time. */
      bool time(const Time& time);

      /** Changes the time portion of self to the given string.
        * @param timeString String with format 'HHMMSS', 'HH:MM:SS' or 'HH:MM'.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid time. */
      bool time(const String& timeString);

      /** Changes the time portion of self to the given values.
        * @param hour The hour should be 00-23.
        * @param minute The minute should be 00-59.
        * @param second The second should be 00-59.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid time. */
      bool time(const u_int32 hour,
                const u_int32 minute,
                const u_int32 second);

      /** Changes date and time of self to the present time.
        * @param zone The time zone, which defaults to local time.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool dateTime(const RWZone& zone = RWZone::local());

      /** Changes date and time of self to the given values.
        * @param date The date as Date.
        * @param time The time as Time.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool dateTime(const Date& date,const Time& time);

      /** Changes date and time of self to the given string.
        * @param str String for the date and time extraction with the format
        *            'YYYYMMDDHHMMSS', 'YYYYMMDDHH:MM:SS' or 'YYYYMMDDHH:MM'.
        * @param pos Start position of the substring which defaults to zero.
        * @param len Length of the substring which defaults to length of str.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool dateTime(const String& str,
                    const size_t pos = 0,
                    const size_t len = RW_NPOS);

      /** Changes date and time of self to the given string.<br>
        * Possible values for the format string are :<br>
        *   %Y : year, including the century [1901,2037]<br>
        *   %y : year within century [00,99]<br>
        *   %m : month number [01,12]<br>
        *   %d : day of month [01,31]<br>
        *   %H : hour (24-hour clock) [00,23]<br>
        *   %M : minute [00,59]<br>
        *   %S : seconds [00,59]<br>
        *   %% : literal '%' character<br>
        * Example : '%y-%m-%d %H:%M:%S'.<br>
        * If the format string is empty, the default formats
        * '%Y%m%d%H%M%S', '%Y%m%d%H:%M:%S' or '%Y%m%d%H:%M' are used.
        * @param str String for the date and time extraction.
        * @param frmStr Describes the format of the substring.
        * @param pos Start position of the substring which defaults to zero.
        * @param len Length of the substring which defaults to length of str.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool dateTime(const String& str,
                    const String& frmStr,
                    const size_t pos = 0,
                    const size_t len = RW_NPOS);

      /** Changes date and time of self to the given values.
        * @param day The day should be 01-31.
        * @param month The month should be 01-12.
        * @param year The year should be 1901-2037.
        * @param hour The hour should be 00-23.
        * @param minute The minute should be 00-59.
        * @param second The second should be 00-59.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool dateTime(const u_int32 day,
                    const u_int32 month,
                    const u_int32 year,
                    const u_int32 hour,
                    const u_int32 minute,
                    const u_int32 second);

      /** Changes self to the given number of seconds since 1901.
        * @param secs Number of seconds since 00:00:00 01/01/1901.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool seconds(const u_int64 secs);

      /** Changes self to the given number of seconds since 1901 in GMT/UTC.<br>
        * Should be used to convert a RWTime value to self.
        * @param secs Number of seconds since 00:00:00 01/01/1901 in GMT/UTC.
        * @param zone Time zone, which defaults to local time.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool secondsGMT(const u_int64 secs,
                      const RWZone& zone = RWZone::local());

      /** Changes self to the given number of seconds since 1970 in GMT/UTC.<br>
        * Should be used to convert a unix time value to self.
        * @param secs Number of seconds since 00:00:00 01/01/1970 in GMT/UTC.
        * @param zone Time zone, which defaults to local time.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool secondsUnix(const u_int64 secs,
                       const RWZone& zone = RWZone::local());

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

      /** Returns the number of seconds since 1901.
        * @return The number of seconds since 00:00:00 01/01/1901. */
      u_int64 seconds() const;

      /** Returns the number of seconds since 1901 in GMT/UTC.<br>
        * Should be used to convert self to a RWTime value.
        * @param zone The time zone, which defaults to local time.
        * @return The number of seconds since 00:00:00 01/01/1901 in GMT/UTC. */
      u_int64 secondsGMT(const RWZone& zone = RWZone::local()) const;

      /** Returns the number of seconds since 1970 in GMT/UTC.<br>
        * Should be used to convert self to a unix time value.
        * @param zone The time zone, which defaults to local time.
        * @return The number of seconds since 00:00:00 01/01/1970 in GMT/UTC. */
      u_int64 secondsUnix(const RWZone& zone = RWZone::local()) const;

      /** Returns self as string with the format 'YYYYMMDDHHMMSS'.
        * @return Self as string or a null string in case of failure. */
      String asString() const;

      /** Returns self as string reference with the format 'YYYYMMDDHHMMSS'.
        * @param result The returned date and time as string.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> invalid date and time. */
      bool toString(String& result) const;

      /** Returns self as string with the specified format.<br>
          Formats are as defined by the function strftime(). */
      String asString(const String& frmStr, const RWZone& zone = RWZone::utc()) const;

      /** Restore the internal representation of self from memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      void binaryRestore(char*& ptr);

      /** Save the internal representation of self to memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      void binarySave(char*& ptr) const;

      /// Returns the number of bytes necessary to store self.
      size_t binaryStoreSize() const;

      /** Serialize the time
        * @param out The output stream for the serialization
        * @return <tt>true</tt> on success,
        *         <tt>false</tt> otherwise */
      bool serialize(std::ostream& out) const;

      /** Restore the time from an input stream
        * @param in The input stream to use
        * @return <tt>true</tt> on success,
        *         <tt>false</tt> otherwise */
      bool restore(std::istream& in);

      /** Compares date portion of self as seconds since 00:00:00 01/01/1901.
        * @param dateTime The date to be compared with self.
        * @return <tt>0</tt> if self is equal to <B>dateTime</B>,<br>
        *         <tt>1</tt> if self is greater than <B>dateTime</B>,<br>
        *         <tt>-1</tt> if self is less than <B>dateTime</B>. */
      int compareDate(const DateTime& dateTime) const;

      /** Compares time portion of self as seconds within the day.
        * @param dateTime The time to be compared with self.
        * @return <tt>0</tt> if self is equal to <B>dateTime</B>,<br>
        *         <tt>1</tt> if self is greater than <B>dateTime</B>,<br>
        *         <tt>-1</tt> if self is less than <B>dateTime</B>. */
      int compareTime(const DateTime& dateTime) const;

      /** Compares date and time of self as seconds since 00:00:00 01/01/1901.
        * @param dateTime The date and time to be compared with self.
        * @return <tt>0</tt> if self is equal to <B>dateTime</B>,<br>
        *         <tt>1</tt> if self is greater than <B>dateTime</B>,<br>
        *         <tt>-1</tt> if self is less than <B>dateTime</B>. */
      int compareTo(const DateTime& dateTime) const;

      /** Check if the date portion of self is between dt1 and dt2, inclusive.
        * @param dt1 The first date to be compared with self.
        * @param dt2 The second date to be compared with self.
        * @return <tt>true</tt> The date portion is between dt1 and dt2,<br>
        *         <tt>false</tt> otherwise. */
      bool dateBetween(const DateTime& dt1, const DateTime& dt2) const;

      /** Check if the time portion of self is between dt1 and dt2, inclusive.
        * @param dt1 The first time to be compared with self.
        * @param dt2 The second time to be compared with self.
        * @return <tt>true</tt> The time portion is between dt1 and dt2,<br>
        *         <tt>false</tt> otherwise. */
      bool timeBetween(const DateTime& dt1, const DateTime& dt2) const;

      /** Check if date and time of self is between dt1 and dt2, inclusive.
        * @param dt1 The first date and time to be compared with self.
        * @param dt2 The second date and time to be compared with self.
        * @return <tt>true</tt> dt1 is less than or equal to dt2 and
        *                       the date and time is between dt1 and dt2,<br>
        *         <tt>false</tt> otherwise. */
      bool between(const DateTime& dt1, const DateTime& dt2) const;

      /** Returns the earliest date and time
        * that can be represented by DateTime. */
      static DateTime min();

      /** Returns the latest date and time
        * that can be represented by DateTime. */
      static DateTime max();
    //@}

    /**@name Related Global Operators */
    //@{

      /** Operator equal-to (==).
        * @param dt1 The first date and time to be compared.
        * @param dt2 The second date and time to be compared.
        * @return <tt>true</tt> if <B>dt1</B> is equal to <B>dt2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator==(const DateTime& dt1, const DateTime& dt2);

      /** Operator not-equal-to (!=).
        * @param dt1 The first date and time to be compared.
        * @param dt2 The second date and time to be compared.
        * @return <tt>true</tt> if <B>dt1</B> is not equal to <B>dt2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator!=(const DateTime& dt1, const DateTime& dt2);

      /** Operator less-than (<).
        * @param dt1 The first date and time to be compared.
        * @param dt2 The second date and time to be compared.
        * @return <tt>true</tt> if <B>dt1</B> is less than <B>dt2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<(const DateTime& dt1, const DateTime& dt2);

      /** Operator less-than-or-equal (<=).
        * @param dt1 The first date and time to be compared.
        * @param dt2 The second date and time to be compared.
        * @return <tt>true</tt> if <B>dt1</B> is less than or equal <B>dt2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<=(const DateTime& dt1, const DateTime& dt2);

      /** Operator greater-than (>).
        * @param dt1 The first date and time to be compared.
        * @param dt2 The second date and time to be compared.
        * @return <tt>true</tt> if <B>dt1</B> is greater than <B>dt2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>(const DateTime& dt1, const DateTime& dt2);

      /** Operator greater-than-or-equal (>=).
        * @param dt1 The first date and time to be compared.
        * @param dt2 The second date and time to be compared.
        * @return <tt>true</tt> if <B>dt1</B> is greater than or equal <B>dt2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>=(const DateTime& dt1, const DateTime& dt2);

      /** Output operator
        * (format 'YYYY/MM/DD HH:MM:SS' or if invalid filled with '#').
        * @param os The output stream.
        * @param dt The date and time to be written to the stream. */
      friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);

    //@}

  private:

    // The following private attributes and functions are used internally.
      u_int64 dateTimeM;       // date and time, stored as
                               // number of seconds since 00:00:00 01/01/1901

    // Class members.

      BAS_EXPORT static const u_int64 rwToUnixSecsCM;

      BAS_EXPORT static const u_int64 invalidSecsCM;

    // Fills the members of the struct tm with the time represented by secs.

      bool extract(struct tm* tmbuf,
                   u_int64 secs) const;

    // Check if secs is during daylight saving time in the given time zone.

      bool checkDaylight(const u_int64 secs,
                         const RWZone& zone) const;

    // Adjust the timezone for the time represented by secs.

      void adjustTimezone(const u_int64 secs,
                          u_int64& result,
                          const RWZone& zone,
                          bool fromGMT) const;

};

//------------------------------------------------------------------------------
// Some constants.
//------------------------------------------------------------------------------

BAS_EXPORT extern const DateTime INVALID_DATETIME;

//------------------------------------------------------------------------------
// Output operator (format 'YYYY/MM/DD HH:MM:SS' or if invalid filled with '#')
//------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& os, const DateTime& dt);

//------------------------------------------------------------------------------
// Operator equal-to (==)
//------------------------------------------------------------------------------

inline bool
operator==(const DateTime& dt1, const DateTime& dt2)
{
  return (dt1.dateTimeM == dt2.dateTimeM);
}

//------------------------------------------------------------------------------
// Operator not-equal-to (!=)
//------------------------------------------------------------------------------

inline bool
operator!=(const DateTime& dt1, const DateTime& dt2)
{
  return (dt1.dateTimeM != dt2.dateTimeM);
}

//------------------------------------------------------------------------------
// Operator less-than (<)
//------------------------------------------------------------------------------

inline bool
operator<(const DateTime& dt1, const DateTime& dt2)
{
  return (dt1.dateTimeM < dt2.dateTimeM);
}

//------------------------------------------------------------------------------
// Operator less-than-or-equal (<=)
//------------------------------------------------------------------------------

inline bool
operator<=(const DateTime& dt1, const DateTime& dt2)
{
  return (dt1.dateTimeM <= dt2.dateTimeM);
}

//------------------------------------------------------------------------------
// Operator greater-than (>)
//------------------------------------------------------------------------------

inline bool
operator>(const DateTime& dt1, const DateTime& dt2)
{
  return (dt1.dateTimeM > dt2.dateTimeM);
}

//------------------------------------------------------------------------------
// Operator greater-than-or-equal (>=)
//------------------------------------------------------------------------------

inline bool
operator>=(const DateTime& dt1, const DateTime& dt2)
{
  return (dt1.dateTimeM >= dt2.dateTimeM);
}

//------------------------------------------------------------------------------
// Set the date and time of self to invalid values
//------------------------------------------------------------------------------

inline void
DateTime::clear()
{
  dateTimeM = DateTime::invalidSecsCM;
}

//------------------------------------------------------------------------------
// Returns true if this is a valid date and time, false otherwise
//------------------------------------------------------------------------------

inline bool
DateTime::isValid() const
{
  return (dateTimeM < DateTime::invalidSecsCM);
}

//------------------------------------------------------------------------------
// Returns a reference to the date portion of self
//------------------------------------------------------------------------------

inline const Date
DateTime::date() const
{
  return Date(dateTimeM);
}

//------------------------------------------------------------------------------
// Returns a reference to the time portion of self
//------------------------------------------------------------------------------

inline const Time
DateTime::time() const
{
  return Time(dateTimeM);
}

//------------------------------------------------------------------------------
// Changes date and time of self to the present time
//------------------------------------------------------------------------------

inline bool
DateTime::dateTime(const RWZone& zone)
{
  RWTime now;

  u_int64 result;

  adjustTimezone((u_int64) now.seconds(), result ,zone, true);

  return seconds(result);
}

//------------------------------------------------------------------------------
// Changes self to the given number of seconds since 1901 in GMT/UTC
//------------------------------------------------------------------------------

inline bool
DateTime::secondsGMT(const u_int64 secs, const RWZone& zone)
{
  u_int64 result;

  adjustTimezone(secs, result, zone, true);

  return seconds(result);
}

//------------------------------------------------------------------------------
// Changes self to the given number of seconds since 1970 in GMT/UTC
//------------------------------------------------------------------------------

inline bool
DateTime::secondsUnix(const u_int64 secs, const RWZone& zone)
{
  u_int64 result;

  adjustTimezone((secs + DateTime::rwToUnixSecsCM), result, zone, true);

  return seconds(result);
}

//------------------------------------------------------------------------------
// Returns the number of seconds since 1901
//------------------------------------------------------------------------------

inline u_int64
DateTime::seconds() const
{
  return dateTimeM;
}

//------------------------------------------------------------------------------
// Returns the number of seconds since 1901 in GMT/UTC
//------------------------------------------------------------------------------

inline u_int64
DateTime::secondsGMT(const RWZone& zone) const
{
  u_int64 result;

  adjustTimezone(dateTimeM, result, zone, false);

  return  result;
}

//------------------------------------------------------------------------------
// Returns the number of seconds since 1970 in GMT/UTC
//------------------------------------------------------------------------------

inline u_int64
DateTime::secondsUnix(const RWZone& zone) const
{
  u_int64 result;

  adjustTimezone(dateTimeM, result, zone, false);

  if (result > DateTime::rwToUnixSecsCM)
  {
    result -= DateTime::rwToUnixSecsCM;
  }
  else
  {
    result = 0;
  }

  return result;
}

//------------------------------------------------------------------------------
// Restore the internal representation of self from memory area
//------------------------------------------------------------------------------

inline void
DateTime::binaryRestore(char*& ptr)
{
  memcpy(&dateTimeM,ptr,sizeof(dateTimeM));
  ptr += sizeof(dateTimeM);
}

//------------------------------------------------------------------------------
// Save the internal representation of self to memory area
//------------------------------------------------------------------------------

inline void
DateTime::binarySave(char*& ptr) const
{
  memcpy(ptr,&dateTimeM,sizeof(dateTimeM));
  ptr += sizeof(dateTimeM);
}

//------------------------------------------------------------------------------
// Returns the number of bytes necessary to store self
//------------------------------------------------------------------------------

inline size_t
DateTime::binaryStoreSize() const
{
  size_t size = (sizeof(dateTimeM));
  return size;
}

//------------------------------------------------------------------------------
// Compares date portion of self as seconds since 00:00:00 01/01/1901
//------------------------------------------------------------------------------

inline int
DateTime::compareDate(const DateTime& dateTime) const
{
  u_int64   myDays = dateTimeM/BAS::Date::secsInDayCM;
  u_int64   argDays = dateTime.dateTimeM/BAS::Date::secsInDayCM;
  return (myDays == argDays ? 0 : (myDays > argDays ? 1 : -1));
}

//------------------------------------------------------------------------------
// Compares the time portion of self as seconds within the day
//------------------------------------------------------------------------------

inline int
DateTime::compareTime(const DateTime& dateTime) const
{
  u_int64   myTime = dateTimeM % BAS::Date::secsInDayCM;
  u_int64   argTime = dateTime.dateTimeM %BAS::Date::secsInDayCM;
  return (myTime == argTime ? 0 : (myTime > argTime ? 1 : -1));
}

//------------------------------------------------------------------------------
// Compares date and time of self as seconds since 00:00:00 01/01/1901
//------------------------------------------------------------------------------

inline int
DateTime::compareTo(const DateTime& dateTime) const
{
  return (dateTimeM == dateTime.dateTimeM ? 0 :
         (dateTimeM > dateTime.dateTimeM ? 1 : -1));
}

//------------------------------------------------------------------------------
// Check if the date portion of self is between dt1 and dt2, inclusive
//------------------------------------------------------------------------------

inline bool
DateTime::dateBetween(const DateTime& dt1,
                          const DateTime& dt2) const
{
  return date().between(dt1.date(), dt2.date());
}

//------------------------------------------------------------------------------
// Check if the time portion of self is between dt1 and dt2, inclusive
//------------------------------------------------------------------------------

inline bool
DateTime::timeBetween(const DateTime& dt1,
                          const DateTime& dt2) const
{
  return time().between(dt1.time(), dt2.time());
}

//------------------------------------------------------------------------------
// Check if date and time of self is between dt1 and dt2, inclusive
//------------------------------------------------------------------------------

inline bool
DateTime::between(const DateTime& dt1,
                      const DateTime& dt2) const
{
  return ((dateTimeM >= dt1.dateTimeM) && (dateTimeM <= dt2.dateTimeM));
}
}
#endif // BAS_DATETIME_HPP

