#ifndef PLI_OutputManagerInterface_HPP
#define PLI_OutputManagerInterface_HPP
//==============================================================================
//
//   Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//   
//   This material is the confidential property of Oracle Corporation or its
//   licensors and may be used, reproduced, stored or transmitted only in
//   accordance with a valid Oracle license or sublicense agreement.
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
// $RCSfile: OutputManagerInterface.hpp,v $
// $Revision: 1.4 $
// $Author: bt $
// $Date: 2001/08/03 13:15:02 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: OutputManagerInterface.hpp,v $
// Revision 1.4  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.3  2001/07/26 13:42:08  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.2  2001/04/26 09:23:26  mliebmann
// GenericIO: TAM added
//
// Revision 1.1  2001/04/09 14:35:38  mliebmann
// Generic IO: files moved from Base
//
// Revision 1.1  2001/03/21 09:40:51  mliebmann
// only for backup
//
//
//==============================================================================

#ifndef   PLG_DATA_PLUG_IN_HPP
  #include "PLG/DataPlugIn.hpp"
#endif
#ifndef   PLI_STDINTERFACE_HPP
  #include "PLI/StdInterface.hpp"
#endif
#ifndef   STR_OutStreamManager_HPP
  #include "STR/OutStreamManager.hpp"
#endif
namespace PLI
{
/** <tt><b>class OutputStreamInterface</b></tt><br>
    This class is the output stream plugin (module) interface.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: OutputManagerInterface.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.4 $</font></td>
    <td><font size=-1>$Date: 2001/08/03 13:15:02 $</font></td>
    <td><font size=-1>$Author: bt $</font></td>
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
class OutputManagerInterface : public StdInterface<STR::OutStreamManager>
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      OutputManagerInterface();

      /** Constructs a instance to load and generate a data plug in object.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      OutputManagerInterface(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~OutputManagerInterface();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      OutputManagerInterface(OutputManagerInterface& right);

      const OutputManagerInterface& operator=(OutputManagerInterface& right);
};
}
#endif // OutputManagerInterface_HPP

