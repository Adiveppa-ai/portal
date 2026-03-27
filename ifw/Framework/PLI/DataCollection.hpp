#ifndef PLI_DATACOLLECTION_HPP
#define PLI_DATACOLLECTION_HPP
//==============================================================================
//
// Copyright (c) 2010, 2011, Oracle and/or its affiliates. 
// All rights reserved. 
//
// This material is the confidential property of Oracle Corporation or
// its licensors and may be used, reproduced, stored or transmitted only
// in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//
//------------------------------------------------------------------------------
// Module Description:
//   DataCollection class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: DataCollection.hpp $
// $Revision: /cgbubrm_main.pipeline/1 $
// $Author: sumeemis $
// $Date: 2011/08/10 01:09:11 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: DataCollection.hpp,v $
// Revision 1.11  2011/03/22 02:13:38 sm
// Bug 11815646 - P-10434779 PHASE II CHANGES FOR PIPELINE PARALLEL LOADING ECR
//
// Revision 1.10  2000/09/29 10:57:46  aro
// Tried to fix doc++ comments.
//
// Revision 1.9  2000/03/08 14:30:25  clohmann
// Shutdown function added.
//
// Revision 1.8  2000/02/14 11:08:47  bt
// Method init() moved from DataInterface to StdInterface.
//
// Revision 1.7  1999/09/06 14:17:42  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
//
// Revision 1.6  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.5  1999/04/22 08:50:59  bt
//
// Revision 1.1  1999/03/24 16:34:30  bt
// Initial version.
//
//==============================================================================


#ifndef   COLLECTION_HPP
  #include "BAS/Collection.hpp"
#endif
#ifndef   PLI_DATAINTERFACE_HPP
  #include "PLI/DataInterface.hpp"
#endif
#include "PLI/ParallelLoadManager.hpp"


//------------------------------------------------------------------------------
// Explicit instantiation of base class BAS::OnlyPointer
//------------------------------------------------------------------------------

#ifndef INC_TEMPL_DEFS
namespace BAS
{
	template class OnlyPointer<PLI::DataInterface>;
}
#endif
namespace PLI
{
/** This class represents a collection of data plug in interfaces.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: DataCollection.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_main.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2011/08/10 01:09:11 $</font></td>
    <td><font size=-1>$Author: sumeemis $</font></td>
    </tr>
    </table>      

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>DataPool</dd>
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
class DataCollection : public BAS::Collection<DataInterface>
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      DataCollection();

      /** Constructs a collection of data plug in interfaces.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      DataCollection(const BAS::String& objectName);

     /** Constructs a collection of data plug in interfaces.<br>
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. 
        * @param baseParallelLoadMgr Parallel load manager pointer passed
        * from Base. */
      DataCollection(const BAS::String& objectName,PLI::ParallelLoadManager *baseParallelLoadMgr);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~DataCollection();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Init function which will be called to initialize all data interfaces.
      virtual bool init();

      /// Final init function.
      virtual bool finalInit();

      /// Shutdown function which will be called to shutdown all data interfaces.
      virtual void shutdown();

      /** Add DAT initialization batch to queue
      */

      void addInitBatch();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      DataCollection(DataCollection& right);

      const DataCollection& operator=(DataCollection& right);

      
      /// Common functionality between the two public constructors 
      void commonConstructionFunc();

    /** Pointer to hold the parallel load manager pointer
    */
    PLI::ParallelLoadManager * pBaseParallelLoadMgrM;
};
}
#endif // DATACOLLECTION_HPP

