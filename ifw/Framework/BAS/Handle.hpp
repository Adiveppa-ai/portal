#ifndef BAS_HANDLE_HPP 
#define BAS_HANDLE_HPP
//==============================================================================
//
// Copyright (c) 2001, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//  This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
//    only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//  This is the base class for the handle template.
//  It used in the EDR Container to make safe that the destructur
//  is called.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work, finished, accepted>
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: Handle.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:44:01 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: BAS_Handle.hpp,v $
// Revision 1.2  2001/05/14 08:40:28  jkeckst
// add some handle classes
//
// Revision 1.1  2001/04/10 07:58:39  jkeckst
// used for handle classes
//
//
//==============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
/**  <tt><b>BAS_Handle</b></tt> A Handle class for defined pointer accesses.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Handle.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:44:01 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>                

    
*/


namespace BAS {
class Handle D_THREADINFO
{
public:
  Handle();
  virtual ~Handle();
  
  virtual Handle * clone();

private:
  Handle(const Handle &);
  Handle& operator=(const Handle&);

};
}

#endif
