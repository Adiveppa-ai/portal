#ifndef __RWDB_SHIFTROW_H__
#define __RWDB_SHIFTROW_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/shiftrow.h#1 $
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
 * Declaration  of class RWDBShiftableRow
 *
 **************************************************************************/

#include <rw/db/row.h>
#include <rw/db/value.h>


class RWDB_GLOBAL RWDBShiftableRow : public RWDBRow
{
public:
    RWDBShiftableRow();

    virtual size_t          shiftInPosition();
    virtual size_t          shiftOutPosition();
    virtual void            shiftInPosition(size_t pos);
    virtual void            shiftOutPosition(size_t pos);
    virtual void            append(const RWDBValue&);

    RWDBShiftableRow&       operator>>(RWDBNullIndicator& aNullIndictator);
    RWDBShiftableRow&       operator>>(char& aVal);
    RWDBShiftableRow&       operator>>(unsigned char& aVal);
    RWDBShiftableRow&       operator>>(short& aVal);
    RWDBShiftableRow&       operator>>(unsigned short& aVal);
    RWDBShiftableRow&       operator>>(int& aVal);
    RWDBShiftableRow&       operator>>(unsigned int& aVal);
    RWDBShiftableRow&       operator>>(long& aVal);
    RWDBShiftableRow&       operator>>(unsigned long& aVal);
    RWDBShiftableRow&       operator>>(long long& aVal);
    RWDBShiftableRow&       operator>>(unsigned long long& aVal);
    RWDBShiftableRow&       operator>>(float& aVal);
    RWDBShiftableRow&       operator>>(double& aVal);
    RWDBShiftableRow&       operator>>(long double& aVal);
    RWDBShiftableRow&       operator>>(RWDecimalPortable& aVal);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    RWDBShiftableRow&       operator>>(RWTime& aVal);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    RWDBShiftableRow&       operator>>(RWDate& aVal);
    RWDBShiftableRow&       operator>>(RWDateTime& aVal);
    RWDBShiftableRow&       operator>>(RWTimeTuple& aVal);
    RWDBShiftableRow&       operator>>(RWTimeTupleOffset& aVal);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    RWDBShiftableRow&       operator>>(RWDBDateTime& aVal);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    RWDBShiftableRow&       operator>>(RWDBDuration& aVal);
    RWDBShiftableRow&       operator>>(RWCString& aVal);
    RWDBShiftableRow&       operator>>(RWDBBlob& aVal);
    RWDBShiftableRow&       operator>>(RWDBValue& aVal);
    RWDBShiftableRow&       operator>>(RWDBMBString& aVal);
    RWDBShiftableRow&       operator>>(RWBasicUString& aVal);
    RWDBShiftableRow&       operator>>(RWWString& aVal);

    bool               checkBounds() const;
    bool               checkConversion(RWDBValue::ValueType aType,
                                       size_t pos) const;

private:
    size_t                  shiftInPosition_;
    size_t                  shiftOutPosition_;

    // Not implemented
    RWDBShiftableRow(const RWDBShiftableRow&);
    RWDBShiftableRow& operator=(const RWDBShiftableRow&);
};

#endif
