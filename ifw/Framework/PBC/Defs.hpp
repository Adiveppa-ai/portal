#ifndef PBC_DEFS_HPP
#define PBC_DEFS_HPP
//==============================================================================
//
//      @(#)%Portal Version: Defs.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:48:43 %
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
// Module Description:
//  Basic definitions.
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
// $RCSfile: Defs.hpp,v $
// $Revision: 1.6 $
// $Author: aro $
// $Date: 2000/09/29 10:27:47 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Defs.hpp,v $
// Revision 1.6  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.5  2000/02/11 09:16:37  pengelbr
// Add new record-types.
//
// Revision 1.2  1999/06/07 12:08:13  aro
// Module PIM_Base renamed to PBC (Plugin Base Classes).
//
// Revision 1.1  1999/04/23 12:18:03  pengelbr
// PlugIn Definitions.
//
//==============================================================================

#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif

namespace PBC
{
/** Call definition type enumeration.

    Values:
    <ul>
    <li>UNKNOWN_DEF - unknown definition
    <li>MOC         - switch mobile originating call
    <li>TA_MOC      - TAB mobile originating call (roaming)
    <li>CFW         - mobile switch call forwarding
    <li>RCF_RFD     - mobile roaming call forwarding 
    <li>SMO         - mobile short message originator
    <li>SMT         - mobile short message terminating
    <li>VMO         - mobile voice mailing originating
    <li>OAB         - mobile operator assisted call (basic)
    <li>OAS         - mobile operator service (call completion)
    <li>MTC         - switch mobile terminating call
    <li>TA_MTC      - TAB mobile termination call (roaming)
    <li>POC         - ISDN/public switch originating
    <li>DX_POC      - ISDN/public switch originating (data exchange)
    <li>PCF         - ISDN/public switch call forwarding
    <li>PVM         - ISDN/public switch voice mail originating
    <li>POB         - ISDN/public operator assisted call (basic)
    <li>POS         - ISDN/public operator service call (call completion)
    <li>PTC         - ISDN/public switch termination call
    <li>DX_PTC      - ISDN/public switch termination (data exchange)
    <li>IOC         - Internet originating
    </ul>
*/
enum S42RecordTypeT
{
  UNKNOWN_TYPE      =   0L,
  MOC               =  20L,
  TA_MOC            =  21L,
  CFW               =  22L,
  RCF_RFD           =  23L,
  SMO               =  24L,
  SMT               =  25L,
  VMO               =  26L,
  OAB               =  27L,
  OAS               =  28L,
  MTC               =  30L,
  TA_MTC            =  31L,
  SCU               =  50L,
  VAS               =  60L,
  POC               = 120L,
  DX_POC            = 121L,
  PCF               = 122L,
  PVM               = 126L,
  POB               = 127L,
  POS               = 128L,
  PTC               = 130L,
  DX_PTC            = 131L,
  IOC               = 220L,
  STD_ZONE          = 960L,
  SEG_ZONE          = 961L,
  STD_ROAMER        = 970L,
  SEG_ROAMER        = 971L,
  GLOB_CHARGE       = 980L,
  CUST_CHARGE       = 981L,
  SPEC_CHARGE       = 982L,
  CONT_CHARGE       = 983L,
  MULTI_CHARGE      = 984L,
  ALT_GLOB_CHARGE   = 985L,
  ALT_CUST_CHARGE   = 986L,
  ALT_SPEC_CHARGE   = 987L,
  ALT_CONT_CHARGE   = 988L,
  ALT_MULTI_CHARGE  = 989L,
  CARRI_CHARGE      = 990L,
  INTER_CHARGE      = 991L,
  ALT_CARRI_CHARGE  = 992L,
  ALT_INTER_CHARGE  = 993L
};
}
#endif // DEFS_HPP
