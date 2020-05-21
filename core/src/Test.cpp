#include <string>
#include "Result.h"

#include "Test.h"

namespace entw {
Test::Test(std::string name, entw::Test::It function)
    : name_(std::move(name)), function_(std::move(function)) {}

ResultPtr Test::operator()() {
  bool passed;
  std::string failureReason;
  try {
    function_();
    passed = true;
  }
  catch (const std::exception& e) {
    failureReason = e.what();
    passed = false;
  }
  return std::make_unique<Result>(passed, name_, failureReason);
}
} // namespace entw