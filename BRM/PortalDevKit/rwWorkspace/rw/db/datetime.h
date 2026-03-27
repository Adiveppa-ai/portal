#ifndef __RWDB_DBDATETIME_H__
#define __RWDB_DBDATETIME_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/datetime.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
 * 
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software, Inc.
 * pursuant to a written license agreement and may be used, copied, transmitted,
 * and stored only in accordance with the terms of such license agreement and
 * with the inclusion of the above copyright notice.  This computer software or
 * any other copies thereof may not be provided or otherwise made available to
 * any other person.
 * 
 * U.S. Government Restricted Rights.  This computer software: (a) was
 * developed at private expense and is in all respects the proprietary
 * information of Rogue Wave Software, Inc.; (b) was not developed with
 * government funds; (c) is a trade secret of Rogue Wave Software, Inc. for all
 * purposes of the Freedom of Information Act; and (d) is a commercial item and
 * thus, pursuant to Section 12.212 of the Federal Acquisition Regulations (FAR)
 * and DFAR Supplement Section 227.7202, Government's use, duplication or
 * disclosure of the computer software is subject to the restrictions set forth
 * by Rogue Wave Software, Inc.
 *
 **************************************************************************
 *
 * ** DEPRECATED **
 * Definition of class RWDBDateTime
 *   Provided only for backward compatibility, new code should be
 *   written using class RWDateTime from Essential Tools Module.
 *
 * This class provides interfaces to manipulate a date coupled with time,
 * as found in most databases.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/locale.h>
#include <rw/tools/datetime.h>
#include <time.h>                /* System time management. */

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

/**
 * \ingroup db_data_types_group
 * \class RWDBDateTime
 *
 * \deprecated
 * As of SourcePro 6, use RWDateTime instead. For more information, see
 * Section "RWDBDateTime" in the Chapter "The Data Model" in the <em>DB
 * Interface Module User's Guide</em> and the entry for RWDateTime in the
 * <em>Essential Tools Module Reference Guide</em>.
 *
 * \brief
 * Deprecated. Represents a date and time stored as the number of
 * milliseconds.
 *
 * RWDBDateTime represents a date and time stored as the number of
 * milliseconds since January 1 1901 00:00:00:000 UTC. The member function
 * isValid() can be used to determine whether an RWDBDateTime is a valid
 * date and time. Note that RWDBDateTime is instantiated from the local
 * system and not the database.
 *
 * RWDBDateTime instances can be converted to and from RWDate, RWDateTime,
 * and/or RWTime instances, and to and from the C Standard Library type
 * <tt>struct tm</tt> defined in \c <time.h>.
 *
 * Output formatting is done using an RWLocale object. The default locale
 * formats data according to U.S. conventions. See the <em>Essential Tools
 * Module Reference Guide</em> for further discussion of RWLocale.
 *
 * \synopsis
 * #include <rw/db/datetime.h>
 *
 * RWDBDateTime now; // construct current date and time
 * RWDBDateTime then((unsigned)1993,2,27,10,2,54)
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDate, RWTime, and RWDateTime can be used to create RWDBDateTime
 * instances. Please see your Essential Tools Module documentation for
 * information on these classes.
 *
 * RWLocale is used to format the output of RWDBDateTime. Please see your
 * Essential Tools Module documentation for information on RWLocale. Note
 * that the character \c u can be used with RWLocale to denote milliseconds.
 * \endparblock
 */
class RW_DEPRECATE_TYPE("Use RWDateTime instead") RWDB_GLOBAL RWDBDateTime
{
public:

    // constructors

    /**
     * The default constructor creates an instance holding the current date
     * and time. Note that RWDBDateTime is instantiated from the local
     * system and not the database.
     */
    RWDBDateTime();

    /**
     * Copy constructor. RWDBDateTime obeys value semantics.
     */
    RWDBDateTime(const RWDBDateTime& dt);

