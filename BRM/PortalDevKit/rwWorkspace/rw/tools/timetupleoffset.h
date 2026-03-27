/**********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/tools/timetupleoffset.h#1 $
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

#ifndef RW_TOOLS_TIMETUPLEOFFSET_H
#define RW_TOOLS_TIMETUPLEOFFSET_H

#include <rw/defs.h>
#include <rw/tools/hash.h>
#include <rw/tools/timetuple.h>
#include <rw/zone.h>

class RWDate;
class RWDateTime;
class RWFile;
class RWvistream;
class RWvostream;

/**
 * \ingroup tools_date_and_time_group
 *
 * \brief
 * Represents a date, time and time zone offset stored as a named tuple of
 * each component.
 *
 * RWTimeTupleOffset represents a date, time and time zone offset, stored as
 * a tuple of each calendar component (e.g. year, month, day, hour, minute,
 * second, picosecond, gmtoff).
 *
 * RWTimeTupleOffset may be useful when individual calendar components will
 * be accessed/modified, but where comparisons and calculations on the
 * overall date/time aren't required. In cases where comparisons and
 * calculations are required, see RWDateTime.
 *
 * RWTimeTupleOffset represents a specific instance in time. In cases when
 * time zone information is not required, RWTimeTuple should be used.
 *
 * \sa
 * RWTimeTupleOffsetFormatter for details on formatting a RWTimeTupleOffset.
 */
class RW_TOOLS_GLOBAL RWTimeTupleOffset
{
public:
    /**
     * Default constructor. All fields of the RWTimeTupleOffset instance are
     * set to -1.
     */
    RWTimeTupleOffset();

    /**
     * Constructs each field of the RWTimeTupleOffset.
     */
    RWTimeTupleOffset(int year, int mon, int mday, int hour, int min, int sec,
                      rwint64 pico, int gmtoff);

    /**
     * Constructs an RWTimeTupleOffset based on the year, month and day of
     * the month from \a date and other fields as specified in the
     * parameters. If \a date is invalid, all of the fields in
     * RWTimeTupleOffset are set to -1.
     *
     * \note
     * If \a date has a julian day number greater than 392446299155, the
     * value of the resulting RWTimeTuple is undefined.
     */
    explicit RWTimeTupleOffset(const RWDate& date, int hour = 0, int min = 0, int sec = 0,
                               rwint64 pico = 0, int gmtoff = 0);

    /**
     * Constructs an RWTimeTupleOffset based on the date/time information in
     * \a dt, as interpreted in the time zone \a zone. If \a dt is a
     * sentinel value, all of the fields in RWTimeTupleOffset are set to -1.
     * Otherwise, this function retrieves the date and time components from
     * \a dt using
     * \ref RWDateTime::extract(struct tm *, const RWZone&) const "dt.extract()"'.
     *
     * \sa
     * RWDateTime::extract(struct tm *, const RWZone&)const for limitations
     * on the date-time values supported.
     */
    explicit RWTimeTupleOffset(const RWDateTime& dt, const RWZone& zone = RWZone::local());

    /**
     * Constructs an RWTimeTupleOffset based on the contents of \a tt and
     * the GMT offset \a gmtoff.
     */
    explicit RWTimeTupleOffset(const RWTimeTuple& tt, int gmtoff = 0);

    /**
     * Constructs an RWTimeTupleOffset based on the date/time information in
     * \a t and the GMT offset \a gmtoff.
     *
     * \note
     * If <tt>t->tm_year > INT_MAX - 1900</tt> or if
     * <tt>t->tm_mon > INT_MAX - 1</tt>, the results are undefined.
     */
    explicit RWTimeTupleOffset(const struct tm* t, rwint64 pico = 0, int gmtoff = 0);

    /**
     * Populates the <tt>struct tm</tt> \a tt based on the values in self.
     * The fields \c tm_wday, \c tm_yday and \c tm_isdst are set to -1 as
     * that information is not known in RWTimeTupleOffset. The picoseconds
     * value of the RWTimeTupleOffset is ignored.
     *
     * \note
     * If <tt>getYear() < INT_MIN + 1900</tt> or if
     * <tt>getMonth() < INT_MIN + 1</tt>, the results are undefined.
     */
    void extract(struct tm* tt) const;

    /**
     * Copy constructor.
     */
    RWTimeTupleOffset(const RWTimeTupleOffset& other);

    /**
     * Assignment operator.
     */
    RWTimeTupleOffset&
    operator=(const RWTimeTupleOffset&);

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
     * Returns the offset from GMT, in seconds.
     */
    int gmtoff() const;

    /**
     * Sets the offset from GMT, in seconds.
     */
    void gmtoff(int s);

