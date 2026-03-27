#ifndef rw_serial_RWObjectStreamMacros_h_
#define rw_serial_RWObjectStreamMacros_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWObjectStreamMacros.h#1 $
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

#if defined(_WIN32)
#  pragma warning (disable:4251)
#endif

#include <rw/serial/RWObjectInputStream.h>
#include <rw/serial/RWObjectOutputStream.h>
#include <rw/serial/RWTExtRestoreGuts.h>
#include <rw/serial/RWTExtSaveGuts.h>
#include <rw/serial/RWTStreamingFactory.h>
#include <rw/serial/StreamTraits.h>
#include <rw/serial/pkgdefs.h>

// Helper macros to export symbols from the library
#define RW_SERIAL_EXPORT        RW_SERIAL_GLOBAL
#define RW_SERIAL_DONT_EXPORT

// Helper class used in external serialization
template<typename T>
struct RWTExtSerialFunctors {
    typedef
    RWTPseudoMethod1<const T*, RWObjectOutputStream&>
    SaveFunctorT;

    typedef
    RWTPseudoMethod1<T*, RWObjectInputStream&>
    RestoreFunctorT;

    static SaveFunctorT    save_;
    static RestoreFunctorT restore_;
};

// External serialization factory
template<typename T>
struct RWTSerialFactory {
    typedef RWTFactory1<void*, RWCString, RWSymbol> FactoryT;

    typedef
    typename FactoryT::RWRegistration FactoryRegistrationT;

    static FactoryRegistrationT factoryRegistration_;
};


// External serialization factory registration
template<typename Derived, typename Base>
struct RWTCreatorRegistration {
    typedef Base* (*Creator)();

    typedef typename
    RWTStreamingFactory<Base*>::Registration
    creatorRegistrationT;

    static creatorRegistrationT creatorRegistration_;
};

// External serialization; functor registration, primary template
template<typename Derived, typename Base>
struct RWTExtSerialFunctorRegistration {
    typedef RWTOnlyPointer<RWPseudoMethodRegistrationBase> RegistrationT;

    static RegistrationT  saveRegistrar_;
    static RegistrationT  restoreRegistrar_;
};

/**************************************************************************/

#define RW_DECLARE_EXT_FUNCTORS_SPECIALIZATION(T,EXPORT)                   \
template<>                                                                 \
struct EXPORT RWTExtSerialFunctors<T>                                      \
{                                                                          \
    typedef                                                                \
    RWTPseudoMethod1<const T*, RWObjectOutputStream&>                      \
    SaveFunctorT;                                                          \
    typedef                                                                \
    RWTPseudoMethod1<T*, RWObjectInputStream&>                             \
    RestoreFunctorT;                                                       \
    static SaveFunctorT    save_;                                          \
    static RestoreFunctorT restore_;                                       \
};

#define RW_DECLARE_SERIAL_FACTORY_SPECIALIZATION(T)                        \
template<>                                                                 \
struct RWTSerialFactory<T>                                                 \
{                                                                          \
    typedef RWTFactory1<void*,RWCString,RWSymbol> FactoryT;                \
    typedef FactoryT::RWRegistration FactoryRegistrationT;                 \
    static FactoryRegistrationT factoryRegistration_;                      \
};

#define RW_DECLARE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(D,B)            \
template<>                                                                 \
struct RWTCreatorRegistration<D, B>                                        \
{                                                                          \
    typedef B*(*Creator)();                                                \
    typedef                                                                \
    RWTStreamingFactory<B*>::Registration creatorRegistrationT;            \
    static creatorRegistrationT creatorRegistration_;                      \
};

#define RW_DECLARE_EXT_FUNCTORS_REGISTRAR_SPECIALIZATION(D,B)              \
template <>                                                                \
struct RWTExtSerialFunctorRegistration <D, B>                              \
{                                                                          \
    typedef                                                                \
    RWTOnlyPointer<RWPseudoMethodRegistrationBase> RegistrationT;          \
                                                                           \
    static RegistrationT  saveRegistrar_;                                  \
    static RegistrationT  restoreRegistrar_;                               \
};

/**************************************************************************/

#define RW_DEFINE_EXT_FUNCTORS_SPECIALIZATION(T)                           \
RWTExtSerialFunctors<T>::SaveFunctorT                                      \
RWTExtSerialFunctors<T>::save_ =                                           \
RWTPseudoMethod1 <const T*, RWObjectOutputStream&> (                       \
    RWTExtSaveGuts<T,T>::mkFunctor());                                     \
                                                                           \
RWTExtSerialFunctors<T>::RestoreFunctorT                                   \
RWTExtSerialFunctors<T>::restore_ =                                        \
RWTPseudoMethod1 <T*, RWObjectInputStream&> (                              \
    RWTExtRestoreGuts<T,T>::mkFunctor());


#define RW_DEFINE_SERIAL_FACTORY_SPECIALIZATION(T)                         \
RWTSerialFactory<T>::FactoryRegistrationT                                  \
RWTSerialFactory<T>::factoryRegistration_ =                                \
    RWTSerialFactory<T>::FactoryRegistrationT (                            \
        *(RWObjectInputStream::getFactory()),                              \
        typeid(T).name(), RWTStreamingFactory<T*>());

#define RW_DEFINE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(D,B)             \
RWTCreatorRegistration<D, B>::creatorRegistrationT                         \
RWTCreatorRegistration<D, B>::creatorRegistration_ =                       \
    RWTCreatorRegistration<D, B>::creatorRegistrationT (                   \
        (*RWTStreamingFactory<B*>::getFactory()),                          \
        RWTypeInfo::registerTypeInfo(typeid(D)),                           \
        RWTFactory0Ctor<B*,D>::ctor);

#define RW_DEFINE_EXT_FUNCTORS_REGISTRAR_SPECIALIZATION(D,B)               \
RWTExtSerialFunctorRegistration<D, B>::RegistrationT                       \
RWTExtSerialFunctorRegistration<D, B>::saveRegistrar_ =                    \
    RWTExtSerialFunctors<B>::save_.mkRegistration (                        \
        typeid(D), (RWTExtSaveGuts<B, D>::mkFunctor()));                   \
                                                                           \
RWTExtSerialFunctorRegistration<D, B>::RegistrationT                       \
RWTExtSerialFunctorRegistration<D, B>::restoreRegistrar_ =                 \
    RWTExtSerialFunctors<B>::restore_.mkRegistration (                     \
        typeid(D), (RWTExtRestoreGuts<B, D>::mkFunctor()));

/************************ Internal macros *********************************/

//--While not directly part of object streams, these macros make heavy use
//--of the object streams interface, delegating most of the work of object
//--serialization  back  to  the  object  stream  implementation.   Object
//--streams  are  thus  able  to  control nearly  all  aspects  of  object
//--serialization,  not  just the  format  of  primitive  data types  like
//--virtual streams.

// Insertion operator - class member
#define RW_SERIAL_DEFINE_MEMBER_INSERTER(Class)                            \
public:                                                                    \
    friend RWObjectOutputStream&                                           \
    operator<< (RWObjectOutputStream& s, const Class& obj)                 \
    {                                                                      \
        RWWithObjectOutputContext c(s);                                    \
        s.startBlock (RWTypeInfo::symbol (typeid(Class)));                 \
        const_cast<Class&>(obj).streamContents(0, &s);                    \
        s.endBlock();                                                      \
        return s;                                                          \
    }


// Extraction operator - class member
#define RW_SERIAL_DEFINE_MEMBER_EXTRACTOR(Class)                           \
public:                                                                    \
    friend RWObjectInputStream&                                            \
    operator>> (RWObjectInputStream& s, const Class& obj)                  \
    {                                                                      \
        RWWithObjectInputContext c(s);                                     \
        s.startBlock ();                                                   \
        const_cast<Class &>(obj).streamContents(&s, 0);                    \
        s.endBlock();                                                      \
        return s;                                                          \
    }

//--This  macro should  be included  within the  class declaration  of any
//--streamable class.  Usually, a good place  to put it is right after the
//--open brace.

// streamContents declaration - class member
#define RW_SERIAL_DECLARE_MEMBER_STREAMER(Class)                           \
public:                                                                    \
    virtual void streamContents(RWObjectInputStream*,                      \
                                RWObjectOutputStream*);

#define RW_SERIAL_DEFINE_MEMBER_STREAMTYPE(Class)                          \
public:                                                                    \
  friend RWStreamType rwStreamType(const Class*) {                         \
      return RW_NESTED_OBJECT;                                             \
  }



