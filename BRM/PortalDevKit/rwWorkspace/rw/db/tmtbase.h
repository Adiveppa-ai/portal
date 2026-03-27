#ifndef __RWDB_TMTBASE_H__
#define __RWDB_TMTBASE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/tmtbase.h#1 $
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
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/table.h>

/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * Abstract base class for the derived class RWDBTPtrMemTable.
 *
 * An abstract base class for the derived class RWDBTPtrMemTable.
 */
class RWDB_GLOBAL RWDBTMemTableBase : public RWDBTable
{
public:
    RWDBTMemTableBase(const RWDBStatus& stat, size_t size);
    RWDBTMemTableBase(size_t size);

    /**
     * This routine uses the RWDBReader instance \a reader to allocate and
     * append to the memory table instances of \c T. It is the application's
     * responsibility to free the memory associated with the table.
     */
    bool populate(RWDBReader& reader);

protected:
    virtual bool readRow(RWDBReader& reader) = 0;

    size_t maxAllowedSize_;
};


#endif
