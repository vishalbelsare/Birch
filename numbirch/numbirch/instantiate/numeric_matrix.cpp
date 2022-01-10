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
 * @def MATRIX
 * 
 * Explicitly instantiate a unary function `f` over floating point matrices.
 * Use cases include transpose(), inv().
 */
#define MATRIX(f) \
    MATRIX_SIG(f, real)
#define MATRIX_SIG(f, T) \
    template Array<T,2> f(const Array<T,2>&);

namespace numbirch {
MATRIX(cholinv)
MATRIX(inv)
MATRIX(transpose)
}