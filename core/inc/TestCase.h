#pragma once

#include <string>

namespace entw {
class TestCase {
 public:
  TestCase() = default;
  virtual void run();
  virtual void setUp() = 0;
};

} // namespace entw