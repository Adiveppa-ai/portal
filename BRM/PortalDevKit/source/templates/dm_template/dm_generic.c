/*******************************************************************
 *
 * Copyright (c) 2000, 2023, Oracle and/or its affiliates. 
 * 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 *******************************************************************/

/***********************************************************
 *   dm_generic.c                                            *
 ***********************************************************/


#ifndef lint
static char   Sccs_id[] = "@(#)dm_generic.c";
#endif

#ifndef PIN_MALLOC
#define PIN_MALLOC
#endif

#include <stdio.h>
#include "pinlog.h"
#include "pin_errs.h"
#include "pcm.h"
#include "dm_sm.h"
#include "dm_debug.h"

/*********************************************************
 *    dm_if_init_process()                               *
 *    This routine starts the initial process            *
 *
 *********************************************************/

PIN_EXPORT void
dm_if_init_process(struct dm_sm_config *confp, u_int *errp)
{
	
	*errp = PIN_ERR_NONE;

	return;
}

/***********************************************************
 * dm_if_process_op()                                      *
 * This routine processes an operation that comes from     *
 * the cm                                                  *
 ***********************************************************/
PIN_EXPORT void
dm_if_process_op(struct dm_sm_info *dsip,
				u_int		pcm_op,
				u_int		pcm_flags,
				pin_flist_t	*in_flistp,
				pin_flist_t	**out_flistpp,
				pin_errbuf_t	*ebufp)
{ 
    void   *vp  = NULL;
    if (PIN_ERR_IS_ERR(ebufp))
		return;
	PIN_ERR_CLEAR_ERR(ebufp);

	/***********************************************************
	 * Copy the flist back.
	 ***********************************************************/
	*out_flistpp = PIN_FLIST_COPY(in_flistp, ebufp);

	/***********************************************************
	 * Log something so we know we got called.
	 ***********************************************************/
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		"dm_if_process_op return flist", *out_flistpp);

	/***********************************************************
	 * Check for error
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {
		PIN_ERR_LOG_EBUF( PIN_ERR_LEVEL_ERROR,
			"dm_if_process_op error", ebufp);
	}

	return;
}

/*******************************************************************
 * dm_if_terminate_connect():
 *
 *	This routine is called to clean up the CM connection
 *
 *******************************************************************/
PIN_EXPORT void
dm_if_terminate_connect(struct dm_sm_info *dsip,
    u_int *errp)
{
	if (dsip->pvti != 0) {

		/* abort transaction */

		dsip->pvti = 0;
	}

	*errp = PIN_ERR_NONE;

	return;
}

/*******************************************************************
 * dm_if_terminate_process():
 *
 *	This routine is called when the DM is terminated.
 *
 *******************************************************************/
PIN_EXPORT void
dm_if_terminate_process(u_int *errp)
{
	/*
	 * NOOP for now
	 */
	*errp = PIN_ERR_NONE;

	return;
}




   

