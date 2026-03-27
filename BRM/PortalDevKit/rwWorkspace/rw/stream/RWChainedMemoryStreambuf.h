#ifndef rw_stream_RWChainedMemoryStreambuf_h_
#define rw_stream_RWChainedMemoryStreambuf_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWChainedMemoryStreambuf.h#1 $
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

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable : 4275)
#endif

#include <rw/stream/pkgdefs.h>
#include <streambuf>

#ifndef RW_CHAINED_MEMORY_BUFFER_SIZE
#  define RW_CHAINED_MEMORY_BUFFER_SIZE 256
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Implementation of the \b std::streambuf interface as a linked list of
 * buffers.
 *
 * Class RWChainedMemoryStreambuf implements the iostreams \b std::streambuf
 * interface. It creates a linked list of buffers, so that existing data is
 * not copied when additional data is written to the streambuf.
 */
class RW_STREAM_GLOBAL RWChainedMemoryStreambuf
    : public std::streambuf
{
public:

    /**
     * A typedef for the character type.
     */
    typedef std::streambuf::char_type char_type;

    /**
     * A typedef for the character traits type.
     */
    typedef std::streambuf::traits_type traits_type;

    /**
     * Creates a buffer suitable for output.
     */
    RWChainedMemoryStreambuf();

    /**
     * Creates a buffer that can be used for input. If output is performed
     * to an RWChainedMemoryStreambuf that was given initial text, it is
     * appended to the end.
     *
     * \param s
     * A pointer to the initial text.
     *
     * \param len
     * The length of the initial text.
     */
    RWChainedMemoryStreambuf(const char_type* s, RWSize len);

    /**
     * Destructor.
     */
    virtual ~RWChainedMemoryStreambuf() RW_STREAMBUF_DTOR_THROWSPEC;

    /**
     * Returns the number of characters available. Can also be called on a
     * buffer that was created with an initial set of characters to
     * determine the number left to be read.
     */
    int in_avail() const;

    /**
     * Returns the length of the string that the str() function would
     * return.
     */
    int out_waiting() const;

    /**
     * Returns the length of the string that the str() function would
     * return.
     */
    RWSize num_avail() const;

    /**
     * Returns the data as a string. This function takes all of the
     * characters out of the buffer and returns them as a single string.
     * Once they have been returned, they are removed from the buffer. The
     * caller must delete the string.
     */
    char_type* str();

    /**
     * Frees the memory associated with the current internal buffer, and
     * allocates a new empty buffer.
     */
    void clear();

protected:

    /**
     * The allocated buffer is chained to the buffer currently being used,
     * and then becomes the default buffer into which elements are inserted.
     * If an error occurs, overflow() returns \c traits_type::eof();
     * otherwise it returns a value other than \c traits_type::eof().
     *
     * \param c
     * Forces a new internal buffer to be allocated, or any other 8-bit
     * value that should be inserted in the \c put area.
     */
    virtual int_type overflow(int_type c = RWChainedMemoryStreambuf::traits_type::eof());

    /**
     * Returns the first character in the \c get area if called when there
     * are characters in the \c get area. If the \c get area is empty, then
     * the function sets the \c get sequence so that it points to the
     * appropriate internal buffer. If no characters are available, the
     * function returns \c traits_type::eof().
     */
    virtual int_type underflow();

    /**
     * This function is used to fill a string backward. It adds characters
     * starting at the last position available. The function returns
     * \c traits_type::eof() in case of failure; otherwise it returns a
     * value other than \c traits_type::eof().
     *
     * \param c
     * The character to be added, or \c traits_type::eof() to move the input
     * sequence one position backward.
     */
    virtual int_type pbackfail(int_type c = RWChainedMemoryStreambuf::traits_type::eof());

    /**
     * This function always returns zero.
     */
    virtual int sync();

    /**
     * This function always returns \c traits_type::eof() to indicate
     * failure.
     */
    virtual pos_type seekoff(off_type off, std::ios_base::seekdir way,
                             std::ios_base::openmode which =
                                 std::ios_base::in | std::ios_base::out);

    /**
     * This function always returns \c traits_type::eof() to indicate
     * failure.
     */
    virtual pos_type seekpos(pos_type sp,
                             std::ios_base::openmode which =
                                 std::ios_base::in | std::ios_base::out);

    /**
     * This function gets \a n characters from the input sequence, and
     * stores them in the array pointed at by \a s. The function returns the
     * number of characters read.
     *
     * \param s
     * A pointer to the first element of the character array.
     *
     * \param n
     * The number of elements to be read.
     */
    virtual std::streamsize xsgetn(char_type* s, std::streamsize n);

    /**
     * This function stores \a n characters pointed to by \a s after the
     * \c put pointer, and increments the \c put pointer by \a n.
     *
     * \param s
     * A pointer to the first element of the character array.
     *
     * \param n
     * The number of elements to be read.
     */
    virtual std::streamsize xsputn(const char_type* s,
                                   std::streamsize n);

    virtual std::streamsize showmanyc();

private:

    void free();

    class Buffer
    {
        friend class RWChainedMemoryStreambuf;
        Buffer(Buffer* next = 0) : next_(next) {}
        char_type* limit();
        Buffer* next_;
        char_type data_[RW_CHAINED_MEMORY_BUFFER_SIZE];
    };

    Buffer*      getbuf_;
    Buffer*      putbuf_;

    // those are not allowed
    RWChainedMemoryStreambuf(const RWChainedMemoryStreambuf&);
    RWChainedMemoryStreambuf& operator=(const RWChainedMemoryStreambuf&);

};

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

#endif // rw_stream_RWChainedMemoryStreambuf_h_
