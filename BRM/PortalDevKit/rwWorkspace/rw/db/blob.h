#ifndef __RWDB_BLOB_H__
#define __RWDB_BLOB_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/blob.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **************************************************************************
 *
 * Definition of class RWDBBlob
 *
 * This class provides interfaces to manipulate binary blocks of data,
 * roughly corresponding to the Binary Large Objects (BLOBs) defined by many
 * RDBMS's. Like the RDBMS's BLOB, RWDBBlob adds no semantics to the data it
 * stores. Applications may wish to derive from RWDBBlob to add semantics.
 *
 **************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/collect.h>
#include <rw/tools/hash.h>


//////////////////////////////////////////////////////////////////////
//
// RWDBBlobData
//    reference counted data storage for manipulation by RWDBBlob
//
//////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBBlobData
    : public RWDBReference
{
    friend class RWDB_GLOBAL RWDBBlob;
private:
    RWDBBlobData(size_t allocation);
    RWDBBlobData(void* data, size_t length);
    ~RWDBBlobData();

    // Accessors
    size_t                  length() const;
    size_t                  capacity() const;
    RWspace                 binaryStoreSize() const;
    unsigned char*          data() const;

    // Manipulators
    void                    setLength(size_t length);

    // Helpers
    void                    acquire()
    {
        mutex_.acquire();
    }
    void                    release()
    {
        mutex_.release();
    }

private:    // Class Members

    // Multithreading safety first
    RWDBLocalRecursiveMutex mutex_;

    bool               allocated_; // allocated by us?
    size_t                  length_;    // length of data in the buffer
    size_t                  capacity_;  // allocate size of data buffer
    unsigned char*          data_;      // data buffer

private:
    // Not implemented to prevent use
    RWDBBlobData(const RWDBBlobData&);
    RWDBBlobData& operator=(const RWDBBlobData&);
};

