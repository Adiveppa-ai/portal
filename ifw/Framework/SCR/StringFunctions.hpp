#ifndef SCR_STRINGFUNCTIONS_HPP
#define SCR_STRINGFUNCTIONS_HPP

//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the interpreter string functions.
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
// $RCSfile: StringFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:04:15 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StringFunctions.hpp,v $
// Revision 1.12  2001/02/07 11:22:27  sd
// - New function Long strByteValue(String).
//
// Revision 1.11  2000/11/13 15:50:24  sd
// - New function String strStrip(String,[Long,[String]])
//
// Revision 1.10  2000/09/26 13:33:04  sd
// - Module SCR is now only dependent from BAS
//
// Revision 1.9  2000/08/17 11:35:40  sd
// - first version with iScript extensions
//
// Revision 1.8  2000/04/18 13:23:27  sd
// - function Long strSearchRegExpr(String,String[,Long]) added
// - function Bool fileDelete(String) added.
//
// Revision 1.7  2000/04/18 12:04:27  sd
// - new function String strMatch(String,const String [, Long]) added.
//
// Revision 1.6  2000/04/11 07:47:54  sd
// - Function strSearch() added.
//
// Revision 1.5  2000/03/29 06:40:15  sd
// - Functions strStartsWith() and strEndsWith() added.
//
// Revision 1.4  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.3  2000/03/10 12:22:13  sd
// - stringDecode() function added.
// - number of arguments check modified.
// - unlimited number of arguments supported.
//
// Revision 1.2  2000/03/10 08:20:12  sd
// - Changed the interface for the factory functions.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// - Initial revision.
//
//==============================================================================

#ifndef RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef RW_TOOLS_RE_H
  #include <rw/re.h>
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif

namespace SCR
{
/**<b><tt>Substr</tt></b> is the function node for the substr() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Substr : public StringNode
{
  public:
    /**@name Substr constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Substr();
    
    //@}

    /**@name Substr public methods*/
    //@{

    /** Execute the substr() function
     *  @return result of substr() function
     */
    virtual const BAS::String& result();

    /** Create a substr() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param stringNode Source string
     *  @param idxNode Start position for substring (starts with position 0)
     *  @param lenNode Length of substring
     */
    Substr( StringNode* stringNode,
                LongNode*   idxNode,
                LongNode*   lenNode );

    // instance members
    StringNode* stringNodeM;
    LongNode*   idxNodeM;
    LongNode*   lenNodeM;
    BAS::String      resultM;
};

/**<b><tt>ToUpper</tt></b> is the function node for the toUpper() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ToUpper : public StringNode
{
  public:
    /**@name ToUpper constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~ToUpper();
    
    //@}

    /**@name ToUpper public methods*/
    //@{

    /** Execute the toUpper() function
     *  @return result of toUpper() function
     */
    virtual const BAS::String& result();

    /** Create a toUpper() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param stringNode String to convert
     */
    ToUpper( StringNode* stringNode );

    // instance members
    StringNode* stringNodeM;
    BAS::String        resultM;
};

/**<b><tt>ToLower</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ToLower : public StringNode
{
  public:
    /**@name ToLower constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~ToLower();
    
    //@}

    /**@name ToLower public methods*/
    //@{

    /** Execute the toLower() function
     *  @return result of toLower() function
     */
    virtual const BAS::String& result();

    /** Create a toLower() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param stringNode String to convert
     */
    ToLower( StringNode* stringNode );

    // instance members
    StringNode* stringNodeM;
    BAS::String        resultM;
};

/**<b><tt>Replace</tt></b> is the function node for the replace function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Replace : public StringNode
{
  public:
    /**@name Replace constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Replace();
    
    //@}

    /**@name Replace public methods*/
    //@{

    virtual const BAS::String& result();

    /** Create a replace() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param toReplaceNode String in which to replace
     *  @param idxNode Start position for replace operation (starts with 0)
     *  @param lenNode Length of substring to replace
     *  @param replaceNode String to insert
     */
    Replace( StringNode* toReplaceNode,
                 LongNode*   idxNode,
                 LongNode*   lenNode,
                 StringNode* replaceNode );

    // instance members
    StringNode* toReplaceNodeM;
    LongNode*   posNodeM;
    LongNode*   lenNodeM;
    StringNode* replaceNodeM;
    BAS::String        resultM;
};

