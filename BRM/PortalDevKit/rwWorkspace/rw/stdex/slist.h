#ifndef RW_TOOLS_STDEX_SLIST_H__
#define RW_TOOLS_STDEX_SLIST_H__
/**********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stdex/slist.h#1 $
 *
 * Copyright (c) 1989-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **********************************************************************/

#include <rw/defs.h>
#include <rw/edefs.h> // for rw_move
#include <rw/tools/traits/RWTEnableIf.h>
#include <rw/tools/traits/RWTIsIntegral.h>
#include <algorithm>
#include <iterator>
#include <limits>
#include <utility>

template <typename T, typename N, typename D> class rw_slist_iterator_base;
template <typename T> struct rw_slist_node;


/**
 * \internal
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * A node in a singly-linked list.
 *
 * rw_slist_node_base represents an element in a singly-linked list. It
 * maintains a pointer to the next node in the list.
 */
template <typename T>
struct rw_slist_node_base {
    /**
     * Constructs an rw_slist_node_base with a pointer \a next to the next
     * node in the chain.
     */
    rw_slist_node_base(rw_slist_node<T>* next);

    /**
     * Pointer to the next node in the chain.
     */
    rw_slist_node<T>* next_;
};


/**
 * \internal
 *
 * \brief
 * A node in a singly-linked list that maintains the value at that node.
 *
 * rw_slist_node represents an element in a singly-linked list. In addition
 * to the pointer to next, it also stores an object of type T.
 */
template <typename T>
struct rw_slist_node : public rw_slist_node_base<T> {
    /**
     * Constructs an rw_slist_node with the value \a val stored at this node
     * and a pointer \a next to the next node in the chain.
     */
    rw_slist_node(const T& val, rw_slist_node* next);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * Constructs an rw_slist_node with the value \a val stored at this node
     * and a pointer \a next to the next node in the chain.
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    rw_slist_node(T&& val, rw_slist_node* next);
#endif

    /**
     * The value stored at this node.
     */
    T value_;
};


/**
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * Maintains a collection of some type T implemented as a singly-linked
 * list.
 *
 * Class rw_slist maintains a collection of \c T, implemented as a
 * singly-linked list. Since this is a \e value-based list, objects are
 * \e copied into and out of the links that make up the list. As with all
 * classes that meet the ANSI \e sequence specification, rw_slist provides
 * for iterators that reference its elements.
 *
 * \note
 * Unlike std::list and std::forward_list, operations that alter the
 * contents of rw_slist invalidate iterators that reference elements at or
 * after the location of change.
 */
template <typename T, typename A = std::allocator<T> >
class rw_slist
{
public:
    /**
     * \internal
     *
     * A type representing the head node.
     */
    typedef rw_slist_node_base<T> base_node_type;

    /**
     * \internal
     *
     * A type representing a node within the container.
     */
    typedef rw_slist_node<T> node_type;

    /**
     * A type representing the value stored in the container.
     */
    typedef T value_type;

    /**
     * A type that provides a reference to an element in the container.
     */
    typedef value_type& reference;

    /**
     * A type that provides a \c const reference to an element in the
     * container.
     */
    typedef const value_type& const_reference;

    /**
     * A type that provides a pointer to an element in the container.
     */
    typedef value_type* pointer;

    /**
     * A type that provides a \c const pointer to an element in the
     * container.
     */
    typedef const value_type* const_pointer;

    /**
     * A type representing the allocator type for the container.
     */
#if defined(RW_ALLOC_INTERFACE_STLV2X_HACK)
    typedef std::allocator_interface < std::allocator<node_type>, node_type>
    allocator_type;
#elif defined(DOXYGEN) || !defined(RW_ALLOCATOR_NO_REBIND)
    typedef typename A::template rebind<node_type>::other allocator_type;
#else
    typedef std::allocator<node_type> allocator_type;
#endif

    /**
     * A signed integral type used to indicate the distance between two
     * valid iterators on the same container.
     */
    typedef typename allocator_type::difference_type difference_type;

    /**
     * An unsigned integral type used for counting the number of elements in
     * the container.
     */
    typedef typename allocator_type::size_type size_type;

    /**
     * A type that provides a forward iterator over the elements in the
     * container.
     */
    typedef rw_slist_iterator_base<T, base_node_type, difference_type> iterator;

