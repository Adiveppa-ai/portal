#ifndef rw_serial_StreamTraits_h_
#define rw_serial_StreamTraits_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/StreamTraits.h#1 $
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

#include <rw/serial/pkgdefs.h>
#include <rw/pointer/RWTSingleton.h>
#include <rw/rstream.h>
#include <rw/tvhdict.h>
#include <string>

// See SP-9216 for more details
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
#  pragma warning(push)
#  pragma warning(disable : 4231)
#  include <rw/pointer/RWTCountingBody.h>
extern template class RWTCountingBody<RWMutexLock>;
#  pragma warning(pop)
#endif

class RWDate;
class RWCString;
class RWWString;
class RWBasicUString;
class RWUString;
class RWDateTime;
class RWDecimalPortable;
class RWInteger;
class RWSymbol;

/**
 * \ingroup serialization_package
 *
 * Constants used to encode simplified type information within annotated
 * object streams.
 */
enum RWStreamType {

    /**
     * = 0
     */
    RW_UNSUPPORTED = 0,

    /**
     * = 1
     */
    RW_CHAR = 1,

    /**
     * = 2
     */
    RW_WCHAR_T = 2,

    /**
     * = 3
     */
    RW_UNSIGNED_CHAR = 3,

    /**
     * = 4
     */
    RW_DOUBLE = 4,

    /**
     * = 5
     */
    RW_FLOAT = 5,

    /**
     * = 6
     */
    RW_INT = 6,

    /**
     * = 7
     */
    RW_UNSIGNED_INT = 7,

    /**
     * = 8
     */
    RW_LONG = 8,

    /**
     * = 9
     */
    RW_UNSIGNED_LONG = 9,

    /**
     * = 10
     */
    RW_SHORT = 10,

    /**
     * = 11
     */
    RW_UNSIGNED_SHORT = 11,

    /**
     * = 12
     */
    RW_STRING = 12,

    /**
     * = 13
     */
    RW_DATE = 13,

    /**
     * = 14
     */
    RW_OBJECT = 14,

    /**
     * = 15
     */
    RW_NESTED_OBJECT = 15,

    /**
     * = 16
     */
    RW_BOOL = 16,

#ifndef RW_NO_LONG_DOUBLE
    /**
     * = 17
     */
    RW_LONG_DOUBLE = 17,
#endif

#if !defined(RW_NO_LONG_LONG)
    /**
     * = 18
     */
    RW_LONG_LONG = 18,

    /**
     * = 19
     */
    RW_UNSIGNED_LONG_LONG = 19,
#endif

    /**
     * = 20
     */
    RW_ID = 20,

    /**
     * = 21
     */
    RW_IDREF = 21,

    /**
     * = 22
     */
    RW_DECIMAL_PORTABLE = 22,

    /**
     * = 23
     */
    RW_DATETIME = 23,

    /**
     * = 30
     */
    RW_NAMESPACE = 30,

    /**
     * = 40
     */
    RW_TYPE = 40,


    /**
     * = 100
     */
    RW_SEQ = 100,

    /**
     * = 101
     */
    RW_SEQ_ELEMENT = 101,


    /**
     * = 10000
     */
    RW_ASSOC = 10000,

    /**
     * = 10001
     */
    RW_ASSOC_ELEMENT = 10001
};

//--A global function overloaded to return the 'RWStreamType' for the
//--type of its argument.
template <class T>
inline RWStreamType
rwStreamType(const T**)
{
    return RW_OBJECT;
}

template <class T>
inline RWStreamType
rwStreamType(T**)
{
    return RW_OBJECT;
}

inline
RWStreamType rwStreamType(const bool*)
{
    return RW_BOOL;
}


inline
RWStreamType rwStreamType(const char*)
{
    return RW_CHAR;
}

inline
RWStreamType rwStreamType(const signed char*)
{
    // No overload for 'signed char' was previously provided, and previously
    // signed char would have matched the 'int' overload. In order to maintain
    // compatibility with existing serialized documents, continue to return the
    // RW_INT identifier for this type
    return RW_INT;
}


