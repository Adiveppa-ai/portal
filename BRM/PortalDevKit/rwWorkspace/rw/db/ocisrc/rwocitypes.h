#ifndef __RWDB_RWOCITYPES_H__
#define __RWDB_RWOCITYPES_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/rwocitypes.h#1 $
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
 **************************************************************************
 *
 * Oracle OCI Access Module Data mapping.
 *
 **************************************************************************/

/******************************************************************************
        Oracle Datatypes and Mapping
            -- See Programmer's Guide to OCI: ch.3

Internal Datatype:  used for Oracle database table.
External Datatype:  used for SQLPLUS, PL/SQL, OCI.
C- Datatype:        user C or C++ host variable type.

(i)     Internal Datatype is the subset of External Datatype and it is the type
        we have to map into C-type accordingly except:
(ii)    There are some useful C-types which are not the Internal Datatype. we
        have to map these types into Internal Datatypes by rw rule.
(iii)   External Datatypes are the by pass types.

_____________________________________________________________________

I type      Maximum-Length  Code    OCI-CONST       C-TYPE

NUMBER      21 bytes        2       SQLT_NUM        unsigned char[n]

ROWID       10 bytes        11      SQLT_RDD        char[30]
DATE        7 bytes         12      SQLT_DAT        oci_date
TIMESTAMP   <N/A>           187     SQLT_TIMESTAMP  OCIDateTime
MLSLABEL    255 bytes       105     SQLT_LAB        char[n]

CHAR(n)     2000 bytes      96      SQLT_AFC        char[n]
RAW(n)      2000 bytes      23      SQLT_BIN        unsigned char[n]
VARCHAR2(n) 4000 bytes      1       SQLT_CHR        char[n]
LONG        2^31 - 1 bytes  8       SQLT_LNG        char[n]
LONG RAW    2^31 - 1 bytes  24      SQLT_LBI        unsigned char[n]

UDT         <N/A>           108     SQLT_NTY        struct
REF         <N/A>           110     SQLT_REF        OCIRef
CLOB        <N/A>           112     SQLT_CLOB       OCILobLocator
BLOB        <N/A>           113     SQLT_BLOB       OCILobLocator

Note: for Oracle 7 server, RAW is <255 bytes and VARCHAR2 is <2000 bytes.
    This effects only IN type binding and mapping because we have to
    know the server information to be able to create proper type.
_____________________________________________________________________


Table 1: IN type mapping and binding (from client to database).
_____________________________________________________________________
USER-TYPE        E-TYPE      OCI-CONST       I-TYPE

Char,
UnsignedChar     NUMBER      SQLT_NUM        NUMBER(3,0)

Short,
Int,
Long             INTEGER     SQLT_INT        NUMBER(p,0) p is OS based size

LongLong         NUMBER      SQLT_CHR        NUMBER(p,0) p < 20

UnsignedShort,
UnsignedInt,
UnsignedLong     INTEGER     SQLT_UIN        NUMBER(p,0)

UnsignedLonglong NUMBER     SQLT_CHR         NUMBER(p,0) p < 20

Float,
Double           FLOAT       SQLT_FLT        FLOAT(126)

Date             oci_date    SQLT_DAT        char(7)

DateTime         OCIDateTime SQLT_TIMESTAMP  TIMESTAMP

Duration         N/A

Decimal          NUMBER      SQLT_CHR        char(21)

String(n)        VARCHAR2    SQLT_CHR        VARCHAR2(n) n < 4000
                 LONG        SQLT_LNG        LONG        n >= 4000

Blob(n)          RAW         SQLT_BIN        RAW         n < 2000
                 LONG RAW    SQLT_LBI        LONG RAW    n >= 2000

MBString,
WString          NVARCHAR2   SQLT_CHR
_____________________________________________________________________



Table 2: OUT type mapping and binding (from database to client).
_____________________________________________________________________
I-TYPE      OCI-CONST           C-TYPE

NUMBER(p,s) SQLT_NUM            long, s=0, p fits digits per long
                                long long, s=0, p=19.
                                double, s=129
                                char[21], otherwise

ROWID       SQLT_RDD            char[30]
DATE        SQLT_DAT            oci_date
TIMESTAMP   SQLT_TIMESTAMP      OCIDateTime
MLSLABEL    SQLT_LAB            char[255]   // fixed length (like rowid).

CHAR(n)     SQLT_AFC            char[n]
RAW(n)      SQLT_BIN            unsigned char[n]
VARCHAR2(n) SQLT_CHR            char[n]
LONG        SQLT_LNG            char[n]
LONG RAW    SQLT_LBI            unsigned char[n]

UDT         SQLT_NTY            struct
REF         SQLT_REF            OCIRef
CLOB        SQLT_CLOB           OCILobLocator
BLOB        SQLT_BLOB           OCILobLocator

_____________________________________________________________________

******************************************************************************/

