#ifndef FSM_ENGINE_HPP
#define FSM_ENGINE_HPP

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
//      This material is the confidential property of Oracle Corporation or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FSM
//------------------------------------------------------------------------------
// Module Description:
//   Engine class.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// $Log: Engine.hpp,v $
// Revision 1.12  2008/11/20  bmclella
// 7475605 Improved performance and reduce memory usage
//
// Revision 1.11  2001/06/22 14:45:03  mwriedt
// Changed copyright, fixed bug in lexer.
//
//==============================================================================

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef RW_TOOLS_TPHMAP_H
  #include <rw/tphdict.h>
#endif

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_HASHSTRING_HPP
  #include "BAS/HashString.hpp"
#endif
#ifndef FSM_STATE_HPP
  #include "FSM/State.hpp"
#endif
#ifndef FSM_ENGINEPART
  #include "FSM/EnginePart.hpp"
#endif

namespace FSM 
{
//==============================================================================

/** <tt><b>Engine</b></tt> is a finite state machine.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Engine.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:53:32 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>

    <p>The machine is able to recognize patterns matching general
       regular expressions. */

  typedef RWTPtrHashMap<BAS::HashString, EnginePart, 
                        BAS::HashString::Hash, equal_to<BAS::HashString> > EnginePartMap;


class Engine D_THREADINFO
{
public:

  /** Default constructor. */
  Engine(u_int32 objId = (u_int32)(~0));  // Set to -1

  /** Destructor. */
  ~Engine();

  /** Inserts a new pattern in the finite state machine.
   *  @param pattern String defining the pattern to insert.
   *  @param pathNumber Path number for this pattern (optional).
   *  @return <tt>True</tt> on success, <tt>false</tt> otherwise. */
  bool insertPattern(const BAS::String& pattern, size_t pathNumber = (size_t)(~0));

  /** Executes final setup operations after all entries have been inserted.
   *  @return <tt>True</tt> on success, <tt>false</tt> otherwise. */
  bool finalSetup();

  /** Processes a string and returns the end state. 
   *  @param string Expression to check.
   *  @return Pointer to last found state. */
  State* process(const char* string) const;

  /** Returns the description of the last error.
   *  @return Reference to the error string. */
  const BAS::String& failure() const;

  /** Clears the finite state machine. */
  void clear();

  /** Resets the finite state machine.
   *  Has the same effects as clear(). */
  void reset();

  /*  Return the total number of paths set for the engine.
   *  @return total number of paths */
  size_t numberOfPaths() const; 

  /*  Sets the total number of paths required for the engine.
   *  @param numberOfPath total number of paths */
  void numberOfPaths(size_t numberOfPath); 

  /*  Return objectId.
   *  @return unique object id. */
  u_int32 getId() const; 

  /** Output operator. */
  friend std::ostream& operator <<(std::ostream& os, const Engine& e);


protected:

  typedef RWTValOrderedVector<int> PathNumVector;
  typedef RWTValMap<StateIdSet, State*, less<StateIdSet> > DetStateMap;
  typedef RWTPtrSlist<StateSet>  TBDStateSetList;

  /* Converts the non-deterministic FSM to a deterministic one.
   * @param stateSet The state set to start with.
   * @param convertedStates Collection of converted states.
   * @return The pointer to the new start state on success. */
  State* makeDeterministic(StateSet& stateSet,
           DetStateMap& convertedStates,
           TBDStateSetList& stateSetsTBD,
           StateIdSet& key);

  /*  Return number of states the FSM contains.
   *  @return Number of states the FSM contains. */
  size_t numStates() const; 

  /*  Return the specified state.
   *  @param i Index of state to return.
   *  @return The state with given index if it exists, <b>NULL</b> otherwise. */
  State* state(size_t i) const;

  /*  Return a string with all path numbers for the FSM.
   *  @return String containing all the Path Numbers. */
  BAS::String pathString() const;
  
 /* clean up non-deterministic FSM after finalSetup */
  void cleanup();

  // Hidden functions and operators (not implemented)
  Engine(const Engine& original);
  const Engine& operator = (const Engine& rVal);

  BAS::String        failureM;
  RWBitVec          *negativePathsM;

  // handle the states for the deterministic FSM
  State*      detStartStateM;
  StateVector detStatesM;
  // NOTE: Most of the non-deterministic FSMs (FSM::DetState)
  //   are part of the EnginePart class.  So these will be
  //   deleted when the EnginePart objects are deleted.
  //   However, we do have some that are created with "new".
  //   These objects are stored in the TBD (To Be Deleted)
  //   variable below.
  StateVector nonDetStatesTBDM;

  // handle the states for the non-deterministic FSM
  State*   nonDetStartStateM;
  EnginePartStack stackTBDM;

  size_t numberOfPathsM;
  bool isPathNumberPresetM;
  int  patternCntM;

private:
  u_int32 objectIdM;

  // friends
  friend class MultiEngine;
  friend class EngineGroup;
};

ostream& operator <<(ostream& os, const Engine& e);


// inlines

inline const BAS::String&
Engine::failure() const
{
  D_ENTER( "FSM::Engine::failure()" );

  return failureM;
}


inline State*
Engine::state(size_t i) const
{
  D_ENTER( "FSM::Engine::state(size_t)" );

  return detStatesM(i);
}

inline u_int32 
Engine::getId() const
{
  D_ENTER( "FSM::Engine::getId()" );

  return objectIdM;
}

inline size_t
Engine::numStates() const
{
  D_ENTER( "FSM::Engine::numStates()" );

  D_ARG(detStatesM.length());

  return detStatesM.length();
}


inline size_t
FSM::Engine::numberOfPaths() const
{
  D_ENTER( "FSM::Engine::numberOfPaths() const" );

  return numberOfPathsM;
}

inline void
FSM::Engine::numberOfPaths(size_t numberOfPath)
{
  D_ENTER( "FSM::Engine::numberOfPaths(size_t)" );

  numberOfPathsM = numberOfPath;
  isPathNumberPresetM = true;
}

inline void
Engine::reset()
{
  D_ENTER( "FSM::Engine::reset()" );

  clear();
}
}
#endif
