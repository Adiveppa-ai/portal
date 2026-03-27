#ifndef FSM_STATE_HPP
#define FSM_STATE_HPP

//==============================================================================
//
// Copyright (c) 1995, 2023, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FSM
//------------------------------------------------------------------------------
// Module Description:
//   State classes.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// $Log: State.hpp,v $
// Revision 1.7  2008/11/20  bmclella
// 7475605 Improved performance and reduce memory usage
//
// Revision 1.6  2001/06/22 14:45:03  mwriedt
// Changed copyright, fixed bug in lexer.
//
//==============================================================================

#ifndef RW_TOOLS_BITVEC_H
  #include <rw/bitvec.h>
#endif
#ifndef RW_TOOLS_TVSRTVEC_H
  #include <rw/tvsrtvec.h>
#endif
#ifndef RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef RW_TOOLS_TPSET_H
  #include <rw/tpset.h>
#endif
#ifndef RW_TOOLS_TVVECTOR_H
  #include <rw/tvvector.h>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace FSM
{
class Engine;

// This vector is used to save the valid calltypes for a state in the finite
// state machine 
typedef RWTValOrderedVector<int> PathNumVec;
typedef RWTValOrderedVector<u_int64> StateIdSet;

class State;
class NonDetState;
class DetState;
class StateSet;

  // This is used to have a linked-list of RWBitVec objects that
  // can use re-used. This is treated like a stack.
typedef struct rwbitvec_entry {
	RWBitVec*               bitvecp;  // Bit vector*
	struct rwbitvec_entry*  nextp;    // linked-list next pointer.
	struct rwbitvec_entry*  backp;    // linked-list back pointer.
} rwbitvec_entry_t;

typedef RWTPtrOrderedVector<State>         StateVector;

#define FSM_MAX_STATES_PER_CHAR   256
  // We use the following to represent the '.' wildcard character
#define FSM_WILDCARD_CHAR         256

// successor states
typedef struct succ_entry {
	State*                  succp;  // Successor State* for ch
	struct succ_entry*      nextp;  // linked-list next pointer.
	unsigned char           ch;
	unsigned char           notUsedFlag;  // Indicates if this entry is not used.
} succ_entry_t;

  // This is used to have a linked-list of StateVector objects that
  // can use re-used. This is treated like a stack.
typedef struct statevec_entry {
	StateVector*            statevecp; // StateVector*
	struct statevec_entry*  nextp;     // linked-list next pointer.
	struct statevec_entry*  backp;     // linked-list back pointer.
} statevec_entry_t;

  // This is used to have a linked-list of StateSet objects that
  // can use re-used.
typedef struct stateset_entry {
	struct stateset_entry*  nextp;     // linked-list next pointer.
  // The next thing is the real StateSet object but since that
  // hasn't been defined yet, I will just make it a pointer to
  // a StateSet.  This doesn't really matter since "obj" isn't
  // really used.
  StateSet*               obj; // StateSet*
} stateset_entry_t;

// This is for the NonDetState memory pool.
typedef struct non_det_state_entry {
  struct non_det_state_entry*  nextp;  // linked-list next pointer.
  // The next thing is the real NonDetState object but since that
  // hasn't been defined yet, I will just make it a pointer to
  // a NonDetState.  This doesn't really matter since "obj" isn't
  // really used.
  NonDetState*             obj;
} non_det_state_entry_t;

// This is for the DetState memory pool.
typedef struct det_state_entry {
  struct det_state_entry*  nextp;  // linked-list next pointer.
  // The next thing is the real DetState object but since that
  // hasn't been defined yet, I will just make it a pointer to
  // a DetState.  This doesn't really matter since "obj" isn't
  // really used.
  DetState*             obj;
} det_state_entry_t;

void doBitToPathVectorConversion (RWBitVec * pbitVec, 
                                  PathNumVec * pathNumbers,
                                  bool preAllocatedFlag=false);
                                  
void insertPathVectorEntry(bool preAllocatedFlag, 
                           size_t offset,
                           int ** pcpPathVector,
                           PathNumVec * pPathNumVector
                           );


/** <tt><b>State</b></tt> implements a single state for a finite state machine.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: State.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:53:59 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>

    <p>It contains 256 (for all possible characters) pointers to the following states. */
class State D_THREADINFO
{
public:

  /** Default constructor. */
  State(int64 objId = -1);

  /** Destructor. */
  virtual ~State();

  /** Returns the successor state for a character.
   *	@param ch Character for which to return the successor state.
   *	@return Pointer to successor state if found, <b>NULL</b> otherwise. */
  State* succState(unsigned char ch) const;

  /** Returns the successor state for a WILDCARD character. */
  State* getSuccStateWild() const;

  /** Sets the successor state for a character.
   *  @param ch Character for which to set the successor state.
   *  @param state Pointer to successor state. */
  void succState(unsigned char ch, State* state);

  /** Sets the successor state for a WILDCARD character.
   *  @param state Pointer to successor state. */
  void succStateWild(State* state);

  /** Indicates if the vector with the path numbers exists.
   *  @return true if is exists, else it returns false. */
  bool pathNumbersExist() const;

  /** Returns the path numbers. 
   *  @return Reference to a vector with path numbers. */
  const PathNumVec& pathNumbers() const;

  /** Returns the path numbers in the BitVector. 
   *  @param numberOfPath Number of Paths to set the correct size for the 
             BitVector of Paths. *
   *  @param doNotCreate Flag to indicate that a new RWBitVec should not be created
              created if it doesn't already exist. *
   *  @return Pointer to bitvector containing all path numbers. */
  const RWBitVec* pathNumbers(size_t numberOfPath, int doNotCreate = 0);

  /** Adds a path number to this state.
   *  @param number Path number. */
  void addPathNumber(int number);

  /** Adds a path number (in the BitVec) to this state.
   *  @param pathNumbers Path numbers. */
  void addPathNumber(const RWBitVec &pathNumbers);

  /** Does a logical AND of this State's path numbers to
   *  to the passed RWBitVec.
   *  @param RWBitVec Path numbers. */
  void andPathNumberTo(RWBitVec &resultPathNumbers);

  /** Adds/Removes a path number (in the BitVec) to this state.
   *  @param RWBitVec Path numbers. */
  void xorPathNumber(const RWBitVec &pathNumbers);

  /** Sets the total path numbers to set the size of the BitVector.
   *  @param Number total path numbers required. */
  void numberOfPaths(size_t numberOfPath);

  /** Removes a path number from this state.
   *  @param number Path number to remove. */
  void removePathNumber(int number);

  /** Gets the path numbers.
   *  @param set Reference to set to fill with path numbers. */
  void pathNumbers(RWBitVec& set);

  /** Return a string with all path numbers.
      @return String. */
  BAS::String pathString() const;

  /** Equal operator.
      Comparison is based on the address.
      @param other State to compare with.
      @return <tt>True</tt> if states are equal. */
  bool operator ==(const State& other) const;

  /** Less operator.
      Comparison is based on the address.
      @param other State to compare with.
      @return <tt>True</tt> if state is less than other. */
  bool operator <(const State& other) const;

  /** Output operator. */
  friend std::ostream& operator <<(std::ostream& os, const State& e);

  /** Returns the epsilon successor states.
      @return Pointer to vector of states. */
  virtual const StateVector* epsilonSuccStates() const;

  /** Adds an epsilon successor state.
      @param state Pointer to state to add. */
  virtual void epsilonSuccState(State* state);

  /** Adds a new epsilon successor state.
   *	@return Pointer to new created state. */
  virtual State* addEpsilonSuccState();

  /** Gets the epsilon closure states.
      @param states Reference to set to fill. */
  virtual void epsilonClosure(StateSet& states) const;

  /** Sets the finite state machine for the following word.
   *	@param engine Pointer to the successor finite state machine. */
  virtual void setNextWordFSM(Engine* engine);

  /** Returns the finite state machine for the following word.
   *	@return Pointer to the successor finite state machine if exists, <b>NULL</b> otherwise. */
  virtual Engine* getNextWordFSM() const;

  /** Prints state and successors.
      @param states Map with already printed states.
      @param os Output stream.
      @param level Hierarchy level. */
  virtual void print(
      RWTValMap<State*, unsigned int, less<State*> >& states,
      std::ostream& os, unsigned int level) const;

  /** Converts the path number vector from RWBitVec to RWTValSortedVec *
   *  @param pathNumbers Reference to a set of Path Numbers */
  void convertBitVecToPathVec(PathNumVec& pathNumbers) const;

  /** Converts the path number vector from RWBitVec to RWTValSortedVec.
   *  This will delete the RWBitVec from the State and allocate a 
   *  PathNumVec.*/
  void convertBitVecToPathVec();

  /** frees the RWBitVec memory pool
      @return void. */
  static void freeRWBitVecMemoryPool();

  /** Returns object Id */ 
  int64 getId();

protected:

  // Hidden functions and operators (not implemented)
  State(const State& original);
  const State& operator =(const State& rVal);

  /** Sets object Id */ 
  void setId(int64 objId);

  /** Pointer to the state's PathNumVec.  This is not used during
   *  setup and is set/valid after finalSetup has been called.
   */
  PathNumVec* pathNumberspM;

  /** Gets a Bit Vector to be used to contain the total number
   *  of paths required for the engine.
   *  @param numberOfPath total number of paths */
  RWBitVec* getAvailBitVec(size_t numberOfPath);

  /** Insert a Bit Vector in the available list
   *  @param numberOfPath total number of paths */
  void insertAvailBitVec(RWBitVec* bitVecp);

public:
  succ_entry_t*  succpM; // a linked-list in order of 'ch'

protected:
  // each state has at least one succ_entry_t, so to cut down
  // on the number of mallocs needed, we have one here as part
  // of the State object.
  succ_entry_t   aSuccEntry;
  RWBitVec*  pathNumbersBitVecM;
  State*  wildCardSuccpM; // Non-null for a wild-card.
  int64  objectIdM;

  // start of a linked-list (like a stack).
  static rwbitvec_entry_t*       bitVectListHeadpM;

  // last entry in the linked-list
  static rwbitvec_entry_t*       bitVectListTailpM;

  // current "used entry" in the linked-list
  static rwbitvec_entry_t*       bitVectListStackpM;

  // Ptrs to arrays of rwbitvec_entry_t
  // (FAKED USING State instead of rwbitvec_entry_t)
  static RWTPtrSlist<State>      bitVecArrayAddrsCM;

  // Nodes that will need to be added.
  static size_t                  bitVecNodesNeededM;

  // An empty PathNumVec
  static PathNumVec              emptyPathNumVecCM;

  //friends
  friend class MultiEngine;
  friend class EngineGroup;
};

std::ostream& operator <<(std::ostream& os, const State& e); //just a declaration within the namespace FSM

// inlines

// This function returns the Successor State for a WILDCARD.
inline State*
State::getSuccStateWild() const
{
  D_ENTER("FSM::State::getSuccStateWild() const");
  D_PRINT("this=" << this << ", wildCardSuccpM=" << wildCardSuccpM);
  return wildCardSuccpM;
}

// This function sets the passed Successor State for a WILDCARD.
inline void
State::succStateWild(State* state)
{
  D_ENTER("FSM::State::succStateWild(State*)");
  D_PRINT("this=" << this << ", state=" << state);
  wildCardSuccpM = state;
}

inline bool
State::pathNumbersExist() const
{
  D_ENTER( "FSM::State::pathNumbersExist() const" );
  if (pathNumberspM)
  {
    return true;
  }
  return false;
}

inline const RWBitVec*
State::pathNumbers(size_t numberOfPath, int doNotCreate)
{
  D_ENTER("FSM::State::pathNumbers(size_t)");
  D_PRINT("numberOfPath=" << numberOfPath <<
    ", doNotCreate=" << doNotCreate);

  if (!pathNumbersBitVecM)
  {
    if (!doNotCreate)
    {
      pathNumbersBitVecM = getAvailBitVec(numberOfPath);
    }
  }
  if (pathNumbersBitVecM)
  {
    D_PRINT("this=" << this << ", *pathNumbersBitVecM: " <<
      *pathNumbersBitVecM);

    if (pathNumbersBitVecM->length() != numberOfPath)
    {
      pathNumbersBitVecM->resize(numberOfPath);
    }
  }
  else
  {
    D_PRINT("this=" << this << ", pathNumbersBitVecM=NULL");
  }

  return pathNumbersBitVecM;
}

inline void
State::addPathNumber(int number)
{
  D_ENTER( "FSM::State::addPathNumber(int)" );

  if (!pathNumbersBitVecM)
  {
    // I can't create it here because I don't know the number of paths
    D_PRINT("ERROR: pathNumbersBitVecM=NULL");
    return;
  }
  pathNumbersBitVecM->setBit(number);
  D_PRINT("this=" << this << ", number=" << number <<
    ", *pathNumbersBitVecM(after): " << *pathNumbersBitVecM);
}

inline void
State::addPathNumber(const RWBitVec& pathNumber)
{
  D_ENTER( "FSM::State::addPathNumber(const RWBitVec&)" );

  if (pathNumbersBitVecM)
  {
    *pathNumbersBitVecM |= pathNumber;
    D_PRINT("this=" << this << ", pathNumber=" << pathNumber <<
      ", *pathNumbersBitVecM(after): " << *pathNumbersBitVecM);
  }
  else
  {
    D_PRINT("this=" << this << ", pathNumber=" << pathNumber <<
      ", pathNumbersBitVecM=NULL(possible ERROR)");
  }
}

inline void
State::andPathNumberTo(RWBitVec& resultPathNumbers)
{
  D_ENTER( "FSM::State::andPathNumberTo(RWBitVec&)" );

  if (!pathNumbersBitVecM)
  {
    pathNumbersBitVecM = getAvailBitVec(resultPathNumbers.length());
  }
  D_PRINT("*pathNumbersBitVecM: " << *pathNumbersBitVecM);
  D_PRINT("resultPathNumbers(before): " << resultPathNumbers);

  resultPathNumbers &= *pathNumbersBitVecM;

  D_PRINT("resultPathNumbers(after): " << resultPathNumbers);
}

inline void
State::xorPathNumber(const RWBitVec& pathNumber)
{
  D_ENTER( "FSM::State::xorPathNumber(const RWBitVec&)" );

  if (!pathNumbersBitVecM)
  {
    pathNumbersBitVecM = getAvailBitVec(pathNumber.length());
  }
  D_PRINT("*pathNumbersBitVecM(before): " << *pathNumbersBitVecM);
  D_PRINT("pathNumber: " << pathNumber);

  *pathNumbersBitVecM ^= pathNumber;

  D_PRINT("*pathNumbersBitVecM(after): " << *pathNumbersBitVecM);
}

inline void 
State::numberOfPaths(size_t numberOfPath)
{
  D_ENTER( "FSM::State::numberOfPaths(size_t)" );

  if (!pathNumbersBitVecM)
  {
    pathNumbersBitVecM = getAvailBitVec(numberOfPath);
  }
  else
  {
    pathNumbersBitVecM->resize(numberOfPath);
  }
}

inline void
State::removePathNumber(int number)
{
  D_ENTER( "FSM::State::removePathNumber(int)" );

  if (!pathNumbersBitVecM)
  {
    // I can't create it here because I don't know the number of paths
    D_PRINT("ERROR: pathNumbersBitVecM=NULL");
    return;
  }
  pathNumbersBitVecM->clearBit(number);

  D_PRINT("pathNumbersBitVecM(after): " << *pathNumbersBitVecM);
}


inline bool
State::operator ==(const State& other) const
{
  return this == &other;
}


inline bool
State::operator <(const State& other) const
{
  return this < &other;
}

inline void 
State::setId(int64 objId)
{
  objectIdM = objId;
}

inline int64 
State::getId()
{
  return objectIdM;
}

/** <tt><b>NonDetState</b></tt> implements a non deterministic state.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: State.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:53:59 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>

    <p>It is used to build the non deterministic FSM during scanning. */
class NonDetState: public State
{
public:

  /** Default constructor. */
  NonDetState(int64 objId = -1);

  /** Destructor. */
  virtual ~NonDetState();

  /** Returns the epsilon successor states.
      @return Pointer to vector of states. */
  const StateVector* epsilonSuccStates() const;

  /** Adds an epsilon successor state.
      @param state Pointer to state to add. */
  void epsilonSuccState(State* state);

  /** Adds a new epsilon successor state.
   *	@return Pointer to new created state. */
  State* addEpsilonSuccState();
  
  /** Gets the epsilon closure states.
      @param states Reference to set to fill. */
  void epsilonClosure(StateSet& states) const;

  /** Prints state and successors.
      @param states Map with already printed states.
      @param os Output stream.
      @param level Hierarchy level. */
  void print(
       RWTValMap<State*, unsigned int, less<State*> >& states,
       std::ostream& os, unsigned int level) const;

  /** frees the StateVector memory pool
      @return void. */
  static void freeStateVectorMemoryPool();

  /** Our private new function.
      Used for improved performance. */
  void* operator new(size_t);

  /** Our private delete function.
      Used for improved performance. */
  void operator delete(void*);

  /** frees the NonDetState memory pool
      @return void. */
  static void freeMemoryPool();

private:

  /**  Gets a StateVector
   *  */
  StateVector* getAvailStateVector();

  /**  Insert a StateVector in the available list
   *  */
  void insertAvailStateVector(StateVector* stateVectorp);

  StateVector* epsilonSuccpM;

  // start of a linked-list (like a stack).
  static statevec_entry_t*       stateVectorListHeadpM;

  // last entry in the linked-list
  static statevec_entry_t*       stateVectorListTailpM;

  // current "used entry" in the linked-list
  static statevec_entry_t*       stateVectorListStackpM;

  // Ptrs to arrays of statevec_entry_t
  // (FAKED: Using State instead of statevec_entry_t)
  static RWTPtrSlist<State>      stateVectorArrayAddrsCM;

  // Nodes that will need to be added.
  static size_t                  stateVectorNodesNeededM;

  // Start of memory pool linked-list
  static non_det_state_entry_t*  nonDetStatePoolCM;

  // Ptrs to arrays of NonDetState
  static RWTPtrSlist<NonDetState> nonDetStateArrayAddrsCM;
};



/** <tt><b>DetState</b></tt> implements a deterministic state.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: State.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:53:59 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>

    <p>It is used to build the deterministic FSM. */
class DetState: public State
{
public:

  /** Default constructor. */
  DetState(int64 objId = -1);

  /** Sets the finite state machine for the following word.
   * @param engine Pointer to the successor finite state machine. */
  void setNextWordFSM(Engine* engine);

  /** Returns the finite state machine for the following word.
   *  @return Pointer to the successor finite state machine if exists,
       <b>NULL</b> otherwise. */
  Engine* getNextWordFSM() const;

  /** Our private new function.
      Used for improved performance. */
  void* operator new(size_t);

  /** Our private delete function.
      Used for improved performance. */
  void operator delete(void*);

  /** frees the DetState memory pool
      @return void. */
  static void freeMemoryPool();


private:

  Engine* nextWordFSMM;

  // Start of memory pool linked-list
  static det_state_entry_t*     detStatePoolCM;

  // Ptrs to arrays of DetState
  static RWTPtrSlist<DetState>  detStateArrayAddrsCM;
};

class StateSetEntry
{
public:
  /** Default constructor. */
  StateSetEntry();

  /** Destructor. */
  virtual ~StateSetEntry();

  /** startPtr */
  StateSetEntry* getNextPtr();

  /** getState */
  State* getState();

//protected:
public:
  // linked-list next pointer.
  StateSetEntry*          nextpM;
  State*                  statepM;

};

class StateSet D_THREADINFO
{
public:
  /** Constructor with optional "no duplicate check" flag. */
  StateSet(int noDupCheckFlag = 0);

  /** Destructor. */
  virtual ~StateSet();

  /** Our private new function.
      Used for improved performance. */
  void* operator new(size_t);

  /** Our private delete function.
      Used for improved performance. */
  void operator delete(void*);

  /** frees the StateSet memory pool
      @return void. */
  static void freeMemoryPool();

  /** startPtr */
  StateSetEntry* getFirstPtr();

  /** getState */
  State* getState();

  /** insert
      Returns true if insert was successful.  Otherwise, it returns false.
   */
  bool insert(State*      statep);

  /** clear */
  void clear();

  /** clearAndDestroy */
  void clearAndDestroy();

  /** destroyEntries - similar to clearAndDestroy except the memory
      for the linked-list entries is not returned.
   */
  void destroyEntries();

  /** isEmpty */
  int isEmpty();

  /** Equal operator.
      Comparison is based on the address.
      @param other State to compare with.
      @return <tt>True</tt> if states are equal. */
  bool operator ==(const StateSet& other) const;

  /** Less operator.
      Comparison is based on the address.
      @param other State to compare with.
      @return <tt>True</tt> if state is less than other. */
  bool operator <(const StateSet& other) const;

  /** Output operator. */
  friend std::ostream& operator <<(std::ostream& os, const StateSet& e);

protected:
  /** frees the StateSetEntry memory pool
      @return void. */
  void freeStateSetEntryMemoryPool();

  // "used linked-list" - first pointer
  StateSetEntry*          firstpM;

  // "used linked-list" - last pointer
  StateSetEntry*          lastpM;

  // "unused linked-list" - first pointer.
  StateSetEntry*          firstAvailpM;

  // Set to 1 if no dup checks are to be done.
  int                     noDupCheckM;

  // Ptrs to arrays of StateSetEntry
  // (FAKED: Using State instead of StateSetEntry)
  // This contains the links for the States in this object.
  RWTPtrSlist<State>      stateSetEntryArrayAddrsM;

  // To avoid some malloc calls
  StateSetEntry           embeddedEntriesM[24];

private:
  // Start of memory pool linked-list
  static stateset_entry_t*        stateSetPoolCM;

  // Ptrs to arrays of stateset_entry_t
  // (FAKED: Using State instead of stateset_entry_t)
  // This contains the links for all of the StateSets.
  static RWTPtrSlist<State>  stateSetArrayAddrsCM;

};

std::ostream& operator <<(std::ostream& os, const StateSet& e); //just a declaration within the namespace FSM

inline StateSetEntry*
StateSetEntry::getNextPtr()
{
  return nextpM;
}

inline State*
StateSetEntry::getState()
{
  return statepM;
}

// StateSet inlines

inline StateSetEntry*
StateSet::getFirstPtr()
{
  return firstpM;
}

}
#endif
