#ifndef rw_xmlstreams_RWTParsedTransformObjectInputStreamImp_h_
#define rw_xmlstreams_RWTParsedTransformObjectInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTParsedTransformObjectInputStreamImp.h#1 $
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

#include <rw/xmlstreams/RWTParsedTransformInputStreamImp.h>
#include <rw/xmlstreams/RWTXmlTraits.h>
#include <rw/xmlstreams/RWXmlObjectInputStreamImp.h>
#include <rw/xmlstreams/pkgdefs.h>

//--The class 'RWTParsedTransformObjectInputStreamImp' uses RWXmlObjectInputStreamImp
//-- and RWTParsedTransformInputStreamImp to construct an XML Stream that applies
//-- a generic transformation to the xml document before reading it from the
//-- the source.
//--
//--Example:
//--
//--// Open an fstream to serve as our source
//--ifstream s("foo.xml");
//--//--
//--// Create a transformation object (must have a transform(const RWXmlElementImp&,ostream&) interface).
//--MyTransform t;
//--
//--// Create an XML data stream using the fstream
//--RWObjectInputStream in = RWTParsedTransformObjectInputStreamImp<MyTransform>::make(s,t);
//--
//--// Read integer from XML data stream
//--int i;
//--in >> i;
//--
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Constructs an XML input stream that applies a generic transformation to
 * the XML document before reading it from the source.
 *
 * This class uses RWXmlObjectInputStreamImp and
 * RWTParsedTransformInputStreamImp to construct an XML input stream that
 * applies a generic transformation to the XML document before reading it
 * from the source.
 *
 * \example
 * \code
 * // Open an fstream to serve as our source
 * ifstream s("foo.xml");
 *
 * // Create a transformation object, which must have a
 * // transform(const RWXmlElementImp&,ostream&) interface
 * MyTransform t;
 *
 * // Create an XML data stream that uses the fstream
 * RWObjectInputStream in =
 *  RWTParsedTransformObjectInputStreamImp<MyTransform>::make(s,t);
 *
 * // Read an integer from XML data stream.
 * int i;
 * in >> i;
 * \endcode
 * \endexample
 */
template <class Transform>
class RWTParsedTransformObjectInputStreamImp : public RWXmlObjectInputStreamImp
{
protected:
    /**
     * Used by the make() function and potentially by derived classes to
     * initialize the source data stream and to insert into the stream a
     * transformation of the XML document based on the transformation object
     * \a transform.
     *
     * The parameter \a istr is a handle to the initialized stream.
     *
     * The parameter \c transform is a transformation object that must
     * supply a public interface function transform(istream&,ostream&).
     *
     * The parameter \c escape sets whether primitive element values will be
     * unescaped. By default, this parameter is set to \c true.
     */
    RWTParsedTransformObjectInputStreamImp(std::istream& istr, Transform transform, bool escape)
        :
        RWXmlObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWTParsedTransformInputStreamImp<RWCharInputStream, RWFilteredCharInputStreamImp, Transform, RWTXmlTraits<char> >::make(RWCharFromStreambufInputStreamImp::make(*(istr.rdbuf())), transform)), escape)
    {
        ;
    }

    /**
     * \copydoc RWTParsedTransformObjectInputStreamImp::RWTParsedTransformObjectInputStreamImp(std::istream&, Transform, bool)
     *
     * This constructor also takes a pointer reference to an \b std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed to this constructor
     * through the make() function. This constructor, in creating the
     * underlying element stream for the XML stream, creates a formatting
     * object for the stream and places the address of that object in the
     * pointer reference. The calling application can then use this
     * formatting object to manipulate data formats in the XML stream. See
     * the corresponding
     * \ref RWTParsedTransformObjectInputStreamImp::make(std::istream&, Transform, std::ios*&, bool) "make()"
     * function description for an example.
     */
    RWTParsedTransformObjectInputStreamImp(std::istream& istr, Transform transform, std::ios*& formatter, bool escape)
        :
        RWXmlObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWTParsedTransformInputStreamImp<RWCharInputStream, RWFilteredCharInputStreamImp, Transform, RWTXmlTraits<char> >::make(RWCharFromStreambufInputStreamImp::make(*(istr.rdbuf())), transform), formatter), escape)
    {
        ;
    }

public:
    //--Constructs an 'RWTParsedTransformObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream stream that is used as the source of bytes.
    //--Parameter 'transform' is the transformation object
    //--Parameter escape determines whether primitive element values will be unescaped (true = yes).
    //--Throws no exceptions.
    /**
     * Constructs an RWTParsedTransformObjectInputStreamImp instance that
     * uses \a source as its source of bytes, and returns a handle to it.
     * The XML input stream includes a transformation of the XML document
     * based on the transformation object \a transform.
     *
     * The parameter \a escape sets whether primitive element values will be
     * unescaped. By default, this parameter is set to \c true.
     */
    static RWObjectInputStream make(std::istream& source, Transform transform, bool escape = true)
    {
        return RWObjectInputStream(new RWTParsedTransformObjectInputStreamImp<Transform>(source, transform, escape));
    }

    //--Constructs an 'RWTParsedTransformObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream stream that is used as the source of bytes.
    //--Parameter 'transform' is the transformation object
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Parameter escape determines whether primitive element values will be unescaped (true = yes).
    //--Throws no exceptions.
    /**
     * \copydoc RWTParsedTransformObjectInputStreamImp::make(std::istream&, Transform, bool)
     *
     * This function also takes a pointer reference to an \c std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed through this make()
     * function to the constructor:
     *
     * \code
     * std::ios* formatter;            // uninitialized pointer
     * RWObjectOutputStream xostr =
     * RWTParsedTransformObjectInputStreamImp<MyTransform>
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
    static RWObjectInputStream make(std::istream& source, Transform transform, std::ios*& formatter, bool escape = true)
    {
        return RWObjectInputStream(new RWTParsedTransformObjectInputStreamImp<Transform>(source, transform, formatter, escape));
    }

};

#endif // rw_xmlstreams_RWTParsedTransformObjectInputStreamImp_h_
