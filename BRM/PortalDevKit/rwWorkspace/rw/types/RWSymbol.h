#ifndef rw_types_RWSymbol_h_
#define rw_types_RWSymbol_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/types/RWSymbol.h#1 $
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

#include <rw/types/pkgdefs.h>  // load all common global, product, and package specific defs
#include <rw/pointer/RWHandleBase.h>
#include <rw/rstream.h> // includes STL or old streams, as appropriate
#include <rw/wstring.h>


class RWSymbolBody;

//--Author Skander Slama
//--Package Types


/**
 * \ingroup types_package
 *
 * \brief
 * Encapsulates a string name in a reference-counted handle-body pattern.
 *
 * Class RWSymbol is the only API class in the Types package.
 *
 * It encapsulates a string name in a reference-counted handle-body pattern.
 * Therefore, several RWSymbol objects can reference one string name, making
 * storage space smaller, name memory management easier, and name
 * comparisons faster.
 *
 * The strings are stored internally as wide characters (\c wchar_t).
 * Members are provided to construct symbols from US-ASCII or wide
 * characters.
 *
 * RWSymbol objects can be streamed across the network, to files, and to
 * standard input and output. The genSymbol() static member allows you to
 * create unique symbols from a name.
 *
 * RWSymbol inherits a highly efficient operator==() from RWHandleBase.
 * RWHandleBase::operator==() returns \c true or \c false based on whether
 * the two RWHandleBase objects point to the same body instance.
 */
class RW_TYPES_SYMBOLIC RWSymbol : public RWHandleBase
{
public:

    /**
     * Creates an empty or unbound RWSymbol.
     */
    RWSymbol();

    /**
     * Creates a symbol for the string \a name. The string is treated as a
     * sequence of US-ASCII characters and internally converted and stored
     * as a sequence of wide characters. This constructor is not intended to
     * be used with multibyte character strings (MBCS).
     */
    RWSymbol(const char* name);

    /**
     * Creates a symbol for the string \a name of wide characters.
     */
    RWSymbol(const wchar_t* name);

    /**
     * Copy constructor. Constructed object references the same string name
     * as \a sym.
     */
    RWSymbol(const RWSymbol& sym);

    /**
     * Destroys the symbol. If it is the last reference to a given name, the
     * internal storage associated with it is deallocated.
     */
    ~RWSymbol();

    /**
     * Returns the name of the RWSymbol as an RWWString.
     */
    RWWString             asWCharString() const;

    /**
     * Converts the symbol's name from the internal wide character
     * representation to US-ASCII and returns it as an RWCString.
     */
    RWCString             asAsciiString() const;

    /**
     * Returns \c true if the symbol has been bound to a name.
     */
    bool             isBound() const;

    /**
     * Returns an unsigned value from the hash function for the symbol.
     */
    unsigned              hash() const;

    /**
     * Supplied for sorting of symbols. Compares address locations of string
     * names referenced by self and \a rhs.
     */
    bool             operator<(const RWSymbol& rhs) const;

    //--Supplied for sorting of symbols.  Compares address locations.
    bool             operator>(const RWSymbol& rhs) const;

    /**
     * Returns an \c int less than, greater than, or equal to zero,
     * according to the result of calling the function \c "::wcscoll()" on
     * self and the symbol supplied as \a rhs. This supports
     * locale-dependent collation.
     */
    int                   collate(const RWSymbol& rhs) const;

    /**
     * Returns an unsigned from the hash function for the symbol.
     */
    static unsigned       hash(const RWSymbol& key);

    /**
     * Creates a new RWSymbol with a unique manufactured name. The symbol
     * name consists of \a prefix followed by an incremented process-global
     * count. The wide character \a prefix can be set. Therefore, by
     * default, the first generated symbol would be G1, the second G2, and
     * so on.
     */
    static RWSymbol       genSymbol(const RWWString& prefix = L"G");

    /**
     * Creates a new RWSymbol with a uniquely manufactured name. The symbol
     * name consists of the US-ASCII \a prefix followed by an incremented
     * process-global count.
     */
    static RWSymbol       genSymbol(const RWCString& prefix);

    /**
     * Streams an input stream \a strm, as US-ASCII, into a symbol \a sym.
     */
    friend RW_TYPES_SYMBOLIC std::istream& operator>>(std::istream& strm,
            RWSymbol& sym);

    /**
     * Streams a symbol \a sym, as US-ASCII, into an output stream \a strm.
     */
    friend RW_TYPES_SYMBOLIC std::ostream& operator<<(std::ostream& strm,
            const RWSymbol& sym);

#if 0
    /**
     * Streams a wide character input stream \a strm into a symbol \a sym.
     */
    friend std::wcistream& operator>>(std::wcistream& strm,
                                      RWSymbol& sym);

    /**
     * Streams a symbol \a sym, as wide characters, into a wide character
     * output stream \a strm.
     */
    friend std::wcostream& operator<<(std::wcostream& strm,
                                      const RWSymbol& sym);
#endif

    /**
     * Streams an RWvistream \a vstrm into a symbol \a sym.
     */
    friend RW_TYPES_SYMBOLIC RWvistream& operator>>(RWvistream& vstrm,
            RWSymbol& sym);

    /**
     * Streams a symbol \a sym into an RWvostream \a vstrm.
     */
    friend RW_TYPES_SYMBOLIC RWvostream& operator<<(RWvostream& vstrm,
            const RWSymbol& sym);

    friend class RWObjectInputStreamImp;
    friend class RWObjectOutputStreamImp;

protected:
    RWSymbol(RWSymbolBody* body);         // used by streamers
    RWSymbolBody* getBody(void) const;
    static unsigned long genSeqNum(void); // generates next sequence number
};


inline
RWSymbolBody*
RWSymbol::getBody(void) const
{
    return reinterpret_cast<RWSymbolBody*>(&(*body_));
}

#endif // rw_types_RWSymbol_h_
