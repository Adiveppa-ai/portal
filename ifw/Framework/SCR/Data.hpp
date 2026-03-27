#ifndef SCR_DATA_HPP
#define SCR_DATA_HPP
/* @(#)%Portal Version: Data.hpp:PlatformR2Int:3:2006-Jul-16 15:28:16 % */

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
// Block: FCT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the data classes for the Interpreter.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// $RCSfile: Data.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
//------------------------------------------------------------------------------
// Log 2004/18/08 ammon
// PRSF00136096:  Added PPoid support.
//
// Log 2002/07/29 cdiab
// - added seek() and tell() methode for file access
//
// Revision 1.10  2001/09/16 21:11:59  sd
// - PETS #37618 Compiler warnings removed
//
// Revision 1.9  2001/05/23 10:47:39  sd
// - Changes for the new iRules extensions.
//
// Revision 1.8  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.7  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.6  2000/05/25 14:02:55  sd
// - function Bool fileFlush(File) added.
//
// Revision 1.5  2000/03/23 14:51:04  sd
// - Functions fileReadLine(), fileEof() and fileIsOpen() added.
//
// Revision 1.4  2000/03/23 11:25:36  sd
// - support for file variables added.
// - new class FileVariable
//
// Revision 1.3  2000/03/10 11:38:13  sd
// Function isLeftValue() removed.
//
// Revision 1.2  2000/03/06 16:48:16  sd
// Implementation changed to support the SUN CC compiler.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// Initial revision.
//
//==============================================================================

#include <stdio.h>
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
namespace SCR
{
/**<b><tt>LongConstant</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongConstant : public LongNode
{
  public:

    /**@name LongConstant constructors and destructor */
    //@{
    
    /** Constructor
     *  @param l The int64 value
     */
    LongConstant( int64 l );

    //@}

    /**@name LongConstant public methods */
    //@{
    
    /** Get the int64 value
     *  @return The int64 value
     */
    virtual int64 result();

	/** Promote to the named type
	 * @param type type to promote to
	 * @return Node* pointer to node containing promoted type
	 */
	Node* promote(int type) const;

    //@}

  private:
    int64 constantM;
};

/**<b><tt>DecimalConstant</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalConstant : public DecimalNode
{
  public:

    /**@name DecimalConstant constructors and destructor */
    //@{
    
    /** Constructor
     *  @param decimal The decimal value
     */
    DecimalConstant( const BAS::Decimal& decimal );

    /** Destructor
     */
    ~DecimalConstant();

    //@}

    /**@name DecimalConstant public methods */
    //@{
    
    /** Get the int64 value
     *  @return The decimal value
     */
    const BAS::Decimal& result();

    //@}

  private:
    BAS::Decimal dataM;
};

/**<b><tt>DateConstant</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateConstant : public DateNode
{
  public:

    /**@name DateConstant constructors and destructor */
    //@{
    
    /** Constructor
     *  @param date The date value
     */
    DateConstant( const BAS::DateTime& dateTime );

    /** Destructor
     */
    ~DateConstant();

    //@}

    /**@name DateConstant public methods */
    //@{
    
    /** Get the int64 value
     *  @return The date value
     */
    const BAS::DateTime& result();

    //@}

  private:
    BAS::DateTime dataM;
};

/**<b><tt>StringConstant</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringConstant : public StringNode
{
  public:

    /**@name StringConstant constructors and destructor */
    //@{
    
    /** Constructor
     *  @param s The string value
     */
    StringConstant( const BAS::String& s );

    /** Destructor
     */
    ~StringConstant();

    //@}

    /**@name StringConstant public methods */
    //@{
    
    /** Get the string value
     *  @return The string value
     */
    const BAS::String& result();

    //@}

  private:
    BAS::String dataM;
};

/**<b><tt>BoolConstant</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolConstant : public BoolNode
{
  public:

    /**@name BoolConstant constructors and destructor */
    //@{
    
    /** Constructor
     *  @param b The bool value
     */
    BoolConstant( bool b );

    /** Destructor
     */
    virtual ~BoolConstant();

    //@}

    /**@name BoolConstant public methods */
    //@{
    
    /** Get the bool value
     *  @return The bool value
     */
    virtual bool result();

    /** Set the bool value
     *  @param value The new bool value
     *  @return <b>true</b>
     */
    bool set( bool value );

    //@}

  private:
    bool dataM;
};

