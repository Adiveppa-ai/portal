#ifndef rw_thread_doxygen_h__
#define rw_thread_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup threads_module Threads Module
 * \ingroup sourcepro_core_product
 *
 * The Threads Module contains C++ classes for writing multithreaded
 * applications. It provides the mechanisms necessary for the creation and
 * synchronization of threads across a variety of operating systems and
 * platforms.
 */

/**
 * \defgroup threading_package Threading
 * \ingroup threads_module
 *
 * The Threading package contains prebuilt, fundamental threading classes,
 * giving you a head-start on building portable, multithreaded applications.
 *
 * The Threading package includes the runnable classes, the thread attribute
 * classes, and the IOU classes.
 *
 * For complete information about the Threading package, see the <em>Threads
 * Module User's Guide</em>.
 */

/**
 * \defgroup rwtMakeRunnableCallback rwtMakeRunnableCallback Macros and Functions
 * \ingroup threading_package
 *
 * \headerfileloc{#include <rw/thread/rwtMakeRunnableCallback.h>}
 *
 * The rwtMakeRunnableCallback() helper functions and macros create functors
 * that may be passed to the \ref RWRunnable::addCallback() "addCallback()"
 * method of an RWRunnableHandle. The functor may be created from functions
 * that accept a constant RWRunnable reference as first argument, and an
 * #RWExecutionState as second argument, and that do not return a value.
 *
 * rwtMakeRunnableCallback() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and as we cannot
 * overload macros, each must have a unique name.
 *
 * In naming the macros we have employed a convention to make the names
 * easier to remember. Each name begins with \c rwtMakeRunnableCallback,
 * which will be followed by either a \c G if the macro is expecting a
 * global function, or an \c M if it is expecting a member function. At that
 * point, the name is complete, if the associated global or member function
 * takes no additional arguments. Otherwise we add one of \c A1 or \c A2,
 * for functions with 1 or 2 additional arguments respectively. For example,
 * you will use macro rwtMakeRunnableCallbackG() to create a runnable that
 * calls a <em>global function</em> that takes no arguments other than the
 * runnable reference and the execution state. The macro
 * rwtMakeRunnableCallbackMA2() will create a runnable that calls a
 * <em>member function</em> that takes four arguments: the runnable
 * reference and the execution state, plus two user-supplied arguments.
 *
 * \example
 * Example Using Templates
 * \code
 *     // Global function with no additional arguments
 *     void function(const RWRunnable&, RWExecutionState);
 *     RWRunnableHandle rnb = ...;
 *     // Create callback for function() and register with runnable
 *     rnb.addCallback(rwtMakeRunnableCallback(function));
 *
 *     class A {
 *       public:
 *         // Member function with one additional argument
 *         void bar(const RWRunnable&, RWExecutionState, int);
 *     };
 *
 *     A a; // Instance of class A
 *     // Create callback for A::bar() and register with runnable
 *     rnb.addCallback(rwtMakeRunnableCallback(a,&A::bar,99);
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * // Create callback for function() and register with runnable
 * rnb.addCallback(rwtMakeRunnableCallbackG(function));
 *
 * // Create callback for A::bar() and register with runnable
 * rnb.addCallback(rwtMakeRunnableCallbackMA1(A,a,&A::bar,int,99));
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWRunnableHandle, RWTFunctor2
 */

