/*	
 *	@(#)%Portal Version: pin_wireless.h:CommonIncludeInt:2:2006-Sep-11 05:25:13 %
 *	
 *	Copyright (c) 1996 - 2006 Oracle. All rights reserved.
 *	
 *	This material is the confidential property of Oracle Corporation or its
 *	licensors and may be used, reproduced, stored or transmitted only in
 *	accordance with a valid Oracle license or sublicense agreement.
 */

#ifndef _PIN_WIRELESS_H
#define	_PIN_WIRELESS_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************
 * WAP FM Definitions.
 *******************************************************************/

/* The values below are used in the PIN_FLD_MODE field.
 * This field defines the mode of the filter list for URLs and APNs 
 * The following is a binary bit mask.
 * Allow_Deny is just for convenience. It is an or of ALLOW and DENY
 */

#define         PIN_WIRELESS_MODE_UNDEFINED	0x0000
#define		PIN_WIRELESS_MODE_ALLOW		0x0001
#define		PIN_WIRELESS_MODE_DENY		0x0010
#define		PIN_WIRELESS_MODE_FREE	 	0x0100	


#define         PIN_WIRELESS_MODE_ALLOWED    (PIN_WIRELESS_MODE_ALLOW | PIN_WIRELESS_MODE_DENY )

/* Values for SUCCESS and FAILURE to be returned from
 * authorization opcodes
 */
#define		PIN_WIRELESS_FAILURE		0
#define		PIN_WIRELESS_SUCCESS		1
#ifdef __cplusplus
}
#endif

#endif	/*_PIN_WIRELESS_H*/
