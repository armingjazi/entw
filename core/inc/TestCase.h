#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Expect.h"
#include "IReport.h"
#include "ITest.h"

namespace entw {
class TestCase {
public:

  TestCase() = default;
  virtual ~TestCase() = default;

  ReportPtr run();

  void it(const std::string &name, const ITest::TestMethod &method, size_t assertions = 1);

  void setName(const std::string &name);

  virtual void include() = 0;

  virtual void runBeforeEach(){};

  virtual void runAfterEach(){};

private:
  std::vector<TestPtr> tests_;
  std::string name_ = "";
};
using TestCasePtr = std::unique_ptr<TestCase>;

} // namespace entw