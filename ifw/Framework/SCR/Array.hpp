#ifndef SCR_ARRAY_HPP
#define SCR_ARRAY_HPP

//==============================================================================
//
// Copyright (c) 1995, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//
//	This material is the confidential property of Oracle Corporation.
//	or its subsidiaries or licensors and may be used, reproduced,
//	stored or transmitted only in accordance with a valid Oracle
//	license or sublicense agreement
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the iScript array class.
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
// $RCSfile: Array.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:00:39 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Array.hpp,v $
// Revision 1.3  2000/10/06 15:11:33  sd
// - Array functions added.
//
// Revision 1.2  2000/10/06 14:35:12  sd
// - Clear() function added to array
//
// Revision 1.1  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
//==============================================================================

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
namespace SCR 
{
/**<b><tt>Array</tt></b> is the variable class for iScript arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Array.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:39 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Array : public Variable
{
  public:
    /**@name Array constructors and destructor */
    //@{
    
    /** Constructor
     *  @param defaultValue The default array member value
     */
    Array( Variable* defaultValue );

    /** Copy constructor
     *  @param other The value to copy
     */
    Array( const Array& other );

    /** Destructor
     */
    virtual ~Array();

    //@}

    /**@name Array public methods */
    //@{

    /** Clone the array
     *  @return Pointer to the cloned array
     */
    virtual Variable* clone() const;

    /** Access an array value
     *  @return Pointer to the array value
     */
    Variable* at( size_t idx );

    /** Get the container datatype
     *  @return The container datatype
     */
    int containerType() const;

    /** Get the default value
     *  @return Pointer to default value
     */
    const Variable* defaultValue() const;

    /** Clear the array
     */
    void clear();

    /** Get the size of the array
     *  @return The size of the array
     */
    int64 size() const;

    //@}

  private:
    // Hide the default constructor
    Array();

    // instance members
    Variable*                     defaultValueM;
    RWTPtrOrderedVector<Variable> arrayM;
};

//==============================================================================
// Get the size of the array
//==============================================================================
inline int64
Array::size() const
{
  return arrayM.entries();
}
}
#endif // ARRAY_HPP
