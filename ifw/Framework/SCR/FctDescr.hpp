#ifndef SCR_FCTDESCR_HPP
#define SCR_FCTDESCR_HPP 

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates. 
// 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Class for the function descriptions.
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
// $RCSfile: FctDescr.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:52 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FctDescr.hpp,v $
// Revision 1.4  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.3  2000/08/24 15:16:03  sd
// - Implementation changed to support AIX.
//
// Revision 1.2  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.1  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.6  2000/06/16 15:03:29  sd
// - Implementation changed to support the IBM AIX xlC compiler.
//
// Revision 1.5  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.4  2000/03/10 12:22:13  sd
// - stringDecode() function added.
// - number of arguments check modified.
// - unlimited number of arguments supported.
//
// Revision 1.3  2000/03/10 08:20:12  sd
// - Changed the interface for the factory functions.
//
// Revision 1.2  2000/03/07 17:00:33  sd
// - Left hand value flag for datatypes introduced.
// - Comments (C and C++ style) added to Lexer.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// - Initial revision.
//
//==============================================================================

#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
namespace SCR
{

class Interpreter;
class ParserStack;
class FctDescr;

typedef Node* (*FunctionFactory)( Interpreter&,
                                      ParserStack&,
                                      const FctDescr& );

/**<b><tt>FctDescr</tt></b> is used to describe and create functions.
 * The class saves parameters like minimal and maximal number of arguements,
 * argument types, etc.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FctDescr.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:52 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FctDescr : public Variable
{
  public:

    enum
    {
      UNLIMITED_ARGS = -1
    };

    /**@name FctDescr constructors and destructor */
    //@{

    /** Constructor
     */
    FctDescr( const BAS::String& name,
                  int               returnType,
                  int               minArgs,
                  int               maxArgs,
                  FunctionFactory   factory,
                  int               arg1 = Node::UNKNOWN_TYPE,
                  int               arg2 = Node::UNKNOWN_TYPE,
                  int               arg3 = Node::UNKNOWN_TYPE,
                  int               arg4 = Node::UNKNOWN_TYPE,
                  int               arg5 = Node::UNKNOWN_TYPE,
                  int               arg6 = Node::UNKNOWN_TYPE,
                  int               arg7 = Node::UNKNOWN_TYPE,
                  int               arg8 = Node::UNKNOWN_TYPE,
                  int               arg9 = Node::UNKNOWN_TYPE );

    //@}

    /**@name FctDescr public methods */
    //@{

    /** Clone the function description
     *  @return Pointer to cloned value
     */
    Variable* clone() const;

    /** Get the name of the function
     *  @return reference to function name
     */
    const BAS::String& name() const;

    /** Get the return type of the function
     *  @return The return type
     */
    int returnType() const;

    /** Get the maximal number of arguments
     *  @return The maximal number of arguments
     */
    int maxNumArgs() const;

    /** Get the minimal number of arguments
     *  @return The minimal number of arguments
     */
    int minNumArgs() const;

    /** Get the argument type for specified argument
     *  @param The argument number
     *  @return The datatype for this argument
     */
    int argType( int arg ) const;

    /** Add a new argument to the function
     *  @param argType The type of the new argument
     */
    void addArg( int argType );

    /** Clear the argument type array
     */
    void clearArgs();

    /** Create the function
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with function parameters etc
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool create( Interpreter& interpreter,
                 ParserStack& stack ) const;

    /** Check for correct type
     *  @param shouldType The "should" type
     *  @param isType The "is" type
     *  @return <b>true</b> if type is correct, <b>false</b> otherwise
     */
    bool checkType( int shouldType, int isType ) const;

    /** Get the functions signature 
     *  @return The functions signature
     */
    BAS::String signature() const;



    //@}

  protected:

    // instance members
    BAS::String               nameM;
    int                      returnTypeM;
    int                      minNumArgsM;
    int                      maxNumArgsM;
    RWTValOrderedVector<int> argTypeM;
    FunctionFactory          factoryM;
};

//==============================================================================
// Get the function name
//==============================================================================
inline const BAS::String&
FctDescr::name() const
{
  return nameM;
}

//==============================================================================
// Get the function name
//==============================================================================
inline int
FctDescr::returnType() const
{
  return returnTypeM;
}

//==============================================================================
// Get the maximal number of arguments
//==============================================================================
inline int
FctDescr::maxNumArgs() const
{
  return maxNumArgsM;
}

//==============================================================================
// Get the minimal number of arguments
//==============================================================================
inline int
FctDescr::minNumArgs() const
{
  return minNumArgsM;
}

//==============================================================================
// Clear the argument type array
//==============================================================================
inline void
FctDescr::clearArgs() 
{
  argTypeM.clear();
}
}
#endif // FCTDEHPP
