#ifndef PIN_AAA_SIMULATOR_OUTPUT_IF_HPP
#define PIN_AAA_SIMULATOR_OUTPUT_IF_HPP

//=============================================================================
//
//
//      @(#)%Portal Version: OutputIf.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:42:13 %
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//
//-----------------------------------------------------------------------------
// Module Description:
// Simulate AAA gateway traffic.
//
// Current Issues:
//
//=============================================================================

#include <exception>

#include "BAS/String.hpp"
#include "BAS/Trace.hpp"

namespace SIM {

/**
 * Abstract base class for objects designed to perform
 * protocol-specific operations on the AAA gateway.
 */
class OutputIf D_THREADINFO
{
  public:
    // Destructor, locally implemented to do nothing.  But since it is
    // virtual, the destructor of the derived class will be called first.
    //
    // Note to authors of derived classes:
    //	It is never okay to throw an exception from a destructor, so don't.
    //
    virtual ~OutputIf()
    {
      // nothing to do here
    }

    // Given an identifier, return the name of the corresponding operation.
    //
    // Parameters:
    //	operationId: the identifier corresponding to operationName
    //
    // This method can throw a std::exception.
    //
    virtual BAS::String getOperationName(const int32 operationId) const = 0;

    // Given a name, return the numeric id of the corresponding operation.
    //
    // Parameters:
    //	operationName: the name corresponding to operationId
    //
    // This method can throw a std::exception.
    //
    virtual int32 getOperationId(const BAS::String& operationName) const = 0;
};

// -------------------------------------------------------------------------
// THIS 'EXTERN C' METHOD MUST EXIST IN THE PLUGIN LIBRARY
// ----
// // Method to get an instance of the implementation of OutputIf.
// extern "C" OutputIf * getOutputHandler();
// ----
// This method should construct the class deriving from OutputIf
// and return a pointer to it.  You can do something like this:
//     OutputIfImpl impl = new OutputIfImpl();
//     return (dynamic_cast<OutputIf *>(impl));
// -------------------------------------------------------------------------

} // namespace SIM

#endif
