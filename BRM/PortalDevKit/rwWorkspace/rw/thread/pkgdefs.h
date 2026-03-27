#ifndef __rw_thread_pkgdefs_h__
#define __rw_thread_pkgdefs_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/pkgdefs.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
 * 
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software, Inc.
 * pursuant to a written license agreement and may be used, copied, transmitted,
 * and stored only in accordance with the terms of such license agreement and
 * with the inclusion of the above copyright notice.  This computer software or
 * any other copies thereof may not be provided or otherwise made available to
 * any other person.
 * 
 * U.S. Government Restricted Rights.  This computer software: (a) was
 * developed at private expense and is in all respects the proprietary
 * information of Rogue Wave Software, Inc.; (b) was not developed with
 * government funds; (c) is a trade secret of Rogue Wave Software, Inc. for all
 * purposes of the Freedom of Information Act; and (d) is a commercial item and
 * thus, pursuant to Section 12.212 of the Federal Acquisition Regulations (FAR)
 * and DFAR Supplement Section 227.7202, Government's use, duplication or
 * disclosure of the computer software is subject to the restrictions set forth
 * by Rogue Wave Software, Inc.
 *
 *************************************************************************/

#include <rw/config/rwconfig_thread.h>
#include <rw/trace/pkgdefs.h>
#include <rw/defs.h>

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_THREAD_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_THREAD_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_THREAD_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_thread)
#  define RW_THREAD_BUILD
#endif

// Compatibility definitions
#if defined(_WIN32) && defined(RW_THREAD_DLL)
#  if defined(_RWBUILD_thread)
#    define _RWTHREADBUILDDLL
#  endif // _RWBUILD_thread
#endif // _WIN32 && RW_THREAD_DLL

//////////////////////////////////////////////////////////////////////////////
// Define catch-all macro for the whole package
//////////////////////////////////////////////////////////////////////////////
// Enhancement requested by customers; see PR #27333
#if !defined(RW_THREAD_DONT_MASK_EXCEPTIONS)
#  define RW_THREAD_THROW_UNKNOWN(x)         throw x
#  define RW_THREAD_RETHROW_UNKNOWN()
#else
#  define RW_THREAD_THROW_UNKNOWN(ignore)    throw
#  define RW_THREAD_RETHROW_UNKNOWN()        throw
#endif // !defined (RW_THREAD_NO_CATCH_ALL)

// Macros describing the product
#define RW_THR_PRODUCT_NAME "SourcePro Core - Threads Module"
#define RW_THR_PRODUCT_VENDOR "Rogue Wave Software, Inc."
#define RW_THR_PRODUCT_COPYRIGHT "Copyright 2013, Rogue Wave Software, Inc. All rights reserved."
#define RW_THR_PRODUCT_TYPE "C++ Library"
#define RW_THR_PRODUCT_THREAD_SAFETY "MT-Safe"
#define RW_THR_PRODUCT_VARIANT_DESCRIPTOR ""
#define RW_THR_PRODUCT_VERSION_LABEL ""

#if defined(RW_THREAD_DEBUG)
#  define RW_THR_PRODUCT_RELEASE_TYPE "Debug"
#else
#  define RW_THR_PRODUCT_RELEASE_TYPE "Release"
#endif

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_THREAD_DLL)
#  if defined(RW_THREAD_BUILD)
#    define RW_THREAD_GLOBAL                      RW_COMPILER_GLOBAL_EXPORT
#    define RW_THREAD_SYMBOLIC                    RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_THREAD_GLOBAL                      RW_COMPILER_GLOBAL_IMPORT
#    define RW_THREAD_SYMBOLIC                    RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_THREAD_GLOBAL
#  define RW_THREAD_SYMBOLIC
#endif

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#define RW_THREAD_IDENT \
  static const char rw_thread_ident[] = "\"@(#)\trw/thread:" __FILE__ " " __DATE__ " " __TIME__ "\""; \
  inline void rw_use_thread_ident(void) { RW_UNUSED(rw_thread_ident); }

//////////////////////////////////////////////////////////////////////////////
// Platform specific macros
//////////////////////////////////////////////////////////////////////////////

// RW_THR_CAN_RECOVER_THREAD_LOCALS
// The environment supports automatic recovery of thread local
// storage.  If not, the Threads Module must do the recovery itself
// either at the time of thread exit for thread started by RWThread
// instances, or at the time the thread-local storage object is
// destructed.
// Both the POSIX and Solaris Thread APIS support this (Windows does not)
#if !defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_CAN_RECOVER_THREAD_LOCALS
#endif

