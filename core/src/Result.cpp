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
  return name_ + (passed_ ? (" passed") : (" failed"));
}

} // namespace entw