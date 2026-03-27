#ifndef RW_CURRENCY_ATTRIO_H
#define RW_CURRENCY_ATTRIO_H

/************************************************************************
 *
 * File:  attrio.h
 *
 * Declarations for the class RWAttributeReader.
 *
 * $Id: //spro/rel2016.1/rw/currency/attrio.h#1 $
 *
 * Copyright (c) 1993-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 ************************************************************************/

/* for backward compatibility */
#ifndef RW_MONEY_ATTRIO_H
#  define RW_MONEY_ATTRIO_H
#endif

#include <rw/dcmldefs.h>
#include <rw/cstring.h>
#include <rw/tvslist.h>
#include <istream>

//
// RWEAttributeReader:  Reads attribute name/value pairs from an istream.
//  Parses values as booleans, words, lists of words, or arbitrary strings.
//
class RWEAttributeReader
{

public:

    // converts a string to a word, word list, or boolean
    static RWCString toWord(const RWCString& str);
    static RWTValSlist<RWCString> toWordList(const RWCString& str);
    static bool toBoolean(const RWCString& str);

    // creates an attribute reader that'll parse the given istream
    RWEAttributeReader(std::istream& is, const RWCString& nameValueSepartors = RWCString());

    // advances to next attribute; returns false at eof
    bool next(void);

    // returns name of current attribute
    inline RWCString getName(void) const;

    // return value of current attribute, in one of four forms
    inline RWCString getStringValue(void) const;
    inline RWCString getWordValue(void) const;
    inline RWTValSlist<RWCString> getWordListValue(void) const;
    inline bool getBooleanValue(void) const;

private:
    static const char* delimiters_;

    size_t findQuote(size_t start = 0);

    std::istream& is_;
    RWCString nameValueSeparators_;
    RWCString name_;
    RWCString value_;
};

//
// RWEAttributeReader::getName:  Returns name of current attribute.
//
inline RWCString
RWEAttributeReader::getName(void) const
{
    return name_;
} // RWEAttributeReader::getName

//
// RWEAttributeReader::getStringValue:  Returns the value of the current
//  attribute as an arbitrary string.  This string may contain embedded
//  whitespace, including newlines.
//
inline RWCString
RWEAttributeReader::getStringValue(void) const
{
    return value_;
} // RWEAttributeReader::getStringValue

//
// RWEAttributeReader::getWordValue:  Returns the value of the current
//  attribute as a single word.  This word will not contain whitespace.
//
inline RWCString
RWEAttributeReader::getWordValue(void) const
{
    return toWord(value_);
} // RWEAttributeReader::getWordValue

//
// RWEAttributeReader::getWordListValue:  Returns the value of the current
//  attribute as a series of words.  No word will contain whitespace.
//
inline RWTValSlist<RWCString>
RWEAttributeReader::getWordListValue(void) const
{
    return toWordList(value_);
} // RWEAttributeReader::getWordListValue

//
// RWEAttributeReader::getBooleanValue:  Returns the value of the current
//  attribute as a boolean.  If the first character of the string is a 'y',
//  'Y', 't', 'T', or '1', true is returned.  Otherwise, false is returned.
//
inline bool
RWEAttributeReader::getBooleanValue(void) const
{
    return toBoolean(value_);
} // RWEAttributeReader::getBooleanValue

#endif // RW_CURRENCY_ATTRIO_H