// RW_THR_HAS_PARTIAL_STACK_COMMITMENT
// The environment allows the user to partially commit the memory
// reserved for the stack to physical memory at the time of thread
// creation.  If this macro is not defined, and the macro
// RW_THR_HAS_STACK_COMMIT_SIZE is defined, then the commit size also
// defines the amount of memory to reserve for the stack, so the
// entire amount must be committed at thread creation.
#if defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_PARTIAL_STACK_COMMITMENT
#endif

// RW_THR_HAS_STACK_COMMIT_SIZE
// The environment allows the user to dictate the amount of the
// memory reserved for a thread stack that is to be committed or
// mapped to physical memory when a thread is created.  This allows
// the user to pre-commit physical memory and pagefile space prior
// to thread execution.  This macro applies to RWThreadAttribute
// instances only.
#if defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_STACK_COMMIT_SIZE
#endif

// RW_THR_HAS_DUAL_PRIORITY
// The environment requires two priorities for threads with system
// contention scope;  one priority value for use in resolving
// system-level scheduling conflicts, and a second priority value for
// use in resolving contention for synchronization resources that are
// shared between threads in a process.  This macro is provided for
// informational purposes; it implies that both the proces-scope and
// system-scope priority attributes are simultaneously accessible for
// when the contention scope is RW_THR_SYSTEM_SCOPE.  This macro
// applies to RWThreadAttribute instances and active instances of the
// RWThread class and its subclasses.
#if defined(RW_THR_THREAD_API_POSIX_SUNOS) || defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_DUAL_PRIORITY
#endif

// RW_THR_HAS_TIME_SLICE_QUANTUM
// The environment supports the time-slice quantum attribute under
// certain circumstances.  This attribute is used to control the
// maximum execution time for threads executing under a time-sliced
// scheduling policy.  This attribite is only supported under certain
// content-scope and scheduling policy combinations, and is supported
// by few environments.  This macro applies to RWThreadAttribute
// instances and active instances of the RWThread class and its
// subclasses.
#if defined(RW_THR_THREAD_API_POSIX_SUNOS) || defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_TIME_SLICE_QUANTUM
#endif

// RW_THR_MUST_CALL_SHUTDOWN
// On some platforms, you must explicitly call shutdown on the
// thread manager in order to ensure that all threads have been
// cleaned up before main exits.  This prevents issues on platforms
// where exceptions thrown from threads after main has exited result
// in immediate termination.
#if ((defined(__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT == 'G') ||  \
        defined(__GCC__)) && defined(RW_THREAD_DLL)
#  define RW_THR_MUST_CALL_SHUTDOWN
#endif

// RW_THR_HAS_START_POLICY
// The environment supports the start policy attribute.  The start
// policy dictates whether a new thread is to be left interrupted at
// creation or allowed to run immediately.  This attribute is
// currently available in all environments. This macro applies to
// RWThreadAttribute instances only.
#define RW_THR_HAS_START_POLICY

// RW_THR_HAS_CONCURRENCY_POLICY
// The environment recognizes or supports the concurrency policy
// attribute.  This attribute is used to control whether a creation
// of a new process-scope thread should result in the creation of a
// new underlying kernel thread (LWP) in order to provide a
// sufficient level of concurrency in environments with N to M
// thread scheduling. This macro applies to RWThreadAttribute
// instances only.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_CONCURRENCY_POLICY 1
#endif

// RW_THR_HAS_CONTENTION_SCOPE
// The environment recognizes or supports the scheduling contention
// scope attribute.  This does not necessarily imply that you may
// change the contention scope specified by a thread attribute, only
// that you may query it.  Contention scope is fixed in many
// environments. This macro applies to RWThreadAttribute instances
// only.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_CONTENTION_SCOPE 1
#elif defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_CONTENTION_SCOPE 1
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
#    define RW_THR_HAS_CONTENTION_SCOPE 1
#  endif
#endif

// RW_THR_HAS_INHERITANCE_POLICY
// The environment supports the scheduling attribute inheritance
// attribute.  This does not necessarily imply that you may change
// the inheritance policy, only that you can query it.  Inheritance
// policy may be fixed in some environments, but is available in all
// currently supported environments.  This macro applies to
// RWThreadAttribute instances only.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_INHERITANCE_POLICY 1
#elif defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_INHERITANCE_POLICY 1
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
#    define RW_THR_HAS_INHERITANCE_POLICY 1
#  endif
#endif

