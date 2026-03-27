#ifndef rw_stream_RWFromUTF8Converter_h_
#define rw_stream_RWFromUTF8Converter_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWFromUTF8Converter.h#1 $
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

#include <rw/stream/RWUTF8Helper.h>
#include <rw/stream/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/wstring.h>
#include <string>

/**
 * \ingroup streams_package
 *
 * \brief
 * Converts \c char, RWCString or \b std::string UTF-8 values to UTF-16.
 *
 * RWFromUTF8Converter converts \c char, RWCString or \b std::string UTF-8
 * values to UTF-16. The character or string to be converted must be encoded
 * in UTF-8. To translate other encodings, use converters supplied by the
 * Internationalization Module. All characters or strings must contain
 * complete UTF-8 characters. Partial encodings will result in the converter
 * throwing an RWExternalStreamException.
 */
class RW_STREAM_SYMBOLIC RWFromUTF8Converter
{
public:

    /**
     * Converts a single byte UTF-8 char to UTF-16 encoded RWUChar.
     *
     * \param from
     * contains the UTF-8 character to convert
     *
     * \param to
     * returns the resulting UTF-16 character
     */
    void convert(char from, RWUChar& to);

    //--
    //-- Convert a single byte UTF8 char to UT16 encoded wchar_t
    //--
    //-- Parameter 'from' contains the UTF8 character to convert
    //-- Parameter 'to' returns the resulting UTF16 character
    //--
    /**
     * Converts a single byte UTF-8 char to UTF-16 encoded \c wchar_t.
     */
    void convert(char from, wchar_t& to);

    //--
    //-- Convert a single byte UTF8 char to a UT16 encoded RWWString
    //--
    //-- Parameter 'from' contains the UTF8 character to convert
    //-- Parameter 'to' returns the resulting UTF16 character
    //--
    /**
     * Converts a single byte UTF-8 char to a UTF-16 encoded RWWString.
     */
    void convert(char from, RWWString& to);

    //--
    //-- Convert one or more UTF8 chars to a UT16 encoded RWWString
    //--
    //-- Parameter 'from' contains the UTF8 character(s) to convert
    //-- Parameter 'to' returns the resulting UTF16 character(s)
    //--
    /**
     * Converts one or more UTF-8 chars to a UTF-16 encoded RWWString.
     */
    void convert(const char* from, size_t len, RWWString& to);

    //--
    //-- Convert a UTF8 encoded RWCString to a UT16 encoded RWWString
    //--
    //-- Parameter 'from' contains the UTF8 string to convert
    //-- Parameter 'to' returns the resulting UTF16 string
    //--
    /**
     * Converts a UTF-8 encoded RWCString to a UTF-16 encoded RWWString.
     */
    void convert(const RWCString& from, RWWString& to);

    //--
    //-- Convert a UTF8 encoded std::string to a UT16 encoded RWWString
    //--
    //-- Parameter 'from' contains the UTF8 string to convert
    //-- Parameter 'to' returns the resulting UTF16 string
    //--
    /**
     * Converts a UTF-8 encoded \c std::string to a UTF-16 encoded
     * RWWString.
     */
    void convert(const std::string& from, RWWString& to);
};


inline void RWFromUTF8Converter::convert(const RWCString& from, RWWString& to)
{
    convert(from.data(), from.length(), to);
}


inline void RWFromUTF8Converter::convert(const std::string& from, RWWString& to)
{
    convert(from.data(), from.length(), to);
}

#endif // rw_stream_RWFromUTF8Converter_h_
