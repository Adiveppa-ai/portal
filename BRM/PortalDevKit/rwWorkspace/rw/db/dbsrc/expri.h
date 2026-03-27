#ifndef __RWDB_EXPRI_H__
#define __RWDB_EXPRI_H__

/***************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/expri.h#1 $
 *
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

#include <rw/db/dbsrc/colldefs.h>
#include <rw/db/dbsrc/stmt.h>
#include <rw/db/dbref.h>
#include <rw/db/expr.h>
#include <rw/db/schema.h>
#include <rw/db/select.h>
#include <rw/db/table.h>

//////////////////////////////////////////////////////////////////////////
//
//  RWDBExprImp
//
//  This class is the base class for all expression implementations.  It
//  contains reference counting facilities and provides the
//  standard interface for all implementations.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBExprImp
    : public RWDBReference
{
public:
    RWDBExprImp();
    virtual ~RWDBExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const = 0;
    virtual RWDBValue::ValueType type();
    virtual int                 nativeType() const;
    virtual void                setNativeType(int nativeType);

    virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    virtual void tableTagExpr(RWSet&) const;

    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

protected:

    friend class RWDBExpr;

private:
    // not implemented
    RWDBExprImp(const RWDBExprImp&);
    RWDBExprImp& operator=(const RWDBExprImp&);
};


//////////////////////////////////////////////////////////////////////////
//
//  RWDBDyadicExprImp
//
//  This class implements an expression consisting of a left expression,
//  an operator and a right expression.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBDyadicExprImp : public RWDBExprImp
{
public:
    RWDBDyadicExprImp();
    RWDBDyadicExprImp(const RWDBExpr&, /*enum*/ RWDBPhraseBook::RWDBPhraseKey,
                      const RWDBExpr&);
    virtual ~RWDBDyadicExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    virtual void tableTagExpr(RWSet&) const;
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

private:
    RWDBExpr leftExpr_;
    RWDBExpr rightExpr_;
    RWDBPhraseBook::RWDBPhraseKey op_;

};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBAssignmentExprImp
//
//  This class implements an expression consisting of a left expression,
//  operator "=", and a right expression.
//
//  Components:
//    leftExpr_ - an RWDBExpr representing the left expression
//    rightExpr_ - an RWDBExpr representing the right expression
//    op_ - an enum that represents the operator in the expression
//    column_ - the column to which an assignment is being made
//    rightExpr_ - the expression being assigned to the column, or an
//             empty expression if a value, rather than an expression is
//             being assigned
//    value_ - the value being assigned to the column, or a NULL value
//             if an expression, rather than a simple value is being assigned
//    valueSize_ - an estimate ( > 0 ) of the size of the rhs of the assignment,
//             if the rhs is a value, or 0 if the rhs is an expression
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBAssignmentExprImp : public RWDBExprImp
{
public:
    RWDBAssignmentExprImp();
    RWDBAssignmentExprImp(const RWDBColumn&, const RWDBExpr&);
    RWDBAssignmentExprImp(const RWDBColumn&, const RWDBValue&);
    virtual ~RWDBAssignmentExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    virtual RWDBColumn column() const;
    virtual RWDBValue value() const;
    virtual RWDBExpr expression() const;
    virtual unsigned long updateSize() const;
    virtual void tableTagExpr(RWSet&) const;
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

private:
    RWDBColumn                    column_;
    RWDBExpr                      rightExpr_;
    unsigned long                 valueSize_;
    RWDBPhraseBook::RWDBPhraseKey op_;
};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBMonadicExprImp
//
//  This class implements an expression consisting of a single expression and
//  an operator.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBMonadicExprImp : public RWDBExprImp
{
public:
    RWDBMonadicExprImp();
    RWDBMonadicExprImp(RWDBPhraseBook::RWDBPhraseKey, const RWDBExpr&);
    virtual ~RWDBMonadicExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    virtual void tableTagExpr(RWSet&) const;
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

private:
    RWDBExpr theExpr_;
    RWDBPhraseBook::RWDBPhraseKey op_;

};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBTableExprImp
//
//  This class implements a column encapsulated in an expression.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBTableExprImp : public RWDBExprImp
{
public:
    RWDBTableExprImp(const RWDBTable&);
    virtual ~RWDBTableExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

private:
    RWDBTable theTable_;
};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBColumnExprImp
//
//  This class implements a column encapsulated in an expression.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBColumnExprImp : public RWDBExprImp
{

public:
    RWDBColumnExprImp(const RWDBColumn&);
    virtual ~RWDBColumnExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    //virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    //defined by base class
    virtual void tableTagExpr(RWSet&) const;
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

    //Accessor method
    RWDBColumn& column();

private:

    RWDBColumn theColumn_;
};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBFormSubstitutionExprImp
//
//  This class implements a special type of expression that can use
//  several expressions substituted into a string.  For example: if
//  there are two expressions:
//    (COL1 + 14)
//    (COL2 * 3.1415)
//  and the format string is of the form:
//    MAX(%0, %1)
//  an instance of this class will produce:
//    MAX(COL1 + 14, COL2 * 3.1415)
//  when the asString member function is invoked.
//
//  Components:
//    exprs_ - an array of RWDBExpr instances that will be used in the
//             substitution.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBFormSubstitutionExprImp : public RWDBExprImp
{
public:
    RWDBFormSubstitutionExprImp(
        const RWDBExpr* = 0, const RWDBExpr* = 0,
        const RWDBExpr* = 0, const RWDBExpr* = 0);
    virtual ~RWDBFormSubstitutionExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    //virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    //defined by base class
    virtual void tableTagExpr(RWSet&) const;
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

protected:
    virtual RWCString getForm(const RWDBPhraseBook&) const = 0;

private:
    RWDBExpr exprs_[4];

};

