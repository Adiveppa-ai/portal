// -*-C++-*-
#ifndef BAS_INSTRUMENTATION_PROBE_GROUP_H
#define BAS_INSTRUMENTATION_PROBE_GROUP_H

//=============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Instrumentation probe class that represents probe in a list of attributes.
//
// Current Issues:
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Ming-Wen Sung
// Backup-Responsible: Shivaram
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 24-Jan-2005  Ming-Wen Sung       Created
// 07-Feb-2006  Ming-Wen Sung       Modified based on design in OMF
//
//=============================================================================

#ifndef BAS_INSTRUMENTATION_PROBE_ATTRIBUTE_H
  #include "BAS/InstrumentationProbeAttribute.hpp"
#endif
#ifndef BAS_INSTRUMENTATION_PROBE_COLLECTION_H
  #include "BAS/InstrumentationProbeCollection.hpp"
#endif

namespace BAS
{
	/** <b>InstrumentationProbeGroup</b> is an instrumentation probe class 
	 * that represents probe in a list of attributes.
	 */
	class InstrumentationProbeGroup : 
		public InstrumentationProbeCollection<BAS::InstrumentationProbeAttribute>
		D_THREADINFO
	{
		D_NONTHREADSAFE

        public:

		/** Standard constructor
		 * @param probeInfo the information of the instrumentation probe object
		 * @param level the instrumentation level for this object
		 */
		InstrumentationProbeGroup(
			const ProbeInfo& probeInfo,
			const int level = defaultLevelCM);

		/** Destructor.
		 */
		virtual ~InstrumentationProbeGroup();

		/** @name InstrumentationProbe interface. */
		//@{
		/** Get name of this instrumentation probe object
		 * @return name  of this instrumentation probe obejct
		 */
		BAS::String getName() const;
		//@}

		/** @name public methods. */
		//@{
		/** Set index for this group object.
		 * @param index the new index value for this group object
		 */
		void setIndex(const int index);

		/** Get index value for this group object.
		 * @return index value for this group object
		 */
		int getIndex() const;
		//@}

        private:
		// Hide
		InstrumentationProbeGroup();
		InstrumentationProbeGroup(const InstrumentationProbeGroup& i);
		const InstrumentationProbeGroup& operator=(const InstrumentationProbeGroup& i);

		/** index value that indicates index for this group is not specified */
		BAS_EXPORT static const int indexNotSpecifiedCM;

		/** index value for this group object */
		int indexM;
	};

inline void
InstrumentationProbeGroup::setIndex(const int index)
{
	indexM = index;
}

inline int
InstrumentationProbeGroup::getIndex() const
{
	return indexM;
}

}
#endif
