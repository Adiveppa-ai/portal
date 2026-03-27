#ifndef __RWDB_DELETERI_H__
#define __RWDB_DELETERI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/deleteri.h#1 $
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

#include <rw/db/dbsrc/stmt.h>
#include <rw/db/connect.h>
#include <rw/db/dbref.h>
#include <rw/db/expr.h>
#include <rw/db/status.h>
#include <rw/db/table.h>


//////////////////////////////////////////////////////////////////////////
//
// RWDBDeleterImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBDeleterImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    RWDBDeleterImp(const RWDBStatus& status);
    RWDBDeleterImp(const RWDBStatus& status,
                   const RWDBTable&    table,
                   const RWDBCriterion& criterion,
                   const RWDBStatement& = RWDBStatement(),
                   bool useTableTags = false);

    virtual ~RWDBDeleterImp();

    // accessors and mutators
    virtual RWDBTable     table() const;
    virtual RWDBCriterion where();
    virtual void          where(const RWDBCriterion& criterion);

    // multithreading functions
    void          acquire() const;
    void          release() const;

    // for SQL expansion
    virtual RWCString     asString(const RWZone& timeZone,
                                   bool verbose = false);
    virtual const RWDBPhraseBook&   phraseBook() const;

    // for execution
    virtual RWDBResult    execute(const RWDBConnection& connection);
    virtual void          cancel(const RWDBConnection& conn,
                                 RWDBStatus&     status);
    virtual void          parse(const RWDBConnection& conn,
                                RWDBStatus&     status);
    virtual void          bind(const RWDBConnection& conn,
                               RWDBStatus&     status);
    virtual RWDBResult    perform(const RWDBConnection& conn,
                                  RWDBStatus&     status);
    virtual RWDBStatus    clear();

    virtual RWDBStatementImp* statement() const;

protected:
    // multithreading data
    RWDBLocalRecursiveMutex     mutex_;
    // Members
    RWDBTable                   table_;
    RWDBCriterion               criterion_;
    RWCString                   sql_;
    RWDBStatement               statement_;
    bool                   changed_;

    // indicates support of table tags
    bool                   useTableTags_;

private:
    RWDBConnection              conn_;

    // Do not dereference. RWZone it points may have been destructed.
    const RWZone*               lastExecZone_;

private:
    // not implemented
    RWDBDeleterImp(const RWDBDeleterImp& deleter);
    RWDBDeleterImp&      operator=(const RWDBDeleterImp& deleter);
};

#endif
