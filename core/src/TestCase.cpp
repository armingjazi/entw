#include <map>

#include "ReportFactory.h"
#include "TestCase.h"

namespace entw {
ReportPtr TestCase::run() {
  include();
  auto results = std::vector<std::string>();
  for (auto &&test : tests_) {
    runBeforeEach();
    if (!test()) {
      results.emplace_back(test.name() + " test failed");
    }
    runAfterEach();
  }
  return ReportFactory().makeReport(results);
}
void TestCase::it(const std::string &name, const TestCase::test &method) {
  tests_.emplace_back(name, method);
}
} // namespace entw