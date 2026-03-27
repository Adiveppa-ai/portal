#ifndef TAM_TRANSIDGENERATOR_HPP
#define TAM_TRANSIDGENERATOR_HPP

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
//   Base class for the transaction id generator.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: TransIdGenerator.hpp,v $
// $Revision: 1.2 $
// $Author: mliebmann $
// $Date: 2001/08/10 08:51:54 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: TransIdGenerator.hpp,v $
// Revision 1.2  2001/08/10 08:51:54  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.1  2001/04/12 16:35:03  bt
// Initial version.
//
//==============================================================================

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
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif

namespace TAM
{
/** This class represents the transaction id generator base object.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TransIdGenerator.hpp,v $</font></td>
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
class TransIdGenerator : public BAS::Object
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      TransIdGenerator();

      /** Constructs the transaction id generator base instance.<br> 
        * @param objectName The string is used for the object registration. */
      TransIdGenerator(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~TransIdGenerator();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Initialize the transaction id generator.
      virtual bool startup();

      /// Shutdown the transaction id generator.
      virtual bool shutdown();

	bool install();

	bool uninstall();

      /// Returns the next transaction id or if not available a null pointer.
      virtual TransId* nextTransactionId();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      TransIdGenerator(TransIdGenerator& right);

      const TransIdGenerator& operator=(TransIdGenerator& right);
};
}
#endif // TRANSIDGENERATOR_HPP

