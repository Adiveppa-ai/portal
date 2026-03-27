#ifndef rw_xmlabstractions_RWXmlReader_h_
#define rw_xmlabstractions_RWXmlReader_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlReader.h#1 $
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

#include <rw/xmlabstractions/RWXmlAttributeSet.h>
#include <rw/xmlabstractions/RWXmlName.h>
#include <rw/xmlabstractions/RWXmlNamespace.h>
#include <rw/xmlabstractions/RWXmlNamespaceStack.h>
#include <rw/xmlabstractions/RWXmlParseError.h>
#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tools/string.h>
#include <iosfwd>
#include <sstream>
#include <string.h>

typedef unsigned long RWXmlChar;

/*
 * RWXmlReader is a undocumented utility class used to provide a single interface
 * for reading XML messages from a RWCString.
 */
class RW_XMLABSTRACTIONS_GLOBAL RWXmlReader
{
public:
    typedef enum { StartTag, EndTag, EmptyTag, Data, Unknown } NodeType;
    static RWXmlName NullName;

    //
    // Uses i as input
    //
    RWXmlReader(std::istream& i);

    //
    // Uses str as input.
    //
    RWXmlReader(const RWCString& str);

    //
    // uses buf as input. no copy is made
    //
    RWXmlReader(unsigned char* buf, size_t length);

    ~RWXmlReader();

    // add a namespace to the namespace stack
    void addNamespace(const RWXmlNamespace& ns);

    // returns true if at the end of the document
    bool eof();

    // These methods read the element specified by name.
    // If the next element isn't specified by 'name', then
    // an exception is thrown
    const RWXmlAttributeSet& readElementStart(const RWXmlName& name);
    void readElementEnd(const RWXmlName& name);
    const RWXmlAttributeSet& readElementStart(const RWCString& name);
    void readElementEnd(const RWCString& name);

    // readElement returns the text of the whole element, unparsed
    RWCString readElement(const RWXmlName& name = NullName);
    RWCString readElement(const RWCString& name);

    // Accessors for the state of the parser
    // Returns information about the last read node
    const RWXmlName& getLastName() const
    {
        return lastName_;
    }
    const RWCString& getLastContent() const
    {
        return lastContent_;
    }
    const RWXmlAttributeSet& getLastAttributes() const
    {
        return lastAttrs_;
    }
    NodeType getLastNodeType() const
    {
        return lastNodeType_;
    }

    // Returns true if the next element is the one given in name.
    bool isElementNext(const RWXmlName& name);
    bool isElementNext(const RWCString& name)
    {
        return isElementNext(getXmlName(name));
    }
    // Reads the start of the next element, skipping content if there is any
    void readElementStart();

    // Reads an end tag for an element, skipping content if there is any
    void readElementEnd();

    // Reads the next node
    void readNextNode();

    // Returns value
    const RWCString& readElementValue();

    // Gets the prefix for the specified URI from the namespace context.  If no
    // prefix is found the empty string is returned.
    const RWCString& getPrefixForURI(const RWCString& uri) const
    {
        return namespaceStack_.getPrefixForURI(uri);
    }

    // Gets the URI for the specified prefix from the namespace context.  If no
    // URI is found the empty string is returned.
    const RWCString& getURIForPrefix(const RWCString& prefix) const
    {
        return namespaceStack_.getURIForPrefix(prefix);
    }

    // get/set expandAttributeReference_
    // if expandAttributeReference_ references in attributes will be expanded
    // ex: "&lt;" expands to "<"
    // expandReference_ defaults to true
    bool getExpandAttributeReference() const
    {
        return expandAttributeReference_;
    }
    void setExpandAttributeReference(bool expandReference)
    {
        expandAttributeReference_ = expandReference;
    }

    // Information from prolog
    const RWCString& getEncoding() const
    {
        return encoding_;
    }
    const RWCString& getVersion() const
    {
        return version_;
    }
    const RWCString& getStandalone() const
    {
        return sddecl_;
    }
    bool             hasStandalone() const
    {
        return hasSddecl_;
    }
    bool             hasEncoding() const
    {
        return hasEncoding_;
    }
private:
    // Returns the next byte as a char.  For use when the exact code point of a
    // UTF-8 character isn't important.
    inline char rd()
    {
        if (pos_ > end_) {
            err("Premature EOF");
        }

        return (char) * pos_++;
    }
    // Pushes back a byte
    inline void pb(unsigned count = 1)
    {
        pos_ -= count;
    }

