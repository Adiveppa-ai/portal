#ifndef __RWDB_CURSORI_H__
#define __RWDB_CURSORI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/cursori.h#1 $
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

#include <rw/db/dbsrc/taggen.h>
#include <rw/db/connect.h>
#include <rw/db/cursor.h>
#include <rw/db/dbref.h>
#include <rw/db/inserter.h>
#include <rw/db/multirow.h>
#include <rw/db/osql.h>
#include <rw/db/schema.h>
#include <rw/db/status.h>
#include <rw/db/tbuffer.h>

//////////////////////////////////////////////////////////////////////////
//
// RWDBCursorImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBCursorImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    // constructors, destructor
    RWDBCursorImp(const RWDBStatus& status);
    RWDBCursorImp(const RWDBStatus&         status,
                  RWDBCursor::CursorType    type,
                  RWDBCursor::CursorAccess  access,
                  const RWCString&          select,
                  const RWDBMultiRow&       inboundBuffers,
                  const RWDBSchema&         updateCols,
                  const RWDBConnection&     connection);
    virtual ~RWDBCursorImp();

    // accessors
    virtual RWCString                   name() const;
    virtual RWDBCursor::CursorType      type() const;
    virtual RWDBCursor::CursorAccess    access() const;
    virtual RWDBConnection              connection() const;
    virtual RWDBSchema                  schema() const;

    // multithreading operations
    void                acquire() const;
    void                release() const;

    // cursor operations
    virtual RWDBStatus          fetchRow(RWDBCursor::CursorPosition position,
                                         int offset);
    virtual RWDBStatus          updateRow(const RWCString& tableName);
    virtual RWDBStatus          deleteRow(const RWCString& tableName);
    virtual RWDBStatus          insertRow(const RWCString& tableName);

    // support for RWDBCursor::operator<< and []
    void appendValue(RWDBValue::ValueType type, RWDBValueManip manip);

    /**
     * \internal
     *
     * Adds buffer \a value at the current insertion position.
     */
    template <class T>
    void appendBuffer(T* value);

    /**
     * \internal
     *
     * Adds buffer \a value at the current insertion position taking into
     * account the storage length of the respective column from self's
     * schema.
     */
    template <class T>
    void appendVariableLengthBuffer(T* value);

    virtual RWDBStatus          setPosition(size_t columnPosition);
    virtual RWDBStatus          setPosition(const RWCString& columnName);

    /**
     * \internal
     *
     * Returns the current position, at which the next value will be shifted
     * in using the insertion operator.
     */
    virtual size_t              position() const;

    // utilities
    virtual RWDBStatus          unbind();
    virtual bool           isNull(size_t colPosition);
    virtual void                setNull(size_t colPosition);
    virtual void                unsetNull(size_t colPosition);

protected:
    // open the cursor
    virtual void                open();

    /**
     * \internal
     *
     * Checks self's state to ensure a new buffer binding can be supported.
     * Returns \c true if new buffer can be bound, otherwise returns
     * \c false and sets error on self's status.
     */
    bool readyToAppendValue();

    /**
     * \internal
     *
     * Sets an application binding \a theBinding for a specific column at
     * \a index.
     *
     * \note
     * Self is responsible for deleting \a theBinding.
     */
    virtual void setApplicationBinding(size_t index, RWDBAbstractBuffer* theBinding);

    // Create an insert string.
    virtual void prepareInsert(const RWCString& tableName);

    // multithreading data
    RWDBLocalRecursiveMutex     mutex_;
    // Other Members
    RWCString                   name_;
    RWDBCursor::CursorType      type_;
    RWDBCursor::CursorAccess    access_;
    RWDBConnection              connection_;

    // schema of cursor, updateable columns marked as in type parameters.
    RWDBSchema                  schema_;

    RWDBSchema                  updateCols_; // deprecated.

    // Current column pointed to
    size_t currentColumn_;

    // RWDBOSql for the cursor
    RWDBOSql osql_;

    // The input bindings for the statement.
    RWDBMultiRow inboundBuffers_;

    // RWDBOSql for an insert statement
    RWDBInserter inserter_;

    // The RWDBHandle used for executing the osql_.
    // We make our own as we want a handle tailored for cursors
    //   (see the constructor's initializer list!)
    RWDBHandle handle_;

    // true if we haven't performed the first fetch
    bool haventYetFetched_;

    RWDBTagGenerator&           tagGenerator();

private:
    // not implemented
    RWDBCursorImp(const RWDBCursorImp& cursor);
    RWDBCursorImp&              operator=(const RWDBCursorImp& cursor);
};

template <class T>
void
RWDBCursorImp::appendBuffer(T* value)
{
    if (readyToAppendValue()) {
        setApplicationBinding(currentColumn_, new RWDBTBuffer<T>(value));
        currentColumn_++;
    }
}

template <class T>
void
RWDBCursorImp::appendVariableLengthBuffer(T* value)
{
    if (readyToAppendValue()) {
        long storageLength = schema_[currentColumn_].storageLength();
        storageLength = (storageLength == RWDB_NO_TRAIT ? 0 : storageLength);
        setApplicationBinding(currentColumn_,
                              new RWDBTBuffer<T>(value, 1, static_cast<size_t>(storageLength)));
        currentColumn_++;
    }
}

#endif
