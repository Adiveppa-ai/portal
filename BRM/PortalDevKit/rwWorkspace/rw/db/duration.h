#ifndef __RWDB_DURATION_H__
#define __RWDB_DURATION_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/duration.h#1 $
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
 * Definition of class RWDBDuration
 *
 * This class provides interfaces to manipulate a duration of time,
 * i.e. one week, three hours, five years, etc.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/cstring.h>
#include <rw/tools/hash.h>

/**
 * \ingroup db_data_types_group
 *
 * \brief
 * Represents a time span in number of seconds.
 *
 * RWDBDuration represents a time span, stored in a \c double as number of
 * seconds.
 *
 * RWDBDuration supports arithmetic operations involving the imprecise
 * quantities months and years. As a reminder, the terms \b RWMonth and
 * \b RWYear are used in some member function names. The following
 * conversions are used:
 *
 * \code
 * static const double DUR_MILLISECONDS_PER_SEC = ((double)1000.0);
 * static const double DUR_SECONDS_PER_MIN      = ((double)60.0);
 * static const double DUR_SECONDS_PER_HR       = ((double)3600.0);     // DUR_SECONDS_PER_MIN * 60.0
 * static const double DUR_SECONDS_PER_DAY      = ((double)86400.0);    // DUR_SECONDS_PER_HR * 24.0
 * static const double DUR_SECONDS_PER_WEEK     = ((double)604800.0);   // DUR_SECONDS_PER_DAY * 7.0
 * static const double DUR_SECONDS_PER_RWMTH    = ((double)2419200.0);  // DUR_SECONDS_PER_WEEK * 4.0
 * static const double DUR_SECONDS_PER_RWYR     = ((double)29030400.0); // DUR_SECONDS_PER_RWMTH * 12.0
 * \endcode
 *
 * For example, adding one \b RWMonth to an RWDBDuration adds four weeks'
 * worth of seconds to the duration, regardless of the number of weeks in
 * any particular month.
 *
 * \synopsis
 * #include <rw/db/duration.h>
 *
 * RWDBDuration d;      // construct zero length duration
 * RWDBDuration d(2,4); // construct duration of 2 years
 *                      // and 4 months
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBDuration
{
public:

    // This enumeration used to be part of the public API.  It is no longer
    // documented as such but is left for backward compatibility purposes
    // for any user code that is dependent on it.
    enum DurationType {
        milliseconds,
        seconds,
        minutes,
        hours,
        days,
        weeks,
        months,
        years
    };

    // constructors

    /**
     * Default constructor. Constructs an RWDBDuration of zero length.
     */
    RWDBDuration();

    /**
     * Constructs an RWDBDuration that is the sum of the supplied parts,
     * according to the conversions listed above.
     */
    RWDBDuration(int yr, int mth = 0, int day = 0, int hr = 0,
                 int min = 0, int sec = 0, int msec = 0);

    /**
     * Constructs an RWDBDuration that takes a time span stored in a double
     * as a number of seconds.
     */
    RWDBDuration(double seconds);

    /**
     * Copy constructor. RWDBDuration obeys value semantics.
     */
    RWDBDuration(const RWDBDuration& d);

    // public member functions

    /**
     * Returns self converted to years.
     */
    double          asRWYears() const;

    /**
     * Returns self converted to months.
     */
    double          asRWMonths() const;


    /**
     * Returns self converted to weeks.
     */
    double          asWeeks() const;

    /**
     * Returns self converted to days.
     */
    double          asDays() const;

    /**
     * Returns self converted to hours.
     */
    double          asHours() const;

    /**
     * Returns self converted to minutes.
     */
    double          asMinutes() const;

    /**
     * Returns self converted to seconds.
     */
    double          asSeconds() const;

    /**
     * Returns self converted to milliseconds.
     */
    double          asMilliseconds() const;

    /**
     * Adds the given number of \a years to self.
     */
    void            addRWYears(int years);

    /**
     * Adds the given number of \a months to self.
     */
    void            addRWMonths(int months);

    /**
     * Adds the given number of \a weeks to self.
     */
    void            addWeeks(int weeks);

    /**
     * Adds the given number of \a days to self.
     */
    void            addDays(int days);

    /**
     * Adds the given number of \a hours to self.
     */
    void            addHours(int hours);

    /**
     * Adds the given number of \a minutes to self.
     */
    void            addMinutes(int minutes);

    /**
     * Adds the given number of \a seconds to self.
     */
    void            addSeconds(int seconds);

    /**
     * Adds the given number of \a milliseconds to self.
     */
    void            addMilliseconds(int milliseconds);

    /**
     * Returns a string of the format <tt># interval</tt>, where the
     * interval is determined by the modularity of the duration, that is,
     * days, seconds, etc. Applications should interpret the actual contents
     * of the interval, and format a string appropriately.
     */
    RWCString       asString() const;

    // RWCollectable support

    /**
     * Returns the number of bytes required to store self.
     */
    RWspace         binaryStoreSize() const;

    /**
     * Returns \c -1, \c 0, or \c 1 depending upon whether self is less
     * than, equal to, or greater than the RWDBDuration addressed by \a d.
     *
     * As a precondition, \a d is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    int             compareTo(const RWDBDuration* d) const;

    /**
     * Returns \c true if \ref compareTo() "compareTo(this, d)"
     * <tt>== 0</tt>, otherwise returns \c false.
     */
    bool       isEqual(const RWDBDuration* d) const;

    /**
     * Returns a value suitable for hashing.
     */
    unsigned        hash() const;

    /**
     * Writes the contents of self to \a file.
     */
    void            saveOn(RWFile& file) const;

    /**
     * Writes the contents of self to \a vos.
     */
    void            saveOn(RWvostream& vos) const;

    /**
     * Reads \a file, replacing contents of self.
     */
    void            restoreFrom(RWFile& file);

    /**
     * Reads \a vis, replacing contents of self.
     */
    void            restoreFrom(RWvistream& vis);

    // public member operators

    /**
     * Unary minus. Returns the negation of self.
     */
    RWDBDuration    operator-() const;

    /**
     * Assignment operator. RWDBDuration obeys value semantics.
     */
    RWDBDuration&   operator=(const RWDBDuration& dur);

    /**
     * Adds \a duration to self and returns the result.
     */
    RWDBDuration&   operator+=(const RWDBDuration& duration);

    /**
     * Subtracts \a duration from self and returns the result.
     */
    RWDBDuration&   operator-=(const RWDBDuration& duration);

    /**
     * Adds \a seconds to self and returns the result.
     */
    RWDBDuration&   operator+=(double seconds);

    /**
     * Subtracts \a seconds from self and returns the result.
     */
    RWDBDuration&   operator-=(double seconds);

    /**
     * Multiplies self by \a factor and returns the result.
     */
    RWDBDuration&   operator*=(double factor);

    /**
     * Divides self by \a divisor and returns the result.
     */
    RWDBDuration&   operator/=(double divisor);

    // related operators

    /**
     * Returns \c true if \a a and \a b are exactly equal, otherwise returns
     * \c false.
     */
    friend  bool RWDB_SYMBOLIC     operator==(const RWDBDuration& a,
            const RWDBDuration& b);
    /**
     * Returns \c true if \a a and \a b are not exactly equal, otherwise
     * returns \c false.
     */
    friend  bool RWDB_SYMBOLIC     operator!=(const RWDBDuration& a,
            const RWDBDuration& b);
    /**
     * Returns \c true if \a a is greater than \a b, otherwise returns
     * \c false.
     */
    friend  bool RWDB_SYMBOLIC     operator>(const RWDBDuration& a,
            const RWDBDuration& b);

    /**
     * Returns \c true if \a a is greater than or equal to \a b, otherwise
     * returns \c false.
     */
    friend  bool RWDB_SYMBOLIC     operator>=(const RWDBDuration& a,
            const RWDBDuration& b);

    /**
     * Returns \c true if \a a is less than \a b, otherwise returns
     * \c false.
     */
    friend  bool RWDB_SYMBOLIC     operator<(const RWDBDuration& a,
            const RWDBDuration& b);

    /**
     * Returns \c true if \a a is less than or equal to \a b, otherwise
     * returns \c false.
     */
    friend  bool RWDB_SYMBOLIC     operator<=(const RWDBDuration& a,
            const RWDBDuration& b);

    /**
     * Returns the result of adding \a a and \a b.
     */
    friend  RWDBDuration RWDB_SYMBOLIC  operator+(RWDBDuration& a,
            const RWDBDuration& b);

    /**
     * Returns the result of subtracting \a b from \a a.
     */
    friend  RWDBDuration RWDB_SYMBOLIC  operator-(RWDBDuration& a,
            const RWDBDuration& b);

    /**
     * Adds \a seconds to \a duration and returns the result.
     */
    friend  RWDBDuration RWDB_SYMBOLIC  operator+(RWDBDuration& duration, double seconds);

    /**
     * Subtracts \a seconds from \a duration and returns the result.
     */
    friend  RWDBDuration RWDB_SYMBOLIC  operator-(RWDBDuration& duration, double seconds);

    /**
     * Returns the result of multiplying \a duration by \a factor.
     */
    friend  RWDBDuration RWDB_SYMBOLIC  operator*(RWDBDuration& duration, double factor);

    /**
     * Returns the result of dividing \a duration by \a divisor.
     */
    friend  RWDBDuration RWDB_SYMBOLIC  operator/(RWDBDuration& duration, double divisor);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 12.5, use
     * \ref RWDateTime::operator-(const RWDateTime&, const RWDateTime&) "operator-(const RWDateTime&, const RWDateTime&)"
     * instead. This function can be replaced by code similar to
     * <tt>RWDBDuration((\<RWDateTime_instance1\> - \<RWDateTime_instance2\>)/1000.0);</tt>.
     *
     * Returns the duration between RWDBDateTime objects \a a and \a b.
     */
    RW_DEPRECATE_FUNC("Use operator-(const RWDateTime&, const RWDateTime&) instead")
    friend  RWDBDuration RWDB_SYMBOLIC  operator-(const RWDBDateTime& a,
            const RWDBDateTime& b);
