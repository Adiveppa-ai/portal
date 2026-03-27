// @(#)%Portal Version: InstrumentationProbeAttribute.hpp:RWSmod7.3.1Int:1:2007-Sep-12 04:44:57 %
#ifndef BAS_INSTRUMENTATION_PROBE_ATTRIBUTE_H
#define BAS_INSTRUMENTATION_PROBE_ATTRIBUTE_H

//=============================================================================
//
// Copyright (c) 2005 - 2007 Oracle. All rights reserved.
//
// This material is the confidential property of Oracle Corporation or
// its licensors and may be used, reproduced, stored or transmitted only
// in accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Instrumentation probe class that represents probe in name and value pair.
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
// 23-Oct-2006  Ming-Wen Sung       CO236127 - add getValueWithoutLock() API
//
//=============================================================================

#ifndef BAS_INSTRUMENTATION_PROBE_H
  #include "BAS/InstrumentationProbe.hpp"
#endif
#ifndef BAS_INSTRUMENTATION_PROBE_VALUE_IF_H
  #include "BAS/InstrumentationProbeValueIf.hpp"
#endif

namespace BAS
{
	/** <b>InstrumentationProbeAttribute</b> is an instrumentation probe 
	 * class that represents a probe in name and value pair.
	 */
	class InstrumentationProbeAttribute : 
		public InstrumentationProbe D_THREADINFO
	{
		D_NONTHREADSAFE

        public:
		/** Standard constructor
		 * @param name the name of the instrumentation probe object 
		 * @param value instrumentation probe value that contains
		 *        the reference of probe itself
		 * @param mode mode for this attribute value
		 * @param level the isntrumentation level for this object
		 */
		InstrumentationProbeAttribute(
			const ProbeInfo& probeInfo,
			BAS::InstrumentationProbeValueIf* value,
			const int level = defaultLevelCM);

		/** Destructor.
		 */
		virtual ~InstrumentationProbeAttribute();

		/** @name InstrumentationProbe interface. */
		//@{
		/** Get instrumentation probe value
		 * @param value value to be returned to
		 * @param lockProtected flag indicates to get the value
		 * that is protected by a lock if there is any
		 * @param name name of the instrumentation probe to be returned
		 * @return true if successful
		 */
		bool getValue(
			BAS::String& value,
			bool lockProtected = true,
			const BAS::String& name = BAS::NULL_STRING);

		/** Set instrumentation probe value
		 * @param value new probe value
		 * @param name name of the instrumentation probe to be set
		 * @return true if successful
		 */
		bool setValue(
			const BAS::String& value,
			const BAS::String& name = BAS::NULL_STRING);

		/** Get instrumentation probe object
		 * @param probeObj probe object to be returned to
		 * @param name name of the instrumentation probe to be returned
		 * @return true if successful
		 */
		bool getProbe(
			BAS::InstrumentationProbe*& probeObj,
			const BAS::String& name = BAS::NULL_STRING);
		//@}

		// Our friend output operator
		friend std::ostream& operator<<(std::ostream& os,
			const InstrumentationProbeAttribute& attributeProbe);
        private:
		// Hide
		InstrumentationProbeAttribute();
		InstrumentationProbeAttribute(const InstrumentationProbeAttribute& i);
		const InstrumentationProbeAttribute& operator=(
			const InstrumentationProbeAttribute& i);

		/** Instrumentation probe value for this object. */
		BAS::OnlyPointer<InstrumentationProbeValueIf> valueM;
	};

	std::ostream&
        operator<<(std::ostream& os, const InstrumentationProbeAttribute& attributeProbe);
}
#endif
