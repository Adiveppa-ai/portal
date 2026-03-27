#ifndef rw_serial_RWTStreamingFactory_h_
#define rw_serial_RWTStreamingFactory_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWTStreamingFactory.h#1 $
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

#if defined(_MSC_VER)
#  pragma warning (disable: 4275)
#endif

#include <rw/serial/pkgdefs.h>
#include <rw/factory/RWTFactory0.h>
#include <rw/cstring.h>
#include <rw/once.h>


//--This class represents a factory for objects derived from Base.
//--It is used by streaming.
template <class Base>
class RWTStreamingFactory
{

public:

    typedef RWSymbol                               key_type;

    typedef RWTFactory0<Base, RWSymbol>            factory_type;
    typedef RWTFactory0<Base, RWSymbol>*           factory_type_ptr;

    typedef typename factory_type::RWRegistration  Registration;

    static factory_type_ptr  getFactory();

    void* operator()(RWSymbol typeName) const;

private:

    class DefaultMethod
    {
    public:
        Base operator()() const
        {
            std::cerr << "Unknown type" << std::endl;
            return rwnil;
        }
    };

    static void
    init();

private:

    static factory_type_ptr ptr_;

    static RWOnce initInstanceOnce_;

};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/serial/RWTStreamingFactory.cc>
#endif

#endif // rw_serial_RWTStreamingFactory_h_
