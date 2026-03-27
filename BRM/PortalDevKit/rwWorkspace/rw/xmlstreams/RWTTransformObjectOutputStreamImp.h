#ifndef rw_xmlstreams_RWTTransformObjectOutputStreamImp_h_
#define rw_xmlstreams_RWTTransformObjectOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTTransformObjectOutputStreamImp.h#1 $
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

#include <rw/xmlstreams/RWTTransformOutputStreamImp.h>
#include <rw/xmlstreams/RWXmlObjectOutputStreamImp.h>
#include <rw/xmlstreams/pkgdefs.h>


//--The class 'RWTTransformObjectOutputStreamImp' uses RWXmlObjectOutputStreamImp
//-- and RWXsltCharOutputStreamImp to construct an XML Stream that applies
//-- an xslt transformation to the xml document before writing it out to
//-- the sink.
//--
//--Example:
//--
//--// Create a stringstream to serve as our sink
//--std::ostringstream s;
//--
//--// Create a transformation object
//--MyTransform t;
//--
//--// Create an XML data stream using the stringstream
//--RWObjectOutputStream out = RWTTransformObjectOutputStreamImp<MyTransform>::make(s,t);
//--
//--// Write integer value '1' to XML data stream
//--out << 1;
//--
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Constructs an XML stream that applies a generic transformation to the XML
 * document before writing it out to the sink.
 *
 * This class uses RWXmlObjectOutputStreamImp and
 * RWTTransformOutputStreamImp to construct an XML stream that applies a
 * generic transformation to the XML document before writing it out to the
 * sink.
 *
 * \example
 * \code
 * // Create a strstream to serve as our sink
 * ostrstream s;
 *
 * // Create a transformation object
 * MyTransform t;
 *
 * // Create an XML data stream using the strstream
 * RWObjectOutputStream out =
 *   RWTTransformObjectOutputStreamImp<MyTransform>::make(s,t);
 *
 * // Write integer value `1' to XML data stream
 * out << 1;
 * \endcode
 * \endexample
 */
template <class Transform>
class RWTTransformObjectOutputStreamImp : public RWXmlObjectOutputStreamImp
{
protected:
    /**
     * Used by the make() function and potentially by derived classes to
     * initialize an output stream and to insert a transformation of the
     * serialized object data based on the transformation object
     * \a transformer.
     *
     * The parameter \a ostr is a handle to the initialized stream.
     *
     * The parameter \a transformer is a transformation object that must
     * supply a public interface function transform(istream&,ostream&).
     *
     * The parameter \a rootElementType must be one of the following:
     *
     * - #nestedObjectTag, if serializing an object by value
     * - #objectTag, if serializing an object by pointer
     * - #sequenceTag, if serializing a sequential collection such as
     * RWTPtrOrderedVector
     * - #mapTag, if serializing a mapping collection such as RWTPtrHashMap
     * - #primitiveTag, if serializing a built-in type such as \c int
     *
     * The value passed indicates the root element of the generated
     * document.
     *
     * The parameter \a escape sets whether to escape XML reserved
     * characters in the data being serialized. By setting this parameter to
     * \c true, reserved characters in \c char and \c string values are
     * escaped, allowing the data to include embedded XML.
     *
     * The reserved characters are:
     *
     * \code
     * <  >  &  "  '
     * \endcode
     *
     * You get slightly better performance if the \a escape parameter is set
     * to \c false, but before doing so be certain that your data does not
     * contain reserved characters.
     */
    RWTTransformObjectOutputStreamImp(std::ostream& ostr, Transform transformer, const RWCString& rootElementType, bool escape)
        :
        RWXmlObjectOutputStreamImp(RWOstreamDataToCharOutputStreamImp::make(RWTTransformOutputStreamImp<RWCharOutputStream, RWFilteredCharOutputStreamImp, Transform >::make(RWCharToStreambufOutputStreamImp::make(*(ostr.rdbuf())), transformer)), rootElementType, escape)
    {
        ;
    }

