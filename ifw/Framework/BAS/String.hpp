#ifndef BAS_STRING_HPP
#define BAS_STRING_HPP
// @(#)%Portal Version: String.hpp:RWSmod7.3.1Int:1:2007-Sep-12 04:45:16 %
//==============================================================================
//
// Copyright (c) 1998, 2024, Oracle and/or its affiliates.
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//  Enhanced String class, derived from RWCString.
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//==============================================================================

#include <locale.h>
#ifndef RW_TOOLS_CSTRING_COMPAT_H
  #include <rw/cstring.h>
#endif
#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef RW_TOOLS_LOCALE_H
  #include <rw/locale.h>
#endif
#ifndef RW_TOOLS_DATE_H
  #include <rw/rwdate.h>
#endif
#ifndef RW_TOOLS_TIME_H
  #include <rw/rwtime.h>
#endif
#ifndef RW_TOOLS_RE_H
  #include <rw/re.h>
#endif
#ifndef BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif

//------------------------------------------------------------------------------
// Declaration of useful vector class.
//------------------------------------------------------------------------------
namespace BAS
{
class String;
class StringRange;

/** String list class.
*/
typedef RWTValOrderedVector<String>      StringList;

/** Range list.
*/
typedef RWTValOrderedVector<StringRange> RangeList;

/** String list iterator.
*/
typedef StringList::iterator             StringListIterator;

/** Constant string list iterator.
*/
typedef StringList::const_iterator       StringListConstIterator;

typedef RWCSubString                         SubString;
typedef RWCConstSubString                    ConstSubString;
typedef RWTValOrderedVector<ConstSubString>   ConstSubStringList;

//------------------------------------------------------------------------------
// String declaration
//------------------------------------------------------------------------------

/** <tt><b>String</b></tt> is the basic string class.

    <p>This class is an lightweight enhancement of RogueWave`s 
    <tt><A HREF="http://timos.portal.com/RogueWaveDocumentation/html/toolsref/rwcstring.html">RWCString</A></tt>.
    The enhancements are basically
    <ul>
    <li>the enhanced tokeniser functionality (refer to <tt>split()</tt>methods),
    <li>the formatting methods (inherited from [z-rate]),
    <li>the fast comparison methods (usable for pattern matching).
    </ul>

    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>n/a
        <dt><b>Messages send</b></dt>
        <dd>n/a
      <dt><b>Messages received</b></dt>
        <dd>n/a
      <dt><b>Errors</b></dt>
        <dd>none
    </dl>               
*/
 class String: public RWCString
{
  D_SINGLETHREADED

  public:

    typedef RWCString::stripType padType;

    //--------------------------------------------------------------------------
    /** @name String Constructors and Destructor*/
    //@{ 
    /** Default constructor.
    */
    String();

    /** Copy constructor.
    */
    String(const String& s);

    /** Destructor
     If any data member is added to String (or its subclasses), the
     destructor must be declared virtual.
    */
    ~String();
    //@}

    //--------------------------------------------------------------------------
    /**@name Standard constructors (mirrored from RWCString).
       For further details on these constructors, please refer to the
       corresponding documentation of <tt>RWCString</tt>.
    */
    //@{
    /** Constructor inherited from RWCString.
    */
    String(const RWCString& s);

    /** Constructor inherited from RWCString.
    */
    String(RWSize_T ic);     

    /** Constructor inherited from RWCString.
    */
    String(const char* a);   

    /** Constructor inherited from RWCString.
    */
    String(const char* a, size_t N); 

    /** Constructor inherited from RWCString.
    */
    String(char c);

    /** Constructor inherited from RWCString.
    */
    String(unsigned char c);

    /** Constructor inherited from RWCString.
    */
    String(signed char c);

    /** Constructor inherited from RWCString.
    */
    String(char a, size_t N);

    /** Constructor inherited from RWCString.
    */
    String(const RWCSubString& ss);

#if defined(RWTOOLS) && (RWTOOLS >= 0x07050000) 
    /** Constructor inherited from RWCString.
    */
    String(const RWCConstSubString& ss);
#endif
    //@}
    
    /** @name String assignment operators.
    */
    //@{
    /** Assignment operator.
        @param rVal r-value
    */
    String& operator=(const String& rVal);

