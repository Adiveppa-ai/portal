#ifndef IXT_DBERROR_HPP
#define IXT_DBERROR_HPP 

//==============================================================================
//
//      @(#)%Portal Version: DbError.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:23 %
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
//   Definition of the class Error. This class is the function node for
//   getting error messages from the iScript database extension.
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
// $RCSfile: Error.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/08/21 14:51:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Error.hpp,v $
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

/**<b><tt>Error</tt></b> is the function node for getting error messages
 * from the iScript database extension.
 *
 */
class Error : public SCR::StringNode
{
  D_SINGLETHREADED

  public:
    /**@name Error constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Error();

    //@}

    /**@name Error public methods */
    //@{

    /** Execute the dbError() function
     *  @return Reference to the result string
     */
    virtual const BAS::String& result();
    
    /** Create a dbError() function 
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

    Error( Extension* dbExtension );

  private:
    // hide default and copy constructor
    Error();
    Error( const Error& other );
    const Error& operator=( const Error& other );

    // instance members
    Extension* dbExtensionM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBERROR_HPP
