#ifndef RW_CURRENCY_NAMEVAL_H
#define RW_CURRENCY_NAMEVAL_H

/***************************************************************************
 *
 * File:  nameval.h
 *
 * Declarations for the class RWAttributeBlockReader and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/nameval.h#1 $
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
 **************************************************************************/

/* for backward compatibility */
#ifndef RW_MONEY_NAMEVAL_H
#  define RW_MONEY_NAMEVAL_H
#endif

#include <rw/cstring.h>
#include <rw/rstream.h>
#include <rw/tvslist.h>

struct RWNameValuePair {
    RWCString name_;
    RWCString value_;
};

bool operator==(const RWNameValuePair& a, const RWNameValuePair& b);
bool operator<(const RWNameValuePair& a, const RWNameValuePair& b);


class RWAttributeBlockReader
{
public:
    enum Status { error, endOfFile };

    RWAttributeBlockReader(std::istream& strm, const RWCString& beginToken,
                           const RWCString& endToken = RWCString(), char commentChar = '#');

    RWCString beginToken() const
    {
        return beginToken_;
    }
    RWCString endToken() const
    {
        return endToken_;
    }
    char      commentChar() const
    {
        return commentChar_;
    }
    Status    status() const
    {
        return status_;
    }
    RWTValSlist<RWNameValuePair> nameValueBlock() const
    {
        return currentValue_;
    }

    void setBeginToken(const RWCString& b)
    {
        beginToken_ = b;
    }
    void setEndToken(const RWCString& e)
    {
        endToken_ = e;
    }
    void setCommentChar(char c)
    {
        commentChar_ = c;
    }
    bool next();

private:
    std::istream&  strm_;
    RWCString beginToken_;
    RWCString endToken_;
    char      commentChar_;
    Status    status_;

    RWTValSlist<RWNameValuePair> currentValue_;

    bool setCurrentValue(const RWCString&);
};

#endif // RW_CURRENCY_NAMEVAL_H
