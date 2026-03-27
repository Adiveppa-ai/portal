#ifndef rw_functor_doxygen_h__
#define rw_functor_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup functor_module Functors
 * \ingroup threads_module
 *
 * The Functor package supplies interfaces for invocation that are
 * independent of the actual functions. You can combine the functor classes
 * with others in the Threads Module to transform your existing
 * single-threaded code into multithreaded code.
 *
 * For complete information about the Functor package, see the <em>Threads
 * Module User's Guide</em>.
 */

/**
 * \defgroup functor0_group rwtMakeFunctor0 Macros and Functions
 * \ingroup functor_module
 *
 * \headerfileloc{#include <rw/functor/functor0.h>}
 *
 * A function object, or functor, is an object that encapsulates a call to
 * an associated global or member function. When a functor is invoked, it
 * calls the associated function.
 *
 * The rwtMakeFunctor0() functions and macros are provided to construct
 * functors based on the RWFunctor0 class. The RWFunctor0 class acts as the
 * handle for a family of functor implementation classes based on the
 * RWFunctor0Imp class. A functor based on RWFunctor0 is invoked with no
 * arguments and returns no value, but the implementation classes can accept
 * functions with up to three arguments and any return type. The values for
 * the additional arguments are defined when an implementation class
 * instance is constructed, and are passed to the function each time the
 * functor is invoked.
 *
 * Each rwtMakeFunctor0() function or macro instantiates and constructs an
 * appropriate functor implementation class instance and returns an
 * RWFunctor0 handle that is bound to that instance.
 *
 * rwtMakeFunctor0() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and because we
 * cannot overload macros, each must have a unique name.
 *
 * In naming the macros, we have employed a convention to make the names
 * easier to remember. Each name begins with rwtMakeFunctor0(), which will
 * be followed by either a \c G if the macro is expecting a global function,
 * or an \c M if it is expecting a member function. At that point, the name
 * is complete if the associated global or member function takes no
 * arguments. Otherwise we add one of \c A1, \c A2, or \c A3 for functions
 * with 1, 2, or 3 arguments respectively. For example, you will use macro
 * #rwtMakeFunctor0G() to create a functor that calls a <em>global
 * function</em> that takes <em>no arguments</em>. The macro
 * #rwtMakeFunctor0MA2() will create a functor that calls a <em>member
 * function</em> that takes <em>two arguments</em>.
 *
 * \example
 * Example Using Templates
 *
 * \code
 * class A {
 * public:
 *     int bar(char);  // Member function with 1 argument
 * };
 *
 * A a;  // an instance of class A
 *
 * int foo(double, long);  // Global function with 2 arguments
 *
 * // Create an rwtFunctor0 set to call foo(3.14,11):
 * RWFunctor0 t1 = rwtMakeFunctor0(NULL, foo, 3.14, 11);
 *
 * // Create an rwtFunctor0 set to call a.bar(`x'):
 * RWFunctor0 t2 = rwtMakeFunctor0(NULL, a, &A::bar, `x');
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * class A {
 * public:
 *     int bar(char);  // Member function with 1 argument
 * };
 *
 * A a;              // An instance of class A
 *
 * int foo(double, long);  // Global function with 2 arguments
 *
 * // Create an rwtFunctor0 set to call foo(3.14,11):
 * RWFunctor0 t1
 *    = rwtMakeFunctor0GA2(int, foo, double, 3.14, long, 11);
 *
 * // Create an rwtFunctor0 set to call a.bar(`x'):
 * RWFunctor0 t2
 *    = rwtMakeFunctor0MA1(A, a, int, &A::bar, char, `x');
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c DR</td>
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
 * <td>\c DR</td>
 * <td>Type name of the function return value.</td>
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
 * RWFunctor0, RWFunctor0Imp
 */

