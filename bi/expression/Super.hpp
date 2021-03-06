/**
 * @file
 */
#pragma once

#include "bi/expression/Expression.hpp"

namespace bi {
/**
 * Keyword `super`.
 *
 * @ingroup expression
 */
class Super: public Expression {
public:
  /**
   * Constructor.
   *
   * @param loc Location.
   */
  Super(Location* loc = nullptr);

  /**
   * Destructor.
   */
  virtual ~Super();

  virtual Expression* accept(Cloner* visitor) const;
  virtual Expression* accept(Modifier* visitor);
  virtual void accept(Visitor* visitor) const;
};
}
