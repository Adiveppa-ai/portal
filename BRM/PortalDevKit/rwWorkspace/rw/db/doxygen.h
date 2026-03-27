#ifndef rw_db_doxygen_h__
#define rw_db_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup sourcepro_db_product SourcePro DB
 *
 * SourcePro DB provides a single interface for database operations related
 * to any supported database. This interface is expressed through the DB
 * Interface Module. The database access modules then express this interface
 * in the syntax required by the specific database.
 */

/**
 * \defgroup db_interface_module DB Interface Module
 * \ingroup sourcepro_db_product
 *
 * The DB Interface Module provides the classes you need for data
 * manipulation, error handling, expression formation, database connection,
 * and database portability. To help you to navigate these classes more
 * easily, they are organized into groups.
 */

/**
 * \defgroup db_common_group Databases
 * \ingroup db_interface_module
 *
 * The Database Classes encapsulate common database objects. All of these
 * classes are contained in the DB Interface Module, and explained in the
 * <em>DB Interface Module User's Guide</em>.
 */

/**
 * \defgroup db_data_types_group Data Types
 * \ingroup db_interface_module
 *
 * The DB Interface Module normalizes data types between applications and
 * vendor databases. In the process, it uses several kinds of data types:
 *
 * - the primitive C++ data types
 * - data types from the Essential Tools Module, including RWCString,
 * RWWString, RWBasicUString, RWDate, RWDateTime, RWDecimalPortable, and
 * RWTime.
 * - data types it defines
 *
 * The data types defined by the DB Interface Module are listed in this
 * group. See the <em>DB Interface Module User's Guide</em> for more
 * information on the data model of the DB Interface Module.
 */

/**
 * \defgroup db_data_manipulation_group Data Manipulation
 * \ingroup db_interface_module
 *
 * The Data Manipulation Classes encapsulate common database operations.
 * These classes are contained in the DB Interface Module, and explained in
 * the <em>DB Interface Module User's Guide</em>.
 */

/**
 * \defgroup db_expression_group Expressions
 * \ingroup db_interface_module
 *
 * Class RWDBExpr is a base class for a family of classes that allow you to
 * program SQL expressions in C++. Additional classes in this category
 * include RWDBAssignment, RWDBCriterion, RWDBCollectableExpr,
 * RWDBBoundExpr, and RWDBJoinExpr. The <em>DB Interface Module User's
 * Guide</em> contains examples of using these classes.
 *
 * The DB Interface Module also provides an extensible mechanism for
 * defining SQL expressions for your specific needs. The classes
 * RWDBExprFormDefinition, RWDBExprFuncDef0, RWDBExprFuncDef1,
 * RWDBExprFuncDef2, RWDBExprFuncDef3, RWDBExprFuncDef4,
 * RWDBCritFormDefinition, and RWDBCritFuncDef0, RWDBCritFuncDef1,
 * RWDBCritFuncDef2, RWDBCritFuncDef3, RWDBCritFuncDef4 support this
 * mechanism.
 */

/**
 * \defgroup db_bulk_operations_group Bulk Operations
 * \ingroup db_interface_module
 *
 * The DB Interface Module provides the alternative classes RWDBBulkReader
 * and RWDBBulkInserter and related classes to help improve application
 * performance. RWDBBulkReader and RWDBBulkInserter implement reading and
 * inserting (writing) directly from arrays supplied by an application.
 * Examples using the Bulk Classes are described in the <em>DB Interface
 * Module User's Guide</em>.
 */

/**
 * \defgroup db_execution_callbacks_group Callbacks
 * \ingroup db_interface_module
 *
 * The DB Interface Module offers execution of your code at various places
 * using callbacks. It provides the capability to customize your
 * applications at both the database and the connection level as needed.
 *
 * Applications can use callbacks for specific purposes such as enabling
 * login authentication mechanisms (for example, Kerberos), or configuring
 * data encryption between the database client and server, or simply to set
 * a database property. Callbacks may be used to execute any user code,
 * whether database related or not, at the callback points in SourcePro DB.
 */

/**
 * \defgroup db_open_sql_group Open SQL
 * \ingroup db_interface_module
 *
 * The Open SQL interface contains three classes that give you direct
 * control over the execution of SQL statements and the data that is bound
 * to them. The Open SQL interface is described in detail in the <em>DB
 * Interface Module User's Guide</em>.
 */

/**
 * \defgroup db_utility_and_diagnostics_group Utilities and Diagnostics
 * \ingroup db_interface_module
 *
 * The Utility and Diagnostics Classes provide specific kinds of
 * functionality. For example, every DB Access Module contains an instance
 * of a class derived from RWDBPhraseBook, which is a list of SQL phrases in
 * the dialect of a specific database. Classes RWDBMemTable and
 * RWDBTPtrMemTable provide ways to store relational data in program memory.
 */

/**
 * \defgroup db_access_modules Access Module System and Environment Handles
 * \ingroup sourcepro_db_product
 *
 * The access modules do not have their own interface; they simply adapt the
 * interface of the DB Interface Module to a specific database. However,
 * each access module does provide classes for accessing system and
 * environment variables.
 */

/**
 * \defgroup msq_access_module DB Access Module for Microsoft SQL Server
 * \ingroup db_access_modules
 */

/**
 * \defgroup oci_access_module DB Access Module for Oracle OCI
 * \ingroup db_access_modules
 */

/**
 * \defgroup ctl_access_module DB Access Module for Sybase
 * \ingroup db_access_modules
 */

/**
 * \defgroup db2_access_module DB Access Module for DB2 CLI
 * \ingroup db_access_modules
 */

/**
 * \defgroup mys_access_module DB Access Module for MySQL
 * \ingroup db_access_modules
 */

/**
 * \defgroup pgs_access_module DB Access Module for PostgreSQL
 * \ingroup db_access_modules
 */

/**
 * \defgroup odb_access_modules DB Access Module for ODBC
 * \ingroup db_access_modules
 */

#endif // rw_db_doxygen_h__ 