////////////////////////////////////////////////////////////////////////////
//
// RWDBJoinExprImp
// Used for constructing outer join expression
//
////////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBJoinExprImp : public RWDBExprImp
{

public :
    RWDBJoinExprImp(RWDBPhraseBook::RWDBPhraseKey pk,
                    const RWDBExpr* x1, const RWDBExpr* x2,
                    RWDBPhraseBook::RWDBPhraseKey precedenceBegin =
                        RWDBPhraseBook::singleSpace,
                    RWDBPhraseBook::RWDBPhraseKey precedenceEnd =
                        RWDBPhraseBook::singleSpace);
    virtual ~RWDBJoinExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWClassID isA() const;

    // Methods for setting ON/USING clauses
    virtual void on(const RWDBColumn& joinColumn);
    virtual void on(const RWDBCriterion& joinCriterion);

    // Accessor methods
    virtual RWDBPhraseBook::RWDBPhraseKey joinOperator() const;
    RWOrdered& columnList() ;
    RWDBCriterion& criterion() ;
    void joinOperator(RWDBPhraseBook::RWDBPhraseKey joinOp);
    RWDBExpr& expr1() ;
    RWDBExpr& expr2() ;

    // Method to remove those tables from the passed in RWSet which
    // constitute self
    void removeTables(RWSet& s) const;

protected:
    RWCString getForm(const RWDBPhraseBook&) const;

    RWOrdered       joinColumnList_;
    RWDBCriterion   joinCriterion_;


private :
    RWDBPhraseBook::RWDBPhraseKey joinOperator_;
    RWDBPhraseBook::RWDBPhraseKey precedenceBegin_;
    RWDBPhraseBook::RWDBPhraseKey precedenceEnd_;

    RWDBExpr exprs_[2];

};


//////////////////////////////////////////////////////////////////////////
//
//  RWDBFunctionExprImp
//
//  This class implements the special case of a RWDBFormSubstitutionExprImp
//  where the substitution string is stored locally in the instance of this
//  class.
//
//  Components:
//    format_ - an RWCString storing the template used in the substitution
//              process.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBFunctionExprImp : public RWDBFormSubstitutionExprImp
{
public:
    RWDBFunctionExprImp(const RWCString&, const RWDBExpr* = 0,
                        const RWDBExpr* = 0, const RWDBExpr* = 0,
                        const RWDBExpr* = 0);
    virtual ~RWDBFunctionExprImp();

    //virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    //defined by base class
    //virtual void tableTagExpr (RWSet&) const; //defined by base class
    virtual RWClassID isA() const;
    // virtual bool isEquivalent(const RWDBExprImp*) const;
    // defined by base class
private:
    RWCString format_;

protected:
    virtual RWCString getForm(const RWDBPhraseBook&) const;

};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBPhraseKeyExprImp
//
//  This class implements the special case of a RWDBFormSubstitutionExprImp
//  where the substitution string comes from an instance of RWDBPhraseBook.
//
//  Components:
//    phraseKey - an enum storing the key to the template used in the
//                substitution process.  The actual template string is then
//                fetched from an instance of RWDBPhraseBook.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBPhraseKeyExprImp : public RWDBFormSubstitutionExprImp
{
public:
    RWDBPhraseKeyExprImp(RWDBPhraseBook::RWDBPhraseKey,
                         const RWDBExpr* = 0,
                         const RWDBExpr* = 0, const RWDBExpr* = 0,
                         const RWDBExpr* = 0);
    virtual ~RWDBPhraseKeyExprImp();

    virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    //virtual void tableTagExpr (RWSet&) const;   //defined by base class
    virtual RWClassID isA() const;
    // virtual bool isEquivalent(const RWDBExprImp*) const;
    // defined by base class
protected:
    RWCString getForm(const RWDBPhraseBook& aPhraseBook) const;

private:
    RWDBPhraseBook::RWDBPhraseKey phraseKey_;
};


