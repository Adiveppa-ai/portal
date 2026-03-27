#ifndef BAS_REGISTRYENTRY_HPP
#define BAS_REGISTRYENTRY_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   RegistryEntry class implementation.
//
//   This class can be used to create a tree-structured registry.
//   The tree can be read from a stream, from which it is parsed.
//   A Yacc-parser is used for this purpose.           
//
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//------------------------------------------------------------------------------
// $Log: BAS_RegistryEntry.hpp,v $
// Revision 1.31  2000/02/11 10:07:02  aro
// Syntax erorrs fixed.
//
// Revision 1.30  2000/02/11 09:48:06  aro
// Mutex lock for the protection of the parser added.
//
// Revision 1.29  1999/11/10 09:04:33  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.28  1999/09/03 14:41:58  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
//
// Revision 1.27  1999/08/24 14:36:07  aro
// BAS_RegisteredObject::unMakeRootNode() added.
//
// Revision 1.26  1999/05/12 08:05:20  aro
// Assigemnt operators fixed.
//
// Revision 1.25  1999/04/20 11:39:44  arockel
// BAS_RegistryEntry::find extendend to serach for root names.
//
// Revision 1.20  1999/03/26 15:09:29  arockel
// Registry syntax extended to support verbose output.
//
// Revision 1.17  1999/03/25 11:54:10  arockel
// BAS_RegistryEntry: verbose output added; registry made modifyable for BAS_RegisteredObject.
//
// Revision 1.15  1999/03/24 14:54:18  arockel
// Registry update methods added to BAS_RegisteredObject.
//
// Revision 1.11  1999/03/23 16:01:28  arockel
// Error logging implemented.
//
// Revision 1.9  1999/03/23 12:27:40  arockel
// BAS_RegistryEntry::isRootNode(bool) removed; online doc improved.
//
// Revision 1.8  1999/03/23 10:16:30  arockel
// BAS_RegisteredObject::registy() fixed to work for complete names.
//
// Revision 1.6  1999/03/18 14:12:49  arockel
// Registry parser fixed to accept pathes.
//
// Revision 1.3  1999/03/17 09:46:24  arockel
// Inline doc updated.
//
// Revision 1.2  1999/03/16 09:24:12  arockel
// Iterator added to registry entry class.
//
// Revision 1.1  1999/03/11 12:34:53  arockel
// BAS_RegistryEntry added.
//
//==============================================================================

#ifndef RW_TOOLS_CSTRING_COMPAT_H
  #include <rw/cstring.h>
#endif
#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef ONLYPOINTER_HPP
  #include "BAS/OnlyPointer.hpp"
#endif


//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
class   BAS_FlexLexer;

namespace BAS {
class   RegistryEntry;
typedef OnlyPointer<BAS_FlexLexer>              FlexLexerPtr;
typedef OnlyPointer<RegistryEntry>        RegistryEntryPtr;
typedef RWTValOrderedVector<RegistryEntryPtr> RegistryTable;
typedef RegistryTable::iterator               RegistryIterator;
typedef RegistryTable::const_iterator         ConstRegistryIterator;
//------------------------------------------------------------------------------
/** <tt><b>RegistryEntry</b></tt> is the registration node class.

    <p>Instances of this class are used to set up the registry tree.
    This class is able to parse a special input syntax using
    the <tt>operator<<()</tt> or the method <tt>parse()</tt> for
    creating a registry tree.
    Note that the parse functionality is not thread save, it is
    expected that registry input is done by one thread only.

    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>n/a
        <dt><b>Messages send</b></dt>
        <dd>n/a
      <dt><b>Messages received</b></dt>
        <dd>n/a
      <dt><b>Errors</b></dt>
        <dd>ERR_REG_PARSE_FAILED (This message is not originated by an 
                                  instance of RegisteredObject)
    </dl>               
*/
class RegistryEntry D_THREADINFO
{

  D_SINGLETHREADED

