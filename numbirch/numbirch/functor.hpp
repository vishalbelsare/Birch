/**
 * @file
 */
#pragma once

#include "numbirch/function.hpp"

namespace numbirch {
struct negate_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return -x;
  }
};

struct add_functor {
  template<class T, class U>
  HOST DEVICE promote_t<T,U> operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x) + V(y);
  }
};

struct subtract_functor {
  template<class T, class U>
  HOST DEVICE promote_t<T,U> operator()(const T x, const U y)
      const {
    using V = promote_t<T,U>;
    return V(x) - V(y);
  }
};

struct multiply_functor {
  template<class T, class U>
  HOST DEVICE promote_t<T,U> operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x)*V(y);
  }
};

struct divide_functor {
  template<class T, class U>
  HOST DEVICE promote_t<T,U> operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x)/V(y);
  }
};

struct not_functor {
  HOST DEVICE bool operator()(const bool x) const {
    return !x;
  }
};

struct and_functor {
  HOST DEVICE bool operator()(const bool x, const bool y) const {
    return x && y;
  }
};

struct or_functor {
  HOST DEVICE bool operator()(const bool x, const bool y) const {
    return x || y;
  }
};

struct equal_functor {
  template<class T, class U>
  HOST DEVICE bool operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x) == V(y);
  }
};

struct not_equal_functor {
  template<class T, class U>
  HOST DEVICE bool operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x) != V(y);
  }
};

struct less_functor {
  template<class T, class U>
  HOST DEVICE bool operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x) < V(y);
  }
};

struct less_or_equal_functor {
  template<class T, class U>
  HOST DEVICE bool operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x) <= V(y);
  }
};

struct greater_functor {
  template<class T, class U>
  HOST DEVICE bool operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x) > V(y);
  }
};

struct greater_or_equal_functor {
  template<class T, class U>
  HOST DEVICE bool operator()(const T x, const U y) const {
    using V = promote_t<T,U>;
    return V(x) >= V(y);
  }
};

struct abs_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::abs(x);
  }
};

struct acos_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::acos(x);
  }
};

struct asin_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::asin(x);
  }
};

template<class T>
struct atan_functor {
  HOST DEVICE T operator()(const T x) const {
    return std::atan(x);
  }
};

struct ceil_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::ceil(x);
  }
};

struct cos_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::cos(x);
  }
};

struct cosh_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::cosh(x);
  }
};

struct count_functor {
  template<class T>
  HOST DEVICE int operator()(const T x) const {
    return (x == T(0)) ? 0 : 1;
  }
};

template<class T>
struct diagonal_functor {
  diagonal_functor(const T a) :
      a(a) {
    //
  }
  HOST DEVICE T operator()(const int i, const int j) const {
    return (i == j) ? value(a) : T(0);
  }
  const T a;
};

struct digamma_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return digamma(x);
  }
};

struct exp_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::exp(x);
  }
};

struct expm1_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::expm1(x);
  }
};

struct floor_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::floor(x);
  }
};

template<class T>
struct lfact_functor {
  HOST DEVICE T operator()(const int x) const {
    return lfact<T>(x);
  }
};

template<class T>
struct lfact_grad_functor {
  HOST DEVICE T operator()(const T g, const int x) const {
    return lfact_grad(g, x);
  }
};

struct lgamma_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::lgamma(x);
  }
};

struct log_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::log(x);
  }
};

struct log1p_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::log1p(x);
  }
};

struct log_abs_functor {
  template<class T>
  HOST DEVICE T operator()(const T x) const {
    return std::log(std::abs(x));
  }
};

template<class T>
struct log_square_functor {
  HOST DEVICE T operator()(const T x) const {
    return 2.0*std::log(x);
  }
};

template<class T>
struct rcp_functor {
  HOST DEVICE T operator()(const T x) const {
    return rcp(x);
  }
};

template<class T>
struct rectify_functor {
  HOST DEVICE T operator()(const T x) const {
    return rectify(x);
  }
};

template<class T>
struct rectify_grad_functor {
  HOST DEVICE T operator()(const T g, const T x) const {
    return rectify_grad(g, x);
  }
};

template<class T>
struct round_functor {
  HOST DEVICE T operator()(const T x) const {
    return std::round(x);
  }
};

template<class T>
struct sin_functor {
  HOST DEVICE T operator()(const T x) const {
    return std::sin(x);
  }
};

template<class T>
struct sinh_functor {
  HOST DEVICE T operator()(const T x) const {
    return std::sinh(x);
  }
};

template<class T>
struct sqrt_functor {
  HOST DEVICE T operator()(const T x) const {
    return std::sqrt(x);
  }
};

template<class T>
struct tan_functor {
  HOST DEVICE T operator()(const T x) const {
    return std::tan(x);
  }
};

template<class T>
struct tanh_functor {
  HOST DEVICE T operator()(const T x) const {
    return std::tanh(x);
  }
};

template<class T>
struct copysign_functor {
  HOST DEVICE T operator()(const T x, const T y) const {
    return copysign(x, y);
  }
};

template<class T>
struct digammap_functor {
  HOST DEVICE T operator()(const T x, const int y) const {
    return digamma(x, y);
  }
};

template<class T>
struct gamma_p_functor {
  HOST DEVICE T operator()(const T a, const T x) const {
    return gamma_p(a, x);
  }
};

template<class T>
struct gamma_q_functor {
  HOST DEVICE T operator()(const T a, const T x) const {
    return gamma_q(a, x);
  }
};

template<class T>
struct lbeta_functor {
  HOST DEVICE T operator()(const T x, const T y) const {
    return lbeta(x, y);
  }
};

template<class T>
struct lchoose_functor {
  HOST DEVICE T operator()(const int x, const int y) const {
    return lchoose<T>(x, y);
  }
};

template<class T>
struct lchoose_grad_functor {
  HOST DEVICE pair<T> operator()(const T d, const int x, const int y)
      const {
    return lchoose_grad<T>(d, x, y);
  }
};

template<class T>
struct lgammap_functor {
  HOST DEVICE T operator()(const T x, const T y) const {
    return lgamma(x, y);
  }
};

template<class T>
struct pow_functor {
  HOST DEVICE T operator()(const T x, const T y) const {
    return pow(x, y);
  }
};

template<class T>
struct single_functor {
  single_functor(const int* i, const int* j) :
      i(i), j(j) {
    //
  }
  HOST DEVICE T operator()(const int i, const int j) const {
    return (i == *this->i - 1 && j == *this->j - 1) ? T(1) : T(0);
  }
  const int *i, *j;
};

template<class T>
struct ibeta_functor {
  HOST DEVICE T operator()(const T a, const T b, const T x) const {
    return ibeta(a, b, x);
  }
};

template<class T>
struct if_then_else_functor {
  HOST DEVICE T operator()(const bool x, const T y, const T z) const {
    return x ? y : z;
  }
};

template<class T>
struct combine_functor {
  combine_functor(const T a , const T b, const T c, const T d) :
      a(a), b(b), c(c), d(d) {
    //
  }
  HOST DEVICE T operator()(const T w, const T x, const T y, const T z) const {
    return a*w + b*x + c*y + d*z;
  }
  const T a, b, c, d;
};

template<class T>
struct combine4_functor {
  combine4_functor(const T a , const T b, const T c, const T d) :
      a(a), b(b), c(c), d(d) {
    //
  }
  HOST DEVICE T operator()(const quad<T>& o) const {
    return a*o.first + b*o.second + c*o.third + d*o.fourth;
  }
  const T a, b, c, d;
};

}
