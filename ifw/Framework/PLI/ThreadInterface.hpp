#ifndef PLI_THREADINTERFACE_HPP
#define PLI_THREADINTERFACE_HPP
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
//   Thread interface class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: ThreadInterface.hpp,v $
// $Revision: 1.6 $
// $Author: bt $
// $Date: 2001/08/03 13:15:02 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: ThreadInterface.hpp,v $
// Revision 1.6  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.5  2001/07/26 13:42:08  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.4  2000/09/29 10:16:03  aro
// Tried to fix doc++ comments.
//
// Revision 1.3  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.2  1999/04/19 16:23:34  bt
//
// Revision 1.1  1999/04/16 09:25:56  bt
// Initial version.
//
//==============================================================================

#ifdef STR
  #undef STR
#endif
#ifndef   PLI_STDTHREADINTERFACE_HPP
  #include "PLI/StdThreadInterface.hpp"
#endif
#ifndef   PLG_THREAD_PLUG_IN_HPP
  #include "PLG/ThreadPlugIn.hpp"
#endif
namespace PLI
{

/** This class represents the thread plug in interface.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: ThreadInterface.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.6 $</font></td>
    <td><font size=-1>$Date: 2001/08/03 13:15:02 $</font></td>
    <td><font size=-1>$Author: bt $</font></td>
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
    <dd>ERR_INVALID_REG_BASE_NAME</dd>
    <dd>ERR_DLOPEN_FAILED</dd>
    <dd>ERR_DLSYM_FAILED</dd>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
    <dd>ERR_CREATE_THREAD_FAILED</dd>
    <dd>ERR_INVALID_THREAD_STATE</dd>
    <dd>ERR_THREAD_EXCEPTION</dd>
</dl> 
*/
class ThreadInterface : public StdThreadInterface<PLG::ThreadPlugIn>
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      ThreadInterface();

      /** Constructs a instance to load and generate a base plug in.<br>
        * The plug in function execute() is called in the newly created thread.
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      ThreadInterface(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~ThreadInterface();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      ThreadInterface(ThreadInterface& right);

      const ThreadInterface& operator=(ThreadInterface& right);
};
}
#endif // THREADINTERFACE_HPP

