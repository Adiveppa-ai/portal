#ifndef __RWDB_COREODBCDEFS_H__
#define __RWDB_COREODBCDEFS_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/coreodbcdefs.h#1 $
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

////////////////////////////////////////////////////////////////////////////////
//
// Following are the #defines for the names of the sql functions that we use
// and typedefs for pointers to SQL function calls. It is not meant to be
// included by any libraries other than the odbc'ish access modules.
//
////////////////////////////////////////////////////////////////////////////////

#define RWDBSQLALLOCHANDLENAME      "SQLAllocHandle"
#define RWDBSQLBINDCOLNAME          "SQLBindCol"
#define RWDBSQLBINDPARAMETERNAME    "SQLBindParameter"
#define RWDBSQLBULKOPERATIONSNAME   "SQLBulkOperations"
#define RWDBSQLCANCELNAME           "SQLCancel"
#define RWDBSQLCLOSECURSORNAME      "SQLCloseCursor"
#define RWDBSQLCOLATTRIBUTENAME     "SQLColAttribute"
#define RWDBSQLCOLUMNSNAME          "SQLColumns"
#define RWDBSQLCONNECTNAME          "SQLConnect"
#define RWDBSQLDESCRIBECOLNAME      "SQLDescribeCol"
#define RWDBSQLDESCRIBEPARAMNAME    "SQLDescribeParam"
#define RWDBSQLDISCONNECTNAME       "SQLDisconnect"
#define RWDBSQLDRIVERCONNECTNAME    "SQLDriverConnect"
#define RWDBSQLENDTRANNAME          "SQLEndTran"
#define RWDBSQLEXECDIRECTNAME       "SQLExecDirect"
#define RWDBSQLEXECUTENAME          "SQLExecute"
#define RWDBSQLFETCHNAME            "SQLFetch"
#define RWDBSQLFETCHSCROLLNAME      "SQLFetchScroll"
#define RWDBSQLFOREIGNKEYSNAME      "SQLForeignKeys"
#define RWDBSQLFREEHANDLENAME       "SQLFreeHandle"
#define RWDBSQLFREESTMTNAME         "SQLFreeStmt"
#define RWDBSQLGETCONNECTATTRNAME   "SQLGetConnectAttr"
#define RWDBSQLGETDATANAME          "SQLGetData"
#define RWDBSQLGETDIAGFIELDNAME     "SQLGetDiagField"
#define RWDBSQLGETDIAGRECNAME       "SQLGetDiagRec"
#define RWDBSQLGETENVATTRNAME       "SQLGetEnvAttr"
#define RWDBSQLGETINFONAME          "SQLGetInfo"
#define RWDBSQLGETSTMTATTRNAME      "SQLGetStmtAttr"
#define RWDBSQLGETTYPEINFONAME      "SQLGetTypeInfo"
#define RWDBSQLMORERESULTSNAME      "SQLMoreResults"
#define RWDBSQLNUMRESULTCOLSNAME    "SQLNumResultCols"
#define RWDBSQLPARAMDATANAME        "SQLParamData"
#define RWDBSQLPREPARENAME          "SQLPrepare"
#define RWDBSQLPRIMARYKEYSNAME      "SQLPrimaryKeys"
#define RWDBSQLPROCEDURECOLUMNSNAME "SQLProcedureColumns"
#define RWDBSQLPROCEDURESNAME       "SQLProcedures"
#define RWDBSQLPUTDATANAME          "SQLPutData"
#define RWDBSQLROWCOUNTNAME         "SQLRowCount"
#define RWDBSQLSETCONNECTATTRNAME   "SQLSetConnectAttr"
#define RWDBSQLSETDESCFIELDNAME     "SQLSetDescField"
#define RWDBSQLSETENVATTRNAME       "SQLSetEnvAttr"
#define RWDBSQLSETPOSNAME           "SQLSetPos"
#define RWDBSQLSETSTMTATTRNAME      "SQLSetStmtAttr"
#define RWDBSQLSTATISTICSNAME       "SQLStatistics"
#define RWDBSQLTABLESNAME           "SQLTables"