    /** Assignment operator (RWCString version).
        @param rVal r-value
    */
    String& operator=(const RWCString& rVal);

    /** Assignment operator (RWCSubString version).
        @param rVal r-value
    */
    String& operator=(const RWCSubString& rVal);

#if defined(RWTOOLS) && (RWTOOLS >= 0x07050000) 
    /** Assignment operator (RWCConstSubString version).
        @param rVal r-value
    */
    String& operator=(const RWCConstSubString& rVal);
#endif

    /** Assignment operator (char* version).
        @param rVal r-value
    */
    String& operator=(const char* rVal);
    //@}

    /**@name Additional String constructor.
    */
    //@{
    /** Constructs a string from a string list. Refer to buildfromList().
        @param list The string list to be concatenated.
        @param separator The concatenation character.
      */
    String(const StringList& list, const char separator = ' ');
    //@}

    /** @name String member comparison operators.
     */
    //@{
    /** equality comparison operator to char* (case sensitive)
        @param str string to compare to
    */

#if defined(RWTOOLS) && (RWTOOLS >= 0x07050000) 
    /** equality comparison operator to RWCConstSubString (case sensitive)
        @param str string to compare to
    */
#endif

    /** equality comparison operator to RWCSubString (case sensitive)
        @param str string to compare to
    */

    /** equality comparison operator to RWCSubString (case sensitive)
        @param str string to compare to
    */

    /** equality comparison operator to String (case sensitive)
        @param str string to compare to
    */

	/** Equality operator comparison to a char
	 */
    /** inequality comparison operator to char* (case sensitive)
        @param str string to compare to
    */
     
#if defined(RWTOOLS) && (RWTOOLS >= 0x07050000)
    /** inequality comparison operator to RWCConstSubString (case sensitive)
       @param str string to compare to
    */
#endif

    /** inequality comparison operator to RWCSubString (case sensitive)
       @param str string to compare to
    */

    /** inequality comparison operator to RWCString (case sensitive)
       @param str string to compare to
    */

    /** inequality comparison operator to String (case sensitive)
        @param str string to compare to
    */

    //@}

    //--------------------------------------------------------------------------
    /**@name Split methods.
       The split methods are used to transform a string into a list of tokens,
       using a splitting separation character.
    */
    //@{
    /** Transforms a string into a list of tokens, using a splitting separation character.
        Returns false if there are less tokens in the string than in
        in the list.
        Looks for whitespace: ' ',\0,\t,\n.
        @param result The list that shall be filled with tokens. The list must have the same
                      length as the expected number of tokens.
        @return <tt>False</tt> if there are less tokens in the string than the list length,
                <tt>true</tt> otherwise.
    */
    bool split(StringList& result) const;

    /** Transforms a string into a list of tokens, using a blank as splitting separation character.
        Creates a new list.
        @return List filled with tokens.
    */
    StringList split() const;
    
    /** Transforms a string into a list of tokens, using a splitting separation character.
        Returns false if there are less tokens in the string than in
        in the list. 
        Looks for whitespace: ' ',\0,\t,\n.
        @param result The list that shall be filled with tokens. The list must have the same
                      length as the expected number of tokens.
        @param splitChar The split character, e.g. "<tt>,</tt>".
        @return <tt>False</tt> if there are less tokens in the string than the list length,
                <tt>true</tt> otherwise.
    */
    bool split(StringList& result, 
               const char      splitChar) const;
    /** Transforms a string into a list of tokens, using a splitting separation character.
	This split variation does not introduce any gratuitous memory allocation or deallocation.
        Returns false if there are less tokens in the string than in
        in the list. 
        Looks for whitespace: ' ',\0,\t,\n.
        @param result The list that shall be filled with substring objects that represent the 
	              tokens. The list must have the same length as the expected number of tokens.
        @param splitChar The split character, e.g. "<tt>,</tt>".
        @return <tt>False</tt> if there are less tokens in the string than the list length,
                <tt>true</tt> otherwise.
    */
    bool split(ConstSubStringList& result, 
               const char      splitChar) const;
    /** Transforms a string into a list of tokens, using a splitting separation character.
        Creates a new list.
        @param splitChar The split character.
        @return List filled with tokens.
    */
    StringList split(const char splitChar) const;
    //@}

