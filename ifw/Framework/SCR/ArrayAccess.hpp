#ifndef SCR_ARRAYACCESS_HPP
#define SCR_ARRAYACCESS_HPP 
/* @(#)% Version: ArrayAccess.hpp:PlatformR2Int:2:2006-Jul-16 15:28:40 % */

//==============================================================================
//
// 	Copyright (c) 1998, 2023, Oracle and/or its affiliates. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the iScript array accessors.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// $RCSfile: ArrayAccess.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
//------------------------------------------------------------------------------
// Revision 1.3  2004/18/08 ammon
// PRSF00136596:  Add PPoid support.
//
// Revision 1.2  2000/09/06 11:59:30  sd
// - Copy & Paste error for private copy constructors removed
//
// Revision 1.1  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
//==============================================================================

#ifndef SCR_DATA_HPP
  #include "SCR/Data.hpp"
#endif
namespace SCR 
{
class Array;
class Hash;

/**<b><tt>ArrayVariableAccess</tt></b> is the iScript accessor data node
 * for arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ArrayVariableAccess : public ArrayNode
{
  public:
    /**@name ArrayNode constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array member value
     */
    ArrayVariableAccess( Array* array );

    /** Destructor
     */
    virtual ~ArrayVariableAccess();

    //@}

    /**@name ArrayVariableAccess public methods */
    //@{

    /** Access an array value
     *  @return Pointer to the array value
     */
    virtual Array* result();

    /** Get the container datatype
     *  @return The container datatype of the array
     */
    virtual int containerType() const;

    //@}

  protected:

    /* Get the default value
     * @return Pointer to the default variable 
     */
    virtual const Variable* defaultValue() const;

  private:
    // Hide the default and copy constructor
    ArrayVariableAccess();
    ArrayVariableAccess( const ArrayVariableAccess& array );

    // instance members
    Array* arrayM;
};

/**<b><tt>ArrayArrayAccess</tt></b> is the accessor for arrays of arrays
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ArrayArrayAccess : public ArrayNode
{
  public:
    /**@name ArrayArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    ArrayArrayAccess( ArrayNode* arrayNode,
                          LongNode*  indexNode );

    /** Destructor
     */
    virtual ~ArrayArrayAccess();

    //@}

    /**@name LongArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual Array* result();

    /** Get the container datatype
     *  @return The container datatype of the array
     */
    virtual int containerType() const;

    /** Get the default value
     *  @return Pointer to the default variable 
     */
    virtual const Variable* defaultValue() const;

    //@}

  private:
    // Hide the default and copy constructor
    ArrayArrayAccess();
    ArrayArrayAccess( const ArrayArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};


/**<b><tt>LongArrayAccess</tt></b> is the accessor for values from long 
 * arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongArrayAccess : public LongDataNode
{
  public:
    /**@name LongArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    LongArrayAccess( ArrayNode* array,
                         LongNode*  indexNode );

    /** Destructor
     */
    virtual ~LongArrayAccess();

    //@}

    /**@name LongArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual int64 result();

    /** Set the array value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( int64 value );

    //@}

  private:
    // Hide the default and copy constructor
    LongArrayAccess();
    LongArrayAccess( const LongArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};



/**<b><tt>AdtArrayAccess</tt></b> is the accessor for values from long 
 * arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class AdtArrayAccess : public AdtDataNode
{
  public:
    /**@name AdtArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    AdtArrayAccess( ArrayNode* array,
                         LongNode*  indexNode );

    /** Destructor
     */
    virtual ~AdtArrayAccess();

    //@}

    /**@name AdtArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual int64 result();

    /** Set the array value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( int64 value );

    /** return the ADT subtype string of this array
     *  @return <b>BAS::String&</b>
     */
    const BAS::String& subType() const;

    /** Set the ADT subtype string
     *  @param type The ADT subtype string( ie, "Flist", "Poid", etc)
     *  @return <b>void</b>
     */
    void setSubType( const BAS::String& type );
    //@}

  private:
    // holds ADT subtype string
    BAS::String		subTypeM;
    // Hide the default and copy constructor
    AdtArrayAccess();
    AdtArrayAccess( const AdtArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
    static const BAS::String  subTypeCM;
};




