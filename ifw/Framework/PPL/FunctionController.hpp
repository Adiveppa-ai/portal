#ifndef PPL_FUNCTION_CONTROL_CONTROLLER_HPP
#define PPL_FUNCTION_CONTROL_CONTROLLER_HPP 
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
// Block: PLG
//------------------------------------------------------------------------------
// Module Description:
//  Function Control PlugIn class implementation.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: FunctionController.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2010/11/15 09:23:43 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FunctionController.hpp,v $
// Revision 1.1  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
//==============================================================================

#ifndef   PPL_THREADBASE_HPP
  #include "PPL/ThreadBase.hpp"
#endif
#ifndef   PLI_FUNCTIONCOLLECTION_HPP
  #include "PLI/FunctionCollection.hpp"
#endif
#ifndef   ONLYPOINTER_HPP
  #include "BAS/OnlyPointer.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   BAS_PROC_TIME_HPP
  #include "BAS/ProcTime.hpp"
#endif

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
namespace BAS
{
class String;
}
namespace EDR
{
class Container;
}
namespace PPL
{

/** FunctionControlPlugIn class declaration.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: FunctionController.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2010/11/15 09:23:43 $</font></td>
    <td><font size=-1>$Author: cprabhak $</font></td>
    </tr>
    </table>                                                                          

<p>
<dl>
    <dt><b>Registry entries</b></dt>
         <dd>none</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Messages receive</b></dt>
         <dd>none</dd>
    <dt><b>Errors</b></dt>
         <dd>none</dd>
</dl>

  This class represents the integRate function pool. The function pool is 
  used to hold all functions for one edr format.
*/
class FunctionController : public ThreadBase
{
  public    :

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    FunctionController();

    /** Standard constructor.<br>
        Creates an registered object.
       @param name    Name of the registered object.
    */
    FunctionController(const BAS::String& name,
                              STR::Queue<EDR::Container*>* in,
                              STR::Queue<EDR::Container*>* out);

    /** Standard constructor.<br>
        Creates an registered object.
       @param name    Name of the registered object.
       @param nextPPLObject Pointer to the next pipeline object for processing
    */
    FunctionController(const BAS::String& name,
                              ThreadBase * nextPPLObject);

    /** Destructor. */
    virtual ~FunctionController();
    //@}

    /** Init function which will be called
        to initialize all function pool objects. */
    virtual bool init();

    /** Shutdown function which will be called
        to shutdown all function pool objects. */
    virtual bool shutdown();

	virtual bool startup();

	virtual bool install();

	virtual bool uninstall();

    /** "Threaded" function. <br>
    */ 
    virtual void execute();

    bool processEdrContainer(EdrContainerList* edrList);

    /**@name Plug in state */
    //@{
    
    // write version information
    const void writeModuleVersion() const;

    // check the usability of the plug in
    bool isUsable();

    //@}

    /**@name Class function members*/
    //@{

    /** self test */
    static bool selfTest();
    //@}
    
    RWTValOrderedVector<BAS::String> getRegisteredPluginNames();

    size_t size() const;

    PLI::FunctionInterface * operator [] ( size_t i ) ;
  
    const PLI::FunctionInterface * operator [] ( size_t i ) const ; 


  protected :

  private   :
    
    // Default, copy constructor and assign operator are not implemented. They are
    // private to prevent unintentionally use.
    FunctionController(FunctionController& right);
    const FunctionController& operator=(FunctionController& right);

    BAS::OnlyPointer<PLI::FunctionCollection> functionsM;

    BAS::ProcTime pluginStatM;
};

inline size_t
PPL::FunctionController::size() const
{
  return functionsM->entries();
}


//======================================================================
// inline
//======================================================================
}
#endif // FUNCTION_CONTROL_CONTROLLER_HPP
