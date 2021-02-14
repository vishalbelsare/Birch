/**
 * @file
 */
#include "libbirch/BiconnectedCollector.hpp"

void libbirch::BiconnectedCollector::visit(Any* o) {
  auto old = o->f.exchangeOr(COLLECTED);
  if (!(old & COLLECTED)) {
    register_unreachable(o);
    o->accept_(*this);
  }
}
