#pragma once

#include <functional>
#include <vector>
#include <string>

#include "Test.h"
#include "IReport.h"

namespace entw {
class TestCase {
public:
  TestCase() = default;
  virtual ~TestCase() = default;;

  using test = std::function<bool(void)>;

  ReportPtr run();

  void it(const std::string &name, const test &method);

  virtual void include() = 0;

  virtual void runBeforeEach(){};

  virtual void runAfterEach(){};

private:
  std::vector<Test> tests_;
};
using TestCasePtr = std::unique_ptr<TestCase>;

} // namespace entw