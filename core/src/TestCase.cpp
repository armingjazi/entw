#include <map>

#include "Report.h"
#include "TestCase.h"

namespace entw {
ReportPtr TestCase::run() {
  include();
  auto report = std::make_unique<Report>();
  for (auto &&test : tests_) {
    runBeforeEach();
    report->add(test());
    runAfterEach();
  }
  return report;
}
void TestCase::it(const std::string &name, const TestCase::test &method) {
  tests_.emplace_back(name, method);
}
} // namespace entw