/**<b><tt>StringArrayAccess</tt></b> is the accessor for values from String 
 * arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringArrayAccess : public StringDataNode
{
  public:
    /**@name StringArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    StringArrayAccess( ArrayNode* array,
                           LongNode*  indexNode );

    /** Destructor
     */
    virtual ~StringArrayAccess();

    //@}

    /**@name StringArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual const BAS::String& result();

    /** Set the array value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::String& value );

    //@}

  private:
    // Hide the default and copy constructor
    StringArrayAccess();
    StringArrayAccess( const StringArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};

/**<b><tt>DecimalArrayAccess</tt></b> is the accessor for values from 
 * Decimal arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalArrayAccess : public DecimalDataNode
{
  public:
    /**@name DecimalArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    DecimalArrayAccess( ArrayNode* array,
                            LongNode*  indexNode );

    /** Destructor
     */
    virtual ~DecimalArrayAccess();

    //@}

    /**@name DecimalArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual const BAS::Decimal& result();

    /** Set the array value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::Decimal& value );

    //@}

  private:
    // Hide the default and copy constructor
    DecimalArrayAccess();
    DecimalArrayAccess( const DecimalArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};

/**<b><tt>DateArrayAccess</tt></b> is the accessor for values from 
 * Decimal arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateArrayAccess : public DateDataNode
{
  public:
    /**@name DateArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    DateArrayAccess( ArrayNode* array,
                            LongNode*  indexNode );

    /** Destructor
     */
    virtual ~DateArrayAccess();

    //@}

    /**@name DateArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual const BAS::DateTime& result();

    /** Set the array value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::DateTime& value );

    //@}

  private:
    // Hide the default and copy constructor
    DateArrayAccess();
    DateArrayAccess( const DateArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};

/**<b><tt>BoolArrayAccess</tt></b> is the accessor for values from 
 *  Bool arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolArrayAccess : public BoolDataNode
{
  public:
    /**@name BoolArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    BoolArrayAccess( ArrayNode* array,
                         LongNode*  indexNode );

    /** Destructor
     */
    virtual ~BoolArrayAccess();

    //@}

    /**@name BoolArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual bool result();

    /** Set the array value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( bool value );

    //@}

  private:
    // Hide the default and copy constructor
    BoolArrayAccess();
    BoolArrayAccess( const BoolArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};

/**<b><tt>HashArrayAccess</tt></b> is the accessor for values from 
 *  hash arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashArrayAccess : public HashNode
{
  public:
    /**@name HashArrayAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param array The array to access
     */
    HashArrayAccess( ArrayNode* array,
                         LongNode*  indexNode );

    /** Destructor
     */
    virtual ~HashArrayAccess();

    //@}

    /**@name HashArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual Hash* result();

    /** Get the container datatype
     *  @return The container datatype of the hash
     */
    virtual int containerType() const;

    /** Get the default value
     *  @return Pointer to the default variable 
     */
    virtual const Variable* defaultValue() const;

    //@}

  private:
    // Hide the default and copy constructor
    HashArrayAccess();
    HashArrayAccess( const HashArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};

/**<b><tt>PPoidArrayAccess</tt></b> is the accessor for values from
 * PPoid arrays.
 */
class PPoidArrayAccess : public PPoidDataNode
{
  public:
    /**@name PPoidArrayAccess constructors and destructor */
    //@{

    /** Constructor
     *  @param array The array to access
     */
    PPoidArrayAccess( ArrayNode* array,
                        LongNode*  indexNode );

    /** Destructor
     */
    virtual ~PPoidArrayAccess();

    //@}

    /**@name PPoidArrayAccess public methods */
    //@{

    /** Access the array value
     *  @return The array value
     */
    virtual const BAS::Identifier& result();

    /** Set the array value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::Identifier& value );

    //@}

  private:
    // Hide the default and copy constructor
    PPoidArrayAccess();
    PPoidArrayAccess( const PPoidArrayAccess& other );

    // instance members
    ArrayNode* arrayNodeM;
    LongNode*  indexNodeM;
};
}
#endif // ARRAYACCESS_HPP
