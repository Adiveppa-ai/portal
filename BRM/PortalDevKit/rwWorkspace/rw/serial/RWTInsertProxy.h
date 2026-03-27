#ifndef rw_serial_RWTInsertProxy_h_
#define rw_serial_RWTInsertProxy_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWTInsertProxy.h#1 $
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
#include <rw/cstring.h>


/**
 * \ingroup serialization_package
 *
 * \brief
 * Proxy object for inserting objects with an instance name into object
 * streams.
 *
 * A proxy object for inserting objects with an instance name into object
 * streams.
 *
 * This class is typically used by calling the convenience global function
 * rwInsertWithName().
 */
template <class T>
class RW_SERIAL_SUN_SYMBOLIC RWTInsertProxy
{
public:
    /**
     * Constructs a proxy object using the parameter \a myName for the
     * instance name and \a myObject for the instance object. Inserting the
     * proxy object into an object stream causes the string contained by
     * \a myName to be used as the name for the object.
     *
     * Not all object streams support this feature. For example, the compact
     * object streams in the Serialization package do \e not provide
     * support, while the XML object streams in the XML Streams Module \e do
     * provide support.
     */
    RWTInsertProxy(RWCString myName, T& myObject):
        instanceName_(myName),
        instance_(myObject)
    {
        ;
    }

    RWCString instanceName_;
    T& instance_;

};


/**
 * \relates RWTInsertProxy
 *
 * \brief
 * Global function that inserts an object and its name into an object
 * stream.
 *
 * \headerfileloc{#include <rw/serial/RWTInsertProxy.h>}
 *
 * Global function that inserts an object and its name into an object
 * stream.
 *
 * \example
 * \code
 * out << rwInsertWithName( "foo", foo );
 * \endcode
 * \endexample
 */
template <class T>
RWTInsertProxy<T> RW_SERIAL_SUN_SYMBOLIC rwInsertWithName(RWCString myName, T& myObject)
{
    return RWTInsertProxy<T>(myName, myObject);
}

#endif // rw_serial_RWTInsertProxy_h_
