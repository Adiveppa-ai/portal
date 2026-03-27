#ifndef __RWDB_BKREADI_H__
#define __RWDB_BKREADI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/bkreadi.h#1 $
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
 * RWDBBulkReaderImp Interface
 *
 **************************************************************************/

#ifdef _MSC_VER
#  pragma warning( disable : 4251)
#endif

#include <rw/db/bindable.h>
#include <rw/db/connect.h>
#include <rw/db/osql.h>
#include <rw/db/select.h>
#include <rw/db/table.h>
#include <rw/tpdlist.h>

class RWDB_GLOBAL RWDBBulkReaderImp
    : public RWDBReference
    , public RWDBStatus
{
public:
    RWDBBulkReaderImp(const RWDBStatus& status,
                      const RWDBSelector& selector,
                      const RWDBConnection& conn);

    RWDBBulkReaderImp(const RWDBStatus& status,
                      const RWDBTable& table,
                      const RWDBConnection& conn,
                      const RWDBOSql& osql,
                      size_t currentResult);

    virtual ~RWDBBulkReaderImp();

    void position(size_t index);
    size_t position() const;

    void shiftIn(RWDBAbstractBuffer& buffer);

    size_t    operator()();
    bool cancel();

protected:
    RWDBTable                      table_;
    RWDBSelector                   selector_;
    RWDBConnection                 connection_;
    RWTPtrDlist<RWDBAbstractBuffer> buffers_;
    RWDBOSql                       osql_;
    size_t                         position_;
    size_t                         numberOfColumns_;
    size_t                         currentResult_;
    bool                      fetched_;


private:
    RWDBBulkReaderImp(const RWDBBulkReaderImp&);
    RWDBBulkReaderImp& operator=(const RWDBBulkReaderImp&);
};


#endif
