#ifndef IXT_DBEXTENSION_HPP
#define IXT_DBEXTENSION_HPP

//==============================================================================
//
//      @(#)%Portal Version: DbExtension.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:19 %
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Extension. This class is the iScript
//   database extension.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: Extension.hpp,v $
// $Revision: 1.5 $
// $Author: sd $
// $Date: 2001/08/23 13:41:25 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Extension.hpp,v $
// Revision 1.5  2001/08/23 13:41:25  sd
// - PETS #38557 - Transaction handling added
//
// Revision 1.4  2000/09/26 13:34:06  sd
// - Interface changed for the new internal iScript interface.
//
// Revision 1.3  2000/08/29 07:46:33  sd
// - Implementation changed to support the IBM compiler
// - The first result in a dbresult is fetched automatically.
//
// Revision 1.2  2000/08/23 15:51:43  sd
// - Modifications to support iScript with hash and array values.
//
// Revision 1.1  2000/08/21 14:51:14  sd
// - Initial revision.
//
//==============================================================================

#include <rw/tpmap.h>
#include "SCR/Variable.hpp"
#include "SCR/Extension.hpp"
#include "IXT/DbResultHandle.hpp"
#include <rw/db/connect.h>

class RWDBResult;
// Forward declaration
namespace DBC
{
class DatabasePlugIn;
}


/** <b><tt>Extension</tt></b> is the iScript extension class for database
 *  access.
 *
 */
namespace IXT 
{
namespace Db 
{
class Extension : public SCR::Extension
{
  D_SINGLETHREADED

  public:

    /**@name Extension constructors and destructor */
    //@{

    /** Constructor
     */
    Extension();

    /** Destructor
     */
    virtual ~Extension();

    //@}

    /**@name Extension public methods */
    //@{

    /** Get the name of the extension
     */
    virtual const BAS::String& extensionName() const;

    /** Get a variable from the database extension
     *  @param name The name of the variable
     *  @return Pointer to the variable on success, 0 otherwise
     */
    virtual SCR::Variable* variable( const BAS::String& name );

    //@}

    /**@name Extension special methods */
    //@{

    /** Connect the database extension to the specified database plugin
     *  @param module The name of the database plugin
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool dataConnection( const BAS::String& module );


    /** Set the failure string for the last error
     *  @return Reference to internal failure string
     */
    void failure( const BAS::String& failure );

    /** Get the failure string for the last error
     *  @return Reference to internal failure string
     */
    const BAS::String& failure() const;

    /** Get a new connection from the DBC::DatabasePlugIn
     *  @return Handle >= 0 on success, < 0 otherwise
     */
    int64 openConnection();

    /** Close a database connection
     *  @param handle The handle for the data connection
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool closeConnection( int64 handle );

    /** Get the connection for the handle
     *  @param handle The handle for the data connection
     *  @return Pointer to connection on success, 0 otherwise
     */
    RWDBConnection* connection( int64 handle );

    /** Get the result class for the handle
     *  @param handle The handle for the database result
     *  @return Pointer to result on success, 0 otherwise
     */
    ResultHandle* result( int64 handle );

    /** Close the result for this handle
     *  @param handle The result handle
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool closeResult( int64 handle );

    /** Execute a SQL statement
     *  @param handle Handle for the database connection
     *  @param statement The SQL statement to execute
     */
    int64 executeSQL( int64              handle,
                     const BAS::String& statement );

    /** Begin a new transaction on the specified connection
     *  @param handle Handle for the database connection
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool beginTransaction( int64 handle );

    /** Commit a transaction on the specified connection
     *  @param handle Handle for the database connection
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool commitTransaction( int64 handle );

    /** Rollback a transaction on the specified connection
     *  @param handle Handle for the database connection
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool rollbackTransaction( int64 handle );

    //@}

  private:

    // instance members
    BAS::String                                     failureM;
    DBC::DatabasePlugIn*                            dbPlugInM;
    int64                                           nextConHandleM;
    int64                                           usedConHandlesM;
    int64                                           nextResHandleM;
    int64                                           usedResHandlesM;
    RWTPtrMap<int64,RWDBConnection,less<int64> >     connectionMapM;
    RWTPtrMap<int64,ResultHandle,less<int64> > resultMapM;

    // class members
    static SCR::VariableMap   constantsCM;
    static const int64        maxConHandlesCM;
    static const int64        maxResHandlesCM;
    static const int64        invalidConHandleCM;
    static const int64        invalidResHandleCM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBEXTENSION_HPP
