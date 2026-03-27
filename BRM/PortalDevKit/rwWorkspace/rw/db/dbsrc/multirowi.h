#ifndef __RWDB_MULTIROWI_H__
#define __RWDB_MULTIROWI_H__

/*************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/multirowi.h#1 $
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
 * Declaration of class RWDBMultiRowImp
 *
 * Provides an object that represents a generic buffer list.
 *
 *************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/multirow.h>
#include <rw/db/row.h>
#include <rw/db/schema.h>
#include <rw/tpdlist.h>

class RWDB_GLOBAL RWDBMultiRowImp
    : public RWDBReference
{
public:
    RWDBMultiRowImp();
    RWDBMultiRowImp(const RWDBSchema& schema,
                    size_t numberOfRows,
                    const RWDBBufferFactory& factory);
    ~RWDBMultiRowImp();

    RWDBRow operator[](size_t index) const;

    RWDBAbstractBuffer& bufferAt(size_t index) const;

    void append(RWDBAbstractBuffer* item, bool ownership);
    void replaceAt(size_t index, RWDBAbstractBuffer* newBuffer,
                   bool ownership);
    void clear();

    size_t numberOfColumns() const;
    size_t entries() const;

    RWDBSchema schema() const;

    void extract(size_t index, RWDBRow& row);

    void sync(RWDBAdapterFactory& f, size_t entries);
    void syncOutputParams(RWDBAdapterFactory& f, size_t entries);
    bool update(RWDBAdapterFactory& f, RWDBTracer& t,
                size_t bulksize, const RWZone& timeZone);

private:
    class BufferElement
    {
    public:
        BufferElement(RWDBAbstractBuffer* buffer, bool ownership);
        ~BufferElement();
        RWDBAbstractBuffer* buffer() const;

        bool operator==(const BufferElement& rhs) const
        {
            return this == &rhs;
        }
        bool operator<(const BufferElement& rhs) const
        {
            return this < &rhs;
        }
    private:
        RWDBAbstractBuffer* buffer_;
        bool           ownership_;

        // disable copy
        BufferElement(const BufferElement&);
        BufferElement& operator=(const BufferElement&);
    };

    RWDBSchema                        schema_;
    RWTPtrDlist<BufferElement>        bufferList_;
    size_t                            minimumEntries_;

    RWDBMultiRowImp(const RWDBMultiRowImp& mr);
    RWDBMultiRowImp& operator=(const RWDBMultiRowImp& mr);
};

#endif // __RWDB_MULTIROWI_H__
