
//==============================================================================
//
// Copyright (c) 1996, 2023, Oracle and/or its affiliates. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLI::Base
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
// $RCSfile: StdInterface.cpp $
// $Revision: /cgbubrm_main.pipeline/1 $
// $Author: sumeemis $
// $Date: 2011/08/10 01:09:15 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: PLI::StdInterface.cpp,v $
// Revision 1.26  2011/07/04 15:04:22  sumeemis
// Bug 11815646 - p-10434779 phase ii changes for pipeline parallel loading ecr
//
// Revision 1.25  2000/06/16 13:06:50  clohmann
// Changes for AIX compiler.
//
// Revision 1.24  2000/03/30 08:41:59  jkeckst
// add getPlugInResponse methode for getting the PlugIn Pointer and
// the response for this pointer
//
// Revision 1.23  2000/03/08 14:30:25  clohmann
// Shutdown function added.
//
// Revision 1.22  2000/02/14 11:08:47  bt
// Method init() moved from PLI::DataInterface to PLI::StdInterface.
//
// Revision 1.21  2000/02/14 10:16:20  bt
// Method init() added.
//
// Revision 1.20  2000/01/11 08:40:46  bt
// Changes to support new Makefile Macros. Money++ library names added.
//
// Revision 1.19  1999/12/07 12:01:07  sd
// Define for target operation system HPUX changed.
//
// Revision 1.18  1999/12/07 11:51:14  sd
// Implementation changed to support the HP aCC compiler.
//
// Revision 1.17  1999/10/20 14:54:16  bt
// Usability check added (method isUsable()).
//
// Revision 1.16  1999/10/07 11:09:18  bt
// dlopen() parameter changed from RTLD_LAZY to RTLD_NOW.
//
// Revision 1.15  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.14  1999/04/27 08:11:58  clohmann
//
// Revision 1.6  1999/03/24 09:20:17  bt
// Function call status(stat) changed to setStatus(stat).
//
//==============================================================================


#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   BAS_REGISTRYENTRY_HPP
  #include "BAS/RegistryEntry.hpp"
#endif
#ifndef   PLI_STDINTERFACE_HPP
  #include "PLI/StdInterface.hpp"
#endif
#ifndef PLI_STDINTERFACEGUARD_HPP
  #include "PLI/StdInterfaceGuard.hpp"
#endif
#ifndef PLI_PARALLEL_LOAD_MANAGER_HPP
  #include "PLI/ParallelLoadManager.hpp"
#endif

template <typename T>
const BAS::String PLI::StdInterface<T>::registryParallelLoadManagerCM     ("ParallelLoadManager");


//------------------------------------------------------------------------------
// Constructs a default instance
//------------------------------------------------------------------------------

template <class T>
PLI::StdInterface<T>::StdInterface()
  : BAS::Object(),
    genFunctionNameM (""),
    libNameM (""),
    plugInNameM (""),
    funcAddressM (0),
    libHandleM (0),
    plugInM (0),
    bMultiThreadedLoadM(false)
{
  D_ENTER("PLI::StdInterface::StdInterface()");

  setStatus("ERR_OBJ_NOT_INITIALIZED",
            BAS::Status::critical,
            "PLI::StdInterface");

  isValid(false);
}

//------------------------------------------------------------------------------
// Constructs a instance to load a base plug in object
//------------------------------------------------------------------------------

template <class T>
PLI::StdInterface<T>::StdInterface(const BAS::String& objectName)
  : BAS::Object(objectName),
    genFunctionNameM (""),
    libNameM (""),
    plugInNameM (""),
    funcAddressM (0),
    libHandleM (0),
    plugInM (0),
    bMultiThreadedLoadM(false)
{
  D_ENTER("PLI::StdInterface::StdInterface(const BAS::String&)");
  D_ARG(objectName);

  //----------------------------------------------------------------------
  // Check if this object is registered
  //----------------------------------------------------------------------

  if (isRegistered() == true)
  {
    isValid(true);
  }
  else
  {
    isValid(false);
  }

  //----------------------------------------------------------------------
  // Read the configuration values out of the registry
  //----------------------------------------------------------------------

  if (isValid() == true)
  {
    isValid(readRegistry());
  }

  //----------------------------------------------------------------------
  // Open the shared library and get the address of the generator function
  //----------------------------------------------------------------------

  if (isValid() == true)
  {
    isValid(accessSharedLibrary());
  }
}

