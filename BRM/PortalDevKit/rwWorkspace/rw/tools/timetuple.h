/**********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/tools/timetuple.h#1 $
 *
 * Copyright (c) 1989-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **********************************************************************/

#ifndef RW_TOOLS_TIMETUPLE_H
#define RW_TOOLS_TIMETUPLE_H

#include <rw/defs.h>
#include <rw/tools/hash.h>
#include <rw/zone.h>

class RWDate;
class RWDateTime;
class RWFile;
class RWTimeTupleOffset;
class RWvistream;
class RWvostream;


/**
 * \ingroup tools_date_and_time_group
 *
 * \brief
 * Represents a date and time stored as a named tuple of each component.
 *
 * RWTimeTuple represents a date and time, stored as a tuple of each
 * calendar component (e.g. year, month, day, hour, minute, second,
 * picosecond).
 *
 * RWTimeTuple may be useful when individual calendar components will be
 * accessed/modified, but where comparisons and calculations on the overall
 * date/time aren't required. In cases where comparisons and calculations
 * are required, see RWDateTime.
 *
 * RWTimeTuple does not capture an offset from GMT, and instead represents a
 * date/time in local time (similar to <tt>struct tm</tt>). In cases where a
 * specific instance in time should be represented, RWTimeTupleOffset should
 * be used.
 *
 * \sa
 * RWTimeTupleFormatter for details on formatting a RWTimeTuple.
 */
class RW_TOOLS_GLOBAL RWTimeTuple
{
public:
    /**
     * Default constructor. All fields of the RWTimeTuple instance are set
     * to -1.
     */
    RWTimeTuple();

    /**
     * Constructs each field of the RWTimeTuple.
     */
    RWTimeTuple(int year, int mon, int mday, int hour, int min, int sec,
                rwint64 pico);

    /**
     * Constructs an RWTimeTuple based on the year, month and day of the
     * month from \a date and other fields as specified in the parameters.
     * If \a date is invalid, all of the fields in RWTimeTuple are set to
     * -1.
     *
     * \note
     * If \a date has a julian day number greater than 392446299155, the
     * value of the resulting RWTimeTuple is undefined.
     */
    explicit RWTimeTuple(const RWDate& date, int hour = 0, int min = 0,
                         int sec = 0, rwint64 pico = 0);

    /**
     * Constructs an RWTimeTuple based on the date/time information in
     * \a dt, as interpreted in the time zone \a zone. If \a dt is a
     * sentinel value, all of the fields in RWTimeTuple are set to -1.
     * Otherwise, this function retrieves the date and time components from
     * \a dt using
     * \ref RWDateTime::extract(struct tm *, const RWZone&) const "dt.extract()"'.
     *
     * \sa
     * RWDateTime::extract(struct tm *, const RWZone&)const for limitations
     * on the date-time values supported.
     */
    explicit RWTimeTuple(const RWDateTime& dt, const RWZone& zone = RWZone::local());

    /**
     * Constructs an RWTimeTuple based on the contents of \a tt. The GMT
     * offset of \a tt is ignored.
     */
    explicit RWTimeTuple(const RWTimeTupleOffset& tt);

    /**
     * Constructs an RWTimeTuple based on the date/time information in \a t.
     *
     * \note
     * If <tt>t->tm_year > INT_MAX - 1900</tt> or if
     * <tt>t->tm_mon > INT_MAX - 1</tt>, the results are undefined.
     */
    explicit RWTimeTuple(const struct tm* t, rwint64 pico = 0);

    /**
     * Populates the <tt>struct tm</tt> \a tt based on the values in self.
     * The fields \c tm_wday, \c tm_yday and \c tm_isdst are set to -1 as
     * that information is not known in RWTimeTuple. The picoseconds value
     * of the RWTimeTuple is ignored.
     *
     * \note
     * If <tt>getYear() < INT_MIN + 1900</tt> or if
     * <tt>getMonth() < INT_MIN + 1</tt>, the results are undefined.
     */
    void extract(struct tm* tt) const;

    /**
     * Copy constructor.
     */
    RWTimeTuple(const RWTimeTuple& other);

    /**
     * Assignment operator.
     */
    RWTimeTuple&
    operator=(const RWTimeTuple& other);

