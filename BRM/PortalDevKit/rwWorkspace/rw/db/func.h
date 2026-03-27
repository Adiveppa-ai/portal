#ifndef __RWDB_FUNC_H__
#define __RWDB_FUNC_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/func.h#1 $
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
#include <rw/db/expr.h>


/**
 * \ingroup db_expression_group
 *
 * \brief
 * Base class for a family of classes that defines functional notation for
 * RWDBExpr.
 *
 * RWDBExprFormDefinition is a base class for a family of classes that
 * provide an extensible mechanism for an application to define functional
 * notation for RWDBExpr. RWDBExprFormDefinition allows the creation an
 * object that translates into an RWDBExpr and can eventually be expanded
 * into an SQL string. The object will allow up to four expressions to be
 * embedded into the resultant string.
 *
 * An RWDBExprFormDefinition object is instantiated with a format string.
 * The format string may contain placeholders for up to four positional
 * parameters, which are labeled \c \%0 through \c \%3. An object defined
 * this way may subsequently be referenced like predefined functions, such
 * as #rwdbMax and #rwdbAvg.
 *
 * When an RWDBExprFormDefinition object is expanded by the
 * \ref RWDBExpr::asString() "asString()" method of RWDBExpr, each instance
 * of \c \%0 is replaced with the first actual parameter, each instance of
 * \c \%1 is replaced with the second actual parameter, and so on. There can
 * be multiple instances of a placeholder in the format string, and the
 * placeholders may occur in any order. This allows great flexibility in
 * defining functions, at the cost of losing compile-time checking on the
 * number of parameters actually passed. To enable compile-time checking on
 * the number of actual parameters, at the cost of some flexibility, use the
 * RWDBExprFuncDef0, RWDBExprFuncDef1, RWDBExprFuncDef2, RWDBExprFuncDef3
 * and RWDBExprFuncDef4 classes.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBExprFormDefinition myFunc("myFormat");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBCritFormDefinition provides a parallel mechanism for defining an
 * RWDBCriterion, rather than using RWDBExpr.
 *
 * RWDBExprFuncDef0, RWDBExprFuncDef1, RWDBExprFuncDef2, RWDBExprFuncDef3,
 * and RWDBExprFuncDef4 are derived from RWDBExprFormDefinition. They
 * provide a simplified interface for functions requiring \c 0 - \c 4
 * parameters, respectively, and do not require positional placeholders.
 *
 * See RWDBExpr for details on SQL expressions in the DB Interface Module,
 * as well as for a complete listing of predefined SQL functions.
 * \endparblock
 *
 * \example
 * Imagine that a database vendor's SQL variant provides the function
 * <tt>DECRYPT(string, length, key)</tt>. The DB Interface Module has no
 * direct support for this function, yet we would like to use it without
 * losing the benefits of its high-level constructs for data manipulation.
 * To do so, we can use a function which we define ourselves:
 *
 * \code
 * RWDBExprFormDefinition decrypt("DECRYPT(%0, %1, %2)");
 * RWCString key = getMyKey();
 * RWDBTable users = myDbase.table("users");
 * RWDBColumn passWord = users["passWord"];
 * RWDBSelector select = users.selector();
 * select << decrypt(passWord, rwdbCharLength(passWord), key);
 * \endcode
 * Note that the number of parameters actually passed to \c decrypt is not
 * checked. Compare this example with the RWDBExprFuncDef3 example to see
 * how such checking can be enabled.
 * \endexample
 */
class RWDB_GLOBAL RWDBExprFormDefinition
{
public:

    /**
     * Creates an empty RWDBExprFormDefinition. Provided for convenience
     * only.
     */
    RWDBExprFormDefinition();

    /**
     * Creates an RWDBExprFormDefinition with the given \a formatString.
     * Objects instantiated this way may subsequently be referenced as
     * though they were predefined SQL functions.
     */
    RWDBExprFormDefinition(const RWCString& formatString);

    virtual ~RWDBExprFormDefinition();

    /**
     * Returns an RWDBExpr that encapsulates the \c formatString associated
     * with RWDBExprFormDefinition.
     */
    virtual RWDBExpr operator()();

