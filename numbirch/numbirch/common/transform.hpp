/**
 * @file
 */
#pragma once

#include "numbirch/transform.hpp"
#include "numbirch/reduce.hpp"
#include "numbirch/common/functor.hpp"

namespace numbirch {
/**
 * @internal
 * 
 * Performs the inverse operation of a scalar broadcast during gradient
 * computation. That is, if a scalar was broadcast during the forward pass,
 * upstream gradients must be aggregated, by summation, during the backward
 * pass.
 */
template<int D, class T>
auto aggregate(const T& x) {
  if constexpr (D == 0 && dimension_v<T> != 0) {
    return sum(x);
  } else {
    return x;
  }
}

/**
 * @internal
 * 
 * Convenience function to apply aggregate to a pair.
 */
template<int D, int E, class T, class U>
auto aggregate(const std::pair<T,U>& x) {
  return std::make_pair(aggregate<D>(x.first), aggregate<E>(x.second));
}

template<class T, class>
bool_t<T> operator!(const T& x) {
  prefetch(x);
  return transform(x, not_functor());
}

template<class T, class>
real_t<T> not_grad(const real_t<T>& g, const bool_t<T>& y,
    const T& x) {
  prefetch(x);
  return transform(g, x, not_grad_functor());
}

template<class T, class U, class>
bool_t<T,U> operator&&(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, and_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> and_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      and_grad_functor()));
}

template<class T, class U, class>
bool_t<T,U> operator||(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, or_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> or_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      or_grad_functor()));
}

template<class T, class U, class>
bool_t<T,U> operator==(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, equal_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> equal_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      equal_grad_functor()));
}

template<class T, class U, class>
bool_t<T,U> operator!=(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, not_equal_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> not_equal_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      not_equal_grad_functor()));
}

template<class T, class U, class>
bool_t<T,U> operator<(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, less_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> less_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      less_grad_functor()));
}

template<class T, class U, class>
bool_t<T,U> operator<=(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, less_or_equal_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> less_or_equal_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      less_or_equal_grad_functor()));
}

template<class T, class U, class>
bool_t<T,U> operator>(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, greater_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> greater_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      greater_grad_functor()));
}

template<class T, class U, class>
bool_t<T,U> operator>=(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, greater_or_equal_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> greater_or_equal_grad(const real_t<T,U>& g,
    const bool_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      greater_or_equal_grad_functor()));
}

template<class T, class>
T abs(const T& x) {
  prefetch(x);
  return transform(x, abs_functor());
}

template<class T, class>
real_t<T> abs_grad(const real_t<T>& g, const T& y, const T& x) {
  prefetch(x);
  return transform(g, x, abs_grad_functor());
}

template<class T, class>
real_t<T> acos(const T& x) {
  prefetch(x);
  return transform(x, acos_functor());
}

template<class T, class>
real_t<T> acos_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, acos_grad_functor());
}

template<class T, class U, class>
implicit_t<T,U> add(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, add_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> add_grad(const real_t<T,U>& g,
    const implicit_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return std::make_pair(aggregate<dimension_v<T>>(g),
      aggregate<dimension_v<U>>(g));
}

template<class T, class>
real_t<T> asin(const T& x) {
  prefetch(x);
  return transform(x, asin_functor());
}

template<class T, class>
real_t<T> asin_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, asin_grad_functor());
}

template<class T, class>
real_t<T> atan(const T& x) {
  prefetch(x);
  return transform(x, atan_functor());
}

template<class T, class>
real_t<T> atan_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, atan_grad_functor());
}

template<class R, class T, class>
explicit_t<R,T> cast(const T& x) {
  prefetch(x);
  return transform(x, cast_functor<R>());
}

template<class T, class>
T ceil(const T& x) {
  prefetch(x);
  return transform(x, ceil_functor());
}

template<class T, class>
real_t<T> ceil_grad(const real_t<T>& g, const T& y, const T& x) {
  prefetch(x);
  return transform(g, x, ceil_grad_functor());
}

template<class T, class U, class>
implicit_t<T,U> copysign(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, copysign_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> copysign_grad(const real_t<T,U>& g,
    const implicit_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      copysign_grad_functor()));
}

template<class T, class>
real_t<T> cos(const T& x) {
  prefetch(x);
  return transform(x, cos_functor());
}

template<class T, class>
real_t<T> cos_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, cos_grad_functor());
}

template<class T, class>
real_t<T> cosh(const T& x) {
  prefetch(x);
  return transform(x, cosh_functor());
}

template<class T, class>
real_t<T> cosh_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, cosh_grad_functor());
}

template<class T, class>
real_t<T> digamma(const T& x) {
  prefetch(x);
  return transform(x, digamma_functor());
}

template<class T, class U, class>
real_t<T,U> digamma(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, digamma_functor());
}

template<class T, class U, class>
implicit_t<T,U> div(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, div_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> div_grad(const real_t<T,U>& g,
    const implicit_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      div_grad_functor()));
}

template<class T, class>
real_t<T> exp(const T& x) {
  prefetch(x);
  return transform(x, exp_functor());
}

template<class T, class>
real_t<T> expm1(const T& x) {
  prefetch(x);
  return transform(x, expm1_functor());
}

