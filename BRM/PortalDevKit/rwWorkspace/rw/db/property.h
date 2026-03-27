#ifndef __RWDB_PROPERTY_H__
#define __RWDB_PROPERTY_H__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/property.h#1 $
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
 * Class RWDBPropertyValue, RWDBProperties, RWDBPropertiesImp,
 *       RWDBPropertiesIterator, RWDBPropertyFactory
 *
 **************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/value.h>
#include <rw/cstring.h>
#include <rw/ctoken.h>
#include <rw/hashdict.h>


///////////////////////////////////////////////////////////////////////////
//
// class RWDBPropertyValue
//
// Holds the string value for connection properties passed via
// RWDBManager::database(..., connectString)
//
///////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBPropertyValue : public RWDBValue
{
public:
    RWDBPropertyValue()
    {
        ;
    }
    RWDBPropertyValue(const RWCString& v)
        : RWDBValue(v)
    {
        ;
    }
    RWDBPropertyValue(const char* v)
        : RWDBValue(v)
    {
        ;
    }
    ~RWDBPropertyValue()
    {
        ;
    }
};

class RWDB_SYMBOLIC RWDBPropertiesIterator;

///////////////////////////////////////////////////////////////////////////
//
// class RWDBPropertiesImp
//
// The implementation for RWDBProperties
//
///////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBPropertiesImp
    : public RWDBReference
{
public:
    RWDBPropertiesImp()
    {
        ;
    }

    virtual ~RWDBPropertiesImp()
    {
        RW_SUPPRESS_CTOR_CALLS_VIRTUAL_FUNC_WARNING
        propList_.clearAndDestroy();
        RW_RESTORE_CTOR_CALLS_VIRTUAL_FUNC_WARNING
    }

    virtual void insert(const RWCString& key, const RWCString& val);
    virtual bool find(const RWCString& key, RWCString& retKey) const;
    virtual bool findKeyAndValue(const RWCString& key,
                                 RWCString& retKey,
                                 RWDBPropertyValue& retVal) const;
    virtual bool findValue(const RWCString& key,
                           RWDBPropertyValue& retVal) const;

    RWDBPropertyValue& operator[](const RWCString& key);
private:
    RWHashDictionary propList_;

    friend class RWDBPropertiesIterator;
    //not implemented
    RWDBPropertiesImp(const RWDBPropertiesImp&);
    RWDBPropertiesImp& operator=(const RWDBPropertiesImp&);
};


///////////////////////////////////////////////////////////////////////////
//
// class RWDBProperties
//
// A collection of Property strings and associated values
//
///////////////////////////////////////////////////////////////////////////

class RWDB_SYMBOLIC RWDBProperties
{
public:
    RWDBProperties();
    RWDBProperties(const RWDBProperties& cp);
    ~RWDBProperties();
    RWDBProperties& operator=(const RWDBProperties& rhs);

    // adds the key with associated item val to the collection
    void insert(const RWCString& key, const RWCString& val);

    // If there exists a key j in self that compares equal to 'key',
    // assigns j to retKey and returns true. Otherwise, returns false
    // and leaves the value of retKey unchanged
    bool find(const RWCString& key, RWCString& retKey) const;

    // If there exists a key j in self that compares equal to 'key',
    // assigns j to retKey, assigns the item associated with j to retVal,
    // and returns true. Otherwise, returns false and leaves the values
    // of retKey and retVal unchanged.
    bool findKeyAndValue(const RWCString& key, RWCString& retKey,
                         RWDBPropertyValue& retVal) const;

    // If there exists a key j in self that compares equal to 'key',
    // assigns the item associated with j to retVal and returns true.
    // Otherwise, returns false and leaves the value of retVal unchanged.
    bool findValue(const RWCString& key, RWDBPropertyValue& retVal) const;

    // Looks up key and returns a reference to its associated item. If the key
    // is not in the dictionary, then it will be added with an associated item
    // provided by the default constructor for RWDBPropertyValue
    RWDBPropertyValue& operator[](const RWCString& key);

private:
    friend RWDBPropertiesImp* getImp(const RWDBProperties& props)
    {
        return props.impl_;
    }
    RWDBCountedRef<RWDBPropertiesImp> impl_;
};

///////////////////////////////////////////////////////////////////////////
//
// class RWDBPropertiesIterator
//
// An iterator for RWDBProperties collection
//
///////////////////////////////////////////////////////////////////////////
class RWDB_SYMBOLIC RWDBPropertiesIterator
{
public:
    RWDBPropertiesIterator(RWDBProperties& p);
    RWDBPropertiesIterator(const RWDBProperties& p);
    // advances self to the next item. Return false if the iterator has
    // advanced past the last item in the container and true otherwise.
    bool operator()();
    // Returns the key portion of the association
    //   currently pointed to by self.
    RWCString key() const;
    // Returns the value portion of the association
    //   currently pointed to by self.
    RWDBPropertyValue value() const;
private:
    RWTScopedPointer<RWHashDictionaryIterator> theIter_;
    RWDBPropertiesIterator();
    RWDBPropertiesIterator& operator=(const RWDBPropertiesIterator&);
};

///////////////////////////////////////////////////////////////////////////
//
// class RWDBPropertyFactory
//
// A static class implementing a method for producing RWDBProperties
//
///////////////////////////////////////////////////////////////////////////

class RWDB_SYMBOLIC RWDBPropertyFactory
{
public:
    // Parses the string into key/value pairs and constructs a RWDBProperties.
    // The expected syntax of the argument is:
    // <key1>=<value1>;<key2>=<value2>;....
    static RWDBProperties make(const RWCString& propString);
};


#endif
