#pragma once

#include <functional>
#include <IResult.h>

#include "ITest.h"

namespace entw {
class Test : ITest {
public:
  using It = std::function<void(void) noexcept(false)>;

  Test(std::string name, It function);
  ~Test() override = default;
  ResultPtr operator()() override;

private:
  std::string name_;
  It function_;
};
} // namespace entw