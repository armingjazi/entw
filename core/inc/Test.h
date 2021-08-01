#pragma once

#include <IResult.h>
#include <functional>

#include "ITest.h"

namespace entw {
class Test : public ITest {
public:
  Test(std::string name, TestMethod function, size_t assertions = 1);
  ~Test() override = default;
  ResultPtr operator()() override;

private:
  std::string name_;
  TestMethod function_;
  size_t assertions_;
};
} // namespace entw