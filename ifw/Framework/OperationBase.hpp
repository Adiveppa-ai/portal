#ifndef PIN_AAA_SIMULATOR_OPERATION_BASE_HPP
#define PIN_AAA_SIMULATOR_OPERATION_BASE_HPP

//=============================================================================
//
// Copyright (c) 2004 - 2007 Oracle. All rights reserved.
//
// This material is the confidential property of Oracle Corporation or
// its licensors and may be used, reproduced, stored or transmitted only
// in accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Module Description:
// Simulate AAA gateway traffic.
//
// Current Issues:
//
//-----------------------------------------------------------------------------
// id string: "@(#)%Portal Version: OperationBase.hpp:Pipeline7.3.1Int:2:2007-Dec-19 18:21:53 % "
//=============================================================================

#include <exception>
#include <rw/tpmap.h>
#include <rw/tpvector.h>
#include "BAS/String.hpp"
#include "BAS/Trace.hpp"

namespace SIM {

/**
 * Abstract base class for objects designed to perform
 * protocol-specific operations on the AAA gateway.
 */
class OperationBase D_THREADINFO
{
  public:
    // Constructor, local (default) implementation
    //
    // Parameters:
    //	operationName: Name of the operation.
    //	operationFlag: Flags relevant to the operation.
    //	timeLimit: Interval (seconds) to schedule between this and the next
    //		   operation with the same call identifier.
    //	inputMessage: Data to send to the gateway for this operation, before
    //		      any fixup.
    //
    OperationBase(const char * operationName,
		  const char * operationFlag,
		  const int32 timeLimit,
		  const char * inputMessage)
    : operationNameM(operationName),
      operationFlagM(operationFlag),
      timeLimitM(timeLimit),
      inputMessageM(inputMessage)
    {
      // nothing more to do here
    }

    // Destructor, locally implemented to do nothing.  But since it is
    // virtual, the destructor of the derived class will be called first.
    //
    // Note to authors of derived classes:
    //	It is never okay to throw an exception from a destructor, so don't.
    //
    virtual ~OperationBase()
    {
      // nothing to do here
    }

    // Fix up inputMessageM class variable with the supplied values
    // so that it represents the input data for a gateway operation.
    //
    // Parameters:
    //	simTime: Offset from the start of the test run (seconds) when
    //		 this operation (operationNameM) will be invoked.
    //	timeOffset: Time when the test started (seconds).
    //	login, callingNumber, calledNumber: Obvious.
    //	callDuration: Interval (seconds) between this and the next
    //		      scheduled operation with the same call identifier.
    //	callId: Identifier that groups operations comprising a call.
    //	len: Out parameter, must contain length of data block being returned.
    //	operationId: Out parameter, must contain operation (opcode) to invoke.
    //	messageBlock: Out parameter, must contain fixed message block; the
    //		      caller will allocate and free memory for this block.
    //	logblock: Optional parameter, must log the fixed message block if TRUE.
    //
    // This method can throw a std::exception if it cannot populate the
    // messageBlock parameter properly.
    //
    virtual void updateMessage(const int32 simTime,
			       const time_t timeOffset,
			       const char * login,
			       const char * callingNumber,
			       const char * calledNumber,
			       const int32 callDuration,
			       const int32 callId,
			       int32& len,
			       int32& operationId,
			       char * messageBlock,
			       const bool logblock = false) = 0;

    // Name of the operation
    BAS::String operationNameM;

    //	Flags relevant to the operation
    BAS::String operationFlagM;

    // interval after this operation, in seconds
    int32 timeLimitM;

    // Data to send to the gateway for this operation
    BAS::String inputMessageM;

  private:
    // hidden default constructor, locally implemented
    OperationBase()
    : operationNameM(""),
      operationFlagM(""),
      timeLimitM(0),
      inputMessageM("")
    {
      // nothing to do here
    }
};

typedef RWTPtrVector< OperationBase >			OperationBufferType;
typedef RWTPtrMap< RWCString, OperationBase, std::less<RWCString> >
							OperationPtrMapType;

// -------------------------------------------------------------------------
// THIS 'EXTERN C' METHOD MUST EXIST IN THE PLUGIN LIBRARY
// ----
// // Method to get an instance of the implementation of OperationBase.
// extern "C" OperationBase *
// getOperationInstance(const char * operationName,
//                      const char * operationFlag,
//                      const int32 timeLimit,
//                      const char * inputMessage);
// ----
// This method should construct the class deriving from OperationBase
// and return a pointer to it.  You can do something like this:
//     OperationBaseImpl impl = new OperationBaseImpl(parameters);
//     return (dynamic_cast<OperationBase *>(impl));
// -------------------------------------------------------------------------

} // namespace SIM

#endif
