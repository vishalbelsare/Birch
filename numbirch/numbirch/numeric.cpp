/**
 * @file
 */
#include "numbirch/numeric.hpp"

#ifdef BACKEND_CUDA
#include "numbirch/cuda/numeric.hpp"
#endif

/**
 * @internal
 * 
 * @def ARRAY
 * 
 * Constructs the type `Array<T,D>`.
 */
#define ARRAY(T, D) Array<T,D>

/**
 * @internal
 * 
 * @def UNARY_ARITHMETIC
 * 
 * Explicit instantiate a unary transformation `f` for all types.
 */
#define UNARY_ARITHMETIC_INSTANTIATION(f, T) \
    template T f(const T&);
#define UNARY_ARITHMETIC_INSTANTIATIONS(f, T) \
    UNARY_ARITHMETIC_INSTANTIATION(f, ARRAY(T, 2)) \
    UNARY_ARITHMETIC_INSTANTIATION(f, ARRAY(T, 1)) \
    UNARY_ARITHMETIC_INSTANTIATION(f, ARRAY(T, 0))
#define UNARY_ARITHMETIC(f) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, double) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, float) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, int) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, bool)

/**
 * @internal
 * 
 * @def UNARY_INTEGRAL
 * 
 * Explicitly instantiate a unary transformation `f` for integral types only.
 */
#define UNARY_INTEGRAL(f) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, int) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, bool)

/**
 * @internal
 * 
 * @def UNARY_INTEGRAL
 * 
 * Explicitly instantiate a unary transformation `f` for floating point types
 * only.
 */
#define UNARY_FLOATING_POINT(f) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, double) \
    UNARY_ARITHMETIC_INSTANTIATIONS(f, float)

/**
 * @internal
 * 
 * @def UNARY_MATRIX
 * 
 * Explicitly instantiate a unary function `f` for a matrix for floating point
 * types only. Use cases include inv(), cholinv(), transpose().
 */
#define UNARY_MATRIX(f) \
    template Array<double,2> f(const Array<double,2>&); \
    template Array<float,2> f(const Array<float,2>&);

/**
 * @internal
 * 
 * @def REDUCE_MATRIX
 * 
 * Explicitly instantiate a reduction function `f` for a matrix for floating
 * point types only. Use cases include ldet(), lcholdet(), trace().
 */
#define REDUCE_MATRIX(f) \
    template Array<double,0> f(const Array<double,2>&); \
    template Array<float,0> f(const Array<float,2>&);

/**
 * @internal
 * 
 * @def SINGLE_VECTOR
 * 
 * For single().
 */
#define SINGLE_VECTOR_INSTANTIATION(f, T, U) \
    template Array<T,1> f(const U& i, const int n);
#define SINGLE_VECTOR_INSTANTIATIONS(f, T) \
    SINGLE_VECTOR_INSTANTIATION(f, T, int) \
    SINGLE_VECTOR_INSTANTIATION(f, T, ARRAY(int, 0))
#define SINGLE_VECTOR(f) \
    SINGLE_VECTOR_INSTANTIATIONS(f, double) \
    SINGLE_VECTOR_INSTANTIATIONS(f, float) \
    SINGLE_VECTOR_INSTANTIATIONS(f, int) \
    SINGLE_VECTOR_INSTANTIATIONS(f, bool)

/**
 * @internal
 * 
 * @def SINGLE_MATRIX
 * 
 * For single().
 */
#define SINGLE_MATRIX_INSTANTIATION(f, T, U, V) \
    template Array<T,2> f(const U& i, const V& j, const int m, const int n);
#define SINGLE_MATRIX_INSTANTIATIONS(f, T) \
    SINGLE_MATRIX_INSTANTIATION(f, T, ARRAY(int, 0), ARRAY(int, 0)) \
    SINGLE_MATRIX_INSTANTIATION(f, T, ARRAY(int, 0), int) \
    SINGLE_MATRIX_INSTANTIATION(f, T, int, ARRAY(int, 0)) \
    SINGLE_MATRIX_INSTANTIATION(f, T, int, int)
#define SINGLE_MATRIX(f) \
    SINGLE_MATRIX_INSTANTIATIONS(f, double) \
    SINGLE_MATRIX_INSTANTIATIONS(f, float) \
    SINGLE_MATRIX_INSTANTIATIONS(f, int) \
    SINGLE_MATRIX_INSTANTIATIONS(f, bool)

/**
 * @internal
 * 
 * @def DIAGONAL_MATRIX
 * 
 * For diagonal().
 */
#define DIAGONAL_MATRIX_INSTANTIATION(f, T) \
    template Array<value_t<T>,2> f(const T& x, const int n);
