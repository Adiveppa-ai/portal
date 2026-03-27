#ifndef __RWDB_OCISPROC_H__
#define __RWDB_OCISPROC_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocisproc.h#1 $
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
 * Oracle OCI Library implementation of RWDBStoredProcImp
 *
 **************************************************************************/

#include <rw/db/ocisrc/rwoci.h>
#include <rw/db/dbsrc/storedi.h>

class RWDB_ACCESS_GLOBAL RWDBOCIStoredProcImp : public RWDBStoredProcImp
{
public:
    RWDBOCIStoredProcImp(const RWDBStatus&     status,
                         const RWDBDatabase&   dbase,
                         const RWCString&      name,
                         const RWDBConnection& connection);

    RWDBOCIStoredProcImp(const RWDBStatus&     status,
                         const RWDBDatabase&   dbase,
                         const RWCString&      name,
                         const RWDBSchema&     schema,
                         const RWDBColumn&     col,
                         const RWCString&      text);

    virtual
    ~RWDBOCIStoredProcImp();

    const RWDBPhraseBook&   phraseBook() const;

    virtual void            doInitialize(const RWDBSchema& columnList, RWDBStoredProcEntry* entry);

    virtual RWCString       doText(const RWDBConnection& connection, RWDBStoredProcEntry* entry);
    virtual RWDBSchema      doParams(const RWDBConnection& connection, RWDBStoredProcEntry* entry);
    virtual bool            doExists(const RWDBConnection& connection, RWDBStoredProcEntry* entry);
    virtual RWDBStatus      drop(const RWDBConnection& connection);

    virtual void            bind(const RWDBConnection& conn,
                                 RWDBStatus& status);

    RWCString               asString(const RWZone& timeZone);

    virtual RWDBValue       returnValue() const;
    using RWDBStoredProcImp::returnValueColumn;

protected:
    void returnValueColumn(const RWDBColumn& col);

private:
    bool                 isFunc_;
    RWCString            packageName_;
    // in the case of a synonym, this will hold the
    // actual procedure name
    RWCString            referencedName_;

    RWDBStatus fetchParams(const RWCString& name,
                           const RWDBConnection& connection);
    //Unimplemented:
    RWDBOCIStoredProcImp(const RWDBOCIStoredProcImp&);
    RWDBOCIStoredProcImp& operator=(const RWDBOCIStoredProcImp&);
};


#endif
