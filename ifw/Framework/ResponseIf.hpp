#ifndef PIN_AAA_SIMULATOR_RESPONSE_IF_HPP
#define PIN_AAA_SIMULATOR_RESPONSE_IF_HPP

//=============================================================================
//
//	@(#)%Portal Version: ResponseIf.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:42:16 %
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Module Description:
// Simulate AAA gateway traffic.
//
// Current Issues:
//
//=============================================================================

#include <stdexcept>
#include <rw/rwerr.h>
#include <rw/toolpro/socket.h>
#include <rw/toolpro/inetaddr.h>

namespace SIM {

/**
 * Interface class for objects designed to receive and decode
 * protocol-specific responses from the AAA gateway.
 */
class ResponseIf
{
  public:
    // constructor
    ResponseIf(int32 maxBlockSize)
    : maxBlockSizeM(maxBlockSize)
    {
      // nothing more to do
    }

    // Destructor
    virtual ~ResponseIf();

    // Read a message block from the passed socket, decode it and
    // populate the appropriate values into the out parameters.
    //
    // Parameters:
    //  sock: Socket over which responses will arrive.
    //  receivedTime: Must be filled with the timestamp of when the
    //                response was received.
    //  operationId: Must be filled with the identifier of the operation
    //               (opcode) this response was for.
    //  callId: Must be filled with the call identifier.
    //  errorStatus: Must be filled with the response type.  Possible values:
    //                -1 - failure
    //                 1 - success
    //               100 - late response
    //  respOrigin: Where was this response created?  Possible values:
    //                 0 - normal response got from the CM
    //                 1 - timeout / exception response from the AAA gateway
    //  logblock: Optional parameter, must log the fixed message block if TRUE.
    //
    // This method can only throw exceptions derived from std::exception.
    //
    virtual void readMessageBlock(RWSocket& sock,
				  struct timeval& receivedTime,
				  int32& operationId,
				  int32& callId,
				  int32& errorStatus,
				  int32& respOrigin,
				  const bool logblock = false) const = 0;

 protected:
   int32 maxBlockSizeM;

};

inline
ResponseIf::~ResponseIf()
{
  // nothing to do here
}

// -------------------------------------------------------------------------
// THIS 'EXTERN C' METHOD MUST EXIST IN THE PLUGIN LIBRARY
// ----
// // Method to get an instance of the implementation of ResponseIf.
// extern "C" ResponseIf * getResponseHandler(int32 maxBlockSize);
// ----
// This method should construct the class deriving from ResponseIf
// and return a pointer to it.  You can do something like this:
//     ResponseIfImpl impl = new ResponseIfImpl(parameters);
//     return (dynamic_cast<ResponseIf *>(impl));
// -------------------------------------------------------------------------

} // namespace SIM

#endif
