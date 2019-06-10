#pragma once

#include <functional>

namespace entw {
class TestCase {
 public:
  TestCase() = default;
  using test = std::function<void(void)>;

  void run();

  void it(test &method);

  virtual void describe() = 0;

  test testMethod_;
};

} // namespace entw