/**
 * \defgroup functor1_group rwtMakeFunctor1 Macros and Functions
 * \ingroup functor_module
 *
 * \headerfileloc{#include <rw/functor/functor1.h>}
 *
 * A function object, or functor, is an object that encapsulates a call to
 * an associated global or member function. When a functor is invoked, it
 * calls the associated function.
 *
 * The rwtMakeFunctor1() functions and macros are provided to construct
 * functors based on the RWTFunctor1 class. The RWTFunctor1 class acts as
 * the handle for a family of functor implementation classes based on the
 * RWTFunctor1Imp class. A functor based on RWTFunctor1 is invoked with one
 * argument and returns no value, but the implementation classes can accept
 * functions with up to two additional arguments and any return type. The
 * values for the additional arguments are defined when an implementation
 * class instance is constructed, and are passed to the function each time
 * the functor is invoked.
 *
 * Each rwtMakeFunctor1() function or macro instantiates and constructs an
 * appropriate functor implementation class instance and returns an
 * RWTFunctor1 handle that is bound to that instance.
 *
 * rwtMakeFunctor1() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and because we
 * cannot overload macros, each must have a unique name.
 *
 * In naming the macros, we have employed a convention to make the names
 * easier to remember. Each name begins with rwtMakeFunctor1(), which will
 * be followed by either a \c G if the macro is expecting a global function,
 * or an \c M if it is expecting a member function. At that point, the name
 * is complete if the associated global or member function takes no
 * additional arguments. Otherwise we add one of \c A1 or \c A2 for
 * functions with 1 or 2 additional arguments respectively. For example, you
 * will use macro #rwtMakeFunctor1G() to create a functor that calls a
 * <em>global function</em> that takes <em>no additional arguments</em>. The
 * macro #rwtMakeFunctor1MA2() will create a functor that calls a <em>member
 * function</em> that takes <em>two additional arguments</em>.
 *
 * \example
 * Example Using Templates
 *
 * \code
 * class A {
 * public:
 * int bar(char);        // Member function with 1 argument
 *                       // (no additional)
 * };
 *
 * A a;                    // an instance of class A
 *
 * float s;
 * char  c;
 *
 * int foo(double, long);  // Global function with 2 args
 *                         // (1 additional)
 *
 * // Create an RWTFunctor1 set to call foo(s, 11):
 * RWTFunctor1<float> t1
 *           = rwtMakeFunctor1((void(*)(float))NULL, foo, 11);
 *
 * // Create an RWTFunctor1 set to call a.bar(c):
 * RWTFunctor1<char> t2
 *           = rwtMakeFunctor1((void(*)(char))NULL, a, &A::bar);
 *
 * s = 3.14;
 * c = 'x';
 *
 * t1(s);  // calls foo(s,11);
 * t2(c);  // calls a.bar(c);
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * class A {
 * public:
 *   int bar(char);  // Member function with 1 argument
 *                   // (no additional)
 * };
 *
 * A a;  // an instance of class A
 *
 * float s;
 * char  c;
 *
 * int foo(double, long);  // Global function with 2 args
 *                         // (1 additional)
 *
 * // Create an RWTFunctor1 set to call foo(s, 11):
 * RWTFunctor1<float> t1
 *          = rwtMakeFunctor1GA1(float, int, foo, double, long, 11);
 *
 * // Create an RWTFunctor1 set to call a.bar(c):
 * RWTFunctor1<char> t2
 *          = rwtMakeFunctor1M(char, A, a, int, &A::bar, char);
 *
 * s = 3.14;
 * c = 'x';
 *
 * t1(s);  // calls foo(s,11);
 * t2(c);  // calls a.bar(c);
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctor1<S1>::operator()(S1)</tt>. \c S1 must be
 * convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a D1</td>
 * <td>Type name of the first argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\a s</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctor1<S1>::operator()(S1)</tt>. \c S1 must be
 * convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee</td>
 * </tr>
 * <tr>
 * <td>\c D1</td>
 * <td>Type name of the first argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\a s</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWTFunctor1, RWTFunctor1Imp
 */

