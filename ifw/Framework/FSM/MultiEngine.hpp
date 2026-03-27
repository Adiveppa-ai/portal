#ifndef FSM_MULTIENGINE_HPP
#define FSM_MULTIENGINE_HPP

//==============================================================================
//
// Copyright (c) 1998, 2018, Oracle and/or its affiliates. All rights reserved.
//      This material is the confidential property of Oracle Corporation or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FSM
//------------------------------------------------------------------------------
// Module Description:
//   MultiEngine class.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// $Log: MultiEngine.hpp,v $
// Revision 1.7  2008/11/20  bmclella
// 7475605 Improved performance and reduce memory usage
//
// Revision 1.6  2001/06/22 14:45:03  mwriedt
// Changed copyright, fixed bug in lexer.
//
//==============================================================================

#ifndef FSM_MULTIENGINEIF_HPP
  #include "FSM/MultiEngineIf.hpp"
#endif

namespace FSM
{

/** <tt>MultiEngine</tt> is a finite state machine for recognizing multi word expressions.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: MultiEngine.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_mainbrm.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2018/06/29 04:08:57 $</font></td>
    <td><font size=-1>$Author: gmnaik $</font></td>
    </tr>
    </table>

    <p>It consists of several engines linked together and used for matching several patterns. */

struct FCT_BitVecHash
{
  unsigned int operator()(const RWBitVec& x) const { return x.hash(); };
};

typedef RWTValHashMap<RWBitVec,Engine*,FCT_BitVecHash, equal_to<RWBitVec> > Engine_HashMap;
 
class MultiEngine : public MultiEngineIf 
{
public:

  typedef RWTPtrOrderedVector<Engine>  EngineVector;
  
  /* Enumeration of serialize data record type */
  enum recType {HEADER, STATE, ENGINE};

  /** Constructor.
   *  @param numWords Number of words to recognize (>0). */
  MultiEngine(size_t numWords);

 /** Constructor.
   *  @param numWords Number of words to recognize (>0). 
   *  @param fsmDataFileName serialized data file name. */
  MultiEngine(size_t numWords, const BAS::String& fsmDataFileName);

  /** Destructor. */
  ~MultiEngine();

  /** Calls all of the FSM classes functions to free all of their
   *  memory pools.  Should only be done before a program terminates.
   *  */
  static void freeAllMemoryPools();

  /** Does the final setup after all expressions have been added.
   *  @return <tt>True</tt> on success, <tt>false</tt> otherwise. */
  bool finalSetup();

  /** Processes the input data and returns a vector of valid path numbers.
   *  @param input The vector containing the patterns to process.
   *  @return Reference to the vector with path numbers. */
  const PathNumVec& process(const MultiEngineVector& input) const;

  /** Processes the input data and returns the end state.
   *  @param input The vector containing the words to process.
   *  @param startFSM If not NULL, the finite state machine to start with.
   *  @return Last found state or NULL, if not found.
   *          The found state must not be a valid endstate. */
  State* process(const MultiEngineVector& input,
                     Engine*                  startFSM);

  /** Clears the entire machine. */
  void clear();
                     
  /** Resets the entire machine.
   *  The state is then equivalent to the state directly after construction.
   *  @param numWords Number of words in pattern to recognize (>0). */
  void reset(size_t numWords);

  /** Resets the entire machine. Also resets the base class.
   *  The state is then equivalent to the state directly after construction.
   *  @param numWords Number of words in pattern to recognize (>0). */
  void resetAll(size_t numWords);

  /** Prints all FSM_Engines.
   *  @param os The output stream. */ 
  void printFSM(std::ostream& os);

private:

  /** Search for existing finite state machine 
   */
  Engine* getFSM(size_t          startField,
                     const RWBitVec& validPatterns);

  /** Insert a new finite state machine 
   */
  void insertFSM(size_t          startField,
                 const RWBitVec& validPatterns,
                 Engine*     engine);

  /** Recursive build up all finite state machines
   */
  Engine* buildFSM(size_t   startField,
                       const RWBitVec& validPatterns,
                       bool&    errorInd );
                       
  /**  Collects detStatesM, assigns unique id for each detState  
   */
  void collectDetStates ();

  /**  Serializes a header record  
   */
  bool serializeHeader(std::ostream& os) const;

  /**  Serializes state record  
   */
  bool serializeState(std::ostream& os) const;

  /**  Serializes FSM engine record  
   */
  bool serializeEngine(std::ostream& os) const;

  /**  Restores header record  
   */
  bool restoreHeader(std::istream& in);

  /**  Restores state record  
  */
  bool restoreState(std::istream& in);

  /**  Restores FSM engine record  
  */
  bool restoreEngine(std::istream& in);
  
  /** Converts Bit Vector to Path Vector
   */    
  void convertBitVecToPathVec();  

  // disallow use of copy constructor
  MultiEngine(const MultiEngine& original);
  const MultiEngine& operator =(const MultiEngine& rVal);

  // member variables
  RWTPtrVector<Engine_HashMap>    fsmHashMapsM;

  // static class members
  static const PathNumVec          emptyPathNumVecCM;

  // container to hold all fsm engines
  MultiEngine::EngineVector                    fsmsM;
};

}
#endif