/**
 * \defgroup rwtMakeRunnableFunction rwtMakeRunnableFunction Macros and Functions
 * \ingroup threading_package
 *
 * \headerfileloc{#include <rw/thread/rwtMakeRunnableFunction.h>}
 *
 * rwtMakeRunnableFunction() creates an instance of RWRunnableFunction
 * directly from a global or member function pointer. The easiest way to
 * create a runnable object with the Threads Module is to begin with
 * rwtMakeRunnableFunction(). By supplying a global or member function
 * pointer you control what your runnable will do after starting. If you
 * wish your runnable to start by calling a function that takes arguments,
 * rwtMakeRunnableFunction() allows you to specify the values that should be
 * passed to that function. Note that runnables created with
 * rwtMakeRunnableFunction() will ignore any return values from the
 * associated function. To create runnables from which you can extract a
 * return value, see rwtMakeRunnableIOUFunction().
 *
 * rwtMakeRunnableFunction() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and as we cannot
 * overload macros, each must have a unique name.
 *
 * In naming the macros we have employed a convention to make the names
 * easier to remember. Each name begins with \c rwtMakeRunnableFunction,
 * which will be followed by either a \c G if the macro is expecting a
 * global function, or an \c M if it is expecting a member function. At that
 * point the name is complete if the associated global or member function
 * takes no arguments. Otherwise we add one of \c A1, \c A2, or \c A3 for
 * functions with 1, 2, or 3 arguments respectively. For example, you will
 * use macro rwtMakeRunnableFunctionG() to create a runnable that calls a
 * <em>global function</em> that takes no arguments. The macro
 * rwtMakeRunnableFunctionMA2() will create a runnable that calls a
 * <em>member function</em> that takes two arguments.
 *
 * \example
 * Example Using Templates
 * \code
 *     class A {
 *     public:
 *       int bar(char);  // Member function with 1 argument
 *     };
 *
 *     A a;  // an instance of class A
 *
 *     int foo(double, long);  // Global function with 2 arguments
 *
 *     // Create an RWRunnableFunction set to call foo(3.14,11):
 *     RWRunnableFunction t1 = rwtMakeRunnableFunction(foo, 3.14, 11);
 *
 *     // Create an RWRunnableFunction set to call a.bar(`x'):
 *     RWRunnableFunction t2 = rwtMakeRunnableFunction(a, &A::bar, `x');
 * \endcode
 *
 * Example Using Macros
 * \code
 * class A {
 * public:
 *   int bar(char);  // Member function with 1 argument
 * };
 *
 * A a;  // an instance of class A
 *
 * int foo(double, long);  // Global function with 2 arguments
 *
 * // Create an RWRunnableFunction set to call foo(3.14,11):
 * RWRunnableFunction t1
 *   = rwtMakeRunnableFunctionGA2(int, foo, double, 3.14, long,
 *     11);
 *
 * // Create an RWRunnableFunction set to call a.bar(`x'):
 * RWRunnableFunction t2
 *     = rwtMakeRunnableFunctionMA1(A, a, int, &A::bar, char, `x');
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the third argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWRunnableFunction
 */