#endif

    // static constants for calculations

    /**
     * Static constant \c double with value \c 1000.0, used in arithmetic
     * operations involving the imprecise quantities months and years.
     */
    static const double DUR_MILLISECONDS_PER_SEC;

    /**
     * Static constant \c double with value \c 60.0, used in arithmetic
     * operations involving the imprecise quantities months and years.
     */
    static const double DUR_SECONDS_PER_MIN;

    /**
     * Static constant \c double with value \c 3600.0, used in arithmetic
     * operations involving the imprecise quantities months and years.
     */
    static const double DUR_SECONDS_PER_HR;

    /**
     * Static constant \c double with value \c 86400.0, used in arithmetic
     * operations involving the imprecise quantities months and years.
     */
    static const double DUR_SECONDS_PER_DAY;

    /**
     * Static constant \c double with value \c 604800.0, used in arithmetic
     * operations involving the imprecise quantities months and years.
     */
    static const double DUR_SECONDS_PER_WEEK;

    /**
     * Static constant \c double with value \c 2419200.0, used in arithmetic
     * operations involving the imprecise quantities months and years.
     */
    static const double DUR_SECONDS_PER_RWMTH;

    /**
     * Static constant \c double with value \c 29030400.0, used in
     * arithmetic operations involving the imprecise quantities months and
     * years.
     */
    static const double DUR_SECONDS_PER_RWYR;
