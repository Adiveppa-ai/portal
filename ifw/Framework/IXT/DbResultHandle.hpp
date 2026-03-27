#ifndef IXT_DBRESULTHANDLE_HPP
#define IXT_DBRESULTHANDLE_HPP

//==============================================================================
//
//      @(#)%Portal Version: DbResultHandle.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:41:12 %
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
//   ResultHandle is used to save the database results inside the 
//   interpreter extension.
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
// $RCSfile: ResultHandle.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2000/08/29 07:46:33 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ResultHandle.hpp,v $
// Revision 1.2  2000/08/29 07:46:33  sd
// - Implementation changed to support the IBM compiler
// - The first result in a dbresult is fetched automatically.
//
// Revision 1.1  2000/08/21 14:51:14  sd
// - Initial revision.
//
//==============================================================================

#include <rw/db/result.h>
#include <rw/db/reader.h>

/** <b><tt>ResultHandle</tt></b> is used to store database results inside
 *  the Extension.
 */
namespace IXT 
{
namespace Db 
{
class ResultHandle D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name ResultHandle consructors and destructor */
    //@{

    /** Constructor
     */
    ResultHandle( RWDBResult& result );

    /** Destructor
     */
    ~ResultHandle();

    //@}

    /**@name ResultHandle public methods */
    //@{

    /** Switch to the next result table
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool nextResult();

    /** Get the database reader
     *  @return Reference to database reader
     */
    RWDBReader& reader();

#ifdef __aix
    bool operator==( const ResultHandle& other ) const
    {
      return( this == &other );
    }
    bool operator<( const ResultHandle& other ) const
    {
      return( this < &other );
    }
#endif

    //@}

  private:
    // instance members
    RWDBResult resultM;
    RWDBReader readerM;
};

//==============================================================================
// Get the database reader 
//==============================================================================
inline RWDBReader& 
ResultHandle::reader()
{
  return readerM;
}

} //namespace Db
} //namespace IXT
#endif // IXT_DBRESULTHANDLE_HPP