//------------------------------------------------------------------------------
// Virtual destructor
//------------------------------------------------------------------------------

// virtual
template <class T>
PLI::StdInterface<T>::~StdInterface()
{
  D_ENTER("PLI::StdInterface::~StdInterface()");
}

//------------------------------------------------------------------------------
// Init function which will be called to initialize the plug in object
//------------------------------------------------------------------------------

// virtual
template <class T> bool
PLI::StdInterface<T>::init()
{
  D_ENTER("PLI::StdInterface::init()");

  if (plugIn() != 0)
  {
    if (plugIn()->init() == false)
    {
      setStatus(plugIn()->status());

      isValid(false);

      return false;
    }
    else
    {
      return true;
    }
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------
// Final init function
//------------------------------------------------------------------------------

// virtual
template <class T> bool
PLI::StdInterface<T>::finalInit()
{
  D_ENTER("PLI::StdInterface::finalInit()");

  if (plugIn() != 0)
  {
    if (plugIn()->finalInit() == false)
    {
      setStatus(plugIn()->status());

      isValid(false);

      return false;
    }
    else
    {
      return true;
    }
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------
// Shutdown function
//------------------------------------------------------------------------------
template <class T> bool
PLI::StdInterface<T>::shutdown()
{
  D_ENTER("PLI::StdInterface::shutdown()");

  if (plugIn() != 0)
  {
	  return plugIn()->shutdown();
  }
  return true;
}

template <class T> bool
PLI::StdInterface<T>::install()
{
  D_ENTER("PLI::StdInterface::install()");

  if (plugIn() != 0)
  {
	  return plugIn()->install();
  }
  return true;
}

template <class T> bool
PLI::StdInterface<T>::startup()
{
  D_ENTER("PLI::StdInterface::startup()");

  if (plugIn() != 0)
  {
	  return plugIn()->startup();
  }
  return true;
}

template <class T> bool
PLI::StdInterface<T>::uninstall()
{
  D_ENTER("PLI::StdInterface::uninstall()");

  if (plugIn() != 0)
  {
	  return plugIn()->uninstall();
  }
  return true;
}


//------------------------------------------------------------------------------
// Return a pointer to the plug in object
//------------------------------------------------------------------------------

// virtual
template <class T> T* 
PLI::StdInterface<T>::plugIn() const
{
  D_ENTER("PLI::StdInterface::plugIn()");

  return plugInM.get();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// virtual
template <class T> T* 
PLI::StdInterface<T>::getPlugInResponse()
{
  D_ENTER("PLI::StdInterface::getPlugInResponse()");

  return plugInM.orphan();
}

//------------------------------------------------------------------------------
// Check the usability of the module
//------------------------------------------------------------------------------

// virtual
template <class T> bool 
PLI::StdInterface<T>::isUsable()
{
  D_ENTER("PLI::StdInterface::isUsable()");

  if (plugIn() != 0)
  {
    return plugIn()->isUsable();
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------
// Read the configuration values out of the registry
//------------------------------------------------------------------------------

// virtual
template <class T> bool 
PLI::StdInterface<T>::readRegistry()
{
  D_ENTER("PLI::StdInterface::readRegistry()");

  const BAS::RegistryEntry* stdIntRegNode = 0;

  const BAS::RegistryEntry* resultRegNode = 0;

  //----------------------------------------------------------------------
  // Get the registry subtree of this object
  //----------------------------------------------------------------------

  stdIntRegNode = registry();

  if (stdIntRegNode == 0)
  {
    D_PRINT("ERROR: registry subtree '" << name() << "' not found" << endl);

    setStatus("ERR_REG_SUBTREE_NOT_FOUND",
              BAS::Status::critical,
              name());

    return false;
  }

  //----------------------------------------------------------------------
  // Get the registry value of the entry 'ModuleName'
  //----------------------------------------------------------------------
  
  resultRegNode = stdIntRegNode->find("ModuleName");

  BAS::String shortLibName;

  if (resultRegNode != 0)
  {
#ifndef WINDOWS
    libNameM      = LIBPREFIX;
#endif

    libNameM     += resultRegNode->value();
    shortLibName += resultRegNode->value();

	// Similarly, for debug we now use '_dbg'
#ifdef _DEBUG
	libNameM     += "_dbg";
#endif
    libNameM     += LIBSUFFIX;
  }
  else
  {
    BAS::String regName = name() + ".ModuleName";

    D_PRINT("ERROR: registry name '" << regName << "' not found" << endl);

    setStatus("ERR_REG_NAME_NOT_FOUND",
              BAS::Status::critical,
              regName);

    return false;
  }

  //----------------------------------------------------------------------
  // Get the registry value of the entry 'ModuleStart'
  //----------------------------------------------------------------------
  
  resultRegNode = stdIntRegNode->find("ModuleStart");

  if (resultRegNode != 0)
  {
    genFunctionNameM = resultRegNode->value();
  }
  else
  {
    genFunctionNameM = shortLibName + "ModuleStart";
  }

  //----------------------------------------------------------------------
  // Get the registry group entry 'Module'
  //----------------------------------------------------------------------
  
  BAS::String regName = name() + ".Module";

  resultRegNode = stdIntRegNode->find("Module");

  if (resultRegNode != 0)
  {
    plugInNameM = regName;
  }
  else
  {
    D_PRINT("ERROR: registry name '" << regName << "' not found" << endl);

    setStatus("ERR_REG_NAME_NOT_FOUND",
              BAS::Status::critical,
              regName);

    return false;
  }

  //----------------------------------------------------------------------
  // Check if 'ParallelLoadManager' entry is present and enabled
  //----------------------------------------------------------------------

  PLI::ParallelLoadManager* loadManager = dynamic_cast<PLI::ParallelLoadManager*>(find(rootName() + "." + registryParallelLoadManagerCM));

  if ( loadManager && loadManager->enabled() )
  {
    bMultiThreadedLoadM = true;
  }

  return true;
}

//------------------------------------------------------------------------------
// Open the shared library and get the address of the generator function
//------------------------------------------------------------------------------

template <class T> bool 
PLI::StdInterface<T>::accessSharedLibrary()
{
  D_ENTER("PLI::StdInterface::accessSharedLibrary()");

  if ( bMultiThreadedLoadM )
  {
    if ( initializeOpenGuard(libNameM) == false )
    {
      BAS::StringList argList;

      argList.append(libNameM);

      setStatus("ERR_ACQUIRE_GUARD_FAILED",
                BAS::Status::critical,
                argList);

      return false;
    }

    //acquire a lock specific to the library    
    acquireOpenGuard(); 
    
    //only one thread goes ahead - others wait here
  }

  //----------------------------------------------------------------------
  // Open the shared library
  //----------------------------------------------------------------------
#ifdef WINDOWS
  libHandleM = LoadLibrary(libNameM.data());

#else
  libHandleM = dlopen(libNameM.data(),
                        RTLD_NOW | RTLD_GLOBAL);
#endif //#ifdef WINDOWS

  if (libHandleM == 0)
  {
#ifdef WINDOWS
    char* dlErrMsg = NULL;

#else
    char* dlErrMsg = dlerror();
#endif //#ifdef WINDOWS
   
    BAS::StringList errList;

    errList.append(libNameM);

    errList.append(dlErrMsg ? dlErrMsg : "");
  
    D_PRINT("ERROR: cannot open shared library '" <<
            errList[0] << "'; " << errList[1] << endl);

    setStatus("ERR_DLOPEN_FAILED",
              BAS::Status::critical,
              errList);

    if ( bMultiThreadedLoadM )
    {
      releaseOpenGuard();
    }

    return false;
  }

  //----------------------------------------------------------------------
  // Get the address of the generator function in the shared library
  //----------------------------------------------------------------------
#ifdef WINDOWS
  funcAddressM = GetProcAddress((HINSTANCE)libHandleM, genFunctionNameM.data());

#else
  funcAddressM = ::dlsym(libHandleM,
                         genFunctionNameM.data());
#endif //#ifdef WINDOWS

  if (funcAddressM == 0)
  {
    BAS::StringList errList;

    errList.append(genFunctionNameM);

#ifdef WINDOWS
    char* dlErrMsg = NULL;

#else
    char* dlErrMsg = dlerror();
#endif //#ifdef WINDOWS

    errList.append(dlErrMsg ? dlErrMsg : "");
  
    D_PRINT("ERROR: cannot get the address of the generator function '" <<
            errList[0] << "'; " << errList[1] << endl);

    setStatus("ERR_DLSYM_FAILED",
              BAS::Status::critical,
              errList);

    if ( bMultiThreadedLoadM )
    {
      releaseOpenGuard();
    }
    return false;
  }

  if ( bMultiThreadedLoadM )
  {
    releaseOpenGuard();
  }

  return true;
}

//------------------------------------------------------------------------------
// Generate the base plug in instance
//------------------------------------------------------------------------------

// virtual
template <class T> bool 
PLI::StdInterface<T>::generateBasePlugIn()
{
  D_ENTER("PLI::StdInterface::generateBasePlugIn()");

  bool bReturnValue = true;

  if ( bMultiThreadedLoadM )
  {
    if ( initializeAccessGuard(libNameM) == false )
    {
      BAS::StringList argList;

      argList.append(libNameM);

      setStatus("ERR_ACQUIRE_GUARD_FAILED",
                BAS::Status::critical,
                argList);

      return false;
    }

    //acquire a lock specific to the library
    acquireAccessGuard();

    //only one thread goes ahead - others wait here
  }
  
  BasePlugInFuncPtr baseGenFunc = (BasePlugInFuncPtr) funcAddressM;

  plugInM = dynamic_cast <T*> (baseGenFunc(plugInNameM));

  if (plugIn() == 0)
  {
    D_PRINT("ERROR: module '" <<
            plugInNameM << "' has a wrong type" << endl);

    setStatus("ERR_PLUGIN_TYPE_INVALID",
              BAS::Status::critical,
              plugInNameM);

    bReturnValue = false;
  }
  else if (plugIn()->isValid() == false)
  {
    D_PRINT("ERROR: invalid plug in object '" <<
            plugInNameM << "'" << endl);

    setStatus(plugIn()->status());

    bReturnValue = false;
  }

  if ( bMultiThreadedLoadM )
  {
    releaseAccessGuard();
  }

  return bReturnValue;
}

//------------------------------------------------------------------------------
// Self test
//------------------------------------------------------------------------------

template <class T> bool 
PLI::StdInterface<T>::selfTest()
{
  D_ENTER_F("PLI::StdInterface::selfTest()");

  cerr << endl << "Starting self test of PLI::StdInterface" << endl << endl;

  BAS::RegisteredObject::rootName("integrate");

  BAS::RegistryEntry root(BAS::RegisteredObject::rootName());
  root.makeRootNode();

  BAS::RegisteredObject::registry(&root);

  BAS::RegistryEntryPtr stdGroup = new BAS::RegistryEntry("StandardInterface");
  stdGroup->addEntry("ModuleName","xyzlib");
  stdGroup->addEntry("ModuleStart","funcxyz");

  BAS::RegistryEntryPtr plugIn = new BAS::RegistryEntry("Module");
  stdGroup->addEntry(plugIn);

  root.addEntry(stdGroup);

  if (root.isValid() == true)
  {
    PLI::StdInterface<T> stdInt("integrate.StandardInterface");

    if (stdInt.isValid() == false)
    {
      if ((stdInt.libNameM.isNull() == true) || 
          (stdInt.genFunctionNameM.isNull() == true) || 
          (stdInt.plugInNameM.isNull() == true))
      {
        cerr << endl << "PLI::StdInterface::selfTest: ";
        cerr << "invalid registry !!!" << endl;
        cerr << stdInt.status() << endl << endl;

        return false;
      }
    }
    else
    {
      cerr << endl << "PLI::StdInterface::selfTest: ";
      cerr << "expected errors not occurred !!!" << endl << endl;

      return false;
    }
  }
  else
  {
    cerr << endl << "PLI::StdInterface::selfTest: ";
    cerr << "invalid registry - parse failed !!!" << endl << endl;

    return false;
  }

  return true;
}

