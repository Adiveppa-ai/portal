#ifndef PLI_PARALLEL_LOAD_INTERFACE_HPP
#define PLI_PARALLEL_LOAD_INTERFACE_HPP
//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLI
//
//------------------------------------------------------------------------------
// Module Description:
//   CommonLoadInterface class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: pc
//
// $RCSfile: CommonLoadInterface.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2010/11/15 09:23:42 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// Revision 1.1  2010/11/09 16:12:12  pc
// Initial version of base class LoadInterface .
//
//==============================================================================

#include "BAS/String.hpp"

namespace PLI
{
class CommonLoadInterface 
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      CommonLoadInterface();

      CommonLoadInterface(const BAS::String& name);

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~CommonLoadInterface();

    //@}

    /**@name Public Member Functions */
    //@{

    //@}

      virtual bool commonInit();

      virtual bool validity();

      virtual void dependencies(BAS::StringList & depList) ;

      const BAS::String& itemName() const;

  private:

    // The following private attributes and functions are used internally.

    BAS::String nameM;

};

}

#endif // STDINTERFACE_HPP