    /**
     * Returns an RWDBExpr that can replace any instance of \c \%0 in self's
     * function definition with \a expr0.
     */
    virtual RWDBExpr operator()(const RWDBExpr& expr0);

    /**
     * Returns an RWDBExpr that can replace any instance of \c \%0 in self's
     * function definition with \a expr0 and \c \%1 with \a expr1.
     */
    virtual RWDBExpr operator()(const RWDBExpr& expr0, const RWDBExpr& expr1);

    /**
     * Returns an RWDBExpr that can replace any instance of \c \%0 in self's
     * function definition with \a expr0, \c \%1 with \a expr1, and so on.
     */
    virtual RWDBExpr operator()(const RWDBExpr& expr0, const RWDBExpr& expr1,
                                const RWDBExpr& expr2);

    /**
     * Returns an RWDBExpr that can replace any instance of \c \%0 in self's
     * function definition with \a expr0, \c \%1 with \a expr1, and so on.
     */
    virtual RWDBExpr operator()(const RWDBExpr& expr0, const RWDBExpr& expr1,
                                const RWDBExpr& expr2, const RWDBExpr& expr3);

protected:
    RWCString format_;

    RWDBExpr buildExpression(const RWDBExpr* = 0, const RWDBExpr* = 0,
                             const RWDBExpr* = 0, const RWDBExpr* = 0);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBExprFormDefinition used to define
 * SQL functions that take no parameters.
 *
 * RWDBExprFuncDef0 is a specialization of the base class
 * RWDBExprFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking no parameters. Unlike the base class, this
 * class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBExprFuncDef0 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBCritFuncDef0 provides a parallel mechanism for defining an
 * RWDBCriterion, rather than an RWDBExpr.
 *
 * The RWDBExprFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBExpr for details on SQL expressions in the DB Interface Module,
 * as well as for a complete listing of predefined SQL functions.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBExprFuncDef3.
 * \endexample
 */
class RWDB_GLOBAL RWDBExprFuncDef0 : private RWDBExprFormDefinition
{
public:

    /**
     * Creates an RWDBExprFuncDef0 for a functional expression that takes no
     * parameters. After such an RWDBExprFuncDef0 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBExprFuncDef0(const RWCString& functionName);

    virtual ~RWDBExprFuncDef0();

    /**
     * Returns an RWDBExpr in the form of a function with zero parameters
     * whose name is the name which was passed to self's constructor.
     */
    virtual RWDBExpr operator()();

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBExprFormDefinition used to define
 * SQL functions that take \c 1 parameter.
 *
 * RWDBExprFuncDef1 is a specialization of the base class
 * RWDBExprFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 1 parameter. Unlike the base class, this
 * class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBExprFuncDef1 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBCritFuncDef1 provides a parallel mechanism for defining an
 * RWDBCriterion, rather than an RWDBExpr.
 *
 * The RWDBExprFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBExpr for details on SQL expressions in the DB Interface Module,
 * as well as for a complete listing of predefined SQL functions.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBExprFuncDef3.
 * \endexample
 */
class RWDB_GLOBAL RWDBExprFuncDef1 : private RWDBExprFormDefinition
{
public:

    /**
     * Creates an RWDBExprFuncDef1 for a functional expression that takes
     * one parameter. After such an RWDBExprFuncDef1 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBExprFuncDef1(const RWCString& functionName);

    virtual ~RWDBExprFuncDef1();

    /**
     * Returns an RWDBExpr in the form of a function with one parameter
     * whose name is the name which was passed to self's constructor.
     */
    virtual RWDBExpr operator()(const RWDBExpr& x1);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBExpr operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBExprFormDefinition used to define
 * SQL functions that take \c 2 parameters.
 *
 * RWDBExprFuncDef2 is a specialization of the base class
 * RWDBExprFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 2 parameters. Unlike the base class,
 * this class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBExprFuncDef2 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBCritFuncDef2 provides a parallel mechanism for defining an
 * RWDBCriterion, rather than an RWDBExpr.
 *
 * The RWDBExprFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBExpr for details on SQL expressions in the DB Interface Module,
 * as well as for a complete listing of predefined SQL functions.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBExprFuncDef3.
 * \endexample
 */
class RWDB_GLOBAL RWDBExprFuncDef2 : private RWDBExprFormDefinition
{
public:

