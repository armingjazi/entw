#pragma once

#include <functional>
#include <IResult.h>

#include "ITest.h"

namespace entw {
class Test : ITest {
 public:
  using signature = std::function<bool(void)>;

  Test(std::string name, signature function);
  ~Test() override = default;
  ResultPtr operator()() override;

 private:
  std::string name_;
  std::function<bool(void)> function_;
};
} // namespace entw