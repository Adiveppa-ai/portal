#ifndef PBC_USABEL_HPP
#define PBC_USABEL_HPP 1
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================
// Block: PBC
//==============================================================================
// Module Description:
//  <description>
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work, finished, accepted>
//
//==============================================================================
// Responsible: jens keckstein
//
// $RCSfile: Usable.hpp,v $
// $Revision: 1.8 $
// $Author: aro $
// $Date: 2000/09/29 10:27:47 $
// $Locker:  $
//==============================================================================
// $Log: Usable.hpp,v $
// Revision 1.8  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.7  1999/12/07 13:25:08  sd
// Anachronistic constructs (for HP's aCC) removed.
//
// Revision 1.6  1999/10/28 06:42:37  jkeckst
// check all code review marks and correct them.
//
// Revision 1.5  1999/10/27 09:20:40  clohmann
// // CodeReview - 10.1999 - clohmann
//
// Revision 1.1  1999/10/01 13:11:47  jkeckst
// new class for handling the usable flag.
//
//==============================================================================
#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace PBC
{
/** <tt><b>Usable</b></tt>: describes one field.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Usable.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.8 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 10:27:47 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
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

  This class can be used to collect all class errors/states when running
  the isUsable function. All methods can put there status in this collection
  and in the isUsable methode you can check all statuses from this
  collection.

*/
class Usable D_THREADINFO
{
  public:

    typedef RWTValHashMap<BAS::String,
                      bool,
                      BAS::StringHash,
                      equal_to<BAS::String> >  UsableHashType;
  
    /**@name constructors and destructor */
    //@{ 
    /** Default constructor.
    */
    Usable();
    /// destructor.
    virtual ~Usable();
    //@}


    /**@name special functions */
    //@{ 
    /// set the specified field to TRUE.
    void setTrueFlag(const BAS::String & fieldName);
    /// set the specified field to FALSE.
    void setFalseFlag(const BAS::String & fieldName);
    /// set the fieldName with the fieldValue
    void setFlag(const BAS::String & fieldName, const bool fieldValue);
    /// returned all field combined with the AND clausel.
    bool summary();
    /// All fields are cleared.
    void clear();
    ///
    const UsableHashType & usableHash() const;
    ///
    friend std::ostream& operator<<(std::ostream& os, const Usable& rVal);
    //@}

  private:
    const int operator= (const Usable &);
    Usable(const Usable & rVal);

    UsableHashType  usableHashM;
};

//==============================================================================
//==============================================================================

inline const Usable::UsableHashType & Usable::usableHash() const
{
  return usableHashM;
}
std::ostream& operator<<(std::ostream& os, const Usable& rVal);
}
#endif 