    /**
     * A type that provides a \c const forward iterator over the elements in
     * the container.
     */
    typedef rw_slist_iterator_base<const T, const base_node_type, difference_type> const_iterator;

    /**
     * Constructs an empty rw_slist.
     */
    rw_slist();

    /**
     * Constructs an rw_slist that is a copy of \a x. Each element from \a x
     * is copied into self.
     */
    rw_slist(const rw_slist<T, A>& x);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * Move constructor. The constructed list takes ownership of the data
     * owned by \a x.
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    rw_slist(rw_slist<T, A>&& x);
#endif // !RW_NO_RVALUE_REFERENCES

    /**
     * Constructs an rw_slist containing a copy of each element in the range
     * [\a first, \a last).
     *
     * \c InputIterator is an input iterator type that points to elements
     * that are convertible to #value_type objects.
     */
    template <typename InputIterator>
#if !defined(DOXYGEN)
    rw_slist(InputIterator first, InputIterator last,
             typename RWTEnableIf < !RWTIsIntegral<InputIterator>::value >::type** = 0)
#  if !defined(_MSC_VER) || (_MSC_VER > 1600)
    ;
#  else
        :
        head_(0), tail_(&head_), size_(0)
    {
        std::copy(first, last, std::inserter(*this, end()));
    }
#  endif
#else
    rw_slist(InputIterator first, InputIterator last);
#endif

    /**
     * Constructs an rw_slist containing \a n instances of \a value.
     */
    rw_slist(size_type n, const T& value);

    /**
     * The destructor releases the memory used by the links.
     */
    ~rw_slist();

    /**
     * Copy assignment. Constructs an rw_slist containing a copy of each
     * element in \a x.
     */
    rw_slist<T, A>&
    operator=(const rw_slist<T, A>& x);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * Move assignment. Self takes ownership of the data owned by \a x.
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    rw_slist<T, A>&
    operator=(rw_slist<T, A>&& x);
#endif // !RW_NO_RVALUE_REFERENCES

    /**
     * Copies each element in the range [\a first, \a last) into self,
     * replacing any existing elements.
     *
     * \c InputIterator is an input iterator type that points to elements
     * that are convertible to #value_type objects.
     *
     * \note
     * If \a first or \a last are iterators into this container, the
     * behavior is undefined.
     */
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last);

    /**
     * Exchanges the contents of self with \a x, retaining the ordering of
     * each. This method does not copy or destroy any of the elements
     * exchanged, but re-links the lists.
     */
    void swap(rw_slist<T, A>& x);

    /**
     * Returns an iterator referring to the first element in the container.
     *
     * If the container is empty, returns end().
     */
    iterator begin();

    /**
     * \copydoc begin()
     */
    const_iterator begin() const;

    /**
     * Returns an iterator referring to the first element in the container.
     *
     * If the container is empty, returns cend().
     */
    const_iterator cbegin() const;

    /**
     * Returns an iterator referring to the element after the last element
     * in the container.
     *
     * Dereferencing the iterator returned by this function results in
     * undefined behavior.
     */
    iterator end();

    /**
     * \copydoc end()
     */
    const_iterator end() const;

    /**
     * \copydoc end()
     */
    const_iterator cend() const;

    /**
     * Returns \c true if self is empty.
     */
    bool empty() const;

    /**
     * Returns the number of elements currently held in self.
     */
    size_type size() const;

    /**
     * Returns the maximum number of elements the container could hold.
     *
     * \note
     * This is a theoretical limit. The actual limit may be constrained by
     * system resources.
     */
    size_type max_size() const;

    /**
     * Returns a reference to the first element in self. If self is empty,
     * the behavior is undefined.
     */
    reference front();

    /**
     * Returns a const_reference to the first element in self. If self is
     * empty, the behavior is undefined.
     */
    const_reference front() const;

    /**
     * Returns a reference to the last element in self. If self is empty,
     * the behavior is undefined.
     */
    reference back();

    /**
     * Returns a const_reference to the last element in self. If self is
     * empty, the behavior is undefined.
     */
    const_reference back() const;

    /**
     * Inserts \a x as the first element of the list.
     */
    void push_front(const T& x);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * \copydoc push_front()
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    void push_front(T&& x);
#endif // !RW_NO_RVALUE_REFERENCES

    /**
     * Inserts \a x as the last element of the list.
     */
    void push_back(const T& x);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * \copydoc push_back()
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    void push_back(T&& x);
#endif // !RW_NO_RVALUE_REFERENCES

    /**
     * Inserts \a x just prior to the element referenced by \a position.
     * Returns an iterator referencing the newly inserted element.
     */
    iterator insert(iterator position, const T& x);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * \copydoc insert(iterator, const T&)
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    iterator insert(iterator position, T&& x);
#endif // !RW_NO_RVALUE_REFERENCES

    /**
     * Inserts a copy of each element in the range [\a first, \a last) into
     * self just prior to the element referenced by \a position. Returns an
     * iterator referencing the first newly inserted element.
     *
     * \c InputIterator is an input iterator type that points to elements
     * that are convertible to #value_type objects.
     *
     * \note
     * If \a first or \a last are iterators into this container, the
     * behavior is undefined.
     */
    template <typename InputIterator>
