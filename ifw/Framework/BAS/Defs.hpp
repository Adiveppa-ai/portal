#ifndef BAS_DEFS_HPP
#define BAS_DEFS_HPP

//
//      Copyright (c) 2001 - 2023 Oracle.
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//
//------------------------------------------------------------------------------
// Module Description:
//   BAS definitions.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: Defs.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:43:41 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: BAS_Defs.hpp,v $
// Revision 1.15  2001/07/25 13:52:09  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.14  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
//==============================================================================

#ifndef RW_TOOLS_DEFS_H
  #include <rw/defs.h>
#endif
#ifndef RW_TOOLS_RSTREAM_H
  #include <rw/rstream.h>
#endif

#ifndef RW_NO_IOSTD
#ifndef _RWSTD_IOMANIP_INCLUDED
  #  include <iomanip>
#endif
#ifndef _RWSTD_SSTREAM_INCLUDED
  #  include <sstream>
#endif
#ifndef _RWSTD_FSTREAM_INCLUDED
  #  include <fstream>
#endif
#else
#  include <iomanip.h>
#  include <stringstream.h>
#  include <fstream.h>
#endif

#if defined(RWTOOLS) && (RWTOOLS >= 0x07050000)
#  ifndef RWSTD_STATIC_CAST
#    define RWSTD_STATIC_CAST _RWSTD_STATIC_CAST
#  endif
#  ifndef RWSTD_REINTERPRET_CAST
#    define RWSTD_REINTERPRET_CAST _RWSTD_REINTERPRET_CAST
#  endif
#  ifndef RWSTD_CONST_CAST
#    define RWSTD_CONST_CAST _RWSTD_CONST_CAST
#  endif
#  ifndef RWSTD_REINTERPRET_CONST_CAST
#    define RWSTD_REINTERPRET_CONST_CAST _RWSTD_REINTERPRET_CONST_CAST
#  endif
#  ifdef __GNUG__
#    ifndef _IOSTREAM_H
#      define _IOSTREAM_H
#    endif
#  endif
#  ifdef __aix
#    ifndef IOSTREAMH
#      define IOSTREAMH
#    endif
#  endif
#else
#error dfsdf
#  include <rw/math.h>
#endif

#define BAS_EXPORT 

#ifdef RW_NAMESPACE_REQUIRED
// Because integrate didn't do it right! ARGH!
#ifndef _RWSTD_IOSTREAM_INCLUDED
  #include <iostream>
#endif
#ifndef _RWSTD_ALGORITHM_INCLUDED
  #include <algorithm>
#endif
#ifndef _RWSTD_FUNCTIONAL_INCLUDED
  #include <functional>
#endif

using std::ostream;
using std::istream;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::equal_to;
using std::less;
using std::endl;
using std::cout;
using std::cerr;
using std::cin;
using std::ios;

  #define BAS_DEFS_STD_GLOBAL(DEFS_NAME) std::DEFS_NAME
#else
  #define BAS_DEFS_STD_GLOBAL(DEFS_NAME) ::DEFS_NAME
#endif

#define LIBPREFIX "lib"
#define LIBSUFFIX ".so"

#define PIN_NODEP_PIN_OS

#endif // BAS_DEFS_HPP

#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif
