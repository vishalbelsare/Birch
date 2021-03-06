/**
 * @file
 */
#include "bi/expression/EmptyExpression.hpp"

#include "bi/visitor/all.hpp"

bi::EmptyExpression::EmptyExpression(Location* loc) :
    Expression(new EmptyType(loc), loc) {
  //
}

bi::EmptyExpression::~EmptyExpression() {
  //
}

bi::Expression* bi::EmptyExpression::accept(Cloner* visitor) const {
  return visitor->clone(this);
}

bi::Expression* bi::EmptyExpression::accept(Modifier* visitor) {
  return visitor->modify(this);
}

void bi::EmptyExpression::accept(Visitor* visitor) const {
  visitor->visit(this);
}

bool bi::EmptyExpression::isEmpty() const {
  return true;
}
