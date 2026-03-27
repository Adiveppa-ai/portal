#ifndef PLI_STDINTERFACEGUARD_HPP
#define PLI_STDINTERFACEGUARD_HPP
//==============================================================================
//
// Copyright (c) 1996, 2011, Oracle and/or its affiliates. 
// All rights reserved. 
//
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLI::
//
//------------------------------------------------------------------------------
// Module Description:
//   StdInterfaceGuard (standard plug in interface) class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: cprabhak
//
// $RCSfile: StdInterfaceGuard.hpp $
// $Revision: /cgbubrm_main.pipeline/1 $
// $Author: sumeemis $
// $Date: 2011/08/10 01:09:15 $
// $Locker:  $
//
//------------------------------------------------------------------------------
//
//   NAME
//     StdInterfaceGuard.hpp - Guard for StdInterface
//   DESCRIPTION
//     This class is used to guard the loading and access of libraries.
//     This is used only during the multi-threaded loading/access of libraries
//   NOTES
//     <other useful comments, qualifications, etc.>

//   MODIFIED   (MM/DD/YY)
//   cprabhak    03/18/11 - Creation
//------------------------------------------------------------------------------


#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif


namespace PLI
{

class StdInterfaceGuard
{
  private:
     class LibraryAccessGuard
      {
        public :
          bool operator == ( const LibraryAccessGuard & r ) const
          {
            return ( r.libraryNameM == libraryNameM );
          }

          LibraryAccessGuard()
          {
          }

          LibraryAccessGuard( const LibraryAccessGuard & r )
          {
            libraryNameM = r.libraryNameM;
          }

          BAS::String libraryNameM;
          RWMutexLock libraryAccessLockM;
      };

  protected:

      StdInterfaceGuard();

      bool initializeGuard(  const BAS::String & libName,
                             RWTPtrOrderedVector<LibraryAccessGuard> & libStore,
                             RWMutexLock & storeLock,
                             RWMutexLock ** itemGuard );

      bool initializeAccessGuard(const BAS::String &);

      void acquireAccessGuard();

      void releaseAccessGuard();

      bool initializeOpenGuard(const BAS::String &);

      void acquireOpenGuard();

      void releaseOpenGuard();


  private:

      static RWTPtrOrderedVector<LibraryAccessGuard> libOpenStoreM;

      static RWMutexLock libOpenStoreLockM;

      static RWTPtrOrderedVector<LibraryAccessGuard> libAccessStoreM;

      static RWMutexLock libAccessStoreLockM;

      RWMutexLock * openGuardM;

      RWMutexLock * accessGuardM;
};


}//end name space decl


#endif
