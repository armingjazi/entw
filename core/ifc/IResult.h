#pragma once

namespace entw
{
class IResult {
 public:
  virtual ~IResult() = default;;
  virtual bool wasSuccessful() const = 0;
  virtual std::string asString() const = 0;
};
using ResultPtr = std::unique_ptr<IResult>;
} // namespace entw