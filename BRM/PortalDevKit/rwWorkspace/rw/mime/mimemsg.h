#if !defined(rw_mime_mimemsg_h_)
#define rw_mime_mimemsg_h_

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/mimemsg.h#1 $
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
 *************************************************************************/

#include <rw/mime/pkgdefs.h>
#include <rw/message.h>

// CHANGE THIS FILE ONLY IN CONJUNCTION WITH mimemsg.cpp

#define RW_MIME_INVALID_HEADER_CONVERSION        rwmime_INVALID_HEADER_CONVERSION()
#define RW_MIME_INVALID_TYPE_CONVERSION          rwmime_INVALID_TYPE_CONVERSION()
#define RW_MIME_INVALID_MULTIPART_CONVERSION     rwmime_INVALID_MULTIPART_CONVERSION()
#define RW_MIME_KNOWN_HEADER_TYPE                rwmime_KNOWN_HEADER_TYPE()
#define RW_MIME_MISSING_TYPE_SEPARATOR           rwmime_MISSING_TYPE_SEPARATOR()
#define RW_MIME_MISSING_HEADER_SEPARATOR         rwmime_MISSING_HEADER_SEPARATOR()
#define RW_MIME_MISSING_HEADER_BODY_SEPARATOR    rwmime_MISSING_HEADER_BODY_SEPARATOR()
#define RW_MIME_MISSING_PARAMETER_SEPARATOR      rwmime_MISSING_PARAMETER_SEPARATOR()
#define RW_MIME_MISSING_HEADER                   rwmime_MISSING_HEADER()
#define RW_MIME_MISSING_BOUNDARY_PARAMETER       rwmime_MISSING_BOUNDARY_PARAMETER()
#define RW_MIME_MISSING_BOUNDARY                 rwmime_MISSING_BOUNDARY()
#define RW_MIME_UNKNOWN_ENCODING                 rwmime_UNKNOWN_ENCODING()
#define RW_MIME_INVALID_BASE64_CHAR              rwmime_INVALID_BASE64_CHAR()
#define RW_MIME_INVALID_VERSION                  rwmime_INVALID_VERSION()
#define RW_MIME_INVALID_LABEL                    rwmime_INVALID_LABEL()
#define RW_MIME_INVALID_TOKEN                    rwmime_INVALID_TOKEN()
#define RW_MIME_INVALID_VALUE                    rwmime_INVALID_VALUE()
#define RW_MIME_INVALID_CHARSET                  rwmime_INVALID_CHARSET()

extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_HEADER_CONVERSION;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_TYPE_CONVERSION;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_MULTIPART_CONVERSION;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_KNOWN_HEADER_TYPE;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_MISSING_TYPE_SEPARATOR;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_MISSING_HEADER_SEPARATOR;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_MISSING_HEADER_BODY_SEPARATOR;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_MISSING_PARAMETER_SEPARATOR;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_MISSING_HEADER;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_MISSING_BOUNDARY_PARAMETER;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_MISSING_BOUNDARY;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_UNKNOWN_ENCODING;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_BASE64_CHAR;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_VERSION;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_LABEL;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_TOKEN;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_VALUE;
extern RW_MIME_SYMBOLIC RWMsgId RW_MIME_INVALID_CHARSET;

#endif // rw_mime_mimemsg_h_
