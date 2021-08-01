#pragma once

#include <string>

#include "IResult.h"

namespace entw {
class Result : public IResult {
public:
  explicit Result(bool successful, std::string test_name, std::string detail = "");
  ~Result() override = default;
  bool wasSuccessful() const override;
  std::string asString() const override;

private:
  std::string name_;
  std::string detail_;
  bool passed_;
};
} // namespace entw
