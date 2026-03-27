
//==============================================================================
//
// 1998,1999 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: INT
//
//------------------------------------------------------------------------------
// Module Description:
//   Standard thread interface class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: StdThreadInterface.cpp $
// $Revision: /cgbubrm_mainbrm.pipeline/1 $
// $Author: ashutask $
// $Date: 2017/07/07 05:45:35 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: PLI::StdThreadInterface.cpp,v $
// Revision 1.18  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.17  2000/10/04 08:37:33  aro
// Patches to reduce future errors on HP/UX.
//
// Revision 1.16  2000/02/24 14:30:46  aro
// Patches to reduce future errors on HP/UX.
//
// Revision 1.15  2000/02/23 14:18:34  bt
// Include BAS::Trace.hpp added.
//
// Revision 1.14  1999/10/20 14:54:16  bt
// Usability check added (method isUsable()).
//
// Revision 1.13  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.12  1999/04/27 13:15:37  bt
// class BAS::Thread added.
//
// Revision 1.1  1999/03/29 16:18:38  bt
// Initial version.
//
//==============================================================================



#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   PLI_STDTHREADINTERFACE_HPP
  #include "PLI/StdThreadInterface.hpp"
#endif


//------------------------------------------------------------------------------
// Constructs a default instance
//------------------------------------------------------------------------------

template <class T>
PLI::StdThreadInterface<T>::StdThreadInterface()
  : PLI::StdInterface<T> (),
    threadM (this)
{
  D_ENTER("PLI::StdThreadInterface::StdThreadInterface()");
}

//------------------------------------------------------------------------------
// Constructs a instance to load and generate a base plug in thread
//------------------------------------------------------------------------------

template <class T>
PLI::StdThreadInterface<T>::StdThreadInterface(const BAS::String& objectName)
  : PLI::StdInterface<T> (objectName),
    threadM (this)
{
  D_ENTER("PLI::StdThreadInterface::StdThreadInterface(const BAS::String&)");
  D_ARG(objectName);

  //----------------------------------------------------------------------
  // Generate the base plug in instance
  //----------------------------------------------------------------------

  if (this->isValid() == true)
  {
    this->isValid(this->generateBasePlugIn());
  }

  //----------------------------------------------------------------------
  // Create a thread instance and call the plug in function execute()
  //----------------------------------------------------------------------

  if (this->isValid() == true)
  {
    this->isValid(threadM.createAndStartThread(
                            rwMakeFunctor0M(T,*(this->plugIn()),
                                            void,&T::execute)));
  }
}

//------------------------------------------------------------------------------
// Constructs a instance to load and generate a stream plug in thread
//------------------------------------------------------------------------------

template <class T>
PLI::StdThreadInterface<T>::
StdThreadInterface(const BAS::String& objectName,
                       STR::Queue<EDR::Container*>* queue): 
		      PLI::StdInterface<T> (objectName),
                      threadM(this)
{
  D_ENTER("PLI::StdThreadInterface::"
          "PLI::StdThreadInterface(const BAS::String&,"
          "STR::Queue<EDR::Container*>*)");
  D_ARG(objectName);

  //----------------------------------------------------------------------
  // Generate the stream plug in instance
  //----------------------------------------------------------------------

  if (this->isValid() == true)
  {
    this->isValid(generateStreamPlugIn(queue));
  }

  //----------------------------------------------------------------------
  // Create a thread instance and call the plug in function execute()
  //----------------------------------------------------------------------

  if (this->isValid() == true)
  {
    this->isValid(threadM.createAndStartThread(
                            rwMakeFunctor0M(T,*(this->plugIn()),
                                            void,&T::execute)));
  }
}

//------------------------------------------------------------------------------
// Constructs a instance to load and generate a control plug in thread
//------------------------------------------------------------------------------

