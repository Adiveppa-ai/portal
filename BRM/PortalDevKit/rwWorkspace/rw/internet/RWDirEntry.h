#ifndef __rw_internet_RWDirEntry_h__
#define __rw_internet_RWDirEntry_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWDirEntry.h#1 $
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
 *************************************************************************/

#include <rw/internet/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  include <rw/rwtime.h>
#endif


/**
 * \ingroup internet_basics_package
 * \class RWDirEntry
 *
 * \brief
 * A convenience class that encapsulates parsing and component storage of
 * directory entries typical of those returned from the FTP \c LIST command.
 *
 * RWDirEntry is a convenience class. It encapsulates parsing and component
 * storage of directory entries typical of those returned from the FTP
 * \c LIST command. The directory entry format is usually some variation of
 * the UNIX \c ls long format. RWDirEntry is robust in its ability to make
 * sense of the data passed to it. RWDirEntry expects text similar to the
 * following:
 *
 * <table>
 * <tr>
 * <td><b>FileType</b></td>
 * <td><b>Owner</b></td>
 * <td><b>Group</b></td>
 * <td><b>Size</b></td>
 * <td><b>Date</b></td>
 * <td><b>Time</b></td>
 * <td><b>Name</b></td>
 * <td><b>Link</b></td>
 * </tr>
 * <tr>
 * <td>\c drwxr-xr-x \c 3</td>
 * <td>\c fred</td>
 * <td>\c staff</td>
 * <td>\c 512</td>
 * <td>\c Apr \c 24</td>
 * <td>\c 16:14</td>
 * <td>\c pub</td>
 * <td></td>
 * </tr>
 * <tr>
 * <td>\c lrwxr-xr-x \c 1</td>
 * <td>\c fred</td>
 * <td>\c staff</td>
 * <td>\c 512</td>
 * <td>\c Jan \c 10</td>
 * <td>\c 1990</td>
 * <td>\c data</td>
 * <td>\c ->/data2</td>
 * </tr>
 * <tr>
 * <td>\c -rw-rw-rw- \c 1</td>
 * <td>\c fred</td>
 * <td>\c staff</td>
 * <td>\c 1024</td>
 * <td>\c Apr \c 24</td>
 * <td>\c 12:23</td>
 * <td>\c stuff</td>
 * <td></td>
 * </tr>
 * </table>
 *
 * If the owner and/or group field is missing, the parsing mechanism
 * provides empty defaults. Data type checks are performed on the fields
 * (for example, \c Size must be an integer and \c Time must be in the form
 * \c XX:XX). If any field fails its format test, the object is set to the
 * invalid state and an error text message is saved. This message is
 * available through the getError() method. If the directory entry parse
 * fails, a copy of the original input string is available through the
 * getData() method.
 *
 * \example
 * \code
 * #include <rw/rstream.h>
 * #include <rw/cstring.h>
 * #include <rw/network/RWWinSockInfo.h>
 * #include <rw/internet/RWDirEntry.h>
 *
 * int
 * main()
 * {
 *     RWWinSockInfo info;
 *
 *     RWCString text =
 *     "lrwxr-xr-x 1 fred staff 512 Jan 10 1990 data -> /data2"
 *
 *     RWDirEntry de = RWDirEntry(text);
 *
 *     cout << de.getName()  << endl;
 *     cout << de.getDateTime()  << endl;
 *     cout << de.getLink()  << endl;
 *     return 0;
 * }
 * \endcode
 *
 * Program Output
 *
 * \code
 * data
 * 01/10/90 12:00:00
 * /data2
 * \endcode
 * \endexample
 */
class RW_INTERNET_SYMBOLIC RWDirEntry
{

public:

    /**
     * Enumerates the possible file types in the file field of an RWDirEntry
     * object.
     */
    enum entryType {

#if !defined(RW_DISABLE_DEPRECATED)

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWDirEntry::ftype_directory "ftype_directory" instead.
         *
         * Entry is a directory.
         */
        RW_DEPRECATE_ENUMERATOR(DIRECTORY, "Use RWDirEntry::ftype_directory instead") = 0,

        /**
         * \deprecated
         * As of SourcePro 1, use \ref RWDirEntry::ftype_link "ftype_link"
         * instead.
         *
         * Entry is a link.
         */
        RW_DEPRECATE_ENUMERATOR(LINK, "Use RWDirEntry::ftype_link instead") = 1,

        /**
         * \deprecated
         * As of SourcePro 1, use \ref RWDirEntry::ftype_file "ftype_file"
         * instead.
         *
         * Entry is a file.
         */
        RW_DEPRECATE_ENUMERATOR(FILE, "Use RWDirEntry::ftype_file instead") = 2,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWDirEntry::ftype_unknown "ftype_unknown" instead.
         *
         * Entry is an unknown type.
         */
        RW_DEPRECATE_ENUMERATOR(UNKNOWN, "Use RWDirEntry::ftype_unknown instead") = 3,

#endif

        /**
         * Entry is a directory.
         */
        ftype_directory = 0,

