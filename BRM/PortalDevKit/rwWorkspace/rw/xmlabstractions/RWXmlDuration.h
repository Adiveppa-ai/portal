#ifndef rw_xmlabstractions_RWXmlDuration_h_
#define rw_xmlabstractions_RWXmlDuration_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlDuration.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 ********************************************************************/

#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>

/****************************************************************************
 *
 * Class RWXmlDuration represents an XML Schema duration simple type.
 * A duration instance has the form PnYnMnDTnHnMnS where the n's are
 * numbers and the letters represent year, month, day, hour, minute, and
 * second.

 * This class provides constructors and convenient methods to create a duration
 * instance and to access its different parts. An instance of this class can be
 * created or constructed either from a valid string or by providing values for
 * each of the parts of a duration. In addition, this class provides operators
 * and methods to add a duration to a RWDateTime instance and to determine
 * ordering relationship between 2 durations.
 *
 ****************************************************************************/

class RW_XMLABSTRACTIONS_GLOBAL RWXmlDuration
{

public:

    /**
     * Constructor. Constructs an based on the values given. Serves as a
     * default ctor as well.
     */
    RWXmlDuration(unsigned long years = 0,
                  unsigned long months = 0,
                  unsigned long days = 0,
                  unsigned long hours = 0,
                  unsigned long minutes = 0,
                  double seconds = 0.0);

    /**
     * Create an instance with a duration string. Calls extract() to extract
     * the contents.
     */
    RWXmlDuration(const RWCString& duration);

    /* Copy constructor */
    RWXmlDuration(const RWXmlDuration& other);

    /* Destructor */
    virtual ~RWXmlDuration();

    /**
     * Equality based on value semantics. Returns true if compareTo(rhs)
     * returns 0.
     */
    virtual bool              isEqual(const RWXmlDuration& rhs);

    /**
     * Returns -1, 0 or 1 depending on whether lhs is less than or equal to
     * or greater than rhs.
     *
     * The comparison is based on value semantics. The duration is converted
     * into a single unit to determine equality. Uses fixed mapping schemes
     * to do the conversion. As per the fixed mapping scheme:
     *
     * \code{.unparsed}
     * 1Y == 12M == 365D
     * 1M == 365/12 days
     * 1D == 24H
     * 1H == 60M
     * 1M == 60Seconds
     * \endcode
     */
    virtual int               compareTo(const RWXmlDuration& rhs);

    /**
     * Extracts duration into self. The given string should be in a format
     * as defined by XML Schema specification for "duration" data type. Self
     * will be set to invalid if the given string is not in the expected
     * format.
     */
    virtual void              extract(const RWCString& duration);

    /**
     * Returns string representation of self. This will be formatted as per
     * XML Schema Specification for "duration" type.
     */
    virtual RWCString         asString() const;

    /**
     * Parsing an invalid timeDuration string will lead to an invalid
     * RWXmlDuration instance. The values for years, months etc are
     * undefined for an invalid instance.
     */
    inline bool               isValid() const;

    /**
     * Returns true if self is a negative duration
     */
    inline bool               isNegative() const;

    /**
     * Changes the number of years represented by self
     */
    inline void               setYears(unsigned long years);

    /**
     * Returns the number of years represented by self
     */
    inline unsigned long      getYears() const;

    /**
     * Changes the number of years represented by self
     */
    inline void               setMonths(unsigned long yemonthsars);

    /**
     * Returns the number of months represented by self
     */
    inline unsigned long      getMonths() const;

    /**
     * Changes the number of days represented by self
     */
    inline void               setDays(unsigned long days);

    /**
     * Returns the number of days represented by self
     */
    inline unsigned long      getDays() const;

    /**
     * Changes the number of hours represented by self
     */
    inline void               setHours(unsigned long hours);

    /**
     * Returns the number of hours represented by self
     */
    inline unsigned long      getHours() const;

    /**
     * Changes the number of minutes represented by self
     */
    inline void               setMinutes(unsigned long minutes);

    /**
     * Returns the number of minutes represented by self
     */
    inline unsigned long      getMinutes() const;

    /**
     * Changes the number of seconds represented by self
     */
    inline void               setSeconds(double seconds);

    /**
     * Returns the number of seconds represented by self
     */
    inline double             getSeconds() const;

    /**
     * This method implements addition as defined by Appendix E of XML
     * Schema Specification : Part 2 Datatypes. Note that as per this
     * algorithm, the order of addition is significant. For example, there
     * could be cases, where:
     *
     * \code
     * ((aDateTime + aDuration1) + aDuration2) != ((aDateTime + aDuration2) + aDuration1));
     * \endcode
     */
    RWDateTime                operator+(const RWDateTime& aDateTime) const;

