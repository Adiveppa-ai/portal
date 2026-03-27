#ifndef __RWDB_TMTABLEI_H__
#define __RWDB_TMTABLEI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/tmtablei.h#1 $
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

#include <rw/db/dbsrc/tablei.h>


//////////////////////////////////////////////////////////////////////////
//
//  R W D B T M e m T a b l e I m p
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBTMemTableImp : public RWDBTableImp
{
public:
    RWDBTMemTableImp(const RWDBStatus&, const RWDBDatabase&);
    virtual ~RWDBTMemTableImp();

    virtual void      setSchema(const RWDBSchema&);

    virtual bool existsAllocateConnection(bool forceLookup = false);
    virtual bool exists(const RWDBConnection& connection,
                        bool forceLookup = false);

protected:
    bool schemaFetched_;

private:
    // not implemented:
    RWDBTMemTableImp(const RWDBTMemTableImp& impl);
    RWDBTMemTableImp& operator=(const RWDBTMemTableImp& impl);
};

#endif
