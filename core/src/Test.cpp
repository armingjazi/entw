#include <string>
#include "Result.h"

#include "Test.h"

namespace entw {
Test::Test(std::string name, entw::Test::signature function)
    : name_(std::move(name)), function_(std::move(function)) {}

ResultPtr Test::operator()() {
  const auto passed = function_();
  return std::make_unique<Result>(passed, name_);
}
} // namespace entw