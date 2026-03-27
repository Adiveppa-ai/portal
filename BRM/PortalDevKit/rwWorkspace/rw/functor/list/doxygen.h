#ifndef rw_functor_list_doxygen_h__
#define rw_functor_list_doxygen_h__

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup functor_list Functor List
 * \ingroup functor_module
 *
 * The Functor List subpackage is made up of classes designed for creating
 * functors that are themselves lists of functors to be invoked in turn.
 * Functor list classes are an extension to the functor class hierarchy.
 *
 * Class names are constructed from the base name \b RWTFunctorList for
 * templatized classes or RWFunctorList for the few non-templatized classes
 * by adding \b 0, \b 1 or \b 2 for the number of caller arguments.
 *
 * The formal template parameters include:
 * <table>
 * <tr>
 * <td>\c S1</td>
 * <td>Type name of the functor list's first argument.</td>
 * </tr>
 * <tr>
 * <td>\c S2</td>
 * <td>Type name of the functor list's second argument.</td>
 * </tr>
 * </table>
 *
 * \note
 * Functor lists do not provide \b R0, \b R1, or \b R2 classes.
 */

#endif // rw_functor_list_doxygen_h__ 
