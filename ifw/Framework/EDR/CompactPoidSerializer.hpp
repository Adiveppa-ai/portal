#ifndef EDR_COMPACTPOIDSERIALIZER_HPP
#define EDR_COMPACTPOIDSERIALIZER_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================
//-----------------------------------------------------------------------------
// Component: EDR
//-----------------------------------------------------------------------------
// Module Description:
// The class for Serializing and De-serializingCompactPoid
//
//
// Group:              Platform
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Shivaram
// Backup-Responsible: Alan Lu
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 20-Apr-2004  Alan Lu             Initial Revision
//
//=============================================================================
#ifndef   EDR_COMPACTPOID_HPP
  #include "EDR/CompactPoid.hpp"
#endif

namespace EDR 
{
    /**
     * This class serializes and deserializes CompactPoid.
     */
    class CompactPoidSerializer
    {
		D_NONTHREADSAFE

    public:  
  
		/**
		 * Room needed for the serialized compact poid.
		 */ 
		static const size_t sizeofSerializedCompactPoidCM;

		/**
		 * Serialize.
		 * @param poid poid to serialize
		 * @param poidBuffer buffer to serialize to
		 */
		static void GetBuffer(const CompactPoid& poid, char* poidBuffer);

		/**
		 * Deserialize.
		 * @param poidBuffer buffer to deserialize from
		 * @return the compact poid deserialized from the buffer
		 */
		static CompactPoid GetPoid(const char* poidBuffer);

	private:

		/**
		 * Constants for readability.
		 */
		static const size_t sizeofTypeNumberCM;
		static const size_t sizeofBASIdentifierIdCM;
		static const size_t sizeofBASIdentifierRevisionCM;
		static const size_t offsetOfBASIdentifierIdCM;
		static const size_t offsetOfBASIdentifierRevisionCM;
	};
}

#endif
