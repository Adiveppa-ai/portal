#ifndef __RWDB_ROWI_H__
#define __RWDB_ROWI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/rowi.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **************************************************************************
 *
 * Declaration of class RWDBRow
 *
 * Provides an object that represents a row from a table.
 *
 **************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/value.h>
#include <rw/ordcltn.h>

static inline bool operator==(const RWDBValue& lhs, const RWDBValue& rhs)
{
    return lhs.isEqual(&rhs);
}


class RWDB_GLOBAL RWDBRowImp
    : public RWDBReference,
      public RWOrdered
{
public:
    RWDBRowImp();
    virtual ~RWDBRowImp();

private:
    RWDBRowImp(const RWDBRowImp& rvalue);
    RWDBRowImp& operator=(const RWDBRowImp& rvalue);
};

#endif