extern "C" {
    typedef SQLRETURN(SQL_API* RWDBSQLALLOCHANDLE)
    (SQLSMALLINT, SQLHANDLE, SQLHANDLE*);

    typedef SQLRETURN(SQL_API* RWDBSQLBINDCOL)
    (SQLHSTMT, SQLUSMALLINT, SQLSMALLINT,
     SQLPOINTER, SQLINTEGER, SQLINTEGER*);

    typedef SQLRETURN(SQL_API* RWDBSQLBINDPARAMETER)
    (SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLSMALLINT,
     SQLSMALLINT, SQLUINTEGER, SQLSMALLINT, SQLPOINTER,
     SQLINTEGER, SQLINTEGER*);

    typedef SQLRETURN(SQL_API* RWDBSQLBULKOPERATIONS)
    (SQLHSTMT, SQLUSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLCANCEL)
    (SQLHSTMT);

    typedef SQLRETURN(SQL_API* RWDBSQLCLOSECURSOR)
    (SQLHSTMT);

    typedef SQLRETURN(SQL_API* RWDBSQLCOLATTRIBUTE)
    (SQLHSTMT, SQLUSMALLINT, SQLUSMALLINT, SQLPOINTER,
     SQLSMALLINT, SQLSMALLINT*, SQLPOINTER);

    typedef SQLRETURN(SQL_API* RWDBSQLCOLUMNS)
    (SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT,
     SQLCHAR*, SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLCONNECT)
    (SQLHDBC, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLDESCRIBECOL)
    (SQLHSTMT, SQLUSMALLINT, SQLCHAR*, SQLSMALLINT,
     SQLSMALLINT*, SQLSMALLINT*, SQLUINTEGER*,
     SQLSMALLINT*, SQLSMALLINT*);

    typedef SQLRETURN(SQL_API* RWDBSQLDESCRIBEPARAM)
    (SQLHSTMT, SQLUSMALLINT, SQLSMALLINT*,
     SQLUINTEGER*, SQLSMALLINT*, SQLSMALLINT*);

    typedef SQLRETURN(SQL_API* RWDBSQLDISCONNECT)
    (SQLHDBC);

    typedef SQLRETURN(SQL_API* RWDBSQLDRIVERCONNECT)
    (SQLHDBC, SQLHWND, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLSMALLINT*, SQLUSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLENDTRAN)
    (SQLSMALLINT, SQLHANDLE, SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLEXECDIRECT)
    (SQLHSTMT, SQLCHAR*, SQLINTEGER);

    typedef SQLRETURN(SQL_API* RWDBSQLEXECUTE)
    (SQLHSTMT);

    typedef SQLRETURN(SQL_API* RWDBSQLFETCH)
    (SQLHSTMT);

    typedef SQLRETURN(SQL_API* RWDBSQLFETCHSCROLL)
    (SQLHSTMT, SQLSMALLINT, SQLINTEGER);

    typedef SQLRETURN(SQL_API* RWDBSQLFOREIGNKEYS)
    (SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT,
     SQLCHAR*, SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLFREEHANDLE)
    (SQLSMALLINT, SQLHANDLE);

    typedef SQLRETURN(SQL_API* RWDBSQLFREESTMT)
    (SQLHSTMT, SQLUSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLGETCONNECTATTR)
    (SQLHDBC, SQLINTEGER, SQLPOINTER,
     SQLINTEGER, SQLINTEGER*);

    typedef SQLRETURN(SQL_API* RWDBSQLGETDATA)
    (SQLHSTMT, SQLUSMALLINT, SQLSMALLINT,
     SQLPOINTER, SQLINTEGER, SQLINTEGER*);

    typedef SQLRETURN(SQL_API* RWDBSQLGETDIAGFIELD)
    (SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLSMALLINT,
     SQLPOINTER, SQLSMALLINT, SQLSMALLINT*);

    typedef SQLRETURN(SQL_API* RWDBSQLGETDIAGREC)
    (SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLCHAR*,
     SQLINTEGER*, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*);

    typedef SQLRETURN(SQL_API* RWDBSQLGETENVATTR)
    (SQLHENV, SQLINTEGER, SQLPOINTER,
     SQLINTEGER, SQLINTEGER*);

    typedef SQLRETURN(SQL_API* RWDBSQLGETINFO)
    (SQLHDBC, SQLUSMALLINT, SQLPOINTER,
     SQLSMALLINT, SQLSMALLINT*);

    typedef SQLRETURN(SQL_API* RWDBSQLGETSTMTATTR)
    (SQLHSTMT, SQLINTEGER, SQLPOINTER,
     SQLINTEGER, SQLINTEGER*);

    typedef SQLRETURN(SQL_API* RWDBSQLGETTYPEINFO)
    (SQLHSTMT, SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLMORERESULTS)
    (SQLHSTMT);

    typedef SQLRETURN(SQL_API* RWDBSQLNUMRESULTCOLS)
    (SQLHSTMT, SQLSMALLINT*);

    typedef SQLRETURN(SQL_API* RWDBSQLPARAMDATA)
    (SQLHSTMT, SQLPOINTER*);

    typedef SQLRETURN(SQL_API* RWDBSQLPREPARE)
    (SQLHSTMT, SQLCHAR*, SQLINTEGER);

    typedef SQLRETURN(SQL_API* RWDBSQLPRIMARYKEYS)
    (SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLPROCEDURECOLUMNS)
    (SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLPROCEDURES)
    (SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLPUTDATA)
    (SQLHSTMT, SQLPOINTER, SQLLEN);

    typedef SQLRETURN(SQL_API* RWDBSQLROWCOUNT)
    (SQLHSTMT, SQLINTEGER*);

    typedef SQLRETURN(SQL_API* RWDBSQLSETCONNECTATTR)
    (SQLHDBC, SQLINTEGER, SQLPOINTER, SQLINTEGER);

    typedef SQLRETURN(SQL_API* RWDBSQLSETDESCFIELD)
    (SQLHDESC, SQLSMALLINT, SQLSMALLINT,
     SQLPOINTER, SQLINTEGER);

    typedef SQLRETURN(SQL_API* RWDBSQLSETENVATTR)
    (SQLHENV, SQLINTEGER, SQLPOINTER, SQLINTEGER);

    typedef SQLRETURN(SQL_API* RWDBSQLSETPOS)
    (SQLHSTMT, SQLUSMALLINT, SQLUSMALLINT,
     SQLUSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLSETSTMTATTR)
    (SQLHSTMT, SQLINTEGER, SQLPOINTER, SQLINTEGER);

    typedef SQLRETURN(SQL_API* RWDBSQLSTATISTICS)
    (SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT,
     SQLUSMALLINT, SQLUSMALLINT);

    typedef SQLRETURN(SQL_API* RWDBSQLTABLES)
    (SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLCHAR*,
     SQLSMALLINT);
}

#endif // __RWDB_COREODBCDEFS_H__
