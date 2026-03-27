#ifndef IXT_DBCONNECTION_HPP
#define IXT_DBCONNECTION_HPP 

//==============================================================================
//
//      @(#)%Portal Version: DbConnection.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:28 %
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
//   Definition of the class Connection. This class is the function node 
//   for opening new database connections.
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
// $RCSfile: Connection.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/08/21 14:51:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Connection.hpp,v $
// Revision 1.1  2000/08/21 14:51:14  sd
// - Initial revision.
//
//==============================================================================

#include "SCR/Node.hpp"

// Forward declaration
namespace SCR
{
class Interpreter;
}

// Forward declaration
namespace SCR
{
class ParserStack;
}

// Forward declaration
namespace SCR
{
class FctDescr;
}

namespace IXT 
{
namespace Db 
{
class Extension;

/**<b><tt>Connection</tt></b> is the function node for getting new
 * database connections.
 *
 */
class Connection : public SCR::LongNode
{
  D_SINGLETHREADED

  public:
    /**@name Connection constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Connection();

    //@}

    /**@name Connection public methods */
    //@{

    /** Execute the dbConnection() function
     *  @return Long handle for the database connection
     */
    virtual int64 result();
    
    /** Create a dbConnection() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}

  protected:

    Connection( Extension* dbExtension );

  private:
    // hide default and copy constructor
    Connection();
    Connection( const Connection& other );
    const Connection& operator=( const Connection& other );

    // instance members
    Extension* dbExtensionM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBCONNECTION_HPP