    /**
     * Returns the number of picoseconds.
     */
    rwint64 picosecond() const;

    /**
     * Sets the number of picoseconds to \a p.
     */
    void picosecond(rwint64 p);

    /**
     * Returns the number of seconds.
     */
    int second() const;

    /**
     * Sets the number of seconds to \a s.
     */
    void second(int s);

    /**
     * Returns the number of minutes.
     */
    int minute() const;

    /**
     * Sets the number of minutes to \a m.
     */
    void minute(int m);

    /**
     * Returns the number of hours.
     */
    int hour() const;

    /**
     * Sets the number of hours to \a h.
     */
    void hour(int h);

    /**
     * Returns the day of the month.
     */
    int dayOfMonth() const;

    /**
     * Sets the day of the month to \a d.
     */
    void dayOfMonth(int d);

    /**
     * Returns the month index (0 == January).
     */
    int month() const;

    /**
     * Sets the month index to \a m (0 == January).
     */
    void month(int m);

    /**
     * Returns the year.
     */
    int year() const;

    /**
     * Sets the year to \a y.
     */
    void year(int y);

    /**
     * \internal
     *
     * Returns the number of bytes necessary to store the object using the
     * global function:
     *
     * \code
     * RWFile& operator<<(RWFile&, const RWTimeTuple&);
     * \endcode
     */
    RWspace
    binaryStoreSize() const;

    /**
     * \internal
     *
     * Replaces existing values in self with values read from \a istrm.
     */
    void restoreFrom(RWvistream& istrm);

    /**
     * \internal
     *
     * Replaces existing values in self with values read from \a file.
     */
    void restoreFrom(RWFile& file);

    /**
     * \internal
     *
     * Writes the values in self to \a ostrm.
     */
    void saveOn(RWvostream& ostrm) const;

    /**
     * \internal
     *
     * Writes the values in self to \a file.
     */
    void saveOn(RWFile& file) const;

    /**
     * \internal
     *
     * Returns &lt;0, 0, or &gt;0 depending on whether \a rhs is greater
     * than, equal to, or less than self.
     *
     * \note
     * This function compares each component of the RWTimeTuple in order
     * (year, month, day of month, hour, minute, second, picosecond) until a
     * difference is detected. If no difference is detected, 0 is returned.
     * Two dates that contain different representations of the same instance
     * in time may not compare equal. For a true comparison of instances of
     * time, see RWDateTime.
     */
    int compareTo(const RWTimeTuple& rhs) const;

private:
    int year_;
    int mon_;
    int mday_;
    int hour_;
    int min_;
    int sec_;
    rwint64 pico_;

    friend struct RWTHash<RWTimeTuple>;
};


/**
 * \relates RWTimeTuple
 * Restores \a t from a virtual stream, replacing the previous contents of
 * \a t.
 */
RW_TOOLS_SYMBOLIC RWvistream&
operator>>(RWvistream& str, RWTimeTuple& t);

/**
 * \relates RWTimeTuple
 * Restores \a t from an RWFile, replacing the previous contents of \a t.
 */
RW_TOOLS_SYMBOLIC RWFile&
operator>>(RWFile& file, RWTimeTuple& t);


/**
 * \relates RWTimeTuple
 * Restores an RWTimeTuple from a virtual stream by allocating an RWDateTime
 * on the heap and restoring its state.
 */
RW_TOOLS_SYMBOLIC RWvistream&
operator>>(RWvistream& str, RWTimeTuple*& t);

/**
 * \relates RWTimeTuple
 * Restores an RWTimeTuple from an RWFile by allocating an RWTimeTuple on
 * the heap and restoring its state.
 */
RW_TOOLS_SYMBOLIC RWFile&
operator>>(RWFile& file, RWTimeTuple*& t);

/**
 * \relates RWTimeTuple
 * Saves \a t to a virtual stream.
 */
RW_TOOLS_SYMBOLIC RWvostream&
operator<<(RWvostream& str, const RWTimeTuple& t);


/**
 * \relates RWTimeTuple
 * Saves \a t to an RWFile.
 */
RW_TOOLS_SYMBOLIC RWFile&
operator<<(RWFile& file, const RWTimeTuple& t);