/**
 * \defgroup functor2_group rwtMakeFunctor2 Macros and Functions
 * \ingroup functor_module
 *
 * \headerfileloc{#include <rw/functor/functor2.h>}
 *
 * A function object, or functor, is an object that encapsulates a call to
 * an associated global or member function. When a functor is invoked, it
 * calls the associated function.
 *
 * The rwtMakeFunctor2() functions and macros are provided to construct
 * functors based on the RWTFunctor2 class. The RWTFunctor2 class acts as
 * the handle for a family of functor implementation classes based on the
 * RWTFunctor2Imp class. A functor based on RWTFunctor2 is invoked with two
 * arguments and returns no value, but the implementation classes can accept
 * functions with up to two additional arguments and any return type. The
 * values for the additional arguments are defined when an implementation
 * class instance is constructed, and are passed to the function each time
 * the functor is invoked.
 *
 * Each rwtMakeFunctor2() function or macro instantiates and constructs an
 * appropriate functor implementation class instance and returns an
 * RWTFunctor2 handle that is bound to that instance.
 *
 * rwtMakeFunctor2() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and because we
 * cannot overload macros, each must have a unique name.
 *
 * In naming the macros, we have employed a convention to make the names
 * easier to remember. Each name begins with rwtMakeFunctor2(), which will
 * be followed by either a \c G if the macro is expecting a global function,
 * or an \c M if it is expecting a member function. At that point, the name
 * is complete if the associated global or member function takes no
 * additional arguments. Otherwise we add one of \c A1 or \c A2 for
 * functions with 1 or 2 additional arguments respectively. For example, you
 * will use macro #rwtMakeFunctor2G() to create a functor that calls a
 * <em>global function</em> that takes <em>no additional arguments</em>. The
 * macro #rwtMakeFunctor2MA2() will create a functor that calls a <em>member
 * function</em> that takes <em>two additional arguments</em>.
 *
 * \example
 * Example Using Templates
 *
 * \code
 * class A {
 * public:
 *  int bar(char,int);  // Member function with 2 args
 *                      // (no additional)
 * };
 *
 * A a;                 // an instance of class A
 *
 * float s1;
 * int   s2;
 *
 * char  c1, c2;
 *
 * // Global function with 3 args (1 additional):
 * int foo(double, long, char);
 *
 * // Create an rwTFunctor2 set to call foo(s1,s2,11):
 * RWTFunctor2<float,int> t1
 *      = rwtMakeFunctor2((void(*)(float,int))NULL, foo, 11);
 *
 * // Create an rwTFunctor2 set to call a.bar(c1,c2):
 * RWTFunctor2<char,char> t2
 *      = rwtMakeFunctor2((void(*)(char,char))NULL, a, &A::bar);
 *
 * s1 = 3.14; s2 = 1.41;
 * c1 = 'x';  c2 = 'y';
 *
 * t1(s1,s2);              // calls foo(s1,s2,11);
 * t2(c1,c2);              // calls a.bar(c1,c2);
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * class A {
 * public:
 *   int bar(char,int);    // Member function with 2 args
 *                         // (no additional)
 * };
 *
 * A a;                    // an instance of class A
 *
 * float s1;
 * int   s2;
 *
 * char  c1, c2;
 *
 * // Global function with 3 arguments (1 additional)
 * int foo(double, long, char);
 *
 * // Create an rwTFunctor2 set to call foo(s1,s2,11):
 * RWTFunctor2<float,int> t1
 *   = rwtMakeFunctor2GA1(float,int,int,foo,double,long,char,11);
 *
 * // Create an rwTFunctor2 set to call a.bar(c1,c2):
 * RWTFunctor2<char,char> t2
 *   = rwtMakeFunctor2M(char,char,A,a,int,&A::bar,char,int);
 *
 * s1 = 3.14; s2 = 1.41;
 * c1 = 'x';  c2 = 'y';
 *
 * t1(s1,s2);  // calls foo(s1,s2,11);
 * t2(c1,c2);  // calls a.bar(c1,c2);
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. \c S1
 * must be convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c S2</td>
 * <td>Type name of the second argument that will be expected when invoking
 * the functor via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. \c S2
 * must be convertible to \c D2.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a D1</td>
 * <td>Type name of the first argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\a D2</td>
 * <td>Type name of the second argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\a s1</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * <tr>
 * <td>\a s2</td>
 * <td>Argument of type \c S2 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. \c S1
 * must be convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c S2</td>
 * <td>Type name of the second argument that will be expected when invoking
 * the functor via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. \c S2
 * must be convertible to \c D2.</td>
 * </tr>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee</td>
 * </tr>
 * <tr>
 * <td>\c D1</td>
 * <td>Type name of the first argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\c A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of \c A1.</td>
 * </tr>
 * <tr>
 * <td>\c A2</td>
 * <td>Type name of the second additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of \c A2.</td>
 * </tr>
 * <tr>
 * <td>\c s1</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * <tr>
 * <td>\c s2</td>
 * <td>Argument of type \c S2 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWTFunctor2, RWTFunctor2Imp
 */

