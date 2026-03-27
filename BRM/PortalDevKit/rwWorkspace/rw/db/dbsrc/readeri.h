#ifndef __RWDB_READERI_H__
#define __RWDB_READERI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/readeri.h#1 $
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
 * Declaration of class RWDBReaderImp, the base class for a family of
 * database-specific reader implementations
 *
 **************************************************************************/

#include <rw/db/dbsrc/rwdbbufferfactory.h>
#include <rw/db/dbsrc/shiftrow.h>
#include <rw/db/connect.h>
#include <rw/db/dbref.h>
#include <rw/db/mbstring.h>
#include <rw/db/multirow.h>
#include <rw/db/osql.h>
#include <rw/db/status.h>
#include <rw/db/table.h>
#include <rw/tools/bustring.h>
#include <rw/wstring.h>

class RWDB_GLOBAL RWDBReaderImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    RWDBReaderImp(const RWDBStatus&     status);
    RWDBReaderImp(const RWDBStatus&     status,
                  const RWDBTable&      table,
                  const RWDBConnection& connection);
    RWDBReaderImp(const RWDBStatus&     status,
                  const RWDBTable&      table,
                  const RWDBConnection& connection,
                  RWDBOSql&       osql,
                  size_t          currentResult,
                  size_t          cacheSize);

    virtual                    ~RWDBReaderImp();

    // Used by RWDBReader for error checking:
    bool                   checkBounds(const RWDBShiftableRow& r,
                                       const char* where);
    bool                   checkConversion(const RWDBShiftableRow& r,
                                           RWDBValue::ValueType t);

    // This group is forwarded by RWDBReader.
    virtual RWDBStatus          status();
    virtual void*               operator()();
    virtual RWDBTable           table();
    virtual RWDBConnection      connection();

    // multithreading functions
    void                acquire() const;
    void                release() const;

    virtual RWDBReaderImp&      operator>>(RWDBNullIndicator& aNullIndictator);

    virtual RWDBReaderImp&      operator>>(RWDBRow& aRow);
    virtual RWDBReaderImp&      operator>>(char& value);
    virtual RWDBReaderImp&      operator>>(unsigned char& value);
    virtual RWDBReaderImp&      operator>>(short& value);
    virtual RWDBReaderImp&      operator>>(unsigned short& value);
    virtual RWDBReaderImp&      operator>>(int& value);
    virtual RWDBReaderImp&      operator>>(unsigned int& value);
    virtual RWDBReaderImp&      operator>>(long& value);
    virtual RWDBReaderImp&      operator>>(unsigned long& value);
    virtual RWDBReaderImp&      operator>>(long long& value);
    virtual RWDBReaderImp&      operator>>(unsigned long long& value);
    virtual RWDBReaderImp&      operator>>(float& value);
    virtual RWDBReaderImp&      operator>>(double& value);
    virtual RWDBReaderImp&      operator>>(long double& value);
    virtual RWDBReaderImp&      operator>>(RWDecimalPortable& value);
    virtual RWDBReaderImp&      operator>>(RWDate& value);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    virtual RWDBReaderImp&      operator>>(RWTime& value);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    virtual RWDBReaderImp&      operator>>(RWDateTime& value);
    virtual RWDBReaderImp&      operator>>(RWTimeTuple& value);
    virtual RWDBReaderImp&      operator>>(RWTimeTupleOffset& value);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    virtual RWDBReaderImp&      operator>>(RWDBDateTime& value);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    virtual RWDBReaderImp&      operator>>(RWDBDuration& value);
    virtual RWDBReaderImp&      operator>>(RWCString& value);
    virtual RWDBReaderImp&      operator>>(RWDBBlob& value);
    virtual RWDBReaderImp&      operator>>(RWDBValue& value);
    virtual RWDBReaderImp&      operator>>(RWDBMBString& value);
    virtual RWDBReaderImp&      operator>>(RWBasicUString& value);
    virtual RWDBReaderImp&      operator>>(RWWString& value);

    virtual size_t              shiftInPosition();
    virtual size_t              setShiftInPosition(size_t pos);
    virtual size_t              shiftOutPosition();
    virtual void                setShiftOutPosition(size_t pos);
    virtual void                setShiftOutPosition(const RWCString& value);
    virtual void                setShiftOutPosition(const RWDBColumn& value);
    virtual RWDBShiftableRow&   currentRow();

protected:
    virtual bool           fetchRow(RWDBShiftableRow* valueList);
    virtual RWDBBufferFactory&  factory() const;
    virtual size_t              defaultCacheSize() const;

    // multithreading data
    RWDBLocalRecursiveMutex     mutex_;
    // Members
    RWDBTable                   table_;
    RWDBConnection              connection_;
    RWDBOSql                    osql_;
    RWDBShiftableRow            valueList_;  // List of RWDBValues.

    RWDBMultiRow                multirow_;
    long                        readPosition_;
    long                        lastFetched_;
    bool                   fetchedBefore_;

    size_t                      currentResult_;
    size_t                      cacheSize_;

private:
    // Not implemented
    RWDBReaderImp(const RWDBReaderImp&);
    RWDBReaderImp& operator=(const RWDBReaderImp&);
};


class RWDB_GLOBAL RWDBMemReaderImp : public RWDBReaderImp
{
public:
    RWDBMemReaderImp(const RWDBTable&   table,
                     const RWDBStatus&  status);
    virtual ~RWDBMemReaderImp();

protected:
    virtual bool          fetchRow(RWDBShiftableRow* row);
    size_t                     rowEntry_;

private:
    // Not implemented
    RWDBMemReaderImp(const RWDBMemReaderImp&);
    RWDBMemReaderImp& operator=(const RWDBMemReaderImp);
};

#endif
