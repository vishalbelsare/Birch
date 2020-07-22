/**
 * Lazy multivariate divide.
 */
operator (y:Expression<Real[_]>/z:Expression<Real>) ->
    Expression<Real[_]> {
  return diagonal(1.0/z, y!.rows())*y;
}

/**
 * Lazy multivariate divide.
 */
operator (y:Real[_]/z:Expression<Real>) -> Expression<Real[_]> {
  return box(y)/z;
}

/**
 * Lazy multivariate divide.
 */
operator (y:Expression<Real[_]>/z:Real) -> Expression<Real[_]> {
  return y/box(z);
}
