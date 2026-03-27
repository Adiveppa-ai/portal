#ifndef SCR_VARIABLE_HPP
#define SCR_VARIABLE_HPP
/* @(#)%Portal Version: Variable.hpp:PlatformR2Int:2:2006-Jul-16 15:25:09 % */

//==========================================================================
//
// Copyright (c) 1995, 2023, Oracle and/or its affiliates. 
// 
//
//	This material is the confidential property of Oracle Corporation.
//	or its subsidiaries or licensors and may be used, reproduced,
//	stored or transmitted only in accordance with a valid Oracle
//	license or sublicense agreement
//
//==========================================================================
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Variable classes used in the interpreter.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// $RCSfile: Variable.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
//------------------------------------------------------------------------------
// Revision 1.9  2004/18/08 ammon
// PRSF00136596:  Added PPoid support.
//
// Revision 1.8  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.7  2000/09/26 13:33:04  sd
// - Module SCR is now only dependent from BAS
//
// Revision 1.6  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.5  2000/08/17 11:35:40  sd
// - first version with iScript extensions
//
// Revision 1.4  2000/06/16 15:03:29  sd
// - Implementation changed to support the IBM AIX xlC compiler.
//
// Revision 1.3  2000/03/24 09:56:44  sd
// - Constants added.
// - Direct assignment in variable declarations added.
//
// Revision 1.2  2000/03/23 11:25:36  sd
// - support for file variables added.
// - new class FileVariable
//
// Revision 1.1  2000/03/06 14:32:50  sd
// Initial revision.
//
//==============================================================================

#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef BAS_IDENTIFIER_H
  #include "BAS/Identifier.hpp"
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
/**<b><tt>Variable</tt></b> is the base class for all variables used
 * in FCT_Interpreter.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Variable D_THREADINFO
{
  public:
    /** Variable constructors and destructor */
    //@{

    /** Constructor
     */
    Variable( int theType );

    /** Destructor
     */
    virtual ~Variable();

    //@}

    /** Variable public methods */
    //@{

    /** Get the datatype of the variable
     *  @return dataType
     */
    int dataType() const;

    /** Set the datatype of the variable
     *  @param theType The datatype for the variable
     */
    void dataType( int theType );

    /** Clone the variable 
     *  @return Pointer to cloned variable
     */
    virtual Variable* clone() const = 0;

    //@}

  protected:
    int dataTypeM;
};

/**<b><tt>StringVariable</tt></b> is the interpreter큦 string variable
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringVariable : public Variable
{
  public:
    /** StringVariable constructors and destructor */
    //@{

    /** Constructor
     */
    StringVariable();

    /** Constructor for direct initialization
     *  @param value The initial value
     *  @param isConst Const flag
     */
    StringVariable( const BAS::String& value,
                        bool              isConst = false );

    /** Destructor
     */
    virtual ~StringVariable();

    //@}

    /** StringVariable public methods */
    //@{

    /** Set the variable
     *  @param value The new value
     */
    void set( const BAS::String& value );

    /** Get the variable
     *  @return The value
     */
    const BAS::String& get() const;

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}
  protected:
    BAS::String valueM;
};

//==============================================================================
// Set the value
//==============================================================================
inline void 
StringVariable::set( const BAS::String& value )
{
  valueM = value;
}

//==============================================================================
// Get the value
//==============================================================================
inline const BAS::String&
StringVariable::get() const
{
  return valueM;
}

/**<b><tt>DecimalVariable</tt></b> is the interpreter큦 decimal variable
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalVariable : public Variable
{
  public:
    /** DecimalVariable constructors and destructor */
    //@{

    /** Constructor
     */
    DecimalVariable();

    /** Constructor for direct initialization
     *  @param value The initial value
     *  @param isConst Const flag
     */
    DecimalVariable( const BAS::Decimal& value,
                         bool               isConst = false );

    /** Destructor
     */
    virtual ~DecimalVariable();

    //@}

    /** DecimalVariable public methods */
    //@{

    /** Set the variable
     *  @param value The new value
     */
    void set( const BAS::Decimal& value );

    /** Get the variable
     *  @return The value
     */
    const BAS::Decimal& get() const;

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}
  protected:
    BAS::Decimal valueM;
};

