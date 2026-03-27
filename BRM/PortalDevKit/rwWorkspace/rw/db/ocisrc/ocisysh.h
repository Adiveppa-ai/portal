#ifndef __RWDB_OCISYSH_H__
#define __RWDB_OCISYSH_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocisysh.h#1 $
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
 * Oracle OCI Access Module implementation of RWDBSystemHandle
 *
 **************************************************************************/

#include <rw/db/ocisrc/ocidbtab.h>
#include <rw/db/ocisrc/rwoci.h>
#include <rw/db/connect.h>
#include <rw/db/syshandl.h>
#include <rw/cstring.h>
#include <rw/tvordvec.h>


/**
 * \ingroup oci_access_module
 *
 * \brief
 * Provides a mechanism for making direct calls to the Oracle OCI API, and
 * some methods for setting access module-specific properties.
 *
 * Class RWDBOCISystemHandle provides methods for setting and retrieving
 * options that affect performance. It also contains the OCI handles
 * \c OCIError, \c OCIEnv, \c OCISvcCtx, and \c OCIServer used by the
 * RWDBConnection.
 *
 * \note
 * Use of this class reduces an application's portability.
 *
 * \synopsis
 * #include <rw/db/ocisrc/ocisysh.h>
 *
 * RWDBOCISystemHandle* sys =
 *       (RWDBOCISystemHandle*)myConnection.systemHandle();
 * \endsynopsis
 *
 * \example
 * If it is necessary for your application to make calls directly to OCI,
 * proceed as in the following example. Please be aware of the complications
 * associated with making direct OCI calls, as the internal logic of the DB
 * Access Module for Oracle OCI is not used. Also note that your application
 * must be compiled with an include path to the include files of the DB
 * Access Module for Oracle OCI.
 * \code
 * #include <rw/db/ocisrc/ocisysh.h>
 * RWDBConnection ociConnect = myDbase.connection();
 * RWDBOCISystemHandle* handle =
 *                (RWDBOCISystemHandle*)ociConnect.systemHandle();
 *
 * OCIEnv* env = handle->ociEnvh();
 * // use the OCIEnv pointer for Oracle OCI calls
 * \endcode
 * \endexample
 */
class RWDB_ACCESS_GLOBAL RWDBOCISystemHandle : public RWDBSystemHandle
{

private:
    // forward declare this nested class
    class RWDBOracleDescriber;

public:
    static const sword RWDB_OCI_INVALID_OBJECT = 24372;
    static const sword RWDB_OCI_OBJECT_DOES_NOT_EXIST = 4043;

    RWDBOCISystemHandle(RWDBEnvironmentHandle* env, RWDBStatus& status);
    virtual
    ~RWDBOCISystemHandle();

    /**
     * Returns the current prefetch row size. The default value is 10.
     */
    ub4        prefetchSize() const
    {
        return rwdbociPrefetchSize_;
    }

    /**
     * Sets the prefetch row size to \a newSize. Returns the previously used
     * prefetch row size.
     *
     * The prefetch row size is used to set the OCI statement attribute
     * \c OCI_ATTR_PREFETCH_ROWS for every execution. This attribute
     * controls the number of rows an Oracle client prefetches from an
     * Oracle server for the result set produced by the query execution. It
     * affects the number of server round trips and has a direct effect on
     * performance.
     */
    ub4        prefetchSize(ub4 newSize)
    {
        ub4 tmp = rwdbociPrefetchSize_;
        rwdbociPrefetchSize_ = newSize;
        return tmp;
    }

    /**
     * Returns the size of chunks, in bytes, used to send or receive large
     * blocks of data (\c LONG, <tt>LONG RAW</tt>, \c CLOB, \c BLOB, or
     * \c SYS.XMLTYPE). The default is 32768.
     */
    size_t     piecewiseSize() const;

    /**
     * When fetching or sending large character or binary data (\c LONG,
     * <tt>LONG RAW</tt>, \c CLOB, \c BLOB, or \c SYS.XMLTYPE), data is sent
     * or received in \a size bytes at a time. Returns the previous setting.
     */
    size_t     piecewiseSize(size_t size);

    /**
     * Returns the size, in bytes (for BLOB) or characters (for CLOB), of
     * LOB data that will be cached by the Oracle client to facilitate
     * faster retrieval of LOB data. The default is 0, meaning this feature
     * is disabled by default.
     *
     * \note
     * This option is only supported on Oracle 11.x clients and newer.
     */
    ub4        lobPrefetchSize() const;

    /**
     * When fetching large character or binary data (\c CLOB or \c BLOB) the
     * Oracle client can cache data to facilitate faster retrieval of LOB
     * columns. Set \a size to the amount of data per row in bytes (for
     * BLOB) or characters (for CLOB) that should be prefetched. Setting
     * \a size to 0 disables prefetching.
     *
     * \note
     * This option is only supported on Oracle 11.x clients and newer. Usage
     * of this method with older Oracle clients will result in a
     * RWDBStatus::invalidUsage error.
     */
    ub4        lobPrefetchSize(ub4 size);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 11, this setting is not used in the DB Access Module
     * for Oracle OCI.
     *
     * Returns the size of the memory buffer used when retrieving
     * large-sized data (<tt>LONG/LONG RAW</tt> or <tt>CLOB/BLOB</tt>). The
     * default size is <tt>32kb - 1</tt>.
     */
    RW_DEPRECATE_FUNC("This function call has no effect and can be safely removed")
    size_t     maximumBlobSize() const;
#endif

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 11, this setting is not used in the DB Access Module
     * for Oracle OCI.
     *
     * Sets the size of the memory buffer used when retrieving large-sized
     * data (<tt>LONG/LONG RAW</tt> or <tt>CLOB/BLOB</tt>). The default size
     * is <tt>32kb - 1</tt>.
     */
    RW_DEPRECATE_FUNC("This function call has no effect and can be safely removed")
    size_t     maximumBlobSize(size_t size);
#endif

