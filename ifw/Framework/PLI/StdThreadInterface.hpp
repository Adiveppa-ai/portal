#ifndef PLI_STDTHREADINTERFACE_HPP
#define PLI_STDTHREADINTERFACE_HPP
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
// $RCSfile: StdThreadInterface.hpp,v $
// $Revision: 1.17 $
// $Author: aro $
// $Date: 2000/09/29 10:16:03 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: StdThreadInterface.hpp,v $
// Revision 1.17  2000/09/29 10:16:03  aro
// Tried to fix doc++ comments.
//
// Revision 1.16  2000/06/15 13:30:39  clohmann
// Changes for AIX.
//
// Revision 1.15  2000/02/11 16:51:44  bt
// Function Control Interface Collection added.
//
// Revision 1.14  1999/11/10 09:26:23  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.13  1999/10/20 14:54:16  bt
// Usability check added (method isUsable()).
//
// Revision 1.12  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.11  1999/04/27 13:15:38  bt
// class BAS::Thread added.
//
// Revision 1.1  1999/03/29 16:18:38  bt
// Initial version.
//
//==============================================================================

#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   BAS_THREAD_HPP
  #include "BAS/Thread.hpp"
#endif
#ifndef   PLI_STDINTERFACE_HPP
  #include "PLI/StdInterface.hpp"
#endif

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
namespace EDR
{
class Container;
}
namespace PLI
{

/** This class represents the standard thread interface.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: StdThreadInterface.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.17 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 10:16:03 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
    </tr>
    </table>  

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>ModuleName (without prefix 'lib' and suffix 'xxd.so')</dd>
    <dd>ModuleStart</dd>
    <dd>Module</dd>
    <dt><b>Messages send</b></dt>
    <dd>MSG_INVALID_THREAD_STATE</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_REG_NAME_NOT_FOUND</dd>
    <dd>ERR_DLOPEN_FAILED</dd>
    <dd>ERR_DLSYM_FAILED</dd>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
    <dd>ERR_CREATE_THREAD_FAILED</dd>
    <dd>ERR_INVALID_THREAD_STATE</dd>
    <dd>ERR_THREAD_EXCEPTION</dd>
</dl> 
*/
template <class T>
class StdThreadInterface : public StdInterface<T>
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      StdThreadInterface();

      /** Constructs a instance to load and generate a base plug in.<br> 
        * The plug in function execute() is called in the newly created thread.
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      StdThreadInterface(const BAS::String& objectName);

      /** Constructs a instance to load and generate a stream plug in.<br> 
        * The plug in function execute() is called in the newly created thread.
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      StdThreadInterface(const BAS::String& objectName,
                             STR::Queue<EDR::Container*>* queue);

      /** Constructs a instance to load and generate a control plug in.<br> 
        * The plug in function execute() is called in the newly created thread.
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      StdThreadInterface(const BAS::String& objectName,
                             STR::Queue<EDR::Container*>* inputQueue,
                             STR::Queue<EDR::Container*>* outputQueue);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~StdThreadInterface();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Request an abort to perform the next shut down immediately.
      virtual void requestAbort();

    //@}

  private:

    // The following private attributes and functions are used internally.

      typedef PLG::StdPlugIn*
      (*StreamPlugInFuncPtr)(const BAS::String& objectName,
                             STR::Queue<EDR::Container*>* queue);

      typedef PLG::StdPlugIn*
      (*ControlPlugInFuncPtr)(const BAS::String& objectName,
                              STR::Queue<EDR::Container*>* inputQueue,
                              STR::Queue<EDR::Container*>* outputQueue);

      BAS::Thread threadM;

    // Generate the stream plug in instance.

      bool generateStreamPlugIn(STR::Queue<EDR::Container*>* queue);

    // Generate the control plug in instance.

      bool generateControlPlugIn(STR::Queue<EDR::Container*>* inputQueue,
                                 STR::Queue<EDR::Container*>* outputQueue);

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      StdThreadInterface(StdThreadInterface<T>& right);

      const StdThreadInterface<T>& operator=(StdThreadInterface<T>& right);
};

//------------------------------------------------------------------------------
// Include the cpp file if INC_TEMPL_DEFS is defined
// (for template instantiation at compile time)
//------------------------------------------------------------------------------
}
#ifdef INC_TEMPL_DEFS
#include "PLI/StdThreadInterface.cpp"
#endif

#endif // STDTHREADINTERFACE_HPP

