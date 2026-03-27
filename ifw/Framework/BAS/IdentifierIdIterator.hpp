#ifndef BAS_IDENTIFIERIDITERATOR_HPP
#define BAS_IDENTIFIERIDITERATOR_HPP

//=============================================================================
//
// Copyright (c) 2004, 2016, Oracle and/or its affiliates. All rights reserved.
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
//
// Module Description:
//  This class is used to contain a range of poid ids.
//
// Current Issues:
//  No support for handing out a range of mangled poid ids > 1.
//  No support for negative poid ids.
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Kirk Lieb
// Backup-Responsible: Giles Douglas
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 03-Feb-2004  Kirk Lieb           Initial version.
// 05-Feb-2004  Kirk Lieb           Add mangling support for single poid id.
// 06-Feb-2004  Kirk Lieb           Add partition encoding support.
// 17-Mar-2004  Kirk Lieb           Update doxygen comments.
// 11-Aug-2006  Abil George         PRSF00228450
// 02-May-2016  pzhou 	            bug-22965000 Utilize pin_virtual_time

//
//=============================================================================

#ifndef BAS_IDENTIFIER_H
  #include "BAS/Identifier.hpp"
#endif
#ifndef   _PIN_PARTITION_MODE_H_
  #include "pin_partition_mode.h"
  #include "pcm.h"
#endif

namespace BAS
{
	/** Contains a range of new poid ids suitable for handing out.
	 * This class is used to ensure the allocation of new poid ids is simple
	 * and secure such that no invalid poid ids are accidentally used.
	 * It internally manages the poid id range with respect to the Infranet
	 * multi-db increment, thus saving the user from needing to know or understand
	 * how to properly select valid poid ids in a given range.<p>
	 *
	 * The following guidelines provide sample usage for proper handling:<p>
	 * 1.  Ensure isValid() is true before using the iterator.<p>
	 * 2.  While next() is true, use value() to get the next poid id.<p>
	 *
	 * <p>Please note that a value() <= 0 is never valid, but proper use of
	 * isValid() and next() will ensure a valid poid id every time.
	 */
	class IdentifierIdIterator
	{
	public:

		enum Status
		{
			ok = 0, // Even when it runs out of poid ids, the status is still ok.
			invalid // Due to bad input constructor arguments.
		};

		/** Default constructor.
		 */
		IdentifierIdIterator();

		/** Standard constructor.
		 * If the following precondition is not met, poid ids are set to 0 and
		 * increment by is set to 1: ((maxId - MinPoidId) % incrementBy == 0).
		 */
		IdentifierIdIterator(
			BAS::Identifier::IdentifierId minId,
			BAS::Identifier::IdentifierId maxId,
			int incrementBy,
			pin_partition_mode_t partitionMode = PIN_PARTITION_MODE_UNKNOWN,
			bool mangled = false);

		// Note: copy constructor, assignment constructor, and destructor
		// are automatically handled by C++ since shallow copy is ok.

		/** Used to see if there are any more poid ids to be gotten from this iterator.
		 *
		 * @return true if minIdM <= maxIdM; else false.
		 */
		bool next() const;

		/** Used to get the next poid id value contained.
		 * The iterator internally manages any Infranet mutli-db increment with
		 * repsect to poid ids, so only valid, useable poid ids will be returned.<p>
		 *
		 * If the last poid id is given, the min and max poid ids are reset to 0.
		 *
		 * @return minIdM; minIdM += incrementByM;
		 */
		BAS::Identifier::IdentifierId value();

		/** Used to get the next poid id value contained in partition mode.
		 * The iterator internally manages any Infranet mutli-db increment with
		 * repsect to poid ids, so only valid, useable poid ids will be returned.<p>
		 * One particular use of it is to utilize pin_virtual_time for a partitioned
		 * object.
		 *
		 * If the last poid id is given, the min and max poid ids are reset to 0.
		 *
		 * @return minIdM; minIdM += incrementByM;
		 */
		BAS::Identifier::IdentifierId value(BAS::DateTime& partitionDay);

		/** Returns mangled flag.
		 *
		 * @return mangledM;
		 */
		bool isMangled() const;

		/** Used to determine the number of contained poid ids.
		 *
		 * @return (maxIdM - minIdM + 1) / incrementByM;
		 */
		size_t quantity() const;

		/** Return the current status of the object.
		 *
		 * @return The status of this object.
		 */
		Status getStatus() const;

		/** Returns the partition mode for the current class.
		 */
		pin_partition_mode_t getPartitionMode() const;

		/** Returns true if the object has a status of ok.
		 */
		bool isValid() const;

		/** Modifies the most significant 20 bits of each id in the iterator.
		 * This method is used to encode target partition information
		 * into the ids.  The most significant 4 bits contain the target
		 * sub-partition, and the next most significant 16 bits contain
		 * the target dayPartition.
		 *
		 * @param dayPartition The day for the targeted partition.
		 * @param subPartition The sub-partition for the given day.
		 * Valid values are in [0-7]; the default is 0.
		 *
		 * @return True if subPartition is in [0-7] and the ids are encoded
		 * with the partition information; else false.
		 */
		bool encodePartition(
			const BAS::DateTime& dayPartition, 
			int subPartition = 0);

		int64 manglePoidId(int64 seq_id);

	private:
		Status statusM;
		BAS::Identifier::IdentifierId minIdM;
		BAS::Identifier::IdentifierId maxIdM;
		int incrementByM;
		pin_partition_mode_t partitionModeM;
		bool mangledM;
	};
}

inline
bool
BAS::IdentifierIdIterator::isMangled() const
{
	return mangledM;
}

inline
BAS::IdentifierIdIterator::Status
BAS::IdentifierIdIterator::getStatus() const
{
	return statusM;
}

inline
pin_partition_mode_t
BAS::IdentifierIdIterator::getPartitionMode() const
{
	return partitionModeM;
}

inline
bool
BAS::IdentifierIdIterator::isValid() const
{
	if (statusM == ok)
	{
		return true;
	}
	return false;
}

#endif

