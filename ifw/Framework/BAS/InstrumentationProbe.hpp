// @(#)%Portal Version: InstrumentationProbe.hpp:RWSmod7.3.1Int:1:2007-Sep-12 04:45:05 %
#ifndef BAS_INSTRUMENTATION_PROBE_H
#define BAS_INSTRUMENTATION_PROBE_H

//=============================================================================
//
// Copyright (c) 2004, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//
// This material is the confidential property of Oracle Corporation or
// its licensors and may be used, reproduced, stored or transmitted only
// in accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Instrumentation probe abstract class
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
// 22-May-2006  Ming-Wen Sung       CO214066 - support 'BigTable' probe type
// 23-Oct-2006  Ming-Wen Sung       CO236127 - add getValueWithoutLock() API
//
//=============================================================================


#ifndef RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

using std::less;

namespace BAS
{


	/** <b>InstrumentationProbe</b> is an abstract class.  It is the base
	 * class for all instrumentation probe classes.  It defines getValue(),
	 * setValue(), and getProbe() interface functions.  It also priveds
	 * accessor functions to get specific data from probe information,
	 * and accessor function for probe level.
	 */
	class InstrumentationProbe  D_THREADINFO
	{
		D_NONTHREADSAFE

	public:
		/** Default instrumentation level */
		BAS_EXPORT static const int defaultLevelCM = 1;

		/** Instrumentation level currently set */
		BAS_EXPORT static int levelCM;

		/** String representation for mode value */
		BAS_EXPORT static const BAS::String modeStrCM[];

		/** String representation for type values */
		BAS_EXPORT static const BAS::String typeStrCM[];

		/** Path that has all probe info files */
		BAS_EXPORT static BAS::String probeInfoPathCM;

		/** Mode for the value in this instrumentation probe object
		 * Available modes are: NotSpecified, Read-Only, Read-Wrte,
		 * and Write-Only
		 * For Read-Only and Read-Write, it returns instrumentation
		 * probe value when getValue(...) is called.
		 * For Read-Write and Write-Only, it allows user to set
		 * the instrumentation probe value.
		 */
		typedef enum
		{
			NotSpecified = 0,
			ReadOnly,
			ReadWrite,
			WriteOnly,
			UnknownMode
		} InstrumentationProbeMode;

		/** Probe type for the value in this instrumentation probe object
		 * Available probe types are: AttributeIntegerValue, AttributeStringValue,
		 * List, Group, Table, and BigTable.
		 * The probe type must be matched with Instrumentation Probe class
		 * used to store the value
		 */
		typedef enum
		{
			Integer = 0,
			String,
			List,
			Group,
			Table,
			BigTable,
			UnknownType
		} InstrumentationProbeType;

		/** Structure to define a component.  The information includes
		 * idM - component id
		 * nameM - component name
		 */
		typedef struct
		{
			int32 idM;
			BAS::String nameM;
		} ComponentInfo;

		/** Structure to define a module.  The information includes
		 * idM - module id
		 * nameM - module name
		 * componentM - component name this module belongs to
		 */
		typedef struct
		{
			int32 idM;
			BAS::String nameM;
			BAS::String componentM;
		} ModuleInfo;

		/** Structure to define a probe.  The information includes
		 * idM - probe id
		 * nameM - probe name 
		 * descriptionM - description for this probe
		 * modeM - access mode (one of them in InstrumentationProbeMode)
		 * typeM - probe type (one of them in InsrumentationProbeType)
		 * unitM - unit (optional)
		 * parentM - parent of this probe.  It could be a module name
		 *          or name of the parent probe
		 */
		typedef struct
		{
			int32 idM;
			BAS::String nameM;
			BAS::String descriptionM;
			InstrumentationProbeMode modeM;
			InstrumentationProbeType typeM;
			BAS::String unitM;
			BAS::String parentM;
		} ProbeInfo;

		/** A map that stored component info */
		typedef RWTValMap <BAS::String, ComponentInfo, less<BAS::String> > ComponentInfoMap;

		/** A map that stored module info */
		typedef RWTValMap <BAS::String, ModuleInfo, less<BAS::String> > ModuleInfoMap;

		/** A map that stored probe info */
		typedef RWTValMap <BAS::String, ProbeInfo, less<BAS::String> > ProbeInfoMap;

