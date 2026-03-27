#ifndef rw_mime_RWMimeParseError_h_
#define rw_mime_RWMimeParseError_h_

/******************************************************************************
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
 * $Id: //spro/rel2016.1/rw/mime/RWMimeParseError.h#1 $
 ******************************************************************************/

#include <rw/mime/RWMimeError.h>
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Reports the failure to successfully parse a MIME header.
 *
 * The MIME package throws RWMimeParseError when asked to parse a string
 * which is not valid MIME.
 */
class RW_MIME_GLOBAL RWMimeParseError : public RWMimeError
{
public:
    /**
     * Constructs an RWMimeParseError with the message \a msg.
     */
    RWMimeParseError(const RWCString& msg);

    /**
     * \internal
     *
     * Constructs a RWMimeParseError with the given message.
     */
    RWMimeParseError(const RWMessage& msg);

    /**
     * Destructor.
     */
    virtual ~RWMimeParseError(void);
};

extern RW_MIME_SYMBOLIC void RWThrow(const RWMimeParseError&);

#endif // rw_mime_RWMimeParseError_h_
