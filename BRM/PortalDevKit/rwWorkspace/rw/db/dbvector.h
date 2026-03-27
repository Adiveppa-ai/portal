#ifndef __RWDB_DBVECTOR_H__
#define __RWDB_DBVECTOR_H__

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbvector.h#1 $
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
 ********************************************************************/

#include <rw/db/tbuffer.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use RWDBTBuffer instead.
 *
 * \brief
 * Deprecated. Used as a buffer when transferring data between the
 * application and the database.
 *
 * Class RWDBVector is derived from RWDBTBuffer and is used to transfer data
 * between the application and the database via classes RWDBBulkReader and
 * RWDBBulkInserter.
 *
 * \synopsis
 * #include <rw/db/dbvector.h>
 *
 * RWDBVector< int > intVector(n);
 * \endsynopsis
 *
 * \example
 * The following example uses an \ref RWDBVector "RWDBVector<int>" to insert
 * an array of integers into a table. The 5th element in the array is
 * inserted as \c NULL.
 *
 * \code
 * RWDBVector< int > intVector(n);
 *
 * // Sets the 5th element to be null.
 * intVector.setNull(4); // 0 based array.
 *
 * // Populates the arrays using a user-defined function.
 * setValues(intVector);
 *
 * // Defines the inserter.
 * RWDBBulkInserter ins = tab.bulkInserter(connection);
 *
 * // Shifts the arrays into the inserter.
 * ins << intVector;
 *
 * // Inserts up to n values at a time.
 * RWDBStatus stat = ins.execute();
 * \endcode
 * \endexample
 */
template <class T>
class RW_DEPRECATE_TYPE("Use RWDBTBuffer<T> instead") RWDBVector : public RWDBTBuffer<T>
{
public:
    RWDBVector(size_t n)
        : RWDBTBuffer<T>(n)
    {
    }
    virtual ~RWDBVector()
    {
    }
};

/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use RWDBBlob along with
 * \ref RWDBTBuffer "RWDBTBuffer<RWDBBlob>" instead.
 *
 * \brief
 * Deprecated. Encapsulates arrays of unsigned characters stored in
 * RWDBBinaryVector instances.
 *
 * RWDBBinaryVectorElement is used to encapsulate arrays of unsigned
 * characters stored in RWDBBinaryVector instances. A method is provided for
 * assigning the data held in RWDBBlob instances.
 *
 * \synopsis
 * #include <rw/db/dbvector.h>
 *
 * RWDBBinaryVector binaryVector(width, length);
 * RWDBBinaryVectorElement element = binaryVector[i];
 * \endsynopsis
 *
 * \example
 * In the following example, the \c i<sup>th</sup> element of vector
 * \c binaryVector is assigned the data held in \c ablob:
 *
 * \code
 * RWDBBinaryVector binaryVector(width,length);
 * RWDBBlob ablob;
 *
 * binaryVector[i] = ablob;
 * \endcode
 * \endexample
 */

class RW_DEPRECATE_TYPE("Use RWDBBlob and RWDBTBuffer<RWDBBlob> instead") RWDBBinaryVectorElement
{
public:
    RWDBBinaryVectorElement(size_t index, RWDBTBuffer<unsigned char>* theBuffer)
        : index_(index), buffer_(theBuffer)
    {
    }

    /**
     * Assignment operator. Assigns the data held in \a blob to self.
     */
    RWDBBinaryVectorElement& operator=(const RWDBBlob& blob)
    {
        // Assert that we weren't asked to copy in a blob larger than we
        // can accurately hold.
        RW_ASSERT(blob.length() <= buffer_->width());

        // memmove() the data into our unsigned char buffer.
        memmove((&(*buffer_)[index_]), blob.data(), blob.length());

        // remember the length, store it in the length buffer.
        buffer_->setWidth(index_, blob.length());

        return *this;
    }
    /**
     * Conversion operator. Returns the <tt>unsigned char*</tt> represented
     * by self.
     */
    operator unsigned char* ()
    {
        return data();
    }

