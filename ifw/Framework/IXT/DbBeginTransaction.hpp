#ifndef IXT_DBBEGINTRANSACTION_HPP
#define IXT_DBBEGINTRANSACTION_HPP 

//==============================================================================
//
//      @(#)%Portal Version: DbBeginTransaction.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:36 %
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
//   Declaration of the function node for dbBeginTransaction.
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
// $RCSfile: BeginTransaction.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/08/23 13:41:25 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: BeginTransaction.hpp,v $
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

/**<b><tt>BeginTransaction</tt></b> is the function node for starting
 * transactions on database connections.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: BeginTransaction.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/23 13:41:25 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 *
 */
class BeginTransaction : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name BeginTransaction constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~BeginTransaction();

    //@}

    /**@name BeginTransaction public methods */
    //@{

    /** Execute the dbBeginTransaction() function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();
    
    /** Create a dbBeginTransaction() function 
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

    BeginTransaction( Extension* dbExtension,
                            SCR::LongNode*    connectionNode );

  private:
    // hide default and copy constructor
    BeginTransaction();
    BeginTransaction( const BeginTransaction& other );
    const BeginTransaction& operator=( const BeginTransaction& other );

    // instance members
    Extension* dbExtensionM;
    SCR::LongNode*    connectionNodeM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBBEGINTRANSACTION_HPP
