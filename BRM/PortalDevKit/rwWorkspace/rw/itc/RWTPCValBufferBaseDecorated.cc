/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBaseDecorated.cc#1 $
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
 *************************************************************************/


/*****************************************************************************

  RWTPCValBufferBaseDecorated<Type,Decorator> - Templatized base class for
    buffers whose entries are stored by-value and decorated with other data,
    such as guard objects or priority values.

******************************************************************************/

#include <rw/itc/RWTPCValBufferBaseDecorated.h>

template <class Type, class Decorator>
RWTPCValBufferBaseDecorated<Type, Decorator>::~RWTPCValBufferBaseDecorated(void)
{
}

template <class Type, class Decorator>
Type
RWTPCValBufferBaseDecorated<Type, Decorator>::read(void)
{
    Decorator decorator = RWTPCValBufferBase<Decorator>::read();
    return decorator.value_;
}

template <class Type, class Decorator>
bool
RWTPCValBufferBaseDecorated<Type, Decorator>::tryRead(Type& value)
{
    Decorator decorator;
    bool result = RWTPCValBufferBase<Decorator>::tryRead(decorator);
    value = decorator.value_;
    return result;
}

template <class Type, class Decorator>
RWWaitStatus
RWTPCValBufferBaseDecorated<Type, Decorator>::read(Type& value, unsigned long milliseconds)
{
    Decorator decorator;
    RWWaitStatus result = RWTPCValBufferBase<Decorator>::read(decorator, milliseconds);
    value = decorator.value_;
    return result;
}

template <class Type, class Decorator>
Type
RWTPCValBufferBaseDecorated<Type, Decorator>::peek(void)
{
    return RWTPCValBufferBase<Decorator>::peek().value_;
}

template <class Type, class Decorator>
bool
RWTPCValBufferBaseDecorated<Type, Decorator>::tryPeek(Type& value)
{
    Decorator decorator;
    bool result = RWTPCValBufferBase<Decorator>::tryPeek(decorator);
    value = decorator.value_;
    return result;
}

template <class Type, class Decorator>
RWWaitStatus
RWTPCValBufferBaseDecorated<Type, Decorator>::peek(Type& value, unsigned long milliseconds)
{
    Decorator decorator;
    RWWaitStatus result = RWTPCValBufferBase<Decorator>::peek(decorator, milliseconds);
    value = decorator.value_;
    return result;
}

template <class Type, class Decorator>
void
RWTPCValBufferBaseDecorated<Type, Decorator>::write(const Type& value)
{
    RWTPCValBufferBase<Decorator>::write(Decorator(value));
}

template <class Type, class Decorator>
bool
RWTPCValBufferBaseDecorated<Type, Decorator>::tryWrite(const Type& value)
{
    return RWTPCValBufferBase<Decorator>::tryWrite(Decorator(value));
}

template <class Type, class Decorator>
RWWaitStatus
RWTPCValBufferBaseDecorated<Type, Decorator>::write(const Type& value, unsigned long milliseconds)
{
    return RWTPCValBufferBase<Decorator>::write(Decorator(value), milliseconds);
}
