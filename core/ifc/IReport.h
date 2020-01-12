#pragma once
#include <string>

namespace entw {
class IReport {
public:
  virtual ~IReport() = default;
  virtual std::string failures() = 0;
  virtual void add(ResultPtr result_ptr) = 0;
};

using ReportPtr = std::unique_ptr<IReport>;
} // namespace entw