    // reads count characters into buf
    inline void rd(size_t count, char* buf, size_t bufCapacity)
    {
        if (pos_ + count - 1 > end_) {
            err("Premature EOF");
        }
        rw_memcpy_s(buf, bufCapacity, pos_, count);
        pos_ += count;
    }

private:
    // Returns the next code point from the string.  Internal encoding is always UTF-8.
    inline RWXmlChar rduchar()
    {
        if (pos_ > end_) {
            err("Premature EOF");
        }

        if (*pos_ <= 0x7F) {
            return RWXmlChar(*pos_++);
        }

        if (*pos_ >= 0xC2 && *pos_ <= 0xDF) {
            RWXmlChar ret = (RWXmlChar(*pos_++) & 0x1F) << 6;
            if (pos_ > end_) {
                err("Premature EOF inside character");
            }
            ret |= RWXmlChar(*pos_++) & 0x3F;
            return ret;
        }

        if (*pos_ >= 0xE0 && *pos_ <= 0xEF) {
            RWXmlChar ret = (RWXmlChar(*pos_++) & 0x0F) << 12;
            if (pos_ + 1 > end_) {
                err("Premature EOF inside character");    // 2 more chars left
            }
            ret |= (RWXmlChar(*pos_++) & 0x3F) << 6;
            ret |= RWXmlChar(*pos_++) & 0x3F;
            return ret;
        }

        //else...
        RWXmlChar ret = (RWXmlChar(*pos_++) & 0x07) << 19;
        if (pos_ + 2 > end_) {
            err("Premature EOF inside character");    //3 more chars left
        }
        ret |= (RWXmlChar(*pos_++) & 0x3F) << 12;
        ret |= (RWXmlChar(*pos_++) & 0x3F) << 6;
        ret |= RWXmlChar(*pos_++) & 0x3F;
        return ret;
    }

    inline RWCString toUTF8(RWXmlChar c)
    {
        RWSize_T len(4);
        RWCString ret(len);
        if (c <= 0x7F) {
            ret = (char)c;
        }
        else if (c <= 0x7FF) {
            ret = char(0xC0 + ((0x7C0 & c) >> 6));
            ret += char(0x80 + (0x3F & c));
        }
        else if (c <= 0xFFFF) {
            ret = char(0xE0 + ((0xF000 & c) >> 12));
            ret += char(0x80 + ((0xFC0 & c) >> 6));
            ret += char(0x80 + (0x3F & c));
        }
        else {
            ret = char(0xF0 + ((0x1C000 & c) >> 18));
            ret += char(0x80 + ((0x3F000 & c) >> 12));
            ret += char(0x80 + ((0xFC0 & c) >> 6));
            ret += char(0x80 + (0x3F & c));
        }
        return ret;
    }
    inline void toUTF8(RWXmlChar c, char*& buf)
    {
        if (c <= 0x7F) {
            *buf++ = (char)c;
        }
        else if (c <= 0x7FF) {
            *buf++ = char(0xC0 + ((0x7C0 & c) >> 6));
            *buf++ = char(0x80 + (0x3F & c));
        }
        else if (c <= 0xFFFF) {
            *buf++ = char(0xE0 + ((0xF000 & c) >> 12));
            *buf++ = char(0x80 + ((0xFC0 & c) >> 6));
            *buf++ = char(0x80 + (0x3F & c));
        }
        else {
            *buf++ = char(0xF0 + ((0x1C000 & c) >> 18));
            *buf++ = char(0x80 + ((0x3F000 & c) >> 12));
            *buf++ = char(0x80 + ((0xFC0 & c) >> 6));
            *buf++ = char(0x80 + (0x3F & c));
        }
    }

public:
    inline void err(const RWCString& txt)
    {
        int row = 1, col = 1;
        for (unsigned char* d = data_; d < pos_; d++) {
            if (*d == '\n') {
                row++;
                col = 1;
            }
            else {
                col++;
            }
        }
        throw RWXmlParseError(txt , "", size_t (row), size_t (col));
    }
private:
    // internal use only
    void readTag();
    void readContent();
    void readDocument();
    void readProlog();
    void readAndProcessBOM();
    void readName(RWCString& s);
    void readName(RWXmlName& n);
    void readAttribute();
    void addAttribute(const RWCString& name, const RWCString& val);
    void fixupAttributeURIs();
    void readComment();
    void readCDATA();
    void readPIOrXmlDecl();
    void readDocTypeDecl();
    RWXmlName getXmlName(const RWCString& name) const;
    RWCString readReference();
    void readS();

    void transcodeDocument(const RWCString& encodingName);

    // built-in transcoders
    RWCString transcode8859_1();
    RWCString transcodeUTF16BE();
    RWCString transcodeUTF16LE();

    //  --------- data members
    unsigned char* pos_, *data_, *end_; // pos_ is always positioned at the next byte
    bool ownBuffer_;
    unsigned depth_;
    RWXmlNamespaceStack namespaceStack_;

    RWCString encoding_, version_, sddecl_;
    bool hasEncoding_, hasSddecl_;
    RWXmlName lastName_;
    RWCString lastContent_;
    RWXmlAttributeSet lastAttrs_;
    NodeType lastNodeType_;
    bool peekedAhead_;

    bool expandAttributeReference_;
    // ---------- not implemented
    RWXmlReader& operator=(const RWXmlReader&);
    RWXmlReader(const RWXmlReader&);

};

#endif // rw_xmlabstractions_RWXmlReader_h_