  public:
    //-----------------------------------------------------------------------
    /** Default constructor.
    */
    RegistryEntry();
    /**
        @param name  The name (or the key) of the entry.
        @param value (Optional) the value of the entry.
        @param isRootNode (Optional) has to be set to <tt>true</tt> if 
               this is the root node, <tt>false</tt> otherwise.
    */
    RegistryEntry(const String& name, 
                      const String& value = "",     
                      const bool isRootNode=false);
    /** Copy constructor.<br>
        NOTE: Does a deep copy. 
        @param val Original instance.
    */
    RegistryEntry(const RegistryEntry& val);
    /// Destructor.
    ~RegistryEntry();

    //-----------------------------------------------------------------------
    /** The name (or the key) of the node (set method).
        @param val The new name.
    */
    void name(const String& val);
    /** The name (or the key) of the node.
        @return The name.
    */
    const String& name() const;

    /** The value of the node (set method).
        @param val The new value.
    */
    void value(const String& val);
    /** The value of the node.<br>
        The value is not set if the node contains sub nodes.
        @return The value.
    */
    const String& value() const;

    /** Mark node as root node.<br>
        This has to be used on the main node of a registry tree,
        prior before reading the tree from a stream.
    */
    void makeRootNode();

    /** Un-mark node as root node.<br>
        The opposite of the method make root node. 
        This method is neccessary if a single registry tree
        has to be prepared from more than one input streams.
    */
    void unMakeRootNode();

    /** Check if the instance is a root node.
        @return <tt>True</tt> if it is a root node,<br>
                <tt>false</tt> otherwise.
    */ 
    bool isRootNode() const;

    /** Verbose output flag.
        @return <tt>True</tt>: verbose mode enabled,<br>
                <tt>false</tt>: verbose mode disabled.
    */
    bool verboseOutput() const;

    /** Verbose output flag (set method).
        @param val The flag.
    */
    void verboseOutput(bool val);

    //-----------------------------------------------------------------------
    /** Returns an iterator for the sub nodes.
        @return An iterator, positioned to the beginning of the entry list.
    */
    RegistryIterator iterator();

    /** Returns an constant iterator for the sub nodes.
        @return An iterator, positioned to the beginning of the entry list. 
    */
    ConstRegistryIterator iterator() const;

    /** Returns the constant end - comparator.
        @return An iterator, positioned to the end of the entry list.
    */ 
    ConstRegistryIterator end() const;
     
    /** Return the number of subsequent entries.
        @return Number of entries.
    */
    size_t entries() const;

    /** Search in the subentry-list of the instance for other
        instances.<br>If name is a '<tt>.</tt>'-concatenated string, e.g.
        "<tt>group1.group2.group3</tt>", the search is done recursively.<br>
        Note: If the part name is started with a '<tt>.</tt>', the search
        starts at the own instance. This is useful if a search has to be done
        from the root node including the root node name.
        @param partName The name of the subsequent entry.
        @return 0 if nothing was found,<br>pointer to found object otherwise.
    */ 
    RegistryEntry* find(const String& partName );

    /** Search in the subentry-list of the instance for other
        instances.<br>If name is a '<tt>.</tt>'-concatenated string, e.g.
        "<tt>group1.group2.group3</tt>", the search is done recursively.
        Note: If the part name is started with a '<tt>.</tt>', the search
        starts at the own instance. This is useful if a search has to be done
        from the root node including the root node name.
        @param partName The name of the subsequent entry.
        @return 0 if nothing was found,<br>pointer to found object otherwise.
    */ 
    const RegistryEntry* find(const String&  partName) const;

    /** Alternative interface for find which accepts a string list instead
        of a concatenated string.
        @param stack The ordered list of strings to be searched for.
        @return 0 if nothing was found,<br>pointer to found object otherwise.
    */
    RegistryEntry* find(StringList& stack);

    /** Alternative interface for find which accepts a string list instead
        of a concatenated string.
        @param stack The ordered list of strings to be searched for.
        @return 0 if nothing was found,<br>pointer to found object otherwise.
    */

    const RegistryEntry* find(StringList& stack) const;
    /** Another interface for the find()-method.
        @param partName The name of the subsequent entry.
        @return 0 if nothing was found,<br>pointer to found object otherwise.
    */
    RegistryEntry* operator[](const String& partName); 