    //--------------------------------------------------------------------------
    /**@name Convenience methods*/
    //@{  
    /** Pad method. Possible pad types:
        <ul>
        <li><tt>RWCString::trailing</tt> - Pad characters are appended.
        <li><tt>RWCString::leading</tt> - Pad characters are prepended.
        <li><tt>RWCString::both </tt> - Pad characters are appenden and prepended (even number length needed).
        </ul>
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.
    */
    void oldPad(size_t len, padType = RWCString::trailing, char padChar = ' ');

    /** Pad method. Possible pad types:
        <ul>
        <li><tt>RWCString::trailing</tt> - Pad characters are appended.
        <li><tt>RWCString::leading</tt> - Pad characters are prepended.
        </ul>
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.
    */
    void pad(size_t len, padType = RWCString::trailing, char padChar = ' ');

    /** Fill string with character
     */
    void fill( size_t pos, size_t len, char fillChar );

    /** Setup method.
        Concatenates a string list to a string. 
        @param list The string list that shall be concatenated.
        @param separator The concatenation character.
    */
    void buildFromList(const StringList& list, const char separator = ' ');

    /** Restore the internal representation of self from memory area.
      * @param ptr Pointer to a previously allocated memory area. */
    void binaryRestore(char*& ptr);

    /** Save the internal representation of self to memory area.
      * @param ptr Pointer to a previously allocated memory area. */
    void binarySave(char*& ptr) const;

    /** Returns the number of bytes necessary to store self.
        @return number of bytes for storing self
    */
    u_int64 binaryStoreSize() const;

    /** Comparison method.
        @param s The string to be compared with self.
        @param useWildCard Flag if wildcard characters shall be ignored in the comparison.
        @return <tt>True</tt>: strings match, <tt>false</tt> otherwise.
    */
    bool compare(const RWCString& s, const bool useWildCard = false) const;
    //@}

    //--------------------------------------------------------------------------
    /**@name String conversion methods.
             These methods are implemented using RogueWave's class
             RWLocaleSnaphot.
    */
    //@{
    /** Conversion method.
        @param val The value to be converted.
        @return Reference to self.
    */


    /** Conversion method.
        @param val The value to be converted.
        @return Reference to self.
    */
    const String& convert(const int32 val);

    /** Conversion method.
        @param val The value to be converted.
        @return Reference to self.
    */
    const String& convert(const u_int32 val);

    /** Conversion method (with padding).
        @param val The value to be converted.
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.
        @return Reference to self.
    */

    /** Conversion method.
        @param val The value to be converted.
        @return Reference to self.
    */
    const String& convert(const int64 val);

    /** Conversion method (with padding).
        @param val The value to be converted.
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.
        @return Reference to self.
    */
    const String& convert(const int64 val, size_t len, padType = RWCString::trailing, char padChar = ' ');
                                                                                
    /** Conversion method.
        @param val The value to be converted.
        @return Reference to self.
    */
    const String& convert(const u_int64 val);

    /** Conversion method (with padding).
        @param val The value to be converted.
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.
        @return Reference to self.
    */
    const String& convert(const u_int64 val, size_t len, padType = RWCString::trailing, char padChar = ' ');

    /** Conversion method.
        @param f The value to be converted.
        @return Reference to self.
    */
    const String& convert(const double f, const int32 precision = 6, const bool showPoint = false);

    /** Conversion method.
        @param f The value to be converted.
        @param showNull Enables the output of Decimal::null if set to true, otherwise a '0' is returned.
        @return Reference to self.
    */
    const String& convert(const Decimal& f, 
                              const int32  precision = 6, 
                              const bool showPoint = true,
                              const bool showNull  = true);

    /** Conversion method (with padding).
        @param val The value to be converted.
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.
        @return Reference to self.
    */
    const String& convert(const double val, 
			      size_t len, 
			      const int32 precision = 6, 
                              const bool showPoint = false, 
			      String::padType padType = RWCString::trailing, 
			      char padChar = ' ');

