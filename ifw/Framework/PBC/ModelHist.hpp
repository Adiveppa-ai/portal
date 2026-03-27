#ifndef PBC_MODELHIST_HPP
#define PBC_MODELHIST_HPP
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
//  Table containing the model-ids for each segment.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <reviewed>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: ModelHist.hpp,v $
// $Revision: 1.2 $
// $Author: aro $
// $Date: 2000/09/29 10:27:47 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ModelHist.hpp,v $
// Revision 1.2  2000/09/29 10:27:47  aro
// Tried to fix doc++ comments.
//
// Revision 1.1  1999/12/03 15:01:46  pengelbr
// Moved some duplicate used classes to PBC.
//
// Revision 1.3  1999/11/26 15:32:29  pengelbr
// Fill the 'iNumZone'-fields in the ChargePackets with 'a'- and 'bNumZone' values.
// Set EDR::ChargePacket.chargeType field to 'N'.
//
// Revision 1.2  1999/11/24 14:53:24  pengelbr
// Add newline at end of file to avoid Sun-CC warnings.
//
// Revision 1.1  1999/11/23 13:04:41  pengelbr
// Changes due to database improvements.
// Tariffmodels may now be linked to segments for a special period.
//
//==============================================================================

#ifndef   RW_TOOLS_TVSLIST_H
  #include <rw/tvslist.h>
#endif
#ifndef   BAS_DATE_HPP
  #include "BAS/Date.hpp"
#endif
namespace PBC
{
/** <b><tt>ModelHist</tt></b>.
  
   <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
   <tr>
   <td><font size=-1>$RCSfile: ModelHist.hpp,v $</font></td>
   <td><font size=-1>$Revision: 1.2 $</font></td>
   <td><font size=-1>$Date: 2000/09/29 10:27:47 $</font></td>
   <td><font size=-1>$Author: aro $</font></td>
   </tr>
   </table>
  
*/
class ModelHist
{
public:

  // typedefs
  typedef RWTValSlist<int64> ModelList;
  typedef RWTValSlistIterator<int64> ModelListIterator;

  /**@name ModelHist constructors and destructor */
  //@{

  /** Default constructor without registration 
   */
  ModelHist();

  /** Constructor
   *  @param name Registry name of object
   */
  ModelHist( const BAS::Date& from, 
                 const BAS::Date& to );

  /** Destructor 
   */
  ~ModelHist();

  //@}

  /**@name ModelHist comparision */
  //@{

  bool operator==(const ModelHist& right) const;

  bool operator<(const ModelHist& right) const;

  bool isValidAt(const BAS::Date& at) const;

  //@}

  /**@name ModelHist get attribute */
  //@{

  ModelList& models();

  //@}

private:

  BAS::Date  validFromM;

  BAS::Date  validToM;
  
  ModelList modelsM;

};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

inline bool 
ModelHist::operator==(const ModelHist& right) const
{
  return (    ( validFromM.compareTo( right.validFromM ) == 0 )
           && ( validToM.compareTo( right.validToM ) == 0 ) );
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

inline bool 
ModelHist::operator<(const ModelHist& right) const
{
  if ( validFromM.compareTo( right.validFromM ) < 0 )
  {
    return true;
  }
  else if ( validFromM.compareTo( right.validFromM ) == 0 )
  {
    if ( validToM.compareTo( right.validToM ) < 0 )
    {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

inline bool 
ModelHist::isValidAt(const BAS::Date& at) const
{
  return (    ( validFromM.compareTo( at ) <= 0 )
           && (    ( validToM.compareTo( BAS::Date() ) == 0 )
               || ( validToM.compareTo( at ) >= 0 ) ) );
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

inline ModelHist::ModelList& 
ModelHist::models()
{
  return modelsM;
}

//------------------------------------------------------------------------------
}
#endif