private:
    double                       seconds_;   // duration represented in seconds
};

/* Global declarations for Related Global operators  */

bool RWDB_SYMBOLIC     operator==(const RWDBDuration& a,
                                  const RWDBDuration& b);
bool RWDB_SYMBOLIC     operator!=(const RWDBDuration& a,
                                  const RWDBDuration& b);
bool RWDB_SYMBOLIC     operator>(const RWDBDuration& a,
                                 const RWDBDuration& b);
bool RWDB_SYMBOLIC     operator>=(const RWDBDuration& a,
                                  const RWDBDuration& b);
bool RWDB_SYMBOLIC     operator<(const RWDBDuration& a,
                                 const RWDBDuration& b);
bool RWDB_SYMBOLIC     operator<=(const RWDBDuration& a,
                                  const RWDBDuration& b);
RWDBDuration RWDB_SYMBOLIC  operator+(RWDBDuration& a,
                                      const RWDBDuration& b);
RWDBDuration RWDB_SYMBOLIC  operator-(RWDBDuration& a,
                                      const RWDBDuration& b);
RWDBDuration RWDB_SYMBOLIC  operator+(RWDBDuration& dur, double seconds);
RWDBDuration RWDB_SYMBOLIC  operator-(RWDBDuration& dur, double seconds);
RWDBDuration RWDB_SYMBOLIC  operator*(RWDBDuration& dur, double factor);
RWDBDuration RWDB_SYMBOLIC  operator/(RWDBDuration& dur, double divisor);

#if !defined(RW_DISABLE_DEPRECATED)
RWDBDuration RWDB_SYMBOLIC  operator-(const RWDBDateTime& a,
                                      const RWDBDateTime& b);
#endif

/**
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * Function object for hashing an RWDBDuration.
 *
 * Provides a C++ Standard Library-compliant hash function object suitable
 * for use with hash or unordered containers.
 */
template <>
struct RWTHash<RWDBDuration> : std::unary_function<RWDBDuration, size_t> {
    /**
     * Returns a hash of \a obj. This function is the equivalent of calling
     *
     * \code
     * obj.hash();
     * \endcode
     */
    size_t operator()(const RWDBDuration& obj) const
    {
        return obj.hash();
    }
};

#endif
