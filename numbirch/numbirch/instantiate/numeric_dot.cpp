/**
 * @file
 */
#ifdef BACKEND_CUDA
#include "numbirch/cuda/numeric.hpp"
#endif
#ifdef BACKEND_EIGEN
#include "numbirch/eigen/numeric.hpp"
#endif

/**
 * @internal
 * 
 * @def DOT
 * 
 * Explicitly instantiate dot().
 */
#define DOT(f) \
    DOT_SIG(f, real)
#define DOT_SIG(f, T) \
    template Array<T,0> f(const Array<T,1>&, const Array<T,1>&);


namespace numbirch {
DOT(dot)
}