    /**
     * \internal
     *
     * Returns the number of bytes necessary to store the object using the
     * global function:
     *
     * \code
     * RWFile& operator<<(RWFile&, const RWTimeTupleOffset&);
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
    int compareTo(const RWTimeTupleOffset& rhs) const;

private:
    RWTimeTuple tt_;
    int gmtoff_;

    friend struct RWTHash<RWTimeTupleOffset>;
};


/**
 * \relates RWTimeTupleOffset
 * Restores \a t from a virtual stream, replacing the previous contents of
 * \a t.
 */
RW_TOOLS_SYMBOLIC RWvistream&
operator>>(RWvistream& str, RWTimeTupleOffset& t);


/**
 * \relates RWTimeTupleOffset
 * Restores \a t from an RWFile, replacing the previous contents of \a t.
 */
RW_TOOLS_SYMBOLIC RWFile&
operator>>(RWFile& file, RWTimeTupleOffset& t);


/**
 * \relates RWTimeTupleOffset
 * Restores an RWTimeTupleOffset from a virtual stream by allocating an
 * RWTimeTupleOffset on the heap and restoring its state.
 */
RW_TOOLS_SYMBOLIC RWvistream&
operator>>(RWvistream& str, RWTimeTupleOffset*& t);


/**
 * \relates RWTimeTupleOffset
 * Restores an RWTimeTupleOffset from an RWFile by allocating an
 * RWTimeTupleOffset on the heap and restoring its state.
 */
RW_TOOLS_SYMBOLIC RWFile&
operator>>(RWFile& file, RWTimeTupleOffset*& t);


/**
 * \relates RWTimeTupleOffset
 * Saves \a t to a virtual stream.
 */
RW_TOOLS_SYMBOLIC RWvostream&
operator<<(RWvostream& str, const RWTimeTupleOffset& t);


/**
 * \relates RWTimeTupleOffset
 * Saves \a t to an RWFile.
 */
RW_TOOLS_SYMBOLIC RWFile&
operator<<(RWFile& file, const RWTimeTupleOffset& t);


/**
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * Function object for hashing an RWTimeTupleOffset.
 *
 * Provides a C++ Standard Library-compliant hash function object suitable
 * for use with hash or unordered containers.
 */
template <>
struct RWTHash<RWTimeTupleOffset>
    : std::unary_function<RWTimeTupleOffset, size_t> {
    /**
     * Returns a hash of \a obj. This function is the equivalent of calling
     *
     * \code
     * obj.hash();
     * \endcode
     */
    size_t operator()(const RWTimeTupleOffset& obj) const;
};


inline
RWTimeTupleOffset::RWTimeTupleOffset()
    : tt_(), gmtoff_(-1)
{
}


inline
RWTimeTupleOffset::RWTimeTupleOffset(int year, int mon, int mday, int hour,
                                     int min, int sec, rwint64 pico,
                                     int gmtoff)
    : tt_(year, mon, mday, hour, min, sec, pico), gmtoff_(gmtoff)
{
}


inline
RWTimeTupleOffset::RWTimeTupleOffset(const struct tm* t, rwint64 pico, int gmtoff)
    : tt_(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
          t->tm_sec, pico),
      gmtoff_(gmtoff)
{
}


inline
void RWTimeTupleOffset::extract(struct tm* tt) const
{
    tt->tm_sec = tt_.second();
    tt->tm_min = tt_.minute();
    tt->tm_hour = tt_.hour();
    tt->tm_mday = tt_.dayOfMonth();
    tt->tm_mon = tt_.month() - 1;
    tt->tm_year = tt_.year() - 1900;
    tt->tm_wday = -1;
    tt->tm_yday = -1;
    tt->tm_isdst = -1;
#if !defined(RW_NO_TM_ZONE)
    tt->tm_gmtoff = gmtoff_;
    tt->tm_zone = "";
#endif
}


inline
RWTimeTupleOffset::RWTimeTupleOffset(const RWTimeTupleOffset& other)
    : tt_(other.tt_), gmtoff_(other.gmtoff_)
{
}


inline RWTimeTupleOffset&
RWTimeTupleOffset::operator=(const RWTimeTupleOffset& other)
{
    if (this != &other) {
        tt_ = other.tt_;
        gmtoff_ = other.gmtoff_;
    }
    return *this;
}


inline rwint64
RWTimeTupleOffset::picosecond() const
{
    return tt_.picosecond();
}


inline void
RWTimeTupleOffset::picosecond(rwint64 p)
{
    tt_.picosecond(p);
}


inline int
RWTimeTupleOffset::second() const
{
    return tt_.second();
}


inline void
RWTimeTupleOffset::second(int s)
{
    tt_.second(s);
}


inline int
RWTimeTupleOffset::minute() const
{
    return tt_.minute();
}


inline void
RWTimeTupleOffset::minute(int m)
{
    tt_.minute(m);
}


inline int
RWTimeTupleOffset::hour() const
{
    return tt_.hour();
}


inline void
RWTimeTupleOffset::hour(int h)
{
    tt_.hour(h);
}


inline int
RWTimeTupleOffset::dayOfMonth() const
{
    return tt_.dayOfMonth();
}


inline void
RWTimeTupleOffset::dayOfMonth(int d)
{
    tt_.dayOfMonth(d);
}


inline int
RWTimeTupleOffset::month() const
{
    return tt_.month();
}


inline void
RWTimeTupleOffset::month(int m)
{
    tt_.month(m);
}


inline int
RWTimeTupleOffset::year() const
{
    return tt_.year();
}


inline void
RWTimeTupleOffset::year(int y)
{
    tt_.year(y);
}


inline int
RWTimeTupleOffset::gmtoff() const
{
    return gmtoff_;
}


inline void
RWTimeTupleOffset::gmtoff(int s)
{
    gmtoff_ = s;
}


inline size_t
RWTHash<RWTimeTupleOffset>::operator()(const RWTimeTupleOffset& obj) const
{
    RWTHash<RWTimeTuple> tt_hasher;
    RWTHash<int> int_hasher;

    return tt_hasher(obj.tt_) ^ int_hasher(obj.gmtoff_);
}

#endif /* RW_TOOLS_TIMETUPLE_H */
