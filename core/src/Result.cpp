#include <string>
#include <utility>

#include "Result.h"

namespace entw {
Result::Result(bool pass, std::string test_name, std::string detail)
    : passed_(pass),
      name_(std::move(test_name)),
      detail_(std::move(detail)){
}
bool Result::wasSuccessful() const {
  return passed_;
}
std::string Result::asString() const {
  const auto state = std::string(passed_ ? ("\033[32mpassed\033[0m") : ("\033[31mfailed\033[0m"));

  auto result = "[" + state + "] " + name_;

  if (!detail_.empty())
    result += "\n" + detail_;

  return result;
}

} // namespace entw