    /**
     * Creates an RWDBExprFuncDef2 for a functional expression that takes
     * two parameters. After such an RWDBExprFuncDef2 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBExprFuncDef2(const RWCString& functionName);
    virtual ~RWDBExprFuncDef2();

    /**
     * Returns an RWDBExpr in the form of a function with two parameters
     * whose name is the name which was passed to self's constructor.
     */
    virtual RWDBExpr operator()(const RWDBExpr& x1, const RWDBExpr& x2);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBExpr operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBExprFormDefinition used to define
 * SQL functions that take \c 3 parameters.
 *
 * RWDBExprFuncDef3 is a specialization of the base class
 * RWDBExprFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 3 parameters. Unlike the base class,
 * this class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBExprFuncDef3 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBCritFuncDef3 provides a parallel mechanism for defining an
 * RWDBCriterion, rather than an RWDBExpr.
 *
 * The RWDBExprFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBExpr for details on SQL expressions in the DB Interface Module,
 * as well as for a complete listing of predefined SQL functions.
 * \endparblock
 *
 * \example
 * Imagine that a database vendor's SQL variant provides the function
 * <tt>DECRYPT(string, length, key)</tt>. The DB Interface Module has no
 * direct support for this function, yet we would like to use it without
 * losing the benefits of its high-level constructs for data manipulation.
 * To do so, we can use a function which we define ourselves:
 *
 * \code
 * RWDBExprFuncDef3 decrypt("DECRYPT");
 * RWCString key = getMyKey();
 * RWDBTable users = myDbase.table("users");
 * RWDBColumn passWord = users["passWord"];
 * RWDBSelector select = myDbase.selector();
 * select << decrypt(passWord, rwdbCharLength(passWord), key);
 * \endcode
 * Notice that the number of actual parameters passed to \c decrypt is
 * checked at compile time. Compare this with the RWDBExprFormDefinition
 * example.
 * \endexample
 */
class RWDB_GLOBAL RWDBExprFuncDef3 : private RWDBExprFormDefinition
{
public:

    /**
     * Creates an RWDBExprFuncDef3 for a functional expression that takes
     * three parameters. After such an RWDBExprFuncDef3 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBExprFuncDef3(const RWCString& functionName);

    virtual ~RWDBExprFuncDef3();

    /**
     * Returns an RWDBExpr in the form of a function with three parameters
     * whose name is the name which was passed to self's constructor.
     */
    virtual RWDBExpr operator()(const RWDBExpr& x1, const RWDBExpr& x2,
                                const RWDBExpr& x3);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBExpr operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBExprFormDefinition used to define
 * SQL functions that take \c 4 parameters.
 *
 * RWDBExprFuncDef4 is a specialization of the base class
 * RWDBExprFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 4 parameters. Unlike the base class,
 * this class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBExprFuncDef4 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBCritFuncDef4 provides a parallel mechanism for defining an
 * RWDBCriterion, rather than an RWDBExpr.
 *
 * The RWDBExprFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBExpr for details on SQL expressions in the DB Interface Module,
 * as well as for a complete listing of predefined SQL functions.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBExprFuncDef3.
 * \endexample
 */
class RWDB_GLOBAL RWDBExprFuncDef4 : private RWDBExprFormDefinition
{
public:

