#ifndef rw_xmlabstractions_RWXmlUtils_h_
#define rw_xmlabstractions_RWXmlUtils_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlUtils.h#1 $
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

#include <rw/xmlabstractions/fwd.h>
#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/rwdate.h>
#include <rw/tools/datetime.h>
#include <rw/tools/decport.h>


/**************************************************************************
 * RWXmlUtils is a utility class used internally. However,
 * applications are free to use this if they find the helper
 * functionality useful. In addition to some string processing helper
 * functions, this class also contains helper functions for converting
 * between DOM classes and standard classes
 ***************************************************************************/
class  RW_XMLABSTRACTIONS_GLOBAL RWXmlUtils
{
public:
    static RWCString   stripWhiteSpaceAndNewlines(const RWCString& str, RWCString::stripType toStrip = RWCString::both);

    static RWCString getPrefix(const RWCString& qName);
    static void        getPrefixAndLocalName(const RWCString& qName,
            RWCString& prefix,
            RWCString& lname);

    static RWCString   changeName(const RWXmlName& name, const RWCString& element);

    static RWDateTime           convertISODateStringToDateTime(
        const RWCString& anISODateStr);

    static RWCString            convertDateTimeToISOString(const RWDateTime& dt,
            const RWCString& format = ISO8601Format);

    static RWDate               convertISODateStringToDate(
        const RWCString& anISODateStr);

    static RWCString            convertDateToISOString(const RWDate& dt);

    static inline bool          isWhiteSpace(const char c);

    static RWCString            convertCharset(const RWCString& buffer, const RWCString& from, const RWCString& to);

    /**
     * Does a simple canonical comparison of 2 XML docs. Elements are
     * expected to be in order, otherwise returns false Whitespace between
     * an endTag and startTag of 2 different elements is considered
     * insignificant Attributes can be in any order. Whitespace in attribute
     * list is considered insignificant
     */
    static bool                 compareXml(const RWCString& xml1, const RWCString& xml2);

    /**
     * Compares 2 attribute sets and returns true if they are equal. The
     * "==" and compareTo() operators of RWXmlAttributeSet do comparison
     * based only on the name of the attribute and not on the value
     * associated with each attribute.
     *
     * This does a comparison both on the name and the value of each
     * corresponding attribute
     */
    static bool                 compareAttributeSet(const RWXmlAttributeSet& a1,
            const RWXmlAttributeSet& a2);

private:
    static bool                 verifyEmptyTag(RWXmlReader& rdr, RWXmlReader& rdr2);
    static bool                 verifyEmptyData(RWXmlReader& rdr, RWXmlReader& rdr2);


public:
    // Some often used string constants
    // These are duplicates of those found in RWSoapUtils
    // At some point we should look at consolidating the two sets of
    // constants in one place but unfortunately both are publicly visible.

    static const RWCString           Blank;
    static const RWCString           EmptyString;
    static const RWCString           Colon ;
    static const RWCString           Hypen ;  // Obsolete.  Left in for backward compatibility.
    static const RWCString           Hyphen;
    static const RWCString           ISO8601Format;
    static const RWCString           ISO8601Date;
    static const RWCString           ISO8601Time;
    static const RWCString           Minus ;
    static const RWCString           Newline;
    static const RWCString           Plus;
    static const RWCString           Tab;
    static const RWCString           TimeSeparator;
    static const RWCString           TZD;
    static const RWCString           UTimeZone;
    static const RWCString           WhiteSpace;

    static const char                BlankUtf8;
    static const char                NewlineUtf8;
    static const char                TabUtf8;

    static const size_t              MinDateLength ;
    static const size_t              MinTimeLength ;
    static const size_t              MinDateTimeLength ;

};

inline bool
RWXmlUtils::isWhiteSpace(const char c)
{
    return (c == BlankUtf8 || c == NewlineUtf8 || c == TabUtf8 ? true : false);  // ' ' | '\n' | '\t'
}

#endif // rw_xmlabstractions_RWXmlUtils_h_