    /** Another interface for the find()-method.
        @param partName The name of the subsequent entry.
        @return 0 if nothing was found,<br>pointer to found object otherwise.
    */
    const RegistryEntry* operator[](const String& partName) const;

    /** Direct access to an subordinated entry.
        @param index The position of the desired subsequent entry.
        @return Pointer to the entry.
    */
    RegistryEntry* operator[](size_t index); 

    /** Direct access to an subordinated entry.
        @param index The position of the desired subsequent entry.
        @return Pointer to the entry.
    */
    const RegistryEntry* operator[](size_t index) const;

    //-----------------------------------------------------------------------
    /** Checks if the value data member is set.
        @return <tt>True</tt> means the value is <em>not</em> set,<br>
                <tt>false</tt> means the opposite.
    */
    bool valueIsNull() const;

    /** Checks if there are subsequent nodes.
        @return <tt>True</tt> means the are subsequent nodes,<br>
                <tt>false</tt> means the opposite.
    */
    bool isLeafNode() const;

    /** Checks if the instance and its subordinates are valid.<br>This has to be 
        used after a parse. This method returns false if a parse has failed
        or if there is another root node down the tree.
    */
    bool                     isValid() const;

    /** Mark the instance as invalid.
    */
    // CodeReview - 10.1999 - clohmann - C - Everyone can set the valid flag, i think
    // CodeReview - 10.1999 - clohmann - that only the object itself can decide this.
    void                     isValid(const bool val);

    /** Comparison operator.<br>
        The comparison operator does a recursive comparison to the instance and
        all instances in the tree below it.
        @return <tt>True</tt> means the bot trees are equal,<br>
                <tt>false</tt> means the opposite.
    */
    bool operator==(const RegistryEntry& rVal) const;

    /** Comparison operator.<br>
        The comparison operator does a recursive comparison to the instance and
        all instances in the tree below it.
        @return <tt>True</tt> means the bot trees are not equal,<br>
                <tt>false</tt> means the opposite.
    */
    bool operator!=(const RegistryEntry& rVal) const;

    /** Assignment operator.<br>
        NOTE: The assignment operator does a deep copy. The 
        whole subtree is copied (which can be expensive).
    */
    RegistryEntry& 
		 operator=(const RegistryEntry& rVal);
    
    /** Searches for matching entries and creates them, if necessary 
        (<em> for internal use only</em>).
        An exception is made for the root node: creating the node means
        setting the name for the root. 
        This method is used by the parser.
        @param stack The ordered list of strings to be searched for.
        @return: Pointer to the found or created entry,<br>
                 0 <em>only</em> in erroneous conditions.
    */
    RegistryEntry* lookup(StringList& stack);

    /** Create a subordinated registry entry instance inside the current one.
        @param name The name (the key) of the node.
        @param value The value of the node (optional).
    */
    void addEntry(const String& name, 
                  const String& value="");

    /** Assign a subordinated registry entry instance into the current one.
        Note: The entry-Pointer is invalid after transfer of responsibility.
        @param entry Smart Pointer to the instance to be added.
    */
    void addEntry(RegistryEntryPtr& entry);

    /** Assign a subordinated registry entry instance into the current one.
        Note: The entry-Pointer shall not be used to delete the instance
        after the responsibility transfer.
        @param entry Pointer to the instance to be added.
    */
    void addEntry(RegistryEntry* entry);

    /** Delete the sub tree and reset the data members name and value.
    */
    void clear();

    /** Create a registry tree from a stream. Sets the
        instance to invalid if there was an error.
        <p>Note: It is recommended to use the stream operator
        interface instead of this method.
        @return <tt>True</tt>: parse successful,<br>
                <tt>false</tt>: parse failed, tree is cleared.
    */ 
    bool parse(std::istream& is);

    // undocumented output method used by operator<<()
    void  print(std::ostream& os) const;

    // undocumented output method used by operator<<()
    void  printVerbose(std::ostream& os) const;

