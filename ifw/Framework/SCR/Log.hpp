#ifndef SCR_LOG_HPP
#define SCR_LOG_HPP

//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Log. This is the base class used for all
//   logging classes.
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
// $RCSfile: Log.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:39 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Log.hpp,v $
// Revision 1.2  2005/09/01 pborah
// PRSF00181265  "WARNING logged as MAJOR error (common_platform)"
//
// Revision 1.1  2000/09/27 06:36:02  sd
// - Initial revision.
//
//==============================================================================

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif

namespace SCR
{

/** <b><tt>Log</tt></b> is the base class for all logging classes used
 *  in the iScript interpreter
 */
class Log D_THREADINFO
{
  public:
    /**@name Log constructors and destructor */
    //@{

    /** Constructor
     */
    Log();

    /** Destructor
     */
    virtual ~Log();

    //@}


    /**@name Log public methods */
    //@{

    /** Log a message
     *  @param msg The message to log
     */
    virtual void log( const BAS::String& msg, BAS::Status::Severity severity=BAS::Status::major);

    //@}

  private:
};
}
#endif // LOG_HPP