    /**
     * Returns the <tt>unsigned char*</tt> represented by self.
     */
    unsigned char* data() const
    {
        return (&(*buffer_)[index_]);
    }
private:
    size_t index_;
    RWDBTBuffer<unsigned char>* buffer_;
};


//////////////////////////////////////////////////////////////////////
//
// ** DEPRECATED **
// RWDBStringVectorElement
//   Provided only for backward compatibility, new code should be
//   written using RWCString directly.
//
//////////////////////////////////////////////////////////////////////
/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use RWCString along with
 * \ref RWDBTBuffer "RWDBTBuffer<RWCString>" instead.
 *
 * \brief
 * Deprecated. Encapsulates arrays of characters stored in RWDBStringVector
 * objects.
 *
 * RWDBStringVectorElement objects are used to encapsulate arrays of
 * characters stored in RWDBStringVector objects. A method is provided for
 * assigning the data held in instances of RWCString.
 *
 * \synopsis
 * #include <rw/db/dbvector.h>
 *
 * RWDBStringVector stringVector(width, length);
 * RWDBStringVectorElement element = stringVector[i];
 * \endsynopsis
 *
 * \example
 * In the following example the \c i<sup>th</sup> element of vector
 * \c stringVector is assigned the data held in \c astring:
 *
 * \code
 * RWDBStringVector stringVector(width,length);
 * RWCString astring;
 *
 * stringVector[i] = astring;
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWCString and RWDBTBuffer<RWCString> instead") RWDBStringVectorElement
{
public:
    RWDBStringVectorElement(size_t index, RWDBTBuffer<char>* theBuffer)
        : index_(index), buffer_(theBuffer)
    {
    }

    /**
     * Assigns the data held in \a s to self.
     */
    RWDBStringVectorElement& operator=(const RWCString& s)
    {
        // Assert that we weren't asked to copy a string larger than
        // we can hold.
        // we use < as opposed to <= because there also has to be room
        // for the \0.
        RW_ASSERT(s.length() < buffer_->width());

        // memcpy() the data into our char buffer.
        // make sure to copy the null by doing the +1.
        memcpy((&(*buffer_)[index_]), s.data(), s.length() + 1);

        // Remember the length, store it in the length buffer.
        buffer_->setWidth(index_, s.length());
        //(*(RWDBTSingleBuffer<RWDBResultOutputSize>*)
        //    (buffer_->lengthBinding()))[index_] = s.length();

        return *this;
    }

    /**
     * Conversion operator. Returns the \c char* represented by self.
     */
    operator char* ()
    {
        return data();
    }

    /**
     * Returns the \c char* represented by self.
     */
    char* data() const
    {
        return (&(*buffer_)[index_]);
    }

private:
    size_t index_;
    RWDBTBuffer<char>* buffer_;
};

