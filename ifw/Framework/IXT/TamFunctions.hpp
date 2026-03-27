#ifndef IXT_TAMFUNCTIONS_HPP
#define IXT_TAMFUNCTIONS_HPP
//
// @(#)%Portal Version: TamFunctions.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:45:03 %
//
//==============================================================================
//
//   Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//   
//   This material is the confidential property of Oracle Corporation or its
//   licensors and may be used, reproduced, stored or transmitted only in
//   accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the iScript Transaction functions.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Mike Ammon
//------------------------------------------------------------------------------
//
// Revision 1.2  2005/03/21 10:54:37  mliu
// - CO 156818 Add function for rollbackReason and add required support in 
//               demanRollback.
//
// Revision 1.1  2003/07/15 ammon
// - CO 50429: Add Namespaces.
//
// Revision 1.0  2003/06/23 15:27:56  ammon
// - CO 46707: Add function for demandRollback and demandCancel.
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class FctDescr;
class ParserStack;
}
namespace IXT
{
class Integrate;

/**<b><tt>DemandRollback</tt></b> is used to force a rollback of the current
 *  transaction
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DemandRollback.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2003/06/23 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: ammon $</font></td>
 *  </tr>
 *  </table>
 */
class DemandRollback : public SCR::BoolNode
{
  public:
    /**@name DemandRollback constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~DemandRollback();

    //@}

    /**@name DemandRollback public functions */
    //@{

    /** Execute the function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a sendEvent() function
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    DemandRollback( Integrate* extension, SCR::StringNode* reason );

  private:
    // Hide default and copy constructor
    DemandRollback();
    DemandRollback( const DemandRollback& other );
    const DemandRollback& operator=( const DemandRollback& other );

    // instance members
    Integrate*                      extensionM;
    SCR::StringNode*		    rollbackReasonM;
};

/**<b><tt>DemandCancel</tt></b> is used to force a cancel of the current
 *  transaction
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DemandCancel.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2003/06/23 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: ammon $</font></td>
 *  </tr>
 *  </table>
 */
class DemandCancel : public SCR::BoolNode
{
  public:
    /**@name DemandCancel constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~DemandCancel();

    //@}

    /**@name DemandCancel public functions */
    //@{

    /** Execute the function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a sendEvent() function
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    DemandCancel( Integrate* extension );

  private:
    // Hide default and copy constructor
    DemandCancel();
    DemandCancel( const DemandCancel& other );
    const DemandCancel& operator=( const DemandCancel& other );

    // instance members
    Integrate*                      extensionM;
};

/**<b><tt>RollbackReason</tt></b> is used to get the rollback reason 
 *  of the current transaction
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TamFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.0 $</font></td>
 *  <td><font size=-1>$Date: 2005/03/17 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: mliu $</font></td>
 *  </tr>
 *  </table>
 */
class RollbackReason : public SCR::StringNode
{
  public:
    /**@name RollbackReason constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~RollbackReason();

    //@}

    /**@name RollbackReason public functions */
    //@{

    /** Execute the function
     *  @return The rollback reason string
     */
    virtual const BAS::String& result();

    /** Create a RollbackReason() function
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}
  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    RollbackReason( Integrate* extension );

  private:
    // Hide default and copy constructor
    RollbackReason();
    RollbackReason( const RollbackReason& other );
    const RollbackReason& operator=( const RollbackReason& other );

    // instance members
    Integrate*                      extensionM;
};

}

#endif // IXT_TAMFUNCTIONS_HPP
