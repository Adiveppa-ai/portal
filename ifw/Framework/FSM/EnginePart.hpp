#ifndef FSM_ENGINEPART
#define FSM_ENGINEPART

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
//      This material is the confidential property of Oracle Corporation or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FSM
//
//------------------------------------------------------------------------------
// Module Description:
//   EnginePart class.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Michael Wriedt
//
// $RCSfile: EnginePart.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:53:39 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: EnginePart.hpp,v $
// Revision 1.12  2008/11/20  bmclella
// 7475605 Improved performance and reduce memory usage
//
// Revision 1.11  2001/06/22 14:45:03  mwriedt
// Changed copyright, fixed bug in lexer.
//
//==============================================================================


#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif

#ifndef FSM_STATE_HPP
  #include "FSM/State.hpp"
#endif

namespace FSM {
class EnginePart;
typedef RWTPtrOrderedVector<EnginePart> EnginePartStack;

// This is for the EnginePart memory pool.
typedef struct eng_part_entry {
  struct eng_part_entry*  nextp;  // linked-list next pointer.
  // The next thing is the real EnginePart object but since that
  // hasn't been defined yet, I will just make it a pointer to
  // an EnginePart.  This doesn't really matter since "obj" isn't
  // really used.
  EnginePart*             obj;
} eng_part_entry_t;

#define FSM_ENG_PART_POOL_ENTRIES_PER_MALLOC  64

/** <tt><b>EnginePart</b></tt> is an engine for a part of a regular expression.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: EnginePart.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:53:39 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>

    <p>It is used for the scanning of a regular expression. */
class EnginePart D_THREADINFO
{
public:

  /** Default Constructor.
      @param exception Defines if characters added do not match. */
  EnginePart(const bool exception = false);

  /** Constructor with character string
      @param string  */
  EnginePart(const char* str);

  /** Constructor with character range
      @param lower Lower character of the range (or the only one if upper is missing).
      @param upper Upper character of the range (optional). */
  EnginePart(const unsigned char lower, const unsigned char upper = 0);

  /** Constructor with integer flag to indicate a wildcard
      @param wildFlag Not used. Just a way to create/use a different constuctor. */
  EnginePart(int wildFlag);

  /** Copy constructor.
      @param engine Engine part to copy from. */  
  EnginePart(const EnginePart& engine);

  /** Destructor. */
  ~EnginePart();

  /** Returns if engine part is negative.
      @return Negative flag. */
  bool isNegative() const;

  /** Returns start state.
      This is the first state of the engine part.
      @return Pointer to start state. */
  State* startState() const;

  /** Returns end state.
      This is the last state of the engine.
      @return Pointer to end state. */
  State* endState() const;

  /** Declares self as negative.
      For '!' pattern. */
  void makeNegative();
  
  /** Adds character range l (to u).
      For '[l-u]' pattern.
      @param lower Lower character of the range (or the only one if upper is missing).
      @param upper Upper character of the range (optional). */
  void addCharacters(const unsigned char lower, unsigned char upper = 0);

  /** Expands self to match zero or one time.
      For '?' pattern. */
  void makeZeroOrOne();
  
  /** Expands self to match one or more times.
      For '+' pattern. */
  void makeOneOrMore();

  /** Expands self to match zero or more times.
      For '*' pattern. */
  void makeZeroOrMore();

  /** Expands self to match x (to y) times.
      For '{x,y}' pattern. */
  void multiply(const unsigned int lower, unsigned int upper = 0);

  /** Concatenates self with another engine part.
      @param engine Pointer to second engine part.
      @return Self. */
  EnginePart& concatenate(EnginePart* engine);

  /** Expands self to match self or another engine part.
      @param engine Pointer to second engine part.
      @return Self. */
  EnginePart& alternative(EnginePart* engine);

  /** Returns engine part stack.
      Used for scanning.
      @return Stack. */
  static EnginePartStack& stack();

  /** frees the EnginePart memory pool
      @return void. */
  static void freeMemoryPool();

  /** Returns last engine in stack.
      @return Pointer to engine part. */
  static EnginePart* enginePart();
  
  /** Returns error appeared during scanning.
      @return Error text. */
  static const BAS::String& errorText();

  /** Sets error text.
      Used for scanning.
      @param errorText Scanning error. */
  static void errorText(const BAS::String& errorText);

  /** Output operator. */
  friend std::ostream& operator <<(std::ostream& os, const EnginePart& e);

  /** Our private new function.
      Used for improved performance. */
  void* operator new(size_t);

  /** Our private delete function.
      Used for improved performance. */
  void operator delete(void*);


private:

  static EnginePartStack stackCM;
  static EnginePartStack stackTBDCM;  // TBD -> To Be Deleted objects

  // Start of memory pool linked-list
  static eng_part_entry_t*        engPartPoolCM;

  // Ptrs to arrays of eng_part_entry_t
  // (FAKED: Using EnginePart instead of eng_part_entry_t)
  static RWTPtrSlist<EnginePart>  engPartArrayAddrsCM;

  // NOTE: Most of the non-deterministic FSMs (FSM::NonDetState)
  //   are part of the EnginePart class.  So these will be
  //   deleted when the EnginePart objects are deleted.
  //   However, we do have some that are created with "new".
  //   These objects are stored in the TBD (To Be Deleted)
  //   variable below.
  StateSet*                   statesTBDpM;
  static BAS::String          errorTextCM;

  State* copy(RWTPtrMap<State, State, less<State> >& states, const State* state);
  bool checkEndState();
  void makeEnds();

  bool negativeM;
  bool exceptionM;
  
  State* startStateM;
  State* endStateM;
};
ostream& operator <<(ostream& os, const EnginePart& e);


// inlines

inline bool
EnginePart::isNegative() const
{
  D_ENTER( "FSM::EnginePart::isNegative() const" );

  return negativeM;
}


inline State*
EnginePart::startState() const
{
  D_ENTER( "FSM::EnginePart::startState() const" );

  return startStateM;
}


inline State*
EnginePart::endState() const
{
  D_ENTER( "FSM::EnginePart::endState() const" );

  return endStateM;
}


inline void
EnginePart::makeNegative()
{
  D_ENTER( "FSM::EnginePart::makeNegative()" );

  negativeM = true;
}


inline EnginePartStack&
EnginePart::stack()
{
  D_ENTER( "FSM::EnginePart::stack()" );

  return stackCM;
}

inline const BAS::String&
EnginePart::errorText()
{
  D_ENTER( "FSM::EnginePart::errorText()" );

  return errorTextCM;
}

inline void
EnginePart::errorText(const BAS::String& errorText)
{
  D_ENTER( "FSM::EnginePart::errorText(const BAS::String&)" );

  errorTextCM = errorText;
}
}
#endif
