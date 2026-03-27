#ifndef __RWDB_STMTI_H__
#define __RWDB_STMTI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/stmti.h#1 $
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
 * Definition of RWDBStatementImp
 *
 **************************************************************************/

#ifdef _MSC_VER
#  pragma warning( disable : 4251)
#endif

#include <rw/db/dbsrc/stmt.h>
#include <rw/db/dbref.h>
#include <rw/db/multirow.h>
#include <rw/db/osql.h>
#include <rw/db/phrase.h>
#include <rw/db/status.h>
#include <rw/wstring.h>


//////////////////////////////////////////////////////////////////////////
//
// class RWDBStatementImp
//
//////////////////////////////////////////////////////////////////////////

class RWDB_GLOBAL RWDBStatementImp
    : public RWDBReference,
      public RWDBStatus
{
public:

    RWDBStatementImp(const RWDBStatus& status,
                     RWDBOSql::StatementType type = RWDBOSql::Query);
    virtual ~RWDBStatementImp();

    // Statement stuff
    virtual void         cancel(const RWDBConnection&, RWDBStatus&,
                                bool changed = 0);
    virtual void         parse(const RWCString&, const RWDBConnection&,
                               RWDBStatus&);
    virtual void         bind(const RWDBConnection&, RWDBStatus&);
    virtual RWDBResult   perform(const RWDBConnection&, RWDBStatus&);
    virtual RWDBResult   perform(const RWDBConnection&, size_t, RWDBStatus&);
    virtual void         clear(const RWDBConnection&, RWDBStatus&);

    virtual RWDBValue    returnValue() const;
    virtual RWDBStatus   fetchReturnParams();

    virtual RWCString    addBoundBuffer(RWDBAbstractBuffer* buffer,
                                        bool ownerShip = false);

    virtual void         clearBoundObjects(void);
    virtual size_t       entries() const;

    virtual RWCString    newPlaceHolder(void);

    virtual RWDBStatement::PlaceHolderFlag
    needsPlaceHolder(const RWDBValue&) const;
    virtual RWDBStatement::PlaceHolderFlag
    needsPlaceHolder(RWDBValue::ValueType,
                     void* data) const;

    RWDBMultiRow&        boundBuffers();
    RWDBOSql&            osql();
    virtual const RWDBPhraseBook& phraseBook() const;

protected:
    RWDBOSql  osql_;
    RWCString sql_;
    unsigned long        currentPlaceHolder_;
    RWDBOSql::StatementType statementType_;

private:
    // not implemented
    RWDBStatementImp(const RWDBStatementImp&);
    RWDBStatementImp& operator=(const RWDBStatementImp&);
};


#endif