#if !defined(DOXYGEN)
    typename RWTEnableIf < !RWTIsIntegral<InputIterator>::value, iterator >::type
#else
    iterator
#endif
    insert(iterator position, InputIterator first, InputIterator last)
#if !defined(_MSC_VER) || (_MSC_VER > 1600)
    ;
#else
    {
        if (first == last) {
            return end();
        }

        iterator current(position);

        while (first != last) {
            current = insert(current, *first);
            ++current;
            ++first;
        }
        return position;
    }
#endif

    /**
     * Inserts \a n copies of \a value into self prior to the element
     * referenced by \a position. Returns an iterator to the first of the
     * newly inserted elements.
     */
    iterator insert(iterator position, size_type n, const T& value);

    /**
     * Erases the first element of self. If self is empty, the behavior is
     * undefined.
     */
    void pop_front();

    /**
     * Removes from self the element referenced by \a position. If
     * \a position does not reference an actual element contained in self,
     * the behavior is undefined. Returns an iterator referencing the
     * location just after the erased element.
     */
    iterator erase(const_iterator position);

    /**
     * Removes from self the elements referenced by the range beginning at
     * \a position and bounded by \a last. Returns an iterator referencing a
     * position just after the last erased element. If \a position does not
     * reference an element in self the behavior is undefined.
     */
    iterator erase(const_iterator position, const_iterator last);

    /**
     * Removes all elements from self.
     */
    void clear();

    /**
     * Inserts the entire contents of \a x into self, just before the
     * element referenced by \a position, leaving \a x empty. This method
     * does not copy or destroy any of the elements moved, but re-links the
     * list nodes from \a x into self.
     */
    void splice(iterator position, rw_slist<T, A>& x);

    /**
     * Inserts the element referenced by \a i into self, just before the
     * element referenced by \a position. The element referenced by \a i is
     * removed from \a x. This method does not copy or destroy the element
     * moved, but re-links the node from \a x into self. If \a i is not an
     * iterator into \a x, the behavior is undefined.
     */
    void splice(iterator position, rw_slist<T, A>& x, iterator i);

    /**
     * Inserts the elements in the range [\a first, \a last) just before the
     * element referenced by \a position. The elements in the range
     * [\a first, \a last) are removed from \a x. This method does not copy
     * or destroy any of the elements moved, but re-links the list nodes
     * from \a x into self. If \a i is not an iterator into \a x, the
     * behavior is undefined.
     */
    void splice(iterator position, rw_slist<T, A>& x, iterator first,
                iterator last);

    /**
     * Removes all of the elements in self that compare equal
     * (<tt>T::operator==()</tt> or equivalent) to \a value.
     */
    void remove(const T& value);

    /**
     * Removes from self all but the first element from each equal range. A
     * precondition is that any duplicate elements are adjacent.
     */
    void unique();

    /**
     * Assuming both \a x and self are sorted, moves every element from \a x
     * into self, leaving \a x empty, and self sorted. If either list is
     * unsorted, the move takes place, but the result may not be sorted.
     * This method does not copy or destroy the elements in \a x, but
     * re-links list nodes into self.
     */
    void merge(rw_slist<T, A>& x);

    /**
     * Reverses the order of the nodes containing the elements in self.
     */
    void reverse();

    /**
     * Sorts self according to <tt>T::operator<(T)</tt> or equivalent. Runs
     * in time proportional to \c N \c log(N), where \c N is the number of
     * elements. This method does not copy or destroy any of the elements
     * exchanged during the sort, but adjusts the order of the links in the
     * list.
     */
    void sort();

