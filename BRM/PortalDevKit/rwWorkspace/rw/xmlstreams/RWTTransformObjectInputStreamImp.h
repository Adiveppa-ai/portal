#ifndef rw_xmlstreams_RWTTransformObjectInputStreamImp_h_
#define rw_xmlstreams_RWTTransformObjectInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTTransformObjectInputStreamImp.h#1 $
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

#include <rw/xmlstreams/RWTTransformInputStreamImp.h>
#include <rw/xmlstreams/RWXmlObjectInputStreamImp.h>
#include <rw/xmlstreams/pkgdefs.h>


//--The class 'RWTTransformObjectInputStreamImp' uses RWXmlObjectInputStreamImp
//-- and RWTTransformInputStreamImp to construct a stream that applies
//-- a generic transformation to an XML document before reading it from the
//-- the source.
//--
//--Example:
//--
//--// Open an fstream to serve as our source
//--ifstream s("foo.xml");
//--//--
//--// Create a transformation object (must have a transform(istream&,ostream&) interface).
//--MyTransform t;
//--
//--// Create an XML data stream using the fstream
//--RWObjectInputStream in = RWTTransformObjectInputStreamImp<MyTransform>::make(s,t);
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
 * This class uses RWXmlObjectInputStreamImp and RWTTransformInputStreamImp
 * to construct an XML input stream that applies a generic transformation to
 * the XML document before reading it from the source.
 *
 * \example
 * \code
 * // Open an fstream to serve as our source
 * ifstream s("foo.xml");
 *
 * // Create a transformation object, which must have a
 * // transform(istream&,ostream&) interface
 * MyTransform t;
 *
 * // Create an XML data stream using the fstream
 * RWObjectInputStream in =
 *   RWTTransformObjectInputStreamImp<MyTransform>::make(s,t);
 *
 * // Read an integer from XML data stream.
 * int i;
 * in >> i;
 * \endcode
 * \endexample
 */
template <class Transform>
class RWTTransformObjectInputStreamImp : public RWXmlObjectInputStreamImp
{
protected:
    /**
     * Used by the make() function and potentially by derived classes to
     * initialize the source data stream and to insert into the stream a
     * transformation of the XML document based on the transformation object
     * \c transform.
     *
     * The parameter \a istr is a handle to the initialized stream.
     *
     * The parameter \a transformer is a transformation object that must
     * supply a public interface function transform(istream&,ostream&).
     *
     * The parameter \a escape sets whether the input stream contains
     * escapes for XML reserved characters that need to be unescaped.
     * Usually this would be because the objects serialized out with
     * RWXmlObjectOutputStreamImp contained embedded XML.
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
    RWTTransformObjectInputStreamImp(std::istream& istr, Transform transformer, bool escape)
        :
        RWXmlObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWTTransformInputStreamImp<RWCharInputStream, RWFilteredCharInputStreamImp, Transform >::make(RWCharFromStreambufInputStreamImp::make(*(istr.rdbuf())), transformer)), escape)
    {
        ;
    }

    /**
     * \copydoc RWTTransformObjectInputStreamImp(std::istream&, Transform, bool)
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
     * \ref RWTTransformObjectInputStreamImp::make(std::istream&, Transform, std::ios*&, bool) "make()"
     * function description for an example.
     */
    RWTTransformObjectInputStreamImp(std::istream& istr, Transform transformer, std::ios*& formatter, bool escape)
        :
        RWXmlObjectInputStreamImp(RWIstreamDataFromCharInputStreamImp::make(RWTTransformInputStreamImp<RWCharInputStream, RWFilteredCharInputStreamImp, Transform >::make(RWCharFromStreambufInputStreamImp::make(*(istr.rdbuf())), transformer), formatter), escape)
    {
        ;
    }

public:
    //--Constructs an 'RWTTransformObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream stream that is used as the source of bytes.
    //--Parameter 'transformer' is the transformation object
    //--Parameter escape determines whether primitive element values will be unescaped (true = yes).
    //--Throws no exceptions.
    /**
     * Constructs an RWTTransformObjectInputStreamImp instance that uses the
     * data stream \a source as its source of bytes, and returns a handle to
     * it. The XML input stream includes a transformation of the XML
     * document based on the transformation object \a transformer.
     *
     * The parameter \a escape sets whether the primitive element values
     * will be unescaped. By default, this parameter is set to \c true.
     */
    static RWObjectInputStream make(std::istream& source, Transform transformer,
                                    bool escape = true)
    {
        return RWObjectInputStream(new RWTTransformObjectInputStreamImp<Transform>(source, transformer, escape));
    }

    //--Constructs an 'RWTTransformObjectInputStreamImp' instance that uses 'source'
    //--as its source of bytes, and returns a handle to it.
    //--Parameter 'source' is the istream stream that is used as the source of bytes.
    //--Parameter 'transformer' is the transformation object
    //--Parameter 'formatter' will be returned with a reference to the formatting object
    //--Parameter escape determines whether primitive element values will be unescaped (true = yes).
    //--Throws no exceptions.
    /**
     * \copydoc RWTTransformObjectInputStreamImp::make(std::istream&, Transform, bool)
     *
     * This function also takes a pointer reference to an \c std::ios
     * formatting object. An empty formatting object pointer is created
     * before the XML stream is created and is passed through this make()
     * function to the constructor:
     *
     * \code
     * std::ios* formatter;            // uninitialized pointer
     * RWObjectOutputStream xostr =
     * RWTTransformObjectInputStreamImp<MyTransform>
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
    static RWObjectInputStream make(std::istream& source, Transform transformer,
                                    std::ios*& formatter, bool escape = true)
    {
        return RWObjectInputStream(new RWTTransformObjectInputStreamImp<Transform>(source, transformer, formatter, escape));
    }

};

#endif // rw_xmlstreams_RWTTransformObjectInputStreamImp_h_
