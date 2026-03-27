#ifndef __rw_internet_RWNumReply_h__
#define __rw_internet_RWNumReply_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWNumReply.h#1 $
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

#include <rw/internet/RWNumReplyLine.h>
#include <rw/internet/RWReply.h>
#include <rw/internet/pkgdefs.h>
#include <rw/network/fwd.h>
#include <rw/cstring.h>
#include <rw/tpslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup internet_basics_package
 *
 * \brief
 * Encapsulates a numerical protocol reply typical of many common Internet
 * protocols.
 *
 * RWNumReply encapsulates a numerical protocol reply typical of many common
 * Internet protocols. For instance, FTP replies in the forms shown in the
 * following table are parsed first into RWNumReplyLine objects and then
 * stored in an RWNumReply object. Individual RWNumReplyLine objects can be
 * obtained using the operator[]().
 *
 * <table>
 * <tr>
 * <td><b>Single Line Replies</b></td>
 * <td><b>Multiple Line Replies</b></td>
 * </tr>
 * <tr>
 * <td>\c 200 \c Command \c Ok</td>
 * <td>\c 220-Text \c Message \c 1</td>
 * </tr>
 * <tr>
 * <td></td>
 * <td>\c Text \c Message \c 2</td>
 * </tr>
 * <tr>
 * <td></td>
 * <td>\c Text \c Message \c 3</td>
 * </tr>
 * <tr>
 * <td></td>
 * <td>\c 220 \c Text \c Message \c 4</td>
 * </tr>
 * </table>
 *
 * The numerical portion of a reply is a 3-digit number in US-ASCII. The
 * first digit of the number indicates the general status of the result of a
 * command. Convenience methods included in RWNumReply enable your
 * application to determine the category (\c 1XX, \c 2XX, \c 3XX, \c 4XX, or
 * \c 5XX).
 */
class RW_INTERNET_GLOBAL RWNumReply : public RWReply
{

public:

    /**
     * Constructs a default invalid RWNumReply object. Using the object
     * without initializing it causes an RWReplyError exception to be
     * thrown.
     */
    RWNumReply(void);

    /**
     * Copy constructor.
     */
    RWNumReply(const RWNumReply& r);

    /**
     * Assignment operator. Sets self to the contents of \a reply. The
     * previous contents of self are lost.
     */
    RWNumReply&
    operator=(const RWNumReply& reply);

    /**
     * Releases the memory used by each internal RWNumReplyLine object.
     */
    virtual ~RWNumReply(void);

    /**
     * Clears all RWNumReplyLine objects from self.
     */
    void clearAndDestroy(void);

    /**
     * Returns \c true if the RWNumReplyLine objects in the reply are
     * members of the specified numerical reply family. For more information
     * about reply families, see RFC 959.
     *
     * \note
     * Only one of the above five methods returns true for any given
     * instance.
     */
    bool is1XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is2XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is3XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is4XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is5XX(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWNumReply::getData() instead")
    RWCString data(void) const;
#endif
    /**
     * Returns the raw data that was used to construct the first
     * RWNumReplyLine object in the reply. This is a convenience routine and
     * is equivalent to getting the first RWNumReplyLine object and calling
     * its RWNumReplyLine::getData() method. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString getData(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWNumReply::getStatusCode() instead")
    unsigned int code(void) const;
#endif
    /**
     * Returns the numeric code of the reply lines in the reply. All reply
     * lines share the same code.
     */
    unsigned int getStatusCode(void) const;

    /**
     * Returns the number of RWNumReplyLine objects that are contained
     * within self.
     */
    size_t entries(void) const;

    /**
     * Indexing operator. Returns a reference to the \a i <sup>th</sup>
     * RWNumReplyLine object in self.
     */
    const RWNumReplyLine& operator[](size_t i) const;

protected:

    /**
     * Reads data from the \a portal to construct RWNumReplyLine objects in
     * self.
     */
    void readFromPortal(const RWPortal& portal);

    /**
     * Appends an RWNumReplyLine object to the internal RWNumReplyLine list.
     */
    void append(RWNumReplyLine& r);

    /**
     * Makes a deep copy of \a r to self. The previous contents of self are
     * lost.
     */
    void copy(const RWNumReply& r);

    /**
     * Provides a general parsing mechanism for data used to construct
     * RWNumReplyLine objects. In cases where additional data is available
     * to these specific classes, derived classes may provide their own
     * parse methods to override this method.
     */
    virtual void parse(void);

private:

    /**
     * Outputs an RWNumReply object to an \c std::ostream.
     *
     * \note
     * This class does not have an extraction (>>) operator.
     */
    friend RW_INTERNET_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWNumReply& r);

private:

    RWTPtrSlist<RWNumReplyLine> replylist_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWNumReply::data(void) const
{
    return getData();
}

inline unsigned int
RWNumReply::code(void) const
{
    return getStatusCode();
}

typedef RW_DEPRECATE_TYPE("Use RWNumReply instead") RWNumReply RWINumReply;
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_internet_RWNumReply_h__
