/*
 *      @(#) % %
 *    
 *      Copyright (c) 1996 - 2024 Oracle.
 *    
 *      This material is the confidential property of Oracle Corporation or its
 *      licensors and may be used, reproduced, stored or transmitted only in
 *      accordance with a valid Oracle license or sublicense agreement.
 */


#ifndef CM_CACHE_H
#define CM_CACHE_H

#undef EXTERN
#ifdef __CMPIN__ 
#define EXTERN PIN_EXPORT 
#else
#define EXTERN PIN_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 * define cache key types
 */
#define CM_CACHE_KEY_STR	1
#define CM_CACHE_KEY_POID	2
#define CM_CACHE_KEY_IDDBSTR	3

/* for cache key of ..._STR, use null terminated char string as key. */
/* for cache key of ..._POID, only use id and db as key. */
typedef struct cm_cache_key_poid {
	int64	id;
	int64	db;
} cm_cache_key_poid_t;

/* for cache key of ..._IDDBSTR, only (poid) id and db + string as key. */
typedef struct cm_cache_key_iddbstr {
	int64	id;
	int64	db;
	char	*str;
} cm_cache_key_iddbstr_t;


typedef void *cm_cache_t;

/*
 * call at init time, specified via fm_module in CM pin.conf
 */
EXTERN cm_cache_t * 
cm_cache_init(char *name,	/* a name, for statistics print mostly */
	int32 n_ents,		/* number of entries to allow */
	int32 size,		/* size of data memory */
	int32 hash_modulus,	/* number of hash buckets */
	int32 keytype,		/* CM_CACHE_KEY_xxx the key type */
	int32 *errp);		/* PIN_ERR_xxx */

EXTERN cm_cache_t *
cm_cache_init_byname(char *name,   /* the name for the cache */
                     int32 keytype, /* CM_CACHE_KEY_xxx the key type */
                     int32 *errp); /* PIN_ERR_xxx */

EXTERN cm_cache_t *
cm_cache_init_by_flist(
                char            *name,		/* the name for the cache */
                pin_flist_t     *in_flistp,	/* The flist of data to cache */
                pin_fld_num_t   field,		/* name of field from which */
						/* to get the CM_CACHE_KEY_xx */
						/* the key type */
                int32           hash_modulus,	/* number of hash buckets */
						/* <= to zero means same as */
						/* number of PIN_FLD_RESULTS */
                int32           *errp );	/* PIN_ERR_xxx */
EXTERN void
cm_cache_re_init_by_flist(
		cm_cache_t      *cachep,
		pin_flist_t     *in_flistp,     /* The flist of data to cache */
		pin_fld_num_t   field,          /* name of field from which */
						/* to get the CM_CACHE_KEY_xx */
						/* the key type */
		int32           *errp );        /* PIN_ERR_xxx */

/* This function will initialize a CM cache and copy the past flist
 * into it.
 * Returns PIN_ERR_xxx
 */
EXTERN int32 cm_cache_init_and_copy_flist(
	pin_flist_t*      in_flistp,       /* input flist */
	char*             cache_name,      /* cache name */
	cm_cache_t**      cachepp,         /* return ptr to created cache */
	pin_flist_t**     out_flistpp);     /* return ptr to flist in the cache */

/*
 * call to find an entry.
 * returns ptr to flist (read only please!), else NULL if not found or error.
 * *errp set to PIN_ERR_NONE if found, else PIN_ERR_xxx
 */
EXTERN pin_flist_t *
cm_cache_find_entry(cm_cache_t *cachep,
	void *keyvalp,
	int32 *errp);
