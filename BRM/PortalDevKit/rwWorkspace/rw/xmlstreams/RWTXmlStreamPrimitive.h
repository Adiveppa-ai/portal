#ifndef rw_xmlstreams_RWTXmlStreamPrimitive_h_
#define rw_xmlstreams_RWTXmlStreamPrimitive_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTXmlStreamPrimitive.h#1 $
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

#include <rw/xmlstreams/RWXmlStreamElement.h>
#include <rw/xmlstreams/pkgdefs.h>

template <class T> class RWTXmlStreamPrimitive;

template <>
class RWTXmlStreamPrimitive<RWCString> : public RWXmlStreamElement
{
    RWCString value_;
public:
    RWTXmlStreamPrimitive<RWCString>(const RWTXmlStreamPrimitive<RWCString>& rhs)
        : RWXmlStreamElement(rhs), value_(rhs.value_) { }
    RWTXmlStreamPrimitive<RWCString>(const RWXmlName& name, RWXmlStreamElement* parent, const RWCString& t, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces)
        : RWXmlStreamElement(name, parent, namespaces, rwStreamType(&t)), value_(t) { }
    void setPrimitiveValue(const RWCString& t)
    {
        value_ = t;
    }
    RWCString getPrimitiveValue()
    {
        return value_;
    }

    virtual void write(RWDataOutputStream& out, int indent)
    {
        const RWCString& name = getName().asString();
        if (name.length()) {
            writePrologue(out, name, indent++);
        }
        out.putString(value_.data(), static_cast<RWSize>(value_.length()));
        if (name.length()) {
            writeEpilogue(out, name, 0);
        }
    }
protected:
    virtual RWXmlStreamElement* make() const
    {
        return new RWTXmlStreamPrimitive<RWCString>(*this);
    }
};

template <>
class RWTXmlStreamPrimitive<char> : public RWXmlStreamElement
{
    char value_;
public:
    RWTXmlStreamPrimitive<char>(const RWTXmlStreamPrimitive<char>& rhs)
        : RWXmlStreamElement(rhs), value_(rhs.value_) { }
    RWTXmlStreamPrimitive<char>(const RWXmlName& name, RWXmlStreamElement* parent, const char& t, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces)
        : RWXmlStreamElement(name, parent, namespaces, rwStreamType(&t)), value_(t) {}
    void setPrimitiveValue(char t)
    {
        value_ = t;
    }
    char getPrimitiveValue()
    {
        return value_;
    }

    virtual void write(RWDataOutputStream& out, int indent)
    {
        const RWCString& name = getName().asString();
        if (name.length()) {
            writePrologue(out, name, indent++);
        }
        out.putCharacter(value_);
        if (name.length()) {
            writeEpilogue(out, name, 0);
        }
    }
protected:
    virtual RWXmlStreamElement* make() const
    {
        return new RWTXmlStreamPrimitive<char>(*this);
    }
};

template <class T>
class RWTXmlStreamPrimitive : public RWXmlStreamElement
{
    T value_;
public:
    RWTXmlStreamPrimitive<T>(const RWTXmlStreamPrimitive<T>& rhs)
        : RWXmlStreamElement(rhs), value_(rhs.value_) { }
    RWTXmlStreamPrimitive<T>(const RWXmlName& name, RWXmlStreamElement* parent, const T& t, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces)
        : RWXmlStreamElement(name, parent, namespaces, rwStreamType(&t)), value_(t) {}
    void setPrimitiveValue(T t)
    {
        value_ = t;
    }
    T getPrimitiveValue()
    {
        return value_;
    }

    virtual void write(RWDataOutputStream& out, int indent)
    {
        const RWCString& name = getName().asString();
        if (name.length()) {
            writePrologue(out, name, indent++);
        }
        out << value_;
        if (name.length()) {
            writeEpilogue(out, name, 0);
        }
    }
protected:
    virtual RWXmlStreamElement* make() const
    {
        return new RWTXmlStreamPrimitive<T>(*this);
    }
};

#endif // rw_xmlstreams_RWTXmlStreamPrimitive_h_
