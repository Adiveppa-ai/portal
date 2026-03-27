#ifndef rw_xmlstreams_RWTParsedTransformObjectOutputStreamImp_h_
#define rw_xmlstreams_RWTParsedTransformObjectOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTParsedTransformObjectOutputStreamImp.h#1 $
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

#include <rw/xmlstreams/RWTParsedTransformOutputStreamImp.h>
#include <rw/xmlstreams/RWTXmlTraits.h>
#include <rw/xmlstreams/RWXmlObjectOutputStreamImp.h>
#include <rw/xmlstreams/pkgdefs.h>

//--The class 'RWTParsedTransformObjectOutputStreamImp' uses RWXmlObjectOutputStreamImp
//-- and RWTParsedTransformOutputStreamImp to construct an XML Stream that applies
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
//--RWObjectOutputStream out =
//--    RWTParsedTransformObjectOutputStreamImp<MyTransform>::make(s,t);
//--
//--// Write integer value '1' to XML data stream
//--out << 1;
//--
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Constructs an XML stream that includes a generic transformation of the
 * XML document before writing it out to the sink.
 *
 * This class uses RWXmlObjectOutputStreamImp and
 * RWTParsedTransformOutputStreamImp to construct an XML stream that
 * includes a generic transformation of the XML document before writing it
 * out to the sink.
 *
 * \example
 * \code
 * // Create a strstream to serve as our sink
 * ostrstream s;
 *
 * // Create a transformation object
 * MyTransform t;
 *
 * // Create an XML data stream that uses the strstream
 * RWObjectOutputStream out =
 * RWTParsedTransformObjectOutputStreamImp\<MyTransform\>::make(s,t);
 *
 * // Write integer value `1' to XML data stream
 * out << 1;
 * \endcode
 * \endexample
 */
template <class Transform>
class RWTParsedTransformObjectOutputStreamImp
    : public RWXmlObjectOutputStreamImp
{
protected:
    /**
     * Used by the make() function and potentially by derived classes to
     * initialize an output stream and to insert a transformation of the
     * serialized object data based on the transformation object
     * \a transform.
     *
     * The parameter \a ostr is a handle to the initialized stream.
     *
     * The parameter \a transform is a transformation object.
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
     * The parameter \a escape sets whether primitive values will be
     * escaped. The default is set to \c true.
     *
     * Throws no exceptions.
     */
    RWTParsedTransformObjectOutputStreamImp(std::ostream& ostr, Transform transform, const RWCString& rootElementType, bool escape)
        :
        RWXmlObjectOutputStreamImp(RWOstreamDataToCharOutputStreamImp::make(RWTParsedTransformOutputStreamImp<RWCharOutputStream, RWFilteredCharOutputStreamImp, Transform, RWTXmlTraits<char> >::make(RWCharToStreambufOutputStreamImp::make(*(ostr.rdbuf())), transform)), rootElementType, escape)
    {
        ;
    }

    /**
     * \copydoc RWTParsedTransformObjectOutputStreamImp::RWTParsedTransformObjectOutputStreamImp(std::ostream&, Transform, const RWCString&, bool)
     *
     * This constructor also takes a pointer reference to an \b std::ios
     * formatting object.
     *
     * An empty formatting object pointer is created before the XML stream
     * is created and is passed to this constructor through the make()
     * function. This constructor, in creating the underlying element stream
     * for the XML stream, creates a formatting object for the stream and
     * places the address of that object in the pointer reference. The
     * calling application can then use this formatting object to manipulate
     * data formats in the XML stream. See the corresponding
     * \ref RWTParsedTransformObjectOutputStreamImp::make(std::ostream&, Transform, std::ios*&, const RWCString&, bool) "make()"
     * function description for an example.
     */
    RWTParsedTransformObjectOutputStreamImp(std::ostream& ostr, Transform transform, std::ios*& formatter, const RWCString& rootElementType, bool escape)
        :
        RWXmlObjectOutputStreamImp(RWOstreamDataToCharOutputStreamImp::make(RWTParsedTransformOutputStreamImp<RWCharOutputStream, RWFilteredCharOutputStreamImp, Transform, RWTXmlTraits<char> >::make(RWCharToStreambufOutputStreamImp::make(*(ostr.rdbuf())), transform), formatter), rootElementType, escape)
    {
        ;
    }

public:
    //--Constructs an 'RWTParsedTransformObjectOutputStreamImp' instance that uses 'sink'
    //--as its sink of bytes, and returns a handle to it.
    //--Parameter 'sink' is the data stream that is used as the sink of bytes.
    //--Parameter 'transform' is the transformation object
    //--Parameter 'rootElementType' should be one of objectTag, nestedObjectTag,
    //--sequenceTag, primitiveTag, or mapTag, depending on what sort of object is streamed
    //--into the document at the top level.
    //--Parameter escape determines whether primitive element values will be escaped (true = yes).
    //--Throws no exceptions.
    /**
     * Constructs an RWTParsedTransformObjectOutputStreamImp instance that
     * uses \a sink as its sink of bytes and returns a handle to it.
     *
     * The parameter \a transform is a transformation object
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
     * The parameter \a escape sets whether primitive values will be
     * escaped. The default is set to \c true.
     *
     * Throws no exceptions.
     */
    static RWObjectOutputStream make(std::ostream& sink, Transform transform, const RWCString& rootElementType = nestedObjectTag, bool escape = true)
    {
        return RWObjectOutputStream(new RWTParsedTransformObjectOutputStreamImp<Transform>(sink, transform, rootElementType, escape));
    }

    //--Constructs an 'RWTParsedTransformObjectOutputStreamImp' instance that uses 'sink'
    //--as its sink of bytes, and returns a handle to it.
    //--Parameter 'sink' is the data stream that is used as the sink of bytes.
    //--Parameter 'transform' is the transformation object
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Parameter 'rootElementType' should be one of objectTag, nestedObjectTag,
    //--sequenceTag, primitiveTag, or mapTag, depending on what sort of object is streamed
    //--into the document at the top level.
    //--Parameter escape determines whether primitive element values will be escaped (true = yes).
    //--Throws no exceptions.
    /**
     * \copydoc RWTParsedTransformObjectOutputStreamImp::make(std::ostream&, Transform, const RWCString&, bool)
     *
     * This function also takes a pointer reference to an \b std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed through this make()
     * function to the constructor:
     *
     * \code
     * std::ios* formatter;            // uninitialized pointer
     * RWObjectOutputStream xostr =
     * RWTParsedTransformObjectOutputStreamImp<MyTransform>
     * \endcode
     *
     * The constructor, in creating the underlying character stream for the
     * XML stream, creates a formatting object for the stream and places the
     * address of that object in the pointer reference. The calling
     * application can then use this formatting object to manipulate data
     * formats in the XML stream.
     *
     * \code
     * formatter->precision(15);  // manipulate data format
     * \endcode
     */
    static RWObjectOutputStream make(std::ostream& sink, Transform transform, std::ios*& formatter, const RWCString& rootElementType = nestedObjectTag, bool escape = true)
    {
        return RWObjectOutputStream(new RWTParsedTransformObjectOutputStreamImp<Transform>(sink, transform, formatter, rootElementType, escape));
    }
};

#endif // rw_xmlstreams_RWTParsedTransformObjectOutputStreamImp_h_
