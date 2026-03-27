#ifndef STR_CONSTANTS_HPP
#define STR_CONSTANTS_HPP
//=============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: STR
//-----------------------------------------------------------------------------
// Module Description:
//  Constants for STR to work around some solaris issues
//
// Current Issues:
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Giles Douglas
// Backup-Responsible:
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 06-Dec-2006  Jitendra Yadav      Adding CAS support for HP-ia
// 05-May-2003  Giles Douglas       Initial revision
//
//=============================================================================

#if !defined STR_BASE_EXPORT
  #if defined(WINDOWS)
    #if !defined(STR_BASE_INTERNAL)
      #define STR_BASE_EXPORT __declspec(dllimport)
    #else
      #define STR_BASE_EXPORT __declspec(dllexport)
    #endif
  #else
    #define STR_BASE_EXPORT
  #endif
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace STR
{
// registry strings
STR_BASE_EXPORT extern const BAS::String registryBlockTransferCM;
STR_BASE_EXPORT extern const BAS::String registryQueueSizeCM;
STR_BASE_EXPORT extern const BAS::String registryBlockSizeCM;
STR_BASE_EXPORT extern const BAS::String registryQueueBlockTimeCM;
STR_BASE_EXPORT extern const BAS::String registryArrayTypeCM;
STR_BASE_EXPORT extern const BAS::String registrySpinCountCM;
STR_BASE_EXPORT extern const BAS::String registryYieldCountCM;
STR_BASE_EXPORT extern const BAS::String registrySleepTimeMilliSecCM;
}
#endif