private:
    base_node_type head_;
    base_node_type* tail_;
    size_type size_;

    allocator_type node_allocator_;
};

/**
 * \relates rw_slist
 *
 * Returns true if \a lhs and \a rhs have the same number of elements and
 * each element of \a rhs tests equal (<tt>T::operator==()</tt> or
 * equivalent) to the corresponding element of \a lhs.
 */
template <typename T, typename A>
bool operator==(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs);

/**
 * \relates rw_slist
 *
 * Equivalent to <tt>!(\a lhs == \a rhs)</tt>.
 */
template <typename T, typename A>
bool operator!=(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs);

/**
 * \relates rw_slist
 *
 * Returns the result of calling:
 *
 * \code
 * lexicographical_compare(lhs.begin(), lhs.end(),
 *                         rhs.begin(), rhs.end());
 * \endcode
 */
template <typename T, typename A>
bool operator<(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs);

/**
 * \relates rw_slist
 *
 * Equivalent to <tt>(\a rhs < \a lhs)</tt>.
 */
template <typename T, typename A>
bool operator>(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs);

/**
 * \relates rw_slist
 *
 * Equivalent to <tt>!(\a rhs < \a lhs)</tt>.
 */
template <typename T, typename A>
bool operator<=(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs);

/**
 * \relates rw_slist
 *
 * Equivalent to <tt>!(\a lhs < \a rhs)</tt>.
 */
template <typename T, typename A>
bool operator>=(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs);


/**
 * \internal
 * \ingroup tools_stl_extension_based_collection_group
 *
 * \brief
 * An iterator to elements in an rw_slist<T, A>
 *
 * rw_slist_iterator_base provides an iterator into an rw_slist<T, A>
 * container. The iterator holds a reference to the node \e prior to the
 * node the iterator references, providing support for efficient operations
 * that modify the container \e before the iterator.
 */
template <typename T, typename N, typename D>
class rw_slist_iterator_base
    : public std::iterator<std::forward_iterator_tag, T, D, T*, T&>
{
public:
    /**
     * \internal
     *
     * A type representing the underlying node type.
     */
    typedef N node_type;

    /**
     * \internal
     *
     * A type representing the base class.
     */
    typedef std::iterator<std::forward_iterator_tag, T, D, T*, T&> base_type;

    /**
     * \internal
     *
     * A type representing the value_type of the iterator.
     */
    typedef typename base_type::value_type value_type;


    /**
     * \internal
     *
     * A type representing a signed integral value when calculating the
     * difference between two iterators.
     */
    typedef typename base_type::difference_type difference_type;

    /**
     * \internal
     *
     * A type representing the type returned by operator-> for the iterator.
     */
    typedef typename base_type::pointer pointer;

    /**
     * \internal
     *
     * A type representing the type returned by operator* for the iterator.
     */
    typedef typename base_type::reference reference;

    /**
     * \internal
     *
     * A type representing the iterator category for the iterator.
     */
    typedef typename base_type::iterator_category iterator_category;

    /**
     * \internal
     *
     * Constructs an invalid rw_slist_iterator_base. The behavior of any
     * operations are undefined until the iterator has been assigned to a
     * valid iterator instance.
     */
    rw_slist_iterator_base();


    /**
     * \internal
     *
     * Constructs an iterator pointing to the node \a prev, where \a prev is
     * the node prior to the node actually represented by this iterator.
     */
    rw_slist_iterator_base(node_type* prev);

    /**
     * \internal
     *
     * Copy constructor.
     */
    rw_slist_iterator_base(const rw_slist_iterator_base& other);


    /**
     * \internal
     *
     * Conversion constructor.
     */
    template <typename T1, typename N1, typename D1>
    rw_slist_iterator_base(const rw_slist_iterator_base<T1, N1, D1>& other);

    /**
     * \internal
     *
     * Assignment operator.
     */
    rw_slist_iterator_base&
    operator=(const rw_slist_iterator_base& other);


    /**
     * \internal
     *
     * Conversion assignment operator.
     */
    template <typename T1, typename N1, typename D1>
    rw_slist_iterator_base&
    operator=(const rw_slist_iterator_base<T1, N1, D1>& other);

    /**
     * \internal
     *
     * Returns a reference to the object pointed to by this iterator.
     */
    reference operator*() const;

    /**
     * \internal
     *
     * Returns a pointer to the object pointed to by this iterator.
     */
    pointer operator->() const;

    /**
     * \internal
     *
     * Increments the iterator to the next position, returning the new
     * iterator.
     */
    rw_slist_iterator_base& operator++();

    /**
     * \internal
     *
     * Increments the iterator to the next position, returning the previous
     * iterator.
     */
    rw_slist_iterator_base operator++(int);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \internal
     *
     * \deprecated
     * As of SourcePro 14, use comparison against rw_slist<T, A>::end()
     * instead.
     *
     * Returns \c true if the iterator is valid, \c false otherwise.
     */
    RW_DEPRECATE_FUNC("Use comparison against rw_slist::end() instead.")
    bool isValid() const;

    /**
     * \internal
     *
     * \copydoc isValid() const
     */
    RW_DEPRECATE_FUNC("Use comparison against rw_slist::end() instead.")
    operator bool() const;

    /**
     * \internal
     *
     * \deprecated
     * As of SourcePro 14, use assignment to an uninitialized
     * rw_slist<T, A>::iterator instead.
     *
     * Restores the iterator to an uninitialized state. Returns \c true if
     * the iterator was previously valid, \c false otherwise.
     */
    RW_DEPRECATE_FUNC("Use assignment to an uninitialized rw_slist::iterator instead.")
    bool reset();
#endif

private:
    node_type* prev_;

    template <typename T1, typename A1>
    friend class rw_slist;

    template <typename T1, typename N1, typename D1>
    friend class rw_slist_iterator_base;

    /**
     * \internal
     * \relates rw_slist_iterator_base
     *
     * Returns \c true if \a lhs and \a rhs refer to the same element in the
     * container, \c false otherwise.
     */
    template <typename T1, typename N1, typename D1, typename T2, typename N2, typename D2>
    friend bool operator==(const rw_slist_iterator_base<T1, N1, D1>& lhs,
                           const rw_slist_iterator_base<T2, N2, D2>& rhs);
};