//==============================================================================
// Set the value
//==============================================================================
inline void 
DecimalVariable::set( const BAS::Decimal& value )
{
  valueM = value;
}

//==============================================================================
// Get the value
//==============================================================================
inline const BAS::Decimal&
DecimalVariable::get() const
{
  return valueM;
}

/**<b><tt>LongVariable</tt></b> is the interpreter큦 long variable
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongVariable : public Variable
{
  public:
    /** LongVariable constructors and destructor */
    //@{

    /** Constructor
     */
    LongVariable();

    /** Constructor for direct initialization
     *  @param value Intial value
     *  @param isConst Flag if value is const
     */
    LongVariable( int64 value,
                      bool isConst = false );

    /** Destructor
     */
    virtual ~LongVariable();

    //@}

    /** LongVariable public methods */
    //@{

    /** Set the variable
     *  @param value The new value
     */
    void set( int64 value );

    /** Get the variable
     *  @return The value
     */
    int64 get() const;

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}

  protected:
    int64 valueM;
};

//==============================================================================
// Set the value
//==============================================================================
inline void 
LongVariable::set( int64 value )
{
  valueM = value;
}

//==============================================================================
// Get the value
//==============================================================================
inline int64
LongVariable::get() const
{
  return valueM;
}


/**<b><tt>AdtVariable</tt></b> is the interpreter큦 adt variable
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
//
// This variable type will handle all abstract data types that
// can be implemented in more detail within extension classes.
// always store this as a numeric value which uniquely id's
// the actual thing.  Quite possibly will be implemented as
// the memory pointer for the value
//
class AdtVariable : public Variable
{
  public:
    /** AdtVariable constructors and destructor */
    //@{

    /** Constructor
     */
    AdtVariable();

    /** Constructor for direct initialization
     *  @param value Intial value
     *  @param isConst Flag if value is const
     */
    AdtVariable( int64 value,
                      bool isConst = false );

    /** Destructor
     */
    virtual ~AdtVariable();

    //@}

    /** AdtVariable public methods */
    //@{

    /** Set the variable
     *  @param value The new value
     */
    void set( int64 value );

    // Get and set the ADT subtype string
    
    /** Set ADT subtype
     *  @param value The new value
     */
    void setSubType( const BAS::String& subtype );

    /** Get ADT subtype
     *  @param value The new value
     */
    const BAS::String& subType() const;


    /** Get the variable
     *  @return The value
     */
    int64 get() const;

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}

  protected:
    int64 valueM;
    BAS::String subTypeM; // hold adt sub type as string
};

//==============================================================================
// Set the value
//==============================================================================
inline void 
AdtVariable::set( int64 value )
{
  valueM = value;
}


//==============================================================================
// Get the value
//==============================================================================
inline int64
AdtVariable::get() const
{
  return valueM;
}
//
//==============================================================================
// Set the sub type
//==============================================================================
inline void 
AdtVariable::setSubType( const BAS::String& type )
{
	subTypeM = type;
}

//==============================================================================
// Get the subtype
//==============================================================================
inline const BAS::String&
AdtVariable::subType() const
{
  return (const BAS::String&)subTypeM;
}



/**<b><tt>BoolVariable</tt></b> is the interpreter큦 bool variable
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolVariable : public Variable
{
  public:
    /** BoolVariable constructors and destructor */
    //@{

    /** Constructor
     */
    BoolVariable();

    /** Constructor for direct initialization
     *  @param value Intial value
     *  @param isConst Flag if value is const
     */
    BoolVariable( bool value,
                      bool isConst = false );

    /** Destructor
     */
    virtual ~BoolVariable();

    //@}

    /** BoolVariable public methods */
    //@{

    /** Set the variable
     *  @param value The new value
     */
    void set( bool value );

    /** Get the variable
     *  @return The value
     */
    bool get() const;

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}
  protected:
    bool valueM;
};

