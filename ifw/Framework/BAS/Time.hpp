#ifndef BAS_TIME_HPP
#define BAS_TIME_HPP
// @(#)%Portal Version: Time.hpp:PlatformR2Int:4:2006-Aug-14 10:46:37 %
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
//   Time class implementation.
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//------------------------------------------------------------------------------
// $Log: Time.hpp,v $
// Revision 1.15  2006/08/13  bertm
// PRSF00228028 - Added Time(u_int64) constructor for DateTime's use.
//
// Revision 1.14  2006/07/18 15:10:59  bertm
// PRSF00223955 - Get rid of "long"s in BAS and FSM modules
//
// Revision 1.13  2002/01/15 09:29:07  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.12  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.11  2001/03/12 15:31:40  bt
// Function toString(String& result, bool appendString = false) added.
//
// Revision 1.10  2000/09/26 12:13:36  bt
// Function time(String&,size_t,size_t) added.
//
// Revision 1.9  2000/06/20 15:32:29  sd
// - Constants are definded extern in header files and declared
//   int cpp file.
//
// Revision 1.8  2000/01/26 14:31:22  bt
// - check code review lines an correct all errors
// - constants INVALID_DATE, INVALID_TIME, INVALID_DATETIME added
//
// Revision 1.7  1999/11/10 09:04:33  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.6  1999/09/21 11:57:06  bt
// Constructors added.
//
// Revision 1.3  1999/06/28 15:48:32  bt
// Methods seconds() and julian() added.
//
// Revision 1.1  1999/06/11 12:42:53  bt
// Classes Date and Time added.
//
//==============================================================================


#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_DATAVALUE_H
  #include "BAS/DataValue.hpp"
#endif

namespace BAS {
/**
 *\class Time Time.h "BAS/Time.h"
 This class represents a time.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Time.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:52:01 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>
                                                                   
    <p>The time is stored as number of seconds within the day.<br><br>

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
	class Time : public DataValue
{
  D_SINGLETHREADED

  public:

    /**@name Public Constructors */
    //@{

      /// Constructs an invalid time object.
      Time();

      /** Constructs a time object with the present time.
        * @param zone The time zone. */
      Time(const RWZone& zone);

      /** Constructs a time object with the given string.
        * @param timeString String with the
        * format 'HHMMSS', 'HH:MM:SS' or 'HH:MM'. */
      Time(const String& timeString);

      /** Constructs a time object with the given values.
        * @param hour The hour should be 00-23.
        * @param minute The minute should be 00-59.
        * @param second The second should be 00-59. */
      Time(const u_int32 hour,
           const u_int32 minute,
           const u_int32 second);

      /** Constructs a time object with the given number of
        *   seconds since 00:00:00 January 1, 1901. Only
        *   the number of seconds in the day will be stored. */
      Time(u_int64 seconds);

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~Time();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Set the time of self to an invalid value.
      void clear();

      /// Returns true if this is a valid time, false otherwise.
      bool isValid() const;

      /** Changes the time of self to the present time.
        * @param zone The time zone, which defaults to local time.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid time. */
      bool time(const RWZone& zone = RWZone::local());

      /** Changes the time of self to the given string.
        * @param str String for the time extraction with the
        *            substring format 'HHMMSS', 'HH:MM:SS' or 'HH:MM'.
        * @param pos Start position of the substring which defaults to zero.
        * @param len Length of the substring which defaults to length of str.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid time. */
      bool time(const String& str,
                const size_t pos = 0,
                const size_t len = RW_NPOS);

      /** Changes the time of self to the given values.
        * @param hour The hour should be 00-23.
        * @param minute The minute should be 00-59.
        * @param second The second should be 00-59.
        * @return <tt>true</tt> change successful,<br>
        *         <tt>false</tt> invalid time. */
      bool time(const u_int32 hour,
                const u_int32 minute,
                const u_int32 second);

      /// Changes the number of seconds within the day.
      bool seconds(const u_int64 secs);

