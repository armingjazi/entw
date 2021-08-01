#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Expect.h"
#include "IReport.h"
#include "ITest.h"
#include "Report.h"
#include "Test.h"

namespace entw {
class TestCase {
public:

  TestCase() = default;
  virtual ~TestCase() = default;

  ReportPtr run() {
    include();
    auto report = std::make_unique<Report>();
    for (auto &&test : tests_) {
      runBeforeEach();
      report->add((*test)());
      runAfterEach();
    }
    return report;
  };

  void test(const std::string &name, const ITest::TestMethod &method, size_t assertions = 1) {
    tests_.emplace_back(std::make_unique<Test>(
        name_.empty() ? name : name_ + ": " + name, method, assertions));
  };

  void setName(const std::string &name) { name_ = name; };

  virtual void include() = 0;

  virtual void runBeforeEach() {};

  virtual void runAfterEach() {};

private:
  std::vector<TestPtr> tests_;
  std::string name_;
};
using TestCasePtr = std::unique_ptr<TestCase>;

} // namespace entw