template<class T, class>
T floor(const T& x) {
  prefetch(x);
  return transform(x, floor_functor());
}

template<class T, class>
real_t<T> floor_grad(const real_t<T>& g, const T& y, const T& x) {
  prefetch(x);
  return transform(g, x, floor_grad_functor());
}

template<class T, class U, class>
real_t<T,U> gamma_p(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, gamma_p_functor());
}

template<class T, class U, class>
real_t<T,U> gamma_q(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, gamma_q_functor());
}

template<class T, class U, class V, class>
real_t<T,U,V> ibeta(const T& x, const U& y, const V& z) {
  prefetch(x);
  prefetch(y);
  prefetch(z);
  return transform(x, y, z, ibeta_functor());
}

template<class T, class U, class>
real_t<T,U> lbeta(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, lbeta_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> lbeta_grad(const real_t<T,U>& g,
    const real_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      lbeta_grad_functor()));
}

template<class T, class U, class>
real_t<T,U> lchoose(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, lchoose_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> lchoose_grad(const real_t<T,U>& g,
    const real_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      lchoose_grad_functor()));
}

template<class T, class>
real_t<T> lfact(const T& x) {
  prefetch(x);
  return transform(x, lfact_functor());
}

template<class T, class>
real_t<T> lfact_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, lfact_grad_functor());
}

template<class T, class>
real_t<T> lgamma(const T& x) {
  prefetch(x);
  return transform(x, lgamma_functor());
}

template<class T, class>
real_t<T> lgamma_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x,
      lgamma_grad_functor());
}

template<class T, class U, class>
real_t<T,U> lgamma(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, lgamma_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> lgamma_grad(const real_t<T,U>& g,
    const real_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      lgamma_grad_functor()));
}

template<class T, class>
real_t<T> log(const T& x) {
  prefetch(x);
  return transform(x, log_functor());
}

template<class T, class>
real_t<T> log_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, log_grad_functor());
}

template<class T, class>
real_t<T> log1p(const T& x) {
  prefetch(x);
  return transform(x, log1p_functor());
}

template<class T, class>
real_t<T> log1p_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, log1p_grad_functor());
}

template<class T, class U, class>
implicit_t<T,U> mul(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, mul_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> mul_grad(const real_t<T,U>& g,
    const implicit_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      mul_grad_functor()));
}

template<class T, class>
T neg(const T& x) {
  prefetch(x);
  return transform(x, neg_functor());
}

template<class T, class U, class>
real_t<T,U> pow(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, pow_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> pow_grad(const real_t<T,U>& g,
    const real_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return aggregate<dimension_v<T>,dimension_v<U>>(transform_pair(g, x, y,
      pow_grad_functor()));
}

template<class T, class>
T rectify(const T& x) {
  prefetch(x);
  return transform(x, rectify_functor());
}

template<class T, class>
real_t<T> rectify_grad(const real_t<T>& g, const T& y, const T& x) {
  prefetch(x);
  return transform(g, x, rectify_grad_functor());
}

template<class T, class>
T round(const T& x) {
  prefetch(x);
  return transform(x, round_functor());
}

template<class T, class>
real_t<T> round_grad(const real_t<T>& g, const T& y, const T& x) {
  prefetch(x);
  return transform(g, x, round_grad_functor());
}

template<class T, class>
real_t<T> sin(const T& x) {
  prefetch(x);
  return transform(x, sin_functor());
}

template<class T, class>
real_t<T> sin_grad(const real_t<T>& g, const real_t<T>& y,
    const T& x) {
  prefetch(x);
  return transform(g, x, sin_grad_functor());
}

template<class T, class>
real_t<T> sinh(const T& x) {
  prefetch(x);
  return transform(x, sinh_functor());
}

template<class T, class>
real_t<T> sinh_grad(const real_t<T>& g, const real_t<T>& y,
    const T& x) {
  prefetch(x);
  return transform(g, x, sinh_grad_functor());
}

template<class T, class>
real_t<T> sqrt(const T& x) {
  prefetch(x);
  return transform(x, sqrt_functor());
}

template<class T, class>
real_t<T> sqrt_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, sqrt_grad_functor());
}

template<class T, class U, class>
implicit_t<T,U> sub(const T& x, const U& y) {
  prefetch(x);
  prefetch(y);
  return transform(x, y, sub_functor());
}

template<class T, class U, class>
std::pair<real_t<T>,real_t<U>> sub_grad(const real_t<T,U>& g,
    const implicit_t<T,U>& z, const T& x, const U& y) {
  prefetch(g);
  prefetch(x);
  prefetch(y);
  return std::make_pair(aggregate<dimension_v<T>>(g),
      neg(aggregate<dimension_v<U>>(g)));
}

template<class T, class>
real_t<T> tan(const T& x) {
  prefetch(x);
  return transform(x, tan_functor());
}

template<class T, class>
real_t<T> tan_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, tan_grad_functor());
}

template<class T, class>
real_t<T> tanh(const T& x) {
  prefetch(x);
  return transform(x, tanh_functor());
}

template<class T, class>
real_t<T> tanh_grad(const real_t<T>& g, const real_t<T>& y, const T& x) {
  prefetch(x);
  return transform(g, x, tanh_grad_functor());
}

}