// RW_THR_HAS_MAX_THREADS
// The environment defines an upper limit on the number of threads
// that may be created.  If this macro is not defined, the number
// of threads is.
#if defined(RW_THR_THREAD_API_POSIX)
#  define RW_THR_HAS_MAX_THREADS 1
#endif

// RW_THR_HAS_PRIORITY
// The environment supports priority scheduling and the priority
// value of a thread attribute or active thread may be set or
// queried.  This macro applies to RWThreadAttribute instances and
// active instances of the RWThread class and its subclasses.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_PRIORITY 1
#elif defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_PRIORITY 1
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
#    define RW_THR_HAS_PRIORITY 1
#  endif
#endif

// RW_THR_HAS_PROCESS_SCOPE_PRIORITY
// The environment supports priority scheduling and defines a
// process-scope priority attribute.  This attribute may be set or
// queried depending on the current contention scope and whether or
// not the environment supports dual priorities.  This macro applies
// to RWThreadAttribute instances and active instances of the
// RWThread class and its subclasses.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_PROCESS_SCOPE_PRIORITY 1
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
#    define RW_THR_HAS_PROCESS_SCOPE_PRIORITY 1
#  endif
#endif

// RW_THR_HAS_SCHEDULING_POLICY
// The environment supports the scheduling policy attribute.  This
// does not necessarily imply that you may change the scheduling
// policy, only that you can query it.  Scheduling policy may be
// fixed under some contention scopes and in some environments.
// This macro applies to RWThreadAttribute instances and active
// instances of the RWThread class and its subclasses.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_SCHEDULING_POLICY 1
#elif defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_SCHEDULING_POLICY 1
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
#    define RW_THR_HAS_SCHEDULING_POLICY 1
#  endif
#endif

// RW_THR_HAS_STACK_GUARD_SIZE
// The environment allows the user to set manager stack guard sizes
// for system stack memory.  If this macro is defined, the user may
// supply a size for the stack guard.  This macro applies to
// RWThreadAttribute instances only.
#if defined(RW_THR_THREAD_API_POSIX)
#  define RW_THR_HAS_STACK_GUARD_SIZE 1
#endif

// RW_THR_HAS_STACK_RESERVE_SIZE
// The environment allows the user to dictate the amount of memory to
// allocate for a thread stack when a thread is created.  This memory
// is generally mapped, or committed on-demand as the stack grows.
// This macro applies to RWThreadAttribute instances only.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_STACK_RESERVE_SIZE 1
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_ATTR_STACKSIZE)
#    define RW_THR_HAS_STACK_RESERVE_SIZE 1
#  endif
#endif

// RW_THR_HAS_SUSPEND_RESUME
// The environment allows the user to suspend and resume an active
// thread running inside an instance of the RWThread class and its
// subclasses.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_SUSPEND_RESUME 1
#elif defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_SUSPEND_RESUME 1
#endif

// RW_THR_HAS_SYSTEM_SCOPE_PRIORITY
// The environment supports priority scheduling and defines a
// system-scope priority attribute.  This attribute may be set or
// queried depending on the current contention scope.  This macro
// applies to RWThreadAttribute instances and active instances of the
// RWThread class and its subclasses.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_SYSTEM_SCOPE_PRIORITY 1
#elif defined(RW_THR_THREAD_API_WIN32)
#  define RW_THR_HAS_SYSTEM_SCOPE_PRIORITY 1
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
#    define RW_THR_HAS_SYSTEM_SCOPE_PRIORITY 1
#  endif
#endif

// RW_THR_HAS_USER_STACK
// The environment allows the user to define and manage their own
// stack memory.  If this macro is defined, the user may supply
// their own memory for the thread stack by specifying values for the
// starting address and size attributes.  This macro applies to
// RWThreadAttribute instances only.
#if defined(RW_THR_THREAD_API_SOLARIS)
#  define RW_THR_HAS_USER_STACK 1
#elif defined(RW_THR_THREAD_API_POSIX_LINUX)
// LinuxThreads appear to have issues with user stacks. See SP-13926.
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#  include <unistd.h>
#  if defined(_POSIX_THREAD_ATTR_STACKADDR)
#    define RW_THR_HAS_USER_STACK 1
#  endif
#endif

#endif // __rw_thread_pkgdefs_h__
