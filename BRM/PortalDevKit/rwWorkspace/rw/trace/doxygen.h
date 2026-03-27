#ifndef rw_trace_doxygen_h__
#define rw_trace_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup execution_tracing_package Execution Tracing
 * \ingroup threads_module
 *
 * \headerfileloc{#include <rw/trace/userdefs.h>}{}
 *
 * Execution Tracing classes enable you to monitor the runtime behavior of
 * your applications. Trace output messages can be filtered at both
 * compile-time and runtime for maximum flexibility.
 *
 * For complete information about the Execution Tracing package, see the
 * <em>Threads Module User's Guide</em>.
 *
 * The set declaration macros implement the runtime lookup of environment
 * variables that determine whether a function will generate a trace event.
 * Trace does not work correctly if the set declaration macros are not used
 * or are used improperly. Set declaration macro names all include the word
 * \c TRACEABLE, to distinguish them from event generation macros. Set
 * declaration macros come in three varieties: package declaration macros,
 * class declaration macros, and function declaration macros.
 *
 * <h4>Package Declaration Macros</h4>
 * The package declaration macros are optional. You use them only when your
 * application is split into packages, and you want to control tracing
 * separately for each package. For information on how you can create your
 * own packages and package tracing macros, see Section 6.9, "Using
 * Package-level Tracing," in the Threads Module User's Guide.
 *
 * \note
 * A predefined package set named \c rw_user acts as a default super set for
 * your classes and functions. If this single package set is sufficient for
 * your purposes, you can skip this section.
 *
 * The package declaration macros are used in the implementation of the
 * Execution Tracing package itself. To get a feel for what these macros do,
 * you can check the \c userdefs.h and \c userdefs.cpp files in the trace
 * source directories.
 *
 * The macros take one parameter, \a packageName, to specify the name of the
 * package to be traced. The \a packageName must be a valid C++ identifier.
 * The \c DECLARE and \c DEFINE macros must be used in pairs, and the
 * \a packageName of the \c DECLARE and \c DEFINE macros must match.
 *
 * \code
 * RW_TRACE_DECLARE_TRACEABLE_PACKAGE(packageName)
 * \endcode
 *
 * Declares a traceable package. This macro is normally placed at the end of
 * the header file that defines the trace macros for that package. For an
 * example, see the trace header file \c userdefs.h or the \c pkgdefs.h file
 * for any other package in the Threads Module.
 *
 * \code
 * RW_TRACE_DEFINE_TRACEABLE_PACKAGE(packageName)
 * \endcode
 *
 * Provides a definition for a static variable defined by the matching
 * \c DECLARE macro (above). This macro must be placed in some
 * implementation file (.cpp) for your application. For an example, see the
 * trace source file \c userdefs.cpp or the \c pkgdefs.cpp file in any of
 * the other packages in the Threads Module.
 *
 * <h4>Class Declaration Macros</h4>
 * The class declaration macros declare classes to be traceable, with the
 * \c rw_user package as the super set. If you intend to trace any of a
 * class' functions (member or static member), you must use these macros.
 * Friend functions can either be traced with these macros or traced as
 * global functions.
 *
 * If you have used the package declaration macros to define other packages,
 * you need to create your own class declaration macros. See Section 6.9,
 * "Using Package-level Tracing," in the Threads Module User's Guide.
 *
 * The macros take one parameter, \a className, to specify the name of the
 * class to be traced. The \a className must be a valid C++ identifier. The
 * \c DECLARE and \c DEFINE macros must be used in pairs, and the
 * \a className of the \c DECLARE and \c DEFINE macros must match.
 *
 * \code
 * RW_USER_DECLARE_TRACEABLE_CLASS(className)
 * \endcode
 *
 * Declares a non-template class as traceable. This macro must be placed in
 * the header file for a class before the class declaration. Otherwise, it
 * generates an undefined symbol compile error.
 *
 * \code
 * RW_USER_DEFINE_TRACEABLE_CLASS(className)
 * \endcode
 *
 * Provides a definition for a static variable defined by the matching
 * \c DECLARE macro (above). This macro must be placed in the implementation
 * (.cpp) file for the class.
 *
 * \code
 * RW_USER_DECLARE_TRACEABLE_TEMPLATE_CLASS(className)
 * \endcode
 *
 * Declares a template class as traceable. Do not include the template
 * parameters in the \a className. This macro must be placed in the header
 * file for a class before the class declaration. Otherwise, it generates an
 * undefined symbol compile error.
 *
 * \code
 * RW_USER_DEFINE_TRACEABLE_TEMPLATE_CLASS(className)
 * \endcode
 *
 * Provides a definition for a static variable defined by the matching
 * \c DECLARE macro (above). Do not include the template parameters in the
 * \a className. This macro must be placed in the implementation file
 * (typically a .cc file) for the template class.
 *
 * <h4>Function Declaration Macros</h4>
 * The function declaration macros declare functions to be traceable. In
 * addition, the macros automatically generate \c ENTRY and \c EXIT trace
 * events upon entry and exit of the function. Every function that requires
 * tracing must have one of these macros, normally as the first line of the
 * function. Attempting to use more than one function declaration macro in a
 * function results in compile or link errors.
 *
 * The macro families come in sets of four macros, including an \c INLINE
 * version for inline functions, a \c TEMPLATE version for template
 * functions, a \c INLINE_TEMPLATE version for inline template functions,
 * and a basic version for all other functions. Using the incorrect version
 * results in compile and link errors.
 *
 * Function declaration macros can take these parameters:
 *
 * - \a functionTag is used as the environment variable to control trace
 * event generation for this function. It also appears in the trace output.
 * The functionTag parameter must be a valid C++ identifier, and it must be
 * enclosed in quotation marks, as a string. The functionTag is usually the
 * name of the function (for a global function) or a string of the form
 * \c "ClassName_functionName" (for a member function). See the <em>Threads
 * Module User's Guide</em>, for more on assigning tag names.
 *
 * - \a className specifies the name of the class to which the member or
 * friend function belongs. It must match the \a className used in the
 * RW_USER_DECLARE_TRACEABLE_CLASS macro for the class.
 */

#endif // rw_trace_doxygen_h__ 
