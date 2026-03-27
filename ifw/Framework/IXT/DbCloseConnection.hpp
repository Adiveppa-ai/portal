#ifndef IXT_DBCLOSECONNECTION_HPP
#define IXT_DBCLOSECONNECTION_HPP 

//==============================================================================
//
//      @(#)%Portal Version: DbCloseConnection.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:34 %
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
//   Definition of the class CloseConnection. This class is the function
//   node for closing new database connections.
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
// $RCSfile: CloseConnection.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/08/21 14:51:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: CloseConnection.hpp,v $
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

/**<b><tt>CloseConnection</tt></b> is the function node for closing
 * database connections.
 *
 */
class CloseConnection : public SCR::BoolNode
{
  D_SINGLETHREADED

  public:
    /**@name CloseConnection constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~CloseConnection();

    //@}

    /**@name CloseConnection public methods */
    //@{

    /** Execute the dbCloseConnection() function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();
    
    /** Create a dbCloseConnection() function 
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

    /* Constructor
     */
    CloseConnection( Extension* dbExtension,
                           SCR::LongNode*    handleNode );

  private:
    // hide default and copy constructor
    CloseConnection();
    CloseConnection( const CloseConnection& other );
    const CloseConnection& operator=( const CloseConnection& other );

    // instance members
    Extension* dbExtensionM;
    SCR::LongNode*    handleNodeM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBCLOSECONNECTION_HPP
