/*
 *	@(#)%Portal Version: pin_os_thread.h:RWSmod7.3.1Int:1:2007-Sep-12 04:45:35 %
 *      
 *      Copyright (c) 1996 - 2023, Oracle and/or its affiliates.
 *      
 *      This material is the confidential property of Oracle Corporation or its
 *      licensors and may be used, reproduced, stored or transmitted only in
 *      accordance with a valid Oracle license or sublicense agreement.
 */

#ifndef _pin_os_thread_h_
#define _pin_os_thread_h_

#ifndef _pin_os_types_h_
  #include <pin_os_types.h>
#endif

#ifndef _pin_os_time_h_
  #include <pin_os_time.h>
#endif




    #include <pthread.h>

    #ifndef _pin_os_network_h_
      #include <pin_os_network.h>
    #endif

    #define _tempnam(dir, pfx)  tempnam((dir), (pfx))

    #endif



#if defined(__cplusplus)
extern "C" {
#endif

/** Get the id of the calling thread
  *
  * This function returns the thread id of the calling thread. Do not make
  * any assumptions about this id's range or whether it will be reused over
  * the course of the lifetime of a process. Treat it like a magic cookie to
  * the greatest extent possible
  *
  * @return The id of the calling thread.
  */
pthread_t pin_get_tid(void);

#if defined(__cplusplus)
}
#endif




/*  PIN_DEPRECATED_STUFF
 *
 *  These things are now deprecated. They are here still in order to make the
 *  transition easier (i.e. so that the whole code base doesn't need to be
 *  swatted at once in order to update pinos.
 *
 *  To check your code against the new stuff, define the PIN_NODEP_PINOS token
 *  for your build, which will force all deprecated PINOS stuff off.
 */
#ifndef PIN_NODEP_PINOS

#define pin_thread_id   pin_get_tid

#endif

