#ifndef BAS_IDENTIFIER_H
#define BAS_IDENTIFIER_H

// @(#)%Portal Version: Identifier.hpp:PlatformR2Int:2:2006-Jul-16 15:31:48 %
/*
 * Identifier.h 
 *
* Copyright (c) 2002, 2016, Oracle and/or its affiliates. All rights reserved.
 *		This material is the confidential property of Oracle Corporation. 
 *		or its subsidiaries or licensors and may be used, reproduced, stored
 *		or transmitted only in accordance with a valid Oracle license or 
 *		sublicense agreement.
 */

#include <string.h>
#ifndef _RWSTD_NEW_INCLUDED
  #include <new>
#endif
#ifndef _RWSTD_IOSTREAM_INCLUDED
  #include <iostream>
#endif

#ifndef BAS_DATAVALUE_H
  #include "BAS/DataValue.hpp"
#endif
#ifndef BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#include <ctype.h>
#ifndef _RWSTD_OSTREAM_INCLUDED
  #include <ostream>
#endif
#ifndef _PCM_H
  #include "pcm.h"
#endif

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif
#ifndef _pin_os_string_h_
  #include "pin_os_string.h"
#endif

namespace BAS 
{
	/** 
	 * \class Identifier Identifier.h "BAS/Identifier.h"
	 * BAS class representing the infranet Identifier
	 */
	class Identifier : public DataValue 
	{
	public:
		/** \typedef IdentifierId
		 *	Type of id portion of an Identifier.
		 */
		typedef int64 IdentifierId; 

		/** \typedef DatabaseId
		 * Type of the database id
		 */
		typedef int64 DatabaseId;

		/** \typedef IdentifierRevision
		 *	Type of revision portion of an Identifier.
		 */
		typedef int32 IdentifierRevision; 

		BAS_EXPORT static const IdentifierId ID_NULL;
		BAS_EXPORT static const IdentifierId ID_INVALID;
		BAS_EXPORT static const DatabaseId DB_INVALID;
		BAS_EXPORT static const u_int16 TYPENUM_INVALID;

		// Encoding related constants.
		static const int SUB_PARTITION_BITS_START = 60; // For shifting bits.
		static const int DAY_PARTITION_BITS_START = 44; // For shifting bits.
		static const int MIN_SUB_PARTITION = 0x0; // real-time partition is 000
		static const int MAX_SUB_PARTITION = 0x7; // max sub partition is 111
		static const int MIN_DAY_PARTITION = 0x0;
		static const int MAX_DAY_PARTITION = 0xFFFF; // 16 bits set.
		static const int SECONDS_PER_DAY = 60 * 60 * 24;

		/** Constructor. Creates an invalid identifier
		 */
		Identifier();
	
		/** Constructor
		 *
		 * @param db the database id
		 * @param poid_type the type of the poid
		 * @param poidId the id of the poid
		 * @param revision the revision number of the poid
		 */
		Identifier(const DatabaseId db, const char* poid_type,
				   const IdentifierId poidId = -1, const IdentifierRevision revision = 0);

		/** Constructor
		 *
		 * @param db the database id
		 * @param poid_typeNum the type of the poid as a number
		 * @param poidId the id of the poid
		 * @param revision the revision number of the poid
		 */
		Identifier(const DatabaseId db, const u_int16 poid_typeNum,
		           const IdentifierId poidId = -1, const IdentifierRevision revision = 0);

		/** Destructor 
		 */
		~Identifier();
		
		/** Accessor method to get the database id
		 * @return const int64 containing the db id
		 */
		const DatabaseId getDB () const;
		
		/** Accessor method for the type
		 * @return const char* containing the poid type
		 */
		const char* getType() const;
		
		/** Accessor method for the type number
		 * @return const u_int16 containing the poid type number
		 */
		const u_int16 getTypeNum() const;

		/** Accessor method for the id
		 * @return const IdentifierId containing the poid id
		 */
		const IdentifierId getId () const;
		
		/** Accessor method for the revision
		 * @return const IdentifierRevision containing the revision number
		 */
		const IdentifierRevision getRevision() const;
		
		/** Setter method for the db
		 * @param db the database id
		 */
		void setDB(const DatabaseId db);
		
		/** Setter method for the type
		 * @param poidType the poid type to store
		 */
		void setType(const char* poidType);
		
