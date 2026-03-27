#ifndef rw_functor_RWPlaceholder_h_
#define rw_functor_RWPlaceholder_h_
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTPlaceholder.h#1 $
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

#include <rw/functor/pkgdefs.h>

template <size_t N>
struct RWTPlaceholder {};

extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<1> rw1;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<2> rw2;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<3> rw3;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<4> rw4;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<5> rw5;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<6> rw6;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<7> rw7;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<8> rw8;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<9> rw9;
extern RW_FUNCTOR_GLOBAL const RWTPlaceholder<10> rw10;

template <typename T>
struct RWTIsPlaceholder {
    enum {
        value = 0
    };
};

template <size_t N>
struct RWTIsPlaceholder<RWTPlaceholder<N> > {
    enum {
        value = N
    };
};

template <size_t N>
struct RWTIsPlaceholder<const RWTPlaceholder<N> > {
    enum {
        value = N
    };
};

template <size_t N>
struct RWTIsPlaceholder<volatile RWTPlaceholder<N> > {
    enum {
        value = N
    };
};

template <size_t N>
struct RWTIsPlaceholder<const volatile RWTPlaceholder<N> > {
    enum {
        value = N
    };
};

#endif
