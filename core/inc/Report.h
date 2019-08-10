#pragma once

#include <string>
#include <vector>

#include "IReport.h"

namespace entw {
class Report : public IReport {
 public:
  explicit Report(std::vector<std::string> results);
  std::string failures() override;
  ~Report() override = default;
 private:
  std::vector<std::string> results_;
};
} // namespace entw