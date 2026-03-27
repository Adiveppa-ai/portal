#ifndef __RWDB_PHRASE_H__
#define __RWDB_PHRASE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/phrase.h#1 $
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
#include <rw/db/value.h>
#include <rw/cstring.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
//
//  RWDBPhraseKey
//
//  This enum is used to define all of the keywords and phrases that might need
//  a local translation for a given database.
//  The values are broken up into groups. Each group is bracketed by
//  'beginXXXX' and 'endXXXX' to provide a simple method of determining the
//  number of members in a group.
//
//////////////////////////////////////////////////////////////////////////
//
//  RWDBPhraseBook
//
//  This class serves as a lookup table for keywords and phrases used by
//  specific databases.  It is referenced using the operator[] with a value from
//  the enum RWDBPhraseKey.  The RWDBExpr family of classes makes extensive use
//  of this class to construct SQL from expressions.
//
//  Components:
//    localPhrases_ - an array of const char* ordered by the enum RWDBPhraseKey.
//                    The strings represent the keywords and phrases used by the
//                    dialect of SQL relevant to some specific database.
//                    This array is in the public interface to allow static
//                    initialization using the {} format.
//
//  Inline Functions:
//    operator[] - the function simply indexes the variable 'localPhrases' and
//                 returns a pointer to the appropriate string.
//    placeHolder(RWCString&) - Uses the placeHolder phrase to construct a database
//                 specific placeholder.
//
//////////////////////////////////////////////////////////////////////////


/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * A lookup table containing keywords and phrases used by specific
 * databases.
 *
 * RWDBPhraseBook serves as a lookup table for keywords and phrases used by
 * specific databases. An RWDBPhraseBook is associated with each
 * RWDBDatabase instance. Internally, the DB Interface Module makes
 * extensive use of this class to construct SQL from expressions.
 *
 * Many classes of the DB Interface Module, like RWDBForeignKey for example,
 * require an RWDBPhraseBook for their asString() method, so that they can
 * generate SQL acceptable to a specific database. To call these asString()
 * methods directly, applications can obtain an RWDBPhraseBook from an
 * RWDBDatabase.
 *
 * \synopsis
 * #include <rw/db/phrase.h>
 *
 * const RWDBPhraseBook& phraseBook = myDbase.phraseBook();
 * \endsynopsis
 */
class RWDB_SYMBOLIC RWDBPhraseBook
{
public:
    enum RWDBPhraseKey {
        // IMPORTANT! Any changes to this group must be reflected in
        // the precedence table.  See prece.h for more information
        beginExprOperatorGroup,
        operatorNoOp,
        operatorPlus,
        operatorUnaryPlus,
        operatorMinus,
        operatorUnaryMinus,
        operatorMultiply,
        operatorDivide,
        operatorModulo,
        operatorEqual,
        operatorNotEqual,
        operatorLess,
        operatorGreater,
        operatorLessOrEqual,
        operatorGreaterOrEqual,
        operatorAnd,
        operatorOr,
        operatorNot,
        operatorBetween,
        operatorIn,
        operatorLike,
        operatorMatchUnique,
        operatorAssignment,
        operatorIsNull,
        operatorUnion,
        operatorUnionAll,
        operatorIntersection,
        operatorDifference,
        operatorLeftOuterJoin,
        operatorRightOuterJoin,
        operatorFullOuterJoin,
        operatorInnerJoin,
        operatorLeftOuterJoinInWhereClause,
        operatorRightOuterJoinInWhereClause,
        operatorFullOuterJoinInWhereClause,
        operatorNaturalLeftOuterJoin,
        operatorNaturalRightOuterJoin,
        operatorNaturalFullOuterJoin,
        operatorExists,
        operatorList,
        operatorSelect,
        operatorSpare1,
        endExprOperatorGroup,

        beginKeywordGroup,
        keywordInsert,
        keywordUpdate,
        keywordDelete,
        keywordSelect,
        keywordDistinct,
        keywordInto,
        keywordFrom,
        keywordWhere,
        keywordOrderBy,
        keywordGroupBy,
        keywordHaving,
        keywordValue,
        keywordSet,
        keywordBeginTran,
        keywordCommitTran,
        keywordRollbackTran,
        keywordCreate,
        keywordDrop,
        keywordTable,
        keywordView,
        keywordIndex,
        keywordProcedure,
        keywordFunction,
        keywordAs,
        keywordUnique,
        keywordClustered,
        keywordOn,
        keywordNullAllowed,
        keywordNullNotAllowed,
        keywordAscending,
        keywordDescending,
        keywordPrimaryKey,
        keywordUsing,
        keywordDefault,
        keywordIdentity,
        keywordConstraint,
        keywordCheck,
        keywordSpare1,
        keywordSpare2,
        keywordSpare3,
        endKeywordGroup,

        beginPhraseGroup,
        phraseSelectAll,
        phraseTableWithTag,
        phraseNameColumn,
        phraseGrant,
        phraseRevoke,
        phraseOrderByOperand,
        phraseOnDeleteRestrict,
        phraseOnDeleteCascade,
        phraseOnDeleteNullify,
        phraseOnDeleteDefaultify,
        phraseOnUpdateRestrict,
        phraseOnUpdateCascade,
        phraseOnUpdateNullify,
        phraseOnUpdateDefaultify,
        phraseForUpdate,
        phraseStartWith,
        phraseMaxValue,
        phraseMinValue,
        phraseIncrementBy,
        phraseCycle,
        phraseSpare1,
        endPhraseGroup,