/**
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * Function object for hashing an RWTimeTuple.
 *
 * Provides a C++ Standard Library-compliant hash function object suitable
 * for use with hash or unordered containers.
 */
template <>
struct RWTHash<RWTimeTuple>
    : std::unary_function<RWTimeTuple, size_t> {
    /**
     * Returns a hash of \a obj. This function is the equivalent of calling
     *
     * \code
     * obj.hash();
     * \endcode
     */
    size_t operator()(const RWTimeTuple& obj) const;
};


inline
RWTimeTuple::RWTimeTuple()
    : year_(-1), mon_(-1), mday_(-1), hour_(-1), min_(-1), sec_(-1), pico_(-1)
{
}


inline
RWTimeTuple::RWTimeTuple(int year, int mon, int mday, int hour, int min,
                         int sec, rwint64 pico)
    : year_(year), mon_(mon), mday_(mday), hour_(hour), min_(min), sec_(sec),
      pico_(pico)

{
}


inline
RWTimeTuple::RWTimeTuple(const struct tm* t, rwint64 pico)
    : year_(t->tm_year + 1900), mon_(t->tm_mon + 1), mday_(t->tm_mday),
      hour_(t->tm_hour), min_(t->tm_min), sec_(t->tm_sec), pico_(pico)
{
}


inline
void RWTimeTuple::extract(struct tm* tt) const
{
    tt->tm_sec = sec_;
    tt->tm_min = min_;
    tt->tm_hour = hour_;
    tt->tm_mday = mday_;
    tt->tm_mon = mon_ - 1;
    tt->tm_year = year_ - 1900;
    tt->tm_wday = -1;
    tt->tm_yday = -1;
    tt->tm_isdst = -1;
#if !defined(RW_NO_TM_ZONE)
    tt->tm_gmtoff = 0;
    tt->tm_zone = "";
#endif
}


inline
RWTimeTuple::RWTimeTuple(const RWTimeTuple& other)
    : year_(other.year_), mon_(other.mon_), mday_(other.mday_),
      hour_(other.hour_), min_(other.min_), sec_(other.sec_),
      pico_(other.pico_)
{
}


inline RWTimeTuple&
RWTimeTuple::operator=(const RWTimeTuple& other)
{
    if (this != &other) {
        year_ = other.year_;
        mon_ = other.mon_;
        mday_ = other.mday_;
        hour_ = other.hour_;
        min_ = other.min_;
        sec_ = other.sec_;
        pico_ = other.pico_;
    }
    return *this;
}


inline rwint64
RWTimeTuple::picosecond() const
{
    return pico_;
}


inline void
RWTimeTuple::picosecond(rwint64 p)
{
    pico_ = p;
}


inline int
RWTimeTuple::second() const
{
    return sec_;
}


inline void
RWTimeTuple::second(int s)
{
    sec_ = s;
}


inline int
RWTimeTuple::minute() const
{
    return min_;
}


inline void
RWTimeTuple::minute(int m)
{
    min_ = m;
}


inline int
RWTimeTuple::hour() const
{
    return hour_;
}


inline void
RWTimeTuple::hour(int h)
{
    hour_ = h;
}


inline int
RWTimeTuple::dayOfMonth() const
{
    return mday_;
}


inline void
RWTimeTuple::dayOfMonth(int d)
{
    mday_ = d;
}


inline int
RWTimeTuple::month() const
{
    return mon_;
}


inline void
RWTimeTuple::month(int m)
{
    mon_ = m;
}


inline int
RWTimeTuple::year() const
{
    return year_;
}


inline void
RWTimeTuple::year(int y)
{
    year_ = y;
}


inline size_t
RWTHash<RWTimeTuple>::operator()(const RWTimeTuple& obj) const
{
    RWTHash<rwint64> int64_hasher;
    RWTHash<int> int_hasher;

    return (int_hasher(obj.year_) ^ int_hasher(obj.mon_) ^
            int_hasher(obj.mday_) ^ int_hasher(obj.hour_) ^
            int_hasher(obj.min_) ^ int_hasher(obj.sec_) ^
            int64_hasher(obj.pico_));
}

#endif /* RW_TOOLS_TIMETUPLE_H */
