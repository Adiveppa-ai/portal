#ifndef __RWDB_ADAPTER_H__
#define __RWDB_ADAPTER_H__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/adapter.h#1 $
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
 * Classes RWDBAdapter, RWDBAdapterFactory
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/tvdlist.h>

// Access Module IDs
#define RWDB_AL_ODBC        1
#define RWDB_AL_INFORMIX    2
#define RWDB_AL_MSSQL       3
#define RWDB_AL_DB2         4
#define RWDB_AL_ORACLE      5
#define RWDB_AL_SYBASECT    7
#define RWDB_AL_OCI         8
#define RWDB_AL_PGS         9
#define RWDB_AL_MYSQL       10
#define RWDB_AL_UNUSED      11


///////////////////////////////////////////////////////////////////////////
//
// class RWDBAdapterFactory
//
// The abstract base for all access module adapter factories.
//
///////////////////////////////////////////////////////////////////////////
class RWDBBuffer;

class RWDB_GLOBAL RWDBAdapterFactoryID
{
public:
    RWDBAdapterFactoryID(size_t accesslibID, void* factoryPtr) :
        accesslibID_(accesslibID), factoryPtr_(factoryPtr)
    {}
    RWDBAdapterFactoryID(const RWDBAdapterFactoryID& id) :
        accesslibID_(id.accesslibID_), factoryPtr_(id.factoryPtr_)
    {}
    virtual ~RWDBAdapterFactoryID();

    bool operator==(const RWDBAdapterFactoryID& rhs) const
    {
        return accesslibID_ == rhs.accesslibID_ &&
               factoryPtr_ == rhs.factoryPtr_;
    }

    size_t accesslibID() const
    {
        return accesslibID_;
    }
    void* factoryPtr() const
    {
        return (void*)factoryPtr_;
    }

protected:
    size_t accesslibID_;
    void* factoryPtr_;
};

class RWDBAdapter;

class RWDB_GLOBAL RWDBAdapterFactory : public RWDBAdapterFactoryID
{
public:
    RWDBAdapterFactory(size_t accesslibID,
                       bool multipleFactoriesPerType = false) :
        RWDBAdapterFactoryID(accesslibID, NULL)
    {
        if (multipleFactoriesPerType) {
            factoryPtr_ = this;
        }
    }
    virtual ~RWDBAdapterFactory();

    RWDBAdapterFactoryID id() const
    {
        return *((const RWDBAdapterFactoryID*)this);
    }

    virtual RWDBAdapter* make(RWDBBuffer* coreBuffer) = 0;

    //  Add the buffer to the registry that the factory just
    //  placed an adapter in.
    virtual void addToRegistry(RWDBBuffer* bufferIn)
    {
        bufferRegistry_.insert(bufferIn);
    }

    //  The buffer that an adapter was in has been destroyed,
    //  remove the buffer from the registry.
    virtual void removeFromRegistry(RWDBBuffer* bufferIn)
    {
        bufferRegistry_.remove(bufferIn);
    }

private:
    RWTValDlist<RWDBBuffer*> bufferRegistry_;
};


///////////////////////////////////////////////////////////////////////////
//
// class RWDBAdapter
//
// An adapter adapts one kind of buffer to other kinds of buffers.
// Access libraries define their own adapter families to adapt core-
// generated buffers to whatever they need for binding purposes.
//
///////////////////////////////////////////////////////////////////////////

class RWDB_GLOBAL RWDBAdapter
{
public:
    RWDBAdapter(RWDBAdapterFactory* factory, RWDBBuffer* coreBuffer) :
        coreBuffer_(coreBuffer), factory_(factory)
    {}

    virtual ~RWDBAdapter();

    RWDBBuffer* coreBuffer() const
    {
        return (RWDBBuffer*)coreBuffer_;
    }

    RWDBAdapterFactory* factory() const
    {
        return factory_;
    }

    RWDBAdapterFactoryID id() const
    {
        return *factory_;
    }
    // For comparing the adapters and factories...
    bool operator==(const RWDBAdapter& rhs) const
    {
        return id() == rhs.id();
    }

    bool operator==(const RWDBAdapterFactory& rhs) const
    {
        // the factoryPtr_ is NULL if we aren't supposed to compare
        // factory instances, only ID's.
        return (id().accesslibID() == rhs.id().accesslibID()) &&
               (id().factoryPtr() == NULL ||
                id().factoryPtr() == rhs.id().factoryPtr());
    }

    bool operator<(const RWDBAdapter& rhs) const
    {
        return (this < &rhs);
    }

    // returns the 'bindable' version of this data.
    // on this base class, it just returns the data of the core buffer.
    // this is obviously overridden for all but the most simple types,
    // in the access module.
    virtual void* data();

    // Sync synchronizes the data that the adapter contains back into
    // the core buffer.  Only the first 'entries' buffer entries are
    // sync'ed.
    virtual void sync(size_t entries);

    // Update updates the data the adapter contains/may contain from
    // the core buffer.  true is returned if a bind address changed,
    // indicating the need to rebind.
    virtual bool update(size_t bulksize);

protected:
    RWDBBuffer* coreBuffer_;
    RWDBAdapterFactory* factory_;

private:
    // not implemented to prevent use
    RWDBAdapter(const RWDBAdapter& a);
    const RWDBAdapter& operator=(const RWDBAdapter& rhs);
};



#endif // __RWDB_ADAPTER_H__
