#ifndef rw_sync_doxygen_h__
#define rw_sync_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup synchronization_package Synchronization
 * \ingroup threads_module
 *
 * The Synchronization package includes a group of synchronization classes
 * and a group of helper classes, called <em>guard</em> classes.
 *
 * For complete information about the Synchronization package, see the
 * <em>Threads Module User's Guide</em>.
 */

/**
 * \ingroup synchronization_package
 * Users can define this macro as part of their build configuration to use a
 * critical section as the implementation for RWMutexLock.
 *
 * \note
 * This option affects only build configurations on Windows platforms.
 */
#define RW_SYNC_MUTEX_USES_CRITICAL_SECTION

/**
 * \ingroup synchronization_package
 * This macro is defined if the underlying implementation used by
 * RWMutexLock supports timed acquire. For platforms without true
 * timed-acquisition support, #RW_THR_TIMEOUT is returned if the mutex
 * cannot be acquired immediately.
 */
#define RW_THR_HAS_TIMED_MUTEX_ACQUIRE

#endif // rw_sync_doxygen_h__ 