/*
 * call to execute the provided function on the cache entry whilst holding a read-lock.
 * This returns the return code of the provided function (which MUST be 0 (success) or
 * positive (failure). A negative return value from cm_cache_exec_entry indicates either:
 *
 * The function will be passed:
 *
 *     keytype  - the type of key (CM_CACHE_KEY_STR, CM_CACHE_KEY_POID, CM_CACHE_KEY_IDDBSTR)
 *     keyvalp  - the key itself
 *     flp      - the cache entry flist (it will be NULL if the object is not found in the cache)
 *     inp      - pointer to some input that might be useful to the function
 *     outpp    - pointer to some output area that contains the result of the function execution (if any)
 *
 * The function returns:
 *
 * == 0 - a succesful execution
 *  > 0 - an error in the called function
 *  < 0 - an unexpected error (see errp value):
 *        CM_CACHE_EXEC_ERROR - a failure prevented the function being called.
 *        CM_CACHE_EXEC_BAD_RETURN_VALUE - the called function returned a negative result code.
 *
 */
#define CM_CACHE_EXEC_ERROR             -1
#define CM_CACHE_EXEC_BAD_RETURN_VALUE  -2

EXTERN int
cm_cache_exec_entry(
	cm_cache_t      *in_cachep,
	void            *keyvalp,
	int             (*funcp)(int32 keytype, void *keyvalp, pin_flist_t *flp, void *inp, void **outpp),
	void            *inp,
	void            **outpp,
	int32           *errp);


/*
 * cm_cache_add_entry - used to (try to) add an entry into the hash
 *	list.  checks to see if already there.
 */

EXTERN void
cm_cache_add_entry(cm_cache_t *cachep,
	void	*keyvalp,
	pin_flist_t	*in_flistp,
	int32	*errp);

/*
 * cm_cache_add_entry_post_exec
 *
 * Adds an entry to the cache and invokes the provided function on the stored data.
 * The inp and outpp pointers provide for context information to be provided to the
 * functiona and output to be generated, if required.
 *
 * @param in_cachep   The CM cache opaque pointer
 * @param keyvalp     The key pointer
 * @param funcp       The pointer to the function to execute
 * @param inp         Additional input data the function may need
 * @param outpp       The function output (it is up to the function how this is used)
 * @param errp        The error code
 *
 * @return -1 (CM_CACHE_EXEC_ERROR) if this function fails to execute correctly
 *         -2 (CM_CACHE_EXEC_BAD_RETURN_VALUE) if 'funcp' returns a negative value
 *          0 For successful execution
 *         >0 The return value of the executed function (used to indicate failures)
 */
int
cm_cache_add_entry_post_exec(cm_cache_t *in_cachep,
	void            *keyvalp,
	pin_flist_t     *in_flistp,
	int             (*funcp)(int32 keytype, void *keyvalp, pin_flist_t *flp, void *inp, void **outpp),
	void            *inp,
	void            **outpp,
	int32           *errp);
/*
 * cm_cache_update_entry - used to update an existing entry
 *	in the cache.  If it doesn't exit, this function
 *	will call add_entry.
 */
EXTERN void
cm_cache_update_entry(
	cm_cache_t	*in_cachep,
	void		*keyvalp,
	pin_flist_t	*in_flistp,
	int32		*errp);
/*
 * cm_cache_update_entry_post_exec
 *
 * Updates an entry in the cache and invokes the provided function on the stored data.
 * The inp and outpp pointers provide for context information to be provided to the
 * function and output to be generated, if required.
 *
 * @param in_cachep   The CM cache opaque pointer
 * @param keyvalp     The key pointer
 * @param funcp       The pointer to the function to execute
 * @param inp         Additional input data the function may need
 * @param outpp       The function output (it is up to the function how this is used)
 * @param errp        The error code
 *
 * @return -1 (CM_CACHE_EXEC_ERROR) if this function fails to execute correctly
 *         -2 (CM_CACHE_EXEC_BAD_RETURN_VALUE) if 'funcp' returns a negative value
 *          0 For successful execution
 *         >0 The return value of the executed function (used to indicate failures)
 */
int
cm_cache_update_entry_post_exec(cm_cache_t *in_cachep,
	void            *keyvalp,
	pin_flist_t     *in_flistp,
	int             (*funcp)(int32 keytype, void *keyvalp, pin_flist_t *flp, void *inp, void **outpp),
	void            *inp,
	void            **outpp,
	int32           *errp);

#ifdef __cplusplus
}
#endif

#undef EXTERN

#endif /*CM_CACHE_H*/
