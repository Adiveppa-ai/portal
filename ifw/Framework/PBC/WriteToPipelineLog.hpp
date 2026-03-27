#ifndef PBC_WRITETOPIPELINELOG_HPP
#define PBC_WRITETOPIPELINELOG_HPP
//==============================================================================
//
// 1998,1999 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description:
//   Defintion of a macro for sending messages to the pipeline log.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: WriteToPipelineLog.hpp,v $
// $Revision: 1.1 $
// $Author: bt $
// $Date: 2001/05/03 16:07:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: WriteToPipelineLog.hpp,v $
// Revision 1.1  2001/05/03 16:07:18  bt
// Format renamed to Pipeline.
//
// Revision 1.3  2000/09/29 10:27:48  aro
// Tried to fix doc++ comments.
//
// Revision 1.2  2000/02/11 10:07:43  sd
// New global function writeToPipelineLog().
//
// Revision 1.1  1999/08/19 13:42:42  sd
// Initial revision.
//
//==============================================================================

#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif

#define PBC_WRITE_TO_PIPELINE_LOG( theState ) \
{ \
  BAS::RegisteredObject* plLog = \
    BAS::RegisteredObject::pipelineLog(this->name()); \
  if (plLog != 0) \
  { \
    plLog->receiveMessage(theState); \
  } \
}
namespace PBC
{
extern void writeToPipelineLog( const BAS::RegisteredObject& origin,
                                    const BAS::Status&           state );
}
#endif // WRITETOPIPELINELOG_HPP
