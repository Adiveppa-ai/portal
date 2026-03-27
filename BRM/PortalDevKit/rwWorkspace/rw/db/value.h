#ifndef __RWDB_VALUE_H__
#define __RWDB_VALUE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/value.h#1 $
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
 * Definition of class RWDBValue
 *
 * This class provides a central interface to all database values, i.e.
 * the C++ primitives int, float, etc, as well as RWDateTime, RWCString,
 * etc. The value can be set either thru the constructors or the assignment
 * operators. IS NULL/ IS NOT NULL semantics are added for those types
 * (i.e. the primitives) which do not support them natively.
 *
 * Explicit type conversion routines (the asXXX() methods) are provided,
 * automatic type conversion is not provided.
 *
 * RWDBValue is derived from RWCollectable, and the compareTo() and isEqual()
 * methods required for RWCollectables are redefined. They should be used
 * with care, however, since no type conversion is implicit in them. RWDBValue
 * instances representing different types will never be equal. For example:
 * short y; int x = y;
 * if (RWDBValue(x).compareTo(RWDBValue(y)) == 0)
 *     //  never happens.
 *
 **************************************************************************/

#include <rw/db/blob.h>
#include <rw/db/datetime.h>
#include <rw/db/defs.h>
#include <rw/db/duration.h>
#include <rw/db/mbstring.h>
#include <rw/collect.h>
#include <rw/decport.h>
#include <rw/rwdate.h>
#include <rw/tools/bustring.h>
#include <rw/tools/datetime.h>
#include <rw/tools/timetuple.h>
#include <rw/tools/timetupleoffset.h>
#include <rw/wstring.h>

// To manipulate state_:
#define RWDBHIBIT               0x80
#define RWDBNOTHIBIT            0x7f
#define RWDBSTATE(isNull, type) static_cast<unsigned char>((isNull) ? ((type) | RWDBHIBIT) : (type))
#define RWDBISNULLSTATE(state)  ((state) & RWDBHIBIT)
#define RWDBTYPE(state)         ((ValueType)((state) & RWDBNOTHIBIT))


// define the RWDBValueManip for the assignment operator with rwdbNull
//
// NOTE: Null values, regardless of type, return a default value;
//       zero(0) or default constructor.  isNull() should always be
//       used to determine null values, not the default null value.

class RWDB_GLOBAL RWDBValue;

/**
 * \relates RWDBValue
 *
 * #RWDBValueManip is a typedef and is typically used to insert a \c NULL
 * value.
 */
typedef void (*RWDBValueManip)(RWDBValue&);

/**
 * \relates RWDBValue
 *
 * #rwdbNull is of type #RWDBValueManip. It is used to represent a literal
 * \c NULL value.
 */
void RWDB_SYMBOLIC rwdbNull(RWDBValue&);


