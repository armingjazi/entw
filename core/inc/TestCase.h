#include <utility>

#pragma once

#include <functional>
#include <vector>
#include <string>
#include <map>
#include "Test.h"

namespace entw {
class Report {
 public:
  explicit Report(std::vector<std::string> results) : results_(std::move(results)) {

  }
  std::string failures() {
    if (results_.empty())
      return "None";
    std::string report = "";
    for(const auto r : results_) {
      if (report != "")
        report += "\n";
      report += r;
    }
    return report;
  }

  std::vector<std::string> results_;
};
class TestCase {
 public:
  TestCase() = default;
  using test = std::function<bool(void)>;

  Report run();

  void it(const std::string& name, const test &method);

  virtual void include() = 0;

  virtual void runBeforeEach() {};

  virtual void runAfterEach() {};

  std::vector<Test> tests_;
};

} // namespace entw