// streamContents definition - class member
#define RW_SERIAL_DEFINE_MEMBER_STREAMER_PROLOG(Class)                     \
void Class::streamContents(RWObjectInputStream*  in,                       \
                           RWObjectOutputStream* out)                      \
{                                                                          \
    Class*       This = this;                                              \
    RWStreamType TypeInfo (RW_UNSUPPORTED);                                \
    RWSymbol     Attribute;                                                \
    RW_UNUSED(This);                                                       \
    RW_UNUSED(TypeInfo);                                                   \
    RW_UNUSED(in);                                                         \
    RW_UNUSED(out);

#define RW_SERIAL_DEFINE_STREAMER_EPILOG }

// Insertor operator - global functions
#define RW_SERIAL_DECLARE_GLOBAL_INSERTER_PTR(Class,EXPORT)                \
    EXPORT RWObjectOutputStream&                                           \
    operator<< (RWObjectOutputStream&, Class*);                            \
    EXPORT RWObjectOutputStream&                                           \
    operator<< (RWObjectOutputStream&, Class const*);

// This macro is used by define streamable base, and is not intended
// to appear directly in streamable class code.  It defines an
// operator to stream out a polymorphic instance based on a pointer.
#define RW_SERIAL_DEFINE_GLOBAL_INSERTER_PTR(Class)                        \
RWObjectOutputStream& operator<< (RWObjectOutputStream& str,               \
                                 Class* pobj)                              \
{                                                                          \
    if (pobj) {                                                            \
        RWWithObjectOutputContext ctx(str);                                \
        if (str.needToWrite(pobj)) {                                       \
            str.newObjectMarker();                                         \
            str.writeTypeInfo(RWTypeInfo::symbol(typeid(*(pobj))));        \
            str.rememberObject(pobj);                                      \
            str << *pobj;                                                  \
        }                                                                  \
    }                                                                      \
    else                                                                   \
        str.writeNullPtr();                                                \
                                                                           \
    return str;                                                            \
}

#define RW_SERIAL_DEFINE_GLOBAL_INSERTER_PTR_CONST(Class)                  \
RWObjectOutputStream& operator<< (RWObjectOutputStream& str,               \
                                 const Class* pobj)                        \
{                                                                          \
    if (pobj) {                                                            \
        RWWithObjectOutputContext ctx(str);                                \
        if (str.needToWrite(pobj)) {                                       \
            str.newObjectMarker();                                         \
            str.writeTypeInfo(                                             \
                RWTypeInfo::symbol(                                        \
                    typeid(*(const_cast<Class*>(pobj)))));                 \
            str.rememberObject(pobj);                                      \
            str << *pobj;                                                  \
        }                                                                  \
    }                                                                      \
    else                                                                   \
        str.writeNullPtr();                                                \
                                                                           \
    return str;                                                            \
}

#define RW_SERIAL_DEFINE_LIBRARY_GLOBAL_INSERTER_PTR(T)                    \
RWObjectOutputStream& operator<< (RWObjectOutputStream& str,               \
                                  T* pobj)                                 \
{                                                                          \
    if (pobj) {                                                            \
        RWWithObjectOutputContext ctxt(str);                               \
        if (str.needToWrite(pobj)) {                                       \
            str.newObjectMarker();                                         \
            str.writeTypeInfo(RWTypeInfo::symbol(typeid (*pobj)));         \
            str.rememberObject(pobj);                                      \
            if (rwStreamType(pobj) != RW_NESTED_OBJECT  &&                 \
                rwStreamType(pobj) != RW_SEQ &&                            \
                rwStreamType(pobj) != RW_ASSOC) {                          \
                    str.startBlock (                                       \
                        RWTypeInfo::symbol(typeid (*pobj)));               \
                    str << *pobj;                                          \
                    str.endBlock ();                                       \
                }                                                          \
            else                                                           \
                str << *pobj;                                              \
        }                                                                  \
    }                                                                      \
    else {                                                                 \
        str.writeNullPtr();                                                \
    }                                                                      \
    return str;                                                            \
}

#define RW_SERIAL_DEFINE_LIBRARY_GLOBAL_INSERTER_PTR_CONST(T)              \
RWObjectOutputStream& operator<< (RWObjectOutputStream& str,               \
                                 const T* pobj)                            \
{                                                                          \
    if (pobj) {                                                            \
        RWWithObjectOutputContext ctxt(str);                               \
        if (str.needToWrite(pobj)) {                                       \
            str.newObjectMarker();                                         \
            str.writeTypeInfo(RWTypeInfo::symbol(                          \
                typeid(*(const_cast<T*>(pobj)))));                         \
            str.rememberObject(pobj);                                      \
            if (rwStreamType(pobj) != RW_NESTED_OBJECT  &&                 \
                rwStreamType(pobj) != RW_SEQ &&                            \
                rwStreamType(pobj) != RW_ASSOC) {                          \
                    str.startBlock(                                        \
                        RWTypeInfo::symbol(                                \
                            typeid(*(const_cast<T*>(pobj)))));             \
                    str << *pobj;                                          \
                    str.endBlock();                                        \
                }                                                          \
            else                                                           \
                str << *pobj;                                              \
        }                                                                  \
    }                                                                      \
    else {                                                                 \
        str.writeNullPtr();                                                \
    }                                                                      \
    return str;                                                            \
}

// Extractor operator - global functions
#define RW_SERIAL_DECLARE_GLOBAL_EXTRACTOR_PTR(Class,EXPORT)               \
    EXPORT RWObjectInputStream&                                            \
    operator>> (RWObjectInputStream&, Class*&);

// This macro is used by define streamable base, and is not intended
// to appear directly in streamable class code.  It defines an
// operator to stream in a polymorphic type as a base pointer.
#define RW_SERIAL_DEFINE_GLOBAL_EXTRACTOR_PTR(Class)                       \
RWObjectInputStream& operator>>(RWObjectInputStream& str,                  \
                                Class*& pobj) {                            \
    RWWithObjectInputContext ctx(str);                                     \
    if (!str.isGood())                                                     \
        return str;                                                        \
                                                                           \
    const void* vp = rwnil;                                                \
    if (str.needToRead(vp)) {                                              \
        vp = str.getNewObject(&(typeid(Class)));                           \
        if (vp != rwnil) {                                                 \
            pobj = static_cast<Class*>(const_cast<void*>(vp));             \
            str >> *pobj;                                                  \
        }                                                                  \
        else {                                                             \
            pobj = 0;                                                      \
        }                                                                  \
    }                                                                      \
    else if (vp != rwnil)                                                  \
        pobj = static_cast<Class*>(const_cast<void*>(vp));                 \
    else                                                                   \
        pobj = 0;                                                          \
                                                                           \
    return str;                                                            \
}


#define RW_SERIAL_DEFINE_LIBRARY_GLOBAL_EXTRACTOR_PTR(T)                   \
RWObjectInputStream& operator>>(RWObjectInputStream& str, T*& pobj)        \
{                                                                          \
    RWWithObjectInputContext ctxt(str);                                    \
    if (!str.isGood()) {                                                   \
        return str;                                                        \
    }                                                                      \
    const void* vp = rwnil;                                                \
    if (str.needToRead(vp)) {                                              \
        vp = str.getNewObject(&(typeid(T)));                               \
        if (vp != rwnil) {                                                 \
            pobj = static_cast<T*>(const_cast<void*>(vp));                 \
            RWWithObjectInputContext ctxt(str);                            \
            if (rwStreamType(pobj) != RW_NESTED_OBJECT) {                  \
                str.startBlock();                                          \
                str >> *pobj;                                              \
                str.endBlock();                                            \
            }                                                              \
            else                                                           \
                str >> *pobj;                                              \
        }                                                                  \
    }                                                                      \
    else if (vp != rwnil) {                                                \
        pobj = static_cast<T*>(const_cast<void*>(vp));                     \
    }                                                                      \
    else                                                                   \
        pobj = 0;                                                          \
                                                                           \
    return str;                                                            \
}



//--When a derived class has a non-public default constructor, use this
//--macro within the derived class declaration for each base class that
//--might be streamed in as a base pointer.
#define RW_SERIAL_DECLARE_BASE_EXTERNAL_CTOR(Derived,Base)                 \
    friend class RWTFactory0Ctor<Base*, Derived>;

#define RW_SERIAL_MK_CREATOR(Base,Derived)                                 \
    RWTFactory0Ctor<Base*,Derived>::ctor


//--Helper macros for defining the 'streamContents()' member function.
//--This member function handles streaming of parents and data members
//--in both directions, thus providing built-in symmetry.
//--

//--Use this macro to identify parent classes that need to be
//--streamed.  If more than one parent, use multiple calls.  If class
//--uses external serialization, then use 'RW_STREAM_EXTERNAL_PARENT'
//--instead of this macro.
#define RW_SERIAL_STREAM_BASE(Base)                                        \
    if (out)                                                               \
        out->startParent(                                                  \
            RWTypeInfo::symbol(typeid((Base*)This)));                      \
    else if (in)                                                           \
        in->startParent(                                                   \
            RWTypeInfo::symbol(typeid((Base*)This)));                      \
    Base::streamContents(in, out);                                         \
    if (out)                                                               \
        out->endParent();                                                  \
    else if (in)                                                           \
        in->endParent();


//--Use this macro to identify an attribute of the class to be
//--streamed in terms of a 'get()' and 'set()' function pair.  This is
//--useful in external streaming when the internal data member is
//--private, but has public 'get()' and 'set()' functions.
#define RW_SERIAL_STREAM_ATTRIBUTE(Name, Type, get, set)                   \
    static RWSymbol Name(#Name);                                           \
    Type Name ## temp;                                                     \
    Attribute = #Name;                                                     \
    if (in && in->startMember(Attribute, TypeInfo)) {                      \
        *in >> Name ## temp;                                               \
        in->endMember();                                                   \
        This->set(Name ## temp);                                           \
    }                                                                      \
                                                                           \
    if (out) {                                                             \
        out->writeMemberInfo(Name, rwStreamType (&(Name ## temp)));        \
        *out << This->get();                                               \
        out->endMember(Name);                                              \
    }

//--Use this macro to identify an enum type attribute of the class to be
//--streamed in terms of a 'get()' and 'set()' function pair.  This is
//--useful in external streaming when the internal data member is
//--private, but has public 'get()' and 'set()' functions.
#define RW_SERIAL_STREAM_ATTRIBUTE_ENUM(Name, Type, get, set)              \
    static RWSymbol Name(#Name);                                           \
    Attribute = #Name;                                                     \
    if (in && in->startMember(Attribute, TypeInfo)) {                      \
        int Name##tempfoo;                                                 \
        *in >> Name##tempfoo;                                              \
        Type Name##temp = static_cast<Type>(Name##tempfoo);                \
        in->endMember();                                                   \
        This->set(Name ## temp);                                           \
    }                                                                      \
                                                                           \
    if (out) {                                                             \
        Type Name ## temp = This->get();                                   \
        /* Cast the enum type to an int to avoid compiler             */   \
        /* type mismatch                                              */   \
        out->writeMemberInfo(Name,  rwStreamType ((int*)0));               \
        *out << static_cast<int>(Name ## temp);                            \
        out->endMember(Name);                                              \
    }

//--Use this macro to identify a data member as an attribute of the
//--class.  If using external streaming, then the data member must be
//--public.
#define RW_SERIAL_STREAM_ATTRIBUTE_MEMBER(Name,memberName)                 \
    static RWSymbol Name(#Name);                                           \
    if (in) {                                                              \
        Attribute = #Name;                                                 \
        if (in->startMember(Attribute, TypeInfo)) {                        \
            *in >> This->memberName;                                       \
            in->endMember();                                               \
        }                                                                  \
    }                                                                      \
    if (out) {                                                             \
        out->writeMemberInfo(Name,                                         \
                             rwStreamType (&(This->memberName)));          \
        *out << This->memberName;                                          \
        out->endMember(Name);                                              \
    }


// Helper function to handle casting from an int to an enumeration
// value when the type of the enumeration is unavailable in the
// macro definition
template <class T>
T rwConvertFromIntToT(int value, T* = 0)
{
    return T(value);
}

//--Use this macro to identify a data member as an enum type attribute of
//--the class.  If using external streaming, then the data member must be
//--public.
#define RW_SERIAL_STREAM_ATTRIBUTE_MEMBER_ENUM(Name,memberName)            \
    static RWSymbol Name(#Name);                                           \
    if (in) {                                                              \
        Attribute = #Name;                                                 \
        if (in->startMember(Attribute, TypeInfo)) {                        \
            /* Create a local copy of the enum to assure that */           \
            /* the enum is interpreted as an int.             */           \
            int tmp = This->memberName;                                    \
            *in >> tmp;                                                    \
            This->memberName =                                             \
                rwConvertFromIntToT(tmp, &(This->memberName));             \
            in->endMember();                                               \
        }                                                                  \
    }                                                                      \
    if (out) {                                                             \
        /* Cast the enum type to an int to avoid compiler     */           \
        /* type mismatch                                      */           \
        out->writeMemberInfo(Name,  rwStreamType ((int*)0));               \
        *out << static_cast<int>(This->memberName);                        \
        out->endMember(Name);                                              \
    }

//--If it is not possible to include
//--'RW_DECLARE_VIRTUAL_STREAM_FNS()' within the class declaration for
//--the target class, then you can use external serialization as an
//--alternative.  Macros below that include the word 'EXTERNAL' in their
//--name are external serialization counterparts to the normal
//--serialization macros. An overloaded 'streamContents()' global
//--function replaces the virtual member function 'streamContents()'.
//--

#define RW_SERIAL_DECLARE_GLOBAL_STREAMER(Class,EXPORT)                    \
    EXPORT void                                                            \
    streamContents(Class* This,                                            \
                   RWObjectInputStream* in,                                \
                   RWObjectOutputStream* out);

#define RW_SERIAL_DEFINE_GLOBAL_INSERTER_REF(Class)                        \
    inline RWObjectOutputStream&                                           \
    operator<<(RWObjectOutputStream& str,                                  \
               const Class& cl) {                                          \
        RWWithObjectOutputContext outputContext(str);                      \
        str.startBlock(RWTypeInfo::symbol(typeid(Class)));                 \
        RWTExtSerialFunctors<Class>::save_(&cl, str);                      \
        str.endBlock();                                                    \
        return str;                                                        \
    }

#define RW_SERIAL_DEFINE_GLOBAL_EXTRACTOR_REF(Class)                       \
    inline RWObjectInputStream&                                            \
    operator>>(RWObjectInputStream& str,                                   \
               Class& cl) {                                                \
        RWWithObjectInputContext inputContext(str);                        \
        str.startBlock();                                                  \
        RWTExtSerialFunctors<Class>::restore_(&cl, str);                   \
        str.endBlock();                                                    \
        return str;                                                        \
    }

#define RW_SERIAL_DEFINE_GLOBAL_STREAMTYPE(Class)                          \
    inline RWStreamType rwStreamType(const Class*) {                       \
        return RW_NESTED_OBJECT;                                           \
    }

#define RW_SERIAL_DEFINE_GLOBAL_STREAMER_PROLOG(Class)                     \
void streamContents(Class* This,                                           \
                    RWObjectInputStream* in,                               \
                    RWObjectOutputStream* out)                             \
{                                                                          \
    RWSymbol Attribute;                                                    \
    RWStreamType TypeInfo (RW_UNSUPPORTED);                                \
                                                                           \
    RW_UNUSED(TypeInfo);                                                   \
    RW_UNUSED(This);                                                       \
    RW_UNUSED(in);                                                         \
    RW_UNUSED(out);

//--Use this macro to identify parent classes that need to be
//--streamed.  If more than one parent, use multiple calls.
#define RW_SERIAL_EXTERNAL_STREAM_BASE(Base)                               \
    if (out) {                                                             \
        out->startParent(                                                  \
            RWTypeInfo::symbol(typeid((Base*)This)));                      \
    }                                                                      \
    else if (in) {                                                         \
        in->startParent(                                                   \
            RWTypeInfo::symbol(typeid((Base*)This)));                      \
    }                                                                      \
    streamContents((Base*)This, in, out);                                  \
    if (out)                                                               \
        out->endParent();                                                  \
    else if (in)                                                           \
        in->endParent();


/**************************  Documented macros ****************************/

/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators, for streaming Rogue Wave
 * value-based template collections. Intrusive or external. Put in header
 * file \e outside the class declaration.
 */
#define RW_DECLARE_STREAMABLE_VAL_SEQUENCE(container)                      \
template <class T, class A>                                                \
RWStreamType                                                               \
rwStreamType(const container<T, A>*) {                                     \
    return RW_SEQ;                                                         \
}                                                                          \
template <class T, class A>                                                \
    RWObjectOutputStream&                                                  \
    operator<<(RWObjectOutputStream& strm, const container<T, A>& seq)     \
    {                                                                      \
        RWWithObjectOutputContext outputContext(strm);                     \
        size_t len = seq.entries();                                        \
        strm.startSequence(                                                \
            static_cast<int> (len),  rwStreamType ((T*)0),                 \
            RWTypeInfo::symbol(typeid(container<T, A>)));                  \
        for (size_t i = 0; i < len; i++) {                                 \
            strm.startElement(static_cast<int> (i));                       \
            strm << seq[i];                                                \
            strm.endElement();                                             \
        }                                                                  \
        strm.endSequence();                                                \
        return strm;                                                       \
    }                                                                      \
template <class T, class A>                                                \
    RWObjectInputStream&                                                   \
    operator>>(RWObjectInputStream& strm, container<T, A>& seq)            \
    {                                                                      \
        RWWithObjectInputContext inputContext(strm);                       \
        int len;                                                           \
        RWStreamType tempType;                                             \
        strm.startSequence(len, tempType);                                 \
        for (int i = 0; i < len; i++) {                                    \
            T temp = T();                                                  \
            strm.startElement(i);                                          \
            strm >> temp;                                                  \
            strm.endElement();                                             \
            seq.insert(temp);                                              \
        }                                                                  \
        strm.endSequence();                                                \
        return strm;                                                       \
    }

// End of RW_DECLARE_STREAMABLE_VAL_SEQUENCE

/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators, for streaming Rogue Wave
 * pointer-based template collections. Intrusive or external. Put in header
 * file \e outside the class declaration.
 */
#define RW_DECLARE_STREAMABLE_PTR_SEQUENCE(container)                      \
template <class T, class Alloc>                                            \
RWStreamType                                                               \
rwStreamType(const container<T,Alloc>*) {                                  \
   return RW_SEQ;                                                          \
}                                                                          \
template <class T, class A>                                                \
   RWObjectOutputStream&                                                   \
   operator<<(RWObjectOutputStream& strm, const container<T, A>& seq)      \
{                                                                          \
  RWWithObjectOutputContext outputContext(strm);                           \
  int len = (int)(seq.entries());                                          \
  strm.startSequence(                                                      \
      len,  rwStreamType ((T**)0),                                         \
      RWTypeInfo::symbol(typeid(container<T, A>)));                        \
  for (int i = 0; i < len; i++) {                                          \
    strm.startElement(i);                                                  \
    strm << seq[static_cast<size_t> (i)];                                  \
    strm.endElement();                                                     \
  }                                                                        \
  strm.endSequence();                                                      \
  return strm;                                                             \
}                                                                          \
template <class T, class A>                                                \
   RWObjectInputStream&                                                    \
   operator>>(RWObjectInputStream& strm, container<T, A>& seq)             \
{                                                                          \
   RWWithObjectInputContext inputContext(strm);                            \
   int len;                                                                \
   RWStreamType tempType;                                                  \
   strm.startSequence(len, tempType);                                      \
   T* temp;                                                                \
   for (int i = 0; i < len; i++) {                                         \
      temp = 0;                                                            \
      strm.startElement(i);                                                \
      strm >> temp;                                                        \
      strm.endElement();                                                   \
      seq.insert(temp);                                                    \
   }                                                                       \
   strm.endSequence();                                                     \
   return strm;                                                            \
}
// End of RW_DECLARE_STREAMABLE_PTR_SEQUENCE

/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators, for streaming C++ Standard
 * Library sequences. Intrusive or external. Put in header file \e outside
 * the class declaration.
 */
#define RW_DECLARE_STREAMABLE_STD_SEQUENCE(container)                      \
template <class T, class Alloc>                                            \
RWStreamType                                                               \
rwStreamType(const container<T,Alloc>*) {                                  \
   return RW_SEQ;                                                          \
}                                                                          \
template <class T, class Alloc>                                            \
   RWObjectOutputStream&                                                   \
   operator<<(RWObjectOutputStream& strm, const container<T,Alloc>& seq)   \
{                                                                          \
  RWWithObjectOutputContext outputContext(strm);                           \
  int len = (int)(seq.size());                                             \
  strm.startSequence(                                                      \
      len,  rwStreamType ((T*)0),                                          \
      RWTypeInfo::symbol(typeid(container<T,Alloc>)));                     \
  int i = 0;                                                               \
  for (typename container<T,Alloc>::const_iterator                         \
           it = seq.begin();                                               \
       it != seq.end(); it++, i++) {                                       \
    strm.startElement(i);                                                  \
    strm << *it;                                                           \
    strm.endElement();                                                     \
  }                                                                        \
  strm.endSequence();                                                      \
  return strm;                                                             \
}                                                                          \
template <class T, class Alloc>                                            \
   RWObjectInputStream&                                                    \
   operator>>(RWObjectInputStream& strm, container<T,Alloc>& seq)          \
{                                                                          \
   RWWithObjectInputContext inputContext(strm);                            \
   int len;                                                                \
   RWStreamType tempType;                                                  \
   strm.startSequence(len, tempType);                                      \
   for (int i = 0; i < len; i++) {                                         \
      T temp = T();                                                        \
      strm.startElement(i);                                                \
      strm >> temp;                                                        \
      strm.endElement();                                                   \
      seq.insert(seq.end(),temp);                                          \
   }                                                                       \
   strm.endSequence();                                                     \
   return strm;                                                            \
}
// End of RW_DECLARE_STREAMABLE_STD_SEQUENCE

//--Use this macro to enable streaming of a C++ Standard Library
//--stack class template or subtype.  Pass the name
//--of the class to this macro without the template parameter list.
//--e.g.  RW_DECLARE_STREAMABLE_STD_STACK(stack)
#define RW_DECLARE_STREAMABLE_STD_STACK(container)                         \
template <class T, class Cont>                                             \
RWStreamType                                                               \
rwStreamType(const container<T,Cont>*) {                                   \
   return RW_SEQ;                                                          \
}                                                                          \
template <class T, class Cont>                                             \
   RWObjectOutputStream&                                                   \
   operator<<(RWObjectOutputStream& strm, container<T,Cont>& seq)          \
{                                                                          \
  RWWithObjectOutputContext outputContext(strm);                           \
  int len = static_cast<int> (seq.size());                                 \
  strm.startSequence(                                                      \
      len,  rwStreamType ((T*)0),                                          \
      RWTypeInfo::symbol(typeid(container<T,Cont>)));                      \
  int i = 0;                                                               \
  container<T> tcont;                                                      \
  while(!seq.empty()){                                                     \
    tcont.push(seq.top());                                                 \
    seq.pop();                                                             \
  }                                                                        \
  while(!tcont.empty()) {                                                  \
    strm.startElement(i);                                                  \
    strm << tcont.top();                                                   \
    strm.endElement();                                                     \
    seq.push(tcont.top());                                                 \
    tcont.pop();                                                           \
    i++;                                                                   \
  }                                                                        \
  strm.endSequence();                                                      \
  return strm;                                                             \
}                                                                          \
template <class T, class Cont>                                             \
   RWObjectInputStream&                                                    \
   operator>>(RWObjectInputStream& strm, container<T,Cont>& seq)           \
{                                                                          \
   RWWithObjectInputContext inputContext(strm);                            \
   int len;                                                                \
   RWStreamType tempType;                                                  \
   strm.startSequence(len, tempType);                                      \
   for (int i = 0; i < len; ++i) {                                         \
      T temp = T();                                                        \
      strm.startElement(i);                                                \
      strm >> temp;                                                        \
      strm.endElement();                                                   \
      seq.push(temp);                                                      \
   }                                                                       \
   strm.endSequence();                                                     \
   return strm;                                                            \
}

// End of RW_DECLARE_STREAMABLE_STD_STACK

//--Use this macro to enable streaming of a C++ Standard Library
//--queue class template or subtype.  Pass the name
//--of the class to this macro without the template parameter list.
//--e.g.  RW_DECLARE_STREAMABLE_STD_QUEUE(queue)
#define RW_DECLARE_STREAMABLE_STD_QUEUE(container)                         \
template <class T, class Cont>                                             \
RWStreamType                                                               \
rwStreamType(const container<T,Cont>*) {                                   \
   return RW_SEQ;                                                          \
}                                                                          \
template <class T, class Cont>                                             \
   RWObjectOutputStream&                                                   \
   operator<<(RWObjectOutputStream& strm,                                  \
              container<T,Cont>& seq)                                      \
{                                                                          \
  RWWithObjectOutputContext outputContext(strm);                           \
  int len = static_cast<int> (seq.size());                                 \
  strm.startSequence(len,  rwStreamType ((T*)0),                           \
                     RWTypeInfo::symbol(typeid(container<T,Cont>)));       \
  for (int i=0; i<len; ++i) {                                              \
    strm.startElement(i);                                                  \
    strm << seq.front();                                                   \
    strm.endElement();                                                     \
    seq.push(seq.front());                                                 \
    seq.pop();                                                             \
  }                                                                        \
  strm.endSequence();                                                      \
  return strm;                                                             \
}                                                                          \
template <class T, class Cont>                                             \
   RWObjectInputStream&                                                    \
   operator>>(RWObjectInputStream& strm,                                   \
              container<T,Cont>& seq)                                      \
{                                                                          \
   RWWithObjectInputContext inputContext(strm);                            \
   int len;                                                                \
   RWStreamType tempType;                                                  \
   strm.startSequence(len, tempType);                                      \
   for (int i = 0; i < len; i++) {                                         \
      T temp = T();                                                        \
      strm.startElement(i);                                                \
      strm >> temp;                                                        \
      strm.endElement();                                                   \
      seq.push(temp);                                                      \
   }                                                                       \
   strm.endSequence();                                                     \
   return strm;                                                            \
}

// End of RW_DECLARE_STREAMABLE_STD_QUEUE

//--Use this macro to enable streaming of a C++ Standard Library
//--set class template such as set.  Pass the name
//--of the class to this macro without the template parameter list.
//--e.g.  RW_DECLARE_STREAMABLE_STD_SET(set)
#define RW_DECLARE_STREAMABLE_STD_SET(container)                           \
template <class T, class Compare, class Alloc>                             \
RWStreamType                                                               \
rwStreamType(const container<T,Compare,Alloc>*) {                          \
   return RW_SEQ;                                                          \
}                                                                          \
template <class T, class Compare, class Alloc>                             \
   RWObjectOutputStream&                                                   \
   operator<<(RWObjectOutputStream& strm,                                  \
              const container<T,Compare,Alloc>& seq)                       \
{                                                                          \
  RWWithObjectOutputContext outputContext(strm);                           \
  int len = static_cast<int> (seq.size());                                 \
  strm.startSequence(                                                      \
      len,  rwStreamType ((T*)0),                                          \
      RWTypeInfo::symbol(typeid(container<T,Compare,Alloc>)));             \
  int i = 0;                                                               \
  for (typename container<T,Compare,Alloc>::const_iterator                 \
           it = seq.begin();                                               \
       it != seq.end(); it++, i++) {                                       \
    strm.startElement(i);                                                  \
    strm << *it;                                                           \
    strm.endElement();                                                     \
  }                                                                        \
  strm.endSequence();                                                      \
  return strm;                                                             \
}                                                                          \
template <class T, class Compare, class Alloc>                             \
   RWObjectInputStream&                                                    \
   operator>>(RWObjectInputStream& strm,                                   \
              container<T,Compare,Alloc>& seq)                             \
{                                                                          \
   RWWithObjectInputContext inputContext(strm);                            \
   int len;                                                                \
   RWStreamType tempType;                                                  \
   strm.startSequence(len, tempType);                                      \
   for (int i = 0; i < len; i++) {                                         \
      T temp = T();                                                        \
      strm.startElement(i);                                                \
      strm >> temp;                                                        \
      strm.endElement();                                                   \
      seq.insert(temp);                                                    \
   }                                                                       \
   strm.endSequence();                                                     \
   return strm;                                                            \
}

// End of RW_DECLARE_STREAMABLE_STD_SET


/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators, for streaming maps
 * (associations) of value-based templates. Intrusive or external. Put in
 * header file \e outside the class declaration.
 */
#define RW_DECLARE_STREAMABLE_VAL_MAP(container)                           \
template <class K, class V, class H, class E, class A>                     \
RWStreamType                                                               \
rwStreamType(const container<K,V,H,E,A>*) {                                \
   return RW_ASSOC;                                                        \
}                                                                          \
template <class K, class V, class H, class E, class A>                     \
RWObjectOutputStream&                                                      \
operator<<(RWObjectOutputStream& str, const container<K,V,H,E,A>& c)       \
{                                                                          \
  RWWithObjectOutputContext outputContext(str);                            \
  str.startMap(                                                            \
      static_cast<int> (c.entries()),  rwStreamType ((K*)0),               \
       rwStreamType ((V*)0),                                               \
      RWTypeInfo::symbol(                                                  \
          typeid(container<K,V,H,E,A>)));                                  \
  for (typename container<K,V,H,E,A>::const_iterator iter = c.begin();     \
          iter != c.end(); ++iter) {                                       \
    str.startAssocKey();                                                   \
    str << iter->first;                                                    \
    str.startAssocValue();                                                 \
    str << iter->second;                                                   \
    str.endAssoc();                                                        \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}                                                                          \
template <class K, class V, class H, class E, class A>                     \
RWObjectInputStream&                                                       \
operator>>(RWObjectInputStream& str, container<K,V,H,E,A>& c)              \
{                                                                          \
  RWWithObjectInputContext inputContext(str);                              \
  int count = 0;                                                           \
  RWStreamType tempKey;                                                    \
  RWStreamType tempVal;                                                    \
  str.startMap(count, tempKey, tempVal);                                   \
  for (int i = 0; i < count; i++) {                                        \
    K key = K();                                                           \
    V val = V();                                                           \
    str.startAssocKey();                                                   \
    str >> key;                                                            \
    str.startAssocValue();                                                 \
    str >> val;                                                            \
    str.endAssoc();                                                        \
    c.insertKeyAndValue(key, val);                                         \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}
// End of RW_DECLARE_STREAMABLE_VAL_MAP

/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators, for streaming maps
 * (associations) of pointers. Intrusive or external. Put in header file
 * \e outside the class declaration.
 */
#define RW_DECLARE_STREAMABLE_PTR_MAP(container)                           \
template <class K, class V, class H, class E, class A>                     \
RWStreamType                                                               \
rwStreamType(const container<K,V,H,E,A>*) {                                \
   return RW_ASSOC;                                                        \
}                                                                          \
template <class K, class V, class H, class E, class A>                     \
RWObjectOutputStream&                                                      \
operator<<(RWObjectOutputStream& str, const container<K,V,H,E,A>& c)       \
{                                                                          \
  RWWithObjectOutputContext outputContext(str);                            \
  str.startMap(                                                            \
      c.entries(),  rwStreamType ((K**)0),                                 \
       rwStreamType ((V**)0),                                              \
      RWTypeInfo::symbol(                                                  \
          typeid(container<K,V,H,E,A>)));                                  \
  for (typename container<K,V,H,E,A>::const_iterator iter = c.begin();     \
          iter != c.end(); ++iter) {                                       \
    str.startAssocKey();                                                   \
    str << iter->first;                                                    \
    str.startAssocValue();                                                 \
    str << iter->second;                                                   \
    str.endAssoc();                                                        \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}                                                                          \
template <class K, class V, class H, class E, class A>                     \
RWObjectInputStream&                                                       \
operator>>(RWObjectInputStream& str, container<K,V,H,E,A>& c)              \
{                                                                          \
  RWWithObjectInputContext inputContext(str);                              \
  int count = 0;                                                           \
  RWStreamType tempKey;                                                    \
  RWStreamType tempVal;                                                    \
  str.startMap(count, tempKey, tempVal);                                   \
  K* key;                                                                  \
  V* value;                                                                \
  for (int i = 0; i < count; i++) {                                        \
    key = 0;                                                               \
    value = 0;                                                             \
    str.startAssocKey();                                                   \
    str >> key;                                                            \
    str.startAssocValue();                                                 \
    str >> value;                                                          \
    str.endAssoc();                                                        \
    c.insertKeyAndValue(key, value);                                       \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}

// End of RW_DECLARE_STREAMABLE_PTR_MAP

/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators, for streaming maps
 * (associations) of C++ Standard Library types. Intrusive or external. Put
 * in header file \e outside the class declaration.
 */
#define RW_DECLARE_STREAMABLE_STD_MAP(container)                           \
template <class K, class V, class C, class A>                              \
RWStreamType                                                               \
rwStreamType(const container<K,V,C,A>*) {                                  \
   return RW_ASSOC;                                                        \
}                                                                          \
template <class K, class V, class C, class A>                              \
RWObjectOutputStream&                                                      \
operator<<(RWObjectOutputStream& str,                                      \
           const container<K,V,C,A>& c)                                    \
{                                                                          \
  RWWithObjectOutputContext outputContext(str);                            \
  typename container<K,V,C,A>::const_iterator iter = c.begin();            \
  str.startMap(                                                            \
      (int)(c.size()),  rwStreamType ((K*)0),                              \
       rwStreamType ((V*)0),                                               \
      RWTypeInfo::symbol(typeid(container<K,V,C,A>)));                     \
  while (iter != c.end()) {                                                \
    str.startAssocKey();                                                   \
    str << (*iter).first;                                                  \
    str.startAssocValue();                                                 \
    str << (*iter).second;                                                 \
    str.endAssoc();                                                        \
    ++iter;                                                                \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}                                                                          \
template <class K, class V, class C, class A>                              \
RWObjectInputStream&                                                       \
operator>>(RWObjectInputStream& str, container<K,V,C,A>& c)                \
{                                                                          \
  RWWithObjectInputContext inputContext(str);                              \
  int count = 0;                                                           \
  RWStreamType tempKey;                                                    \
  RWStreamType tempVal;                                                    \
  str.startMap(count, tempKey, tempVal);                                   \
  for (int i = 0; i < count; i++) {                                        \
    K key = K();                                                           \
    V val = V();                                                           \
    str.startAssocKey();                                                   \
    str >> key;                                                            \
    str.startAssocValue();                                                 \
    str >> val;                                                            \
    str.endAssoc();                                                        \
    c.insert(                                                              \
        c.end(),typename container<K,V,C,A>::value_type(key, val));        \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}

// End of RW_DECLARE_STREAMABLE_STD_MAP

//--Use this macro to enable streaming of a Rogue Wave value based
//--set class template such as RWTValHashSet.  Pass the name
//--of the class to this macro without the template parameter list.
//--e.g.  RW_DECLARE_STREAMABLE_VAL_SET(RWTValHashSet)
#define RW_DECLARE_STREAMABLE_VAL_SET(container)                           \
template <class T, class H, class E, class A>                              \
RWStreamType                                                               \
rwStreamType(const container<T,H,E,A>*) {                                  \
    return RW_SEQ;                                                         \
}                                                                          \
template <class T, class H, class E, class A>                              \
RWObjectOutputStream                                                       \
operator<<(RWObjectOutputStream& strm, const container<T,H,E,A>& seq)      \
{                                                                          \
    RWWithObjectOutputContext outputContext(strm);                         \
                                                                           \
    int len = seq.entries();                                               \
    int i = 0;                                                             \
    strm.startSequence(                                                    \
        len,  rwStreamType ((T*)0),                                        \
        RWTypeInfo::symbol(                                                \
            typeid(container<T,H,E,A>)));                                  \
                                                                           \
    for (typename container<T,H,E,A>::                                     \
             const_iterator it = seq.begin();                              \
         it != seq.end(); it++, i++) {                                     \
        strm.startElement(i);                                              \
        strm << *it;                                                       \
        strm.endElement();                                                 \
    }                                                                      \
    strm.endSequence();                                                    \
    return strm;                                                           \
}                                                                          \
                                                                           \
template <class T, class H, class E, class A>                              \
RWObjectInputStream&                                                       \
operator>>(RWObjectInputStream& strm, container<T,H,E,A>& seq)             \
{                                                                          \
    RWWithObjectInputContext inputContext(strm);                           \
                                                                           \
    int len;                                                               \
    RWStreamType tempType;                                                 \
    strm.startSequence(len, tempType);                                     \
                                                                           \
    for (int i = 0; i < len; i++) {                                        \
        T temp = T();                                                      \
        strm.startElement(i);                                              \
        strm >> temp;                                                      \
        strm.endElement();                                                 \
        seq.insert(temp);                                                  \
    }                                                                      \
    strm.endSequence();                                                    \
    return strm;                                                           \
}

// End of RW_DECLARE_STREAMABLE_VAL_SET

//--Use this macro to enable streaming of a Rogue Wave pointer based
//--set class template such as RWTHashSet.  Pass the name
//--of the class to this macro without the template parameter list.
//--e.g.  RW_DECLARE_STREAMABLE_PTR_SET(RWTPtrHashSet)
#define RW_DECLARE_STREAMABLE_PTR_SET(container)                           \
template <class T, class H, class E, class A>                              \
RWStreamType                                                               \
rwStreamType(const container<T,H,E,A>*) {                                  \
    return RW_SEQ;                                                         \
}                                                                          \
template <class T, class H, class E, class A>                              \
RWObjectOutputStream&                                                      \
operator<<(RWObjectOutputStream& strm, const container<T,H,E,A>& seq)      \
{                                                                          \
    RWWithObjectOutputContext outputContext(strm);                         \
                                                                           \
    int len = seq.entries();                                               \
    int i = 0;                                                             \
    strm.startSequence(                                                    \
        len,  rwStreamType ((T**)0),                                       \
        RWTypeInfo::symbol(                                                \
            typeid(container<T,H,E,A>)));                                  \
                                                                           \
    for (typename container<T,H,E,A>::const_iterator it = seq.begin();     \
         it != seq.end(); it++, i++) {                                     \
        strm.startElement(i);                                              \
        strm << *it;                                                       \
        strm.endElement();                                                 \
    }                                                                      \
    strm.endSequence();                                                    \
    return strm;                                                           \
}                                                                          \
                                                                           \
template <class T, class H, class E, class A>                              \
RWObjectInputStream&                                                       \
operator>>(RWObjectInputStream& strm, container<T,H,E,A>& seq)             \
{                                                                          \
    RWWithObjectInputContext inputContext(strm);                           \
                                                                           \
    int len;                                                               \
    RWStreamType tempType;                                                 \
    strm.startSequence(len, tempType);                                     \
                                                                           \
    T* temp;                                                               \
    for (int i = 0; i < len; i++) {                                        \
        temp = 0;                                                          \
        strm.startElement(i);                                              \
        strm >> temp;                                                      \
        strm.endElement();                                                 \
        seq.insert(temp);                                                  \
    }                                                                      \
                                                                           \
    strm.endSequence();                                                    \
    return strm;                                                           \
}

// End of RW_DECLARE_STREAMABLE_PTR_SET


/*********************** End of container macros **************************/


//
// Both intrusive and external serialization
//

/**
 * \ingroup serialization_package_macros
 *
 * Ends the \c streamContents() function.
 */
#define RW_END_STREAM_CONTENTS                                             \
        RW_SERIAL_DEFINE_STREAMER_EPILOG


// Declarations of the streaming pointers
#define RW_DECLARE_STREAMING_POINTER_OPERATORS(Class)                      \
        RW_SERIAL_DECLARE_GLOBAL_INSERTER_PTR(Class,RW_SERIAL_DONT_EXPORT) \
        RW_SERIAL_DECLARE_GLOBAL_EXTRACTOR_PTR(Class,RW_SERIAL_DONT_EXPORT)

//--This  macro  implements the  declarations  from  above  and should  be
//--included in a source module  corresponding to the header file where it
//--appears.
#define RW_DEFINE_STREAMING_POINTER_OPERATORS(Class)                       \
        RW_SERIAL_DEFINE_GLOBAL_INSERTER_PTR(Class)                        \
        RW_SERIAL_DEFINE_GLOBAL_INSERTER_PTR_CONST(Class)                  \
        RW_SERIAL_DEFINE_GLOBAL_EXTRACTOR_PTR(Class)

// Defines insertion and extraction operators for class template pointers
#define RW_DEFINE_STREAMABLE_POINTER_OPERATORS_T_1(Class)                  \
        template<typename T>                                               \
        RW_SERIAL_DEFINE_GLOBAL_INSERTER_PTR(Class<T>)                     \
                                                                           \
        template<typename T>                                               \
        RW_SERIAL_DEFINE_GLOBAL_INSERTER_PTR_CONST(Class<T>)               \
                                                                           \
       template<typename T>                                                \
        RW_SERIAL_DEFINE_GLOBAL_EXTRACTOR_PTR(Class<T>)

/**
 * \ingroup serialization_package_macros
 *
 * For classes derived from a serializable base class. Calls
 * \c streamContents() on the base class to stream the contents of the base
 * class before streaming the derived class. Put in source file for class.
 * For intrusive serialization only. (For external, use
 * #RW_STREAM_EXTERNAL_PARENT.)
 */
#define RW_STREAM_PARENT(Base) RW_SERIAL_STREAM_BASE(Base)

/**
 * \ingroup serialization_package_macros
 *
 * Use this macro to identify an attribute of the class to be streamed in
 * terms of a \c get() and \c set() function pair. This is useful in
 * external streaming when the internal data member is private, but has
 * public \c get() and \c set() functions.
 */
#define RW_STREAM_ATTR_GET_SET(Name,Type,get,set)                          \
        RW_SERIAL_STREAM_ATTRIBUTE(Name, Type, get, set)

/**
 * \ingroup serialization_package_macros
 *
 * Use this macro to identify an enum type attribute of the class to be
 * streamed in terms of a \c get() and \c set() function pair. This is
 * useful in external streaming when the internal data member is private,
 * but has public \c get() and \c set() functions.
 */
#define RW_STREAM_ATTR_ENUM_GET_SET(Name, Type, get, set)                  \
        RW_SERIAL_STREAM_ATTRIBUTE_ENUM(Name, Type, get, set)

/**
 * \ingroup serialization_package_macros
 *
 * Use this macro to identify a data member as an attribute of the class. If
 * using external streaming, then the data member must be public.
 */
#define RW_STREAM_ATTR_MEMBER(Name,memberName)                             \
        RW_SERIAL_STREAM_ATTRIBUTE_MEMBER(Name,memberName)

/**
 * \ingroup serialization_package_macros
 *
 * Use this macro to identify a data member as an enum type attribute of the
 * class. If using external streaming, then the data member must be public.
 */
#define RW_STREAM_ATTR_ENUM_MEMBER(Name, memberName)                       \
        RW_SERIAL_STREAM_ATTRIBUTE_MEMBER_ENUM(Name,memberName)

/**
 * \ingroup serialization_package_macros
 *
 * Used to insert custom code into stream contents that only executes during
 * input operations.
 */
#define RW_WHEN_INPUT(body) if (in) { body }

/**
 * \ingroup serialization_package_macros
 *
 * Used to insert custom code into stream contents that only executes during
 * output operations.
 */
#define RW_WHEN_OUTPUT(body) if (out) { body }

/**
 * \ingroup serialization_package_macros
 *
 * Used in custom code to access the object input stream
 */
#define RW_INPUT_STREAM     *in

/**
 * \ingroup serialization_package_macros
 *
 * Used in custom code to access the object output stream
 */
#define RW_OUTPUT_STREAM    *out




//
// Intrusive serialization
//


/**
 * \ingroup serialization_package_macros
 *
 * Starts the \c streamContents() function. Put in source file for class.
 * For intrusive serialization only. (For external, use
 * #RW_BEGIN_EXTERNAL_STREAM_CONTENTS.)
 */
#define RW_BEGIN_STREAM_CONTENTS(Class)                                    \
        RW_SERIAL_DEFINE_MEMBER_STREAMER_PROLOG(Class)


/**
 * \ingroup serialization_package_macros
 *
 * When a derived class has a non-public default constructor, use this macro
 * within the derived class declaration for each base class that might be
 * streamed in as a polymorphic pointer.
 */
#define RW_DECLARE_FRIEND_CTOR_METHOD(Derived,Base)                        \
        RW_SERIAL_DECLARE_BASE_EXTERNAL_CTOR(Derived,Base)

//--For every concrete 'Derived', and for every streamable 'Class'
//--pointer type which might hold a 'Derived' instance, a source
//--module containing this macro must be linked so that the
//--'Derived' can be factored.  If the class requires non-standard
//--factory behavior, then it iss up to the class designer, to replace
//--this macro with their custom code.

// Declarations
#define RW_DECLARE_STREAMING_FACTORY(Class)                                \
        RW_DECLARE_SERIAL_FACTORY_SPECIALIZATION(Class)

#define RW_DECLARE_STREAMABLE_AS(Class,Other)                              \
        RW_DECLARE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(Class,Other)

// Definitions
#define RW_DEFINE_STREAMING_FACTORY(Class)                                 \
        RW_DEFINE_SERIAL_FACTORY_SPECIALIZATION(Class)

#define RW_DEFINE_STREAMABLE_AS(Class,Other)                               \
        RW_DEFINE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(Class,Other)


//--Injects the necessary members for intrusive serialization
#define RW_DECLARE_VIRTUAL_STREAMING_FUNCTIONS(Class)                      \
        RW_SERIAL_DECLARE_MEMBER_STREAMER(Class)                           \
        RW_SERIAL_DEFINE_MEMBER_INSERTER (Class)                           \
        RW_SERIAL_DEFINE_MEMBER_EXTRACTOR(Class)                           \
        RW_SERIAL_DEFINE_MEMBER_STREAMTYPE(Class)                          \
private:

/**
 * \ingroup serialization_package_macros
 *
 * Declares \c streamContents(), used to add the contents of your object to
 * a virtual stream, and other things. Put in header file \e inside the
 * class declaration. For intrusive serialization only. (For external, use
 * #RW_DECLARE_EXTERNAL_STREAM_FNS).
 */
#define RW_DECLARE_VIRTUAL_STREAM_FNS(Class)                               \
        RW_DECLARE_VIRTUAL_STREAMING_FUNCTIONS(Class)

/**
 * \ingroup serialization_package_macros
 *
 * #RW_DECLARE_STREAMABLE_POINTER declares the global serialization
 * operators for pointers.
 *
 * Place #RW_DECLARE_STREAMABLE_POINTER in the header for the class (outside
 * of the class declaration). For intrusive serialization only. (For
 * external, use #RW_DECLARE_EXTERNAL_STREAMABLE_POINTER.)
 *
 * \sa
 * RW_DEFINE_STREAMABLE_POINTER
 */
#define RW_DECLARE_STREAMABLE_POINTER(Class)                               \
        RW_DECLARE_STREAMING_FACTORY(Class)                                \
        RW_DECLARE_STREAMING_POINTER_OPERATORS(Class)

/**
 * \ingroup serialization_package_macros
 *
 * #RW_DEFINE_STREAMABLE_POINTER defines the global serialization operators
 * for pointers.
 *
 * Place #RW_DEFINE_STREAMABLE_POINTER in the source file for class. For
 * intrusive serialization only. (For external, use
 * #RW_DEFINE_EXTERNAL_STREAMABLE_POINTER. For template classes, use
 * #RW_DEFINE_STREAMABLE_TEMPLATE_POINTER in the header file.)
 *
 * \sa
 * RW_DECLARE_STREAMABLE_POINTER
 */
#define RW_DEFINE_STREAMABLE_POINTER(Class)                                \
        RW_DEFINE_STREAMING_FACTORY(Class)                                 \
        RW_DEFINE_STREAMING_POINTER_OPERATORS(Class)

// Streamable as self and as base
/**
 * \ingroup serialization_package_macros
 *
 * Allows concrete derived types to be streamed out and streamed back in as
 * pointers to their base class. Place #RW_DECLARE_STREAMABLE_AS_BASE in the
 * header of your serializable class. Usually you will want to place this
 * macro after the #RW_DECLARE_STREAMABLE_AS_SELF macro. For intrusive
 * serialization only. (For external, use
 * #RW_DECLARE_EXTERNAL_STREAMABLE_AS_BASE.)
 */
#define RW_DECLARE_STREAMABLE_AS_BASE(Class,Other)                         \
        RW_DECLARE_STREAMABLE_AS(Class,Other)

/**
 * \ingroup serialization_package_macros
 *
 * Allows concrete derived types to be streamed out and streamed back in as
 * pointers to their base class. Place #RW_DEFINE_STREAMABLE_AS_BASE in the
 * source file of your serializable class. Usually you will want to place
 * this macro after the #RW_DEFINE_STREAMABLE_AS_SELF macro. For intrusive
 * serialization only. (For external, use
 * #RW_DEFINE_EXTERNAL_STREAMABLE_AS_BASE.)
 */
#define RW_DEFINE_STREAMABLE_AS_BASE(Class,Other)                          \
        RW_DEFINE_STREAMABLE_AS(Class,Other)

/**
 * \ingroup serialization_package_macros
 *
 * Apply this macro to a class if its instantiations will be serialized as
 * pointers directly to the instantiations. For intrusive serialization
 * only. (For external, use #RW_DEFINE_EXTERNAL_STREAMABLE_AS_SELF.)
 */
#define RW_DECLARE_STREAMABLE_AS_SELF(Class)                               \
        RW_DECLARE_STREAMABLE_AS(Class,Class)

/**
 * \ingroup serialization_package_macros
 *
 * \copydoc RW_DECLARE_STREAMABLE_AS_SELF
 */
#define RW_DEFINE_STREAMABLE_AS_SELF(Class)                                \
        RW_DEFINE_STREAMABLE_AS(Class,Class)


/**
 * \ingroup serialization_package_macros
 *
 * Defines the global serialization operators to provide serialization
 * support for template classes. (For other classes, use
 * #RW_DEFINE_STREAMABLE_POINTER in the source file.)
 */
#define RW_DEFINE_STREAMABLE_TEMPLATE_POINTER(Class)                       \
        RW_DEFINE_STREAMABLE_POINTER_OPERATORS_T_1(Class)

//
// External serialization
//

/**
 * \ingroup serialization_package_macros
 *
 * Starts the \c streamContents() function. Put in separate source file. For
 * external serialization only. (For intrusive, use
 * #RW_BEGIN_STREAM_CONTENTS.)
 */
#define RW_BEGIN_EXTERNAL_STREAM_CONTENTS(Class)                           \
        RW_SERIAL_DEFINE_GLOBAL_STREAMER_PROLOG(Class)

// For every concrete 'Derived', and for every streamable 'Class'
// pointer type which might hold a 'Derived' instance, a source
// module containing this macro must be linked so that the
// 'Derived' can be factored.  If the class requires non-standard
// factory behavior, then it is the class designer's responsibility to replace
// this macro with their custom code.

// Declarations
#define RW_DECLARE_EXTERNAL_STREAMABLE_AS(Class,Other)                     \
    RW_DECLARE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(Class,Other)        \
    RW_DECLARE_EXT_FUNCTORS_REGISTRAR_SPECIALIZATION(Class,Other)

// Definitions
#define RW_DEFINE_EXTERNAL_STREAMABLE_AS(Class,Other)                      \
    RW_DEFINE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(Class,Other)         \
    RW_DEFINE_EXT_FUNCTORS_REGISTRAR_SPECIALIZATION(Class,Other)


//--If it is not possible to include
//--'RW_DECLARE_VIRTUAL_STREAM_FNS()' within the class declaration for
//--the target class, then you can use external serialization as an
//--alternative.  Macros below that include the word 'EXTERNAL' in their
//--name are external serialization counterparts to the normal
//--serialization macros. An overloaded 'streamContents()' global
//--function replaces the virtual member function 'streamContents()'.
//--
//--This macro goes in a (new) header file that must be included in
//--modules that perform serialization on the target class.
#define RW_DECLARE_EXTERNAL_STREAMING_FUNCTIONS(Class)                     \
        RW_SERIAL_DECLARE_GLOBAL_STREAMER(Class,RW_SERIAL_DONT_EXPORT)     \
        RW_SERIAL_DEFINE_GLOBAL_STREAMTYPE(Class)                          \
        RW_SERIAL_DEFINE_GLOBAL_INSERTER_REF(Class)                        \
        RW_SERIAL_DEFINE_GLOBAL_EXTRACTOR_REF(Class)                       \

/**
 * \ingroup serialization_package_macros
 *
 * Declares \c streamContents(), used to add the contents of your object to
 * a virtual stream, and other things. For external serialization only. (For
 * intrusive, use #RW_DECLARE_VIRTUAL_STREAM_FNS.)
 */
#define RW_DECLARE_EXTERNAL_STREAM_FNS(Class)                              \
        RW_DECLARE_EXTERNAL_STREAMING_FUNCTIONS(Class)

/**
 * \ingroup serialization_package_macros
 *
 * For classes derived from a serializable base class. Calls
 * \c streamContents() on the base class to stream the contents of the base
 * class before streaming the derived class. Put in separate source file.
 * For external serialization only. (For intrusive, use #RW_STREAM_PARENT.)
 */
#define RW_STREAM_EXTERNAL_PARENT(Base)                                    \
        RW_SERIAL_EXTERNAL_STREAM_BASE(Base)


// Declares/defines the external save/restore functors which call
// the global streamContent overload for the appropriate derived type
#define RW_DECLARE_EXTERNAL_SAVE_RESTORE(Class)                            \
        RW_DECLARE_EXT_FUNCTORS_SPECIALIZATION(Class,RW_SERIAL_DONT_EXPORT)

#define RW_DEFINE_EXTERNAL_SAVE_RESTORE(Class)                             \
        RW_DEFINE_EXT_FUNCTORS_SPECIALIZATION(Class)

// Declare and register save/restore external functors
#define RW_DECLARE_EXTERNAL_SAVE_RESTORE_AS(Class,Other)                   \
        RW_DECLARE_EXT_FUNCTORS_REGISTRAR_SPECIALIZATION(Class,Other)

#define RW_DEFINE_EXTERNAL_SAVE_RESTORE_AS(Class,Other)                    \
        RW_DEFINE_EXT_FUNCTORS_REGISTRAR_SPECIALIZATION(Class,Other)

// Declare a streaming factory for pointers of type T
#define RW_DECLARE_EXTERNAL_STREAMING_FACTORY(Class)                       \
        RW_DECLARE_SERIAL_FACTORY_SPECIALIZATION(Class)

#define RW_DEFINE_EXTERNAL_STREAMING_FACTORY(Class)                        \
        RW_DEFINE_SERIAL_FACTORY_SPECIALIZATION(Class)

// Declaration for registration of creator of D returning B*
#define RW_DECLARE_EXTERNAL_CREATOR_AS(Class,Other)                        \
        RW_DECLARE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(Class,Other)

#define RW_DEFINE_EXTERNAL_CREATOR_AS(Class,Other)                         \
        RW_DEFINE_SERIAL_CREATOR_REGISTRAR_SPECIALIZATION(Class,Other)

#define RW_DECLARE_EXTERNAL_STREAMABLE_POINTER_AS_BASE(Class,Other)        \
        RW_DECLARE_EXTERNAL_SAVE_RESTORE_AS(Class,Other)                   \
        RW_DECLARE_EXTERNAL_CREATOR_AS(Class,Other)

#define RW_DEFINE_EXTERNAL_STREAMABLE_POINTER_AS_BASE(Class,Other)         \
        RW_DEFINE_EXTERNAL_SAVE_RESTORE_AS(Class,Other)                    \
        RW_DEFINE_EXTERNAL_CREATOR_AS(Class,Other)

/**************************************************************************/

// Documented macros
/**
 * \ingroup serialization_package_macros
 *
 * Defines the global serialization operators. Place
 * #RW_DECLARE_EXTERNAL_STREAMABLE_POINTER in the header of your
 * serializable class. For external serialization only. (For intrusive, use
 * #RW_DECLARE_STREAMABLE_POINTER.)
 *
 * \sa
 * #RW_DEFINE_EXTERNAL_STREAMABLE_POINTER
 */
#define RW_DECLARE_EXTERNAL_STREAMABLE_POINTER(Class)                      \
        RW_DECLARE_STREAMING_FACTORY(Class)                                \
        RW_DECLARE_STREAMING_POINTER_OPERATORS(Class)

/**
 * \ingroup serialization_package_macros
 *
 * Defines the global serialization operators. Place
 * #RW_DEFINE_EXTERNAL_STREAMABLE_POINTER in the source file for your
 * serializable class. For external serialization only. (For intrusive, use
 * #RW_DEFINE_STREAMABLE_POINTER.)
 *
 * \sa
 * #RW_DECLARE_EXTERNAL_STREAMABLE_POINTER
 */
#define RW_DEFINE_EXTERNAL_STREAMABLE_POINTER(Class)                       \
        RW_DEFINE_STREAMING_FACTORY(Class)                                 \
        RW_DEFINE_STREAMING_POINTER_OPERATORS(Class)

/**
 * \ingroup serialization_package_macros
 *
 * Apply this macro to a class if its instantiations will be serialized as
 * pointers directly to the instantiations. Place
 * #RW_DECLARE_EXTERNAL_STREAMABLE_AS_SELF in the header of your
 * serializable class. For external serialization only. (For intrusive, use
 * #RW_DECLARE_STREAMABLE_AS_SELF.)
 *
 * \sa
 * #RW_DEFINE_EXTERNAL_STREAMABLE_POINTER
 */
#define RW_DECLARE_EXTERNAL_STREAMABLE_AS_SELF(Class)                      \
        RW_DECLARE_EXTERNAL_SAVE_RESTORE(Class)                            \
        RW_DECLARE_EXTERNAL_CREATOR_AS(Class,Class)

/**
 * \ingroup serialization_package_macros
 *
 * Apply this macro to a class if its instantiations will be serialized as
 * pointers directly to the instantiations. Place
 * #RW_DEFINE_EXTERNAL_STREAMABLE_AS_SELF in the source file of your
 * serializable class. For external serialization only. (For intrusive, use
 * #RW_DEFINE_STREAMABLE_AS_SELF.)
 *
 * \sa
 * #RW_DECLARE_EXTERNAL_STREAMABLE_POINTER
 */
#define RW_DEFINE_EXTERNAL_STREAMABLE_AS_SELF(Class)                       \
        RW_DEFINE_EXTERNAL_SAVE_RESTORE(Class)                             \
        RW_DEFINE_EXTERNAL_CREATOR_AS(Class,Class)

/**
 * \ingroup serialization_package_macros
 *
 * Allows concrete derived types to be streamed out and streamed back in as
 * pointers to their base class. Place
 * #RW_DECLARE_EXTERNAL_STREAMABLE_AS_BASE in your header, after the
 * declaration of the class. Usually you will want to place this macro after
 * you have used the #RW_DECLARE_EXTERNAL_STREAMABLE_AS_SELF macro. For
 * external serialization only. (For intrusive, use
 * #RW_DEFINE_STREAMABLE_AS_BASE.)
 *
 * \sa
 * #RW_DEFINE_EXTERNAL_STREAMABLE_AS_BASE
 */
#define RW_DECLARE_EXTERNAL_STREAMABLE_AS_BASE(Class,Other)                \
        RW_DECLARE_EXTERNAL_STREAMABLE_POINTER_AS_BASE(Class,Other)

/**
 * \ingroup serialization_package_macros
 *
 * Allows concrete derived types to be streamed out and streamed back in as
 * pointers to their base class. Place
 * #RW_DEFINE_EXTERNAL_STREAMABLE_AS_BASE in the source file for your
 * serializable class. Usually you will want to place this macro after you
 * have used the #RW_DECLARE_EXTERNAL_STREAMABLE_AS_SELF macro. For external
 * serialization only. (For intrusive, use #RW_DECLARE_STREAMABLE_AS_BASE.)
 *
 * \sa
 * #RW_DECLARE_EXTERNAL_STREAMABLE_AS_BASE
 */
#define RW_DEFINE_EXTERNAL_STREAMABLE_AS_BASE(Class,Other)                 \
        RW_DEFINE_EXTERNAL_STREAMABLE_POINTER_AS_BASE(Class,Other)



/**************************************************************************/

#define RW_DEFINE_STREAMABLE_COLLECTABLE_SEQUENCE_CONTENT(container)       \
{                                                                          \
    if (in) {                                                              \
        RWWithObjectInputContext inputContext(*in);                        \
                                                                           \
        int len;                                                           \
        RWStreamType tempType;                                             \
        in->startSequence(len, tempType);                                  \
                                                                           \
        RWCollectable* temp;                                               \
        for (int i = 0; i < len; i++) {                                    \
            temp = 0;                                                      \
            in->startElement(i);                                           \
            *in >> temp;                                                   \
            in->endElement();                                              \
            This->insert(temp);                                            \
        }                                                                  \
        in->endSequence();                                                 \
    }                                                                      \
                                                                           \
    if (out) {                                                             \
        RWWithObjectOutputContext outputContext(*out);                     \
                                                                           \
        int len = (int)(This->entries());                                  \
                                                                           \
        name2(container,Iterator) iter((container&)(*This));               \
        out->startSequence(len,  rwStreamType ((RWCollectable**)0),        \
                           RWTypeInfo::symbol(typeid(container)));         \
                                                                           \
        int i = 0;                                                         \
        while (iter()) {                                                   \
            out->startElement(i++);                                        \
            *out << iter.key();                                            \
            out->endElement();                                             \
        }                                                                  \
        out->endSequence();                                                \
    }                                                                      \
}


/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators for streaming
 * \ref RWCollectable "RWCollectable-based" collections. Intrusive or
 * external. Put in header file outside the class declaration.
 */
#define RW_DECLARE_STREAMABLE_COLLECTABLE_SEQUENCE(container)              \
        RW_DECLARE_EXTERNAL_SAVE_RESTORE(container)                        \
        RW_DECLARE_EXTERNAL_SAVE_RESTORE_AS(container,RWCollectable)       \
        RW_DECLARE_STREAMING_FACTORY(container)                            \
        RW_DECLARE_EXTERNAL_CREATOR_AS(container,container)                \
        RW_DECLARE_EXTERNAL_CREATOR_AS(container,RWCollectable)            \
        RW_DECLARE_STREAMING_POINTER_OPERATORS(container)                  \
                                                                           \
inline RWStreamType                                                        \
rwStreamType(const container*) {                                           \
    return RW_SEQ;                                                         \
}                                                                          \
                                                                           \
inline RWObjectOutputStream&                                               \
operator<<(RWObjectOutputStream& strm, const container& seq)               \
{                                                                          \
  RWWithObjectOutputContext outputContext(strm);                           \
  int len = static_cast<int>(seq.entries());                               \
  name2(container,Iterator) iter((container&)(seq));                       \
  strm.startSequence(                                                      \
      len,  rwStreamType ((RWCollectable**)0),                             \
      RWTypeInfo::symbol(typeid(container)));                              \
  int i = 0;                                                               \
  while (iter()) {                                                         \
    strm.startElement(i++);                                                \
    strm << iter.key();                                                    \
    strm.endElement();                                                     \
  }                                                                        \
  strm.endSequence();                                                      \
  return strm;                                                             \
}                                                                          \
                                                                           \
inline RWObjectInputStream&                                                \
operator>>(RWObjectInputStream& strm, container& seq)                      \
{                                                                          \
   RWWithObjectInputContext inputContext(strm);                            \
   int len;                                                                \
   RWStreamType tempType;                                                  \
   strm.startSequence(len, tempType);                                      \
   RWCollectable* temp;                                                    \
   for (int i = 0; i < len; i++) {                                         \
      temp = 0;                                                            \
      strm.startElement(i);                                                \
      strm >> temp;                                                        \
      strm.endElement();                                                   \
      seq.insert(temp);                                                    \
   }                                                                       \
   strm.endSequence();                                                     \
   return strm;                                                            \
}


#define RW_DEFINE_STREAMABLE_COLLECTABLE_SEQUENCE(Container)               \
    RW_DEFINE_EXTERNAL_SAVE_RESTORE(Container)                             \
    RW_DEFINE_EXTERNAL_SAVE_RESTORE_AS(Container,RWCollectable)            \
    RW_DEFINE_STREAMING_FACTORY(Container)                                 \
    RW_DEFINE_EXTERNAL_CREATOR_AS(Container,Container)                     \
    RW_DEFINE_EXTERNAL_CREATOR_AS(Container,RWCollectable)                 \
    RW_DEFINE_STREAMING_POINTER_OPERATORS(Container)                       \
    RW_BEGIN_EXTERNAL_STREAM_CONTENTS (Container)                          \
        RW_DEFINE_STREAMABLE_COLLECTABLE_SEQUENCE_CONTENT(Container)       \
    RW_END_STREAM_CONTENTS

/**************************************************************************/

/**
 * \ingroup serialization_package_macros
 *
 * Declares global serialization operators for streaming
 * \ref RWCollectable "RWCollectable-based" maps (associations). Intrusive
 * or external. Put in header file outside the class declaration.
 */
#define RW_DECLARE_STREAMABLE_COLLECTABLE_MAP(container)                   \
    RW_DECLARE_EXTERNAL_SAVE_RESTORE(container)                            \
    RW_DECLARE_EXTERNAL_SAVE_RESTORE_AS(container,RWCollectable)           \
    RW_DECLARE_STREAMING_FACTORY(container)                                \
    RW_DECLARE_EXTERNAL_CREATOR_AS(container,container)                    \
    RW_DECLARE_EXTERNAL_CREATOR_AS(container,RWCollectable)                \
    RW_DECLARE_STREAMING_POINTER_OPERATORS(container)                      \
                                                                           \
inline RWStreamType                                                        \
rwStreamType(const container*) {                                           \
   return RW_ASSOC;                                                        \
}                                                                          \
inline RWObjectOutputStream&                                               \
operator<<(RWObjectOutputStream& str, const container& c)                  \
{                                                                          \
  RWWithObjectOutputContext outputContext(str);                            \
  name2(container,Iterator) iter((container&)(c));                         \
  str.startMap(static_cast<int> (c.entries()),                             \
                rwStreamType ((RWCollectable**)0),                         \
                rwStreamType ((RWCollectable**)0),                         \
               RWTypeInfo::symbol(typeid(container)));                     \
  while (iter()) {                                                         \
    str.startAssocKey();                                                   \
    str << iter.key();                                                     \
    str.startAssocValue();                                                 \
    str << iter.value();                                                   \
    str.endAssoc();                                                        \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}                                                                          \
inline RWObjectInputStream&                                                \
operator>>(RWObjectInputStream& str, container& c)                         \
{                                                                          \
  RWWithObjectInputContext inputContext(str);                              \
  int count = 0;                                                           \
  RWStreamType tempKey;                                                    \
  RWStreamType tempVal;                                                    \
  str.startMap(count, tempKey, tempVal);                                   \
  RWCollectable* key;                                                      \
  RWCollectable* val;                                                      \
  for (int i = 0; i < count; i++) {                                        \
    key = 0;                                                               \
    val = 0;                                                               \
    str.startAssocKey();                                                   \
    str >> key;                                                            \
    str.startAssocValue();                                                 \
    str >> val;                                                            \
    str.endAssoc();                                                        \
    c.insertKeyAndValue(key, val);                                         \
  }                                                                        \
  str.endMap();                                                            \
  return str;                                                              \
}

// End of RW_DECLARE_STREAMABLE_COLLECTABLE_MAP


#define RW_DEFINE_STREAMABLE_COLLECTABLE_MAP_CONTENT(container)            \
{                                                                          \
    if (in) {                                                              \
        RWWithObjectInputContext inputContext(*in);                        \
                                                                           \
        int len;                                                           \
        RWStreamType tempKey, tempVal;                                     \
        in->startMap(len, tempKey, tempVal);                               \
                                                                           \
        RWCollectable *key, *val;                                          \
        for (int i = 0; i < len; i++) {                                    \
            key = val = 0;                                                 \
                                                                           \
            in->startAssocKey();                                           \
            *in >> key;                                                    \
            in->startAssocValue();                                         \
            *in >> val;                                                    \
            in->endAssoc();                                                \
            This->insertKeyAndValue(key, val);                             \
        }                                                                  \
        in->endMap();                                                      \
    }                                                                      \
                                                                           \
    if (out) {                                                             \
        RWWithObjectOutputContext outputContext(*out);                     \
                                                                           \
        out->startMap(static_cast<int> (This->entries()),                  \
                       rwStreamType ((RWCollectable**)0),                  \
                       rwStreamType ((RWCollectable**)0),                  \
                      RWTypeInfo::symbol(typeid(container)));              \
                                                                           \
        name2(container,Iterator) iter((container&)(*This));               \
        while (iter()) {                                                   \
            out->startAssocKey();                                          \
            *out << iter.key();                                            \
            out->startAssocValue();                                        \
            *out << iter.value();                                          \
            out->endAssoc();                                               \
                                                                           \
        }                                                                  \
        out->endMap();                                                     \
    }                                                                      \
}

#define RW_DEFINE_STREAMABLE_COLLECTABLE_MAP(Container)                    \
    RW_DEFINE_EXTERNAL_SAVE_RESTORE(Container)                             \
    RW_DEFINE_EXTERNAL_SAVE_RESTORE_AS(Container,RWCollectable)            \
    RW_DEFINE_STREAMING_FACTORY(Container)                                 \
    RW_DEFINE_EXTERNAL_CREATOR_AS(Container,Container)                     \
    RW_DEFINE_EXTERNAL_CREATOR_AS(Container,RWCollectable)                 \
    RW_DEFINE_STREAMING_POINTER_OPERATORS(Container)                       \
    RW_BEGIN_EXTERNAL_STREAM_CONTENTS (Container)                          \
        RW_DEFINE_STREAMABLE_COLLECTABLE_MAP_CONTENT(Container)            \
    RW_END_STREAM_CONTENTS

/**************************************************************************/

// Library types made streamable
#if defined(_MSC_VER) || defined(__IBMCPP__)

#  define RW_DECLARE_STREAMABLE_LIBRARY_POINTER(T)                         \
        RW_DECLARE_STREAMING_FACTORY(T)                                    \
        RW_DECLARE_EXTERNAL_CREATOR_AS(T,T)                                \
        RW_SERIAL_DECLARE_GLOBAL_INSERTER_PTR(T,RW_SERIAL_EXPORT)          \
        RW_SERIAL_DECLARE_GLOBAL_EXTRACTOR_PTR(T,RW_SERIAL_EXPORT)

#  define RW_DEFINE_STREAMABLE_LIBRARY_POINTER(T)                         \
        RW_DEFINE_STREAMING_FACTORY(T)                                    \
        RW_DEFINE_EXTERNAL_CREATOR_AS(T,T)                                \
        RW_SERIAL_DEFINE_LIBRARY_GLOBAL_INSERTER_PTR(T)                   \
        RW_SERIAL_DEFINE_LIBRARY_GLOBAL_INSERTER_PTR_CONST(T)             \
        RW_SERIAL_DEFINE_LIBRARY_GLOBAL_EXTRACTOR_PTR(T)

#else

#  define RW_DECLARE_STREAMABLE_LIBRARY_POINTER(T)                        \
        RW_DECLARE_STREAMING_FACTORY(T)                                   \
        RW_DECLARE_EXTERNAL_CREATOR_AS(T,T)

#  define RW_DEFINE_STREAMABLE_LIBRARY_POINTER(T)                         \
        RW_DEFINE_STREAMING_FACTORY(T)                                    \
        RW_DEFINE_EXTERNAL_CREATOR_AS(T,T)

#endif

// RWCollectable
#define RW_DECLARE_STREAMABLE_COLLECTABLE                                 \
        RW_DECLARE_EXT_FUNCTORS_SPECIALIZATION(                           \
            RWCollectable,RW_SERIAL_EXPORT)                               \
        RW_DECLARE_STREAMING_FACTORY(RWCollectable)                       \
        RW_DECLARE_EXTERNAL_CREATOR_AS(RWCollectable,RWCollectable)       \
        RW_SERIAL_DECLARE_GLOBAL_STREAMER(RWCollectable,RW_SERIAL_EXPORT) \
        RW_SERIAL_DEFINE_GLOBAL_STREAMTYPE(RWCollectable)                 \
        RW_SERIAL_DEFINE_GLOBAL_INSERTER_REF(RWCollectable)               \
        RW_SERIAL_DEFINE_GLOBAL_EXTRACTOR_REF(RWCollectable)              \
        RW_SERIAL_DECLARE_GLOBAL_INSERTER_PTR(                            \
            RWCollectable,RW_SERIAL_EXPORT)                               \
        RW_SERIAL_DECLARE_GLOBAL_EXTRACTOR_PTR(                           \
            RWCollectable,RW_SERIAL_EXPORT)

#define RW_DEFINE_STREAMABLE_COLLECTABLE                                  \
        RW_BEGIN_EXTERNAL_STREAM_CONTENTS(RWCollectable)                  \
        RW_END_STREAM_CONTENTS                                            \
        RW_DEFINE_EXTERNAL_SAVE_RESTORE(RWCollectable)                    \
        RW_DEFINE_STREAMING_FACTORY(RWCollectable)                        \
        RW_DEFINE_EXTERNAL_CREATOR_AS(RWCollectable,RWCollectable)        \
        RW_DEFINE_STREAMING_POINTER_OPERATORS(RWCollectable)

#define RW_DECLARE_STREAMABLE_DERIVED_COLLECTABLE(T,U)                    \
        RW_DECLARE_EXT_FUNCTORS_SPECIALIZATION(T,RW_SERIAL_EXPORT)        \
        RW_DECLARE_EXTERNAL_SAVE_RESTORE_AS(T,RWCollectable)              \
        RW_DECLARE_STREAMING_FACTORY(T)                                   \
        RW_DECLARE_EXTERNAL_CREATOR_AS(T,T)                               \
        RW_DECLARE_EXTERNAL_CREATOR_AS(T,RWCollectable)                   \
        RW_SERIAL_DECLARE_GLOBAL_STREAMER(T,RW_SERIAL_EXPORT)             \
        RW_SERIAL_DEFINE_GLOBAL_STREAMTYPE(T)                             \
        RW_SERIAL_DEFINE_GLOBAL_INSERTER_REF(T)                           \
        RW_SERIAL_DEFINE_GLOBAL_EXTRACTOR_REF(T)                          \
        RW_SERIAL_DECLARE_GLOBAL_INSERTER_PTR(T,RW_SERIAL_EXPORT)         \
        RW_SERIAL_DECLARE_GLOBAL_EXTRACTOR_PTR(T,RW_SERIAL_EXPORT)

#define RW_DEFINE_STREAMABLE_DERIVED_COLLECTABLE(T,U)                     \
        RW_BEGIN_EXTERNAL_STREAM_CONTENTS(T)                              \
            RW_STREAM_EXTERNAL_PARENT(RWCollectable)                      \
            RW_STREAM_EXTERNAL_PARENT(U)                                  \
        RW_END_STREAM_CONTENTS                                            \
        RW_DEFINE_EXTERNAL_SAVE_RESTORE(T)                                \
        RW_DEFINE_EXTERNAL_SAVE_RESTORE_AS(T,RWCollectable)               \
        RW_DEFINE_STREAMING_FACTORY(T)                                    \
        RW_DEFINE_EXTERNAL_CREATOR_AS(T,T)                                \
        RW_DEFINE_EXTERNAL_CREATOR_AS(T,RWCollectable)                    \
        RW_DEFINE_STREAMING_POINTER_OPERATORS(T)


#endif // rw_serial_RWObjectStreamMacros_h_