/**
 * \defgroup functorR0_group rwtMakeFunctorR0 Macros and Functions
 * \ingroup functor_module
 *
 * \headerfileloc{#include <rw/functor/functorR0.h>}
 *
 * A function object, or functor, is an object that encapsulates a call to
 * an associated global or member function. When a functor is invoked, it
 * calls the associated function.
 *
 * The rwtMakeFunctorR0() functions and macros are provided to construct
 * functors based on the RWTFunctorR0 class. The RWTFunctorR0 class acts as
 * the handle for a family of functor implementation classes based on the
 * RWTFunctorR0Imp class. A functor based on RWTFunctorR0 is invoked with no
 * arguments and returns a value of type \c SR, but the implementation
 * classes can accept functions with up to three arguments. The values for
 * the additional arguments are defined when an implementation class
 * instance is constructed, and are passed to the function each time the
 * functor is invoked.
 *
 * Each rwtMakeFunctorR0() function or macro instantiates and constructs an
 * appropriate functor implementation class instance and returns an
 * RWTFunctorR0 handle that is bound to that instance.
 *
 * rwtMakeFunctorR0() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and because we
 * cannot overload macros, each must have a unique name.
 *
 * In naming the macros, we have employed a convention to make the names
 * easier to remember. Each name begins with rwtMakeFunctorR0(), which will
 * be followed by either a \c G if the macro is expecting a global function,
 * or an \c M if it is expecting a member function. At that point, the name
 * is complete if the associated global or member function takes no
 * arguments. Otherwise we add one of \c A1, \c A2, or \c A3 for functions
 * with 1, 2, or 3 arguments respectively. For example, you will use macro
 * #rwtMakeFunctorR0G() to create a functor that calls a <em>global
 * function</em> that takes <em>no arguments</em>. The macro
 * #rwtMakeFunctorR0MA2() will create a functor that calls a <em>member
 * function</em> that takes <em>two arguments</em>.
 *
 * \example
 * Example Using Templates
 *
 * \code
 * #include <rw/functor/functorR0.h>
 *
 * class A {
 * public:
 * int bar(char);         // Member function with 1 argument
 * };
 *
 * int main()
 * {
 *  A a;                    // an instance of class A
 *
 *  int foo(double, long);  // Global function with 2 arguments
 *
 *  // Create an RWTFunctorR0 set to call foo(3.14,11):
 *  RWTFunctorR0<int> t1
 *        = rwtMakeFunctorR0((int(*)(void))NULL, foo, 3.14, 11);
 *
 *  // Create an RWTFunctorR0 set to call a.bar('x'):
 *  RWTFunctorR0<int> t2
 *        = rwtMakeFunctorR0((int(*)(void))NULL, a, &A::bar, 'x');
 *
 *  int result1 = t1();
 *  int result2 = t2();
 *
 *  return 0;
 * }
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * #include <rw/functor/functorR0.h>
 *
 * class A {
 * public:
 *   int bar(char);  // Member function with 1 argument
 * };
 *
 * int main()
 * {
 *   A a;  // an instance of class A
 *
 *   int foo(double, long);  // Global function with 2 arguments
 *
 *   // Create an RWTFunctorR0 set to call foo(3.14,11):
 *   RWTFunctorR0<int> t1
 *     = rwtMakeFunctorR0GA2(int, int, foo, double, 3.14, long, 11);
 *
 *   // Create an RWTFunctorR0 set to call a.bar('x'):
 *   RWTFunctorR0<int> t2
 *     = rwtMakeFunctorR0MA1(int, A, a, int, &A::bar, char, 'x');
 *
 *   int result1 = t1();
 *   int result2 = t2();
 * return 0;
 * }
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c SR</td>
 * <td>The actual type name to be used to instantiate the RWTFunctorR0.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. \c DR must be convertible to
 * \c SR.</td>
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
 * <td>\c SR</td>
 * <td>The actual type name to be used to instantiate the RWTFunctorR0.</td>
 * </tr>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. \c DR must be convertible to
 * \c SR.</td>
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
 * RWTFunctorR0, RWTFunctorR0Imp
 */