		/** Setter method for the type
		 * @param poidTypeNum the poid type number to store
		 */
		void setTypeNum(const u_int16 poidTypeNum);

		/** Setter method for the id
		 * @param poidID the id of the poid
		 */
		void setId(const IdentifierId poidId);
		
		/** Setter method for the revision
		 * @param revision the revision to store
		 */
		void setRevision(const IdentifierRevision revision);
		
		/** Modifies the most significant 20 bits of the id.
		 * This method is used to encode target partition information
		 * into the id.  The most significant 4 bits contain the target
		 * sub-partition, and the next most significant 16 bits contain
		 * the target dayPartition.
		 *
		 * @param dayPartition The day for the targeted partition.
		 * @param subPartition The sub-partition for the given day.
		 * Valid values are in [0-7]; the default is 0.
		 *
		 * @return True if subPartition is in [0-7] and the id is encoded
		 * with the partition information; else false.
		 */
		bool encodePartition(
			const BAS::DateTime& dayPartition, 
			int subPartition = 0);
	
		/** Modifies the most significant 20 bits of the given id.
		 * This method is used to encode target partition information
		 * into the id.  The most significant 4 bits contain the target
		 * sub-partition, and the next most significant 16 bits contain
		 * the target dayPartition.
		 *
		 * @param id The identifier id to be encoded.
		 * @param dayPartition The day for the targeted partition.
		 * @param subPartition The sub-partition for the given day.
		 * Valid values are in [0-7]; the default is 0.
		 *
		 * @return True if subPartition is in [0-7] and the id is encoded
		 * with the partition information; else false.
		 */
		static bool encodePartition(
			IdentifierId& id,
			const BAS::DateTime& dayPartition, 
			int subPartition = 0);
	
		/** Copy constructor
		 */
		Identifier(const BAS::Identifier&);

		/** Assignment operator
		 * @param rVal r-value
		 */
		const BAS::Identifier& operator=(const Identifier& rval);
	
		/** Convert to a string
		 * @param str string to convert to
		 * @return true for success, false for failure
		 */
		bool toString(BAS::String& str) const;

		friend bool operator==(const BAS::Identifier& p1,
							   const BAS::Identifier& p2);

		friend std::ostream& operator<<(std::ostream& os,
										const BAS::Identifier& poid);

	private:
		
		/** Storage for poid type */
		char idTypeM[PCM_MAX_POID_TYPE];

		/** Storage for poid type as a number*/
		u_int16 idTypeNumM;
		
		/** Storage for poid db */
		DatabaseId	dbM;
		
		/** Storage for poid id */
		IdentifierId poidIdM;
		
		/** Storage for revision */
		IdentifierRevision revisionM;

		/** The "invalid" string */
		static const char* invalidIdCM;

	};
	bool operator==(const BAS::Identifier& p1,
					const BAS::Identifier& p2);

	std::ostream& operator<<(std::ostream& os,
							 const BAS::Identifier& poid);


	BAS_EXPORT extern const Identifier INVALID_IDENTIFIER;
	BAS_EXPORT extern const Identifier NULL_IDENTIFIER;

	inline const Identifier::IdentifierRevision
	Identifier::getRevision() const 
	{
		return revisionM;
	}

	inline const Identifier::IdentifierId
	Identifier::getId() const 
	{
		return poidIdM;
	}

	inline const char*
	Identifier::getType() const 
	{
		return idTypeM; 
	}

    inline const u_int16
    Identifier::getTypeNum() const
    {
        return idTypeNumM;
    }


	
	inline const
	Identifier::DatabaseId Identifier::getDB() const 
	{
		return dbM;
	}

	inline void
	Identifier::setDB(const Identifier::DatabaseId db) 
	{
		dbM = db;
	}

	inline void
	Identifier::setType(const char* poidType)
	{
		pin_strlcpy(idTypeM, poidType ,PCM_MAX_POID_TYPE);
	}
    inline void
    Identifier::setTypeNum(const u_int16 poidTypeNum)
    {
        idTypeNumM = poidTypeNum;
    }


	inline void
	Identifier::setId(const IdentifierId poidId)
	{
		poidIdM = poidId;
	}
	
	inline void
	Identifier::setRevision(const IdentifierRevision revision)
	{
		revisionM = revision;
	}
}

#endif