/**<b><tt>DecimalToStr</tt></b> implements the decimalToStr() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalToStr : public StringNode
{
  public:
    /**@name DecimalToStr constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DecimalToStr();

    //@}

    /**@name DecimalToStr public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::String& result();

    /** Create a decimalToStr() function on datastack
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     *  @param decimal Value to convert
     *  @param precision Precision for conversion (can be 0)
     */
    DecimalToStr( DecimalNode* decimal,
                      LongNode*    precision );

    // instance members
    DecimalNode* decimalM;
    LongNode*    precisionM;
    BAS::String       resultM;
};

/**<b><tt>DateToStr</tt></b> implements the dateToStr() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateToStr : public StringNode
{
  public:
    /**@name DateToStr constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DateToStr();

    //@}

    /**@name DateToStr public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::String& result();

    /** Create a dateToStr() function on datastack
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     *  @param date Value to convert
     *  @param format Format string to convert the date
     */
    DateToStr( DateNode* date, StringNode * format );
  
    // instance members
    DateNode    * dateM;
    StringNode  * formatM;
    BAS::String        resultM;
};

/**<b><tt>LongToStr</tt></b> implements the longToStr() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongToStr : public StringNode
{
  public:
    /**@name LongToStr constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongToStr();

    //@}

    /**@name LongToStr public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::String& result();

    /** Create a longToStr() function on datastack
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     *  @param longnode Value to convert
     */
    LongToStr( LongNode* longnode );

    // instance members
    LongNode*    longM;
    BAS::String         resultM;
};

/**<b><tt>StringDecode</tt></b> implements the stringDecode() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringDecode : public StringNode
{
  public:
    /**@name StringDecode constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StringDecode();

    //@}

    /**@name StringDecode public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::String& result();

    /** Create a stringDecode() function on datastack
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    /** Add a new map entry to the map.
     *  @param source Source mapping entry
     *  @param dest Destination mapping entry
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addMapEntry( const BAS::String& source, 
                      const BAS::String& dest );

    /** Set the source node
     *  @param The decode node
     */
    void decodeNode( StringNode* decodeNode );

    /** Set the default value
     *  @param The default value
     */
    void defaultValue( const BAS::String& defValue );
    
    //@}

  protected:

    /** Constructor
     */
    StringDecode();

    RWTValMap< BAS::String,BAS::String,less<BAS::String> > mapM;
    StringNode*                         decodeNodeM;
    BAS::String                              defaultValueM;
    BAS::String                              resultM;
};

/**<b><tt>StrStartsWith</tt></b> is the function node for function
 * strStartsWith(String,String)
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrStartsWith : public BoolNode
{
  public:
    /**@name StrStartsWith constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrStartsWith();
    
    //@}

    /**@name StrStartsWithh public methods*/
    //@{

    /** Check if the string starts with the prefix
     *  @return <b>true</b> if string starts with suffix, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a length function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     */
    StrStartsWith( StringNode* string,
                       StringNode* prefix );

    StringNode* stringNodeM;
    StringNode* prefixNodeM;
};

/**<b><tt>StrEndsWith</tt></b> is the function node for function
 * strEndsWith(String,String)
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrEndsWith : public BoolNode
{
  public:
    /**@name StrEndsWith constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrEndsWith();
    
    //@}

    /**@name StrEndsWithh public methods*/
    //@{

    /** Check if the string starts ends the suffix
     *  @return <b>true</b> if string ends with suffix, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a length function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param string The string node to check
     *  @param suffix The suffix to look for
     */
    StrEndsWith( StringNode* string,
                     StringNode* suffix );

    StringNode* stringNodeM;
    StringNode* suffixNodeM;
};

/**<b><tt>StrSearch</tt></b> is the function node for function
 * strSearch(String,String[,Long])
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrSearch : public LongNode
{
  public:
    /**@name StrSearch constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrSearch();
    
    //@}

    /**@name StrSearch public methods*/
    //@{

    /** Execute the function
     *  @return <b>true</b> if string ends with suffix, <b>false</b> otherwise
     */
    virtual int64 result();

    /** Create a strSearch() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param string The string node to check
     *  @param suffix The suffix to look for
     */
    StrSearch( StringNode* string,
                   StringNode* search,
                   LongNode*   indexNode = 0 );

    StringNode* stringNodeM;
    StringNode* searchNodeM;
    LongNode*   indexNodeM;
};

