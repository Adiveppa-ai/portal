#ifndef IXT_DBROLLBACKTRANSACTION_HPP
#define IXT_DBROLLBACKTRANSACTION_HPP 

//==============================================================================
//
//      @(#)%Portal Version: DbRollbackTransaction.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:10 %
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
//   Declaration of the function node for dbRollbackTransaction.
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
// $RCSfile: RollbackTransaction.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/08/23 13:41:25 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: RollbackTransaction.hpp,v $
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

/**<b><tt>RollbackTransaction</tt></b> is the function node for starting
 * transactions on database connections.
 *
 */
class RollbackTransaction : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name RollbackTransaction constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~RollbackTransaction();

    //@}

    /**@name RollbackTransaction public methods */
    //@{

    /** Execute the dbRollbackTransaction() function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();
    
    /** Create a dbRollbackTransaction() function 
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

    RollbackTransaction( Extension* dbExtension,
                            SCR::LongNode*    connectionNode );

  private:
    // hide default and copy constructor
    RollbackTransaction();
    RollbackTransaction( const RollbackTransaction& other );
    const RollbackTransaction& operator=( 
      const RollbackTransaction& other );

    // instance members
    Extension* dbExtensionM;
    SCR::LongNode*    connectionNodeM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBROLLBACKTRANSACTION_HPP
