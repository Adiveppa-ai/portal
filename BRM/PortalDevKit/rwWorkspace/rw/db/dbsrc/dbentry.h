#ifndef __RWDB_ENTRY_H__
#define __RWDB_ENTRY_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/dbentry.h#1 $
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

#include <rw/db/dbsrc/dbsysdefs.h>
#include <rw/db/dbase.h>
#include <rw/db/dberr.h>
#include <rw/db/dbmgr.h>
#include <rw/db/dbmutex.h>
#include <rw/db/defs.h>


////////////////////////////////////////////////////////////////////////
//
// RWDBEntry
//
//      An RWDBEntry is an element of the RWDBManagerProxy's set of
//      access module entries.
//      It contains the names of regular and XA-Enabled Implementation
//      functions and function pointers by which one obtains an instance
//      of either Implementations, as well as an opaque handle for use in
//      environments which support runtime linkage.
//
//      It also stores names of XA switch functions and function pointers
//      by which one obtains a pointer to the XA switch.
//
//      If runtime linkage is supported and in use, the Implementation
//      name (dbType) may be the name of a dynamically linkable library.
//
//      At link time, the Manager's set of imps is populated with
//      entries for all implementations which are statically linked.
//      These are identified by a RWDBLibHandle of 0.
//
//      At runtime, if dynamic linkage is supported and the manager is
//      asked to supply an implementation for a dbType not present,
//      a search is made for a dynamic library whose name matches
//      the dbType. If found, an attempt is made to find a function
//      in the library through which the application can obtain the
//      desired implementation. If all goes well, the function and the
//      handle are stored in the entry.
//
//      This class was written interface/implementation to allow for
//      reference counting of the entry.  Doing this allows us to prevent
//      accidentally unloading the access module before the destruction of
//      RWDBDatabaseImps that depend on the library.
//
////////////////////////////////////////////////////////////////////////
class RWDBEntryImp : public RWDBReference
{
public:

    // Default constructor
    RWDBEntryImp();

    // Constructor taking database type and names of implementation functions.
    // Generally used by dynamic builds.
    RWDBEntryImp(const RWCString& dbType,
                 const RWCString& impFuncName,
                 const RWCString& xaImpFuncName,
                 const RWCString& xaSwitchFuncName);

    // Constructor taking database type and function pointers.
    // Generally used by static builds.
    RWDBEntryImp(const RWCString& dbType,
                 const RWDBNewImpFunc impFunc = 0,
                 const RWDBNewImpFunc xaImpFunc = 0,
                 const RWDBXASwitchFunc xaSwitchFunc = 0);

    virtual      ~RWDBEntryImp();


    // When dynamic linkage is supported, opens the library to search
    // for the function names.
    bool           openLib();

    // Closes the dynamically linked library.
    void                closeLib();

    // Returns the database type
    RWCString           dbType() const;

    // Returns a function pointer to the function which returns regular (non-XA)
    // database implementation.
    RWDBNewImpFunc      impFunc() const;

    // Returns a function pointer to the function which returns XA-Enabled
    // database implementation.
    RWDBNewImpFunc      xaImpFunc() const;

    // Returns a function pointer to the function which returns XA Switch.
    RWDBXASwitchFunc    xaSwitchFunc() const;

protected:
    // Stores database type
    RWCString           dbType_;

    // Stores Library Handle in case dynamic linkage is supported.
    RWDBLibHandle       libHandle_;

    // Name of the function returning non-XA implementation.
    RWCString           impFuncName_;
    // Function pointer to the function which returns regular (non-XA)
    // database implementation.
    RWDBNewImpFunc      impFunc_;

    // Name of the function returning XA-Enabled implementation.
    RWCString           xaImpFuncName_;
    // Function pointer to the function which returns XA-Enabled
    // database implementation.
    RWDBNewImpFunc      xaImpFunc_;

    // Name of the function returning XA Switch.
    RWCString           xaSwitchFuncName_;
    // Function pointer to the function which returns XA Switch.
    RWDBXASwitchFunc    xaSwitchFunc_;
};


class  RWDBEntry
{
    friend class  RWDBManagerProxy;
public:
    // Default constructor
    RWDBEntry();

    // Copy constructors
    RWDBEntry(const RWDBEntry& entry);
    RWDBEntry& operator=(const RWDBEntry& rhs);

    // destructor
    ~RWDBEntry();


    // Defines criteria for two RWDBEntrys to be considered equal.
    bool operator==(const RWDBEntry& rhs) const;

    // Accessors methods.
    RWCString           dbType() const;
    RWDBNewImpFunc      impFunc() const;
    RWDBNewImpFunc      xaImpFunc() const;
    RWDBXASwitchFunc    xaSwitchFunc() const;

    bool operator<(const RWDBEntry&) const
    {
        // This code should never be reached, and only exists to
        // satisfy a select few compilers that need this operator.
        // If this assertion is reached, this object has been placed
        // in an inappropriate collection.
        RW_ASSERT(false);
        return false;
    }

protected:
    // Constructor taking database type and names of implementation functions.
    RWDBEntry(const RWCString& dbType,
              const RWCString& impFuncName,
              const RWCString& xaImpFuncName,
              const RWCString& xaSwitchFuncName);

    // Constructor taking database type and function pointers.
    RWDBEntry(const RWCString& dbType,
              const RWDBNewImpFunc impFunc = 0,
              const RWDBNewImpFunc xaImpFunc = 0,
              const RWDBXASwitchFunc xaSwitchFunc = 0);

    // When dynamic linkage is supported, opens the library to search
    // for the function names.
    bool           openLib();

    // Closes the dynamically linked library.
    void                closeLib();

    RWDBCountedRef<RWDBEntryImp> impl_;

};

#endif
