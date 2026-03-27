#ifndef __RWDB_SELECTI_H__
#define __RWDB_SELECTI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/selecti.h#1 $
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

#include <rw/db/dbsrc/stmti.h>
#include <rw/db/connect.h>
#include <rw/db/cursor.h>
#include <rw/db/dbase.h>
#include <rw/db/dbref.h>
#include <rw/db/expr.h>
#include <rw/db/schema.h>
#include <rw/db/select.h>
#include <rw/ordcltn.h>


class RWDB_GLOBAL RWDBSelectorBaseImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    RWDBSelectorBaseImp(const RWDBStatus& status);
    RWDBSelectorBaseImp(const RWDBStatus& status,
                        const RWDBDatabase& db,
                        const RWDBStatement& = RWDBStatement());
    virtual ~RWDBSelectorBaseImp();

    virtual RWDBCompoundSelectorImp* compoundSelectorImp(
        const RWDBSelectorBase&,
        RWDBPhraseBook::RWDBPhraseKey,
        const RWDBSelectorBase&);

    virtual RWCString  asString(const RWDBPhraseBook&,
                                const RWZone& timeZone,
                                RWDBStatementImp* stmt = 0,
                                bool clearStmt = true,
                                bool verbose = false) const;

    // accessors
    virtual RWDBDatabase            database() const;
    virtual const RWDBPhraseBook&   phraseBook() const;
    virtual RWDBSchema              schema() const;

    virtual RWDBColumn              column(size_t position) const;
    virtual RWDBColumn              column(const RWCString& name) const;
    virtual RWDBColumn              column(const RWCString& name,
                                           RWCString::caseCompare caseCompare) const;

    virtual RWDBResult          execute(const RWDBConnection&);
    virtual void                cancel(const RWDBConnection&, RWDBStatus&);
    virtual void                parse(const RWDBConnection&, RWDBStatus&);
    virtual void                bind(const RWDBConnection&, RWDBStatus&);
    virtual RWDBResult          perform(const RWDBConnection&, RWDBStatus&);
    virtual RWDBStatus          clear();
    virtual RWDBStatementImp*   statement() const;
    RWDBMultiRow&       boundBuffers();
    virtual bool  fetchSchema(const RWDBConnection& connection);

    virtual void orderBy(const RWDBColumn& column,
                         RWDBSelectorBase::OrderByDirection direction);
    virtual void orderBy(int columnNumber,
                         RWDBSelectorBase::OrderByDirection direction);
    virtual void orderBy(const RWDBExpr& expr,
                         RWDBSelectorBase::OrderByDirection direction);
    virtual void orderByClear();

    virtual RWDBReaderImp* readerImp(const RWDBConnection&, size_t cacheSize);

    virtual RWDBBulkReaderImp* bulkReaderImp(const RWDBConnection&);

    virtual RWDBCursorImp* cursorImp(const RWDBConnection&    connection,
                                     RWDBCursor::CursorType   type,
                                     RWDBCursor::CursorAccess access);
    virtual RWDBCursorImp* cursorImp(const RWDBSchema&        updateCols,
                                     const RWDBConnection&    connection,
                                     RWDBCursor::CursorType   type,
                                     RWDBCursor::CursorAccess access);

protected:
    RWOrdered       orderBy_;
    RWCString       sql_;
    bool       changed_;
    RWDBSchema      schema_;

    RWDBStatement   statement_;
    RWDBDatabase    database_;
    RWDBConnection  conn_;

    // Do not dereference. RWZone it points may have been destructed.
    const RWZone*   lastExecZone_;

private:
    //not implemented
    RWDBSelectorBaseImp(const RWDBSelectorBaseImp&);
    RWDBSelectorBaseImp& operator=(const RWDBSelectorBaseImp&);
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBSelectorImp : public RWDBSelectorBaseImp
{
public:
    RWDBSelectorImp(const RWDBStatus& status);
    RWDBSelectorImp(const RWDBStatus& status, const RWDBDatabase& db,
                    const RWDBCriterion& crit,
                    const RWDBStatement& = RWDBStatement());
    virtual ~RWDBSelectorImp();

    virtual RWCString asString(const RWDBPhraseBook&,
                               const RWZone& timeZone,
                               RWDBStatementImp* stmt = 0,
                               bool cleatStmt = true,
                               bool verbose = false) const;

    virtual RWDBCriterion where() const;

    virtual RWDBStatus clear();

    virtual void select(const RWDBExpr& expr);
    virtual void selectClear();
    virtual void where(const RWDBCriterion& criterion);
    virtual void into(const RWCString& name);
    virtual void having(const RWDBCriterion& criterion);
    virtual void groupBy(const RWDBColumn& column);
    virtual void groupBy(const RWDBExpr& expr);
    virtual void groupBy(int columnNumber);
    virtual void groupByClear();
    virtual void distinct(bool = true);
    virtual void from(const RWCString&);
    virtual void from(const RWDBTable&);
    virtual void from(const RWDBJoinExpr&);
    virtual void fromClear();

    // Gets and sets the from clause generation mechanism.
    virtual void fromGeneration(RWDBSelector::FromGeneration flag);
    virtual RWDBSelector::FromGeneration fromGeneration() const;

    // Defines certain tables to be external to this query.
    // These tables are not included in the from clause.
    virtual void fromExtern(const RWDBTable& table);
    virtual void fromExternClear();


    // ON and USING clauses to attach join criterion and join column list.
    // BOTH THESE METHODS ARE DEPRECATED.
    virtual void on(const RWDBColumn& joinColumn);
    virtual void on(const RWDBCriterion& joinCriterion);

protected:
    RWOrdered       selectList_;
    RWOrdered       fromList_;
    RWOrdered       fromExternList_; // list of tables extern to this SELECT

    RWDBSelector::FromGeneration fromGen_; // FROM clause generation mechanism

    bool       outerJoin_;

    // Controls outer join syntax
    /* Following 2 protected attributes should    **
     * be removed when the deprecated ON methods **
     * on RWDBSelector and RWDBSelectorImp are   **
     * removed.                                  **
     * ie: joinColumnList_ and joinCriterion_    **
     *                                           **
     */

    RWOrdered       joinColumnList_;
    RWDBCriterion   joinCriterion_;

    RWDBCriterion   where_;

    RWCString       into_;
    RWOrdered       groupBy_;
    RWDBCriterion   having_;
    bool       distinct_;

    //Production redefinitions
    virtual RWDBBulkReaderImp* bulkReaderImp(const RWDBConnection&);
private:
    // Not implemented
    RWDBSelectorImp(const RWDBSelectorImp&);
    RWDBSelectorImp& operator=(const RWDBSelectorImp&);

};

#endif
