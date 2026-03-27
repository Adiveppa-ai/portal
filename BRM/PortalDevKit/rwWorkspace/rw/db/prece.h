#ifndef __RWDB_PRECE_H__
#define __RWDB_PRECE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/prece.h#1 $
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
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/phrase.h>

//////////////////////////////////////////////////////////////////////////
//
//  RWPrecedence
//
//  This class sets up a method of determining the relative precedences
//  of the standard expression operators.  The table is referenced using
//  operator[] using an int.  However, it is intended that a RWDBPhraseKey
//  be used instead.
//
//  Components:
//    precedenceTable_ - an array of relative values used for comparing
//        precedence of two expression operators.  The number of elements
//        in this array is determined by the number of entries between the
//        'endExprOperatorGroup' and 'beginExprOperatorGroup' enum values
//        in the enum RWDBPhraseKey.  The precedence table is in the public
//        section of this class so that an instance of the class may be
//        statically initialized using the {} format. The default table
//        is initialized by RWDBExpr in expr.cpp
//
//////////////////////////////////////////////////////////////////////////
//
//  RWDBCPPPrecedence
//
//  This enum is used to initialize a default precedence table using the
//  precedence outlined in "The C++ Programming Language" Second Edition
//  by Bjarne Stroustrup pp 89-90.
//
//////////////////////////////////////////////////////////////////////////

class RWDB_SYMBOLIC RWDBPrecedence
{
public:
    enum RWDBCPPPrecedence {
        precedenceLowest,
        precedenceAssignment,
        precedenceOr,
        precedenceAnd,
        precedenceEqualGroup,
        precedenceLessGroup,
        precedencePlusGroup,
        precedenceMultiplyGroup,
        precedenceLikeInGroup,
        precedenceNot,
        precedenceUnaryGroup,
        precedenceNoOp,
        precedenceHighest
    };

    int precedenceTable_[RWDBPhraseBook::endExprOperatorGroup -
                         RWDBPhraseBook::beginExprOperatorGroup];
    int operator[](int) const;
};

#endif
