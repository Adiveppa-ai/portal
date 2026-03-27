// @(#)%Portal Version: InstrumentationProbeCollection.hpp:CUPmod7.3PatchInt:1:2006-Nov-17 16:34:00 %
#ifndef BAS_INSTRUMENTATION_PROBE_COLLECTION_H
#define BAS_INSTRUMENTATION_PROBE_COLLECTION_H
//=============================================================================
//
// Copyright (c) 2004 - 2006 Oracle. All rights reserved.
//
// This material is the confidential property of Oracle Corporation or
// its licensors and may be used, reproduced, stored or transmitted only
// in accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	This is the base class for AttributeInstrumentationProbe, 
// GroupInstrumentationProbe, TableInstrumentationProbe, and 
// InstrumentationProbeList classes.  This template class has a singly-linked
// list as the member variable that contains a list of objects (class T) and 
// provides basic functions to maintain the list (e.g. append, begin, end, 
// isEmpty, clear, contains, and entries).  This template class is inherited
// from InstrumentationProbe abstract class, therefore, it also provides
// getValue() and setValue() interface functions to get and set a value of
// the object from the list that matches with the desired name.
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
// 27-Jan-2005  Ming-Wen Sung       Created
// 07-Feb-2006  Ming-Wen Sung       Modified based on design in OMF
// 23-Oct-2006  Ming-Wen Sung       CO236127 - add getValueWithoutLock() API
//
//=============================================================================

#ifndef RW_TOOLS_TVSLIST_H
  #include "rw/tvslist.h"
#endif
#ifndef BAS_INSTRUMENTATION_PROBE_H
  #include "BAS/InstrumentationProbe.hpp"
#endif


namespace BAS
{
	/** <b>InstrumentationProbeCollection</b> is a template class that is 
	 * the base class for AttributeInstrumentationProbe, 
	 * GroupInstrumentationProbe, TableInstrumentationProbe, and 
	 * InstrumentationProbeList classes.  This template class has a singly-linked
	 * list as the member variable that contains a list of objects (class T) and 
	 * provides basic functions to maintain the list (e.g. append, begin, end, 
	 * isEmpty, clear, contains, and entries).  This template class is inherited
	 * from InstrumentationProbe abstract class, therefore, it also provides
	 * getValue() and setValue() interface functions to get and set a value of
	 * the object from the list that matches with the desired name.
	 */
	template<class T> class InstrumentationProbeCollection : 
		public InstrumentationProbe D_THREADINFO
	{
		D_NONTHREADSAFE

        public:

		/** Define iterator instrumentation probe list type */
		typedef typename RWTValSlist<T*>::const_iterator ProbeListConstItr;

		/** Standard constructor
		 * @param name the name of the registered object to construct
		 * @param level instrumentation level
		 */
                InstrumentationProbeCollection(
			const ProbeInfo& probeInfo,
			const int level = defaultLevelCM);

		/** Destructor.
		 */
		virtual ~InstrumentationProbeCollection();

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

		/** Set instrumentation probe value by name
		 * @param value the new value
		 * @param name name of instrumentation probe to be set
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

		/** @name other public methods. */
		//@{
		/** Appends the object to list
		 * @param InstrumentationProbe object to append
		 */
		void append(T* probe);

		/** Removes an object from the list
		 * @param Instrumentation object to be removed
		 */
		bool remove(T* probe);

		/** Get the iterator pointing to the start
		 */
		ProbeListConstItr begin() const;

		/** Get the iterator's end
		 */
		ProbeListConstItr end() const;

		/** Tells if this list is empty
		 */
		bool isEmpty() const;

		/** clears the list
		 * clears the list, does not delete the objects 
		 */
		void clear();

		/** clears the list and destroys obejcts also
		 */
		void clearAndDestroy();

		/** Indicates if the list contains the specified object
		 */
		bool contains(const T*) const;
        
		/** Number of entries in this list object
		 * @return number of entries in this list object
		 */
		int entries() const;
		//@}

		/** @name other global methods. */
		//@{
		// the friend output operator
		friend std::ostream& operator<<(std::ostream& os,
			const BAS::InstrumentationProbeCollection<T>& listProbe)
		{
			os << BAS::InstrumentationProbe::typeStrCM[listProbe.getType()] <<
				": " << listProbe.getName() << endl;
			typename BAS::InstrumentationProbeCollection<T>::ProbeListConstItr itr = 
				listProbe.begin();
			typename BAS::InstrumentationProbeCollection<T>::ProbeListConstItr itrEnd = 
				listProbe.end();
			for (; itr != itrEnd; itr++)
			{
				os << *(*itr);
			}

			return os;
		}
		//@}

        private:
		// Hide
		InstrumentationProbeCollection();
		InstrumentationProbeCollection(const InstrumentationProbeCollection& i);
		const InstrumentationProbeCollection& operator=(
			const InstrumentationProbeCollection& i);

		/** Define instrumentation probe list type */
		typedef RWTValSlist<T*> ProbeList;

		/** A collection of instrumentation probe objects */
		ProbeList probeListM;
	};

//----------------------------------------------------------------------------------
// Append the object to the list
//----------------------------------------------------------------------------------
template<class T>
inline void
InstrumentationProbeCollection<T>::append(T* probe)
{
	probeListM.append(probe);
}
//----------------------------------------------------------------------------------
// Remove the object from the list
//----------------------------------------------------------------------------------
template<class T>
inline bool
InstrumentationProbeCollection<T>::remove(T* probe)
{
	return probeListM.remove(probe);
}
//----------------------------------------------------------------------------------
// get the iterator 
//----------------------------------------------------------------------------------
template<class T>
inline typename InstrumentationProbeCollection<T>::ProbeListConstItr
InstrumentationProbeCollection<T>::begin() const
{
	return probeListM.begin();
}
//----------------------------------------------------------------------------------
// get to the end of the iterator 
//----------------------------------------------------------------------------------
template<class T>
inline typename InstrumentationProbeCollection<T>::ProbeListConstItr
InstrumentationProbeCollection<T>::end() const
{
	return probeListM.end();
}
//----------------------------------------------------------------------------------
// is it empty ?
//----------------------------------------------------------------------------------
template<class T>
inline bool
InstrumentationProbeCollection<T>::isEmpty() const
{
	return probeListM.isEmpty();
}
//----------------------------------------------------------------------------------
// clear all values
//----------------------------------------------------------------------------------
template<class T>
inline void
InstrumentationProbeCollection<T>::clear()
{
	probeListM.clear();
}
//----------------------------------------------------------------------------------
// clear all values and destroy the probe as well
//----------------------------------------------------------------------------------
template<class T>
inline void
InstrumentationProbeCollection<T>::clearAndDestroy()
{
	ProbeListConstItr it = probeListM.begin();
	ProbeListConstItr itEnd = probeListM.end();
	for (; it != itEnd; it++)
	{
		delete (*it);
	}
	probeListM.clear();
}
//----------------------------------------------------------------------------------
// indicate if the list contains the probe object
//----------------------------------------------------------------------------------
template<class T>
inline bool
InstrumentationProbeCollection<T>::contains(const T* probe) const
{
	return probeListM.contains(probe);
}
//----------------------------------------------------------------------------------
// clear all values and destroy the probe as well
//----------------------------------------------------------------------------------
template<class T>
inline int
InstrumentationProbeCollection<T>::entries() const
{
	return probeListM.entries();
}

}

#ifdef INC_TEMPL_DEFS
#include "BAS/InstrumentationProbeCollection.cpp"
#endif

#endif
