#pragma once

#include "IResult.h"

namespace entw {
class Result : public IResult {
public:
  explicit Result(bool successful, std::string test_name);
  ~Result() override = default;
  bool wasSuccessful() const override;
  std::string asString() const override;

private:
  std::string name_;
  bool passed_;
};
} // namespace entw
