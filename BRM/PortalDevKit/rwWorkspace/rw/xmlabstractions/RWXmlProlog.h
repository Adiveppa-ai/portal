#ifndef rw_xmlabstractions_RWXmlProlog_h_
#define rw_xmlabstractions_RWXmlProlog_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlProlog.h#1 $
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

#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>

/* The RWXmlProlog class encapsulates the representation
 * and manipulation of the XML Prolog as documented in the XML 1.0 spec,
 * section, "2.8 Prolog and Document Type Declaration".  This prolog only
 * includes the XMLDecl items of the prolog and does not contain
 * the doctypedecl or Misc elements.
 * The relevant portions of the BNF grammar are:
 * [23]    XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'
 * [24]    VersionInfo    ::=    S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')
 * [80]    EncodingDecl    ::=    S 'encoding' Eq ('"' EncName '"' | "'" EncName "'" )
 * [81]    EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')*
 *             Encoding name contains only Latin characters
 * [32]    SDDecl    ::=    S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"'))
 * [26]    VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+
 */

class RW_XMLABSTRACTIONS_GLOBAL RWXmlProlog
{
public:

    /**
     * always good to have a place to hang some destruction, if needed
     */
    virtual ~RWXmlProlog();

    /**
     * Default constructor.
     */
    RWXmlProlog();

    /**
     * Copy constructor has the usual semantics
     */
    RWXmlProlog(const RWXmlProlog&);


    // public member functions

    /**
     * Assignment has copy semantics (not copy-on-write)
     */
    RWXmlProlog&                  operator=(const RWXmlProlog& n);


    /**
     * Returns an XML string that represents the contents of this object.
     */
    RWCString                     asString() const;

    /**
     * Sets the XML version number as defined in the XML 1.0 spec.
     */
    inline void                   setVersion(const RWCString& version);

    /**
     * Gets the XML version number as defined in the XML 1.0 spec.
     */
    inline RWCString              getVersion() const;

    /**
     * Sets the character encoding as defined in the XML 1.0 spec. The
     * character encoding must be used when an XML document is not in UTF-8
     * or UTF-16 encoding. "charset" is one of the set of charset names
     * registered with IANA. For the full set of charset names see:
     * http://www.iana.org/assignments/character-sets As the charset spec
     * reports:
     * "The character set names may be up to 40 characters taken from the
     * printable characters of US-ASCII."
     */
    inline void                   setCharacterEncoding(const RWCString& charset);

    /**
     * Gets the character encoding as defined in the XML 1.0 spec. Returns
     * one of the set of charset names registered with IANA. This function
     * returns the string "UTF-8" unless the user has previously used
     * setCharacterEncoding.
     */
    inline RWCString              getCharacterEncoding() const;

    /**
     * Is the CharacterEncoding set?
     */
    inline bool                   hasCharacterEncoding() const;

    /**
     * Remove the CharacterEncoding, if any
     */
    inline void                   removeCharacterEncoding();


    /**
     * Sets the SDDecl as defined in the XML 1.0 spec.
     */
    inline void                   setStandalone(const bool standalone);

    /**
     * Gets the SDDecl as defined in the XML 1.0 spec.
     */
    inline bool                   getStandalone() const;

    /**
     * Is the SDDecl set?
     */
    inline bool                   hasStandalone() const;

    /**
     * Remove the SDDecl, if any
     */
    inline void                   removeStandalone();

private:
    RWCString                     version_;
    RWCString                     characterEncoding_;
    bool                          hasCharacterEncoding_;
    bool                          standalone_;
    bool                          hasStandalone_;

};  // end of class RWXmlProlog


/**
 * operator == returns true if the names and namespace uris are both equal
 */
RW_XMLABSTRACTIONS_GLOBAL bool operator==(const RWXmlProlog&, const RWXmlProlog&);

/**
 * operator != returns true if == returns false.
 */
RW_XMLABSTRACTIONS_GLOBAL bool operator!=(const RWXmlProlog& lhs, const RWXmlProlog& rhs);

inline RWCString
RWXmlProlog::getVersion() const
{
    return version_;
}

inline void
RWXmlProlog::setVersion(const RWCString& version)
{
    version_ = version;
}


inline RWCString
RWXmlProlog::getCharacterEncoding() const
{
    return characterEncoding_;
}

inline void
RWXmlProlog::setCharacterEncoding(const RWCString& charset)
{
    characterEncoding_ = charset;
    hasCharacterEncoding_ = true;
}

inline bool
RWXmlProlog::hasCharacterEncoding() const
{
    return hasCharacterEncoding_;
}

inline void
RWXmlProlog::removeCharacterEncoding()
{
    characterEncoding_.remove(0);
    hasCharacterEncoding_ = false;
}


inline bool
RWXmlProlog::getStandalone() const
{
    return standalone_;
}

inline void
RWXmlProlog::setStandalone(const bool standalone)
{
    standalone_ = standalone;
    hasStandalone_ = true;
}

inline bool
RWXmlProlog::hasStandalone() const
{
    return hasStandalone_;
}

inline void
RWXmlProlog::removeStandalone()
{
    standalone_ = false;
    hasStandalone_ = false;
}

#endif // rw_xmlabstractions_RWXmlProlog_h_
