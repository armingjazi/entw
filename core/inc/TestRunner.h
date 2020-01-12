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

  void run(std::ostream &results);
  void add(TestCasePtr testCase);

private:
  std::vector<TestCasePtr> testCases_;
};

} // namespace entw