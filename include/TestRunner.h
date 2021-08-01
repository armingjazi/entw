#pragma once
#include <iostream>
#include <ostream>
#include <vector>

#include "TestCase.h"

namespace entw {
class TestRunner {
public:
  TestRunner() = default;
  ~TestRunner() = default;

  int run(std::ostream &results) {
    auto failures = size_t(0);
    for (auto const &testCase: testCases_) {
      auto result = testCase->run();
      results << result->full();
      failures += result->countFailures();
      results << "\n";
    }

    return failures ? 1 : 0;
  };
  void add(TestCasePtr testCase) {
    testCases_.emplace_back(std::move(testCase));
  };

private:
  std::vector<TestCasePtr> testCases_;
};

} // namespace entw