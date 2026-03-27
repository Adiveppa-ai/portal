// -*-C++-*-
#ifndef BAS_INSTRUMENTATION_PROBE_TABLE_H
#define BAS_INSTRUMENTATION_PROBE_TABLE_H

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
//	Instrumentation probe class that represents probe in a list of groups.
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

#ifndef BAS_INSTRUMENTATION_PROBE_COLLECTION_H
  #include "BAS/InstrumentationProbeCollection.hpp"
#endif
#ifndef BAS_INSTRUMENTATION_PROBE_GROUP_H
  #include "BAS/InstrumentationProbeGroup.hpp"
#endif

namespace BAS
{
	/** <b>InstrumentationProbeTable</b> is an instrumentation probe class 
	 * that represents probe in a list of groups.
	 */
	class InstrumentationProbeTable : 
		public InstrumentationProbeCollection<BAS::InstrumentationProbeGroup>
		D_THREADINFO
	{
		D_NONTHREADSAFE

        public:

		/** Standard constructor
		 * @param name the name of the instrumentation probe object
		 * @param the instrumentation level for this object
		 */
		InstrumentationProbeTable(
			const ProbeInfo& probeInfo,
			const int level = defaultLevelCM);

		/** Destructor.
		 */
		virtual ~InstrumentationProbeTable();

		/** @name ListInstrumentationProbe interface */
		//@{
		/** Appends the object to list
		 * @param InstrumentationProbe object to be appended
		 */
		void append(BAS::InstrumentationProbeGroup* groupProbe);
		//@}

        private:
		// Hide
		InstrumentationProbeTable();
		InstrumentationProbeTable(const InstrumentationProbeTable& i);
		const InstrumentationProbeTable& operator=(const InstrumentationProbeTable& i);

		int rowCountM;
	};

}
#endif