		/** Standard constructor
		 * @param name the name of the registered object to construct
		 * @param level instrumentation level
		 */
		InstrumentationProbe(
			const ProbeInfo& probeInfo,
			const int level = defaultLevelCM);

		/** Destructor.
		 */
		virtual ~InstrumentationProbe();

		/** Read all component info defined in the component file
		 * @param filename component info file name
		 * @param componentInfoMap has all component info added in this
		 *        ComponentInfoMap container
		 * @return true if successful
		 */
		static bool ReadComponentInfoFile(
			const BAS::String& filename,
			ComponentInfoMap& componentInfoMap);

		/** Read all module info defined in the module file
		 * @param filename module info file name
		 * @parem moduleInfoMap has all module info added in this 
		 *        ModuleInfoMap container
		 * @return true if successful
		 */
		static bool ReadModuleInfoFile(
			const BAS::String& filename,
			ModuleInfoMap& moduleInfoMap);

		/** Read all probe info defined in the probe file
		 * @param filename probe info file name
		 * @param probeInfoMap has all probe info added to this ProbeInfoMap
		 *        container
		 * @return true if successful
		 */
		static bool ReadProbeInfoFile(
			const BAS::String& filename,
			ProbeInfoMap& probeInfoMap);

		/** Read a valid component, module, or probe info line from
		 * the input stream.
		 * @param is the input stream
		 * @return the a valid info line that is not a comment line or
		 * an emptry line
		 */
		static BAS::String ReadLine(std::istream& is);

		/** @name InstrumentationProbe interface. */
		//@{
		/** Get instrumentation probe value
		 * @param value value to be returned to
		 * @param lockProtected the flag indicates to get the value
		 * that is protected by a lock if there is any
		 * @param name name of the instrumentation probe to be returned
		 * @return true if successful
		 */
		virtual bool getValue(
			BAS::String& value,
			bool lockProtected = true,
			const BAS::String& name = BAS::NULL_STRING) = 0;

		/** Set instrumentation probe value by name
		 * @param value the new value
		 * @param name name of instrumentation probe to be set
		 * @return true if successful
		 */
		virtual bool setValue(
			const BAS::String& value,
			const BAS::String& name = BAS::NULL_STRING) = 0;

		/** Get instrumentation probe object
		 * @param probeObj probe object to be returned to
		 * @param name name of the instrumentation probe to be returned
		 * @return true if successful
		 */
		virtual bool getProbe(
			InstrumentationProbe*& probeObj,
			const BAS::String& name = BAS::NULL_STRING) = 0;
		//@}

		/** @name other public methods. */
		//@{
		/** Get id for this instrumentation probe object
		 * @return id for this instrumentation probe object
		 */
		int getId() const;

		/** Get name for this instrumentation probe object
		 * @return name for this instrumentation probe object
		 */
		virtual BAS::String getName() const;

		/** Get description for this instrumentation probe object
		 * @return description for this instrumentation probe object
		 */
		BAS::String getDescription() const;

		/** Get access mode for this instrumentation probe object
		 * @return access mode for this instrumentation probe object
		 */
		InstrumentationProbeMode getMode() const;

		/** Get probe type for this instrumentation probe object
		 * @return probe type for this instrumentation probe object
		 */
		InstrumentationProbeType getType() const;

		/** Get unit name for this instrumentation probe object
		 * @return unit name for this instrumentation probe object
		 */
		BAS::String getUnit() const;

		/** Get parent name for this instrumentation probe object
		 * @return parent name type for this instrumentation probe object
		 */
		BAS::String getParent() const;

		/** Get probe level
		 * @return probe level
		 */
		int getLevel() const;

		/** Equality operator this is based on name
		 * @param rVal InstrumentationProbe object to be compared to
		 * @return true if names are equal, false otherwise
		 */
		bool operator==(const InstrumentationProbe& rVal) const;

		/** Less than operator this is based on name
		 * @param rVal InstrumentationProbe object to be compared to
		 * @return true if this object is than rVal
		 */
		bool operator<(const InstrumentationProbe& rVal) const;
		//@}

		/**@name Related Global Operators
		//@{
		* Output operator for InstrumentationProbeMode enum */
		friend std::ostream& operator<<(std::ostream& os,
			const InstrumentationProbeMode& mode);

		/** Input operator for InstrumentationProbeMode enum */
		friend std::istream& operator>>(std::istream& is,
			InstrumentationProbeMode& mode);