/**
 * \defgroup rwtMakeRunnableGuard rwtMakeRunnableGuard Macros and Functions
 * \ingroup threading_package
 *
 * \headerfileloc{#include <rw/thread/rwtMakeRunnableGuard.h>}
 *
 * An #RWRunnableGuard is a typedef to a functor used in conjunction with
 * the RWTPCValBufferBaseGuarded and derived classes, templatized on a
 * RWRunnable. The runnable server classes RWRunnableServer and RWServerPool
 * use these functors internally. A runnable guard functor is used by the
 * RWTPCValBufferBaseGuarded classes to select the next enqueued runnable to
 * execute. It is designed to allow a runnable to remain in a queue until
 * some condition is satisfied.
 *
 * When a client requests a runnable from a runnable queue, the queue
 * selects the next runnable to execute by traversing any enqueued
 * runnables, and executing their guard functors, until it finds a runnable
 * whose guard functor evaluates to \c true. That runnable is then returned
 * to the client.
 *
 * \example
 * \code
 * #include <iostream>
 * #include<rw/thread/RWRunnableFunction.h>
 * #include<rw/thread/RWRunnableServer.h>
 * #include<rw/thread/rwtMakeRunnableFunction.h>
 * #include<rw/thread/RWRunnableGuard.h>
 *
 * void something() { std::cout << "I'm a runnable" << std::endl; }
 *
 * class YourClass {
 *    public:
 *       bool yourFunc() {
 *          if (//some condition
 *              )
 *             return true;
 *          else
 *             return false;
 *       }
 * };
 *
 * int main() {
 *
 *   RWRunnableServer runnableServer(RWRunnableServer::make());
 *   runnableServer.start();
 *
 *   RWRunnableFunction doSomething;
 *   doSomething = rwtMakeRunnableFunction(something);
 *
 *   YourClass yourClass;
 *
 *   // Construct a guard functor using a template function.
 *   RWRunnableGuard guard1;
 *   guard1 = rwtMakeRunnableGuard(yourClass,
 *                                &YourClass::yourFunc);
 *
 *   runnableServer.enqueue(doSomething, guard1);
 *
 *   // Construct a guard functor using a macro.
 *   RWRunnableGuard guard2;
 *   guard2 = rwtMakeRunnableGuardM(YourClass,
 *                                 yourClass,
 *                                 bool,
 *                                 &YourClass::yourFunc);
 *
 *   runnableServer.enqueue(doSomething, guard2);
 *
 *   runnableServer.stop();
 *   runnableServer.join();
 *
 *   return 0;
 * }
 * \endcode
 * \endexample
 *
 * <h4>Global Function Templates</h4>
 * The function templates in this section use the following naming
 * conventions for their arguments:
 *
 * <table>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. For runnable guards the
 * return must be convertible to a \c bool.</td>
 * </tr>
 * <tr>
 * <td>\c Callee</td>
 * <td>Name of the class of a member function used as a runnable guard.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Class instance bound to the member function used as a runnable
 * guard.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Name of the function, member or otherwise, to be used as a runnable
 * guard.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type of the first \a callee argument accepted by the runnable guard
 * function.</td>
 * </tr>
 * <tr>
 * <td>\c AA1</td>
 * <td>Type name of the first caller argument passed to the runnable guard,
 * at the creation of the runnable guard instance.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Value of the first caller argument passed to a runnable guard
 * instance at its creation.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second \a callee argument accepted by the runnable
 * guard function.</td>
 * </tr>
 * <tr>
 * <td>\c AA2</td>
 * <td>Type name of the second caller argument passed to the runnable guard,
 * at the creation of the runnable guard instance.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Value of the second caller argument passed to a runnable guard
 * instance at its creation.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type of the third \a callee argument accepted by the runnable guard
 * function.</td>
 * </tr>
 * <tr>
 * <td>\c AA3</td>
 * <td>Type name of the third caller argument passed to the runnable guard,
 * at the creation of the runnable guard instance.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Value of the third caller argument passed to a runnable guard
 * instance at its creation.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. For runnable guards, the
 * return type is a \c bool.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the third argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWRunnableServer, RWServerPool
 */