/**<b><tt>StrMatch</tt></b> is the function node for matching regular
 * expressions against strings
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrMatch : public StringNode
{
  public:
    /**@name StrMatch constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrMatch();
    
    //@}

    /**@name StrMatch public methods*/
    //@{

    /** Execute the strMatch() function
     *  @return result of strMatch() function
     */
    virtual const BAS::String& result();

    /** Create a strMatch() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param stringNode String to examine
     *  @param regExp String specifying the regular expression
     *  @param 
     */
    StrMatch( StringNode*   stringNode,
                  LongNode*     indexNode,
                  const BAS::String& regularExpression );

    /** Check if the script is valid
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

  private:
    // disallow use of default and copy constructor
    StrMatch();
    StrMatch( const StrMatch& );
    const StrMatch& operator=( const StrMatch& );

    // instance members
    StringNode* stringNodeM;
    LongNode*   indexNodeM;
    BAS::String      resultM;
    RWCRExpr        regExpM;
};

/**<b><tt>StrSearchRegExpr</tt></b> is the function node for searching
 * regular expressions in strings.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrSearchRegExpr : public LongNode
{
  public:
    /**@name StrSearchRegExpr constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrSearchRegExpr();
    
    //@}

    /**@name StrSearchRegExpr public methods*/
    //@{

    /** Execute the strMatch() function
     *  @return result of strMatch() function
     */
    virtual int64 result();

    /** Create a strMatch() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param stringNode String to examine
     *  @param regExp String specifying the regular expression
     *  @param 
     */
    StrSearchRegExpr( StringNode*   stringNode,
                  LongNode*     indexNode,
                  const BAS::String& regularExpression );

    /** Check if the script is valid
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

  private:
    // disallow use of default and copy constructor
    StrSearchRegExpr();
    StrSearchRegExpr( const StrSearchRegExpr& );
    const StrSearchRegExpr& operator=( const StrSearchRegExpr& );


    // instance members
    StringNode* stringNodeM;
    LongNode*   indexNodeM;
    BAS::String      resultM;
    RWCRExpr        regExpM;
};

/**<b><tt>StrStrip</tt></b> is the function node for stripping characters
 * at 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrStrip : public StringNode
{
  public:
    /**@name StrStrip constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrStrip();
    
    //@}

    /**@name StrStrip public methods*/
    //@{

    /** Execute the strStrip() function
     *  @return result of strStrip() function
     */
    virtual const BAS::String& result();

    /** Create a strStrip() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param stringNode String to strip
     *  @param stripMode Stripping mode (leading, trailing, etc.)
     *  @param stripChar String specifying the strip character
     */
    StrStrip( StringNode*   stringNode,
                  LongNode*     stripMode,
                  StringNode*   stripChar );

  private:
    // disallow use of default and copy constructor
    StrStrip();
    StrStrip( const StrStrip& );
    const StrStrip& operator=( const StrStrip& );

    // instance members
    StringNode* stringNodeM;
    LongNode*   stripModeM;
    StringNode* stripCharM;
    BAS::String      resultM;
};

/**<b><tt>StrByteValue</tt></b> is the function node for converting
 * the first character of a string to it's ASCII value.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StringFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:15 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrByteValue : public LongNode
{
  public:
    /**@name StrByteValue constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrByteValue();
    
    //@}

    /**@name StrByteValue public methods*/
    //@{

    /** Execute the strByteValue() function
     *  @return result of strCharToAscii() function
     */
    virtual int64 result();

    /** Create a strByteValue() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param stringNode String to examine
     */
    StrByteValue( StringNode* stringNode );

  private:
    // disallow use of default and copy constructor
    StrByteValue();
    StrByteValue( const StrByteValue& );
    const StrByteValue& operator=( const StrByteValue& );


    // instance members
    StringNode* stringNodeM;
};
}
#endif // STRINGFUNCTIONS_HPP
