/**
 * @file
 */
#pragma once

#include "bi/exception/Exception.hpp"

namespace bi {
/**
 * Driver exception.
 *
 * @ingroup exception
 */
struct DriverException: public Exception {
  /**
   * Default constructor.
   */
  DriverException();

  /**
   * Constructor.
   *
   * @param msg Message.
   */
  DriverException(const std::string& msg);
};
}
