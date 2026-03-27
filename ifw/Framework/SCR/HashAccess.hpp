#ifndef SCR_HASHACCESS_HPP
#define SCR_HASHACCESS_HPP 
/* @(#)% Version: HashAccess.hpp:PlatformR2Int:2:2006-Jul-16 15:27:17 % */

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
//   Definition of the iScript hash accessors.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// $RCSfile: HashAccess.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
//------------------------------------------------------------------------------
// Revision 1.3  2004/18/12 ammon
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

class Hash;

/**<b><tt>HashVariableAccess</tt></b> is the iScript accessor data node
 * for hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashVariableAccess : public HashNode
{
  public:
    /**@name HashNode constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash member value
     */
    HashVariableAccess( Hash* hash );

    /** Destructor
     */
    virtual ~HashVariableAccess();

    //@}

    /**@name HashVariableAccess public methods */
    //@{

    /** Access an hash value
     *  @return Pointer to the hash value
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
    HashVariableAccess();
    HashVariableAccess( const HashVariableAccess& hash );

    // instance members
    Hash* hashM;
};

/**<b><tt>HashHashAccess</tt></b> is the accessor for hashs of hashs
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashHashAccess : public HashNode
{
  public:
    /**@name HashHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    HashHashAccess( HashNode*   hashNode,
                        StringNode* keyNode );

    /** Destructor
     */
    virtual ~HashHashAccess();

    //@}

    /**@name EbufHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
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
    HashHashAccess();
    HashHashAccess( const HashHashAccess& other );

    // instance members
    HashNode*   hashNodeM;
    StringNode* keyNodeM;
};

/**<b><tt>LongHashAccess</tt></b> is the accessor for values from long 
 * hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongHashAccess : public LongDataNode
{
  public:
    /**@name LongHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    LongHashAccess( HashNode*   hash,
                        StringNode* keyNode );

    /** Destructor
     */
    virtual ~LongHashAccess();

    //@}

    /**@name LongHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual int64 result();

    /** Set the hash value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( int64 value );

    //@}

  private:
    // Hide the default and copy constructor
    LongHashAccess();
    LongHashAccess( const LongHashAccess& other );

    // instance members
    HashNode* hashNodeM;
    StringNode*  keyNodeM;
};


/**<b><tt>AdtHashAccess</tt></b> is the accessor for values from long 
 * hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class AdtHashAccess : public AdtDataNode
{
  public:
    /**@name AdtHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    AdtHashAccess( HashNode*   hash,
                        StringNode* keyNode );

    /** Destructor
     */
    virtual ~AdtHashAccess();

    //@}

    /**@name AdtHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual int64 result();

    /** Set the hash value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( int64 value );

   /** return the ADT subtype string of this hash table
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
    AdtHashAccess();
    AdtHashAccess( const AdtHashAccess& other );

    // instance members
    HashNode* hashNodeM;
    StringNode*  keyNodeM;
    static const BAS::String  subTypeCM;
};

/**<b><tt>StringHashAccess</tt></b> is the accessor for values from String 
 * hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringHashAccess : public StringDataNode
{
  public:
    /**@name StringHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    StringHashAccess( HashNode*   hash,
                          StringNode* keyNode );

    /** Destructor
     */
    virtual ~StringHashAccess();

    //@}

    /**@name StringHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual const BAS::String& result();

    /** Set the hash value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::String& value );

    //@}

  private:
    // Hide the default and copy constructor
    StringHashAccess();
    StringHashAccess( const StringHashAccess& other );

    // instance members
    HashNode* hashNodeM;
    StringNode*  keyNodeM;
};

/**<b><tt>DecimalHashAccess</tt></b> is the accessor for values from 
 * Decimal hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalHashAccess : public DecimalDataNode
{
  public:
    /**@name DecimalHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    DecimalHashAccess( HashNode*   hash,
                           StringNode* keyNode );

    /** Destructor
     */
    virtual ~DecimalHashAccess();

    //@}

    /**@name DecimalHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual const BAS::Decimal& result();

    /** Set the hash value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::Decimal& value );

    //@}

  private:
    // Hide the default and copy constructor
    DecimalHashAccess();
    DecimalHashAccess( const DecimalHashAccess& other );

    // instance members
    HashNode* hashNodeM;
    StringNode*  keyNodeM;
};

/**<b><tt>DateHashAccess</tt></b> is the accessor for values from 
 * Decimal hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateHashAccess : public DateDataNode
{
  public:
    /**@name DateHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    DateHashAccess( HashNode*   hash,
                        StringNode* keyNode );

    /** Destructor
     */
    virtual ~DateHashAccess();

    //@}

    /**@name DateHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual const BAS::DateTime& result();

    /** Set the hash value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::DateTime& value );

    //@}

  private:
    // Hide the default and copy constructor
    DateHashAccess();
    DateHashAccess( const DateHashAccess& other );

    // instance members
    HashNode* hashNodeM;
    StringNode*  keyNodeM;
};

/**<b><tt>BoolHashAccess</tt></b> is the accessor for values from 
 *  Bool hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolHashAccess : public BoolDataNode
{
  public:
    /**@name BoolHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    BoolHashAccess( HashNode*   hash,
                        StringNode* keyNode );

    /** Destructor
     */
    virtual ~BoolHashAccess();

    //@}

    /**@name BoolHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual bool result();

    /** Set the hash value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( bool value );

    //@}

  private:
    // Hide the default and copy constructor
    BoolHashAccess();
    BoolHashAccess( const BoolHashAccess& other );

    // instance members
    HashNode*   hashNodeM;
    StringNode* keyNodeM;
};

/**<b><tt>ArrayHashAccess</tt></b> is the accessor for values from 
 *  array hashs.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashAccess.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ArrayHashAccess : public ArrayNode
{
  public:
    /**@name ArrayHashAccess constructors and destructor */
    //@{
    
    /** Constructor
     *  @param hash The hash to access
     */
    ArrayHashAccess( HashNode*   hash,
                         StringNode* keyNode );

    /** Destructor
     */
    virtual ~ArrayHashAccess();

    //@}

    /**@name ArrayHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual Array* result();

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
    ArrayHashAccess();
    ArrayHashAccess( const ArrayHashAccess& other );

    // instance members
    HashNode*   hashNodeM;
    StringNode* keyNodeM;
};

/**<b><tt>PPoidHashAccess</tt></b> is the accessor for values from
 * PPoid hashs.
 */
class PPoidHashAccess : public PPoidDataNode
{
  public:
    /**@name PPoidHashAccess constructors and destructor */
    //@{

    /** Constructor
     *  @param hash The hash to access
     */
    PPoidHashAccess( HashNode*   hash,
                     StringNode* keyNode );

    /** Destructor
     */
    virtual ~PPoidHashAccess();

    //@}

    /**@name PPoidHashAccess public methods */
    //@{

    /** Access the hash value
     *  @return The hash value
     */
    virtual const BAS::Identifier& result();

    /** Set the hash value
     *  @param value The new value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool set( const BAS::Identifier& value );

    //@}

  private:
    // Hide the default and copy constructor
    PPoidHashAccess();
    PPoidHashAccess( const PPoidHashAccess& other );

    // instance members
    HashNode* hashNodeM;
    StringNode*  keyNodeM;
};
}
#endif // HASHACCESS_HPP
