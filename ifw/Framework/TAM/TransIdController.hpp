#ifndef TAM_TRANSIDCONTROLLER_HPP
#define TAM_TRANSIDCONTROLLER_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: TAM
//
//------------------------------------------------------------------------------
// Module Description:
//   Transaction id controller class implementation.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: TransIdController.hpp,v $
// $Revision: 1.2 $
// $Author: mliebmann $
// $Date: 2001/08/10 08:51:54 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: TransIdController.hpp,v $
// Revision 1.2  2001/08/10 08:51:54  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.1  2001/04/12 16:35:03  bt
// Initial version.
//
//==============================================================================

#if !defined TAM_EXPORT
  #if defined(WINDOWS)
    #if !defined(TAM_INTERNAL)
      #define TAM_EXPORT __declspec(dllimport)
    #else
      #define TAM_EXPORT __declspec(dllexport)
    #endif
  #else
    #define TAM_EXPORT 
  #endif
#endif

#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_REGISTRYENTRY_HPP
  #include "BAS/RegistryEntry.hpp"
#endif
#ifndef   BAS_OBJECT_H
  #include "BAS/Object.hpp"
#endif
#ifndef   TAM_TRANSIDGENERATOR_HPP
  #include "TAM/TransIdGenerator.hpp"
#endif

namespace TAM
{
/** This class represents the transaction id controller object.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TransIdController.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.2 $</font></td>
    <td><font size=-1>$Date: 2001/08/10 08:51:54 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                     

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
*/
class TransIdController : public BAS::Object
{
  public:

    /**@name Public Constructors */
    //@{

      /** Constructs a default instance.
        * @param setObjStatus set object registration status or not, default is true
	*/
      TransIdController(const bool setObjStatus=true);

      /** Constructs the transaction id controller instance.<br> 
        * @param objectName The string is used for the object registration. */
      TransIdController(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~TransIdController();

    //@}

	/**@name BAS::Object functions */
	//@{
	/** Shutdown function which will be called
	 * to shutdown the transaction id generator. */
	bool shutdown();

	/** Start up and initialize the trans id controller 
	 */
	bool startup();

	/** Install the trans id controller
	 */
	bool install();

	/** Uninstall the transid controller
	 */
	bool uninstall();
	//@}

    /**@name Public Member Functions */
    //@{


      /// Returns the next available transaction id.
      TransId* nextTransactionId();

    //@}

  private:

    // The following private attributes and functions are used internally.

      RWMutexLock transIdCtrlLockerM;

      TransIdGenerator* transIdGeneratorM;

      const BAS::RegistryEntry* registrySubTreeM;

      bool inputSourceFileM;

    // Class members.

      TAM_EXPORT static const BAS::String regInputSrcCM;

      TAM_EXPORT static const BAS::String regInputSrcValFileCM;

      TAM_EXPORT static const BAS::String regInputSrcValDatabaseCM;

      TAM_EXPORT static const BAS::String regTransIdGeneratorCM;

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      TransIdController(TransIdController& right);

      const TransIdController& operator=(TransIdController& right);

    // Read the configuration values out of the registry.

      virtual bool readRegistry();

    // Create the transaction id generator object.

      bool createTransIdGenerator();
};
}
#endif // TRANSIDCONTROLLER_HPP