/**
 * \defgroup functorR1_group rwtMakeFunctorR1 Macros and Functions
 * \ingroup functor_module
 *
 * \headerfileloc{#include <rw/functor/functorR1.h>}
 *
 * A function object, or functor, is an object that encapsulates a call to
 * an associated global or member function. When a functor is invoked, it
 * calls the associated function.
 *
 * The rwtMakeFunctorR1() functions and macros are provided to construct
 * functors based on the RWTFunctorR1 class. The RWTFunctorR1 class acts as
 * the handle for a family of functor implementation classes based on the
 * RWTFunctorR1Imp class. A functor based on RWTFunctorR1 is invoked with
 * one argument and returns a value of type \c SR, while the implementation
 * classes can accept functions with up to two additional arguments. The
 * values for the additional arguments are defined when an implementation
 * class instance is constructed, and are passed to the function each time
 * the functor is invoked.
 *
 * Each rwtMakeFunctorR1() function or macro instantiates and constructs an
 * appropriate functor implementation class instance and returns an
 * RWTFunctorR1 handle that is bound to that instance.
 *
 * rwtMakeFunctorR1() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and because we
 * cannot overload macros, each must have a unique name.
 *
 * In naming the macros, we have employed a convention to make the names
 * easier to remember. Each name begins with rwtMakeFunctorR1(), which will
 * be followed by either a \c G if the macro is expecting a global function,
 * or an \c M if it is expecting a member function. At that point, the name
 * is complete if the associated global or member function takes no
 * additional arguments. Otherwise we add one of \c A1 or \c A2 for
 * functions with 1 or 2 additional arguments respectively. For example, you
 * will use macro #rwtMakeFunctorR1G() to create a functor that calls a
 * <em>global function</em> that takes <em>no additional arguments</em>. The
 * macro #rwtMakeFunctorR1MA2() will create a functor that calls a
 * <em>member function</em> that takes <em>two additional arguments</em>.
 *
 * \example
 * Example Using Templates
 *
 * \code
 * #include <iostream.h>
 * #include <rw/functor/RWTFunctorR1.h>
 * #include <rw/functor/rwtMakeFunctorR1.h>
 *
 * class A {
 * public:
 * int bar(char);           // Member function with 1 argument
 *                          // (no additional)
 * };
 *
 * int main()
 * {
 *
 *     A a;                    // an instance of class A
 *
 *     float s;
 *     char  c;
 *
 *     int foo(double, long);   // Global function with 2 args
 *                              // (1 additional)
 *
 *     // Create an RWTFunctorR1 set to call foo(s, 11):
 *     RWTFunctorR1<int,double> t1
 *           = rwtMakeFunctorR1((int(*)(float))NULL, foo, 11);
 *
 *     // Create an RWTFunctorR1 set to call a.bar(c):
 *     RWTFunctorR1<int,char> t2
 *           = rwtMakeFunctorR1((int(*)(char))NULL, a, &A::bar);
 *
 *     s = 3.14;
 *     c = 'x';
 *
 *     int result1 = t1(s);    // calls foo(s,11);
 *     int result2 = t2(c);    // calls a.bar(c);
 *
 *     return 0;
 * }
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * #include <iostream.h>
 * #include <rw/functor/RWTFunctorR1.h>
 * #include <rw/functor/rwtMakeFunctorR1.h>
 *
 * class A {
 * public:
 *   int bar(char);         // Member function with 1 argument
 *                          // (no additional)
 * };
 *
 * int main()
 * {
 *   A a;  // an instance of class A
 *
 *   float s;
 *   char  c;
 *
 *   // Global function with 2 arguments (1 additional):
 *   int foo(double, long);
 *
 *   // Create an RWTFunctorR1 set to call foo(s, 11):
 *   RWTFunctorR1<int,float> t1
 *     = rwtMakeFunctorR1GA1(int,float, int, foo, double, long, 11);
 *
 *   // Create an RWTFunctorR1 set to call a.bar(c):
 *   RWTFunctorR1<int,char> t2
 *     = rwtMakeFunctorR1M(int,char, A, a, int, &A::bar, char);
 *
 *   s = 3.14;
 *   c = 'x';
 *
 *   int result1 = t1(s);  // calls foo(s,11);
 *   int result2 = t2(c);  // calls a.bar(c);
 *
 *   return 0;
 * }
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c SR</td>
 * <td>The actual type name to be used to instantiate the RWTFunctorR1.</td>
 * </tr>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. \c S1 must
 * be convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. \c DR must be convertible to
 * \c SR.</td>
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
 * <td>\a s</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c SR</td>
 * <td>The actual type name to be used to instantiate the RWTFunctorR1.</td>
 * </tr>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. \c S1 must
 * be convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. \c DR must be convertible to
 * \c SR.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee</td>
 * </tr>
 * <tr>
 * <td>\c D1</td>
 * <td>Type name of the first argument of the function.</td>
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
 * <td>\a s</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWTFunctorR1, RWTFunctorR1Imp
 */