/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use RWDecimalPortable along with
 * \ref RWDBTBuffer "RWDBTBuffer<RWDecimalPortable>" instead.
 *
 * \brief
 * Deprecated. Encapsulates arrays of decimals stored in RWDBDecimalVector
 * objects.
 *
 * RWDBDecimalVectorElement objects are used to encapsulate arrays of
 * decimals stored in RWDBDecimalVector objects. A method is provided for
 * assigning the data held in instances of RWDecimalPortable.
 *
 * \synopsis
 * #include <rw/db/dbvector.h>
 *
 * RWDBDecimalVector decVector(width, length);
 * RWDBDecimalVectorElement element = decVector[i];
 * \endsynopsis
 *
 * \example
 * In the following example the \c i<sup>th</sup> element of vector
 * \c decVector is assigned the data held in \c dec:
 *
 * \code
 * RWDBDecimalVector decVector(width,length);
 * RWDecimalPortable dec("3.1415926");
 *
 * decVector[i] = dec;
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWDecimalPortable and RWDBTBuffer<RWDecimalPortable> instead") RWDBDecimalVectorElement
{
public:
    RWDBDecimalVectorElement(size_t index, RWDBTBuffer<char>* theBuffer)
        : index_(index), buffer_(theBuffer)
    {
    }

    /**
     * Assigns the data held in \a val to self.
     */
    RWDBDecimalVectorElement& operator=(const RWDecimalPortable& val)
    {
        // convert the decimal portable to a string, and then copy it in.
        RWCString str = val;
        size_t copyLength = str.length() <= buffer_->width() - 1 ?
                            str.length() : buffer_->width() - 1;
        strncpy((&(*buffer_)[index_]), str.data(), copyLength);
        *((char*)(buffer_->data()) + index_ * buffer_->width() + copyLength) = '\0';
        // remember the length, store it in the length buffer.
        buffer_->setWidth(index_, copyLength);


        return *this;
    }

    /**
     * Assigns the data held in \a val to self.
     */
    RWDBDecimalVectorElement& operator=(const long val)
    {
        *this = RWDecimalPortable(val);
        return *this;
    }

    /**
     * Assigns the data held in \a val to self.
     */
    RWDBDecimalVectorElement& operator=(const int val)
    {
        *this = RWDecimalPortable(val);
        return *this;
    }

    /**
     * Conversion operator. Returns the \c char* represented by self.
     */
    operator char* ()
    {
        return (&(*buffer_)[index_]);
    }
private:
    size_t index_;
    RWDBTBuffer<char>* buffer_;
};

/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use \ref RWDBTBuffer "RWDBTBuffer<RWDBBlob>" and
 * RWDBBlob instead.
 *
 * \brief
 * Deprecated. Transfers binary arrays between the application and the
 * database.
 *
 * RWDBBinaryVector instances are used to transfer binary arrays of width
 * \c width between the application and the database via classes
 * RWDBBulkReader and RWDBBulkInserter.
 *
 * \synopsis
 * #include <rw/db/dbvector.h>
 *
 * RWDBBinaryVector binaryVector(width, length);
 * \endsynopsis
 *
 * \example
 * In the following example, the \c i<sup>th</sup> element of an
 * RWDBBinaryVector is set to hold the data \c Hello, and the data and width
 * are output to the screen.
 *
 * \code
 * RWDBBinaryVector binaryVector(width, length);
 * .
 * .
 * .
 * binaryVector[i] = RWDBBlob("Hello", 5);
 * .
 * .
 * .
 * RWDBBinaryVectorElement element = binaryVector[i];
 * // print the contents of the element
 * cout << "length of element is:  " << binaryVector.width(i) << endl;
 * cout << "the element's data is:  ";
 * unsigned char* ptr = (unsigned char*) element;
 * for (size_t j = 0; j < binVector.width(i); ++j, ++ptr)
 *   cout.put(*ptr);
 * cout << endl;
 * \endcode
 *
 * Program Output:
 * \code
 * length of element is: 5
 * the element's data is: Hello
 * \endcode
 * \endexample
 */

class RW_DEPRECATE_TYPE("Use RWDBTBuffer<RWDBBlob> and RWDBBlob instead") RWDBBinaryVector : public RWDBTBuffer<unsigned char>
{
public:

    /**
     * Constructs an RWDBBinaryVector of \a length elements, each of whose
     * elements is \a width wide.
     */
    RWDBBinaryVector(size_t width, size_t length)
        : RWDBTBuffer<unsigned char>(length, width)
    {
        //this->length_ =
        //    new RWDBTSingleBuffer<RWDBResultOutputSize>(length);
        //this->ownsLength_ = true;
    }

    /**
     * Returns an RWDBBinaryVectorElement holding a reference to the \a i
     * <sup>th</sup> element of self.
     */
    RWDBBinaryVectorElement operator[](size_t i)
    {
        return RWDBBinaryVectorElement(i, this);
    }