/**<b><tt>PPoidConstant</tt></b>
 */
class PPoidConstant : public PPoidNode
{
  public:

    /**@name PPoidConstant constructors and destructor */
    //@{

    /** Constructor
     *  @param poid The poid value
     */
    PPoidConstant( const BAS::Identifier& poid );

    /** Destructor
     */
    ~PPoidConstant();

    //@}

    /**@name PPoidConstant public methods */
    //@{

    /** Get the poid value
     *  @return The poid value
     */
    const BAS::Identifier& result();

    //@}

  private:
    BAS::Identifier dataM;
};

/**<b><tt>LongDataNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongDataNode : public LongNode
{
  public:

    /**@name LongDataNode public methods */
    //@{
    
    /** Get the value
     *  @return The int64 value
     */
    virtual int64 result() = 0;

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( int64 value ) = 0;

    //@}
};


/**<b><tt>AdtDataNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class AdtDataNode : public AdtNode
{
  public:

    /**@name AdtDataNode public methods */
    //@{
    
    /** Get the value
     *  @return The int64 value
     */
    virtual int64 result() = 0;

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( int64 value ) = 0;

    //@}
};


/**<b><tt>StringDataNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringDataNode : public StringNode
{
  public:

    /**@name StringDataNode public methods */
    //@{
    
    /** Get the value
     *  @return The string value
     */
    virtual const BAS::String& result() = 0;

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( const BAS::String& value ) = 0;

    //@}
};

/**<b><tt>DecimalDataNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalDataNode : public DecimalNode
{
  public:

    /**@name DecimalDataNode public methods */
    //@{
    
    /** Get the value
     *  @return The decimal value
     */
    virtual const BAS::Decimal& result() = 0;

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( const BAS::Decimal& value ) = 0;

    //@}
};


/**<b><tt>DateDataNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateDataNode : public DateNode
{
  public:

    /**@name DateDataNode public methods */
    //@{
    
    /** Get the value
     *  @return The decimal value
     */
    virtual const BAS::DateTime& result() = 0;

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( const BAS::DateTime& value ) = 0;

    //@}
};

/**<b><tt>PPoidDataNode</tt></b>
 */
class PPoidDataNode : public PPoidNode
{
  public:

    /**@name PPoidDataNode public methods */
    //@{

    /** Get the value
     *  @return The decimal value
     */
    virtual const BAS::Identifier& result() = 0;

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( const BAS::Identifier& value ) = 0;

    //@}
};

/**<b><tt>AdtVariableAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class AdtVariableAccess : public AdtDataNode
{
  public:

    /**@name AdtVariableAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param variable The associated variable
     */
    AdtVariableAccess( AdtVariable* variable );

    /** Destructor 
     */
    virtual ~AdtVariableAccess();

    //@}

    /**@name AdtVariableAccess public methods */
    //@{
    
    /** Get the int64 value
     *  @return The int64 value
     */
    virtual int64 result();

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b>
     */
    virtual bool set( int64 value );

    /** Get the Adt subtype value (ie, "Flist", "Poid", etc.)
     *  @return <b>text describing ADT subtype </b>
     */
    const BAS::String& subType() const;

    /** Set the ADT subType string
     *  @param type The adt subtype string to use(ie, "Flist", "Poid", etc.)
     *  @return void
     */
    void setSubType(const BAS::String& type );

    //@}

  private:
    AdtVariable* variableM;
};


/**<b><tt>LongVariableAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongVariableAccess : public LongDataNode
{
  public:

    /**@name LongVariableAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param variable The associated variable
     */
    LongVariableAccess( LongVariable* variable );

    /** Destructor 
     */
    virtual ~LongVariableAccess();

    //@}

    /**@name LongVariableAccess public methods */
    //@{
    
    /** Get the int64 value
     *  @return The int64 value
     */
    virtual int64 result();

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b>
     */
    virtual bool set( int64 value );

    //@}

  private:
    LongVariable* variableM;
};


/**<b><tt>DecimalVariableAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalVariableAccess : public DecimalDataNode
{
  public:

    /**@name DecimalVariableAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param variable The associated variable
     */
    DecimalVariableAccess( DecimalVariable* variable );

    //@}

    /**@name DecimalVariableAccess public methods */
    //@{
    
    /** Get the value
     *  @return The decimal value
     */
    virtual const BAS::Decimal& result();

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b>
     */
    virtual bool set( const BAS::Decimal& value );

    //@}

  private:
    DecimalVariable* variableM;
};

