#ifndef PLG_STDPLUGIN_HPP
#define PLG_STDPLUGIN_HPP
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
// $RCSfile: StdPlugIn.hpp,v $
// $Revision: 1.25 $
// $Author: mliebmann $
// $Date: 2001/08/31 09:37:45 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StdPlugIn.hpp,v $
// Revision 1.25  2001/08/31 09:37:45  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.24  2001/08/28 12:04:23  jkeckst
// PETS 37618 code review 08.2001
//
// Revision 1.23  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.22  2001/05/03 16:02:25  bt
// Format renamed to Pipeline.
//
// Revision 1.21  2001/04/04 10:21:54  sd
// - Include of PBC::EdrMsg.hpp removed
//
// Revision 1.20  2000/09/29 12:25:20  aro
// Tried to fix doc++ comments.
//
// Revision 1.19  2000/07/19 06:43:44  jkeckst
// code review CR-07-2000
//
// Revision 1.18  2000/03/08 11:53:22  clohmann
// shutdown() function added.
//
// Revision 1.17  2000/02/14 10:51:36  bt
// Method init() moved from DataPlugIn to StdPlugIn.
//
// Revision 1.16  2000/01/26 14:49:49  jkeckst
// changes for version 2 (EDRC)
//
// Revision 1.15  2000/01/18 07:53:55  jkeckst
// newest changes for v4.0.
//
// Revision 1.14  1999/11/05 13:08:53  clohmann
// Check all code review remarks.
//
// Revision 1.13  1999/11/04 09:12:52  jkeckst
// codeReview
//
// Revision 1.10  1999/05/06 17:31:11  aro
// CVS Recovery.
//
// Revision 1.10  1999/05/06 12:55:38  aro
// StdPlugIn::writeToFormatLog() added.
//          
//==============================================================================

#if !defined PLG_BASE_EXPORT
  #if defined(WINDOWS)
    #if !defined(PLG_BASE_INTERNAL)
      #define PLG_BASE_EXPORT __declspec(dllimport)
    #else
      #define PLG_BASE_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PLG_BASE_EXPORT 
  #endif
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_OBJECT_H
  #include "BAS/Object.hpp"
#endif

namespace PLG
{
/** StdPlugIn Class declaration.

<pre>
    <b>Registry entries</b>
         none
    <b>Messages send</b>
         none
    <b>Messages receive</b>
         none
    <b>Errors</b>
         none

    This is the base class for every integRate plug in. 
    The class defines the interface for the plug in.

</pre>
*/
class StdPlugIn : public BAS::Object
{
  public    :

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br> 
        Creates an unregistered object.
    */
    StdPlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the registered object.
        @param version Version of the plug in. */
    StdPlugIn(const BAS::String& name, const BAS::String& version);

    /** Destructor. */
    virtual ~StdPlugIn();
    //@}

    /**@name Public Member Functions */
    //@{
    /// Init function which will be called to initialize the module.
    virtual bool init();

    /// Final init function.
    virtual bool finalInit();

    /// Shutdown function .
    virtual bool shutdown();

	virtual bool startup();

	virtual bool install();

	virtual bool uninstall();

    /// Returns the version information.
    const BAS::String& version() const;

    /// Write the version information.
    const void writeModuleVersion() const;
    //@}

  protected :

    /** Sends a log message to the the pipeline log object.
        @param s The status to be logged. */
    void writeToPipelineLog(const BAS::Status& msg) const;

  private   :
    
    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

    StdPlugIn(StdPlugIn& right);

    const StdPlugIn& operator=(StdPlugIn& right);

    // plug in version number
    BAS::String plugInVersionM;

    BAS::RegisteredObject* pipelineLogM;

};

//======================================================================
// inlines
//======================================================================
}
#endif // STDPLUGIN_HPP
