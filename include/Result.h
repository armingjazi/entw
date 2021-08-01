#pragma once

#include <string>

#include "IResult.h"

namespace entw {
class Result : public IResult {
public:
  explicit Result(bool pass, std::string test_name, std::string detail = "") : passed_(pass),
                                                                               name_(std::move(test_name)),
                                                                               detail_(std::move(detail)) {
  };
  ~Result() override = default;
  bool wasSuccessful() const override {
    return passed_;
  };
  std::string asString() const override {
    const auto state = std::string(passed_ ? ("\033[32mpassed\033[0m") : ("\033[31mfailed\033[0m"));

    auto result = "[" + state + "] " + name_;

    if (!detail_.empty())
      result += "\n" + detail_;

    return result;
  };

private:
  std::string name_;
  std::string detail_;
  bool passed_;
};
} // namespace entw