/**
 * \ingroup db_data_types_group
 *
 * \brief
 * Stores Binary Large Objects (Blobs) and includes relevant accessors.
 *
 * Most database vendors supply one or more data types that can store binary
 * data of any length. These data types are commonly known as <em>Binary
 * Large Objects</em> or \e Blobs. The DB Interface Module stores data of
 * these types as RWDBBlob. Class RWDBBlob provides storage and rudimentary
 * access to the binary data. Applications may want to derive from RWDBBlob
 * to add semantics to the data.
 *
 * This class is implemented using a technique called <em>copy on
 * write</em>. With this technique, the copy constructor and assignment
 * operators still reference the old object and hence are very fast. An
 * actual copy is made only when a \e write is performed, that is, if the
 * object is about to be changed. The net result is excellent performance,
 * but with easy-to-understand value semantics.
 *
 * The member function putBytes() is used to populate an RWDBBlob. This
 * method is safe and robust, but can be inconvenient in cases where large
 * objects have already been loaded into memory. The constructor
 * RWDBBlob(void* data, size_t length) is provided to allow applications to
 * \e wrap existing data blocks in an RWDBBlob interface. Blobs built with
 * this constructor do \b not manage the memory addressed by the data
 * pointer; your application continues to be responsible for it.
 *
 * RWDBBlob inherits from class RWCollectable. The virtual functions of the
 * base class RWCollectable have been redefined.
 *
 * \synopsis
 * #include <rw/db/blob.h>
 *
 * RWDBBlob b;          // default; zero capacity and length
 * RWDBBlob b(2048);
 * RWDBBlob b((void*)&myGif.data(),myGif.size());
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBBlob
    : public RWCollectable
{
public:
    /**
     * Default constructor. Creates a blob with zero capacity and length.
     */
    RWDBBlob();
    /**
     * Creates a blob that has an initial capacity to store \a size bytes of
     * binary data. The length is set to zero.
     */
    RWDBBlob(size_t size);
    /**
     * Creates a blob using the data block provided. The caller retains
     * ownership of the data, and is responsible for providing an accurate
     * \a length, for ensuring that the data pointer is valid for the
     * lifetime of the blob, and for deallocation of the data, if necessary.
     */
    RWDBBlob(void* data, size_t length);

    /**
     * Copy constructor. The created blob shares data with \a blob until the
     * data is modified.
     */
    RWDBBlob(const RWDBBlob& blob);

    virtual ~RWDBBlob();

    /**
     * Assignment operator. Self shares data with \a blob until the data is
     * modified. Returns a reference to self.
     */
    RWDBBlob&        operator=(const RWDBBlob& blob);

    // public member functions

    /**
     * Sets self's data length to 0 and capacity to \a size. If the current
     * capacity is not equal to \a size, reallocates memory to adjust self's
     * capacity to \a size. To avoid reallocation of memory, pass the
     * current capacity as \a size.
     */
    void             clear(size_t size = 0);

    /**
     * Copies \a size bytes, starting at self's \a offset to \a buffer. The
     * \a buffer is assumed to be large enough to contain the bytes. Failure
     * to provide a large enough buffer results in a memory overwrite, which
     * may have unpredictable results.
     */
    void             getBytes(void* buffer, size_t size,
                              size_t offset = 0) const;

    /**
     * Copies \a size bytes from \a buffer into self, starting at self's
     * \a offset. Exactly \a size bytes are copied, and therefore \a buffer
     * is assumed to contain at least \a size bytes. Self's capacity is
     * enlarged by multiples of \a resize bytes if the existing capacity is
     * insufficient.
     */
    void             putBytes(const void* buffer, size_t size,
                              size_t offset = 0, size_t resize = 256);

    /**
     * Returns the current length of self's data in bytes.
     */
    size_t           length() const;

    /**
     * Returns the current capacity of self in bytes. This is the number of
     * bytes self can hold without resizing.
     */
    size_t           capacity() const;

    /**
     * Provides access to the blob's data as a pointer to the data storage.
     * The data storage is owned by the RWDBBlob and may not be changed or
     * deleted. If the data must be manipulated, the application should
     * derive from RWDBBlob to gain access to the protected data storage and
     * controls.
     */
    unsigned char*   data() const;    // returns pointer to actual data

    // Redefined from RWCollectable

    /**
     * Returns the number of bytes needed to store self.
     */
    virtual RWspace  binaryStoreSize() const;

    /**
     * Returns \c 0, if self and \a c share data; returns \c 1, if self has
     * length greater than \a c; returns \c -1, if \a c has length greater
     * than self, or if \a c is not an RWDBBlob via the isA() method.
     * Otherwise, returns an integer less than, greater than, or equal to
     * zero, depending upon whether self's data is less than, greater than,
     * or equal to the data of \a c, according to the semantics of the C++
     * Standard Library function \b std::memcmp().
     *
     * As a precondition, \a c is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual int      compareTo(const RWCollectable* c) const;

    /**
     * Returns \c true if self and \a c are byte for byte the same. Calls
     * compareTo() to perform the comparison.
     */
    virtual bool     isEqual(const RWCollectable* c) const;

    /**
     * Returns a hash value for use in collection classes.
     */
    virtual unsigned hash() const;

    /**
     * Writes the contents of self to \a file.
     */
    virtual void     saveGuts(RWFile& file) const;

    /**
     * Writes the contents of self to \a stream.
     */
    virtual void     saveGuts(RWvostream& stream) const;

    /**
     * Reads \a file, replacing the contents of self.
     */
    virtual void     restoreGuts(RWFile& file);

    /**
     * Reads \a stream, replacing the contents of self.
     */
    virtual void     restoreGuts(RWvistream& stream);

    /**
     * Redefined from class RWCollectable. Returns __RWDBBLOB.
     */
    virtual RWClassID isA() const;

    // any documentation for the following is in the base class
    virtual RWCollectable* newSpecies() const;
    virtual RWCollectable* copy() const;
    static RWClassID       classIsA();

    friend RWDB_SYMBOLIC RWvistream&
    operator>>(RWvistream& s, RWDBBlob*& pCl);

    friend RWDB_SYMBOLIC RWFile&
    operator>>(RWFile& f, RWDBBlob*& pCl);

    RW_INLINE_FRIEND
    RWvostream& operator<<(RWvostream& v, const RWDBBlob& Cl)
    {
        Cl.recursiveSaveOn(v);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator<<(RWFile& f, const RWDBBlob& Cl)
    {
        Cl.recursiveSaveOn(f);
        return f;
    }

    RW_INLINE_FRIEND
    RWvistream& operator>>(RWvistream& v, RWDBBlob& Cl)
    {
        RWCollectable::recursiveRestoreFrom(v, &Cl);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator>>(RWFile& f, RWDBBlob& Cl)
    {
        RWCollectable::recursiveRestoreFrom(f, &Cl);
        return f;
    }

    // multithreading operations
    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void             acquire() const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void             release() const;

private:
    static RWClassID myAtom;
    friend struct RWInit(RWDBBlob);
    friend RWCollectable* rwCreateFN(RWDBBlob)();

protected:
    RWDBCountedRef<RWDBBlobData> data_;
};


/**
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * Function object for hashing an RWDBBlob.
 *
 * Provides a C++ Standard Library-compliant hash function object suitable
 * for use with hash or unordered containers.
 */
template <>
struct RWTHash<RWDBBlob> : std::unary_function<RWDBBlob, size_t> {
    /**
     * Returns a hash of \a obj. This function is the equivalent of calling
     *
     * \code
     * obj.hash();
     * \endcode
     */
    size_t operator()(const RWDBBlob& obj) const
    {
        return obj.hash();
    }
};

#endif
