/**
 * Random variate.
 *
 * - Value: Value type.
 */
final class Random<Value> < Expression<Value> {  
  /**
   * Associated distribution.
   */
  p:Distribution<Value>?;

  /**
   * Value.
   */
  x:Value?;
  
  /**
   * Gradient.
   */
  dfdx:Value?;

  /**
   * Log-weight of prior.
   */
  w:Real <- 0.0;

  /**
   * Value assignment.
   */
  operator <- x:Value {
    assert !p?;
    this.x <- x;
  }

  /**
   * Optional value assignment.
   */
  operator <- x:Value? {
    assert !p?;
    this.x <- x;
  }

  /**
   * Does this have a value?
   */
  function hasValue() -> Boolean {
    return x?;
  }

  /**
   * Does this have a distribution?
   */
  function hasDistribution() -> Boolean {
    return p?;
  }
  
  function rows() -> Integer {
    if x? {
      return global.rows(x!);
    } else {
      assert p?;
      return p!.rows();
    }
  }

  function columns() -> Integer {
    if x? {
      return global.columns(x!);
    } else {
      assert p?;
      return p!.columns();
    }
  }

  function distribution() -> Distribution<Value>? {
    return p;
  }

  function set(p:Distribution<Value>) {
    assert !this.p?;
    assert !this.x?;
    this.p <- p;
    this.x <- p.value();
  }

  function value() -> Value {
    if !x? {
      p <- p!.graft();
      x <- p!.value();
      //p <- nil;
    }
    return x!;
  }

  function grad(d:Value) {
    assert x?;
    if p? {
      if dfdx? {
        dfdx <- dfdx! + d;
      } else {
        auto ψ <- p!.lazy(this);
        if ψ? {
          dfdx <- d;
          w <- ψ!.value();
          ψ!.grad(1.0);
        }
      }
    }
  }

  /**
   * Observe the value of the random variate.
   */
  function observe(x:Value) -> Real {
    assert !hasValue();
    assert hasDistribution();
    this.x <- x;
    p <- p!.graft();
    auto w <- p!.observe(x);
    //p <- nil;
    return w;
  }

  /**
   * Evaluate the log probability density (or mass) function, if it exists.
   *
   * - x: The value.
   *
   * Return: the log probability density (or mass).
   */
  function logpdf(x:Value) -> Real {
    p <- p!.graft();
    return p!.logpdf(x);
  }

  /**
   * Evaluate the probability density (or mass) function, if it exists.
   *
   * - x: The value.
   *
   * Return: the probability density (or mass).
   */
  function pdf(x:Value) -> Real {
    p <- p!.graft();
    return p!.pdf(x);
  }

  /**
   * Evaluate the cumulative distribution function at a value.
   *
   * - x: The value.
   *
   * Return: the cumulative probability, if supported.
   */
  function cdf(x:Value) -> Real? {
    p <- p!.graft();
    return p!.cdf(x);
  }

  /**
   * Evaluate the quantile function at a cumulative probability.
   *
   * - P: The cumulative probability.
   *
   * Return: the quantile value, if supported.
   */
  function quantile(P:Real) -> Value? {
    p <- p!.graft();
    return p!.quantile(P);
  }
  
  /**
   * Finite lower bound of the support of this node, if any.
   */
  function lower() -> Value? {
    p <- p!.graft();
    return p!.lower();
  }
  
  /**
   * Finite upper bound of the support of this node, if any.
   */
  function upper() -> Value? {
    p <- p!.graft();
    return p!.upper();
  }

  function graftGaussian() -> Gaussian? {
    if !hasValue() {
      auto q <- p!.graftGaussian();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }
    
  function graftBeta() -> Beta? {
    if !hasValue() {
      auto q <- p!.graftBeta();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }
  
  function graftGamma() -> Gamma? {
    if !hasValue() {
      auto q <- p!.graftGamma();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }
  
  function graftInverseGamma() -> InverseGamma? {
    if !hasValue() {
      auto q <- p!.graftInverseGamma();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  } 

  function graftIndependentInverseGamma() -> IndependentInverseGamma? {
    if !hasValue() {
      auto q <- p!.graftIndependentInverseGamma();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  } 

  function graftInverseWishart() -> InverseWishart? {
    if !hasValue() {
      auto q <- p!.graftInverseWishart();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  } 
  
  function graftNormalInverseGamma() -> NormalInverseGamma? {
    if !hasValue() {
      auto q <- p!.graftNormalInverseGamma();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }
  
  function graftDirichlet() -> Dirichlet? {
    if !hasValue() {
      auto q <- p!.graftDirichlet();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftRestaurant() -> Restaurant? {
    if !hasValue() {
      auto q <- p!.graftRestaurant();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftMultivariateGaussian() -> MultivariateGaussian? {
    if !hasValue() {
      auto q <- p!.graftMultivariateGaussian();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftMultivariateNormalInverseGamma() ->
      MultivariateNormalInverseGamma? {
    if !hasValue() {
      auto q <- p!.graftMultivariateNormalInverseGamma();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftMatrixGaussian() -> MatrixGaussian? {
    if !hasValue() {
      auto q <- p!.graftMatrixGaussian();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftMatrixNormalInverseGamma() -> MatrixNormalInverseGamma? {
    if !hasValue() {
      auto q <- p!.graftMatrixNormalInverseGamma();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftMatrixNormalInverseWishart() -> MatrixNormalInverseWishart? {
    if !hasValue() {
      auto q <- p!.graftMatrixNormalInverseWishart();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftDiscrete() -> Discrete? {
    if !hasValue() {
      auto q <- p!.graftDiscrete();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function graftBoundedDiscrete() -> BoundedDiscrete? {
    if !hasValue() {
      auto q <- p!.graftBoundedDiscrete();
      p <-? Distribution<Value>?(q);
      return q;
    }
    return nil;
  }

  function read(buffer:Buffer) {
    assert !hasDistribution();
    assert !hasValue();
    x <- buffer.get(x);
  }

  function write(buffer:Buffer) {
    if hasValue() {
      buffer.set(value());
    } else if hasDistribution() {
      p!.write(buffer);
    } else {
      buffer.setNil();
    }
  }
}