    /** Conversion method (with padding).
        @param val The value to be converted.
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.
        @return Reference to self.
    */
    const String& convert(const Decimal&  d, 
			      size_t              len, 
			      int32                 precision = 6, 
                              bool                showPoint = true, 
                              bool                showNull  = false, 
			      String::padType padType   = RWCString::leading, 
			      char                padChar   = ' ');

    /** Conversion method.
        @param val The value to be converted.
        @return Reference to self.
    */
    const String& convert(const struct tm& val, const char format, const RWZone& zone = RWZone::local());

    /** Conversion method (with padding).
        @param val The value to be converted.
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.  
        @return Reference to self.
    */
    const String& convert(const struct tm& val, const char format, size_t len, 
                 const RWZone& zone = RWZone::local(), padType = RWCString::trailing, char padChar = ' ');

    /** Conversion method.
        @param val The value to be converted.
        @return Reference to self.
    */
    const String& convertMoney(double val, const RWLocale::CurrSymbol s = RWLocale::LOCAL);

    /** Conversion method (with padding).
        @param val The value to be converted.
        @param len The length that shall be padded.
        @param padType The pad type (see above).
        @param padChar The pad character.  
        @return Reference to self.
    */
    const String& convertMoney(double val, size_t len, const RWLocale::CurrSymbol s = RWLocale::LOCAL,
                                   padType = RWCString::trailing, char padChar = ' ');

    /** Conversion method.
        @param d The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toNum(double& d) const;

    /** Conversion method.
        @param l The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toNum(int64& l) const;

    /** Conversion method.
        @param l The conversion result.
        @param pos Start position for conversion
	@param len Length for converion
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toNum(int64& l, size_t pos, size_t len,
               bool checkForDigits = true) const;

   /** Conversion method.
        @param l The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toNum(u_int64& l) const;            

    /** Conversion method.
        @param i The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toNum(int32& i) const;

    /** Conversion method.
        @param i The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toNum(u_int32& i) const;
    /** Conversion method.
        @param t The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toDate(struct tm& t) const;

    /** Conversion method.
        @param t The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toTime(struct tm& t) const;

    /** Conversion method.
        @param d The conversion result.
        @return <tt>True</tt>: conversion succesful,<br><tt>false</tt> otherwise.
    */
    bool toMoney(double& d, const RWLocale::CurrSymbol s = RWLocale::LOCAL) const;

    /** Resole the escape sequences in self. 
        @return Reference to seld
     */
    const String& resolveEscSeq();

    //@}

    //--------------------------------------------------------------------------
    /**@name RWCString build-in replace methods.
    */
    //@{
    String&
    replace(size_t pos, size_t N, const char* cs);

    String&
    replace(size_t pos, size_t N1,const char* cs, size_t N2);

    String&
    replace(size_t pos, size_t N, const RWCString& str);

    String&
    replace(size_t pos, size_t N1,const RWCString& str, size_t N2);

    String&
    replace(size_t pos, size_t N, const std::string& str);

    String&
    replace(size_t pos, size_t N1,const String& str, size_t N2);

    String&
    replace(size_t pos, size_t N1,const std::string& str, size_t N2);

    void
    replace(const RWCRExpr& pattern,
	    const char* replacement, scopeType scope=one);

    void
    replace(const RWCRExpr& pattern, 
	    const RWCString& replacement,scopeType scope=one);

    void
    replace(const RWCRExpr& pattern, 
	    const String& replacement,scopeType scope=one);

    //@}
        
    //--------------------------------------------------------------------------
    /**@name String replace methods.
    */
    //@{


    /** replace method.
      * Possible pad types:
      * <ul>
      * <li><tt>RWCString::trailing</tt> - Pad characters are appended.
      * <li><tt>RWCString::leading</tt> - Pad characters are prepended.
      * </ul>
      * @param value to insert
      * @pos position to start insert
      * @len insert len chars
      * @padType see above
      * @padChar with this character
    */
    void replace( const String& value,
                 size_t pos, 
                 size_t len, 
                 padType = RWCString::trailing,
                 char padChar = ' ' );

