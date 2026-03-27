#ifndef EDR_COMPACTPOID_HPP
#define EDR_COMPACTPOID_HPP

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
// The class for CompactPoid
//
//
// Group:              Platform
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Shivaram
// Backup-Responsible: Giles Douglas
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 13-Feb-2004  Shivaram            Initial Revision
// 13-Oct-2004  Jasper Lan          CO128145. Add operator<
// 13-jun-2006  Keshav              CO219689, typedef'd CompactPoidVector
// 12-Jul-2006  Bert McLellan       CO223277 - Get unit tests to work
//=============================================================================

#ifndef   RW_TOOLS_TVSRTVEC_H
  #include <rw/tvsrtvec.h>
#endif

#ifndef   EDR_POIDIF_HPP
  #include "EDR/PoidIf.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

#include <string.h>
#ifndef   _RWSTD_OSTREAM_INCLUDED
  #include <ostream>
#endif

namespace BAS
{
    class Identifier;
}

namespace EDR 
{
    /**
     * This is like SDSPoid but without the buffer 
     */
    class CompactPoid: public EDR::PoidIf D_THREADINFO_M
    {
		D_NONTHREADSAFE

    public:    

		EDR_EXPORT static const EDR::PoidIf::PoidNumber INVALID_POID_NUMBER;

       /** Default Constructor. Creates a NULL poid for now 
         */
        CompactPoid();


        /**
         * constructor. used unsigned short type number 
         * instead of type string
         * @param typeNum type number of the poid
         * @param id id of the poid
         * @param dbNumber db number of poid
         * @param revision revision number of the poid
         */
        CompactPoid(const EDR::PoidIf::PoidNumber poid_typeNum,
					const BAS::Identifier::IdentifierId poidId = BAS::Identifier::ID_INVALID, 
					const BAS::Identifier::DatabaseId dbNumber = BAS::Identifier::DB_INVALID, 
					const BAS::Identifier::IdentifierRevision revision = 0);

        /**
         * Destructor.
         */
        ~CompactPoid();

        /**
         * Function to get Id of the Poid.
         * @return id of the Poid
         */
        const BAS::Identifier::IdentifierId getId() const;

        /**
         * Function to get dbNumber of the Poid.
         * @return dbNumber of the Poid
         */
        const BAS::Identifier::DatabaseId getDb() const;
        
        /**
         * Function to get type number of the Poid.
         * @return type number of the Poid
         */
        const EDR::PoidIf::PoidNumber getTypeNumber() const;

        /**
         * Function to get revision number of the Poid.
         * @return revision number of the Poid
         */
        const BAS::Identifier::IdentifierRevision getRevision() const;

        /**
         * Function to set Id of the Poid.
         * @param id id of the Poid to set to
         */
        void setId(BAS::Identifier::IdentifierId id);

        /**
         * Function to set dbNumber of the Poid.
         * @param dbNumber dbNumber of the  Poid to set to
         */
        void setDb(BAS::Identifier::DatabaseId id);
        
        /**
         * Function to set type number of the Poid.
         * @param typeNum type number of the Poid to set to
         */
        void setTypeNumber(const EDR::PoidIf::PoidNumber typeNum);

        /**
         * Function to set revision number of the Poid.
         * @param revision revision number of the Poid to set to
         */
        void setRevision(BAS::Identifier::IdentifierRevision revision);
        
		/** Function to convert from SDSPoid to BAS::Identifier.
         * @param id place to store Identifier value
         * @param dbNumber dbNumber needs to be passed in since no EDR->OAL 
         * @return true if conversion succeded, false otherwise
         * if false, id is set to NULL_IDENTIFIER
         */
        bool toBASIdentifier(BAS::Identifier& id, 
							 BAS::Identifier::DatabaseId dbNumber) const;
 
        /**
         * Function to get the Object Buffer pointed to by the Poid
         * @return the pointer to the object buffer
         */
        const char* getObjectBuffer() const;
        /** Convert to a string
         * @param str string to convert to
         * @return true for success, false for failure
         */
        bool toString(BAS::String& str) const;

        const CompactPoid& operator=(const CompactPoid& compactPoid);

        CompactPoid(const CompactPoid& compactPoid);

	bool operator==(const EDR::CompactPoid& compactPoid) const;

	friend bool operator<(const EDR::CompactPoid& poid1, const EDR::CompactPoid& poid2);

