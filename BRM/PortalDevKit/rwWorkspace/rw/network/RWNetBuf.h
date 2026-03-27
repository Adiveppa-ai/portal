#ifndef __rw_network_RWNetBuf_h__
#define __rw_network_RWNetBuf_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWNetBuf.h#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

/*
 * RWNetBuf: a SourcePro Net - Essential Networking Module buffer
 *
 * An Essential Networking Module buffer is a buffer of bytes of data
 * plus flags indicating something about the state of the buffer.  Not
 * to be confused with a TLI netbuf, which is something completely
 * different.
 *
 * The buffer is implemented using an RWCString to hold the bytes.
 * There is no reason it has to be done this way.
 */

#include <rw/network/pkgdefs.h>
#include <rw/cstring.h>

/**
 * \ingroup networking_module
 * \class RWNetBuf
 *
 * \brief
 * Network communication buffer class.
 *
 * RWNetBuf is a network communication buffer class. A network communication
 * buffer contains bytes of data and associated flags that indicate the
 * state of the buffer. An RWNetBuf should not be confused with a TLI netbuf
 * (TLI is the Unix System V network communication interface).
 */
class RW_NETWORK_SYMBOLIC RWNetBuf
{
public:
    // The State enum indicates the state of the buffer.  Complex state
    // is indicated by or'ing together any of the following values.
    /**
     * The #State enum indicates the state of the buffer.
     */
    enum State {
        /**
         * Nothing special
         */
        normal = 1,

        /**
         * End of file
         */
        eof = 0
    };

public:
    /**
     * Constructs an empty buffer.
     */
    RWNetBuf();

    /**
     * Constructs a buffer from an RWCString. The optional state parameter
     * indicates the state of the buffer at the time of construction.
     */
    RWNetBuf(const RWCString& buf, State state = normal);

    /**
     * Returns \c true if the state of the buffer is #normal.
     */
    operator bool() const;

    /**
     * Returns an RWCString containing the buffer's contents.
     */
    operator RWCString() const;

    // use in place of operator RWCString() to avoid ambiguity
    /**
     * Returns an \c RWCString containing the buffer's contents.
     */
    RWCString getData() const;

    // use in place of operator bool() to avoid ambiguity
    /**
     * Returns the state of the buffer.
     */
    State getState() const;

private:
    RWCString buf_;
    State     state_;
};

inline RWCString
RWNetBuf::getData() const
{
    return buf_;
}

inline RWNetBuf::State
RWNetBuf::getState() const
{
    return state_;
}

#endif  // __rw_network_RWNetBuf_h__