		/** Output operator for InstrumentationProbeType enum */
		friend std::ostream& operator<<(std::ostream& os,
			const InstrumentationProbeType& type);

		/** Input operator for InstrumentationProbeType enum */
		friend std::istream& operator>>(std::istream& is,
			InstrumentationProbeType& type);

		/** Output operator for ComponentInfo struct */
		friend std::ostream& operator<<(std::ostream& os,
			const ComponentInfo& componentInfo);

		/** Input operator for ComponentInfo struct */
		friend std::istream& operator>>(std::istream& is,
			ComponentInfo& componentInfo);

		/** Output operator for ModuleInfo struct */
		friend std::ostream& operator<<(std::ostream& os,
			const ModuleInfo& moduleInfo);

		/** Input operator for ModuleInfo struct */
		friend std::istream& operator>>(std::istream& is,
			ModuleInfo& moduleInfo);

		/** Output operator for ProbeInfo struct */
		friend std::ostream& operator<<(std::ostream& os,
			const ProbeInfo& probeInfo);

		/** Input operator for ProbeInfo struct */
		friend std::istream& operator>>(std::istream& is,
			ProbeInfo& probeInfo);
		//@}

        private:
		// Hide
		InstrumentationProbe();
		InstrumentationProbe(const InstrumentationProbe& i);
		const InstrumentationProbe& operator=(const InstrumentationProbe& i);

		// The following constants used for parsing the
		// component, module, and probe info files
		BAS_EXPORT static const char separatorCM;
		BAS_EXPORT static const char commentCM;

		/** Name for this instrumentation probe object */
		ProbeInfo probeInfoM;

		/** Instrumentation level for this instrumentation probe object */
		int levelM;
	};

//------------------------------------------------------------------------------
// Operator equal-to (==)
//------------------------------------------------------------------------------

inline bool
InstrumentationProbe::operator==(const InstrumentationProbe& rVal) const
{
	return (this->getName() == rVal.getName());
}

//------------------------------------------------------------------------------
// Operator less-than (<)
//------------------------------------------------------------------------------

inline bool
InstrumentationProbe::operator<(const InstrumentationProbe& rVal) const
{
	return (this->getName() < rVal.getName());
}

inline int32
InstrumentationProbe::getId() const
{
	return probeInfoM.idM;
}

inline BAS::String
InstrumentationProbe::getName() const
{
	return probeInfoM.nameM;
}

inline BAS::String
InstrumentationProbe::getDescription() const
{
	return probeInfoM.descriptionM;
}

inline InstrumentationProbe::InstrumentationProbeMode
InstrumentationProbe::getMode() const
{
	return probeInfoM.modeM;
}

inline InstrumentationProbe::InstrumentationProbeType
InstrumentationProbe::getType() const
{
	return probeInfoM.typeM;
}

inline BAS::String
InstrumentationProbe::getUnit() const
{
	return probeInfoM.unitM;
}

inline BAS::String
InstrumentationProbe::getParent() const
{
	return probeInfoM.parentM;
}

inline int
InstrumentationProbe::getLevel() const
{
	return levelM;
}

std::ostream&
operator<<(std::ostream& os, const InstrumentationProbe::InstrumentationProbeMode& mode);

std::istream&
operator>>(std::istream& is, InstrumentationProbe::InstrumentationProbeMode& mode);

std::ostream&
operator<<(std::ostream& os, const InstrumentationProbe::InstrumentationProbeType& type);

std::istream&
operator>>(std::istream& is, InstrumentationProbe::InstrumentationProbeType& type);

std::ostream&
operator<<(std::ostream& os, const InstrumentationProbe::ComponentInfo& componentInfo);

std::istream&
operator>>(std::istream& is, InstrumentationProbe::ComponentInfo& componentInfo);

std::ostream&
operator<<(std::ostream& os, const InstrumentationProbe::ModuleInfo& moduleInfo);

std::istream&
operator>>(std::istream& is, InstrumentationProbe::ModuleInfo& moduleInfo);

std::ostream&
operator<<(std::ostream& os, const InstrumentationProbe::ProbeInfo& probeInfo);

std::istream&
operator>>(std::istream& is, InstrumentationProbe::ProbeInfo& probeInfo);

std::ostream&
operator<<(std::ostream& os, const InstrumentationProbe::ModuleInfo& moduleInfo);

std::istream&
operator>>(std::istream& is, InstrumentationProbe::ModuleInfo& moduleInfo);
}

#endif
