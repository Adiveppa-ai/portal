#ifndef PBC_EDRSEGMENTLINK_HPP
#define PBC_EDRSEGMENTLINK_HPP 
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description:
//   Linktable to evaluate the segment for an edr container.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: EdrSegmentLink.hpp,v $
// $Revision: 1.5 $
// $Author: mwriedt $
// $Date: 2000/11/13 13:46:12 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrSegmentLink.hpp,v $
// Revision 1.5  2000/11/13 13:46:12  mwriedt
// Removed FSM concerning parts.
//
// Revision 1.4  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.3  2000/01/12 13:29:21  sd
// Segment hash table replaced by FSM to improve performance.
//
// Revision 1.2  1999/12/16 11:14:36  pengelbr
// Remove EDR dependency.
//
// Revision 1.1  1999/12/03 15:01:46  pengelbr
// Moved some duplicate used classes to PBC.
//
//==============================================================================

#ifndef   RW_TOOLS_TPHMAP_H
  #include <rw/tphdict.h>
#endif
#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   FSM_ENGINE_HPP
  #include "FSM/Engine.hpp"
#endif
namespace PBC
{
// CodeReview - 10.1999 - pengelbr - V - 05.04
//   For every registered object the header file must contain 
//   the documentation of 
//   - the registry values of the object 
//   - the messages send or received by the object 
//   - the error messages of the object 
//   This section is missing.

/** <b><tt>EdrSegmentLink</tt></b> is a table used to evaluate the segment
    for an edr container. 
   
   <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
   <tr>
   <td><font size=-1>$RCSfile: EdrSegmentLink.hpp,v $</font></td>
   <td><font size=-1>$Revision: 1.5 $</font></td>
   <td><font size=-1>$Date: 2000/11/13 13:46:12 $</font></td>
   <td><font size=-1>$Author: mwriedt $</font></td>
   </tr>
   </table>
  
*/
class EdrSegmentLink : public BAS::RegisteredObject
{
  public:
    /**@name EdrSegmentLink constructors and destructor */
    //@{

    /** Default constructor without registration 
     */
    EdrSegmentLink(); 
    
    /** Standard constructor with registration 
     *  @param name Name of registered object
     */
    EdrSegmentLink( const BAS::String& name );

    /** Destructor 
     */
    virtual ~EdrSegmentLink();

    //@}

    /**@name EdrSegmentLink public methods */
    //@{

    /** Get the segment for the edr container 
     *  @param edr The edr container for which to evaluate the segment
     *  @return Pointer to segment name if found, <b>0</b> otherwise
     */
    const BAS::String* segment( const BAS::String& sourceNetwork ) const;

    //@}

  private:

    /** Evaluate the registry 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool readRegistry();

    /** Clear the hash table
     */
    void clear();

    FSM::Engine     segmentFsmM;
    BAS::StringList segmentsM;
};
}
#endif // EDRSEGMENTLINK_HPP
