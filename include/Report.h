#pragma once

#include <string>
#include <vector>

#include "IResult.h"
#include "IReport.h"

namespace entw {
class Report : public IReport {
public:
  std::string failures() override {
    std::string report;
    for (const auto &r : results_) {
      if (!report.empty())
        report += "\n";
      if (!r->wasSuccessful())
        report += r->asString();
    }
    if (report.empty())
      return "None";
    return report;
  };
  std::size_t countFailures() override {
    std::size_t count = 0;
    for (const auto &r : results_) {
      if (!r->wasSuccessful())
        ++count;
    }
    return count;
  };
  std::string full() override {
    std::string report;
    for (const auto &r : results_) {
      if (!report.empty())
        report += "\n";
      report += r->asString();
    }
    if (report.empty())
      return "No Tests";
    return report;
  };
  void add(ResultPtr result_ptr) override {
    results_.emplace_back(std::move(result_ptr));
  };

private:
  std::vector<ResultPtr> results_;
};
} // namespace entw