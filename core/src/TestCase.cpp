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
void TestCase::it(const std::string &name, const Test::It &method) {
    tests_.emplace_back(name_.empty()? name : name_ + ": " + name, method);
}
void TestCase::setName(const std::string &name) {
  name_ = name;
}
} // namespace entw