/**
 * \internal
 * \relates rw_slist_iterator_base
 *
 * Returns \c false if \a lhs and \a rhs refer to the same element in the
 * container, \c true otherwise.
 */
template <typename T1, typename N1, typename D1, typename T2, typename N2, typename D2>
bool operator!=(const rw_slist_iterator_base<T1, N1, D1>& lhs,
                const rw_slist_iterator_base<T2, N2, D2>& rhs);



template <typename T>
inline
rw_slist_node_base<T>::rw_slist_node_base(rw_slist_node<T>* next)
    : next_(next)
{
}


template <typename T>
inline
rw_slist_node<T>::rw_slist_node(const T& val, rw_slist_node* next)
    : rw_slist_node_base<T>(next), value_(val)
{
}


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename T>
inline
rw_slist_node<T>::rw_slist_node(T&& val, rw_slist_node* next)
    : rw_slist_node_base<T>(next), value_(rw_move(val))
{
}
#endif


template <typename T, typename A>
inline
rw_slist<T, A>::rw_slist() : head_(0), tail_(&head_), size_(0) {}


template <typename T, typename A>
inline
rw_slist<T, A>::rw_slist(const rw_slist<T, A>& x)
    : head_(0), tail_(&head_), size_(0)
{
    std::copy(x.begin(), x.end(), std::inserter(*this, end()));
}


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename T, typename A>
inline
rw_slist<T, A>::rw_slist(rw_slist<T, A>&& x)
    : head_(0), tail_(&head_), size_(0)
{
    swap(x);
}
#endif // !RW_NO_RVALUE_REFERENCES

#if !defined(_MSC_VER) || (_MSC_VER > 1600)
template <typename T, typename A>
template <typename InputIterator>
inline
rw_slist<T, A>::rw_slist(InputIterator first, InputIterator last,
                         typename RWTEnableIf < !RWTIsIntegral<InputIterator>::value >::type**)
    : head_(0), tail_(&head_), size_(0)
{
    std::copy(first, last, std::inserter(*this, end()));
}
#endif


template <typename T, typename A>
inline
rw_slist<T, A>::~rw_slist()
{
    erase(begin(), end());
}