      /// Returns the number of seconds within the day.
      u_int64 seconds() const;

      /** Extract hour, minute and second of self.
        * @param hour The returned hour.
        * @param minute The returned minute.
        * @param second The returned second.
        * @return <tt>true</tt> extract successful,<br>
        *         <tt>false</tt> invalid time. */
      bool extract(u_int32& hour,
                   u_int32& minute,
                   u_int32& second) const;

      /** Returns the time as string with the format 'HHMMSS'.
        * @return The time as string or a null string in case of failure. */
      String asString() const;

      /** Returns the time as string reference with the format 'YYYYMMDD'.
        * @param result The returned time as string.
        * @param appendString If true, the time is appended to the result.
        * @return <tt>true</tt> conversion successful,<br>
        *         <tt>false</tt> invalid time. */
      bool toString(String& result, bool appendString = false) const;

      /** Compares time of self as seconds within the day.
        * @param time The time to be compared with self.
        * @return <tt>0</tt> if self is equal to <B>time</B>,<br>
        *         <tt>1</tt> if self is greater than <B>time</B>,<br>
        *         <tt>-1</tt> if self is less than <B>time</B>. */
      int compareTo(const Time& time) const;

      /** Check if time of self is between t1 and t2, inclusive.
        * @param t1 The first time to be compared with self.
        * @param t2 The second time to be compared with self.
        * @return <tt>true</tt> t1 is less than or equal to t2 and
        *                       the time is between t1 and t2,<br>
        *         <tt>false</tt> otherwise. */
      bool between(const Time& t1, const Time& t2) const;

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

      /// Returns the earliest time that can be represented by Time.
      static Time min();

      /// Returns the latest time that can be represented by Time.
      static Time max();

      /** Self test method (<em>for internal use only</em>).
        * @return <tt>True</tt> if class test was successful,<br>
                  <tt>false</tt> otherwise. */
      static bool selfTest();

    //@}

    /**@name Related Global Operators */
    //@{

      /** Operator equal-to (==).
        * @param t1 The first time to be compared.
        * @param t2 The second time to be compared.
        * @return <tt>true</tt> if <B>t1</B> is equal to <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator==(const Time& t1, const Time& t2);

      /** Operator not-equal-to (!=).
        * @param t1 The first time to be compared.
        * @param t2 The second time to be compared.
        * @return <tt>true</tt> if <B>t1</B> is not equal to <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator!=(const Time& t1, const Time& t2);

      /** Operator less-than (<).
        * @param t1 The first time to be compared.
        * @param t2 The second time to be compared.
        * @return <tt>true</tt> if <B>t1</B> is less than <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<(const Time& t1, const Time& t2);

      /** Operator less-than-or-equal (<=).
        * @param t1 The first time to be compared.
        * @param t2 The second time to be compared.
        * @return <tt>true</tt> if <B>t1</B> is less than or equal <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator<=(const Time& t1, const Time& t2);

      /** Operator greater-than (>).
        * @param t1 The first time to be compared.
        * @param t2 The second time to be compared.
        * @return <tt>true</tt> if <B>t1</B> is greater than <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>(const Time& t1, const Time& t2);

      /** Operator greater-than-or-equal (>=).
        * @param t1 The first time to be compared.
        * @param t2 The second time to be compared.
        * @return <tt>true</tt> if <B>t1</B> is greater than or equal <B>t2</B>,<br>
        *         <tt>false</tt> otherwise. */
      friend bool operator>=(const Time& t1, const Time& t2);

      /** Output operator (format 'HH:MM:SS' or invalid time '##:##:##').
        * @param os The output stream.
        * @param time The time to be written to the stream. */
      friend std::ostream& operator<<(std::ostream& os, const Time& time);

    //@}

  private:

    // The following private attributes and functions are used internally.

      friend class DateTime;

      u_int64 timeM;     // number of seconds within the day

    // Class members.