    /**
     * Returns the number of elements in self.
     */
    size_t length() const
    {
        return entries();
    }

private:

};

//////////////////////////////////////////////////////////////////////
//
// ** DEPRECATED **
// RWDBStringVector
//   Provided only for backward compatibility, new code should be
//   written using RWDBTBuffer<RWCString> or RWDBTBuffer<char> directly.
//
//////////////////////////////////////////////////////////////////////
/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use \ref RWDBTBuffer "RWDBTBuffer<RWCString>" and
 * RWCString instead.
 *
 * \brief
 * Deprecated. Transfers character arrays of width \c width between the
 * application and the database.
 *
 * RWDBStringVector instances are used to transfer character arrays of width
 * \c width between the application and the database via classes
 * RWDBBulkReader and RWDBBulkInserter. Note that it is the user's
 * responsibility to ensure that the elements of the vectors are null
 * terminated, and so the width of each element should be set to accommodate
 * this additional character.
 *
 * \synopsis
 * #include <rw/db/dbvector.h>
 *
 * RWDBStringVector stringVector(width, length);
 * \endsynopsis
 *
 * \example
 * In the following example, the \c i<sup>th</sup> element of an
 * RWDBStringVector is set to the string \c "Hello";
 *
 * \code
 * RWDBStringVector stringVector(width, length);
 * .
 * .
 * .
 * stringVector[i] = RWCString("Hello");
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWDBTBuffer<RWCString> and RWCString instead") RWDBStringVector : public RWDBTBuffer<char>
{
public:
    /**
     * Constructs an RWDBStringVector of \a length elements, each of whose
     * elements is \a width wide.
     */
    RWDBStringVector(size_t width, size_t length)
        : RWDBTBuffer<char>(length, width, true)
    {
    }

    /**
     * Returns an RWDBStringVectorElement instance holding a reference to
     * the \a i <sup>th</sup> element of self.
     */
    RWDBStringVectorElement operator[](size_t i)
    {
        return RWDBStringVectorElement(i, this);
    }

    /**
     * Returns the number of elements in self.
     */
    size_t length() const
    {
        return entries();
    }
};

/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use \ref RWDBTBuffer "RWDBTBuffer<RWDecimalPortable>"
 * and RWDecimalPortable instead.
 *
 * \brief
 * Deprecated. Transfers decimal arrays of width \c width between the
 * application and the database. \c width between the application and the
 * database.
 *
 * RWDBDecimalVector instances are used to transfer decimal arrays of width
 * \c width between the application and the database via instances of
 * RWDBBulkReader and RWDBBulkInserter. Note that it is the user's
 * responsibility to ensure that the elements of the vectors are null
 * terminated.
 *
 * \synopsis
 * #include <rw/db/dbvector.h>
 *
 * RWDBDecimalVector decVector(width, length);
 * \endsynopsis
 *
 * \example
 * In the following example, the \c i<sup>th</sup> element of an
 * RWDBDecimalVector is set to the decimal \c 12.567:
 *
 * \code
 * RWDBDecimalVector decVector(width, length);
 * .
 * .
 * .
 * decVector[i] = "12.567";
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWDBTBuffer<RWDecimalPortable> and RWDecimalPortable instead") RWDBDecimalVector : public RWDBTBuffer<char>
{
public:
    /**
     * Constructs an RWDBDecimalVector of \a length elements, each of whose
     * elements is \a width wide.
     */
    RWDBDecimalVector(size_t width, size_t length)
        : RWDBTBuffer<char>(length, width, true)
    {
    }

    /**
     * Returns an RWDBDecimalVectorElement instance holding a reference to
     * the \a i <sup>th</sup> element of self.
     */
    RWDBDecimalVectorElement operator[](size_t index)
    {
        return RWDBDecimalVectorElement(index, this);
    }

    /**
     * Returns the number of elements in self.
     */
    size_t length() const
    {
        return entries();
    }

};

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif
