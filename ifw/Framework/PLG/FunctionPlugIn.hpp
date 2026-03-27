#ifndef PLG_FUNCTION_PLUG_IN_HPP
#define PLG_FUNCTION_PLUG_IN_HPP 
//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLG_Base
//------------------------------------------------------------------------------
// Module Description:
//  FunctionPlugIn class implementation.
//
//  This class is the base class for all FunctionPlugIn Implementations. 
//  Every FunctionPlugIn must inhereted from this class. 
//
//------------------------------------------------------------------------------
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.20  2001/08/31 09:37:45  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.19  2001/08/28 12:04:23  jkeckst
// PETS 37618 code review 08.2001
//
// Revision 1.18  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.17  2001/05/03 16:02:25  bt
// Format renamed to Pipeline.
//
// Revision 1.16  2001/04/26 09:28:33  mliebmann
// GenericIO: TAM added
//
// Revision 1.15  2000/09/29 12:25:20  aro
// Tried to fix doc++ comments.
//
// Revision 1.14  2000/02/28 11:57:54  clohmann
// Implementation changed to support edr container list.
//
// Revision 1.13  1999/11/05 13:08:53  clohmann
// Check all code review remarks.
//
// Revision 1.12  1999/11/04 09:12:52  jkeckst
// codeReview
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   PLG_TRANSACTIONPLUGIN_HPP
  #include "PLG/TransactionPlugIn.hpp"
#endif
namespace PLG
{
//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------

typedef RWTPtrOrderedVector<EDR::Container> EdrContainerList;

/** FunctionPlugIn class declaration.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: FunctionPlugIn.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2010/11/15 09:23:37 $</font></td>
    <td><font size=-1>$Author: cprabhak $</font></td>
    </tr>
    </table>  

<pre>
    <b>Registry entries</b>
         <dd>Active</dd>
    <b>Messages send</b>
         none
    <b>Messages receive</b>
         none
    <b>Errors</b>
         <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
         <dd>ERR_REG_ENTRY_NOT_FOUND</dd>
         <dd>INF_FKT_ACTIVE</dd>
         <dd>INF_FKT_INACTIVE</dd>
         <dd>INF_LOADING_FCT_PLUGIN</dd>
         <dd>INF_UNLOADING_FCT_PLUGIN</dd>
</pre>

  This is the base class for the integRate function plugin's. It the interface for a
  integrate function plugin and handles the Registry-Entry for the active flag. 

*/
class FunctionPlugIn : public TransactionPlugIn
{
  public    :

    /**@name Constructors and destructors. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    FunctionPlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the plug in.
        @param version Version of the plug in.
    */
    FunctionPlugIn(const BAS::String& name, const BAS::String& version);

    /** Destructor */
    virtual ~FunctionPlugIn();
    //@}

    /**@name Main function */
    //@{
    /** Process the given edr container.  
        @param edr Pointer to edr container. <br>
                   Return value and error status 
                   are reported through the edr container. 
        @return   true  - The function ends normally. <br>
                  false - An internal error occured. 
    */
    virtual bool processEdrContainer(EdrContainerList& edrVector);
    //@}

    /** Registry update.
        Must be called in registry update function of derivered classes.
    */
    virtual bool registryUpdate(const BAS::RegistryEntry* update,
                                BAS::ProtectedBool&       workedOn);

    /** Plugin state.
        @return - True if function is active.
    */
    virtual bool isActive() const;

    virtual void loadDependencies (BAS::StringList & depList);

  protected :
     virtual bool readRegistry();

  private   :
    
    // Copy constructor and assign operator are not implemented. They are
    // private to prevent unintentionally use.
    FunctionPlugIn(FunctionPlugIn& right);
    const FunctionPlugIn& operator=(FunctionPlugIn& right);

    // Function activation flag
    bool   isActiveM;

    PLG_BASE_EXPORT static const BAS::String registryActiveCM;
};
}
#endif // FUNCTION_PLUG_IN_HPP
