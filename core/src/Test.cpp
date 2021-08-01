#include "Result.h"
#include "TestCase.h"

#include "Test.h"

namespace entw {
Test::Test(std::string name, TestMethod function, size_t assertions)
    : name_(std::move(name)), function_(std::move(function)),
      assertions_(assertions) {}

ResultPtr Test::operator()() {
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
}
} // namespace entw