// -*-C++-*-
#ifndef BAS_INSTRUMENTATION_PROBE_LIST_H
#define BAS_INSTRUMENTATION_PROBE_LIST_H
//=============================================================================
//
// Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
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
//	This is a class that has a list of InstrumentationProbe Objects
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
// 07-Dec-2004  Shivaram            Created
// 07-Feb-2006  Ming-Wen Sung       Modified based on design in OMF
//
//=============================================================================

#ifndef BAS_INSTRUMENTATION_PROBE_COLLECTION_H
  #include "BAS/InstrumentationProbeCollection.hpp"
#endif

namespace BAS
{
	/** <b>InstrumentationProbeList</b> is an instrumentation probe class 
	 * that has a list of instrumentationProbe objects
	 */
	class InstrumentationProbeList : 
		public InstrumentationProbeCollection<BAS::InstrumentationProbe>
		D_THREADINFO
	{
		D_NONTHREADSAFE

        public:

		/** Standard constructor
		 * @param name the name of the registered object to construct
		 * @param level instrumentation level
		 */
                InstrumentationProbeList(
			const ProbeInfo& probeInfo,
			const int level = defaultLevelCM);

		/** Destructor.
		 */
		virtual ~InstrumentationProbeList();

        private:
		// Hide
		InstrumentationProbeList();
		InstrumentationProbeList(const InstrumentationProbeList& i);
		const InstrumentationProbeList& operator=(const InstrumentationProbe& i);
	};
}

#endif
