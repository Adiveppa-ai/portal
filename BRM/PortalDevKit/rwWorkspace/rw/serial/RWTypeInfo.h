#ifndef rw_serial_RWTypeInfo_h_
#define rw_serial_RWTypeInfo_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWTypeInfo.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 ********************************************************************/

#include <rw/serial/pkgdefs.h>
#include <rw/types/RWSymbol.h>
#include <rw/tools/hash.h>
#include <typeinfo>


class RW_SERIAL_SYMBOLIC RWTypeInfo
{
public:

    RWTypeInfo(const std::type_info& ti)
        : type_info_ptr_(&ti) {}


    RWTypeInfo(const std::type_info* tip)
        : type_info_ptr_(tip) {}


    RWTypeInfo(const RWTypeInfo& other)
        : type_info_ptr_(other.type_info_ptr_) {}

    RWTypeInfo& operator=(const RWTypeInfo& other)
    {
        if (this != &other) {
            type_info_ptr_ = other.type_info_ptr_;
        }
        return *this;
    }

    bool operator==(const RWTypeInfo& other) const
    {
        return (type_info_ptr_->operator==(*(other.type_info_ptr_)) != 0);
    }

    const char* name() const
    {
        return type_info_ptr_->name();
    }

    unsigned hash() const
    {
        return RWTypeInfo::hash(*this);
    }

    // Static functions

    // Hash RWTypeInfo objects on name.
    static unsigned hash(const RWTypeInfo& ti);

    // Fix up RTTI type names to look the same on different machines.
    static RWCString canonicalName(const RWTypeInfo& ti);

    //Return string (symbol) associated with RTTI type information.
    static RWSymbol symbol(const RWTypeInfo& ti);

    // Used by macros to associate the internal RTTI name of a type, with
    // its string representation.
    static RWSymbol registerTypeInfo(const RWTypeInfo& ti);

private:

    RWTypeInfo()
    {
    }

    const std::type_info* type_info_ptr_;
};

template <>
struct RWTHash<RWTypeInfo> {
    typedef size_t result_type;

    typedef RWTypeInfo argument_type;

    result_type operator()(const argument_type& obj) const
    {
        return RWTypeInfo::hash(obj);
    }
};

#endif // rw_serial_RWTypeInfo_h_
