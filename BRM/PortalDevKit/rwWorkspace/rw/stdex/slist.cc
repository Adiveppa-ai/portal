/**********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stdex/slist.cc#1 $
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

#include <rw/stdex/destroy.h>
#include <memory>

template <typename T, typename A>
typename rw_slist<T, A>::node_type*
rw_advance_node(typename rw_slist<T, A>::node_type* node,
                typename rw_slist<T, A>::size_type n)
{
    for (size_t i = 0; i < n && node != 0; ++i) {
        node = node->next_;
    }
    return node;
}


template <typename T, typename A>
std::pair<typename rw_slist<T, A>::node_type*, typename rw_slist<T, A>::node_type*>
rw_merge_nodes(typename rw_slist<T, A>::node_type* first1,
               typename rw_slist<T, A>::node_type* bound1,
               typename rw_slist<T, A>::node_type* first2,
               typename rw_slist<T, A>::node_type* bound2)
{
    typedef typename rw_slist<T, A>::node_type node_type;

    RW_ASSERT(first1 && first1 != bound1);
    RW_ASSERT(first2 && first2 != bound2);

    node_type* primary = 0;
    const node_type* primary_end = 0;
    node_type* secondary = 0;
    const node_type* secondary_end = 0;

    // choose starting chain based on which has the smallest value.
    if (first1->value_ < first2->value_) {
        primary = first1;
        primary_end = bound1;
        secondary = first2;
        secondary_end = bound2;
    }
    else {
        primary = first2;
        primary_end = bound2;
        secondary = first1;
        secondary_end = bound1;
    }

    node_type* first = primary;
    node_type* last = primary;
    primary = primary->next_;

    do {
        // Iterate over primary until secondary has a value that's less than
        // than the current value.
        while (primary != primary_end &&
                (secondary == secondary_end ||
                 !(secondary->value_ < primary->value_))) {
            last = primary;
            primary = primary->next_;
        }
        // Swap secondary with the rest of primary.
        if (secondary != secondary_end) {
            last->next_ = secondary;
            rw_swap(primary, secondary);
            rw_swap(primary_end, secondary_end);
        }
    }
    while (primary != primary_end);

    // Reset the last node's next pointer to the next element of the second
    // range.
    last->next_ = bound2;
    return std::make_pair(first, last);
}


template <typename T, typename A>
typename rw_slist<T, A>::iterator
rw_slist<T, A>::insert(iterator position, const T& x)
{
    RW_ASSERT(position.prev_);

    node_type* nn = (node_type*) RW_TLS_ALLOCATE(node_allocator_, 1, node_type);
    RW_ASSERT(nn != 0);

    // always use placement new
    new(nn) node_type(x, position.prev_->next_);

    if (position.prev_ == tail_) {
        tail_ = nn;
    }
    position.prev_->next_ = nn;

    ++size_;  // update count of entries

    return position;
}


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename T, typename A>
typename rw_slist<T, A>::iterator
rw_slist<T, A>::insert(iterator position, T&& x)
{
    RW_ASSERT(position.prev_);

    node_type* nn = (node_type*) RW_TLS_ALLOCATE(node_allocator_, 1, node_type);
    RW_ASSERT(nn != 0);

    // always use placement new
    new(nn) node_type(rw_move(x), position.prev_->next_);

    if (position.prev_ == tail_) {
        tail_ = nn;
    }
    position.prev_->next_ = nn;

    ++size_;  // update count of entries

    return position;
}
#endif // !RW_NO_RVALUE_REFERENCES


#if !defined(_MSC_VER) || (_MSC_VER > 1600)
template <typename T, typename A>
template <typename InputIterator>
typename RWTEnableIf < !RWTIsIntegral<InputIterator>::value, typename rw_slist<T, A>::iterator >::type
rw_slist<T, A>::insert(iterator position, InputIterator first,
                       InputIterator last)
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


template <typename T, typename A>
typename rw_slist<T, A>::iterator
rw_slist<T, A>::insert(iterator position, size_type n,
                       const value_type& value)
{
    if (n < 1) {
        return end();
    }

    const iterator ret(position);
    for (size_t i = 0; i < n; ++i) {
        position = insert(position, value);
    }
    return ret;
}


template <typename T, typename A>
typename rw_slist<T, A>::iterator
rw_slist<T, A>::erase(const_iterator position)
{
    RW_ASSERT(position.prev_);

    base_node_type* prev = const_cast<base_node_type*>(position.prev_);
    node_type* node = prev->next_;

    RW_ASSERT(node);

    if (node == tail_) {
        tail_ = prev;
    }
    prev->next_ = node->next_;

    rw_destroy(&(node->value_));
    RW_TLS_DEALLOCATE(node_allocator_, node, 1);

    --size_;

    return iterator(prev);
}


template <typename T, typename A>
typename rw_slist<T, A>::iterator
rw_slist<T, A>::erase(const_iterator position, const_iterator last)
{
    RW_ASSERT(position.prev_);
    RW_ASSERT(last.prev_);

    base_node_type* beg = const_cast<base_node_type*>(position.prev_);
    const node_type* const end = const_cast<node_type*>(last.prev_->next_);

    while (beg->next_ != end) {
        node_type* node = beg->next_;
        if (node == tail_) {
            tail_ = beg;
        }
        beg->next_ = node->next_;

        rw_destroy(&(node->value_));
        RW_TLS_DEALLOCATE(node_allocator_, node, 1);
        --size_;
    }
    return iterator(beg);
}


template <typename T, typename A>
void
rw_slist<T, A>::splice(iterator position, rw_slist<T, A>& x)
{
    node_type* const beg = x.head_.next_;
    base_node_type* const tail = x.tail_;

    if (!beg) {
        return;
    }

    const size_type count = x.size_;

    // extract nodes from x
    x.head_.next_ = 0;
    x.tail_ = &x.head_;
    x.size_ = 0;

    // insert nodes into self
    base_node_type* const prev = position.prev_;
    if (tail_ == prev) {
        tail_ = tail;
    }
    tail->next_ = prev->next_;
    prev->next_ = beg;
    size_ += count;
}


template <typename T, typename A>
void
rw_slist<T, A>::splice(iterator position, rw_slist<T, A>& x, iterator i)
{
    RW_ASSERT(i.prev_);

    node_type* const node = i.prev_->next_;

    RW_ASSERT(node);

    // extract nodes from x
    i.prev_->next_ = node->next_;
    if (x.tail_ == node) {
        x.tail_ = i.prev_;
    }
    x.size_ -= 1;

    // Add nodes to this container
    base_node_type* const prev = position.prev_;
    if (tail_ == prev) {
        tail_ = node;
    }
    node->next_ = prev->next_;
    prev->next_ = node;
    size_ += 1;
}


template <typename T, typename A>
void
rw_slist<T, A>::splice(iterator position, rw_slist<T, A>& x, iterator first,
                       iterator last)
{
    if (first == last) {
        return;
    }

    RW_ASSERT(first.prev_);
    RW_ASSERT(last.prev_);

    const difference_type count = rw_distance(first, last);

    node_type* const beg = first.prev_->next_;
    base_node_type* const end = last.prev_;

    // extract nodes from x
    first.prev_->next_ = end->next_;
    x.size_ -= count;
    if (x.tail_ == end) {
        x.tail_ = first.prev_;
    }

    // Add nodes to this container
    base_node_type* const prev = position.prev_;
    if (tail_ == prev) {
        tail_ = end;
    }
    end->next_ = prev->next_;
    prev->next_ = beg;
    size_ += count;
}


template <typename T, typename A>
void
rw_slist<T, A>::remove(const value_type& value)
{
    iterator hunt = begin();
    while (hunt != end()) {
        if (*hunt == value) {
            hunt = erase(hunt);
        }
        else {
            ++hunt;
        }
    }
}


template <typename T, typename A>
void
rw_slist<T, A>::unique()
{
    if (tail_ == &head_) {
        return;
    }

    iterator hunt = begin();

    // use T* to avoid assuming T::operator=()
    T* first = &*(hunt++);

    // which may not exist (e.g. if T is pair<const ...>)
    while (hunt != end()) {
        if (*first == *hunt) {
            hunt = erase(hunt);
        }
        else {
            first = &*(hunt++);
        }
    }
}


template <typename T, typename A>
void
rw_slist<T, A>::merge(rw_slist<T, A>& x)
{
    RW_ASSERT(x.tail_);
    RW_ASSERT(tail_);

    node_type* const beg1 = x.head_.next_;
    node_type* const end1 = x.tail_->next_;

    node_type* const beg2 = head_.next_;
    node_type* const end2 = tail_->next_;

    if (!beg2) {
        swap(x);
        return;
    }
    else if (!beg1) {
        return;
    }

    const size_type count = x.size_;

    // extract nodes from x
    x.head_.next_ = 0;
    x.tail_ = &x.head_;
    x.size_ = 0;

    // merge nodes with self
    const std::pair<node_type*, node_type*> ret =
        rw_merge_nodes<T, A>(beg1, end1, beg2, end2);
    head_.next_ = ret.first;
    tail_ = ret.second;
    size_ += count;
}


template <typename T, typename A>
void
rw_slist<T, A>::reverse()
{
    if (tail_ == &head_) {
        return;
    }

    node_type* next = head_.next_;
    node_type* prev = 0;
    head_.next_ = static_cast<node_type*>(tail_);
    tail_ = next;
    while (next != 0) {
        node_type* cur = next;
        next = cur->next_;
        cur->next_ = prev;
        prev = cur;
    }
}


template <typename T, typename A>
void
rw_slist<T, A>::sort()
{
    if (size_ < 2) {
        return;
    }

    for (size_t i = 1; i < size_; i *= 2) {
        base_node_type* head = &head_;
        base_node_type* last = tail_;
        while (head != 0) {
            node_type* const node = head->next_;
            node_type* const p1 = node;
            node_type* const p2 = rw_advance_node<T, A>(p1, i);
            node_type* const p3 = rw_advance_node<T, A>(p2, i);
            if (p2 != p3) {
                const std::pair<node_type*, node_type*> ret =
                    rw_merge_nodes<T, A>(p1, p2, p2, p3);
                head->next_ = ret.first;
                last = ret.second;
                head = ret.second;
            }
            else {
                head = p3;
            }
        }
        tail_ = last;
    }
}