    /** replace method.
      * Possible pad types:
      * <ul>
      * <li><tt>RWCString::trailing</tt> - Pad characters are appended.
      * <li><tt>RWCString::leading</tt> - Pad characters are prepended.
      * </ul>
      * @param value to insert
      * @pos position to start replace
      * @len replace len chars
      * @padType see above
      * @padChar with this character
    */
    void replace( const int64 value,
                  size_t pos, 
                  size_t len, 
                  padType = RWCString::leading,
                  char padChar = '0' );

    /** Replace the string totally by a substring.
     *  @param str String from where to extract the substring
     *  @param pos Position of the substring
     *  @param len Length of the substring
     */
    void totReplace( const String& str, size_t pos, size_t len );

    /** replace method.
     *  Possible pad types:
     *  @param value to insert
     *  @pos position to start replace
     */
    void replace( char value, size_t pos );

    /** replace method.
      * Possible pad types:
      * <ul>
      * <li><tt>RWCString::trailing</tt> - Pad characters are appended.
      * <li><tt>RWCString::leading</tt> - Pad characters are prepended.
      * </ul>
      * @param value to insert
      * @pos position to start replace
      * @len replace len chars
      * @precision 
      * @showPoint
      * @padType see above
      * @padChar with this character
    */
    void replace( const double value,
                  size_t pos, 
                  size_t len,
                  const int32 precision = 6,
                  const bool showPoint = false,
                  padType = RWCString::leading,
                  char padChar = '0' );

    /** replace method.
      * Possible pad types:
      * <ul>
      * <li><tt>RWCString::trailing</tt> - Pad characters are appended.
      * <li><tt>RWCString::leading</tt> - Pad characters are prepended.
      * </ul>
      * @param value to insert
      * @pos position to start replace
      * @len replace len chars
      * @precision 
      * @showPoint
      * @showNull
      * @padType see above
      * @padChar with this character
    */
    void replace( const Decimal& value,
                 size_t pos, 
                 size_t len,
                 const int32 precision  = 6,
                 const bool showPoint = true,
                 const bool showNull  = false,
                 padType = RWCString::leading,
                 char padChar = '0' );

    /** Serialze the string
     */
    bool serialize(std::ostream& out) const;

    /** Restore the serialized string
     */
    bool restore(std::istream& in);

    //@}
    
    //--------------------------------------------------------------------------
    /**@name String class methods*/
    //@{
    /** Comparison method.
    */
    static bool compare(const char*  aStr, 
                        const char*  bStr, 
                        const bool   useWildCard = false,
                        const size_t len         = 0);

    /** Comparison method.
    */
    static bool compare(const char*  aStr, 
                        const char*  bStr, 
                        const RangeList& range);

    /** Comparison method to identify the prefix of a string
     *  @param substring to look for at the start of our String
     *  @return <tt>true</tt> on success, <tt>false</tt> otherwise.
     */
    bool startsWith(const RWCString& str)const;
    
    /**
    */
    static RangeList    
		range(const char* str, 
                      const size_t len, 
                      const char   splitChar);

    /**
    */
    static void range(const char*    str, 
                      const size_t   len, 
                      const char     splitChar,
		      RangeList& list);

    /**
    */
    static const char wildCard();

    /**
    */
    static u_int64  hash(const String& s);

    /** Self test method (<em>for internal use only</em>).
        @return <tt>True</tt> if class test was successful, <tt>false</tt> otherwise.
    */
    static bool selfTest();
    //@}

	std::istream& readFile(std::istream& is);

  private:
    //--------------------------------------------------------------------------
    // class members
    //--------------------------------------------------------------------------

    BAS_EXPORT static const char             wildCardCM;
    BAS_EXPORT static const RWLocaleSnapshot localeCM;
#ifdef WIN64
    RWBoolean getStringNumber(const char *&, size_t*) const;
    int32 getStringSign(const char*&) const;
#endif
 };


//------------------------------------------------------------------------------
// StringRange declaration
class StringRange
{
  public:

    //--------------------------------------------------------------------------
    // constructors / destructors
    //--------------------------------------------------------------------------

    StringRange();
    StringRange(const size_t pos, const size_t len);
    StringRange(const StringRange& val);
    ~StringRange();

    //--------------------------------------------------------------------------
    // data access methods
    //--------------------------------------------------------------------------
    
