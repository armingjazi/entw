#pragma once

#include <functional>

namespace entw {
class TestCase {
 public:
  TestCase() = default;
  using TestMethodType = std::function<void(void)>;

  void run();

  void test(TestMethodType& method);

  virtual void include() = 0;

  TestMethodType testMethod_;
};

} // namespace entw