/**
 * \ingroup db_data_types_group
 * \class RWDBValue
 *
 * \brief
 * Provides storage for C++ primitive types and structured types used by the
 * DB Interface Module, and adds <tt>NULL/NOT NULL</tt> semantics.
 *
 * RWDBValue provides storage for C++ primitive types and structured types
 * used by the DB Interface Module. It also adds <tt>NULL/NOT NULL</tt>
 * semantics to the types. RWDBValue is used in two ways:
 *
 * - \e Externally, RWDBValue allows your applications to work with data
 * from the database without knowing the data's type. For example, you could
 * write an ad hoc query tool to process and print result data from
 * arbitrary queries that return different types of data. Instead of using
 * specific data types like \c int or RWDateTime, you could simply read the
 * data into an RWDBValue instance and use the asString() method to convert
 * the data into an RWCString.
 * - \e Internally, RWDBValue provides a value-oriented interface to
 * application programs. See the chapter "The Data Model" in the <em>DB
 * Interface Module User's Guide</em> for more information on the data model
 * of the DB Interface Module.
 *
 * RWDBValue inherits from class RWCollectable of the Essential Tools
 * Module. The virtual functions of the base class RWCollectable are
 * redefined, allowing instances of RWDBValue to be stored in the
 * Smalltalk-like collections of the Essential Tools Module.
 *
 * \synopsis
 * #include <rw/db/value.h>
 *
 * RWDBValue value;             //null, no type value
 * RWDBValue value(20);         //integer value
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBValue : public RWCollectable
{
    friend void RWDB_SYMBOLIC rwdbNull(RWDBValue&);

public:
    /**
     * Every RWDBValue is tagged with a #ValueType. In addition, RWDBColumn
     * uses RWDBValue::ValueType to store schema information. In that
     * context, #Tiny and #UnsignedTiny refer to one-byte integers. The DB
     * Interface Module does not store data as #Tiny or #UnsignedTiny.
     */
    enum ValueType {

        /**
         * Indicates there is no associated data.
         */
        NoType = 0,

        /**
         * Associated with data of type \c char.
         */
        Char,

        /**
         * Associated with data of type <tt>unsigned char</tt>.
         */
        UnsignedChar,

        /**
         * Used by RWDBColumn to indicate a one-byte integral type.
         */
        Tiny,

        /**
         * Used by RWDBColumn to indicate a one-byte unsigned integral type.
         */
        UnsignedTiny,

        /**
         * Associated with data of type \c short.
         */
        Short,

        /**
         * Associated with data of type <tt>unsigned short</tt>.
         */
        UnsignedShort,

        /**
         * Associated with data of type \c int.
         */
        Int,

        /**
         * Associated with data of type <tt>unsigned int</tt>.
         */
        UnsignedInt,

        /**
         * Associated with data of type \c long.
         */
        Long,

        /**
         * Associated with data of type <tt>unsigned long</tt>.
         */
        UnsignedLong,

        /**
         * Associated with data of type <tt>long long</tt>.
         */
        LongLong,

        /**
         * Associated with data of type <tt>unsigned long long</tt>.
         */
        UnsignedLongLong,

        /**
         * Associated with data of type \c float.
         */
        Float,

        /**
         * Associated with data of type \c double.
         */
        Double,

        /**
         * Associated with data of type <tt>long double</tt>.
         */
        LongDouble,

        /**
         * Associated with data of type RWDecimalPortable.
         */
        Decimal,

        /**
         * Associated with data of type RWDate.
         */
        Date,

        /**
         * Associated with data of type RWDateTime.
         */
        DateTime,

        /**
         * Associated with data of type RWTimeTuple.
         */
        TimeTuple,

        /**
         * Associated with data of type RWTimeTupleOffset.
         */
        TimeTupleOffset,

        /**
         * Associated with data of type RWDBDuration.
         */
        Duration,

        /**
         * Associated with data of type RWCString.
         */
        String,

        /**
         * Associated with data of type RWDBBlob.
         */
        Blob,

        /**
         * Associated with data of type RWWString.
         */
        WString,

        /**
         * Associated with data of type RWDBMBString.
         */
        MBString,

        /**
         * Associated with data of type RWBasicUString.
         */
        UString
    };

    /**
     * The default constructor creates a \c NULL value without type.
     */
    RWDBValue();

    /**
     * Copy constructor. RWDBValue obeys value semantics.
     */
    RWDBValue(const RWDBValue& value);

    /**
     * Constructs an RWDBValue defined by the semantics of \a manip. In
     * particular, #rwdbNull can be used to construct a \c NULL value
     * without type.
     */
    RWDBValue(RWDBValueManip manip);

    /**
     * Constructs an RWDBValue from the supplied \a value. Self is
     * non-\c NULL and is tagged with the appropriate #ValueType.
     */
    RWDBValue(char value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(unsigned char value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(short value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(unsigned short value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(int value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(unsigned int value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(long value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(unsigned long value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(long long value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(unsigned long long value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(float value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(double value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(long double value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const char* value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const wchar_t* value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWDecimalPortable& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWDate& value);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 12.5, use
     * \ref RWDBValue::RWDBValue(const RWDateTime&) "RWDBValue(const RWDateTime&)"
     * instead.
     *
     * \copydoc RWDBValue(char)
     */
    RW_DEPRECATE_FUNC("Use RWDBValue::RWDBValue(const RWDateTime&) instead")
    RWDBValue(const RWDBDateTime& value);
#endif

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWDateTime& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWTimeTuple& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWTimeTupleOffset& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWDBDuration& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWCString& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWDBBlob& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWWString& value);

    /**
     * \copydoc RWDBValue(char)
     */
    RWDBValue(const RWDBMBString& value);

    /**
     * \copydoc RWDBValue(char)
     *
     * \note
     * This function accepts Unicode strings. For more information, see the
     * entry for RWBasicUString in the Essential Tools Module Reference
     * Guide. For more information on internationalization, see the chapter
     * "Internationalization" of the <em>DB Interface Module User's
     * Guide</em>.
     */
    RWDBValue(const RWBasicUString& value);

    // destructor
    virtual ~RWDBValue();

    /**
     * Returns the number of bytes required to store self in an RWFile.
     */
    virtual RWspace     binaryStoreSize() const;

    /**
     * Interprets \a cp as a pointer to an RWDBValue, dereferences it, and
     * compares the result with self. If either self or *\a cp is \c NULL,
     * the result is undefined. Otherwise, if self and *\a cp have the same
     * type, the result is \c &lt;0, \c 0, or \c &gt;0, depending upon
     * whether self is less than, equal to, or greater than *\a cp,
     * according to the semantics of self's type. Otherwise self and *\a cp
     * have different types, and the result is defined only as nonzero.
     *
     * As a precondition, \a cp is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual int         compareTo(const RWCollectable* cp) const;

    /**
     * Returns \c true if \ref compareTo() "compareTo( \a cp )"
     * <tt>== 0</tt>, otherwise returns \c false.
     */
    virtual bool        isEqual(const RWCollectable* cp) const;

    /**
     * Returns a suitable value for hashing.
     */
    virtual unsigned    hash() const;

    /**
     * Writes self to \a file.
     */
    virtual void        saveGuts(RWFile&     file) const;

    /**
     * Writes self to \a stream.
     */
    virtual void        saveGuts(RWvostream& stream) const;

    /**
     * Replaces the value of self with a value read from \a file.
     */
    virtual void        restoreGuts(RWFile&     file);

    /**
     * Replaces the value of self with a value read from \a stream.
     */
    virtual void        restoreGuts(RWvistream& stream);

    /**
     * Returns the data type of self.
     */
    ValueType           type() const;

    /**
     * Returns the data type of self formatted as a \c string.
     */
    RWCString           typeString() const;

    /**
     * Returns \c true if self represents a \c NULL value, otherwise returns
     * \c false. Note that the results of arithmetic and logical operations
     * on \c NULL values are undefined; checks for \c NULL must be made
     * independently.
     */
    bool                isNull() const;

    /**
     * Returns \c true if self can be converted to \a type by an
     * <b>RWDBValue::as\e Type()</b> method, otherwise returns \c false.
     *
     * The table below shows the supported type conversions. Each row is a
     * data type to be converted, while each column is a conversion type. A
     * \c 1 means <em>can convert</em> and a \c 0 means <em>can't
     * convert</em>. For example, table shows that type #Blob can be
     * converted to itself and to #String, #WString, #MBString, and
     * #UString.
     *
     * <b>Supported Type Conversions</b>
     * <table>
     * <tr>
     * <td></td>
     * <td><b>Type</b></td>
     * <td><b>a</b></td>
     * <td><b>b</b></td>
     * <td><b>c</b></td>
     * <td><b>d</b></td>
     * <td><b>e</b></td>
     * <td><b>f</b></td>
     * <td><b>g</b></td>
     * <td><b>h</b></td>
     * <td><b>i</b></td>
     * <td><b>j</b></td>
     * <td><b>k</b></td>
     * <td><b>l</b></td>
     * <td><b>m</b></td>
     * <td><b>n</b></td>
     * <td><b>o</b></td>
     * <td><b>p</b></td>
     * <td><b>q</b></td>
     * <td><b>r</b></td>
     * <td><b>s</b></td>
     * <td><b>t</b></td>
     * <td><b>u</b></td>
     * <td><b>v</b></td>
     * <td><b>w</b></td>
     * <td><b>x</b></td>
     * <td><b>y</b></td>
     * </tr>
     * <tr>
     * <td><b>a</b></td>
     * <td>#NoType</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * </tr>
     * <tr>
     * <td><b>b</b></td>
     * <td>#Char</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>c</b></td>
     * <td>#UnsignedChar</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>d</b></td>
     * <td>#Short</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>e</b></td>
     * <td>#UnsignedShort</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>f</b></td>
     * <td>#Int</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>g</b></td>
     * <td>#UnsignedInt</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>h</b></td>
     * <td>#Long</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>i</b></td>
     * <td>#UnsignedLong</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>j</b></td>
     * <td>#LongLong</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>k</b></td>
     * <td>#UnsignedLongLong</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>l</b></td>
     * <td>#Float</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>m</b></td>
     * <td>#Double</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1<sup>1</sup></td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>n</b></td>
     * <td>#LongDouble</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>o</b></td>
     * <td>#Decimal</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>p</b></td>
     * <td>#Date</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>q</b></td>
     * <td>#DateTime</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>r</b></td>
     * <td>#TimeTuple</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>1</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>s</b></td>
     * <td>#TimeTupleOffset</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * <td>1</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>t</b></td>
     * <td>#Duration</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>0</td>
     * </tr>
     * <tr>
     * <td><b>u</b></td>
     * <td>#String</td>
     * <td>0</td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>1<sup>2</sup></td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * </tr>
     * <tr>
     * <td><b>v</b></td>
     * <td>#Blob</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * </tr>
     * <tr>
     * <td><b>w</b></td>
     * <td>#WString</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * </tr>
     * <tr>
     * <td><b>x</b></td>
     * <td>#MBString</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * </tr>
     * <tr>
     * <td><b>y</b></td>
     * <td>#UString</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>0</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * <td>1</td>
     * </tr>
     * </table>
     *
     * <sup>1</sup> Conversion will only be carried out to a scale of 6.\n
     * <sup>2</sup> Conversion is supported only if the string value is
     * representable as a number.\n
     *
     * \note
     * Loss of precision can result without warning if you try to convert a
     * string representation of a number into a value that can't hold it. If
     * this is a concern, please use RWDecimalPortable, as in the following
     * example:
     * \code
     * RWDBValue aNumber("12345.6789");
     * assert(aNumber.canConvert(RWDBValue::Char));
     * char numberThatIsTooSmall = aNumber.asChar();      // No way that 12345.6789 can fit.
     * assert(aNumber.canConvert(RWDBValue::Decimal));
     * RWDecimalPortable bigEnough = aNumber.asDecimal(); // This is OK.
     * \endcode
     */
    bool                canConvert(ValueType type) const;

    /**
     * Returns self as a \c char. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Char, returns a \c char
     * with value <tt>(char)0</tt>.
     */
    char                asChar() const;

    /**
     * Returns self as an <tt>unsigned char</tt>. If self cannot be
     * converted according to canConvert() using an argument of
     * RWDBValue::UnsignedChar, returns an <tt>unsigned char</tt> with a
     * value of <tt>(unsigned char) 0</tt>.
     */
    unsigned char       asUnsignedChar() const;

    /**
     * Returns self as a \c short. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Short, returns a
     * \c short with a value of \c 0.
     */
    short               asShort() const;

    /**
     * Returns self as an <tt>unsigned short</tt>. If self cannot be
     * converted according to canConvert() using an argument of
     * RWDBValue::UnsignedShort, returns an <tt>unsigned short</tt> with a
     * value of \c 0.
     */
    unsigned short      asUnsignedShort() const;

    /**
     * Returns self as an \c int. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Int, returns an \c int
     * with a value of \c 0.
     */
    int                 asInt() const;

    /**
     * Returns self as an <tt>unsigned int</tt>. If self cannot be converted
     * according to canConvert() using an argument of
     * RWDBValue::UnsignedInt, returns an <tt>unsigned int</tt> with a value
     * of \c 0.
     */
    unsigned int        asUnsignedInt() const;

    /**
     * Returns self as a \c long. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Long, returns a \c long
     * with a value of \c 0.
     */
    long                asLong() const;

    /**
     * Returns self as an <tt>unsigned long</tt>. If self cannot be
     * converted according to canConvert() using an argument of
     * RWDBValue::UnsignedLong, returns an <tt>unsigned long</tt> with a
     * value of \c 0.
     */
    unsigned long       asUnsignedLong() const;

    /**
     * Returns self as a <tt>long long</tt>. If self cannot be converted
     * according to canConvert() using an argument of RWDBValue::LongLong,
     * returns a <tt>long long</tt> with a value of \c 0.
     */
    long long           asLongLong() const;

    /**
     * Returns self as an <tt>unsigned long long</tt>. If self cannot be
     * converted according to canConvert() using an argument of
     * RWDBValue::UnsignedLongLong, returns an <tt>unsigned long long</tt>
     * with a value of \c 0.
     */
    unsigned long long  asUnsignedLongLong() const;

    /**
     * Returns self as a \c float. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Float, returns a
     * \c float with a value of \c 0.
     */
    float               asFloat() const;

    /**
     * Returns self as a \c double. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Double, returns a
     * \c double with a value of \c 0.
     */
    double              asDouble() const;

    /**
     * Returns self as a <tt>long double</tt>. If self cannot be converted
     * according to canConvert() using an argument of RWDBValue::LongDouble,
     * returns a <tt>long double</tt> with a value of \c 0.
     */
    long double         asLongDouble() const;

    /**
     * Returns self as an RWDecimalPortable. If self cannot be converted
     * according to canConvert() using an argument of RWDBValue::Decimal,
     * returns an RWDecimalPortable with a value of \c 0.
     */
    RWDecimalPortable   asDecimal() const;

    /**
     * Returns self as an RWDate. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Date, returns an RWDate
     * whose state is invalid.
     */
    RWDate              asDate() const;

    /**
     * Returns self as an RWDateTime. If self cannot be converted according
     * to canConvert() using an argument of RWDBValue::DateTime, returns an
     * RWDateTime whose state is invalid.
     */
    RWDateTime          asDateTime() const;

    /**
     * Returns self as an RWTimeTuple. If self cannot be converted according
     * to canConvert() using an argument of RWDBValue::TimeTuple, returns an
     * RWTimeTuple with all fields set to \c -1.
     */
    RWTimeTuple         asTimeTuple() const;

    /**
     * Returns self as an RWTimeTupleOffset. If self cannot be converted
     * according to canConvert() using an argument of
     * RWDBValue::TimeTupleOffset, returns an RWTimeTupleOffset with all
     * fields set to \c -1.
     */
    RWTimeTupleOffset   asTimeTupleOffset() const;

    /**
     * Returns self as an RWDBDuration. If self cannot be converted
     * according to canConvert() using an argument of RWDBValue::Duration,
     * returns an RWDBDuration whose state is invalid.
     */
    RWDBDuration        asDuration() const;

    /**
     * Returns self as an RWCString. Any RWDBValue can be converted to an
     * RWCString. Uses default format specifications.
     */
    RWCString           asString() const;

    /**
     * Returns self as an RWCString. Any RWDBValue can be converted to an
     * RWCString. Uses format specifications from the supplied
     * \a phraseBook.
     */
    RWCString           asString(const RWDBPhraseBook& phraseBook) const;

    void                asString(const RWDBPhraseBook& phrasebook,
                                 RWCString& result) const;

    /**
     * Returns self as an RWDBBlob. If self cannot be converted according to
     * canConvert() using an argument of RWDBValue::Blob, returns an
     * RWDBBlob with zero length. If self holds data of type
     * RWDBValue::UString, conversion to RWDBBlob checks the endian format
     * used by the current system (Big-Endian or Little-Endian) to give the
     * same RWDBBlob data for the same #UString data independent of the
     * endian format of the system.
     */
    RWDBBlob            asBlob() const;
    /**
     * Returns self as an RWWString. Any RWDBValue can be converted to an
     * RWWString.
     */
    RWWString           asWString() const;
    /**
     * Returns self as an RWDBMBString. Any RWDBValue can be converted to an
     * RWDBMBString.
     */
    RWDBMBString        asMBString() const;

    /**
     * Returns self as an RWBasicUString. If self cannot be converted
     * according to canConvert() using an argument of RWDBValue::UString,
     * then returns an empty RWBasicUString. If self holds data of type
     * RWDBValue::Blob, conversion to RWBasicUString checks the endian
     * format used by the current system (Big-Endian or Little-Endian) to
     * give the same RWBasicUString data for the same #Blob data independent
     * of the endian format of the system.
     *
     * \note
     * This function returns a Unicode string. For more information, see the
     * entry for RWBasicUString in the Essential Tools Module Reference
     * Guide. For more information on internationalization, see the Chapter
     * "Internationalization" of the <em>DB Interface Module User's
     * Guide</em>.
     */
    RWBasicUString      asUString() const;

    /**
     * Assignment operator. RWDBValue obeys value semantics.
     */
    RWDBValue&  operator=(const RWDBValue& value);

    /**
     * Assigns a type and value defined by \a manip to self. In particular,
     * #rwdbNull can be assigned to an RWDBValue, changing it into a \c NULL
     * value without type.
     */
    RWDBValue&  operator=(RWDBValueManip manip);

    /**
     * Assigns \a value's type and value to self.
     */
    RWDBValue&  operator=(char value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(unsigned char value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(short value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(unsigned short value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(int value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(unsigned int value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(long value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(unsigned long value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(long long value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(unsigned long long value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(float value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(double value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(long double value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWDecimalPortable& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWDate& value);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 12.5, use
     * \ref RWDBValue::operator=(const RWDateTime&) "operator=(const RWDateTime&)"
     * instead.
     *
     * \copydoc operator=(char)
     */
    RW_DEPRECATE_FUNC("Use RWDBValue::operator=(const RWDateTime&) instead")
    RWDBValue&  operator=(const RWDBDateTime& value);
#endif

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWDateTime& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWTimeTuple& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWTimeTupleOffset& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWDBDuration& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWCString& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWDBBlob& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWWString& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWDBMBString& value);

    /**
     * \copydoc operator=(char)
     */
    RWDBValue&  operator=(const RWBasicUString& value);

    // static asString methods.  These do not require creating
    // an RWDBValue object
    static void asString(char v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(unsigned char v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(short v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(unsigned short v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(int v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(unsigned int v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(long v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(unsigned long v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(long long v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(unsigned long long v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(float v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(double v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(long double v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(const RWDecimalPortable& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(const RWDate& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    static void asString(const RWDBDateTime& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    static void asString(const RWDateTime& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

    static void asString(const RWTimeTuple& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

    static void asString(const RWTimeTupleOffset& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

    static void asString(const RWDBDuration& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

    static void asString(const RWCString& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(const RWDBBlob& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(const RWWString& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);
    static void asString(const RWDBMBString& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

    static void asString(const RWBasicUString& v,
                         const RWDBPhraseBook& pb,
                         RWCString& theString);

    /**
     * Redefined from class RWCollectable. Returns __RWDBVALUE.
     */
    virtual RWClassID isA() const;

    // any documentation for the following is in the base class
    virtual RWCollectable* newSpecies() const;
    virtual RWCollectable* copy() const;
    static RWClassID       classIsA();

    friend RWDB_SYMBOLIC RWvistream&
    operator>>(RWvistream& s, RWDBValue*& pCl);

    friend RWDB_SYMBOLIC RWFile&
    operator>>(RWFile& f, RWDBValue*& pCl);

    RW_INLINE_FRIEND
    RWvostream& operator<<(RWvostream& v, const RWDBValue& Cl)
    {
        Cl.recursiveSaveOn(v);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator<<(RWFile& f, const RWDBValue& Cl)
    {
        Cl.recursiveSaveOn(f);
        return f;
    }

    RW_INLINE_FRIEND
    RWvistream& operator>>(RWvistream& v, RWDBValue& Cl)
    {
        RWCollectable::recursiveRestoreFrom(v, &Cl);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator>>(RWFile& f, RWDBValue& Cl)
    {
        RWCollectable::recursiveRestoreFrom(f, &Cl);
        return f;
    }

public:
    // Internal methods. Not part of user API.
    RWCString           asString(const RWZone& zone) const;
    RWCString           asString(const RWDBPhraseBook& phrasebook,
                                 const RWZone& zone) const;
    void                asString(const RWDBPhraseBook& phrasebook,
                                 RWCString& result,
                                 const RWZone& zone) const;

protected:

    union {
        long                long_;       // stores char, tiny, short, int and long
        unsigned long       ulong_;      // stores unsigned versions of above
        long long           longlong_;   // stores long long
        unsigned long long  ulonglong_;  // stores unsigned long long
        double              double_;     // stores float and double
        long double         longdouble_; // stores long double
        char                decimal_[sizeof(RWDecimalPortable)];
        char                datetime_[sizeof(RWDateTime)];
        char                timetuple_[sizeof(RWTimeTuple)];
        char                timetupleoffset_[sizeof(RWTimeTupleOffset)];
        char                duration_[sizeof(RWDBDuration)];
        char                string_[sizeof(RWCString)];
        char                mbstring_[sizeof(RWDBMBString)];
        char                blob_[sizeof(RWDBBlob)];
        char                ustring_[sizeof(RWBasicUString)];
        char                wstring_[sizeof(RWWString)];
    };

private:
    static RWClassID myAtom;
    friend struct RWInit(RWDBValue);
    friend RWCollectable* rwCreateFN(RWDBValue)();

    RWDecimalPortable*       asRWDecimalPortable();
    const RWDecimalPortable* asRWDecimalPortable() const;

    RWDateTime*       asRWDateTime();
    const RWDateTime* asRWDateTime() const;

    RWTimeTuple*       asRWTimeTuple();
    const RWTimeTuple* asRWTimeTuple() const;

    RWTimeTupleOffset*       asRWTimeTupleOffset();
    const RWTimeTupleOffset* asRWTimeTupleOffset() const;

    RWDBDuration*       asRWDBDuration();
    const RWDBDuration* asRWDBDuration() const;

    RWCString*       asRWCString();
    const RWCString* asRWCString() const;

    RWDBMBString*       asRWDBMBString();
    const RWDBMBString* asRWDBMBString() const;

    RWDBBlob*       asRWDBBlob();
    const RWDBBlob* asRWDBBlob() const;

    RWBasicUString*       asRWBasicUString();
    const RWBasicUString* asRWBasicUString() const;

    RWWString*       asRWWString();
    const RWWString* asRWWString() const;

    void             cleanup();
    static void      enclose(RWCString& string, const char* openquote,
                             const char* closequote, const char* escape,
                             const char* quotePrefix = 0);
    static void      duplicateCharacter(RWCString& string,
                                        const char* escape);

    unsigned char     state_;            // codes type and nullness
    static const char RWDBConversions[]; // table of allowable conversions
};

inline RWDecimalPortable* RWDBValue::asRWDecimalPortable()
{
    return reinterpret_cast<RWDecimalPortable*>(decimal_);
}

inline const RWDecimalPortable* RWDBValue::asRWDecimalPortable() const
{
    return reinterpret_cast<const RWDecimalPortable*>(decimal_);
}

inline RWDateTime* RWDBValue::asRWDateTime()
{
    return reinterpret_cast<RWDateTime*>(datetime_);
}

inline const RWDateTime* RWDBValue::asRWDateTime() const
{
    return reinterpret_cast<const RWDateTime*>(datetime_);
}

inline RWTimeTuple* RWDBValue::asRWTimeTuple()
{
    return reinterpret_cast<RWTimeTuple*>(timetuple_);
}

inline const RWTimeTuple* RWDBValue::asRWTimeTuple() const
{
    return reinterpret_cast<const RWTimeTuple*>(timetuple_);
}

inline RWTimeTupleOffset* RWDBValue::asRWTimeTupleOffset()
{
    return reinterpret_cast<RWTimeTupleOffset*>(timetupleoffset_);
}

inline const RWTimeTupleOffset* RWDBValue::asRWTimeTupleOffset() const
{
    return reinterpret_cast<const RWTimeTupleOffset*>(timetupleoffset_);
}

inline RWDBDuration* RWDBValue::asRWDBDuration()
{
    return reinterpret_cast<RWDBDuration*>(duration_);
}

inline const RWDBDuration* RWDBValue::asRWDBDuration() const
{
    return reinterpret_cast<const RWDBDuration*>(duration_);
}

inline RWCString* RWDBValue::asRWCString()
{
    return reinterpret_cast<RWCString*>(string_);
}

inline const RWCString* RWDBValue::asRWCString() const
{
    return reinterpret_cast<const RWCString*>(string_);
}

inline RWDBMBString* RWDBValue::asRWDBMBString()
{
    return reinterpret_cast<RWDBMBString*>(mbstring_);
}

inline const RWDBMBString* RWDBValue::asRWDBMBString() const
{
    return reinterpret_cast<const RWDBMBString*>(mbstring_);
}

inline RWDBBlob* RWDBValue::asRWDBBlob()
{
    return reinterpret_cast<RWDBBlob*>(blob_);
}

inline const RWDBBlob* RWDBValue::asRWDBBlob() const
{
    return reinterpret_cast<const RWDBBlob*>(blob_);
}

inline RWBasicUString* RWDBValue::asRWBasicUString()
{
    return reinterpret_cast<RWBasicUString*>(ustring_);
}

inline const RWBasicUString* RWDBValue::asRWBasicUString() const
{
    return reinterpret_cast<const RWBasicUString*>(ustring_);
}

inline RWWString* RWDBValue::asRWWString()
{
    return reinterpret_cast<RWWString*>(wstring_);
}

inline const RWWString* RWDBValue::asRWWString() const
{
    return reinterpret_cast<const RWWString*>(wstring_);
}

/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Represents an Oracle PL/SQL cursor type.
 *
 * RWDBNativeType1 is a special type used to represent the Oracle PL/SQL
 * cursor type as a RWDBTBuffer template type.
 *
 * This is explained in detail in the subsection "Supported Datatypes for
 * Output Binding" in the Section "Open SQL and Oracle OCI" in the <em>DB
 * Access Module for Oracle OCI User's Guide</em>.
 */
#ifndef DOXYGEN
// Hide the fact there is an inheritance relationship here to doxygen.
// We do not want to expose to end users that RWDBNativeType1 inherits from
// RWDBValue incase we need to break that relationship in the future.
class RWDBNativeType1 : public RWDBValue { };
#else
class RWDBNativeType1 { };
#endif

/**
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * Function object for hashing an RWDBValue.
 *
 * Provides a C++ Standard Library-compliant hash function object suitable
 * for use with hash or unordered containers.
 */
template <>
struct RWTHash<RWDBValue> : std::unary_function<RWDBValue, size_t> {
    /**
     * Returns a hash of \a obj. This function is the equivalent of calling
     *
     * \code
     * obj.hash();
     * \endcode
     */
    size_t operator()(const RWDBValue& obj) const
    {
        return obj.hash();
    }
};

#endif