    /**
     * Returns a pointer to the \c OCIError encapsulated by the respective
     * RWDBConnection.
     */
    OCIError*   errorHandle();

    /**
     * Returns a pointer to the \c OCIEnv encapsulated by the respective
     * RWDBConnection.
     */
    OCIEnv*     ociEnvh();

    /**
     * Returns a pointer to the \c OCISvcCtx encapsulated by the respective
     * RWDBConnection. Each RWDBConnection maintains a separate
     * \c OCISvcCtx.
     */
    OCISvcCtx*  ociServerContext();

    /**
     * Returns a pointer to the \c OCIServer encapsulated by the respective
     * RWDBConnection.
     */
    OCIServer*  serverHandle();

    // These methods are not for public API.
    // They are used by oracle access module implementation.
    virtual
    void       initialize();

    bool       check(RWDBStatus& s, sword ret);

    virtual
    void       rwopen(const RWCString& user,
                      const RWCString& pass,
                      const RWCString& db,
                      const RWCString& server,
                      RWDBConnection::ConnectionType connType,
                      RWDBDatabaseCallback& dbcb,
                      RWDBStatus& status);
    virtual
    void       rwclose(RWDBStatus& status);

    virtual
    void       commitTransaction(RWDBStatus& status);
    virtual
    void       rollbackTransaction(RWDBStatus& status);

    void       describeStmt(OCIStmt* stmt,
                            RWDBSchema& schema,
                            RWDBStatus& status);
    void       describeTable(const RWCString& name,
                             bool& isView,
                             RWCString& referencedTable,
                             RWDBSchema& schema,
                             RWDBStatus& status,
                             bool setTblNotFoundErr = false);
    void       describeTableName(const RWCString& name,
                                 RWCString& referencedTable,
                                 const bool isView,
                                 RWDBStatus& status);
    void       describeProc(const RWCString& name,
                            bool& isFunction,
                            RWCString& packageName,
                            RWCString& referencedName,
                            RWDBSchema& schema,
                            RWDBStatus& status);
    bool      findTable(const RWCString& name,
                        RWDBStatus& status);

    // Returns the username from the sessionHandle
    RWCString  ociUserName();

protected:

    virtual
    sword      allocateResource();

    void       deallocateResource();

    void       describeParam(OCIParam* param,
                             RWDBColumn& column,
                             RWDBStatus& status);

    bool       describeName(RWCString& name,
                            RWDBOracleDescriber& desc,
                            RWDBStatus& status,
                            ub1& objectType,
                            sword& retCode);

    bool       getPackage(RWCString& object, RWDBStatus& status,
                          bool& isFunction, OCIParam** proc,
                          RWDBOracleDescriber& desc);

    bool       getSynonym(RWCString& newName,
                          RWDBOracleDescriber& desc);

    void       getProcName(const RWCString& name,
                           bool& isFunction,
                           RWCString& packageName,
                           RWCString& referencedName,
                           OCIParam** proc,
                           RWDBStatus& status,
                           RWDBOracleDescriber& desc);

    // Data Members
    bool       opened_;

    OCIEnv*     ociEnv_;       // cached for performance.
    OCIServer*  server_;
    OCISession* session_;
    OCISvcCtx*  ociConn_;
    OCIError*   errorHandle_;

    // Setting prefetch size can give better performance, however it is observed
    // that Oracle returns incorrect data if the prefetch size is set.
    // (RW# 28574)
    ub4         rwdbociPrefetchSize_;

    ub4         lobPrefetchSize_;

    size_t      piecewiseSize_;
    size_t      maximumBlobSize_;

    RWDBStatus& connStatus_;

private:

    bool        resourcesAllocated_;
    RWCString   ociUserName_;

    // not implemented
    RWDBOCISystemHandle(const RWDBOCISystemHandle&);
    RWDBOCISystemHandle& operator=(const RWDBOCISystemHandle&);

    // An embedded class that manages the describe handles
    class RWDBOracleDescriber
    {
    private:
        OCIDescribe*         describe_;
        sword               ret_;
    public:
        RWDBOracleDescriber(OCIEnv* ociEnv)
            : describe_(NULL), ret_(OCI_INVALID_HANDLE)
        {
            ret_ = OCIHandleAlloc(ociEnv, (RWDBOCIdvoidp*)&describe_,
                                  (ub4) OCI_HTYPE_DESCRIBE ,
                                  (size_t) 0, (dvoid**)0);
            if (!isValid()) {
                describe_ = NULL;
            }
        }
        inline sword            getReturnedValue() const
        {
            return ret_;
        }
        inline OCIDescribe*     describeHandle() const
        {
            return describe_;
        }
        inline bool        isValid() const
        {
            return (ret_ == OCI_SUCCESS || ret_ == OCI_SUCCESS_WITH_INFO);
        }
        ~RWDBOracleDescriber()
        {
            if (isValid()) {
                OCIHandleFree(describe_, OCI_HTYPE_DESCRIBE);
            }
        }
    };
    // End of describer class

};


#endif
