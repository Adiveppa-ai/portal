#ifndef IXT_INTERPRETER_HPP
#define IXT_INTERPRETER_HPP

//==============================================================================
//
//      @(#)%Portal Version: Interpreter.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:50:20 %
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   The integRate iScript interpreter Integrate. This class is derived 
//   from the standard iScript interpreter SCR::Interpreter and automatically
//   add the integRate iScript extension to the standard interpreter.
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
// $RCSfile: Interpreter.hpp,v $
// $Revision: 1.5 $
// $Author: sd $
// $Date: 2001/04/12 12:22:52 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Interpreter.hpp,v $
// Revision 1.6  2003/05/05 12:31:14  ammon
// - Change getDuplicateEdrs() to getInternalEdrs() so deletes can be handled
// correctly
//
// Revision 1.5  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.1  2000/12/04 08:21:07  sd
// - Module moved from IXT to iScript.
//
// Revision 1.3  2000/09/27 14:15:58  sd
// - Function name() added.
//
// Revision 1.2  2000/09/27 14:09:06  sd
// - New function extension() added.
//
// Revision 1.1  2000/09/27 13:22:40  sd
// - Initial revision
//
//==============================================================================

#ifndef   SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif
#ifndef   IXT_LOG_HPP
  #include "IXT/Log.hpp"
#endif
#ifndef   IXT_INTEGRATE_HPP
  #include "IXT/Integrate.hpp"
#endif

namespace IXT
{
/** <b><tt>Interpreter</tt></b> is the iScript interpreter used in integRate
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Interpreter.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/12 12:22:52 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class Interpreter : public SCR::Interpreter
{
  public:
    /**@name Interpreter constructors and destructor */
    //@{

    /** Constructor
     *  @param name Registry name of the integrate iScript extension
     */
    Interpreter( const BAS::String& name );

    /** Destructor
     */
    ~Interpreter();

    //@}


    /**@name Interpreter public methods */
    //@{

    /** Check if the interpreter's extension is registered
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool isRegistered() const;

    /** Do the first initialization of edr container before executing a script
     *  @param edr The edr container to use
     */
    void initEdrContainer( EDR::Container* edr );

    /** Get the internal edr containers
     *  @param edrVector Vector for returning the result
     */
    void getInternalEdrs( RWTPtrOrderedVector<EDR::Container>& edrVector ) 
      const;

    /** Set the origin name used for events
     *  @param originName The origin name for all events send by the interpreter
     */
    void eventOriginName( const BAS::String& originName );

    /** Set the current message
     *  @param msg The current message to use
     */
    void currentMsg( const BAS::Message* msg );

    /** Get the extension
     *  @return Pointer to the extension
     */
    Integrate* extension() const;

    /** Get the registry name of the extension
     *  @return reference to registry name
     */
    const BAS::String& name() const;

    //@}

  private:
    Log        logM;
    Integrate* extensionM;
};

//==============================================================================
// Init the edr container before executing a script
//==============================================================================
inline void
Interpreter::initEdrContainer( EDR::Container* edr )
{
  RWPRECONDITION( extensionM != 0 );
  extensionM->initEdrContainer( edr );
}

//==============================================================================
// Get the internal edrs
//==============================================================================
inline void 
Interpreter::getInternalEdrs(
  RWTPtrOrderedVector<EDR::Container>& edrVector ) const
{
  RWPRECONDITION( extensionM != 0 );
  extensionM->getInternalEdrs( edrVector );
}

//==============================================================================
// Set the origin name used by send event
//==============================================================================
inline void 
Interpreter::eventOriginName( const BAS::String& originName )
{
  RWPRECONDITION( extensionM != 0 );
  extensionM->eventOriginName( originName );
}

//==============================================================================
// Set the current message
//==============================================================================
inline void
Interpreter::currentMsg( const BAS::Message* msg )
{
  RWPRECONDITION( extensionM != 0 );
  extensionM->currentMsg( msg );
}

//==============================================================================
// Get the extension
//==============================================================================
inline Integrate*
Interpreter::extension() const
{
  RWPRECONDITION( extensionM != 0 );
  return extensionM;
}

//==============================================================================
// Get the registry name of the extension
//==============================================================================
inline const BAS::String&
Interpreter::name() const
{
  RWPRECONDITION( extensionM != 0 );
  return extensionM->name();
}
}
#endif // INTERPRETER_HPP