    /**
     * Creates an RWDBExprFuncDef4 for a functional expression that takes
     * four parameters. After such an RWDBExprFuncDef4 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBExprFuncDef4(const RWCString& functionName);

    virtual ~RWDBExprFuncDef4();

    /**
     * Returns an RWDBExpr in the form of a function with four parameters
     * whose name is the name which was passed to self's constructor.
     */
    virtual RWDBExpr operator()(const RWDBExpr& x1, const RWDBExpr& x2,
                                const RWDBExpr& x3, const RWDBExpr& x4);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBExpr operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBExpr operator()(const RWDBExpr&, const RWDBExpr&,
                                const RWDBExpr&);
};


//////////////////////////////////////////////////////////////////////////
//
//  RWDBPhraseExprDefinition
//
//  This class allows a programmer to create an object that will translate
//  into an RWDBExpr and then into an SQL string.  Each instance will allow
//  up to four expressions to be embedded into the SQL statement. It is
//  similar to RWDBExprFormDefinition, however, an index into an
//  RWDBPhraseBook is stored, rather than a format string.  The format
//  string is eventually fetched from the phraseBook.
//
//  The operator() variants are used to convert instances of
//  RWDBPhraseExprDefinition into RWDBExpr instances.
//
//  Components:
//    aPhraseKey_ - an RWDBPhraseKey to be used to get a template for the
//                  final substitution of expressions. The template may
//                  contain markers of the form '%n' (n can be 0..3,
//                  inclusive).  Each instance of '%0' is eventually replaced
//                  by the first positional parameter, %1, by the second,
//                  and so on.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBPhraseExprDefinition
{
public:
    RWDBPhraseExprDefinition(RWDBPhraseBook::RWDBPhraseKey pk);
    virtual ~RWDBPhraseExprDefinition();
    virtual RWDBExpr operator()();
    virtual RWDBExpr operator()(const RWDBExpr& x0);
    virtual RWDBExpr operator()(const RWDBExpr& x0, const RWDBExpr& x1);
    virtual RWDBExpr operator()(const RWDBExpr& x0, const RWDBExpr& x1,
                                const RWDBExpr& x2);
    virtual RWDBExpr operator()(const RWDBExpr& x0, const RWDBExpr& x1,
                                const RWDBExpr& x2, const RWDBExpr& x3);

protected:
    RWDBPhraseBook::RWDBPhraseKey aPhraseKey_;

    RWDBExpr buildExpression(const RWDBExpr* x0 = 0, const RWDBExpr* x1 = 0,
                             const RWDBExpr* x2 = 0, const RWDBExpr* x3 = 0);
};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBCritFormDefinition
//
//  This class allows a programmer to create an object that will translate
//  into an RWDBExpr and then into an SQL string.  Each instance will allow
//  up to four expressions to be embedded into the SQL statement. It is
//  similar to RWDBExprFormDefinition. However, the instances of this
//  class are converted into RWDBCriterion instances, rather than
//  RWDBExpr instances.
//
//  The operator() variants are used to convert instances of
//  RWDBCritFormDefinition into RWDBCriterion instances.
//
//  Components:
//    format_ - an RWCString to be used as a template for the final
//              substitution of expressions.  The template may
//              contain markers of the form '%n' (n can be 0..3,
//              inclusive).  Each instance of '%0' is eventually replaced
//              by the first positional parameter, %1, by the second,
//              and so on.
//
//////////////////////////////////////////////////////////////////////////

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Base class for a family of classes used to define functional notation for
 * RWDBCriterion.
 *
 * RWDBCritFormDefinition is a base class for a family of classes that
 * provides an extensible mechanism an application can use to define
 * functional notation for RWDBCriterion. RWDBCritFormDefinition creates an
 * object that can translate into an RWDBCriterion and eventually be
 * expanded into an SQL string. The object allows up to four expressions to
 * be embedded into the resultant string.
 *
 * An RWDBCritFormDefinition object is instantiated with a format string.
 * The format string may contain placeholders for up to four positional
 * parameters, which are labeled \c \%0 through \c \%3. An object defined in
 * this way may subsequently be referenced in the same way that predefined
 * functions like #rwdbMax and #rwdbAvg are referenced.
 *
 * When an RWDBCritFormDefinition object is expanded by the
 * \ref RWDBCriterion::asString() "asString()" method of an RWDBCriterion,
 * each instance of \c \%0 is replaced with the first actual parameter, each
 * instance of \c \%1 is replaced with the second actual parameter, and so
 * on. Multiple instances of a placeholder can exist in the format string,
 * and the placeholders may occur in any order. This allows great
 * flexibility in defining functions, at the cost of losing compile-time
 * checking on the number of parameters actually passed. To enable
 * compile-time checking on the number of actual parameters, at the cost of
 * some flexibility, use the RWDBCritFuncDef0, RWDBCritFuncDef1,
 * RWDBCritFuncDef2, RWDBCritFuncDef3 and RWDBCritFuncDef4 classes.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBCritFormDefinition myFunc("myFormat");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBExprFormDefinition provides a parallel mechanism for defining an
 * RWDBExpr, rather than using an RWDBCriterion.
 *
 * RWDBCritFuncDef0, RWDBCritFuncDef1, RWDBCritFuncDef2, RWDBCritFuncDef3,
 * and RWDBCritFuncDef4 are derived from RWDBCritFormDefinition. They
 * provide a simplified interface for functions requiring \c 0 - \c 4
 * parameters, respectively, and do not require positional placeholders.
 *
 * See RWDBCriterion for details on SQL \c WHERE clauses in the DB Interface
 * Module.
 * \endparblock
 *
 * \example
 * Imagine that a database vendor's SQL variant provides the boolean
 * function <tt>VALID_NAME(string)</tt>, which can be used in a \c WHERE
 * clause. The DB Interface Module has no direct support for this function,
 * yet we would like to use it without losing the benefits of high-level
 * constructs for data manipulation. To do so, we can use a function which
 * we define ourselves:
 *
 * \code
 * RWDBCritFormDefinition validName("VALID_NAME(%0)");
 * RWDBTable potentialNames = myDbase.table("potentialNames");
 * RWDBColumn name = potentialNames["name"];
 * RWDBSelector usableNames = myDbase.selector();
 * usableNames << name;
 * usableNames.where(validName(name));
 * \endcode
 * Note that the number of parameters actually passed to \c validName is not
 * checked. Compare this example with the RWDBCritFuncDef1 example to see
 * how such checking can be enabled.
 * \endexample
 */
class RWDB_GLOBAL RWDBCritFormDefinition
{
public:
    /**
     * The default constructor creates an empty RWDBCritFormDefinition.
     */
    RWDBCritFormDefinition();

