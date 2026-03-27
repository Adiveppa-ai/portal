#ifndef rw_xmlabstractions_RWXmlParseError_h_
#define rw_xmlabstractions_RWXmlParseError_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlParseError.h#1 $
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

#include <rw/xmlabstractions/RWXmlDomainError.h>  // Xml error space
#include <rw/xmlabstractions/pkgdefs.h>     // every class needs this
#include <rw/message.h>             // use RWMessage for i18n purposes
#include <stdexcept>                // standard exception hierarchy

/******************************************************************************
 *
 * RWXmlParseError will be thrown when a parse error occurs while parsing a
 * XML document. It indicates the XML document being parsed is ill-formed in
 * some respect.
 *
 * It inherits from RWXmlDomainError.
 *
 ******************************************************************************/

class RW_XMLABSTRACTIONS_GLOBAL RWXmlParseError : public RWXmlDomainError
{

public:

    RWXmlParseError(const RWCString& msg, const RWCString& srcFile = RWCString(),
                    size_t lineNumber = 0, size_t columnNumber = 0);
    RWXmlParseError(const RWMessage&, const RWCString& srcFile = RWCString(),
                    size_t lineNumber = 0, size_t columnNumber = 0);
    virtual ~RWXmlParseError() RW_NO_THROW;

    /**
     * Return the source file name that caused this error. If none is
     * available returns an empty string
     */
    inline RWCString          getSourceFile() const;

    /**
     * Set the name of the source file that caused this error
     */
    inline void               setSourceFile(const RWCString& fileName);

    /**
     * Return the line number of the source that resulted in this error If
     * none is available return 0
     */
    inline size_t             getLineNumber() const;

    /**
     * Set the line number of the source that caused the error
     */
    inline void               setLineNumber(size_t lineNumber);

    /**
     * Return the column number of the source that resulted in this error If
     * none is available return 0
     */
    inline size_t             getColumnNumber() const;

    /**
     * Set the column number of the source that caused the error
     */
    inline void               setColumnNumber(size_t columnNumber);

private :

    RWCString      srcFile_;
    size_t         lineNumber_;
    size_t         columnNumber_;

};

extern RW_XMLABSTRACTIONS_GLOBAL void RWThrow(const RWXmlParseError&);


inline RWCString
RWXmlParseError::getSourceFile() const
{
    return srcFile_;
}

inline void
RWXmlParseError::setSourceFile(const RWCString& fileName)
{
    srcFile_ = fileName;
}

inline size_t
RWXmlParseError::getLineNumber() const
{
    return lineNumber_;
}

inline void
RWXmlParseError::setLineNumber(size_t lineNumber)
{
    lineNumber_ = lineNumber;
}

inline size_t
RWXmlParseError::getColumnNumber() const
{
    return columnNumber_;
}

inline void
RWXmlParseError::setColumnNumber(size_t columnNumber)
{
    columnNumber_ = columnNumber;
}

#endif // rw_xmlabstractions_RWXmlParseError_h_
