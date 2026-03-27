#ifndef BAS_EXCEPTION_HPP
#define BAS_EXCEPTION_HPP
//==============================================================================
//
// 1998-2000 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   Exception class declaration.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: aro
//
// $RCSfile: Exception.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:43:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: BAS_Exception.hpp,v $
// Revision 1.2  2000/02/11 10:26:20  aro
// Syntax error fixed.
//
// Revision 1.1  2000/02/11 10:25:01  aro
// New class BAS_Exception added.
//
//==============================================================================

#ifndef BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif

/** <tt>BAS_Exception</tt> is the base class of the exception hierarchy.
    This class acts as the base for the derivations of other, more specialised 
    exceptions.
    <p>
    Currently, this class is implemented as a simple typedef on the
    class BAS_Status. 

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Exception.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:43:48 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>
                                     
    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>n/a
        <dt><b>Messages send</b></dt>
        <dd>n/a
      <dt><b>Messages received</b></dt>
        <dd>n/a
      <dt><b>Errors</b></dt>
        <dd>n/a
    </dl>                            
*/
typedef BAS_Status BAS_Exception;

#endif // BAS_EXCEPTION_HPP