    /* Assignment operator*/
    RWXmlDuration&            operator=(const RWXmlDuration& rhs);

    /**
     * Unary negation of self. Changes self to a negative duration if self
     * is positive. Self is changed to a positive duration if self is
     * already a negative duration
     */
    inline RWXmlDuration&     operator-();

protected :

    unsigned long             maxDaysInMonth(long yearValue, long monthValue) const;

private: //methods

    enum ParseState { Begin = 0, Years, Months, Days, Hours, Minutes, Seconds };

    void                      verifyAndAssign(ParseState previous, ParseState current,
            bool pExists, bool timeSeparatorExists,
            char* data);
    //Clears all values of self
    void                      clear();


private: //data members

    //Members.
    unsigned long   years_;
    unsigned long   months_;
    unsigned long   days_;
    unsigned long   hours_;
    unsigned long   minutes_;
    double          seconds_;

    bool            isValid_;

    bool            negativeDuration_;

    //Static constants
    static const double   DaysInMonth ;
    static const unsigned DaysInYear ;

    static const unsigned SecondsInMinute;
    static const unsigned SecondsInHour;
    static const unsigned SecondsInDay ;


}; // end of class RWXmlDuration


/**
 * Equality is based on identity. That is the asString() of both the
 * durations should match. Same number of years, months etc..
 */
RW_XMLABSTRACTIONS_GLOBAL bool
operator==(const RWXmlDuration& lhs,
           const RWXmlDuration& rhs);
RW_XMLABSTRACTIONS_GLOBAL bool
operator!=(const RWXmlDuration& lhs,
           const RWXmlDuration& rhs);
/**
 * The order relation on duration is partial order since there is no
 * determinate relationship between certain durations such as one month and
 * 30days.
 *
 * This method is implemented based on the ordering algorithm defined in
 * Section 3.2.6.2 of XML Schema part 2:Datatypes. This algorithm determines
 * ordering by adding (as per operator+(const RWDateTime)) 4 specific time
 * instants to the each of these durations and comparing the result.
 *
 * As the ordering is partial some comparisons will be indeterminate. For
 * example comparing P1M and P30D will return false for both P1M < P30D and
 * P30D < P1M. Check the schema specification for all indeterminate margin
 * values.
 */
RW_XMLABSTRACTIONS_GLOBAL bool
operator<(const RWXmlDuration& lhs,
          const RWXmlDuration& rhs);

inline bool operator>(const RWXmlDuration& lhs, const RWXmlDuration& rhs)
{
    return rhs < lhs;
}

inline bool operator>=(const RWXmlDuration& lhs, const RWXmlDuration& rhs)
{
    return !(lhs < rhs);
}

inline bool operator<=(const RWXmlDuration& lhs, const RWXmlDuration& rhs)
{
    return !(lhs > rhs);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// Inline implementations
//
////////////////////////////////////////////////////////////////////////////////////////////
inline bool
RWXmlDuration::isValid() const
{
    return isValid_;
}

inline bool
RWXmlDuration::isNegative() const
{
    return negativeDuration_;
}

inline void
RWXmlDuration::setYears(unsigned long years)
{
    years_ = years;
}

inline unsigned long
RWXmlDuration::getYears() const
{
    return years_;
}

inline void
RWXmlDuration::setMonths(unsigned long months)
{
    months_ = months;
}

inline unsigned long
RWXmlDuration::getMonths() const
{
    return months_;
}

inline void
RWXmlDuration::setDays(unsigned long days)
{
    days_ = days;
}

inline unsigned long
RWXmlDuration::getDays() const
{
    return days_;
}


inline void
RWXmlDuration::setHours(unsigned long hours)
{
    hours_ = hours;
}

inline unsigned long
RWXmlDuration::getHours() const
{
    return hours_;
}


inline void
RWXmlDuration::setMinutes(unsigned long minutes)
{
    minutes_ = minutes;
}

inline unsigned long
RWXmlDuration::getMinutes() const
{
    return minutes_;
}


inline void
RWXmlDuration::setSeconds(double seconds)
{
    seconds_ = seconds;
}

inline double
RWXmlDuration::getSeconds() const
{
    return seconds_;
}

inline RWXmlDuration&
RWXmlDuration::operator-()
{

    negativeDuration_ = negativeDuration_ ? false : true;
    return *this;

}//operator-

#endif // rw_xmlabstractions_RWXmlDuration_h_
