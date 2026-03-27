#ifndef __RWDB_FOREIGNKEYI_H__
#define __RWDB_FOREIGNKEYI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/forkeyi.h#1 $
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
 * Definition of class RWDBForeignKeyImp, the reference-counted
 * implementation of class RWDBForeignKey.
 *
 * Note: this is NOT a base class for database-specific variants.
 *
 **************************************************************************/

#include <rw/db/dbsrc/schemai.h>
#include <rw/db/forkey.h>

//////////////////////////////////////////////////////////////////////////
//
// RWDBForeignKeyImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBForeignKeyImp : public RWDBSchemaImp
{
    friend class RWDBForeignKey;

public:
    RWDBForeignKeyImp(const RWDBStatus&);

    RWDBForeignKeyImp(const RWDBStatus&,
                      const RWCString& refName,
                      RWDBForeignKey::Constraint updateConstraint,
                      RWDBForeignKey::Constraint deleteConstraint);

    RWDBForeignKeyImp(const RWDBStatus&,
                      const RWCString& constraintName,
                      const RWCString& refName,
                      RWDBForeignKey::Constraint updateConstraint,
                      RWDBForeignKey::Constraint deleteConstraint);

    virtual ~RWDBForeignKeyImp();

    RWDBForeignKeyImp* clone() const;

    RWCString       asString(const RWDBPhraseBook& pb) const;

    RWCString       deleteConstraintAsString(const RWDBPhraseBook& pb) const;
    RWCString       updateConstraintAsString(const RWDBPhraseBook& pb) const;

    // accessors
    RWCString       referenceName() const;
    RWCString       constraintName() const;
    RWDBSchema&     referenceKey();

    RWDBForeignKey::Constraint updateConstraint() const;
    RWDBForeignKey::Constraint deleteConstraint() const;

    // mutators
    void            constraintName(const RWCString& newName);
    void            referenceName(const RWCString& newName);
    void            updateConstraint(RWDBForeignKey::Constraint newConstraint);
    void            deleteConstraint(RWDBForeignKey::Constraint newConstraint);
    void            referenceKey(const RWDBSchema& schema);

    // collectable API
    virtual RWspace binaryStoreSize() const;
    virtual void    saveGuts(RWFile& file) const;
    virtual void    saveGuts(RWvostream& stream) const;
    virtual void    restoreGuts(RWFile& file);
    virtual void    restoreGuts(RWvistream& stream);

private:
    RWCString                  constraintName_;
    RWCString                  referenceName_;
    RWDBForeignKey::Constraint updateConstraint_;
    RWDBForeignKey::Constraint deleteConstraint_;

    // the columns from the primary table that this foreign key
    // refers to
    RWTScopedPointer<RWDBSchema> refKey_;

    // not implemented:
    RWDBForeignKeyImp(const RWDBForeignKeyImp& impl);
    RWDBForeignKeyImp& operator=(const RWDBForeignKeyImp& impl);
};

#endif
