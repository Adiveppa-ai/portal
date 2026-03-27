#ifndef SCR_PATTERNINTERFACE_HPP
#define SCR_PATTERNINTERFACE_HPP

//==============================================================================
//
//             1998, 1999, 2000 (c) Copyright by SOLUTION42 AG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Base interface class for all classes used to return compare patterns.
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
// $RCSfile: CompareInterface.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:00 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: CompareInterface.hpp,v $
// Revision 1.2  2001/05/23 10:47:39  sd
// - Changes for the new iRules extensions.
//
// Revision 1.1  2000/09/27 07:08:01  sd
// - New interface for compilation of compare patters introduced.
//
//==============================================================================
namespace SCR
{
class BoolNode;
class Interpreter;
class ParserStack;

/** <b><tt>CompareInterface</tt></b> is the interface class used by the
 *  compiler to return compare patterns to applications.
 */
class CompareInterface
{
  public:

    /**@name CompareInterface public methods */
    //@{

    /** Is used by the compiler when a new bool condition is compile
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addBoolCondition( BoolNode* boolNode ) = 0;

    /** Is used by the compiler when a new compare pattern was compiled
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addComparePattern( Interpreter& interpreter,
                                    ParserStack& parserStack ) = 0;

    //@}
};
}
#endif // COMPAREINTERFACE_HPP