#define DIAGONAL_MATRIX_INSTANTIATIONS(f, T) \
    DIAGONAL_MATRIX_INSTANTIATION(f, T) \
    DIAGONAL_MATRIX_INSTANTIATION(f, ARRAY(T, 0))
#define DIAGONAL_MATRIX(f) \
    DIAGONAL_MATRIX_INSTANTIATIONS(f, double) \
    DIAGONAL_MATRIX_INSTANTIATIONS(f, float) \
    DIAGONAL_MATRIX_INSTANTIATIONS(f, int) \
    DIAGONAL_MATRIX_INSTANTIATIONS(f, bool)

/**
 * @internal
 * 
 * @def REDUCE_SUM
 * 
 * Explicitly instantiate a reduction function `f`. Archetype is sum().
 */
#define REDUCE_SUM_INSTANTIATION(f, T) \
    template Array<value_t<T>,0> f(const T&);
#define REDUCE_SUM_INSTANTIATIONS(f, T) \
    REDUCE_SUM_INSTANTIATION(f, ARRAY(T, 2)) \
    REDUCE_SUM_INSTANTIATION(f, ARRAY(T, 1)) \
    REDUCE_SUM_INSTANTIATION(f, ARRAY(T, 0))
#define REDUCE_SUM(f) \
    REDUCE_SUM_INSTANTIATIONS(f, double) \
    REDUCE_SUM_INSTANTIATIONS(f, float) \
    REDUCE_SUM_INSTANTIATIONS(f, int) \
    REDUCE_SUM_INSTANTIATIONS(f, bool)

/**
 * @internal
 * 
 * @def REDUCE_COUNT
 * 
 * Explicitly instantiate a reduction function `f` with integral return type.
 * Archetype is count().
 */
#define REDUCE_COUNT_INSTANTIATION(f, T) \
    template Array<int,0> f(const T&);
#define REDUCE_COUNT_INSTANTIATIONS(f, T) \
    REDUCE_COUNT_INSTANTIATION(f, ARRAY(T, 2)) \
    REDUCE_COUNT_INSTANTIATION(f, ARRAY(T, 1)) \
    REDUCE_COUNT_INSTANTIATION(f, ARRAY(T, 0))
#define REDUCE_COUNT(f) \
    REDUCE_COUNT_INSTANTIATIONS(f, double) \
    REDUCE_COUNT_INSTANTIATIONS(f, float) \
    REDUCE_COUNT_INSTANTIATIONS(f, int) \
    REDUCE_COUNT_INSTANTIATIONS(f, bool)

/**
 * @internal
 * 
 * @def UNARY_EXPLICIT
 * 
 * Explicitly instantiate a unary transformation `f` for all types and sizes,
 * where the result type must be explicitly specified in the case of integral
 * arguments.
 * 
 * For example, `int abs(int)` is *not* in this category, as the result type
 * of `abs` is always the same as the argument type, while `double sin(int)`
 * *is* in this category, as the return type must be explicitly specified in
 * the case of an integral argument.
 */
#define UNARY_EXPLICIT_INSTANTIATION(f, T, U) \
    template promote_t<T,U> f<T>(const U&);
#define UNARY_EXPLICIT_INSTANTIATIONS(f, T, U) \
    UNARY_EXPLICIT_INSTANTIATION(f, T, ARRAY(U, 2)) \
    UNARY_EXPLICIT_INSTANTIATION(f, T, ARRAY(U, 1)) \
    UNARY_EXPLICIT_INSTANTIATION(f, T, ARRAY(U, 0))
#define UNARY_EXPLICIT(f) \
    UNARY_FLOATING_POINT(f) \
    UNARY_EXPLICIT_INSTANTIATIONS(f, double, int) \
    UNARY_EXPLICIT_INSTANTIATIONS(f, double, bool) \
    UNARY_EXPLICIT_INSTANTIATIONS(f, float, int) \
    UNARY_EXPLICIT_INSTANTIATIONS(f, float, bool)

/**
 * @internal
 * 
 * @def BINARY_ARITHMETIC
 * 
 * Explicitly instantiate a binary transformation `f` for all pairs of
 * compatible types.
 */
#define BINARY_ARITHMETIC_INSTANTIATION(f, T, U) \
    template promote_t<T,U> f(const T&, const U&);
#define BINARY_ARITHMETIC_INSTANTIATIONS(f, T, U) \
    BINARY_ARITHMETIC_INSTANTIATION(f, ARRAY(T, 2), ARRAY(U, 2)) \
    BINARY_ARITHMETIC_INSTANTIATION(f, ARRAY(T, 1), ARRAY(U, 1)) \
    BINARY_ARITHMETIC_INSTANTIATION(f, ARRAY(T, 0), ARRAY(U, 0)) \
    BINARY_ARITHMETIC_INSTANTIATION(f, ARRAY(T, 0), U) \
    BINARY_ARITHMETIC_INSTANTIATION(f, T, ARRAY(U, 0))