    /**
     * Conversion constructor. Constructs an instance of RWDBDateTime from
     * an instance of RWDateTime.
     */
    explicit RWDBDateTime(const RWDateTime& dt);

    /**
     * Constructs an RWDBDateTime from the \c tm_year, \c tm_mon,
     * \c tm_mday, \c tm_hour, \c tm_minute, and \c tm_sec components of
     * \a tm, with \c milliseconds \c = \c 0. These components are
     * understood to be relative to the time zone, \a zone, which defaults
     * to local time. Note that the numbering of months and years in a
     * \c struct \a tm differs from numbering in RWDBDateTime parameters.
     */
    RWDBDateTime(const struct tm* tm,
                 const RWZone& zone = RWZone::local());

    /**
     * Constructs an RWDBDateTime from the date and time provided by RWTime.
     * The \a zone argument is ignored.
     */
    RWDBDateTime(const RWTime& time,
                 const RWZone& zone = RWZone::local());

    /**
     * Constructs an RWDBDateTime from the given \a date and the given
     * \c time components. The time components are taken to be relative to
     * the time zone, \a zone, which defaults to local time.
     */
    RWDBDateTime(const RWDate& date,
                 unsigned hour = 0, unsigned minute = 0,
                 unsigned second = 0, unsigned millesecond = 0,
                 const RWZone& zone = RWZone::local());

    /**
     * Constructs an RWDBDateTime for the given \a date, extracting the time
     * from the string \a str. The time is understood to be relative to the
     * time zone, \a zone, which defaults to local time. The specified
     * \a locale is used for formatting information. You can use isValid()
     * to check the results.
     */
    RWDBDateTime(const RWDate& date,
                 const RWCString& str,
                 const RWZone& zone = RWZone::local(),
                 const RWLocale& locale = RWLocale::global());

    /**
     * Constructs an RWDBDateTime from the given components. The date and
     * time components are understood to be relative to the time zone,
     * \a zone, which defaults to local time.
     */
    RWDBDateTime(unsigned year, unsigned month, unsigned day,
                 unsigned hour = 0, unsigned minute = 0,
                 unsigned second = 0, unsigned millesecond = 0,
                 const RWZone& zone = RWZone::local());

    /**
     * Constructs an RWDBDateTime from the Julian Day number \a jd and the
     * given time components. The time components are understood to be
     * relative to the time zone, \a zone, which defaults to local time.
     */
    RWDBDateTime(unsigned long jd,
                 unsigned hour = 0, unsigned minute = 0,
                 unsigned second = 0, unsigned millesecond = 0,
                 const RWZone& zone = RWZone::local());

    ~RWDBDateTime();

    // public member functions

    /**
     * Returns the number of bytes necessary to store self.
     */
    inline RWspace binaryStoreSize() const
    {
        return (datetime_.binaryStoreSize());
    }

    /**
     * Sets self to the current date and time.
     */
    inline void now()
    {
        datetime_ = RWDateTime(RWDateTime::setCurrentTime);
    }

    /**
     * Returns with the \a tmbuf parameter filled out entirely. Note that
     * the encoding for months and days of the week used in
     * <tt>struct tm</tt> differs from that used in RWDBDateTime. If self is
     * invalid, all fields in \a tmbuf are set to \c 0 if RWZone does not
     * observe DST, and to \c 1 if DST is observed.
     */
    inline void extract(struct tm* tmbuf,
                        const RWZone& zone = RWZone::local()) const
    {
        // datetime_ will return true for isValid() if self is an
        // actual time or is the null sentinel. If self is null or
        // self is not valid fill in struct with -1
        if (!datetime_.isValid()) {
            tmbuf->tm_hour = tmbuf->tm_isdst = tmbuf->tm_mday = tmbuf->tm_min
                                               = tmbuf->tm_mon = tmbuf->tm_sec = tmbuf->tm_wday = tmbuf->tm_yday
                                                       = tmbuf->tm_year = -1;
            return;
        }
        datetime_.extract(tmbuf, zone);
    }