//==============================================================================
// Set the value
//==============================================================================
inline void
BoolVariable::set( bool value )
{
  valueM = value;
}

//==============================================================================
// Get the value
//==============================================================================
inline bool
BoolVariable::get() const
{
  return valueM;
}


/**<b><tt>DateVariable</tt></b> is the interpreter큦 date variable
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateVariable : public Variable
{
  public:
    /** DateVariable constructors and destructor */
    //@{

    /** Constructor
     */
    DateVariable();

    /** Constructor
     *  @param value Intial value
     *  @param isConst Flag if value is const
     */
    DateVariable( const BAS::DateTime& value,
                      bool                isConst = false );

    /** Destructor
     */
    virtual ~DateVariable();

    //@}

    /** DateVariable public methods */
    //@{

    /** Set the variable
     *  @param value The new value
     */
    void set( const BAS::DateTime& value );

    /** Get the variable
     *  @return The value
     */
    const BAS::DateTime& get() const;

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}
  protected:
    BAS::DateTime valueM;
};

//==============================================================================
// Set the value
//==============================================================================
inline void 
DateVariable::set( const BAS::DateTime& value )
{
  valueM = value;
}

//==============================================================================
// Get the value
//==============================================================================
inline const BAS::DateTime&
DateVariable::get() const
{
  return valueM;
}


/**<b><tt>FileVariable</tt></b> is the interpreter큦 file variable
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Variable.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileVariable : public Variable
{
  public:
    /** FileVariable constructors and destructor */
    //@{

    /** Constructor
     */
    FileVariable();

    /** Destructor
     */
    virtual ~FileVariable();

    //@}

    /** DateVariable public methods */
    //@{

    /** Get the file pointer
     *  @return The file pointer
     */
    FILE* get() const;


    /** Set the file pointer
     *  @param value The file pointer
     */
    void set( FILE* value );

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}

  protected:
    
    FILE* fileM;
};

typedef RWTPtrMap<BAS::String,Variable,less<BAS::String> > VariableMap;

//==============================================================================
// Set the file pointer
//==============================================================================
inline void 
FileVariable::set( FILE* value )
{
  fileM = value;
}

//==============================================================================
// Get the file pointer
//==============================================================================
inline FILE*
FileVariable::get() const
{
  return fileM;
}

//##############################################################################
// PPoidVariable
//##############################################################################
/**<b><tt>PPoidVariable</tt></b> is the interpreter큦 poid variable
 */
class PPoidVariable : public Variable
{
  public:
    /** PPoidVariable constructors and destructor */
    //@{

    /** Constructor
     */
    PPoidVariable();

    /** Constructor
     *  @param value Intial value
     *  @param isConst Flag if value is const
     */
    PPoidVariable( const BAS::Identifier& value,
                      bool isConst = false );

    /** Destructor
     */
    virtual ~PPoidVariable();

    //@}

    /** PPoidVariable public methods */
    //@{

    /** Set the variable
     *  @param value The new value
     */
    void set( const BAS::Identifier& value );

    /** Get the variable
     *  @return The value
     */
    const BAS::Identifier& get() const;

    /** Clone the variable
     *  @return Pointer to the cloned value
     */
    virtual Variable* clone() const;

    //@}
  protected:
    BAS::Identifier valueM;
};

//==============================================================================
// Set the value
//==============================================================================
inline void
PPoidVariable::set( const BAS::Identifier& value )
{
  valueM = value;
}

//==============================================================================
// Get the value
//==============================================================================
inline const BAS::Identifier&
PPoidVariable::get() const
{
  return valueM;
}
}
#endif // VARIABLE_HPP