#define BINARY_ARITHMETIC(f) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, double, double) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, double, float) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, double, int) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, double, bool) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, float, double) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, float, float) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, float, int) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, float, bool) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, int, double) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, int, float) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, int, int) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, int, bool) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, bool, double) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, bool, float) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, bool, int) \
    BINARY_ARITHMETIC_INSTANTIATIONS(f, bool, bool)

/**
 * @internal
 * 
 * @def BINARY_COMPARE
 * 
 * Explicitly instantiate a binary comparison `f` for all pairs of
 * compatible types.
 */
#define BINARY_COMPARE_INSTANTIATION(f, T, U) \
    template Array<bool,dimension_v<T>> f(const T&, const U&);
#define BINARY_COMPARE_INSTANTIATIONS(f, T, U) \
    BINARY_COMPARE_INSTANTIATION(f, ARRAY(T, 2), ARRAY(U, 2)) \
    BINARY_COMPARE_INSTANTIATION(f, ARRAY(T, 1), ARRAY(U, 1)) \
    BINARY_COMPARE_INSTANTIATION(f, ARRAY(T, 0), ARRAY(U, 0)) \
    BINARY_COMPARE_INSTANTIATION(f, ARRAY(T, 0), U) \
    BINARY_COMPARE_INSTANTIATION(f, T, ARRAY(U, 0))
#define BINARY_COMPARE(f) \
    BINARY_COMPARE_INSTANTIATIONS(f, double, double) \
    BINARY_COMPARE_INSTANTIATIONS(f, double, float) \
    BINARY_COMPARE_INSTANTIATIONS(f, double, int) \
    BINARY_COMPARE_INSTANTIATIONS(f, double, bool) \
    BINARY_COMPARE_INSTANTIATIONS(f, float, double) \
    BINARY_COMPARE_INSTANTIATIONS(f, float, float) \
    BINARY_COMPARE_INSTANTIATIONS(f, float, int) \
    BINARY_COMPARE_INSTANTIATIONS(f, float, bool) \
    BINARY_COMPARE_INSTANTIATIONS(f, int, double) \
    BINARY_COMPARE_INSTANTIATIONS(f, int, float) \
    BINARY_COMPARE_INSTANTIATIONS(f, int, int) \
    BINARY_COMPARE_INSTANTIATIONS(f, int, bool) \
    BINARY_COMPARE_INSTANTIATIONS(f, bool, double) \
    BINARY_COMPARE_INSTANTIATIONS(f, bool, float) \
    BINARY_COMPARE_INSTANTIATIONS(f, bool, int) \
    BINARY_COMPARE_INSTANTIATIONS(f, bool, bool)

/**
 * @internal
 * 
 * @def BINARY_SCALAR
 * 
 * Explicitly instantiate a binary comparison `f` for all pairs of
 * compatible types.
 */
#define BINARY_SCALAR_INSTANTIATION(f, T, U) \
    template promote_t<T,U> f(const T&, const U&);
#define BINARY_SCALAR_INSTANTIATIONS(f, T, U) \
    BINARY_SCALAR_INSTANTIATION(f, ARRAY(T, 2), ARRAY(U, 0)) \
    BINARY_SCALAR_INSTANTIATION(f, ARRAY(T, 2), U) \
    BINARY_SCALAR_INSTANTIATION(f, ARRAY(T, 1), ARRAY(U, 0)) \
    BINARY_SCALAR_INSTANTIATION(f, ARRAY(T, 1), U) \
    BINARY_SCALAR_INSTANTIATION(f, ARRAY(T, 0), ARRAY(U, 0)) \
    BINARY_SCALAR_INSTANTIATION(f, ARRAY(T, 0), U) \
    BINARY_SCALAR_INSTANTIATION(f, T, ARRAY(U, 0))
#define BINARY_SCALAR(f) \
    BINARY_SCALAR_INSTANTIATIONS(f, double, double) \
    BINARY_SCALAR_INSTANTIATIONS(f, double, float) \
    BINARY_SCALAR_INSTANTIATIONS(f, double, int) \
    BINARY_SCALAR_INSTANTIATIONS(f, double, bool) \
    BINARY_SCALAR_INSTANTIATIONS(f, float, double) \
    BINARY_SCALAR_INSTANTIATIONS(f, float, float) \
    BINARY_SCALAR_INSTANTIATIONS(f, float, int) \
    BINARY_SCALAR_INSTANTIATIONS(f, float, bool) \
    BINARY_SCALAR_INSTANTIATIONS(f, int, double) \
    BINARY_SCALAR_INSTANTIATIONS(f, int, float) \
    BINARY_SCALAR_INSTANTIATIONS(f, int, int) \
    BINARY_SCALAR_INSTANTIATIONS(f, int, bool) \
    BINARY_SCALAR_INSTANTIATIONS(f, bool, double) \
    BINARY_SCALAR_INSTANTIATIONS(f, bool, float) \
    BINARY_SCALAR_INSTANTIATIONS(f, bool, int) \
    BINARY_SCALAR_INSTANTIATIONS(f, bool, bool)

