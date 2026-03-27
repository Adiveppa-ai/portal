/* @(#)%Portal Version: EdrOutputMap.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:48:59 % */
#ifndef LRP_EDROUTPUTMAP_HPP
#define LRP_EDROUTPUTMAP_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrOutputMap. This class is the iScript
//   function node for executing the edrOutputMap() function.
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
// $RCSfile: EdrOutputMap.hpp,v $
// $Revision: 1.3 $
// $Author: sd $
// $Date: 2001/06/25 15:13:20 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.3  2004/07/27 ammon
// PRSF00116930  Added edrOutputMapToBuffer
//
// Revision 1.2  2001/06/25 15:13:20  sd
// - Missing error message in case of output mapping failure added
//
// Revision 1.1  2001/04/24 14:13:14  sd
// - Long renamed to Integer
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   SCR_DATA_HPP
  #include "SCR/Data.hpp"
#endif
#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
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
}
namespace FRM
{
class OutputMapping;
}
namespace LRP
{
class IScriptOutExt;

/** <b><tt>EdrOutputMap</tt></b> is the function node for mapping
 *  the edr container fields to an output file record.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrOutputMap.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/25 15:13:20 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrOutputMap : public SCR::BoolNode
{
  public:

    /**@name EdrOutputMap constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrOutputMap();

    //@}


    /**@name EdrOutputMap public methods */
    //@{

    /** Execute the edrOutputMap() function
     *  @return The result of the function execution
     */
    virtual bool result();

    /** Factory for creation of the function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    /** Initialize the output mapping description
     *  @param mapping Pointer to the mapping description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool outputMapping( FRM::OutputMapping* mapping );

    //@}

  protected:

    /* Constructor
     * @param integRateExtension Pointer to the integRate iScript extension
     * @param outputExtension Pointer to the output iScript extension
     * @param currentNodeVector Additional indices for the different edr blocks
     * @param mappingDescr Name of the mapping description to use
     */
    EdrOutputMap( IXT::Integrate*                     integRateExtension,
                      IScriptOutExt*                 extension,
                      RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector );
    
  private:
    // Hide copy constructor and assignment operator
    EdrOutputMap( const EdrOutputMap& );
    const EdrOutputMap operator=( const EdrOutputMap& );

    // Instance members
    IXT::Integrate*                    integRateExtensionM;
    IScriptOutExt*                outputExtensionM;
    FRM::OutputMapping*                outputMappingM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};

/** <b><tt>EdrOutputMapToBuffer</tt></b> is the function node for mapping
 *  the edr container fields to an output file record.
 *
 */
class EdrOutputMapToBuffer : public SCR::BoolNode
{
  public:

    /**@name EdrOutputMapToBuffer constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrOutputMapToBuffer();

    //@}


    /**@name EdrOutputMapToBuffer public methods */
    //@{

    /** Execute the edrOutputMap() function
     *  @return The result of the function execution
     */
    virtual bool result();

    /** Factory for creation of the function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    /** Initialize the output mapping description
     *  @param mapping Pointer to the mapping description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool outputMapping( FRM::OutputMapping* mapping );

    //@}

  protected:

    /* Constructor
     * @param integRateExtension Pointer to the integRate iScript extension
     * @param outputExtension Pointer to the output iScript extension
     * @param currentNodeVector Additional indices for the different edr blocks
     * @param mappingDescr Name of the mapping description to use
     */
    EdrOutputMapToBuffer( IXT::Integrate*                  integRateExtension,
                      IScriptOutExt*                       extension,
                      SCR::StringDataNode*                 outputString,
                      RWTPtrOrderedVector<SCR::LongNode>&  currentNodeVector );

  private:
    // Hide copy constructor and assignment operator
    EdrOutputMapToBuffer( const EdrOutputMapToBuffer& );
    const EdrOutputMapToBuffer operator=( const EdrOutputMapToBuffer& );

    // Instance members
    IXT::Integrate*                       integRateExtensionM;
    IScriptOutExt*                        outputExtensionM;
    FRM::OutputMapping*                   outputMappingM;
    RWTPtrOrderedVector<SCR::LongNode>    currentNodeVectorM;
    EDR::CurrentVector                    currentVectorM;
    BAS::OnlyPointer<SCR::StringDataNode> outputStringNodeM;
    BAS::String                           stringBufferM;
};
}
#endif // EDROUTPUTMAP_HPP