/**
 * \defgroup functorR2_group rwtMakeFunctorR2 Macros and Functions
 * \ingroup functor_module
 *
 * \headerfileloc{#include <rw/functor/functorR2.h>}
 *
 * A function object, or functor, is an object that encapsulates a call to
 * an associated global or member function. When a functor is invoked, it
 * calls the associated function.
 *
 * The rwtMakeFunctorR2() functions and macros are provided to construct
 * functors based on the RWTFunctorR2 class. The RWTFunctorR2 class acts as
 * the handle for a family of functor implementation classes based on the
 * RWTFunctorR2Imp class. A functor based on RWTFunctorR2 is invoked with
 * one argument and returns a value of type \c SR, while the implementation
 * classes can accept functions with up to two additional arguments. The
 * values for the additional arguments are defined when an implementation
 * class instance is constructed, and are passed to the function each time
 * the functor is invoked.
 *
 * Each rwtMakeFunctorR2() function or macro instantiates and constructs an
 * appropriate functor implementation class instance and returns an
 * RWTFunctorR2 handle that is bound to that instance.
 *
 * rwtMakeFunctorR2() comes in two flavors. First, there is a set of
 * overloaded global function templates. Since not all compilers are able to
 * handle templates to the degree required by these functions, we also
 * provide a corresponding set of macros. The template functions are
 * slightly easier to use and you only have to remember one name. The macros
 * are more portable but they do require more arguments; and because we
 * cannot overload macros, each must have a unique name.
 *
 * In naming the macros, we have employed a convention to make the names
 * easier to remember. Each name begins with rwtMakeFunctorR2(), which will
 * be followed by either a \c G if the macro is expecting a global function,
 * or an \c M if it is expecting a member function. At that point, the name
 * is complete if the associated global or member function takes no
 * additional arguments. Otherwise we add one of \c A1 or \c A2 for
 * functions with 1 or 2 additional arguments respectively. For example, you
 * will use macro #rwtMakeFunctorR2G() to create a functor that calls a
 * <em>global function</em> that takes <em>no additional arguments</em>. The
 * macro #rwtMakeFunctorR2MA2() will create a functor that calls a
 * <em>member function</em> that takes <em>two additional arguments</em>.
 *
 * \example
 * Example Using Templates
 *
 * \code
 * #include <rw/functor/functorR2.h>
 *
 * class A {
 * public:
 *     int bar(char,int);  // Member function with 2 args
 *                         // (no additional)
 * };
 *
 * int main()
 * {
 *     A a;  // an instance of class A
 *
 *     float s1;
 *     int   s2;
 *
 *     char  c1, c2;
 *
 *     // Global function with 3 args (1 additional):
 *     int foo(double, long, char);
 *
 *     // Create an RWTFunctorR2 set to call foo(s1,s2,11):
 *     RWTFunctorR2<int,float,int> t1
 *         = rwtMakeFunctorR2((int(*)(float,int))NULL, foo, 11);
 *
 *     // Create an RWTFunctorR2 set to call a.bar(c1,c2):
 *     RWTFunctorR2<int,char,char> t2
 *         = rwtMakeFunctorR2((int(*)(char,char))NULL, a, &A::bar);
 *
 *     s1 = 3.14; s2 = 1.41;
 *     c1 = 'x';  c2 = 'y';
 *
 *     int result1 = t1(s1,s2);  // calls foo(s1,s2,11);
 *     int result2 = t2(c1,c2);  // calls a.bar(c1,c2);
 *
 *     return 0;
 * }
 * \endcode
 *
 * Example Using Macros
 *
 * \code
 * #include <rw/functor/functorR2.h>
 *
 * class A {
 * public:
 *   int bar(char,int);  // Member function with 2 args
 *                       // (no additional)
 * };
 *
 * int main()
 * {
 *   A a;  // an instance of class A
 *
 *   float s1;
 *   int   s2;
 *
 *   char  c1, c2;
 *
 *   // Global function with 3 args (1 additional):
 *   int foo(double, long, char);
 *
 *   // Create an RWTFunctorR2 set to call foo(s1,s2,11):
 *   RWTFunctorR2<int,float,int> t1
 *     = rwtMakeFunctorR2GA1(int,float,int,int,foo,
 *                           double,long,char,11);
 *
 *   // Create an RWTFunctorR2 set to call a.bar(c1,c2):
 *   RWTFunctorR2<int,char,char> t2
 *     = rwtMakeFunctorR2M(int,char,char,A,a,int,&A::bar,char,int);
 *
 *   s1 = 3.14; s2 = 1.41;
 *   c1 = 'x';  c2 = 'y';
 *
 *   int result1 = t1(s1,s2);  // calls foo(s1,s2,11);
 *   int result2 = t2(c1,c2);  // calls a.bar(c1,c2);
 *   return 0;
 * }
 * \endcode
 * \endexample
 *
 * <h4>Macros (for Use With Global Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c SR</td>
 * <td>The actual type name to be used to instantiate the RWTFunctorR2.</td>
 * </tr>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctorR2<SR,S1,S2>::operator()(S1,S2)</tt>. \c S1
 * must be convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c S2</td>
 * <td>Type name of the second argument that will be expected when invoking
 * the functor via <tt>RWTFunctorR2<SR,S1,S2>::operator()(S1,S2)</tt>. \c S2
 * must be convertible to \c D2.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. \c DR must be convertible to
 * \c SR.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\c D1</td>
 * <td>Type name of the first argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\c D2</td>
 * <td>Type name of the second argument of the function.</td>
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
 * <td>\a s1</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * <tr>
 * <td>\a s2</td>
 * <td>Argument of type \c S2 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * <h4>Macros (for Use With Member Functions)</h4>
 * The macros in this section use the following naming conventions for the
 * macro arguments:
 * <table>
 * <tr>
 * <td>\c SR</td>
 * <td>The actual type name to be used to instantiate the RWTFunctorR2.</td>
 * </tr>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the first argument that will be expected when invoking
 * the functor via <tt>RWTFunctorR2<SR,S1,S2>::operator()(S1,S2)</tt>. \c S1
 * must be convertible to \c D1.</td>
 * </tr>
 * <tr>
 * <td>\c S2</td>
 * <td>Type name of the second argument that will be expected when invoking
 * the functor via <tt>RWTFunctorR2<SR,S1,S2>::operator()(S1,S2)</tt>. \c S2
 * must be convertible to \c D2.</td>
 * </tr>
 * <tr>
 * <td>\c Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a \c Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\c DR</td>
 * <td>Type name of the function return value. \c DR must be convertible to
 * \c SR.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Pointer to member function of class \c Callee</td>
 * </tr>
 * <tr>
 * <td>\c D1</td>
 * <td>Type name of the first argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\c D2</td>
 * <td>Type name of the second argument of the function.</td>
 * </tr>
 * <tr>
 * <td>\c D1</td>
 * <td>Type name of the first argument of the function.</td>
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
 * <td>\a s1</td>
 * <td>Argument of type \c S1 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * <tr>
 * <td>\a s2</td>
 * <td>Argument of type \c S2 that will be passed when invoking the
 * functor.</td>
 * </tr>
 * </table>
 *
 * \sa
 * RWTFunctorR2, RWTFunctorR2Imp
 */

#endif // rw_functor_doxygen_h__ 
