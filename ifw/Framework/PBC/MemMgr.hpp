#ifndef PBC_MEMMGR_HPP
#define PBC_MEMMGR_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description
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
// $RCSfile: MemMgr.hpp,v $
// $Revision: 1.4 $
// $Author: aro $
// $Date: 2000/09/29 10:27:47 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: MemMgr.hpp,v $
// Revision 1.4  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.3  2000/06/15 12:21:01  bt
// Changes for AIX xlC V366.
//
// Revision 1.1  1999/06/16 06:33:34  pengelbr
// MemMgr added.
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
namespace PBC
{
/** <b><tt>MemBlock</tt></b>.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: MemMgr.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.4 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 10:27:47 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
    </tr>
    </table>      
*/
class MemBlock D_THREADINFO
{
   public:
      MemBlock( int recordSize, int numRecords );
      ~MemBlock();

      void* getFreeRecord();

      bool freeRecord( void* record );

#ifdef __aix
      bool operator==(const MemBlock& rVal) const { return true; };
      bool operator<(const MemBlock& rVal) const { return true; };
#endif

   private:
      
      bool  recordIsFree( unsigned int record );
      void* useRecord( unsigned int record );

      bool           isValidM;
      int            recordSizeM;
      int            numUsedM;
      int            numTotalM;
      int            nextM;
      char*          memoryBlockM;
      unsigned int*  freeVectorM;
};

/** <b><tt>MemMgr</tt></b>
 */
class MemMgr
{
   public:
      MemMgr( int recordSize, int numRecordsPerBlock );

      ~MemMgr();

      void* newRecord();

      bool  deleteRecord( void* record );

   private:
      int recordSizeM;
      int numRecordsPerBlockM;

      RWTPtrOrderedVector<MemBlock> blockVectorM;
};
}
#endif // MEMMGR_HPP