/**
 * \defgroup rwtMakeRunnableIOUFunction rwtMakeRunnableIOUFunction Macros and Functions
 * \ingroup threading_package
 *
 * \headerfileloc{#include <rw/thread/rwtMakeRunnableIOUFunction.h>}
 *
 * The easiest way to create a runnable object with the Threads Module is to
 * begin with rwtMakeRunnableIOUFunction(). By supplying a global or member
 * function pointer you control what your runnable will do after starting.
 * If you wish your runnable to start by calling a function that takes
 * arguments, rwtMakeRunnableIOUFunction() allows you to specify the values
 * that should be passed to that function. Note that runnables created with
 * rwtMakeRunnableIOUFunction() allow you to extract the return value from
 * the associated function. This distinguishes them from those created by
 * rwtMakeRunnableFunction(), which do not.
 *
 * rwtMakeRunnableIOUFunction() comes in two flavors. First, there is a set
 * of overloaded global function templates. Since not all compilers are able
 * to handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments, and as we can not
 * overload macros, each must have a unique name.
 *
 * In naming the macros we have employed a convention to make the names
 * easier to remember. Each name begins with \c rwtMakeRunnableIOUFunction,
 * which will be followed by either a \c G if the macro is expecting a
 * global function, or an \c M if it is expecting a member function. At that
 * point the name is complete if the associated global or member function
 * takes no arguments. Otherwise we add one of \c A1, \c A2, or \c A3 for
 * functions with 1, 2, or 3 arguments respectively. For example, you will
 * use macro rwtMakeRunnableIOUFunctionG() to create a runnable that calls a
 * <em>global function</em> that takes no arguments. The macro
 * rwtMakeRunnableIOUFunctionMA2() will create a runnable that calls a
 * <em>member function</em> that takes two arguments.
 *
 * \example
 * Example Using Templates
 *
 * \code
 * class A {
 *   public:
 *     int bar(char);  // Member function with 1 argument
 *   };
 *
 *   A a;  // an instance of class A
 *
 *   int foo(double, long);  // Global function with 2 arguments
 *
 *   // Create an RWTRunnableIOUFunction set to call foo(3.14,11):
 *   RWTRunnableIOUFunction<int> t1
 *           = rwtMakeRunnableIOUFunction(foo, 3.14, 11);
 *
 *   // Create an RWTRunnableIOUFunction set to call a.bar(`x'):
 *     RWTRunnableIOUFunction<int> t2
 *           = rwtMakeRunnableIOUFunction(a, &A::bar, `x');
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * class A {
 * public:
 *   int bar(char);  // Member function with 1 argument
 * };
 *
 * A a;  // an instance of class A
 *
 * int foo(double, long);  // Global function with 2 arguments
 *
 * // Create an RWTRunnableIOUFunction set to call foo(3.14,11):
 * RWTRunnableIOUFunction<int> t1
 *   = rwtMakeRunnableIOUFunctionGA2(int, foo, double, 3.14, long,
 *     11);
 *
 * // Create an RWTRunnableIOUFunction set to call a.bar(`x'):
 * RWTRunnableIOUFunction<int> t2
 *   = rwtMakeRunnableIOUFunctionMA1(A, a, int, &A::bar, char,
 *     `x');
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the third argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWTRunnableIOUFunction
 */

/**
 * \defgroup rwtMakeThreadFunction rwtMakeThreadFunction Macros and Functions
 * \ingroup threading_package
 *
 * \headerfileloc{#include <rw/thread/rwtMakeThreadFunction.h>}
 *
 * The easiest way to create a thread with the Threads Module is to begin
 * with rwtMakeThreadFunction(). By supplying a global or member function
 * pointer you control what your thread will do after starting. If you wish
 * your thread to start by calling a function that takes arguments,
 * rwtMakeThreadFunction() allows you to specify the values that should be
 * passed to that function. Note that threads created with
 * rwtMakeThreadFunction() will ignore any return values from the associated
 * function. To create threads from which you can extract a return value,
 * see rwtMakeThreadIOUFunction().
 *
 * rwtMakeThreadFunction() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments, and as we can not
 * overload macros, each must have a unique name.
 *
 * In naming the macros we have employed a convention to make the names
 * easier to remember. Each name begins with \c rwtMakeThreadFunction, which
 * will be followed by either a \c G if the macro is expecting a global
 * function, or an \c M if it is expecting a member function. At that point
 * the name is complete if the associated global or member function takes no
 * arguments. Otherwise we add one of \c A1, \c A2, or \c A3 for functions
 * with 1, 2, or 3 arguments respectively. For example, you will use macro
 * rwtMakeThreadFunctionG() to create a thread that calls a <em>global
 * function</em> that takes no arguments. The macro
 * rwtMakeThreadFunctionMA2() will create a thread that calls a <em>member
 * function</em> that takes two arguments.
 *
 * \example
 * Example Using Templates
 *
 * \code
 *   class A {
 *     public:
 *       int bar(char);  // Member function with 1 argument
 *     };
 *
 *     A a;  // an instance of class A
 *
 *     int foo(double, long);  // Global function with 2 arguments
 *
 *     // Create an RWThreadFunction set to call foo(3.14,11):
 *     RWThreadFunction t1 = rwtMakeThreadFunction(foo, 3.14, 11);
 *
 *     // Create an RWThreadFunction set to call a.bar(`x'):
 *     RWThreadFunction t2 = rwtMakeThreadFunction(a, &A::bar, `x');
 * \endcode
 * Example Using Macros
 *
 * \code
 *   class A {
 *     public:
 *       int bar(char);  // Member function with 1 argument
 *   };
 *
 *   A a;  // an instance of class A
 *
 *   int foo(double, long);  // Global function with 2 arguments
 *
 *   // Create an RWThreadFunction set to call foo(3.14,11):
 *   RWThreadFunction t1
 *       = rwtMakeThreadFunctionGA2(int, foo, double, 3.14, long, 11);
 *
 *   // Create an RWThreadFunction set to call a.bar(`x'):
 *   RWThreadFunction t2
 *         = rwtMakeThreadFunctionMA1(A, a, int, &A::bar, char, `x');
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the third argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWThreadFunction
 */

