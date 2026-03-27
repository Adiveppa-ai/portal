#ifndef BAS_PROTECTEDBOOL_HPP
#define BAS_PROTECTEDBOOL_HPP

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
//  This contains a one-way boolean value which is set to FALSE at
//  construction time, and can only be set to TRUE subsequently.
//
//------------------------------------------------------------------------------
//
// Revision: 10004  6.5_SP2  02-May-2003  keshav
// PRSF00039774: Incorporate gatekeeper comments of PRSF00037803
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
//==============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef _RWSTD_OSTREAM_INCLUDED
  #include <ostream>
#endif

/**
 * <tt><b>BAS::ProtectedBool</b></tt>: Class to represent a boolean value that
 * can be changed from <tt><u>false</u></tt> to <tt><u>true</u></tt>, but not
 * the other way around.<p>The BAS::RegisteredObject::registryUpdate method now
 * takes a BAS::ProtectedBool& parameter.
 */
namespace BAS {
class ProtectedBool D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name ProtectedBool constructors, destructor */
    //@{
    /** Constructor; sets itself to represent <tt>false</tt>. */
    ProtectedBool();

    /**
     * Constructor; sets itself to represent the passed value<br>If the value
     * of the param is <tt>true</tt>, then the value of the constructed object
     * is a constant <tt>true</tt>.
     * @param b The boolean value to set itself to.
     */
    ProtectedBool(const bool& b);

    /**
     * Copy constructor<br>If the value of the param is <tt>true</tt>,
     * then the value of the constructed object is a constant <tt>true</tt>.
     * @param pb The ProtectedBool to copy from.
     */
    ProtectedBool(const ProtectedBool& pb);

    /** Destructor; does nothing. */
    ~ProtectedBool();
    //@}

    /**@name ProtectedBool public methods */
    //@{
    /**
     * Get the boolean value represented by the class.
     * @return the boolean value represented by the class
     */
    const bool getValue() const;

    /**
     * Assignment operator<br>This is ignored if the value of the passed
     * param is not <tt>true</tt> or if the value of this object is
     * already <tt>true</tt>.
     * @param b The boolean value being assigned.
     * @return reference to ProtectedBool object representing the new value.
     */
    ProtectedBool& operator=(const bool b);

    /**
     * Assignment operator<br>This is ignored if the boolean value of the
     * passed parameter is not <tt>true</tt> or if the value of this object
     * is already <tt>true</tt>.
     * @param b The ProtectedBool value being assigned.
     * @return reference to ProtectedBool object representing the new value.
     */
    ProtectedBool& operator=(const ProtectedBool& pb);

    /**
     * Equality comparision operator
     * @param b The boolean value being compared to.
     * @return <tt>true</tt> or <tt>false</tt>.
     */
     bool operator==(const bool b);

    /**
     * Equality comparision operator
     * @param pb The ProtectedBool being compared to.
     * @return <tt>true</tt> or <tt>false</tt>.
     */
     bool operator==(const ProtectedBool& pb);

    /**
     * Inequality comparision operator
     * @param b The boolean value being compared to.
     * @return <tt>true</tt> or <tt>false</tt>.
     */
     bool operator!=(const bool b);

    /**
     * Inequality comparision operator
     * @param pb The ProtectedBool being compared to.
     * @return <tt>true</tt> or <tt>false</tt>.
     */
     bool operator!=(const ProtectedBool& pb);

    /**
     * Output operator
     */
     friend std::ostream& operator<<(
			std::ostream& os, const ProtectedBool& pb);

    /**
     * Self test method (<em>for internal use only</em>).
     * @return <tt>True</tt> if class test was successful,
     *         <tt>false</tt> otherwise.
     */
    static bool selfTest();

    //@}

  private:
    bool boolM;
};

std::ostream& operator<<(std::ostream& os, const ProtectedBool& value);

// Getter fn
inline const bool
ProtectedBool::getValue() const
{
  return boolM;
}

// Setter fn
inline ProtectedBool&
ProtectedBool::operator=(const bool b)
{
  // if boolM is already set to TRUE, do nothing...
  if (boolM == false)
  {
     boolM = b;			// if b == false, this is a noop.
  }
  return *this;
}

// Setter fn
inline ProtectedBool&
ProtectedBool::operator=(const ProtectedBool& pb)
{
  // if boolM is already set to TRUE, do nothing...
  if (boolM == false)
  {
    boolM = pb.getValue();	// if pb.boolM == false, this is a noop.
  }
  return *this;
}

// Tester fn
inline bool
ProtectedBool::operator==(const bool b)
{
  return (boolM == b);
}

// Tester fn
inline bool
ProtectedBool::operator==(const ProtectedBool& pb)
{
  return (boolM == pb.getValue());
}


// Tester fn
inline bool
ProtectedBool::operator!=(const bool b)
{
  return (boolM != b);
}

// Tester fn
inline bool
ProtectedBool::operator!=(const ProtectedBool& pb)
{
  return (boolM != pb.getValue());
}

} // end namespace BAS

#endif