inline
RWStreamType rwStreamType(const wchar_t*)
{
    return RW_WCHAR_T;
}


inline
RWStreamType rwStreamType(const unsigned char*)
{
    return RW_UNSIGNED_CHAR;
}


inline
RWStreamType rwStreamType(const double*)
{
    return RW_DOUBLE;
}


#ifndef RW_NO_LONG_DOUBLE
inline
RWStreamType rwStreamType(const long double*)
{
    return RW_LONG_DOUBLE;
}

#endif // RW_NO_LONG_DOUBLE

inline
RWStreamType rwStreamType(const float*)
{
    return RW_FLOAT;
}


inline
RWStreamType rwStreamType(const int*)
{
    return RW_INT;
}


inline
RWStreamType rwStreamType(const unsigned int*)
{
    return RW_UNSIGNED_INT;
}


inline
RWStreamType rwStreamType(const long*)
{
    return RW_LONG;
}


inline
RWStreamType rwStreamType(const unsigned long*)
{
    return RW_UNSIGNED_LONG;
}


#if !defined(RW_NO_LONG_LONG)

inline
RWStreamType rwStreamType(const long long*)
{
    return RW_LONG_LONG;
}


inline
RWStreamType rwStreamType(const unsigned long long*)
{
    return RW_UNSIGNED_LONG_LONG;
}

#endif // !RW_NO_LONG_LONG

inline
RWStreamType rwStreamType(const short*)
{
    return RW_SHORT;
}


inline
RWStreamType rwStreamType(const unsigned short*)
{
    return RW_UNSIGNED_SHORT;
}


inline
RWStreamType rwStreamType(const RWCString*)
{
    return RW_STRING;
}


inline
RWStreamType rwStreamType(const RWSymbol*)
{
    return RW_STRING;
}


inline
RWStreamType rwStreamType(const std::string*)
{
    return RW_STRING;
}


inline
RWStreamType rwStreamType(const RWWString*)
{
    return RW_STRING;
}


inline
RWStreamType rwStreamType(const RWBasicUString*)
{
    return RW_STRING;
}


inline
RWStreamType rwStreamType(const RWUString*)
{
    return RW_STRING;
}


inline
RWStreamType rwStreamType(const RWDate*)
{
    return RW_DATE;
}


inline
RWStreamType rwStreamType(const RWDecimalPortable*)
{
    return RW_DECIMAL_PORTABLE;
}


inline
RWStreamType rwStreamType(const RWDateTime*)
{
    return RW_DATETIME;
}


inline
RWStreamType rwStreamType(const RWInteger*)
{
    return RW_INT;
}



//--Returns an 'RWStreamType' as a string identifier.
inline const char* rwStreamToStringType(RWStreamType stype)
{
    const char* ret = 0;

    if (stype >= RW_ASSOC) {
        ret = "map";
    }
    else if (stype >= RW_SEQ) {
        ret = "sequence";
    }
    else {
        switch (stype) {
            case RW_UNSUPPORTED:
                ret = "unsupported";
                break;

            case RW_CHAR:
                ret = "char";
                break;

            case RW_WCHAR_T:
                ret = "wchar_t";
                break;

            case RW_UNSIGNED_CHAR:
                ret = "unsigned_char";
                break;

            case RW_DOUBLE:
                ret = "double";
                break;

            case RW_FLOAT:
                ret = "float";
                break;

            case RW_INT:
                ret = "int";
                break;

            case RW_UNSIGNED_INT:
                ret = "unsigned_int";
                break;

            case RW_LONG :
                ret = "long";
                break;

            case RW_UNSIGNED_LONG:
                ret = "unsigned_long";
                break;

            case RW_SHORT:
                ret = "short";
                break;

            case RW_UNSIGNED_SHORT:
                ret = "unsigned_short";
                break;

            case RW_STRING:
                ret = "string";
                break;

            case RW_DATE:
                ret = "date";
                break;

            case RW_OBJECT:
                ret = "object";
                break;

            case RW_NESTED_OBJECT:
                ret = "nested_object";
                break;

            case RW_BOOL:
                ret = "boolean";
                break;


#ifndef RW_NO_LONG_DOUBLE
            case RW_LONG_DOUBLE:
                ret = "long_double";
                break;
#endif // RW_NO_LONG_DOUBLE

#if !defined(RW_NO_LONG_LONG)
            case RW_LONG_LONG :
                ret = "long_long";
                break;
            case RW_UNSIGNED_LONG_LONG:
                ret = "unsigned_long_long";
                break;
#endif // !RW_NO_LONG_LONG

            case RW_ID:
                ret = "ID";
                break;

            case RW_IDREF:
                ret = "IDREF";
                break;

            case RW_DATETIME:
                ret = "datetime";
                break;

            case RW_DECIMAL_PORTABLE:
                ret = "decimal_portable";
                break;

            case RW_NAMESPACE:
                ret = "Namespace";
                break;

            case RW_TYPE:
                ret = "Unknown_Type";
                break;

            default:
                ret = "";
                break;

        }
    }

    return ret;
}

