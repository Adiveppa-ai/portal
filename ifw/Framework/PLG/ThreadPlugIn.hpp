#ifndef PLG_THREAD_PLUG_IN_HPP
#define PLG_THREAD_PLUG_IN_HPP 
//==============================================================================
//
// 1998,1999 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: PLG
//------------------------------------------------------------------------------
// Module Description:
//  ThreadPlugIn class implementation.
//
//  This class is the base class for all "threaded" PlugIn's. 
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Carsten Lohmann
//
// $RCSfile: ThreadPlugIn.hpp,v $
// $Revision: 1.13 $
// $Author: mliebmann $
// $Date: 2001/11/21 10:36:49 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ThreadPlugIn.hpp,v $
// Revision 1.13  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// Revision 1.12  2000/09/29 12:29:44  aro
// Tried to fix doc++ comments.
//
// Revision 1.11  1999/11/04 10:01:21  jkeckst
// codeReview
//
// Revision 1.9  1999/05/06 17:31:00  aro
// CVS Recovery.
//
// Revision 1.9  1999/05/06 06:55:29  aro
// Online doc updated.
//
//==============================================================================

#ifndef   PLG_STDPLUGIN_HPP
  #include "PLG/StdPlugIn.hpp"
#endif

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
namespace BAS
{
class String;
}

namespace PLG
{

/** ThreadPlugIn class.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: ThreadPlugIn.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.13 $</font></td>
    <td><font size=-1>$Date: 2001/11/21 10:36:49 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                                                                          

<p><dl>
    <dt><b>Registry entries</b></dt>
         <dd>none</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Messages receive</b></dt>
         <dd>none</dd>
    <dt><b>Errors</b></dt>
         <dd>none</dd>

    // CodeReview - 10.1999 - jkeckstein - V - 5.3 - missing discription
</dl>
*/
class ThreadPlugIn : public StdPlugIn
{
  public    :

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    ThreadPlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the registered object.
        @param version Version of the registered object.
    */
    ThreadPlugIn(const BAS::String& name, const BAS::String& version);

    /** Destructor. */
    virtual ~ThreadPlugIn();
    //@}

    /** "Threaded" function. <br>
    */ 
    virtual void execute() = 0;

    /** Plug in state */
    //@{

    /// request abort
    virtual void requestAbort();

    //@}

    /**@name Class function members*/
    //@{

    /** Derived method from stdPlugIn, which is in the normal way not used
        by the threadPlugIn.
        @return <tt>true</tt> everytime successfull.
      */
    virtual bool init();

    //@}

  protected :

  private   :
    
    // Default, copy constructor and assign operator are not implemented. They are
    // private to prevent unintentionally use.
    ThreadPlugIn(ThreadPlugIn& right);
    const ThreadPlugIn& operator=(ThreadPlugIn& right);
};

//======================================================================
// inline
//======================================================================

//======================================================================
// prepare for abort
//======================================================================
inline void ThreadPlugIn::requestAbort()
{
  // CodeReview - 10.1999 - jkeckstein - I - for what is this?
}

}
#endif // THREAD_PLUG_IN_HPP
