
#ifndef BAS_SIMPLESTRING_HPP
#define BAS_SIMPLESTRING_HPP
//==============================================================================
//
// Copyright (c) 2003, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//  Simple Lightweight String class to using minimal memory.
//
// Open Points:                                            
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Louis Piro                                  
//
//------------------------------------------------------------------------------

#include <string.h>
#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_DATAVALUE_H
  #include "BAS/DataValue.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef _pin_os_string_h_
  #include "pin_os_string.h"
#endif

namespace BAS
{
/** Simple String list class.
*/
class SimpleString;
typedef RWTValOrderedVector<SimpleString>      SimpleStringList;


/** <b><tt>SimpleString</tt></b> is a lightweight string class focused on reducing memory consumption.
*/
class SimpleString : public DataValue
{
  D_SINGLETHREADED

  public:

   /** Default constructor for a SimpleString. 
       Initialized to an empty string.
   */
   SimpleString();

   /** Destuctor for a SimpleString. */
   ~SimpleString();

   /** Preferred constructor for a SimpleString.
       @param data used to construct object.
              NULL parameter initializes to an empty string.
              Caller continues to own memory pointed to by data.
   */
   SimpleString(const char* data);

   /** Overloaded constructor for a SimpleString
       @param BAS::String object
       SimpleString Initializes with data of BAS::String object.
   */
   explicit SimpleString(const BAS::String& basString);

   /** Copy constructor for a SimpleString.
       @param object to be copied.
   */
   SimpleString(const SimpleString& copy);

   /** Assignment operator for a SimpleString.
       @param assign object.
   */
   SimpleString& operator=(const SimpleString& assign);

   /** char* assignment operator for a SimpleString.
       @param object to assign, if NULL then initialized to empty string.
   */
   SimpleString& operator=(const char* assign);

   /** Conversion operator for a SimpleString.
       converts to char*, object continues to own storage
       of converted return value.
   */
   operator const char* () const;

   /** Data accessor for a SimpleString.
       returns char* representation, object continues to own storage
       of returned value.
   */
   const char* data() const;

   /** Data setter for a SimpleString.
       @param accepts const char* representation, caller continues to own storage
              of the inputed char* parameter. If data equals NULL, then data set to
              an empty string.
   */
   void setData(const char* data);

   /** returns length of simple string
   */
   size_t length() const;

   /** Stream << operator for a SimpleString. 
       convienient for cout messaging.
   */
   friend std::ostream& operator<<(std::ostream& os, const SimpleString& theString);


   /** Stream << operator for a SimpleStringList. 
       convienient for cout messaging.
   */
   friend std::ostream& operator<<(std::ostream& os, const SimpleStringList& theString);

   /** Returns null if data equals an empty string.
   */
   bool isNull() const;

   /** Addition operator allows strings to be added.
       @param string to be appended.
   */
   SimpleString& operator+=(const SimpleString& addition);

   /** Addition operator allows char* to be added.
       @param char* to be appended.
   */
   SimpleString& operator+=(const char* addition);

   /** Equality operator allows string to be compared case insensitive.
       @param String to be compared for equality.
   */
   bool operator== (const SimpleString& string) const;

   /** Inequality operator allows string to be compared case insensitive.
       @param String to be compared for inequality.
   */
   bool operator!= (const SimpleString& string) const;

   /** Inequality operator allows a char pointer to be compared case insensitive.
       @param String to be compared for inequality.
   */
   bool operator!= (const char* string) const;

   /** Equivalence operator allows string to be compared case insensitive.
       @param String to be compared for equivalence.
   */
   bool operator< (const SimpleString& string) const;

 private:
   /** Initialized the data from construction or assignment
   */
  void initData(const char* source);

 private:
   char* dataM;

};

std::ostream& operator<<(std::ostream& os, const SimpleString& theString);
std::ostream& operator<<(std::ostream& os, const SimpleStringList& theString);


//-------------------------------------------------------------------------
// inlines
//-------------------------------------------------------------------------
inline bool 
SimpleString::operator== (const SimpleString& string) const 
{
  D_ENTER("SimpleString::operator== (const SimpleString& string) const");

  return (strcasecmp(dataM, string.data())==0);
}

//-------------------------------------------------------------------------
inline bool 
SimpleString::operator!= (const SimpleString& string) const 
{
  D_ENTER("SimpleString::operator!= (const SimpleString& string) const");

  return (*this != string.data());
}

//-------------------------------------------------------------------------
inline bool 
SimpleString::operator!= (const char* string) const 
{
  D_ENTER("SimpleString::operator!= (const char* string) const");

  return (strcasecmp(dataM, string)!=0);
}

//-------------------------------------------------------------------------
inline bool 
SimpleString::operator< (const SimpleString& string) const 
{
  D_ENTER("SimpleString::operator< (const SimpleString& string) const");

  return (strcasecmp(dataM, string.data())<0);
}

//-------------------------------------------------------------------------
inline bool 
SimpleString::isNull() const 
{
  D_ENTER("SimpleString::isNull() const");

  return (strlen(dataM)==0);
}

//-------------------------------------------------------------------------
inline size_t 
SimpleString::length() const 
{
  D_ENTER("SimpleString::length() const");

  return strlen(dataM);
}

//-------------------------------------------------------------------------
inline const char* 
SimpleString::data() const 
{
  D_ENTER("SimpleString::data() const");

  return dataM;
}

//-------------------------------------------------------------------------
inline
SimpleString::operator const char* () const 
{
  D_ENTER("SimpleString::operator const char* () const");

  return dataM;
};

//-------------------------------------------------------------------------
}
#endif
