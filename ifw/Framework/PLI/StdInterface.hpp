#ifndef PLI_STDINTERFACE_HPP
#define PLI_STDINTERFACE_HPP
//==============================================================================
//
// Copyright (c) 1996, 2011, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//
//------------------------------------------------------------------------------
// Module Description:
//   StdInterface (standard plug in interface) class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: StdInterface.hpp $
// $Revision: /cgbubrm_main.pipeline/1 $
// $Author: sumeemis $
// $Date: 2011/08/10 01:09:15 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: StdInterface.hpp,v $
// Revision 1.28  2011/07/04 15:26:01  sm
// Bug 11815646 - p-10434779 phase ii changes for pipeline parallel loading ecr
//
// Revision 1.27  2000/09/29 10:57:46  aro
// Tried to fix doc++ comments.
//
// Revision 1.26  2000/06/15 13:25:26  bt
// Changes for AIX xlC V366.
//
// Revision 1.25  2000/03/30 08:41:59  jkeckst
// add getPlugInResponse methode for getting the PlugIn Pointer and
// the response for this pointer
//
// Revision 1.24  2000/03/08 14:30:25  clohmann
// Shutdown function added.
//
// Revision 1.23  2000/02/14 11:08:47  bt
// Method init() moved from DataInterface to StdInterface.
//
// Revision 1.22  2000/02/14 10:16:20  bt
// Method init() added.
//
// Revision 1.21  2000/01/11 08:40:46  bt
// Changes to support new Makefile Macros. Money++ library names added.
//
// Revision 1.20  1999/12/07 12:01:07  sd
// Define for target operation system HPUX changed.
//
// Revision 1.19  1999/12/07 11:51:14  sd
// Implementation changed to support the HP aCC compiler.
//
// Revision 1.18  1999/11/10 09:26:47  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.17  1999/10/20 14:54:16  bt
// Usability check added (method isUsable()).
//
// Revision 1.16  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.15  1999/04/19 13:00:50  bt
//
// Revision 1.1  1999/03/12 16:12:12  bt
// Initial version of base class StdInterface.
//
//==============================================================================
#ifndef WINDOWS
#include <dlfcn.h>
#endif //#ifndef WINDOWS

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   ONLYPOINTER_HPP
  #include "BAS/OnlyPointer.hpp"
#endif
#ifndef   BAS_OBJECT_H
  #include "BAS/Object.hpp"
#endif
#ifndef   PLG_STDPLUGIN_HPP
  #include "PLG/StdPlugIn.hpp"
#endif
#ifndef PLI_STDINTERFACEGUARD_HPP
  #include "PLI/StdInterfaceGuard.hpp"
#endif

namespace PLI
{
/** The base class for all plug in interfaces.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: StdInterface.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_main.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2011/08/10 01:09:15 $</font></td>
    <td><font size=-1>$Author: sumeemis $</font></td>
    </tr>
    </table>      

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>ModuleName (without prefix 'lib' and suffix 'xxd.so')</dd>
    <dd>ModuleStart</dd>
    <dd>Module</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_REG_NAME_NOT_FOUND</dd>
    <dd>ERR_DLOPEN_FAILED</dd>
    <dd>ERR_DLSYM_FAILED</dd>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
</dl> 
*/
template <class T>
class StdInterface : public BAS::Object , protected StdInterfaceGuard
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      StdInterface();

      /** Constructs a instance to load a base plug in.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      StdInterface(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~StdInterface();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Init function which will be called to initialize the plug in object.
      virtual bool init();

      /// Final init function.
      virtual bool finalInit();

      /// Shutdown function which will be called to shutdown the plug in object.
      virtual bool shutdown();

	bool install();

	bool uninstall();

	bool startup();

      /// Returns a pointer to the plug in object or if invalid a null pointer.
      virtual T* plugIn() const;

      /** Returns a pointer to the plug in object or if invalid a null pointer.
        After this call no one can use the plugIn() methode.
      **/
      virtual T* getPlugInResponse();

      /// Check the usability of the module.
      virtual bool isUsable();

    //@}

    /**@name Static Public Member Functions */
    //@{

      /** Self test.
        * @return <tt>true</tt>: self test was successful<br>
        *         <tt>false</tt>: unsuccessful */
      static bool selfTest();

    //@}

  protected:

      /// Generate the base plug in instance.
      virtual bool generateBasePlugIn();

      BAS::String plugInNameM;

      void* funcAddressM;

      BAS::OnlyPointer<T> plugInM;

  private:

    // The following private attributes and functions are used internally.

      typedef PLG::StdPlugIn*
      (*BasePlugInFuncPtr)(const BAS::String& objectName);

      BAS::String genFunctionNameM;

      BAS::String libNameM;

      bool bMultiThreadedLoadM;

      void* libHandleM;

      static const BAS::String registryParallelLoadManagerCM;

    // Read the configuration values out of the registry.

      virtual bool readRegistry();

    // Open the shared library and get the address of the generator function.

      bool accessSharedLibrary();

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      StdInterface(StdInterface<T>& right);

      const StdInterface<T>& operator=(StdInterface<T>& right);
};

//------------------------------------------------------------------------------
// Include the cpp file if INC_TEMPL_DEFS is defined
// (for template instantiation at compile time)
//------------------------------------------------------------------------------
}
#ifdef INC_TEMPL_DEFS
#include "PLI/StdInterface.cpp"
#endif

#endif // STDINTERFACE_HPP

