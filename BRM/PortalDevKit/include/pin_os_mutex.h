#ifndef _pin_os_mutex_h_
#define _pin_os_mutex_h_
/*
 *	@(#)%Portal Version: pin_os_mutex.h:PlatformR2Int:2:2006-Sep-12 03:30:27 %
 *      
 *      Copyright (c) 1996 - 2023, Oracle and/or its affiliates.
 *      
 *      This material is the confidential property of Oracle Corporation or its
 *      licensors and may be used, reproduced, stored or transmitted only in
 *      accordance with a valid Oracle license or sublicense agreement.
 */

/* All OSs must define:
 *   PTHREAD_MUTEXATTR_DEFAULT
 *   PTHREAD_CONDATTR_DEFAULT
 *   PTHREAD_ATTR_DEFAULT
 *
 * Which are the default attributes to use when initialising/creating
 * mutexes, conds and threads respectively.
 */


  #include <pthread.h>

  #define PTHREAD_MUTEXATTR_DEFAULT 0
  #define PTHREAD_CONDATTR_DEFAULT 0
  #define PTHREAD_ATTR_DEFAULT 0


#endif

