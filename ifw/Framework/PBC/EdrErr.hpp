#ifndef PBC_EDRERR_HPP
#define PBC_EDRERR_HPP
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
//   A simple class for edr error messages. All messages will be registered
//   so it is possible to create a list with all error messages automatically.
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
// $RCSfile: EdrErr.hpp,v $
// $Revision: 1.6 $
// $Author: aro $
// $Date: 2000/09/29 11:14:01 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrErr.hpp,v $
// Revision 1.6  2000/09/29 11:14:01  aro
// Tried to fix doc++ comments.
//
// Revision 1.4  1999/09/07 10:14:16  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
//
// Revision 1.2  1999/09/03 09:41:15  sd
// Order of parameters module and error changed
//
// Revision 1.1  1999/09/03 09:19:28  sd
// Initial revision.
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
/** <b><tt>EdrErr</tt></b> is a class for registered edr errors. The class
    makes it possible to create lists of modules and the edr errors used in it
    automatically.
  
    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: EdrErr.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.6 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 11:14:01 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
    </tr>
    </table>
*/
class EdrErr : public BAS::String
{
  public:
    
    /**@name EdrErr constructors and destructor */
    //@{

    /** Constructor.
     *  @param module Name of module in which the message is used
     *  @param error Name of the error message appended to edr 
     */
    EdrErr( const BAS::String& module, const BAS::String& error );

    //@}

    /**@name EdrErr public methods */
    //@{

    /** Dump all error messages to output stream
     *  @param stream Stream in which to dump the messages
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    static bool dumpEdrErrors( std::ostream& stream );

    //@}

    // type definitions
    typedef RWTValSortedDlist<BAS::String, less<BAS::String> > EdrErrMsgList;
    typedef RWTValSortedDlistIterator<BAS::String, less<BAS::String> > EdrErrMsgListIterator;
    typedef RWTPtrHashMap<BAS::String, EdrErrMsgList, BAS::StringHash, equal_to<BAS::String> > EdrErrModuleHash;
    typedef RWTPtrHashMapIterator<BAS::String, EdrErrMsgList, BAS::StringHash, equal_to<BAS::String> > EdrErrModuleHashIterator;

  private:

    // class members
    PBC_EXPORT static EdrErrModuleHash* moduleHashCM;
};
}
#endif // EDRERR_HPP

