#ifndef rw_xmlabstractions_RWXmlStreamWriter_h_
#define rw_xmlabstractions_RWXmlStreamWriter_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlStreamWriter.h#1 $
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

#include <rw/xmlabstractions/RWXmlWriter.h>
#include <rw/rstream.h>

/**
 * \internal
 *
 * \brief
 * Stream-based RWXmlWriter implementation that can be constructed on any
 * ostream implementation.
 *
 * A stream based RWXmlWriter implementation. This class can be constructed
 * on any ostream implementation.
 */
class RWXmlStreamWriter : public RWXmlWriter
{

public:
    /**
     * Creates a RWXmlStreamWriter instance on the specified ostream. The
     * caller should ensure that out is good.
     */
    RWXmlStreamWriter(std::ostream& out) : out_(out)
    {
    }

    /**
     * Provides the stream based flush implementation.
     */
    void flush();

    /**
     * Provides the stream based write implementation.
     */
    using RWXmlWriter::writeToSink;

    /**
     * Provides the stream based string write implementation.
     */

    void writeToSink(const RWCString& text);

    /**
     * Provides the stream based character write implementation.
     */
    void writeToSink(char c);

private:
    std::ostream& out_;
};


inline void
RWXmlStreamWriter::flush()
{
    out_.flush();
}


inline void
RWXmlStreamWriter::writeToSink(const RWCString& text)
{
    out_ << text;
}


inline void
RWXmlStreamWriter::writeToSink(char c)
{
    out_ << c;
}


#endif // rw_xmlabstractions_RWXmlStreamWriter_h_
