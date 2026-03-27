#ifndef TAM_TRANSIDDBGENERATOR_HPP
#define TAM_TRANSIDDBGENERATOR_HPP
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
//   Transaction id database generator class implementation.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: TransIdDbGenerator.hpp,v $
// $Revision: 1.2 $
// $Author: mliebmann $
// $Date: 2001/08/10 08:51:54 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: TransIdDbGenerator.hpp,v $
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

#ifndef   TAM_TRANSIDGENERATOR_HPP
  #include "TAM/TransIdGenerator.hpp"
#endif
#ifndef   DBC_DATABASEPLUGIN_HPP
  #include "DBC/DatabasePlugIn.hpp"
#endif

namespace TAM
{
/** This class represents the transaction id database generator object.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TransIdDbGenerator.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.2 $</font></td>
    <td><font size=-1>$Date: 2001/08/10 08:51:54 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                     

    <dl>
    <dt><b>Registry entries</b></dt>
    <dd>TransactionManagerDataConnection</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>none</dd>
    </dl> 
*/
class TransIdDbGenerator : public TransIdGenerator
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      TransIdDbGenerator();

      /** Constructs the transaction id database generator instance.<br> 
        * @param objectName The string is used for the object registration. */
      TransIdDbGenerator(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~TransIdDbGenerator();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Initialize the transaction id database generator.
      virtual bool startup();

      /// Shutdown the transaction id database generator.
      virtual bool shutdown();

      /// Observer pattern update function (reconnect with the database).
      virtual void update(const BAS::String& name);

	using BAS::Object::update;

      /// Returns the next transaction id or if not available a null pointer.
      virtual TransId* nextTransactionId();

    //@}

  private:

    // The following private attributes and functions are used internally.

      DBC::DatabasePlugIn* dataPlugInM;

      RWDBConnection connectionM;

      RWDBTable tamTabM;

      RWDBSelector tamSelM;

      RWDBReader tamReaderM;

      RWDBUpdater tamUpdaterM;

      RWDBAssignment tamAssignM;

      RWDBResult tamResultM;

      RWDBColumn tamColIdM;

      RWDBColumn tamColIncrM;

      BAS::String tamIdStrM;

      BAS::String tamIncrStrM;

      TransId actualTransIdM;

      TransId actualIncrM;

      TransId checkTransIdM;

      bool initializedM;

    // Class members.

      TAM_EXPORT static const BAS::String regDataPoolCM;

      TAM_EXPORT static const BAS::String regDataConnectCM;

      TAM_EXPORT static const BAS::String regModuleCM;

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      TransIdDbGenerator(TransIdDbGenerator& right);

      const TransIdDbGenerator& operator=(TransIdDbGenerator& right);

    // Read the configuration values out of the registry.

      virtual bool readRegistry();

    // Read the transaction id and increment values from the database table.

      bool readTransIdAndIncrement();

    // Increase the transaction id value in the database table.

      bool increaseTransId();

    // Insert a default transaction id and increment if the table is empty.

      bool insertTransIdAndIncrement();

    // Final update of the transaction id value in the database table.

      bool finalTransIdUpdate();

};
}
#endif // TRANSIDDBGENERATOR_HPP

