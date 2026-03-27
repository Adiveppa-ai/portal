#ifndef IXT_DBCOMMITTRANSACTION_HPP
#define IXT_DBCOMMITTRANSACTION_HPP 

//==============================================================================
//
//      @(#)%Portal Version: DbCommitTransaction.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:30 %
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
//   Declaration of the function node for dbCommitTransaction.
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
// $RCSfile: CommitTransaction.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/08/23 13:41:25 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: CommitTransaction.hpp,v $
// Revision 1.1  2001/08/23 13:41:25  sd
// - PETS #38557 - Transaction handling added
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

/**<b><tt>CommitTransaction</tt></b> is the function node for starting
 * transactions on database connections.
 *
 */
class CommitTransaction : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name CommitTransaction constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~CommitTransaction();

    //@}

    /**@name CommitTransaction public methods */
    //@{

    /** Execute the dbCommitTransaction() function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();
    
    /** Create a dbCommitTransaction() function 
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

    CommitTransaction( Extension* dbExtension,
                            SCR::LongNode*    connectionNode );

  private:
    // hide default and copy constructor
    CommitTransaction();
    CommitTransaction( const CommitTransaction& other );
    const CommitTransaction& operator=( 
      const CommitTransaction& other );

    // instance members
    Extension* dbExtensionM;
    SCR::LongNode*    connectionNodeM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBCOMMITTRANSACTION_HPP
