/**
 * @file
 */
#pragma once

namespace numbirch {
/**
 * Logical `not`.
 * 
 * @ingroup cpp-raw
 * 
 * @param m Number of rows.
 * @param n Number of columns.
 * @param A Matrix.
 * @param ldA Column stride of `A`.
 * @param[out] B Matrix.
 * @param ldB Column stride of `B`.
 */
void logical_not(const int m, const int n, const bool* A, const int ldA,
    bool* B, const int ldB);

/**
 * Negation.
 * 
 * @ingroup cpp-raw
 * 
 * @tparam T Value type (`double` or `float`).
 * 
 * @param m Number of rows.
 * @param n Number of columns.
 * @param A Matrix.
 * @param ldA Column stride of `A`.
 * @param[out] B Matrix.
 * @param ldB Column stride of `B`.
 */
template<class T>
void neg(const int m, const int n, const T* A, const int ldA, T* B,
    const int ldB);

}