    /**
     * Returns a suitable hashing value.
     */
    inline unsigned hash() const
    {
        return datetime_.hash();
    }

    /**
     * Returns \c true if self represents a valid date and time, otherwise
     * returns \c false.
     */
    inline bool isValid() const
    {
        // RWDBDateTime::isValid will return true if self
        // represents a valid date and time
        // RWDateTime::isValid will return true if self represents
        // an actual time or is the null sentinel
        return (datetime_.isNull() ? false : datetime_.isValid());
    }

    /**
     * Returns the year part of self, adjusted to the given time \a zone.
     */
    inline unsigned year(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.year(zone);
    }

    /**
     * Returns the month number (\c 1 - \c 12) of self, adjusted to the
     * given time \a zone.
     */
    inline unsigned month(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.month(zone);
    }

    /**
     * Returns the name of self's month, formatted for the given \a locale,
     * adjusted to the given time \a zone.
     */
    inline RWCString monthName(const RWLocale& locale
                               = RWLocale::global(),
                               const RWZone& zone
                               = RWZone::local()) const
    {
        return datetime_.monthName(locale, zone);
    }

    /**
     * Returns the weekdays number (Monday = \c 1, ..., Sunday = \c 7) of
     * self, adjusted to the given time \a zone.
     */
    inline unsigned weekDay(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.weekDay(zone);
    }

    /**
     * Returns the name of self's weekdays, formatted for the given
     * \a locale, adjusted to the given time \a zone.
     */
    inline RWCString weekDayName(const RWLocale& locale
                                 = RWLocale::global(),
                                 const RWZone& zone
                                 = RWZone::local()) const
    {
        return datetime_.weekDayName(locale, zone);
    }

    /**
     * Returns the day of the year (\c 1 - \c 366) of self, adjusted to the
     * given time \a zone.
     */
    inline unsigned day(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.day(zone);
    }

    /**
     * Returns the day of the month (\c 1 - \c 31) of self, adjusted to the
     * given time \a zone.
     */
    inline unsigned dayOfMonth(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.dayOfMonth(zone);
    }

    /**
     * Returns the day of the year (\c 1 - \c 366) corresponding to the
     * first day of self's month, adjusted to the given time \a zone.
     */
    inline unsigned firstDayOfMonth(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.firstDayOfMonth(zone);
    }

    /**
     * Returns the day of the year (\c 1 - \c 366) corresponding to the
     * first day of the given month (\c 1 - \c 12) in self's year, adjusted
     * to the given time \a zone.
     */
    inline unsigned firstDayOfMonth(unsigned month,
                                    const RWZone& zone = RWZone::local()) const
    {
        return datetime_.firstDayOfMonth(month, zone);
    }

    /**
     * Returns \c true if self represents a leap year, otherwise returns
     * \c false. Result is adjusted to the given time \a zone.
     */
    inline bool leap(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.leap(zone);
    }

    /**
     * Returns an RWDBDateTime representing the previous numbered day of the
     * week, where Monday = \c 1, ..., Sunday = \c 7. The parameter
     * \a dayNum must be between \c 1 and \c 7, inclusive. Result is
     * adjusted to the given time \a zone.
     */
    inline RWDBDateTime previous(unsigned dayNum,
                                 const RWZone& zone = RWZone::local()) const
    {
        return RWDBDateTime(datetime_.previous(dayNum, zone));
    }

    /**
     * Returns an RWDBDateTime representing the previous \a dayName, for
     * example, the previous Monday. The \a dayName is interpreted according
     * to the given \a locale. Result is adjusted to the given time \a zone.
     */
    inline RWDBDateTime previous(const char* dayName,
                                 const RWLocale& locale
                                 = RWLocale::global(),
                                 const RWZone& zone
                                 = RWZone::local()) const
    {
        return RWDBDateTime(datetime_.previous(dayName, locale, zone));
    }

