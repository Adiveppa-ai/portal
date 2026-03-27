#ifndef rw_serial_doxygen_h__
#define rw_serial_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup advanced_tools_module Advanced Tools Module
 * \ingroup sourcepro_core_product
 *
 * The Advanced Tools Module provides C++ classes for a nonintrusive
 * streaming mechanism for complex stream transformations and object
 * serializations.
 */

/**
 * \defgroup serialization_package Serialization
 * \ingroup advanced_tools_module
 *
 * The Serialization package provides a way to flatten objects, so they can
 * be easily transported across communication boundaries or stored to disk.
 * This <em>object serialization</em> mechanism includes two processes:
 *
 * - Translation of an object or set of related objects in memory into a
 * linear series of atomic events or tokens.
 * - Translation of such a series back into an equivalent object or set of
 * related objects.
 *
 * The classes, macros, and functions in the Serialization package help you
 * to define serializable objects with a minimum of custom code, while
 * retaining control over the formats and policies used. To make your C++
 * classes <em>serializable</em>, you instrument them with a small set of
 * streaming macros. These macros encapsulate the details associated with
 * streaming protocols, shielding your application from the implementation
 * details but otherwise not affecting your application code. You have a
 * choice of intrusive serialization for your own classes or external
 * serialization for classes that you can't modify, such as classes from a
 * third-party library. The Serialization package also includes a set of
 * utility functions for streaming objects to and from various formats.
 *
 * For complete information about the Serialization package, see the
 * <em>Advanced Tools Module User's Guide</em>.
 */

/**
 * \defgroup serialization_package_macros Serialization Macros
 * \ingroup serialization_package
 *
 * \headerfileloc{#include <rw/serial/RWObjectStreamMacros.h>}
 *
 * This group includes macro definitions used to define operations that
 * enable objects to be serialized.
 *
 * While not directly part of object streams, these macros make heavy use of
 * the object streams interface, delegating most of the work of object
 * serialization back to the object stream implementation. Object streams
 * are thus able to control nearly all aspects of object serialization, not
 * just the format of primitive data types like virtual streams.
 *
 * Some of these macros have positional restrictions with respect to each
 * other. As a general rule of thumb, the \c RW_XXX_AS_SELF macros come
 * before \c RW_XXX_AS_BASE macros. For more insight, please see Section
 * 6.4, "Basic Examples," in the <em>Advanced Tools Module User's
 * Guide</em>.
 */

#endif // rw_serial_doxygen_h__ 
