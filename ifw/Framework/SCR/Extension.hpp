#ifndef SCR_EXTENSION_HPP
#define SCR_EXTENSION_HPP 

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates. 
// 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the base class for all iScript extensions.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: Extension.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:44 $
// $Locker:  $ 
//------------------------------------------------------------------------------
// $Log: Extension.hpp,v $
// Revision 1.4  2000/09/26 13:33:04  sd
// - Module SCR is now only dependent from BAS
//
// Revision 1.3  2000/08/24 15:16:03  sd
// - Implementation changed to support AIX.
//
// Revision 1.2  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.1  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
//==============================================================================

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace SCR
{

class Variable;
class Interpreter;
class FctDescr;

/** <b><tt>Extension</tt></b> is the base class for all iScript extensions
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Extension.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Extension D_THREADINFO
{
  public:
    /**@name Extension constructors and destructor */
    //@{

    /** Constructor
     */
    Extension();

    /** Destructor
     */
    virtual ~Extension();

    //@}

    /**@name Extension public methods */
    //@{

    /** Get the name of the iScript extension
     *  @return Reference to string with the name
     */
    virtual const BAS::String& extensionName() const = 0;

    /** Get a variable from the extension
     *  @param name The name of the variable
     *  @return Pointer to the variable on success, 0 otherwise
     */
    virtual Variable* variable( const BAS::String& name );

    //@}


  protected:

  private:

    // Hide the copy constructor 
    Extension( const Extension& other );
    const Extension& operator=( const Extension& other );
};

typedef RWTPtrOrderedVector<Extension> ExtensionVector;
}
#endif // EXTENSION_HPP
