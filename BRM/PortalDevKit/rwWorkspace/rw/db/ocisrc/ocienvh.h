#ifndef __RWDB_OCIENVH_H__
#define __RWDB_OCIENVH_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocienvh.h#1 $
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
 * RWDBEnvironmentHandle specialization for OCI Access Module
 *
 **************************************************************************/

#include <rw/db/ocisrc/rwoci.h>
#include <rw/db/envhandl.h>
#include <rw/db/status.h>
#include <rw/cstring.h>


/**
 * \ingroup oci_access_module
 *
 * \brief
 * Provides methods for setting and retrieving certain connect time and
 * configuration parameters with Oracle OCI.
 *
 * Class RWDBOCIEnvironmentHandle provides methods for setting and
 * retrieving certain connect time and configuration parameters.
 *
 * \note
 * Use of this class reduces an application's portability.
 *
 * \synopsis
 * #include <rw/db/ocisrc/ocienvh.h>
 *
 * RWDBOCIEnvironmentHandle* env =
 *       (RWDBOCIEnvironmentHandle*)myDatabase.environmentHandle();
 * \endsynopsis
 */
class RWDB_ACCESS_GLOBAL RWDBOCIEnvironmentHandle
    : public RWDBEnvironmentHandle
{

public:

    RWDBOCIEnvironmentHandle(RWDBStatus& status);
    virtual
    ~RWDBOCIEnvironmentHandle();

    /**
     * Returns \c true if a higher-performance version of
     * RWDBTable::foreignKeys() is used, \c false otherwise. The default
     * value is \c false.
     */
    bool             foreignKeysFromView();

    /**
     * Sets whether the higher-performance version of
     * RWDBTable::foreignKeys() should be used. A \a value is \c true
     * enables the higher-performance version. The default is \c false to
     * enable the standard version.
     *
     * The higher-performance version is implemented by installing a stored
     * procedure in the database for quicker system table queries. Returns
     * the previous value.
     */
    bool             foreignKeysFromView(bool value);

    /**
     * Returns \c true if \c TIMESTAMP should be used for both table
     * creation and sending and receiving data, otherwise returns \c false.
     * The default value is \c true.
     */
    bool             useTimestamp() const
    {
        return useTimestamp_;
    }

    /**
     * Sets the type used for table creation or sending and receiving data.
     * If \a value is \c true, the \c TIMESTAMP type is used, otherwise
     * \c DATE is used.
     *
     * \note
     * Be careful to maintain the same \c TIMESTAMP setting on an object
     * between executions; changing the setting while the object is still in
     * scope does not have an effect.
     */
    bool             useTimestamp(bool value)
    {
        bool oldVal = useTimestamp_;
        useTimestamp_ = value;
        return oldVal;
    }

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 5, this can be achieved by setting the native types
     * in the table's RWDBSchema. See the table "Type mapping when creating
     * tables" in the Section "Datatypes" in the <em>DB Access Module for
     * Oracle OCI User's Guide</em>.
     *
     * Returns \c true if, when creating tables, a \c Locator column is
     * associated with an RWDBColumn that has an RWDBValue::ValueType of
     * \ref RWDBValue::String "String". The default value is \c false.
     */
    RW_DEPRECATE_FUNC("Set the native type in the table's RWDBSchema")
    bool             ociLocatorForDefaultString();
#endif

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 5, this can be achieved by setting the native types
     * in the table's RWDBSchema. See the table "Type mapping when creating
     * tables" in the Section "Datatypes" in the <em>DB Access Module for
     * Oracle OCI User's Guide</em>.
     *
     * When creating tables, sets the flag for controlling whether or not a
     * \c Locator column is associated with an RWDBColumn that has an
     * RWDBValue::ValueType of \ref RWDBValue::String "String".
     *
     * This method was previously used to distinguish between Oracle server
     * types \c LONG and \c CLOB during the creation of tables.
     */
    RW_DEPRECATE_FUNC("Set the native type in the table's RWDBSchema")
    void                  ociLocatorForDefaultString(bool);
#endif

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 5, this can be achieved by setting the native types
     * in the table's RWDBSchema. See the table "Type mapping when creating
     * tables" in the Section "Datatypes" in the <em>DB Access Module for
     * Oracle OCI User's Guide</em>.
     *
     * Returns \c true if, when creating tables, a \c Locator column is
     * associated with an RWDBColumn that has an RWDBValue::ValueType of
     * \ref RWDBValue::Blob "Blob". The default value is \c false.
     *
     * This method was previously used to distinguish between Oracle server
     * types \c RAW and \c BLOB during the creation of tables.
     */
    RW_DEPRECATE_FUNC("Set the native type in the table's RWDBSchema")
    bool             ociLocatorForDefaultBlob();
#endif

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 5, this can be achieved by setting the native types
     * in the table's RWDBSchema. See the table "Type mapping when creating
     * tables" in the Section "Datatypes" in the <em>DB Access Module for
     * Oracle OCI User's Guide</em>.
     *
     * When creating tables, sets the flag for controlling whether or not a
     * \c Locator column is associated with an RWDBColumn that has an
     * RWDBValue::ValueType of \ref RWDBValue::Blob "Blob".
     *
     * This method was previously used to distinguish between Oracle server
     * types \c RAW and \c BLOB during the creation of tables.
     */
    RW_DEPRECATE_FUNC("Set the native type in the table's RWDBSchema")
    void                  ociLocatorForDefaultBlob(bool);
#endif

    OCIEnv*                ociEnvh();

    //For internal use only:
    virtual void initialize();
    virtual const
    RWDBBufferFactory&    bufferFactory() const;

protected:
    OCIEnv*                ociEnvh_;
    RWDBStatus            status_;

private:
    // Not implemented
    RWDBOCIEnvironmentHandle(const RWDBOCIEnvironmentHandle&);
    RWDBOCIEnvironmentHandle&
    operator=(const RWDBOCIEnvironmentHandle&);

    bool             foreignKeysFromView_;
    bool             ociLocatorForDefaultString_;
    bool             ociLocatorForDefaultBlob_;

    // Provided for using DATE datatype with Oracle 9 and later.
    // SourcePro DB Defaults to TIMESTAMP which causes failures with
    // older servers. Defaults to true
    bool             useTimestamp_;
};


#endif //  __RWDB_OCIENVH_H__
