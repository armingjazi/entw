#pragma once

#include <functional>

#include "IResult.h"
#include "ITest.h"
#include "Result.h"

namespace entw {
class Test : public ITest {
public:
  Test(std::string name, TestMethod function, size_t assertions = 1)
      : name_(std::move(name)), function_(std::move(function)),
        assertions_(assertions) {};
  ~Test() override = default;
  ResultPtr operator()() override {
    bool passed;
    std::string failureReason;
    auto expectFactory = Expect{};
    try {
      function_(expectFactory);
      passed = true;
    } catch (const std::exception &e) {
      failureReason = e.what();
      passed = false;
    }

    if (expectFactory.getAssertionCount() != assertions_) {
      failureReason = "expected " + std::to_string(assertions_) +
          " assertions\nreceived " +
          std::to_string(expectFactory.getAssertionCount());
      passed = false;
    }

    return std::make_unique<Result>(passed, name_, failureReason);
  };

private:
  std::string name_;
  TestMethod function_;
  size_t assertions_;
};
} // namespace entw