/**
 * @file
 */
#include "bi/expression/Span.hpp"

#include "bi/visitor/all.hpp"

bi::Span::Span(Expression* single, Location* loc) :
    Expression(loc),
    Single<Expression>(single) {
  //
}

bi::Span::~Span() {
  //
}

bi::Expression* bi::Span::accept(Cloner* visitor) const {
  return visitor->clone(this);
}

bi::Expression* bi::Span::accept(Modifier* visitor) {
  return visitor->modify(this);
}

void bi::Span::accept(Visitor* visitor) const {
  return visitor->visit(this);
}