#include <rw/db/ocisrc/rwoci.h>
#include <rw/db/adapter.h>
#include <rw/db/coretypes.h>

static const int RWDB_OCI_MLS_LABEL_SIZE = 20;
static const int RWDB_OCI_ROW_ID_SIZE    = 30;

static const size_t RWDB_OCI_PIECEWISE_SIZE = 32768;
static const size_t RWDB_OCI_MAX_BLOB_SIZE  = 32767;

static const int RWDB_OCI_MAXVARCHAR2    = 4000;
static const int RWDB_OCI_MAXNVARCHAR2   = 2000;
static const int RWDB_OCI_MAXRAW         = 2000;

///////////////////////////////////////////////////////////////////////////
//
// class RWDBOCIAdapter
//
// Adapts Buffers to Oracle OCI
//
///////////////////////////////////////////////////////////////////////////
class RWDBOCIHandleImp;
class RWDBBuffer;

class RWDBOCIAdapter : public RWDBAdapter
{
protected:
    OCIDefine*               defineHandle_; // Set for output defines
    OCIBind*                 bindHandle_; // set for input binds
public:
    RWDBOCIAdapter(RWDBAdapterFactory* id, RWDBBuffer* coreBuffer)
        : RWDBAdapter(id, coreBuffer)
        , defineHandle_(NULL)
        , bindHandle_(NULL)
    {
    }

    virtual ~RWDBOCIAdapter() {}

    // Binds as a parameter
    // Set asPLSQLArray to true if this is being bound into a PL/SQL Array
    // parameter.
    virtual sword bindByPos(RWDBOCIHandleImp* ocih,
                            ub4 position, bool asPLSQLArray = false) = 0;

    // Call this after OCIStmtExecute() to have the adapter send it's data,
    // if applicable.
    virtual sword sendData(size_t)
    {
        return OCI_SUCCESS;
    }

    // Call this after OCIStmtExecte() returns OCI_NEED_DATA with a user callback
    virtual bool insertData(RWDBOCIHandleImp*, OCIBind*, ub4, ub1, ub4, sword&, ub4)
    {
        return true;
    }

    // Call this before OCIStmtFetch2 to set piece info for user callback adapters
    virtual void setFetchPiece(OCIError*, ub1)
    {
        ;
    }

    virtual bool onFetch(size_t, bool&)
    {
        return true;
    }

    // Binds ("defines") as an output column
    virtual sword defineByPos(RWDBOCIHandleImp* ocih, ub4 position) = 0;

    virtual OCIDefine* defineHandle() const
    {
        return defineHandle_;
    }
};


///////////////////////////////////////////////////////////////////////////
//
// class RWDBOCIAdapterFactory
//
// Constructs adapters for OCI
//
///////////////////////////////////////////////////////////////////////////
class RWDBOCIAdapterFactory : public RWDBAdapterFactory
{
public:
    // The true passed to the base class means each OCIAdapterFactory
    // instance should be considered unique.
    RWDBOCIAdapterFactory(const RWDBConnection& cn);
    virtual ~RWDBOCIAdapterFactory();

    RWDBConnectionImp* connImp() const
    {
        return connImp_;
    }

private:
    // NOT allowed as the factory requires its OCIEnv member to be initialized.
    RWDBOCIAdapterFactory();

    virtual RWDBAdapter* make(RWDBBuffer* coreBuffer);

    RWDBConnectionImp* connImp_;
    OCIError*   err_;
    OCIEnv*     env_;
    bool   useTimestamp_;
};


class RWDBOCIConstants
{
public:
    static const int MAX_DECDIGITS_CHAR_;
    static const int MAX_DECDIGITS_SHORT_;
    static const int MAX_DECDIGITS_INT_;
    static const int MAX_DECDIGITS_LONG_;
    static const int MAX_DECDIGITS_LONGLONG_;
};

class RWDBOCIValueTypeMapping
{
public:
    static RWDBValue::ValueType detect(int nativeType,
                                       ub2 precision = 0,
                                       sb1 scale = 0,
                                       ub1 ncharTypeInfo = 0,
                                       int columnType = 0);

    static sb4 calculateDecimalWidth(int precision, int scale);
};

#endif // __RWDB_RWOCITYPES_H__