//--Outputs an 'RWStreamType' as a string identifier.
inline
std::ostream&
operator<<(std::ostream& strm, RWStreamType stype)
{
    strm << rwStreamToStringType(stype);
    return strm;
}

//--Class used to convert a string identifier into an 'RWStreamType'.
class RWStringToStreamType : public RWTValHashDictionary<RWCString, RWStreamType>
{
    friend class RWTSingleton<RWStringToStreamType>;
public:
    static RWStreamType convert(const RWCString& name)
    {
        RWStreamType result = (RWStreamType) - 1;
        (*RWTSingleton<RWStringToStreamType>::instance()).
        findValue(name, result);
        return result;
    }
private:
    RWStringToStreamType()
    {
        insertKeyAndValue("map", RW_ASSOC);
        insertKeyAndValue("sequence", RW_SEQ);
        insertKeyAndValue("unsupported", RW_UNSUPPORTED);
        insertKeyAndValue("char", RW_CHAR);
        insertKeyAndValue("wchar_t", RW_WCHAR_T);
        insertKeyAndValue("unsigned_char", RW_UNSIGNED_CHAR);
        insertKeyAndValue("double", RW_DOUBLE);
        insertKeyAndValue("float", RW_FLOAT);
        insertKeyAndValue("int", RW_INT);
        insertKeyAndValue("unsigned_int", RW_UNSIGNED_INT);
        insertKeyAndValue("long", RW_LONG);
        insertKeyAndValue("unsigned_long", RW_UNSIGNED_LONG);
        insertKeyAndValue("short", RW_SHORT);
        insertKeyAndValue("unsigned_short", RW_UNSIGNED_SHORT);
        insertKeyAndValue("string", RW_STRING);
        insertKeyAndValue("date", RW_DATE);
        insertKeyAndValue("datetime", RW_DATETIME);
        insertKeyAndValue("decimal_portable", RW_DECIMAL_PORTABLE);
        insertKeyAndValue("object", RW_OBJECT);
        insertKeyAndValue("nested_object", RW_NESTED_OBJECT);
        insertKeyAndValue("boolean", RW_BOOL);
#ifndef RW_NO_LONG_DOUBLE
        insertKeyAndValue("long_double", RW_BOOL);
#endif // RW_NO_LONG_DOUBLE
#if !defined(RW_NO_LONG_LONG)
        insertKeyAndValue("long_long", RW_LONG_LONG);
        insertKeyAndValue("unsigned_long_long", RW_UNSIGNED_LONG_LONG);
#endif // !RW_NO_LONG_LONG
        insertKeyAndValue("ID", RW_ID);
        insertKeyAndValue("IDREF", RW_IDREF);
        insertKeyAndValue("Namespace", RW_NAMESPACE);
        insertKeyAndValue("UnKnown_Type", RW_TYPE);
    }
};

#endif // rw_serial_StreamTraits_h_
