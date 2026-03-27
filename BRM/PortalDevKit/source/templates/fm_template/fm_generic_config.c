/* Continuus file information --- %full_filespec: fm_generic_config.c~2:csrc:2 % */
/************************************************************************
 *
 * @(#)fm_generic_config.c 
 *
 * Copyright (c) 2000, 2023, Oracle and/or its affiliates. 
 *  
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ************************************************************************/



/******************************************************
 This file creates an opcode-to-function mapping      *
*******************************************************/

#include <stdio.h>	
#include "pcm.h"
#include "cm_fm.h"
#include "op_define.h"



/*******************************************************************
 *******************************************************************/
struct cm_fm_config fm_generic_config[] = {
	/* opcode as a u_int, function name (as a string) */
	{ PCM_OP_GENERIC,	"op_generic" },
	{ 0,	(char *)0 }
};


