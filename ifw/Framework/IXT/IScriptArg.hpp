#ifndef IXT_ISCRIPTARG_HPP
#define IXT_ISCRIPTARG_HPP

//==============================================================================
//
// Copyright (c) 1996, 2013, Oracle and/or its affiliates. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FCT
//------------------------------------------------------------------------------
// Module Description:
//   Class used for passing arguments from the registry to the interpreter.
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
// $RCSfile: IScriptArg.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: kdarak $
// $Date: 2013/08/27 03:23:43 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: IScriptArg.hpp,v $
// Revision 1.3  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.1  2000/12/04 08:21:07  sd
// - Module moved from IXT to iScript.
//
// Revision 1.1  2000/09/27 11:33:21  sd
// - IXT is a framework module again
//
// Revision 1.1  2000/09/26 13:33:35  sd
// - Initial revision for separate integRate iScript extension.
//
// Revision 1.2  2000/06/16 15:03:29  sd
// - Implementation changed to support the IBM AIX xlC compiler.
//
// Revision 1.1  2000/04/07 14:14:39  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace IXT
{
/**<b><tt>IScriptArg</tt></b> is the class for passing arguments to 
 * the IScript interpreter. 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: IScriptArg.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2013/08/27 03:23:43 $</font></td>
 *  <td><font size=-1>$Author: kdarak $</font></td>
 *  </tr>
 *  </table>
 */
class IScriptArg D_THREADINFO
{
  public:
    /** IScriptArg constructors and destructor */
    //@{

    /** Default constructor
     */
    IScriptArg();

    /** Constructor for dircect initialization
     */ 
    IScriptArg( const BAS::String& name,
                    const BAS::String& value );

    //@}

    /** IScriptArg public member functions */
    //@{

    /** Get the argument name
     */
    const BAS::String& name() const;

    /** Get the argument value
     */
    const BAS::String& value() const;

   /** Set the argument name
   */
   void name(const BAS::String& name);

   /** Set the argument value
   */
   void value(const BAS::String& value);

#ifdef __aix
    bool operator<( const IScriptArg& rVal ) const 
    { 
      return( this < &rVal ); 
    };
    bool operator==( const IScriptArg& rVal ) const 
    { 
      return( this == &rVal ); 
    };
#endif
    //@}

  private:

    // instance members
    BAS::String nameM;
    BAS::String valueM;
};

typedef RWTValOrderedVector<IScriptArg> IScriptArgVector;
}
#endif // ISCRIPTARG_HPP


