/*	
 *	@(#)%Portal Version: fm_utils_gal.h:CommonIncludeInt:2:2006-Sep-11 05:23:26 %
 *	
 *	Copyright (c) 1996 - 2006 Oracle. All rights reserved.
 *	
 *	This material is the confidential property of Oracle Corporation or its
 *	licensors and may be used, reproduced, stored or transmitted only in
 *	accordance with a valid Oracle license or sublicense agreement.
 */

#ifndef _FM_UTILS_GAL_H_
#define _FM_UTILS_GAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <pcm.h>
#include <cm_fm.h>
#include <pin_errs.h>
#include <pinlog.h>


#include "cm_cache.h"

#ifdef WIN32
#ifdef FM_UTILS_DLL
#define EXTERN __declspec(dllexport)
#else
#define EXTERN __declspec(dllimport)
#endif
#else
#define EXTERN extern
#endif


/*
 * Constants
 */


#ifdef _DEBUG
#define _UTILS_GAL_DEBUG
#endif


/*
 * Prototypes
 */

EXTERN
void
fm_utils_gal_profiles_get_filter_list(
	pcm_context_t	*ctxp,
	poid_t		*profile_poidp,
	pin_flist_t	**r_flistpp,
	int		mode,
	pin_errbuf_t	*ebufp);

EXTERN
void
fm_utils_gal_profiles_read_profile_obj(
	pcm_context_t	*ctxp, 
	cm_cache_t	*cachep, 
	poid_t		*profile_poidp,
	pin_flist_t	**r_flpp,
	pin_errbuf_t	*ebufp);

EXTERN
void
fm_utils_gal_passwd_find_password(
	pcm_context_t	*ctxp, 
	pin_flist_t	*i_flistp, 
	pin_errbuf_t	*ebufp);

#undef EXTERN

#ifdef __cplusplus
}
#endif

#endif
