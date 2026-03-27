#ifndef PLI_FUNCTIONCOLLECTION_HPP
#define PLI_FUNCTIONCOLLECTION_HPP
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
// Block: Base
//
//------------------------------------------------------------------------------
// Module Description:
//   FunctionCollection class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: FunctionCollection.hpp,v $
// $Revision: 1.9 $
// $Author: aro $
// $Date: 2000/09/29 10:57:46 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: FunctionCollection.hpp,v $
// Revision 1.9  2000/09/29 10:57:46  aro
// Tried to fix doc++ comments.
//
// Revision 1.8  2000/03/08 14:30:25  clohmann
// Shutdown function added.
//
// Revision 1.7  2000/02/14 10:16:20  bt
// Method init() added.
//
// Revision 1.6  1999/10/20 14:54:16  bt
// Usability check added (method isUsable()).
//
// Revision 1.5  1999/09/06 14:17:42  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
//
// Revision 1.4  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.3  1999/03/29 08:12:38  bt
//
// Revision 1.1  1999/03/25 17:09:32  bt
// Initial version.
//
//==============================================================================


#ifndef   COLLECTION_HPP
  #include "BAS/Collection.hpp"
#endif
#ifndef   BAS_CONTROLLERIF_H
  #include "BAS/ControllerIf.hpp"
#endif
#ifndef   PLI_FUNCTIONINTERFACE_HPP
  #include "PLI/FunctionInterface.hpp"
#endif


//------------------------------------------------------------------------------
// Explicit instantiation of base class BAS::OnlyPointer
//------------------------------------------------------------------------------

#ifndef INC_TEMPL_DEFS
namespace BAS
{
  template class OnlyPointer<PLI::FunctionInterface>;
}
#endif
namespace PLI
{
/** This class represents a collection of function plug in interfaces.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: FunctionCollection.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.9 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 10:57:46 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
    </tr>
    </table>      

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>FunctionPool</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_INVALID_REG_BASE_NAME</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
</dl> 
*/
	class FunctionCollection : public BAS::Collection<FunctionInterface>,
	public BAS::ControllerIf
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      FunctionCollection();

      /** Constructs a collection of function plug in interfaces.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      FunctionCollection(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~FunctionCollection();

    //@}

    /**@name Public Member Functions */
    //@{

      /** Init function which will be called
        * to initialize all function interfaces. */
      virtual bool init();

      /** Final init function. */
      virtual bool finalInit();

      /** Shutdown function which will be called
        * to shutdown all function interfaces. */
      virtual bool shutdown();
	
	virtual bool startup();
	
	virtual bool install();

	virtual bool uninstall();

      /// Check the usability of all function modules.
      virtual bool isUsable();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      FunctionCollection(FunctionCollection& right);

      const FunctionCollection& operator=(FunctionCollection& right);
};
}
#endif // FUNCTIONCOLLECTION_HPP

