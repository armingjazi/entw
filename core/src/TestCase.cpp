#include "TestCase.h"
#include "Report.h"
#include "Test.h"

namespace entw {
ReportPtr TestCase::run() {
  include();
  auto report = std::make_unique<Report>();
  for (auto &&test : tests_) {
    runBeforeEach();
    report->add((*test)());
    runAfterEach();
  }
  return report;
}

void TestCase::it(const std::string &name,
                  const ITest::TestMethod &method, size_t assertions) {
  tests_.emplace_back(std::make_unique<Test>(
      name_.empty() ? name : name_ + ": " + name, method, assertions));
}

void TestCase::setName(const std::string &name) { name_ = name; }
} // namespace entw