        /**
         * Entry is a link.
         */
        ftype_link = 1,

        /**
         * Entry is a file.
         */
        ftype_file = 2,

        /**
         * Entry is an unknown type.
         */
        ftype_unknown = 3

    };

    /**
     * Constructs a default invalid directory entry.
     */
    RWDirEntry();

    /**
     * Constructs an RWDirEntry object from an RWCString.
     */
    RWDirEntry(const RWCString& line);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWDirEntry::getData() instead")
    RWCString       data() const;
#endif
    /**
     * Returns the raw text that was used to build the object. It is valid
     * to use this method on an object that returns \c false from the
     * isValid() method. It is useful in the event that the entry text could
     * not be parsed successfully. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString       getData() const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWDirEntry::getType() instead")
    entryType type() const;
#endif
    /**
     * Returns the type of the entry.
     */
    entryType getType() const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWDirEntry::getName() instead")
    RWCString       name() const;
#endif
    /**
     * Returns the name of the entry. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString       getName() const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWDirEntry::getSize() instead")
    int             size() const;
#endif
    /**
     * Returns the size of the entry.
     */
    int             getSize() const;
    // Gets the size of the file. Note: This value is
    // generally rounded up by the native file system
    // and should not be considered exact.

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    RW_DEPRECATE_FUNC("Use RWDirEntry::getDateTime() instead")
    RWTime          time() const;

    /**
     * Returns the time that the file was created.
     *
     * Typically, files that are at least one year old have only a creation
     * date. For these entries, this method returns 12:00:00. For files less
     * than one year old, the year is typically not specified -- the year is
     * either the current or previous year, depending on the current date.
     * For example, if the current date is 10/15 and the file date is 9/2
     * (no year), the year of the file is assumed to be the current year. If
     * the current date is 1/4, and the file date is 9/2, the year of the
     * file is assumed to be the previous year.
     *
     * \deprecated 
     * As of SourcePro 10, use getDateTime() instead.
     */
    RW_DEPRECATE_FUNC("Use RWDirEntry::getDateTime() instead")
    RWTime          getTime() const;

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * Returns an RWDateTime object containing the date and time that the file
     * was created.
     *
     * Typically, files that are at least one year old have only a creation
     * date. For these entries, this method returns 12:00:00. For files less
     * than one year old, the year is typically not specified -- the year is
     * either the current or previous year, depending on the current date.
     * For example, if the current date is 10/15 and the file date is 9/2
     * (no year), the year of the file is assumed to be the current year. If
     * the current date is 1/4, and the file date is 9/2, the year of the
     * file is assumed to be the previous year.
     */
    RWDateTime      getDateTime() const;

    // Gets the time the file was created.  Note that
    // if the file was specified as a year rather then
    // time by the server this method will return
    // 12:00 PM.

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWDirEntry::getLink() instead")
    RWCString       link() const;
#endif
    /**
     * Returns the link destination if the entry is of type \c LINK. If the
     * entry is not of type \c LINK, an empty string is returned. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWCString       getLink() const;

    /**
     * Returns \c true if the entry was parsed successfully. If it was not,
     * the getData() method can be used to retrieve the original text, and
     * the getError() method can be used to return a text description of the
     * parse error.
     */
    bool       isValid() const;
    // Returns true if the directory entry was parsed successfully.
    // Note: Not all ftp servers return the directory information
    // in a consistent way.  For this reason the data() method
    // is provided to obtain a copy of the original text buffer.

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWDirEntry::getError() instead")
    RWCString       error() const;
#endif
    /**
     * Returns a text description of the error that was encountered during
     * the directory entry parsing phase. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString       getError() const;

private:

    /**
     * Outputs an RWDirEntry object to an \c std::ostream in a common
     * format.
     *
     * \note
     * This class does not have an extraction (>>) operator.
     */
    friend RW_INTERNET_SYMBOLIC std::ostream&
    operator<< (std::ostream& str, const RWDirEntry&);

private:

    void init();
    // Resets to the invalid state

    void parse(const RWCString& line);
    // Parses the text representation

    void setInvalid(const RWCString& reason);
    // Sets the reason why it's invalid

    RWCString       data_;
    entryType       type_;
    RWCString       name_;
    RWCString       linkdest_;
    int             size_;
    RWDateTime      time_;
    bool       isValid_;
    RWCString       reason_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWDirEntry::data() const
{
    return getData();
}

inline RWCString
RWDirEntry::link() const
{
    return getLink();
}

inline RWCString
RWDirEntry::error() const
{
    return getError();
}

inline RWDirEntry::entryType
RWDirEntry::type() const
{
    return getType();
}

inline RWCString
RWDirEntry::name() const
{
    return getName();
}

inline int
RWDirEntry::size() const
{
    return getSize();
}

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

inline RWTime
RWDirEntry::time() const
{
    return getTime();
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWDirEntry instead") RWDirEntry RWIDirEntry;
#endif

#endif

#endif // __rw_internet_RWDirEntry_h__