/**
 * \defgroup rwtMakeThreadIOU rwtMakeThreadIOU Macros and Functions
 * \ingroup threading_package
 *
 * \headerfileloc{#include <rw/thread/rwtMakeThreadIOU.h>}
 *
 * Helper function for creating thread-safe escrow implementations. The
 * result of the function can be used to initialize an RWTIOUResult or an
 * RWTIOUEscrow.
 *
 * \example
 * \code
 * RWTIOUResult<RWCString> res = rwtMakeThreadIOU((RWCString*)0);
 *
 * // is equivalent to:
 *
 * RWTIOUResult<RWCString> res = RWTThreadEscrowImp<RWCString>::make();
 * \endcode
 * \endexample
 *
 * \sa
 * RWTEscrowImp, RWTEscrowHandle, RWTIOUResult, RWTIOUEscrow
 */

/**
 * \defgroup rwtMakeThreadIOUFunction rwtMakeThreadIOUFunction Macros and Functions
 * \ingroup threading_package
 *
 * \headerfileloc{#include <rw/thread/rwtMakeThreadIOUFunction.h>}
 *
 * The easiest way to create a thread with the Threads Module is to begin
 * with rwtMakeThreadIOUFunction(). By supplying a global or member function
 * pointer, you control what your thread will do after starting. If you wish
 * your thread to start by calling a function that takes arguments,
 * rwtMakeThreadIOUFunction() allows you to specify the values that should
 * be passed to that function. Note that threads created with
 * rwtMakeThreadIOUFunction() allow you to extract the return value from the
 * associated function. This distinguishes them from those created by
 * rwtMakeThreadFunction(), which do not.
 *
 * rwtMakeThreadIOUFunction() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and as we cannot
 * overload macros, each must have a unique name.
 *
 * In naming the macros we have employed a convention to make the names
 * easier to remember. Each name begins with \c rwtMakeThreadIOUFunction,
 * which will be followed by either a \c G if the macro is expecting a
 * global function, or an \c M if it is expecting a member function. At that
 * point the name is complete if the associated global or member function
 * takes no arguments. Otherwise we add one of \c A1, \c A2, or \c A3 for
 * functions with 1, 2, or 3 arguments respectively. For example, you will
 * use macro rwtMakeThreadIOUFunctionG() to create a thread that calls a
 * <em>global function</em> that takes no arguments. The macro
 * rwtMakeThreadIOUFunctionMA2() will create a thread that calls a
 * <em>member function</em> that takes two arguments.
 *
 * \example
 * Example Using Templates
 * \code
 *   class A {
 *     public:
 *       int bar(char);  // Member function with 1 argument
 *   };
 *
 *   A a;  // an instance of class A
 *
 *   int foo(double, long);  // Global function with 2 arguments
 *
 *   // Create an RWTThreadIOUFunction set to call foo(3.14,11):
 *   RWTThreadIOUFunction<int> t1
 *           = rwtMakeThreadIOUFunction(foo, 3.14, 11);
 *
 *   // Create an RWTThreadIOUFunction set to call a.bar(`x'):
 *   RWTThreadIOUFunction<int> t2
 *           = rwtMakeThreadIOUFunction(a, &A::bar, `x');
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 *   class A {
 *     public:
 *       int bar(char);  // Member function with 1 argument
 *   };
 *
 *   A a;  // an instance of class A
 *
 *   int foo(double, long);  // Global function with 2 arguments
 *
 *   // Create an RWTThreadIOUFunction set to call foo(3.14,11):
 *   RWTThreadIOUFunction<int> t1
 *       = rwtMakeThreadIOUFunctionGA2(int, foo, double, 3.14, long, 11);
 *
 *   // Create an RWTThreadIOUFunction set to call a.bar(`x'):
 *   RWTThreadIOUFunction<int> t2
 *       = rwtMakeThreadIOUFunctionMA1(A, a, int, &A::bar, char, `x');
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 *
 * <table>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the third argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c R</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class Callee.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c A3</td>
 * <td>Type name of the second argument.</td>
 * </tr>
 * <tr>
 * <td>\a a3</td>
 * <td>Expression that can be converted to an instance of \c A3.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWTThreadIOUFunction
 */


