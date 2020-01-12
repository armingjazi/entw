#include <string>
#include <utility>

#include "Result.h"

namespace entw {
Result::Result(bool pass, std::string test_name)
    : passed_(pass),
      name_(std::move(test_name)) {
}
bool Result::wasSuccessful() const {
  return passed_;
}
std::string Result::asString() const {
  const auto state = std::string(passed_ ? ("\033[32mpassed\033[0m") : ("\033[31mfailed\033[0m"));
  return "[" + state + "] " + name_;
}

} // namespace entw