    /**
     * Creates an RWDBCritFormDefinition with the given \a formatString.
     * Objects instantiated in this way may subsequently be referenced as
     * though they were predefined SQL functions.
     */
    RWDBCritFormDefinition(const RWCString& formatString);

    virtual ~RWDBCritFormDefinition();

    /**
     * Returns an RWDBCriterion that encapsulates the formatString
     * associated with RWDBCritFormDefinition.
     */
    virtual RWDBCriterion operator()();

    /**
     * Returns an RWDBCriterion with the ability to replace any instance of
     * \c \%0 in self's function definition with \a expr0.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& expr0);

    /**
     * Returns an RWDBCriterion with the ability to replace any instance of
     * \c \%0 in self's function definition with \a expr0 and \c \%1 with
     * \a expr1.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& expr0, const RWDBExpr& expr1);

    /**
     * Returns an RWDBCriterion with the ability to replace any instance of
     * \c \%0 in self's function definition with \a expr0, \c \%1 with
     * \a expr1, and so on.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& expr0, const RWDBExpr& expr1,
                                     const RWDBExpr& expr2);

    /**
     * Returns an RWDBCriterion with the ability to replace any instance of
     * \c \%0 in self's function definition with \a expr0, \c \%1 with
     * \a expr1, and so on.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& expr0, const RWDBExpr& expr1,
                                     const RWDBExpr& expr2, const RWDBExpr& expr3);

protected:
    RWCString format_;

    RWDBCriterion buildExpression(const RWDBExpr* = 0, const RWDBExpr* = 0,
                                  const RWDBExpr* = 0, const RWDBExpr* = 0);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBCritFormDefinition used for defining
 * SQL functions taking no parameters.
 *
 * RWDBCritFuncDef0 is a specialization of the base class
 * RWDBCritFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking no parameters. Unlike the base class, this
 * class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBCritFuncDef0 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBExprFuncDef0 provides a parallel mechanism for defining an RWDBExpr,
 * rather than using an RWDBCriterion.
 *
 * The RWDBCritFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBCriterion for details on SQL \c WHERE clauses in the DB Interface
 * Module.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBCritFuncDef1.
 * \endexample
 */
class RWDB_GLOBAL RWDBCritFuncDef0 : private RWDBCritFormDefinition
{
public:

