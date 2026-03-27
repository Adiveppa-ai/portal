#ifndef PLG_TRANSACTIONPLUGIN_HPP
#define PLG_TRANSACTIONPLUGIN_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Basis
//------------------------------------------------------------------------------
// Module Description:
//  StdPlugIn class implementation.
//
//  This class is the base class for all PlugIn Implementations. Every PlugIn
//  must inhereted from this class. 
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: TransactionPlugIn.hpp,v $
// $Revision: 1.8 $
// $Author: mliebmann $
// $Date: 2001/08/31 09:37:45 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TransactionPlugIn.hpp,v $
// Revision 1.8  2001/08/31 09:37:45  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.7  2001/08/28 12:04:23  jkeckst
// PETS 37618 code review 08.2001
//
// Revision 1.6  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.5  2001/05/31 10:32:04  mliebmann
// central getEdrFactory for all PlugIn added
//
// Revision 1.4  2001/05/17 08:00:00  bt
// Online documentation added.
//
// Revision 1.3  2001/05/03 16:02:25  bt
// Format renamed to Pipeline.
//
// Revision 1.2  2001/04/26 09:28:33  mliebmann
// GenericIO: TAM added
//
// Revision 1.1  2001/04/25 09:36:34  mliebmann
// new transaction plugin
//
//          
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   PLG_STDPLUGIN_HPP
  #include "PLG/StdPlugIn.hpp"
#endif
namespace TAM
{
class ManagerRestrictedIf;
}
namespace EDR
{
class Factory;
}
namespace PLG
{
/** TransactionPlugIn Class declaration.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TransactionPlugIn.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.8 $</font></td>
    <td><font size=-1>$Date: 2001/08/31 09:37:45 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>  

<pre>
    <b>Registry entries</b>
         none
    <b>Messages send</b>
         none
    <b>Messages receive</b>
         none
    <b>Errors</b>
         none

    This is the base class for every integRate input and output Device
    and stream module. 
    The class defines the interface for these modules.

</pre>
*/
class TransactionPlugIn : public StdPlugIn
{
  public    :

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br> 
        Creates an unregistered object.
    */
    TransactionPlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the registered object.
        @param version Version of the plug in.
    */
    TransactionPlugIn(const BAS::String& name, const BAS::String& version);

    /** Destructor. */
    virtual ~TransactionPlugIn();
    //@}

    /** Returns a pointer to the restricted transaction manager interface.
      * @return The interface pointer or a null pointer in case of failure. */
    TAM::ManagerRestrictedIf* transactionManager();

    /** Returns a pointer to the edr-factory.
      * @return The edr-factory pointer or a null pointer in case of failure. */
    EDR::Factory* edrFactory() const;

  private   :
    
    TAM::ManagerRestrictedIf* transactionManagerM;
    EDR::Factory*             edrFactoryM;

    PLG_BASE_EXPORT static const BAS::String registryPipelinesCM;

    PLG_BASE_EXPORT static const BAS::String registryManagerCM;
    
    // Copy constructor and assign operator are not implemented. They are
    // private to prevent unintentionally use.
    TransactionPlugIn(TransactionPlugIn& right);
    const TransactionPlugIn& operator=(TransactionPlugIn& right);

    bool getTransactionManager();
    bool getEdrFactory();

};

//======================================================================
// inlines
//======================================================================
inline TAM::ManagerRestrictedIf * TransactionPlugIn::transactionManager()
{
  return transactionManagerM;
}

inline EDR::Factory * TransactionPlugIn::edrFactory() const
{
  return edrFactoryM;
}
}
#endif // TRANSACTIONPLUGIN_HPP
