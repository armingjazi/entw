#include "TestRunner.h"

namespace entw {
int TestRunner::run(std::ostream &results) {
  auto failures = 0;
  for (auto const& testCase: testCases_) {
    auto result = testCase->run();
    results << result->full();
    failures += result->countFailures();
    results << "\n";
  }

  return failures ? 1 : 0;
}
void TestRunner::add(TestCasePtr testCase) {
  testCases_.emplace_back(std::move(testCase));
}
} // namespace entw