	/** \typedef CompactPoidVector
	 * Sorted vector to hold compact poid values
	 */
	typedef RWTValSortedVector<EDR::CompactPoid,
				   std::less<EDR::CompactPoid> >
							CompactPoidVector;

    private:

        /** Storage for poid type as a number*/
        EDR::PoidIf::PoidNumber poidTypeNumM;

        /** Storage for poid id */
        BAS::Identifier::IdentifierId poidIdM;

        /** Storage for dbNumber  */
        BAS::Identifier::DatabaseId dbNumberM;

        /** Storage for revision */
        BAS::Identifier::IdentifierRevision revisionM;

    };

    EDR_EXPORT extern const CompactPoid NULL_COMPACTPOID;


	/** @todo Compare revision also?
	 */
	inline bool
	EDR::CompactPoid::operator==(const EDR::CompactPoid& compactPoid) const
	{
	    return ((this->getId() == compactPoid.getId())
	        && (this->getTypeNumber()==compactPoid.getTypeNumber()));
	}

	inline bool
	operator<(const EDR::CompactPoid& poid1, const EDR::CompactPoid& poid2)
	{
	    if (poid1.getDb() < poid2.getDb())
	    {
	        return true;
	    }
	    else if (poid1.getDb() > poid2.getDb())
	    {
	        return false;
	    }
	    else 
	    {
	        if (poid1.getTypeNumber() < poid2.getTypeNumber())
		{
		    return true;
		}
		else if (poid1.getTypeNumber() > poid2.getTypeNumber())
		{
		    return false;
		}
		else 
		{
		    if (poid1.getId() < poid2.getId())
		    {
		        return true;
		    }
		    else if (poid1.getTypeNumber() > poid2.getTypeNumber())
		    {
		        return false;
		    }
		    else 
		    {
		        if (poid1.getId() < poid2.getId())
			{
			    return true;
			}
			else if (poid1.getId() > poid2.getId())
			{
			    return false;
			}
			else
			{
			    if (poid1.getRevision() < poid2.getRevision())
			    {
			        return true;
			    }
			    else 
			    {
			        return false;
			    }
			}
		    }
		}
	    }
	}
	
	inline const  BAS::Identifier::IdentifierId  
	EDR::CompactPoid::getId() const
	{
	    D_ENTER("EDR::CompactPoid::getId() const");
		return poidIdM;
	}

	inline const  BAS::Identifier::DatabaseId  
	EDR::CompactPoid::getDb() const
	{
	    D_ENTER("EDR::CompactPoid::getDb() const");
		return dbNumberM;
	}
	
	inline const EDR::PoidIf::PoidNumber
	EDR::CompactPoid::getTypeNumber() const
	{
	    D_ENTER("EDR::CompactPoid::getTypeNum() const");
		return poidTypeNumM;
	}
	
	inline const BAS::Identifier::IdentifierRevision  
	EDR::CompactPoid::getRevision() const
	{
	    D_ENTER("EDR::CompactPoid::getRevision() const");
		return revisionM;
	    
	}
	
	inline void
	EDR::CompactPoid::setId( BAS::Identifier::IdentifierId  id)
	{
		D_ENTER("EDR::CompactPoid::setId( BAS::Identifier::IdentifierId )");
		D_ARG(id);
		poidIdM = id;
	}

	inline void
	EDR::CompactPoid::setDb( BAS::Identifier::DatabaseId  dbNumber)
	{
		D_ENTER("EDR::CompactPoid::setDb( BAS::Identifier::DatabaseId )");
		D_ARG(dbNumber);
		dbNumberM = dbNumber;
	}
	
	inline void
	EDR::CompactPoid::setTypeNumber(const EDR::PoidIf::PoidNumber typeNumber)
	{
	    D_ENTER("EDR::CompactPoid::setTypeNumber(EDR::PoidIf::PoidNumber )");
	    D_ARG(typeNumber);
		poidTypeNumM = typeNumber;
	
	}
	
	inline void 
	EDR::CompactPoid::setRevision(BAS::Identifier::IdentifierRevision revision)
	{
	    D_ENTER("EDR::CompactPoid::setRevision( BAS::Identifier::IdentifierRevision )");
	    D_ARG(revision);
		revisionM = revision;
	}
	
	inline const char*
	EDR::CompactPoid::getObjectBuffer() const
	{
	    return 0;	// not used
	}

}

#endif
