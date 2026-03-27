//==============================================================================
//
//      
// Copyright (c) 1996, 2011, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of the class IXT::ERA::Extension. This class is the iScript
//   extension class for getting ERAs.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------

#ifndef IXTERAFUNCTIONS_HPP
#define IXTERAFUNCTIONS_HPP

#include "SCR/Node.hpp"

// Forward declaration
namespace SCR
{
  class Interpreter;
  class ParserStack;
  class FctDescr;
}

namespace IXT
{
  // Forward declaration
  class EraExt;


/**<b><tt>EraAccountModule</tt></b> 
 *
 */
class EraAccountModule : public SCR::BoolNode
{

  public:
    /**@name EraAccountModule constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EraAccountModule();

    //@}

    /**@name EraAccountModule public methods */
    //@{

    /** Execute the sample() function
     *  @return Long handle for the database connection
     */
    virtual bool result();

    /** Create a setDAT_AccountModule() function 
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

    EraAccountModule( EraExt* eraExtension, 
                                SCR::StringNode*    moduleName );

  private:
    // hide default and copy constructor
    EraAccountModule();
    EraAccountModule( const EraAccountModule& other );
    const EraAccountModule& operator=( const EraAccountModule& other );

    // instance members
    SCR::StringNode*   moduleNameM;
    EraExt* eraExtensionM;
};




/**<b><tt>EraExtSrvRating</tt></b> 
 *
 */
class EraExtSrvRating : public SCR::StringNode
{

  public:
    /**@name EraExtSrvRating constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EraExtSrvRating();

    //@}

    /**@name EraExtSrvRating public methods */
    //@{

    /** Execute the sample() function
     *  @return Long handle for the database connection
     */
    virtual const BAS::String& result();

    /** Create a setDAT_AccountModule() function 
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

    /** Constructor
     */
    EraExtSrvRating( EraExt* eraExtension, 
                     SCR::StringNode*    key,
                     SCR::StringNode*    svcCode, 
                     SCR::StringNode*    era, 
                     SCR::DateNode*      date );

  private:
    // hide default and copy constructor
    EraExtSrvRating();
    EraExtSrvRating( const EraExtSrvRating& other );
    const EraExtSrvRating& operator=( const EraExtSrvRating& other );

    // instance members
    SCR::StringNode*   keyM;
    SCR::StringNode*   svcCodeM;
    SCR::StringNode*   eraM;
    SCR::DateNode*     dateM;
    EraExt*  eraExtensionM;
    BAS::String        resultM;
};




/**<b><tt>EraExtSrvRating</tt></b> 
 *
 */
class EraExtActRating : public SCR::StringNode
{

  public:
    /**@name EraExtActRating constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EraExtActRating();

    //@}

    /**@name EraExtActRating public methods */
    //@{

    /** Execute the sample() function
     *  @return Long handle for the database connection
     */
    virtual const BAS::String& result();

    /** Create a setDAT_AccountModule() function 
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

    /** Constructor
     */
    EraExtActRating( EraExt* eraExtension, 
                                SCR::StringNode*    key,
                                SCR::StringNode*    svcCode, 
                                SCR::StringNode*    era, 
                                SCR::DateNode*      date );

  private:
    // hide default and copy constructor
    EraExtActRating();
    EraExtActRating( const EraExtActRating& other );
    const EraExtActRating& operator=( const EraExtActRating& other );

    // instance members
    SCR::StringNode*   keyM;
    SCR::StringNode*   svcCodeM;
    SCR::StringNode*   eraM;
    SCR::DateNode*     dateM;
    EraExt*  eraExtensionM;
    BAS::String        resultM;
};

/**<b><tt>EraExtDom</tt></b> 
 *
 */
class EraExtDom : public SCR::StringNode
{

  public:
    /**@name EraExtDom constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EraExtDom();

    //@}

    /**@name EraExtDom public methods */
    //@{

    /** Execute the sample() function
     *  @return Long handle for the database connection
     */
    virtual const BAS::String& result();

    /** Create a getAcctDom() function 
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

    /** Constructor
     */
    EraExtDom( EraExt* eraExtension, 
                                SCR::StringNode*    key,
                                SCR::StringNode*    svcCode, 
                                SCR::DateNode*      date );

  private:
    // hide default and copy constructor
    EraExtDom();
    EraExtDom( const EraExtDom& other );
    const EraExtDom& operator=( const EraExtDom& other );

    // instance members
    SCR::StringNode*   keyM;
    SCR::StringNode*   svcCodeM;
    SCR::DateNode*     dateM;
    EraExt*  eraExtensionM;
    BAS::String        resultM;
};
}//namespace IXT

#endif // IXTERAFUNCTIONS_HPP