/**
 * @internal
 * 
 * @def BINARY_COPYSIGN
 * 
 * Explicitly instantiate a binary transformation `f` for all pairs of
 * compatible types, where the return type is that of the first parameter. The
 * archetype is `copysign()`.
 */
#define BINARY_COPYSIGN_INSTANTIATION(f, T, U) \
    template T f(const T&, const U&);
#define BINARY_COPYSIGN_INSTANTIATIONS(f, T, U) \
    BINARY_COPYSIGN_INSTANTIATION(f, ARRAY(T, 2), ARRAY(U, 2)) \
    BINARY_COPYSIGN_INSTANTIATION(f, ARRAY(T, 1), ARRAY(U, 1)) \
    BINARY_COPYSIGN_INSTANTIATION(f, ARRAY(T, 0), ARRAY(U, 0)) \
    BINARY_COPYSIGN_INSTANTIATION(f, ARRAY(T, 0), U) \
    BINARY_COPYSIGN_INSTANTIATION(f, T, ARRAY(U, 0))
#define BINARY_COPYSIGN(f) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, double, double) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, double, float) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, double, int) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, double, bool) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, float, double) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, float, float) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, float, int) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, float, bool) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, int, double) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, int, float) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, int, int) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, int, bool) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, bool, double) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, bool, float) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, bool, int) \
    BINARY_COPYSIGN_INSTANTIATIONS(f, bool, bool)

/**
 * @internal
 * 
 * @def MATRIX_MULTIPLY
 * 
 * Explicitly instantiation matrix multiplications.
 */
#define MATRIX_MULTIPLY_INSTANTIATIONS(f, T) \
    template Array<T,1> f(const Array<T,2>&, const Array<T,1>&); \
    template Array<T,2> f(const Array<T,2>&, const Array<T,2>&);
#define MATRIX_MULTIPLY(f) \
    MATRIX_MULTIPLY_INSTANTIATIONS(f, double) \
    MATRIX_MULTIPLY_INSTANTIATIONS(f, float)

namespace numbirch {

UNARY_ARITHMETIC(operator+)
UNARY_ARITHMETIC(operator-)
BINARY_ARITHMETIC(operator+)
BINARY_ARITHMETIC(operator-)
BINARY_SCALAR(operator*)
MATRIX_MULTIPLY(operator*)
BINARY_SCALAR(operator/)
UNARY_INTEGRAL(operator!)
BINARY_COMPARE(operator==)
BINARY_COMPARE(operator!=)
BINARY_COMPARE(operator<)
BINARY_COMPARE(operator<=)
BINARY_COMPARE(operator>)
BINARY_COMPARE(operator>=)

UNARY_ARITHMETIC(abs)
UNARY_EXPLICIT(acos)
UNARY_EXPLICIT(asin)
UNARY_EXPLICIT(atan)
UNARY_ARITHMETIC(ceil)
UNARY_MATRIX(cholinv)
MATRIX_MULTIPLY(cholmul)
MATRIX_MULTIPLY(cholsolve)
BINARY_COPYSIGN(copysign)
UNARY_EXPLICIT(cos)
UNARY_EXPLICIT(cosh)
REDUCE_COUNT(count)
DIAGONAL_MATRIX(diagonal)
UNARY_EXPLICIT(digamma)
UNARY_EXPLICIT(exp)
UNARY_EXPLICIT(expm1)
UNARY_ARITHMETIC(floor)
BINARY_ARITHMETIC(hadamard)
MATRIX_MULTIPLY(inner)
UNARY_MATRIX(inv)
REDUCE_MATRIX(lcholdet)
REDUCE_MATRIX(ldet)
UNARY_EXPLICIT(lgamma)
UNARY_EXPLICIT(log)
UNARY_EXPLICIT(log1p)
UNARY_EXPLICIT(rcp)
UNARY_EXPLICIT(rectify)
UNARY_ARITHMETIC(round)
UNARY_EXPLICIT(sin)
SINGLE_VECTOR(single)
SINGLE_MATRIX(single)
UNARY_EXPLICIT(sinh)
MATRIX_MULTIPLY(solve)
UNARY_EXPLICIT(sqrt)
REDUCE_SUM(sum)
UNARY_EXPLICIT(tan)
UNARY_EXPLICIT(tanh)
REDUCE_MATRIX(trace)
UNARY_MATRIX(transpose)

}