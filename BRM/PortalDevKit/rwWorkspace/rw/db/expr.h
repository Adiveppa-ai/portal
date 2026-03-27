#ifndef __RWDB_EXPR_H__
#define __RWDB_EXPR_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/expr.h#1 $
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

#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/phrase.h>
#include <rw/db/value.h>
#include <rw/colclass.h>
#include <rw/tools/bustring.h>

/**
 * \ingroup db_expression_group
 * \class RWDBExpr
 *
 * \brief
 * A C++ representation of expressions used in constructing SQL statements.
 *
 * RWDBExpr represents expressions used in constructing SQL statements,
 * allowing the SQL to be constructed using C++ syntax. Because there are
 * several types of expressions, this class is simply an interface to a
 * family of implementations that can represent numeric and string
 * constants, columns from tables, or other expressions. By its nature, an
 * RWDBExpr can actually represent a complete complex expression in the form
 * of a parse tree.
 *
 * Because instances of this class are typically created anonymously, it has
 * constructors taking the various operands used in expressions. These
 * include the C++ primitive types, as well as the structured types used by
 * the DB Interface Module, such as RWCString and RWDBColumn.
 *
 * RWDBExpr is designed around the Interface/Implementation paradigm. An
 * RWDBExpr instance is an interface to a reference-counted implementation;
 * copy constructors and assignment operators produce additional references
 * to a shared implementation.
 *
 * This class has a number of related global functions that may be applied
 * to RWDBExpr instances to build RWDBExpr objects representing SQL
 * functions. The SQL syntax for these functions typically varies among the
 * various vendors' implementations. The DB Interface Module hides the
 * variations by providing the database-specific syntax at runtime.
 *
 * The DB Interface Module also provides an extensible mechanism for
 * applications to define their own functional notation. See
 * RWDBExprFormDefinition.
 *
 * \synopsis
 * #include <rw/db/expr.h>
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBAssignment is a special kind of expression used to encapsulate the
 * SQL phrase:
 *
 * \c SET <em>column = expression</em>.
 *
 * RWDBAssignment instances are produced by the method RWDBColumn::assign().
 *
 * RWDBBoundExpr is used to bind application variables to an SQL statement.
 *
 * RWDBCollectableExpr derives from RWDBExpr and RWCollectable.
 *
 * RWDBPhraseBook is used to store database-specific SQL syntax.
 *
 * RWDBCriterion is a special kind of expression used to encapsulate an SQL
 * \c WHERE clause. It is formed from RWDBExpr instances connected with
 * logical operators.
 *
 * RWDBExprFormDefinition provides an extensible mechanism that allows
 * application programmers to define their own functional SQL notation.
 *
 * RWDBJoinExpr is used to construct ANSI SQL join syntax.
 * \endparblock
 *
 * \example
 * In this example, an RWDBExpr is created anonymously to be used as part of
 * an SQL \c SELECT statement. The intent is to create a selector that adds
 * the value of the program variable \c x to each value selected.
 *
 * \code
 * int x = somevalue;
 * RWDBTable myTable = myDbase.table("myTable");
 * RWDBSelector select = myDbase.selector();
 * select << myTable["integerColumn"] + x;
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBExpr
{
public:

    /**
     * This \c enum holds values to format asString() output.
     */
    enum AsStringControlFlag {

        /**
         * Normal formatting
         */
        normal = 0,

        /**
         * Suppress usage of table tags to qualify table columns
         */
        suppressTagsOnColumns = 1,

        /**
         * Prevent usage of placeholders
         */
        noPlaceHolder = 2,

        /**
         * Placeholder usage is not recommended
         */
        placeHolderNotRecommended = 4
    };


    /**
     * The default constructor builds an empty RWDBExpr, that is, one whose
     * asString() method returns an SQL \c NULL keyword, as specified in its
     * parameter \c phraseBook. Since an empty expression cannot hold a
     * value, RWDBExpr() cannot be used as \c NULL value.
     */
    RWDBExpr();

    /**
     * Copy constructor. Self shares an implementation with \a expr.
     */
    RWDBExpr(const RWDBExpr& expr);

    /**
     * Creates an RWDBExpr from the given \a value.
     */
    RWDBExpr(char value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(unsigned char value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(short value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(unsigned short value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(int value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(unsigned int value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(long int value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(unsigned long int value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(long long value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(unsigned long long value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(float value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(double value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(long double value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const char* value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const wchar_t* value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWCString& value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWDecimalPortable& value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWDateTime& value);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 12.5, use
     * \ref RWDBExpr::RWDBExpr(const RWDateTime&) "RWDBExpr(const RWDateTime&)"
     * instead.
     *
     * \copydoc RWDBExpr(char)
     */
    RW_DEPRECATE_FUNC("Use RWDBExpr(const RWDateTime&) instead")
    RWDBExpr(const RWDBDateTime& value);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWDBDuration& value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWDate& value);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWTime& value);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWDBBlob& value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWBasicUString& value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWDBMBString& value);

    /**
     * \copydoc RWDBExpr(char)
     */
    RWDBExpr(const RWWString& value);

    /**
     * Creates an RWDBExpr from an RWDBValue. When the asString() function
     * is applied to this RWDBExpr, it passes its \c phraseBook parameter on
     * to the RWDBValue for interpretation. Passing \c false for the
     * \a usePhraseBook parameter suppresses this behavior. The effect of
     * suppressing the use of the \c phraseBook is to prevent strings from
     * being quoted and RWDateTime instances from using the database's
     * designated format.
     */
    RWDBExpr(const RWDBValue& value, bool usePhraseBook = true);

    /**
     * Creates an RWDBExpr from the \a column reference.
     */
    RWDBExpr(const RWDBColumn& column);

    /**
     * Creates an RWDBExpr from an RWDBSelector or RWDBCompoundSelector.
     * This constructor supports the SQL subquery construct.
     */
    RWDBExpr(const RWDBSelectorBase& subSelect);

    /**
     * Creates an RWDBExpr according to the semantics of \a manip. In
     * particular, an expression representing a literal \c NULL may be
     * constructed from \ref RWDBValue::rwdbNull "rwdbNull".
     */
    RWDBExpr(RWDBValueManip manip);

    /**
     * Creates an RWDBExpr that represents a delimited list of the items in
     * \a collection. The parameter \a collection must be a collection of
     * RWDBCollectableExpr instances. \a collection must remain in scope for
     * the entire period that the RWDBExpr can be referenced, since the
     * expression is not expanded into a string until the asString() method
     * is called, which can happen long after you assign the collectable to
     * the expression.
     */
    RWDBExpr(const RWCollection& collection);

    virtual ~RWDBExpr();

    /**
     * Assignment operator. Self shares an implementation with \a expr.
     */
    RWDBExpr& operator=(const RWDBExpr& expr);

    /**
     * \internal
     *
     * Returns an enum representing the operator associated with this
     * expression. Returns \c RWDBPhraseBook::operatorNoOp if there is no
     * operator.
     */
    RWDBPhraseBook::RWDBPhraseKey getOperator(void) const;

    RWDBValue::ValueType type() const;

    /**
     * Returns an RWCString representing self as a string based on the
     * format found in \a phraseBook. Normally, references to columns in
     * self are represented in the string with table tags attached. Setting
     * the value of \a control with RWDBExpr::suppressTagsOnColumns prevents
     * the tags from being included in the string.
     */
    RWCString asString(const RWDBPhraseBook& phraseBook,
                       AsStringControlFlag control = normal) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e expression \c BETWEEN \a expression1 \c AND \a expression2
     *
     * where \e expression refers to self. RWDBCriterion encapsulates SQL
     * \c WHERE clauses.
     */
    RWDBCriterion between(const RWDBExpr& expression1, const RWDBExpr& expression2) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * phrase:
     *
     * \e expression \c IN \a expression1
     *
     * where \e expression refers to self. An RWDBCriterion is an
     * encapsulation of an SQL \c WHERE clause. For example, to produce the
     * SQL clause (shown using Oracle placeholder syntax):
     *
     * \code
     * (col1 + 'bye') in (:ph0, :ph1)
     * \endcode
     *
     * we could write:
     *
     * \code
     * RWDBExpr anExpression(col1 + "bye");
     * RWOrdered aCollection;
     *
     * RWCString hello("hello");
     * RWCString goodbye("goodbye");
     * RWDBBoundExpr expr1(&hello);
     * RWDBBoundExpr expr2(&goodbye);
     * RWDBCollectableExpr colExpr1(expr1);
     * RWDBCollectableExpr colExpr2(expr2);
     * aCollection.insert(&colExpr1);
     * aCollection.insert(&colExpr2);
     * anExpression.in(aCollection);
     * \endcode
     *
     * To produce the SQL clause:
     *
     * \code
     * (col1 + 'bye') in ('hello','goodbye')
     * \endcode
     *
     * we could write:
     *
     * \code
     * RWDBExpr anExpression(col1 + "bye");
     * RWOrdered aCollection;
     *
     * RWDBExpr expr1("hello");
     * RWDBExpr expr2("goodbye");
     *
     * aCollection.insert(&expr1);
     * aCollection.insert(&expr2);
     * anExpression.in(aCollection);
     * \endcode
     *
     * Alternatively, we could write:
     *
     * \code
     * RWDBExpr anExpression(col1 + "bye");
     * anExpression.in(RWDBExpr("('hello', 'good-bye')", false));
     * \endcode
     *
     * \note
     * The parameter \c false in the constructor for the RWDBExpr above is
     * required in order to suppress quotation marks in the resultant SQL
     * string.
     */
    RWDBCriterion in(const RWDBExpr& expression1) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e expression <tt>IS NULL</tt>
     *
     * where \a expression refers to self. An RWDBCriterion is an
     * encapsulation of an SQL \c WHERE clause.
     */
    RWDBCriterion isNull(void) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the
     * <tt>LEFT OUTER JOIN</tt> SQL phrase. An RWDBCriterion is an
     * encapsulation of an SQL \c WHERE clause.
     */
    RWDBCriterion leftOuterJoin(const RWDBExpr& expression) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e expression \c LIKE \a expression1
     *
     * where \e expression refers to self. For example, to produce the SQL
     * clause:
     *
     * \code
     * col1 LIKE `%object%'
     * \endcode
     * we would write:
     *
     * \code
     * table["col1"].like("%object%");
     * \endcode
     */
    RWDBCriterion like(const RWDBExpr& expression1) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the
     * <tt>RIGHT OUTER JOIN</tt> SQL phrase. An RWDBCriterion is an
     * encapsulation of an SQL \c WHERE clause.
     */
    RWDBCriterion rightOuterJoin(const RWDBExpr& expression) const;

    RWDBCriterion fullOuterJoin(const RWDBExpr&) const;

    RWDBExpr(const RWCString&, const RWDBExpr*, const RWDBExpr*,
             const RWDBExpr* = 0, const RWDBExpr* = 0);
    RWDBExpr(const RWDBExpr*, const RWDBExpr*,
             RWDBPhraseBook::RWDBPhraseKey,
             RWDBPhraseBook::RWDBPhraseKey pk = RWDBPhraseBook::singleSpace,
             RWDBPhraseBook::RWDBPhraseKey pk2 = RWDBPhraseBook::singleSpace);

    RWDBExpr(RWDBPhraseBook::RWDBPhraseKey, const RWDBExpr* = 0,
             const RWDBExpr* = 0, const RWDBExpr* = 0, const RWDBExpr* = 0);
    RWDBExpr(RWDBPhraseBook::RWDBPhraseKey, const RWDBExpr&);
    RWDBExpr(const RWDBSchema&);

    /**
     * Returns \c true if self is not an empty (null) expression.
     */
    bool isValid(void) const;

    bool isEquivalent(const RWDBExpr&) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e expression <tt>MATCH UNIQUE</tt> \a expression1
     *
     * where \e expression refers to self.
     */
    RWDBCriterion matchUnique(const RWDBExpr& expression1) const;

    /**
     * Creates an RWDBExpr that represents a table.
     */
    RWDBExpr(const RWDBTable&);

    /**
     * \internal
     *
     * Creates an RWDBExpr that represents a dyadic expression; that is, an
     * expression of the form: \a lhs \a op \a rhs.
     */
    RWDBExpr(const RWDBExpr& lhs, RWDBPhraseBook::RWDBPhraseKey op, const RWDBExpr& rhs);

    /**
     * Creates an RWDBExpr that represents an encapsulation of the SQL
     * expression:
     *
     * \a left = \a right
     *
     * where \a left is the name of the column and \a right is the
     * expression against which to compare.
     */
    RWDBExpr(const RWDBColumn& left, const RWDBExpr& right);

    /**
     * Creates an RWDBExpr that represents an encapsulation of the SQL
     * expression:
     *
     * \a left = \a right
     *
     * where \a left is the name of the column and \a right is the value
     * against which to compare.
     */
    RWDBExpr(const RWDBColumn& left, const RWDBValue& right);

protected:
    RWDBExpr(RWDBExprImp*);
    RWDBCountedRef<RWDBExprImp> impl_;
    friend RWDBExprImp* getImp(const RWDBExpr& expr)
    {
        return expr.impl_;
    }
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Adds RWCollectable semantics to RWDBExpr.
 *
 * RWDBCollectableExpr adds RWCollectable semantics to RWDBExpr. The DB
 * Interface Module uses RWDBCollectableExpr internally to store lists of
 * RWDBExpr objects. Applications requiring similar functionality can do the
 * same.
 *
 * \synopsis
 * #include <rw/db/expr.h>
 * \endsynopsis
 *
 * \sa
 * RWDBCollectableExpr is a special case of RWDBExpr. See RWDBExpr for
 * details. See your Essential Tools Module documentation for details about
 * RWCollectable.
 */
class RWDB_GLOBAL RWDBCollectableExpr : public RWCollectable, public RWDBExpr
{
public:
    /**
     * The default constructor builds an empty RWDBCollectableExpr, that is,
     * one whose asString() method returns an SQL \c NULL keyword, as
     * specified in its parameter \c phraseBook. Since an empty expression
     * cannot hold a value, RWDBCollectableExpr() cannot be used as \c NULL
     * value.
     */
    RWDBCollectableExpr();

    /**
     * Creates an RWDBCollectableExpr from the given \a expr.
     */
    RWDBCollectableExpr(const RWDBExpr& expr);

    /**
     * \internal
     * Creates an RWDBCollectableExpr from \a imp.
     */
    RWDBCollectableExpr(RWDBExprImp* imp);

    virtual ~RWDBCollectableExpr();

    /**
     * If \a c points to an RWDBCollectableExpr of the same type of
     * expression as self, returns the result of
     * <tt>asString().\ref RWCString::compareTo() "compareTo(c->asString())"</tt>
     * using the default \c phrasebook. Throws an \b std::bad_cast exception
     * if \a c is not a pointer to an RWDBCollectableExpr.
     *
     * As a precondition, \a c is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual int     compareTo(const RWCollectable* c) const;

    /**
     * Returns <tt>asString().\ref RWCString::hash() "hash()"</tt>.
     */
    unsigned        hash() const;

    /**
     * Dereferences \a expr as a pointer to RWDBCollectableExpr and compares
     * the result of its asString() to the result of self's asString().
     */
    bool            isEqual(const RWCollectable* expr) const;

    /**
     * Returns __RWDBCOLLECTABLEEXPR.
     */
    virtual RWClassID isA() const;

    // any documentation for the following is in the base class
    RWspace         binaryStoreSize() const;
    virtual void    saveGuts(RWFile& file) const;
    virtual void    saveGuts(RWvostream& stream) const;
    virtual void    restoreGuts(RWFile& file);
    virtual void    restoreGuts(RWvistream& stream);
    virtual RWCollectable* newSpecies() const;
    virtual RWCollectable* copy() const;
    static RWClassID       classIsA();

    /**
     * Looks at the next object on the input stream or RWFile, respectively,
     * and either creates a new object of the proper type off the heap and
     * returns a pointer to it, or else returns a pointer to a previously
     * read instance. Recursively calls the virtual function restoreGuts(),
     * taking duplicate objects into account. If an object is created off
     * the heap, then you are responsible for deleting it. For more
     * information, see the discussion on Persistence in the <em>Essential
     * Tools Module User's Guide</em>.
     *
     * Various exceptions that could be thrown are RWInternalErr (if the
     * RWFactory does not know how to make the object), and RWExternalErr
     * (corrupted stream or file). If an exception is thrown during this
     * call, the pointer to the partly restored object may be lost, creating
     * a memory leak. For this reason, you may prefer to use the static
     * method RWCollectable::tryRecursiveRestore().
     */
    friend RWDB_SYMBOLIC RWvistream&
    operator>>(RWvistream& s, RWDBCollectableExpr*& pCl);

    /**
     * \copydoc operator>>(RWvistream&, RWDBCollectableExpr*&)
     */
    friend RWDB_SYMBOLIC RWFile&
    operator>>(RWFile& f, RWDBCollectableExpr*& pCl);

    /**
     * Saves the object \a obj to a virtual stream. Recursively calls the
     * virtual function saveGuts(), taking duplicate objects into account.
     * See the discussion on Persistence in the <em>Essential Tools Module
     * User's Guide</em> for more information.
     *
     * \note
     * Bound variables in the expression are evaluated at the time the
     * expression is persisted.
     *
     * \note
     * Column names are persisted without an associated table name or table
     * tag.
     */
    RW_INLINE_FRIEND
    RWvostream& operator<<(RWvostream& v, const RWDBCollectableExpr& Cl)
    {
        Cl.recursiveSaveOn(v);
        return v;
    }


    /**
     * Saves the object \a obj to an RWFile. Recursively calls the virtual
     * function saveGuts(), taking duplicate objects into account. See the
     * discussion on Persistence in the <em>Essential Tools Module User's
     * Guide</em> for more information.
     *
     * \note
     * Bound variables in the expression are evaluated at the time the
     * expression is persisted.
     *
     * \note
     * Column names are persisted without an associated table name or table
     * tag.
     */
    RW_INLINE_FRIEND
    RWFile& operator<<(RWFile& f, const RWDBCollectableExpr& Cl)
    {
        Cl.recursiveSaveOn(f);
        return f;
    }


    /**
     * Restores an RWDBCollectableExpr into \a obj from a virtual stream,
     * replacing the previous contents of \a obj. Recursively calls the
     * virtual function restoreGuts(), taking duplicate objects into
     * account. For more information, see the discussion on Persistence in
     * the <em>Essential Tools Module User's Guide</em>.
     *
     * Various exceptions that could be thrown are RWInternalErr (if the
     * RWFactory does not know how to make the object), and RWExternalErr
     * (corrupted stream or file).
     */
    RW_INLINE_FRIEND
    RWvistream& operator>>(RWvistream& v, RWDBCollectableExpr& Cl)
    {
        RWCollectable::recursiveRestoreFrom(v, &Cl);
        return v;
    }

    /**
     * Restores an RWDBCollectableExpr into \a obj from an RWFile, replacing
     * the previous contents of \a obj. Recursively calls the virtual
     * function restoreGuts(), taking duplicate objects into account. For
     * more information, see the discussion on Persistence in the
     * <em>Essential Tools Module User's Guide</em>.
     *
     * Various exceptions that could be thrown are RWInternalErr (if the
     * RWFactory does not know how to make the object), and RWExternalErr
     * (corrupted stream or file).
     */
    RW_INLINE_FRIEND
    RWFile& operator>>(RWFile& f, RWDBCollectableExpr& Cl)
    {
        RWCollectable::recursiveRestoreFrom(f, &Cl);
        return f;
    }

private:
    static RWClassID myAtom;
    friend struct RWInit(RWDBCollectableExpr);
    friend RWCollectable* rwCreateFN(RWDBCollectableExpr)();
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Represents the result of applying logical operators to RWDBExpr. It
 * encapsulates search conditions that are used in SQL \c WHERE clauses and
 * \c CHECK constraints.
 *
 * RWDBCriterion is the result of applying logical operators to RWDBExpr. It
 * is used to encapsulate search conditions that are used in SQL \c WHERE
 * clauses and SQL \c CHECK constraints.
 *
 * RWDBCriterion represents a specialized type of RWDBExpr that is evaluated
 * in an SQL statement as a boolean value. RWDBCriterion adds neither
 * components nor member functions to the base class. Instead, it ensures
 * that a nonboolean expression is not placed in a context that requires a
 * boolean expression during compilation.
 *
 * \synopsis
 * #include <rw/db/expr.h>
 * \endsynopsis
 *
 * \sa
 * RWDBCriterion is a special case of RWDBExpr. Please see RWDBExpr for
 * details about RWDBCriterion usage, including operators and constructors.
 *
 * \example
 * In this example, an RWDBCriterion is created anonymously to be used as
 * part of an SQL \c WHERE clause:
 * \code
 * int x = somevalue;
 * RWDBSelector select = myDbase.selector();
 * select.where(myTable["myColumn"] != x);
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBCriterion : public RWDBExpr
{
public:
    /**
     * The default constructor creates an empty criterion.
     */
    RWDBCriterion(void);

    /**
     * \internal
     *
     * Creates a dyadic RWDBCriterion from the \a Left and \a Right operands
     * connected by the logical operator \a op.
     */
    RWDBCriterion(const RWDBExpr& Left,
                  RWDBPhraseBook::RWDBPhraseKey op,
                  const RWDBExpr& Right);

    /**
     * \internal
     *
     * Creates a monadic RWDBCriterion from the given \a op and \a expr.
     */
    RWDBCriterion(RWDBPhraseBook::RWDBPhraseKey op, const RWDBExpr& expr);

    RWDBCriterion(RWDBPhraseBook::RWDBPhraseKey, const RWDBExpr* x0 = 0,
                  const RWDBExpr* x1 = 0, const RWDBExpr* x2 = 0,
                  const RWDBExpr* x3 = 0);
    RWDBCriterion(const RWCString& s, const RWDBExpr* x0,
                  const RWDBExpr* x1, const RWDBExpr* x2 = 0,
                  const RWDBExpr* x3 = 0);
    virtual ~RWDBCriterion();

    RWDBCriterion& operator=(const RWDBCriterion& crit);
};
/**
 * \ingroup db_expression_group
 *
 * \brief
 * Represents the result of applying the RWDBColumn::assign() method to an
 * RWDBExpr.
 *
 * RWDBAssignment is the result of applying the RWDBColumn::assign() method
 * to an RWDBExpr. The result is an encapsulation of the SQL \c SET
 * \e column \c = \e expression phrase, where \e column refers to the
 * RWDBColumn instance whose \ref RWDBColumn::assign() "assign()" method
 * produced the RWDBAssignment, and \e expression refers to its parameter.
 * RWDBAssignment is used only to build instances of RWDBUpdater.
 *
 * \synopsis
 * #include <rw/db/expr.h>
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBAssignment is a special case of RWDBExpr. See RWDBExpr for details.
 *
 * RWDBAssignment instances are produced only by the
 * \ref RWDBColumn::assign() "assign()" method of RWDBColumn.
 * \endparblock
 *
 * \example
 * This example adds the phrase <tt>SET name = 'Joe'</tt> to an RWDBUpdater
 * for the \c Names table. To do this, an RWDBAssignment instance is created
 * anonymously:
 *
 * \code
 * RWDBTable Names = myDbase.table("Names");
 * RWDBUpdater update = Names.updater();
 * update << Names["name"].assign("Joe");
 * \endcode
 * \endexample
 */

class RWDB_GLOBAL RWDBAssignment : public RWDBExpr, public RWCollectable
{
public:

    /**
     * Constructs a default RWDBAssignment. Provided for convenience only.
     */
    RWDBAssignment(void);

    /**
     * Constructs an RWDBAssignment from an RWDBColumn and an RWDBExpr. Self
     * then emulates the SQL construct <tt>SET \a c = \a e</tt>.
     */
    RWDBAssignment(const RWDBColumn& c, const RWDBExpr& e);

    /**
     * Constructs an RWDBAssignment from an RWDBColumn and an RWDBValue.
     * Self then emulates the SQL construct <tt>SET \a c = \a v</tt>.
     */
    RWDBAssignment(const RWDBColumn& c, const RWDBValue& v);

    virtual ~RWDBAssignment();

    /**
     * Returns the RWDBColumn associated with self.
     */
    RWDBColumn column() const;

    /**
     * Returns the RWDBValue associated with self.
     */
    RWDBValue value() const;

    /**
     * Returns the RWDBExpr associated with self.
     */
    RWDBExpr expression() const;

    unsigned long updateSize() const;
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Acts as a placeholder in a dynamic SQL statement, providing a type-safe
 * interface for binding a local variable to a dynamic SQL statement.
 *
 * RWDBBoundExpr is a specialized type of RWDBExpr that is evaluated as a
 * placeholder within a dynamic SQL statement. It provides a type-safe
 * interface that allows applications to bind a local variable and an
 * optional null indicator to a dynamic SQL statement.
 *
 * \synopsis
 * #include <rw/db/expr.h>
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBBoundExpr can be used in conjunction with any other expression
 * classes and operators, such as RWDBAssignment.
 *
 * Other classes that use RWDBBoundExpr include RWDBSelector, RWDBDeleter,
 * RWDBInserter, and RWDBUpdater.
 * \endparblock
 *
 * \example
 * In this example, an RWDBBoundExpr is created and shifted into an
 * RWDBInserter. The RWDBInserter is then executed several times after
 * changing the bound local variable.
 *
 * \code
 * RWDBConnection connection = myDbase.connection();
 * RWDBTable myTable = myDbase.table("myTable");
 * RWDBInserter inserter = myDbase.inserter( myTable );
 * RWDBNullIndicator nullIndicator = 0;
 * float avg = .453;
 * inserter << RWDBBoundExpr(&avg, &nullIndicator);
 * inserter.execute( connection );            // Insert .453.
 *
 * nullIndicator = RWDBNullIndicator(true);   // Set to true.
 * inserter.execute( connection );            // Insert null.
 *
 * nullIndicator = RWDBNullIndicator(false);  // Set to false.
 * avg = .329;
 * inserter.execute( connection );            // Insert .329
 * \endcode
 * \endexample
 *
 * \note
 * An explicit connection is used for each execution of the RWDBInserter.
 * The application must ensure that the bound local variable and the
 * RWDBNullIndicator pointed to by the optional null indicator remain in
 * scope for all executions.
 */

class RWDB_GLOBAL RWDBBoundExpr : public RWDBExpr
{
public:

    /**
     * The default constructor builds an empty RWDBBoundExpr. An empty
     * RWDBBoundExpr is one whose method
     * \ref asString() "asString(const RWDBPhraseBook& phraseBook)" returns
     * an SQL \c NULL keyword, as specified in \c phraseBook.
     */
    RWDBBoundExpr();

    /**
     * Creates an RWDBBoundExpr from the given value, and an optional
     * pointer to a null indicator. Sets \a entries to \c 1, where
     * \a entries is the number of entries that \a valuePtr and
     * \a nullIndicator point to, and \c 1 is the only currently supported
     * value.
     *
     * When the asString() method expands in the context of a dynamic SQL
     * statement, the RWDBBoundExpr becomes a placeholder, with syntax that
     * varies among Access Modules. The application's value and the dynamic
     * SQL statement are then considered bound. If the optional pointer to a
     * null indicator is passed, the bound value is treated as \c NULL when
     * the value pointed at by \a nullIndicator is nonzero.
     */

    RWDBBoundExpr(short* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(unsigned short* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);
    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(int* i,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);
    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(unsigned int* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(long* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(unsigned long* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);
    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(long long* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(unsigned long long* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(float* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(double* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(long double* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWCString* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWDecimalPortable* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWDate* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWDateTime* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 12.5, use
     * \ref RWDBBoundExpr::RWDBBoundExpr(RWDateTime*, RWDBNullIndicator*, size_t) "RWDBBoundExpr(RWDateTime*, RWDBNullIndicator*, size_t)"
     * instead.
     *
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RW_DEPRECATE_FUNC("Use RWDBBoundExpr(RWDateTime*, RWDBNullIndicator*, size_t) instead")
    RWDBBoundExpr(RWDBDateTime* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWDBDuration* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWDBBlob* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWDBMBString* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);

    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWBasicUString* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);
    /**
     * \copydoc RWDBBoundExpr(short*, RWDBNullIndicator*, size_t)
     */
    RWDBBoundExpr(RWWString* valuePtr,
                  RWDBNullIndicator* nullIndicator = NULL,
                  size_t entries = 1);


    RWDBBoundExpr(RWDBExprImp* imp);
    virtual ~RWDBBoundExpr();

protected:

private:
    RWDBBoundExpr& operator=(const RWDBBoundExpr&);

};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Used to build outer join constructs.
 *
 * RWDBJoinExpr is created by a set of global functions that generate ANSI
 * SQL outer join syntax. It represents a specialized type of RWDBExpr that
 * is used only for building outer join constructs.
 *
 * \synopsis
 * #include <rw/db/expr.h>
 * \endsynopsis
 *
 * \sa
 * RWDBJoinExpr is a special case of RWDBExpr. See RWDBExpr for more
 * details. Also see RWDBColumn.
 *
 * \example
 * In this example, an RWDBJoinExpr is created anonymously by the related
 * global function rwdbOuter(), and set as part of the \c FROM clause.
 *
 * \code
 * // Instantiate a table object to represent the first table.
 * RWDBTable t1 = aDatabase.table("table1");
 *
 * // Instantiate a table object to represent the second table.
 * RWDBTable t2 = aDatabase.table("table2");
 *
 * // Instantiate a selector to represent a join query.
 * RWDBSelector aSelector = aDB.selector();
 *
 * // Construct an isolated full outer join expression
 * // using the global method rwdbOuter().
 * RWDBJoinExpr join = rwdbOuter(t1, t2);
 *
 * // Specify the join criterion and attach it to the
 * // join expression using the on method.
 * join.on(t1["c1"] == t2["c2"]);
 *
 * // Explicitly attach the join to the FROM clause
 * // of the selector.
 * aSelector.from( join );
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBJoinExpr : public RWDBExpr
{
public :
    /**
     * The default constructor is provided for convenience. Typically,
     * RWDBJoinExpr instances are obtained through outer join global
     * functions.
     */
    RWDBJoinExpr();

    /**
     * \internal
     *
     * Constructs an RWDBJoinExpr from two expressions. The constructed
     * RWDBJoinExpr represents an encapsulation of the SQL phrase:
     *
     * \a expr1 \a op \a expr2
     */
    RWDBJoinExpr(const RWDBExpr& expr1, const RWDBExpr& expr2,
                 RWDBPhraseBook::RWDBPhraseKey op,
                 RWDBPhraseBook::RWDBPhraseKey precdBegin =
                     RWDBPhraseBook::singleSpace,
                 RWDBPhraseBook::RWDBPhraseKey precdEnd =
                     RWDBPhraseBook::singleSpace
                );

    virtual ~RWDBJoinExpr();

    /**
     * Copy constructor. The created RWDBJoinExpr shares an implementation
     * with \a jexpr.
     */
    RWDBJoinExpr(const RWDBJoinExpr& jexpr);

    /**
     * Assignment operator. Self shares an implementation with \a jexpr.
     * Returns a reference to self.
     */
    RWDBJoinExpr& operator=(const RWDBJoinExpr& jexpr);

    // Methods to include ON and USING clauses to the outer join

    /**
     * Specifies the join condition as self's SQL \c ON clause. If self
     * already has an \c ON clause, this method replaces it. Returns a
     * reference to self.
     */
    RWDBJoinExpr& on(const RWDBCriterion& criterion); //ON clause

    /**
     * Adds the \a column to self's SQL \c USING clause, which specifies the
     * join columns for the join. Returns a reference to self.
     */
    RWDBJoinExpr& on(const RWDBColumn& column); //USING clause

protected:
private:

};



//////////////////////////////////////////////////////////////////////////
//
//  Related Global Functions
//
//////////////////////////////////////////////////////////////////////////
/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing a dyadic expression between two
 * subexpressions with \c + (plus) as the operator.
 */
RWDBExpr RWDB_SYMBOLIC operator+ (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing a monadic expression with \c + (plus) as
 * the operator.
 */
RWDBExpr RWDB_SYMBOLIC operator+ (const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing a dyadic expression between two
 * subexpressions with \c - (minus) as the operator.
 */
RWDBExpr RWDB_SYMBOLIC operator- (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing a monadic expression with \c - (minus)
 * as the operator.
 */
RWDBExpr RWDB_SYMBOLIC operator- (const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing a dyadic expression between two
 * subexpressions with \c * (multiply) as the operator.
 */
RWDBExpr RWDB_SYMBOLIC operator* (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing a dyadic expression between two
 * sub-expressions with \c / (divide) as the operator.
 */
RWDBExpr RWDB_SYMBOLIC operator/ (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing a dyadic expression between two
 * subexpressions with the \c % (modulo) operator.
 */
RWDBExpr RWDB_SYMBOLIC operator% (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with the \c == (equality) operator.
 */
RWDBCriterion RWDB_SYMBOLIC operator== (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with the \c != (inequality) operator.
 */
RWDBCriterion RWDB_SYMBOLIC operator!= (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with the \c > (greater than) operator.
 */
RWDBCriterion RWDB_SYMBOLIC operator> (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with the \c < (less than) operator.
 */
RWDBCriterion RWDB_SYMBOLIC operator< (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with the \c >= (greater than or equal to) operator.
 */
RWDBCriterion RWDB_SYMBOLIC operator>= (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with the \c <= (less than or equal to) operator.
 */
RWDBCriterion RWDB_SYMBOLIC operator<= (const RWDBExpr&, const RWDBExpr&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with \c && (and) as the operator, if both operands are
 * initialized. If only one operand is initialized, returns an RWDBCriterion
 * representing a monadic expression.
 */
RWDBCriterion RWDB_SYMBOLIC operator&& (const RWDBCriterion&,
                                        const RWDBCriterion&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a dyadic expression between two
 * subexpressions with \c || (or) as the operator, if both operands are
 * initialized. If only one operand is initialized, returns an RWDBCriterion
 * representing a monadic expression.
 */
RWDBCriterion RWDB_SYMBOLIC operator|| (const RWDBCriterion&,
                                        const RWDBCriterion&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing a monadic expression with the
 * operator \c ! (not).
 */
RWDBCriterion RWDB_SYMBOLIC operator!(const RWDBCriterion&);

/**
 * \relates RWDBExpr
 * Returns an RWDBCriterion representing the database-specific equivalent of
 * the SQL expression
 *
 * \c EXISTS(\e <select-statement>).
 *
 * In this expression, \e <select-statement> is the SQL select statement
 * encapsulated by \a select.
 */
RWDBCriterion RWDB_SYMBOLIC rwdbExists(const RWDBSelectorBase& select);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c AVERAGE(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbAvg(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c CAST(\a expr, \a type)
 *
 * For example, to produce the SQL phrase:
 *
 * \code
 * CAST(Col1 + 7, STRING)
 * \endcode
 *
 * we would write:
 *
 * \code
 * RWDBExpr anExpression = rwdbCast(col1 + 7, "STRING");
 * \endcode
 */
RWDBExpr RWDB_SYMBOLIC rwdbCast(const RWDBExpr& expr, const RWDBValue& type);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c CAST(\a expr, \a typeName, \a formatString)
 *
 * For example, to produce the SQL phrase:
 *
 * \code
 * CAST(dateCol, STRING, `MM-DD-YY')
 * \endcode
 * we would write:
 *
 * \code
 * RWDBExpr  anExpression  =  rwdbCast(dateCol,"STRING","'MM-DD-YY'");
 * \endcode
 */
RWDBExpr RWDB_SYMBOLIC rwdbCast(const RWDBExpr& expr, const RWDBValue& typeName,
                                const RWDBExpr& formatString);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c CAST(\a expr, \a typeName, \a formatString, \a secondaryFormat)
 *
 * For example, to produce the SQL phrase:
 *
 * \code
 * CAST(dateCol, STRING, `MM-DD-YY', French_France.WE8ISO88591')
 * \endcode
 *
 * where the last parameter is a database-specific directive to use French
 * style formatting, write:
 *
 * \code
 * RWDBExpr  anExpression  =
 * rwdbCast(dateCol,"STRING","'MM-DD-YY'", "'French_France.WE8ISO88591'");
 * \endcode
 */
RWDBExpr RWDB_SYMBOLIC rwdbCast(const RWDBExpr& expr,
                                const RWDBValue& typeName,
                                const RWDBExpr& formatString,
                                const RWDBExpr& secondaryFormat);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c CHARACTER_LENGTH(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbCharLength(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c COUNT(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbCount(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c COUNT(*)
 */
RWDBExpr RWDB_SYMBOLIC rwdbCount();

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c COUNT \c DISTINCT (\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbCountDistinct(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific function that
 * returns the name of the current user.
 */
RWDBExpr RWDB_SYMBOLIC rwdbCurrentUser();

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c TOLOWER(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbLower(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c MAX(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbMax(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c MIN(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbMin(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL phrase:
 *
 * \a name = \a expr.
 *
 * For example, to encapsulate the SQL statement:
 * \code
 * SELECT employeeName = name from employees
 * \endcode
 * write:
 *
 * \code
 * mySelector  <<  rwdbName("employeeName", employees["name"]);
 * \endcode
 */
RWDBExpr RWDB_SYMBOLIC rwdbName(const RWCString& name, const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c POSITION(\a expr1, \a expr2)
 *
 * The goal is to produce an SQL statement that gives the index of the
 * string \a expr1 in \a expr2.
 */
RWDBExpr RWDB_SYMBOLIC rwdbPosition(const RWDBExpr& expr1, const RWDBExpr& expr2);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c SESSION_USER()
 *
 * The details of the \c SESSION_USER() function are vendor-specific.
 */
RWDBExpr RWDB_SYMBOLIC rwdbSessionUser();

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c SUBSTRING(\a expr1, \a expr2)
 *
 * The goal is to produce an SQL statement that gives the substring of
 * \a expr1 starting at the index given by \a expr2.
 */
RWDBExpr RWDB_SYMBOLIC rwdbSubString(const RWDBExpr& expr1, const RWDBExpr& expr2);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c SUBSTRING(\a expr1, \a expr2, \a expr3)
 *
 * The goal is to produce an SQL statement that gives the substring of
 * \a expr1 starting at the index given by \a expr2, with length given by
 * \a expr3.
 */
RWDBExpr RWDB_SYMBOLIC rwdbSubString(const RWDBExpr& expr1,
                                     const RWDBExpr& expr2,
                                     const RWDBExpr& expr3);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c SUM(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbSum(const RWDBExpr& expr);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c SYSTEM_DATETIME()
 */
RWDBExpr RWDB_SYMBOLIC rwdbSystemDateTime();

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c SYSTEM_USER()
 */
RWDBExpr RWDB_SYMBOLIC rwdbSystemUser();

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c TRIM_LEADING(\a expr1, \a expr2)
 *
 * where \a expr1 represents the character to trim and \a expr2 represents
 * the string expression to be trimmed.
 */
RWDBExpr RWDB_SYMBOLIC rwdbTrimLeading(const RWDBExpr& expr1,
                                       const RWDBExpr& expr2);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c TRIM_TRAILING(\a exp1, \a expr2)
 *
 * where \a expr1 represents the character to trim and \a expr2 represents
 * the string expression to be trimmed.
 */
RWDBExpr RWDB_SYMBOLIC rwdbTrimTrailing(const RWDBExpr& expr1,
                                        const RWDBExpr& expr2);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c TRIM_BOTH(\a expr1, \a expr2)
 *
 * where \a expr1 represents the character to trim and \a expr2 represents
 * the string expression to be trimmed.
 */
RWDBExpr RWDB_SYMBOLIC rwdbTrimBoth(const RWDBExpr& expr1,
                                    const RWDBExpr& expr2);

/**
 * \relates RWDBExpr
 * Returns an RWDBExpr representing the database-specific equivalent of the
 * SQL function:
 *
 * \c UPPER(\a expr)
 */
RWDBExpr RWDB_SYMBOLIC rwdbUpper(const RWDBExpr& expr);


//////////////////////////////////////////////////////////////////////////////
//
// Outer Join Constructs
//
//////////////////////////////////////////////////////////////////////////////

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>LEFT OUTER JOIN</tt> SQL phrase between two tables.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbLeftOuter(const RWDBTable&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>LEFT OUTER JOIN</tt> SQL phrase between a table and an outer join
 * expression. For databases that support precedence in outer joins, the
 * generated SQL adds precedence to \a jexpr such that \a jexpr is evaluated
 * first before the \a table is joined.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbLeftOuter(const RWDBTable& table, const RWDBJoinExpr& jexpr);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>LEFT OUTER JOIN</tt> SQL phrase between an outer join expression and
 * a table. This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbLeftOuter(const RWDBJoinExpr&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>LEFT OUTER JOIN</tt> SQL phrase between two outer join expressions.
 * This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbLeftOuter(const RWDBJoinExpr&, const RWDBJoinExpr&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>RIGHT OUTER JOIN</tt> SQL phrase between two tables.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbRightOuter(const RWDBTable&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>RIGHT OUTER JOIN</tt> SQL phrase between a table and an outer join
 * expression. For databases that support precedence in outer joins, the
 * generated SQL adds precedence to \a jexpr, such that \a jexpr is
 * evaluated first before the \a table is joined.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbRightOuter(const RWDBTable& table, const RWDBJoinExpr& jexpr);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>RIGHT OUTER JOIN</tt> SQL phrase between an outer join expression and
 * a table. This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbRightOuter(const RWDBJoinExpr&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>RIGHT OUTER JOIN</tt> SQL phrase between two outer join expressions.
 * This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbRightOuter(const RWDBJoinExpr&, const RWDBJoinExpr&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>FULL OUTER JOIN</tt> SQL phrase between two tables.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbOuter(const RWDBTable&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>FULL OUTER JOIN</tt> SQL phrase between a table and an outer join
 * expression. For databases that support precedence in outer joins, the
 * generated SQL adds precedence to \a jexpr, such that \a jexpr is
 * evaluated first before the \a table is joined.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbOuter(const RWDBTable& table, const RWDBJoinExpr& jexpr);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>FULL OUTER JOIN</tt> SQL phrase between an outer join expression and
 * a table. This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbOuter(const RWDBJoinExpr& jexpr, const RWDBTable& table);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>FULL OUTER JOIN</tt> SQL phrase between two outer join expressions.
 * This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbOuter(const RWDBJoinExpr&, const RWDBJoinExpr&);

//////////////////////////////////////////////////////////////////////////////
//
// Inner Join Constructs
//
//////////////////////////////////////////////////////////////////////////////

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>INNER JOIN</tt> SQL phrase between two tables.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbInner(const RWDBTable&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>INNER JOIN</tt> SQL phrase between a table and an inner join
 * expression. For databases that support precedence in inner joins, the
 * generated SQL adds precedence to \a jexpr, such that \a jexpr is
 * evaluated first before the \a table is joined.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbInner(const RWDBTable& table, const RWDBJoinExpr& jexpr);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>INNER JOIN</tt> SQL phrase between an inner join expression and a
 * table. This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbInner(const RWDBJoinExpr& jexpr, const RWDBTable& table);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>INNER JOIN</tt> SQL phrase between two inner join expressions. This
 * does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbInner(const RWDBJoinExpr&, const RWDBJoinExpr&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL FULL OUTER JOIN</tt> SQL phrase between two tables.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalOuter(const RWDBTable&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL FULL OUTER JOIN</tt> SQL phrase between a table and an outer
 * join expression. For databases that support precedence in outer joins,
 * the generated SQL adds precedence to \a jexpr, such that \a jexpr is
 * evaluated first before the \a table is joined.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalOuter(
    const RWDBTable& table, const RWDBJoinExpr& jexpr);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL FULL OUTER JOIN</tt> SQL phrase between an outer join
 * expression and a table. This does not add any precedence to the
 * constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalOuter(
    const RWDBJoinExpr&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL FULL OUTER JOIN</tt> SQL phrase between two outer join
 * expressions. This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalOuter(
    const RWDBJoinExpr&, const RWDBJoinExpr&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL LEFT OUTER JOIN</tt> SQL phrase between two tables.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalLeftOuter(
    const RWDBTable&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL LEFT OUTER JOIN</tt> SQL phrase between a table and an outer
 * join expression. For databases that support precedence in outer joins,
 * the generated SQL adds precedence to \a jexpr, such that \a jexpr is
 * evaluated first before the \a table is joined.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalLeftOuter(
    const RWDBTable& table, const RWDBJoinExpr& jexpr);


/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL LEFT OUTER JOIN</tt> SQL phrase between an outer join
 * expression and a table. This does not add any precedence to the
 * constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalLeftOuter(
    const RWDBJoinExpr&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL LEFT OUTER JOIN</tt> SQL phrase between two outer join
 * expressions. This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalLeftOuter(
    const RWDBJoinExpr&, const RWDBJoinExpr&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL RIGHT OUTER JOIN</tt> SQL phrase between two tables.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalRightOuter(
    const RWDBTable&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL RIGHT OUTER JOIN</tt> SQL phrase between a table and an outer
 * join expression. For databases that support precedence in outer joins,
 * the generated SQL adds precedence to \a jexpr, such that \a jexpr is
 * evaluated first before the \a table is joined.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalRightOuter(
    const RWDBTable& table, const RWDBJoinExpr& jexpr);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL RIGHT OUTER JOIN</tt> SQL phrase between an outer join
 * expression and a table. This does not add any precedence to the
 * constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalRightOuter(
    const RWDBJoinExpr&, const RWDBTable&);

/**
 * \relates RWDBJoinExpr
 * Returns an RWDBJoinExpr that represents an encapsulation of the
 * <tt>NATURAL RIGHT OUTER JOIN</tt> SQL phrase between two outer join
 * expressions. This does not add any precedence to the constructs.
 */
RWDBJoinExpr RWDB_SYMBOLIC rwdbNaturalRightOuter(
    const RWDBJoinExpr&, const RWDBJoinExpr&);


#endif
