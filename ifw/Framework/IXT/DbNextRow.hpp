#ifndef IXT_DBNEXTROW_HPP
#define IXT_DBNEXTROW_HPP

//==============================================================================
//
//      @(#)%Portal Version: DbNextRow.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:14 %
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
//   Definiton of class NextRow. This is the iScript function node for 
//   getting results from the database.
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
// $RCSfile: NextRow.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/08/21 14:51:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: NextRow.hpp,v $
// Revision 1.1  2000/08/21 14:51:14  sd
// - Initial revision.
//
//==============================================================================

#include <rw/tpordvec.h>
#include <rw/tvordvec.h>
#include "SCR/Node.hpp"
#include <rw/db/datetime.h>

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

/**<b><tt>NextRow</tt></b> is the iScript function node for getting 
 * results from the database
 *
 */
class NextRow : public SCR::LongNode
{
  D_SINGLETHREADED

  public:
    /**@name NextRow constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~NextRow();

    //@}

    /**@name NextRow public methods */
    //@{

    /** Execute the dbFetch(Long,...) function
     *  @return 0 on no more results, 1 on results, -1 on error
     */
    virtual int64 result();
    
    /** Create a dbFetch() function 
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

    /* Add a new datanode to the function node
     * @param dataType The type of the data node
     * @param dataNode The new datanode to add
     */
    void addDataNode( int       dataType, 
                      SCR::Node* dataNode );

    NextRow( Extension* dbExtension,
                   SCR::LongNode*    resultNode );

  private:
    // hide default and copy constructor
    NextRow();
    NextRow( const NextRow& other );
    const NextRow& operator=( const NextRow& other );

    // instance members
    Extension*              dbExtensionM;
    SCR::LongNode*                 resultNodeM;
    RWTValOrderedVector<int>      dataTypesM;
    RWTPtrOrderedVector<SCR::Node> dataNodesM;
    BAS::String                    stringBufferM;
    BAS::Decimal                   decimalBufferM;
    RWDBDateTime                  dateTimeBufferM;
    BAS::DateTime                  basDateTimeBufferM;
};

} //namespace Db
} //namespace IXT
#endif // IXT_DBNEXTROW_HPP