    /**
     * Returns the hour part of self, adjusted to the given time \a zone.
     */
    inline unsigned hour(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.hour(zone);
    }

    /**
     * Returns self's hour in UTC (GMT).
     */
    inline unsigned hourGMT() const
    {
        return datetime_.hourGMT();
    }

    /**
     * Returns \c true if self is during daylight-saving time in the
     * specified time \a zone, otherwise returns \c false.
     */
    inline bool isDST(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.isDST(zone);
    }

    /**
     * Returns the minutes part of self, adjusted to the given \a zone.
     */
    inline unsigned minute(const RWZone& zone = RWZone::local()) const
    {
        return datetime_.minute(zone);
    }

    /**
     * Returns self's minute in UTC (GMT).
     */
    inline unsigned minuteGMT() const
    {
        return datetime_.minuteGMT();
    }

    /**
     * Returns the seconds part of self.
     */
    inline unsigned second() const
    {
        return datetime_.second();
    }

    /**
     * Returns the milliseconds part of self.
     */
    inline unsigned millisecond() const
    {
        return datetime_.milliSecond();
    }

    /**
     * Returns the number of seconds since 00:00:00 January 1, 1901 UTC.
     */
    inline rwint64 seconds() const
    {
        return datetime_.milliSeconds() / 1000;
    }

    /**
     * Comparison function. Returns \c -1, \c 0, or \c 1, depending upon
     * whether self is less than, equal to, or greater than the RWDBDateTime
     * addressed by \a dt.
     */
    inline int compareTo(const RWDBDateTime* dt) const
    {
        return datetime_.compareTo(dt->datetime_);
    }

    /**
     * Comparison function. Returns \c -1, \c 0, or \c 1, depending upon
     * whether self's date part is less than, equal to, or greater than the
     * RWDate addressed by \a d.
     */
    int             compareTo(const RWDate* d) const;

    /**
     * Comparison function. Returns \c -1, \c 0, or \c 1, depending upon
     * whether self's time part is less than, equal to, or greater than the
     * RWTime addressed by \a t.
     */
    int             compareTo(const RWTime* t) const;

    // RWDB_MEMBER_MAX macro is used to workaround MSVC max macros.
    // Actual method:
    //      RWDBDateTime    max(const RWDBDateTime& dt) const
    /**
     * Returns the later of self and \a dt.
     */
    RWDBDateTime    RWDB_MEMBER_MAX(const RWDBDateTime& dt) const
    {
        return ((compareTo(&dt) < 0) ? dt : *this);
    }

    // RWDB_MEMBER_MIN macro is used to workaround MSVC min macros.
    // Actual method:
    //      RWDBDateTime    min(const RWDBDateTime& dt) const
    /**
     * Returns the earlier of self and \a dt.
     */
    RWDBDateTime    RWDB_MEMBER_MIN(const RWDBDateTime& dt) const
    {
        return ((compareTo(&dt) > 0) ? dt : *this);
    }

    /**
     * Returns \c true if self is between \a dt1 and \a dt2, inclusive.
     */
    inline bool between(const RWDBDateTime& dt1,
                        const RWDBDateTime& dt2) const
    {
        return datetime_.between(dt1.datetime_, dt2.datetime_);
    }

    /**
     * Returns \c true if
     * \ref compareTo(const RWDBDateTime *) const "compareTo(this, &dt) == 0",
     * otherwise returns \c false.
     */
    inline bool isEqual(const RWDBDateTime& dt) const
    {
        return (datetime_.compareTo(dt.datetime_) == 0);
    }

    /**
     * Adds \a num years to self's years part. The result is not necessarily
     * a valid date. For example, <tt>February 29 1992</tt> plus one year is
     * not a valid date.
     */
    RWDBDateTime    addYears(long int num);

