/* Continuus file information --- %full_filespec: fm_generic_opcode.c~2:csrc:2 % */
/***********************************************************************
 *
 * @(#)fm_generic_opcode.c 
 *
 * Copyright (c) 2000, 2024, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation or its
 *  licensors and may be used, reproduced, stored or transmitted only in
 *  accordance with a valid Oracle license or sublicense agreement.
 *
 ***********************************************************************/

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "pcm.h"
#include "cm_fm.h"
#include "pin_errs.h"
#include "pinlog.h"
#include "pin_cust.h"
#include "op_define.h"



#define FILE_SOURCE_ID  "fm_generic_opcode"

/*******************************************************************
 * Routines contained herein.
 *******************************************************************/
EXPORT_OP void
op_generic(
        cm_nap_connection_t	*connp,
	u_int			opcode,
        u_int			flags,
        pin_flist_t		*in_flistp,
        pin_flist_t		**ret_flistpp,
        pin_errbuf_t		*ebufp);

static void
fm_generic_opcode(
	pcm_context_t		*ctxp,
	pin_flist_t		*in_flistp,
	pin_flist_t		**out_flistpp,
        pin_errbuf_t		*ebufp);

/*******************************************************************
 * Main routine for the PCM_OP_GENERIC  command
 *******************************************************************/
void
op_generic(
        cm_nap_connection_t	*connp,
	u_int			opcode,
        u_int			flags,
        pin_flist_t		*in_flistp,
        pin_flist_t		**ret_flistpp,
        pin_errbuf_t		*ebufp)
{
	pcm_context_t		*ctxp = connp->dm_ctx;
	pin_flist_t		*r_flistp = NULL;

	/***********************************************************
	* Null out results until we have some.
	***********************************************************/
	*ret_flistpp = NULL;
	PIN_ERR_CLEAR_ERR(ebufp);

	/***********************************************************
        * Error out in case opcode is not PCM_OP_GENERIC
	***********************************************************/
	if (opcode != PCM_OP_GENERIC) {
     	   pin_set_err(ebufp, PIN_ERRLOC_FM,
			PIN_ERRCLASS_SYSTEM_DETERMINATE,
			PIN_ERR_BAD_OPCODE, 0, 0, opcode);
		        PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"bad opcode in op_generic", ebufp);
           return;
	}

	/***********************************************************
        * Debug what we got.
        ***********************************************************/
        PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
                "op_generic input flist", in_flistp);


	/***********************************************************
	 * Call main function to do it
	 ***********************************************************/
	fm_generic_opcode(ctxp, in_flistp, &r_flistp, ebufp);

	/***********************************************************
	 * Results.
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {
              *ret_flistpp = (pin_flist_t *)NULL;
	      PIN_FLIST_DESTROY_EX(&r_flistp, NULL);
	      PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
		        	"op_generic error", ebufp);
	} else {
	      *ret_flistpp = r_flistp;
	      PIN_ERR_CLEAR_ERR(ebufp);
	      PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		        	"op_generic return flist", r_flistp);
	}

	return;
}

/*******************************************************************
 * fm_generic_opcode()
 * You can add your code here
 *	
 *
 *******************************************************************/
static void
fm_generic_opcode(
	pcm_context_t		*ctxp,
	pin_flist_t		*in_flistp,
	pin_flist_t		**out_flistpp,
        pin_errbuf_t		*ebufp)
{

	if (PIN_ERR_IS_ERR(ebufp))
		return;
	PIN_ERR_CLEAR_ERR(ebufp);

	/**********************************************************
	 * Copies the input flist to outgoing flist               *
	 *********************************************************/

	*out_flistpp = PIN_FLIST_COPY(in_flistp, ebufp);

	/***********************************************************
	 * Error?
	 ***********************************************************/
 	if (PIN_ERR_IS_ERR(ebufp)) {
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"fm_generic_opcode error", ebufp);
	}

	return;
}
