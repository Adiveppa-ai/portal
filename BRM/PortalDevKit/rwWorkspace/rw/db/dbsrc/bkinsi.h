#ifndef __RWDB_BKINSI_H__
#define __RWDB_BKINSI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/bkinsi.h#1 $
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
 * RWDBBulkInserterImp Interface
 *
 **************************************************************************/

#ifdef _MSC_VER
#  pragma warning( disable : 4251)
#endif

#include <rw/db/connect.h>
#include <rw/db/osql.h>
#include <rw/db/table.h>
#include <rw/tvdlist.h>

class RWDB_GLOBAL RWDBBulkInserterImp
    : public RWDBReference
    , public RWDBStatus
{
public:
    RWDBBulkInserterImp(const RWDBStatus& stat,
                        const RWDBTable& tb,
                        const RWDBConnection& conn);
    virtual ~RWDBBulkInserterImp();

    /**
     * \internal
     *
     * Returns the current position, at which the next value will be shifted
     * in using the insertion operator.
     */
    size_t position() const;

    void position(size_t index);
    void position(const RWCString& columnName);

    void shiftIn(const RWDBAbstractBuffer& buffer);

    virtual RWDBResultImp* execute(size_t iters);

    virtual RWCString asString();

    class ShiftedElement
    {
        RWCString name_;
        RWDBAbstractBuffer* buffer_;
    public:
        ShiftedElement() : name_(""), buffer_(0) { }
        ShiftedElement(const RWCString& name, RWDBAbstractBuffer* buffer)
            : name_(name), buffer_(buffer) { }

        // SPDB-4964
        RWCString& name()
        {
            return RW_EXPOSE(name_);
        }

        RWDBAbstractBuffer* buffer()
        {
            return buffer_;
        }

        bool operator==(const ShiftedElement& rhs) const
        {
            return this == &rhs;
        }
        bool operator<(const ShiftedElement& rhs) const
        {
            return this < &rhs;
        }
    };

protected:
    RWDBConnection         connection_;
    RWDBTable              table_;
    RWDBOSql               osql_;
    RWTValDlist<ShiftedElement> buffers_;
    size_t                 position_;
    bool              changed_;

private:
    RWDBBulkInserterImp(const RWDBBulkInserterImp&);
    RWDBBulkInserterImp& operator=(const RWDBBulkInserterImp&);
};


#endif