template <typename T, typename A>
inline
rw_slist<T, A>&
rw_slist<T, A>::operator=(const rw_slist<T, A>& x)
{
    if (this != &x) {
        rw_slist<T, A> other(x.begin(), x.end());
        swap(other);
    }
    return *this;
}


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename T, typename A>
inline
rw_slist<T, A>&
rw_slist<T, A>::operator=(rw_slist<T, A>&& x)
{
    if (this != &x) {
        swap(x);
    }
    return *this;
}
#endif // !RW_NO_RVALUE_REFERENCES


template <typename T, typename A>
template <typename InputIterator>
inline
void
rw_slist<T, A>::assign(InputIterator first, InputIterator last)
{
    rw_slist<T, A> other(first, last);
    swap(other);
}


template <typename T, typename A>
inline
void
rw_slist<T, A>::swap(rw_slist<T, A>& x)
{
    rw_swap(head_, x.head_);
    rw_swap(tail_, x.tail_);
    if (tail_ == &x.head_) {
        tail_ = &head_;
    }
    if (x.tail_ == &head_) {
        x.tail_ = &x.head_;
    }
    rw_swap(size_, x.size_);
    rw_swap(node_allocator_, x.node_allocator_);
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::iterator
rw_slist<T, A>::begin()
{
    return iterator(&head_);
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::const_iterator
rw_slist<T, A>::begin() const
{
    return const_iterator(&head_);
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::const_iterator
rw_slist<T, A>::cbegin() const
{
    return const_iterator(&head_);
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::iterator
rw_slist<T, A>::end()
{
    return iterator(tail_);
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::const_iterator
rw_slist<T, A>::end() const
{
    return const_iterator(tail_);
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::const_iterator
rw_slist<T, A>::cend() const
{
    return const_iterator(tail_);
}


template <typename T, typename A>
inline
bool
rw_slist<T, A>::empty() const
{
    return !size_;
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::size_type
rw_slist<T, A>::size() const
{
    return size_;
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::size_type
rw_slist<T, A>::max_size() const
{
    return (std::numeric_limits<typename rw_slist<T, A>::size_type>::max)();
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::reference
rw_slist<T, A>::front()
{
    RW_ASSERT(head_.next_);
    return head_.next_->value_;
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::const_reference
rw_slist<T, A>::front() const
{
    RW_ASSERT(head_.next_);
    return head_.next_->value_;
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::reference
rw_slist<T, A>::back()
{
    RW_ASSERT(tail_);
    return static_cast<node_type*>(tail_)->value_;
}


template <typename T, typename A>
inline
typename rw_slist<T, A>::const_reference
rw_slist<T, A>::back() const
{
    RW_ASSERT(tail_);
    return static_cast<const node_type*>(tail_)->value_;
}


template <typename T, typename A>
inline
void
rw_slist<T, A>::push_front(const T& x)
{
    insert(begin(), x);
}


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename T, typename A>
inline
void
rw_slist<T, A>::push_front(T&& x)
{
    insert(begin(), rw_move(x));
}
#endif // !RW_NO_RVALUE_REFERENCES


template <typename T, typename A>
inline
void
rw_slist<T, A>::push_back(const T& x)
{
    insert(end(), x);
}


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename T, typename A>
inline
void
rw_slist<T, A>::push_back(T&& x)
{
    insert(end(), rw_move(x));
}
#endif // !RW_NO_RVALUE_REFERENCES


template <typename T, typename A>
inline
rw_slist<T, A>::rw_slist(size_type n, const T& value)
    : head_(0), tail_(&head_), size_(0)
{
    insert(begin(), n, value);
}


template <typename T, typename A>
inline
void
rw_slist<T, A>::pop_front()
{
    erase(begin());
}


template <typename T, typename A>
inline
void
rw_slist<T, A>::clear()
{
    erase(begin(), end());
}


template <typename T, typename A>
inline
bool
operator==(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs)
{
    return lhs.size() == rhs.size() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}


template <typename T, typename A>
inline
bool
operator!=(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs)
{
    return !(lhs == rhs);
}


template <typename T, typename A>
inline
bool
operator<(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end());
}


template <typename T, typename A>
inline
bool
operator>(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs)
{
    return (rhs < lhs);
}


template <typename T, typename A>
inline
bool
operator<=(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs)
{
    return !(rhs < lhs);
}


template <typename T, typename A>
inline
bool
operator>=(const rw_slist<T, A>& lhs, const rw_slist<T, A>& rhs)
{
    return !(lhs < rhs);
}


template <typename T, typename N, typename D>
inline
rw_slist_iterator_base<T, N, D>::rw_slist_iterator_base() : prev_(0)
{
}


template <typename T, typename N, typename D>
inline
rw_slist_iterator_base<T, N, D>::rw_slist_iterator_base(node_type* prev)
    : prev_(prev)
{
}


template <typename T, typename N, typename D>
inline
rw_slist_iterator_base<T, N, D>::rw_slist_iterator_base(const rw_slist_iterator_base& other)
    : prev_(other.prev_)
{
}


template <typename T, typename N, typename D>
template <typename T1, typename N1, typename D1>
inline
rw_slist_iterator_base<T, N, D>::rw_slist_iterator_base(const rw_slist_iterator_base<T1, N1, D1>& other)
    : prev_(other.prev_)
{
}


template <typename T, typename N, typename D>
inline
rw_slist_iterator_base<T, N, D>&
rw_slist_iterator_base<T, N, D>::operator=(const rw_slist_iterator_base& other)
{
    if (this != &other) {
        prev_ = other.prev_;
    }
    return *this;
}


template <typename T, typename N, typename D>
template <typename T1, typename N1, typename D1>
inline
rw_slist_iterator_base<T, N, D>&
rw_slist_iterator_base<T, N, D>::operator=(const rw_slist_iterator_base<T1, N1, D1>& other)
{
    prev_ = other.prev_;
    return *this;
}


template <typename T, typename N, typename D>
inline
typename rw_slist_iterator_base<T, N, D>::reference
rw_slist_iterator_base<T, N, D>::operator*() const
{
    RW_ASSERT(prev_ != 0 && prev_->next_ != 0);
    return prev_->next_->value_;
}


template <typename T, typename N, typename D>
inline
typename rw_slist_iterator_base<T, N, D>::pointer
rw_slist_iterator_base<T, N, D>::operator->() const
{
    RW_ASSERT(prev_ != 0 && prev_->next_ != 0);
    return &prev_->next_->value_;
}


template <typename T, typename N, typename D>
inline
rw_slist_iterator_base<T, N, D>&
rw_slist_iterator_base<T, N, D>::operator++()
{
    RW_ASSERT(prev_ != 0 && prev_->next_ != 0);
    prev_ = prev_->next_;
    return *this;
}


template <typename T, typename N, typename D>
inline
rw_slist_iterator_base<T, N, D>
rw_slist_iterator_base<T, N, D>::operator++(int)
{
    RW_ASSERT(prev_ != 0 && prev_->next_ != 0);
    rw_slist_iterator_base prev = *this;
    prev_ = prev_->next_;
    return prev;
}


#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <typename T, typename N, typename D>
inline
bool
rw_slist_iterator_base<T, N, D>::isValid() const
{
    return (prev_ != 0 && prev_->next_ != 0);
}


template <typename T, typename N, typename D>
inline
rw_slist_iterator_base<T, N, D>::operator bool() const
{
    return isValid();
}


template <typename T, typename N, typename D>
inline
bool
rw_slist_iterator_base<T, N, D>::reset()
{
    const bool res = (prev_ != 0 && prev_->next_ != 0);
    prev_ = 0;
    return res;
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif


template <typename T1, typename N1, typename D1, typename T2, typename N2, typename D2>
bool
operator==(const rw_slist_iterator_base<T1, N1, D1>& lhs,
           const rw_slist_iterator_base<T2, N2, D2>& rhs)
{
    return lhs.prev_ == rhs.prev_;
}


template <typename T1, typename N1, typename D1, typename T2, typename N2, typename D2>
bool
operator!=(const rw_slist_iterator_base<T1, N1, D1>& lhs,
           const rw_slist_iterator_base<T2, N2, D2>& rhs)
{
    return !(lhs == rhs);
}


#ifdef RW_NO_IMPLICIT_INCLUSION
#  include <rw/stdex/slist.cc>
#endif // RW_NO_IMPLICIT_INCLUSION

#endif /* RW_TOOLS_STDEX_SLIST_H__ */
