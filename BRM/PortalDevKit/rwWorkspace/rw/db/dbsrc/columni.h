#ifndef __RWDB_COLUMNI_H__
#define __RWDB_COLUMNI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/columni.h#1 $
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

#include <rw/db/column.h>
#include <rw/db/dbref.h>
#include <rw/db/expr.h>
#include <rw/db/identity.h>
#include <rw/db/status.h>
#include <rw/db/table.h>

//////////////////////////////////////////////////////////////////////////
//
// RWDBColumnImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBColumnImp
    : public RWDBReference
    , public RWDBStatus
{
public:
    RWDBColumnImp(const RWDBStatus& status);
    RWDBColumnImp(const RWDBStatus&, const RWCString&,
                  RWDBValue::ValueType = RWDBValue::NoType,
                  int = RWDB_NO_TRAIT,
                  long = RWDB_NO_TRAIT,
                  int = RWDB_NO_TRAIT,
                  int = RWDB_NO_TRAIT,
                  bool = true,
                  RWDBColumn::ParamType = RWDBColumn::notAParameter,
                  int = RWDB_NO_TRAIT,
                  const RWDBExpr* const = 0);

    virtual ~RWDBColumnImp();

    virtual RWCString             name() const;
    virtual RWCString             qualifiedName() const;
    virtual bool                  nullAllowed() const;
    virtual RWDBValue::ValueType  type() const;
    virtual int                   nativeType() const;
    virtual int                   auxiliaryType() const;
    virtual long                  storageLength() const;
    virtual int                   precision() const;
    virtual int                   scale() const;
    virtual RWDBColumn::ParamType paramType() const;
    virtual RWDBTable             table() const;
    virtual RWDBExpr              defaultValue() const;
    virtual bool                  hasDefault() const;
    virtual RWDBIdentityConstraint getIdentity() const;

    virtual void                  defaultValue(const RWDBExpr&);
    virtual void                  setIdentity(const RWDBIdentityConstraint&);
    virtual void                  name(const RWCString&);
    virtual void                  nullAllowed(bool);
    virtual void                  type(RWDBValue::ValueType);
    virtual void                  nativeType(int);
    virtual void                  auxiliaryType(int);
    virtual void                  storageLength(long);
    virtual void                  precision(int);
    virtual void                  scale(int);
    virtual void                  paramType(RWDBColumn::ParamType);
    virtual void                  table(const RWDBTable&);
    virtual void                  clearTable();

    // multithreading functions
    void                  acquire() const;
    void                  release() const;

    // undocumented methods to allow the cache manager to be persisted.
    void saveGuts(RWFile& f) const;
    void restoreGuts(RWFile& f);

    void saveGuts(RWvostream& s) const;
    void restoreGuts(RWvistream& s);

private:
    RWCString                   name_ ;
    // multithreading data
    RWDBLocalRecursiveMutex     mutex_;
    RWDBTable                   associatedTable_;
    long                        storageLength_;
    int                         precision_;
    int                         scale_;
    int                         nativeType_;
    int                         auxiliaryType_;
    RWDBValue::ValueType        type_;
    RWDBColumn::ParamType       paramType_;
    bool                        nullAllowed_;

    // Pointer is NULL unless an expression has been set.
    // A copy of the value is created and pointed to by this
    // when the user sets this attribute.
    RWTScopedPointer<RWDBExpr>  defaultValue_;
    RWDBIdentityConstraint      idConstraint_;

    // not implemented
    RWDBColumnImp(const RWDBColumnImp&);
    RWDBColumnImp& operator=(const RWDBColumnImp&);

};

#endif
