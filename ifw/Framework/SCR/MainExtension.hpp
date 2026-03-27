#ifndef SCR_MAINEXTENSION_HPP
#define SCR_MAINEXTENSION_HPP

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   The "main" iScript extension
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
//------------------------------------------------------------------------------
// $Log: MainExtension.hpp,v $
// Revision 1.4  2000/10/06 08:23:31  sd
// - line number directive added.
// - Memory leaks in StringAdd removed
// - Constant variable map in MainExtension will be freed now
//
// Revision 1.3  2000/09/26 13:33:04  sd
// - Module SCR is now only dependent from BAS
//
// Revision 1.2  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.1  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
//==============================================================================

#if !defined SCR_EXPORT
 #define SCR_EXPORT 
#endif

#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
#ifndef SCR_EXTENSION_HPP
  #include "SCR/Extension.hpp"
#endif
namespace SCR
{

class MutexVal
{
  public:
    bool        usedM;
    RWMutexLock mutexM;
    MutexVal( bool used = false ) : usedM(used) {};
    MutexVal( const MutexVal& other ) 
      : mutexM()
    {
      usedM = other.usedM;
    };
    const MutexVal operator=( const MutexVal& other )
    {
      usedM = other.usedM;
      return *this;
    }
};


/**<b><tt>MainExtension</tt></b> is the "main" extension for iScript
 */
class MainExtension : public Extension
{
  public:
    /**@name DAT_CustIScriptExt constructors and destructor */
    //@{

    /** Constructor
     */
    MainExtension();

    /** Destructor
     */
    ~MainExtension();

    //@}

    /**@name DAT_CustIScriptExt public methods */
    //@{

    /** Get the name of the extension
     *  @return Reference to the string with the name of the extension
     */
    virtual const BAS::String& extensionName() const;

    /** Get a variable from the "main" extension
     *  @param name The name of the variable
     *  @return Pointer to the variable on success, 0 otherwise
     */
    virtual Variable* variable( const BAS::String& name );

    /** Create a new mutex 
     *  @return Handle for the new mutex (>=0) on success, <0 otherwise
     */
    long mutexCreate();

    /** Destroy a mutex
     *  @param mutexHandle Handle of the mutex to destroy
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool mutexDestroy( long mutexHandle );

    /** Acquire a mutex
     *  @param mutexHandle Handle of the mutex to acquire
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool mutexAcquire( long mutexHandle );

    /** Release a mutex
     *  @param mutexHandle Handle of the mutex to acquire
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool mutexRelease( long mutexHandle );

    //@}

  private:
    // instance members
    RWMutexLock                       mutexTableLockM;
    RWTValOrderedVector<MutexVal> mutexTableM;
    size_t                            mutexesUsedM;

    // class members
    SCR_EXPORT static RWMutexLock     mutexCM;
    SCR_EXPORT static int             instancesCM;
    SCR_EXPORT static VariableMap constantsCM;
};
}
#endif // MAINEXTENSION_HPP