        beginAlterTableGroup,
        alterTableAdd,
        alterTableDrop,
        alterTableSpare1,
        alterTableSpare2,
        alterTableSpare3,
        alterTableSpare4,
        alterTableSpare5,
        endAlterTableGroup,

        beginFunctionGroup,
        functionAvg,
        functionCast2,
        functionCast3,
        functionCast4,
        functionCharLength,
        functionCount,
        functionCountAll,
        functionCountDistinct,
        functionCurrentUser,
        functionLower,
        functionMax,
        functionMin,
        functionPosition,
        functionSessionUser,
        functionSubString1,
        functionSubString2,
        functionSum,
        functionSystemDateTime,
        functionSystemUser,
        functionTrimBoth,
        functionTrimLeading,
        functionTrimTrailing,
        functionUpper,
        functionSpare1,
        functionSpare2,
        functionSpare3,
        functionSpare4,
        functionSpare5,
        functionSpare6,
        functionSpare7,
        functionSpare8,
        functionSpare9,
        functionSpare10,
        endFunctionGroup,

        beginLiteralGroup,
        literalChar,         // sprintf() style with int argument
        literalUchar,        // sprintf() style with int argument
        literalShort,        // sprintf() style with long argument
        literalUshort,       // sprintf() style with long argument
        literalInt,          // sprintf() style with long argument
        literalUint,         // sprintf() style with long argument
        literalLong,         // sprintf() style with long argument
        literalUlong,        // sprintf() style with long argument
        literalFloat,        // sprintf() style with double argument
        literalDouble,       // sprintf() style with double argument
        literalLongDouble,   // sprintf() style with long double argument
        literalDecimal,
        literalDate,         // sprintf() style with string argument
        literalDateTime,     // sprintf() style with string argument
        literalDuration,
        literalBlob,         // sprintf() style with string argument
        literalWildCard,     // "match anything" char, usually "%"
        literalLongLong,     // sprintf() style with long long argument
        literalULongLong,    // sprintf() style with unsigned long long argument
        literalTimeTuple,
        literalTimeTupleOffset,
        literalSpare1,
        literalSpare2,
        literalSpare3,
        endLiteralGroup,

        beginTypeNameGroup,
        typeBit,
        typeByte,
        typeTinyInt,
        typeShortInt,
        typeLongInt,
        typeShortFloat,
        typeLongFloat,
        typeCharFixed,
        typeCharVariable,
        typeBinaryFixed,
        typeBinaryVariable,
        typeDate,
        typeTime,
        typeDuration,
        typeShortDateTime,
        typeLongDateTime,
        typeShortMoney,
        typeLongMoney,
        typeDecimal,
        typeNumeric,
        typeText,
        typeBlob,
        typeNCharFixed,
        typeNCharVariable,
        typeUniCharFixed,
        typeUniCharVariable,
        typeLongLong,
        typeSpare1,
        typeSpare2,
        typeTimeTuple,
        typeTimeTupleOffset,
        typeSpare3,
        endTypeNameGroup,

        beginMiscGroup,
        singleSpace,
        openStringQuote,     // used in constructing literals
        closeStringQuote,    // used in constructing literals
        openNStringQuote,    // used in constructing literals in National Character Sets
        closeNStringQuote,   // used in constructing literals in National Character Sets
        nationalQuotePrefix, // used in constructing literals in National Character Sets
        stringEscape,        // used in constructing literals
        openCharacterQuote,  // used in constructing literals
        closeCharacterQuote, // used in constructing literals
        characterEscape,     // used in constructing literals
        listBeginner,        // usually (
        listDelimiter,       // usually ,
        listEnder,           // usually )
        nameQualifier,       // usually .
        leftSubScript,       // ( or [
        rightSubScript,      // ) or ]
        null,                // word to indicate null values
        zeroLengthBlob,      // word to indicate zero length blob values
        sqlDelimiter,        // batch delimiter in files
        dateFormat,          // follows RWLocale formatting
        datetimeFormat,      // follows RWLocale formatting + %L for milliseconds
        subSelectBegin,      // opening delimiter for subselects
        subSelectEnd,        // closing delimiter for subselects
        outerJoinListBeginner, // Beginning
        outerJoinListEnder,
        joinListDelimiter,
        joinPrecedenceBegin,
        joinPrecedenceEnd,
        placeHolderCharacter,
        placeHolderRegEx,
        miscSpare1,
        timetupleFormat,       // follows RWLocale formatting
        timetupleoffsetFormat, // follows RWLocale formatting
        miscSpare2,
        miscSpare3,
        endMiscGroup,

        endOfPhraseList
    };

    const char* localPhrases_[endOfPhraseList + 1];
    inline const char* operator[](RWDBPhraseKey key) const
    {
        return localPhrases_[key];
    }
    RWCString placeHolder(unsigned long name) const;

};

#endif