    const size_t pos() const;
    void         pos(const size_t val);

    const size_t len() const;
    void         len(const size_t val);

    //--------------------------------------------------------------------------
    // operators
    //--------------------------------------------------------------------------
    
     const StringRange& operator=(const StringRange& rVal);



  private:
    size_t posM;
    size_t lenM;

    //--------------------------------------------------------------------------
    // friends
    //--------------------------------------------------------------------------
    
    friend std::ostream& operator<<(std::ostream& os, const RangeList& rVal);
};


//------------------------------------------------------------------------------
// Some constants.
//------------------------------------------------------------------------------

BAS_EXPORT extern const String NULL_STRING;     // DO NOT INITIALIZE TO AVOID MUTEX PROBLEM!
BAS_EXPORT extern const String PATH_SEPARATOR;
BAS_EXPORT extern const String FILE_DOT;

const char SPACE_CHAR             = ' ';
const char POINT_CHAR             = '.';
const char PLUS_CHAR              = '+';
const char MINUS_CHAR             = '-';
const char ZERO_CHAR              = '0';
const char TERM_CHAR              = '\0';
const char TAB_CHAR               = '\t';
const char NL_CHAR                = '\n';
const char CR_CHAR                = '\r';

//------------------------------------------------------------------------------
/** String hash functor to be used in collections. Uses the 
    RWCString hash function. 
*/
struct StringHash
{
  u_int64 operator()(const String& x) const { return String::hash(x); }
};

//------------------------------------------------------------------------------
///
std::ostream& operator<<(std::ostream& os, const StringList& rVal);
///
std::ostream& operator<<(std::ostream& os, const RangeList&  rVal);

//------------------------------------------------------------------------------
// Some global comparison functions for String
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// inlines
//------------------------------------------------------------------------------

inline
String::String()
{
}

//-------------------------------------------------------------------------

inline
String::String(const String& s)
           :RWCString(s)
{
}

//-------------------------------------------------------------------------

inline
String::String(const RWCString& s)
           :RWCString(s)
{
}

//-------------------------------------------------------------------------

inline
String::String(RWSize_T ic)
           :RWCString(ic)
{
}

//-------------------------------------------------------------------------

inline
String::String(const char * a)
           :RWCString(a)
{
}

//-------------------------------------------------------------------------

inline
String::String(const char * a, size_t N)
           :RWCString(a, N)
{
}

//-------------------------------------------------------------------------

inline
String::String(char c)
           :RWCString(c)
{
}

//-------------------------------------------------------------------------

inline
String::String(char a, size_t N)
           :RWCString(a, N)
{
}

//-------------------------------------------------------------------------

inline
String::String(unsigned char c)
           :RWCString(c)
{
}

//-------------------------------------------------------------------------

inline
String::String(signed char c)
           :RWCString(c)
{
}

//-------------------------------------------------------------------------

inline
String::String(const RWCSubString& ss)
           :RWCString(ss)
{
}

//-------------------------------------------------------------------------

#if defined(RWTOOLS) && (RWTOOLS >= 0x07050000) 
inline
String::String(const RWCConstSubString& ss)
           :RWCString(ss)
{
}
#endif

//-------------------------------------------------------------------------
 
inline
String::~String()
{
}

//-------------------------------------------------------------------------

inline const char
String::wildCard()
{
  return wildCardCM;
}

//-------------------------------------------------------------------------
 
inline u_int64
String::hash(const String& s)
{
 return s.RWCString::hash();
}

//-------------------------------------------------------------------------

inline
StringRange::StringRange()
                 :posM(0),lenM(0)
{
}

//-------------------------------------------------------------------------

inline
StringRange::StringRange(const size_t pos, const size_t len)
                :posM(pos),lenM(len)
{
}

//-------------------------------------------------------------------------

inline
StringRange::StringRange(const StringRange& val)
{
  *this = val;
}

//-------------------------------------------------------------------------

inline
StringRange::~StringRange()
{
}

//-------------------------------------------------------------------------

inline const size_t 
StringRange::pos() const
{
  return posM;
}

//-------------------------------------------------------------------------

inline void  
StringRange::pos(const size_t val)
{
  posM = val;
}

//-------------------------------------------------------------------------

inline const size_t 
StringRange::len() const
{
  return lenM;
}

//-------------------------------------------------------------------------

inline void  
StringRange::len(const size_t val)
{
  lenM = val;
}

//-------------------------------------------------------------------------

inline const StringRange& 
StringRange::operator=(const StringRange& rVal)
{
  if (this != &rVal)
  {
    posM = rVal.posM;
    lenM = rVal.lenM;
  }

  return rVal;
}

//------------------------------------------------------------------------------
// Restore the internal representation of self from memory area
//------------------------------------------------------------------------------

inline void
String::binaryRestore(char*& ptr)
{
  size_t len;

  memcpy(&len,ptr,sizeof(len));
  ptr += sizeof(len);

  RWCString::replace(0,length(),ptr,len);
  ptr += len;
}

//------------------------------------------------------------------------------
// Save the internal representation of self to memory area
//------------------------------------------------------------------------------

inline void
String::binarySave(char*& ptr) const
{
  size_t len = length();

  memcpy(ptr,&len,sizeof(len));
  ptr += sizeof(len);

  memcpy(ptr,data(),len);
  ptr += len;
}

//------------------------------------------------------------------------------
// Returns the number of bytes necessary to store self
//------------------------------------------------------------------------------

inline u_int64
String::binaryStoreSize() const
{
  return ( sizeof(size_t) + length() );
}

inline const String&
String::convert(const int32 val)
{
  convert(RWSTD_STATIC_CAST(const int64,val));

  return *this;
}

//-------------------------------------------------------------------------

inline const String&
String::convert(const u_int32 val)
{
  convert(RWSTD_STATIC_CAST(const u_int64,val));

  return *this;
}

//-------------------------------------------------------------------------
/*
inline const String&
String::convert(const long l)
{
  *this = localeCM.asString(l);
  return *this;
}
*/
//-------------------------------------------------------------------------
/*
inline const String&
String::convert(const unsigned long l)
{
  *this = localeCM.asString(l);
  return *this;
}
*/
//-------------------------------------------------------------------------

inline const String&
String::convert(const u_int64 val, size_t len, padType t, char padChar)
{
  convert(val);
  pad(len, t, padChar);
  return *this;
}

//-------------------------------------------------------------------------

inline const String&
String::convert(const double f, const int32 precision, const bool showPoint)
{
  *this = localeCM.asString(f, precision, showPoint);
  return *this;
}

//-------------------------------------------------------------------------

inline const String&
String::convert(const Decimal& d, const int32 precision, const bool showPoint, const bool showNull)
{
  d.toString( *this, -1, precision, showPoint, showNull );
  return *this;
}

//-------------------------------------------------------------------------

inline const String&
String::convert(const struct tm& tmbuf, const char format, const RWZone& zone)
{
  *this = localeCM.asString(&tmbuf, format, zone);
  return *this;
}

//-------------------------------------------------------------------------

inline const String&
String::convert(const struct tm& val, const char format, size_t len,
                    const RWZone& zone, padType t, char padChar) 
{
  convert(val, format, zone);
  pad(len, t, padChar);
  return *this;
} 

//-------------------------------------------------------------------------

inline const String&
String::convertMoney(double value, const RWLocale::CurrSymbol s)
{
  *this = localeCM.moneyAsString(value, s);
  return *this;
}

//-------------------------------------------------------------------------

inline const String&
String::convertMoney(double val, size_t len, const RWLocale::CurrSymbol s,
                         padType t, char padChar)
{
  convertMoney(val, s);
  pad(len, t, padChar);
  return *this;
} 
                                                                                       
//-------------------------------------------------------------------------

inline bool
String::toNum(double& d) const
{
  return localeCM.stringToNum(*this, &d);
}

//-------------------------------------------------------------------------

inline bool
String::toNum(int64& l) const
{
  // use long internally, as RWLocale::stringToNum() only support long.
  long tmp = 0;

  if (localeCM.stringToNum(*this, &tmp))
  {
      l = tmp;
      return true;
  }

  return false;
}

//-------------------------------------------------------------------------

inline bool
String::toDate(struct tm& t) const
{
  return localeCM.stringToDate(*this, &t);
}

//-------------------------------------------------------------------------

inline bool
String::toTime(struct tm& t) const
{
  return localeCM.stringToTime(*this, &t);
}
                                                      
//-------------------------------------------------------------------------

inline bool
String::toMoney(double& d, const RWLocale::CurrSymbol s) const
{
  return localeCM.stringToMoney(*this, &d, s);
}

//-------------------------------------------------------------------------

inline String& 
String::operator=(const String& rVal)
{
  RWCString::operator=(rVal);
  return *this;
}

//-------------------------------------------------------------------------               

inline String&
String::operator=(const RWCString& rVal)
{
  RWCString::operator=(rVal);
  return *this;
}

//-------------------------------------------------------------------------               
inline String&
String::operator=(const RWCSubString& rVal)
{
  RWCString::operator=(RWCString(rVal));
  return *this;
}

//-------------------------------------------------------------------------               
#if defined(RWTOOLS) && (RWTOOLS >= 0x07050000) 
inline String&
String::operator=(const RWCConstSubString& rVal)
{
  RWCString::operator=(RWCString(rVal));
  return *this;
}
#endif

//-------------------------------------------------------------------------               
inline String&
String::operator=(const char* rVal)
{
  RWCString::operator=(rVal);
  return *this;
}

//-------------------------------------------------------------------------
inline String&
String::replace(size_t pos, size_t N, const char* cs)
{
  RWCString::replace(pos, N, cs, strlen(cs));
  return *this;
}

//-------------------------------------------------------------------------
inline String&
String::replace(size_t pos, size_t N1,const char* cs, size_t N2)
{
  RWCString::replace(pos, N1, cs, N2);
  return *this;
}

//-------------------------------------------------------------------------
inline String&
String::replace(size_t pos, size_t N, const RWCString& str)
{
  RWCString::replace(pos, N, str.data(), str.length());
  return *this;
}

//-------------------------------------------------------------------------
inline String&
String::replace(size_t pos, size_t N1,const RWCString& str, size_t N2)
{
  RWCString::replace(pos, N1, str.data(), N2);
  return *this;
}

//-------------------------------------------------------------------------
inline String&
String::replace(size_t pos, size_t N, const std::string& str)
{
  RWCString::replace(pos, N, str);
  return *this;
}

//-------------------------------------------------------------------------

inline String&
String::replace(size_t pos, size_t N1, const String& str, size_t N2)
{
  RWCString::replace(pos, N1, str.data(), N2);
  return *this;
}

//-------------------------------------------------------------------------

inline String&
String::replace(size_t pos, size_t N1, const std::string& str, size_t N2)
{
  RWCString::replace(pos, N1, str, N2);
  return *this;
}

//-------------------------------------------------------------------------

inline void
String::replace(const RWCRExpr& pattern,
                const char* replacement,
                scopeType scope)
{
  RWCString::replace(pattern, replacement, scope);
}

//-------------------------------------------------------------------------

inline void
String::replace(const RWCRExpr& pattern, 
                const RWCString& replacement,
                scopeType scope)
{
  RWCString::replace(pattern, replacement, scope);
}

//-------------------------------------------------------------------------

inline void
String::replace(const RWCRExpr& pattern, 
                const String& replacement,
                scopeType scope)
{
  RWCString::replace(pattern, replacement, scope);
}


//-------------------------------------------------------------------------
inline void 
String::replace( char value, size_t pos )
{
  RWPRECONDITION( length() >= pos + 1 );
  
  replace( pos, 1, &value, 1 );
}

//-------------------------------------------------------------------------
inline bool 
String::startsWith(const RWCString& str) const
{
  if (strncmp(str.data(), this->data(), str.length()) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//-------------------------------------------------------------------------
inline bool 
toDecimal(ConstSubString &str, Decimal& dec)
{
  dec = Decimal(str.data(), str.length());
  return dec.isNumber();
}

//-------------------------------------------------------------------------
inline bool 
toInt(ConstSubString &str, int64& l)
{
  Decimal dec(str.data(), str.length());
  bool isdec = dec.isNumber();
  if (isdec) {
    l = toInt(dec);
  }
  return isdec;
}
}
#endif // BAS_STRING_HPP
