#pragma once
#include "IResult.h"

namespace entw {
class IReport {
public:
  virtual ~IReport() = default;
  virtual std::string failures() = 0;
  virtual std::string full() = 0;
  virtual std::size_t countFailures() = 0;
  virtual void add(ResultPtr result_ptr) = 0;
};

using ReportPtr = std::unique_ptr<IReport>;
} // namespace entw