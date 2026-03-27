#ifndef BAS_HASHSTRING_HPP
#define BAS_HASHSTRING_HPP
// @(#)%Portal Version: HashString.hpp:PlatformR2Int:2:2006-Jul-19 16:15:20 %
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
//
//------------------------------------------------------------------------------
// Module Description:
//   HashString class.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Michael Wriedt
//
// $RCSfile: HashString.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:44:10 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: HashString.h,v $
// Revision 1.2.2.1  2002/01/15 16:14:40  mwriedt
// PETS #42457: New methods.
//
// Revision 1.2  2001/10/15 09:41:19  mwriedt
// Added RWCString constructor and operator.
//
// Revision 1.1  2001/10/05 08:19:28  mwriedt
// - Introduced new class HashString.
//
//==============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace BAS
{
/** <tt><b>HashString</b></tt> stores a string and its hash value.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: HashString.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:44:10 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>

    <p>It should be used in a map for quick comparison and less memory usage. */
class HashString D_THREADINFO
{
public:

  /** Default/initialising constructor. */
  HashString(const String& string = "");

  /** Default/initialising constructor. */
  HashString(const RWCString& string);

  /** Copy constructor. */
  HashString(const HashString& other);

  /** Destructor. */
  ~HashString();

  /** Returns the string. */
  String string() const;

  /** Returns the hash value. */
  u_int64 hash() const;

  /** Returns the char data. */
  const char* data() const;

  /** Returns comparison. */
  int compareTo(const HashString& other) const;

  /** Comparison operator. */
  bool operator ==(const HashString& other) const;

  /** Comparison operator. */
  bool operator !=(const HashString& other) const;

  /** Comparison operator. */
  bool operator <(const HashString& other) const;

  /** Comparison operator. */
  bool operator >(const HashString& other) const;

  /** Assignment operator. */
  const HashString& operator =(const String& string);

  /** Assignment operator. */
  const HashString& operator =(const RWCString& string);

  /** Assignment operator. */
  const HashString& operator =(const HashString& other);

  /** Output operator. */
  friend std::ostream& operator <<(std::ostream& os, const BAS::HashString& s);
  // Hash object
  struct Hash
  {
    u_int64 operator()(const HashString& s) const
    {
      return s.hash();
    }
  };


private:

  void create(const char* data);
  void assign(size_t length, const char* data);

  char*    stringM;
  u_int64  hashM;

  size_t   capacityM;
};

	std::ostream& operator <<(std::ostream& os, const BAS::HashString& s);

// inlines

inline String
HashString::string() const
{
  return stringM;
}


inline u_int64
HashString::hash() const
{
  return hashM;
}


inline const char*
HashString::data() const
{
  return stringM;
}


inline bool
HashString::operator !=(const HashString& other) const
{
  return !operator ==(other);
}
}
#endif