    /**
     * Adds \a num months to self's month part. The result is not
     * necessarily a valid date. For example, <tt>January 31</tt> plus one
     * month is not a valid date.
     */
    RWDBDateTime    addMonths(long int num);

    /**
     * Adds \a num days to self. The result is not necessarily a valid date.
     * For example, <tt>April 1 2000 2:03am</tt> plus one day is not a valid
     * date.
     */
    inline RWDBDateTime    addDays(long int num)
    {
        RW_PRECONDITION(isValid());
        datetime_ = datetime_ + num * RWDateTime::millisecsInDay;
        return *this;
    }

    /**
     * Adds \a num hours to self.
     */
    inline RWDBDateTime    addHours(rwint64 num)
    {
        datetime_.incrementHour(num);
        return *this;
    }

    /**
     * Adds \a num minutes to self.
     */
    inline RWDBDateTime    addMinutes(rwint64 num)
    {
        datetime_.incrementMinute(num);
        return *this;
    }

    /**
     * Adds \a num seconds to self.
     */
    inline RWDBDateTime    addSeconds(rwint64 num)
    {
        datetime_.incrementSecond(num);
        return *this;
    }
    /**
     * Adds \a num milliseconds to self.
     */
    inline RWDBDateTime    addMilliseconds(rwint64 num)
    {
        datetime_.incrementMillisecond(num);
        return *this;
    }

    /**
     * Returns the date portion of self as an RWDate.
     */
    RWDate          rwdate() const;

    /**
     * Returns the time portion of self as an RWTime.
     */
    RWTime          rwtime() const;

    /**
     * Returns self as a \b std::string, formatted by the given \a locale,
     * with the time zone adjusted according to the given \a zone. The valid
     * values for \a format are as defined by RWLocale except for the \c 'u'
     * character which will print the milliseconds. The default format is
     * \c '\\0', which is the same as \c 'x X'. See RWLocale in the
     * <em>Essential Tools Module Reference Guide</em> for a complete
     * listing of possible formats.
     */
    RWCString       asString(char format = (char)'\0',
                             const RWZone& zone = RWZone::local(),
                             const RWLocale& locale = RWLocale::global()) const;

    /**
     * Returns self as a \b std::string, formatted by the given \a locale,
     * with the time zone adjusted according to the given \a zone. The
     * \a format string may consist of any sequence of characters containing
     * single formats as defined by RWLocale except for the \c 'u' character
     * which will print the milliseconds. The default format is the date
     * followed by the time: \c 'x X'. See RWLocale in the <em>Essential
     * Tools Module Reference Guide</em> for a complete listing of possible
     * formats.
     */
    RWCString       asString(const char* format,
                             const RWZone& zone = RWZone::local(),
                             const RWLocale& locale = RWLocale::global()) const;

    /**
     * Writes contents of self to \a file. There are two ways of reading and
     * writing the date. See the persistence() member functions or the
     * <em>DB Interface Module User's Guide</em> for details.
     */
    void            saveOn(RWFile& file) const;

    /**
     * Writes contents of self to \a vos. There are two ways of reading and
     * writing the date. See the persistence() member functions or the
     * <em>DB Interface Module User's Guide</em> for details.
     */
    void            saveOn(RWvostream& vos) const;

    /**
     * Reads \a file, replacing the contents of self. There are two ways or
     * reading and writing the date. See the persistence() member functions
     * or the <em>DB Interface Module User's Guide</em> for details.
     */
    void            restoreFrom(RWFile& file);

    /**
     * Reads \a vis, replacing contents of self. There are two ways of
     * reading and writing the date. See the persistence() member functions
     * or the <em>DB Interface Module User's Guide</em> for details.
     */
    void            restoreFrom(RWvistream& vis);

