#ifndef BAS_DBINTEGER_HPP
#define BAS_DBINTEGER_HPP


//=============================================================================
//
// Copyright (c) 2005, 2023, Oracle and/or its affiliates.
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS::DBInteger
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 08-Apr-2005  rtang               PRSF00162240 - add DBInteger datatype
//
//==============================================================================
#ifndef RW_TOOLS_TOOLDEFS_H
  #include <rw/tooldefs.h>
#endif
#ifndef __RWDECPORT_DBTOOLS_H__
  #include <rw/db/decport.h>
#endif
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif

/** This does not define a class -- this is a work around solution to support 
 *  Windows IA-64 and Unix 32-bit platform, as RW DB library does not support __int64 and long long.
 *  We need to revisit the code when moving to RW8, as RW claims they will support __int64 in edition 8.
 */

#if RWTOOLS <= 0x23010000
#if defined (HAS_LONGLONG)
  typedef int64 DBInteger;
#else
  typedef RWDecimalPortable DBInteger;
#endif
#endif


namespace BAS {

	/** Convert a DBInteger value to int64.
	 *  @param	dval	The DBInteger value to convert.
	 *  @return	The equivalent int64 value.
	 */
	const int64 toInt64(const DBInteger& dval);
	const int64 fromDecimalPortable(const RWDecimalPortable& dval);

	/** Convert an int64 value to DBInteger.
	 *  @param	ival	The int64 value to convert.
	 *  @return	The equivalent DBInteger value.
	 */
	const DBInteger toDBInteger(const int64 ival);
	const RWDecimalPortable toDecimalPortable(const int64 ival);

    /** Method to convert an int64 value to its DBInteger equivalent. */
	inline const DBInteger
	toDBInteger(const int64 ival)
    {
	#if defined (HAS_LONGLONG)
		return ival;
	#else
		return toDecimalPortable(ival);
	#endif
	}
	/** Method to convert a DBInteger value to its int64 equivalent. */
	inline const int64
	toInt64(const DBInteger& dval)
	{
	#if defined (HAS_LONGLONG)
		return dval;
	#else   
		return fromDecimalPortable(dval);
	#endif
	}
}

#endif // BAS_DBINTEGER_HPP
