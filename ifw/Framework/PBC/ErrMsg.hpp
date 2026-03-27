#ifndef PBC_ERRMSG_HPP
#define PBC_ERRMSG_HPP
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
//  <description>
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
// $RCSfile: ErrMsg.hpp,v $
// $Revision: 1.10 $
// $Author: aro $
// $Date: 2000/09/29 12:21:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ErrMsg.hpp,v $
// Revision 1.10  2000/09/29 12:21:38  aro
// Tried to fix doc++ comments.
//
// Revision 1.8  1999/09/21 15:00:52  sd
// Changes to support RogueWave without STL.
//
// Revision 1.7  1999/09/07 10:14:16  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
//
// Revision 1.6  1999/09/07 09:31:51  sd
// LOG includes removed.
//
// Revision 1.5  1999/09/07 09:30:38  sd
// checkErrMessages() functions removed to avoid dependency to module LOG.
//
// Revision 1.3  1999/09/03 09:20:34  sd
// Module information added.
//
//==============================================================================

#if !defined PBC_EXPORT
  #if defined(WINDOWS)
    #if !defined(PBC_INTERNAL)
      #define PBC_EXPORT __declspec(dllimport)
    #else
      #define PBC_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PBC_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TVSRTDLI_H
  #include <rw/tvsrtdli.h>
#endif
#ifndef   RW_TOOLS_TPHMAP_H
  #include <rw/tphdict.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace PBC
{
/** <b><tt>ErrMsg</tt></b> is a class for registered error messages. 
    The class makes it possible to create lists of modules and the edr errors
    used in it automatically.
   
    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: ErrMsg.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.10 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 12:21:38 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
    </tr>
    </table>
*/
class ErrMsg : public BAS::String
{
  public:

    // type definitions
    typedef RWTValSortedDlist<BAS::String, less<BAS::String> >         ErrMsgMsgList;
    typedef RWTValSortedDlistIterator<BAS::String, less<BAS::String> > ErrMsgMsgListIterator;
    typedef RWTPtrHashMap<BAS::String, ErrMsgMsgList, BAS::StringHash, equal_to<BAS::String> > ErrMsgModuleHash;
    typedef RWTPtrHashMapIterator<BAS::String, ErrMsgMsgList, BAS::StringHash, equal_to<BAS::String> > ErrMsgModuleHashIterator;
    
    /**@name ErrMsg constructors and destructor */
    //@{

    /** Constructor.
     *  @param module Name of module in which the message is used
     *  @param msg Name of the error message
     */
    ErrMsg( const BAS::String& module, const BAS::String& msg );
    
    //@}

    /**@name ErrMsg public methods */
    //@{

    /** Dump all error messages to output stream
     *  @param stream Stream in which to dump the messages
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    static bool dumpErrMessages( std::ostream& stream );

    /** Get an iterator for the module hash table
     *  @return Iterator for the module hash table
     */
    static ErrMsgModuleHashIterator moduleIterator();

    /** Get an iterator for the module's error message list
     */
    static ErrMsgMsgListIterator messageIterator( ErrMsgMsgList& list );

    //@}

  private:

    // class members
    PBC_EXPORT static ErrMsgModuleHash* moduleHashCM;
};
}
#endif // ERRMSG_HPP
