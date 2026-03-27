#ifndef IXT_EDRINPUTSTATE_HPP
#define IXT_EDRINPUTSTATE_HPP
/* @(#)%Portal Version: EdrInputState.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:44:58 % */

//==============================================================================
//
// Copyright (c) 1996 - 2008 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of EdrMissingInput, EdrEmptyInput and
//   EdrInputState classes.
//------------------------------------------------------------------------------
//
// Revision       10052  10-Sep-2004   6.7_FP2   ammon
// PRSF00124011   Add edrInternalState().
//
// Revision       10051  14-Aug-2003   6.5_FP3   ammon
// PRSF00045175   Propagate to 6.5_FP3.  Add namespaces.
//
// Revision       10050  30-Jun-2003   6.5_SP1_EBF   keshav
// PRSF00045126   Differentiate between MISSING and EMPTY fields
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{
class Integrate;

//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/
// Class EdrMissingInput
//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/

/**<b><tt>EdrMissingInput</tt></b> is the function class for setting
 * the input state of fields from the edr container to MISSING.
 */
class EdrMissingInput : public SCR::BoolNode
{
  public:
    /**@name EdrMissingInput constructors and destructor */
    //@{

    /** Destructor */
    virtual ~EdrMissingInput();

    //@}

    /**@name EdrMissingInput public methods */
    //@{

    /** Check if edr field is valid */
    bool isValid() const;

    /** Set the input state of an edr field to MISSING
     *  @return true on success, false otherwise
     */
    virtual bool result();

    /** Factory for setting the input state of an edr field to MISSING
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory(SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr);

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrMissingInput(Integrate* extension);

    /** Initialize the function node
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init(const BAS::String&                  fieldName,
              RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector);

  private:
    // Hide default and copy constructor
    EdrMissingInput();
    EdrMissingInput(const EdrMissingInput& other);
    const EdrMissingInput& operator=(const EdrMissingInput& other);

    // instance members
    Integrate*                         extensionM;
    EDR::Index                         fieldIdxM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};

//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/
// Class EdrEmptyInput
//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/

/**<b><tt>EdrEmptyInput</tt></b> is the function class for setting
 * the input state of fields from the edr container to EMPTY.
 */
class EdrEmptyInput : public SCR::BoolNode
{
  public:
    /**@name EdrEmptyInput constructors and destructor */
    //@{

    /** Destructor */
    virtual ~EdrEmptyInput();

    //@}

    /**@name EdrEmptyInput public methods */
    //@{

    /** Check if edr field is valid */
    bool isValid() const;

    /** Set the input state of an edr field to EMPTY
     *  @return true on success, false otherwise
     */
    virtual bool result();

    /** Factory for setting the input state of an edr field to EMPTY
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory(SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr);

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrEmptyInput(Integrate* extension);

    /** Initialize the function node
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init(const BAS::String&                  fieldName,
              RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector);

  private:
    // Hide default and copy constructor
    EdrEmptyInput();
    EdrEmptyInput(const EdrEmptyInput& other);
    const EdrEmptyInput& operator=(const EdrEmptyInput& other);

    // instance members
    Integrate*                         extensionM;
    EDR::Index                         fieldIdxM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};

//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/
// Class EdrInputState
//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/

/**<b><tt>EdrInputState</tt></b> is the function class for getting
 * the input state of fields from the edr container.
 */
class EdrInputState : public SCR::LongNode
{
  public:
    /**@name EdrInputState constructors and destructor */
    //@{

    /** Destructor */
    virtual ~EdrInputState();

    //@}

    /**@name EdrInputState public methods */
    //@{

    /** Check if edr field is valid */
    bool isValid() const;

    /** Get the input state of an edr field
     *  @return <b>EMPTY</b> if the input state is EMPTY,
     *          <b>MISSING</b> if it is MISSING,
     *          <b>OTHER</b> if it is anything else.
     */
    virtual int64 result();

    /** Factory for getting the input state of an edr field
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory(SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr);

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrInputState(Integrate* extension);

    /** Initialize the function node
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init(const BAS::String&                  fieldName,
              RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector);

  private:
    // Hide default and copy constructor
    EdrInputState();
    EdrInputState(const EdrInputState& other);
    const EdrInputState& operator=(const EdrInputState& other);

    // instance members
    Integrate*                         extensionM;
    EDR::Index                         fieldIdxM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};

//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/
// Class EdrInternalState
//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/

/**<b><tt>EdrInternalState</tt></b> is the function class for getting
 * the internal state of fields from the edr container.
 */
class EdrInternalState : public SCR::LongNode
{
  public:
    /**@name EdrInternalState constructors and destructor */
    //@{

    /** Destructor */
    virtual ~EdrInternalState();

    //@}

    /**@name EdrInternalState public methods */
    //@{

    /** Check if edr field is valid */
    bool isValid() const;

    /** Get the internal state of an edr field
     *  @return <b>EMPTY</b> if the internal state is EMPTY,
     *          <b>MISSING</b> if it is MISSING,
     *          <b>OTHER</b> if it is anything else.
     */
    virtual int64 result();

    /** Factory for getting the internal state of an edr field
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory(SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr);

    static SCR::Node* otherFactory(SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr);

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrInternalState(Integrate* extension,
                         SCR::StringNode* edrFieldNameNode = NULL, 
                         SCR::ArrayNode* indicesArrayNode = NULL,
                         SCR::LongNode* noOfIndicesNode = NULL);

    bool flagM;
    SCR::StringNode* edrFieldNameNodeM;
    SCR::ArrayNode* indicesArrayNodeM;
    SCR::LongNode* noOfIndicesNodeM;

    /** Initialize the function node
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init(const BAS::String&                  fieldName,
              RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector);
    bool init();

  private:
    // Hide default and copy constructor
    EdrInternalState();
    EdrInternalState(const EdrInternalState& other);
    const EdrInternalState& operator=(const EdrInternalState& other);

    // instance members
    Integrate*                         extensionM;
    EDR::Index                         fieldIdxM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};
}

#endif // IXT_EDRINPUTSTATE_HPP
