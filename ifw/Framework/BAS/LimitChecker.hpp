#ifndef BAS_LIMITCHECKER_HPP
#define BAS_LIMITCHECKER_HPP
//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//  user limits checker class
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//------------------------------------------------------------------------------
// $Log: BAS_LimitChecker.hpp,v $
// Revision 1.3  2000/11/28 13:28:53  mwriedt
// Adapted values, beautified output.
//
// Revision 1.2  2000/06/26 11:46:26  rmurawsk
// doc++ comments changed
//
// Revision 1.1  2000/06/20 09:50:32  rmurawsk
// #2132# BAS_LimitChecker added
//
//==============================================================================
#include <sys/resource.h>

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

using std::cerr;

namespace BAS
{
/** <tt><b>LimitChecker</b></tt> user limit checker.

    <p> This class checks the data segment size, the memory size and the
    number of open files.
*/
class LimitChecker D_THREADINFO
{

  D_SINGLETHREADED

  public:

    /** @name String Constructors and Destructor */
    //@{

    /** default constructor
     */
    LimitChecker();

    /** standard constructor
        @param dataSegSize   data segment size
        @param memSize       memory size
        @param maxOpenFiles  number of open files
     */
    LimitChecker(const rlim_t dataSegSize,
                     const rlim_t memSize,
                     const rlim_t maxOpenFiles);

    /** destructor
     */
    virtual ~LimitChecker();
    //@}

    /** outstream operator
     */
    friend std::ostream& operator << (std::ostream& os, const LimitChecker& value);

    /** checks user limits
        @return true if limits are ok
     */
    bool check() const;

  private:

    // constants
    BAS_EXPORT static const rlim_t defaultDataSegSizeCM;
    BAS_EXPORT static const rlim_t defaultMemSizeCM;
    BAS_EXPORT static const rlim_t defaultMaxOpenFilesCM;

    // methods
    bool checkSingleLimit(const rlim_t theLimit,
                          const int resource,
                          const String& resName,
                          const String& unit = "",
                          const int divisor = 1) const;

    // member variable
    const rlim_t  dataSegSizeM;
    const rlim_t  memSizeM;
    const rlim_t  maxOpenFilesM;
};
std::ostream& operator << (std::ostream& os, const BAS::LimitChecker& value);
}
#endif  // BAS_LIMITCHECKER