    /**
     * Creates an RWDBCritFuncDef0 for a functional expression that takes no
     * parameters. After such an RWDBCritFuncDef0 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBCritFuncDef0(const RWCString& functionName);

    virtual ~RWDBCritFuncDef0();

    /**
     * Returns an RWDBCriterion in the form of a function with no parameter
     * whose name is the name that was passed to self's constructor.
     */
    virtual RWDBCriterion operator()();

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * no parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBCritFormDefinition used for defining
 * SQL functions taking \c 1 parameter.
 *
 * RWDBCritFuncDef1 is a specialization of the base class
 * RWDBCritFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 1 parameter. Unlike the base class, this
 * class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBCritFuncDef1 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBExprFuncDef1 provides a parallel mechanism for defining an RWDBExpr,
 * rather than using an RWDBCriterion.
 *
 * The RWDBCritFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBCriterion for details on SQL \c WHERE clauses in the DB Interface
 * Module.
 * \endparblock
 *
 * \example
 * Imagine that a database vendor's SQL variant provides the boolean
 * function <tt>VALID_NAME(string)</tt>, which can be used in a \c WHERE
 * clause. The DB Interface Module has no direct support for this function,
 * yet we would like to use it without losing the benefits of high-level
 * constructs for data manipulation. To do so, we can use a function which
 * we define ourselves:
 *
 * \code
 * RWDBCritFuncDef1 validName("VALID_NAME");
 * RWDBTable potentialNames = myDbase.table("potentialNames");
 * RWDBColumn name = potentialNames["name"];
 * RWDBSelector usableNames = myDbase.selector();
 * usableNames << name;
 * usableNames.where(validName(name));
 * \endcode
 * Notice that the number of actual parameters passed to \c validName is
 * checked at compile time. Compare this with the example for
 * RWDBCritFormDefinition.
 * \endexample
 */
class RWDB_GLOBAL RWDBCritFuncDef1 : private RWDBCritFormDefinition
{
public:

    /**
     * Creates an RWDBCritFuncDef1 for a functional expression that takes 1
     * parameter. After such an RWDBCritFuncDef1 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBCritFuncDef1(const RWCString& functionName);

    virtual ~RWDBCritFuncDef1();

    /**
     * Returns an RWDBCriterion in the form of a function with 1 parameter
     * whose name is the name that was passed to self's constructor.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& x1);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBCriterion operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * one parameter.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBCritFormDefinition used for defining
 * SQL functions taking \c 2 parameters.
 *
 * RWDBCritFuncDef2 is a specialization of the base class
 * RWDBCritFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 2 parameters. Unlike the base class,
 * this class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBCritFuncDef2 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBExprFuncDef2 provides a parallel mechanism for defining an RWDBExpr,
 * rather than using an RWDBCriterion.
 *
 * The RWDBCritFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBCriterion for details on SQL \c WHERE clauses in the DB Interface
 * Module.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBCritFuncDef1.
 * \endexample
 */
class RWDB_GLOBAL RWDBCritFuncDef2 : private RWDBCritFormDefinition
{
public:

    /**
     * Creates an RWDBCritFuncDef2 for a functional expression that takes 2
     * parameters. After such an RWDBCritFuncDef2 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBCritFuncDef2(const RWCString& functionName);

    virtual ~RWDBCritFuncDef2();

    /**
     * Returns an RWDBCriterion in the form of a function with 2 parameters
     * whose name is the name that was passed to self's constructor.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& x1, const RWDBExpr& x2);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBCriterion operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * two parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBCritFormDefinition used for defining
 * SQL functions taking \c 3 parameters.
 *
 * RWDBCritFuncDef3 is a specialization of the base class
 * RWDBCritFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 3 parameters. Unlike the base class,
 * this class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBCritFuncDef3 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBExprFuncDef3 provides a parallel mechanism for defining an RWDBExpr,
 * rather than using an RWDBCriterion.
 *
 * The RWDBCritFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBCriterion for details on SQL \c WHERE clauses in the DB Interface
 * Module.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBCritFuncDef1.
 * \endexample
 */
class RWDB_GLOBAL RWDBCritFuncDef3 : private RWDBCritFormDefinition
{
public:

    /**
     * Creates an RWDBCritFuncDef3 for a functional expression that takes 3
     * parameters. After such an RWDBCritFuncDef3 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBCritFuncDef3(const RWCString& functionName);

    virtual ~RWDBCritFuncDef3();

    /**
     * Returns an RWDBCriterion in the form of a function with 3 parameters
     * whose name is the name that was passed to self's constructor.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& x1, const RWDBExpr& x2,
                                     const RWDBExpr& x3);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBCriterion operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * three parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&, const RWDBExpr&);
};

/**
 * \ingroup db_expression_group
 *
 * \brief
 * Specialization of the base class RWDBCritFormDefinition used for defining
 * SQL functions taking \c 4 parameters.
 *
 * RWDBCritFuncDef4 is a specialization of the base class
 * RWDBCritFormDefinition. This class provides a simplified mechanism for
 * defining SQL functions taking \c 4 parameters. Unlike the base class,
 * this class does not require positional placeholders in its function
 * definitions. Also, since the number of required parameters is fixed,
 * compile-time checking can be done on the number of parameters actually
 * passed.
 *
 * \synopsis
 * #include <rw/db/func.h>
 *
 * RWDBCritFuncDef4 myFunc("myFunc");
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBExprFuncDef4 provides a parallel mechanism for defining an RWDBExpr,
 * rather than using an RWDBCriterion.
 *
 * The RWDBCritFormDefinition base class may be used directly to gain
 * additional flexibility.
 *
 * See RWDBCriterion for details on SQL \c WHERE clauses in the DB Interface
 * Module.
 * \endparblock
 *
 * \example
 * Please refer to the example in RWDBCritFuncDef1.
 * \endexample
 */
class RWDB_GLOBAL RWDBCritFuncDef4 : private RWDBCritFormDefinition
{
public:

    /**
     * Creates an RWDBCritFuncDef4 for a functional expression that takes 4
     * parameters. After such an RWDBCritFuncDef4 is instantiated,
     * \a functionName may be used as though it were a predefined function.
     */
    RWDBCritFuncDef4(const RWCString& functionName);

    virtual ~RWDBCritFuncDef4();

    /**
     * Returns an RWDBCriterion in the form of a function with 4 parameters
     * whose name is the name that was passed to self's constructor.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&,
                                     const RWDBExpr&, const RWDBExpr&);

private:

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBCriterion operator()();

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr&, const RWDBExpr&);

    /**
     * Not applicable to this class. This class defines SQL functions taking
     * four parameters.
     */
    virtual RWDBCriterion operator()(const RWDBExpr& x1, const RWDBExpr& x2,
                                     const RWDBExpr& x3);
};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBPhraseCritDefinition
//
//  This class allows a programmer to create an object that will translate
//  into an RWDBCriterion and then into an SQL string.  Each instance will allow
//  up to four expressions to be embedded into the SQL statement. It is
//  similar to RWDBCritFormDefinition, however, an index into an
//  RWDBPhraseBook is stored, rather than a format string.  The format
//  string is eventually fetched from the phraseBook.
//
//  The operator() variants are used to convert instances of
//  RWDBPhraseCritDefinition into RWDBCriterion instances.
//
//  Components:
//    aPhraseKey_ - an RWDBPhraseKey to be used to get a template for the
//                  final substitution of expressions. The template may
//                  contain markers of the form '%n' (n can be 0..3,
//                  inclusive).  Each instance of '%0' is eventually replaced
//                  by the first positional parameter, %1, by the second,
//                  and so on.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBPhraseCritDefinition
{
public:
    RWDBPhraseCritDefinition(RWDBPhraseBook::RWDBPhraseKey pk);
    virtual ~RWDBPhraseCritDefinition();
    virtual RWDBCriterion operator()();
    virtual RWDBCriterion operator()(const RWDBExpr& x0);
    virtual RWDBCriterion operator()(const RWDBExpr& x0, const RWDBExpr& x1);
    virtual RWDBCriterion operator()(const RWDBExpr& x0, const RWDBExpr& x1,
                                     const RWDBExpr& x2);
    virtual RWDBCriterion operator()(const RWDBExpr& x0, const RWDBExpr& x1,
                                     const RWDBExpr& x2, const RWDBExpr& x3);

protected:
    RWDBPhraseBook::RWDBPhraseKey aPhraseKey_;

    RWDBCriterion buildExpression(const RWDBExpr* x0 = 0,
                                  const RWDBExpr* x1 = 0,
                                  const RWDBExpr* x2 = 0,
                                  const RWDBExpr* x3 = 0);
};

#endif
