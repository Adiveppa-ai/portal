#ifndef BAS_HELPERS_HPP
#define BAS_HELPERS_HPP

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
// Component: BAS::Helpers
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Keshav Subramanya
// Backup-Responsible: Ming-Wen Sung
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 07-Jan-2004  Keshav Subramanya   PRSF00083957 - initial version. 
// 14-Jan-2004  Keshav Subramanya   PRSF00086489 - int64 <-> RWDecimalPortable
// 20-Jan-2004  Keshav Subramanya   PRSF00087960 - moved from DOC to BAS modules
// 05-Apr-2005  rtang               PRSF00162240 - move RWDecimalPortable related 
//                                                 api to db/DBInteger
//
//==============================================================================

//#include <rw/db/decport.h>
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif
#ifndef BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif


/** This does not define a class -- it simply defines a set of functions
 *  that behave like static C functions.  Classes that can get a pointer to
 *  a valid registered object can include this header and proceed to write
 *  messages to the pipeline log - they don't need to *be* registered objects.
 */
namespace BAS {

	/** Write to the pipeline log.
	 *  This is like a static C function -- it is not a class or within a class.
	 *  @param	rObjPtr		Pointer to a registered object.  This method does
	 *						nothing if the pointer is NULL.
	 *  @param	message		What to write into the pipeline log.
	 */
	void writeToPipelineLog(const BAS::RegisteredObject*	rObjPtr,
							const BAS::Status&				message);

	/** Write to the pipeline log.
	 *  This is like a static C function -- it is not a class or within a class.
	 *  @param	rObjPtr		Pointer to a registered object.  This method does
	 *						nothing if the pointer is NULL.
	 *  @param	error		The error identifier.
	 *  @param	severity	The severity of the error.
	 */
	void writeToPipelineLog(const BAS::RegisteredObject*	rObjPtr,
							const BAS::String&				error,
							const BAS::Status::Severity		severity);

	/** Write to the pipeline log.
	 *  This is like a static C function -- it is not a class or within a class.
	 *  @param	rObjPtr		Pointer to a registered object.  This method does
	 *						nothing if the pointer is NULL.
	 *  @param	error		The error identifier.
	 *  @param	severity	The severity of the error.
	 *  @param	argument	Value for single error message argument.
	 */
	void writeToPipelineLog(const BAS::RegisteredObject*	rObjPtr,
							const BAS::String&				error,
							const BAS::Status::Severity		severity,
							const BAS::String&				argument);

	/** Write to the pipeline log.
	 *  This is like a static C function -- it is not a class or within a class.
	 *  @param	rObjPtr		Pointer to a registered object.  This method does
	 *						nothing if the pointer is NULL.
	 *  @param	error		The error identifier.
	 *  @param	severity	The severity of the error.
	 *  @param	arguments	Values for multiple error message arguments.
	 */
	void writeToPipelineLog(const BAS::RegisteredObject*	rObjPtr,
							const BAS::String&				error,
							const BAS::Status::Severity		severity,
							const BAS::StringList&			arguments);
#if 0
	/** Convert a RWDecimalPortable value to int64.
	 *  @param	dval		The RWDecimalPortable value to convert.
	 *  @return	The equivalent int64 value.
	 */
	const int64 toInt64(const RWDecimalPortable& dval);

	/** Convert an int64 value to RWDecimalPortable.
	 *  @param	ival		The int64 value to convert.
	 *  @return	The equivalent RWDecimalPortable value.
	 */
	const RWDecimalPortable toPortableDecimal(const int64 ival);
#endif
}

#endif // BAS_HELPERS_HPP
