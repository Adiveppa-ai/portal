#ifndef SCR_DATEFUNCTIONS_HPP
#define SCR_DATEFUNCTIONS_HPP
/* @(#)%Portal Version: DateFunctions.hpp:RWSmod7.3.1Int:1:2007-Jun-28 07:00:49 % */
//==============================================================================
//
// Copyright (c) 1998 - 2007 Oracle. All rights reserved.
//
// This material is the confidential property of Oracle Corporation or
// its licensors and may be used, reproduced, stored or transmitted only
// in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   The interpreter´s date functions.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Yogesh Joshi
//
// $RCSfile: DateFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:26 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DateFunctions.hpp,v $
// Revision 1.6  2007/04/19 11:35:39  yjoshi
// - Added an iScript Function Declaration CurrentTimeInMillis.
//
// Revision 1.5  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.4  2000/04/11 11:41:03  sd
// - New function dateIsValid(Date) added.
//
// Revision 1.3  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.2  2000/03/10 08:20:12  sd
// Changed the interface for the factory functions.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// Initial revision.
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
namespace SCR
{

/**<b><tt>Sysdate</tt></b> is the function node for getting the system
 *  date/time.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DateFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:26 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Sysdate : public DateNode
{
  public:
    /**@name Sysdate constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Sysdate();

    //@}

    /**@name Sysdate public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::DateTime& result();

    /** Create a sysdate() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     */
    Sysdate();

    // instance members
    BAS::DateTime dateTimeM;
};

/**<b><tt>StrToDate</tt></b> is the function node for creating a date 
 * from a string.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DateFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:26 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrToDate : public DateNode
{
  public:
    /**@name StrToDate constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrToDate();

    //@}

    /**@name StrToDate public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::DateTime& result();

    /** Create a strToDate() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:
    /** Constructor
     *  @param string String node to convert
     */
    StrToDate( StringNode* string, StringNode * format );

    // instance members
    StringNode*   stringM;
    StringNode*   formatM;
    BAS::DateTime      dateTimeM;
};

/**<b><tt>DateDiff</tt></b> calculate the difference between to dates.
 *  The difference is returned in seconds.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DateFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:26 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateDiff : public LongNode
{
  public:
    /**@name DateDiff constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DateDiff();
    
    //@}

    /**@name DateDiff public methods*/
    //@{

    /** Get the difference of the two dates in seconds
     *  @return difference in seconds
     */
    virtual int64 result();

    /** Create a dateDiff() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param date1 the first date
     *  @param date2 the second date
     */
    DateDiff( DateNode* date1,
                    DateNode* date2 );

    // instance members
    DateNode* date1M;
    DateNode* date2M;
};

/**<b><tt>DateIsValid</tt></b> is the function node to check if a date
 *  is valid
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DateFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:26 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateIsValid : public BoolNode
{
  public:
    /**@name DateIsValid constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DateIsValid();

    //@}

    /**@name DateIsValid public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual bool result();

    /** Create a dateIsValid() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     */
    DateIsValid( DateNode* dateNode );

    // instance members
    DateNode* dateNodeM;
};
/**<b><tt>CurrentTimeInMillis</tt></b> is the function node to get the Time in
 *  miliSeconds
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DateFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:26 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
  class CurrentTimeInMillis : public SCR::LongNode
  {
    public:
      /**@name CurrentTimeInMillis constructors and destructor */
      //@{

      /** Destructor
       */
      virtual ~CurrentTimeInMillis();

      //@}


      /**@name IXT_CurrentTimeInMillis public methods */
      //@{

      /** Execute the result() function
       *  @return The current time in the Milli Seconds.
       */
      int64 result();

      /** Factory for creation of the function node
       *  @param interpreter Interpreter for the function
       *  @param stack Stack with parameters etc
       *  @param descr Function description
       *  @return <b>Pointer</b> on success, <b>0</b> otherwise
       */
      static SCR::Node* factory( SCR::Interpreter&    interpreter,
                                SCR::ParserStack&    stack,
                                const SCR::FctDescr& descr );

      //@}

    protected:
      /* Constructor
       * @param extension Pointer to the integRate iScript extension
       */
      CurrentTimeInMillis();

    private:
      // Hide the copy constructor and assignment operator
      CurrentTimeInMillis( const CurrentTimeInMillis& );
      const CurrentTimeInMillis& operator=( const CurrentTimeInMillis& );
  };
}
#endif // DATEFUNCTIONS_HPP
