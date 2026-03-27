#ifndef rw_functor_map_doxygen_h__
#define rw_functor_map_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup functor_map_package Functor Map
 * \ingroup functor_module
 *
 * The Functor Map subpackage is made up of classes designed for creating
 * functors that are themselves a collection of functors, one of which is to
 * be invoked according to a given key. Functor map classes are an extension
 * to the functor class hierarchy.
 *
 * Class names are constructed from the base name \b RWTFunctorMap by adding
 * \b 1 or \b 2 for the number of caller arguments and an optional \b R if
 * the map returns a value. Because every functor map invocation requires a
 * key, there is no \b RWTFunctorMap0.
 *
 * The formal template parameters include:
 * <table>
 * <tr>
 * <td>\c SR</td>
 * <td>The type of the functor's map's return value.</td>
 * </tr>
 * <tr>
 * <td>\c Key</td>
 * <td>The type of the functor map's key (which is the functor map's first
 * argument).</td>
 * </tr>
 * <tr>
 * <td>\c S1</td>
 * <td>The type of the encapsulated functor's first argument (which is the
 * functor map's second argument).</td>
 * </tr>
 * </table>
 */

#endif // rw_functor_map_doxygen_h__ 
