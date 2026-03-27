#ifndef EDR_PARAMETER_HPP
#define EDR_PARAMETER_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Parameter. This class is used to parameterize
//   the datatypes used in the input format description. 
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: Parameter.hpp,v $
// $Revision: 1.4 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Parameter.hpp,v $
// Revision 1.4  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.3  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.2  2001/03/19 16:12:09  sd
// - Interface for addParameter() changed.
//
// Revision 1.1  2000/11/30 17:56:47  sd
// - Creation of Base.
//
//==============================================================================

#ifndef   BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace EDR
{
/** <b><tt>Parameter</tt></b> is used to parameterize the datatypes used in
 *  the input format description.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Parameter.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class Parameter D_THREADINFO
{
  D_SINGLETHREADED

  public:
    typedef enum
    {
      PARAM_CHAR,
      PARAM_STRING,
      PARAM_LONG,
      PARAM_BOOL,
      PARAM_DECIMAL,
      PARAM_IDENTIFIER
    } ParamTypeT;

    /**@name Parameter constructors and destructor */
    //@{

    /** Constructor for string values and identifiers
     *  @param value The string value
     */
    Parameter( const BAS::String& value,
                   ParamTypeT        paramType = PARAM_STRING );

    /** Constructor for decimal values
     *  @param value The decimal value
     */
    Parameter( const BAS::Decimal& value );
    
    /** Constructor for long values
     *  @param value The long value
     */
    Parameter( int64 value );

    /** Constructor for bool values
     *  @param value The bool value
     */
    Parameter( bool value );

    /** Constructor for char values
     *  @param value The char value
     */
    Parameter( char value );

    /** Destructor
     */
    ~Parameter();
    
    //@}

    /**@name Parameter public methods */
    //@{

    /** Get the parameters datatype
     *  @return The parameters datatype
     */
    ParamTypeT datatype() const;

    /** Get the string value
     *  @return Reference to string value
     */
    const BAS::String& stringVal() const;

    /** Get the long value
     *  @return The long value
     */
    int64 longVal() const;
    
    /** Get the bool value
     *  @return The bool value
     */
    bool boolVal() const;

    /** Get the decimal value
     *  @return The decimal value
     */
    const BAS::Decimal& decimalVal() const;

    /** Get the character value
     *  @return The character value
     */
    char charVal() const;

    /** Get the string description for a datatype
     *  @param paramtype Datatype
     *  @return String describing the datatcype
     */
    static BAS::String datatypeAsString( ParamTypeT paramtype );

    //@}

  private:

    // instance members
    ParamTypeT  datatypeM;
    BAS::String  stringValM;
    int64        longValM;
    bool        boolValM;
    BAS::Decimal decimalValM;
    char        charValM;
};

typedef RWTValOrderedVector<Parameter> ParameterList;

//==============================================================================
// Get the datatype
//==============================================================================
inline Parameter::ParamTypeT
Parameter::datatype() const
{
  return datatypeM;
}

//==============================================================================
// Get the string value
//==============================================================================
inline const BAS::String&
Parameter::stringVal() const
{
  return stringValM;
}

//==============================================================================
// Get the decimal value
//==============================================================================
inline const BAS::Decimal&
Parameter::decimalVal() const
{
  return decimalValM;
}

//==============================================================================
// Get the long value
//==============================================================================
inline int64
Parameter::longVal() const
{
  return longValM;
}

//==============================================================================
// Get the bool value
//==============================================================================
inline bool
Parameter::boolVal() const
{
  return boolValM;
}

//==============================================================================
// Get the character value
//==============================================================================
inline char
Parameter::charVal() const
{
  return charValM;
}
}
#endif // PARAMETER_HPP
