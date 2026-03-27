#ifndef PLG_SEQUENCERCOLLECTION_HPP
#define PLG_SEQUENCERCOLLECTION_HPP
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
// Block: INT::Base
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
// $RCSfile: SequencerCollection.hpp,v $
// $Revision: 1.10 $
// $Author: aro $
// $Date: 2000/09/29 10:57:46 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: SequencerCollection.hpp,v $
// Revision 1.10  2000/09/29 10:57:46  aro
// Tried to fix doc++ comments.
//
// Revision 1.9  2000/03/08 14:30:25  clohmann
// Shutdown function added.
//
// Revision 1.8  2000/02/14 11:08:47  bt
// Method init() moved from INT::DataInterface to INT::StdInterface.
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
#ifndef   PLG_SEQUENCER_HPP
  #include "PLG/Sequencer.hpp"
#endif


//------------------------------------------------------------------------------
// Explicit instantiation of base class BAS::OnlyPointer
//------------------------------------------------------------------------------
namespace PLG
{
/** This class represents a collection of sequencers.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: SequencerCollection.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.10 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 10:57:46 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
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
class SequencerCollection : public BAS::Collection<Sequencer>
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      SequencerCollection();

      /** Constructs a collection of sequencers.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      SequencerCollection(const BAS::String& objectName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~SequencerCollection();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Init function which will be called to initialize all data interfaces.
      virtual bool init();

      /// Shutodwn function which will be called to shutdown all data interfaces.
      virtual void shutdown();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      SequencerCollection(SequencerCollection& right);

      const SequencerCollection& operator=(SequencerCollection& right);
};
}

#endif // SEQUENCERCOLLECTION_HPP