    //-----------------------------------------------------------------------
    /** The root node for parsing (<em>for internal use only</em>).
        @return The root node.
    */
    static RegistryEntry* root();

    /** The lexer instance (<em>for internal use only</em>).
        @return The lexer.
    */
    static FlexLexerPtr& lexer();

    //-----------------------------------------------------------------------
  private:
    // Private Class Members
    BAS_EXPORT static RWMutexLock       parserLockerCM; // needed because the parser is not thread-safe
    BAS_EXPORT static FlexLexerPtr      lexerCM;
    BAS_EXPORT static RegistryEntry*    rootCM;

    // Private Function Members
    void initialiseLexer(std::istream& is);
    void printVerboseImpl(std::ostream& os, StringList& nameStack) const;

    // Data Members
    bool              isValidM;
    bool              isRootNodeM;
    bool              verboseOutputM;
    String        nameM;
    String        valueM; 
	RWCString         levelM;

    RegistryTable subEntriesM;
	};

// Help functions

/** Input operator.<br>
    This operator uses the built-in parser of
    the class <tt>RegistryEntry</tt>.
    <p>Note: The operator is not thread-safe.
*/
std::istream& operator>>(std::istream& is, RegistryEntry& rVal);

/** Output operator.<br>
    <p>Note: The operator is not thread-safe.
*/
std::ostream& operator<<(std::ostream& os, const RegistryEntry& rVal);

//------------------------------------------------------------------------------
// inlines
//------------------------------------------------------------------------------

inline void
RegistryEntry::name(const String& val)
{
  nameM = val;
}

//------------------------------------------------------------------------------

inline const String&        
RegistryEntry::name() const
{
  return nameM;
}

//------------------------------------------------------------------------------

inline void
RegistryEntry::value(const String& val)
{
  valueM = val.strip();
}

//------------------------------------------------------------------------------

inline const String&        
RegistryEntry::value() const
{
  return valueM;
}

//------------------------------------------------------------------------------

inline void
RegistryEntry::makeRootNode()
{
  isRootNodeM = true;
}

//------------------------------------------------------------------------------

inline void
RegistryEntry::unMakeRootNode()
{
  isRootNodeM = false;
}

//------------------------------------------------------------------------------

inline bool
RegistryEntry::isRootNode() const
{
  return isRootNodeM;
}

//------------------------------------------------------------------------------

inline bool
RegistryEntry::valueIsNull() const
{
  return valueM.isNull();
}

//------------------------------------------------------------------------------

inline bool
RegistryEntry::isLeafNode() const
{
  return subEntriesM.isEmpty();
}

//------------------------------------------------------------------------------

inline RegistryEntry*       
RegistryEntry::operator[](const String& partName)
{
  return find(partName);
}

//------------------------------------------------------------------------------

inline const RegistryEntry* 
RegistryEntry::operator[](const String& partName) const
{
  return find(partName);
}

//------------------------------------------------------------------------------

inline FlexLexerPtr&
RegistryEntry::lexer()
{
  return lexerCM;
}

//------------------------------------------------------------------------------

inline RegistryEntry*
RegistryEntry::root()
{
  RWPRECONDITION(rootCM);
  return rootCM;
}

//------------------------------------------------------------------------------

inline bool
RegistryEntry::operator!=(const RegistryEntry& rVal) const
{
  return !(*this == rVal);
}

//------------------------------------------------------------------------------

inline RegistryIterator             
RegistryEntry::iterator()
{
  return subEntriesM.begin();
}

//------------------------------------------------------------------------------

inline ConstRegistryIterator             
RegistryEntry::iterator() const
{
  return subEntriesM.begin();
}

//------------------------------------------------------------------------------

inline ConstRegistryIterator             
RegistryEntry::end() const
{
  return subEntriesM.end();
}

//------------------------------------------------------------------------------
inline bool 
RegistryEntry::verboseOutput() const
{
  return verboseOutputM;
}

//------------------------------------------------------------------------------

inline void 
RegistryEntry::verboseOutput(bool val)
{
  verboseOutputM = val;
}

//------------------------------------------------------------------------------
}
#endif // BAS_REGISTRYENTRY_HPP
