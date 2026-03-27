#ifndef IXT_DBEXECUTE_HPP
#define IXT_DBEXECUTE_HPP

//==============================================================================
//
//      @(#)%Portal Version: DbExecute.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:21 %
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
//   Definition of class Execute. This is the function node for the
//   iScript dbExecute() function.
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
// $RCSfile: Execute.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/08/21 14:51:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Execute.hpp,v $
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

/**<b><tt>Execute</tt></b> is the function node for executing 
 * SQL statements.
 *
 */
class Execute : public SCR::LongNode
{
  D_SINGLETHREADED

  public:
    /**@name Execute constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Execute();

    //@}

    /**@name Execute public methods */
    //@{

    /** Execute the dbExecute() function
     *  @return Long handle for the database connection
     */
    virtual int64 result();
    
    /** Create a dbExecute() function 
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

    Execute( Extension* dbExtension,
                   SCR::LongNode*    connectionNode,
                   SCR::StringNode*  statementNode );

  private:
    // hide default and copy constructor
    Execute();
    Execute( const Execute& other );
    const Execute& operator=( const Execute& other );

    // instance members
    Extension* dbExtensionM;
    SCR::LongNode*    connectionNodeM;
    SCR::StringNode*  statementNodeM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBEXECUTE_HPP
