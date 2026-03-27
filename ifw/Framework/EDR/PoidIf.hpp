#ifndef EDR_POIDIF_HPP
#define EDR_POIDIF_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2007 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================
//-----------------------------------------------------------------------------
// Component: OAL
//-----------------------------------------------------------------------------
// Module Description:
// The abstract class for poids
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Alan Lu
// Backup-Responsible: Keith B. 
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 07-20-2000   Alan Lu             created. 
// 21-Jun-2003	kbref				added virtual dtor
// 12-Feb-2003	Shivaram			moved from OAL/Poid
//
//=============================================================================
#if !defined EDR_EXPORT
  #if defined(WINDOWS)
    #if !defined(EDR_INTERNAL)
      #define EDR_EXPORT __declspec(dllimport)
    #else
      #define EDR_EXPORT __declspec(dllexport)
    #endif
  #else
    #define EDR_EXPORT
  #endif
#endif


namespace BAS
{
    class String;
}

#ifndef   _PIN_TYPE_H_
  #include "pin_type.h"
#endif
#ifndef   BAS_IDENTIFIER_H
  #include "BAS/Identifier.hpp"
#endif

namespace EDR 
{
	/** @todo Indent properly.
 	*/

  /**
   * Base class for OAL-specific poid and systemwide CompactPoid to replace Identifier.
   */
  class PoidIf
  {
  public:
	virtual ~PoidIf() = 0;

	/**
	 * Typedef for poid type number type 
	 * u_int16 is pcm.type
	 */
	typedef u_int16 PoidNumber;

	/**
	 * Pure virtual function to get Id of the Poid.
	 * @return id of the Poid
	 */
	virtual const BAS::Identifier::IdentifierId getId() const = 0;

    /**
     * Pure virtual function to get type of the Poid as Number.
     * @return type of the Poid
     */
    virtual const PoidNumber getTypeNumber() const = 0;

	/**
	 * Pure virtual function to get revision number of the Poid.
	 * @return revision number of the Poid
	 */
	virtual const BAS::Identifier::IdentifierRevision  getRevision() const = 0;

	/**
	 * Pure virtual function to set Id of the Poid.
	 * @param id id of the Poid to set to
	 */
	virtual void setId(BAS::Identifier::IdentifierId id) = 0;

    /**
     * Pure virtual function to set type of the Poid as number.
     * @param type type of the Poid as number to set to
     */
    virtual void setTypeNumber(const PoidNumber typeNumber) = 0;

	/**
	 * Pure virtual function to set revision number of the Poid.
	 * @param revision revision number of the Poid to set to
	 */
	virtual void setRevision(BAS::Identifier::IdentifierRevision revision) = 0;

    /**
     * Function to get the raw object buffer pointed to by the poid.
     * @return the pointer to the object buffer
     */
    virtual const char* getObjectBuffer() const = 0;

	/**
	 * Function to match self on a given object type.
	 * @param typeNum type Number to match on
	 * @return true if matches, false otherwise
	 */
	bool matchOnObjectTypeNumber(EDR::PoidIf::PoidNumber typeNumber) const;

	/*
	 * Output operator
	 */
	friend std::ostream&
	operator<<(std::ostream& os, const EDR::PoidIf& poid);

  };

	std::ostream&
	operator<<(std::ostream& os, const EDR::PoidIf& poid);

  inline PoidIf::~PoidIf()
  {
  }
  inline bool
  PoidIf::matchOnObjectTypeNumber(PoidIf::PoidNumber typeNumber) const
  {
    return (typeNumber == getTypeNumber());
  }

}

#endif
