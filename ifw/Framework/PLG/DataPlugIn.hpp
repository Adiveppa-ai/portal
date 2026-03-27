#ifndef PLG_DATA_PLUG_IN_HPP
#define PLG_DATA_PLUG_IN_HPP 
//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Basis
//------------------------------------------------------------------------------
// Module Description:
//  DataPlugIn class implementation.
//
//  This class is the base class for all DataPlugIn Implementations. 
//  Every PlugIn must inhereted from this class. 
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
// $RCSfile: DataPlugIn.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2010/11/15 09:23:37 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DataPlugIn.hpp,v $
// Revision 1.17  2001/08/31 09:37:45  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.16  2001/08/28 12:04:23  jkeckst
// PETS 37618 code review 08.2001
//
// Revision 1.15  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.14  2000/09/29 12:25:20  aro
// Tried to fix doc++ comments.
//
// Revision 1.13  2000/02/14 10:51:36  bt
// Method init() moved from DataPlugIn to StdPlugIn.
//
// Revision 1.12  1999/11/05 13:08:53  clohmann
// Check all code review remarks.
//
// Revision 1.11  1999/11/04 09:12:52  jkeckst
// codeReview
//
// Revision 1.9  1999/07/27 09:41:27  clohmann
// Load / unload messages.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   PLG_STDPLUGIN_HPP
  #include "PLG/StdPlugIn.hpp"
#endif
namespace PLG
{
//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------

/** DataPlugIn Class declaration.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: DataPlugIn.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2010/11/15 09:23:37 $</font></td>
    <td><font size=-1>$Author: cprabhak $</font></td>
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
        <dd>INF_LOADING_DATA_PLUGIN </dd>
        <dd>INF_UNLOADING_DATA_PLUGIN</dd>
</pre>

    This class is the base class for every integRate data plug in. 
*/
class DataPlugIn : public StdPlugIn
{
  public    :

    /**@name Constructors and destructors. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    DataPlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the object.
        @param version Version of the plug in.
    */
    DataPlugIn(const BAS::String& name,
                   const BAS::String& version);

    /** Destructor */
    virtual ~DataPlugIn();

    virtual void loadDependencies (BAS::StringList & depList);
    //@}

  protected :

  private   :
    
    // Copy constructor and assign operator are not implemented. They are
    // private to prevent unintentionally use.
    DataPlugIn(DataPlugIn& right);
    const DataPlugIn& operator=(DataPlugIn& right);
};
}
#endif // DATA_PLUG_IN_HPP
