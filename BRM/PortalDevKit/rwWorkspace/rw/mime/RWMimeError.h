#ifndef rw_mime_RWMimeError_h_
#define rw_mime_RWMimeError_h_

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
 * $Id: //spro/rel2016.1/rw/mime/RWMimeError.h#1 $
 ******************************************************************************/

#include <rw/mime/pkgdefs.h>     // every class needs this
#include <rw/cstring.h>
#include <rw/rwerr.h>            // RWxmsg

/**
 * \ingroup mime_package
 *
 * \brief
 * Base class for the heirarchy of exceptions in the MIME package.
 *
 * RWMimeError is the base class for the heirarchy of exceptions in the MIME
 * package. The MIME package throws RWMimeError when it is unable to perform
 * an operation.
 */
class RW_MIME_GLOBAL RWMimeError : public RWxmsg
{
public:
    /**
     * Constructs an RWMimeError with the message \a msg.
     */
    RWMimeError(const RWCString& msg);

    /**
     * \internal
     *
     * Constructs a RWMimeError with the given message.
     */
    RWMimeError(const RWMessage& msg);

    /**
     * Destructor.
     */
    virtual ~RWMimeError(void);
};

extern RW_MIME_SYMBOLIC void RWThrow(const RWMimeError&);

#endif // rw_mime_RWMimeError_h_
