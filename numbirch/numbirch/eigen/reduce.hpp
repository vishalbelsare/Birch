/**
 * @file
 */
#pragma once

#include "numbirch/reduce.hpp"
#include "numbirch/eigen/eigen.hpp"
#include "numbirch/eigen/transform.hpp"
#include "numbirch/common/functor.hpp"
#include "numbirch/common/element.hpp"

namespace numbirch {

template<class R, class T, class>
Array<R,0> count(const T& x) {
  return make_eigen(x).unaryExpr(count_functor<R>()).sum();
}

template<class R, class T, class>
Array<R,0> sum(const T& x) {
  return make_eigen(x).sum();
}

}