//////////////////////////////////////////////////////////////////////////
//
//  RWDBValueExprImp
//
//  This class implements an RWDBValue encapsulated in an expression. Ie,
//  a literal.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBValueExprImp : public RWDBExprImp, public RWDBValue
{
public:
    RWDBValueExprImp(const RWDBValue& v, bool b = true);
    RWDBValueExprImp(char v);
    RWDBValueExprImp(unsigned char v);
    RWDBValueExprImp(short v);
    RWDBValueExprImp(unsigned short v);
    RWDBValueExprImp(int v);
    RWDBValueExprImp(unsigned int v);
    RWDBValueExprImp(long int v);
    RWDBValueExprImp(unsigned long int v);
    RWDBValueExprImp(long long v);
    RWDBValueExprImp(unsigned long long v);
    RWDBValueExprImp(float v);
    RWDBValueExprImp(double v);
    RWDBValueExprImp(long double v);
    virtual ~RWDBValueExprImp();

    virtual int                 nativeType() const;
    virtual void                setNativeType(int nativeType);

    virtual RWDBValue::ValueType type();
    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString&,
                          RWDBStatementImp* stmt = 0) const;

    //virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    //defined by base class
    //virtual void tableTagExpr (RWSet&) const;   //defined by base class
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

    bool usePhraseBook() const;

protected:
    // These functions inherited from RWDBValue, but must be
    // overridden to avoid warnings
    RWCString asString() const;
    RWCString asString(const RWDBPhraseBook& phrasebook) const;
private:
    bool usePhraseBook_;
    int nativeType_;
};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBCollectionExprImp
//
//  This class implements an RWCollection encapsulated in an expression.
//  The collection is assumed to contain RWDBCollectableExpr instances.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBCollectionExprImp : public RWDBExprImp
{
public:
    RWDBCollectionExprImp(const RWCollection& c);
    virtual ~RWDBCollectionExprImp();

    virtual void                   asString(const RWDBPhraseBook&,
                                            const RWZone& timeZone,
                                            RWDBExpr::AsStringControlFlag,
                                            RWCString&,
                                            RWDBStatementImp* stmt = 0) const;
    virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    virtual void                  tableTagExpr(RWSet&) const;
    virtual RWClassID             isA() const;
    virtual bool                  isEquivalent(const RWDBExprImp*) const;

private:
    const RWCollection& theCollection_;
};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBSelectorExprImp
//
//  This class implements an RWDBSelector encapsulated in an expression.
//  Its main purpose is to support the notion of the sub-select.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBSelectorExprImp : public RWDBExprImp
{
public:
    RWDBSelectorExprImp(const RWDBSelectorBase&);
    virtual ~RWDBSelectorExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString&,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    //virtual void tableTagExpr (RWSet&) const;   //defined by base class
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

private:
    RWDBSelectorBase theSelector_;

};

//////////////////////////////////////////////////////////////////////////
//
//  RWDBSchemaExprImp
//
//  This class implements an RWDBSchema encapsulated in an expression.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBSchemaExprImp : public RWDBExprImp
{
public:
    RWDBSchemaExprImp(const RWDBSchema& s);
    virtual ~RWDBSchemaExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString&,
                          RWDBStatementImp* stmt = 0) const;

    //virtual RWDBPhraseBook::RWDBPhraseKey getOperator() const;
    //defined by base class
    //virtual void tableTagExpr (RWSet&) const;
    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

private:
    const RWDBSchema theSchema_;
};

//////////////////////////////////////////////////////////////////////////
//
// class RWDBBoundExprImp
//
// This class provides users with the ability to the binding ability of
// the underlying Database.
//
//////////////////////////////////////////////////////////////////////////
class RWDBBoundExprImp : public RWDBExprImp
{
public:
    RWDBBoundExprImp(RWDBAbstractBuffer* boundBuffer);

    virtual ~RWDBBoundExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

    RWDBAbstractBuffer*   boundBuffer() const;

protected:
    RWTScopedPointer<RWDBAbstractBuffer> boundBuffer_;
};


//////////////////////////////////////////////////////////////////////////
//
//  RWDBPersistedExprImp
//
//  This class provides an expression implementation after it has been
//  restored from a persisted source.
//
//////////////////////////////////////////////////////////////////////////
class RWDBPersistedExprImp : public RWDBExprImp
{
public:
    RWDBPersistedExprImp(const RWCString& str);
    virtual ~RWDBPersistedExprImp();

    virtual void asString(const RWDBPhraseBook&,
                          const RWZone& timeZone,
                          RWDBExpr::AsStringControlFlag,
                          RWCString& retString,
                          RWDBStatementImp* stmt = 0) const;

    virtual RWClassID isA() const;
    virtual bool isEquivalent(const RWDBExprImp*) const;

private:
    RWCString template_;
};


#endif