    /**
     * Member that provides compatibility with the old storage format.
     *
     * \note
     * For more information on persistence in RWDBDateTime, see Section
     * "Persistence" in the Chapter "The Data Model" in the <em>DB Interface
     * Module User's Guide</em>.
     */
    enum Persistence {

        /**
         * Persistence model of the class is set to default; dates are
         * stored in a new format that is compatible with RWDateTime.
         */
        Default,

        /**
         * Persistence model of the class is set to the legacy format
         */
        Legacy
    };

    /**
     * Sets the persistence to either #Persistence::#Default or
     * #Persistence::#Legacy. This affects the member functions saveOn() and
     * restoreFrom().
     */
    inline static void persistence(const RWDBDateTime::Persistence per)
    {
        persistence_ = per;
    }

    /**
     * Returns a copy of the current persistence mechanism in use.
     */
    inline static Persistence persistence(void)
    {
        return persistence_;
    }

    // public member operators

    /**
     * Assignment operator. RWDBDateTime obeys value semantics.
     */
    inline RWDBDateTime& operator=(const RWDBDateTime& dt)
    {
        datetime_ = dt.datetime_;
        return *this;
    }

    /**
     * Conversion operator. Used to convert an instance of RWDBDateTime to
     * an instance of RWDateTime.
     */
    operator RWDateTime() const
    {
        return datetime_;
    }

    // related global operators

    /**
     * Returns \c true if \a dt1 is before \a dt2, otherwise returns
     * \c false.
     */
    friend bool RWDB_SYMBOLIC     operator< (const RWDBDateTime& dt1,
            const RWDBDateTime& dt2);

    /**
     * Returns \c true if \a dt1 is earlier or the same as \a dt2, otherwise
     * returns \c false.
     */
    friend bool RWDB_SYMBOLIC     operator<=(const RWDBDateTime& dt1,
            const RWDBDateTime& dt2);

    /**
     * Returns \c true if \a dt1 is after \a dt2, otherwise returns
     * \c false.
     */
    friend bool RWDB_SYMBOLIC     operator> (const RWDBDateTime& dt1,
            const RWDBDateTime& dt2);

    /**
     * Returns \c true if \a dt1 is after or the same as \a dt2, otherwise
     * returns \c false.
     */
    friend bool RWDB_SYMBOLIC     operator>=(const RWDBDateTime& dt1,
            const RWDBDateTime& dt2);

    /**
     * Returns \c true if \a dt1 is the same as \a dt2, otherwise returns
     * \c false.
     */
    friend bool RWDB_SYMBOLIC     operator==(const RWDBDateTime& dt1,
            const RWDBDateTime& dt2);

    /**
     * Returns \c true if \a dt1 is not the same as \a dt2, otherwise
     * returns \c false.
     */
    friend bool RWDB_SYMBOLIC     operator!=(const RWDBDateTime& dt1,
            const RWDBDateTime& dt2);

private:
    RWCString millisecondsAsString() const;
    static Persistence persistence_;
    RWDateTime datetime_;
};

/* Global declarations for Related Global operators */

bool RWDB_SYMBOLIC     operator< (const RWDBDateTime& dt1,
                                  const RWDBDateTime& dt2);

bool RWDB_SYMBOLIC     operator<=(const RWDBDateTime& dt1,
                                  const RWDBDateTime& dt2);

bool RWDB_SYMBOLIC     operator> (const RWDBDateTime& dt1,
                                  const RWDBDateTime& dt2);

bool RWDB_SYMBOLIC     operator>=(const RWDBDateTime& dt1,
                                  const RWDBDateTime& dt2);

bool RWDB_SYMBOLIC     operator==(const RWDBDateTime& dt1,
                                  const RWDBDateTime& dt2);

bool RWDB_SYMBOLIC     operator!=(const RWDBDateTime& dt1,
                                  const RWDBDateTime& dt2);

RW_RESTORE_DEPRECATED_WARNINGS
#endif // ! RW_DISABLE_DEPRECATED

#endif
