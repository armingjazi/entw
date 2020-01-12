#include "TestRunner.h"

namespace entw {
void TestRunner::run(std::ostream &results) {
  for (auto const& testCase: testCases_) {
    auto result = testCase->run();
    results << result->full();
    results << "\n";
  }
}
void TestRunner::add(TestCasePtr testCase) {
  testCases_.emplace_back(std::move(testCase));
}
} // namespace entw