      BAS_EXPORT static const u_int64 secsInMinCM;
      BAS_EXPORT static const u_int64 minsInHourCM;
      BAS_EXPORT static const u_int64 hoursInDayCM;
      BAS_EXPORT static const u_int64 secsInHourCM;
      BAS_EXPORT static const u_int64 secsInDayCM;
      BAS_EXPORT static const u_int64 invalidSecsCM;
      BAS_EXPORT static const u_int64 minSecsCM;
      BAS_EXPORT static const u_int64 maxSecsCM;

    // Convert string to time.

      bool toTime(const String& str,
                  const size_t pos = 0,
                  const size_t len = RW_NPOS);
};

//------------------------------------------------------------------------------
// Some constants.
//------------------------------------------------------------------------------

BAS_EXPORT extern const Time INVALID_TIME;

//------------------------------------------------------------------------------
// Output operator (format 'HH:MM:SS' or invalid time '##:##:##')
//------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& os, const Time& time);

//------------------------------------------------------------------------------
// Operator equal-to (==)
//------------------------------------------------------------------------------

inline bool
operator==(const Time& t1, const Time& t2)
{
  return (t1.timeM == t2.timeM);
}

//------------------------------------------------------------------------------
// Operator not-equal-to (!=)
//------------------------------------------------------------------------------

inline bool
operator!=(const Time& t1, const Time& t2)
{
  return (t1.timeM != t2.timeM);
}

//------------------------------------------------------------------------------
// Operator less-than (<)
//------------------------------------------------------------------------------

inline bool
operator<(const Time& t1, const Time& t2)
{
  return (t1.timeM < t2.timeM);
}

//------------------------------------------------------------------------------
// Operator less-than-or-equal (<=)
//------------------------------------------------------------------------------

inline bool
operator<=(const Time& t1, const Time& t2)
{
  return (t1.timeM <= t2.timeM);
}

//------------------------------------------------------------------------------
// Operator greater-than (>)
//------------------------------------------------------------------------------

inline bool
operator>(const Time& t1, const Time& t2)
{
  return (t1.timeM > t2.timeM);
}

//------------------------------------------------------------------------------
// Operator greater-than-or-equal (>=)
//------------------------------------------------------------------------------

inline bool
operator>=(const Time& t1, const Time& t2)
{
  return (t1.timeM >= t2.timeM);
}

//------------------------------------------------------------------------------
// Set the time of self to an invalid value
//------------------------------------------------------------------------------

inline void
Time::clear()
{
  timeM = Time::invalidSecsCM;
}

//------------------------------------------------------------------------------
// Returns true if this is a valid time, false otherwise
//------------------------------------------------------------------------------

inline bool
Time::isValid() const
{
  return (timeM < Time::invalidSecsCM);
}

//------------------------------------------------------------------------------
// Changes the time of self to the given string
// (format 'HHMMSS', 'HH:MM:SS' or 'HH:MM')
//------------------------------------------------------------------------------

inline bool
Time::time(const String& str,
               const size_t pos,
               const size_t len)
{
  return toTime(str,pos,len);
}

//------------------------------------------------------------------------------
// Changes the number of seconds within the day
//------------------------------------------------------------------------------

inline bool
Time::seconds(const u_int64 secs)
{
  timeM = secs;

  return isValid();
}

//------------------------------------------------------------------------------
// Returns the number of seconds within the day
//------------------------------------------------------------------------------

inline u_int64
Time::seconds() const
{
  return timeM;
}

//------------------------------------------------------------------------------
// Compares time of self as seconds within the day
//------------------------------------------------------------------------------

inline int
Time::compareTo(const Time& time) const
{
  return (timeM == time.timeM ? 0 : (timeM > time.timeM ? 1 : -1));
}

//------------------------------------------------------------------------------
// Check if time of self is between t1 and t2, inclusive
//------------------------------------------------------------------------------

inline bool
Time::between(const Time& t1, const Time& t2) const
{
  return ((timeM >= t1.timeM) && (timeM <= t2.timeM));
}
}
#endif // TIME_HPP