/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the concurrency policy. If this macro is not defined, any
 * attempt to set the concurrency policy will fail.
 */
#define RW_THR_HAS_CONCURRENCY_POLICY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the contention scope. If this macro is not defined, any
 * attempt to set the contention scope will fail.
 */
#define RW_THR_HAS_CONTENTION_SCOPE

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * dual priority threads.
 */
#define RW_THR_HAS_DUAL_PRIORITY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the inheritance policy. If this macro is not defined, any
 * attempt to set the inheritance policy will fail.
 */
#define RW_THR_HAS_INHERITANCE_POLICY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * determining the maximum number of user threads. If this macro is not
 * defined any attempt to get the maximum thread count will fail.
 */
#define RW_THR_HAS_MAX_THREADS

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment allows partial
 * stack commitment and the stack commit size may be set to a value less
 * than the stack reserve size. If this macro is not defined, then the stack
 * reserve size and stack commit size attributes are mutually exclusive and
 * only one or the other may be set.
 */
#define RW_THR_HAS_PARTIAL_STACK_COMMITMENT

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * getting and setting thread priorities. If this macro is not defined, any
 * attempt to get or set the thread priority will fail.
 */
#define RW_THR_HAS_PRIORITY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying process scope priority. If this macro is not defined, any
 * attempt to set the process scope priority will fail.
 */
#define RW_THR_HAS_PROCESS_SCOPE_PRIORITY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the scheduling policy. If this macro is not defined, any
 * attempt to set the scheduling policy will fail.
 */
#define RW_THR_HAS_SCHEDULING_POLICY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the stack commit size. If this macro is not defined, any
 * attempt to set the stack commit size will fail.
 */
#define RW_THR_HAS_STACK_COMMIT_SIZE

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the stack reserve size. If this macro is not defined, any
 * attempt to set the stack reserve size will fail.
 */
#define RW_THR_HAS_STACK_RESERVE_SIZE

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying a start policy. If this macro is not defined, any attempt to
 * set the start policy will fail.
 */
#define RW_THR_HAS_START_POLICY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the contention scope. If this macro is not defined, any
 * attempt to suspend or resume a thread will fail.
 */
#define RW_THR_HAS_SUSPEND_RESUME

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying system scope priority. If this macro is not defined, any
 * attempt to set the priority of a system scope thread will fail.
 */
#define RW_THR_HAS_SYSTEM_SCOPE_PRIORITY

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying the time slice quantum. If this macro is not defined, any
 * attempt to set the time slice quantum will fail.
 */
#define RW_THR_HAS_TIME_SLICE_QUANTUM

/**
 * \ingroup threading_package
 *
 * This configuration macro indicates the build environment has support for
 * specifying a user stack. If this macro is not defined, any attempt to set
 * a user stack will fail.
 */
#define RW_THR_HAS_USER_STACK

#endif // rw_thread_doxygen_h__ 