    /**
     * \copydoc RWTTransformObjectOutputStreamImp::RWTTransformObjectOutputStreamImp(std::ostream&, Transform, const RWCString&, bool)
     *
     * This constructor also takes a pointer reference to an \c std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed to this constructor
     * through the make() function. This constructor, in creating the
     * underlying character stream for the XML stream, creates a formatting
     * object for the stream and places the address of that object in the
     * pointer reference. The calling application can then use this
     * formatting object to manipulate data formats in the XML stream. See
     * the corresponding
     * \ref RWTTransformObjectOutputStreamImp::make(std::ostream&, Transform, std::ios*&, const RWCString&, bool) "make()"
     * function description for an example.
     */
    RWTTransformObjectOutputStreamImp(std::ostream& ostr, Transform transformer, std::ios*& formatter, const RWCString& rootElementType, bool escape)
        :
        RWXmlObjectOutputStreamImp(RWOstreamDataToCharOutputStreamImp::make(RWTTransformOutputStreamImp<RWCharOutputStream, RWFilteredCharOutputStreamImp, Transform >::make(RWCharToStreambufOutputStreamImp::make(*(ostr.rdbuf())), transformer), formatter), rootElementType, escape)
    {
        ;
    }

public:
    //--Constructs an 'RWTTransformObjectOutputStreamImp' instance that uses 'sink'
    //--as its sink of bytes, and returns a handle to it.
    //--Parameter 'sink' is the data stream that is used as the sink of bytes.
    //--Parameter 'transformer' is the transformation object
    //--Parameter 'rootElementType' should be one of objectTag, nestedObjectTag,
    //--sequenceTag, primitiveTag, or mapTag, depending on what sort of object is streamed
    //--into the document at the top level.
    //--Parameter escape determines whether primitive element values will be escaped (true = yes).
    //--Throws no exceptions.
    /**
     * Constructs an RWTTransformObjectOutputStreamImp instance and returns
     * a handle to it. The constructed instance applies a generic
     * transformation to the serialized object data and then passes the data
     * to the output stream \a sink.
     *
     * The parameter \a transformer is a transformation object that must
     * supply a public interface function transform(istream&,ostream&).
     *
     * The parameter \a rootElementType must be one of the following:
     *
     * - #nestedObjectTag, if serializing an object by value
     * - #objectTag, if serializing an object by pointer
     * - #sequenceTag, if serializing a sequential collection such as
     * RWTPtrOrderedVector
     * - #mapTag, if serializing a mapping collection such as RWTPtrHashMap
     * - #primitiveTag, if serializing a built-in type such as \c int
     *
     * The value passed indicates the root element of the generated
     * document. The default setting is #nestedObjectTag.
     *
     * The parameter \a escape sets whether to escape XML reserved
     * characters in the data being serialized. By setting this parameter to
     * \c true, reserved characters in \c char and \c string values are
     * escaped, allowing the data to include embedded XML.
     *
     * The reserved characters are:
     *
     * \code
     * <  >  &  "  '
     * \endcode
     *
     * You get slightly better performance if the \a escape parameter is set
     * to \c false, but before doing so be certain that your data does not
     * contain reserved characters.
     */
    static RWObjectOutputStream make(std::ostream& sink, Transform transformer, const RWCString& rootElementType = nestedObjectTag, bool escape = true)
    {
        return RWObjectOutputStream(new RWTTransformObjectOutputStreamImp<Transform>(sink, transformer, rootElementType, escape));
    }

    //--Constructs an 'RWTTransformObjectOutputStreamImp' instance that uses 'sink'
    //--as its sink of bytes, and returns a handle to it.
    //--Parameter 'sink' is the data stream that is used as the sink of bytes.
    //--Parameter 'transformer' is the transformation object
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Parameter 'rootElementType' should be one of objectTag, nestedObjectTag,
    //--sequenceTag, primitiveTag, or mapTag, depending on what sort of object is streamed
    //--into the document at the top level.
    //--Parameter escape determines whether primitive element values will be escaped (true = yes).
    //--Throws no exceptions.
    /**
     * \copydoc RWTTransformObjectOutputStreamImp::make(std::ostream&, Transform, const RWCString&, bool)
     *
     * This function also takes a pointer reference to an \c std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed through this make()
     * function to the constructor:
     *
     * \code
     * std::ios* formatter;            // uninitialized pointer
     * RWObjectOutputStream xostr =
     * RWTTransformObjectOutputStreamImp<MyTransform>
     * \endcode
     *
     * The constructor, in creating the underlying character stream for the
     * XML stream, creates a formatting object for the stream and places the
     * address of that object in the pointer reference. The calling
     * application can then use this formatting object to manipulate data
     * formats in the XML stream.
     *
     * \code
     * formatter->precision(15);       // manipulate data format
     * \endcode
     */
    static RWObjectOutputStream make(std::ostream& sink, Transform transformer, std::ios*& formatter, const RWCString& rootElementType = nestedObjectTag, bool escape = true)
    {
        return RWObjectOutputStream(new RWTTransformObjectOutputStreamImp<Transform>(sink, transformer, formatter, rootElementType, escape));
    }
};

#endif // rw_xmlstreams_RWTTransformObjectOutputStreamImp_h_