template <class T>
PLI::StdThreadInterface<T>::
StdThreadInterface(const BAS::String& objectName,
                       STR::Queue<EDR::Container*>* inputQueue,
                       STR::Queue<EDR::Container*>* outputQueue)
  : PLI::StdInterface<T> (objectName),
    threadM (this)
{
  D_ENTER("PLI::StdThreadInterface::"
          "PLI::StdThreadInterface(const BAS::String&,"
          "STR::Queue<EDR::Container*>*,STR::Queue<EDR::Container*>*)");
  D_ARG(objectName);

  //----------------------------------------------------------------------
  // Generate the control plug in instance
  //----------------------------------------------------------------------

  if (this->isValid() == true)
  {
    this->isValid(generateControlPlugIn(inputQueue,outputQueue));
  }

  //----------------------------------------------------------------------
  // Create a thread instance and call the plug in function execute()
  //----------------------------------------------------------------------

  if (this->isValid() == true)
  {
    this->isValid(threadM.createAndStartThread(
                            rwMakeFunctor0M(T,*(this->plugIn()),
                                            void,&T::execute)));
  }
}

//------------------------------------------------------------------------------
// Virtual destructor
//------------------------------------------------------------------------------

// virtual
template <class T>
PLI::StdThreadInterface<T>::~StdThreadInterface()
{
  D_ENTER("PLI::StdThreadInterface::~StdThreadInterface()");

  //----------------------------------------------------------------------
  // Request cancellation and wait for the thread to complete execution
  //----------------------------------------------------------------------

  this->isValid(threadM.cancelAndJoinThread());
}

//------------------------------------------------------------------------------
// Request an abort to perform the next shut down immediately
//------------------------------------------------------------------------------

// virtual
template <class T> void 
PLI::StdThreadInterface<T>::requestAbort()
{
  D_ENTER("PLI::StdThreadInterface::requestAbort()");

  if (this->plugIn() != 0)
  {
    this->plugIn()->requestAbort();
  }
}

//------------------------------------------------------------------------------
// Generate the stream plug in instance
//------------------------------------------------------------------------------

template <class T> bool 
PLI::StdThreadInterface<T>::
generateStreamPlugIn(STR::Queue<EDR::Container*>* queue)
{
  D_ENTER("PLI::StdThreadInterface::"
          "generateStreamPlugIn(STR::Queue<EDR::Container*>*)");

  StreamPlugInFuncPtr streamGenFunc = (StreamPlugInFuncPtr) this->funcAddressM;

  this->plugInM = dynamic_cast <T*> (streamGenFunc(this->plugInNameM,
                                                   queue));

  if (this->plugIn() == 0)
  {
    D_PRINT("ERROR: cannot create the plug in object '" <<
            this->plugInNameM << "' (invalid (NULL) pointer)" << endl);

    setStatus("ERR_CREATE_OBJECT_FAILED",
              BAS::Status::critical,
              this->plugInNameM);

    return false;
  }
  else if (this->plugIn()->isValid() == false)
  {
    D_PRINT("ERROR: invalid plug in object '" <<
            this->plugInNameM << "'" << endl);

    this->setStatus(this->plugIn()->status());

    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
// Generate the control plug in instance
//------------------------------------------------------------------------------

template <class T> bool 
PLI::StdThreadInterface<T>::
generateControlPlugIn(STR::Queue<EDR::Container*>* inputQueue,
                      STR::Queue<EDR::Container*>* outputQueue)
{
  D_ENTER("PLI::StdThreadInterface::"
          "generateControlPlugIn(STR::Queue<EDR::Container*>*,"
          "STR::Queue<EDR::Container*>*)");

  ControlPlugInFuncPtr controlGenFunc = (ControlPlugInFuncPtr) this->funcAddressM;

  this->plugInM = dynamic_cast <T*> (controlGenFunc(this->plugInNameM,
                                                    inputQueue,
                                                    outputQueue));

  if (this->plugIn() == 0)
  {
    D_PRINT("ERROR: cannot create the plug in object '" <<
            this->plugInNameM << "' (invalid (NULL) pointer)" << endl);

    setStatus("ERR_CREATE_OBJECT_FAILED",
              BAS::Status::critical,
              this->plugInNameM);

    return false;
  }
  else if (this->plugIn()->isValid() == false)
  {
    D_PRINT("ERROR: invalid plug in object '" <<
            this->plugInNameM << "'" << endl);

    setStatus(this->plugIn()->status());

    return false;
  }

  return true;
}

