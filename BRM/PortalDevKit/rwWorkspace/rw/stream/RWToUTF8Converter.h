#ifndef rw_stream_RWToUTF8Converter_h_
#define rw_stream_RWToUTF8Converter_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWToUTF8Converter.h#1 $
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
 * Converts UTF-16 values to UTF-8.
 *
 * RWToUTF8Converter converts #RWUChar, RWWString, \c wchar_t or
 * \c std::wstring UTF-16 values to UTF-8. The character or string to be
 * converted must encoded in UTF-16. To translate other encodings, use
 * converters supplied by the Internationalization Module.
 */
class RW_STREAM_SYMBOLIC RWToUTF8Converter
{
public:
    /**
     * Converts one UTF-16 #RWUChar to a UTF-8 encoded RWCString.
     *
     * \param from
     * contains the UTF-16 character to convert.
     *
     * \param to
     * returns the resulting UTF-8 string
     */
    void convert(RWUChar from, RWCString& to);

    //--
    //-- Convert several UTF16 RWUChars to a UTF8 encoded RWCString
    //--
    //-- Parameter 'from' contains the UTF16 string to convert
    //-- Parameter 'to' returns the resulting UTF8 string
    //--
    /**
     * Converts several UTF-16 #RWUChar to a UTF-8 encoded RWCString.
     */
    void convert(const RWUChar* from, size_t len, RWCString& to);

    /**
     * Converts one UTF-16 \c wchar_t to a UTF-8 encoded RWCString.
     */
    void convert(wchar_t from, RWCString& to);

    //--
    //-- Convert several UTF16 wchar_t's to a UTF8 encoded RWCString
    //--
    //-- Parameter 'from' contains the UTF16 character to convert
    //-- Parameter 'to' returns the resulting UTF8 string
    //--
    /**
     * Converts several UTF-16 \c wchar_t's to a UTF-8 encoded RWCString.
     */
    void convert(const wchar_t* from, size_t len, RWCString& to);

    //--
    //-- Convert a UTF16 RWWString to a UTF8 encoded RWCString
    //--
    //-- Parameter 'from' contains the UTF16 character to convert
    //-- Parameter 'to' returns the resulting UTF8 string
    //--
    /**
     * Converts a UTF-16 RWWString to a UTF-8 encoded RWCString.
     */
    void convert(const RWWString& from, RWCString& to);

    //--
    //-- Convert a UTF16 std::wstring to a UTF8 encoded RWCString
    //--
    //-- Parameter 'from' contains the UTF16 character to convert
    //-- Parameter 'to' returns the resulting UTF8 string
    //--
#ifndef RW_NO_STD_WSTRING
    /**
     * Converts a UTF-16 \c std::wstring to a UTF-8 encoded RWCString.
     */
    void convert(const std::wstring& from, RWCString& to);

#endif
};

inline void RWToUTF8Converter::convert(wchar_t from, RWCString& to)
{
    convert(static_cast<RWUChar>(from), to);
}

inline void RWToUTF8Converter::convert(const RWWString& from, RWCString& to)
{
    convert(from.data(), from.length(), to);
}

#ifndef RW_NO_STD_WSTRING
inline void RWToUTF8Converter::convert(const std::wstring& from, RWCString& to)
{
    convert(from.data(), from.length(), to);
}
#endif

#endif // rw_stream_RWToUTF8Converter_h_
