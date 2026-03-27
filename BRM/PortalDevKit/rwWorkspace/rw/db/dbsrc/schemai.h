#ifndef __RWDB_SCHEMAI_H__
#define __RWDB_SCHEMAI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/schemai.h#1 $
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
 * Definition of class RWDBSchemaImp, the reference-counted implementation
 * of class RWDBSchema.
 * A schema is implemented as an RWOrdered (collection) of collectable
 * RWDBColumns.  Class RWDBCollectableColumn is defined here as well.
 *
 * Note: this is NOT a base class for database-specific variants.
 *
 **************************************************************************/

#include <rw/db/checkconstr.h>
#include <rw/db/column.h>
#include <rw/db/dbref.h>
#include <rw/db/forkey.h>
#include <rw/db/schema.h>
#include <rw/db/status.h>
#include <rw/db/uniqueconstr.h>
#include <rw/tools/pointer.h>

//////////////////////////////////////////////////////////////////////////
//
// RWDBSchemaImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBSchemaImp
    : public RWOrdered,  public RWDBReference,  public RWDBStatus
{
public:

    RWDBSchemaImp(const RWDBStatus&);

    virtual ~RWDBSchemaImp();

    virtual RWDBSchemaImp*    clone() const;  // for deep copies

    // multithreading functions
    void                      acquire() const;
    void                      release() const;

    virtual RWDBColumn        column(size_t) const;
    virtual RWDBColumn        column(const RWCString& name,
                                     RWCString::caseCompare cc) const;
    virtual RWCString         columnName(size_t) const;

    virtual size_t            locate(const RWCString& name,
                                     RWCString::caseCompare cc) const;

    virtual RWDBColumn        appendColumn(const RWCString& name,
                                           RWDBValue::ValueType type,
                                           long storageLength,
                                           int nativeType,
                                           int precision,
                                           int scale,
                                           bool nullAllowed,
                                           RWDBColumn::ParamType paramType);
    virtual RWDBColumn        appendColumn(const RWDBColumn&);
    virtual RWDBColumn        prependColumn(const RWDBColumn&);
    virtual RWCString         keysAsString(const RWDBPhraseBook& pb) const;
    virtual RWCString         uniqueConstraintsAsString(const RWDBPhraseBook& pb) const;
    virtual RWCString         checkConstraintsAsString(const RWDBPhraseBook& pb) const;
    virtual RWCString         asString(const RWDBPhraseBook& pb) const;

    virtual void              foreignKey(const RWDBForeignKey& fk);

    virtual void              primaryKey(const RWDBPrimaryKey& pk);
    virtual RWDBPrimaryKey    primaryKey() const;

    virtual void              checkConstraint(const RWDBCheckConstraint& cc);
    virtual void              uniqueConstraint(const RWDBUniqueConstraint& cc);

    // collectable API
    virtual RWspace  binaryStoreSize() const;
    virtual void     saveGuts(RWFile& file) const;
    virtual void     saveGuts(RWvostream& stream) const;
    virtual void     restoreGuts(RWFile& file);
    virtual void     restoreGuts(RWvistream& stream);

private:
    RWDBLocalRecursiveMutex          mutex_;

    RWDBCheckConstraintList          ccList_;
    RWDBUniqueConstraintList         uList_;
    RWDBForeignKeyList               fkList_;
    RWTScopedPointer<RWDBPrimaryKey> pkPtr_;

    // not implemented:
    RWDBSchemaImp& operator=(const RWDBSchemaImp& impl);
    RWDBSchemaImp(const RWDBSchemaImp& impl);
    RWDBSchemaImp();
};

//////////////////////////////////////////////////////////////////////////
//
// RWDBCollectableColumn
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBCollectableColumn : public RWCollectable, public RWDBColumn
{
    RW_DECLARE_COLLECTABLE_CLASS(RWDB_SYMBOLIC, RWDBCollectableColumn)

public:
    RWDBCollectableColumn()
    {}

    RWDBCollectableColumn(const RWDBColumn& c);
    virtual ~RWDBCollectableColumn();

    virtual int      compareTo(const RWCollectable* v) const;
    virtual bool     isEqual(const RWCollectable* v) const;

    virtual RWspace  binaryStoreSize() const;
    virtual unsigned hash() const;
    virtual void     saveGuts(RWFile& f) const;
    virtual void     saveGuts(RWvostream& s) const;
    virtual void     restoreGuts(RWFile& f);
    virtual void     restoreGuts(RWvistream& s);
};

#endif