/**<b><tt>DateVariableAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateVariableAccess : public DateDataNode
{
  public:

    /**@name DateVariableAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param variable The associated variable
     */
    DateVariableAccess( DateVariable* variable );

    //@}

    /**@name DateVariableAccess public methods */
    //@{
    
    /** Get the value
     *  @return The date value
     */
    virtual const BAS::DateTime& result();

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b>
     */
    virtual bool set( const BAS::DateTime& value );

    //@}

  private:
    DateVariable* variableM;
};

/**<b><tt>StringVariableAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringVariableAccess : public StringDataNode
{
  public:

    /**@name StringVariableAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param variable The associated variable
     */
    StringVariableAccess( StringVariable* variable );

    //@}

    /**@name StringVariableAccess public methods */
    //@{
    
    /** Get the value
     *  @param The string value
     *  @return <b>true</b>
     */
    virtual const BAS::String& result();

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b>
     */
    virtual bool set( const BAS::String& value );

    /** Get the string variable (used by iRules)
     *  @return Pointer to the string variable
     */
    StringVariable* variable();

    //@}

  private:
    StringVariable* variableM;
};

/**<b><tt>PPoidVariableAccess</tt></b>
 */
class PPoidVariableAccess : public PPoidDataNode
{
  public:

    /**@name PPoidVariableAccess constructors and destructor */
    //@{

    /** Constructor
     *  @param variable The associated variable
     */
    PPoidVariableAccess( PPoidVariable* variable );

    //@}

    /**@name PPoidVariableAccess public methods */
    //@{

    /** Get the value
     *  @return The date value
     */
    virtual const BAS::Identifier& result();

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b>
     */
    virtual bool set( const BAS::Identifier& value );

    //@}

  private:
    PPoidVariable* variableM;
};

/**<b><tt>BoolDataNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolDataNode : public BoolNode
{
  public:

    /**@name BoolDataNode public methods */
    //@{
    
    /** Get the value
     *  @return The value
     */
    virtual bool result() = 0;

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool set( bool value ) = 0;

    //@}
};

/**<b><tt>BoolVariableAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolVariableAccess : public BoolDataNode
{
  public:

    /**@name BoolVariableAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param variable The associated variable
     */
    BoolVariableAccess( BoolVariable* variable );

    //@}

    /**@name BoolVariableAccess public methods */
    //@{
    
    /** Get the value
     *  @return The bool value
     */
    virtual bool result();

    /** Set the value
     *  @param value The new value
     *  @return <b>true</b>
     */
    virtual bool set( bool value );

    //@}

  private:
    BoolVariable* variableM;
};

/**<b><tt>FileData</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Data.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileData : public Node
{
  public:

    /**@name FileData constructors and destructor */
    //@{
    
    /** Constructor.
     *  @param variable The associated file variable
     */
    FileData( FileVariable* variable );

    /** Destructor
     */
    virtual ~FileData();

    //@}

    /**@name FileData public methods */
    //@{

    /** Open the file 
     *  @param fileName The name of the file to open
     *  @param openMode The openmode for the file
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool open( const BAS::String& fileName,
               const BAS::String& openMode );

    /** Close the file
     */
    void close();

    /** Write a string to the output file 
     *  @param string  The string to write
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool writeString( const BAS::String& string );

    /** Read a line from the input file
     *  @param string The string for the read data
     *  @param size The maximal line size
     */
    bool readLine( StringDataNode* string, size_t size );

    /** Check for end of file
     *  @return <b>true</b> if end-of-file, <b>false</b> otherwise
     */
    bool eof();

    /** Check if file is open 
     *  @return <b>true</b> if open, <b>false</b> otherwise
     */
    bool isOpen();

    /** Flush the file data
     */
    bool flush();

    /** Get the position of the read/write pointer in the current file
     *  @return <b>offset in bytes</b> on success, <b>-1</b> otherwise
     */
    int64 tell();
    
    /** Set the position of the read/write pointer in the current file
     *  @param long offset The offset in bytes from the start of the file
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    /* note, we have to use long here because fseek() requires it */
    bool seek(long offset);
    
    //@}

  private:

    // instance members
    FileVariable* variableM;
};
}
#endif // DATA_HPP
