#ifndef TAM_TRANSIDFILEGENERATOR_HPP
#define TAM_TRANSIDFILEGENERATOR_HPP
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
//   Transaction id file generator class implementation.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: TransIdFileGenerator.hpp,v $
// $Revision: 1.2 $
// $Author: mliebmann $
// $Date: 2001/08/10 08:51:54 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: TransIdFileGenerator.hpp,v $
// Revision 1.2  2001/08/10 08:51:54  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.1  2001/05/15 10:29:41  bt
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

namespace TAM
{
/** This class represents the transaction id file generator object.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TransIdFileGenerator.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.2 $</font></td>
    <td><font size=-1>$Date: 2001/08/10 08:51:54 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                     

    <dl>
    <dt><b>Registry entries</b></dt>
    <dd>FileName</dd>
    <dd>Increment</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>none</dd>
    </dl> 
*/
class TransIdFileGenerator : public TransIdGenerator
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      TransIdFileGenerator();

      /** Constructs the transaction id file generator instance.<br> 
        * @param objectName The string is used for the object registration. */
      TransIdFileGenerator(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~TransIdFileGenerator();

    //@}

    /**@name Public Member Functions */
    //@{

	/// Initialize the transaction id file generator.
	virtual bool startup();

	/// Shutdown the transaction id file generator.
	virtual bool shutdown();

	/// install the transaction id file generator.
	virtual bool install();

	/// uninstall the transaction id file generator.
	virtual bool uninstall();

	/// Returns the next transaction id or if not available a null pointer.
	virtual TransId* nextTransactionId();

    //@}

  private:

    // The following private attributes and functions are used internally.

      BAS::String fileNameM;

      BAS::String fileRegRootNameM;

      BAS::String convTransIdM;

      TransId actualTransIdM;

      TransId actualIncrM;

      TransId checkTransIdM;

      TransId regIncrM;

    // Class members.

      TAM_EXPORT static const BAS::String regFileNameCM;

      TAM_EXPORT static const BAS::String regTransIdCM;

      TAM_EXPORT static const BAS::String regIncrementCM;

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      TransIdFileGenerator(TransIdFileGenerator& r);

      const TransIdFileGenerator& operator=(TransIdFileGenerator& r);

    // Read the configuration values out of the registry.

      virtual bool readRegistry();

    // Increase the transaction id value in the file.

      bool increaseTransId();

    // Final write of the transaction id into the file.

      bool finalTransIdWrite();

    // Read the transaction id from the file.

      bool readTransIdFile();

    // Write the transaction id into the file.

      bool writeTransIdFile(const TransId& id);

};
}
#endif // TRANSIDFILEGENERATOR_HPP

