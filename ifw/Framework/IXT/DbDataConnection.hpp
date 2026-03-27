#ifndef IXT_DBDATACONNECTION_HPP
#define IXT_DBDATACONNECTION_HPP

//==============================================================================
//
//      @(#)%Portal Version: DbDataConnection.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:26 %
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
//   Definition of the class DataConnection. This class is the function
//   node for connecting the database extension to a DBC::DbDatabase plugin.
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
// $RCSfile: DataConnection.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/08/21 14:51:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DataConnection.hpp,v $
// Revision 1.1  2000/08/21 14:51:14  sd
// - Initial revision.
//
//==============================================================================

#include "SCR/Node.hpp"

// Forward declaration
namespace SCR
{
class Interpreter;
class FctDescr;
class ParserStack;
}

namespace IXT 
{
namespace Db 
{

class Extension;
/**<b><tt>DataConnection</tt></b> is the function node for connecting the
 * iScript database extension to a DBC::DbDatabase plugin.
 *
 */
class DataConnection : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name DataConnection constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DataConnection();

    //@}

    /**@name DataConnection public methods */
    //@{

    /** Execute the dbDataConnection(String) function
     */
    virtual bool result();
    
    /** Create a dbDataConnection(String) function 
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
    DataConnection( Extension* dbExtension,
                        SCR::StringNode*  dataConnectionNode );

  private:
    // hide default and copy constructor
    DataConnection();
    DataConnection( const DataConnection& other );
    const DataConnection& operator=( const DataConnection& other );

    // instance members
    Extension* dbExtensionM;
    SCR::StringNode*  dataConnectionNodeM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBDATACONNECTION_HPP
