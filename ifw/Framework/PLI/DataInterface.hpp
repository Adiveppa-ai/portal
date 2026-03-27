#ifndef PLI_DATAINTERFACE_HPP
#define PLI_DATAINTERFACE_HPP
//==============================================================================
//
// Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved. 
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
//   DataInterface (data plug in interface) class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: DataInterface.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2010/11/15 09:23:36 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: DataInterface.hpp,v $
// Revision 1.14  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.13  2001/07/26 13:43:27  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.12  2000/09/29 10:57:46  aro
// Tried to fix doc++ comments.
//
// Revision 1.11  2000/02/14 11:08:47  bt
// Method init() moved from DataInterface to StdInterface.
//
// Revision 1.10  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.1  1999/03/22 17:15:40  bt
// Initial version.
//
//==============================================================================

#ifndef   PLG_DATA_PLUG_IN_HPP
  #include "PLG/DataPlugIn.hpp"
#endif
#ifndef   PLI_STDINTERFACE_HPP
  #include "PLI/StdInterface.hpp"
#endif

#include "PLI/CommonLoadInterface.hpp"

namespace PLI
{
/** This class is the data plug in interface.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: DataInterface.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2010/11/15 09:23:36 $</font></td>
    <td><font size=-1>$Author: cprabhak $</font></td>
    </tr>
    </table>      

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>ModuleName (without prefix 'lib' and suffix 'xxd.so')</dd>
    <dd>ModuleStart</dd>
    <dd>Module</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_REG_NAME_NOT_FOUND</dd>
    <dd>ERR_DLOPEN_FAILED</dd>
    <dd>ERR_DLSYM_FAILED</dd>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
</dl> 
*/
class DataInterface : public StdInterface<PLG::DataPlugIn>, public PLI::CommonLoadInterface
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      DataInterface();

      /** Constructs a instance to load and generate a data plug in object.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      DataInterface(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~DataInterface();

      virtual void dependencies ( BAS::StringList & depList );

      virtual void loadDependencies( BAS::StringList & depList );

      virtual bool commonInit();

      virtual bool validity();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      DataInterface(DataInterface& right);

      const DataInterface& operator=(DataInterface& right);
};
}
#endif // DATAINTERFACE_HPP

