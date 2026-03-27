#ifndef __RWDB_MBSTRING_H__
#define __RWDB_MBSTRING_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/mbstring.h#1 $
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
 * Definition of class RWDBMBString
 *
 * This class is a simple wrapper around RWCString.  Because databases
 * differentiate between multibyte strings and standard US-ASCII strings,
 * the DB Interface must do the same.  Essential Tools does not differentiate,
 * storing both types of strings in the class RWCString.  This class
 * allows the DB Interface to treat multibyte strings differently even though it
 * ends up storing them in an instance of RWCString.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/cstring.h>
#include <rw/tools/hash.h>


/**
 * \ingroup db_data_types_group
 *
 * \brief
 * Represents a multibyte character string, ensuring that these get handled
 * correctly by databases that differentiate between multibyte and single
 * byte character strings.
 *
 * Some databases require different handling of single byte character sets
 * (SBCS), like US-ASCII or ISO Latin-1, and multibyte character sets
 * (MBCS). Writing applications using class RWDBMBString for MBCS strings
 * and class RWCString for SBCS strings allows the DB Interface Module to
 * make the critical differentiation.
 *
 * RWDBMBString derives publicly from RWCString, such that all the
 * facilities and functions of RWCString are available. For a complete
 * description of those functions, see the Essential Tools Module
 * documentation for class RWCString.
 *
 * We recommend that you do \e not derive from RWDBMBString.
 *
 * \synopsis
 * #include <rw/db/mbstring.h>
 * RWDBMBString a;
 * \endsynopsis
 *
 * \persistence{Simple}
 *
 * \example
 * \code
 * #include <iostream.h>
 * #include <rw/db/mbstring.h>
 *
 * void
 * outputTest(RWDBDatabase& aDB){
 *     RWDBInserter ins = aDB.table("t1").inserter();
 *     RWDBMBString mbstring("\x4E\x16\x75\x4C\x60\xA8\x59\x7D");
 *     ins << mbstring;
 *     cout << ins.asString() << endl;
 * }
 * \endcode
 *
 * Oracle treats multibyte and single byte strings differently. If \c aDB
 * represents an Oracle database and the proper character set is loaded on
 * the machine, the output is:
 *
 * \code
 * INSERT INTO T1 VALUES (N'<U+4E16><U+754C><U+60A8><U+597D>')
 * \endcode
 *
 * Sybase does not differentiate between multibyte and single byte strings.
 * If \c aDB represents a Sybase database and the proper character set is
 * loaded on the machine, the output is:
 *
 * \code
 * INSERT INTO T1 VALUES ('<U+4E16><U+754C><U+60A8><U+597D>')
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBMBString : public RWCString
{
public:

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString()
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(RWSize_T ic) : RWCString(ic)
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(const RWCString& S) : RWCString(S)
    {
        ;
    }

    /**
     * Copy constructor. The created string copies \a str's data.
     */
    RWDBMBString(const RWDBMBString& str) : RWCString(str)
    {
        ;
    }

    /**
     * Calls the corresponding constructor of RWCString.
     */
    RWDBMBString(const char* a) : RWCString(a)
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(const char* a, size_t N) : RWCString(a, N)
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(char c) : RWCString(c)
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(char c, size_t N) : RWCString(c, N)
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(const RWCSubString& SS) : RWCString(SS)
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(unsigned char c) : RWCString(c)
    {
        ;
    }

    /**
     * \copydoc RWDBMBString(const char *)
     */
    RWDBMBString(signed char c) : RWCString(c)
    {
        ;
    }

    virtual ~RWDBMBString()
    {
        ;
    }

    /**
     * Copies the null-terminated character string pointed to by \a cs into
     * self. Returns a reference to self. This function is incompatible with
     * \a cs strings with embedded nulls. This function may be incompatible
     * with \a cs MBCS strings.
     */
    RWDBMBString&    operator=(const char* cs)
    {
        RWCString::operator=(cs);
        return *this;
    }

    /**
     * The string copies \a str's data. Returns a reference to self.
     */
    RWDBMBString&    operator=(const RWCString& str)
    {
        RWCString::operator=(str);
        return *this;
    }

    /**
     * The string copies \a str's data. Returns a reference to self.
     */
    RWDBMBString&    operator=(const RWDBMBString& str)
    {
        RWCString::operator=(str);
        return *this;
    }

private:

};


/**
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * Function object for hashing an RWDBMBString.
 *
 * Provides a C++ Standard Library-compliant hash function object suitable
 * for use with hash or unordered containers.
 */
template <>
struct RWTHash<RWDBMBString> : std::unary_function<RWDBMBString, size_t> {
    /**
     * Returns a hash of \a obj. This function is the equivalent of calling
     *
     * \code
     * obj.hash();
     * \endcode
     */
    size_t operator()(const RWDBMBString& obj) const
    {
        return obj.hash();
    }
};

#endif
